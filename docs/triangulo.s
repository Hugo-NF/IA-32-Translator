section .data
TRIANGULO EQU 1
DOIS dd 2
section .bss
B resd 5
H resd 1
R resd 1
section .text
global _start
_start:
PLACEHOLDER INPUT
PLACEHOLDER INPUT
PLACEHOLDER LOAD
PLACEHOLDER MUL
%if TRIANGULO
PLACEHOLDER DIV
%endif
PLACEHOLDER STORE
PLACEHOLDER OUTPUT

mov eax, 1
mov ebx, 0
int 80h

