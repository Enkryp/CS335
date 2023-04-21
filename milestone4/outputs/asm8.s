
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
mov $1000, %rax
mov %rax, -24(%rbp)
L4:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L5:
L6:
mov $0, %rax
mov %rax, -40(%rbp)
L7:
mov -40(%rbp), %rax
mov %rax, -48(%rbp)
L8:
L9:
mov $1, %rax
mov %rax, -56(%rbp)
L10:
mov -56(%rbp), %rax
mov %rax, -64(%rbp)
L11:
L12:
mov -64(%rbp), %rax
mov -32(%rbp), %rbx
cmp %rbx, %rax
setle %al
movzb %al, %rax
mov %rax, -72(%rbp)
L13:
mov -72(%rbp), %rax
cmp $0, %rax
jne L15
L14:
jmp L24
L15:
mov -64(%rbp), %rax
mov -64(%rbp), %rbx
imul %rbx, %rax
mov %rax, -80(%rbp)
L16:
mov -64(%rbp), %rax
mov -80(%rbp), %rbx
imul %rbx, %rax
mov %rax, -88(%rbp)
L17:
mov -88(%rbp), %rax
mov -48(%rbp), %rbx
add %rbx, %rax
mov %rax, -96(%rbp)
L18:
mov -96(%rbp), %rax
mov %rax, -48(%rbp)
L19:
L20:
mov -64(%rbp), %rax
mov %rax, -104(%rbp)
L21:
mov $1, %rax
mov %rax, -112(%rbp)
L22:
mov -112(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L23:
jmp L12
L24:
L25:
mov %rbp, %rsp
mov $128, %r9
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
L26:
L27:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L28:
L29:


format:
        .ascii  "%ld\n"


