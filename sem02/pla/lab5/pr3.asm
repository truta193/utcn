.386
.model flat, stdcall

includelib msvcrt.lib
extern exit: proc

;Parity flag indicates whether the lowest order byte of the result an arithmetic or bit wise operation 
; has an even or odd number of 1s. Flag = 1 if parity is even; Flag = 0 if parity is odd.
;https://home.adelphi.edu/~siegfried/cs174/174l6.pdf
;idk daca e ok olly arata dubiosenii

public start

.data
nr dw 10
dwl dd 16
.code
start:
	mov ax, 0
	xor esi, esi
	; in bx tinem nr de biti de 1
	xor bx, bx
lp:
	inc esi
	cmp nr, 0
	; sarim peste incremetare daca e par
	jp nocnt
	inc bx
	
nocnt:
	; shift la dreapta sa ca sa trecem cu fiecare bit al word-ului pe pozitia cea mai putin semnificativa pt parity check
    shr nr, 1
	cmp esi, dwl
	jl lp
	
	push 0
	call exit
end start
