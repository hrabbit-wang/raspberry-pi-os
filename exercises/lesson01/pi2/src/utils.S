.globl put32
put32:
	str r1,[r0]
	mov pc, lr

.globl get32
get32:
	ldr r0,[r0]
	mov pc, lr

.globl delay
delay:
	subs r0, r0, #1
	bne delay
	mov pc, lr
