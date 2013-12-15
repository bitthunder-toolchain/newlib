#ifndef _BT_SYSCALL_H_
#define _BT_SYSCALL_H_

#ifndef __thumb__
#define DO_SYSCALL(nr, resvar)	__asm__ __volatile__ ("svc %[flag]" : "=r"(resvar) : [flag] "I"(nr))
#else
#define DO_SYSCALL
#endif

#define BT_SYS_yield	0
#define BT_SYS_getpid	1
#define BT_SYS_open		2
#define BT_SYS_close	3
#define BT_SYS_read		4
#define BT_SYS_write	5
#define BT_SYS_klog		6
#define BT_SYS_sleep	7
#define BT_SYS_gpioset	8

#endif
