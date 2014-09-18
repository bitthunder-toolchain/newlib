#include "include/bt_types.h"
#include <stdlib.h>
#include "include/bt_syscall.h"

#define WEAK	__attribute__((weak))

/**
 *	This file does the SYSCALL magic, allowing the libc-syscall layer to be identical between bt- and bitthunder- compiler variants.
 **/

int bt_sys_open(const char *name, int flags, int mode) {
	// This helper function gets the arguments into the correct registers before making the syscall :)
	int result;
	DO_SYSCALL(BT_SYS_open, result);
	return result;
}

int bt_sys_close(int fd) {
	int result;
	DO_SYSCALL(BT_SYS_close, result);
	return result;
}

int bt_sys_lseek(int fd, int ptr, int dir) {
	int result;
	DO_SYSCALL(BT_SYS_lseek, result);
	return result;
}

int bt_sys_read(int fd, char *ptr, int len) {
	int result;
	DO_SYSCALL(BT_SYS_read, result);
	return result;
}

int bt_sys_write(int fd, const char *ptr, int len) {
	int result;
	DO_SYSCALL(BT_SYS_write, result);
	return result;
}
