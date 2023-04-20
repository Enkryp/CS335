
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
L2:
L3:
L4:
L5:
L6:
L7:
EuclidsAlgorithm_f1:
push %rbp
mov %rsp, %rbp
L8:
L9:
L10:
mov $2, %rax
mov %rax, -8(%rbp)
L11:
mov -8(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 0(%r10)
L12:
mov 40(%rbp), %rax
mov 48(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L13:
mov -16(%rbp), %rax
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
L20:
L21:
L22:
L23:
L24:
L25:
E2_f1:
push %rbp
mov %rsp, %rbp
L26:
mov $10, %rax
mov %rax, -8(%rbp)
L27:
mov -8(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 0(%r10)
L28:
L29:
leave
ret
L30:
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
mov $16, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -8(%rbp)
mov $16, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -16(%rbp)
L80:
mov $10, %rax
mov %rax, -24(%rbp)
L81:
mov -24(%rbp), %rax
mov -16(%rbp), %r10
mov %rax, 8(%r10)
L82:
L31:
L32:
mov %rbp, %rsp
mov $40, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $16, %rdi
call malloc@plt
mov %rax, -32(%rbp)
L83:
mov $0, %rax
mov %rax, -40(%rbp)
L84:
mov -40(%rbp), %rax
mov -32(%rbp), %r10
mov %rax, 0(%r10)
L33:
L34:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -16(%rbp)
push -32(%rbp)
call E2_f1
L35:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -32(%rbp), %r10
mov 0(%r10), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L36:
L37:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L38:
L39:


format:
        .ascii  "%ld\n"


