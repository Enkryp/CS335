
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
mov $10, %rax
mov %rax, -24(%rbp)
L4:
mov $100, %rax
mov %rax, -32(%rbp)
L5:
mov -32(%rbp), %rax
mov -24(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L6:
mov $8, %rax
mov %rax, -48(%rbp)
L7:
mov -48(%rbp), %rax
mov -40(%rbp), %rbx
imul %rbx, %rax
mov %rax, -56(%rbp)
L8:
mov %rbp, %rsp
mov $72, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -56(%rbp), %rdi
call malloc@plt
mov %rax, -64(%rbp)
L9:
L10:
mov $0, %rax
mov %rax, -72(%rbp)
L11:
mov $0, %rax
mov %rax, -80(%rbp)
L12:
mov -32(%rbp), %rax
mov -72(%rbp), %rbx
imul %rbx, %rax
mov %rax, -88(%rbp)
L13:
mov -80(%rbp), %rax
mov -88(%rbp), %rbx
add %rbx, %rax
mov %rax, -96(%rbp)
L14:
mov $8, %rax
mov %rax, -104(%rbp)
L15:
mov -104(%rbp), %rax
mov -96(%rbp), %rbx
imul %rbx, %rax
mov %rax, -112(%rbp)
L16:
mov -64(%rbp), %rax
mov -112(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -120(%rbp)
L17:
mov -120(%rbp), %rax
mov %rax, -128(%rbp)
L18:
L19:
mov $4, %rax
mov %rax, -136(%rbp)
L20:
mov $5, %rax
mov %rax, -144(%rbp)
L21:
mov -32(%rbp), %rax
mov -136(%rbp), %rbx
imul %rbx, %rax
mov %rax, -152(%rbp)
L22:
mov -144(%rbp), %rax
mov -152(%rbp), %rbx
add %rbx, %rax
mov %rax, -160(%rbp)
L23:
mov $8, %rax
mov %rax, -168(%rbp)
L24:
mov -168(%rbp), %rax
mov -160(%rbp), %rbx
imul %rbx, %rax
mov %rax, -176(%rbp)
L25:
mov -64(%rbp), %rax
mov -176(%rbp), %rbx
add %rbx, %rax
mov -128(%rbp), %rbx
mov %rbx, (%rax)
L26:
mov $0, %rax
mov %rax, -184(%rbp)
L27:
mov -184(%rbp), %rax
mov %rax, -192(%rbp)
L28:
L29:
mov $10, %rax
mov %rax, -200(%rbp)
L30:
mov -192(%rbp), %rax
mov -200(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -208(%rbp)
L31:
mov -208(%rbp), %rax
cmp $0, %rax
jne L33
L32:
jmp L57
L33:
mov $0, %rax
mov %rax, -216(%rbp)
L34:
mov -216(%rbp), %rax
mov %rax, -224(%rbp)
L35:
L36:
mov $100, %rax
mov %rax, -232(%rbp)
L37:
mov -224(%rbp), %rax
mov -232(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -240(%rbp)
L38:
mov -240(%rbp), %rax
cmp $0, %rax
jne L40
L39:
jmp L51
L40:
mov -32(%rbp), %rax
mov -192(%rbp), %rbx
imul %rbx, %rax
mov %rax, -248(%rbp)
L41:
mov -224(%rbp), %rax
mov -248(%rbp), %rbx
add %rbx, %rax
mov %rax, -256(%rbp)
L42:
mov $8, %rax
mov %rax, -264(%rbp)
L43:
mov -264(%rbp), %rax
mov -256(%rbp), %rbx
imul %rbx, %rax
mov %rax, -272(%rbp)
L44:
mov -224(%rbp), %rax
mov -192(%rbp), %rbx
add %rbx, %rax
mov %rax, -280(%rbp)
L45:
mov -64(%rbp), %rax
mov -272(%rbp), %rbx
add %rbx, %rax
mov -280(%rbp), %rbx
mov %rbx, (%rax)
L46:
L47:
mov -224(%rbp), %rax
mov %rax, -288(%rbp)
L48:
mov $1, %rax
mov %rax, -296(%rbp)
L49:
mov -296(%rbp), %rax
mov -288(%rbp), %rbx
add %rbx, %rax
mov %rax, -224(%rbp)
L50:
jmp L36
L51:
L52:
L53:
mov -192(%rbp), %rax
mov %rax, -304(%rbp)
L54:
mov $1, %rax
mov %rax, -312(%rbp)
L55:
mov -312(%rbp), %rax
mov -304(%rbp), %rbx
add %rbx, %rax
mov %rax, -192(%rbp)
L56:
jmp L29
L57:
L58:
L59:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L60:
L61:


format:
        .ascii  "%ld\n"


