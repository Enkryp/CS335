
        .global main

        .text

   
L0:
main:
sub $16, %rsp
mov %rsp, %rbp
push %rbp
mov %rsp, %rbp
L1:
mov $1000, %rax
mov %rax, -8(%rbp)
L2:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L3:
L4:
mov $1, %rax
mov %rax, -24(%rbp)
L5:
mov -24(%rbp), %rax
add -16(%rbp), %rax
mov %rax, -32(%rbp)
L6:
mov -40(%rbp), %rax
imul -32(%rbp), %rax
mov %rax, -48(%rbp)
L7:
mov %rbp, %rsp
sub $64, %rsp
mov -48(%rbp), %rdi
call malloc
mov %rax, -56(%rbp)
L8:
L9:
mov $0, %rax
mov %rax, -64(%rbp)
L10:
mov $0, %rax
mov %rax, -72(%rbp)
L11:
mov $0, %rax
mov %rax, -80(%rbp)
L12:
mov -80(%rbp), %rax
add -72(%rbp), %rax
mov %rax, -88(%rbp)
L13:
mov -56(%rbp), %rax
mov -64(%rbp), %rbx
add %rbx, %rax
mov -88(%rbp), %rbx
mov %rbx, (%rax)
L14:
mov $0, %rax
mov %rax, -96(%rbp)
L15:
mov $0, %rax
mov %rax, -104(%rbp)
L100:
mov -56(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -112(%rbp)
L101:
mov -56(%rbp), %rax
mov -112(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -120(%rbp)
L16:
mov -56(%rbp), %rax
mov -96(%rbp), %rbx
add %rbx, %rax
mov -120(%rbp), %rbx
mov %rbx, (%rax)
L17:
mov $1, %rax
mov %rax, -128(%rbp)
L18:
mov -128(%rbp), %rax
mov %rax, -136(%rbp)
L19:
L20:
mov -136(%rbp), %rax
cmp -16(%rbp), %rax
setle %al
movzb %al, %rax
mov %rax, -144(%rbp)
L21:
mov -144(%rbp), %rax
cmp $0, %rax
jne L23
L22:
jmp L33
L23:
mov $1, %rax
mov %rax, -152(%rbp)
L24:
mov -136(%rbp), %rax
sub -152(%rbp), %rax
mov %rax, -160(%rbp)
L177:
mov -40(%rbp), %rax
imul -160(%rbp), %rax
mov %rax, -168(%rbp)
L25:
mov -136(%rbp), %rax
imul -136(%rbp), %rax
mov %rax, -176(%rbp)
L26:
mov -136(%rbp), %rax
imul -176(%rbp), %rax
mov %rax, -184(%rbp)
L147:
mov -56(%rbp), %rax
mov -168(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -192(%rbp)
L27:
mov -184(%rbp), %rax
add -192(%rbp), %rax
mov %rax, -200(%rbp)
L299:
mov -40(%rbp), %rax
imul -136(%rbp), %rax
mov %rax, -208(%rbp)
L28:
mov -56(%rbp), %rax
mov -208(%rbp), %rbx
add %rbx, %rax
mov -200(%rbp), %rbx
mov %rbx, (%rax)
L29:
L30:
mov $1, %rax
mov %rax, -216(%rbp)
L31:
mov -136(%rbp), %rax
add -216(%rbp), %rax
mov %rax, -136(%rbp)
L32:
jmp L20
L33:
L131:
mov -40(%rbp), %rax
imul -16(%rbp), %rax
mov %rax, -224(%rbp)
L130:
mov -56(%rbp), %rax
mov -224(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -232(%rbp)
L34:
mov %rbp, %rsp
sub $248, %rsp
mov -232(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L35:
L36:
L37:
L38:


  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
format:
        .ascii  "%lld\n"


