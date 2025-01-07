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
	; foloseste eax
	oddSum MACRO n
	LOCAL lp
	push ebx
	push ecx
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	mov eax, n
	mov ebx, 1
	mov ecx, 0
	
	lp:
		; incepe cu 1, creste cu 2 la fiecare rep, pana cand e mai mare sau egal
		add ecx, ebx
		inc ebx
		inc ebx
	cmp ebx, eax
	jb	lp

	mov eax, ecx
	pop ecx
	pop ebx
	ENDM
	
	mov esi, 10
	oddSum esi
	
	;terminarea programului
	push 0
	call exit
end start
