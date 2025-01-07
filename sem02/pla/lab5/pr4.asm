.386
.model flat, stdcall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;includem biblioteci, si declaram ce functii vrem sa importam
includelib msvcrt.lib
extern exit: proc
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;declaram simbolul start ca public - de acolo incepe executia
public start
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;sectiunile programului, date, respectiv cod
.data
sir db "Hello there, general Kenobi"
sirlen dd $-sir
subsir db "Hello"
sublen dd $ - sir

.code
start:
	mov esi, offset sir - 1
    mov edi, offset subsir - 1
    mov ecx, -1
	
iloop:
	mov edi, offset subsir
	xor ecx, ecx
	inc esi
	
jloop:
	inc edi
	mov al, byte ptr [edi]
	cmp byte ptr [esi], al
	inc ecx
	jne iloop
	cmp ecx, sublen
	jne jloop
	

done:
	
	push 0
	call exit
end start
