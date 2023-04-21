
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
BinarySearchExample_binarySearch:
push %rbp
mov %rsp, %rbp
L2:
L3:
L4:
L5:
L6:
mov 40(%rbp), %rax
mov 48(%rbp), %rbx
add %rbx, %rax
mov %rax, -8(%rbp)
L7:
mov $2, %rax
mov %rax, -16(%rbp)
L8:
mov -8(%rbp), %rax
mov -16(%rbp), %rbx
cqo
idiv %rbx
mov %rax, -24(%rbp)
L9:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L10:
L11:
mov 48(%rbp), %rax
mov 40(%rbp), %rbx
cmp %rbx, %rax
setle %al
movzb %al, %rax
mov %rax, -40(%rbp)
L12:
mov -40(%rbp), %rax
cmp $0, %rax
jne L14
L13:
jmp L44
L14:
mov $8, %rax
mov %rax, -48(%rbp)
L15:
mov -48(%rbp), %rax
mov -32(%rbp), %rbx
imul %rbx, %rax
mov %rax, -56(%rbp)
L16:
mov 56(%rbp), %rax
mov -56(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -64(%rbp)
L17:
mov -64(%rbp), %rax
mov 32(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -72(%rbp)
L18:
mov -72(%rbp), %rax
cmp $0, %rax
jne L20
L19:
jmp L25
L20:
mov $1, %rax
mov %rax, -80(%rbp)
L21:
mov -80(%rbp), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov %rax, -88(%rbp)
L22:
mov -88(%rbp), %rax
mov %rax, 48(%rbp)
L23:
L24:
jmp L38
L25:
mov $8, %rax
mov %rax, -96(%rbp)
L26:
mov -96(%rbp), %rax
mov -32(%rbp), %rbx
imul %rbx, %rax
mov %rax, -104(%rbp)
L27:
mov 56(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -112(%rbp)
L28:
mov -112(%rbp), %rax
mov 32(%rbp), %rbx
cmp %rbx, %rax
je L30
L29:
jmp L34
L30:
mov %rbp, %rsp
mov $128, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -32(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L31:
jmp L44
L32:
L33:
jmp L38
L34:
mov $1, %rax
mov %rax, -120(%rbp)
L35:
mov -32(%rbp), %rax
mov -120(%rbp), %rbx
sub %rbx, %rax
mov %rax, -128(%rbp)
L36:
mov -128(%rbp), %rax
mov %rax, 40(%rbp)
L37:
L38:
mov 40(%rbp), %rax
mov 48(%rbp), %rbx
add %rbx, %rax
mov %rax, -136(%rbp)
L39:
mov $2, %rax
mov %rax, -144(%rbp)
L40:
mov -136(%rbp), %rax
mov -144(%rbp), %rbx
cqo
idiv %rbx
mov %rax, -152(%rbp)
L41:
mov -152(%rbp), %rax
mov %rax, -32(%rbp)
L42:
L43:
jmp L11
L44:
mov 48(%rbp), %rax
mov 40(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -160(%rbp)
L45:
mov -160(%rbp), %rax
cmp $0, %rax
jne L47
L46:
jmp L51
L47:
mov $1, %rax
mov %rax, -168(%rbp)
L48:
mov -168(%rbp), %rax
mov -168(%rbp), %rax
neg %rax
mov %rax, -176(%rbp)
mov %rax, -176(%rbp)
L49:
mov %rbp, %rsp
mov $192, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -176(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L50:
L51:
L52:
leave
ret
L53:
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
L54:
L55:
mov $10, %rax
mov %rax, -24(%rbp)
L56:
mov $8, %rax
mov %rax, -32(%rbp)
L57:
mov -32(%rbp), %rax
mov -24(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L58:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rdi
call malloc@plt
mov %rax, -48(%rbp)
L59:
L60:
mov $0, %rax
mov %rax, -56(%rbp)
L61:
mov -56(%rbp), %rax
mov %rax, -64(%rbp)
L62:
L63:
mov $10, %rax
mov %rax, -72(%rbp)
L64:
mov -64(%rbp), %rax
mov -72(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -80(%rbp)
L65:
mov -80(%rbp), %rax
cmp $0, %rax
jne L67
L66:
jmp L77
L67:
mov $8, %rax
mov %rax, -88(%rbp)
L68:
mov -88(%rbp), %rax
mov -64(%rbp), %rbx
imul %rbx, %rax
mov %rax, -96(%rbp)
L69:
mov $10, %rax
mov %rax, -104(%rbp)
L70:
mov -64(%rbp), %rax
mov -104(%rbp), %rbx
imul %rbx, %rax
mov %rax, -112(%rbp)
L71:
mov -48(%rbp), %rax
mov -96(%rbp), %rbx
add %rbx, %rax
mov -112(%rbp), %rbx
mov %rbx, (%rax)
L72:
L73:
mov -64(%rbp), %rax
mov %rax, -120(%rbp)
L74:
mov $1, %rax
mov %rax, -128(%rbp)
L75:
mov -128(%rbp), %rax
mov -120(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L76:
jmp L63
L77:
L78:
mov $30, %rax
mov %rax, -136(%rbp)
L79:
mov -136(%rbp), %rax
mov %rax, -144(%rbp)
L80:
L81:
mov $10, %rax
mov %rax, -152(%rbp)
L82:
mov $1, %rax
mov %rax, -160(%rbp)
L83:
mov -152(%rbp), %rax
mov -160(%rbp), %rbx
sub %rbx, %rax
mov %rax, -168(%rbp)
L84:
mov -168(%rbp), %rax
mov %rax, -176(%rbp)
L85:
L86:
mov $0, %rax
mov %rax, -184(%rbp)
L87:
mov %rbp, %rsp
mov $200, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
push %rax
L88:
mov -184(%rbp), %rax
push %rax
L89:
mov -176(%rbp), %rax
push %rax
L90:
mov -144(%rbp), %rax
push %rax
L91:
push -8(%rbp)
push -16(%rbp)
call BinarySearchExample_binarySearch
L92:
mov $0, %rax
mov %rax, -192(%rbp)
L93:
mov $50, %rax
mov %rax, -200(%rbp)
L94:
mov %rbp, %rsp
mov $216, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
push %rax
L95:
mov -192(%rbp), %rax
push %rax
L96:
mov -176(%rbp), %rax
push %rax
L97:
mov -200(%rbp), %rax
push %rax
L98:
push -8(%rbp)
push -16(%rbp)
call BinarySearchExample_binarySearch
L99:
mov $0, %rax
mov %rax, -208(%rbp)
L100:
mov $100, %rax
mov %rax, -216(%rbp)
L101:
mov %rbp, %rsp
mov $232, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
push %rax
L102:
mov -208(%rbp), %rax
push %rax
L103:
mov -176(%rbp), %rax
push %rax
L104:
mov -216(%rbp), %rax
push %rax
L105:
push -8(%rbp)
push -16(%rbp)
call BinarySearchExample_binarySearch
L106:
L107:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L108:
L109:


format:
        .ascii  "%ld\n"


