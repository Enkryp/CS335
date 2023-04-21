
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
mov $8, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -16(%rbp)
mov $8, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -24(%rbp)
L21:
L22:
mov %rbp, %rsp
mov $40, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $8, %rdi
call malloc@plt
mov %rax, -32(%rbp)
L68:
mov $0, %rax
mov %rax, -40(%rbp)
L69:
mov -40(%rbp), %rax
mov -32(%rbp), %r10
mov %rax, 0(%r10)
L23:
L24:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $16, %rdi
call malloc@plt
mov %rax, -48(%rbp)
L70:
mov $100, %rax
mov %rax, -56(%rbp)
L71:
mov -56(%rbp), %rax
mov -48(%rbp), %r10
mov %rax, 0(%r10)
L72:
mov $134, %rax
mov %rax, -64(%rbp)
L73:
mov -64(%rbp), %rax
mov -48(%rbp), %r10
mov %rax, 8(%r10)
L25:
L26:
mov %rbp, %rsp
mov $80, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %r10
mov 0(%r10), %rax
push %rax
L27:
mov -48(%rbp), %r10
mov 8(%r10), %rax
push %rax
L28:
push -8(%rbp)
push -16(%rbp)
push -48(%rbp)
call EuclidsAlgorithm_f1
mov %rax, -72(%rbp)
L29:
mov -72(%rbp), %rax
mov -32(%rbp), %r10
mov %rax, 0(%r10)
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


