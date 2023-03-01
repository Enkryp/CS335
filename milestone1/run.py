import os 

os.system("cd src && make")

for i in range(1, 21):
    print("Erros for test case: ",i)
    os.system("./src/myASTGenerator --input ./tests/test"+ str(i)+".java --output ./outputs/out"+str(i)+".dot")
    os.system("	dot -Tpdf ./outputs/out"+str(i)+".dot > ./outputs/out"+str(i)+".pdf ")