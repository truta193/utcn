.386
.model flat, stdcall

includelib msvcrt.lib
extern exit: proc
extern printf: proc
extern scanf: proc

public start
.data
n1 dd 0
n2 dd 0
initmsg db "Introduceti 2 numere: ", 0
scanformat db "%d %d", 0
printformat db "%d", 0

;S ̆a se scrie ˆın limbaj de asamblare un program care cere utilizatorului 2 numere, de
;la tastatur ̆a, apoi afis, eaz ̆a suma acestora pe ecran.
.code
start:
	push offset initmsg
	call printf
	add esp, 4
	
	push offset n1
	push offset n2
	push offset scanformat
	call scanf
	add esp, 12
	
	xor ebx, ebx
	add ebx, n1
	add ebx, n2
	
	push ebx
	push offset printformat
	call printf
	add esp, 8
	
	
	
	push 0
	call exit
end start
