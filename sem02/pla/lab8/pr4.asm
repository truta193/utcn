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
p dd 1.2, 3, 0, 4.9, 8.27
n EQU ($-p)/4 -1
x dd 5.2
res dd 0
temp dd 0
.code
start:
	xor eax, eax
	finit
	mov eax, p[0]
	add res, eax;Adunam termenul cu x^0 si trecem mai departe
	xor eax, eax
	fld x
	
	lp:
	inc eax
	
	fst ST(1) ; Copiem x
	
	fld p[eax] ; Incarcam coeficientul
	fmul ;Pe ST(0) acum vom avea coeficient * x^eax
	fstp temp ; Adaugam la rezultat termenul si mutam x^eax
	xor ebx, ebx
	mov ebx, temp
	add res, ebx
	
	fld x
	fmul ; Inmultim x^eax cu inca un x pt a trece la uramtoarea putere a lui x
	
	cmp eax, n
	jbe lp
	
	;terminarea programului
	push 0
	call exit
end start
