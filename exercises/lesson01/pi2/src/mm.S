.globl memzero
memzero:
	mov r3, #0
	str r3, [r0], #4
	subs r1, r1, #4
	beq endzero
	ble endzero
	b memzero
endzero:
	mov pc, lr
