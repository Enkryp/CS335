
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
mov $20, %rax
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
mov -32(%rbp), %rax
mov -88(%rbp), %rbx
imul %rbx, %rax
mov %rax, -104(%rbp)
L15:
mov -96(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov %rax, -112(%rbp)
L16:
mov $0, %rax
mov %rax, -120(%rbp)
L17:
mov -48(%rbp), %rax
mov -112(%rbp), %rbx
imul %rbx, %rax
mov %rax, -128(%rbp)
L18:
mov -120(%rbp), %rax
mov -128(%rbp), %rbx
add %rbx, %rax
mov %rax, -136(%rbp)
L19:
mov $8, %rax
mov %rax, -144(%rbp)
L20:
mov -144(%rbp), %rax
mov -136(%rbp), %rbx
imul %rbx, %rax
mov %rax, -152(%rbp)
L21:
mov -80(%rbp), %rax
mov -152(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -160(%rbp)
L22:
mov -160(%rbp), %rax
mov %rax, -168(%rbp)
L23:
L24:
mov $4, %rax
mov %rax, -176(%rbp)
L25:
mov $5, %rax
mov %rax, -184(%rbp)
L26:
mov -32(%rbp), %rax
mov -176(%rbp), %rbx
imul %rbx, %rax
mov %rax, -192(%rbp)
L27:
mov -184(%rbp), %rax
mov -192(%rbp), %rbx
add %rbx, %rax
mov %rax, -200(%rbp)
L28:
mov $2, %rax
mov %rax, -208(%rbp)
L29:
mov -48(%rbp), %rax
mov -200(%rbp), %rbx
imul %rbx, %rax
mov %rax, -216(%rbp)
L30:
mov -208(%rbp), %rax
mov -216(%rbp), %rbx
add %rbx, %rax
mov %rax, -224(%rbp)
L31:
mov $8, %rax
mov %rax, -232(%rbp)
L32:
mov -232(%rbp), %rax
mov -224(%rbp), %rbx
imul %rbx, %rax
mov %rax, -240(%rbp)
L33:
mov $20, %rax
mov %rax, -248(%rbp)
L34:
mov -80(%rbp), %rax
mov -240(%rbp), %rbx
add %rbx, %rax
mov -248(%rbp), %rbx
mov %rbx, (%rax)
L35:
mov $0, %rax
mov %rax, -256(%rbp)
L36:
mov -256(%rbp), %rax
mov %rax, -264(%rbp)
L37:
L38:
mov $10, %rax
mov %rax, -272(%rbp)
L39:
mov -264(%rbp), %rax
mov -272(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -280(%rbp)
L40:
mov -280(%rbp), %rax
cmp $0, %rax
jne L42
L41:
jmp L81
L42:
mov $0, %rax
mov %rax, -288(%rbp)
L43:
mov -288(%rbp), %rax
mov %rax, -296(%rbp)
L44:
L45:
mov $100, %rax
mov %rax, -304(%rbp)
L46:
mov -296(%rbp), %rax
mov -304(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -312(%rbp)
L47:
mov -312(%rbp), %rax
cmp $0, %rax
jne L49
L48:
jmp L75
L49:
mov $0, %rax
mov %rax, -320(%rbp)
L50:
mov -320(%rbp), %rax
mov %rax, -328(%rbp)
L51:
L52:
mov $20, %rax
mov %rax, -336(%rbp)
L53:
mov -328(%rbp), %rax
mov -336(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -344(%rbp)
L54:
mov -344(%rbp), %rax
cmp $0, %rax
jne L56
L55:
jmp L69
L56:
mov -32(%rbp), %rax
mov -264(%rbp), %rbx
imul %rbx, %rax
mov %rax, -352(%rbp)
L57:
mov -296(%rbp), %rax
mov -352(%rbp), %rbx
add %rbx, %rax
mov %rax, -360(%rbp)
L58:
mov -48(%rbp), %rax
mov -360(%rbp), %rbx
imul %rbx, %rax
mov %rax, -368(%rbp)
L59:
mov -328(%rbp), %rax
mov -368(%rbp), %rbx
add %rbx, %rax
mov %rax, -376(%rbp)
L60:
mov $8, %rax
mov %rax, -384(%rbp)
L61:
mov -384(%rbp), %rax
mov -376(%rbp), %rbx
imul %rbx, %rax
mov %rax, -392(%rbp)
L62:
mov -328(%rbp), %rax
mov -296(%rbp), %rbx
imul %rbx, %rax
mov %rax, -400(%rbp)
L63:
mov -400(%rbp), %rax
mov -264(%rbp), %rbx
add %rbx, %rax
mov %rax, -408(%rbp)
L64:
mov -80(%rbp), %rax
mov -392(%rbp), %rbx
add %rbx, %rax
mov -408(%rbp), %rbx
mov %rbx, (%rax)
L65:
mov -328(%rbp), %rax
mov %rax, -416(%rbp)
L66:
mov $1, %rax
mov %rax, -424(%rbp)
L67:
mov -424(%rbp), %rax
mov -416(%rbp), %rbx
add %rbx, %rax
mov %rax, -328(%rbp)
L68:
jmp L52
L69:
L70:
L71:
mov -296(%rbp), %rax
mov %rax, -432(%rbp)
L72:
mov $1, %rax
mov %rax, -440(%rbp)
L73:
mov -440(%rbp), %rax
mov -432(%rbp), %rbx
add %rbx, %rax
mov %rax, -296(%rbp)
L74:
jmp L45
L75:
L76:
L77:
mov -264(%rbp), %rax
mov %rax, -448(%rbp)
L78:
mov $1, %rax
mov %rax, -456(%rbp)
L79:
mov -456(%rbp), %rax
mov -448(%rbp), %rbx
add %rbx, %rax
mov %rax, -264(%rbp)
L80:
jmp L38
L81:
L82:
mov $4, %rax
mov %rax, -464(%rbp)
L83:
mov $5, %rax
mov %rax, -472(%rbp)
L84:
mov -32(%rbp), %rax
mov -464(%rbp), %rbx
imul %rbx, %rax
mov %rax, -480(%rbp)
L85:
mov -472(%rbp), %rax
mov -480(%rbp), %rbx
add %rbx, %rax
mov %rax, -488(%rbp)
L86:
mov $2, %rax
mov %rax, -496(%rbp)
L87:
mov -48(%rbp), %rax
mov -488(%rbp), %rbx
imul %rbx, %rax
mov %rax, -504(%rbp)
L88:
mov -496(%rbp), %rax
mov -504(%rbp), %rbx
add %rbx, %rax
mov %rax, -512(%rbp)
L89:
mov $8, %rax
mov %rax, -520(%rbp)
L90:
mov -520(%rbp), %rax
mov -512(%rbp), %rbx
imul %rbx, %rax
mov %rax, -528(%rbp)
L91:
mov -80(%rbp), %rax
mov -528(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -536(%rbp)
L92:
mov %rbp, %rsp
mov $552, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -536(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L93:
L94:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L95:
L96:


format:
        .ascii  "%ld\n"


