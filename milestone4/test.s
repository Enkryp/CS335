
        .global main

        .text
main:
   
mov $2, %rax
mov %rax, 8(%rsp)
mov 8(%rsp), %rax
mov %rax, 16(%rsp)
mov $32, %rax
mov %rax, 24(%rsp)
mov 24(%rsp), %rax
neg %rax
mov %rax, 32(%rsp)
mov 32(%rsp), %rax
mov %rax, 40(%rsp)
mov 40(%rsp), %rax
mov 16(%rsp), %cl
shr %cl, %rax
mov %rax, 48(%rsp)
mov 48(%rsp), %rax
mov %rax, 56(%rsp)
mov 40(%rsp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
mov 56(%rsp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   


  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
format:
        .ascii  "%d\n"


