#include <barrier.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <file.h>
#include <ulib.h>
#include <asynccall.h>

// #define BUFFER_ENTRIES (1)
// #define BS (0x1000)
#define MAX_INSIZE (0x1000000)
#define MAX_ID (0x10000)
int BUFFER_ENTRIES = 64;
int BS = 0x1000;
int INSIZE = 0x1000000;
#define ID_MAX (INSIZE / BS)
#define min(a, b) (a > b ? b : a)

int FD;

int hash(char *buf)
{
    int i, checksum = 0;
    for (i = 0; i < BS / 32; ++i)
    {
        checksum ^= *(int *)(buf + 4 * i);
    }
    return checksum;
}

int rand_buffer(char *buf)
{
    int i;
    for (i = 0; i < BS / 32; ++i)
    {
        *(int *)(buf + 4 * i) = rand();
    }
    return 0;
}

int init_buffer(char *buf, int *check)
{
    int i;
    for (i = 0; i < ID_MAX; ++i)
    {
        rand_buffer(&buf[BS * i]);
        check[i] = hash(&buf[BS * i]);
    }
    return 0;
}

int write_file(struct async_call_buffer *buffer, char *buf)
{
    int rid = 0, cid = 0;
    while (cid < ID_MAX)
    {
        int ocid = cid;
        int orid = rid;
        while (*buffer->comp_ring.khead < smp_load_acquire(buffer->comp_ring.ktail))
        {
            int cached_head = *buffer->comp_ring.khead;
            struct comp_ring_entry *comp = comp_ring_get_entry(buffer, cached_head);
            if (comp->result != BS)
            {
                // cprintf("written length error %d != %d user_data = %d\n", comp->result, BS, comp->user_data);
                return 1;
            }
            smp_store_release(buffer->comp_ring.khead, cached_head + 1);
            cid++;
        }
        if (ocid != cid) {
            // cprintf("writes finished: %d\n", cid - ocid);
        } 
        while (rid < ID_MAX && *buffer->req_ring.ktail <
                                   (smp_load_acquire(buffer->req_ring.khead) + BUFFER_ENTRIES))
        {
            int cached_tail = *buffer->req_ring.ktail;
            struct req_ring_entry *req = req_ring_get_entry(buffer, cached_tail);
            async_call_write(req, FD, &buf[BS * rid], BS, rid * BS);
            rid++;
            smp_store_release(buffer->req_ring.ktail, cached_tail + 1);
        }
        if (orid != rid) {
            // cprintf("write requests commit: %d\n", rid - orid);
        }
        yield();
    }
    cputs("write check over");
    return 0;
}

int check_file(struct async_call_buffer *buffer, char *buf, int *check)
{
    int rid = 0, cid = 0;
    while (cid < ID_MAX)
    {
        int ocid = cid;
        int orid = rid;
        while (*buffer->comp_ring.khead < smp_load_acquire(buffer->comp_ring.ktail))
        {
            int cached_head = *buffer->comp_ring.khead;
            struct comp_ring_entry *comp = comp_ring_get_entry(buffer, cached_head);
            if (comp->result != BS)
            {
                // cputs("read length error");
                return 1;
            }
            if (hash(&buf[BS * cid]) != check[cid])
            {
                // cprintf("read content error: %d != %d\n", hash(&buf[BS * cid]), check[cid]);
                return 1;
            }
            cid++;
            smp_store_release(buffer->comp_ring.khead, cached_head + 1);
        }
        if (ocid != cid) {
            // cprintf("read finished: %d", cid - ocid);
        } 
        while (rid < ID_MAX && *buffer->req_ring.ktail <
                                   (smp_load_acquire(buffer->req_ring.khead) + BUFFER_ENTRIES))
        {
            int cached_tail = *buffer->req_ring.ktail;
            struct req_ring_entry *req = req_ring_get_entry(buffer, cached_tail);
            async_call_read(req, FD, &buf[BS * rid], BS, rid * BS);
            rid++;
            smp_store_release(buffer->req_ring.ktail, cached_tail + 1);
        }
        if (orid != rid) {
            // cprintf("read requests commit: %d\n", rid - orid);
        } 
        yield();
    }
    // cputs("read check over");
    return 0;
}

char buf[MAX_INSIZE];
int check[MAX_ID];

int run_test(struct async_call_buffer *buffer, int seed)
{
    int ret;
    memset(buf, 0, INSIZE);
    srand(seed);
    init_buffer(buf, check);
    ret = write_file(buffer, buf);
    if (ret != 0)
        return ret;
    memset(buf, 0, INSIZE);
    return check_file(buffer, buf, check);
}

static inline int isdigit(int c)
{
	return '0' <= c && c <= '9';
}

static int atoi(char *s)
{
	int i = 0;
	while (isdigit(*s))
		i = i * 10 + *(s++) - '0';
	return i;
}

int main(int argc, char *argv[])
{
    cputs("Usage: read_after_write INSIZE BS BUFFER_ENTRIES");
    FD = open("tmp.txt", O_RDWR | O_CREAT);
    if (FD < 0)
    {
        cputs("open file error");
        return FD;
    }
    cputs("tmp file created!");
    if (argc != 4) {
        cprintf("Usage: read_after_write INSIZE BS BUFFER_ENTRIES\n");
        return 0;
    }
    INSIZE = atoi(argv[1]);
    BS = atoi(argv[2]);
    BUFFER_ENTRIES = atoi(argv[3]);
    if (INSIZE > MAX_INSIZE || ID_MAX > MAX_ID || BS < 32 || BS > INSIZE || (INSIZE % BS) != 0) {
        cputs("Invalid parameters");
        return 0;
    }
    struct async_call_buffer buffer;
    int ret = async_call_buffer_init(BUFFER_ENTRIES, BUFFER_ENTRIES << 1, 0, &buffer);
    if (ret != 0)
    {
        cputs("setup error");
        return ret;
    }
    cputs("test start!");
    int t0 = sys_times();
    ret = run_test(&buffer, strlen(argv[0]));
    int t1 = sys_times();
    if (ret != 0)
    {
        cputs("result error");
        return ret;
    }
    close(FD);
    cprintf("Simple test: OK, insize = %d, bs = %d, entry = %d, time_delta = %d", 
        INSIZE, BS, BUFFER_ENTRIES, t1 - t0);
    return 0;
}