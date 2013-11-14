/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include "bt_types.h"

//#define BT_LIBC_TRACE

void _exit() {
	while(1);
}

#ifdef BT_LIBC_TRACE
#define TP( s, args... )	BT_kPrint(s, ## args)
#else
#define TP( s, args... )
#endif

int _open(const char *name, int flags) {

	TP("newlib0: _open(%s, %08x);", name, flags);

	BT_ERROR Error = 0;
	BT_HANDLE hFile = BT_Open(name, "rb", &Error);

	if(!hFile) {
		TP("newlib: _open: Error opening file.");
		return -1;
	}

	TP("newlib: _open: Success opening file %p.", hFile);

	BT_SetFileDescriptor(3, hFile);

	return 3;
}

int _close(int file) {

	TP("newlib: _close(%d);", file);

	BT_ERROR Error = 0;
	BT_HANDLE hFile = BT_GetFileDescriptor(file, &Error);

	BT_CloseHandle(hFile);
	BT_SetFileDescriptor(file, NULL);

	TP("newlib: _close() succeeded");

	return 0;
}

char **environ; /* pointer to array of char * strings that define the current environment variables */

int _execve(char *name, char **argv, char **env) {
	return -1;
}


int _fork() {
	return -1;
}

int _fstat(int file, struct stat *st) {
	return -1;
}

int _getpid() {
	return 0;
}

int _isatty(int file) {
	return -1;
}

int _kill(int pid, int sig) {
	return -1;
}

int _link(char *old, char *new) {
	return -1;
}

int _lseek(int file, int ptr, int dir) {
	return -1;
}

int _read(int file, char *ptr, int len) {

	BT_ERROR Error = 0;

	TP("newlib: _read(%d, %p, %d);", file, ptr, len);

	BT_HANDLE hFile = BT_GetFileDescriptor(file, &Error);

	Error = 0;

	TP("newlib: Read handle %p", hFile);

	BT_u32 read = BT_Read(hFile, 0, len, ptr, &Error);
	if(!Error) {
		return read;
	}

	return -1;
}

/*caddr_t _sbrk(int incr) {
	BT_kPrint("newlib: _sbrk(%08x);", incr);
	return 0;
	}*/

int _stat(const char *file, struct stat *st) {
	return -1;
}

clock_t _times(struct tms *buf) {
	return 0;
}

int _unlink(char *name) {
	return -1;
}

int _wait(int *status) {
	return -1;
}

int _write(int file, char *ptr, int len) {
	return -1;
}

int _gettimeofday(struct timeval *p, struct timezone *z) {
	return -1;
}

void *_malloc_r(struct reent *r, size_t size) {
	void *new = BT_kMalloc(size);
	TP("newlib: _malloc_r(%d) : %p;", size, new);	
	return new;
}

void _free_r(struct reent *r,  void *ptr) {
	TP("newlib: _free_r(%p);", ptr);
	BT_kFree(ptr);
}

void *_realloc_r(struct reent *r, void *ptr, size_t size) {
	TP("newlib: _realloc_r(%p, %d);", ptr, size);
	void *new = BT_kMalloc(size);
	memcpy(new, ptr, size);
	BT_kFree(ptr);
	return new;
}

void *_calloc_r(struct reent *r, size_t size) {
	TP("newlib: _calloc_r(%d);", size);
	void *new = BT_kMalloc(size);
	memset(new, 0, size);
	return new;
}
