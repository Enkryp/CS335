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

curclass = ""
curfunc = ""
class2size={}
class2offsetStatic={}
class2offsetNon={}
class2init = {}
class2func={}
var2class = {}

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


def move (a, b):
    # a is element 
    # b is register
    global out
    global curclass

    if (a.find('.') != -1):
        parts = a.split('.')
        classnow = var2class[parts[0]]
        if (parts[1] in class2offsetStatic[classnow].keys()):
            off2pointer = class2offsetStatic[classnow][parts[1]]
            classpt = var2offset["static@base" + classnow]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + str(off2pointer) + "(%r10), " + b)
            return

        elif (parts[1] in class2offsetNon[classnow].keys() and curfunc != "main"):
            off2pointer = class2offsetNon[classnow][parts[1]]
            classpt = var2offset["my@base"]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + str(off2pointer) + "(%r10), " + b)
            return
        
    else :
        if(a in var2offset.keys()):
            out.append("mov " + str(var2offset[a]) + "(%rbp), " + b)
            return
        elif (a in class2offsetStatic[curclass].keys()):
            off2pointer = class2offsetStatic[curclass][a]
            classpt = var2offset["static@base" + curclass]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + str(off2pointer) + "(%r10), " + b)
            return
        elif (a in class2offsetNon[curclass].keys() and curfunc != "main"):
            off2pointer = class2offsetStatic[curclass][a]
            classpt = var2offset["my@base"]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + str(off2pointer) + "(%r10), " + b)
            return
        else :
            out.append("mov " + str(retaddr(a)) + "(%rbp), " + b)
            return



def move2 (a, b):
    # a is register 
    # b is element
    global out
    global curclass

    if (b.find('.') != -1):
        
        parts = b.split('.')
        classnow = var2class[parts[0]]
        if (parts[1] in class2offsetStatic[classnow].keys()):
            off2pointer = class2offsetStatic[classnow][parts[1]]
            classpt = var2offset["static@base" + classnow]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + a + ", " + str(off2pointer) + "(%r10)")
            return
        
        elif (parts[1] in class2offsetNon[classnow].keys() and curfunc != "main"):
            off2pointer = class2offsetNon[classnow][parts[1]]
            classpt = var2offset["my@base"]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + a + ", " + str(off2pointer) + "(%r10)")
            return
    
    else :
        if(b in var2offset.keys()):
            out.append("mov " + a + ", " + str(var2offset[b]) + "(%rbp)")
            return
        elif (b in class2offsetStatic[curclass].keys()):
            off2pointer = class2offsetStatic[curclass][b]
            classpt = var2offset["static@base" + curclass]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + a + ", " + str(off2pointer) + "(%r10)")
            return
        elif (b in class2offsetNon[curclass].keys() and curfunc != "main"):
            off2pointer = class2offsetNon[curclass][b]
            classpt = var2offset["my@base"]
            out.append( "mov " + str(classpt) + "(%rbp), %r10")
            out.append("mov " + a + ", " + str(off2pointer) + "(%r10)")
            return
        else :
            out.append("mov " + a + ", " + str(retaddr(b)) + "(%rbp)")
            return


# initial parse
data1 = data.copy()
for line in data1:
    line = line.strip()
    while(line.find("  ")!=-1):
        line = line.replace("  ", " ")
    elements = line.split()
    if(len(elements)<=1):
        continue
    for i in range(len(elements)):
        elements[i] = elements[i].strip()
    # print(elements)
    elements= elements[1:]

    if(elements[0] == "begin" and elements[1] == "class"):
        curclass = elements[2]
        class2size[curclass] = 0
        class2offsetStatic[curclass] = {}
        class2offsetNon[curclass] = {}
        class2init[curclass] = {}
        class2func[curclass] = {}
        continue

    if(elements[0] == "fieldstatic"):

        class2offsetStatic[curclass][elements[1]] = class2size[curclass]
        class2size[curclass] = class2size[curclass] + 8
        if(len(elements) >= 4 and elements[2] == "="):
            class2init[curclass][elements[1]] = elements[3:]
        continue

    if(elements[0] == "fieldnon"):

        class2offsetNon[curclass][elements[1]] = class2size[curclass]
        class2size[curclass] = class2size[curclass] + 8
        if(len(elements) >= 4 and elements[2] == "="):
            class2init[curclass][elements[1]] = elements[3:]
        continue

    


    if(elements[0] == 'begin' and elements[1] == 'func'):
        class2func[curclass][elements[2]] = 1
        
      
#second parse


popstart =False

out =[]
out.append("""
        .global main

        .text

   """)


def callnew (a =0):
    global out
    out.append("mov %rbp, %rsp")
    out.append("sub $" + str(-offset+8) + ", %rsp")
    classlist = list(class2size.keys())
    for i in classlist:
        # push var2offset["static@base" + i] to stack 
        out.append("push " + str(var2offset["static@base" + i]) + "(%rbp)")
    # if(a==0):
    #     out.append("push %rax")
               


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

    if(elements[0] == "begin" and elements[1] == "class"):
        curclass = elements[2]
        # class2size[curclass] = 0
        # class2offsetStatic[curclass] = {}
        # class2offsetNon[curclass] = {}
        # class2init[curclass] = {}
        # class2func[curclass] = {}
        continue

    if(elements[0] == "fieldstatic"):

        # class2offsetStatic[curclass][elements[1]] = class2size[curclass]
        # class2size[curclass] = class2size[curclass] + 8
        # if(len(elements) >= 4 and elements[2] == "="):
        #     class2init[curclass][elements[1]] = elements[3:]
        continue

    if(elements[0] == "fieldnon"):

        # class2offsetNon[curclass][elements[1]] = class2size[curclass]
        # class2size[curclass] = class2size[curclass] + 8
        # if(len(elements) >= 4 and elements[2] == "="):
        #     class2init[curclass][elements[1]] = elements[3:]
        continue

    


    if(elements[0] == 'begin' and elements[1] == 'func'):
        # class2func[curclass][elements[2]] = 1
        var2class={}
        popstart =False
        curfunc = elements[2]
        boolmain=0
        boolenter=0
        out.append(elements[2] + ":")
        offset=-8
        retoffset=16
        var2offset.clear()
        if(elements[2] == 'main'):


            out.append("sub $16, %rsp")
            out.append("mov %rsp, %rbp")

            for i in class2size.keys():
                # use malloc 
                out.append("mov $"+ str(class2size[i]) + ", %rdi")
                out.append("call malloc")
                out.append("mov %rax, %r10")
                out.append("mov %r10, " + str(retaddr("static@base" + i)) + "(%rbp)")
            boolmain=1
        out.append("push %rbp")
        out.append("mov %rsp, %rbp")
        continue
        

    if(elements[0] == 'end' and elements[1] == 'func'):
        boolmain =0
        if(curfunc == 'main'):
            out.append("""
  
        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit""")
            
        if(boolmain!=1):

            
            out.append("leave")
            out.append("ret")
        
        continue

    if(elements[0] == 'return'):
        move (elements[1], "%rax")
        out.append("leave")
        out.append("ret")
        continue

    if(elements[0] == 'push'):
        if(boolenter==0):
            boolenter=1

            callnew()
        move(elements[2], "%rax")         
        out.append("push %rax")
        continue

    if(elements[0] == 'pop'):
        popstart = True
        var2offset[elements[2]] = retoffset
        retoffset = retoffset + 8
        continue
    
    if(popstart):
        popstart = False
        if(curfunc != 'main'):
            classlist = list(class2size.keys())
            classlist.reverse()

            var2offset["my@base"] = retoffset
            retoffset = retoffset + 8

            for i in classlist:
                var2offset["static@base" + i] = retoffset
                retoffset = retoffset + 8




    if ('call,' in elements):
        if(boolenter==0):
            boolenter=1
            callnew()
        boolenter =0
        if(elements[2] == 'call,'):

            if (elements[3].find('.')!=-1):
                # TODO
                parts = elements[3].split('.')
                out.append("push " + str(var2offset[parts[0]]) + "(%rbp)")
                out.append("call " + var2class[parts[0]] + "!" + parts[1])
                move2("%rax", elements[0])

            else :
                out.append("push %rax")
                    
                out.append("call " + elements[3])
                move2("%rax", elements[0])
        else :
            out.append("call " + elements[1])
            # TODO cases where needed 
       

    if (elements[0]== 'print'):
        callnew()
        move(elements[1], "%rax")
        out.append("""mov $format, %rdi\nmov %rax, %rsi\nxor     %rax, %rax\ncall printf   """)

    if(elements[0]== 'if'):
        if (len(elements)==6):
            if(elements[2]=='=='):
                move (elements[1], "%rax")
                move (elements[3], "%rbx")
                out.append("cmp %rbx, %rax")
                out.append("je L"+elements[5])

            if(elements[2]=='!='):
                move (elements[1], "%rax")
                move (elements[3], "%rbx")
                out.append("cmp %rbx, %rax")
                out.append("jne L"+elements[5])

                
        if (len(elements)==4):
            move (elements[1], "%rax")
            out.append("cmp $0, %rax")
            out.append("jne L"+elements[3])


            
        
    if  (elements[0]== 'goto'):
        if(len(elements)!=2):
            continue
        else :
            out.append("jmp L"+elements[1])
    
    if(elements[1]== '['):
        move(elements[0], "%rax")
        move(elements[2], "%rbx")
        
        out.append("add %rbx, %rax")

        move (elements[5], "%rbx")

        out.append("mov %rbx, (%rax)")

    if (elements[1]== '='):
        if (elements[2]== 'class'):
            var2class[elements[0]] = elements[4]


            callnew()
            out.append("mov $"+ str(class2size[elements[4]]) + ", %rdi")
            out.append("call malloc")
            move2("%rax", elements[0])
            continue


        if (elements[2]== 'array'):
            callnew()
            move(elements[4], "%rdi")
            out.append("call malloc")
            move2("%rax", elements[0])
            continue




        # constant assignment
        # print(elements)
        elif (elements[2][0].isdigit()):

            out.append("mov $"+elements[2]+", %rax")
            move2("%rax", elements[0])

        # variable assignment
        elif (len(elements)==3):
            move (elements[2], "%rax")
            move2("%rax", elements[0])
        

        #array element to be  assigned
        elif (len(elements)==6):
            move(elements[2], "%rax")
            move(elements[4], "%rbx")
            out.append("add %rbx, %rax")
            out.append("mov (%rax), %rbx")

            move2("%rbx", elements[0])

        # unary assignment

        elif (len(elements)==4):
            if (elements[2]== '-'):
                move (elements[3], "%rax")

                move (elements[3], "%rax")
                out.append("neg %rax")
                move2("%rax", elements[0])
                move2("%rax", elements[0])

            if (elements[2] == '!'):
                move (elements[3], "%rax")
                out.append("cmp $0, %rax")
                out.append("sete %al")
                out.append("movzb %al, %rax")
                move2("%rax", elements[0])
            
            if (elements[2]== '~'):
                move (elements[3], "%rax")
                out.append("not %rax")
                move2("%rax", elements[0])
            

        # arithmetic assignment
        elif (len(elements)==5):

            # addition
                if (elements[3][0]== '+'):
                    move (elements[4], "%rax")
                    move (elements[2], "%rbx")
                    out.append("add %rbx, %rax")
                    move2("%rax", elements[0])

                # subtraction

                if (elements[3][0]== '-'):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    out.append("sub %rbx, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3][0]== '*'):
                    move (elements[4], "%rax")
                    move (elements[2], "%rbx")
                    out.append("imul %rbx, %rax")
                    move2("%rax", elements[0])

                
                if(elements[3] == '<<'):
                    move (elements[2], "%rax")
                    move (elements[4], "%cl")
                    out.append("sal %cl, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3]== '>>'):
                    move (elements[2], "%rax")
                    move (elements[4], "%cl")
                    out.append("sar %cl, %rax")
                    move2("%rax", elements[0])

                if (elements[3]== '>>>'):
                
                    # unsigned right shift
                    move (elements[2], "%rax")
                    move (elements[4], "%cl")
                    out.append("shr %cl, %rax")
                    move2("%rax", elements[0])
                    

                if (elements[3][0] == '%'):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    # out.append("mov $0, %rdx")
                    out.append ("cqo")
                    out.append("idiv %rbx")
                    move2("%rdx", elements[0])
                
                if (elements[3][0]== '/'):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    out.append ("cqo")
                    out.append("idiv %rbx")
                    move2("%rax", elements[0])

                # TODO >>>

                if (elements[3] == '|'):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    out.append("or %rbx, %rax")
                    move2("%rax", elements[0])

                if (elements[3] == '&'):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    out.append("and %rbx, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '^'):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    out.append("xor %rbx, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '=='):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    out.append("cmp %rbx, %rax")
                    out.append("sete %al")
                    out.append("movzb %al, %rax")
                    move2("%rax", elements[0])

                if (elements[3] == '!='):
                    move (elements[2], "%rax")
                    move (elements[4], "%rbx")
                    out.append("cmp %rbx, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '<'):
                    move (elements[2], "%rax")

                    move (elements[4], "%rbx")
                    out.append("cmp %rbx, %rax")
                    out.append("setl %al")
                    out.append("movzb %al, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '>'):
                    move (elements[2], "%rax")

                    move (elements[4], "%rbx")
                    out.append("cmp %rbx, %rax")
                    out.append("setg %al")
                    out.append("movzb %al, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '<='):
                    move (elements[2], "%rax")

                    move (elements[4], "%rbx")
                    out.append("cmp %rbx, %rax")
                    out.append("setle %al")
                    out.append("movzb %al, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '>='):
                    move (elements[2], "%rax")

                    move (elements[4], "%rbx")
                    out.append("cmp %rbx, %rax")
                    out.append("setge %al")
                    out.append("movzb %al, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '&&'):


                    move (elements[2], "%rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rbx")
                    move (elements[4], "%rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rax")
                    out.append("and %rbx, %rax")
                    move2("%rax", elements[0])
                
                if (elements[3] == '||'):

                    move (elements[2], "%rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rbx")
                    move (elements[4], "%rax")
                    out.append("cmp $0, %rax")
                    out.append("setne %al")
                    out.append("movzb %al, %rax")
                    out.append("or %rbx, %rax")
                    move2("%rax", elements[0])
                

                





    elif (elements[1]== '*='):
        move (elements[0], "%rax")
        move (elements[2], "%rbx")
        out.append("imul %rbx, %rax")
        move2("%rax", elements[0])
    
    elif (elements[1]== '/='):

        move (elements[0], "%rax")

        move (elements[2], "%rbx")
        out.append ("cqo")
        out.append("idiv %rbx")
        move2("%rax", elements[0])

    elif (elements[1]== '%='):

        move (elements[0], "%rax")
        move (elements[2], "%rbx")
        out.append ("cqo")
        out.append("idiv %rbx")
        move2("%rdx", elements[0])

    elif (elements[1]== '+='):

        move (elements[0], "%rax")

        move (elements[2], "%rbx")
        out.append("add %rbx, %rax")
        move2("%rax", elements[0])
    
    elif (elements[1]== '-='):

        move (elements[0], "%rax")

        move (elements[2], "%rbx")
        out.append("sub %rbx, %rax")
        move2("%rax", elements[0])
    





            
            


out.append("""

format:
        .ascii  "%lld\\n"

""")
            



for i in out:
    print(i)

