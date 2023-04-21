
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
mov $20, %rax
mov %rax, -24(%rbp)
L4:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L5:
L6:
mov $18, %rax
mov %rax, -40(%rbp)
L7:
mov -40(%rbp), %rax
mov %rax, -48(%rbp)
L8:
L9:
mov -32(%rbp), %rax
mov -48(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -56(%rbp)
L10:
mov -56(%rbp), %rax
cmp $0, %rax
jne L12
L11:
jmp L16
L12:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L13:
mov -64(%rbp), %rax
mov %rax, -72(%rbp)
L14:
L15:
L16:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -80(%rbp)
L17:
mov -80(%rbp), %rax
mov %rax, -72(%rbp)
L18:
L19:
L20:
mov $20, %rax
mov %rax, -88(%rbp)
L21:
mov -88(%rbp), %rax
mov %rax, -32(%rbp)
L22:
L23:
mov $18, %rax
mov %rax, -96(%rbp)
L24:
mov -96(%rbp), %rax
mov %rax, -48(%rbp)
L25:
L26:
mov -32(%rbp), %rax
mov -48(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -104(%rbp)
L27:
mov -104(%rbp), %rax
cmp $0, %rax
jne L29
L28:
jmp L33
L29:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -112(%rbp)
L30:
mov -112(%rbp), %rax
mov %rax, -72(%rbp)
L31:
L32:
L33:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -120(%rbp)
L34:
mov -120(%rbp), %rax
mov %rax, -72(%rbp)
L35:
L36:
L37:
mov $20, %rax
mov %rax, -128(%rbp)
L38:
mov -128(%rbp), %rax
mov %rax, -32(%rbp)
L39:
L40:
mov $18, %rax
mov %rax, -136(%rbp)
L41:
mov -136(%rbp), %rax
mov %rax, -48(%rbp)
L42:
L43:
mov -32(%rbp), %rax
mov -48(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -144(%rbp)
L44:
mov -144(%rbp), %rax
cmp $0, %rax
jne L46
L45:
jmp L50
L46:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -152(%rbp)
L47:
mov -152(%rbp), %rax
mov %rax, -72(%rbp)
L48:
L49:
L50:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -160(%rbp)
L51:
mov -160(%rbp), %rax
mov %rax, -72(%rbp)
L52:
L53:
L54:
mov $20, %rax
mov %rax, -168(%rbp)
L55:
mov -168(%rbp), %rax
mov %rax, -32(%rbp)
L56:
L57:
mov $18, %rax
mov %rax, -176(%rbp)
L58:
mov -176(%rbp), %rax
mov %rax, -48(%rbp)
L59:
L60:
mov -32(%rbp), %rax
mov -48(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -184(%rbp)
L61:
mov -184(%rbp), %rax
cmp $0, %rax
jne L63
L62:
jmp L67
L63:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -192(%rbp)
L64:
mov -192(%rbp), %rax
mov %rax, -72(%rbp)
L65:
L66:
L67:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -200(%rbp)
L68:
mov -200(%rbp), %rax
mov %rax, -72(%rbp)
L69:
L70:
L71:
mov $20, %rax
mov %rax, -208(%rbp)
L72:
mov -208(%rbp), %rax
mov %rax, -32(%rbp)
L73:
L74:
mov $18, %rax
mov %rax, -216(%rbp)
L75:
mov -216(%rbp), %rax
mov %rax, -48(%rbp)
L76:
L77:
mov -32(%rbp), %rax
mov -48(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -224(%rbp)
L78:
mov -224(%rbp), %rax
cmp $0, %rax
jne L80
L79:
jmp L84
L80:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -232(%rbp)
L81:
mov -232(%rbp), %rax
mov %rax, -72(%rbp)
L82:
L83:
L84:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -240(%rbp)
L85:
mov -240(%rbp), %rax
mov %rax, -72(%rbp)
L86:
L87:
mov %rbp, %rsp
mov $256, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -72(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L88:
L89:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L90:
L91:


format:
        .ascii  "%ld\n"


