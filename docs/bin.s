section .data
DOIS dd 2

section .bss
OLD_DATA resd 1
NEW_DATA resd 1
TMP_DATA resd 1

section .text
global _start
_start:
PLACEHOLDER INPUT
mov eax, [OLD_DATA]

L1:
PLACEHOLDER DIV
mov [NEW_DATA], eax

PLACEHOLDER MUL
mov [TMP_DATA], eax

mov eax, [OLD_DATA]

sub eax, [TMP_DATA]

mov [TMP_DATA], eax

PLACEHOLDER OUTPUT
push eax
mov eax, [NEW_DATA]
mov [OLD_DATA], eax
pop eax

mov eax, [OLD_DATA]

cmp eax, 0
jns L1


mov eax, 1
mov ebx, 0
int 80h

