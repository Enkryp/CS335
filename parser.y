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
%type<val>  DIMS
%token<val> BOOLEAN BYTE SHORT INT LONG CHAR FLOAT DOUBLE 

/* Separators */
%token<val> COMMA QUESTIONMARK SEMICOLON  OPENCURLY CLOSECURLY ANGULARLEFT ANGULARRIGHT OPENSQUARE CLOSESQUARE OPENPARAN CLOSEPARAN DOUBLECOLON TRIPLEDOT WS

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

COMPILATIONUNIT     :    ORDINARYCOMPILATIONUNIT EOFF {return 0;}
/* Type definitions */
TYPE    :   PRIMITIVETYPE
            |   REFERENCETYPE;

PRIMITIVETYPE   :   NUMERICTYPE
                |   BOOLEAN;

NUMERICTYPE     :   INTEGRALTYPE
                |   FLOATINGTYPE;

INTEGRALTYPE    : BYTE
                | SHORT 
                | INT 
                | LONG 
                | CHAR;

FLOATINGTYPE    :   FLOAT
                |   DOUBLE;

REFERENCETYPE   :   CLASSORINTERFACETYPE
                /* |   ARRAYTYPE; */


/* CLASSORINTERFACETYPE    :   CLASSTYPE
                        |   INTERFACETYPE; */


CLASSORINTERFACETYPE    :   CLASSTYPE 
                        /* |   CLASSTYPE TYPEARGUMENTS */
CLASSTYPE   :   CLASSTYPE1
        //     |   CLASSTYPE3; Nested classes excluded

CLASSTYPE1  :   IDENTIFIER
            /* |   IDENTIFIER  TYPEARGUMENTS; Type Argument supported excluded*/

TYPEARGUMENTS   :   ANGULARLEFT TYPEARGUMENTLIST  ANGULARRIGHT

TYPEARGUMENTLIST    :   TYPEARGUMENT
                    |   TYPEARGUMENTLIST COMMA TYPEARGUMENT

TYPEARGUMENT    :   REFERENCETYPE
                |   WILDCARD;

WILDCARD    :   QUESTIONMARK 
            |   QUESTIONMARK WILDCARDBOUNDS

WILDCARDBOUNDS  :   EXTENDS REFERENCETYPE
                |   SUPER REFERENCETYPE;

// CLASSTYPE3  :   CLASSORINTERFACETYPE DOT IDENTIFIER 
            /* |   CLASSORINTERFACETYPE DOT IDENTIFIER TYPEARGUMENTS */

INTERFACETYPE   :   CLASSTYPE

/* TYPEVARIABLE    :   IDENTIFIER */

 /* ARRAYTYPE   :   PRIMITIVETYPE   DIMS
             |   CLASSORINTERFACETYPE  DIMS */

DIMS    :   OPENSQUARE CLOSESQUARE  {$1=addlabel(chartostring($1)); $2=addlabel(chartostring($2)); $$=addlabel("dimension");addedge($$,$1,"dimension"); addedge($$,$2,"dimension"); }
        |   DIMS OPENSQUARE CLOSESQUARE

/* Names */

/* TYPENAME    :   IDENTIFIER */


METHODNAME  :   UNQUALIFIEDMETHODIDENTIFIER     //identifier other than yield

EXPRESSIONNAME   :   IDENTIFIER DOT IDENTIFIER
                |   EXPRESSIONNAME DOT IDENTIFIER

/* Start Symbol : CompilationUnit */

/* // {$0=addlabel("compilation"); $$=addlabel("compilationunit"); addedge($$,$0);} */

ORDINARYCOMPILATIONUNIT :   
                        |   TOPLEVELCLASSORINTERFACEDECLARATION ;

TOPLEVELCLASSORINTERFACEDECLARATION :   CLASSDECLARATION
                                    |   SEMICOLON;

/* Ignored enum and record */
CLASSDECLARATION    :   NORMALCLASSDECLARATION
                    

NORMALCLASSDECLARATION  :    CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY
                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY
                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY
                            | CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER CLASSEXTENDS CLASSBODY
                            | CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSEXTENDS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            // | CLASSMODIFIER CLASS IDENTIFIER CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER TYPEPARAMETERS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSBODY

// CLASSMODIFIER   :   SUPERMODIFIER
//                 |   CLASSMODIFIER SUPERMODIFIER;

/* CLASSMODIFIER1   :  ABSTRACT | SEALED  */

TYPEPARAMETERS  :   ANGULARLEFT TYPEPARAMETERLIST ANGULARRIGHT

TYPEPARAMETERLIST   :   TYPEPARAMETER
                    |   TYPEPARAMETERLIST COMMA TYPEPARAMETER

TYPEPARAMETER   :   IDENTIFIER TYPEBOUND
                |   IDENTIFIER;


TYPEBOUND   :  EXTENDS IDENTIFIER
            |   EXTENDS CLASSORINTERFACETYPE ADDITIONALBOUND

ADDITIONALBOUND :   AND INTERFACETYPE
                |   ADDITIONALBOUND AND INTERFACETYPE

CLASSEXTENDS    :   EXTENDS CLASSTYPE

CLASSIMPLEMENTS :    IMPLEMENTS INTERFACETYPELIST

INTERFACETYPELIST   :   INTERFACETYPE
                    |   INTERFACETYPELIST COMMA INTERFACETYPE

CLASSPERMITS    :   PERMITS TYPENAMES

TYPENAMES   :   IDENTIFIER
            |   TYPENAMES COMMA IDENTIFIER

CLASSBODY   :  OPENCURLY CLOSECURLY {}
            |   OPENCURLY CLASSBODYDECLARATIONS CLOSECURLY

CLASSBODYDECLARATIONS   :   CLASSBODYDECLARATION
                        |   CLASSBODYDECLARATIONS CLASSBODYDECLARATION

CLASSBODYDECLARATION    :   CLASSMEMBERDECLARATION
                        |   INSTANCEINITIALIZER
                        |   STATICINITIALIZER
                        |   CONSTRUCTORDECLARATION;

CLASSMEMBERDECLARATION:     FIELDDECLARATION
                            |   METHODDECLARATION
                            |   CLASSDECLARATION
                            |   SEMICOLON

FIELDDECLARATION    :   FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON
                    |   SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON
                    |   SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON
                    |   TYPE VARIABLEDECLARATORLIST SEMICOLON;


// FIELDMODIFIERS  :   FIELDMODIFIER
//                 |   FIELDMODIFIERS FIELDMODIFIER
//                 |   SUPERMODIFIER
//                 |   FIELDMODIFIERS SUPERMODIFIER;

/*SUPERMODIFIER   :   PUBLIC | PROTECTED |  PRIVATE | STATIC | FINAL 
FIELDMODIFIER   :   TRANSIENT | VOLATILE
*/

VARIABLEDECLARATORLIST  :   VARIABLEDECLARATOR
                        |   VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR;

VARIABLEDECLARATOR  :   VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER
                    |   VARIABLEDECLARATORID

VARIABLEDECLARATORID    :   IDENTIFIER 
                        |   IDENTIFIER DIMS

VARIABLEINITIALIZER :    EXPRESSION
                    |   ARRAYINITIALIZER

EXPRESSION  :  ASSIGNMENTEXPRESSION

ASSIGNMENTEXPRESSION    :   CONDITIONALEXPRESSION
                        |   ASSIGNMENT

ASSIGNMENT  :   LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION

LEFTHANDSIDE    :   EXPRESSIONNAME
                |   IDENTIFIER
                |   FIELDACCESS
                |   ARRAYACCESS

ASSIGNMENTOPERATOR  :  EQUALS
                    |  MULTIPLYEQUALS
                    |   DIVIDEEQUALS
                    |   MODEQUALS
                    |   PLUSEQUALS
                    |   MINUSEQUALS
                    
FIELDACCESS: PRIMARY DOT IDENTIFIER
            |	SUPER DOT IDENTIFIER
            |	IDENTIFIER DOT SUPER DOT IDENTIFIER

PRIMARY: PRIMARYNONEWARRAY
        |	ARRAYCREATIONEXPRESSION


/* here */
PRIMARYNONEWARRAY: LITERAL
                  |	CLASSLITERAL
                  |	THIS
                  |	IDENTIFIER DOT THIS
                  |	OPENPARAN EXPRESSION CLOSEPARAN
                  |	CLASSINSTANCECREATIONEXPRESSION         
                  |	FIELDACCESS
                  |	ARRAYACCESS
                  |	METHODINVOCATION
                  |	METHODREFERENCE

LITERAL: INTEGERLITERAL
        |	FLOATINGPOINTLITERAL
        |	BOOLEANLITERAL
        |	CHARACTERLITERAL
        |	STRINGLITERAL
        |	TEXTBLOCK
        |	NULLLITERAL

CLASSLITERAL: IDENTIFIER DOTCLASS
             |	NUMERICTYPE DOTCLASS
             |	BOOLEAN DOTCLASS
             |	VOID DOTCLASS
             | IDENTIFIER SQUARESTAR DOTCLASS
             |	NUMERICTYPE SQUARESTAR DOTCLASS
             |	BOOLEAN SQUARESTAR DOTCLASS

SQUARESTAR  :   OPENSQUARE CLOSESQUARE
            |   SQUARESTAR  OPENSQUARE CLOSESQUARE

CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION
                                |	EXPRESSIONNAME DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION
                                |	IDENTIFIER DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION
                                |	PRIMARY DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION

UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION:     NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN
                                            |   NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY
                                            |   NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN
                                            |   NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY 
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY

CLASSORINTERFACETYPETOINSTANTIATE:  IDENTIFIER  
                                // |   IDENTIFIER DOTIDENTIFIER
                                // |   IDENTIFIER TYPEARGUMENTSORDIAMOND
                                // |   IDENTIFIER DOTIDENTIFIER TYPEARGUMENTSORDIAMOND

DOTIDENTIFIER   :   DOT IDENTIFIER
                |   DOTIDENTIFIER DOT IDENTIFIER

/* here <> ignored */
TYPEARGUMENTSORDIAMOND: TYPEARGUMENTS

ARGUMENTLIST: EXPRESSION
            |   ARGUMENTLIST COMMA EXPRESSION

METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN
                 |  METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN
                 |	IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	IDENTIFIER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN
                 |	IDENTIFIER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	EXPRESSIONNAME DOT IDENTIFIER OPENPARAN CLOSEPARAN
                 |	EXPRESSIONNAME DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	EXPRESSIONNAME DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN
                 |	EXPRESSIONNAME DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	PRIMARY DOT IDENTIFIER OPENPARAN CLOSEPARAN
                 |	PRIMARY DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	PRIMARY DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN
                 |	PRIMARY DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	SUPER DOT IDENTIFIER OPENPARAN CLOSEPARAN
                 |	SUPER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN
                 |	SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	IDENTIFIER DOT SUPER DOT IDENTIFIER OPENPARAN CLOSEPARAN
                 |	IDENTIFIER DOT SUPER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN
                 |	IDENTIFIER DOT SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN CLOSEPARAN
                 |	IDENTIFIER DOT SUPER DOT TYPEARGUMENTS IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN

METHODREFERENCE:    PRIMARY DOUBLECOLON TYPEARGUMENTS IDENTIFIER
                |	CLASSTYPE DOUBLECOLON TYPEARGUMENTS IDENTIFIER
                |	SUPER DOUBLECOLON TYPEARGUMENTS IDENTIFIER
                |	IDENTIFIER DOT SUPER DOUBLECOLON TYPEARGUMENTS IDENTIFIER
                |	CLASSTYPE DOUBLECOLON TYPEARGUMENTS NEW
                /* |	CLASSTYPE TYPEARGUMENTS DOUBLECOLON TYPEARGUMENTS NEW */
                /* |	ARRAYTYPE DOUBLECOLON NEW 
                ClassOrInterfaceType
TypeVariable
ArrayType
*/
                |   CLASSTYPE DOUBLECOLON IDENTIFIER
                |	PRIMARY DOUBLECOLON IDENTIFIER

                |	SUPER DOUBLECOLON IDENTIFIER
                |	IDENTIFIER DOT SUPER DOUBLECOLON IDENTIFIER
                |	CLASSTYPE DOUBLECOLON NEW
                /* |	CLASSTYPE TYPEARGUMENTS DOUBLECOLON NEW */

ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS
                        |	NEW CLASSORINTERFACETYPE DIMEXPRS DIMS
                        |	NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER
                        |	NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER
                        |   NEW PRIMITIVETYPE DIMEXPRS 
                        |	NEW CLASSORINTERFACETYPE DIMEXPRS 
                        |   NEW PRIMITIVETYPE DIMS
                        |	NEW CLASSORINTERFACETYPE DIMS
                        |   NEW PRIMITIVETYPE 
                        |	NEW CLASSORINTERFACETYPE 

ARRAYINITIALIZER    :  OPENCURLY ARRAYINITIALIZER1 CLOSECURLY
                    |   OPENCURLY CLOSECURLY

ARRAYINITIALIZER1   :  VARIABLEINITIALIZERLIST 
                    |   COMMA
                    |   VARIABLEINITIALIZERLIST COMMA

DIMEXPRS: DIMEXPR
        |   DIMEXPRS DIMEXPR


/* lookhere*/ 
DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE;

VARIABLEINITIALIZERLIST :   VARIABLEINITIALIZER
                        |   VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER




/* =================== */

ARRAYACCESS: EXPRESSIONNAME OPENSQUARE EXPRESSION CLOSESQUARE
            |	PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE
            |	IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE

CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION
                      |	CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION

CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION
                        |	CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION

CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION
                         |	CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION

INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION
                      |	INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION

EXCLUSIVEOREXPRESSION: ANDEXPRESSION
                      |	EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION

ANDEXPRESSION: EQUALITYEXPRESSION
              |	ANDEXPRESSION AND EQUALITYEXPRESSION

EQUALITYEXPRESSION: RELATIONALEXPRESSION
                   |	EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION
                   |	EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION

RELATIONALEXPRESSION: SHIFTEXPRESSION
                     |	RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION
                     |	RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION
                     |	RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION
                     |	RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION
                     |	INSTANCEOFEXPRESSION

SHIFTEXPRESSION: ADDITIVEEXPRESSION
                |	SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION
                |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION
                |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION

ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION
                   |	ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION
                   |	ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION

MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION
                         |	MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION
                         |	MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION
                         |	MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION

UNARYEXPRESSION: PREINCREMENTEXPRESSION
                |	PREDECREMENTEXPRESSION
                |	PLUS UNARYEXPRESSION
                |	MINUS UNARYEXPRESSION
                |	UNARYEXPRESSIONNOTPLUSMINUS

PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION

PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION

UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION
                            |	COMPLEMENT UNARYEXPRESSION
                            |	NOT UNARYEXPRESSION
                            
POSTFIXEXPRESSION: PRIMARY
                  |	EXPRESSIONNAME
                  | IDENTIFIER
                  |	POSTINCREMENTEXPRESSION
                  |	POSTDECREMENTEXPRESSION

POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS

POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS

INSTANCEOFEXPRESSION: RELATIONALEXPRESSION INSTANCEOF REFERENCETYPE
                     
/* TYPE: PRIMITIVETYPE
          |	REFERENCETYPE */

/*TYPE: PRIMITIVETYPE
          |	REFERENCETYPE
*/
/* PRIMITIVETYPE: NUMERICTYPE
                   |	BOOLEAN */

/* REFERENCETYPE: CLASSORINTERFACETYPE
                   |	TYPEVARIABLE
                   |	ARRAYTYPE */


/* REFERENCETYPE: CLASSORINTERFACETYPE
                   |	ARRAYTYPE */

/*REFERENCETYPE: CLASSORINTERFACETYPE
                    |	ARRAYTYPE
*/
/* CLASSORINTERFACETYPE: CLASSTYPE */

/* CLASSTYPE: IDENTIFIER TYPEARGUMENTS
                |   IDENTIFIER 
               |	CLASSORINTERFACETYPE DOT IDENTIFIER TYPEARGUMENTS
               |	CLASSORINTERFACETYPE DOT IDENTIFIER  */

/* INTERFACETYPE: CLASSTYPE */

/* TYPEVARIABLE: IDENTIFIER  */



/* ARRAYTYPE: PRIMITIVETYPE DIMS
               |	CLASSORINTERFACETYPE DIMS
               |	IDENTIFIER DIMS */

/*ARRAYTYPE: PRIMITIVETYPE DIMS
               |	CLASSORINTERFACETYPE DIMS
                |	IDENTIFIER DIMS */

METHODDECLARATION:  METHODHEADER METHODBODY
                    |   SUPER1 METHODHEADER METHODBODY
                    |   SUPER2 METHODHEADER METHODBODY
                    |   SUPER3 METHODHEADER METHODBODY
                    |   METHODMODIFIERS METHODHEADER METHODBODY

// METHODMODIFIERS :   METHODMODIFIER
//                 |   METHODMODIFIERS METHODMODIFIER
//                 |   SUPERMODIFIER
//                 |   METHODMODIFIERS SUPERMODIFIER

// METHODMODIFIER:  ABSTRACT | SYNCHRONIZED| NATIVE | STRICTFP

METHODHEADER: TYPE METHODDECLARATOR THROWS2
            |   TYPE METHODDECLARATOR 
             |	TYPEPARAMETERS TYPE METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS TYPE METHODDECLARATOR 
             |  VOID METHODDECLARATOR THROWS2
            |   VOID METHODDECLARATOR 
             |	TYPEPARAMETERS VOID METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS VOID METHODDECLARATOR 

/* RESULT: TYPE
       |	VOID */

THROWS2: THROWS EXCEPTIONTYPELIST

EXCEPTIONTYPELIST: EXCEPTIONTYPE    
                |   EXCEPTIONTYPELIST COMMA EXCEPTIONTYPE

EXCEPTIONTYPE: CLASSTYPE

METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN 
                |   IDENTIFIER OPENPARAN CLOSEPARAN DIMS
                |   IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS
                |   IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN 
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN 
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN DIMS
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN 

RECEIVERPARAMETER:  TYPE THIS
                |   TYPE IDENTIFIER DOT THIS

FORMALPARAMETERLIST: FORMALPARAMETER 
                    |   FORMALPARAMETERLIST COMMA FORMALPARAMETER

FORMALPARAMETER:  TYPE VARIABLEDECLARATORID
                |	VARIABLEARITYPARAMETER
                |   VARIABLEMODIFIERS TYPE VARIABLEDECLARATORID

VARIABLEMODIFIERS   :   VARIABLEMODIFIER
                    |   VARIABLEMODIFIERS VARIABLEMODIFIER

VARIABLEARITYPARAMETER  :  TYPE TRIPLEDOT IDENTIFIER
                        |   VARIABLEMODIFIERS TYPE TRIPLEDOT IDENTIFIER

VARIABLEMODIFIER:   FINAL

METHODBODY: BLOCK
           |	SEMICOLON

INSTANCEINITIALIZER: BLOCK

STATICINITIALIZER: STATIC BLOCK

BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY
    |   OPENCURLY  CLOSECURLY

BLOCKSTATEMENTS: BLOCKSTATEMENT 
                |  BLOCKSTATEMENTS BLOCKSTATEMENT 

BLOCKSTATEMENT: LOCALCLASSORINTERFACEDECLARATION
               |	LOCALVARIABLEDECLARATIONSTATEMENT
               |	STATEMENT
 
 /* here interface ignored */
LOCALCLASSORINTERFACEDECLARATION: CLASSDECLARATION

LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON

LOCALVARIABLEDECLARATION: VARIABLEMODIFIERS LOCALVARIABLETYPE VARIABLEDECLARATORLIST
                        |   LOCALVARIABLETYPE VARIABLEDECLARATORLIST

LOCALVARIABLETYPE: TYPE
                  |	VAR

/* Statement */

STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT
          |	LABELEDSTATEMENT
          |	IFTHENSTATEMENT
          |	IFTHENELSESTATEMENT
          |	WHILESTATEMENT
          |	FORSTATEMENT

STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK
                                     |	EMPTYSTATEMENT
                                     |	EXPRESSIONSTATEMENT
                                     |	ASSERTSTATEMENT
                                     |	BREAKSTATEMENT
                                     |	CONTINUESTATEMENT
                                     |	RETURNSTATEMENT
                                     |	THROWSTATEMENT
                                     |	YIELDSTATEMENT

EMPTYSTATEMENT: SEMICOLON

EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON

STATEMENTEXPRESSION: ASSIGNMENT
                    |	PREINCREMENTEXPRESSION
                    |	PREDECREMENTEXPRESSION
                    |	POSTINCREMENTEXPRESSION
                    |	POSTDECREMENTEXPRESSION
                    |	METHODINVOCATION
                    |	CLASSINSTANCECREATIONEXPRESSION

ASSERTSTATEMENT: ASSERT EXPRESSION SEMICOLON
                |	ASSERT EXPRESSION COLON EXPRESSION SEMICOLON

BREAKSTATEMENT: BREAK SEMICOLON
                |   BREAK IDENTIFIER SEMICOLON

CONTINUESTATEMENT: CONTINUE SEMICOLON
                |   CONTINUE IDENTIFIER SEMICOLON

RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON
                |   RETURN SEMICOLON

THROWSTATEMENT: THROW EXPRESSION SEMICOLON

YIELDSTATEMENT: YIELD EXPRESSION SEMICOLON

LABELEDSTATEMENT: IDENTIFIER COLON STATEMENT

IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT

IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT

IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN  STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF

STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT
                   |	LABELEDSTATEMENTNOSHORTIF
                   |	IFTHENELSESTATEMENTNOSHORTIF
                   |	WHILESTATEMENTNOSHORTIF
                   |	FORSTATEMENTNOSHORTIF

LABELEDSTATEMENTNOSHORTIF: IDENTIFIER COLON STATEMENTNOSHORTIF

WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF

FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF
                      |	ENHANCEDFORSTATEMENTNOSHORTIF


WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT

FORSTATEMENT: BASICFORSTATEMENT
             |	ENHANCEDFORSTATEMENT

BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT
                  |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT

BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF
                  |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF

ENHANCEDFORSTATEMENT: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENT

ENHANCEDFORSTATEMENTNOSHORTIF: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF

FORINIT: STATEMENTEXPRESSIONLIST
        |	LOCALVARIABLEDECLARATION

FORUPDATE: STATEMENTEXPRESSIONLIST

STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION 
                        |   STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION 

CONSTRUCTORDECLARATION:     CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY
                        |   CONSTRUCTORDECLARATOR CONSTRUCTORBODY
                        |   SUPER1 CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY  
                        |   SUPER1 CONSTRUCTORDECLARATOR CONSTRUCTORBODY 

// CONSTRUCTORMODIFIERS    :   SUPERMODIFIER
//                         |   CONSTRUCTORMODIFIERS SUPERMODIFIER

/* CONSTRUCTORMODIFIER :   PUBLIC | PRIVATE | PROTECTED */

CONSTRUCTORDECLARATOR: SIMPLETYPENAME OPENPARAN  CLOSEPARAN
                    |   SIMPLETYPENAME OPENPARAN FORMALPARAMETERLIST CLOSEPARAN
                    |   SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA CLOSEPARAN
                    |   SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA FORMALPARAMETERLIST CLOSEPARAN
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN  CLOSEPARAN
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN FORMALPARAMETERLIST CLOSEPARAN
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA CLOSEPARAN
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA FORMALPARAMETERLIST CLOSEPARAN

SIMPLETYPENAME: IDENTIFIER

CONSTRUCTORBODY: OPENCURLY EXPLICITCONSTRUCTORINVOCATION BLOCKSTATEMENTS CLOSECURLY
                |   OPENCURLY EXPLICITCONSTRUCTORINVOCATION CLOSECURLY
                |   OPENCURLY BLOCKSTATEMENTS CLOSECURLY
                |   OPENCURLY  CLOSECURLY

EXPLICITCONSTRUCTORINVOCATION: THIS OPENPARAN CLOSEPARAN SEMICOLON
                            |    THIS OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   TYPEARGUMENTS THIS OPENPARAN  CLOSEPARAN SEMICOLON
                            |   TYPEARGUMENTS THIS OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   SUPER OPENPARAN CLOSEPARAN SEMICOLON
                            |    SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   TYPEARGUMENTS SUPER OPENPARAN  CLOSEPARAN SEMICOLON
                            |   TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   EXPRESSIONNAME DOT SUPER OPENPARAN CLOSEPARAN SEMICOLON
                            |   EXPRESSIONNAME DOT SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   EXPRESSIONNAME DOT TYPEARGUMENTS SUPER OPENPARAN  CLOSEPARAN SEMICOLON
                            |   EXPRESSIONNAME DOT TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   IDENTIFIER DOT SUPER OPENPARAN CLOSEPARAN SEMICOLON
                            |   IDENTIFIER DOT SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   IDENTIFIER DOT TYPEARGUMENTS SUPER OPENPARAN  CLOSEPARAN SEMICOLON
                            |   IDENTIFIER DOT TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |  PRIMARY DOT SUPER OPENPARAN CLOSEPARAN SEMICOLON
                            |   PRIMARY DOT SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   PRIMARY DOT TYPEARGUMENTS SUPER OPENPARAN  CLOSEPARAN SEMICOLON
                            |   PRIMARY DOT TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON

SUPER1 : PUBLIC | PRIVATE | PROTECTED
        | SUPER1 PUBLIC 
        | SUPER1 PRIVATE 
        | SUPER1 PROTECTED
    
SUPER2 : SUPER1 STATIC
        | SUPER1 FINAL
        | SUPER2 STATIC
        | SUPER2 FINAL
        | SUPER2 PUBLIC
        | SUPER2 PRIVATE
        | SUPER2 PROTECTED

SUPER3 : SUPER2 ABSTRACT
        | SUPER2 STRICTFP
        | SUPER3 ABSTRACT
        | SUPER3 STRICTFP
        | SUPER3 PUBLIC
        | SUPER3 PRIVATE
        | SUPER3 PROTECTED
        | SUPER3 STATIC
        | SUPER3 FINAL

FIELDMODIFIERS: SUPER3 TRANSIENT
            |   SUPER3 VOLATILE
            |  FIELDMODIFIERS TRANSIENT
            |  FIELDMODIFIERS VOLATILE
            | FIELDMODIFIERS PUBLIC
            | FIELDMODIFIERS PRIVATE
            | FIELDMODIFIERS PROTECTED
            | FIELDMODIFIERS STATIC
            | FIELDMODIFIERS FINAL


METHODMODIFIERS : SUPER3 SYNCHRONIZED
                | SUPER3 NATIVE
                | METHODMODIFIERS SYNCHRONIZED
                | METHODMODIFIERS NATIVE
                | METHODMODIFIERS ABSTRACT
                | METHODMODIFIERS STRICTFP
                | METHODMODIFIERS PUBLIC
                | METHODMODIFIERS PRIVATE
                | METHODMODIFIERS PROTECTED
                | METHODMODIFIERS STATIC
                | METHODMODIFIERS FINAL


%%


void yyerror(char *s){
    cout<<"syntax error"<<endl;
}

int main(){
    yyparse();
    cout << "digraph ASTVisual {\n";
    for(auto e: labels){
        cout<<e.num<<" [ label=\""<<e.l<<"\"]\n";
    }
    for(auto e: edges){
        cout<<e.a<< " -> "<<e.b << "[ label=\""<<e.l<<"\"]\n";
    }
    cout << "  }\n";

}