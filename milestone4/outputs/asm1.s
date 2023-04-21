
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
PrimeExample2_checkPrime:
push %rbp
mov %rsp, %rbp
L2:
L3:
mov $0, %rax
mov %rax, -8(%rbp)
L4:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L5:
L6:
L7:
mov $0, %rax
mov %rax, -24(%rbp)
L8:
mov 32(%rbp), %rax
mov -24(%rbp), %rbx
cmp %rbx, %rax
je L13
L9:
jmp L10
L10:
mov $1, %rax
mov %rax, -32(%rbp)
L11:
mov 32(%rbp), %rax
mov -32(%rbp), %rbx
cmp %rbx, %rax
je L13
L12:
jmp L17
L13:
mov $0, %rax
mov %rax, -40(%rbp)
L14:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L15:
L16:
jmp L47
L17:
mov $2, %rax
mov %rax, -48(%rbp)
L18:
mov -48(%rbp), %rax
mov %rax, -56(%rbp)
L19:
mov -56(%rbp), %rax
mov -56(%rbp), %rbx
imul %rbx, %rax
mov %rax, -64(%rbp)
L20:
mov -64(%rbp), %rax
mov 32(%rbp), %rbx
cmp %rbx, %rax
setle %al
movzb %al, %rax
mov %rax, -72(%rbp)
L21:
mov -72(%rbp), %rax
cmp $0, %rax
jne L23
L22:
jmp L39
L23:
mov 32(%rbp), %rax
mov -56(%rbp), %rbx
cqo
idiv %rbx
mov %rdx, -80(%rbp)
L24:
mov $0, %rax
mov %rax, -88(%rbp)
L25:
mov -80(%rbp), %rax
mov -88(%rbp), %rbx
cmp %rbx, %rax
je L27
L26:
jmp L34
L27:
mov $1, %rax
mov %rax, -96(%rbp)
L28:
mov -96(%rbp), %rax
mov -96(%rbp), %rax
neg %rax
mov %rax, -104(%rbp)
mov %rax, -104(%rbp)
L29:
mov %rbp, %rsp
mov $120, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -104(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L30:
mov $1, %rax
mov %rax, -112(%rbp)
L31:
mov -112(%rbp), %rax
mov %rax, -16(%rbp)
L32:
jmp L39
L33:
L34:
L35:
mov -56(%rbp), %rax
mov %rax, -120(%rbp)
L36:
mov $1, %rax
mov %rax, -128(%rbp)
L37:
mov -128(%rbp), %rax
mov -120(%rbp), %rbx
add %rbx, %rax
mov %rax, -56(%rbp)
L38:
jmp L19
L39:
L40:
mov $0, %rax
mov %rax, -136(%rbp)
L41:
mov -16(%rbp), %rax
mov -136(%rbp), %rbx
cmp %rbx, %rax
je L43
L42:
jmp L46
L43:
mov $1, %rax
mov %rax, -144(%rbp)
L44:
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
L45:
L46:
L47:
L48:
leave
ret
L49:
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
L50:
L51:
mov $1, %rax
mov %rax, -24(%rbp)
L52:
mov %rbp, %rsp
mov $40, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -24(%rbp), %rax
push %rax
L53:
push -8(%rbp)
push -16(%rbp)
call PrimeExample2_checkPrime
L54:
mov $3, %rax
mov %rax, -32(%rbp)
L55:
mov %rbp, %rsp
mov $48, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -32(%rbp), %rax
push %rax
L56:
push -8(%rbp)
push -16(%rbp)
call PrimeExample2_checkPrime
L57:
mov $17, %rax
mov %rax, -40(%rbp)
L58:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L59:
push -8(%rbp)
push -16(%rbp)
call PrimeExample2_checkPrime
L60:
mov $20, %rax
mov %rax, -48(%rbp)
L61:
mov %rbp, %rsp
mov $64, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
push %rax
L62:
push -8(%rbp)
push -16(%rbp)
call PrimeExample2_checkPrime
L63:
mov $1000000007, %rax
mov %rax, -56(%rbp)
L64:
mov %rbp, %rsp
mov $72, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -56(%rbp), %rax
push %rax
L65:
push -8(%rbp)
push -16(%rbp)
call PrimeExample2_checkPrime
L66:
L67:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L68:
L69:


format:
        .ascii  "%ld\n"


