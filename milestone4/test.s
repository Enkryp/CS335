
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
mov 40(%rbp), %rax
mov 48(%rbp), %rbx
add %rbx, %rax
mov %rax, -8(%rbp)
L11:
mov -8(%rbp), %rax
leave
ret
L12:
L13:
leave
ret
L14:
L15:
L16:
L17:
L18:
L19:
L20:
L21:
L22:
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
mov $16, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -8(%rbp)
mov $16, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -16(%rbp)
L78:
mov $10, %rax
mov %rax, -24(%rbp)
L79:
mov -24(%rbp), %rax
mov -16(%rbp), %r10
mov %rax, 8(%r10)
L80:
L24:
L25:
mov %rbp, %rsp
mov $40, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $16, %rdi
call malloc@plt
mov %rax, -32(%rbp)
L81:
mov $0, %rax
mov %rax, -40(%rbp)
L82:
mov -40(%rbp), %rax
mov -32(%rbp), %r10
mov %rax, 0(%r10)
L26:
L27:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $16, %rdi
call malloc@plt
mov %rax, -48(%rbp)
L83:
mov $100, %rax
mov %rax, -56(%rbp)
L84:
mov -56(%rbp), %rax
mov -48(%rbp), %r10
mov %rax, 0(%r10)
L85:
mov $134, %rax
mov %rax, -64(%rbp)
L86:
mov -64(%rbp), %rax
mov -48(%rbp), %r10
mov %rax, 8(%r10)
L87:
L28:
L29:
mov %rbp, %rsp
mov $80, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %r10
mov 0(%r10), %rax
push %rax
L30:
mov -48(%rbp), %r10
mov 8(%r10), %rax
push %rax
L31:
push -8(%rbp)
push -16(%rbp)
push -48(%rbp)
call EuclidsAlgorithm_f1
mov %rax, -72(%rbp)
L32:
mov -72(%rbp), %rax
mov -32(%rbp), %r10
mov %rax, 0(%r10)
L33:
mov -32(%rbp), %r10
mov 0(%r10), %rax
mov -16(%rbp), %r10
mov 8(%r10), %rbx
add %rbx, %rax
mov %rax, -80(%rbp)
L34:
mov %rbp, %rsp
mov $96, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -80(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
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


