
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
Graph_Graph:
push %rbp
mov %rsp, %rbp
L10:
L11:
mov 40(%rbp), %rax
mov 16(%rbp), %r10
mov %rax, 0(%r10)
L12:
L13:
leave
ret
L14:
Graph_addEdge:
push %rbp
mov %rsp, %rbp
L15:
L16:
L17:
L18:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov 56(%rbp), %rbx
imul %rbx, %rax
mov %rax, -8(%rbp)
L19:
mov 48(%rbp), %rax
mov -8(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L20:
mov $8, %rax
mov %rax, -24(%rbp)
L21:
mov -24(%rbp), %rax
mov -16(%rbp), %rbx
imul %rbx, %rax
mov %rax, -32(%rbp)
L22:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -32(%rbp), %rbx
add %rbx, %rax
mov 40(%rbp), %rbx
mov %rbx, (%rax)
L23:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov 48(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L24:
mov 56(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -48(%rbp)
L25:
mov $8, %rax
mov %rax, -56(%rbp)
L26:
mov -56(%rbp), %rax
mov -48(%rbp), %rbx
imul %rbx, %rax
mov %rax, -64(%rbp)
L27:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -64(%rbp), %rbx
add %rbx, %rax
mov 40(%rbp), %rbx
mov %rbx, (%rax)
L28:
L29:
leave
ret
L30:
Graph_printDistances:
push %rbp
mov %rsp, %rbp
L31:
L32:
mov $0, %rax
mov %rax, -8(%rbp)
L33:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L34:
L35:
mov -16(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -24(%rbp)
L36:
mov -24(%rbp), %rax
cmp $0, %rax
jne L38
L37:
jmp L47
L38:
mov $8, %rax
mov %rax, -32(%rbp)
L39:
mov -32(%rbp), %rax
mov -16(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L40:
mov 40(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -48(%rbp)
L41:
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
L42:
L43:
mov -16(%rbp), %rax
mov %rax, -56(%rbp)
L44:
mov $1, %rax
mov %rax, -64(%rbp)
L45:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L46:
jmp L35
L47:
L48:
L49:
leave
ret
L50:
Graph_printGraph:
push %rbp
mov %rsp, %rbp
L51:
mov $0, %rax
mov %rax, -8(%rbp)
L52:
mov -8(%rbp), %rax
mov %rax, -16(%rbp)
L53:
L54:
mov -16(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -24(%rbp)
L55:
mov -24(%rbp), %rax
cmp $0, %rax
jne L57
L56:
jmp L80
L57:
mov $0, %rax
mov %rax, -32(%rbp)
L58:
mov -32(%rbp), %rax
mov %rax, -40(%rbp)
L59:
L60:
mov -40(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -48(%rbp)
L61:
mov -48(%rbp), %rax
cmp $0, %rax
jne L63
L62:
jmp L74
L63:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -16(%rbp), %rbx
imul %rbx, %rax
mov %rax, -56(%rbp)
L64:
mov -40(%rbp), %rax
mov -56(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L65:
mov $8, %rax
mov %rax, -72(%rbp)
L66:
mov -72(%rbp), %rax
mov -64(%rbp), %rbx
imul %rbx, %rax
mov %rax, -80(%rbp)
L67:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -80(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -88(%rbp)
L68:
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
L69:
L70:
mov -40(%rbp), %rax
mov %rax, -96(%rbp)
L71:
mov $1, %rax
mov %rax, -104(%rbp)
L72:
mov -104(%rbp), %rax
mov -96(%rbp), %rbx
add %rbx, %rax
mov %rax, -40(%rbp)
L73:
jmp L60
L74:
L75:
L76:
mov -16(%rbp), %rax
mov %rax, -112(%rbp)
L77:
mov $1, %rax
mov %rax, -120(%rbp)
L78:
mov -120(%rbp), %rax
mov -112(%rbp), %rbx
add %rbx, %rax
mov %rax, -16(%rbp)
L79:
jmp L54
L80:
L81:
L82:
leave
ret
L83:
Graph_dijkstra:
push %rbp
mov %rsp, %rbp
L84:
L85:
mov $8, %rax
mov %rax, -8(%rbp)
L86:
mov -8(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
imul %rbx, %rax
mov %rax, -16(%rbp)
L87:
mov %rbp, %rsp
mov $32, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -16(%rbp), %rdi
call malloc@plt
mov %rax, -24(%rbp)
L88:
L89:
mov $8, %rax
mov %rax, -32(%rbp)
L90:
mov -32(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L91:
mov %rbp, %rsp
mov $56, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rdi
call malloc@plt
mov %rax, -48(%rbp)
L92:
L93:
mov $0, %rax
mov %rax, -56(%rbp)
L94:
mov -56(%rbp), %rax
mov %rax, -64(%rbp)
L95:
L96:
mov -64(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -72(%rbp)
L97:
mov -72(%rbp), %rax
cmp $0, %rax
jne L99
L98:
jmp L108
L99:
mov $8, %rax
mov %rax, -80(%rbp)
L100:
mov -80(%rbp), %rax
mov -64(%rbp), %rbx
imul %rbx, %rax
mov %rax, -88(%rbp)
L101:
mov $1000000000, %rax
mov %rax, -96(%rbp)
L102:
mov -48(%rbp), %rax
mov -88(%rbp), %rbx
add %rbx, %rax
mov -96(%rbp), %rbx
mov %rbx, (%rax)
L103:
L104:
mov -64(%rbp), %rax
mov %rax, -104(%rbp)
L105:
mov $1, %rax
mov %rax, -112(%rbp)
L106:
mov -112(%rbp), %rax
mov -104(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L107:
jmp L96
L108:
L109:
mov $8, %rax
mov %rax, -120(%rbp)
L110:
mov -120(%rbp), %rax
mov 40(%rbp), %rbx
imul %rbx, %rax
mov %rax, -128(%rbp)
L111:
mov $0, %rax
mov %rax, -136(%rbp)
L112:
mov -48(%rbp), %rax
mov -128(%rbp), %rbx
add %rbx, %rax
mov -136(%rbp), %rbx
mov %rbx, (%rax)
L113:
mov $0, %rax
mov %rax, -144(%rbp)
L114:
mov -144(%rbp), %rax
mov %rax, -64(%rbp)
L115:
L116:
mov $1, %rax
mov %rax, -152(%rbp)
L117:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -152(%rbp), %rbx
sub %rbx, %rax
mov %rax, -160(%rbp)
L118:
mov -64(%rbp), %rax
mov -160(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -168(%rbp)
L119:
mov -168(%rbp), %rax
cmp $0, %rax
jne L121
L120:
jmp L235
L121:
mov $1000000000, %rax
mov %rax, -176(%rbp)
L122:
mov -176(%rbp), %rax
mov %rax, -184(%rbp)
L123:
L124:
mov $1, %rax
mov %rax, -192(%rbp)
L125:
mov -192(%rbp), %rax
mov -192(%rbp), %rax
neg %rax
mov %rax, -200(%rbp)
mov %rax, -200(%rbp)
L126:
mov -200(%rbp), %rax
mov %rax, -208(%rbp)
L127:
L128:
mov $0, %rax
mov %rax, -216(%rbp)
L129:
mov -216(%rbp), %rax
mov %rax, -224(%rbp)
L130:
L131:
mov -224(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -232(%rbp)
L132:
mov -232(%rbp), %rax
cmp $0, %rax
jne L134
L133:
jmp L157
L134:
mov $8, %rax
mov %rax, -240(%rbp)
L135:
mov -240(%rbp), %rax
mov -224(%rbp), %rbx
imul %rbx, %rax
mov %rax, -248(%rbp)
L136:
mov -24(%rbp), %rax
mov -248(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -256(%rbp)
L137:
mov $0, %rax
mov %rax, -264(%rbp)
L138:
mov -256(%rbp), %rax
mov -264(%rbp), %rbx
cmp %rbx, %rax
je L140
L139:
jmp L152
L140:
mov $8, %rax
mov %rax, -272(%rbp)
L141:
mov -272(%rbp), %rax
mov -224(%rbp), %rbx
imul %rbx, %rax
mov %rax, -280(%rbp)
L142:
mov -48(%rbp), %rax
mov -280(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -288(%rbp)
L143:
mov -288(%rbp), %rax
mov -184(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -296(%rbp)
L144:
mov -296(%rbp), %rax
cmp $0, %rax
jne L146
L145:
jmp L152
L146:
mov $8, %rax
mov %rax, -304(%rbp)
L147:
mov -304(%rbp), %rax
mov -224(%rbp), %rbx
imul %rbx, %rax
mov %rax, -312(%rbp)
L148:
mov -48(%rbp), %rax
mov -312(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -320(%rbp)
L149:
mov -320(%rbp), %rax
mov %rax, -184(%rbp)
L150:
mov -224(%rbp), %rax
mov %rax, -208(%rbp)
L151:
L152:
L153:
mov -224(%rbp), %rax
mov %rax, -328(%rbp)
L154:
mov $1, %rax
mov %rax, -336(%rbp)
L155:
mov -336(%rbp), %rax
mov -328(%rbp), %rbx
add %rbx, %rax
mov %rax, -224(%rbp)
L156:
jmp L131
L157:
L158:
mov $1, %rax
mov %rax, -344(%rbp)
L159:
mov -344(%rbp), %rax
mov -344(%rbp), %rax
neg %rax
mov %rax, -352(%rbp)
mov %rax, -352(%rbp)
L160:
mov -208(%rbp), %rax
mov -352(%rbp), %rbx
cmp %rbx, %rax
je L162
L161:
jmp L164
L162:
jmp L235
L163:
L164:
mov $8, %rax
mov %rax, -360(%rbp)
L165:
mov -360(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -368(%rbp)
L166:
mov $1, %rax
mov %rax, -376(%rbp)
L167:
mov -24(%rbp), %rax
mov -368(%rbp), %rbx
add %rbx, %rax
mov -376(%rbp), %rbx
mov %rbx, (%rax)
L168:
mov $0, %rax
mov %rax, -384(%rbp)
L169:
mov -384(%rbp), %rax
mov %rax, -392(%rbp)
L170:
L171:
mov -392(%rbp), %rax
mov 16(%rbp), %r10
mov 0(%r10), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -400(%rbp)
L172:
mov -400(%rbp), %rax
cmp $0, %rax
jne L174
L173:
jmp L229
L174:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -408(%rbp)
L175:
mov -392(%rbp), %rax
mov -408(%rbp), %rbx
add %rbx, %rax
mov %rax, -416(%rbp)
L176:
mov $8, %rax
mov %rax, -424(%rbp)
L177:
mov -424(%rbp), %rax
mov -416(%rbp), %rbx
imul %rbx, %rax
mov %rax, -432(%rbp)
L178:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -432(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -440(%rbp)
L179:
mov $0, %rax
mov %rax, -448(%rbp)
L180:
mov -440(%rbp), %rax
mov -448(%rbp), %rbx
cmp %rbx, %rax
setne %al
movzb %al, %rax
mov %rax, -456(%rbp)
L181:
mov -456(%rbp), %rax
cmp $0, %rax
jne L183
L182:
jmp L224
L183:
mov $8, %rax
mov %rax, -464(%rbp)
L184:
mov -464(%rbp), %rax
mov -392(%rbp), %rbx
imul %rbx, %rax
mov %rax, -472(%rbp)
L185:
mov -24(%rbp), %rax
mov -472(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -480(%rbp)
L186:
mov $0, %rax
mov %rax, -488(%rbp)
L187:
mov -480(%rbp), %rax
mov -488(%rbp), %rbx
cmp %rbx, %rax
je L189
L188:
jmp L224
L189:
mov $8, %rax
mov %rax, -496(%rbp)
L190:
mov -496(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -504(%rbp)
L191:
mov -48(%rbp), %rax
mov -504(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -512(%rbp)
L192:
mov $1000000000, %rax
mov %rax, -520(%rbp)
L193:
mov -512(%rbp), %rax
mov -520(%rbp), %rbx
cmp %rbx, %rax
setne %al
movzb %al, %rax
mov %rax, -528(%rbp)
L194:
mov -528(%rbp), %rax
cmp $0, %rax
jne L196
L195:
jmp L224
L196:
mov $8, %rax
mov %rax, -536(%rbp)
L197:
mov -536(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -544(%rbp)
L198:
mov -48(%rbp), %rax
mov -544(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -552(%rbp)
L199:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -560(%rbp)
L200:
mov -392(%rbp), %rax
mov -560(%rbp), %rbx
add %rbx, %rax
mov %rax, -568(%rbp)
L201:
mov $8, %rax
mov %rax, -576(%rbp)
L202:
mov -576(%rbp), %rax
mov -568(%rbp), %rbx
imul %rbx, %rax
mov %rax, -584(%rbp)
L203:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -584(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -592(%rbp)
L204:
mov -592(%rbp), %rax
mov -552(%rbp), %rbx
add %rbx, %rax
mov %rax, -600(%rbp)
L205:
mov $8, %rax
mov %rax, -608(%rbp)
L206:
mov -608(%rbp), %rax
mov -392(%rbp), %rbx
imul %rbx, %rax
mov %rax, -616(%rbp)
L207:
mov -48(%rbp), %rax
mov -616(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -624(%rbp)
L208:
mov -600(%rbp), %rax
mov -624(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -632(%rbp)
L209:
mov -632(%rbp), %rax
cmp $0, %rax
jne L211
L210:
jmp L224
L211:
mov $8, %rax
mov %rax, -640(%rbp)
L212:
mov -640(%rbp), %rax
mov -392(%rbp), %rbx
imul %rbx, %rax
mov %rax, -648(%rbp)
L213:
mov $8, %rax
mov %rax, -656(%rbp)
L214:
mov -656(%rbp), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -664(%rbp)
L215:
mov -48(%rbp), %rax
mov -664(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -672(%rbp)
L216:
mov 16(%rbp), %r10
mov 0(%r10), %rax
mov -208(%rbp), %rbx
imul %rbx, %rax
mov %rax, -680(%rbp)
L217:
mov -392(%rbp), %rax
mov -680(%rbp), %rbx
add %rbx, %rax
mov %rax, -688(%rbp)
L218:
mov $8, %rax
mov %rax, -696(%rbp)
L219:
mov -696(%rbp), %rax
mov -688(%rbp), %rbx
imul %rbx, %rax
mov %rax, -704(%rbp)
L220:
mov 16(%rbp), %r10
mov 8(%r10), %rax
mov -704(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -712(%rbp)
L221:
mov -712(%rbp), %rax
mov -672(%rbp), %rbx
add %rbx, %rax
mov %rax, -720(%rbp)
L222:
mov -48(%rbp), %rax
mov -648(%rbp), %rbx
add %rbx, %rax
mov -720(%rbp), %rbx
mov %rbx, (%rax)
L223:
L224:
L225:
mov -392(%rbp), %rax
mov %rax, -728(%rbp)
L226:
mov $1, %rax
mov %rax, -736(%rbp)
L227:
mov -736(%rbp), %rax
mov -728(%rbp), %rbx
add %rbx, %rax
mov %rax, -392(%rbp)
L228:
jmp L171
L229:
L230:
L231:
mov -64(%rbp), %rax
mov %rax, -744(%rbp)
L232:
mov $1, %rax
mov %rax, -752(%rbp)
L233:
mov -752(%rbp), %rax
mov -744(%rbp), %rbx
add %rbx, %rax
mov %rax, -64(%rbp)
L234:
jmp L116
L235:
L236:
mov $0, %rax
mov %rax, -760(%rbp)
L237:
mov $8, %rax
mov %rax, -768(%rbp)
L238:
mov -768(%rbp), %rax
mov -760(%rbp), %rbx
imul %rbx, %rax
mov %rax, -776(%rbp)
L239:
mov -48(%rbp), %rax
mov -776(%rbp), %rbx
add %rbx, %rax
mov (%rax), %rbx
mov %rbx, -784(%rbp)
L240:
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
L241:
mov %rbp, %rsp
mov $800, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -48(%rbp), %rax
push %rax
L242:
push 32(%rbp)
push 24(%rbp)
push 16(%rbp)
call Graph_printDistances
L243:
L244:
leave
ret
L245:
L246:
L247:
L248:
Dijkstra_addEdge:
push %rbp
mov %rsp, %rbp
L249:
L250:
L251:
L252:
mov $1, %rax
mov %rax, -8(%rbp)
L253:
mov -8(%rbp), %rax
mov -8(%rbp), %rax
neg %rax
mov %rax, -16(%rbp)
mov %rax, -16(%rbp)
L254:
mov %rbp, %rsp
mov $32, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -16(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L255:
L256:
leave
ret
L257:
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
mov $16, %rdi
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
L258:
L259:
mov $5, %rax
mov %rax, -32(%rbp)
L260:
mov %rbp, %rsp
mov $48, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $16, %rdi
call malloc@plt
mov %rax, -40(%rbp)
L628:
mov $100, %rax
mov %rax, -48(%rbp)
L629:
mov -48(%rbp), %rax
mov -40(%rbp), %r10
mov %rax, 0(%r10)
L630:
mov -40(%rbp), %r10
mov 0(%r10), %rax
mov -40(%rbp), %r10
mov 0(%r10), %rbx
imul %rbx, %rax
mov %rax, -56(%rbp)
L631:
mov $8, %rax
mov %rax, -64(%rbp)
L632:
mov -64(%rbp), %rax
mov -56(%rbp), %rbx
imul %rbx, %rax
mov %rax, -72(%rbp)
L633:
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
L261:
mov %rbp, %rsp
mov $88, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -32(%rbp), %rax
push %rax
L262:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_Graph
L263:
L264:
mov $0, %rax
mov %rax, -80(%rbp)
L265:
mov $1, %rax
mov %rax, -88(%rbp)
L266:
mov $9, %rax
mov %rax, -96(%rbp)
L267:
mov %rbp, %rsp
mov $112, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -80(%rbp), %rax
push %rax
L268:
mov -88(%rbp), %rax
push %rax
L269:
mov -96(%rbp), %rax
push %rax
L270:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L271:
mov $0, %rax
mov %rax, -104(%rbp)
L272:
mov $2, %rax
mov %rax, -112(%rbp)
L273:
mov $6, %rax
mov %rax, -120(%rbp)
L274:
mov %rbp, %rsp
mov $136, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -104(%rbp), %rax
push %rax
L275:
mov -112(%rbp), %rax
push %rax
L276:
mov -120(%rbp), %rax
push %rax
L277:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L278:
mov $0, %rax
mov %rax, -128(%rbp)
L279:
mov $3, %rax
mov %rax, -136(%rbp)
L280:
mov $5, %rax
mov %rax, -144(%rbp)
L281:
mov %rbp, %rsp
mov $160, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -128(%rbp), %rax
push %rax
L282:
mov -136(%rbp), %rax
push %rax
L283:
mov -144(%rbp), %rax
push %rax
L284:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L285:
mov $0, %rax
mov %rax, -152(%rbp)
L286:
mov $4, %rax
mov %rax, -160(%rbp)
L287:
mov $3, %rax
mov %rax, -168(%rbp)
L288:
mov %rbp, %rsp
mov $184, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -152(%rbp), %rax
push %rax
L289:
mov -160(%rbp), %rax
push %rax
L290:
mov -168(%rbp), %rax
push %rax
L291:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L292:
mov $2, %rax
mov %rax, -176(%rbp)
L293:
mov $1, %rax
mov %rax, -184(%rbp)
L294:
mov $2, %rax
mov %rax, -192(%rbp)
L295:
mov %rbp, %rsp
mov $208, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -176(%rbp), %rax
push %rax
L296:
mov -184(%rbp), %rax
push %rax
L297:
mov -192(%rbp), %rax
push %rax
L298:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L299:
mov $2, %rax
mov %rax, -200(%rbp)
L300:
mov $3, %rax
mov %rax, -208(%rbp)
L301:
mov $4, %rax
mov %rax, -216(%rbp)
L302:
mov %rbp, %rsp
mov $232, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -200(%rbp), %rax
push %rax
L303:
mov -208(%rbp), %rax
push %rax
L304:
mov -216(%rbp), %rax
push %rax
L305:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_addEdge
L306:
mov $0, %rax
mov %rax, -224(%rbp)
L307:
mov %rbp, %rsp
mov $240, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -224(%rbp), %rax
push %rax
L308:
push -8(%rbp)
push -16(%rbp)
push -40(%rbp)
call Graph_dijkstra
L309:
mov %rbp, %rsp
mov $240, %r9
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
L310:
L311:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L312:
L313:


format:
        .ascii  "%ld\n"


