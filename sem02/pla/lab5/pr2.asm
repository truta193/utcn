.386
.model flat, stdcall
;suma sir
includelib msvcrt.lib
extern exit: proc

public start

.data
sir db 5, 7, 2, 9, 2, 6
sirlen dd $-sir
sum db 0

.code
start:
	xor esi, esi
	
lp:
	mov bl, sir[esi]
	inc esi
	add sum, bl
	cmp esi, sirlen
	jl lp
	
	push 0
	call exit
end start
