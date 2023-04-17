
        .global main

        .text
main:
   
mov $1, %rax
mov %rax, 8(%rsp)
mov $31, %rax
mov %rax, 16(%rsp)
mov 8(%rsp), %rax
mov 16(%rsp), %cl
sal %cl, %rax
mov %rax, 24(%rsp)
mov 24(%rsp), %rax
neg %rax
mov %rax, 32(%rsp)
mov 32(%rsp), %rax
mov %rax, 40(%rsp)
mov $100, %rax
mov %rax, 48(%rsp)
mov $7, %rax
mov %rax, 56(%rsp)
mov 48(%rsp), %rax
mov 56(%rsp), %rbx
cqo
idiv %rbx
mov %rdx, 64(%rsp)
mov 64(%rsp), %rax
mov %rax, 72(%rsp)
mov 72(%rsp), %rax
add 40(%rsp), %rax
mov %rax, 80(%rsp)
mov 80(%rsp), %rax
mov %rax, 88(%rsp)
mov 88(%rsp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
mov $100, %rax
mov %rax, 96(%rsp)
mov $7, %rax
mov %rax, 104(%rsp)
mov 96(%rsp), %rax
mov 104(%rsp), %rbx
cqo
idiv %rbx
mov %rdx, 112(%rsp)
mov 112(%rsp), %rax
mov %rax, 72(%rsp)
mov 72(%rsp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
mov $1, %rax
mov %rax, 120(%rsp)
mov $30, %rax
mov %rax, 128(%rsp)
mov 120(%rsp), %rax
mov 128(%rsp), %cl
sal %cl, %rax
mov %rax, 136(%rsp)
mov $1, %rax
mov %rax, 144(%rsp)
mov $31, %rax
mov %rax, 152(%rsp)
mov 144(%rsp), %rax
mov 152(%rsp), %cl
sal %cl, %rax
mov %rax, 160(%rsp)
mov 160(%rsp), %rax
imul 136(%rsp), %rax
mov %rax, 168(%rsp)
mov $1, %rax
mov %rax, 176(%rsp)
mov $59, %rax
mov %rax, 184(%rsp)
mov 176(%rsp), %rax
mov 184(%rsp), %cl
sal %cl, %rax
mov %rax, 192(%rsp)
mov 168(%rsp), %rax
mov 192(%rsp), %rbx
cqo
idiv %rbx
mov %rax, 200(%rsp)
mov 200(%rsp), %rax
mov %rax, 72(%rsp)
mov 72(%rsp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
mov $121, %rax
mov %rax, 208(%rsp)
mov $10, %rax
mov %rax, 216(%rsp)
mov 208(%rsp), %rax
mov 216(%rsp), %rbx
cqo
idiv %rbx
mov %rdx, 224(%rsp)
mov 224(%rsp), %rax
mov %rax, 72(%rsp)
mov 72(%rsp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
mov $121, %rax
mov %rax, 232(%rsp)
mov 232(%rsp), %rax
neg %rax
mov %rax, 240(%rsp)
mov $10, %rax
mov %rax, 248(%rsp)
mov 248(%rsp), %rax
neg %rax
mov %rax, 256(%rsp)
mov 240(%rsp), %rax
mov 256(%rsp), %rbx
cqo
idiv %rbx
mov %rax, 264(%rsp)
mov 264(%rsp), %rax
mov %rax, 72(%rsp)
mov 72(%rsp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
mov $121, %rax
mov %rax, 272(%rsp)
mov 272(%rsp), %rax
neg %rax
mov %rax, 280(%rsp)
mov $10, %rax
mov %rax, 288(%rsp)
mov 280(%rsp), %rax
mov 288(%rsp), %rbx
cqo
idiv %rbx
mov %rdx, 296(%rsp)
mov 296(%rsp), %rax
mov %rax, 72(%rsp)
mov 72(%rsp), %rax
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


