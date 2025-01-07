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
rez DW 0
num1 DW 3
num2 DW 4

.code
start:
	;4*3 + 4 * (4 + 7)
	mov AX, 4
	mov CX, AX
	mov BX, 7
	mul num1
	; in ax avem ax*num1
	add rez, ax
	mov ax, cx
	add ax, bx
	mul num2
	add rez, ax
	
	;terminarea programului
	push 0
	call exit
end start
