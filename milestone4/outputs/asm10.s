
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
add %rbx, %rax
mov %rax, -40(%rbp)
L6:
mov $100, %rax
mov %rax, -48(%rbp)
L7:
mov -48(%rbp), %rax
mov -40(%rbp), %rbx
imul %rbx, %rax
mov %rax, -56(%rbp)
L8:
mov $8, %rax
mov %rax, -64(%rbp)
L9:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
imul %rbx, %rax
mov %rax, -72(%rbp)
L10:
mov %rbp, %rsp
mov $88, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -72(%rbp), %rdi
call malloc@plt
mov %rax, -80(%rbp)
L11:
L12:
mov $0, %rax
mov %rax, -88(%rbp)
L13:
mov $0, %rax
mov %rax, -96(%rbp)
L14:
mov -48(%rbp), %rax
mov -88(%rbp), %rbx
imul %rbx, %rax
mov %rax, -104(%rbp)
L15:
mov -96(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov %rax, -112(%rbp)
L16:
mov $8, %rax
mov %rax, -120(%rbp)
L17:
mov -120(%rbp), %rax
mov -112(%rbp), %rbx
imul %rbx, %rax
mov %rax, -128(%rbp)
L18:
mov -80(%rbp), %rax
mov -128(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -136(%rbp)
L19:
mov -136(%rbp), %rax
mov %rax, -144(%rbp)
L20:
L21:
mov $4, %rax
mov %rax, -152(%rbp)
L22:
mov $5, %rax
mov %rax, -160(%rbp)
L23:
mov -48(%rbp), %rax
mov -152(%rbp), %rbx
imul %rbx, %rax
mov %rax, -168(%rbp)
L24:
mov -160(%rbp), %rax
mov -168(%rbp), %rbx
add %rbx, %rax
mov %rax, -176(%rbp)
L25:
mov $8, %rax
mov %rax, -184(%rbp)
L26:
mov -184(%rbp), %rax
mov -176(%rbp), %rbx
imul %rbx, %rax
mov %rax, -192(%rbp)
L27:
mov -80(%rbp), %rax
mov -192(%rbp), %rbx
add %rbx, %rax
mov -144(%rbp), %rbx
mov %rbx, (%rax)
L28:
mov $0, %rax
mov %rax, -200(%rbp)
L29:
mov -200(%rbp), %rax
mov %rax, -208(%rbp)
L30:
L31:
mov $10, %rax
mov %rax, -216(%rbp)
L32:
mov -208(%rbp), %rax
mov -216(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -224(%rbp)
L33:
mov -224(%rbp), %rax
cmp $0, %rax
jne L35
L34:
jmp L59
L35:
mov $0, %rax
mov %rax, -232(%rbp)
L36:
mov -232(%rbp), %rax
mov %rax, -240(%rbp)
L37:
L38:
mov $100, %rax
mov %rax, -248(%rbp)
L39:
mov -240(%rbp), %rax
mov -248(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -256(%rbp)
L40:
mov -256(%rbp), %rax
cmp $0, %rax
jne L42
L41:
jmp L53
L42:
mov -48(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -264(%rbp)
L43:
mov -240(%rbp), %rax
mov -264(%rbp), %rbx
add %rbx, %rax
mov %rax, -272(%rbp)
L44:
mov $8, %rax
mov %rax, -280(%rbp)
L45:
mov -280(%rbp), %rax
mov -272(%rbp), %rbx
imul %rbx, %rax
mov %rax, -288(%rbp)
L46:
mov -240(%rbp), %rax
mov -208(%rbp), %rbx
add %rbx, %rax
mov %rax, -296(%rbp)
L47:
mov -80(%rbp), %rax
mov -288(%rbp), %rbx
add %rbx, %rax
mov -296(%rbp), %rbx
mov %rbx, (%rax)
L48:
L49:
mov -240(%rbp), %rax
mov %rax, -304(%rbp)
L50:
mov $1, %rax
mov %rax, -312(%rbp)
L51:
mov -312(%rbp), %rax
mov -304(%rbp), %rbx
add %rbx, %rax
mov %rax, -240(%rbp)
L52:
jmp L38
L53:
L54:
L55:
mov -208(%rbp), %rax
mov %rax, -320(%rbp)
L56:
mov $1, %rax
mov %rax, -328(%rbp)
L57:
mov -328(%rbp), %rax
mov -320(%rbp), %rbx
add %rbx, %rax
mov %rax, -208(%rbp)
L58:
jmp L31
L59:
L60:
mov $4, %rax
mov %rax, -336(%rbp)
L61:
mov $5, %rax
mov %rax, -344(%rbp)
L62:
mov -48(%rbp), %rax
mov -336(%rbp), %rbx
imul %rbx, %rax
mov %rax, -352(%rbp)
L63:
mov -344(%rbp), %rax
mov -352(%rbp), %rbx
add %rbx, %rax
mov %rax, -360(%rbp)
L64:
mov $8, %rax
mov %rax, -368(%rbp)
L65:
mov -368(%rbp), %rax
mov -360(%rbp), %rbx
imul %rbx, %rax
mov %rax, -376(%rbp)
L66:
mov -80(%rbp), %rax
mov -376(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -384(%rbp)
L67:
mov %rbp, %rsp
mov $400, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -384(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L68:
L69:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L70:
L71:


format:
        .ascii  "%ld\n"


