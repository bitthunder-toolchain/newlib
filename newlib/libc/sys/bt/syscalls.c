/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <time.h>
#include <stdio.h>
#include "bt_types.h"
#include "bt_api.h"

//#define BT_LIBC_TRACE

void _exit() {
	while(1);
}

#ifdef BT_LIBC_TRACE
#define TP( s, args... )	BT_kPrint("newlib: %s" s, __func__, ## args)
#else
#define TP( s, args... )
#endif

int _open_r(struct _reent *r, const char *name, int flags, int mode) {
	return bt_sys_open(name, flags, mode);
}

int _close_r(struct _reent *r, int file) {
	return bt_sys_close(file);
}

char **environ; /* pointer to array of char * strings that define the current environment variables */

int _execve_r(struct _reent *r, char *name, char **argv, char **env) {
	return -1;
}

int _fork_r(struct _reent *r) {
	return -1;
}

int _fstat_r(struct _reent *r, int file, struct stat *st) {
	return -1;
}

int _getpid_r(struct _reent *r) {
	return 0;
}

int _isatty_r(struct _reent *r, int file) {
	return -1;
}

int _kill_r(struct _reent *r, int pid, int sig) {
	return -1;
}

int _link_r(struct _reent *r, char *old, char *new) {
	return -1;
}

int _lseek_r(struct _reent *r, int file, int ptr, int dir) {
	return bt_sys_lseek(file, ptr, dir);
}

int _read_r(struct _reent *r, int file, char *ptr, int len) {
	return bt_sys_read(file, ptr, len);
}

int _write_r(struct _reent *r, int file, char *ptr, int len) {
	return bt_sys_write(file, ptr, len);
}

/*caddr_t _sbrk(int incr) {
	BT_kPrint("newlib: _sbrk(%08x);", incr);
	return 0;
	}*/

int _stat_r(struct _reent *r, const char *file, struct stat *st) {
	return -1;
}

int stat(const char *path, struct stat *st) {
	return -1;
}

clock_t _times_r(struct _reent *r, struct tms *buf) {
	return 0;
}

int _unlink_r(struct _reent *r, char *name) {
	return -1;
}

int _wait_r(struct _reent *r, int *status) {
	return -1;
}

int _gettimeofday_r(struct _reent *r, struct timeval *p, struct timezone *z) {
	bt_sys_gettimeofday(p, z);
	return 0;
}

int gettimeofday(struct timeval *p, struct timezone *z) {
	bt_sys_gettimeofday(p, z);
	return 0;
}

int _settimeofday_r(struct _reent *r, struct timeval *p, struct timezone *z) {
	bt_sys_settimeofday(p, z);
	return 0;
}

int settimeofday(struct timeval *p, struct timezone *z) {
	bt_sys_settimeofday(p, z);
	return 0;
}

void *_malloc_r(struct _reent *r, size_t size) {
	void *new = BT_kMalloc(size);
	TP("(%d) : %p;", size, new);
	return new;
}

void _free_r(struct _reent *r,  void *ptr) {
	TP("(%p);", ptr);
	BT_kFree(ptr);
}

void *_realloc_r(struct _reent *r, void *ptr, size_t size) {
	TP("(%p, %d);", ptr, size);
	void *new = BT_kMalloc(size);
	memcpy(new, ptr, size);
	BT_kFree(ptr);
	return new;
}

void *_calloc_r(struct _reent *r, size_t nmemb, size_t size) {
	void *new = BT_kMalloc(size * nmemb);
	TP("(%d); : %p", size, new);
	if(!new) {
		return new;
	}
	memset(new, 0, size * nmemb);
	return new;
}

struct _reent *__getreent(void) {
	struct _reent *tag = BT_GetThreadTag();
	if(!tag) {
		tag = BT_kMalloc(sizeof(struct _reent));
		_REENT_INIT_PTR(tag);
		BT_SetThreadTag(tag);
	}

	return tag;
}

int isatty(int fd) {
	return -1;
}
