section .data
ovfl_msg dd 'O','v','e','r','f','l','o','w',' ', 'd', 'e','t','e','c','t','e','d','.',' ','E','x','i','t','i','n','g','.','.','.',0
nwl dd 0xd, 0xa
TRIANGULO EQU 1
DOIS dd 2

section .bss
B resd 1
H resd 1
R resd 1

section .text
global _start
_start:
;INPUT
push B
call ReadInteger
add esp, 4
;INPUT
push H
call ReadInteger
add esp, 4
;LOAD
mov eax, dword[B]
;MUL
imul dword[H]
jbe sys_overflow
%if TRIANGULO
;DIV
cdq
idiv dword[DOIS]
%endif
;STORE
mov dword[R], eax
;OUTPUT
push dword[R]
call PrintInteger
add esp, 4
;STOP
sys_exit:
mov eax, 1
mov ebx, 0
int 80h

ReadChar:
    enter 0,0
    pusha
    mov eax, 3
    mov ebx, 0
    mov ecx, [EBP+8] 
    mov edx, 1
    int 80h
    popa
    leave
    ret

PrintChar:
    enter 0,0
    pusha
    mov eax,4
    mov ebx,1
    mov ecx,[EBP+8]
    mov edx,1
    int 80h
    popa
    leave
    ret
    
ReadString:
    enter 0,0
    pusha
    mov eax,0
read:
    mov ecx,[EBP+8]
    mov ebx,eax
    shl ebx,2
    add ecx,ebx
    push ecx
    call ReadChar
    add esp,4
    inc eax
    cmp dword [ecx],0xa
    jne read
    mov dword [ecx],0
    popa
    add esp, 4
    leave
    ret    
    
PrintString:
    enter 0,0
    push eax
    mov eax,[EBP+8]
write:
    push eax
    call PrintChar
    add esp,4
    add eax,4
    cmp dword [eax],0
    jnz write
    pop eax
    add esp, 4
    leave
    ret
    
    
ReadInteger:
	enter 5,0
	pusha
	mov ebx,ebp
	sub ebx,1
	mov dword [EBP-5],0
ReadInt:
	push ebx
	call ReadChar
	add esp,4
	cmp byte [EBP-1],0xa
	je DoneInt
	mov eax, [EBP-5]
	mov edx,eax
	shl eax,2
	add eax,eax
	add eax,edx
	add eax,edx
	mov [EBP-5],eax
	mov eax,[EBP-1]
	sub eax,0x30
	add [EBP-5],eax
	jmp ReadInt
DoneInt:
	mov eax,[EBP-5]
	mov ebx,[EBP+8]
	mov [ebx],eax 
	popa
	leave
	ret

PrintInteger:
	enter 0,0
	pusha
	mov ebx,esp
	mov eax,[EBP+8]
	mov edx, 0
	push edx
	mov ecx,10
mod:
	mov edx,0
	div ecx
	add edx,0x30
	push edx
	cmp eax,0
	jnz mod
	push esp
	call PrintString
	add esp,4
	mov esp,ebx
	popa
	leave
	ret

sys_overflow:
    push ovfl_msg
    call PrintString
    add esp, 4
    jmp sys_exit

	

