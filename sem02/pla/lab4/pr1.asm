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
sir DB 11, 3, 5, 7, 9

.code
start:
	; initializari
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	lea ebx, sir
	
	;adunam cele 5 numere in al
	add al, byte ptr [ebx]
	inc ebx	
	add al, byte ptr [ebx]
	inc ebx	
	add al, byte ptr [ebx]
	inc ebx	
	add al, byte ptr [ebx]
	inc ebx	
	add al, byte ptr [ebx]
	inc ebx
	;ebx - sir ne va da nr de elem
	;facem impartirea
	sub ebx, offset sir
	div bl
	
	
	
	
	;terminarea programului
	push 0
	call exit
end start
