.globl _start
.extern main
.extern exit

_start:
	bl main
	bl exit

_loop:
	b _loop
