#ifndef __USER_LIBS_SYSCALL_H__
#define __USER_LIBS_SYSCALL_H__

struct stat;
struct dirent;
struct timespec;
struct async_call_info;

int sys_exit(int error_code);
int sys_fork(void);
int sys_wait(int pid, int *store);
int sys_exec(const char *name, int argc, const char **argv);
int sys_yield(void);
int sys_kill(int pid);
int sys_getpid(void);
int sys_pgdir(void);
int sys_sleep(unsigned int time);
int sys_gettime(void);
int sys_nanosleep(struct timespec* time);
int sys_open(const char *path, uint32_t open_flags);
int sys_close(int fd);
int sys_read(int fd, void *base, size_t len);
int sys_write(int fd, void *base, size_t len);
int sys_seek(int fd, off_t pos, int whence);
int sys_fstat(int fd, struct stat *stat);
int sys_fsync(int fd);
int sys_getcwd(char *buffer, size_t len);
int sys_getdirentry(int fd, struct dirent *dirent);
int sys_dup(int fd1, int fd2);
void sys_set_priority(uint32_t priority); //only for lab6
void *sys_mmap(void *addr, size_t len, int prot, int flags, int fd, size_t offset);


void sys_block_in_kernel(void);
int sys_setup_async_call(int req_capacity, int comp_capacity, int worker_num, struct async_call_info *info,
                         size_t info_size);

#endif /* !__USER_LIBS_SYSCALL_H__ */
