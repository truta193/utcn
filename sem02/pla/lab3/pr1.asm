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
; 7 * 7 - 2 * 8 - 8/8
	mov eax, 7
	mov ebx, 8
	
	mov ecx, 7
	; eax * 7, in eax
	mul ecx
	
	;mutam ebx in ecx
	mov ecx, ebx
	
	;7*eax se schimba cu 8
	xchg eax, ebx
	mov edx, 2
	mul edx
	
	;in ebx e 7*eax, in eax e 2 * ebx
	sub ebx, eax
	;in ebx e 7eax - 2ebx
	mov eax, ecx
	mov edx, 8
	div edx
	sub ebx, eax
	;terminarea programului
	push 0
	call exit
end start
