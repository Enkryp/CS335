
        .global main

        .text

   
L0:
main:
sub $16, %rsp
mov %rsp, %rbp
push %rbp
mov %rsp, %rbp
L1:
mov $5, %rax
mov %rax, -8(%rbp)
L2:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L3:
L4:
mov $0, %rax
mov %rax, -24(%rbp)
L5:
mov -24(%rbp), %rax
mov %rax, -32(%rbp)
L6:
L7:
mov -16(%rbp), %rax
cmp -32(%rbp), %rax
setg %al
movzb %al, %rax
mov %rax, -40(%rbp)
L8:
mov -40(%rbp), %rax
cmp $0, %rax
jne L10
L9:
jmp L14
L10:
mov $1, %rax
mov %rax, -48(%rbp)
L11:
mov -32(%rbp), %rax
add -48(%rbp), %rax
mov %rax, -32(%rbp)
L12:
L13:
jmp L7
L14:
mov $2, %rax
mov %rax, -56(%rbp)
L15:
mov -32(%rbp), %rax
imul -56(%rbp), %rax
mov %rax, -64(%rbp)
L16:
mov -16(%rbp), %rax
cmp -64(%rbp), %rax
setg %al
movzb %al, %rax
mov %rax, -72(%rbp)
L17:
mov -72(%rbp), %rax
cmp $0, %rax
jne L19
L18:
jmp L24
L19:
mov $3, %rax
mov %rax, -80(%rbp)
L20:
mov -80(%rbp), %rax
add -32(%rbp), %rax
mov %rax, -88(%rbp)
L21:
mov -88(%rbp), %rax
mov %rax, -32(%rbp)
L22:
L23:
jmp L14
L24:
mov %rbp, %rsp
sub $104, %rsp
mov -32(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L25:
mov %rbp, %rsp
sub $104, %rsp
mov -16(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L26:
mov %rbp, %rsp
sub $104, %rsp
mov -32(%rbp), %rax
mov $format, %rdi
mov %rax, %rsi
xor     %rax, %rax
call printf   
L27:
mov $4, %rax
mov %rax, -96(%rbp)
L28:
mov -32(%rbp), %rax
imul -96(%rbp), %rax
mov %rax, -104(%rbp)
L29:
mov -16(%rbp), %rax
cmp -104(%rbp), %rax
setg %al
movzb %al, %rax
mov %rax, -112(%rbp)
L30:
mov -112(%rbp), %rax
cmp $0, %rax
jne L32
L31:
jmp L56
L32:
mov $0, %rax
mov %rax, -120(%rbp)
L33:
mov -120(%rbp), %rax
mov %rax, -128(%rbp)
L34:
L35:
mov -32(%rbp), %rax
cmp -128(%rbp), %rax
setg %al
movzb %al, %rax
mov %rax, -136(%rbp)
L36:
mov -136(%rbp), %rax
cmp $0, %rax
jne L38
L37:
jmp L52
L38:
mov $0, %rax
mov %rax, -144(%rbp)
L39:
mov -144(%rbp), %rax
mov %rax, -152(%rbp)
L40:
L41:
mov -152(%rbp), %rax
cmp -32(%rbp), %rax
setg %al
movzb %al, %rax
mov %rax, -160(%rbp)
L42:
mov -160(%rbp), %rax
cmp $0, %rax
jne L44
L43:
jmp L48
L44:
mov $1, %rax
mov %rax, -168(%rbp)
L45:
mov -32(%rbp), %rax
add -168(%rbp), %rax
mov %rax, -32(%rbp)
L46:
L47:
jmp L41
L48:
mov $1, %rax
mov %rax, -176(%rbp)
L49:
mov -152(%rbp), %rax
add -176(%rbp), %rax
mov %rax, -152(%rbp)
L50:
L51:
jmp L35
L52:
mov $1, %rax
mov %rax, -184(%rbp)
L53:
mov -128(%rbp), %rax
add -184(%rbp), %rax
mov %rax, -128(%rbp)
L54:
L55:
jmp L27
L56:
L57:
L58:
L59:


  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
format:
        .ascii  "%lld\n"


