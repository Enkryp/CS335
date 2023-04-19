
        .global main

        .text

   
L0:
L1:
L2:
L3:
Rectangle_getLength:
push %rbp
mov %rsp, %rbp
L4:
mov 16(%rbp), %r10
mov 0(%r10), %rax
leave
ret
L5:
L6:
leave
ret
L7:
Rectangle_getWidth:
push %rbp
mov %rsp, %rbp
L8:
mov 16(%rbp), %r10
mov 8(%r10), %rax
leave
ret
L9:
L10:
leave
ret
L11:
Rectangle_getArea:
push %rbp
mov %rsp, %rbp
L12:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
imul %rbx, %rax
mov %rax, -8(%rbp)
L13:
mov -8(%rbp), %rax
leave
ret
L14:
L15:
leave
ret
L16:
L17:
L18:
L19:
main:
sub $16, %rsp
mov %rsp, %rbp
push %rbp
mov %rsp, %rbp
mov $16, %rdi
call malloc
mov %rax, %r10
mov %r10, -8(%rbp)
mov $0, %rdi
call malloc
mov %rax, %r10
mov %r10, -16(%rbp)
L20:
L21:
mov $10, %rax
mov %rax, -24(%rbp)
L22:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L23:
L24:
mov $20, %rax
mov %rax, -40(%rbp)
L25:
mov -40(%rbp), %rax
mov %rax, -48(%rbp)
L26:
L27:
mov %rbp, %rsp
sub $64, %rsp
mov $16, %rdi
call malloc
mov %rax, -56(%rbp)
L28:
L29:
mov -32(%rbp), %rax
mov -56(%rbp), %r10
mov %rax, 0(%r10)
L30:
mov -48(%rbp), %rax
mov -56(%rbp), %r10
mov %rax, 8(%r10)
L31:
mov %rbp, %rsp
sub $72, %rsp
push -8(%rbp)
push -16(%rbp)
push -56(%rbp)
call Rectangle_getArea
mov %rax, -64(%rbp)
L32:
mov -64(%rbp), %rax
mov %rax, -72(%rbp)
L33:
L34:
mov %rbp, %rsp
sub $88, %rsp
mov -72(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L35:
L36:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L37:
L38:


format:
        .ascii  "%ld\n"


