
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
mov $9876541, %rax
mov %rax, -24(%rbp)
L4:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L5:
mov $0, %rax
mov %rax, -40(%rbp)
L6:
mov -40(%rbp), %rax
mov %rax, -48(%rbp)
L7:
L8:
L9:
mov $0, %rax
mov %rax, -56(%rbp)
L10:
mov -32(%rbp), %rax
mov -56(%rbp), %rbx
cmp %rbx, %rax
setne %al
movzb %al, %rax
mov %rax, -64(%rbp)
L11:
mov -64(%rbp), %rax
cmp $0, %rax
jne L13
L12:
jmp L26
L13:
mov $10, %rax
mov %rax, -72(%rbp)
L14:
mov -32(%rbp), %rax
mov -72(%rbp), %rbx
cqo
idiv %rbx
mov %rdx, -80(%rbp)
L15:
mov -80(%rbp), %rax
mov %rax, -88(%rbp)
L16:
L17:
mov $10, %rax
mov %rax, -96(%rbp)
L18:
mov -96(%rbp), %rax
mov -48(%rbp), %rbx
imul %rbx, %rax
mov %rax, -104(%rbp)
L19:
mov -88(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov %rax, -112(%rbp)
L20:
mov -112(%rbp), %rax
mov %rax, -48(%rbp)
L21:
mov $10, %rax
mov %rax, -120(%rbp)
L22:
mov -32(%rbp), %rax
mov -120(%rbp), %rbx
cqo
idiv %rbx
mov %rax, -128(%rbp)
L23:
mov -128(%rbp), %rax
mov %rax, -32(%rbp)
L24:
L25:
jmp L9
L26:
mov %rbp, %rsp
mov $144, %r9
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
L27:
mov $2, %rax
mov %rax, -136(%rbp)
L28:
mov -48(%rbp), %rax
mov -136(%rbp), %cl
sal %cl, %rax
mov %rax, -144(%rbp)
L29:
mov %rbp, %rsp
mov $160, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -144(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L30:
L31:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L32:
L33:


format:
        .ascii  "%ld\n"


