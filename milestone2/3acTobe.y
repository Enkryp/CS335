%{
    // lineno
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
    #include"scope.h"
    #include"metadata.h"
    int num_var = 0, num_address=0;
    vector<string> code;
    scope* root=new scope;
    map<char*, map<string,string>> label;
    map<char*, map<string,vector<string>>> lists;
    scope * curr=root;
    
    char* new_label(){
        return numtochar(label.size()+1);
    }

    char* new_address(){
        return numtochar(num_address++);
    }

    string new_var(){
        return "t"+numtostring(num_var++);
    }

    void backpatch(vector<int> &lines, int goto){
        for(int i=0;i<lines.size();i++){
            code[lines[i]] += " "+numtostring(goto);
        }
        lines.clear();
    }

    vector<int> merge(vector<int> &v1, vector<int> &v2){
        vector<int> v3;
        for(int i=0;i<v1.size();i++)
        v3.push_back(v1[i]);
        for(int i=0;i<v2.size();i++)
        v3.push_back(v2[i]);
        v1.clear();
        v2.clear();
        return v3;
    }

    string give_type(int curr){
        return numtostring(symtable[curr]["type"]);
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
                    |   ORDINARYCOMPILATIONUNIT EOFF {return 0;}
                    
TYPE    :   PRIMITIVETYPE {$$=$1;}
            |   REFERENCETYPE {$$=$1;}

PRIMITIVETYPE   :   NUMERICTYPE {$$=$1;}
                |   BOOLEAN {$$=new_label(); label[$$]["type"]="bool";}

NUMERICTYPE     :   INTEGRALTYPE {$$=$1;}
                |   FLOATINGTYPE {$$=$1;}

INTEGRALTYPE    : BYTE {$$=new_label(); label[$$]["type"]="byte";}
                | SHORT  {$$=new_label(); label[$$]["type"]="short";}
                | INT {$$=new_label(); label[$$]["type"]="int";}
                | LONG {$$=new_label(); label[$$]["type"]="long";}
                | CHAR {$$=new_label(); label[$$]["type"]="char";}

FLOATINGTYPE    :   FLOAT {$$=new_label(); label[$$]["type"]="float";}
                |   DOUBLE {$$=new_label(); label[$$]["type"]="double";}

REFERENCETYPE   :   CLASSORINTERFACETYPE {$$=$1;}

CLASSORINTERFACETYPE    :   CLASSTYPE {$$=$1;}

CLASSTYPE   :   CLASSTYPE1 {$$=$1;}

CLASSTYPE1  :   IDENTIFIER {$$=new_label(); label[$$]["id"]=chartostring($1);}

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

DIMS    :   OPENSQUARE CLOSESQUARE {$$=new_label(); label[$$]["dims"]=numtochar(1);}
        |   DIMS OPENSQUARE CLOSESQUARE {$$=$1;label[$$]["dims"]=numtochar(chartonum(label[$$]["dims"])+1);}

METHODNAME  :   IDENTIFIER {    $$ = new_address();
                                int curr1 = chartonum($$);
                                ds[curr]["type"] = get_symbol_table(chartostring($1),"type");
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr]["var"] = chartostring($1);
}

EXPRESSIONNAME   :   IDENTIFIER DOT IDENTIFIER {    $$ = new_address();
                                                    int curr = chartonum($$);
                                                    string  name = chartostring($1), name2 = chartostring($3);
                                                    ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                    ds[curr]["var"] = name+"."+name2;
                                                    // ds[curr]["lineno"] = get_symbol_table(name,"lineno");
}
                |   EXPRESSIONNAME DOT IDENTIFIER


ORDINARYCOMPILATIONUNIT :   TOPLEVELCLASSORINTERFACEDECLARATION 
                        |   ORDINARYCOMPILATIONUNIT TOPLEVELCLASSORINTERFACEDECLARATION

TOPLEVELCLASSORINTERFACEDECLARATION :   CLASSDECLARATION
                                    |   INTERFACEDECLARATION
                                    |   SEMICOLON 
                                    |   IMPORTDECLARATION TOPLEVELCLASSORINTERFACEDECLARATION

IMPORTDECLARATION   :   IMPORT EXPRESSIONNAME SEMICOLON
                    |   IMPORT EXPRESSIONNAME DOT MULTIPLY SEMICOLON
                    |   IMPORT STATIC EXPRESSIONNAME SEMICOLON
                    |   IMPORT STATIC EXPRESSIONNAME DOT MULTIPLY SEMICOLON

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


OPENCURLY : OPENCURLY1   {
    scope* temp=new scope();
    curr->child.push_back(temp);
    temp->parent=curr;
    curr=temp;

}              
CLOSECURLY : CLOSECURLY1  {curr=curr->parent;}            

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

TYPEPARAMETERLIST   :   TYPEPARAMETER {$$=new_label(); label[$$][chartostring($1)]=chartostring($1);}
                    |   TYPEPARAMETERLIST COMMA TYPEPARAMETER {$$=$1; label[$$][chartostring($3)]=chartostring($3);}

TYPEPARAMETER   :   IDENTIFIER TYPEBOUND
                |   IDENTIFIER {$$=new_label();label[$$]["id"]=$1;}


TYPEBOUND   :  EXTENDS IDENTIFIER 
            |   EXTENDS CLASSORINTERFACETYPE ADDITIONALBOUND

ADDITIONALBOUND :   AND INTERFACETYPE
                |   ADDITIONALBOUND AND INTERFACETYPE

CLASSEXTENDS    :   EXTENDS CLASSTYPE

CLASSIMPLEMENTS :    IMPLEMENTS INTERFACETYPELIST

INTERFACETYPELIST   :   INTERFACETYPE
                    |   INTERFACETYPELIST COMMA INTERFACETYPE

CLASSPERMITS    :   PERMITS TYPENAMES

TYPENAMES   :   IDENTIFIER {$$=new_label(); label[$$][chartostring($1)]=chartostring($1);}
            |   TYPENAMES COMMA IDENTIFIER {$$=$1; label[$$][chartostring($3)]=chartostring($3);}

CLASSBODY   :  OPENCURLY CLOSECURLY 
            |   OPENCURLY CLASSBODYDECLARATIONS CLOSECURLY

CLASSBODYDECLARATIONS   :   CLASSBODYDECLARATION
                        |   CLASSBODYDECLARATIONS CLASSBODYDECLARATION

CLASSBODYDECLARATION    :   CLASSMEMBERDECLARATION
                        |   INSTANCEINITIALIZER
                        |   STATICINITIALIZER
                        |   CONSTRUCTORDECLARATION 

CLASSMEMBERDECLARATION:     FIELDDECLARATION    {$$ = $1;}
                            |   METHODDECLARATION   {$$ = $1;}
                            |   CLASSDECLARATION    
                            |   SEMICOLON   
                            |   INTERFACEDECLARATION

FIELDDECLARATION    :   FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON    
                    |   SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON
                    |   SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON
                    |   TYPE VARIABLEDECLARATORLIST SEMICOLON   {   $$ = new_address();
                                                                    int curr1 = chartonum($1), curr2 = chartonum($2), curr = chartonum($$);
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    if(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=ds[curr1]["type"]){
                                                                        error("incompatible declaration");
                                                                    }
                                                                    
                                                                    
                    }



VARIABLEDECLARATORLIST  :   VARIABLEDECLARATOR  {   $$ = new_address();
                                                    int curr = chartonum($$), curr1 = chartonum($1);
                                                    if(ds[curr1].find("start")!=ds[curr1].end()){
                                                        ds[curr]["start"] = ds[curr1]["start"];
                                                        ds[curr]["type"] = ds[curr1]["type"];
                                                    }
                                                    ds[curr]["lineno"] = ds[curr1]["lineno"];
}
                        |   VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR {   $$ = new_address();
                                                    int curr = chartonum($$), curr1 = chartonum($1),curr3 = chartonum($3);
                                                    if(ds[curr1].find("start")!=ds[curr1].end()){
                                                        ds[curr]["start"] = ds[curr1]["start"];
                                                        ds[curr]["type"] = ds[curr1]["type"];
                                                    }
                                                    else if(ds[curr3].find("start")!=ds[curr3].end()){
                                                        ds[curr]["start"] = ds[curr3]["start"];
                                                        ds[curr]["type"] = ds[curr1]["type"];
                                                    }
                                                    ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                    if(ds[curr3].find("type")!=ds[curr3].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"])
                                                    error("Incompatible types");

}

VARIABLEDECLARATOR  :   VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER {   $$ = new_address();
                                                                            int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                            ds[curr]["start"] = code.size();
                                                                            ds[curr]["type"] = ds[curr3]["type"];
                                                                            ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                            code.push_back(ds[curr1]["var"]+"="+ds[curr3]["var"]);
}
                    |   VARIABLEDECLARATORID

VARIABLEDECLARATORID    :   IDENTIFIER {    $$ = new_address();
                                            int curr1 = chartonum($$);
                                            ds[curr]["type"] = get_symbol_table(chartostring($1),"type");
                                            ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring($1);
}
                        |   IDENTIFIER DIMS

VARIABLEINITIALIZER :    EXPRESSION {$$ = $1;}
                    |   ARRAYINITIALIZER    {$$ = $1;}

EXPRESSION  :  ASSIGNMENTEXPRESSION {$$ = $1;}

ASSIGNMENTEXPRESSION    :   CONDITIONALEXPRESSION   {$$ = $1;}
                        |   ASSIGNMENT {$$ = $1;}

ASSIGNMENT  :   LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION {
    
    // code.pb($1.val + $2.val + $3.val )
    // string t  =new_var();
    // code.pb(t + " = " + $1.val);
    // $$.val = t;
    $$ = $1;
    int curr1 = chartonum($1), curr3 = chartonum($3), curr2 = chartonum($2);
    type_check(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    type_conversion(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    code.push_back(ds[curr1]["var"]+ds[curr2]["op"]+ds[curr3]["var"]);

}

LEFTHANDSIDE    :   EXPRESSIONNAME    {$$ = $1;}
                |   IDENTIFIER {    $$ = new_address();
                                    int curr = chartonum($$);
                                    ds[curr]["type"] = get_symbol_table(chartostring($1),"type");
                                    ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring($1);
                                    /* look here */
                                    ds[curr]["start"] = code.size();
                }
                |   FIELDACCESS {$$ = $1;}
                |   ARRAYACCESS

ASSIGNMENTOPERATOR  :  EQUALS {$$ = new_address();int curr = chartonum($$);
                                ds[curr]["op"] = "=";}
                    |  MULTIPLYEQUALS {$$ = new_address();int curr = chartonum($$);
                                ds[curr]["op"] = "*=";}
                    |   DIVIDEEQUALS {$$ = new_address();int curr = chartonum($$);
                                ds[curr]["op"] = "/=";}
                    |   MODEQUALS {$$ = new_address();int curr = chartonum($$);
                                ds[curr]["op"] = "%=";}
                    |   PLUSEQUALS {$$ = new_address();int curr = chartonum($$);
                                ds[curr]["op"] = "+=";}
                    |   MINUSEQUALS {$$ = new_address();int curr = chartonum($$);
                                ds[curr]["op"] = "-=";}
                    
FIELDACCESS: PRIMARY DOT IDENTIFIER {$$ = new_address();
                                        int curr = chartonum($$), curr1 = chartonum($1);
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]=="YES"){
                                            ds[curr]["var"] = "this."+chartostring($3);
                                        }else error("unexpected type\n");
                                        }
            |	SUPER DOT IDENTIFIER
            |	IDENTIFIER DOT SUPER DOT IDENTIFIER

PRIMARY: PRIMARYNONEWARRAY  {$$ = $1;}
        |	ARRAYCREATIONEXPRESSION {$$ = $1;}

PRIMARYNONEWARRAY: LITERAL  {$$ = $1;}
                  |	CLASSLITERAL    {$$ = $1;}
                  |	THIS    {$$ = new_address();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum($$);
                            ds[curr]["this"] = "YES";}
                  |	IDENTIFIER DOT THIS
                  |	OPENPARAN EXPRESSION CLOSEPARAN {$$ = $2;}
                  |	CLASSINSTANCECREATIONEXPRESSION         
                  |	FIELDACCESS {$$ = $1;}
                  |	ARRAYACCESS {$$.type = "array"; $$.val = $1.val;}
                  |	METHODINVOCATION    {$$ = $1;}
                  |	METHODREFERENCE

LITERAL: INTEGERLITERAL {$$.val = $1; $$.type = "int";}
        |	FLOATINGPOINTLITERAL {$$.val = $1; $$.type = "float";}
        |	BOOLEANLITERAL {$$.val = $1; $$.type = "bool";}
        |	CHARACTERLITERAL {$$.val = $1; $$.type = "char";}
        |	STRINGLITERAL {$$.val = $1; $$.type = "string";}
        |	TEXTBLOCK {$$.val = $1; $$.type = "string";}
        |	NULLLITERAL {$$.val = $1; $$.type = "null"; /* TODO ADD WIDTH MAP*/}

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

ARGUMENTLIST: EXPRESSION    {$$ = $1;}
            |   ARGUMENTLIST COMMA EXPRESSION   {$$ = new_address();
                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds[curr]["var"] = ds[curr1]["var"];
                                                }

METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN   {   $$ = new_address();
                                                        int curr = chartonum($$), curr1 = chartonum($1);
                                                        string name = ds[curr1]["var"];
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = get_symbol_table(name,"type");
                                                        vector<string> types;
                                                        type_check_function(name,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+"= call, "+name);
}
                 |  METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN    {   $$ = new_address();
                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                        string name = ds[curr1]["var"];
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = get_symbol_table(name,"type");
                                                        vector<string> types;
                                                        for(auto i:ds[curr3]["type"])
                                                        types.push_back(i);
                                                        type_check_function(name,types);    // takes in name of function and types of parameters
                                                        for(auto i:ds[curr3]["var"])
                                                        code.push_back("push param "+i);
                                                        ds[curr]["start"] = ds[curr3]["start"];
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+"= call, "+name);
}
                 |	IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  {   /* Method invocation using object?  */
                                                          $$ = new_address();
                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                        string name = ds[curr1]["var"], name2 = ds[curr3]["var"];
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                        vector<string> types;
                                                        type_check_function_obj(name,name2,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+"= call, "+name);
}
                 |	IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN {   /* Method invocation using object?  */
                                                          $$ = new_address();
                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3), curr5 = chartonum($5);
                                                        string name = ds[curr1]["var"], name2 = ds[curr3]["var"];
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                        vector<string> types;
                                                        for(auto i:ds[curr5]["type"])
                                                        types.push_back(i);
                                                        type_check_function_obj(name,name2,types);    // takes in name of function and types of parameters
                                                        for(auto i:ds[curr5]["var"])
                                                        code.push_back("push param "+i);
                                                        ds[curr]["start"] = ds[curr5]["start"];
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+"= call, "+name);
}
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


{}

ARRAYACCESS: EXPRESSIONNAME OPENSQUARE EXPRESSION CLOSESQUARE
            {/*TODO*/}
            |	PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE
            {
                assert()
                
            }
            |	IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE
            {ds[$$][string("base")] = $1; 
            temp ++;
            ds[$$][string("adplace")] = string("t") + to_string(temp);
            ds[$$]["get"] =  ds[$3]["code"] + "\n";
            ds[$$]["get"] +=  ds[$$][string("adplace")] + " = " + ds[$3][string("place")] + " * " + ds[$1][string("width")] + "\n";
            ds[$$]["get"] += $1 + "[" + ds[$$][string("adplace")] + "]\n";
            }

CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  {$$ = $1;}
                      |	CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION {}

CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION   {$$ = $1; }
                        |	CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION   {   $$ = new_address();
                                                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                        backpatch(ds[curr1]["falselist"],ds[curr3]["start"]);
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"||");
                                                                                        ds[curr]["falselist"] = ds[curr3]["falselist"];
                                                                                        ds[curr]["truelist"] = merge(ds[curr1]["truelist"],ds[curr3]["truelist"]);
                                                                                        // backpatch(ds[curr1]["truelist"],code.size());
                                                                                        // backpatch(ds[curr3]["truelist"],code.size());
                                                                                        // ds[curr]["var"] = new_var();
                                                                                        // code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" || "+ds[curr3]["var"]);
                                                                                        // ds[curr]["code"] = ds[curr1]["code"] + "\n" + ds[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}

CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION     {$$ = $1; }
                         |	CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION   {   $$ = new_address();
                                                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                        backpatch(ds[curr1]["truelist"],ds[curr3]["start"]);
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds[curr]["truelist"] = ds[curr3]["truelist"];
                                                                                        ds[curr]["falselist"] = merge(ds[curr1]["falselist"],ds[curr3]["falselist"]);
                                                                                        // ds[curr]["code"] = ds[curr1]["code"] + "\n" + ds[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}

INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION   {$$ = $1;}
                      |	INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  {    $$ = new_address();
                                                                            int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + "|" + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }

EXCLUSIVEOREXPRESSION: ANDEXPRESSION    {$$ = $1; }
                      |	EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION {           $$ = new_address();
                                                                            int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + "^" + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
ANDEXPRESSION: EQUALITYEXPRESSION   {$$ = $1; }
              |	ANDEXPRESSION AND EQUALITYEXPRESSION    {   $$ = new_address();
                                                                            int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + "&" + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }

EQUALITYEXPRESSION: RELATIONALEXPRESSION    {$$ = $1; int curr = chartonum($$);
                                            if(ds[curr].find("truelist")==ds[curr].end()){
                                                ds[curr]["truelist"] = vector<string>();
                                                ds[curr]["falselist"] = vector<string>();
                                            }
                                        }
                   |	EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION    {   $$ = new_address();
                                                                                    int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                    type_check(ds[curr1]["type"],ds[curr3]["type"],"==");
                                                                                    backpatch(ds[curr1]["truelist"],ds[curr3]["start"]);
                                                                                    backpatch(ds[curr1]["falselist"],ds[curr3]["start"]);
                                                                                    backpatch(ds[curr3]["truelist"],code.size());
                                                                                    backpatch(ds[curr3]["falselist"],code.size());
                                                                                    ds[curr]["type"] = "bool";
                                                                                    ds[curr]["var"] = new_var();
                                                                                    code.push_back(ds[curr]["var"])
                                                                                    code.push_back("if "+ds[curr1]["var"]+"=="+ds[curr3]["var"]+" goto ");
                                                                                    ds[curr]["truelist"].push_back(code.size()-1);
                                                                                    code.push_back("goto ");
                                                                                    ds[curr]["falselist"].push_back(code.size()-1);
                                                                                    ds[curr]["start"] = ds[curr1]["start"];
                   }
                   |	EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION       {   
                                                                                    $$ = new_address();
                                                                                    int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                    type_check(ds[curr1]["type"],ds[curr3]["type"],"!=");
                                                                                    backpatch(ds[curr1]["truelist"],ds[curr3]["start"]);
                                                                                    backpatch(ds[curr1]["falselist"],ds[curr3]["start"]);
                                                                                    backpatch(ds[curr3]["truelist"],code.size());
                                                                                    backpatch(ds[curr3]["falselist"],code.size());
                                                                                    ds[curr]["type"] = "bool";
                                                                                    ds[curr]["var"] = new_var();
                                                                                    code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"!="+ds[curr3]["var"])
                                                                                    code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                    ds[curr]["truelist"].push_back(code.size()-1);
                                                                                    code.push_back("goto ");
                                                                                    ds[curr]["falselist"].push_back(code.size()-1);
                                                                                    ds[curr]["start"] = ds[curr1]["start"];
                   }

RELATIONALEXPRESSION: SHIFTEXPRESSION   {   $$ = $1; int curr = chartonum($$);
                                            if(ds[curr].find("truelist")==ds[curr].end()){
                                                ds[curr]["truelist"] = vector<int>();
                                                ds[curr]["falselist"] = vector<int>();
                                            }}
                     |	RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION    {      // IS backpatching for $1 required?
                                                                                $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"<"+ds[curr3]["var"])
                                                                                ds[curr]["falselist"] = vector<int>();
                                                                                ds[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION   {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+">"+ds[curr3]["var"])
                                                                                ds[curr]["falselist"] = vector<int>();
                                                                                ds[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION    {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">=");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+">="+ds[curr3]["var"])
                                                                                ds[curr]["falselist"] = vector<int>();
                                                                                ds[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<=");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"<="+ds[curr3]["var"])
                                                                                ds[curr]["falselist"] = vector<int>();
                                                                                ds[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	INSTANCEOFEXPRESSION

SHIFTEXPRESSION: ADDITIVEEXPRESSION {$$ = $1;}
                |	SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION   {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION     {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }

ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION    {   $$ = $1; }
                   |	ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION    {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" + "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                   |	ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION   {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" - "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }

MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION   {$$ = $1;}
                         |	MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION   {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"*"+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                         |	MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION     {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"/"+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                         |	MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION        {   $$ = new_address();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"%"+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }

UNARYEXPRESSION: PREINCREMENTEXPRESSION {$$ = $1;}
                |	PREDECREMENTEXPRESSION  {$$ = $1;}
                |	PLUS UNARYEXPRESSION    {$$ = $2;
                                            type_check_unary(ds[curr2]["type"],"+");}
                |	MINUS UNARYEXPRESSION   {   $$ = new_address();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = -"+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
                |	UNARYEXPRESSIONNOTPLUSMINUS {$$ = $1;}

PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION    {   $$ = new_address();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    yyerror();
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+"+1");
                                                code.push_back(ds[curr2]["var"]+"="+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] += 1;  /* Modify the actual underlying variable */
                    }

PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  {   $$ = new_address();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+"-1");
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    yyerror();
                                                }
                                                code.push_back(ds[curr2]["var"]+ "="+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] -= 1;
                    }

UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  {$$ = $1;}
                            |	COMPLEMENT UNARYEXPRESSION  {   $$ = new_address();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~"+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
                            |	NOT UNARYEXPRESSION {   $$ = new_address();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = !"+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
                            
POSTFIXEXPRESSION: PRIMARY  {$$ = $1;}
                  |	EXPRESSIONNAME  {$$ = $1;}
                  | IDENTIFIER  {   $$ = new_address();
                                    int curr = chartonum($$);
                                    /* How to access symbol table entry of a terminal */
                                    ds[curr]["type"] = get_symbol_table(curr,"type");
                                    ds[curr]["identifier"] = "YES";
                                    ds[curr]["start"] = code.size();
                                    // ds[curr]["var"] = 
                                    /* How to pass values from here? */
                  }
                  |	POSTINCREMENTEXPRESSION {$$ = $1;}
                  |	POSTDECREMENTEXPRESSION {$$ = $1;}

POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS {   $$ = new_address();
                                                int curr = chartonum($$), curr1 = chartonum($1);
                                                type_check_unary(ds[curr1]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    yyerror();
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                code.push_back(ds[curr1]["var"]+ "="+ ds[curr]["var"]+"+1");
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
}

POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS   {   $$ = new_address();
                                                int curr = chartonum($$), curr1 = chartonum($1);
                                                type_check_unary(ds[curr1]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    yyerror();
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                code.push_back(ds[curr1]["var"]+ "="+ ds[curr]["var"]+"-1");
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                // ds[curr]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
                                                // ds[curr1]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
}

INSTANCEOFEXPRESSION: RELATIONALEXPRESSION INSTANCEOF REFERENCETYPE


METHODDECLARATION:  METHODHEADER METHODBODY {$$ = $1;
                                                code.push_back("end func");} 
                    |   SUPER1 METHODHEADER METHODBODY
                    |   SUPER2 METHODHEADER METHODBODY
                    |   SUPER3 METHODHEADER METHODBODY
                    |   METHODMODIFIERS METHODHEADER METHODBODY {$$ = $1;
                                                code.push_back("end func");} 
                    | AT OVERRIDE METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER1 METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER2 METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER3 METHODHEADER METHODBODY  
                    | AT OVERRIDE METHODMODIFIERS METHODHEADER METHODBODY  


METHODHEADER: TYPE METHODDECLARATOR THROWS2 
            |   TYPE METHODDECLARATOR { $$ = new_address();
                                        int curr = chartonum($$), curr1 = chartonum($1), curr2 = chartonum($2);
                                        ds[curr]["start"] = ds[curr2]["start"];
            }
             |	TYPEPARAMETERS TYPE METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS TYPE METHODDECLARATOR 
             |  VOID METHODDECLARATOR THROWS2
            |   VOID METHODDECLARATOR   { $$ = new_address();
                                        int curr = chartonum($$), curr1 = chartonum($1), curr2 = chartonum($2);
                                        ds[curr]["start"] = ds[curr2]["start"];
            }
             |	TYPEPARAMETERS VOID METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS VOID METHODDECLARATOR 


THROWS2: THROWS EXCEPTIONTYPELIST

EXCEPTIONTYPELIST: EXCEPTIONTYPE    
                |   EXCEPTIONTYPELIST COMMA EXCEPTIONTYPE

EXCEPTIONTYPE: CLASSTYPE

METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN { $$ = new_address();
                                        int curr = chartonum($$);
                                        ds[curr]["start"] = code.size();
                                        code.push_back("begin func "+chartostring($1));
}
                |   IDENTIFIER OPENPARAN CLOSEPARAN DIMS
                |   IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS
                |   IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN { $$ = new_address();
                                        int curr = chartonum($$), curr3 = chartonum($3);
                                        ds[curr]["start"] = code.size();
                                        code.push_back("begin func "+chartostring($1));
                                        for(auto i:ds[curr3]["param"])
                                        code.push_back("pop param, "i);
}
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN 
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN DIMS
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN 

RECEIVERPARAMETER:  TYPE THIS
                |   TYPE IDENTIFIER DOT THIS

FORMALPARAMETERLIST: FORMALPARAMETER {   $$ = new_address();
                                        int curr = chartonum($$), curr1 = chartonum($1);
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds[curr]["param"] = vector<string>();
                                        ds[curr]["param"].push_back(ds[curr1]["var"]);
}
                    |   FORMALPARAMETERLIST COMMA FORMALPARAMETER   {   $$ = new_address();
                                        int curr = chartonum($$), curr1 = chartonum($1),curr3 = chartonum($3);
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds[curr]["param"] = ds[curr1]["param"];
}

FORMALPARAMETER:  TYPE VARIABLEDECLARATORID {   $$ = new_address();
                                        int curr = chartonum($$), curr2 = chartonum($2);
                                        ds[curr]["var"] = ds[curr2]["var"];
}
                |	VARIABLEARITYPARAMETER
                |   FINAL TYPE VARIABLEDECLARATORID {   $$ = new_address();
                                        int curr = chartonum($$), curr2 = chartonum($2);
                                        ds[curr]["var"] = ds[curr2]["var"];
}


VARIABLEARITYPARAMETER  :  TYPE TRIPLEDOT IDENTIFIER
                        |   FINAL TYPE TRIPLEDOT IDENTIFIER


METHODBODY: BLOCK   {$$ = $1;}
           |	SEMICOLON

INSTANCEINITIALIZER: BLOCK  

STATICINITIALIZER: STATIC BLOCK

BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY {$$ = $2;}
    |   OPENCURLY  CLOSECURLY

BLOCKSTATEMENTS: BLOCKSTATEMENT    {$$ = $1;}
                |  BLOCKSTATEMENTS BLOCKSTATEMENT { $$ = new_address();
                                                    int curr = chartonum($$), curr1 = chartonum($1), curr2 = chartonum($2);
                                                    ds[curr]["continuelist"] = merge(ds[curr1]["continuelist"]);
                                                    ds[curr]["breaklist"] = merge(ds[curr1]["breaklist"]);
                                                    ds[curr]["start"] = ds[curr1]["start"];
                }

BLOCKSTATEMENT: LOCALCLASSORINTERFACEDECLARATION
               |	LOCALVARIABLEDECLARATIONSTATEMENT   {$$ = $1;}
               |	STATEMENT   {$$ = $1;}
 
LOCALCLASSORINTERFACEDECLARATION: CLASSDECLARATION  

LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON   {$$ = $1;}

LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST    {$$ = $3;}
                        |   LOCALVARIABLETYPE VARIABLEDECLARATORLIST    {$$ = $3;}

LOCALVARIABLETYPE: TYPE 
                  |	VAR


STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT {$$ = $1;}
          |	LABELEDSTATEMENT    {$$ = $1;}
          |	IFTHENSTATEMENT {$$ = $1;}
          |	IFTHENELSESTATEMENT {$$ = $1;}
          |	WHILESTATEMENT  {$$ = $1;}
          |	FORSTATEMENT    {$$ = $1;}

STATEMENTWITHOUTTRAILINGSUBSTATEMENT    :BLOCK  {$$ = $1;}
                                     |	EMPTYSTATEMENT  {$$ = $1;}
                                     |	EXPRESSIONSTATEMENT {$$ = $1;}
                                     |	ASSERTSTATEMENT {$$ = $1;}
                                     |	BREAKSTATEMENT  {$$ = $1;}
                                     |	CONTINUESTATEMENT   {$$ = $1;}
                                     |	RETURNSTATEMENT {$$ = $1;}
                                     |	THROWSTATEMENT  {$$ = $1;}
                                     |	YIELDSTATEMENT  {$$ = $1;}

EMPTYSTATEMENT: SEMICOLON   {$$ = new_address();}

EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  {$$ = $1;}

STATEMENTEXPRESSION: ASSIGNMENT {$$ = $1;}
                    |	PREINCREMENTEXPRESSION  {$$ = $1;}
                    |	PREDECREMENTEXPRESSION  {$$ = $1;}
                    |	POSTINCREMENTEXPRESSION {$$ = $1;}
                    |	POSTDECREMENTEXPRESSION {$$ = $1;}
                    |	METHODINVOCATION    {$$ = $1;}
                    |	CLASSINSTANCECREATIONEXPRESSION {$$ = $1;}

ASSERTSTATEMENT: ASSERT EXPRESSION SEMICOLON
                |	ASSERT EXPRESSION COLON EXPRESSION SEMICOLON

BREAKSTATEMENT: BREAK SEMICOLON     {   $$ = new_address();
                                            int curr = chartonum($$);
                                            ds[curr]["breaklist"] = vector<int>();
                                            ds[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = code.size();
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
                |   BREAK IDENTIFIER SEMICOLON

CONTINUESTATEMENT: CONTINUE SEMICOLON   {   $$ = new_address();
                                            int curr = chartonum($$);
                                            ds[curr]["continuelist"] = vector<int>();
                                            ds[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = code.size();
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
                |   CONTINUE IDENTIFIER SEMICOLON

RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON    {$$ = new_address();
                                                    int curr = chartonum($$), exp = chartonum($2);
                                                    ds[curr]["start"] = code.size();
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
                |   RETURN SEMICOLON    {$$ = new_address();
                                                    int curr = chartonum($$);
                                                    ds[curr]["start"] = code.size();
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }

THROWSTATEMENT: THROW EXPRESSION SEMICOLON

YIELDSTATEMENT: YIELD EXPRESSION SEMICOLON

LABELEDSTATEMENT: IDENTIFIER COLON STATEMENT

IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT   {   $$ = new_address(); //Not keeping truelist and falselist corresponding to statements
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5);
                                                                    backpatch(ds[curr3]["truelist"],ds[curr5]["start"]);
                                                                    backpatch(ds[curr3]["falselist"],code.size());
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["contiuelist"] = ds[curr5]["continuelist"];
                                                                    ds[curr]["breaklist"] = ds[curr5]["breaklist"];
                                                                    // ds[curr]["falselist"] = ds[curr3]["falselist"];
                                                                    // ds[curr]["truelist"] = vector<int>();
}

IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT   {   $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    backpatch(ds[curr3]["falselist"],ds[curr7]["start"]);
                                                                    backpatch(ds[curr3]["truelist"],ds[curr5]["start"]);
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["contiuelist"] = merge(ds[curr5]["continuelist"],ds[curr7]["continuelist"]);
                                                                    ds[curr]["breaklist"] = merge(ds[curr5]["breaklist"],ds[curr7]["breaklist"]);
                                                                    // ds[curr]["truelist"] = vector<int>();
                                                                    // ds[curr]["falselist"] = vector<int>();
}

IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF     {   $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    backpatch(ds[curr3]["falselist"],ds[curr7]["start"]);
                                                                    backpatch(ds[curr3]["truelist"],ds[curr5]["start"]);
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["contiuelist"] = merge(ds[curr5]["continuelist"],ds[curr7]["continuelist"]);
                                                                    ds[curr]["breaklist"] = merge(ds[curr5]["breaklist"],ds[curr7]["breaklist"]);
                                                                    // ds[curr]["truelist"] = vector<int>();
                                                                    // ds[curr]["falselist"] = vector<int>();
}

STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT    {$$ = $1;}
                   |	LABELEDSTATEMENTNOSHORTIF   {$$ = $1;}
                   |	IFTHENELSESTATEMENTNOSHORTIF    {$$ = $1;}
                   |	WHILESTATEMENTNOSHORTIF {$$ = $1;}
                   |	FORSTATEMENTNOSHORTIF   {$$ = $1;}

LABELEDSTATEMENTNOSHORTIF: IDENTIFIER COLON STATEMENTNOSHORTIF  /*  for later */

WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF   {   $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5);
                                                                    backpatch(ds[curr3]["truelist"],ds[curr5]["start"]);
                                                                    backpatch(ds[curr5]["continuelist"],ds[curr3]["start"]); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr3]["falselist"],code.size());
                                                                    backpatch(ds[curr5]["breaklist"],code.size());
                                                                    // ds[curr]["falselist"] = ds[curr3]["falselist"];
}

FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF   {$$ = $1;}
                      |	ENHANCEDFORSTATEMENTNOSHORTIF   {$$ = $1;}


WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT {   $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5);
                                                                    backpatch(ds[curr3]["truelist"],ds[curr5]["start"]);
                                                                    backpatch(ds[curr5]["continuelist"],ds[curr3]["start"]); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr3]["falselist"],code.size());
                                                                    backpatch(ds[curr5]["breaklist"],code.size());
}

FORSTATEMENT: BASICFORSTATEMENT {$$ = $1;}
             |	ENHANCEDFORSTATEMENT    {$$ = $1;}

BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT   {   $$ = new_address();
                                                                    int curr = chartonum($$), curr6 = chartonum($6);
                                                                    backpatch(ds[curr6]["continuelist"],ds[curr6]["start"]); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr6]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT    {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), update = chartonum($5), body = chartonum($7);
                                                                    backpatch(ds[body]["continuelist"],ds[update]["start"]); 
                                                                    backpatch(ds[update]["goto1"],ds[body]["start"]);
                                                                    backpatch(ds[update]["goto2"],ds[body]["start"]);
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[body]["start"];
                                                                    code.push_back("goto "+ds[update]["start"]);
                                                                    backpatch(ds[body]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT   {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr4 = chartonum($4), curr7 = chartonum($7);
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds[curr7]["continuelist"],ds[curr]["start"]); 
                                                                    backpatch(ds[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), exp = chartonum($4), update = chartonum($6), body = chartonum($8);
                                                                    if(ds[exp]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[exp]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[update]["goto1"],ds[body]["start"]);
                                                                    backpatch(ds[update]["goto2"],ds[exp]["start"]);
                                                                    backpatch(ds[exp]["truelist"],ds[body]["start"]);
                                                                    backpatch(ds[body]["continuelist"],ds[update]["start"]); 
                                                                    backpatch(ds[body]["breaklist"],code.size()); 
                                                                    backpatch(ds[exp]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr7 = chartonum($7);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr7]["start"]);
                                                                    // backpatch(ds[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds[curr7]["continuelist"],ds[curr7]["start"]); 
                                                                    backpatch(ds[curr7]["breaklist"],code.size()); 
                                                                    // backpatch(ds[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT    {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), init = chartonum($3), update = chartonum($6), body = chartonum($8);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[init]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    // backpatch(ds[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds[update]["goto1"],ds[body]["start"]); 
                                                                    backpatch(ds[update]["goto2"],ds[body]["start"]); 
                                                                    backpatch(ds[body]["continuelist"],ds[update]["start"]); 
                                                                    backpatch(ds[body]["breaklist"],code.size()); 
                                                                    // backpatch(ds[curr4]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT   {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr8 = chartonum($8);
                                                                    if(ds[curr5]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    // int gotoupdate = code.size();
                                                                    // for(auto s:ds[curr6]["code"])
                                                                    // code.push_back(s);
                                                                    code.push_back("goto "+ds[curr5]["start"]);
                                                                    backpatch(ds[curr5]["truelist"],ds[curr8]["start"]);
                                                                    backpatch(ds[curr8]["continuelist"],ds[curr5]["start"]); 
                                                                    backpatch(ds[curr8]["breaklist"],code.size()); 
                                                                    backpatch(ds[curr5]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), init = chartonum($3), exp = chartonum($5), update = chartonum($7), body = chartonum($9);
                                                                    if(ds[exp]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[init]["start"];
                                                                    code.push_back("goto "+ds[exp]["start"]);
                                                                    backpatch(ds[exp]["truelist"],ds[body]["start"]);
                                                                    backpatch(ds[body]["continuelist"],ds[update]["start"]); 
                                                                    backpatch(ds[body]["breaklist"],code.size()); 
                                                                    backpatch(ds[exp]["falselist"],code.size());
                                                                    backpatch(ds[update]["goto1"],ds[body]["start"]);
                                                                    backpatch(ds[update]["goto2"],ds[exp]["start"]);
}

BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF   {   $$ = new_address();
                                                                    int curr = chartonum($$), curr6 = chartonum($6);
                                                                    backpatch(ds[curr6]["continuelist"],ds[curr6]["start"]); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr6]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF    {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    backpatch(ds[curr7]["continuelist"],code.size()); 
                                                                    for(auto s:ds[curr5]["code"])
                                                                    code.push_back(s);
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr7]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr6]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF   {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr4 = chartonum($4), curr7 = chartonum($7);
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds[curr7]["continuelist"],ds[curr]["start"]); 
                                                                    backpatch(ds[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr4 = chartonum($4), curr6 = chartonum($6), curr8 = chartonum($8);
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds[curr6]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds[curr4]["truelist"],ds[curr8]["start"]);
                                                                    backpatch(ds[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds[curr8]["breaklist"],code.size()); 
                                                                    backpatch(ds[curr4]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr7 = chartonum($7);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr7]["start"]);
                                                                    // backpatch(ds[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds[curr7]["continuelist"],ds[curr7]["start"]); 
                                                                    backpatch(ds[curr7]["breaklist"],code.size()); 
                                                                    // backpatch(ds[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF    {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr6 = chartonum($6), curr8 = chartonum($8);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds[curr6]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    // backpatch(ds[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds[curr8]["breaklist"],code.size()); 
                                                                    // backpatch(ds[curr4]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF   {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr8 = chartonum($8);
                                                                    if(ds[curr5]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    // int gotoupdate = code.size();
                                                                    // for(auto s:ds[curr6]["code"])
                                                                    // code.push_back(s);
                                                                    code.push_back("goto "+ds[curr5]["start"]);
                                                                    backpatch(ds[curr5]["truelist"],ds[curr8]["start"]);
                                                                    backpatch(ds[curr8]["continuelist"],ds[curr5]["start"]); 
                                                                    backpatch(ds[curr8]["breaklist"],code.size()); 
                                                                    backpatch(ds[curr5]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF {      /* For update code should be after forbody code */
                                                                                            $$ = new_address();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7), curr9 = chartonum($9);
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds[curr7]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr5]["start"]);
                                                                    backpatch(ds[curr5]["truelist"],ds[curr9]["start"]);
                                                                    backpatch(ds[curr9]["continuelist"],gotoupdate); 
                                                                    backpatch(ds[curr9]["breaklist"],code.size()); 
                                                                    backpatch(ds[curr5]["falselist"],code.size());
}


ENHANCEDFORSTATEMENT: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENT

ENHANCEDFORSTATEMENTNOSHORTIF: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF

FORINIT: STATEMENTEXPRESSIONLIST    {$$ = $1;}
        |	LOCALVARIABLEDECLARATION    {$$ = $1;}

FORUPDATE: STATEMENTEXPRESSIONLIST  {$$ = $1;
                                        int curr = numtochar($$);
                                        ds[curr]["code"] = vector<string>();
                                        for(int i=ds[curr]["start"];i<code.size();i++){
                                            ds[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds[curr]["code"].size();i++)
                                        code.pop_back();
                                        }

STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION {$$ = $1;}
                        |   STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION {

                            $$ = new_address();
                            int curr = chartonum($$), curr1 = chartonum($1);
                            ds[curr]["start"] = ds[curr1]["start"];

                        }

CONSTRUCTORDECLARATION:     CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY
                        |   CONSTRUCTORDECLARATOR CONSTRUCTORBODY
                        |   SUPER1 CONSTRUCTORDECLARATOR THROWS2 CONSTRUCTORBODY  
                        |   SUPER1 CONSTRUCTORDECLARATOR CONSTRUCTORBODY 


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

SUPER1 : PUBLIC 
        | PRIVATE 
        | PROTECTED
        | SUPER1 PUBLIC 
        | SUPER1 PRIVATE 
        | SUPER1 PROTECTED
    
SUPER2 : STATIC
        | FINAL 
        | SUPER1 STATIC
        | SUPER1 FINAL
        | SUPER2 STATIC
        | SUPER2 FINAL
        | SUPER2 PUBLIC
        | SUPER2 PRIVATE
        | SUPER2 PROTECTED

SUPER3 : ABSTRACT
        | STRICTFP
        | SUPER2 ABSTRACT
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


int main(int argc, char** argv){
    yyparse();
    for(int i=1;i<code.size();i++){
        cout<<i<<": "<<code[i-1]<<"\n";
    }
    /* cout << "digraph ASTVisual {\n ordering = out ;\n"; */
    /* for(auto e: labels){
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
    cout << "  }\n"; */

}