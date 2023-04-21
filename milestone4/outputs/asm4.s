
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
mov $13, %rax
mov %rax, -24(%rbp)
L4:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L5:
L6:
mov $8, %rax
mov %rax, -40(%rbp)
L7:
mov -40(%rbp), %rax
mov -32(%rbp), %rbx
imul %rbx, %rax
mov %rax, -48(%rbp)
L8:
mov %rbp, %rsp
mov $64, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rdi
call malloc@plt
mov %rax, -56(%rbp)
L9:
L10:
mov $0, %rax
mov %rax, -64(%rbp)
L11:
mov -64(%rbp), %rax
mov %rax, -72(%rbp)
L12:
L13:
mov -72(%rbp), %rax
mov -32(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -80(%rbp)
L14:
mov -80(%rbp), %rax
cmp $0, %rax
jne L16
L15:
jmp L24
L16:
mov $8, %rax
mov %rax, -88(%rbp)
L17:
mov -88(%rbp), %rax
mov -72(%rbp), %rbx
imul %rbx, %rax
mov %rax, -96(%rbp)
L18:
mov -32(%rbp), %rax
mov -72(%rbp), %rbx
sub %rbx, %rax
mov %rax, -104(%rbp)
L19:
mov -56(%rbp), %rax
mov -96(%rbp), %rbx
add %rbx, %rax
mov -104(%rbp), %rbx
mov %rbx, (%rax)
L20:
mov -72(%rbp), %rax
mov %rax, -112(%rbp)
L21:
mov $1, %rax
mov %rax, -120(%rbp)
L22:
mov -120(%rbp), %rax
mov -112(%rbp), %rbx
add %rbx, %rax
mov %rax, -72(%rbp)
L23:
jmp L13
L24:
L25:
mov $0, %rax
mov %rax, -128(%rbp)
L26:
mov -128(%rbp), %rax
mov %rax, -72(%rbp)
L27:
L28:
mov $1, %rax
mov %rax, -136(%rbp)
L29:
mov -32(%rbp), %rax
mov -136(%rbp), %rbx
sub %rbx, %rax
mov %rax, -144(%rbp)
L30:
mov -72(%rbp), %rax
mov -144(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -152(%rbp)
L31:
mov -152(%rbp), %rax
cmp $0, %rax
jne L33
L32:
jmp L83
L33:
mov $0, %rax
mov %rax, -160(%rbp)
L34:
mov -160(%rbp), %rax
mov %rax, -168(%rbp)
L35:
L36:
mov -32(%rbp), %rax
mov -72(%rbp), %rbx
sub %rbx, %rax
mov %rax, -176(%rbp)
L37:
mov $1, %rax
mov %rax, -184(%rbp)
L38:
mov -176(%rbp), %rax
mov -184(%rbp), %rbx
sub %rbx, %rax
mov %rax, -192(%rbp)
L39:
mov -168(%rbp), %rax
mov -192(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -200(%rbp)
L40:
mov -200(%rbp), %rax
cmp $0, %rax
jne L42
L41:
jmp L77
L42:
mov $8, %rax
mov %rax, -208(%rbp)
L43:
mov -208(%rbp), %rax
mov -168(%rbp), %rbx
imul %rbx, %rax
mov %rax, -216(%rbp)
L44:
mov -56(%rbp), %rax
mov -216(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -224(%rbp)
L45:
mov $1, %rax
mov %rax, -232(%rbp)
L46:
mov -232(%rbp), %rax
mov -168(%rbp), %rbx
add %rbx, %rax
mov %rax, -240(%rbp)
L47:
mov $8, %rax
mov %rax, -248(%rbp)
L48:
mov -248(%rbp), %rax
mov -240(%rbp), %rbx
imul %rbx, %rax
mov %rax, -256(%rbp)
L49:
mov -56(%rbp), %rax
mov -256(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -264(%rbp)
L50:
mov -224(%rbp), %rax
mov -264(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -272(%rbp)
L51:
mov -272(%rbp), %rax
cmp $0, %rax
jne L53
L52:
jmp L72
L53:
mov $8, %rax
mov %rax, -280(%rbp)
L54:
mov -280(%rbp), %rax
mov -168(%rbp), %rbx
imul %rbx, %rax
mov %rax, -288(%rbp)
L55:
mov -56(%rbp), %rax
mov -288(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -296(%rbp)
L56:
mov -296(%rbp), %rax
mov %rax, -304(%rbp)
L57:
L58:
mov $8, %rax
mov %rax, -312(%rbp)
L59:
mov -312(%rbp), %rax
mov -168(%rbp), %rbx
imul %rbx, %rax
mov %rax, -320(%rbp)
L60:
mov $1, %rax
mov %rax, -328(%rbp)
L61:
mov -328(%rbp), %rax
mov -168(%rbp), %rbx
add %rbx, %rax
mov %rax, -336(%rbp)
L62:
mov $8, %rax
mov %rax, -344(%rbp)
L63:
mov -344(%rbp), %rax
mov -336(%rbp), %rbx
imul %rbx, %rax
mov %rax, -352(%rbp)
L64:
mov -56(%rbp), %rax
mov -352(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -360(%rbp)
L65:
mov -56(%rbp), %rax
mov -320(%rbp), %rbx
add %rbx, %rax
mov -360(%rbp), %rbx
mov %rbx, (%rax)
L66:
mov $1, %rax
mov %rax, -368(%rbp)
L67:
mov -368(%rbp), %rax
mov -168(%rbp), %rbx
add %rbx, %rax
mov %rax, -376(%rbp)
L68:
mov $8, %rax
mov %rax, -384(%rbp)
L69:
mov -384(%rbp), %rax
mov -376(%rbp), %rbx
imul %rbx, %rax
mov %rax, -392(%rbp)
L70:
mov -56(%rbp), %rax
mov -392(%rbp), %rbx
add %rbx, %rax
mov -304(%rbp), %rbx
mov %rbx, (%rax)
L71:
L72:
L73:
mov -168(%rbp), %rax
mov %rax, -400(%rbp)
L74:
mov $1, %rax
mov %rax, -408(%rbp)
L75:
mov -408(%rbp), %rax
mov -400(%rbp), %rbx
add %rbx, %rax
mov %rax, -168(%rbp)
L76:
jmp L36
L77:
L78:
L79:
mov -72(%rbp), %rax
mov %rax, -416(%rbp)
L80:
mov $1, %rax
mov %rax, -424(%rbp)
L81:
mov -424(%rbp), %rax
mov -416(%rbp), %rbx
add %rbx, %rax
mov %rax, -72(%rbp)
L82:
jmp L28
L83:
L84:
mov $0, %rax
mov %rax, -432(%rbp)
L85:
mov -432(%rbp), %rax
mov %rax, -72(%rbp)
L86:
L87:
mov -72(%rbp), %rax
mov -32(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -440(%rbp)
L88:
mov -440(%rbp), %rax
cmp $0, %rax
jne L90
L89:
jmp L99
L90:
mov $8, %rax
mov %rax, -448(%rbp)
L91:
mov -448(%rbp), %rax
mov -72(%rbp), %rbx
imul %rbx, %rax
mov %rax, -456(%rbp)
L92:
mov -56(%rbp), %rax
mov -456(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -464(%rbp)
L93:
mov %rbp, %rsp
mov $480, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -464(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L94:
L95:
mov -72(%rbp), %rax
mov %rax, -472(%rbp)
L96:
mov $1, %rax
mov %rax, -480(%rbp)
L97:
mov -480(%rbp), %rax
mov -472(%rbp), %rbx
add %rbx, %rax
mov %rax, -72(%rbp)
L98:
jmp L87
L99:
L100:
L101:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L102:
L103:


format:
        .ascii  "%ld\n"


