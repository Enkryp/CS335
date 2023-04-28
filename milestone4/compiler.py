import os


os.system("python3 run.py")

print("All test cases parsed, check above if any errors were found")

print ()

for i in range(1, 13):
    print("Test case " + str(i) + ":")


    os.system("cp ./outputs/" + str(i) + "_3ac.txt ./outputs/proc.txt")
    os.system("python3 to86.py > ./outputs/asm"+ str(i)+ ".s")
    print("Assembly code generated")


    os.system("gcc ./outputs/asm"+ str(i)+ ".s -o ./outputs/asm"+ str(i)+ ".out")
    print("Assembly code compiled\n\nOutput:")

    os.system("./outputs/asm"+ str(i)+ ".out")
    print()
    