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
TWO dd 2
ONE dd 1
THREE dd 3

.code
start:
	fild TWO
	fild ONE
	fild THREE
	fdivp ;Aici avem 1/3 deasupra de 2 in stiva
	f2xm1 ; Se face 2 ^ 1/3 - 1
	fild ONE
	faddp ;Adunam 1 si ramane 2 ^ 1/3
	;Pentru 5 ^ 1/3 se foloseste formula a^b
	
	push 0
	call exit
end start
