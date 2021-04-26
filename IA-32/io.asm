;########################################################################################

ReadChar:
    enter 0,0                   ; Enter stack frame
    push ebx                    ; Save all used registers
    push ecx
    push edx
                                ; Sys call settings
    mov eax, 3                  ; File descriptor
    mov ebx, 0                  ; Read mode
    mov ecx, [ebp + 8]          ; Char logical address on memory
    mov edx, 1                  ; Amount of chars to be printed

    int 80h                     ; Software interruption

    mov dword[ecx + 4], 0       ; Make char NULL terminated

    mov eax, 1                  ; Return value to eax (1 char read)

    pop edx                     ; Restore used registers
    pop ecx
    pop ebx

    leave                       ; Destroy stack frame
    ret                         ; Return without poping arguments

PrintChar:
    enter 0,0                   ; Enter stack frame

    push ebx                    ; Save all used registers
    push ecx
    push edx
                                ; Sys call settings
    mov eax, 4                  ; File descriptor
    mov ebx, 1                  ; Write mode
    mov ecx, [EBP+8]            ; Char logical address on memory
    mov edx, 1                  ; Amount of chars to be printed

    int 80h                     ; Software interruption

    mov eax, 1                  ; Return value to eax (1 char printed)

    pop edx                     ; Restore used registers
    pop ecx
    pop ebx

    leave                       ; Destroy stack frame
    ret                         ; Return without poping arguments

;########################################################################################

PrintString:
    enter 0, 0                      ; Enter stack frame
    push ebx                        ; Save all used registers
    push ecx
    push edx

    mov ecx, [ebp + 8]              ; String logical address on memory
    mov eax, -1                     ; String size init

    find_size1:
        inc eax                     ; Increase string size
        cmp DWORD[ecx+eax*4], 0x00  ; Compare with \0
        je  found1                  ; string[i] == \0
        jmp find_size1              ; loop

    found1:
    push eax                        ; Save bytes size
    shl eax, 2                      ; size *4
    mov edx, eax                    ; Config sys_call - move size to edx
    mov eax, 4                      ; File descriptor
    mov ebx, 1                      ; Write mode

    int 80h                         ; Software interruption

    pop eax                         ; Restore bytes size (to return)

    pop edx                         ; Restore used registers
    pop ecx
    pop ebx

    leave                           ; Destroy stack frame
    ret                             ; Return without poping arguments

ReadString:
    enter 0,0                       ; Enter stack frame

    push ebx                        ; Save all used registers
    push ecx
    push edx

    mov eax, 0                      ; Clears string size
    mov ecx,[EBP+8]                 ; Read string address
    sub ecx, 4                      ; Align string starting address to loop
    read:
    add ecx, 4                      ; Go to next character
    push eax                        ; Save eax (string size)
    push ecx                        ; Push ecx as argument
    call ReadChar                   ; Read character
    add esp, 4                      ; Clears parameters
    pop eax                         ; Restore string size
    inc eax                         ; Increase string size (to return)
    cmp dword[ecx], 0xa             ; Compare with '\n'
    jne read                        ; If diff read next char
    mov dword[ecx], 0               ; Move '\0' to end of string
    dec eax

    pop edx                         ; Restore used registers
    pop ecx
    pop ebx

    leave                           ; Destroy stack frame
    ret                             ; Return without poping arguments

;########################################################################################

PrintInteger:
    enter 0, 0                      ; Enter stack frame
    push ebx                        ; Save all used registers
    push ecx
    push edx

    mov eax, [ebp + 8]              ; Integer logical address in memory
    ;mov eax, dword[ecx]             ; Integer itself to eax

    cmp eax, 0                      ; Compare with 0 (print '-' or not)
    jge pprint

    push eax                        ; Save number
    push 0x2D                       ; Print '-' ASCII Char
    push esp
    call PrintChar
    add  esp, 8
    pop  eax                        ; Restore number
    neg  eax                        ; Get 2's complement of integer

    pprint:
    mov ebx, 10                     ; Divisor to ebx
    mov ecx, 0                      ; Clears amount of digits
    push ecx                        ; Push '\0' to make string
    new_dig:
    inc ecx                         ; Increase amount of digits
    mov edx, 0                      ; Clears edx
    div ebx                         ; Make division
    add edx, 0x30                   ; Convert to char
    push edx                        ; Push char to stack
    cmp eax, 0                      ; Compare quotient with 0
    jnz new_dig                     ; if != 0 get new digit
    push esp                        ; push top of stack
    call PrintString
    add esp, 4

    mov  eax, ecx                   ; Move return value to eax
    mov  ebx, ebp                   ; Move esp to restore registers
    sub  ebx, 12
    mov  esp, ebx

    pop edx                         ; Restore used registers
    pop ecx
    pop ebx

    leave                           ; Destroy stack frame
    ret                             ; Return without poping arguments


ReadInteger:
    enter 12, 0                     ; Enter stack frame
    push ebx                        ; Save all used registers
    push edx
    push ecx
    mov ecx, [ebp+8]
    mov dword[ecx], 0               ; Init local variables
    mov dword[ebp-4], 0             ; numero ebp - 4
    mov dword[ebp-8], 1             ; casas ebp - 8

    read_dig_loop:
    mov dword[ebp-4], 0

    mov eax, 3                      ; Syscall to read one digit (byte)
    mov ebx, 0
    mov ecx, ebp
    sub ecx, 4
    mov edx, 1
    int 80h

    cmp dword[ebp-4], 0x0A          ; Compare input with '\n'
    je done_dig_loop

    cmp dword[ebp-4], 0x2D          ; Compare input with '-'
    jne cont_conv_dig
    mov dword[ebp-12], 0xFF         ; Flag set
    jmp read_dig_loop               ; Skip to next character

    cont_conv_dig:
    sub dword[ebp-4], 0x30          ; Convert to number
    mov ecx, [ebp+8]
    mov eax, [ecx]
    mov ecx, [ebp-8]
    mul ecx
    add eax, dword[ebp-4]
    mov ecx, [ebp+8]
    mov dword[ecx], eax	            ; Update

    mov dword[ebp-8], 10

    jmp read_dig_loop

    done_dig_loop:
    cmp dword[ebp-12], 0xFF
    jne cont_exit_l
    mov ecx, [ebp+8]
    neg dword[ecx]
    cont_exit_l:
    pop ecx                         ; Restore used registers
    pop edx
    pop ebx
    leave                           ; Destroy stack frame
    ret                             ; Return without poping arguments

sys_overflow:
    push ovfl_msg
    call PrintString
    add esp, 4
    jmp sys_exit
