/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
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

struct flag_mask {
	BT_u32 flag;
	BT_u32 mask;
};

#define FLAGS_DEFAULT BT_FS_MODE_READ			// In c flags = 0 mean read only.

static const struct flag_mask libc_to_bt_flags[] = {
	{BT_FS_MODE_WRITE, 						~(BT_FS_MODE_READ)},		// O_RDONLY
	{BT_FS_MODE_READ | BT_FS_MODE_WRITE, 	0},							// O_RDWR
	{0, 0},
	{BT_FS_MODE_APPEND, 					0},							// O_APPEND
	{0, 0},																// _FMARK
	{0, 0},																// _FDEFER
	{0, 0},																// _FASYNC
	{0, 0},																// _FSHLOCK
	{0, 0},																// _FEXLOCK
	{BT_FS_MODE_CREATE,						0},							// O_CREAT
	{BT_FS_MODE_TRUNCATE, 					0},							// O_TRUNC
};

static BT_u32 convert_flags(int flags) {
	BT_u32 i;
	BT_u32 bt_flags = FLAGS_DEFAULT;

	for(i = 0; i < sizeof(libc_to_bt_flags)/sizeof(struct flag_mask); i++) {
		if((1 << i) & flags) {
			if(libc_to_bt_flags[i].mask) {
				bt_flags &= libc_to_bt_flags[i].mask;
			}

			bt_flags |= libc_to_bt_flags[i].flag;
		}
	}

	return bt_flags;
}

int _open_r(struct _reent *r, const char *name, int flags, int mode) {

	BT_ERROR Error = 0;

	BT_s32 fd = BT_AllocFileDescriptor();
	if(fd < 0) {
		TP("(%s, %08x) : %d [Could not allocate file descriptor]", name, flags, -1);
		return -1;
	}

	TP("(%s, %08x) : %d", name, flags, fd);

	BT_u32 bt_flags = convert_flags(flags);

	BT_HANDLE hFile = BT_Open(name, bt_flags, &Error);
	if(!hFile) {
		TP("(): Error opening file.");
		BT_FreeFileDescriptor(fd);
		return -1;
	}

	BT_SetFileDescriptor(fd, hFile);

	return (int) fd;
}

int _close_r(struct _reent *r, int file) {

	TP("(%d);", file);

	BT_ERROR Error = 0;
	BT_HANDLE hFile = BT_GetFileDescriptor(file, &Error);

	BT_CloseHandle(hFile);
	BT_SetFileDescriptor(file, NULL);
	BT_FreeFileDescriptor(file);

	return 0;
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

	BT_ERROR Error = 0;

	TP("(%d, %d, %d);", file, ptr, dir);

	BT_HANDLE hFile = BT_GetFileDescriptor(file, &Error);

	Error = 0;

	TP("(): Seek handle %p", hFile);

	Error = BT_Seek(hFile, ptr, dir);
	if(!Error) {
		return 0;
	}

	return -1;
}

int _read_r(struct _reent *r, int file, char *ptr, int len) {

	BT_ERROR Error = 0;

	TP("(%d, %p, %d);", file, ptr, len);

	BT_HANDLE hFile = BT_GetFileDescriptor(file, &Error);

	Error = 0;

	TP("(): Read handle %p", hFile);

	BT_u32 read = BT_Read(hFile, 0, len, ptr, &Error);
	if(!Error) {
		return read;
	}

	return -1;
}

int _write_r(struct _reent *r, int file, char *ptr, int len) {
	BT_ERROR Error = 0;

	TP("(%d, %p, %d)", file, ptr, len);

	BT_HANDLE hFile = BT_GetFileDescriptor(file, &Error);

	Error = 0;

	TP("(): Write handle %p", hFile);

	BT_u32 written = BT_Write(hFile, 0, len, ptr, &Error);
	if(!Error) {
		return written;
	}

	return -1;
}

/*caddr_t _sbrk(int incr) {
	BT_kPrint("newlib: _sbrk(%08x);", incr);
	return 0;
	}*/

int _stat_r(struct _reent *r, const char *file, struct stat *st) {
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
	return -1;
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