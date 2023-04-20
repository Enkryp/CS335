
        .global main

        .text

   
L0:
L1:
main:
sub $16, %rsp
mov %rsp, %rbp
push %rbp
mov %rsp, %rbp
mov $0, %rdi
call malloc
mov %rax, %r10
mov %r10, -8(%rbp)
L2:
L3:
mov $5, %rax
mov %rax, -16(%rbp)
L4:
mov -16(%rbp), %rax
mov %rax, -24(%rbp)
L5:
L6:
mov $0, %rax
mov %rax, -32(%rbp)
L7:
mov -32(%rbp), %rax
mov %rax, -40(%rbp)
L8:
L9:
mov -24(%rbp), %rax
mov -40(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -48(%rbp)
L10:
mov -48(%rbp), %rax
cmp $0, %rax
jne L12
L11:
jmp L17
L12:
mov -40(%rbp), %rax
mov %rax, -56(%rbp)
L13:
mov $1, %rax
mov %rax, -64(%rbp)
L14:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
add %rbx, %rax
mov %rax, -40(%rbp)
L15:
L16:
jmp L9
L17:
mov $2, %rax
mov %rax, -72(%rbp)
L18:
mov -40(%rbp), %rax
mov -72(%rbp), %rbx
imul %rbx, %rax
mov %rax, -80(%rbp)
L19:
mov -24(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -88(%rbp)
L20:
mov -88(%rbp), %rax
cmp $0, %rax
jne L22
L21:
jmp L27
L22:
mov $3, %rax
mov %rax, -96(%rbp)
L23:
mov -96(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -104(%rbp)
L24:
mov -104(%rbp), %rax
mov %rax, -40(%rbp)
L25:
L26:
jmp L17
L27:
mov %rbp, %rsp
sub $120, %rsp
mov -40(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L28:
mov %rbp, %rsp
sub $120, %rsp
mov -24(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L29:
mov $4, %rax
mov %rax, -112(%rbp)
L30:
mov -40(%rbp), %rax
mov -112(%rbp), %rbx
imul %rbx, %rax
mov %rax, -120(%rbp)
L31:
mov -24(%rbp), %rax
mov -120(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -128(%rbp)
L32:
mov -128(%rbp), %rax
cmp $0, %rax
jne L34
L33:
jmp L61
L34:
mov $0, %rax
mov %rax, -136(%rbp)
L35:
mov -136(%rbp), %rax
mov %rax, -144(%rbp)
L36:
L37:
mov -40(%rbp), %rax
mov -144(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -152(%rbp)
L38:
mov -152(%rbp), %rax
cmp $0, %rax
jne L40
L39:
jmp L56
L40:
mov $0, %rax
mov %rax, -160(%rbp)
L41:
mov -160(%rbp), %rax
mov %rax, -168(%rbp)
L42:
L43:
mov -168(%rbp), %rax
mov -40(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -176(%rbp)
L44:
mov -176(%rbp), %rax
cmp $0, %rax
jne L46
L45:
jmp L51
L46:
mov -40(%rbp), %rax
mov %rax, -184(%rbp)
L47:
mov $1, %rax
mov %rax, -192(%rbp)
L48:
mov -192(%rbp), %rax
mov -184(%rbp), %rbx
add %rbx, %rax
mov %rax, -40(%rbp)
L49:
L50:
jmp L43
L51:
mov -168(%rbp), %rax
mov %rax, -200(%rbp)
L52:
mov $1, %rax
mov %rax, -208(%rbp)
L53:
mov -208(%rbp), %rax
mov -200(%rbp), %rbx
add %rbx, %rax
mov %rax, -168(%rbp)
L54:
L55:
jmp L37
L56:
mov -144(%rbp), %rax
mov %rax, -216(%rbp)
L57:
mov $1, %rax
mov %rax, -224(%rbp)
L58:
mov -224(%rbp), %rax
mov -216(%rbp), %rbx
add %rbx, %rax
mov %rax, -144(%rbp)
L59:
L60:
jmp L29
L61:
L62:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L63:
L64:


format:
        .ascii  "%ld\n"


