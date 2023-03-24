import os 

os.system("cd src && make")
print("Outputs will be directed to files, terminal shows verbose")
for i in range(1, 11):
    print("./src/a.out < ./tests/test_" +str(i)+".java")
    os.system("./src/a.out < ./tests/test_" +str(i)+".java")
    os.system("mv ./3ac.txt ./outputs/3ac"+str(i)+".txt")
    os.system("mv ./symtable.csv ./outputs/symtable"+str(i)+".csv")
    