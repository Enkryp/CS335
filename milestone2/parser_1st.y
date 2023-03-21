%{
    #include<bits/stdc++.h>
    extern "C" int yylex();
    extern "C" FILE *yyin;
    extern "C" int yylineno; 
    using namespace std;   
    void yyerror(char *s){
        cerr<<s<<" at: "<<yylineno<<endl;
        exit(0);
    }
    
    #include"conversion.h"
    #include"metadata.h"
    #include"scope.h"    
    char* new_scope(){
        char* c= numtochar(scopes.size()+1);
        scopes[c]=new scope;
        return c;
    }
    scope* root;
    map<char*,map<string,string>> temp;
    map<char*,map<string,vector<string>>> temp_list;
    char* new_temp(){
        char* c= numtochar(temp.size()+1);
        temp[c];
        return c;
    }
    char* new_temp_list(){
        char* c= numtochar(temp_list.size()+1);
        temp_list[c];
        return c;
    }
    map<char*,Type*> type;
    map<char*,vector<Type*>> type_list;
    char * new_type(){
        char* c= numtochar(type.size()+1);
        type[c]=new Type;
        return c;
    }
    char * new_type_list(){
        char* c= numtochar(type_list.size()+1);
        type_list[c];
        return c;
    }
%}
%union{
    char* val;
}

/* data types */
%start COMPILATIONUNIT
%type<val>  ADDITIONALBOUND ADDITIVEEXPRESSION ANDEXPRESSION ARGUMENTLIST ARRAYACCESS ARRAYCREATIONEXPRESSION ARRAYINITIALIZER ARRAYINITIALIZER1 ASSERTSTATEMENT ASSIGNMENT ASSIGNMENTEXPRESSION ASSIGNMENTOPERATOR BASICFORSTATEMENT BASICFORSTATEMENTNOSHORTIF BLOCK BLOCKSTATEMENT BLOCKSTATEMENTS BREAKSTATEMENT CLASSBODY CLASSBODYDECLARATION CLASSBODYDECLARATIONS CLASSDECLARATION CLASSEXTENDS CLASSIMPLEMENTS CLASSINSTANCECREATIONEXPRESSION CLASSLITERAL CLASSMEMBERDECLARATION CLASSORINTERFACETYPE CLASSORINTERFACETYPETOINSTANTIATE CLASSPERMITS CLASSTYPE CLASSTYPE1 COMPILATIONUNIT CONDITIONALANDEXPRESSION CONDITIONALEXPRESSION CONDITIONALOREXPRESSION CONSTRUCTORBODY CONSTRUCTORDECLARATION CONSTRUCTORDECLARATOR CONTINUESTATEMENT DIMEXPR DIMEXPRS DIMS EMPTYSTATEMENT ENHANCEDFORSTATEMENT ENHANCEDFORSTATEMENTNOSHORTIF EQUALITYEXPRESSION EXCEPTIONTYPE EXCEPTIONTYPELIST EXCLUSIVEOREXPRESSION EXPLICITCONSTRUCTORINVOCATION EXPRESSION EXPRESSIONNAME EXPRESSIONSTATEMENT FIELDACCESS FIELDDECLARATION FIELDMODIFIERS FLOATINGTYPE FORINIT FORMALPARAMETER FORMALPARAMETERLIST FORSTATEMENT FORSTATEMENTNOSHORTIF FORUPDATE IFTHENELSESTATEMENT IFTHENELSESTATEMENTNOSHORTIF IFTHENSTATEMENT INCLUSIVEOREXPRESSION INSTANCEINITIALIZER INSTANCEOFEXPRESSION INTEGRALTYPE INTERFACETYPE INTERFACETYPELIST LABELEDSTATEMENT LABELEDSTATEMENTNOSHORTIF LEFTHANDSIDE LITERAL LOCALCLASSORINTERFACEDECLARATION LOCALVARIABLEDECLARATION LOCALVARIABLEDECLARATIONSTATEMENT LOCALVARIABLETYPE METHODBODY METHODDECLARATION METHODDECLARATOR METHODHEADER METHODINVOCATION METHODMODIFIERS METHODNAME METHODREFERENCE MULTIPLICATIVEEXPRESSION NORMALCLASSDECLARATION NUMERICTYPE ORDINARYCOMPILATIONUNIT POSTDECREMENTEXPRESSION POSTFIXEXPRESSION POSTINCREMENTEXPRESSION PREDECREMENTEXPRESSION PREINCREMENTEXPRESSION PRIMARY PRIMARYNONEWARRAY PRIMITIVETYPE RECEIVERPARAMETER REFERENCETYPE RELATIONALEXPRESSION RETURNSTATEMENT SHIFTEXPRESSION SIMPLETYPENAME SQUARESTAR STATEMENT STATEMENTEXPRESSION STATEMENTEXPRESSIONLIST STATEMENTNOSHORTIF STATEMENTWITHOUTTRAILINGSUBSTATEMENT STATICINITIALIZER SUPER1 SUPER2 SUPER3 THROWS2 THROWSTATEMENT TOPLEVELCLASSORINTERFACEDECLARATION TYPE TYPEARGUMENT TYPEARGUMENTLIST TYPEARGUMENTS TYPEBOUND TYPENAMES TYPEPARAMETER TYPEPARAMETERLIST TYPEPARAMETERS UNARYEXPRESSION UNARYEXPRESSIONNOTPLUSMINUS UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION VARIABLEARITYPARAMETER VARIABLEDECLARATOR VARIABLEDECLARATORID VARIABLEDECLARATORLIST VARIABLEINITIALIZER VARIABLEINITIALIZERLIST WHILESTATEMENT WHILESTATEMENTNOSHORTIF WILDCARD WILDCARDBOUNDS YIELDSTATEMENT IMPORTDECLARATION NORMALINTERFACEDECLARATION INTERFACEBODY INTERFACEMEMBERDECLARATION INTERFACEDECLARATION INTERFACEMEMBERDECLARATIONS OPENCURLY CLOSECURLY
%token<val> BOOLEAN BYTE SHORT INT LONG CHAR FLOAT DOUBLE 

/* Separators */
%token<val> COMMA QUESTIONMARK SEMICOLON  OPENCURLY1 CLOSECURLY1 ANGULARLEFT ANGULARRIGHT OPENSQUARE CLOSESQUARE OPENPARAN CLOSEPARAN DOUBLECOLON TRIPLEDOT WS AT OVERRIDE

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
%%



COMPILATIONUNIT     :   EOFF  {return 0;}
                    |   ORDINARYCOMPILATIONUNIT EOFF {root=scopes[$1]; return 0;}
                    
TYPE    :   PRIMITIVETYPE {$$=$1;}
            |   REFERENCETYPE {$$=$1;}

PRIMITIVETYPE   :   NUMERICTYPE {$$=$1;}
                |   BOOLEAN {}

NUMERICTYPE     :   INTEGRALTYPE {$$=$1;}
                |   FLOATINGTYPE {$$=$1;}

INTEGRALTYPE    : BYTE 
                | SHORT  
                | INT 
                | LONG 
                | CHAR 

FLOATINGTYPE    :   FLOAT 
                |   DOUBLE 
/* INTEGRALTYPE    : BYTE {$$=new_scope(); scopes[$$]["type"]="byte";}
                | SHORT  {$$=new_scope(); scopes[$$]["type"]="short";}
                | INT {$$=new_scope(); scopes[$$]["type"]="int";}
                | LONG {$$=new_scope(); scopes[$$]["type"]="long";}
                | CHAR {$$=new_scope(); scopes[$$]["type"]="char";}

FLOATINGTYPE    :   FLOAT {$$=new_scope(); scopes[$$]["type"]="float";}
                |   DOUBLE {$$=new_scope(); scopes[$$]["type"]="double";} */

REFERENCETYPE   :   CLASSORINTERFACETYPE {$$=$1;}

CLASSORINTERFACETYPE    :   CLASSTYPE {$$=$1;}

CLASSTYPE   :   CLASSTYPE1 {$$=$1;}

CLASSTYPE1  :   IDENTIFIER {$$=$1;}

TYPEARGUMENTS   :   ANGULARLEFT TYPEARGUMENTLIST  ANGULARRIGHT 

TYPEARGUMENTLIST    :   TYPEARGUMENT {}
                    |   TYPEARGUMENTLIST COMMA TYPEARGUMENT {}

TYPEARGUMENT    :   REFERENCETYPE {$$=$1;}
                |   WILDCARD {$$=$1;}

WILDCARD    :   QUESTIONMARK 
            |   QUESTIONMARK WILDCARDBOUNDS 

WILDCARDBOUNDS  :   EXTENDS REFERENCETYPE
                |   SUPER REFERENCETYPE 


INTERFACETYPE   :   CLASSTYPE {$$=$1;}

DIMS    :   OPENSQUARE CLOSESQUARE 
        |   DIMS OPENSQUARE CLOSESQUARE {}

METHODNAME  :   IDENTIFIER {}

EXPRESSIONNAME   :   IDENTIFIER DOT IDENTIFIER 
                |   EXPRESSIONNAME DOT IDENTIFIER


ORDINARYCOMPILATIONUNIT :   TOPLEVELCLASSORINTERFACEDECLARATION  {$$=new_scope();add_child($$,$1);}
                        |   ORDINARYCOMPILATIONUNIT TOPLEVELCLASSORINTERFACEDECLARATION {$$=$1;add_child($$,$1);}

TOPLEVELCLASSORINTERFACEDECLARATION :   CLASSDECLARATION {$$=$1;}
                                    |   INTERFACEDECLARATION {$$=$1;}
                                    |   SEMICOLON  {$$=$1;}
                                    |   IMPORTDECLARATION TOPLEVELCLASSORINTERFACEDECLARATION

IMPORTDECLARATION   :   IMPORT EXPRESSIONNAME SEMICOLON
                    |   IMPORT EXPRESSIONNAME DOT MULTIPLY SEMICOLON
                    |   IMPORT STATIC EXPRESSIONNAME SEMICOLON
                    |   IMPORT STATIC EXPRESSIONNAME DOT MULTIPLY SEMICOLON

CLASSDECLARATION    :   NORMALCLASSDECLARATION {$$=$1;}
                    

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
                            | CLASS IDENTIFIER CLASSEXTENDS CLASSBODY  {
                                $$=$4;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($2);
                                scopes[$$]->class_meta.inherited_from=temp[$3]["extend"];    
                            }
                            | CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | CLASS IDENTIFIER CLASSBODY{
                                $$=$3;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($2);
                            }
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
                            | SUPER1 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY//
                            {
                                $$=$5;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($3);
                                scopes[$$]->class_meta.inherited_from=temp[$4]["extend"];
                                auto& e=temp_list[$1]["modifiers"];
                                for(auto e1:e ){
                                    scopes[$$]->class_meta.modifiers[e1]++;
                                    if(scopes[$$]->class_meta.modifiers[e1]>1){
                                        yyerror("multiple same type access modifier ");
                                    }
                                }
                                
                            }
                            | SUPER1 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | SUPER1 CLASS IDENTIFIER CLASSBODY//
                            {
                                $$=$4;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($3);
                                auto& e=temp_list[$1]["modifiers"];
                                for(auto e1:e ){
                                    scopes[$$]->class_meta.modifiers[e1]++;
                                    if(scopes[$$]->class_meta.modifiers[e1]>1){
                                        yyerror("multiple same type access modifier ");
                                    }
                                }
                                
                            }
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
                            | SUPER2 CLASS IDENTIFIER CLASSEXTENDS CLASSBODY {
                                $$=$5;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($3);
                                scopes[$$]->class_meta.inherited_from=temp[$4]["extend"];
                                auto& e=temp_list[$1]["modifiers"];
                                for(auto e1:e ){
                                    scopes[$$]->class_meta.modifiers[e1]++;
                                    if(scopes[$$]->class_meta.modifiers[e1]>1){
                                        yyerror("multiple same type access modifier ");
                                    }
                                }
                                
                            }
                            | SUPER2 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | SUPER2 CLASS IDENTIFIER CLASSBODY {
                                $$=$4;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($3);
                                auto& e=temp_list[$1]["modifiers"];
                                for(auto e1:e ){
                                    scopes[$$]->class_meta.modifiers[e1]++;
                                    if(scopes[$$]->class_meta.modifiers[e1]>1){
                                        yyerror("multiple same type access modifier ");
                                    }
                                }
                                
                            }
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
                            {
                                $$=$5;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($3);
                                scopes[$$]->class_meta.inherited_from=temp[$4]["extend"];
                                auto& e=temp_list[$1]["modifiers"];
                                for(auto e1:e ){
                                    scopes[$$]->class_meta.modifiers[e1]++;
                                    if(scopes[$$]->class_meta.modifiers[e1]>1){
                                        yyerror("multiple same type access modifier ");
                                    }
                                }
                                
                            }
                            | SUPER3 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSIMPLEMENTS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSPERMITS CLASSBODY
                            | SUPER3 CLASS IDENTIFIER CLASSBODY {
                                $$=$4;
                                scopes[$$]->type="class";
                                scopes[$$]->class_meta.name=chartostring($3);
                                auto& e=temp_list[$1]["modifiers"];
                                for(auto e1:e ){
                                    scopes[$$]->class_meta.modifiers[e1]++;
                                    if(scopes[$$]->class_meta.modifiers[e1]>1){
                                        yyerror("multiple same type access modifier ");
                                    }
                                }
                                
                            }


NORMALINTERFACEDECLARATION  : INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS INTERFACEBODY
                            | INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS INTERFACEBODY
                            | INTERFACE IDENTIFIER TYPEPARAMETERS CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER TYPEPARAMETERS INTERFACEBODY
                            | INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | INTERFACE IDENTIFIER CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER CLASSEXTENDS INTERFACEBODY
                            | INTERFACE IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER CLASSIMPLEMENTS INTERFACEBODY
                            | INTERFACE IDENTIFIER CLASSPERMITS INTERFACEBODY
                            | INTERFACE IDENTIFIER INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER TYPEPARAMETERS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER CLASSEXTENDS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER CLASSPERMITS INTERFACEBODY
                            | SUPER1 INTERFACE IDENTIFIER INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER TYPEPARAMETERS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER CLASSEXTENDS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER CLASSPERMITS INTERFACEBODY
                            | SUPER2 INTERFACE IDENTIFIER INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSEXTENDS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER TYPEPARAMETERS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER CLASSEXTENDS CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER CLASSEXTENDS CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER CLASSEXTENDS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER CLASSIMPLEMENTS CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER CLASSIMPLEMENTS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER CLASSPERMITS INTERFACEBODY
                            | SUPER3 INTERFACE IDENTIFIER INTERFACEBODY


OPENCURLY : OPENCURLY1   {}              
CLOSECURLY : CLOSECURLY1  {}            

INTERFACEBODY   :  OPENCURLY CLOSECURLY 
            |   OPENCURLY INTERFACEMEMBERDECLARATIONS CLOSECURLY

INTERFACEMEMBERDECLARATIONS   :   INTERFACEMEMBERDECLARATION
                        |   INTERFACEMEMBERDECLARATIONS INTERFACEMEMBERDECLARATION

INTERFACEMEMBERDECLARATION  :   METHODDECLARATION 
                            |   DEFAULT METHODHEADER METHODBODY 
                            |   SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON
                            |   CLASSDECLARATION
                            |   SEMICOLON

INTERFACEDECLARATION    :   NORMALINTERFACEDECLARATION            


TYPEPARAMETERS  :   ANGULARLEFT TYPEPARAMETERLIST ANGULARRIGHT

TYPEPARAMETERLIST   :   TYPEPARAMETER 
                    |   TYPEPARAMETERLIST COMMA TYPEPARAMETER 

TYPEPARAMETER   :   IDENTIFIER TYPEBOUND
                |   IDENTIFIER 


TYPEBOUND   :  EXTENDS IDENTIFIER 
            |   EXTENDS CLASSORINTERFACETYPE ADDITIONALBOUND

ADDITIONALBOUND :   AND INTERFACETYPE
                |   ADDITIONALBOUND AND INTERFACETYPE

CLASSEXTENDS    :   EXTENDS CLASSTYPE {$$=new_temp();temp[$$]["extend"]=chartostring($2);}

CLASSIMPLEMENTS :    IMPLEMENTS INTERFACETYPELIST

INTERFACETYPELIST   :   INTERFACETYPE
                    |   INTERFACETYPELIST COMMA INTERFACETYPE

CLASSPERMITS    :   PERMITS TYPENAMES

TYPENAMES   :   IDENTIFIER {}
            |   TYPENAMES COMMA IDENTIFIER {}

CLASSBODY   :  OPENCURLY CLOSECURLY {$$=new_scope();}
            |   OPENCURLY CLASSBODYDECLARATIONS CLOSECURLY {$$=$2;} 

CLASSBODYDECLARATIONS   :   CLASSBODYDECLARATION 
                            {
                                $$=new_scope();
                                add_child($$,$1);
                                if(scopes[$1]->type=="field"){
                                    for(auto e:scopes[$1]->field_meta ){
                                        scopes[$$]->class_meta.fields.push_back(e);
                                    }
                                }
                                else if(scopes[$1]->type=="method")
                                {
                                    scopes[$$]->class_meta.methods.push_back(scopes[$1]->method_meta);
                                }
                            }
                        |   CLASSBODYDECLARATIONS CLASSBODYDECLARATION
                            {
                                $$=$1;
                                add_child($$,$2);
                                if(scopes[$2]->type=="field"){
                                    for(auto e:scopes[$1]->field_meta ){
                                        scopes[$$]->class_meta.fields.push_back(e);
                                    }
                                }
                                else if(scopes[$2]->type=="method")
                                {
                                    scopes[$$]->class_meta.methods.push_back(scopes[$2]->method_meta);
                                }
                            }

CLASSBODYDECLARATION    :   CLASSMEMBERDECLARATION {$$=$1;}
                        |   INSTANCEINITIALIZER {$$=$1;}
                        |   STATICINITIALIZER {$$=$1;}
                        |   CONSTRUCTORDECLARATION {$$=$1;}

CLASSMEMBERDECLARATION:     FIELDDECLARATION {$$=$1;}
                            |   METHODDECLARATION {$$=$1;}
                            |   CLASSDECLARATION 
                            |   SEMICOLON {$$==new_scope();}
                            |   INTERFACEDECLARATION 

FIELDDECLARATION    :   FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON {
                            $$=new_scope();
                            scopes[$$]->type="field";
                            for(auto e: type_list[$3]){
                                field_metadata c; 
                                auto e1=e;
                                while(e1->is_array!=0){
                                    e1=e1->next;
                                }
                                e1->type= temp[$2]["type"];
                                c.name=e->name;
                                c.type=*e;
                                for(auto e1: temp_list[$1]["modifiers"]){
                                    c.modifiers[e1]++;
                                    if(c.modifiers[e1]>1){
                                        yyerror("multiple same type modifier");
                                    }
                                }

                                scopes[$$]->field_meta.push_back(c);
                            }
                            
                        }
                    |   SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON {
                            $$=new_scope();
                            scopes[$$]->type="field";
                            for(auto e: type_list[$3]){
                                field_metadata c; 
                                auto e1=e;
                                while(e1->is_array!=0){
                                    e1=e1->next;
                                }
                                e1->type= temp[$2]["type"];
                                c.name=e->name;
                                c.type=*e;
                                for(auto e1: temp_list[$1]["modifiers"]){
                                    c.modifiers[e1]++;
                                    if(c.modifiers[e1]>1){
                                        yyerror("multiple same type modifier");
                                    }
                                }

                                scopes[$$]->field_meta.push_back(c);
                            }
                            
                        }
                    |   SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON {
                            $$=new_scope();
                            scopes[$$]->type="field";
                            for(auto e: type_list[$3]){
                                field_metadata c; 
                                auto e1=e;
                                while(e1->is_array!=0){
                                    e1=e1->next;
                                }
                                e1->type= temp[$2]["type"];
                                c.name=e->name;
                                c.type=*e;
                                for(auto e1: temp_list[$1]["modifiers"]){
                                    c.modifiers[e1]++;
                                    if(c.modifiers[e1]>1){
                                        yyerror("multiple same type modifier");
                                    }
                                }

                                scopes[$$]->field_meta.push_back(c);
                            }
                            
                        }
                    |   TYPE VARIABLEDECLARATORLIST SEMICOLON {
                            $$=new_scope();
                            scopes[$$]->type="field";
                            for(auto e: type_list[$2]){
                                field_metadata c; 
                                auto e1=e;
                                while(e1->is_array!=0){
                                    e1=e1->next;
                                }
                                e1->type= temp[$1]["type"];
                                c.name=e->name;
                                c.type=*e;
                               

                                scopes[$$]->field_meta.push_back(c);
                            }
                        }

VARIABLEDECLARATORLIST  :   VARIABLEDECLARATOR {$$ = new_type_list(); type_list[$$].push_back(type[$1]);}
                        |   VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR {$$ = $1; type_list[$$].push_back(type[$3]);}

VARIABLEDECLARATOR  :   VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER {$$=$1;}
                    |   VARIABLEDECLARATORID {$$=$1;}

VARIABLEDECLARATORID    :   IDENTIFIER {$$=new_type(); type[$$]->name=chartostring($1);}
                        |   IDENTIFIER DIMS {$$=$2; type[$$]->name=chartostring($1);}

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
  
                |   CLASSTYPE DOUBLECOLON IDENTIFIER
                |	PRIMARY DOUBLECOLON IDENTIFIER

                |	SUPER DOUBLECOLON IDENTIFIER
                |	IDENTIFIER DOT SUPER DOUBLECOLON IDENTIFIER
                |	CLASSTYPE DOUBLECOLON NEW

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

DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE 

VARIABLEINITIALIZERLIST :   VARIABLEINITIALIZER
                        |   VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER




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


METHODDECLARATION:  METHODHEADER METHODBODY
                    |   SUPER1 METHODHEADER METHODBODY
                    |   SUPER2 METHODHEADER METHODBODY
                    |   SUPER3 METHODHEADER METHODBODY
                    |   METHODMODIFIERS METHODHEADER METHODBODY
                    | AT OVERRIDE METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER1 METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER2 METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER3 METHODHEADER METHODBODY  
                    | AT OVERRIDE METHODMODIFIERS METHODHEADER METHODBODY  


METHODHEADER: TYPE METHODDECLARATOR THROWS2
            |   TYPE METHODDECLARATOR 
             |	TYPEPARAMETERS TYPE METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS TYPE METHODDECLARATOR 
             |  VOID METHODDECLARATOR THROWS2
            |   VOID METHODDECLARATOR 
             |	TYPEPARAMETERS VOID METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS VOID METHODDECLARATOR 


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
                |   FINAL TYPE VARIABLEDECLARATORID


VARIABLEARITYPARAMETER  :  TYPE TRIPLEDOT IDENTIFIER
                        |   FINAL TYPE TRIPLEDOT IDENTIFIER


METHODBODY: BLOCK {$$=$1;}
           |	SEMICOLON {$$=new_scope();}

INSTANCEINITIALIZER: BLOCK {$$=$1;}

STATICINITIALIZER: STATIC BLOCK {$$=$1;scopes[$$]->is_static=1;}

BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY
    |   OPENCURLY  CLOSECURLY

BLOCKSTATEMENTS: BLOCKSTATEMENT 
                |  BLOCKSTATEMENTS BLOCKSTATEMENT 

BLOCKSTATEMENT: LOCALCLASSORINTERFACEDECLARATION
               |	LOCALVARIABLEDECLARATIONSTATEMENT
               |	STATEMENT
 
LOCALCLASSORINTERFACEDECLARATION: CLASSDECLARATION

LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON

LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST
                        |   LOCALVARIABLETYPE VARIABLEDECLARATORLIST

LOCALVARIABLETYPE: TYPE
                  |	VAR


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

IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF

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

CONSTRUCTORDECLARATION:     CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY{
                            $$=$3;
                            scopes[$$]->type="method";
                            scopes[$$]->method_meta.is_constructor=1;
                            scopes[$$]->method_meta.name=temp[$1]["name"];
                            scopes[$$]->method_meta.args=scopes[stringtochar(temp[$1]["formalparameterlist"])]->method_meta.args;

                        }
                        |   CONSTRUCTORDECLARATOR CONSTRUCTORBODY
                        {
                            $$=$2;
                            scopes[$$]->type="method";
                            scopes[$$]->method_meta.is_constructor=1;
                            scopes[$$]->method_meta.name=temp[$1]["name"];
                            scopes[$$]->method_meta.args=scopes[stringtochar(temp[$1]["formalparameterlist"])]->method_meta.args;

                        }
                        |   SUPER1 CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY  
                        {
                            $$=$4;
                            scopes[$$]->type="method";
                            scopes[$$]->method_meta.is_constructor=1;
                            scopes[$$]->method_meta.name=temp[$2]["name"];
                            scopes[$$]->method_meta.args=scopes[stringtochar(temp[$2]["formalparameterlist"])]->method_meta.args;
                            for(auto e1: temp_list[$1]["modifiers"]){
                                scopes[$$]->method_meta.modifiers[e1]++;
                                if(scopes[$$]->method_meta.modifiers[e1]>1){
                                    yyerror("multiple same type modifier");
                                }
                            }

                        }
                        |   SUPER1 CONSTRUCTORDECLARATOR CONSTRUCTORBODY 
                        {
                            $$=$3;
                            scopes[$$]->type="method";
                            scopes[$$]->method_meta.is_constructor=1;
                            scopes[$$]->method_meta.name=temp[$2]["name"];
                            scopes[$$]->method_meta.args=scopes[stringtochar(temp[$2]["formalparameterlist"])]->method_meta.args;
                            for(auto e1: temp_list[$1]["modifiers"]){
                                scopes[$$]->method_meta.modifiers[e1]++;
                                if(scopes[$$]->method_meta.modifiers[e1]>1){
                                    yyerror("multiple same type modifier");
                                }
                            }
                        }


CONSTRUCTORDECLARATOR: SIMPLETYPENAME OPENPARAN  CLOSEPARAN {
                        $$=new_temp(); 
                        temp[$$]["constructor"]="1"; 
                        temp[$$]["name"]=chartostring($1);
                        }
                    |   SIMPLETYPENAME OPENPARAN FORMALPARAMETERLIST CLOSEPARAN {
                        $$=new_temp(); 
                        temp[$$]["constructor"]="1"; 
                        temp[$$]["name"]=chartostring($1);
                        temp[$$]["formalparameterlist"]=chartostring($3);
                        }
                    |   SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA CLOSEPARAN {
                        $$=new_temp(); 
                        temp[$$]["constructor"]="1"; 
                        temp[$$]["name"]=chartostring($1);
                        temp[$$]["receiverparameter"]=chartostring($3);
                        }
                    |   SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA FORMALPARAMETERLIST CLOSEPARAN {
                        $$=new_temp(); 
                        temp[$$]["constructor"]="1"; 
                        temp[$$]["name"]=chartostring($1);
                        temp[$$]["formalparameterlist"]=chartostring($5);
                        temp[$$]["receiverparameter"]=chartostring($3);
                        }
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN  CLOSEPARAN
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN FORMALPARAMETERLIST CLOSEPARAN
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA CLOSEPARAN
                    |   TYPEPARAMETERS SIMPLETYPENAME OPENPARAN RECEIVERPARAMETER COMMA FORMALPARAMETERLIST CLOSEPARAN

SIMPLETYPENAME: IDENTIFIER {$$=$1;}

CONSTRUCTORBODY: OPENCURLY EXPLICITCONSTRUCTORINVOCATION BLOCKSTATEMENTS CLOSECURLY {$$=$3;}
                |   OPENCURLY EXPLICITCONSTRUCTORINVOCATION CLOSECURLY {$$=new_scope();}
                |   OPENCURLY BLOCKSTATEMENTS CLOSECURLY {$$=$2;}
                |   OPENCURLY  CLOSECURLY {$$=new_scope();}

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
                            |   PRIMARY DOT SUPER OPENPARAN CLOSEPARAN SEMICOLON
                            |   PRIMARY DOT SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON
                            |   PRIMARY DOT TYPEARGUMENTS SUPER OPENPARAN  CLOSEPARAN SEMICOLON
                            |   PRIMARY DOT TYPEARGUMENTS SUPER OPENPARAN ARGUMENTLIST CLOSEPARAN SEMICOLON

SUPER1 : PUBLIC {$$=new_temp_list(); temp_list[$$]["modifiers"].push_back(chartostring($1));}
        | PRIVATE {$$=new_temp_list(); temp_list[$$]["modifiers"].push_back(chartostring($1));}
        | PROTECTED {$$=new_temp_list(); temp_list[$$]["modifiers"].push_back(chartostring($1));}
        | SUPER1 PUBLIC {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER1 PRIVATE {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER1 PROTECTED {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
    
SUPER2 : STATIC {$$=new_temp_list(); temp_list[$$]["modifiers"].push_back(chartostring($1));}
        | FINAL {$$=new_temp_list(); temp_list[$$]["modifiers"].push_back(chartostring($1));}
        | SUPER1 STATIC {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER1 FINAL {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER2 STATIC {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER2 FINAL {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER2 PUBLIC {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER2 PRIVATE {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER2 PROTECTED {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }

SUPER3 : ABSTRACT {$$=new_temp_list(); temp_list[$$]["modifiers"].push_back(chartostring($1));}
        | STRICTFP {$$=new_temp_list(); temp_list[$$]["modifiers"].push_back(chartostring($1));}
        | SUPER2 ABSTRACT {$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER2 STRICTFP{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER3 ABSTRACT{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER3 STRICTFP{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER3 PUBLIC{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER3 PRIVATE{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER3 PROTECTED{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER3 STATIC{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
        | SUPER3 FINAL{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }

FIELDMODIFIERS: SUPER3 TRANSIENT{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            |   SUPER3 VOLATILE{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            |  FIELDMODIFIERS TRANSIENT{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            |  FIELDMODIFIERS VOLATILE{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            | FIELDMODIFIERS PUBLIC{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            | FIELDMODIFIERS PRIVATE{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            | FIELDMODIFIERS PROTECTED{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            | FIELDMODIFIERS STATIC{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }
            | FIELDMODIFIERS FINAL{$$=$1;temp_list[$$]["modifiers"].push_back(chartostring($2)); }


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


int main(int argc, char** argv){
    yyparse();
    /* cout << "digraph ASTVisual {\n ordering = out ;\n"; */
    /* for(auto e: scopess){
        string s;
        
         for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'  ){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        cout<<e.num<<" [ scopes=\""<<s<<"\"]\n";
    }
    for(auto e: edges){
        string s;

        for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        cout<<e.a<< " -> "<<e.b << "[ scopes=\""<<s<<"\"]\n";
    }
    cout << "  }\n"; */

}
