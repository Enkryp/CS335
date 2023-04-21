
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
main:
sub $16, %rsp
mov %rsp, %rbp
push %rbp
mov %rsp, %rbp
mov %rbp, %rsp
mov $16, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $0, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -8(%rbp)
mov $0, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -16(%rbp)
L2:
L3:
mov $99567, %rax
mov %rax, -24(%rbp)
L4:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L5:
L6:
mov $1, %rax
mov %rax, -40(%rbp)
L7:
mov -40(%rbp), %rax
mov %rax, -48(%rbp)
L8:
L9:
mov $2, %rax
mov %rax, -56(%rbp)
L10:
mov -56(%rbp), %rax
mov %rax, -64(%rbp)
L11:
L12:
mov -64(%rbp), %rax
mov -64(%rbp), %rbx
imul %rbx, %rax
mov %rax, -72(%rbp)
L13:
mov -72(%rbp), %rax
mov -32(%rbp), %rbx
cmp %rbx, %rax
setle %al
movzb %al, %rax
mov %rax, -80(%rbp)
L14:
mov -80(%rbp), %rax
cmp $0, %rax
jne L16
L15:
jmp L29
L16:
mov -32(%rbp), %rax
mov -64(%rbp), %rbx
cqo
idiv %rbx
mov %rdx, -88(%rbp)
L17:
mov $0, %rax
mov %rax, -96(%rbp)
L18:
mov -88(%rbp), %rax
mov -96(%rbp), %rbx
cmp %rbx, %rax
je L20
L19:
jmp L24
L20:
mov $0, %rax
mov %rax, -104(%rbp)
L21:
mov -104(%rbp), %rax
mov %rax, -48(%rbp)
L22:
jmp L29
L23:
L24:
L25:
mov -64(%rbp), %rax
mov %rax, -112(%rbp)
L26:
mov $1, %rax
mov %rax, -120(%rbp)
L27:
mov -120(%rbp), %rax
mov -112(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L28:
jmp L12
L29:
L30:
mov $2, %rax
mov %rax, -128(%rbp)
L31:
mov -32(%rbp), %rax
mov -128(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -136(%rbp)
L32:
mov -136(%rbp), %rax
cmp $0, %rax
jne L34
L33:
jmp L37
L34:
mov $0, %rax
mov %rax, -144(%rbp)
L35:
mov -144(%rbp), %rax
mov %rax, -48(%rbp)
L36:
L37:
mov %rbp, %rsp
mov $160, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L38:
L39:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L40:
L41:


format:
        .ascii  "%ld\n"


