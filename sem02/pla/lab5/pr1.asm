.386
.model flat, stdcall

includelib msvcrt.lib
extern exit: proc

public start

.data
sir dw 4, 9 , -7, 3, 21, -66, 56
lensir dd $-sir
max dw 0
min dw 0

.code
start:
	xor esi, esi
	mov ax, sir[esi]
	mov bx, sir[esi]
	
	floop:
		inc esi
		cmp ax, sir[esi]
		jl dpmax
		mov ax, sir[esi]
	dpmax:
		cmp bx, sir[esi]
		jg dpmin
		mov bx, sir[esi]
	dpmin:
		cmp esi, lensir
		jb floop
		
	mov max, ax
	mov min, bx
		
	
	push 0
	call exit
end start
