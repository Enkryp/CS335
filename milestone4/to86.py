data =None
with open ("./outputs/10_3ac.txt", "r") as myfile:
    data=myfile.readlines()

sample = """0 begin func main
1 t1 = 20
2 n = t1
3 stackpointer + 4
4 t2 = 10
5 x = t2
6 stackpointer + 4
7 t3 = n +int x
8 g = t3
9 stackpointer + 4
10 stackpointer - 12
11 pop param, args
12 end func
13 stackpointer - 0


"""


offset = 0

var2offset = {}

def retaddr (a):
    if(a in var2offset.keys()):
        return var2offset[a]
    
    global offset

    offset = offset + 8
    var2offset[a] = offset
    return offset


out =[]
out.append("""
        .global main

        .text
main:
   """)


for line in data:
    line = line.strip()
    elements = line.split()
    for i in range(len(elements)):
        elements[i] = elements[i].strip()
    elements= elements[1:]
    # print(elements)

    if (elements[0]== 'print'):

        out.append("mov "+str(retaddr(elements[1]))+"(%rsp), %rax")

        out.append("""mov $format, %rdi\nmov %rax, %rsi\nxor     %rax, %rax\ncall printf   """)

    if (elements[1]== '='):

        # constant assignment
        if (elements[2][0].isdigit()):

            out.append("mov $"+elements[2]+", %rax")
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")

        # variable assignment
        elif (len(elements)==3):
            out.append("mov "+str(retaddr(elements[2])) + "(%rsp), %rax")
            out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")
        

        # unary assignment

        elif (len(elements)==4):
            if (elements[2]== '-'):
                out.append("mov "+str(retaddr(elements[3])) + "(%rsp), %rax")
                out.append("neg %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")

            if (elements[2] == '!'):
                out.append("mov "+str(retaddr(elements[3])) + "(%rsp), %rax")
                out.append("cmp $0, %rax")
                out.append("sete %al")
                out.append("movzbl %al, %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")
            
            if (elements[2]== '~'):
                out.append("mov "+str(retaddr(elements[3])) + "(%rsp), %rax")
                out.append("not %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")
            

        # arithmetic assignment
        elif (len(elements)==5):

            # addition
            if (elements[3]== '+int'):
                out.append("mov "+str(retaddr(elements[4])) + "(%rsp), %rax")
                out.append("add "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")

            # subtraction

            if (elements[3]== '-int'):
                out.append("mov "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("sub "+str(retaddr(elements[4])) + "(%rsp), %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")
            
            if (elements[3]== '*int'):
                out.append("mov "+str(retaddr(elements[4])) + "(%rsp), %rax")
                out.append("imul "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")

            
            if(elements[3] == '<<'):
                out.append("mov "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("mov "+str(retaddr(elements[4])) + "(%rsp), %cl")
                out.append("sal %cl, %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")
            
            if (elements[3]== '>>'):
                out.append("mov "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("mov "+str(retaddr(elements[4])) + "(%rsp), %cl")
                out.append("sar %cl, %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")

            if (elements[3]== '>>>'):
            
                # unsigned right shift
                out.append("mov "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("mov "+str(retaddr(elements[4])) + "(%rsp), %cl")
                out.append("shr %cl, %rax")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")
                

            if (elements[3] == '%int'):
                out.append("mov "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("mov "+str(retaddr(elements[4])) + "(%rsp), %rbx")
                # out.append("mov $0, %rdx")
                out.append ("cqo")
                out.append("idiv %rbx")
                out.append("mov %rdx, "+str(retaddr(elements[0])) + "(%rsp)")
            
            if (elements[3]== '/int'):
                out.append("mov "+str(retaddr(elements[2])) + "(%rsp), %rax")
                out.append("mov "+str(retaddr(elements[4])) + "(%rsp), %rbx")
                out.append ("cqo")
                out.append("idiv %rbx")
                out.append("mov %rax, "+str(retaddr(elements[0])) + "(%rsp)")
            


out.append("""

  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
format:
        .ascii  "%d\\n"

""")
            



for i in out:
    print(i)

