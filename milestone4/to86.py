data =None
with open ("./outputs/10_3ac.txt", "r") as myfile:
    data=myfile.readlines()

sample = """

0 begin func main
1 t1 = 1000
2 n = t1
3 stackpointer + 4
4 t2 = 1
5 t3 = n +int t2
6 t4 = t3 * 4
7 sums = array ( t4 )
8 stackpointer + 0
9 t5 = 0
10 t6 = 0
11 t7 = 0
12 t8 = t6 +int t7
13 sums[ t5 ] = t8
14 t9 = 0
15 t10 = 0
16 sums[ t9 ] = sums[sums[t10]]
17 t11 = 1
18 i = t11
19 stackpointer + 4
20 t12 = i <= n
21 if t12 goto  23
22 goto  33
23 t14 = 1
24 t15 = i -int t14
25 t16 = i *int i
26 t17 = t16 *int i
27 t18 = sums[t15] +int t17
28 sums[ i ] = t18
29 stackpointer - 0
30 t13 = 1
31 i += t13
32 goto 20
33 stackpointer - 4
34 print sums[n]
35 stackpointer - 4
36 pop param, args
37 end func
38 stackpointer - 0



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


def callnew ():
    global out
    out.append("mov %rbp, %rsp")
    out.append("sub $" + str(-offset+8) + ", %rsp")
               


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

            callnew()         
        out.append("push "+str(retaddr(elements[2]))+ "(%rbp)")
        continue

    if(elements[0] == 'pop'):
        var2offset[elements[2]] = retoffset
        retoffset = retoffset + 8

    if ('call,' in elements):
        if(boolenter==0):
            boolenter=1
            callnew()
        boolenter =0
        if(elements[2] == 'call,'):
            out.append("call " + elements[3])
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
        else :
            out.append("call " + elements[1])
            # TODO cases where needed 
       

    if (elements[0]== 'print'):
        callnew()
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
    
    if(elements[1]== '['):
        
        out.append("mov "+str(retaddr(elements[0]))+"(%rbp), %rax")
        out.append("mov "+str(retaddr(elements[2]))+"(%rbp), %rbx")
        out.append("add %rbx, %rax")
        out.append("mov "+ str(retaddr(elements[5]))+"(%rbp), %rbx")

        out.append("mov %rbx, (%rax)")

    if (elements[1]== '='):
        if (elements[2]== 'array'):
            callnew()
            out.append("mov "+str(retaddr(elements[4]))+"(%rbp), %rdi")
            out.append("call malloc")
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
            continue




        # constant assignment
        # print(elements)
        elif (elements[2][0].isdigit()):

            out.append("mov $"+elements[2]+", %rax")
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")

        # variable assignment
        elif (len(elements)==3):
            out.append("mov "+str(retaddr(elements[2])) + "(%rbp), %rax")
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rbp)")
        

        #array element to be  assigned
        elif (len(elements)==6):
            out.append("mov "+str(retaddr(elements[2]))+"(%rbp), %rax")
            out.append("mov "+str(retaddr(elements[4]))+"(%rbp), %rbx")
            out.append("add %rbx, %rax")
            out.append("mov (%rax), %rbx")

            out.append("mov %rbx, " + str(retaddr(elements[0])) + "(%rbp)")

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

