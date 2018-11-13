section .data
N2 dd -5

section .bss
N1 resd 1
N3 resd 2
N4 resd 1

section .text
global _start
_start:
ROT:
PLACEHOLDER INPUT
push eax
mov eax, [N1]
mov [N4], eax
pop eax

ROT2:
push eax
mov eax, [N2]
mov [N3], eax
pop eax

push eax
mov eax, [N3]
mov [N3+1], eax
pop eax

PLACEHOLDER OUTPUT

mov eax, 1
mov ebx, 0
int 80h

