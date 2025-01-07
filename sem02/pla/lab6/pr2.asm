.386
.model flat, stdcall

includelib msvcrt.lib
extern exit: proc
extern scanf: proc
extern fopen: proc
extern fclose: proc
extern fprintf: proc

public start

.data
stringbuf db 100 dup(0)
scanformat db "%s",0
filename db "text.out",0
filemode db "w+",0

.code
start:
	push offset stringbuf
	push offset scanformat
	call scanf
	add esp, 8
	
	push offset filemode
	push offset filename
	call fopen
	add esp, 8
	
;push string onto stack
	xor ecx,ecx
invloop:
	xor edx, edx
	mov dl, stringbuf[ecx]
	push edx
	inc ecx
	cmp edx, 0
	jne invloop

;pop string from stack
	pop edx ; null char that was pushed
recloop:
	xor ebx, ebx
	pop ebx
	mov stringbuf[edx], bl
	inc edx
	dec ecx
	cmp ecx, 0
	jne recloop
	
	mov ebx, 0 ; set null terminator where it's supposed to be
	mov stringbuf[edx-1], bl
	
	

	mov ebx, eax
	push offset stringbuf
	push offset scanformat
	push eax
	call fprintf
	add esp, 12
	
	
	push ebx
	call fclose
	add esp, 4
	
	push 0
	call exit
end start
