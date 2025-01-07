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
n dd 8
res dd 0
temp dd 0
restemp dd 0

.code
start:
	finit
	;aici se scrie codul
	xor eax, eax
	lp:
	inc eax
	mov temp, eax
	fild temp
	fsqrt
	fild temp
	fdivp
	fst restemp
	mov ebx, restemp
	add res, ebx
	
	cmp eax, n
	jbe lp
	
	;terminarea programului
	push 0
	call exit
end start
