
.section    .rodata
.note0:

        .string "%ld\n"
        .text
        .globl main
   
L0:
L1:
MultiArrayAccess_printarray:
push %rbp
mov %rsp, %rbp
L2:
L3:
L4:
mov $0, %rax
mov %rax, -8(%rbp)
L5:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L6:
L7:
mov -16(%rbp), %rax
mov 32(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -24(%rbp)
L8:
mov -24(%rbp), %rax
cmp $0, %rax
jne L10
L9:
jmp L19
L10:
mov $8, %rax
mov %rax, -32(%rbp)
L11:
mov -32(%rbp), %rax
mov -16(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L12:
mov 40(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -48(%rbp)
L13:
mov %rbp, %rsp
mov $64, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L14:
L15:
mov -16(%rbp), %rax
mov %rax, -56(%rbp)
L16:
mov $1, %rax
mov %rax, -64(%rbp)
L17:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L18:
jmp L7
L19:
L20:
L21:
leave
ret
L22:
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
L23:
L24:
mov $10, %rax
mov %rax, -24(%rbp)
L25:
mov $100, %rax
mov %rax, -32(%rbp)
L26:
mov -32(%rbp), %rax
mov -24(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L27:
mov $20, %rax
mov %rax, -48(%rbp)
L28:
mov -48(%rbp), %rax
mov -40(%rbp), %rbx
imul %rbx, %rax
mov %rax, -56(%rbp)
L29:
mov $4, %rax
mov %rax, -64(%rbp)
L30:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
imul %rbx, %rax
mov %rax, -72(%rbp)
L31:
mov $8, %rax
mov %rax, -80(%rbp)
L32:
mov -80(%rbp), %rax
mov -72(%rbp), %rbx
imul %rbx, %rax
mov %rax, -88(%rbp)
L33:
mov %rbp, %rsp
mov $104, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -88(%rbp), %rdi
call malloc@plt
mov %rax, -96(%rbp)
L34:
L35:
mov $0, %rax
mov %rax, -104(%rbp)
L36:
mov $0, %rax
mov %rax, -112(%rbp)
L37:
mov -32(%rbp), %rax
mov -104(%rbp), %rbx
imul %rbx, %rax
mov %rax, -120(%rbp)
L38:
mov -112(%rbp), %rax
mov -120(%rbp), %rbx
add %rbx, %rax
mov %rax, -128(%rbp)
L39:
mov $0, %rax
mov %rax, -136(%rbp)
L40:
mov -48(%rbp), %rax
mov -128(%rbp), %rbx
imul %rbx, %rax
mov %rax, -144(%rbp)
L41:
mov -136(%rbp), %rax
mov -144(%rbp), %rbx
add %rbx, %rax
mov %rax, -152(%rbp)
L42:
mov $0, %rax
mov %rax, -160(%rbp)
L43:
mov -64(%rbp), %rax
mov -152(%rbp), %rbx
imul %rbx, %rax
mov %rax, -168(%rbp)
L44:
mov -160(%rbp), %rax
mov -168(%rbp), %rbx
add %rbx, %rax
mov %rax, -176(%rbp)
L45:
mov $8, %rax
mov %rax, -184(%rbp)
L46:
mov -184(%rbp), %rax
mov -176(%rbp), %rbx
imul %rbx, %rax
mov %rax, -192(%rbp)
L47:
mov -96(%rbp), %rax
mov -192(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -200(%rbp)
L48:
mov -200(%rbp), %rax
mov %rax, -208(%rbp)
L49:
L50:
mov $4, %rax
mov %rax, -216(%rbp)
L51:
mov $5, %rax
mov %rax, -224(%rbp)
L52:
mov -32(%rbp), %rax
mov -216(%rbp), %rbx
imul %rbx, %rax
mov %rax, -232(%rbp)
L53:
mov -224(%rbp), %rax
mov -232(%rbp), %rbx
add %rbx, %rax
mov %rax, -240(%rbp)
L54:
mov $2, %rax
mov %rax, -248(%rbp)
L55:
mov -48(%rbp), %rax
mov -240(%rbp), %rbx
imul %rbx, %rax
mov %rax, -256(%rbp)
L56:
mov -248(%rbp), %rax
mov -256(%rbp), %rbx
add %rbx, %rax
mov %rax, -264(%rbp)
L57:
mov $0, %rax
mov %rax, -272(%rbp)
L58:
mov -64(%rbp), %rax
mov -264(%rbp), %rbx
imul %rbx, %rax
mov %rax, -280(%rbp)
L59:
mov -272(%rbp), %rax
mov -280(%rbp), %rbx
add %rbx, %rax
mov %rax, -288(%rbp)
L60:
mov $8, %rax
mov %rax, -296(%rbp)
L61:
mov -296(%rbp), %rax
mov -288(%rbp), %rbx
imul %rbx, %rax
mov %rax, -304(%rbp)
L62:
mov $20, %rax
mov %rax, -312(%rbp)
L63:
mov -96(%rbp), %rax
mov -304(%rbp), %rbx
add %rbx, %rax
mov -312(%rbp), %rbx
mov %rbx, (%rax)
L64:
mov $0, %rax
mov %rax, -320(%rbp)
L65:
mov -320(%rbp), %rax
mov %rax, -328(%rbp)
L66:
L67:
mov $10, %rax
mov %rax, -336(%rbp)
L68:
mov -328(%rbp), %rax
mov -336(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -344(%rbp)
L69:
mov -344(%rbp), %rax
cmp $0, %rax
jne L71
L70:
jmp L127
L71:
mov $0, %rax
mov %rax, -352(%rbp)
L72:
mov -352(%rbp), %rax
mov %rax, -360(%rbp)
L73:
L74:
mov $100, %rax
mov %rax, -368(%rbp)
L75:
mov -360(%rbp), %rax
mov -368(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -376(%rbp)
L76:
mov -376(%rbp), %rax
cmp $0, %rax
jne L78
L77:
jmp L121
L78:
mov $0, %rax
mov %rax, -384(%rbp)
L79:
mov -384(%rbp), %rax
mov %rax, -392(%rbp)
L80:
L81:
mov $20, %rax
mov %rax, -400(%rbp)
L82:
mov -392(%rbp), %rax
mov -400(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -408(%rbp)
L83:
mov -408(%rbp), %rax
cmp $0, %rax
jne L85
L84:
jmp L115
L85:
mov $0, %rax
mov %rax, -416(%rbp)
L86:
mov -416(%rbp), %rax
mov %rax, -424(%rbp)
L87:
L88:
mov $4, %rax
mov %rax, -432(%rbp)
L89:
mov -424(%rbp), %rax
mov -432(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -440(%rbp)
L90:
mov -440(%rbp), %rax
cmp $0, %rax
jne L92
L91:
jmp L109
L92:
mov -32(%rbp), %rax
mov -328(%rbp), %rbx
imul %rbx, %rax
mov %rax, -448(%rbp)
L93:
mov -360(%rbp), %rax
mov -448(%rbp), %rbx
add %rbx, %rax
mov %rax, -456(%rbp)
L94:
mov -48(%rbp), %rax
mov -456(%rbp), %rbx
imul %rbx, %rax
mov %rax, -464(%rbp)
L95:
mov -392(%rbp), %rax
mov -464(%rbp), %rbx
add %rbx, %rax
mov %rax, -472(%rbp)
L96:
mov -64(%rbp), %rax
mov -472(%rbp), %rbx
imul %rbx, %rax
mov %rax, -480(%rbp)
L97:
mov -424(%rbp), %rax
mov -480(%rbp), %rbx
add %rbx, %rax
mov %rax, -488(%rbp)
L98:
mov $8, %rax
mov %rax, -496(%rbp)
L99:
mov -496(%rbp), %rax
mov -488(%rbp), %rbx
imul %rbx, %rax
mov %rax, -504(%rbp)
L100:
mov -392(%rbp), %rax
mov -360(%rbp), %rbx
imul %rbx, %rax
mov %rax, -512(%rbp)
L101:
mov -512(%rbp), %rax
mov -328(%rbp), %rbx
add %rbx, %rax
mov %rax, -520(%rbp)
L102:
mov -424(%rbp), %rax
mov -520(%rbp), %rbx
add %rbx, %rax
mov %rax, -528(%rbp)
L103:
mov -96(%rbp), %rax
mov -504(%rbp), %rbx
add %rbx, %rax
mov -528(%rbp), %rbx
mov %rbx, (%rax)
L104:
L105:
mov -424(%rbp), %rax
mov %rax, -536(%rbp)
L106:
mov $1, %rax
mov %rax, -544(%rbp)
L107:
mov -544(%rbp), %rax
mov -536(%rbp), %rbx
add %rbx, %rax
mov %rax, -424(%rbp)
L108:
jmp L88
L109:
L110:
L111:
mov -392(%rbp), %rax
mov %rax, -552(%rbp)
L112:
mov $1, %rax
mov %rax, -560(%rbp)
L113:
mov -560(%rbp), %rax
mov -552(%rbp), %rbx
add %rbx, %rax
mov %rax, -392(%rbp)
L114:
jmp L81
L115:
L116:
L117:
mov -360(%rbp), %rax
mov %rax, -568(%rbp)
L118:
mov $1, %rax
mov %rax, -576(%rbp)
L119:
mov -576(%rbp), %rax
mov -568(%rbp), %rbx
add %rbx, %rax
mov %rax, -360(%rbp)
L120:
jmp L74
L121:
L122:
L123:
mov -328(%rbp), %rax
mov %rax, -584(%rbp)
L124:
mov $1, %rax
mov %rax, -592(%rbp)
L125:
mov -592(%rbp), %rax
mov -584(%rbp), %rbx
add %rbx, %rax
mov %rax, -328(%rbp)
L126:
jmp L67
L127:
L128:
mov $4, %rax
mov %rax, -600(%rbp)
L129:
mov $5, %rax
mov %rax, -608(%rbp)
L130:
mov -32(%rbp), %rax
mov -600(%rbp), %rbx
imul %rbx, %rax
mov %rax, -616(%rbp)
L131:
mov -608(%rbp), %rax
mov -616(%rbp), %rbx
add %rbx, %rax
mov %rax, -624(%rbp)
L132:
mov $2, %rax
mov %rax, -632(%rbp)
L133:
mov -48(%rbp), %rax
mov -624(%rbp), %rbx
imul %rbx, %rax
mov %rax, -640(%rbp)
L134:
mov -632(%rbp), %rax
mov -640(%rbp), %rbx
add %rbx, %rax
mov %rax, -648(%rbp)
L135:
mov $1, %rax
mov %rax, -656(%rbp)
L136:
mov -64(%rbp), %rax
mov -648(%rbp), %rbx
imul %rbx, %rax
mov %rax, -664(%rbp)
L137:
mov -656(%rbp), %rax
mov -664(%rbp), %rbx
add %rbx, %rax
mov %rax, -672(%rbp)
L138:
mov $8, %rax
mov %rax, -680(%rbp)
L139:
mov -680(%rbp), %rax
mov -672(%rbp), %rbx
imul %rbx, %rax
mov %rax, -688(%rbp)
L140:
mov -96(%rbp), %rax
mov -688(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -696(%rbp)
L141:
mov %rbp, %rsp
mov $712, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -696(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L142:
mov $7, %rax
mov %rax, -704(%rbp)
L143:
mov $8, %rax
mov %rax, -712(%rbp)
L144:
mov -712(%rbp), %rax
mov -704(%rbp), %rbx
imul %rbx, %rax
mov %rax, -720(%rbp)
L145:
mov %rbp, %rsp
mov $736, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -720(%rbp), %rdi
call malloc@plt
mov %rax, -728(%rbp)
L146:
L147:
mov $0, %rax
mov %rax, -736(%rbp)
L148:
mov -736(%rbp), %rax
mov %rax, -328(%rbp)
L149:
L150:
mov $7, %rax
mov %rax, -744(%rbp)
L151:
mov -328(%rbp), %rax
mov -744(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -752(%rbp)
L152:
mov -752(%rbp), %rax
cmp $0, %rax
jne L154
L153:
jmp L175
L154:
mov $8, %rax
mov %rax, -760(%rbp)
L155:
mov -760(%rbp), %rax
mov -328(%rbp), %rbx
imul %rbx, %rax
mov %rax, -768(%rbp)
L156:
mov -32(%rbp), %rax
mov -328(%rbp), %rbx
imul %rbx, %rax
mov %rax, -776(%rbp)
L157:
mov -328(%rbp), %rax
mov -776(%rbp), %rbx
add %rbx, %rax
mov %rax, -784(%rbp)
L158:
mov $2, %rax
mov %rax, -792(%rbp)
L159:
mov -48(%rbp), %rax
mov -784(%rbp), %rbx
imul %rbx, %rax
mov %rax, -800(%rbp)
L160:
mov -792(%rbp), %rax
mov -800(%rbp), %rbx
add %rbx, %rax
mov %rax, -808(%rbp)
L161:
mov $3, %rax
mov %rax, -816(%rbp)
L162:
mov -64(%rbp), %rax
mov -808(%rbp), %rbx
imul %rbx, %rax
mov %rax, -824(%rbp)
L163:
mov -816(%rbp), %rax
mov -824(%rbp), %rbx
add %rbx, %rax
mov %rax, -832(%rbp)
L164:
mov $8, %rax
mov %rax, -840(%rbp)
L165:
mov -840(%rbp), %rax
mov -832(%rbp), %rbx
imul %rbx, %rax
mov %rax, -848(%rbp)
L166:
mov -96(%rbp), %rax
mov -848(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -856(%rbp)
L167:
mov $2, %rax
mov %rax, -864(%rbp)
L168:
mov -864(%rbp), %rax
mov -856(%rbp), %rbx
imul %rbx, %rax
mov %rax, -872(%rbp)
L169:
mov -728(%rbp), %rax
mov -768(%rbp), %rbx
add %rbx, %rax
mov -872(%rbp), %rbx
mov %rbx, (%rax)
L170:
L171:
mov -328(%rbp), %rax
mov %rax, -880(%rbp)
L172:
mov $1, %rax
mov %rax, -888(%rbp)
L173:
mov -888(%rbp), %rax
mov -880(%rbp), %rbx
add %rbx, %rax
mov %rax, -328(%rbp)
L174:
jmp L150
L175:
L176:
mov $7, %rax
mov %rax, -896(%rbp)
L177:
mov %rbp, %rsp
mov $912, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -728(%rbp), %rax
push %rax
L178:
mov -896(%rbp), %rax
push %rax
L179:
push -8(%rbp)
push -16(%rbp)
call MultiArrayAccess_printarray
L180:
L181:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L182:
L183:


format:
        .ascii  "%ld\n"


