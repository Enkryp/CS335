
        .global main

        .text

   
L0:
findGCD:
push %rbp
mov %rsp, %rbp
L17:
L18:
L1:
mov $0, %rax
mov %rax, -8(%rbp)
L2:
mov 16(%rbp), %rax
cmp -8(%rbp), %rax
je L4
L3:
jmp L6
L4:
mov 24(%rbp), %rax
leave
ret
L5:
L6:
mov $0, %rax
mov %rax, -16(%rbp)
L7:
mov 16(%rbp), %rax
cmp -16(%rbp), %rax
setne %al
movzb %al, %rax
mov %rax, -24(%rbp)
L8:
mov -24(%rbp), %rax
cmp $0, %rax
jne L10
L9:
jmp L16
L10:
mov 24(%rbp), %rax
mov 16(%rbp), %rbx
cqo
idiv %rbx
mov %rdx, -32(%rbp)
L11:
add $-48, %rsp
push 16(%rbp)
L12:
push -32(%rbp)
L13:
call findGCD
mov %rax, -40(%rbp)
L14:
mov -40(%rbp), %rax
leave
ret
L15:
L16:
L19:
leave
ret
L20:
main:
mov %rsp, %rbp
push %rbp
mov %rsp, %rbp
L21:
mov $5, %rax
mov %rax, -8(%rbp)
L22:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L23:
L24:
mov $100, %rax
mov %rax, -24(%rbp)
L25:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L26:
L27:
add $-48, %rsp
push -16(%rbp)
L28:
push -32(%rbp)
L29:
call findGCD
mov %rax, -40(%rbp)
L30:
mov -40(%rbp), %rax
mov %rax, -48(%rbp)
L31:
L32:
mov -48(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L33:
L34:
L35:


  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
format:
        .ascii  "%lld\n"


