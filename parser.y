%{
    #include<bits/stdc++.h>
    using namespace std;   
    extern "C" int yylex();
    extern "C" FILE *yyin;
    extern "C" int yylineno; 
    void yyerror(char *s);
    char* numtochar( int num){
        string s="0";
        while(num>0){
            s.push_back(num%10+'0');
            num/=10;
        }
        reverse(s.begin(),s.end());
        int n=s.size();
        char* c= (char*)malloc(sizeof(char)*(n+1));
        for( int i=0;i<n;i++){  
            c[i]=s[i];
        }
        c[n]='\0';
        return c;
    }
    int chartonum(char * c){
        int i=0;
        int num=0;
        while(c[i]!='\0'){
            num*=10;
            num+=c[i]-'0';
            i++;
        }
        return num;
    } 
    string chartostring(char* c){
        string s;
        int i=0;
        while(c[i]!='\0'){
            s.push_back(c[i]);
            i++;
        }
        return s;
    }
    struct label{
        int num;
        string l;
    } ;
    struct edge{
        int a;
        int b;
        string l;
    };
    
    vector<label> labels;
    vector<edge> edges;
    char* addlabel(string c){  // takes argument as the label of the node in string form and output a char* which is a unique number to the node
        // string c=chartostring(c1);
        int n=labels.size()+1;
        label q;
        q.num=n*10;
        q.l=c;
        labels.push_back(q);
        return numtochar(n);
    }
    void addedge(char* a, char* b, string l=""){  // takes numbers of node in char* and label in string form
        edge q;
        q.a=chartonum(a);
        q.b=chartonum(b);
        q.l=l;
        edges.push_back(q);
        
    }
%}
%union{
    char* val;
}

/* data types */
%start COMPILATIONUNIT
%type<val>  ADDITIONALBOUND ADDITIVEEXPRESSION ANDEXPRESSION ARGUMENTLIST ARRAYACCESS ARRAYCREATIONEXPRESSION ARRAYINITIALIZER ARRAYINITIALIZER1 ASSERTSTATEMENT ASSIGNMENT ASSIGNMENTEXPRESSION ASSIGNMENTOPERATOR BASICFORSTATEMENT BASICFORSTATEMENTNOSHORTIF BLOCK BLOCKSTATEMENT BLOCKSTATEMENTS BREAKSTATEMENT CLASSBODY CLASSBODYDECLARATION CLASSBODYDECLARATIONS CLASSDECLARATION CLASSEXTENDS CLASSIMPLEMENTS CLASSINSTANCECREATIONEXPRESSION CLASSLITERAL CLASSMEMBERDECLARATION CLASSORINTERFACETYPE CLASSORINTERFACETYPETOINSTANTIATE CLASSPERMITS CLASSTYPE CLASSTYPE1 COMPILATIONUNIT CONDITIONALANDEXPRESSION CONDITIONALEXPRESSION CONDITIONALOREXPRESSION CONSTRUCTORBODY CONSTRUCTORDECLARATION CONSTRUCTORDECLARATOR CONTINUESTATEMENT DIMEXPR DIMEXPRS DIMS EMPTYSTATEMENT ENHANCEDFORSTATEMENT ENHANCEDFORSTATEMENTNOSHORTIF EQUALITYEXPRESSION EXCEPTIONTYPE EXCEPTIONTYPELIST EXCLUSIVEOREXPRESSION EXPLICITCONSTRUCTORINVOCATION EXPRESSION EXPRESSIONNAME EXPRESSIONSTATEMENT FIELDACCESS FIELDDECLARATION FIELDMODIFIERS FLOATINGTYPE FORINIT FORMALPARAMETER FORMALPARAMETERLIST FORSTATEMENT FORSTATEMENTNOSHORTIF FORUPDATE IFTHENELSESTATEMENT IFTHENELSESTATEMENTNOSHORTIF IFTHENSTATEMENT INCLUSIVEOREXPRESSION INSTANCEINITIALIZER INSTANCEOFEXPRESSION INTEGRALTYPE INTERFACETYPE INTERFACETYPELIST LABELEDSTATEMENT LABELEDSTATEMENTNOSHORTIF LEFTHANDSIDE LITERAL LOCALCLASSORINTERFACEDECLARATION LOCALVARIABLEDECLARATION LOCALVARIABLEDECLARATIONSTATEMENT LOCALVARIABLETYPE METHODBODY METHODDECLARATION METHODDECLARATOR METHODHEADER METHODINVOCATION METHODMODIFIERS METHODNAME METHODREFERENCE MULTIPLICATIVEEXPRESSION NORMALCLASSDECLARATION NUMERICTYPE ORDINARYCOMPILATIONUNIT POSTDECREMENTEXPRESSION POSTFIXEXPRESSION POSTINCREMENTEXPRESSION PREDECREMENTEXPRESSION PREINCREMENTEXPRESSION PRIMARY PRIMARYNONEWARRAY PRIMITIVETYPE RECEIVERPARAMETER REFERENCETYPE RELATIONALEXPRESSION RETURNSTATEMENT SHIFTEXPRESSION SIMPLETYPENAME SQUARESTAR STATEMENT STATEMENTEXPRESSION STATEMENTEXPRESSIONLIST STATEMENTNOSHORTIF STATEMENTWITHOUTTRAILINGSUBSTATEMENT STATICINITIALIZER SUPER1 SUPER2 SUPER3 THROWS2 THROWSTATEMENT TOPLEVELCLASSORINTERFACEDECLARATION TYPE TYPEARGUMENT TYPEARGUMENTLIST TYPEARGUMENTS TYPEBOUND TYPENAMES TYPEPARAMETER TYPEPARAMETERLIST TYPEPARAMETERS UNARYEXPRESSION UNARYEXPRESSIONNOTPLUSMINUS UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION VARIABLEARITYPARAMETER VARIABLEDECLARATOR VARIABLEDECLARATORID VARIABLEDECLARATORLIST VARIABLEINITIALIZER VARIABLEINITIALIZERLIST WHILESTATEMENT WHILESTATEMENTNOSHORTIF WILDCARD WILDCARDBOUNDS YIELDSTATEMENT IMPORTDECLARATION
%token<val> BOOLEAN BYTE SHORT INT LONG CHAR FLOAT DOUBLE 

/* Separators */
%token<val> COMMA QUESTIONMARK SEMICOLON  OPENCURLY CLOSECURLY ANGULARLEFT ANGULARRIGHT OPENSQUARE CLOSESQUARE OPENPARAN CLOSEPARAN DOUBLECOLON TRIPLEDOT WS AT OVERRIDE

/* Operators  AND -> & COMPLEMENT -> ~ */
%token<val> EQUALS MULTIPLYEQUALS DIVIDEEQUALS MODEQUALS PLUSEQUALS MINUSEQUALS PLUS MINUS DIVIDE MULTIPLY MOD OR XOR COLON NOT COMPLEMENT AND DOT OROR ANDAND PLUSPLUS MINUSMINUS ANGULARLEFTANGULARLEFT ANGULARRIGHTANGULARRIGHT ANGULARRIGHTANGULARRIGHTANGULARRIGHT
EQUALSEQUALS NOTEQUALS
/* Literals */
%token<val> INTEGERLITERAL FLOATINGPOINTLITERAL BOOLEANLITERAL CHARACTERLITERAL STRINGLITERAL TEXTBLOCK NULLLITERAL

/* Keywords */
%token<val> EXTENDS SUPER CLASS PUBLIC PRIVATE IMPLEMENTS PERMITS PROTECTED STATIC FINAL TRANSIENT VOLATILE INSTANCEOF THIS VOID NEW THROW ASSERT VAR BREAK CONTINUE RETURN YIELD IF ELSE WHILE FOR ABSTRACT SYNCHRONIZED NATIVE STRICTFP

/*  Unused keywords  See throw, throws and throwss check non_sealed*/
%token<val> SWITCH DEFAULT PACKAGE DO GOTO IMPORT THROWS CASE ENUM CATCH TRY INTERFACE FINALLY CONST UNDERSCORE EXPORTS OPENS REQUIRES USES MODULE SEALED PROVIDES TO WITH OPEN RECORD TRANSITIVE ERROR ONCE NL NON_SEALED


%token<val> IDENTIFIER UNQUALIFIEDMETHODIDENTIFIER  DOTCLASS
%token<val> EOFF


/* %type<val> CHAPTERTITLE SECTIONTITLE  */

%%


COMPILATIONUNIT : EOFF   {$$=addlabel("COMPILATIONUNIT");$1=addlabel(string("eoff") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);return 0;}
 | ORDINARYCOMPILATIONUNIT EOFF   {$$=addlabel("COMPILATIONUNIT");addedge($$, $1);return 0;}
TYPE : PRIMITIVETYPE  {$$= $1;}
 | REFERENCETYPE   {$$= $1;}
PRIMITIVETYPE : NUMERICTYPE  {$$= $1;}
 | BOOLEAN   {$$=addlabel("PRIMITIVETYPE");$1=addlabel(string("boolean") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
NUMERICTYPE : INTEGRALTYPE  {$$= $1;}
 | FLOATINGTYPE   {$$= $1;}
INTEGRALTYPE : BYTE  {$$=addlabel("INTEGRALTYPE");$1=addlabel(string("byte") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | SHORT   {$$=addlabel("INTEGRALTYPE");$1=addlabel(string("short") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | INT   {$$=addlabel("INTEGRALTYPE");$1=addlabel(string("int") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | LONG   {$$=addlabel("INTEGRALTYPE");$1=addlabel(string("long") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | CHAR   {$$=addlabel("INTEGRALTYPE");$1=addlabel(string("char") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
FLOATINGTYPE : FLOAT  {$$=addlabel("FLOATINGTYPE");$1=addlabel(string("float") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | DOUBLE   {$$=addlabel("FLOATINGTYPE");$1=addlabel(string("double") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
REFERENCETYPE : CLASSORINTERFACETYPE  {$$= $1;}
CLASSORINTERFACETYPE : CLASSTYPE   {$$= $1;}
CLASSTYPE : CLASSTYPE1  {$$= $1;}
CLASSTYPE1 : IDENTIFIER  {$$=addlabel("CLASSTYPE1");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
TYPEARGUMENTS : ANGULARLEFT TYPEARGUMENTLIST ANGULARRIGHT  {$$=addlabel("TYPEARGUMENTS");addedge($$, $2);}
TYPEARGUMENTLIST : TYPEARGUMENT  {$$= $1;}
 | TYPEARGUMENTLIST COMMA TYPEARGUMENT  {$$=addlabel("TYPEARGUMENTLIST");addedge($$, $1);addedge($$, $3);}
TYPEARGUMENT : REFERENCETYPE  {$$= $1;}
 | WILDCARD   {$$= $1;}
WILDCARD : QUESTIONMARK   {$$=addlabel("WILDCARD");$1=addlabel(string("questionmark") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | QUESTIONMARK WILDCARDBOUNDS  {$$=addlabel("WILDCARD");addedge($$, $2);}
WILDCARDBOUNDS : EXTENDS REFERENCETYPE  {$$=addlabel("WILDCARDBOUNDS");addedge($$, $2);}
 | SUPER REFERENCETYPE   {$$=addlabel("WILDCARDBOUNDS");addedge($$, $2);}
INTERFACETYPE : CLASSTYPE  {$$= $1;}
DIMS : OPENSQUARE CLOSESQUARE   {$$=addlabel("DIMS");}
 | DIMS OPENSQUARE CLOSESQUARE  {$$=addlabel("DIMS");addedge($$, $1);}
METHODNAME : IDENTIFIER   {$$=addlabel("METHODNAME");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
EXPRESSIONNAME : IDENTIFIER DOT IDENTIFIER  {$$=addlabel("EXPRESSIONNAME");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 | EXPRESSIONNAME DOT IDENTIFIER  {$$=addlabel("EXPRESSIONNAME");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
ORDINARYCOMPILATIONUNIT : TOPLEVELCLASSORINTERFACEDECLARATION   {$$= $1;}
 | ORDINARYCOMPILATIONUNIT TOPLEVELCLASSORINTERFACEDECLARATION  {$$=addlabel("ORDINARYCOMPILATIONUNIT");addedge($$, $1);addedge($$, $2);}
TOPLEVELCLASSORINTERFACEDECLARATION : CLASSDECLARATION  {$$= $1;}
 | SEMICOLON   {$$=addlabel("TOPLEVELCLASSORINTERFACEDECLARATION");$1=addlabel(string("semicolon") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | IMPORTDECLARATION TOPLEVELCLASSORINTERFACEDECLARATION  {$$=addlabel("TOPLEVELCLASSORINTERFACEDECLARATION");addedge($$, $1);addedge($$, $2);}
IMPORTDECLARATION : IMPORT EXPRESSIONNAME SEMICOLON  {$$=addlabel("IMPORTDECLARATION");addedge($$, $2);}
 | IMPORT EXPRESSIONNAME DOT MULTIPLY SEMICOLON  {$$=addlabel("IMPORTDECLARATION");addedge($$, $2);$3=addlabel(string("dot") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);$4=addlabel(string("multiply") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 | IMPORT STATIC EXPRESSIONNAME SEMICOLON  {$$=addlabel("IMPORTDECLARATION");addedge($$, $3);}
 | IMPORT STATIC EXPRESSIONNAME DOT MULTIPLY SEMICOLON  {$$=addlabel("IMPORTDECLARATION");addedge($$, $3);$4=addlabel(string("dot") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);$5=addlabel(string("multiply") +  string("(") +  chartostring($5)+string(")"));addedge($$, $5);}
CLASSDECLARATION : NORMALCLASSDECLARATION  {$$= $1;}
NORMALCLASSDECLARATION : CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | CLASS IDENTIFIER CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | CLASS IDENTIFIER CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | CLASS IDENTIFIER CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);addedge($$, $8);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER1 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER1 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER1 CLASS IDENTIFIER CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER1 CLASS IDENTIFIER CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);addedge($$, $8);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER2 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER2 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER2 CLASS IDENTIFIER CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER2 CLASS IDENTIFIER CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);addedge($$, $8);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);addedge($$, $7);}
 | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER3 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);addedge($$, $6);}
 | SUPER3 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER3 CLASS IDENTIFIER CLASSPERMITS CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | SUPER3 CLASS IDENTIFIER CLASSBODY  {$$=addlabel("NORMALCLASSDECLARATION");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);}
TYPEPARAMETERS : ANGULARLEFT TYPEPARAMETERLIST ANGULARRIGHT  {$$=addlabel("TYPEPARAMETERS");addedge($$, $2);}
TYPEPARAMETERLIST : TYPEPARAMETER  {$$= $1;}
 | TYPEPARAMETERLIST COMMA TYPEPARAMETER  {$$=addlabel("TYPEPARAMETERLIST");addedge($$, $1);addedge($$, $3);}
TYPEPARAMETER : IDENTIFIER TYPEBOUND  {$$=addlabel("TYPEPARAMETER");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
 | IDENTIFIER   {$$=addlabel("TYPEPARAMETER");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
TYPEBOUND : EXTENDS IDENTIFIER  {$$=addlabel("TYPEBOUND");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 | EXTENDS CLASSORINTERFACETYPE ADDITIONALBOUND  {$$=addlabel("TYPEBOUND");addedge($$, $2);addedge($$, $3);}
ADDITIONALBOUND : AND INTERFACETYPE  {$$=addlabel("ADDITIONALBOUND");$1=addlabel(string("and") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
 | ADDITIONALBOUND AND INTERFACETYPE  {$$=addlabel("ADDITIONALBOUND");addedge($$, $1);$2=addlabel(string("and") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
CLASSEXTENDS : EXTENDS CLASSTYPE  {$$=addlabel("CLASSEXTENDS");addedge($$, $2);}
CLASSIMPLEMENTS : IMPLEMENTS INTERFACETYPELIST  {$$=addlabel("CLASSIMPLEMENTS");addedge($$, $2);}
INTERFACETYPELIST : INTERFACETYPE  {$$= $1;}
 | INTERFACETYPELIST COMMA INTERFACETYPE  {$$=addlabel("INTERFACETYPELIST");addedge($$, $1);addedge($$, $3);}
CLASSPERMITS : PERMITS TYPENAMES  {$$=addlabel("CLASSPERMITS");addedge($$, $2);}
TYPENAMES : IDENTIFIER  {$$=addlabel("TYPENAMES");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | TYPENAMES COMMA IDENTIFIER  {$$=addlabel("TYPENAMES");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
CLASSBODY : OPENCURLY CLOSECURLY   {$$=addlabel("CLASSBODY");}
 | OPENCURLY CLASSBODYDECLARATIONS CLOSECURLY  {$$=addlabel("CLASSBODY");addedge($$, $2);}
CLASSBODYDECLARATIONS : CLASSBODYDECLARATION  {$$= $1;}
 | CLASSBODYDECLARATIONS CLASSBODYDECLARATION  {$$=addlabel("CLASSBODYDECLARATIONS");addedge($$, $1);addedge($$, $2);}
CLASSBODYDECLARATION : CLASSMEMBERDECLARATION  {$$= $1;}
 | INSTANCEINITIALIZER  {$$= $1;}
 | STATICINITIALIZER  {$$= $1;}
 | CONSTRUCTORDECLARATION   {$$= $1;}
CLASSMEMBERDECLARATION: FIELDDECLARATION  {$$= $1;}
 | METHODDECLARATION  {$$= $1;}
 | CLASSDECLARATION  {$$= $1;}
 | SEMICOLON  {$$=addlabel("CLASSMEMBERDECLARATION");$1=addlabel(string("semicolon") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
FIELDDECLARATION : FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON  {$$=addlabel("FIELDDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON  {$$=addlabel("FIELDDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON  {$$=addlabel("FIELDDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | TYPE VARIABLEDECLARATORLIST SEMICOLON   {$$=addlabel("FIELDDECLARATION");addedge($$, $1);addedge($$, $2);}
VARIABLEDECLARATORLIST : VARIABLEDECLARATOR  {$$= $1;}
 | VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR   {$$=addlabel("VARIABLEDECLARATORLIST");addedge($$, $1);addedge($$, $3);}
VARIABLEDECLARATOR : VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER  {$$=addlabel("VARIABLEDECLARATOR");addedge($$, $1);$2=addlabel(string("equals") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 | VARIABLEDECLARATORID  {$$= $1;}
VARIABLEDECLARATORID : IDENTIFIER   {$$=addlabel("VARIABLEDECLARATORID");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | IDENTIFIER DIMS  {$$=addlabel("VARIABLEDECLARATORID");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
VARIABLEINITIALIZER : EXPRESSION  {$$= $1;}
 | ARRAYINITIALIZER  {$$= $1;}
EXPRESSION : ASSIGNMENTEXPRESSION  {$$= $1;}
ASSIGNMENTEXPRESSION : CONDITIONALEXPRESSION  {$$= $1;}
 | ASSIGNMENT  {$$= $1;}
ASSIGNMENT : LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  {$$=addlabel("ASSIGNMENT");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
LEFTHANDSIDE : EXPRESSIONNAME  {$$= $1;}
 | IDENTIFIER  {$$=addlabel("LEFTHANDSIDE");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | FIELDACCESS  {$$= $1;}
 | ARRAYACCESS  {$$= $1;}
ASSIGNMENTOPERATOR : EQUALS  {$$=addlabel("ASSIGNMENTOPERATOR");$1=addlabel(string("equals") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | MULTIPLYEQUALS  {$$=addlabel("ASSIGNMENTOPERATOR");$1=addlabel(string("multiplyequals") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | DIVIDEEQUALS  {$$=addlabel("ASSIGNMENTOPERATOR");$1=addlabel(string("divideequals") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | MODEQUALS  {$$=addlabel("ASSIGNMENTOPERATOR");$1=addlabel(string("modequals") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | PLUSEQUALS  {$$=addlabel("ASSIGNMENTOPERATOR");$1=addlabel(string("plusequals") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | MINUSEQUALS  {$$=addlabel("ASSIGNMENTOPERATOR");$1=addlabel(string("minusequals") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
FIELDACCESS: PRIMARY DOT IDENTIFIER  {$$=addlabel("FIELDACCESS");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	SUPER DOT IDENTIFIER  {$$=addlabel("FIELDACCESS");$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	IDENTIFIER DOT SUPER DOT IDENTIFIER  {$$=addlabel("FIELDACCESS");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$4=addlabel(string("dot") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);$5=addlabel(string("identifier") +  string("(") +  chartostring($5)+string(")"));addedge($$, $5);}
PRIMARY: PRIMARYNONEWARRAY  {$$= $1;}
 |	ARRAYCREATIONEXPRESSION  {$$= $1;}
PRIMARYNONEWARRAY: LITERAL  {$$= $1;}
 |	CLASSLITERAL  {$$= $1;}
 |	THIS  {$$=addlabel("PRIMARYNONEWARRAY");$1=addlabel(string("this") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	IDENTIFIER DOT THIS  {$$=addlabel("PRIMARYNONEWARRAY");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 |	OPENPARAN EXPRESSION CLOSEPARAN  {$$=addlabel("PRIMARYNONEWARRAY");addedge($$, $2);}
 |	CLASSINSTANCECREATIONEXPRESSION   {$$= $1;}
 |	FIELDACCESS  {$$= $1;}
 |	ARRAYACCESS  {$$= $1;}
 |	METHODINVOCATION  {$$= $1;}
 |	METHODREFERENCE  {$$= $1;}
LITERAL: INTEGERLITERAL  {$$=addlabel("LITERAL");$1=addlabel(string("integerliteral") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	FLOATINGPOINTLITERAL  {$$=addlabel("LITERAL");$1=addlabel(string("floatingpointliteral") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	BOOLEANLITERAL  {$$=addlabel("LITERAL");$1=addlabel(string("booleanliteral") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	CHARACTERLITERAL  {$$=addlabel("LITERAL");$1=addlabel(string("characterliteral") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	STRINGLITERAL  {$$=addlabel("LITERAL");$1=addlabel(string("stringliteral") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	TEXTBLOCK  {$$=addlabel("LITERAL");$1=addlabel(string("textblock") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	NULLLITERAL  {$$=addlabel("LITERAL");$1=addlabel(string("nullliteral") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
CLASSLITERAL: IDENTIFIER DOTCLASS  {$$=addlabel("CLASSLITERAL");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dotclass") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 |	NUMERICTYPE DOTCLASS  {$$=addlabel("CLASSLITERAL");addedge($$, $1);$2=addlabel(string("dotclass") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 |	BOOLEAN DOTCLASS  {$$=addlabel("CLASSLITERAL");$2=addlabel(string("dotclass") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 |	VOID DOTCLASS  {$$=addlabel("CLASSLITERAL");$2=addlabel(string("dotclass") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 | IDENTIFIER SQUARESTAR DOTCLASS  {$$=addlabel("CLASSLITERAL");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);$3=addlabel(string("dotclass") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	NUMERICTYPE SQUARESTAR DOTCLASS  {$$=addlabel("CLASSLITERAL");addedge($$, $1);addedge($$, $2);$3=addlabel(string("dotclass") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	BOOLEAN SQUARESTAR DOTCLASS  {$$=addlabel("CLASSLITERAL");addedge($$, $2);$3=addlabel(string("dotclass") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
SQUARESTAR : OPENSQUARE CLOSESQUARE  {$$=addlabel("SQUARESTAR");}
 | SQUARESTAR OPENSQUARE CLOSESQUARE  {$$=addlabel("SQUARESTAR");addedge($$, $1);}
CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  {$$= $1;}
 |	EXPRESSIONNAME DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  {$$=addlabel("CLASSINSTANCECREATIONEXPRESSION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	IDENTIFIER DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  {$$=addlabel("CLASSINSTANCECREATIONEXPRESSION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	PRIMARY DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  {$$=addlabel("CLASSINSTANCECREATIONEXPRESSION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);}
 | NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);addedge($$, $5);}
 | NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);addedge($$, $4);}
 | NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY   {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);addedge($$, $4);addedge($$, $6);}
 | NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);}
 | NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);addedge($$, $6);}
 | NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);addedge($$, $5);}
 | NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY  {$$=addlabel("UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);addedge($$, $5);addedge($$, $7);}
CLASSORINTERFACETYPETOINSTANTIATE: IDENTIFIER   {$$=addlabel("CLASSORINTERFACETYPETOINSTANTIATE");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
ARGUMENTLIST: EXPRESSION  {$$= $1;}
 | ARGUMENTLIST COMMA EXPRESSION  {$$=addlabel("ARGUMENTLIST");addedge($$, $1);addedge($$, $3);}
METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);}
 | METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);addedge($$, $3);}
 |	IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $5);}
 |	IDENTIFIER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 |	IDENTIFIER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $6);}
 |	EXPRESSIONNAME DOT IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	EXPRESSIONNAME DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $5);}
 |	EXPRESSIONNAME DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 |	EXPRESSIONNAME DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $6);}
 |	PRIMARY DOT IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	PRIMARY DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $5);}
 |	PRIMARY DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 |	PRIMARY DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $6);}
 |	SUPER DOT IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	SUPER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $5);}
 |	SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 |	SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $6);}
 |	IDENTIFIER DOT SUPER DOT IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$4=addlabel(string("dot") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);$5=addlabel(string("identifier") +  string("(") +  chartostring($5)+string(")"));addedge($$, $5);}
 |	IDENTIFIER DOT SUPER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$4=addlabel(string("dot") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);$5=addlabel(string("identifier") +  string("(") +  chartostring($5)+string(")"));addedge($$, $5);addedge($$, $7);}
 |	IDENTIFIER DOT SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$4=addlabel(string("dot") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $5);$6=addlabel(string("identifier") +  string("(") +  chartostring($6)+string(")"));addedge($$, $6);}
 |	IDENTIFIER DOT SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  {$$=addlabel("METHODINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$4=addlabel(string("dot") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $5);$6=addlabel(string("identifier") +  string("(") +  chartostring($6)+string(")"));addedge($$, $6);addedge($$, $8);}
METHODREFERENCE: PRIMARY DOUBLECOLON TYPEARGUMENTS IDENTIFIER  {$$=addlabel("METHODREFERENCE");addedge($$, $1);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 |	CLASSTYPE DOUBLECOLON TYPEARGUMENTS IDENTIFIER  {$$=addlabel("METHODREFERENCE");addedge($$, $1);addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 |	SUPER DOUBLECOLON TYPEARGUMENTS IDENTIFIER  {$$=addlabel("METHODREFERENCE");addedge($$, $3);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
 |	IDENTIFIER DOT SUPER DOUBLECOLON TYPEARGUMENTS IDENTIFIER  {$$=addlabel("METHODREFERENCE");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $5);$6=addlabel(string("identifier") +  string("(") +  chartostring($6)+string(")"));addedge($$, $6);}
 |	CLASSTYPE DOUBLECOLON TYPEARGUMENTS NEW  {$$=addlabel("METHODREFERENCE");addedge($$, $1);addedge($$, $3);}
 | CLASSTYPE DOUBLECOLON IDENTIFIER  {$$=addlabel("METHODREFERENCE");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	PRIMARY DOUBLECOLON IDENTIFIER  {$$=addlabel("METHODREFERENCE");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	SUPER DOUBLECOLON IDENTIFIER  {$$=addlabel("METHODREFERENCE");$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 |	IDENTIFIER DOT SUPER DOUBLECOLON IDENTIFIER  {$$=addlabel("METHODREFERENCE");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$5=addlabel(string("identifier") +  string("(") +  chartostring($5)+string(")"));addedge($$, $5);}
 |	CLASSTYPE DOUBLECOLON NEW  {$$=addlabel("METHODREFERENCE");addedge($$, $1);}
ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS  {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 |	NEW CLASSORINTERFACETYPE DIMEXPRS DIMS  {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 |	NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER  {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 |	NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER  {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | NEW PRIMITIVETYPE DIMEXPRS   {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);}
 |	NEW CLASSORINTERFACETYPE DIMEXPRS   {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);}
 | NEW PRIMITIVETYPE DIMS  {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);}
 |	NEW CLASSORINTERFACETYPE DIMS  {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);addedge($$, $3);}
 | NEW PRIMITIVETYPE   {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);}
 |	NEW CLASSORINTERFACETYPE   {$$=addlabel("ARRAYCREATIONEXPRESSION");addedge($$, $2);}
ARRAYINITIALIZER : OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  {$$=addlabel("ARRAYINITIALIZER");addedge($$, $2);}
 | OPENCURLY CLOSECURLY  {$$=addlabel("ARRAYINITIALIZER");}
ARRAYINITIALIZER1 : VARIABLEINITIALIZERLIST   {$$= $1;}
 | COMMA  {$$=addlabel("ARRAYINITIALIZER1");$1=addlabel(string("comma") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | VARIABLEINITIALIZERLIST COMMA  {$$=addlabel("ARRAYINITIALIZER1");addedge($$, $1);}
DIMEXPRS: DIMEXPR  {$$= $1;}
 | DIMEXPRS DIMEXPR  {$$=addlabel("DIMEXPRS");addedge($$, $1);addedge($$, $2);}
DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE   {$$=addlabel("DIMEXPR");addedge($$, $2);}
VARIABLEINITIALIZERLIST : VARIABLEINITIALIZER  {$$= $1;}
 | VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  {$$=addlabel("VARIABLEINITIALIZERLIST");addedge($$, $1);addedge($$, $3);}
ARRAYACCESS: EXPRESSIONNAME OPENSQUARE EXPRESSION CLOSESQUARE  {$$=addlabel("ARRAYACCESS");addedge($$, $1);addedge($$, $3);}
 |	PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE  {$$=addlabel("ARRAYACCESS");addedge($$, $1);addedge($$, $3);}
 |	IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE  {$$=addlabel("ARRAYACCESS");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $3);}
CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  {$$= $1;}
 |	CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  {$$=addlabel("CONDITIONALEXPRESSION");addedge($$, $1);addedge($$, $3);$4=addlabel(string("colon") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $5);}
CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  {$$= $1;}
 |	CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  {$$=addlabel("CONDITIONALOREXPRESSION");addedge($$, $1);$2=addlabel(string("oror") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  {$$= $1;}
 |	CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  {$$=addlabel("CONDITIONALANDEXPRESSION");addedge($$, $1);$2=addlabel(string("andand") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  {$$= $1;}
 |	INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  {$$=addlabel("INCLUSIVEOREXPRESSION");addedge($$, $1);$2=addlabel(string("or") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
EXCLUSIVEOREXPRESSION: ANDEXPRESSION  {$$= $1;}
 |	EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  {$$=addlabel("EXCLUSIVEOREXPRESSION");addedge($$, $1);$2=addlabel(string("xor") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
ANDEXPRESSION: EQUALITYEXPRESSION  {$$= $1;}
 |	ANDEXPRESSION AND EQUALITYEXPRESSION  {$$=addlabel("ANDEXPRESSION");addedge($$, $1);$2=addlabel(string("and") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
EQUALITYEXPRESSION: RELATIONALEXPRESSION  {$$= $1;}
 |	EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  {$$=addlabel("EQUALITYEXPRESSION");addedge($$, $1);$2=addlabel(string("equalsequals") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  {$$=addlabel("EQUALITYEXPRESSION");addedge($$, $1);$2=addlabel(string("notequals") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
RELATIONALEXPRESSION: SHIFTEXPRESSION  {$$= $1;}
 |	RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  {$$=addlabel("RELATIONALEXPRESSION");addedge($$, $1);addedge($$, $3);}
 |	RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  {$$=addlabel("RELATIONALEXPRESSION");addedge($$, $1);addedge($$, $3);}
 |	RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  {$$=addlabel("RELATIONALEXPRESSION");addedge($$, $1);$3=addlabel(string("equals") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);}
 |	RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  {$$=addlabel("RELATIONALEXPRESSION");addedge($$, $1);$3=addlabel(string("equals") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);}
 |	INSTANCEOFEXPRESSION  {$$= $1;}
SHIFTEXPRESSION: ADDITIVEEXPRESSION  {$$= $1;}
 |	SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  {$$=addlabel("SHIFTEXPRESSION");addedge($$, $1);$2=addlabel(string("angularleftangularleft") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  {$$=addlabel("SHIFTEXPRESSION");addedge($$, $1);$2=addlabel(string("angularrightangularright") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  {$$=addlabel("SHIFTEXPRESSION");addedge($$, $1);$2=addlabel(string("angularrightangularrightangularright") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  {$$= $1;}
 |	ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  {$$=addlabel("ADDITIVEEXPRESSION");addedge($$, $1);$2=addlabel(string("plus") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  {$$=addlabel("ADDITIVEEXPRESSION");addedge($$, $1);$2=addlabel(string("minus") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  {$$= $1;}
 |	MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  {$$=addlabel("MULTIPLICATIVEEXPRESSION");addedge($$, $1);$2=addlabel(string("multiply") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  {$$=addlabel("MULTIPLICATIVEEXPRESSION");addedge($$, $1);$2=addlabel(string("divide") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 |	MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  {$$=addlabel("MULTIPLICATIVEEXPRESSION");addedge($$, $1);$2=addlabel(string("mod") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
UNARYEXPRESSION: PREINCREMENTEXPRESSION  {$$= $1;}
 |	PREDECREMENTEXPRESSION  {$$= $1;}
 |	PLUS UNARYEXPRESSION  {$$=addlabel("UNARYEXPRESSION");$1=addlabel(string("plus") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
 |	MINUS UNARYEXPRESSION  {$$=addlabel("UNARYEXPRESSION");$1=addlabel(string("minus") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
 |	UNARYEXPRESSIONNOTPLUSMINUS  {$$= $1;}
PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  {$$=addlabel("PREINCREMENTEXPRESSION");$1=addlabel(string("plusplus") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  {$$=addlabel("PREDECREMENTEXPRESSION");$1=addlabel(string("minusminus") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  {$$= $1;}
 |	COMPLEMENT UNARYEXPRESSION  {$$=addlabel("UNARYEXPRESSIONNOTPLUSMINUS");$1=addlabel(string("complement") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
 |	NOT UNARYEXPRESSION  {$$=addlabel("UNARYEXPRESSIONNOTPLUSMINUS");$1=addlabel(string("not") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
POSTFIXEXPRESSION: PRIMARY  {$$= $1;}
 |	EXPRESSIONNAME  {$$= $1;}
 | IDENTIFIER  {$$=addlabel("POSTFIXEXPRESSION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 |	POSTINCREMENTEXPRESSION  {$$= $1;}
 |	POSTDECREMENTEXPRESSION  {$$= $1;}
POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  {$$=addlabel("POSTINCREMENTEXPRESSION");addedge($$, $1);$2=addlabel(string("plusplus") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  {$$=addlabel("POSTDECREMENTEXPRESSION");addedge($$, $1);$2=addlabel(string("minusminus") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
INSTANCEOFEXPRESSION: RELATIONALEXPRESSION INSTANCEOF REFERENCETYPE  {$$=addlabel("INSTANCEOFEXPRESSION");addedge($$, $1);addedge($$, $3);}
METHODDECLARATION: METHODHEADER METHODBODY  {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);}
 | SUPER1 METHODHEADER METHODBODY  {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | SUPER2 METHODHEADER METHODBODY  {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | SUPER3 METHODHEADER METHODBODY  {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | METHODMODIFIERS METHODHEADER METHODBODY  {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | AT OVERRIDE METHODHEADER METHODBODY   {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | AT OVERRIDE SUPER1 METHODHEADER METHODBODY   {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | AT OVERRIDE SUPER2 METHODHEADER METHODBODY   {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | AT OVERRIDE SUPER3 METHODHEADER METHODBODY   {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
 | AT OVERRIDE METHODMODIFIERS METHODHEADER METHODBODY   {$$=addlabel("METHODDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);addedge($$, $4);addedge($$, $5);}
METHODHEADER: TYPE METHODDECLARATOR THROWS2  {$$=addlabel("METHODHEADER");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | TYPE METHODDECLARATOR   {$$=addlabel("METHODHEADER");addedge($$, $1);addedge($$, $2);}
 |	TYPEPARAMETERS TYPE METHODDECLARATOR THROWS2  {$$=addlabel("METHODHEADER");addedge($$, $1);addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | TYPEPARAMETERS TYPE METHODDECLARATOR   {$$=addlabel("METHODHEADER");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | VOID METHODDECLARATOR THROWS2  {$$=addlabel("METHODHEADER");addedge($$, $2);addedge($$, $3);}
 | VOID METHODDECLARATOR   {$$=addlabel("METHODHEADER");addedge($$, $2);}
 |	TYPEPARAMETERS VOID METHODDECLARATOR THROWS2  {$$=addlabel("METHODHEADER");addedge($$, $1);addedge($$, $3);addedge($$, $4);}
 | TYPEPARAMETERS VOID METHODDECLARATOR   {$$=addlabel("METHODHEADER");addedge($$, $1);addedge($$, $3);}
THROWS2: THROWS EXCEPTIONTYPELIST  {$$=addlabel("THROWS2");addedge($$, $2);}
EXCEPTIONTYPELIST: EXCEPTIONTYPE   {$$= $1;}
 | EXCEPTIONTYPELIST COMMA EXCEPTIONTYPE  {$$=addlabel("EXCEPTIONTYPELIST");addedge($$, $1);addedge($$, $3);}
EXCEPTIONTYPE: CLASSTYPE  {$$= $1;}
METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN   {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | IDENTIFIER OPENPARAN CLOSEPARAN DIMS  {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $4);}
 | IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS  {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $3);addedge($$, $5);}
 | IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN   {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $3);}
 | IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN   {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);}
 | IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN DIMS  {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);addedge($$, $6);}
 | IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS  {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);addedge($$, $5);addedge($$, $7);}
 | IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN   {$$=addlabel("METHODDECLARATOR");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);addedge($$, $2);addedge($$, $5);}
RECEIVERPARAMETER: TYPE THIS  {$$=addlabel("RECEIVERPARAMETER");addedge($$, $1);}
 | TYPE IDENTIFIER DOT THIS  {$$=addlabel("RECEIVERPARAMETER");addedge($$, $1);$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);$3=addlabel(string("dot") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
FORMALPARAMETERLIST: FORMALPARAMETER   {$$= $1;}
 | FORMALPARAMETERLIST COMMA FORMALPARAMETER  {$$=addlabel("FORMALPARAMETERLIST");addedge($$, $1);addedge($$, $3);}
FORMALPARAMETER: TYPE VARIABLEDECLARATORID  {$$=addlabel("FORMALPARAMETER");addedge($$, $1);addedge($$, $2);}
 |	VARIABLEARITYPARAMETER  {$$= $1;}
 | FINAL TYPE VARIABLEDECLARATORID  {$$=addlabel("FORMALPARAMETER");addedge($$, $2);addedge($$, $3);}
VARIABLEARITYPARAMETER : TYPE TRIPLEDOT IDENTIFIER  {$$=addlabel("VARIABLEARITYPARAMETER");addedge($$, $1);$3=addlabel(string("identifier") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);}
 | FINAL TYPE TRIPLEDOT IDENTIFIER  {$$=addlabel("VARIABLEARITYPARAMETER");addedge($$, $2);$4=addlabel(string("identifier") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);}
METHODBODY: BLOCK  {$$= $1;}
 |	SEMICOLON  {$$=addlabel("METHODBODY");$1=addlabel(string("semicolon") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
INSTANCEINITIALIZER: BLOCK  {$$= $1;}
STATICINITIALIZER: STATIC BLOCK  {$$=addlabel("STATICINITIALIZER");addedge($$, $2);}
BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  {$$=addlabel("BLOCK");addedge($$, $2);}
 | OPENCURLY CLOSECURLY  {$$=addlabel("BLOCK");}
BLOCKSTATEMENTS: BLOCKSTATEMENT   {$$= $1;}
 | BLOCKSTATEMENTS BLOCKSTATEMENT   {$$=addlabel("BLOCKSTATEMENTS");addedge($$, $1);addedge($$, $2);}
BLOCKSTATEMENT: LOCALCLASSORINTERFACEDECLARATION  {$$= $1;}
 |	LOCALVARIABLEDECLARATIONSTATEMENT  {$$= $1;}
 |	STATEMENT  {$$= $1;}
LOCALCLASSORINTERFACEDECLARATION: CLASSDECLARATION  {$$= $1;}
LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  {$$=addlabel("LOCALVARIABLEDECLARATIONSTATEMENT");addedge($$, $1);}
LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  {$$=addlabel("LOCALVARIABLEDECLARATION");addedge($$, $2);addedge($$, $3);}
 | LOCALVARIABLETYPE VARIABLEDECLARATORLIST  {$$=addlabel("LOCALVARIABLEDECLARATION");addedge($$, $1);addedge($$, $2);}
LOCALVARIABLETYPE: TYPE  {$$= $1;}
 |	VAR  {$$=addlabel("LOCALVARIABLETYPE");$1=addlabel(string("var") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  {$$= $1;}
 |	LABELEDSTATEMENT  {$$= $1;}
 |	IFTHENSTATEMENT  {$$= $1;}
 |	IFTHENELSESTATEMENT  {$$= $1;}
 |	WHILESTATEMENT  {$$= $1;}
 |	FORSTATEMENT  {$$= $1;}
STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  {$$= $1;}
 |	EMPTYSTATEMENT  {$$= $1;}
 |	EXPRESSIONSTATEMENT  {$$= $1;}
 |	ASSERTSTATEMENT  {$$= $1;}
 |	BREAKSTATEMENT  {$$= $1;}
 |	CONTINUESTATEMENT  {$$= $1;}
 |	RETURNSTATEMENT  {$$= $1;}
 |	THROWSTATEMENT  {$$= $1;}
 |	YIELDSTATEMENT  {$$= $1;}
EMPTYSTATEMENT: SEMICOLON  {$$=addlabel("EMPTYSTATEMENT");$1=addlabel(string("semicolon") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  {$$=addlabel("EXPRESSIONSTATEMENT");addedge($$, $1);}
STATEMENTEXPRESSION: ASSIGNMENT  {$$= $1;}
 |	PREINCREMENTEXPRESSION  {$$= $1;}
 |	PREDECREMENTEXPRESSION  {$$= $1;}
 |	POSTINCREMENTEXPRESSION  {$$= $1;}
 |	POSTDECREMENTEXPRESSION  {$$= $1;}
 |	METHODINVOCATION  {$$= $1;}
 |	CLASSINSTANCECREATIONEXPRESSION  {$$= $1;}
ASSERTSTATEMENT: ASSERT EXPRESSION SEMICOLON  {$$=addlabel("ASSERTSTATEMENT");addedge($$, $2);}
 |	ASSERT EXPRESSION COLON EXPRESSION SEMICOLON  {$$=addlabel("ASSERTSTATEMENT");addedge($$, $2);$3=addlabel(string("colon") +  string("(") +  chartostring($3)+string(")"));addedge($$, $3);addedge($$, $4);}
BREAKSTATEMENT: BREAK SEMICOLON  {$$=addlabel("BREAKSTATEMENT");}
 | BREAK IDENTIFIER SEMICOLON  {$$=addlabel("BREAKSTATEMENT");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
CONTINUESTATEMENT: CONTINUE SEMICOLON  {$$=addlabel("CONTINUESTATEMENT");}
 | CONTINUE IDENTIFIER SEMICOLON  {$$=addlabel("CONTINUESTATEMENT");$2=addlabel(string("identifier") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  {$$=addlabel("RETURNSTATEMENT");addedge($$, $2);}
 | RETURN SEMICOLON  {$$=addlabel("RETURNSTATEMENT");}
THROWSTATEMENT: THROW EXPRESSION SEMICOLON  {$$=addlabel("THROWSTATEMENT");addedge($$, $2);}
YIELDSTATEMENT: YIELD EXPRESSION SEMICOLON  {$$=addlabel("YIELDSTATEMENT");addedge($$, $2);}
LABELEDSTATEMENT: IDENTIFIER COLON STATEMENT  {$$=addlabel("LABELEDSTATEMENT");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("colon") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  {$$=addlabel("IFTHENSTATEMENT");addedge($$, $3);addedge($$, $5);}
IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT  {$$=addlabel("IFTHENELSESTATEMENT");addedge($$, $3);addedge($$, $5);addedge($$, $7);}
IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF  {$$=addlabel("IFTHENELSESTATEMENTNOSHORTIF");addedge($$, $3);addedge($$, $5);addedge($$, $7);}
STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  {$$= $1;}
 |	LABELEDSTATEMENTNOSHORTIF  {$$= $1;}
 |	IFTHENELSESTATEMENTNOSHORTIF  {$$= $1;}
 |	WHILESTATEMENTNOSHORTIF  {$$= $1;}
 |	FORSTATEMENTNOSHORTIF  {$$= $1;}
LABELEDSTATEMENTNOSHORTIF: IDENTIFIER COLON STATEMENTNOSHORTIF  {$$=addlabel("LABELEDSTATEMENTNOSHORTIF");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("colon") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("WHILESTATEMENTNOSHORTIF");addedge($$, $3);addedge($$, $5);}
FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  {$$= $1;}
 |	ENHANCEDFORSTATEMENTNOSHORTIF  {$$= $1;}
WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  {$$=addlabel("WHILESTATEMENT");addedge($$, $3);addedge($$, $5);}
FORSTATEMENT: BASICFORSTATEMENT  {$$= $1;}
 |	ENHANCEDFORSTATEMENT  {$$= $1;}
BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $6);}
 |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $5);addedge($$, $7);}
 |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $4);addedge($$, $7);}
 |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $4);addedge($$, $6);addedge($$, $8);}
 |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $3);addedge($$, $7);}
 |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $3);addedge($$, $6);addedge($$, $8);}
 |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $3);addedge($$, $5);addedge($$, $8);}
 |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  {$$=addlabel("BASICFORSTATEMENT");addedge($$, $3);addedge($$, $5);addedge($$, $7);addedge($$, $9);}
BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $6);}
 |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $5);addedge($$, $7);}
 |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $4);addedge($$, $7);}
 |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $4);addedge($$, $6);addedge($$, $8);}
 |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $3);addedge($$, $7);}
 |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $3);addedge($$, $6);addedge($$, $8);}
 |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $3);addedge($$, $5);addedge($$, $8);}
 |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("BASICFORSTATEMENTNOSHORTIF");addedge($$, $3);addedge($$, $5);addedge($$, $7);addedge($$, $9);}
ENHANCEDFORSTATEMENT: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENT  {$$=addlabel("ENHANCEDFORSTATEMENT");addedge($$, $3);$4=addlabel(string("colon") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $5);addedge($$, $7);}
ENHANCEDFORSTATEMENTNOSHORTIF: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  {$$=addlabel("ENHANCEDFORSTATEMENTNOSHORTIF");addedge($$, $3);$4=addlabel(string("colon") +  string("(") +  chartostring($4)+string(")"));addedge($$, $4);addedge($$, $5);addedge($$, $7);}
FORINIT: STATEMENTEXPRESSIONLIST  {$$= $1;}
 |	LOCALVARIABLEDECLARATION  {$$= $1;}
FORUPDATE: STATEMENTEXPRESSIONLIST  {$$= $1;}
STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION   {$$= $1;}
 | STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION   {$$=addlabel("STATEMENTEXPRESSIONLIST");addedge($$, $1);addedge($$, $3);}
CONSTRUCTORDECLARATION: CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY  {$$=addlabel("CONSTRUCTORDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
 | CONSTRUCTORDECLARATOR CONSTRUCTORBODY  {$$=addlabel("CONSTRUCTORDECLARATION");addedge($$, $1);addedge($$, $2);}
 | SUPER1 CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY   {$$=addlabel("CONSTRUCTORDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);addedge($$, $4);}
 | SUPER1 CONSTRUCTORDECLARATOR CONSTRUCTORBODY   {$$=addlabel("CONSTRUCTORDECLARATION");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
CONSTRUCTORDECLARATOR: SIMPLETYPENAME OPENPARAN CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);}
 | SIMPLETYPENAME OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);addedge($$, $3);}
 | SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);addedge($$, $3);}
 | SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA FORMALPARAMETERLIST CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);addedge($$, $3);addedge($$, $5);}
 | TYPEPARAMETERS SIMPLETYPENAME OPENPARAN CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);addedge($$, $2);}
 | TYPEPARAMETERS SIMPLETYPENAME OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);addedge($$, $2);addedge($$, $4);}
 | TYPEPARAMETERS SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);addedge($$, $2);addedge($$, $4);}
 | TYPEPARAMETERS SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA FORMALPARAMETERLIST CLOSEPARAN  {$$=addlabel("CONSTRUCTORDECLARATOR");addedge($$, $1);addedge($$, $2);addedge($$, $4);addedge($$, $6);}
SIMPLETYPENAME: IDENTIFIER  {$$=addlabel("SIMPLETYPENAME");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
CONSTRUCTORBODY: OPENCURLY EXPLICITCONSTRUCTORINVOCATION BLOCKSTATEMENTS CLOSECURLY  {$$=addlabel("CONSTRUCTORBODY");addedge($$, $2);addedge($$, $3);}
 | OPENCURLY EXPLICITCONSTRUCTORINVOCATION CLOSECURLY  {$$=addlabel("CONSTRUCTORBODY");addedge($$, $2);}
 | OPENCURLY BLOCKSTATEMENTS CLOSECURLY  {$$=addlabel("CONSTRUCTORBODY");addedge($$, $2);}
 | OPENCURLY CLOSECURLY  {$$=addlabel("CONSTRUCTORBODY");}
EXPLICITCONSTRUCTORINVOCATION: THIS OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");}
 | THIS OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $3);}
 | TYPEARGUMENTS THIS OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);}
 | TYPEARGUMENTS THIS OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);addedge($$, $4);}
 | SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");}
 | SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $3);}
 | TYPEARGUMENTS SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);}
 | TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);addedge($$, $4);}
 | EXPRESSIONNAME DOT SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 | EXPRESSIONNAME DOT SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $5);}
 | EXPRESSIONNAME DOT TYPEARGUMENTS SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 | EXPRESSIONNAME DOT TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $6);}
 | IDENTIFIER DOT SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 | IDENTIFIER DOT SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $5);}
 | IDENTIFIER DOT TYPEARGUMENTS SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 | IDENTIFIER DOT TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");$1=addlabel(string("identifier") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $6);}
 | PRIMARY DOT SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);}
 | PRIMARY DOT SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $5);}
 | PRIMARY DOT TYPEARGUMENTS SUPER OPENPARAN CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);}
 | PRIMARY DOT TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON  {$$=addlabel("EXPLICITCONSTRUCTORINVOCATION");addedge($$, $1);$2=addlabel(string("dot") +  string("(") +  chartostring($2)+string(")"));addedge($$, $2);addedge($$, $3);addedge($$, $6);}
SUPER1 : PUBLIC   {$$=addlabel("SUPER1");$1=addlabel(string("public") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | PRIVATE   {$$=addlabel("SUPER1");$1=addlabel(string("private") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | PROTECTED  {$$=addlabel("SUPER1");$1=addlabel(string("protected") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | SUPER1 PUBLIC   {$$=addlabel("SUPER1");addedge($$, $1);}
 | SUPER1 PRIVATE   {$$=addlabel("SUPER1");addedge($$, $1);}
 | SUPER1 PROTECTED  {$$=addlabel("SUPER1");addedge($$, $1);}
SUPER2 : STATIC  {$$=addlabel("SUPER2");$1=addlabel(string("static") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | FINAL   {$$=addlabel("SUPER2");$1=addlabel(string("final") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | SUPER1 STATIC  {$$=addlabel("SUPER2");addedge($$, $1);}
 | SUPER1 FINAL  {$$=addlabel("SUPER2");addedge($$, $1);}
 | SUPER2 STATIC  {$$=addlabel("SUPER2");addedge($$, $1);}
 | SUPER2 FINAL  {$$=addlabel("SUPER2");addedge($$, $1);}
 | SUPER2 PUBLIC  {$$=addlabel("SUPER2");addedge($$, $1);}
 | SUPER2 PRIVATE  {$$=addlabel("SUPER2");addedge($$, $1);}
 | SUPER2 PROTECTED  {$$=addlabel("SUPER2");addedge($$, $1);}
SUPER3 : ABSTRACT  {$$=addlabel("SUPER3");$1=addlabel(string("abstract") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | STRICTFP  {$$=addlabel("SUPER3");$1=addlabel(string("strictfp") +  string("(") +  chartostring($1)+string(")"));addedge($$, $1);}
 | SUPER2 ABSTRACT  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER2 STRICTFP  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER3 ABSTRACT  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER3 STRICTFP  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER3 PUBLIC  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER3 PRIVATE  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER3 PROTECTED  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER3 STATIC  {$$=addlabel("SUPER3");addedge($$, $1);}
 | SUPER3 FINAL  {$$=addlabel("SUPER3");addedge($$, $1);}
FIELDMODIFIERS: SUPER3 TRANSIENT  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | SUPER3 VOLATILE  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | FIELDMODIFIERS TRANSIENT  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | FIELDMODIFIERS VOLATILE  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | FIELDMODIFIERS PUBLIC  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | FIELDMODIFIERS PRIVATE  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | FIELDMODIFIERS PROTECTED  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | FIELDMODIFIERS STATIC  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
 | FIELDMODIFIERS FINAL  {$$=addlabel("FIELDMODIFIERS");addedge($$, $1);}
METHODMODIFIERS : SUPER3 SYNCHRONIZED  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | SUPER3 NATIVE  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS SYNCHRONIZED  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS NATIVE  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS ABSTRACT  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS STRICTFP  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS PUBLIC  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS PRIVATE  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS PROTECTED  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS STATIC  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}
 | METHODMODIFIERS FINAL  {$$=addlabel("METHODMODIFIERS");addedge($$, $1);}

%%


void yyerror(char *s){
    cout<<"syntax error in line number "<<yylineno<<endl;
}

int main(int argc, char** argv){
    bool inset = false, outset = false;
    for (int i=0; i< argc; i++){
        // handle input arguments 
        //  arguments can be space separated 
        // arguments are help, input, output, verbose

        if (strcmp(argv[i], "help") == 0){
            cout<<"Usage: ./myASTgen [help] [input <filename>] [output <filename>] [verbose]\n";
            cout<< "Example: ./myASTgen input input.txt output output.txt\n";
            
        }
        else if (strcmp(argv[i], "input") == 0){
            yyin = fopen(argv[i+1], "r");
            inset = true;
        }
        else if (strcmp(argv[i], "output") == 0){
            freopen(argv[i+1], "w", stdout);
            outset = true;
        }
        else if (strcmp(argv[i], "verbose") == 0){
            cout<<"Verbose Output directed to parser.output\n";
        }
    }

    if (!inset){
        cout<< "Input not set, see help";
        return 0;
    }
    if (!outset){
        cout<< "Output not set, see help";
        return 0;
    }
    yyparse();
    cout << "digraph ASTVisual {\n ordering = out ;\n";
    for(auto e: labels){
        string s;
        
         for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'  ){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        cout<<e.num<<" [ label=\""<<s<<"\"]\n";
    }
    for(auto e: edges){
        string s;

        for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        cout<<e.a<< " -> "<<e.b << "[ label=\""<<s<<"\"]\n";
    }
    cout << "  }\n";

}



