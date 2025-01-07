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
	xor ecx, ecx
	xor edx, edx
	mov ecx, 10
	mov edx, 5
	
	;fastcall foloseste ecx edx, vom pastra rez. in eax
	isDiv PROC 
	push eax
	push ebx
	
	xor eax, eax
	xor ebx, ebx
	mov eax, ecx
	mov ebx, edx
	div ebx
	
	mov eax, edx
	
	pop ebx
	pop eax
	ret
	isDiv ENDP
	

	
	call isDiv
	
	;terminarea programului
	push 0
	call exit
end start
