
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
EuclidsAlgorithm_findGCD:
push %rbp
mov %rsp, %rbp
L2:
L3:
L4:
mov $0, %rax
mov %rax, -8(%rbp)
L5:
mov 32(%rbp), %rax
mov -8(%rbp), %rbx
cmp %rbx, %rax
je L7
L6:
jmp L9
L7:
mov 40(%rbp), %rax
leave
ret
L8:
L9:
mov $0, %rax
mov %rax, -16(%rbp)
L10:
mov 32(%rbp), %rax
mov -16(%rbp), %rbx
cmp %rbx, %rax
setne %al
movzb %al, %rax
mov %rax, -24(%rbp)
L11:
mov -24(%rbp), %rax
cmp $0, %rax
jne L13
L12:
jmp L19
L13:
mov 40(%rbp), %rax
mov 32(%rbp), %rbx
cqo
idiv %rbx
mov %rdx, -32(%rbp)
L14:
mov %rbp, %rsp
mov $48, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov 32(%rbp), %rax
push %rax
L15:
mov -32(%rbp), %rax
push %rax
L16:
push 24(%rbp)
push 16(%rbp)
call EuclidsAlgorithm_findGCD
mov %rax, -40(%rbp)
L17:
mov -40(%rbp), %rax
leave
ret
L18:
L19:
mov $0, %rax
mov %rax, -48(%rbp)
L20:
mov -48(%rbp), %rax
leave
ret
L21:
L22:
leave
ret
L23:
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
L24:
L25:
mov $100, %rax
mov %rax, -24(%rbp)
L26:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L27:
L28:
mov $134, %rax
mov %rax, -40(%rbp)
L29:
mov -40(%rbp), %rax
mov %rax, -48(%rbp)
L30:
L31:
mov %rbp, %rsp
mov $64, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -32(%rbp), %rax
push %rax
L32:
mov -48(%rbp), %rax
push %rax
L33:
push -8(%rbp)
push -16(%rbp)
call EuclidsAlgorithm_findGCD
mov %rax, -56(%rbp)
L34:
mov -56(%rbp), %rax
mov %rax, -64(%rbp)
L35:
L36:
mov %rbp, %rsp
mov $80, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -64(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L37:
L38:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L39:
L40:


format:
        .ascii  "%ld\n"


