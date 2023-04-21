
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
L2:
L3:
L4:
L5:
L6:
L7:
L8:
L9:
Car_Car:
push %rbp
mov %rsp, %rbp
L10:
L11:
L12:
L13:
mov 24(%rbp), %r10
mov 0(%r10), %rax
mov %rax, -8(%rbp)
L14:
mov $1, %rax
mov %rax, -16(%rbp)
L15:
mov -16(%rbp), %rax
mov -8(%rbp), %rbx
add %rbx, %rax
mov 24(%rbp), %r10
mov %rax, 0(%r10)
L16:
mov 48(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 8(%r10)
L17:
mov 40(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 16(%r10)
L18:
mov 32(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 24(%r10)
L19:
L20:
leave
ret
L21:
Car_getModel:
push %rbp
mov %rsp, %rbp
L22:
mov 16(%rbp), %r10
mov 8(%r10), %rax
leave
ret
L23:
L24:
leave
ret
L25:
Car_getYear:
push %rbp
mov %rsp, %rbp
L26:
mov 16(%rbp), %r10
mov 16(%r10), %rax
leave
ret
L27:
L28:
leave
ret
L29:
Car_getMileage:
push %rbp
mov %rsp, %rbp
L30:
mov 16(%rbp), %r10
mov 24(%r10), %rax
leave
ret
L31:
L32:
leave
ret
L33:
Car_setMileage:
push %rbp
mov %rsp, %rbp
L34:
L35:
mov 32(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 24(%r10)
L36:
L37:
leave
ret
L38:
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
mov $32, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -8(%rbp)
mov $32, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -16(%rbp)
L172:
mov $0, %rax
mov %rax, -24(%rbp)
L173:
mov -24(%rbp), %rax
mov -8(%rbp), %r10
mov %rax, 0(%r10)
L39:
L40:
mov $1001, %rax
mov %rax, -32(%rbp)
L41:
mov $2015, %rax
mov %rax, -40(%rbp)
L42:
mov $50000, %rax
mov %rax, -48(%rbp)
L43:
mov %rbp, %rsp
mov $64, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $32, %rdi
call malloc@plt
mov %rax, -56(%rbp)
L174:
mov $1, %rax
mov %rax, -64(%rbp)
L175:
mov -64(%rbp), %rax
mov -56(%rbp), %r10
mov %rax, 8(%r10)
L44:
mov %rbp, %rsp
mov $80, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -32(%rbp), %rax
push %rax
L45:
mov -40(%rbp), %rax
push %rax
L46:
mov -48(%rbp), %rax
push %rax
L47:
push -8(%rbp)
push -56(%rbp)
call Car_Car
L48:
L49:
mov %rbp, %rsp
mov $80, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -8(%rbp), %r10
mov 0(%r10), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L50:
mov %rbp, %rsp
mov $80, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -56(%rbp)
call Car_getModel
mov %rax, -72(%rbp)
L51:
mov %rbp, %rsp
mov $88, %r9
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
L52:
mov %rbp, %rsp
mov $88, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -56(%rbp)
call Car_getYear
mov %rax, -80(%rbp)
L53:
mov %rbp, %rsp
mov $96, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -80(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L54:
mov %rbp, %rsp
mov $96, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -56(%rbp)
call Car_getMileage
mov %rax, -88(%rbp)
L55:
mov %rbp, %rsp
mov $104, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -88(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L56:
mov $55000, %rax
mov %rax, -96(%rbp)
L57:
mov %rbp, %rsp
mov $112, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -96(%rbp), %rax
push %rax
L58:
push -8(%rbp)
push -56(%rbp)
call Car_setMileage
L59:
mov %rbp, %rsp
mov $112, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -56(%rbp)
call Car_getMileage
mov %rax, -104(%rbp)
L60:
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
L61:
mov $1002, %rax
mov %rax, -112(%rbp)
L62:
mov $2020, %rax
mov %rax, -120(%rbp)
L63:
mov $15000, %rax
mov %rax, -128(%rbp)
L64:
mov %rbp, %rsp
mov $144, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $32, %rdi
call malloc@plt
mov %rax, -136(%rbp)
L176:
mov $1, %rax
mov %rax, -64(%rbp)
L177:
mov -64(%rbp), %rax
mov -136(%rbp), %r10
mov %rax, 8(%r10)
L65:
mov %rbp, %rsp
mov $152, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -112(%rbp), %rax
push %rax
L66:
mov -120(%rbp), %rax
push %rax
L67:
mov -128(%rbp), %rax
push %rax
L68:
push -8(%rbp)
push -136(%rbp)
call Car_Car
L69:
L70:
mov %rbp, %rsp
mov $152, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -8(%rbp), %r10
mov 0(%r10), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L71:
mov %rbp, %rsp
mov $152, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -136(%rbp)
call Car_getModel
mov %rax, -144(%rbp)
L72:
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
L73:
mov %rbp, %rsp
mov $160, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -136(%rbp)
call Car_getYear
mov %rax, -152(%rbp)
L74:
mov %rbp, %rsp
mov $168, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -152(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L75:
mov %rbp, %rsp
mov $168, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -136(%rbp)
call Car_getMileage
mov %rax, -160(%rbp)
L76:
mov %rbp, %rsp
mov $176, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -160(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L77:
mov $20000, %rax
mov %rax, -168(%rbp)
L78:
mov %rbp, %rsp
mov $184, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -168(%rbp), %rax
push %rax
L79:
push -8(%rbp)
push -136(%rbp)
call Car_setMileage
L80:
mov %rbp, %rsp
mov $184, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -136(%rbp)
call Car_getMileage
mov %rax, -176(%rbp)
L81:
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
L82:
L83:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L84:
L85:


format:
        .ascii  "%ld\n"


