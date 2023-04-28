
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
Car_fn:
push %rbp
mov %rsp, %rbp
L39:
L40:
mov $2, %rax
mov %rax, -8(%rbp)
L41:
mov -8(%rbp), %rax
mov 32(%rbp), %rbx
imul %rbx, %rax
mov %rax, -16(%rbp)
L42:
mov $5, %rax
mov %rax, -24(%rbp)
L43:
mov -24(%rbp), %rax
mov -16(%rbp), %rbx
add %rbx, %rax
mov %rax, -32(%rbp)
L44:
mov -32(%rbp), %rax
leave
ret
L45:
L46:
leave
ret
L47:
Car_pr:
push %rbp
mov %rsp, %rbp
L48:
L49:
mov %rbp, %rsp
mov $16, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov 32(%rbp), %rax
mov %rax, %rsi
 lea .note0(%rip), %rax
 mov %rax, %rdi
 xor     %rax, %rax
call printf@plt 
L50:
L51:
leave
ret
L52:
Car_wert:
push %rbp
mov %rsp, %rbp
L53:
L54:
mov $0, %rax
mov %rax, -8(%rbp)
L55:
mov 32(%rbp), %rax
mov -8(%rbp), %rbx
cmp %rbx, %rax
je L57
L56:
jmp L59
L57:
mov $0, %rax
mov %rax, -16(%rbp)
L58:
mov -16(%rbp), %rax
leave
ret
L59:
mov %rbp, %rsp
mov $32, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov 32(%rbp), %rax
push %rax
L60:
push 24(%rbp)
push 16(%rbp)
call Car_pr
L61:
mov $1, %rax
mov %rax, -24(%rbp)
L62:
mov 32(%rbp), %rax
mov -24(%rbp), %rbx
sub %rbx, %rax
mov %rax, -32(%rbp)
L63:
mov %rbp, %rsp
mov $48, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -32(%rbp), %rax
push %rax
L64:
push 24(%rbp)
push 16(%rbp)
call Car_wert
mov %rax, -40(%rbp)
L65:
mov $1, %rax
mov %rax, -48(%rbp)
L66:
mov -48(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -56(%rbp)
L67:
mov -56(%rbp), %rax
leave
ret
L68:
L69:
leave
ret
L70:
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
L772:
mov $0, %rax
mov %rax, -24(%rbp)
L773:
mov -24(%rbp), %rax
mov -8(%rbp), %r10
mov %rax, 0(%r10)
L71:
L72:
mov $0, %rax
mov %rax, -32(%rbp)
L73:
mov -32(%rbp), %rax
mov %rax, -40(%rbp)
L74:
L75:
mov $2, %rax
mov %rax, -48(%rbp)
L76:
mov -48(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -56(%rbp)
L77:
mov -56(%rbp), %rax
mov %rax, -40(%rbp)
L78:
mov %rbp, %rsp
mov $72, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L79:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L80:
mov $3, %rax
mov %rax, -64(%rbp)
L81:
mov -40(%rbp), %rax
mov -64(%rbp), %rbx
sub %rbx, %rax
mov %rax, -72(%rbp)
L82:
mov -72(%rbp), %rax
mov %rax, -80(%rbp)
L83:
L84:
mov %rbp, %rsp
mov $96, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -80(%rbp), %rax
push %rax
L85:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L86:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
imul %rbx, %rax
mov %rax, -88(%rbp)
L87:
mov -88(%rbp), %rax
mov %rax, -96(%rbp)
L88:
L89:
mov %rbp, %rsp
mov $112, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -96(%rbp), %rax
push %rax
L90:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L91:
mov $2, %rax
mov %rax, -104(%rbp)
L92:
mov -40(%rbp), %rax
mov -104(%rbp), %rbx
cqo
idiv %rbx
mov %rax, -112(%rbp)
L93:
mov -112(%rbp), %rax
mov %rax, -96(%rbp)
L94:
mov $100, %rax
mov %rax, -120(%rbp)
L95:
mov -120(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -128(%rbp)
L96:
mov -128(%rbp), %rax
mov %rax, -40(%rbp)
L97:
mov $12, %rax
mov %rax, -136(%rbp)
L98:
mov -136(%rbp), %rax
mov %rax, -144(%rbp)
L99:
L100:
mov -40(%rbp), %rax
mov -144(%rbp), %rbx
cqo
idiv %rbx
mov %rax, -152(%rbp)
L101:
mov -152(%rbp), %rax
mov %rax, -40(%rbp)
L102:
mov %rbp, %rsp
mov $168, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L103:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L104:
mov -40(%rbp), %rax
mov -40(%rbp), %rax
neg %rax
mov %rax, -160(%rbp)
mov %rax, -160(%rbp)
L105:
mov -160(%rbp), %rax
mov %rax, -40(%rbp)
L106:
mov -96(%rbp), %rax
mov -80(%rbp), %rbx
imul %rbx, %rax
mov %rax, -168(%rbp)
L107:
mov -168(%rbp), %rax
mov -40(%rbp), %rbx
cqo
idiv %rbx
mov %rax, -176(%rbp)
L108:
mov -176(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -184(%rbp)
L109:
mov -144(%rbp), %rax
mov -184(%rbp), %rbx
add %rbx, %rax
mov %rax, -192(%rbp)
L110:
mov -192(%rbp), %rax
mov -40(%rbp), %rbx
sub %rbx, %rax
mov %rax, -200(%rbp)
L111:
mov -200(%rbp), %rax
mov %rax, -40(%rbp)
L112:
mov %rbp, %rsp
mov $216, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L113:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L114:
mov -40(%rbp), %rax
mov %rax, -208(%rbp)
L115:
mov $1, %rax
mov %rax, -216(%rbp)
L116:
mov -216(%rbp), %rax
mov -208(%rbp), %rbx
add %rbx, %rax
mov %rax, -40(%rbp)
L117:
mov %rbp, %rsp
mov $232, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L118:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L119:
mov -40(%rbp), %rax
mov %rax, -224(%rbp)
L120:
mov $1, %rax
mov %rax, -232(%rbp)
L121:
mov -224(%rbp), %rax
mov -232(%rbp), %rbx
sub %rbx, %rax
mov %rax, -40(%rbp)
L122:
mov %rbp, %rsp
mov $248, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L123:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L124:
mov $1, %rax
mov %rax, -240(%rbp)
L125:
mov -240(%rbp), %rax
mov -40(%rbp), %rbx
add %rbx, %rax
mov %rax, -248(%rbp)
L126:
mov -248(%rbp), %rax
mov %rax, -40(%rbp)
L127:
mov %rbp, %rsp
mov $264, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L128:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L129:
mov $1, %rax
mov %rax, -256(%rbp)
L130:
mov -40(%rbp), %rax
mov -256(%rbp), %rbx
sub %rbx, %rax
mov %rax, -264(%rbp)
L131:
mov -264(%rbp), %rax
mov %rax, -40(%rbp)
L132:
mov %rbp, %rsp
mov $280, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L133:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L134:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
je L136
L135:
jmp L140
L136:
mov $1, %rax
mov %rax, -272(%rbp)
L137:
mov %rbp, %rsp
mov $288, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -272(%rbp), %rax
push %rax
L138:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L139:
jmp L143
L140:
mov $0, %rax
mov %rax, -280(%rbp)
L141:
mov %rbp, %rsp
mov $296, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -280(%rbp), %rax
push %rax
L142:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L143:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
setne %al
movzb %al, %rax
mov %rax, -288(%rbp)
L144:
mov -288(%rbp), %rax
cmp $0, %rax
jne L146
L145:
jmp L150
L146:
mov $1, %rax
mov %rax, -296(%rbp)
L147:
mov %rbp, %rsp
mov $312, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -296(%rbp), %rax
push %rax
L148:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L149:
jmp L153
L150:
mov $0, %rax
mov %rax, -304(%rbp)
L151:
mov %rbp, %rsp
mov $320, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -304(%rbp), %rax
push %rax
L152:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L153:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
setg %al
movzb %al, %rax
mov %rax, -312(%rbp)
L154:
mov -312(%rbp), %rax
cmp $0, %rax
jne L156
L155:
jmp L160
L156:
mov $1, %rax
mov %rax, -320(%rbp)
L157:
mov %rbp, %rsp
mov $336, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -320(%rbp), %rax
push %rax
L158:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L159:
jmp L163
L160:
mov $0, %rax
mov %rax, -328(%rbp)
L161:
mov %rbp, %rsp
mov $344, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -328(%rbp), %rax
push %rax
L162:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L163:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -336(%rbp)
L164:
mov -336(%rbp), %rax
cmp $0, %rax
jne L166
L165:
jmp L170
L166:
mov $1, %rax
mov %rax, -344(%rbp)
L167:
mov %rbp, %rsp
mov $360, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -344(%rbp), %rax
push %rax
L168:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L169:
jmp L173
L170:
mov $0, %rax
mov %rax, -352(%rbp)
L171:
mov %rbp, %rsp
mov $368, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -352(%rbp), %rax
push %rax
L172:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L173:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
setge %al
movzb %al, %rax
mov %rax, -360(%rbp)
L174:
mov -360(%rbp), %rax
cmp $0, %rax
jne L176
L175:
jmp L180
L176:
mov $1, %rax
mov %rax, -368(%rbp)
L177:
mov %rbp, %rsp
mov $384, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -368(%rbp), %rax
push %rax
L178:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L179:
jmp L183
L180:
mov $0, %rax
mov %rax, -376(%rbp)
L181:
mov %rbp, %rsp
mov $392, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -376(%rbp), %rax
push %rax
L182:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L183:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
setle %al
movzb %al, %rax
mov %rax, -384(%rbp)
L184:
mov -384(%rbp), %rax
cmp $0, %rax
jne L186
L185:
jmp L190
L186:
mov $1, %rax
mov %rax, -392(%rbp)
L187:
mov %rbp, %rsp
mov $408, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -392(%rbp), %rax
push %rax
L188:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L189:
jmp L193
L190:
mov $0, %rax
mov %rax, -400(%rbp)
L191:
mov %rbp, %rsp
mov $416, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -400(%rbp), %rax
push %rax
L192:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L193:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
and %rbx, %rax
mov %rax, -408(%rbp)
L194:
mov -408(%rbp), %rax
mov %rax, -416(%rbp)
L195:
L196:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
or %rbx, %rax
mov %rax, -424(%rbp)
L197:
mov -424(%rbp), %rax
mov %rax, -416(%rbp)
L198:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
xor %rbx, %rax
mov %rax, -432(%rbp)
L199:
mov -432(%rbp), %rax
mov %rax, -416(%rbp)
L200:
mov -40(%rbp), %rax
not %rax
mov %rax, -440(%rbp)
L201:
mov -440(%rbp), %rax
mov %rax, -416(%rbp)
L202:
mov $2, %rax
mov %rax, -448(%rbp)
L203:
mov -40(%rbp), %rax
mov -448(%rbp), %cl
sal %cl, %rax
mov %rax, -456(%rbp)
L204:
mov -456(%rbp), %rax
mov %rax, -416(%rbp)
L205:
mov $2, %rax
mov %rax, -464(%rbp)
L206:
mov -40(%rbp), %rax
mov -464(%rbp), %cl
sar %cl, %rax
mov %rax, -472(%rbp)
L207:
mov -472(%rbp), %rax
mov %rax, -416(%rbp)
L208:
mov $2, %rax
mov %rax, -480(%rbp)
L209:
mov -40(%rbp), %rax
mov -480(%rbp), %cl
shr %cl, %rax
mov %rax, -488(%rbp)
L210:
mov -488(%rbp), %rax
mov %rax, -416(%rbp)
L211:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
je L213
L212:
jmp L220
L213:
mov -80(%rbp), %rax
mov -96(%rbp), %rbx
cmp %rbx, %rax
je L215
L214:
jmp L220
L215:
mov $1, %rax
mov %rax, -496(%rbp)
L216:
mov %rbp, %rsp
mov $512, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -496(%rbp), %rax
push %rax
L217:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L218:
L219:
jmp L223
L220:
mov $0, %rax
mov %rax, -504(%rbp)
L221:
mov %rbp, %rsp
mov $520, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -504(%rbp), %rax
push %rax
L222:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L223:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
je L227
L224:
jmp L225
L225:
mov -80(%rbp), %rax
mov -96(%rbp), %rbx
cmp %rbx, %rax
je L227
L226:
jmp L231
L227:
mov $1, %rax
mov %rax, -512(%rbp)
L228:
mov %rbp, %rsp
mov $528, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -512(%rbp), %rax
push %rax
L229:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L230:
jmp L234
L231:
mov $0, %rax
mov %rax, -520(%rbp)
L232:
mov %rbp, %rsp
mov $536, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -520(%rbp), %rax
push %rax
L233:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L234:
mov $0, %rax
mov %rax, -528(%rbp)
L235:
L236:
L237:
mov -536(%rbp), %rax
cmp $0, %rax
sete %al
movzb %al, %rax
mov %rax, -544(%rbp)
L238:
mov $1, %rax
mov %rax, -552(%rbp)
L239:
mov %rbp, %rsp
mov $568, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -552(%rbp), %rax
push %rax
L240:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L241:
jmp L245
L242:
mov $0, %rax
mov %rax, -560(%rbp)
L243:
mov %rbp, %rsp
mov $576, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -560(%rbp), %rax
push %rax
L244:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L245:
mov -80(%rbp), %rax
mov %rax, -40(%rbp)
L246:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
add %rbx, %rax
mov %rax, -40(%rbp)
L247:
mov %rbp, %rsp
mov $576, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L248:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L249:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
sub %rbx, %rax
mov %rax, -40(%rbp)
L250:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
imul %rbx, %rax
mov %rax, -40(%rbp)
L251:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cqo
idiv %rbx
mov %rax, -40(%rbp)
L252:
mov %rbp, %rsp
mov $576, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L253:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L254:
L255:
L256:
mov $1, %rax
mov %rax, -568(%rbp)
L257:
mov $2, %rax
mov %rax, -576(%rbp)
L258:
mov -584(%rbp), %rax
cmp $0, %rax
jne L259
L259:
mov -568(%rbp), %rax
mov %rax, -592(%rbp)
L260:
jmp L262
L261:
mov -576(%rbp), %rax
mov %rax, -592(%rbp)
L262:
mov -592(%rbp), %rax
mov %rax, -40(%rbp)
L263:
mov %rbp, %rsp
mov $608, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L264:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L265:
mov $0, %rax
mov %rax, -600(%rbp)
L266:
mov -600(%rbp), %rax
mov %rax, -608(%rbp)
L267:
L268:
mov $2, %rax
mov %rax, -616(%rbp)
L269:
mov -608(%rbp), %rax
mov -616(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -624(%rbp)
L270:
mov -624(%rbp), %rax
cmp $0, %rax
jne L272
L271:
jmp L317
L272:
mov -40(%rbp), %rax
mov -80(%rbp), %rbx
cmp %rbx, %rax
je L274
L273:
jmp L293
L274:
mov $0, %rax
mov %rax, -632(%rbp)
L275:
mov -632(%rbp), %rax
mov %rax, -640(%rbp)
L276:
L277:
mov $20, %rax
mov %rax, -648(%rbp)
L278:
mov -640(%rbp), %rax
mov -648(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -656(%rbp)
L279:
mov -656(%rbp), %rax
cmp $0, %rax
jne L281
L280:
jmp L291
L281:
mov -40(%rbp), %rax
mov %rax, -664(%rbp)
L282:
mov $1, %rax
mov %rax, -672(%rbp)
L283:
mov -672(%rbp), %rax
mov -664(%rbp), %rbx
add %rbx, %rax
mov %rax, -40(%rbp)
L284:
mov -640(%rbp), %rax
mov %rax, -680(%rbp)
L285:
mov $1, %rax
mov %rax, -688(%rbp)
L286:
mov -688(%rbp), %rax
mov -680(%rbp), %rbx
add %rbx, %rax
mov %rax, -640(%rbp)
L287:
mov %rbp, %rsp
mov $704, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -640(%rbp), %rax
push %rax
L288:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L289:
L290:
jmp L277
L291:
L292:
jmp L312
L293:
mov $0, %rax
mov %rax, -696(%rbp)
L294:
mov -696(%rbp), %rax
mov %rax, -704(%rbp)
L295:
L296:
mov $23, %rax
mov %rax, -712(%rbp)
L297:
mov -704(%rbp), %rax
mov -712(%rbp), %rbx
cmp %rbx, %rax
setl %al
movzb %al, %rax
mov %rax, -720(%rbp)
L298:
mov -720(%rbp), %rax
cmp $0, %rax
jne L300
L299:
jmp L310
L300:
mov -40(%rbp), %rax
mov %rax, -728(%rbp)
L301:
mov $1, %rax
mov %rax, -736(%rbp)
L302:
mov -728(%rbp), %rax
mov -736(%rbp), %rbx
sub %rbx, %rax
mov %rax, -40(%rbp)
L303:
mov %rbp, %rsp
mov $752, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -704(%rbp), %rax
push %rax
L304:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L305:
L306:
mov -704(%rbp), %rax
mov %rax, -744(%rbp)
L307:
mov $1, %rax
mov %rax, -752(%rbp)
L308:
mov -752(%rbp), %rax
mov -744(%rbp), %rbx
add %rbx, %rax
mov %rax, -704(%rbp)
L309:
jmp L296
L310:
L311:
L312:
L313:
mov -608(%rbp), %rax
mov %rax, -760(%rbp)
L314:
mov $1, %rax
mov %rax, -768(%rbp)
L315:
mov -768(%rbp), %rax
mov -760(%rbp), %rbx
add %rbx, %rax
mov %rax, -608(%rbp)
L316:
jmp L268
L317:
L318:
mov %rbp, %rsp
mov $784, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L319:
push -8(%rbp)
push -16(%rbp)
call Car_fn
mov %rax, -776(%rbp)
L320:
mov -776(%rbp), %rax
mov %rax, -40(%rbp)
L321:
mov %rbp, %rsp
mov $792, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -40(%rbp), %rax
push %rax
L322:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L323:
mov $3, %rax
mov %rax, -784(%rbp)
L324:
mov %rbp, %rsp
mov $800, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -784(%rbp), %rax
push %rax
L325:
push -8(%rbp)
push -16(%rbp)
call Car_wert
mov %rax, -792(%rbp)
L326:
mov -792(%rbp), %rax
mov %rax, -800(%rbp)
L327:
L328:
mov %rbp, %rsp
mov $816, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -800(%rbp), %rax
push %rax
L329:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L330:
mov $1001, %rax
mov %rax, -808(%rbp)
L331:
mov $2015, %rax
mov %rax, -816(%rbp)
L332:
mov $50000, %rax
mov %rax, -824(%rbp)
L333:
mov %rbp, %rsp
mov $840, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $32, %rdi
call malloc@plt
mov %rax, -832(%rbp)
L774:
mov $1, %rax
mov %rax, -840(%rbp)
L775:
mov -840(%rbp), %rax
mov -832(%rbp), %r10
mov %rax, 8(%r10)
L334:
mov %rbp, %rsp
mov $856, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -808(%rbp), %rax
push %rax
L335:
mov -816(%rbp), %rax
push %rax
L336:
mov -824(%rbp), %rax
push %rax
L337:
push -8(%rbp)
push -832(%rbp)
call Car_Car
L338:
L339:
mov %rbp, %rsp
mov $856, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -8(%rbp), %r10
mov 0(%r10), %rax
push %rax
L340:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L341:
mov %rbp, %rsp
mov $856, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -832(%rbp)
call Car_getModel
mov %rax, -848(%rbp)
L342:
mov %rbp, %rsp
mov $864, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -848(%rbp), %rax
push %rax
L343:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L344:
mov %rbp, %rsp
mov $864, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -832(%rbp)
call Car_getYear
mov %rax, -856(%rbp)
L345:
mov %rbp, %rsp
mov $872, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -856(%rbp), %rax
push %rax
L346:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L347:
mov %rbp, %rsp
mov $872, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -832(%rbp)
call Car_getMileage
mov %rax, -864(%rbp)
L348:
mov %rbp, %rsp
mov $880, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -864(%rbp), %rax
push %rax
L349:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L350:
mov $55000, %rax
mov %rax, -872(%rbp)
L351:
mov %rbp, %rsp
mov $888, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -872(%rbp), %rax
push %rax
L352:
push -8(%rbp)
push -832(%rbp)
call Car_setMileage
L353:
mov %rbp, %rsp
mov $888, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -832(%rbp)
call Car_getMileage
mov %rax, -880(%rbp)
L354:
mov %rbp, %rsp
mov $896, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -880(%rbp), %rax
push %rax
L355:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L356:
mov $1002, %rax
mov %rax, -888(%rbp)
L357:
mov $2020, %rax
mov %rax, -896(%rbp)
L358:
mov $15000, %rax
mov %rax, -904(%rbp)
L359:
mov %rbp, %rsp
mov $920, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov $32, %rdi
call malloc@plt
mov %rax, -912(%rbp)
L776:
mov $1, %rax
mov %rax, -840(%rbp)
L777:
mov -840(%rbp), %rax
mov -912(%rbp), %r10
mov %rax, 8(%r10)
L360:
mov %rbp, %rsp
mov $928, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -888(%rbp), %rax
push %rax
L361:
mov -896(%rbp), %rax
push %rax
L362:
mov -904(%rbp), %rax
push %rax
L363:
push -8(%rbp)
push -912(%rbp)
call Car_Car
L364:
L365:
mov %rbp, %rsp
mov $928, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -8(%rbp), %r10
mov 0(%r10), %rax
push %rax
L366:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L367:
mov %rbp, %rsp
mov $928, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -912(%rbp)
call Car_getModel
mov %rax, -920(%rbp)
L368:
mov %rbp, %rsp
mov $936, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -920(%rbp), %rax
push %rax
L369:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L370:
mov %rbp, %rsp
mov $936, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -912(%rbp)
call Car_getYear
mov %rax, -928(%rbp)
L371:
mov %rbp, %rsp
mov $944, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -928(%rbp), %rax
push %rax
L372:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L373:
mov %rbp, %rsp
mov $944, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -912(%rbp)
call Car_getMileage
mov %rax, -936(%rbp)
L374:
mov %rbp, %rsp
mov $952, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -936(%rbp), %rax
push %rax
L375:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L376:
mov $20000, %rax
mov %rax, -944(%rbp)
L377:
mov %rbp, %rsp
mov $960, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -944(%rbp), %rax
push %rax
L378:
push -8(%rbp)
push -912(%rbp)
call Car_setMileage
L379:
mov %rbp, %rsp
mov $960, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
push -8(%rbp)
push -912(%rbp)
call Car_getMileage
mov %rax, -952(%rbp)
L380:
mov %rbp, %rsp
mov $968, %r9
shr $4, %r9
add $1, %r9
shl $4, %r9
sub %r9, %rsp
mov -952(%rbp), %rax
push %rax
L381:
push -8(%rbp)
push -16(%rbp)
call Car_pr
L382:
L383:

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
leave
ret
L384:
L385:


format:
        .ascii  "%ld\n"


