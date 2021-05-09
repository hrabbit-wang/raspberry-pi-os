#include "mm.h"

.section ".text.boot"

.globl _start
_start:
	mrc	p15, 0, r0, c0, c0, 5	// MPIDR (Multiprocessor Affinity Reg)
	// mrs	r0, mpidr_el1		
	and	r0, r0,#0xFF		// Check processor id
	cmp r0, #0x0		// Hang for all non-primary CPU
	beq master
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	ldr	r0, =bss_begin
	ldr	r1, =bss_end
	sub	r1, r1, r0
	bl 	memzero

	mov	sp, #LOW_MEMORY 
	bl	kernel_main
	b 	proc_hang		// should never come here
