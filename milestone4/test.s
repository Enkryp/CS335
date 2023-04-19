
        .global main

        .text

   
L0:
L1:
main:
push %rbp
mov %rsp, %rbp
L2:
L3:
mov $1000, %rax
mov %rax, -8(%rbp)
L4:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L5:
L6:
mov %rbp, %rsp
sub $32, %rsp
push 32(%rbp)
mov -16(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L7:
L8:
leave
ret
L9:
L10:


format:
        .ascii  "%ld\n"


