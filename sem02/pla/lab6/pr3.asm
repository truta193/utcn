.586
.model flat, stdcall

includelib msvcrt.lib
extern exit: proc
extern scanf: proc
extern printf: proc

public start

.data
nrrand dd 0
nrguess dd 0
gmsg db "Mai mare",10,13,0
smsg db "Mai mic",10,13,0
scanformat db "%d",0


.code
start:
	rdtsc 
	;facem numarul mai mic sa nu ne plictisim cat ghicim
	shr eax, 20
	mov nrrand, eax
	
guessl:
	push offset nrguess
	push offset scanformat
	call scanf
	add esp, 8
	
	mov ebx, nrguess
	cmp ebx, nrrand
	jb sml
	ja grt
	je done

sml:
	push offset gmsg
	call printf
	add esp, 4
	jmp guessl
grt:
	push offset smsg
	call printf
	add esp, 4
	jmp guessl
	
done:

	push 0
	call exit
end start
