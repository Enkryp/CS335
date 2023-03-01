import os 

os.system("cd src && make")
print("Note empty line for error, indicates no error")
for i in range(1, 26):
    print("Errors for test case ",i, ":")
    print()
    os.system("./src/myASTGenerator --input ./tests/test"+ str(i)+".java --output ./outputs/out"+str(i)+".dot")
    os.system("	dot -Tpdf ./outputs/out"+str(i)+".dot > ./outputs/out"+str(i)+".pdf ")