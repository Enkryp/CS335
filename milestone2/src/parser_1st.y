%{
    #include<bits/stdc++.h>
    using namespace std;   

    #include "conversion.h"
    #include "structs.h"

    
    
    /*TODO typecheck for unary operators
    Line numbers in error
    3ac type sizes in array access
    2 parse for future class, methods, fields
    array access new exp, literal exp for offsets
    offsets for arguments ?

    back patach type check for fields
    negative for addrs in new exp
    GOTOS for */
    /*TODO : in method_det use classname and functionname both as keys because multiple classes have functions with same name. maintain current class name in global variable -- done */
    /*TODO add variable size in dimexprs */
    extern "C" int yylex();
    extern "C" FILE *yyin;
    #define ll long long
    extern "C" int yylineno; 
    #define all(x) (x).begin(), (x).end()


    ll scope=0;

    ll lasttype=0;

    // bool typecompatiblity(string t1, string t2, string operator){
    //     //  types = {int, long, float, double, char, boolean, byte, short, void, var}
    //     // operators = {+, -, *, /, %, &, |, ^, <<, >>, >>>, &&, ||, ==, !=, <, >, <=, >=, =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=, >>>=}

    // }
    // vector <ll>lastfeild  TODO

    // struct general{
    //     string name;
    //     vector <ll> vec;


    //     bool operator<(const general& other) const{
    //         return name<other.name;
    //     }
        
    // };

    // map<char*, general> generalmap;

    // struct methodsig{
    //     vector <ll>access;
    //     ll rettype;
    //     vector<ll> argtype;
    //     bool operator<(const methodsig& other) const{
    //         return rettype<other.rettype;
    //     }
    // };
    // struct fieldsig{
    //     vector <ll>access;
    //     ll type;
    //     bool operator<(const fieldsig& other) const{
    //         return type<other.type;
    //     }
    // };

    // struct varentry{
    //     ll type;
    //     ll scope;
    //     bool operator<(const varentry& other) const{
    //         return scope<other.scope;
    //     }
    // };



    string checkclassname="";

    // void typ_error(){
    //     cout<<"Unexpected type\n";
    //     // cout<<"Expected value of type "+a+" at line number "+lineno+". Instead found value of type "+b+"\n";
    //     exit(0);
    // }
    void typ_error(string a, string b, int lineno){
        cout<<"Expected value of type "+a+" at line number "<<lineno<<". Instead found value of type "+b+"\n";
        exit(0);
    }
    

    void resetclass(){
        methods.clear();
        fields.clear();
        symboltable.clear();
        scope = 0;
        checkclassname="";
        
        
    } 
    stack<ll> scopes;
    ll scopemax=0;
    /*TODO ADD PRESEVRED FIELDS AND METHODS*/
    /*TODO ARRAY PASSED AS ARG IN METHOD*/
    /*TODO NEW INT ARRAY*/
    /*TODO FOR LOOP*/
    /*TODO FIELD OR ARG OR METHOD PREV DECLARED*/
        void popscope (){
        
        vector <string> todelete;
        for (auto x : symboltable){
            if (x.second.scope == scope){
                todelete.push_back(x.first);
            }
        }
        for (auto x : todelete){
            symboltable.erase(x);
            // cout<<x<<endl;
        }
        // cout<<scopes.size()<<endl;
        scopes.pop();
        scope = scopes.top();
        ll dec = scopeoffset.top()- curoffset;
        curoffset += dec;
        code.push_back("stackpointer - "+ numtostring(-dec));
        scopeoffset.pop();

    }
    bool tempincscope = false;
    void newscope(){
        if(tempincscope){tempincscope=false; return;}
        
        scopeoffset.push(curoffset);
        ll prev = scope;
        scope = ++scopemax;
        scopes.push(scope);
        parentscope[scope] = prev;
    }
     void tempnextscope(){
        assert(tempincscope==false);
        newscope();
        tempincscope = true;
    }




    string gettypefromsymtable(string a){
        
        // cout<< "gettypefromsymtable"<<endl;
        // cout<< a<<endl;
        // return "";
        dbgsymtable();
        

        string r= "";
        if(symboltable.find(a)!= symboltable.end()){
            r = symboltable[a].typ.name;
        }
        else if(fields.find(a)!= fields.end()){
            r = fields[a].typ.name;
        }
        else {
            assert(0 && "not found in symtable");
        }
        return r;
    }
    string curr_class;

    ll gettype(string s){
        if(s=="int")return 1;
        if(s=="long")return 3;
        if(s=="float")return 5;
        if(s=="double")return 7;
        if(s=="char")return 9;
        if(s=="bool")return 11;
        if(s=="byte")return 13;
        if(s=="short")return 15;
        if(s=="void")return 17;
        if(s=="var")return 19;
        ll t =0;

        for (auto x: s){
            t*=128;
            t+=(char)x-'\0';
        }
        return 2*t+21;
        return 0;
    }



    void yyerror(char *s){
        cout<<s<<" at: "<<yylineno<<endl;
        exit(0);
    }
    map<char*,ll> temp;
    ll gid=0;
    char * new_temp(){
        ll num=gid++;
        num*=10;
        return numtochar(num);
    }

    


    
%}
%union{
    char* val;
}

/* data types */
%start COMPILATIONUNIT
%type<val>  ADDITIONALBOUND ADDITIVEEXPRESSION ANDEXPRESSION ARGUMENTLIST ARRAYACCESS ARRAYCREATIONEXPRESSION ARRAYINITIALIZER ARRAYINITIALIZER1 ASSERTSTATEMENT ASSIGNMENT ASSIGNMENTEXPRESSION ASSIGNMENTOPERATOR BASICFORSTATEMENT BASICFORSTATEMENTNOSHORTIF BLOCK BLOCKSTATEMENT BLOCKSTATEMENTS BREAKSTATEMENT CLASSBODY CLASSBODYDECLARATION CLASSBODYDECLARATIONS CLASSDECLARATION CLASSEXTENDS CLASSIMPLEMENTS CLASSINSTANCECREATIONEXPRESSION CLASSLITERAL CLASSMEMBERDECLARATION CLASSORINTERFACETYPE CLASSORINTERFACETYPETOINSTANTIATE CLASSPERMITS CLASSTYPE CLASSTYPE1 COMPILATIONUNIT CONDITIONALANDEXPRESSION CONDITIONALEXPRESSION CONDITIONALOREXPRESSION CONSTRUCTORBODY CONSTRUCTORDECLARATION CONSTRUCTORDECLARATOR CONTINUESTATEMENT DIMEXPR DIMEXPRS DIMS EMPTYSTATEMENT ENHANCEDFORSTATEMENT ENHANCEDFORSTATEMENTNOSHORTIF EQUALITYEXPRESSION EXCEPTIONTYPE EXCEPTIONTYPELIST EXCLUSIVEOREXPRESSION EXPLICITCONSTRUCTORINVOCATION EXPRESSION EXPRESSIONNAME EXPRESSIONSTATEMENT FIELDACCESS FIELDDECLARATION FIELDMODIFIERS FLOATINGTYPE FORINIT FORMALPARAMETER FORMALPARAMETERLIST FORSTATEMENT FORSTATEMENTNOSHORTIF FORUPDATE IFTHENELSESTATEMENT IFTHENELSESTATEMENTNOSHORTIF IFTHENSTATEMENT INCLUSIVEOREXPRESSION INSTANCEINITIALIZER INSTANCEOFEXPRESSION INTEGRALTYPE INTERFACETYPE INTERFACETYPELIST LABELEDSTATEMENT LABELEDSTATEMENTNOSHORTIF LEFTHANDSIDE LITERAL LOCALCLASSORINTERFACEDECLARATION LOCALVARIABLEDECLARATION LOCALVARIABLEDECLARATIONSTATEMENT LOCALVARIABLETYPE METHODBODY METHODDECLARATION METHODDECLARATOR METHODHEADER METHODINVOCATION METHODMODIFIERS METHODNAME METHODREFERENCE MULTIPLICATIVEEXPRESSION NORMALCLASSDECLARATION NUMERICTYPE ORDINARYCOMPILATIONUNIT POSTDECREMENTEXPRESSION POSTFIXEXPRESSION POSTINCREMENTEXPRESSION PREDECREMENTEXPRESSION PREINCREMENTEXPRESSION PRIMARY PRIMARYNONEWARRAY PRIMITIVETYPE RECEIVERPARAMETER REFERENCETYPE RELATIONALEXPRESSION RETURNSTATEMENT SHIFTEXPRESSION SIMPLETYPENAME SQUARESTAR STATEMENT STATEMENTEXPRESSION STATEMENTEXPRESSIONLIST STATEMENTNOSHORTIF STATEMENTWITHOUTTRAILINGSUBSTATEMENT STATICINITIALIZER SUPER1 SUPER2 SUPER3 THROWS2 THROWSTATEMENT TOPLEVELCLASSORINTERFACEDECLARATION TYPE TYPEARGUMENT TYPEARGUMENTLIST TYPEARGUMENTS TYPEBOUND TYPENAMES TYPEPARAMETER TYPEPARAMETERLIST TYPEPARAMETERS UNARYEXPRESSION UNARYEXPRESSIONNOTPLUSMINUS UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION VARIABLEARITYPARAMETER VARIABLEDECLARATOR VARIABLEDECLARATORID VARIABLEDECLARATORLIST VARIABLEINITIALIZER VARIABLEINITIALIZERLIST WHILESTATEMENT WHILESTATEMENTNOSHORTIF WILDCARD WILDCARDBOUNDS YIELDSTATEMENT IMPORTDECLARATION NORMALINTERFACEDECLARATION INTERFACEBODY INTERFACEMEMBERDECLARATION INTERFACEDECLARATION INTERFACEMEMBERDECLARATIONS OPENCURLY CLOSECURLY FOR CLASSNAME
%token<val> BOOLEAN BYTE SHORT INT LONG CHAR FLOAT DOUBLE 

/* Separators */
%token<val> COMMA QUESTIONMARK SEMICOLON  OPENCURLY1 CLOSECURLY1 ANGULARLEFT ANGULARRIGHT OPENSQUARE CLOSESQUARE OPENPARAN CLOSEPARAN DOUBLECOLON TRIPLEDOT WS AT OVERRIDE

/* Operators  AND -> & COMPLEMENT -> ~ */
%token<val> EQUALS MULTIPLYEQUALS DIVIDEEQUALS MODEQUALS PLUSEQUALS MINUSEQUALS PLUS MINUS DIVIDE MULTIPLY MOD OR XOR COLON NOT COMPLEMENT AND DOT OROR ANDAND PLUSPLUS MINUSMINUS ANGULARLEFTANGULARLEFT ANGULARRIGHTANGULARRIGHT ANGULARRIGHTANGULARRIGHTANGULARRIGHT
EQUALSEQUALS NOTEQUALS
/* Literals */
%token<val> INTEGERLITERAL FLOATINGPOINTLITERAL BOOLEANLITERAL CHARACTERLITERAL STRINGLITERAL TEXTBLOCK NULLLITERAL

/* Keywords */
%token<val> EXTENDS SUPER CLASS PUBLIC PRIVATE IMPLEMENTS PERMITS PROTECTED STATIC FINAL TRANSIENT VOLATILE INSTANCEOF THIS VOID NEW THROW ASSERT VAR BREAK CONTINUE RETURN YIELD IF ELSE WHILE FOR1 PRINTLN ABSTRACT SYNCHRONIZED NATIVE STRICTFP 

/*  Unused keywords  See throw, throws and throwss check non_sealed*/
%token<val> SWITCH DEFAULT PACKAGE DO GOTO IMPORT THROWS CASE ENUM CATCH TRY INTERFACE FINALLY CONST UNDERSCORE EXPORTS OPENS REQUIRES USES MODULE SEALED PROVIDES TO WITH OPEN RECORD TRANSITIVE ERROR ONCE NL NON_SEALED  


%token<val> IDENTIFIER UNQUALIFIEDMETHODIDENTIFIER  DOTCLASS
%token<val> EOFF
%%



COMPILATIONUNIT     :   EOFF  {return 0;}
                    |   ORDINARYCOMPILATIONUNIT EOFF {
                    
                    return 0;
                }
                    
TYPE    :   PRIMITIVETYPE { $$=$1; }
            |   REFERENCETYPE {$$ = $1;/*TODO*/}

PRIMITIVETYPE   :   NUMERICTYPE {$$=$1;}
                |   BOOLEAN  {$$ = stringtochar("bool");}

NUMERICTYPE     :   INTEGRALTYPE {$$=$1;}
                |   FLOATINGTYPE {$$=$1;}

INTEGRALTYPE    : BYTE  {$$=$1;}
                | SHORT  {$$=$1;}
                | INT {$$=$1;}
                | LONG {$$=$1;}
                | CHAR {$$=$1;}

FLOATINGTYPE    :   FLOAT  {$$=$1;}
                |   DOUBLE {$$=$1;}

REFERENCETYPE   :   CLASSORINTERFACETYPE {$$=$1;}

CLASSORINTERFACETYPE    :   CLASSTYPE {$$=$1;}

CLASSTYPE   :   CLASSTYPE1 {$$=$1;}

CLASSTYPE1  :   IDENTIFIER {$$=$1; }


DIMS    :   OPENSQUARE CLOSESQUARE {$$=new_temp(); temp[$$]= 1;}
        |   DIMS OPENSQUARE CLOSESQUARE {$$= new_temp(); temp[$$]=temp[$1]+1;}

METHODNAME  :   IDENTIFIER  {    $$ = new_temp();
                                ll curr1 = chartonum($$);
                                ds[curr1]["type"] = methods[chartostring($1)].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring($1);
                            }

EXPRESSIONNAME   :   IDENTIFIER DOT IDENTIFIER {    
    /* makise */    /* check whether second identifier an object or a function. */
                                                    $$ = new_temp();
                                                    int curr = chartonum($$);
                                                    string  name = chartostring($1), name2 = chartostring($3);
                                                    // ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                    // if(get_symbol_table_function(name,name2,"type"))
                                                    objdetails detail = getobjdetails(name,name2);
                                                    if(detail.isfield){
                                                        ds[curr]["var"] = pref[chartostring($1)]+chartostring($3);
                                                        ds[curr]["type"] = detail.field.typ.name;
                                                    }else{
                                                        object_error(name,name2,yylineno);
                                                    }
                                                    // ds[curr]["lineno"] = get_symbol_table(name,"lineno");
                                                    /* TODO */
}
                |   EXPRESSIONNAME DOT IDENTIFIER {/*TODO*/}


ORDINARYCOMPILATIONUNIT :   TOPLEVELCLASSORINTERFACEDECLARATION 
                        |   ORDINARYCOMPILATIONUNIT TOPLEVELCLASSORINTERFACEDECLARATION

TOPLEVELCLASSORINTERFACEDECLARATION :   CLASSDECLARATION  {  

    // assert(classfields.find(chartostring($1))==classfields.end());
    // assert(classmethods.find(chartostring($1))==classmethods.end());
    assert(listofclasses.find(chartostring($1))==listofclasses.end());
    listofclasses.insert(chartostring($1));

    // classfields[chartostring($1)]= fields;
    // classmethods[chartostring($1)]= methods;


    for (auto x : fields ){
        // preservedfields[{x.first, chartostring($1)}] = x.second;
        preservedsymboltable[{x.first, -1}].lineno = x.second.lineno;
        preservedsymboltable[{x.first, -1}].typ = x.second.typ;
        preservedsymboltable[{x.first, -1}].token = "identifier - field of" + chartostring($1) ;
        
        //cout<<x.first;
        //cout<<x.second.typ.name;
        //cout<<x.second.typ.dims;
//         for(auto y : x.second.dims){
//             cout<<"["<<y<<"]";
//         }
// cout<<endl;
    }
    // cout<<"meth";
    for(auto x : methods){
        preservedsymboltable[{x.first, -1}].lineno = x.second.lineno;
        preservedsymboltable[{x.first, -1}].typ = x.second.rettype;
        preservedsymboltable[{x.first, -1}].token = "identifier - method of" + chartostring($1) ;
        
        // preservedfields[{x.first, chartostring($1)}] = x.second;
        // cout<<x.first<<endl;
        // cout<<x.second.rettype.name <<x.second.rettype.dims <<endl;
        // for (auto y : x.second.argtype){
        //     cout<<y.name<<" "<<y.dims<<" ";

        // }
        // cout<<endl;
        
        
        }
     resetclass();}
                                    |   SEMICOLON  
                                    |   IMPORTDECLARATION TOPLEVELCLASSORINTERFACEDECLARATION
                                    |   INTERFACEDECLARATION 

IMPORTDECLARATION   :   IMPORT EXPRESSIONNAME SEMICOLON
                    |   IMPORT EXPRESSIONNAME DOT MULTIPLY SEMICOLON
                    |   IMPORT STATIC EXPRESSIONNAME SEMICOLON
                    |   IMPORT STATIC EXPRESSIONNAME DOT MULTIPLY SEMICOLON 

CLASSDECLARATION    :   NORMALCLASSDECLARATION  {$$ = $1;for(auto obj:object_list){
                        string pr = pref[obj.first];
                        vector<string> methods = getallmethods(obj.first,obj.second);
                        // vector<string> methods = {"f"};
                        for(auto method : methods){
                            // code.push_back(method);
                            // cout<<"methods "<<method<<"\n";

                            add_func(code, pr, method_det[obj.second][method].start, method_det[obj.second][method].end);
                        }
                    }}
                    

NORMALCLASSDECLARATION  :    CLASS CLASSNAME CLASSBODY {$$ = $2;if(checkclassname!="") assert(checkclassname== chartostring($2));/*TODO begin class */}
                            | SUPER1 CLASS IDENTIFIER CLASSBODY {$$ = $3; if(checkclassname!="")assert(checkclassname== chartostring($2));}
                            | SUPER2 CLASS IDENTIFIER CLASSBODY {$$ = $3;if(checkclassname!="")assert(checkclassname== chartostring($2));}
                            | SUPER3 CLASS IDENTIFIER CLASSBODY {$$ = $3;if(checkclassname!="")assert(checkclassname== chartostring($2));}

                            | CLASS IDENTIFIER TYPEPARAMETERS CLASSEXTENDS CLASSIMPLEMENTS CLASSPERMITS CLASSBODY
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
                            

CLASSNAME : IDENTIFIER  {$$ = $1; curr_class = chartostring($$); }

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

FOR : FOR1 {newscope();}
OPENCURLY : OPENCURLY1    {newscope(); }
CLOSECURLY : CLOSECURLY1  {popscope();}         

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

CLASSEXTENDS    :   EXTENDS CLASSTYPE

CLASSIMPLEMENTS :    IMPLEMENTS INTERFACETYPELIST

INTERFACETYPELIST   :   INTERFACETYPE
                    |   INTERFACETYPELIST COMMA INTERFACETYPE

CLASSPERMITS    :   PERMITS TYPENAMES

TYPENAMES   :   IDENTIFIER 
            |   TYPENAMES COMMA IDENTIFIER 

CLASSBODY   :  OPENCURLY CLOSECURLY 
            |   OPENCURLY CLASSBODYDECLARATIONS CLOSECURLY

CLASSBODYDECLARATIONS   :   CLASSBODYDECLARATION
                        |   CLASSBODYDECLARATIONS CLASSBODYDECLARATION

CLASSBODYDECLARATION    :   CLASSMEMBERDECLARATION
                        |   INSTANCEINITIALIZER
                        |   STATICINITIALIZER
                        |   CONSTRUCTORDECLARATION 

CLASSMEMBERDECLARATION:     FIELDDECLARATION
                            |   METHODDECLARATION
                            |   CLASSDECLARATION
                            |   SEMICOLON
                            |   INTERFACEDECLARATION

FIELDDECLARATION    :   FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON {
                                if(generalmap[$3].typ.name != "")assert(chartostring($2)== generalmap[$3].typ.name);

                    {   $$ = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum($3), curr = chartonum($$);
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    
                                                                    
                                                                    
                    }
                        
                        for (auto x: generalmap[$3].vlist){
                            assert(fields.find(x.first.name) == fields.end());
                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring($2);

                            fields[x.first.name].access = generalmap[$1].modifiers;
                            /*CHECK TODO*/
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                                                        fields[x.first.name].lineno = yylineno;

                            classfields[curr_class][x.first.name] = fields[x.first.name];

                        }
                    }
                    |   SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON{
                                                    if(generalmap[$3].typ.name != "")assert(chartostring($2)== generalmap[$3].typ.name);

                        {   $$ = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum($3), curr = chartonum($$);
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    
                                                                    
                                                                    
                    }
                        for (auto x: generalmap[$3].vlist){
                            assert(fields.find(x.first.name) == fields.end());

                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring($2);
                            fields[x.first.name].access = generalmap[$1].modifiers;
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                                                        fields[x.first.name].lineno = yylineno;
                                                        classfields[curr_class][x.first.name] = fields[x.first.name];


                        }
                    }
                    |   SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON{
                                                    if(generalmap[$3].typ.name != "")assert(chartostring($2)== generalmap[$3].typ.name);

                        {   $$ = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum($3), curr = chartonum($$);

                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($2)));
                                                                    // if((ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($2)))
                                                                    // typ_error();
                                                                    
                                                                    
                    }
                        for (auto x: generalmap[$3].vlist){
                            assert(fields.find(x.first.name) == fields.end());

                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring($2);
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                            fields[x.first.name].access = generalmap[$1].modifiers;
                                                        fields[x.first.name].lineno = yylineno;
                                                                                    classfields[curr_class][x.first.name] = fields[x.first.name];


                        }
                    }
                    |   TYPE VARIABLEDECLARATORLIST SEMICOLON {
                        if(generalmap[$2].typ.name != "")assert(chartostring($1)== generalmap[$2].typ.name);


                        {   $$ = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum($2), curr = chartonum($$);
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    else ds[curr]["start"] = numtostring(code.size());
                                                                    // code.push_back("start="+ds[curr]["start"]);
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($1)));
                                                                    for(auto i:ds2[curr2]["type"]){
                                                                        if(i!=chartostring($1)){
                                                                            typ_error(chartostring($1),i,int(yylineno));
                                                                        }
                                                                    }
                                                                    
                                                                    
                    }
                        
                        for (auto x: generalmap[$2].vlist){
                            
                            assert(fields.find(x.first.name) == fields.end());

                           fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring($1);
                             reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                                                        fields[x.first.name].lineno = yylineno;
                                                                                    classfields[curr_class][x.first.name] = fields[x.first.name];


                        }
                    }



VARIABLEDECLARATORLIST  :   VARIABLEDECLARATOR {$$ = new_temp(); generalmap[$$].typ = generalmap[$1].typ; generalmap[$$].vlist.push_back({generalmap[$1].vid, generalmap[$1].vinit});
{   
                                                    int curr = chartonum($$), curr1 = chartonum($1);
                                                    if(ds[curr1].find("start")!=ds[curr1].end()){
                                                        ds[curr]["start"] = ds[curr1]["start"];
                                                        ds2[curr]["type"].push_back(ds[curr1]["type"]);
                                                    }
                                                    // ds[curr]["start"] = ds[curr1]["start"];
                                                    // assert(!(ds[curr1].find("type")!=ds[curr1].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"]));
                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
}
}
                        |   VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR {$$ = $1; if(generalmap[$3].typ.name != "" && generalmap[$$].typ.name != "" )assert(generalmap[$3].typ.name == generalmap[$$].typ.name); else generalmap[$$].typ.name = max(generalmap[$3].typ.name, generalmap[$$].typ.name );  generalmap[$$].vlist.push_back({generalmap[$3].vid, generalmap[$3].vinit});
                        {                           

                                                    int curr = chartonum($$), curr1 = chartonum($1),curr3 = chartonum($3);
                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                    // assert(!(ds[curr3].find("type")!=ds[curr3].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"]));

                                                    // if((ds[curr3].find("type")!=ds[curr3].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"])){
                                                    //     cout<<ds[curr3]["type"]<<" "<<ds[curr1]["type"]<<"\n";
                                                    // // typ_error();
                                                    // }
                                                    
                                                    if(ds[curr3].find("start")!=ds[curr3].end()){
                                                        if(ds[curr].find("start")==ds[curr].end())
                                                        ds[curr]["start"] = ds[curr3]["start"];
                                                        // ds[curr]["type"] = ds[curr3]["type"];
                                                        ds2[curr]["type"].push_back(ds[curr3]["type"]);
                                                    }
                                                    // assert(ds[curr].find("start")!=ds[curr].end());
                                                    // error("Incompatible types");

}
}

VARIABLEDECLARATOR  :   VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER {$$ = new_temp(); generalmap[$$]= generalmap[$1]; generalmap[$$].vinit = generalmap[$3].vinit ;   generalmap[$$].typ= generalmap[$3].typ;                                   int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);                 
                                                                            if(ds[curr3].find("class")!=ds[curr3].end()){
                                                                                ds[curr]["var"] = ds[curr1]["var"];
                                                                                string cls = ds[curr3]["var"];    // stores the class name after new
                                                                                // cout<<"class "<<cls<<"\n";
                                                                                object_list.push_back({ds[curr]["var"],cls}); // Add object to object list
                                                                                pref[ds[ chartonum($$)]["var"]] = new_var2();
                                                                            }
                                                                            else if(ds[curr3].find("arr")!=ds[curr3].end()){
                                                                                if(ds[curr3].find("start")==ds[curr3].end())
                                                                                ds[curr]["start"] = numtostring(code.size());
                                                                                else ds[curr]["start"] = ds[curr3]["start"];
                                                                                ds[curr]["type"] = ds[curr3]["type"];
                                                                                code.push_back(ds[curr1]["var"]+" = array ( "+ds[curr3]["var"]+" )");
                                                                            }
                                                                            else{
                                                                                if(ds[curr3].find("start")==ds[curr3].end())
                                                                                ds[curr]["start"] = numtostring(code.size());
                                                                                else ds[curr]["start"] = ds[curr3]["start"];
                                                                                ds[curr]["type"] = ds[curr3]["type"];

                                                                                // code.push_back(ds[curr]["type"]);
                                                                                code.push_back(ds[curr1]["var"]+" = "+ds[curr3]["var"]);
                                                                            }
                                                                            generalmap[$$].vinit.classname = generalmap[$3].classname;
                                                                            generalmap[$$].vinit.isnewclass = generalmap[$3].isnewclass;

                                                                            
                                                                            // code.push_back("start="+ds[curr]["start"]);
                                                                            
                                                                            // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                            // code.push_back("hello");
                                                                            }
                    |   VARIABLEDECLARATORID {$$ = new_temp(); generalmap[$$]= generalmap[$1];}
 
VARIABLEDECLARATORID    :   IDENTIFIER {$$ = new_temp(); generalmap[$$].vid.name= chartostring($1); 
 int curr = chartonum($$);

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring($1);

}
                        |   IDENTIFIER DIMS  {$$ = new_temp(); generalmap[$$].vid.name= chartostring($1);  generalmap[$$].vid.num = temp[$2];
                        int curr = chartonum($$);
                                    ds[curr]["var"] = chartostring($1);
                        /*TODO*/
                        }


VARIABLEINITIALIZER :    EXPRESSION {$$ = new_temp(); generalmap[$$]= generalmap[$1]; ds[chartonum($$)] = ds[chartonum($1)]; }
                    |   ARRAYINITIALIZER {$$ = $1;}

EXPRESSION  :  ASSIGNMENTEXPRESSION {$$ = $1; }

ASSIGNMENTEXPRESSION    :   CONDITIONALEXPRESSION {
                            $$ = $1;
                        }
                        |   ASSIGNMENT {$$ = $1;/*TODO CHECK multiple assign*/} 

ASSIGNMENT  :   LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION {
    
    // code.pb($1.val + $2.val + $3.val )
    // string t  =new_var();
    // code.pb(t + " = " + $1.val);
    // $$.val = t;
    $$ = $1;
    int curr1 = chartonum($1), curr3 = chartonum($3), curr2 = chartonum($2);
    type_check(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    type_conversion(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    // code.push_back("hello");
    code.push_back(ds[curr1]["var"]+" "+ds[curr2]["op"]+" "+ds[curr3]["var"]);

}

LEFTHANDSIDE    :   EXPRESSIONNAME    {$$ = $1;}
                |   IDENTIFIER {    $$ = new_temp();
                                    int curr = chartonum($$);
                                    ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring($1);
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
                |   FIELDACCESS {$$ = $1;}
                |   ARRAYACCESS {   $$ = $1;
                                    ds[chartonum($$)]["var"] = ds[chartonum($$)]["array"]+"[ "+ds[chartonum($1)]["var"]+" ]";
                }

ASSIGNMENTOPERATOR  :  EQUALS {$$ = new_temp();int curr = chartonum($$);
                                ds[curr]["op"] = "=";}
                    |  MULTIPLYEQUALS {$$ = new_temp();int curr = chartonum($$);
                                ds[curr]["op"] = "*=";}
                    |   DIVIDEEQUALS {$$ = new_temp();int curr = chartonum($$);
                                ds[curr]["op"] = "/=";}
                    |   MODEQUALS {$$ = new_temp();int curr = chartonum($$);
                                ds[curr]["op"] = "%=";}
                    |   PLUSEQUALS {$$ = new_temp();int curr = chartonum($$);
                                ds[curr]["op"] = "+=";}
                    |   MINUSEQUALS {$$ = new_temp();int curr = chartonum($$);
                                ds[curr]["op"] = "-=";}
                    
FIELDACCESS: PRIMARY DOT IDENTIFIER {$$ = new_temp();
                                        int curr = chartonum($$), curr1 = chartonum($1);
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring($3);
                                        }else assert(0 && "unexpected type\n");
                                        }
            |	SUPER DOT IDENTIFIER
            |	IDENTIFIER DOT SUPER DOT IDENTIFIER

PRIMARY: PRIMARYNONEWARRAY  {$$ = $1;
                            if(ds[chartonum($$)].find("array")!=ds[chartonum($$)].end())
                            ds[chartonum($$)]["var"] = ds[chartonum($$)]["array"]+"["+ds[chartonum($1)]["var"]+"]"; }
        |	ARRAYCREATIONEXPRESSION {$$ = $1;}

PRIMARYNONEWARRAY: LITERAL  {$$ = $1;}
                  |	CLASSLITERAL    {$$ = $1;}
                  |	THIS    {$$ = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum($$);
                            ds[curr]["this"] = chartostring("YES");
                            }
                  |	IDENTIFIER DOT THIS
                  |	OPENPARAN EXPRESSION CLOSEPARAN {$$ = $2;}
                  |	CLASSINSTANCECREATIONEXPRESSION       {$$ = $1; generalmap[$$].isnewclass = true;}  
                  |	FIELDACCESS {$$ = $1;}
                  |	ARRAYACCESS {$$ = $1;}
                  |	METHODINVOCATION    {$$ = $1;}
                  |	METHODREFERENCE

LITERAL: INTEGERLITERAL {$$ = new_temp();  ds[chartonum($$)]["type"] = "int"; ds[chartonum($$)]["var"] = new_var(); ds[chartonum($$)]["start"] = numtostring(code.size()); tempinitval[ds[chartonum($$)]["var"]]= chartonum($1); code.push_back(ds[chartonum($$)]["var"]+ " = "+ chartostring($1));}
        |	FLOATINGPOINTLITERAL {$$ = new_temp(); ds[chartonum($$)]["type"] = "float"; ds[chartonum($$)]["start"] = numtostring(code.size());ds[chartonum($$)]["var"] = new_var(); code.push_back(ds[chartonum($$)]["var"]+ " = "+ chartostring($1));}
        |	BOOLEANLITERAL {$$ = new_temp(); ds[chartonum($$)]["type"] = "bool";ds[chartonum($$)]["start"] = numtostring(code.size()); ds[chartonum($$)]["var"] = new_var(); code.push_back(ds[chartonum($$)]["var"]+ " = "+ chartostring($1));}
        |	CHARACTERLITERAL {$$ = new_temp(); ds[chartonum($$)]["type"] = "char";ds[chartonum($$)]["start"] = numtostring(code.size()); ds[chartonum($$)]["var"] = new_var(); code.push_back(ds[chartonum($$)]["var"]+ " = "+ chartostring($1));}
        |	STRINGLITERAL {$$ = new_temp(); ds[chartonum($$)]["type"] = "String";ds[chartonum($$)]["start"] = numtostring(code.size()); ds[chartonum($$)]["var"] = new_var(); code.push_back(ds[chartonum($$)]["var"]+ " = "+ chartostring($1));}
        |	TEXTBLOCK {$$ = new_temp(); ds[chartonum($$)]["type"] = "String";ds[chartonum($$)]["start"] = numtostring(code.size()); ds[chartonum($$)]["var"] = new_var(); code.push_back(ds[chartonum($$)]["var"]+ " = "+ chartostring($1));}
        |	NULLLITERAL {$$ = new_temp(); ds[chartonum($$)]["type"] = "null";ds[chartonum($$)]["start"] = numtostring(code.size()); ds[chartonum($$)]["var"] = new_var(); code.push_back(ds[chartonum($$)]["var"]+ " = "+ chartostring($1));}

CLASSLITERAL: IDENTIFIER DOTCLASS
             |	NUMERICTYPE DOTCLASS
             |	BOOLEAN DOTCLASS
             |	VOID DOTCLASS
             | IDENTIFIER SQUARESTAR DOTCLASS
             |	NUMERICTYPE SQUARESTAR DOTCLASS
             |	BOOLEAN SQUARESTAR DOTCLASS

SQUARESTAR  :   OPENSQUARE CLOSESQUARE
            |   SQUARESTAR  OPENSQUARE CLOSESQUARE

CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION {$$ = $1;}
                                |	EXPRESSIONNAME DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION
                                |	IDENTIFIER DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION
                                |	PRIMARY DOT UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION

UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION:     NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN {$$ = new_temp(); generalmap[$$].isnewclass = true; generalmap[$$].classname = ds[ chartonum($2)]["var"]; ds[ chartonum($$)] = ds[ chartonum($2)];  }
                                            |   NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY {/*TODO*/}
                                            |   NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN {/*TODO*/}
                                            |   NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY {/*TODO*/}
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN
                                            |   NEW TYPEARGUMENTS CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY

CLASSORINTERFACETYPETOINSTANTIATE:  IDENTIFIER  {   $$ = new_temp(); ds[ chartonum($$)]["var"] = chartostring($1); ds[ chartonum($$)]["class"] = "true";
                                                     }

ARGUMENTLIST: EXPRESSION    {$$ = $1;
                            ds2[chartonum($$)]["type"].push_back(ds[chartonum($1)]["type"]);
                            ds2[chartonum($$)]["var"].push_back(ds[chartonum($1)]["var"]);
                            }
            |   ARGUMENTLIST COMMA EXPRESSION   {$$ = new_temp();
                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }

METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN   {   $$ = new_temp();
                                                        int curr = chartonum($$), curr1 = chartonum($1);
                                                        string name = ds[curr1]["var"];
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = methods[name].rettype.name;
                                                        vector<string> types;
                                                        type_check_function(name,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = numtostring(code.size());
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+name);
                                                        else code.push_back("call, "+name);
}
                 |  METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN    {   $$ = new_temp();
                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                        string name = ds[curr1]["var"] ;
                                                        ds[curr]["type"] = methods[name].rettype.name;
                                                        vector<string> types;
                                                        // cout<<"type2 : "<<ds2[curr3]["type"].size()<<"\n";
                                                        for(auto i:ds2[curr3]["type"]){
                                                            types.push_back(i);
                                                        }
                                                        type_check_function(name,types);    // takes in name of function and types of parameters
                                                        for(auto i:ds2[curr3]["var"])
                                                        code.push_back("push param "+i);
                                                        ds[curr]["start"] = ds[curr3]["start"];
                                                        if(ds[curr]["type"]!="void"){
                                                        ds[curr]["var"] = new_var();
                                                        code.push_back(ds[curr]["var"]+" = call, "+name);
                                                        }
                                                        else code.push_back("call, "+name);
}
                 |	IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  {   /* Method invocation using object?  */
                                                          $$ = new_temp();
                                                        int curr = chartonum($$);
                                                        string name = chartostring($1), name2 = chartostring($3);
                                                        objdetails detail = getobjdetails(name,name2);
                                                        string fname = "";
                                                        if(detail.ismethod&&not_static_check(detail.method.access)){
                                                            fname = pref[chartostring($1)]+chartostring($3);
                                                            // ds[curr]["type"] = detail.field.typ.name;
                                                        }else{
                                                            object_error_func(name,name2,yylineno);
                                                        }
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = detail.method.rettype.name;
                                                        // cout<<""
                                                        // code.push_back(ds[curr]["type"]);
                                                        vector<string> types;
                                                        type_check_function_obj(detail.method.argtype,types);    // takes in name of function and types of parameters
                                                        // cout<<"curr var "<<ds[curr]["var"]<<"\n";
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
}
                 |	IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN {   /* Method invocation using object?  */
                                                          $$ = new_temp();
                                                        int curr = chartonum($$), curr5 = chartonum($5);
                                                        string name = chartostring($1), name2 = chartostring($3);
                                                        objdetails detail = getobjdetails(name,name2);
                                                        string fname = "";
                                                        if(detail.ismethod&&not_static_check(detail.method.access)){
                                                            fname = pref[chartostring($1)]+chartostring($3);
                                                            // ds[curr]["type"] = detail.field.typ.name;
                                                        }else{
                                                            object_error_func(name,name2,yylineno);
                                                        }
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = detail.method.rettype.name;;
                                                        // cout<<"curr typed "<<ds[curr]["type"]<<"\n";
                                                        vector<string> types;
                                                        for(auto i:ds2[curr5]["type"]){
                                                            types.push_back(i);
                                                        }
                                                        type_check_function_obj(detail.method.argtype,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
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

ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS {/*NOT SUPPORTED*/}
                        |	NEW CLASSORINTERFACETYPE DIMEXPRS DIMS {/*NOT SUPPORTED*/}
                        |	NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER { $$ = new_temp();  generalmap[$$].typ.name= chartostring($2);  generalmap[$$].vinit = generalmap[$4].vinit; assert (generalmap[$4].vinit.dims.size() == temp[$3]); }
                        |	NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER {/*NOT SUPPORTED*/}
                        |   NEW PRIMITIVETYPE DIMEXPRS  { $$ = new_temp();  generalmap[$$].typ.name= chartostring($2);  generalmap[$$].vinit = generalmap[$3].vinit; ds[chartonum($$)]["arr"] = "true"; ds[chartonum($$)]["var"] = ds[chartonum($3)]["var"]; ds[chartonum($$)]["type"] = chartostring($2); ds[chartonum($$)]["start"] = ds[chartonum($3)]["start"];}
                        |	NEW CLASSORINTERFACETYPE DIMEXPRS  {/*NOT SUPPORTED*/}
                        |   NEW PRIMITIVETYPE DIMS {/*NOT SUPPORTED*/}
                        |	NEW CLASSORINTERFACETYPE DIMS {/*NOT SUPPORTED*/}
                        |   NEW PRIMITIVETYPE  {/*TODO whats this*/}
                        |	NEW CLASSORINTERFACETYPE {/*TODO whats this*/}

ARRAYINITIALIZER    :  OPENCURLY ARRAYINITIALIZER1 CLOSECURLY {$$=$2; generalmap[$$].vinit.dims.push_back(generalmap[$$].num); generalmap[$$].num=0;}
                    |   OPENCURLY CLOSECURLY {$$=new_temp(); generalmap[$$].vinit.dims.push_back(0);}

ARRAYINITIALIZER1   :  VARIABLEINITIALIZERLIST {$$= $1;}
                    |   COMMA {$$ = new_temp(); generalmap[$$].num=2;} 
                    |   VARIABLEINITIALIZERLIST COMMA {$$ = $1; generalmap[$$].num++;}

DIMEXPRS: DIMEXPR {$$ = new_temp(); generalmap[$$].vinit.dims.push_back(generalmap[$1].num); ds[ chartonum($$)] = ds[ chartonum($1)];}
        |   DIMEXPRS DIMEXPR {$$ = $1; generalmap[$$].vinit.dims.push_back(generalmap[$2].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum($1)]["var"]+" *"+ds[chartonum($2)]["type"]+" "+ds[ chartonum($2)]["var"]);
                              ds[ chartonum($$)]["var"] = t;  }

DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE  {$$ = new_temp(); generalmap[$$].num = varaddrstoint(ds[chartonum($2)]["var"]); ds[ chartonum($$)] = ds[ chartonum($2)];}
       
VARIABLEINITIALIZERLIST :   VARIABLEINITIALIZER {$$=$1; generalmap[$$].num=1;}
                        |   VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER {$$=$1; generalmap[$$].num++; assert(generalmap[$$].vinit.dims == generalmap[$3].vinit.dims);}





ARRAYACCESS: EXPRESSIONNAME OPENSQUARE EXPRESSION CLOSESQUARE
            |	PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE {
                $$ = new_temp(); 
                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                if(ds[curr3]["type"]!="int"&&ds[curr3]["type"]!="long"&&ds[curr3]["type"]!="short"&&ds[curr3]["type"]!="byte")
                cout<<"Array index not integer\n";
                ds[curr] = ds[curr1];   
                ds[curr]["var"] = new_var();
                int i = stringtonum(ds[curr]["dims"])+1;
                ds[curr]["dims"] = numtostring(stringtonum(ds[curr]["dims"])+1);
                string t = new_var();
                // cout<<"index"<<i<<"\n";
                // cout<<ds[curr]["array"]<<"\n";
                // cout<<symboltable[ds[curr]["array"]].dims.size()<<"\n";
                int bound = symboltable[ds[curr]["array"]].dims[i];
                code.push_back(t+" = "+ds[curr1]["var"]+" * "+numtostring(bound));
                code.push_back(ds[curr]["var"]+" = "+t+" + "+ds[curr3]["var"]); 
            }
            |	IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE    {
                $$ = new_temp();
                int curr = chartonum($$), curr3 = chartonum($3);
                string name = chartostring($1);
                ds[curr]["dims"] = "0";
                ds[curr]["array"] = name;
                ds[curr]["start"] = ds[curr3]["start"];
                ds[curr]["var"] = ds[curr3]["var"];
                ds[curr]["type"] = symboltable[name].typ.name;
                if(ds[curr3]["type"]!="int"&&ds[curr3]["type"]!="long"&&ds[curr3]["type"]!="short"&&ds[curr3]["type"]!="byte")
                cout<<"Array index not integer\n";
                // code.push_back(ds[curr]["var"]+" = "+ds[curr3]["var"]);
            }

CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  {$$ = $1;}
                      |	CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION {}

CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION   {$$ = $1; } /*TODO if(false || false) case not handled */
                        |	CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION   {   $$ = new_temp();
                                                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                        backpatch(ds3[curr1]["falselist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"||");
                                                                                        ds3[curr]["falselist"] = ds3[curr3]["falselist"];
                                                                                        ds3[curr]["truelist"] = merge(ds3[curr1]["truelist"],ds3[curr3]["truelist"]);
                                                                                        // backpatch(ds3[curr1]["truelist"],code.size());
                                                                                        // backpatch(ds3[curr3]["truelist"],code.size());
                                                                                        // ds[curr]["var"] = new_var();
                                                                                        // code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" || "+ds[curr3]["var"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}

CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION     {$$ = $1; }
                         |	CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION   {   $$ = new_temp();
                                                                                        int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}

INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION   {$$ = $1;}
                      |	INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  {    $$ = new_temp();
                                                                            int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }

EXCLUSIVEOREXPRESSION: ANDEXPRESSION    {$$ = $1; }
                      |	EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION {           $$ = new_temp();
                                                                            int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
ANDEXPRESSION: EQUALITYEXPRESSION   {$$ = $1; }
              |	ANDEXPRESSION AND EQUALITYEXPRESSION    {   $$ = new_temp();
                                                                            int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }

EQUALITYEXPRESSION: RELATIONALEXPRESSION    {$$ = $1; int curr = chartonum($$);
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
                   |	EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION    {   $$ = new_temp();
                                                                                    int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                    type_check(ds[curr1]["type"],ds[curr3]["type"],"==");
                                                                                    backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                    backpatch(ds3[curr1]["falselist"],stringtonum(ds[curr3]["start"]));
                                                                                    backpatch(ds3[curr3]["truelist"],code.size());
                                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                                    ds[curr]["type"] = "bool";
                                                                                    ds[curr]["var"] = new_var();
                                                                                    // code.push_back(ds[curr]["var"]);
                                                                                    code.push_back("if "+ds[curr1]["var"]+" == "+ds[curr3]["var"]+" goto ");
                                                                                    ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                    code.push_back("goto ");
                                                                                    ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                    ds[curr]["start"] = ds[curr1]["start"];
                   }
                   |	EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION       {   
                                                                                    $$ = new_temp();
                                                                                    int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                    type_check(ds[curr1]["type"],ds[curr3]["type"],"!=");
                                                                                    backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                    backpatch(ds3[curr1]["falselist"],stringtonum(ds[curr3]["start"]));
                                                                                    backpatch(ds3[curr3]["truelist"],code.size());
                                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                                    ds[curr]["type"] = "bool";
                                                                                    ds[curr]["var"] = new_var();
                                                                                    code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" != "+ds[curr3]["var"]);
                                                                                    code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                    ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                    code.push_back("goto ");
                                                                                    ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                    ds[curr]["start"] = ds[curr1]["start"];
                   }

RELATIONALEXPRESSION: SHIFTEXPRESSION   {   $$ = $1; int curr = chartonum($$);
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
                     |	RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION    {      // IS backpatching for $1 required?
                                                                                $$ = new_temp();
                                                                                // code.push_back("REL0 "+ds[chartonum($1)]["start"]);
                                                                                // code.push_back("REL1 "+ds[chartonum($3)]["start"]);
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" < "+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"][0]<<"\n";
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION   {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" > "+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION    {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($4);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">=");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >= "+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($4);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<=");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" <= "+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
                     |	INSTANCEOFEXPRESSION

SHIFTEXPRESSION: ADDITIVEEXPRESSION {$$ = $1;}
                |	SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION   {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION     {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                |	SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }

ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION    {   $$ = $1; }
                   |	ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION    {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                   |	ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION   {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }

MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION   {$$ = $1;}
                         |	MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION   {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                         |	MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION     {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
                         |	MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION        {   $$ = new_temp();
                                                                                int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }

UNARYEXPRESSION: PREINCREMENTEXPRESSION {$$ = $1;}
                |	PREDECREMENTEXPRESSION  {$$ = $1;}
                |	PLUS UNARYEXPRESSION    {$$ = $2;
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                            type_check_unary(ds[curr2]["type"],"+");}
                |	MINUS UNARYEXPRESSION   {   $$ = new_temp();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
                |	UNARYEXPRESSIONNOTPLUSMINUS {$$ = $1;}

PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION    {   $$ = new_temp();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    assert(0&& "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+" +1");
                                                code.push_back(ds[curr2]["var"]+" = "+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] += 1;  /* Modify the actual underlying variable */
                    }

PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  {   $$ = new_temp();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+" -1");
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr2]["var"]+ " = "+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] -= 1;
                    }

UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  {$$ = $1;}
                            |	COMPLEMENT UNARYEXPRESSION  {   $$ = new_temp();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
                            |	NOT UNARYEXPRESSION {   $$ = new_temp();
                                                int curr = chartonum($$), curr2 = chartonum($2);
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
                            
POSTFIXEXPRESSION: PRIMARY  {$$ = $1;}
                  |	EXPRESSIONNAME  {$$ = $1;}
                  | IDENTIFIER  {   $$ = new_temp();
                                    int curr = chartonum($$);
                                    /* How to access symbol table entry of a terminal */
                                    ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                    ds[curr]["identifier"] = "YES";
                                    // cout<<"\n\n\n";
                                    // for(auto i:code){
                                    //     cout<<i<<"\n";
                                    // }
                                    ds[curr]["start"] = numtostring(code.size());
                                    ds[curr]["var"] = chartostring($1);
                                    // ds[curr]["var"] = 
                                    /* How to pass values from here? */
                  }
                  |	POSTINCREMENTEXPRESSION {$$ = $1;}
                  |	POSTDECREMENTEXPRESSION {$$ = $1;}

POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS {   $$ = new_temp();
                                                int curr = chartonum($$), curr1 = chartonum($1);
                                                type_check_unary(ds[curr1]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                code.push_back(ds[curr1]["var"]+ " = "+ ds[curr]["var"]+" +1");
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
}

POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS   {   $$ = new_temp();
                                                int curr = chartonum($$), curr1 = chartonum($1);
                                                type_check_unary(ds[curr1]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                code.push_back(ds[curr1]["var"]+ " = "+ ds[curr]["var"]+" -1");
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                // ds[curr]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
                                                // ds[curr1]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
}

INSTANCEOFEXPRESSION: RELATIONALEXPRESSION INSTANCEOF REFERENCETYPE


METHODDECLARATION:  METHODHEADER METHODBODY {
    $$ =$1;
    method_det[curr_class][ds[chartonum($$)]["method_name"]].end = code.size(); 
    
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$1].name<<endl;
    
}


                    |   SUPER1 METHODHEADER METHODBODY{
                        $$ =$2;
                        method_det[curr_class][ds[chartonum($$)]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;

    // assert(methods.find(generalmap[$2].name) == methods.end());

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    // vector <type> argtype;
    // methods[generalmap[$2].name].lineno = yylineno;
    
    // methods[generalmap[$2].name].access = generalmap[$1].modifiers;


    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
         
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    //     classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


}
                    |   SUPER2 METHODHEADER METHODBODY{$$ =$2;
                    method_det[curr_class][ds[chartonum($$)]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;
    //     assert(methods.find(generalmap[$2].name) == methods.end());
      

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    //     methods[generalmap[$2].name].lineno = yylineno;

    // methods[generalmap[$2].name].access = generalmap[$1].modifiers;

    // vector <type> argtype;
    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
        
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    // classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


}
                    |   SUPER3 METHODHEADER METHODBODY{$$ =$2;
                    method_det[curr_class][ds[chartonum($$)]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;
    //     assert(methods.find(generalmap[$2].name) == methods.end());

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    //     methods[generalmap[$2].name].lineno = yylineno;

    // methods[generalmap[$2].name].access = generalmap[$1].modifiers;

    // vector <type> argtype;

    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
        
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    //     classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


}
                    |   METHODMODIFIERS METHODHEADER METHODBODY{$$ =$2;
                    method_det[curr_class][ds[chartonum($$)]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;
    //     assert(methods.find(generalmap[$2].name) == methods.end());

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    //     methods[generalmap[$2].name].lineno = yylineno;

    // methods[generalmap[$2].name].access = generalmap[$1].modifiers;

    // vector <type> argtype;

    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
        
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    //     classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


}
                    | AT OVERRIDE METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER1 METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER2 METHODHEADER METHODBODY  
                    | AT OVERRIDE SUPER3 METHODHEADER METHODBODY  
                    | AT OVERRIDE METHODMODIFIERS METHODHEADER METHODBODY  


METHODHEADER: TYPE METHODDECLARATOR  { $$ = $2;  generalmap[$$].typ.name = chartostring($1); 
tempnextscope(); 

assert(methods.find(generalmap[$2].name) == methods.end());
    methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    methods[generalmap[$2].name].lineno = yylineno;
    
    vector <type> argtype;
     

    for (auto x : generalmap[$2].farglist)
        {argtype.push_back(x.typ);
         }
    methods[generalmap[$2].name].argtype = argtype;
        classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


for (auto x : generalmap[$$].farglist){
symboltable[x.vid.name].typ.dims= x.vid.num;
        symboltable[x.vid.name].typ.name= x.typ.name;
        symboltable[x.vid.name].scope = scope;
        symboltable[x.vid.name].lineno = yylineno;
        symboltable[x.vid.name].token = "IDENTIFIER";

        // cout<<x.vid.name;
        printvarentry(symboltable[x.vid.name]);
        preservedsymboltable[{x.vid.name, scope}]= symboltable[x.vid.name];
        
        }
        //  in reverse
        ll toffset=0;
        for(int ii=generalmap[$$].farglist.size()-1 ; ii>=0; ii-- ){

                toffset -=   gettypesize(symboltable[generalmap[$$].farglist[ii].vid.name].typ.name);
                              
        symboltable[generalmap[$$].farglist[ii].vid.name].offset= toffset;
        }
        
        


        }
            |   VOID METHODDECLARATOR { $$ = $2;  generalmap[$$].typ.name = chartostring($1); 
            tempnextscope();

            assert(methods.find(generalmap[$2].name) == methods.end());
    methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    methods[generalmap[$2].name].lineno = yylineno;
    
    vector <type> argtype;
     

    for (auto x : generalmap[$2].farglist)
        {argtype.push_back(x.typ);
         }
    methods[generalmap[$2].name].argtype = argtype;
        classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];



for (auto x : generalmap[$$].farglist){
symboltable[x.vid.name].typ.dims= x.vid.num;
        symboltable[x.vid.name].typ.name= x.typ.name;
        symboltable[x.vid.name].scope = scope;
        symboltable[x.vid.name].lineno = yylineno;
        symboltable[x.vid.name].token = "IDENTIFIER";

        // cout<<x.vid.name;
        printvarentry(symboltable[x.vid.name]);
        preservedsymboltable[{x.vid.name, scope}]= symboltable[x.vid.name];
        
        }}
            |   TYPE METHODDECLARATOR THROWS2
             |	TYPEPARAMETERS TYPE METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS TYPE METHODDECLARATOR 
             |  VOID METHODDECLARATOR THROWS2
             |	TYPEPARAMETERS VOID METHODDECLARATOR THROWS2
             |  TYPEPARAMETERS VOID METHODDECLARATOR 


THROWS2: THROWS EXCEPTIONTYPELIST

EXCEPTIONTYPELIST: EXCEPTIONTYPE    
                |   EXCEPTIONTYPELIST COMMA EXCEPTIONTYPE

EXCEPTIONTYPE: CLASSTYPE

METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  {$$ = new_temp(); generalmap[$$].num = 0; generalmap[$$].name = chartostring($1);
 int curr = chartonum($$);              
                                        method_det[curr_class][chartostring($1)].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring($1);
                                        code.push_back("begin func "+chartostring($1));
                                        // cout<<"methodhead "<<ds[chartonum($$)]["method_name"]<<"\n";
                                        }
                |   IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN {$$ = new_temp(); generalmap[$$]= generalmap[$3]; generalmap[$$].num = 0; generalmap[$$].name = chartostring($1);int curr = chartonum($$), curr3 = chartonum($3);
                method_det[curr_class][chartostring($1)].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring($1);
                                        code.push_back("begin func "+chartostring($1));
                                        for(auto i:ds2[curr3]["param"])
                                        code.push_back("pop param, "+ i);}
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN 
                |   IDENTIFIER OPENPARAN CLOSEPARAN DIMS
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN CLOSEPARAN DIMS
                |   IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN DIMS
                |   IDENTIFIER RECEIVERPARAMETER COMMA OPENPARAN FORMALPARAMETERLIST CLOSEPARAN 

RECEIVERPARAMETER:  TYPE THIS
                |   TYPE IDENTIFIER DOT THIS

FORMALPARAMETERLIST: FORMALPARAMETER { $$ = new_temp(); generalmap[$$].farglist.push_back(generalmap[$1].farg);                                        int curr = chartonum($$), curr1 = chartonum($1);
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
                    |   FORMALPARAMETERLIST COMMA FORMALPARAMETER {$$= new_temp(); generalmap[$$]= generalmap[$1]; generalmap[$$].farglist.push_back(generalmap[$3].farg);   int curr = chartonum($$), curr1 = chartonum($1),curr3 = chartonum($3);
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }

FORMALPARAMETER:  TYPE VARIABLEDECLARATORID { $$ = new_temp(); generalmap[$$].farg.typ.name = chartostring($1); generalmap[$$].farg.typ.dims = generalmap[$2].vid.num; generalmap[$$].farg.vid = generalmap[$2].vid;
     int curr = chartonum($$), curr2 = chartonum($2);
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
                |	VARIABLEARITYPARAMETER
                |   FINAL TYPE VARIABLEDECLARATORID {   $$ = new_temp();
                                        int curr = chartonum($$), curr2 = chartonum($2);
                                        ds[curr]["var"] = ds[curr2]["var"];
}


VARIABLEARITYPARAMETER  :  TYPE TRIPLEDOT IDENTIFIER
                        |   FINAL TYPE TRIPLEDOT IDENTIFIER


METHODBODY: BLOCK   {$$ = $1;}
           |	SEMICOLON

INSTANCEINITIALIZER: BLOCK  

STATICINITIALIZER: STATIC BLOCK

BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY {$$ = $2;  }
    |   OPENCURLY  CLOSECURLY

BLOCKSTATEMENTS: BLOCKSTATEMENT    {$$ = $1;  
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
                |  BLOCKSTATEMENTS BLOCKSTATEMENT { $$ = new_temp();
                                                    int curr = chartonum($$), curr1 = chartonum($1), curr2 = chartonum($2);
                                                    ds3[curr]["continuelist"] = merge(ds3[curr1]["continuelist"], ds3[curr2]["continuelist"]);
                                                    ds3[curr]["breaklist"] = merge(ds3[curr1]["breaklist"], ds3[curr2]["breaklist"]);
                                                    if(ds[curr1].find("start")!=ds[curr1].end())
                                                    ds[curr]["start"] = ds[curr1]["start"];
                                                     else if(ds[curr2].find("start")!=ds[curr2].end())
                                                     ds[curr]["start"] = ds[curr2]["start"];
                                                    // code.push_back("start = "+ds[curr]["start"]);
                }

BLOCKSTATEMENT: LOCALCLASSORINTERFACEDECLARATION
               |	LOCALVARIABLEDECLARATIONSTATEMENT   {$$ = $1; 
                
               }
               |	STATEMENT   {$$ = $1;
               }
               |    PRINTLN {code.push_back("print "+ chartostring($1).substr(19,chartostring($1).size() -21));}
 
LOCALCLASSORINTERFACEDECLARATION: CLASSDECLARATION  

LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON   {$$ = $1;}

LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST {

                            if(generalmap[$3].typ.name != "")assert(chartostring($2)== generalmap[$3].typ.name);
                            $$ = $3;
                            int curr = chartonum($$);
                                                    // assert(ds[curr].find("start")!=ds[curr].end());
                            // assert()
                            if(ds[curr].find("start")==ds[curr].end())
                            ds[curr]["start"] = numtostring(code.size());
                            string t = chartostring($2);
                            for(auto t2:ds2[curr]["type"]){
                                if(!((t=="double"||t=="float")&&(t2=="int"||t2=="long"))){
                                    if(!((t=="double"&&t2=="float")||(t=="long"&&t2=="int")))
                                        if(t2!=chartostring($2))
                                        typ_error(chartostring($2),t2,int(yylineno));
                                    // }
                                }
                            }
                            for (auto x: generalmap[$3].vlist){
                            
                            // cout<<x.first.name<<endl;
                            assert(symboltable.find(x.first.name) == symboltable.end());
                            /*ADD SIMILAR FOR FILEDS AND METHODS*/

                           symboltable[x.first.name].typ.dims= x.first.num;
                            symboltable[x.first.name].typ.name= chartostring($2);
                             reverse(all(x.second.dims));
                            symboltable[x.first.name].dims = x.second.dims;
                            symboltable[x.first.name].scope = scope;
                            symboltable[x.first.name].lineno = yylineno;
                            symboltable[x.first.name].token = "IDENTIFIER";
                            symboltable[x.first.name].offset = curoffset;
                          ll arrsize = 1;
                            for(auto x: symboltable[x.first.name].dims){
                                ll ft = x;
                                 if(x<0){
                                    auto g = numtostring(tempinitval[dimtoid[-x]]);
                                    assert(isnum(g) && "only constant direct expressions supported");
                                    ft = stringtonum(g);


                                }
                                arrsize *= ft;
                               
                            }   
                            ll increment = arrsize* gettypesize(symboltable[x.first.name].typ.name);
                              curoffset += increment;
                              code.push_back("stackpointer + "+ numtostring(increment));

                            // TODO support class sizes

                            // cout<<x.first.name;
                            // TODO: printvarentry needed
                            printvarentry(symboltable[x.first.name]);
                            preservedsymboltable[{x.first.name,scope}] = symboltable[x.first.name];
                        }
                        }
                        |   LOCALVARIABLETYPE VARIABLEDECLARATORLIST {

                            if(generalmap[$2].typ.name != "")assert(chartostring($1)== generalmap[$2].typ.name);
                            $$ = $2;
                            int curr = chartonum($$);
                                                    // assert(ds[curr].find("start")!=ds[curr].end());
                            // assert()
                            if(ds[curr].find("start")==ds[curr].end())
                            ds[curr]["start"] = numtostring(code.size());
                            string t = chartostring($1);
                            for(auto t2:ds2[curr]["type"]){
                                if(!((t=="double"||t=="float")&&(t2=="int"||t2=="long"))){
                                    if(!((t=="double"&&t2=="float")||(t=="long"&&t2=="int")))
                                        if(t2!=chartostring($1))
                                        typ_error(chartostring($1),t2,int(yylineno));
                                    // }
                                }
                            }
                            
                            for (auto x: generalmap[$2].vlist){
                            
                            // cout<<x.first.name<<endl;
                            assert(symboltable.find(x.first.name) == symboltable.end());
                            /*ADD SIMILAR FOR FILEDS AND METHODS*/

                           symboltable[x.first.name].typ.dims= x.first.num;
                            symboltable[x.first.name].typ.name= chartostring($1);
                             reverse(all(x.second.dims));
                            symboltable[x.first.name].dims = x.second.dims;
                            symboltable[x.first.name].scope = scope;
                            symboltable[x.first.name].lineno = yylineno;
                            symboltable[x.first.name].token = "IDENTIFIER";
                            symboltable[x.first.name].offset = curoffset;
                            ll arrsize = 1;
                            for(auto x: symboltable[x.first.name].dims){
                                ll ft = x;
                                 if(x<0){
                                    auto g = numtostring(tempinitval[dimtoid[-x]]);
                                   

                                    assert(isnum(g) && "only constant direct expressions supported");
                                    ft = stringtonum(g);


                                }
                                arrsize *= ft;

                            }
                            
                              
                            ll increment = arrsize* gettypesize(symboltable[x.first.name].typ.name);
                              curoffset += increment;
                              code.push_back("stackpointer + "+ numtostring(increment));
                              
                              // TODO support class sizes

                            // cout<<x.first.name;
                            printvarentry(symboltable[x.first.name]);
                            preservedsymboltable[{x.first.name,scope}] = symboltable[x.first.name];
                        }
                        }

LOCALVARIABLETYPE: TYPE {$$ = $1;}
                  |	VAR {$$ = $1;}


STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT {$$ = $1; int curr = chartonum($$); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
          |	LABELEDSTATEMENT    {$$ = $1; int curr = chartonum($$); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
          |	IFTHENSTATEMENT {$$ = $1; int curr = chartonum($$); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
          |	IFTHENELSESTATEMENT {$$ = $1; int curr = chartonum($$); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
          |	WHILESTATEMENT  {$$ = $1; int curr = chartonum($$); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
          |	FORSTATEMENT    {$$ = $1; int curr = chartonum($$); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}

STATEMENTWITHOUTTRAILINGSUBSTATEMENT    :BLOCK  {$$ = $1;}
                                                    // assert(ds[curr].find("start")!=ds[curr].end());}
                                     |	EMPTYSTATEMENT  {$$ = $1;}
                                     |	EXPRESSIONSTATEMENT {$$ = $1;}
                                     |	ASSERTSTATEMENT {$$ = $1;}
                                     |	BREAKSTATEMENT  {$$ = $1;}
                                     |	CONTINUESTATEMENT   {$$ = $1;}
                                     |	RETURNSTATEMENT {$$ = $1;}
                                     |	THROWSTATEMENT  {$$ = $1;}
                                     |	YIELDSTATEMENT  {$$ = $1;}

EMPTYSTATEMENT: SEMICOLON   {$$ = new_temp();}

EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  {$$ = $1; }

STATEMENTEXPRESSION: ASSIGNMENT {$$ = $1;}
                    |	PREINCREMENTEXPRESSION  {$$ = $1;}
                    |	PREDECREMENTEXPRESSION  {$$ = $1;}
                    |	POSTINCREMENTEXPRESSION {$$ = $1;}
                    |	POSTDECREMENTEXPRESSION {$$ = $1;}
                    |	METHODINVOCATION    {$$ = $1;}
                    |	CLASSINSTANCECREATIONEXPRESSION {$$ = $1;}

ASSERTSTATEMENT: ASSERT EXPRESSION SEMICOLON
                |	ASSERT EXPRESSION COLON EXPRESSION SEMICOLON

BREAKSTATEMENT: BREAK SEMICOLON     {   $$ = new_temp();
                                            int curr = chartonum($$);
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
                |   BREAK IDENTIFIER SEMICOLON

CONTINUESTATEMENT: CONTINUE SEMICOLON   {   $$ = new_temp();
                                            int curr = chartonum($$);
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
                |   CONTINUE IDENTIFIER SEMICOLON

RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON    {$$ = new_temp();
                                                    int curr = chartonum($$), exp = chartonum($2);
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
                |   RETURN SEMICOLON    {$$ = new_temp();
                                                    int curr = chartonum($$);
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }

THROWSTATEMENT: THROW EXPRESSION SEMICOLON

YIELDSTATEMENT: YIELD EXPRESSION SEMICOLON

LABELEDSTATEMENT: IDENTIFIER COLON STATEMENT

IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT   {   $$ = new_temp(); //Not keeping truelist and falselist corresponding to statements
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5);
                                                                    // code.push_back("if="+ds[curr5]["start"]);
                                                                    // for(auto )
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    // code.push_back(ds[curr]["start"]);
                                                                    // cout<<"Inside if then statement\n";
                                                                    // cout<<ds[curr]["start"]<<"\n";
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = ds3[curr5]["continuelist"];
                                                                    ds3[curr]["breaklist"] = ds3[curr5]["breaklist"];
                                                                    // ds3[curr]["falselist"] = ds3[curr3]["falselist"];
                                                                    // ds3[curr]["truelist"] = vector<int>();
}

IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT   {   $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    backpatch(ds3[curr3]["falselist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = merge(ds3[curr5]["continuelist"],ds3[curr7]["continuelist"]);
                                                                    ds3[curr]["breaklist"] = merge(ds3[curr5]["breaklist"],ds3[curr7]["breaklist"]);
                                                                    // ds3[curr]["truelist"] = vector<int>();
                                                                    // ds3[curr]["falselist"] = vector<int>();
}

IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF     {   $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    backpatch(ds3[curr3]["falselist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = merge(ds3[curr5]["continuelist"],ds3[curr7]["continuelist"]);
                                                                    ds3[curr]["breaklist"] = merge(ds3[curr5]["breaklist"],ds3[curr7]["breaklist"]);
                                                                    // ds3[curr]["truelist"] = vector<int>();
                                                                    // ds3[curr]["falselist"] = vector<int>();
}

STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT    {$$ = $1;}
                   |	LABELEDSTATEMENTNOSHORTIF   {$$ = $1;}
                   |	IFTHENELSESTATEMENTNOSHORTIF    {$$ = $1;}
                   |	WHILESTATEMENTNOSHORTIF {$$ = $1;}
                   |	FORSTATEMENTNOSHORTIF   {$$ = $1;}

LABELEDSTATEMENTNOSHORTIF: IDENTIFIER COLON STATEMENTNOSHORTIF  /*  for later */

WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF   {   $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5);
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    backpatch(ds3[curr5]["continuelist"],stringtonum(ds[curr3]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                    backpatch(ds3[curr5]["breaklist"],code.size());
                                                                    // ds3[curr]["falselist"] = ds3[curr3]["falselist"];
}

FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF   {$$ = $1; popscope();}
                      |	ENHANCEDFORSTATEMENTNOSHORTIF   {$$ = $1;popscope();}


WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT {   $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5);
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    backpatch(ds3[curr5]["continuelist"],stringtonum(ds[curr3]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                    backpatch(ds3[curr5]["breaklist"],code.size());
}

FORSTATEMENT: BASICFORSTATEMENT {$$ = $1;popscope();}
             |	ENHANCEDFORSTATEMENT    {$$ = $1;popscope();}

BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT   {   $$ = new_temp();
                                                                    int curr = chartonum($$), curr6 = chartonum($6);
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT    {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    backpatch(ds3[curr7]["continuelist"],code.size()); 
                                                                    for(auto s:ds2[curr5]["code"])
                                                                    code.push_back(s);
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr7]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT   {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr4 = chartonum($4), curr7 = chartonum($7);
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
                                                                    // assert(0 && "Exp Error");
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr4 = chartonum($4), curr6 = chartonum($6), curr8 = chartonum($8);
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds2[curr6]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr8]["start"]));
                                                                    backpatch(ds3[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr7 = chartonum($7);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr7]["start"]);
                                                                    // backpatch(ds3[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr7]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    // backpatch(ds3[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT    {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr6 = chartonum($6), curr8 = chartonum($8);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds2[curr6]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr8]["start"]);
                                                                    // backpatch(ds3[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds3[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    // backpatch(ds3[curr4]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT   {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr8 = chartonum($8);
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    // int gotoupdate = code.size();
                                                                    // for(auto s:ds2[curr6]["code"])
                                                                    // code.push_back(s);
                                                                    code.push_back("goto "+ds[curr5]["start"]);
                                                                    backpatch(ds3[curr5]["truelist"],stringtonum(ds[curr8]["start"]));
                                                                    backpatch(ds3[curr8]["continuelist"],stringtonum(ds[curr5]["start"])); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr5]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7), curr9 = chartonum($9);
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds2[curr7]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr5]["start"]);
                                                                    backpatch(ds3[curr5]["truelist"],stringtonum(ds[curr9]["start"]));
                                                                    backpatch(ds3[curr9]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr9]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr5]["falselist"],code.size());
}

BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF   {   $$ = new_temp();
                                                                    int curr = chartonum($$), curr6 = chartonum($6);
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF    {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    backpatch(ds3[curr7]["continuelist"],code.size()); 
                                                                    for(auto s:ds2[curr5]["code"])
                                                                    code.push_back(s);
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr7]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF   {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr4 = chartonum($4), curr7 = chartonum($7);
                                                                    
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr4 = chartonum($4), curr6 = chartonum($6), curr8 = chartonum($8);
                                                                    
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds2[curr6]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr8]["start"]));
                                                                    backpatch(ds3[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr7 = chartonum($7);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr7]["start"]);
                                                                    // backpatch(ds3[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr7]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    // backpatch(ds3[curr4]["falselist"],code.size()); 
}
                  |	FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF    {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr6 = chartonum($6), curr8 = chartonum($8);
                                                                    // if(ds[curr4]["type"]!="boolean")
                                                                    // error();
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds2[curr6]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr8]["start"]);
                                                                    // backpatch(ds3[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds3[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    // backpatch(ds3[curr4]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF   {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr8 = chartonum($8);
                                                                    
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    // int gotoupdate = code.size();
                                                                    // for(auto s:ds2[curr6]["code"])
                                                                    // code.push_back(s);
                                                                    code.push_back("goto "+ds[curr5]["start"]);
                                                                    backpatch(ds3[curr5]["truelist"],stringtonum(ds[curr8]["start"]));
                                                                    backpatch(ds3[curr8]["continuelist"],stringtonum(ds[curr5]["start"])); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr5]["falselist"],code.size());
}
                  |	FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF {      /* For update code should be after forbody code */
                                                                                            $$ = new_temp();
                                                                    int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7), curr9 = chartonum($9);
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cout<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    int gotoupdate = code.size();
                                                                    for(auto s:ds2[curr7]["code"])
                                                                    code.push_back(s);
                                                                    code.push_back("goto "+ds[curr5]["start"]);
                                                                    backpatch(ds3[curr5]["truelist"],stringtonum(ds[curr9]["start"]));
                                                                    backpatch(ds3[curr9]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr9]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr5]["falselist"],code.size());
}


ENHANCEDFORSTATEMENT: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENT

ENHANCEDFORSTATEMENTNOSHORTIF: FOR OPENPARAN LOCALVARIABLEDECLARATION COLON EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF

FORINIT: STATEMENTEXPRESSIONLIST    {$$ = $1;}
        |	LOCALVARIABLEDECLARATION    {$$ = $1;}

FORUPDATE: STATEMENTEXPRESSIONLIST  {$$ = $1;
                                        int curr = chartonum($$);
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }

STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION {$$ = $1;}
                        |   STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION {

                            $$ = new_temp();
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

SUPER1 : PUBLIC {$$ = new_temp(); generalmap[$$].modifiers.push_back(chartostring($1));}
        | PRIVATE  {$$ = new_temp(); generalmap[$$].modifiers.push_back(chartostring($1));}
        | PROTECTED {$$ = new_temp(); generalmap[$$].modifiers.push_back(chartostring($1));}
        | SUPER1 PUBLIC  {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER1 PRIVATE  {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER1 PROTECTED {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
    
SUPER2 : STATIC {$$ = new_temp(); generalmap[$$].modifiers.push_back(chartostring($1));}
        | FINAL  {$$ = new_temp(); generalmap[$$].modifiers.push_back(chartostring($1));}
        | SUPER1 STATIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER1 FINAL {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER2 STATIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER2 FINAL {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER2 PUBLIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER2 PRIVATE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER2 PROTECTED {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}

SUPER3 : ABSTRACT {$$ = new_temp(); generalmap[$$].modifiers.push_back(chartostring($1));}
        | STRICTFP {$$ = new_temp(); generalmap[$$].modifiers.push_back(chartostring($1));}
        | SUPER2 ABSTRACT {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER2 STRICTFP {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER3 ABSTRACT {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER3 STRICTFP {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER3 PUBLIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER3 PRIVATE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER3 PROTECTED {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER3 STATIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
        | SUPER3 FINAL {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
 
FIELDMODIFIERS: SUPER3 TRANSIENT {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            |   SUPER3 VOLATILE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            |  FIELDMODIFIERS TRANSIENT {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            |  FIELDMODIFIERS VOLATILE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            | FIELDMODIFIERS PUBLIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            | FIELDMODIFIERS PRIVATE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            | FIELDMODIFIERS PROTECTED {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            | FIELDMODIFIERS STATIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
            | FIELDMODIFIERS FINAL {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}


METHODMODIFIERS : SUPER3 SYNCHRONIZED {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | SUPER3 NATIVE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS SYNCHRONIZED {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS NATIVE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS ABSTRACT {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS STRICTFP {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS PUBLIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS PRIVATE {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS PROTECTED {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS STATIC {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}
                | METHODMODIFIERS FINAL {$$ = $1; generalmap[$$].modifiers.push_back(chartostring($2));}

TYPEARGUMENTS   :   ANGULARLEFT TYPEARGUMENTLIST  ANGULARRIGHT 

TYPEARGUMENTLIST    :   TYPEARGUMENT 
                    |   TYPEARGUMENTLIST COMMA TYPEARGUMENT 

TYPEARGUMENT    :   REFERENCETYPE {$$=$1;}
                |   WILDCARD {$$=$1;}

WILDCARD    :   QUESTIONMARK 
            |   QUESTIONMARK WILDCARDBOUNDS 

WILDCARDBOUNDS  :   EXTENDS REFERENCETYPE
                |   SUPER REFERENCETYPE 


INTERFACETYPE   :   CLASSTYPE {$$=$1;}

%%


int main(int argc, char** argv){


    //Create command line options 


    bool inset = false, outset = false, verbose = false;
    string outpre="";

    for (int i=0; i< argc; i++){
        // handle input arguments 
        //  arguments can be space separated 
        // arguments are help, input, output, verbose

        if (strcmp(argv[i], "--help") == 0){
            cerr<<"Usage: ./a.out [--help] [--input <filename>] [--output <output path prefix>] [--verbose]\n";
            cerr<< "Example: ./a.out --input input.java --output outpre\n";
            
        }

        else if (strcmp(argv[i], "--input") == 0){
            yyin = fopen(argv[i+1], "r");
            inset = true;
        }

        else if (strcmp(argv[i], "--output") == 0){
            outpre = chartostring(argv[i+1]);

            outset = true;
        }
        else if (strcmp(argv[i], "--verbose") == 0){
            verbose = true;
        }
    }

    if (!inset){
        cerr<< "Input not set, see help\n";
        return 0;
    }
    if (!outset){
        cerr<< "Output not set, see help\n";
        return 0;
    }

    // end command line
    //   if(!verbose)  freopen("/dev/null", "w", stderr);

        newscope();
    yyparse();
    // type_check_function_strong();
    /*Uncomment for debug*/
    

    ofstream cout1(outpre + "_3ac.txt");
    // cout<<"CODE:\n";

    for (int i=0; i< code.size(); i++){
        cout1<<i<<" "<<code[i]<<endl;
    }
    ofstream cout2(outpre +"_symtable.csv");

    cout2<<"Token, Name(Lexeme), Type, Line Number, Scope, Dims(If array), ScopeINFO(Child), ScopeINFO(Parent) << Offsets\n";

    for (auto x : preservedsymboltable){
        cout2<< x.second.token << ", " << x.first.first << ", " << x.second.typ.name << ", " << x.second.lineno << ", " << x.first.second << ", " << x.second.typ.dims << ", "<<x.second.offset << endl;

    }
   
    

    for(auto x : parentscope){
        cout2<<", , , , , , "<<x.first<<", "<<x.second<<", "<<endl;
    }



  

}