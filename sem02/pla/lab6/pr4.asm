.386
.model flat, stdcall

includelib msvcrt.lib
extern exit: proc
extern exit: proc
extern fgets: proc
extern fprintf: proc
extern fopen: proc
extern fclose: proc
extern fseek: proc
extern ftell: proc

public start

.data

strbuf db 100 dup(0)
seekline dd 20 dup(0)
maxlen dd 100
finname db "text.in",0
foutname db "text.out",0
readmode db "r",0
writemode db "w",0
writeformat db "%s",0

finaddr dd 0
foutaddr dd 0
; Basically stochez offseturile la fiecare linie intr-un array si dupa parcurg array-ul invers si dupa pot citi liniile in orice ordine vreau
; Dar ceva nu e ok si olly arata doar "DB XX" :( so no debug
.code
start:
	xor eax,eax
	xor ebx,ebx
	xor ecx, ecx
	push offset writemode
	push offset foutname
	call fopen
	add esp, 8
	mov foutaddr, eax ; mutam addr fout
	push offset readmode
	push offset finname
	call fopen
	add esp, 8 
	
	mov finaddr, eax ; mutam addr fin
	
	;push finaddr
	;call ftell
	;add esp, 4
	xor esi, esi
nlloop:
	;	read line
	push finaddr
	push maxlen
	push offset strbuf
	call fgets
	add esp, 12
	
	mov ebx, eax ;ebx stores fgets return val (null if eof)
	
	push finaddr
	call ftell
	add esp, 4
	mov seekline[esi], eax ; keep end of line offset so basically the offset for the start of the next one
	inc esi
	
	cmp ebx, 0
	je printloop


printloop:
	dec esi
	push 0
	push seekline[esi]
	push finaddr
	call fseek
	add esp, 12
	
	push finaddr
	push maxlen
	push offset strbuf
	call fgets
	add esp, 12
	
	push offset strbuf
	push offset writeformat
	push foutaddr
	call fprintf
	add esp, 12
	
	cmp esi, 0
	jne printloop

	; Prima linie de al offset 0 nu e luata in array 
	push 0
	push 0
	push finaddr
	call fseek
	add esp, 12
	
	push finaddr
	push maxlen
	push offset strbuf
	call fgets
	add esp, 12
	
	push offset strbuf
	push offset writeformat
	push foutaddr
	call fprintf
	add esp, 12
	
	


	;close files
	push finaddr
	call fclose
	add esp, 4
	push foutaddr
	call fclose
	add esp, 4
	

	push 0
	call exit
end start


;Am incercat sa inserez o linie, sa dau fseek la inceput si sa inserez urmatoarea dar nu stiu cum sa mut continutul fisierului sa ii fac loc :(
;.386
;.model flat, stdcall
;
;includelib msvcrt.lib
;extern exit: proc
;extern fgets: proc
;extern fprintf: proc
;extern fopen: proc
;extern fclose: proc
;extern fseek: proc
;
;public start
;
;.data
;strbuf db 100 dup(0)
;maxlen dd 100
;finname db "text.in",0
;foutname db "text.out",0
;readmode db "r",0
;writemode db "w",0
;writeformat db "%s",0
;
;finaddr dd 0
;foutaddr dd 0
;
;.code
;start:
;	xor eax,eax
;	xor ebx,ebx
;	xor ecx, ecx
;	push offset writemode
;	push offset foutname
;	call fopen
;	add esp, 8
;	mov foutaddr, eax ; mutam addr fout
;	push offset readmode
;	push offset finname
;	call fopen
;	add esp, 8 
;	
;	mov finaddr, eax ; mutam addr fin
;	
;writeloop:
;	read line
;	push finaddr
;	push maxlen
;	push offset strbuf
;	call fgets
;	add esp, 12
;	
;	cmp eax, 0
;	je done
;	
;	;write line and fseek
;	push 0
;	push 0
;	push foutaddr
;	call fseek
;	add esp, 12
;	
;	push offset strbuf
;	push offset writeformat
;	push foutaddr
;	call fprintf
;	add esp, 12
;
;	jmp writeloop
;	
;	
;done:
;	
;	push finaddr
;	call fclose
;	add esp, 4
;	push foutaddr
;	call fclose
;	add esp, 4
;	
;	push 0
;	call exit
;end start

