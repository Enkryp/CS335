
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
functionandIfElse_function1:
push %rbp
mov %rsp, %rbp
L2:
mov $0, %rax
mov %rax, -8(%rbp)
L3:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L4:
L5:
mov -16(%rbp), %rax
mov %rax, -24(%rbp)
L6:
L7:
mov -16(%rbp), %rax
mov -24(%rbp), %rbx
add %rbx, %rax
mov %rax, -32(%rbp)
L8:
mov -32(%rbp), %rax
leave
ret
L9:
L10:
leave
ret
L11:
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
L12:
L13:
mov %rbp, %rsp
mov $32, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -16(%rbp)
call functionandIfElse_function1
mov %rax, -24(%rbp)
L14:
mov $5, %rax
mov %rax, -32(%rbp)
L15:
mov $8, %rax
mov %rax, -40(%rbp)
L16:
mov -40(%rbp), %rax
mov -32(%rbp), %rbx
imul %rbx, %rax
mov %rax, -48(%rbp)
L17:
mov %rbp, %rsp
mov $64, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rdi
call malloc@plt
mov %rax, -56(%rbp)
L18:
L19:
mov $0, %rax
mov %rax, -64(%rbp)
L20:
mov $8, %rax
mov %rax, -72(%rbp)
L21:
mov -72(%rbp), %rax
mov -64(%rbp), %rbx
imul %rbx, %rax
mov %rax, -80(%rbp)
L22:
mov -56(%rbp), %rax
mov -80(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -88(%rbp)
L23:
mov -88(%rbp), %rax
mov %rax, -96(%rbp)
L24:
L25:
mov $1, %rax
mov %rax, -104(%rbp)
L26:
mov $8, %rax
mov %rax, -112(%rbp)
L27:
mov -112(%rbp), %rax
mov -104(%rbp), %rbx
imul %rbx, %rax
mov %rax, -120(%rbp)
L28:
mov -56(%rbp), %rax
mov -120(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -128(%rbp)
L29:
mov -128(%rbp), %rax
mov %rax, -136(%rbp)
L30:
L31:
mov -136(%rbp), %rax
mov -96(%rbp), %rbx
add %rbx, %rax
mov %rax, -144(%rbp)
L32:
mov -144(%rbp), %rax
mov %rax, -152(%rbp)
L33:
L34:
mov -152(%rbp), %rax
mov %rax, -160(%rbp)
L35:
L36:
L37:
mov -152(%rbp), %rax
mov %rax, -160(%rbp)
L38:
L39:
L40:
mov -152(%rbp), %rax
mov %rax, -168(%rbp)
L41:
L42:
L43:
mov -152(%rbp), %rax
mov %rax, -160(%rbp)
L44:
L45:
mov $5, %rax
mov %rax, -176(%rbp)
L46:
mov -176(%rbp), %rax
mov -96(%rbp), %rbx
add %rbx, %rax
mov %rax, -184(%rbp)
L47:
mov -184(%rbp), %rax
mov %rax, -192(%rbp)
L48:
L49:
mov $2, %rax
mov %rax, -200(%rbp)
L50:
mov -192(%rbp), %rax
mov -200(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -208(%rbp)
L51:
mov -208(%rbp), %rax
cmp $0, %rax
jne L53
L52:
jmp L57
L53:
mov $5, %rax
mov %rax, -216(%rbp)
L54:
mov -216(%rbp), %rax
mov %rax, -192(%rbp)
L55:
L56:
jmp L60
L57:
mov $10, %rax
mov %rax, -224(%rbp)
L58:
mov -224(%rbp), %rax
mov %rax, -192(%rbp)
L59:
L60:
L61:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L62:
L63:


format:
        .ascii  "%ld\n"


