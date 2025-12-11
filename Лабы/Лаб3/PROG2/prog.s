.global main

main:
        movl $0xaf, %eax    # Работаем с EAX
        mov $512, %rbx      # Работаем с RBX
        movb $9, %cl        # Работаем с CL
        
        add $16, %rbx       # RBX = 512 + 16 = 528
        
        # Переносим результат в EAX для корректного возврата
        mov $0, %eax        # Код возврата 0 (успех)
        ret
