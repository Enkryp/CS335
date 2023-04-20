
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
L10:
L11:
L12:
Graph_Graph:
push %rbp
mov %rsp, %rbp
L13:
L14:
mov 40(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 16(%r10)
L15:
L16:
leave
ret
L17:
Graph_addEdge:
push %rbp
mov %rsp, %rbp
L18:
L19:
L20:
L21:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov 56(%rbp), %rbx
imul %rbx, %rax
mov %rax, -8(%rbp)
L22:
mov 48(%rbp), %rax
mov -8(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L23:
mov $8, %rax
mov %rax, -24(%rbp)
L24:
mov -24(%rbp), %rax
mov -16(%rbp), %rbx
imul %rbx, %rax
mov %rax, -32(%rbp)
L25:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov 40(%rbp), %rbx
mov %rbx, (%rax)
L26:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov 48(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L27:
mov 56(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -48(%rbp)
L28:
mov $8, %rax
mov %rax, -56(%rbp)
L29:
mov -56(%rbp), %rax
mov -48(%rbp), %rbx
imul %rbx, %rax
mov %rax, -64(%rbp)
L30:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -64(%rbp), %rbx
add %rbx, %rax
mov 40(%rbp), %rbx
mov %rbx, (%rax)
L31:
L32:
leave
ret
L33:
Graph_printDistances:
push %rbp
mov %rsp, %rbp
L34:
L35:
mov %rbp, %rsp
mov $16, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L36:
mov $0, %rax
mov %rax, -8(%rbp)
L37:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L38:
L39:
mov -16(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -24(%rbp)
L40:
mov -24(%rbp), %rax
cmp $0, %rax
jne L42
L41:
jmp L51
L42:
mov $8, %rax
mov %rax, -32(%rbp)
L43:
mov -32(%rbp), %rax
mov -16(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L44:
mov 40(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -48(%rbp)
L45:
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
L46:
L47:
mov -16(%rbp), %rax
mov %rax, -56(%rbp)
L48:
mov $1, %rax
mov %rax, -64(%rbp)
L49:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L50:
jmp L39
L51:
L52:
L53:
leave
ret
L54:
Graph_printGraph:
push %rbp
mov %rsp, %rbp
L55:
mov $0, %rax
mov %rax, -8(%rbp)
L56:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L57:
L58:
mov -16(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -24(%rbp)
L59:
mov -24(%rbp), %rax
cmp $0, %rax
jne L61
L60:
jmp L73
L61:
mov $0, %rax
mov %rax, -32(%rbp)
L62:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -16(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L63:
mov -32(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -48(%rbp)
L64:
mov $8, %rax
mov %rax, -56(%rbp)
L65:
mov -56(%rbp), %rax
mov -48(%rbp), %rbx
imul %rbx, %rax
mov %rax, -64(%rbp)
L66:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -64(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -72(%rbp)
L67:
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
L68:
L69:
mov -16(%rbp), %rax
mov %rax, -80(%rbp)
L70:
mov $1, %rax
mov %rax, -88(%rbp)
L71:
mov -88(%rbp), %rax
mov -80(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L72:
jmp L58
L73:
L74:
L75:
leave
ret
L76:
Graph_dijkstra:
push %rbp
mov %rsp, %rbp
L77:
L78:
mov $8, %rax
mov %rax, -8(%rbp)
L79:
mov -8(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
imul %rbx, %rax
mov %rax, -16(%rbp)
L80:
mov %rbp, %rsp
mov $32, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -16(%rbp), %rdi
call malloc@plt
mov %rax, -24(%rbp)
L81:
L82:
mov $8, %rax
mov %rax, -32(%rbp)
L83:
mov -32(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L84:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rdi
call malloc@plt
mov %rax, -48(%rbp)
L85:
L86:
mov $0, %rax
mov %rax, -56(%rbp)
L87:
mov -56(%rbp), %rax
mov %rax, -64(%rbp)
L88:
L89:
mov -64(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -72(%rbp)
L90:
mov -72(%rbp), %rax
cmp $0, %rax
jne L92
L91:
jmp L101
L92:
mov $8, %rax
mov %rax, -80(%rbp)
L93:
mov -80(%rbp), %rax
mov -64(%rbp), %rbx
imul %rbx, %rax
mov %rax, -88(%rbp)
L94:
mov $1000000000, %rax
mov %rax, -96(%rbp)
L95:
mov -48(%rbp), %rax
mov -88(%rbp), %rbx
add %rbx, %rax
mov -96(%rbp), %rbx
mov %rbx, (%rax)
L96:
L97:
mov -64(%rbp), %rax
mov %rax, -104(%rbp)
L98:
mov $1, %rax
mov %rax, -112(%rbp)
L99:
mov -112(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L100:
jmp L89
L101:
L102:
mov $8, %rax
mov %rax, -120(%rbp)
L103:
mov -120(%rbp), %rax
mov 40(%rbp), %rbx
imul %rbx, %rax
mov %rax, -128(%rbp)
L104:
mov $0, %rax
mov %rax, -136(%rbp)
L105:
mov -48(%rbp), %rax
mov -128(%rbp), %rbx
add %rbx, %rax
mov -136(%rbp), %rbx
mov %rbx, (%rax)
L106:
mov $0, %rax
mov %rax, -144(%rbp)
L107:
mov -144(%rbp), %rax
mov %rax, -64(%rbp)
L108:
L109:
mov $1, %rax
mov %rax, -152(%rbp)
L110:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -152(%rbp), %rbx
sub %rbx, %rax
mov %rax, -160(%rbp)
L111:
mov -64(%rbp), %rax
mov -160(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -168(%rbp)
L112:
mov -168(%rbp), %rax
cmp $0, %rax
jne L114
L113:
jmp L228
L114:
mov $1000000000, %rax
mov %rax, -176(%rbp)
L115:
mov -176(%rbp), %rax
mov %rax, -184(%rbp)
L116:
L117:
mov $1, %rax
mov %rax, -192(%rbp)
L118:
mov -192(%rbp), %rax
mov -192(%rbp), %rax
neg %rax
mov %rax, -200(%rbp)
mov %rax, -200(%rbp)
L119:
mov -200(%rbp), %rax
mov %rax, -208(%rbp)
L120:
L121:
mov $0, %rax
mov %rax, -216(%rbp)
L122:
mov -216(%rbp), %rax
mov %rax, -224(%rbp)
L123:
L124:
mov -224(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -232(%rbp)
L125:
mov -232(%rbp), %rax
cmp $0, %rax
jne L127
L126:
jmp L150
L127:
mov $8, %rax
mov %rax, -240(%rbp)
L128:
mov -240(%rbp), %rax
mov -224(%rbp), %rbx
imul %rbx, %rax
mov %rax, -248(%rbp)
L129:
mov -24(%rbp), %rax
mov -248(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -256(%rbp)
L130:
mov $0, %rax
mov %rax, -264(%rbp)
L131:
mov -256(%rbp), %rax
mov -264(%rbp), %rbx
cmp %rbx, %rax
je L133
L132:
jmp L145
L133:
mov $8, %rax
mov %rax, -272(%rbp)
L134:
mov -272(%rbp), %rax
mov -224(%rbp), %rbx
imul %rbx, %rax
mov %rax, -280(%rbp)
L135:
mov -48(%rbp), %rax
mov -280(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -288(%rbp)
L136:
mov -288(%rbp), %rax
mov -184(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -296(%rbp)
L137:
mov -296(%rbp), %rax
cmp $0, %rax
jne L139
L138:
jmp L145
L139:
mov $8, %rax
mov %rax, -304(%rbp)
L140:
mov -304(%rbp), %rax
mov -224(%rbp), %rbx
imul %rbx, %rax
mov %rax, -312(%rbp)
L141:
mov -48(%rbp), %rax
mov -312(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -320(%rbp)
L142:
mov -320(%rbp), %rax
mov %rax, -184(%rbp)
L143:
mov -224(%rbp), %rax
mov %rax, -208(%rbp)
L144:
L145:
L146:
mov -224(%rbp), %rax
mov %rax, -328(%rbp)
L147:
mov $1, %rax
mov %rax, -336(%rbp)
L148:
mov -336(%rbp), %rax
mov -328(%rbp), %rbx
add %rbx, %rax
mov %rax, -224(%rbp)
L149:
jmp L124
L150:
L151:
mov $1, %rax
mov %rax, -344(%rbp)
L152:
mov -344(%rbp), %rax
mov -344(%rbp), %rax
neg %rax
mov %rax, -352(%rbp)
mov %rax, -352(%rbp)
L153:
mov -208(%rbp), %rax
mov -352(%rbp), %rbx
cmp %rbx, %rax
je L155
L154:
jmp L157
L155:
jmp L228
L156:
L157:
mov $8, %rax
mov %rax, -360(%rbp)
L158:
mov -360(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -368(%rbp)
L159:
mov $1, %rax
mov %rax, -376(%rbp)
L160:
mov -24(%rbp), %rax
mov -368(%rbp), %rbx
add %rbx, %rax
mov -376(%rbp), %rbx
mov %rbx, (%rax)
L161:
mov $0, %rax
mov %rax, -384(%rbp)
L162:
mov -384(%rbp), %rax
mov %rax, -392(%rbp)
L163:
L164:
mov -392(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -400(%rbp)
L165:
mov -400(%rbp), %rax
cmp $0, %rax
jne L167
L166:
jmp L222
L167:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -408(%rbp)
L168:
mov -392(%rbp), %rax
mov -408(%rbp), %rbx
add %rbx, %rax
mov %rax, -416(%rbp)
L169:
mov $8, %rax
mov %rax, -424(%rbp)
L170:
mov -424(%rbp), %rax
mov -416(%rbp), %rbx
imul %rbx, %rax
mov %rax, -432(%rbp)
L171:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -432(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -440(%rbp)
L172:
mov $0, %rax
mov %rax, -448(%rbp)
L173:
mov -440(%rbp), %rax
mov -448(%rbp), %rbx
cmp %rbx, %rax
setne %al
movzb %al, %rax
mov %rax, -456(%rbp)
L174:
mov -456(%rbp), %rax
cmp $0, %rax
jne L176
L175:
jmp L217
L176:
mov $8, %rax
mov %rax, -464(%rbp)
L177:
mov -464(%rbp), %rax
mov -392(%rbp), %rbx
imul %rbx, %rax
mov %rax, -472(%rbp)
L178:
mov -24(%rbp), %rax
mov -472(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -480(%rbp)
L179:
mov $0, %rax
mov %rax, -488(%rbp)
L180:
mov -480(%rbp), %rax
mov -488(%rbp), %rbx
cmp %rbx, %rax
je L182
L181:
jmp L217
L182:
mov $8, %rax
mov %rax, -496(%rbp)
L183:
mov -496(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -504(%rbp)
L184:
mov -48(%rbp), %rax
mov -504(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -512(%rbp)
L185:
mov $1000000000, %rax
mov %rax, -520(%rbp)
L186:
mov -512(%rbp), %rax
mov -520(%rbp), %rbx
cmp %rbx, %rax
setne %al
movzb %al, %rax
mov %rax, -528(%rbp)
L187:
mov -528(%rbp), %rax
cmp $0, %rax
jne L189
L188:
jmp L217
L189:
mov $8, %rax
mov %rax, -536(%rbp)
L190:
mov -536(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -544(%rbp)
L191:
mov -48(%rbp), %rax
mov -544(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -552(%rbp)
L192:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -560(%rbp)
L193:
mov -392(%rbp), %rax
mov -560(%rbp), %rbx
add %rbx, %rax
mov %rax, -568(%rbp)
L194:
mov $8, %rax
mov %rax, -576(%rbp)
L195:
mov -576(%rbp), %rax
mov -568(%rbp), %rbx
imul %rbx, %rax
mov %rax, -584(%rbp)
L196:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -584(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -592(%rbp)
L197:
mov -592(%rbp), %rax
mov -552(%rbp), %rbx
add %rbx, %rax
mov %rax, -600(%rbp)
L198:
mov $8, %rax
mov %rax, -608(%rbp)
L199:
mov -608(%rbp), %rax
mov -392(%rbp), %rbx
imul %rbx, %rax
mov %rax, -616(%rbp)
L200:
mov -48(%rbp), %rax
mov -616(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -624(%rbp)
L201:
mov -600(%rbp), %rax
mov -624(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -632(%rbp)
L202:
mov -632(%rbp), %rax
cmp $0, %rax
jne L204
L203:
jmp L217
L204:
mov $8, %rax
mov %rax, -640(%rbp)
L205:
mov -640(%rbp), %rax
mov -392(%rbp), %rbx
imul %rbx, %rax
mov %rax, -648(%rbp)
L206:
mov $8, %rax
mov %rax, -656(%rbp)
L207:
mov -656(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -664(%rbp)
L208:
mov -48(%rbp), %rax
mov -664(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -672(%rbp)
L209:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -680(%rbp)
L210:
mov -392(%rbp), %rax
mov -680(%rbp), %rbx
add %rbx, %rax
mov %rax, -688(%rbp)
L211:
mov $8, %rax
mov %rax, -696(%rbp)
L212:
mov -696(%rbp), %rax
mov -688(%rbp), %rbx
imul %rbx, %rax
mov %rax, -704(%rbp)
L213:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -704(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -712(%rbp)
L214:
mov -712(%rbp), %rax
mov -672(%rbp), %rbx
add %rbx, %rax
mov %rax, -720(%rbp)
L215:
mov -48(%rbp), %rax
mov -648(%rbp), %rbx
add %rbx, %rax
mov -720(%rbp), %rbx
mov %rbx, (%rax)
L216:
L217:
L218:
mov -392(%rbp), %rax
mov %rax, -728(%rbp)
L219:
mov $1, %rax
mov %rax, -736(%rbp)
L220:
mov -736(%rbp), %rax
mov -728(%rbp), %rbx
add %rbx, %rax
mov %rax, -392(%rbp)
L221:
jmp L164
L222:
L223:
L224:
mov -64(%rbp), %rax
mov %rax, -744(%rbp)
L225:
mov $1, %rax
mov %rax, -752(%rbp)
L226:
mov -752(%rbp), %rax
mov -744(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L227:
jmp L109
L228:
L229:
mov $0, %rax
mov %rax, -760(%rbp)
L230:
mov $8, %rax
mov %rax, -768(%rbp)
L231:
mov -768(%rbp), %rax
mov -760(%rbp), %rbx
imul %rbx, %rax
mov %rax, -776(%rbp)
L232:
mov -48(%rbp), %rax
mov -776(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -784(%rbp)
L233:
mov %rbp, %rsp
mov $800, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -784(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L234:
mov %rbp, %rsp
mov $800, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
push %rax
L235:
push 32(%rbp)
push 24(%rbp)
push 16(%rbp)
call Graph_printDistances
L236:
L237:
leave
ret
L238:
L239:
L240:
L241:
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
mov $24, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -8(%rbp)
mov $0, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -16(%rbp)
mov $0, %rdi
call malloc@plt
mov %rax, %r10
mov %r10, -24(%rbp)
L242:
L243:
mov $10, %rax
mov %rax, -32(%rbp)
L244:
mov %rbp, %rsp
mov $48, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $24, %rdi
call malloc@plt
mov %rax, -40(%rbp)
L594:
mov $10, %rax
mov %rax, -48(%rbp)
L595:
mov -48(%rbp), %rax
mov -40(%rbp), %r10
mov %rax, 0(%r10)
L596:
mov -40(%rbp), %r10
mov 0(%r10), %rax
mov -40(%rbp), %r10
mov 0(%r10), %rbx
imul %rbx, %rax
mov %rax, -56(%rbp)
L597:
mov $8, %rax
mov %rax, -64(%rbp)
L598:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
imul %rbx, %rax
mov %rax, -72(%rbp)
L599:
mov %rbp, %rsp
mov $88, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -72(%rbp), %rdi
call malloc@plt
mov -40(%rbp), %r10
mov %rax, 8(%r10)
L600:
mov $0, %rax
mov %rax, -80(%rbp)
L601:
mov -80(%rbp), %rax
mov -40(%rbp), %r10
mov %rax, 16(%r10)
L245:
mov %rbp, %rsp
mov $96, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_Graph
L246:
L247:
mov $0, %rax
mov %rax, -88(%rbp)
L248:
mov $1, %rax
mov %rax, -96(%rbp)
L249:
mov $9, %rax
mov %rax, -104(%rbp)
L250:
mov %rbp, %rsp
mov $120, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -88(%rbp), %rax
push %rax
L251:
mov -96(%rbp), %rax
push %rax
L252:
mov -104(%rbp), %rax
push %rax
L253:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L254:
mov $0, %rax
mov %rax, -112(%rbp)
L255:
mov $2, %rax
mov %rax, -120(%rbp)
L256:
mov $6, %rax
mov %rax, -128(%rbp)
L257:
mov %rbp, %rsp
mov $144, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -112(%rbp), %rax
push %rax
L258:
mov -120(%rbp), %rax
push %rax
L259:
mov -128(%rbp), %rax
push %rax
L260:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L261:
mov $0, %rax
mov %rax, -136(%rbp)
L262:
mov $3, %rax
mov %rax, -144(%rbp)
L263:
mov $5, %rax
mov %rax, -152(%rbp)
L264:
mov %rbp, %rsp
mov $168, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -136(%rbp), %rax
push %rax
L265:
mov -144(%rbp), %rax
push %rax
L266:
mov -152(%rbp), %rax
push %rax
L267:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L268:
mov $0, %rax
mov %rax, -160(%rbp)
L269:
mov $4, %rax
mov %rax, -168(%rbp)
L270:
mov $3, %rax
mov %rax, -176(%rbp)
L271:
mov %rbp, %rsp
mov $192, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -160(%rbp), %rax
push %rax
L272:
mov -168(%rbp), %rax
push %rax
L273:
mov -176(%rbp), %rax
push %rax
L274:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L275:
mov $2, %rax
mov %rax, -184(%rbp)
L276:
mov $1, %rax
mov %rax, -192(%rbp)
L277:
mov $2, %rax
mov %rax, -200(%rbp)
L278:
mov %rbp, %rsp
mov $216, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -184(%rbp), %rax
push %rax
L279:
mov -192(%rbp), %rax
push %rax
L280:
mov -200(%rbp), %rax
push %rax
L281:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L282:
mov $2, %rax
mov %rax, -208(%rbp)
L283:
mov $3, %rax
mov %rax, -216(%rbp)
L284:
mov $4, %rax
mov %rax, -224(%rbp)
L285:
mov %rbp, %rsp
mov $240, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -208(%rbp), %rax
push %rax
L286:
mov -216(%rbp), %rax
push %rax
L287:
mov -224(%rbp), %rax
push %rax
L288:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L289:
mov $0, %rax
mov %rax, -232(%rbp)
L290:
mov %rbp, %rsp
mov $248, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -232(%rbp), %rax
push %rax
L291:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_dijkstra
L292:
mov %rbp, %rsp
mov $248, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %r10
mov 0(%r10), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L293:
L294:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L295:
L296:


format:
        .ascii  "%ld\n"


