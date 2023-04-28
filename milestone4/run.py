import os 

os.system("cd src && make")
print("Outputs will be directed to files")
for i in range(1, 13):
    print("cd src && ./a.out --input ../tests/test_" +str(i)+".java --output ../outputs/"+str(i))
    os.system("cd src && ./a.out --input ../tests/test_" +str(i)+".java --output ../outputs/"+str(i))
