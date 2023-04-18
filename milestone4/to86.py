data =None
with open ("./outputs/10_3ac.txt", "r") as myfile:
    data=myfile.readlines()

sample = """0 begin func findGCD
1 t1 = 0
2 if b == t1 goto  4
3 goto  6
4 return a
5 stackpointer - 0
6 t3 = 0
7 t4 = b != t3
8 if t4 goto  10
9 goto  16
10 t5 = a %int b
11 push param b
12 push param t5
13 t6 = call, findGCD
14 return t6
15 stackpointer - 0
16 stackpointer - 0
17 pop param, a
18 pop param, b
19 end func
20 begin func main
21 t7 = 100
22 num1 = t7
23 stackpointer + 4
24 t8 = 134
25 num2 = t8
26 stackpointer + 4
27 push param num1
28 push param num2
29 t9 = call, findGCD
30 gcd = t9
31 stackpointer + 4
32 print gcd
33 stackpointer - 12
34 pop param, args
35 end func
36 stackpointer - 0


"""


offset = -8
boolenter =0
boolmain=0
var2offset = {}
retoffset=16

def retaddr (a):
    if(a in var2offset.keys()):
        return var2offset[a]
    
    global offset

    var2offset[a] = offset

    offset = offset - 8
    return var2offset[a]


out =[]
out.append("""
        .global main

        .text

   """)


for line in data:
    line = line.strip()
    while(line.find("  ")!=-1):
        line = line.replace("  ", " ")
    elements = line.split()
    if(len(elements)<=1):
        continue
    for i in range(len(elements)):
        elements[i] = elements[i].strip()
    out.append("L"+ elements[0] + ":")
    # print(elements)
    elements= elements[1:]
    
    if(elements[0] == 'begin'):
        boolmain=0
        boolenter=0
        out.append(elements[2] + ":")
        offset=-8
        retoffset=16
        var2offset.clear()
        if(elements[2] == 'main'):
            out.append("sub $16, %rsp")
            out.append("mov %rsp, %rbp")
            boolmain=1
        out.append("push %rbp")
        out.append("mov %rsp, %rbp")
        continue
        

    if(elements[0] == 'end'):
        if(boolmain!=1):

            
            out.append("leave")
            out.append("ret")
        
        continue

    if(elements[0] == 'return'):
        out.append("mov "+str(retaddr(elements[1]))+"(%rbp), %rax")
        out.append("leave")
        out.append("ret")
        continue

    if(elements[0] == 'push'):
        if(boolenter==0):
            boolenter=1

            out.append("mov %rbp, %rsp")
            out.append("sub $" + str(-offset+8) + ", %rsp")
                        
        out.append("push "+str(retaddr(elements[2]))+ "(%rbp)")
        continue

    if(elements[0] == 'pop'):
        var2offset[elements[2]] = retoffset
        retoffset = retoffset + 8

    if ('call,' in elements):
        if(boolenter==0):
            boolenter=1

            out.append("mov %rbp, %rsp")
            out.append("sub $" + str(-offset+8) + ", %rsp")
            
        boolenter =0
        if(elements[2] == 'call,'):
            out.append("call " + elements[3])
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
        else :
            out.append("call " + elements[1])
            # TODO cases where needed 
       

    if (elements[0]== 'print'):
        out.append("mov %rbp, %rsp")
        out.append("sub $" + str(-offset+8) + ", %rsp")

        out.append("mov "+str(retaddr(elements[1]))+"(%rbp), %rax")

        out.append("""mov $format, %rdi\nmov %rax, %rsi\nxor     %rax, %rax\ncall printf   """)

    if(elements[0]== 'if'):
        if (len(elements)==6):
            if(elements[2]=='=='):
                out.append("mov "+str(retaddr(elements[1]))+"(%rbp), %rax")
                out.append("cmp "+str(retaddr(elements[3]))+"(%rbp), %rax")
                out.append("je L"+elements[5])

            if(elements[2]=='!='):
                out.append("mov "+str(retaddr(elements[1]))+"(%rbp), %rax")
                out.append("cmp "+str(retaddr(elements[3]))+"(%rbp), %rax")
                out.append("jne L"+elements[5])

                
        if (len(elements)==4):

            out.append("mov "+str(retaddr(elements[1]))+"(%rbp), %rax")
            out.append("cmp $0, %rax")
            out.append("jne L"+elements[3])


            
        
    if  (elements[0]== 'goto'):
        if(len(elements)!=2):
            continue
        else :
            out.append("jmp L"+elements[1])

    if (elements[1]== '='):

        # constant assignment
        # print(elements)
        if (elements[2][0].isdigit()):

            out.append("mov $"+elements[2]+", %rax")
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

        # variable assignment
        elif (len(elements)==3):
            out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
        

        # unary assignment

        elif (len(elements)==4):
            if (elements[2]== '-'):
                out.append("mov "+str(retaddr(elements[3])) + "(%rbp), %rax")
                out.append("neg %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

            if (elements[2] == '!'):
                out.append("mov "+str(retaddr(elements[3])) + "(%rbp), %rax")
                out.append("cmp $0, %rax")
                out.append("sete %al")
                out.append("movzb %al, %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
            
            if (elements[2]== '~'):
                out.append("mov "+str(retaddr(elements[3])) + "(%rbp), %rax")
                out.append("not %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
            

        # arithmetic assignment
        elif (len(elements)==5):

            # addition
                if (elements[3][0]== '+'):
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("add "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

                # subtraction

                if (elements[3][0]== '-'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("sub "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3][0]== '*'):
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("imul "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

                
                if(elements[3] == '<<'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %cl")
                    out.append("sal %cl, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3]== '>>'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %cl")
                    out.append("sar %cl, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

                if (elements[3]== '>>>'):
                
                    # unsigned right shift
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %cl")
                    out.append("shr %cl, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                    

                if (elements[3][0] == '%'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %rbx")
                    # out.append("mov $0, %rdx")
                    out.append ("cqo")
                    out.append("idiv %rbx")
                    out.append("mov %rdx, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3][0]== '/'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %rbx")
                    out.append ("cqo")
                    out.append("idiv %rbx")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

                # TODO >>>

                if (elements[3] == '|'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("or "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

                if (elements[3] == '&'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("and "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '^'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("xor "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '=='):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("sete %al")
                    out.append("movzb %al, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

                if (elements[3] == '!='):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '<'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("setl %al")
                    out.append("movzb %al, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '>'):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("setg %al")
                    out.append("movzb %al, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '<='):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("setle %al")
                    out.append("movzb %al, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '>='):
                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("setge %al")
                    out.append("movzb %al, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '&&'):


                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rbx")
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rax")
                    out.append("and %rbx, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                
                if (elements[3] == '||'):

                    out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rbx")
                    out.append("mov "+str(retaddr(elements[4])) + "(%rbp), %rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rax")
                    out.append("or %rbx, %rax")
                    out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
                

                





    elif (elements[1]== '*='):
        out.append("mov "+str(retaddr(elements[0])) + "(%rbp), %rax")
        out.append("imul "+str(retaddr(elements[2])) + "(%rbp), %rax")
        out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
    
    elif (elements[1]== '/='):

        out.append("mov "+str(retaddr(elements[0])) + "(%rbp), %rax")
        out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rbx")
        out.append ("cqo")
        out.append("idiv %rbx")
        out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

    elif (elements[1]== '%='):

        out.append("mov "+str(retaddr(elements[0])) + "(%rbp), %rax")
        out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rbx")
        out.append ("cqo")
        out.append("idiv %rbx")
        out.append("mov %rdx, "+str(retaddr(elements[0])) + "(%rbp)")

    elif (elements[1]== '+='):

        out.append("mov "+str(retaddr(elements[0])) + "(%rbp), %rax")
        out.append("add "+str(retaddr(elements[2])) + "(%rbp), %rax")
        out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
    
    elif (elements[1]== '-='):

        out.append("mov "+str(retaddr(elements[0])) + "(%rbp), %rax")
        out.append("sub "+str(retaddr(elements[2])) + "(%rbp), %rax")
        out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
    





            
            


out.append("""

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
format:
        .ascii  "%lld\\n"

""")
            



for i in out:
    print(i)

