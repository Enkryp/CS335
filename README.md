# Java 17 Compiler



This is the repo for the Course Project of CS335. This includes a complete implementation of Java 17 Compiler  from scratch. The Compiler supports most of the features of Java 17. The compiler is written in C++ and uses flex and bison for lexical and syntax analysis. The compiler generates assembly code for the x86-64 architecture. The compiler is tested on Fedora 34. Please refer to milestone4/doc/doc.pdf for detailed documentation.

List of features supported by the compiler:
-  All primitive data types
-  Multidimensional arrays
-  All basic operators (arithmetic, increment, relational , bitwise
...)

-  Control flow statements including if-else, for, while.

-  Support for method calling.
-  Support for recursion.
-  Support for System.out.println() : Note this library is not supported, System.out.println() is provided for IO testing.  
-  Support for classes and objects.
-  Syntax and Semantic checks have been implemented in accordance with https://docs.oracle.com/javase/specs/jls/se17/html/index.html 
-  Support for static methods and variables.



## Installation and Execution

```cd milestone4/src```

```make```

```cd ..```

```./a.out - -input ./path/input.java - -output ./path/output``` - This generates output_3ac.txt

```cp ./path/output_3ac.txt ./outputs/proc.txt ``` 

```python3 ./to86.py > asm.s ``` - Generates assembly code in asm.s

```gcc asm.s -o asm.out``` - Compiles assembly code to generate executable

```./asm.out``` 

## Testing
I have provided an easy python script to automate the testing and bulk execution.

- Please change directory into ```./milestone4/```

-  Execute ```python3 compiler.py```
-  The tests are named ./tests/test [1-10].java, corresponding outputs in-
clude ./outputs/[1-10] symtable.csv, ./outputs/[1-10] 3ac.txt, ./outputs/asm[1-
10].s and ./outputs/asm[1-10].out, .out files indicate the final binaries.
 -  This script may be used by the tester for end-to-end evaluation as well. The number of test cases may be changed in line 10 of compiler.py and line 5 of run.py. Please ensure that tests are named correctly i.e. ./tests/test [1- 10].java.
