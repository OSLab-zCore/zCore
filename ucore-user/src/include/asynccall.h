#ifndef __ASYNC_CALL_H__
#define __ASYNC_CALL_H__

#include "defs.h"
#include "stdarg.h"
#include "unistd.h"
#include "syscall.h"

struct req_ring_entry
{
    uint64_t opcode;
    uint64_t arg0;
    uint64_t arg1;
    uint64_t arg2;
    uint64_t arg3;
    uint64_t arg4;
    uint64_t arg5;
    uint32_t flags;
    uint32_t user_data;
};

struct comp_ring_entry
{
    uint32_t user_data;
    int32_t result;
};

struct request_ring
{
    uint32_t *khead;
    uint32_t *ktail;
    uint32_t *capacity;
    uint32_t *capacity_mask;
    struct req_ring_entry *entries;
};

struct completion_ring
{
    uint32_t *khead;
    uint32_t *ktail;
    uint32_t *capacity;
    uint32_t *capacity_mask;
    struct comp_ring_entry *entries;
};

struct async_call_buffer
{
    struct request_ring req_ring;
    struct completion_ring comp_ring;
};

struct ring_offsets
{
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    uint32_t capacity_mask;
    uint32_t entries;
};

struct async_call_info
{
    void *user_buf_ptr;
    size_t buf_size;
    struct ring_offsets req_off;
    struct ring_offsets comp_off;
};

int async_call_buffer_init(int req_capacity, int comp_capacity, int worker_num, struct async_call_buffer *buffer);

extern unsigned long long tag;

#define MAX_ARGS 5

enum REQUEST_STATE {
    S_NULL = 0,
    S_INIT = 1,
    S_WORKING = 2,
    S_DONE = 3,
};

static inline unsigned long long async_call(int num, struct req_ring_entry *req, ...)
{
    va_list ap;
    va_start(ap, req);
    size_t a[MAX_ARGS];
    int i;
    for (i = 0; i < MAX_ARGS; i++)
    {
        a[i] = va_arg(ap, size_t);
    }
    va_end(ap);
    req->opcode = num;
    req->flags = S_INIT;
    req->user_data = tag++;
    req->arg0 = a[0];
    req->arg1 = a[1];
    req->arg2 = a[2];
    req->arg3 = a[3];
    req->arg4 = a[4];
    return tag;
}

static inline unsigned long long async_call_write(struct req_ring_entry *req, int fd, const void *addr,
                                    unsigned len, uint64_t offset)
{
    return async_call(SYS_writeat, req, fd, addr, len, offset);
}

static inline unsigned long long async_call_read(struct req_ring_entry *req, int fd, const void *addr,
                                   unsigned len, uint64_t offset)
{
    return async_call(SYS_readat, req, fd, addr, len, offset);
}

struct req_ring_entry *req_ring_get_entry(struct async_call_buffer *buffer, uint32_t idx);

struct comp_ring_entry *comp_ring_get_entry(struct async_call_buffer *buffer, uint32_t idx);

#endif // __ASYNC_CALL_H__
