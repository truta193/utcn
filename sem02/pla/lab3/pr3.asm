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
;aici declaram date

.code
start:
	mov eax, 12345678h
	
	xor ebx, ebx
	xchg al, bl
	rol ebx, 8
	ror eax, 8
	xchg al, bl
	rol ebx, 8
	ror eax, 8
	xchg al, bl
	rol ebx, 8
	ror eax, 8
	xchg al, bl

	xchg eax, ebx

	push 0
	call exit
end start
