
.global main

.text
main:
    push %rbp
    mov %rsp, %rbp
    
    mov $0x11, %eax
    mov $258, %rbx
    mov $9, %ch
    
    mov $0, %eax    # код возврата 0
    pop %rbp
    ret
