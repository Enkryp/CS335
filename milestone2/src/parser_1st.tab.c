/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser_1st.y"

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

    


    

#line 281 "parser_1st.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser_1st.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BOOLEAN = 3,                    /* BOOLEAN  */
  YYSYMBOL_BYTE = 4,                       /* BYTE  */
  YYSYMBOL_SHORT = 5,                      /* SHORT  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_LONG = 7,                       /* LONG  */
  YYSYMBOL_CHAR = 8,                       /* CHAR  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_DOUBLE = 10,                    /* DOUBLE  */
  YYSYMBOL_COMMA = 11,                     /* COMMA  */
  YYSYMBOL_QUESTIONMARK = 12,              /* QUESTIONMARK  */
  YYSYMBOL_SEMICOLON = 13,                 /* SEMICOLON  */
  YYSYMBOL_OPENCURLY1 = 14,                /* OPENCURLY1  */
  YYSYMBOL_CLOSECURLY1 = 15,               /* CLOSECURLY1  */
  YYSYMBOL_ANGULARLEFT = 16,               /* ANGULARLEFT  */
  YYSYMBOL_ANGULARRIGHT = 17,              /* ANGULARRIGHT  */
  YYSYMBOL_OPENSQUARE = 18,                /* OPENSQUARE  */
  YYSYMBOL_CLOSESQUARE = 19,               /* CLOSESQUARE  */
  YYSYMBOL_OPENPARAN = 20,                 /* OPENPARAN  */
  YYSYMBOL_CLOSEPARAN = 21,                /* CLOSEPARAN  */
  YYSYMBOL_DOUBLECOLON = 22,               /* DOUBLECOLON  */
  YYSYMBOL_TRIPLEDOT = 23,                 /* TRIPLEDOT  */
  YYSYMBOL_WS = 24,                        /* WS  */
  YYSYMBOL_AT = 25,                        /* AT  */
  YYSYMBOL_OVERRIDE = 26,                  /* OVERRIDE  */
  YYSYMBOL_EQUALS = 27,                    /* EQUALS  */
  YYSYMBOL_MULTIPLYEQUALS = 28,            /* MULTIPLYEQUALS  */
  YYSYMBOL_DIVIDEEQUALS = 29,              /* DIVIDEEQUALS  */
  YYSYMBOL_MODEQUALS = 30,                 /* MODEQUALS  */
  YYSYMBOL_PLUSEQUALS = 31,                /* PLUSEQUALS  */
  YYSYMBOL_MINUSEQUALS = 32,               /* MINUSEQUALS  */
  YYSYMBOL_PLUS = 33,                      /* PLUS  */
  YYSYMBOL_MINUS = 34,                     /* MINUS  */
  YYSYMBOL_DIVIDE = 35,                    /* DIVIDE  */
  YYSYMBOL_MULTIPLY = 36,                  /* MULTIPLY  */
  YYSYMBOL_MOD = 37,                       /* MOD  */
  YYSYMBOL_OR = 38,                        /* OR  */
  YYSYMBOL_XOR = 39,                       /* XOR  */
  YYSYMBOL_COLON = 40,                     /* COLON  */
  YYSYMBOL_NOT = 41,                       /* NOT  */
  YYSYMBOL_COMPLEMENT = 42,                /* COMPLEMENT  */
  YYSYMBOL_AND = 43,                       /* AND  */
  YYSYMBOL_DOT = 44,                       /* DOT  */
  YYSYMBOL_OROR = 45,                      /* OROR  */
  YYSYMBOL_ANDAND = 46,                    /* ANDAND  */
  YYSYMBOL_PLUSPLUS = 47,                  /* PLUSPLUS  */
  YYSYMBOL_MINUSMINUS = 48,                /* MINUSMINUS  */
  YYSYMBOL_ANGULARLEFTANGULARLEFT = 49,    /* ANGULARLEFTANGULARLEFT  */
  YYSYMBOL_ANGULARRIGHTANGULARRIGHT = 50,  /* ANGULARRIGHTANGULARRIGHT  */
  YYSYMBOL_ANGULARRIGHTANGULARRIGHTANGULARRIGHT = 51, /* ANGULARRIGHTANGULARRIGHTANGULARRIGHT  */
  YYSYMBOL_EQUALSEQUALS = 52,              /* EQUALSEQUALS  */
  YYSYMBOL_NOTEQUALS = 53,                 /* NOTEQUALS  */
  YYSYMBOL_INTEGERLITERAL = 54,            /* INTEGERLITERAL  */
  YYSYMBOL_FLOATINGPOINTLITERAL = 55,      /* FLOATINGPOINTLITERAL  */
  YYSYMBOL_BOOLEANLITERAL = 56,            /* BOOLEANLITERAL  */
  YYSYMBOL_CHARACTERLITERAL = 57,          /* CHARACTERLITERAL  */
  YYSYMBOL_STRINGLITERAL = 58,             /* STRINGLITERAL  */
  YYSYMBOL_TEXTBLOCK = 59,                 /* TEXTBLOCK  */
  YYSYMBOL_NULLLITERAL = 60,               /* NULLLITERAL  */
  YYSYMBOL_EXTENDS = 61,                   /* EXTENDS  */
  YYSYMBOL_SUPER = 62,                     /* SUPER  */
  YYSYMBOL_CLASS = 63,                     /* CLASS  */
  YYSYMBOL_PUBLIC = 64,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 65,                   /* PRIVATE  */
  YYSYMBOL_IMPLEMENTS = 66,                /* IMPLEMENTS  */
  YYSYMBOL_PERMITS = 67,                   /* PERMITS  */
  YYSYMBOL_PROTECTED = 68,                 /* PROTECTED  */
  YYSYMBOL_STATIC = 69,                    /* STATIC  */
  YYSYMBOL_FINAL = 70,                     /* FINAL  */
  YYSYMBOL_TRANSIENT = 71,                 /* TRANSIENT  */
  YYSYMBOL_VOLATILE = 72,                  /* VOLATILE  */
  YYSYMBOL_INSTANCEOF = 73,                /* INSTANCEOF  */
  YYSYMBOL_THIS = 74,                      /* THIS  */
  YYSYMBOL_VOID = 75,                      /* VOID  */
  YYSYMBOL_NEW = 76,                       /* NEW  */
  YYSYMBOL_THROW = 77,                     /* THROW  */
  YYSYMBOL_ASSERT = 78,                    /* ASSERT  */
  YYSYMBOL_VAR = 79,                       /* VAR  */
  YYSYMBOL_BREAK = 80,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 81,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 82,                    /* RETURN  */
  YYSYMBOL_YIELD = 83,                     /* YIELD  */
  YYSYMBOL_IF = 84,                        /* IF  */
  YYSYMBOL_ELSE = 85,                      /* ELSE  */
  YYSYMBOL_WHILE = 86,                     /* WHILE  */
  YYSYMBOL_FOR1 = 87,                      /* FOR1  */
  YYSYMBOL_PRINTLN = 88,                   /* PRINTLN  */
  YYSYMBOL_ABSTRACT = 89,                  /* ABSTRACT  */
  YYSYMBOL_SYNCHRONIZED = 90,              /* SYNCHRONIZED  */
  YYSYMBOL_NATIVE = 91,                    /* NATIVE  */
  YYSYMBOL_STRICTFP = 92,                  /* STRICTFP  */
  YYSYMBOL_SWITCH = 93,                    /* SWITCH  */
  YYSYMBOL_DEFAULT = 94,                   /* DEFAULT  */
  YYSYMBOL_PACKAGE = 95,                   /* PACKAGE  */
  YYSYMBOL_DO = 96,                        /* DO  */
  YYSYMBOL_GOTO = 97,                      /* GOTO  */
  YYSYMBOL_IMPORT = 98,                    /* IMPORT  */
  YYSYMBOL_THROWS = 99,                    /* THROWS  */
  YYSYMBOL_CASE = 100,                     /* CASE  */
  YYSYMBOL_ENUM = 101,                     /* ENUM  */
  YYSYMBOL_CATCH = 102,                    /* CATCH  */
  YYSYMBOL_TRY = 103,                      /* TRY  */
  YYSYMBOL_INTERFACE = 104,                /* INTERFACE  */
  YYSYMBOL_FINALLY = 105,                  /* FINALLY  */
  YYSYMBOL_CONST = 106,                    /* CONST  */
  YYSYMBOL_UNDERSCORE = 107,               /* UNDERSCORE  */
  YYSYMBOL_EXPORTS = 108,                  /* EXPORTS  */
  YYSYMBOL_OPENS = 109,                    /* OPENS  */
  YYSYMBOL_REQUIRES = 110,                 /* REQUIRES  */
  YYSYMBOL_USES = 111,                     /* USES  */
  YYSYMBOL_MODULE = 112,                   /* MODULE  */
  YYSYMBOL_SEALED = 113,                   /* SEALED  */
  YYSYMBOL_PROVIDES = 114,                 /* PROVIDES  */
  YYSYMBOL_TO = 115,                       /* TO  */
  YYSYMBOL_WITH = 116,                     /* WITH  */
  YYSYMBOL_OPEN = 117,                     /* OPEN  */
  YYSYMBOL_RECORD = 118,                   /* RECORD  */
  YYSYMBOL_TRANSITIVE = 119,               /* TRANSITIVE  */
  YYSYMBOL_ERROR = 120,                    /* ERROR  */
  YYSYMBOL_ONCE = 121,                     /* ONCE  */
  YYSYMBOL_NL = 122,                       /* NL  */
  YYSYMBOL_NON_SEALED = 123,               /* NON_SEALED  */
  YYSYMBOL_IDENTIFIER = 124,               /* IDENTIFIER  */
  YYSYMBOL_UNQUALIFIEDMETHODIDENTIFIER = 125, /* UNQUALIFIEDMETHODIDENTIFIER  */
  YYSYMBOL_DOTCLASS = 126,                 /* DOTCLASS  */
  YYSYMBOL_EOFF = 127,                     /* EOFF  */
  YYSYMBOL_YYACCEPT = 128,                 /* $accept  */
  YYSYMBOL_COMPILATIONUNIT = 129,          /* COMPILATIONUNIT  */
  YYSYMBOL_TYPE = 130,                     /* TYPE  */
  YYSYMBOL_PRIMITIVETYPE = 131,            /* PRIMITIVETYPE  */
  YYSYMBOL_NUMERICTYPE = 132,              /* NUMERICTYPE  */
  YYSYMBOL_INTEGRALTYPE = 133,             /* INTEGRALTYPE  */
  YYSYMBOL_FLOATINGTYPE = 134,             /* FLOATINGTYPE  */
  YYSYMBOL_REFERENCETYPE = 135,            /* REFERENCETYPE  */
  YYSYMBOL_CLASSORINTERFACETYPE = 136,     /* CLASSORINTERFACETYPE  */
  YYSYMBOL_CLASSTYPE = 137,                /* CLASSTYPE  */
  YYSYMBOL_CLASSTYPE1 = 138,               /* CLASSTYPE1  */
  YYSYMBOL_DIMS = 139,                     /* DIMS  */
  YYSYMBOL_METHODNAME = 140,               /* METHODNAME  */
  YYSYMBOL_EXPRESSIONNAME = 141,           /* EXPRESSIONNAME  */
  YYSYMBOL_ORDINARYCOMPILATIONUNIT = 142,  /* ORDINARYCOMPILATIONUNIT  */
  YYSYMBOL_TOPLEVELCLASSORINTERFACEDECLARATION = 143, /* TOPLEVELCLASSORINTERFACEDECLARATION  */
  YYSYMBOL_IMPORTDECLARATION = 144,        /* IMPORTDECLARATION  */
  YYSYMBOL_CLASSDECLARATION = 145,         /* CLASSDECLARATION  */
  YYSYMBOL_NORMALCLASSDECLARATION = 146,   /* NORMALCLASSDECLARATION  */
  YYSYMBOL_CLASSNAME = 147,                /* CLASSNAME  */
  YYSYMBOL_NORMALINTERFACEDECLARATION = 148, /* NORMALINTERFACEDECLARATION  */
  YYSYMBOL_FOR = 149,                      /* FOR  */
  YYSYMBOL_OPENCURLY = 150,                /* OPENCURLY  */
  YYSYMBOL_CLOSECURLY = 151,               /* CLOSECURLY  */
  YYSYMBOL_INTERFACEBODY = 152,            /* INTERFACEBODY  */
  YYSYMBOL_INTERFACEMEMBERDECLARATIONS = 153, /* INTERFACEMEMBERDECLARATIONS  */
  YYSYMBOL_INTERFACEMEMBERDECLARATION = 154, /* INTERFACEMEMBERDECLARATION  */
  YYSYMBOL_INTERFACEDECLARATION = 155,     /* INTERFACEDECLARATION  */
  YYSYMBOL_TYPEPARAMETERS = 156,           /* TYPEPARAMETERS  */
  YYSYMBOL_TYPEPARAMETERLIST = 157,        /* TYPEPARAMETERLIST  */
  YYSYMBOL_TYPEPARAMETER = 158,            /* TYPEPARAMETER  */
  YYSYMBOL_TYPEBOUND = 159,                /* TYPEBOUND  */
  YYSYMBOL_ADDITIONALBOUND = 160,          /* ADDITIONALBOUND  */
  YYSYMBOL_CLASSEXTENDS = 161,             /* CLASSEXTENDS  */
  YYSYMBOL_CLASSIMPLEMENTS = 162,          /* CLASSIMPLEMENTS  */
  YYSYMBOL_INTERFACETYPELIST = 163,        /* INTERFACETYPELIST  */
  YYSYMBOL_CLASSPERMITS = 164,             /* CLASSPERMITS  */
  YYSYMBOL_TYPENAMES = 165,                /* TYPENAMES  */
  YYSYMBOL_CLASSBODY = 166,                /* CLASSBODY  */
  YYSYMBOL_CLASSBODYDECLARATIONS = 167,    /* CLASSBODYDECLARATIONS  */
  YYSYMBOL_CLASSBODYDECLARATION = 168,     /* CLASSBODYDECLARATION  */
  YYSYMBOL_CLASSMEMBERDECLARATION = 169,   /* CLASSMEMBERDECLARATION  */
  YYSYMBOL_FIELDDECLARATION = 170,         /* FIELDDECLARATION  */
  YYSYMBOL_VARIABLEDECLARATORLIST = 171,   /* VARIABLEDECLARATORLIST  */
  YYSYMBOL_VARIABLEDECLARATOR = 172,       /* VARIABLEDECLARATOR  */
  YYSYMBOL_VARIABLEDECLARATORID = 173,     /* VARIABLEDECLARATORID  */
  YYSYMBOL_VARIABLEINITIALIZER = 174,      /* VARIABLEINITIALIZER  */
  YYSYMBOL_EXPRESSION = 175,               /* EXPRESSION  */
  YYSYMBOL_ASSIGNMENTEXPRESSION = 176,     /* ASSIGNMENTEXPRESSION  */
  YYSYMBOL_ASSIGNMENT = 177,               /* ASSIGNMENT  */
  YYSYMBOL_LEFTHANDSIDE = 178,             /* LEFTHANDSIDE  */
  YYSYMBOL_ASSIGNMENTOPERATOR = 179,       /* ASSIGNMENTOPERATOR  */
  YYSYMBOL_FIELDACCESS = 180,              /* FIELDACCESS  */
  YYSYMBOL_PRIMARY = 181,                  /* PRIMARY  */
  YYSYMBOL_PRIMARYNONEWARRAY = 182,        /* PRIMARYNONEWARRAY  */
  YYSYMBOL_LITERAL = 183,                  /* LITERAL  */
  YYSYMBOL_CLASSLITERAL = 184,             /* CLASSLITERAL  */
  YYSYMBOL_SQUARESTAR = 185,               /* SQUARESTAR  */
  YYSYMBOL_CLASSINSTANCECREATIONEXPRESSION = 186, /* CLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION = 187, /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_CLASSORINTERFACETYPETOINSTANTIATE = 188, /* CLASSORINTERFACETYPETOINSTANTIATE  */
  YYSYMBOL_ARGUMENTLIST = 189,             /* ARGUMENTLIST  */
  YYSYMBOL_METHODINVOCATION = 190,         /* METHODINVOCATION  */
  YYSYMBOL_METHODREFERENCE = 191,          /* METHODREFERENCE  */
  YYSYMBOL_ARRAYCREATIONEXPRESSION = 192,  /* ARRAYCREATIONEXPRESSION  */
  YYSYMBOL_ARRAYINITIALIZER = 193,         /* ARRAYINITIALIZER  */
  YYSYMBOL_ARRAYINITIALIZER1 = 194,        /* ARRAYINITIALIZER1  */
  YYSYMBOL_DIMEXPRS = 195,                 /* DIMEXPRS  */
  YYSYMBOL_DIMEXPR = 196,                  /* DIMEXPR  */
  YYSYMBOL_VARIABLEINITIALIZERLIST = 197,  /* VARIABLEINITIALIZERLIST  */
  YYSYMBOL_ARRAYACCESS = 198,              /* ARRAYACCESS  */
  YYSYMBOL_CONDITIONALEXPRESSION = 199,    /* CONDITIONALEXPRESSION  */
  YYSYMBOL_CONDITIONALOREXPRESSION = 200,  /* CONDITIONALOREXPRESSION  */
  YYSYMBOL_CONDITIONALANDEXPRESSION = 201, /* CONDITIONALANDEXPRESSION  */
  YYSYMBOL_INCLUSIVEOREXPRESSION = 202,    /* INCLUSIVEOREXPRESSION  */
  YYSYMBOL_EXCLUSIVEOREXPRESSION = 203,    /* EXCLUSIVEOREXPRESSION  */
  YYSYMBOL_ANDEXPRESSION = 204,            /* ANDEXPRESSION  */
  YYSYMBOL_EQUALITYEXPRESSION = 205,       /* EQUALITYEXPRESSION  */
  YYSYMBOL_RELATIONALEXPRESSION = 206,     /* RELATIONALEXPRESSION  */
  YYSYMBOL_SHIFTEXPRESSION = 207,          /* SHIFTEXPRESSION  */
  YYSYMBOL_ADDITIVEEXPRESSION = 208,       /* ADDITIVEEXPRESSION  */
  YYSYMBOL_MULTIPLICATIVEEXPRESSION = 209, /* MULTIPLICATIVEEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSION = 210,          /* UNARYEXPRESSION  */
  YYSYMBOL_PREINCREMENTEXPRESSION = 211,   /* PREINCREMENTEXPRESSION  */
  YYSYMBOL_PREDECREMENTEXPRESSION = 212,   /* PREDECREMENTEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSIONNOTPLUSMINUS = 213, /* UNARYEXPRESSIONNOTPLUSMINUS  */
  YYSYMBOL_POSTFIXEXPRESSION = 214,        /* POSTFIXEXPRESSION  */
  YYSYMBOL_POSTINCREMENTEXPRESSION = 215,  /* POSTINCREMENTEXPRESSION  */
  YYSYMBOL_POSTDECREMENTEXPRESSION = 216,  /* POSTDECREMENTEXPRESSION  */
  YYSYMBOL_INSTANCEOFEXPRESSION = 217,     /* INSTANCEOFEXPRESSION  */
  YYSYMBOL_METHODDECLARATION = 218,        /* METHODDECLARATION  */
  YYSYMBOL_METHODHEADER = 219,             /* METHODHEADER  */
  YYSYMBOL_THROWS2 = 220,                  /* THROWS2  */
  YYSYMBOL_EXCEPTIONTYPELIST = 221,        /* EXCEPTIONTYPELIST  */
  YYSYMBOL_EXCEPTIONTYPE = 222,            /* EXCEPTIONTYPE  */
  YYSYMBOL_METHODDECLARATOR = 223,         /* METHODDECLARATOR  */
  YYSYMBOL_RECEIVERPARAMETER = 224,        /* RECEIVERPARAMETER  */
  YYSYMBOL_FORMALPARAMETERLIST = 225,      /* FORMALPARAMETERLIST  */
  YYSYMBOL_FORMALPARAMETER = 226,          /* FORMALPARAMETER  */
  YYSYMBOL_VARIABLEARITYPARAMETER = 227,   /* VARIABLEARITYPARAMETER  */
  YYSYMBOL_METHODBODY = 228,               /* METHODBODY  */
  YYSYMBOL_INSTANCEINITIALIZER = 229,      /* INSTANCEINITIALIZER  */
  YYSYMBOL_STATICINITIALIZER = 230,        /* STATICINITIALIZER  */
  YYSYMBOL_BLOCK = 231,                    /* BLOCK  */
  YYSYMBOL_BLOCKSTATEMENTS = 232,          /* BLOCKSTATEMENTS  */
  YYSYMBOL_BLOCKSTATEMENT = 233,           /* BLOCKSTATEMENT  */
  YYSYMBOL_LOCALCLASSORINTERFACEDECLARATION = 234, /* LOCALCLASSORINTERFACEDECLARATION  */
  YYSYMBOL_LOCALVARIABLEDECLARATIONSTATEMENT = 235, /* LOCALVARIABLEDECLARATIONSTATEMENT  */
  YYSYMBOL_LOCALVARIABLEDECLARATION = 236, /* LOCALVARIABLEDECLARATION  */
  YYSYMBOL_LOCALVARIABLETYPE = 237,        /* LOCALVARIABLETYPE  */
  YYSYMBOL_STATEMENT = 238,                /* STATEMENT  */
  YYSYMBOL_STATEMENTWITHOUTTRAILINGSUBSTATEMENT = 239, /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
  YYSYMBOL_EMPTYSTATEMENT = 240,           /* EMPTYSTATEMENT  */
  YYSYMBOL_EXPRESSIONSTATEMENT = 241,      /* EXPRESSIONSTATEMENT  */
  YYSYMBOL_STATEMENTEXPRESSION = 242,      /* STATEMENTEXPRESSION  */
  YYSYMBOL_ASSERTSTATEMENT = 243,          /* ASSERTSTATEMENT  */
  YYSYMBOL_BREAKSTATEMENT = 244,           /* BREAKSTATEMENT  */
  YYSYMBOL_CONTINUESTATEMENT = 245,        /* CONTINUESTATEMENT  */
  YYSYMBOL_RETURNSTATEMENT = 246,          /* RETURNSTATEMENT  */
  YYSYMBOL_THROWSTATEMENT = 247,           /* THROWSTATEMENT  */
  YYSYMBOL_YIELDSTATEMENT = 248,           /* YIELDSTATEMENT  */
  YYSYMBOL_LABELEDSTATEMENT = 249,         /* LABELEDSTATEMENT  */
  YYSYMBOL_IFTHENSTATEMENT = 250,          /* IFTHENSTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENT = 251,      /* IFTHENELSESTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENTNOSHORTIF = 252, /* IFTHENELSESTATEMENTNOSHORTIF  */
  YYSYMBOL_STATEMENTNOSHORTIF = 253,       /* STATEMENTNOSHORTIF  */
  YYSYMBOL_LABELEDSTATEMENTNOSHORTIF = 254, /* LABELEDSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENTNOSHORTIF = 255,  /* WHILESTATEMENTNOSHORTIF  */
  YYSYMBOL_FORSTATEMENTNOSHORTIF = 256,    /* FORSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENT = 257,           /* WHILESTATEMENT  */
  YYSYMBOL_FORSTATEMENT = 258,             /* FORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENT = 259,        /* BASICFORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENTNOSHORTIF = 260, /* BASICFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_ENHANCEDFORSTATEMENT = 261,     /* ENHANCEDFORSTATEMENT  */
  YYSYMBOL_ENHANCEDFORSTATEMENTNOSHORTIF = 262, /* ENHANCEDFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_FORINIT = 263,                  /* FORINIT  */
  YYSYMBOL_FORUPDATE = 264,                /* FORUPDATE  */
  YYSYMBOL_STATEMENTEXPRESSIONLIST = 265,  /* STATEMENTEXPRESSIONLIST  */
  YYSYMBOL_CONSTRUCTORDECLARATION = 266,   /* CONSTRUCTORDECLARATION  */
  YYSYMBOL_CONSTRUCTORDECLARATOR = 267,    /* CONSTRUCTORDECLARATOR  */
  YYSYMBOL_SIMPLETYPENAME = 268,           /* SIMPLETYPENAME  */
  YYSYMBOL_CONSTRUCTORBODY = 269,          /* CONSTRUCTORBODY  */
  YYSYMBOL_EXPLICITCONSTRUCTORINVOCATION = 270, /* EXPLICITCONSTRUCTORINVOCATION  */
  YYSYMBOL_SUPER1 = 271,                   /* SUPER1  */
  YYSYMBOL_SUPER2 = 272,                   /* SUPER2  */
  YYSYMBOL_SUPER3 = 273,                   /* SUPER3  */
  YYSYMBOL_FIELDMODIFIERS = 274,           /* FIELDMODIFIERS  */
  YYSYMBOL_METHODMODIFIERS = 275,          /* METHODMODIFIERS  */
  YYSYMBOL_TYPEARGUMENTS = 276,            /* TYPEARGUMENTS  */
  YYSYMBOL_TYPEARGUMENTLIST = 277,         /* TYPEARGUMENTLIST  */
  YYSYMBOL_TYPEARGUMENT = 278,             /* TYPEARGUMENT  */
  YYSYMBOL_WILDCARD = 279,                 /* WILDCARD  */
  YYSYMBOL_WILDCARDBOUNDS = 280,           /* WILDCARDBOUNDS  */
  YYSYMBOL_INTERFACETYPE = 281             /* INTERFACETYPE  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   6323

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  154
/* YYNRULES -- Number of rules.  */
#define YYNRULES  607
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1151

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   382


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   241,   241,   242,   247,   248,   250,   251,   253,   254,
     256,   257,   258,   259,   260,   262,   263,   265,   267,   269,
     271,   274,   275,   277,   284,   301,   304,   305,   307,   350,
     351,   352,   354,   355,   356,   357,   359,   373,   374,   375,
     376,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   441,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   508,   509,   510,   512,
     513,   515,   516,   518,   519,   520,   521,   522,   524,   527,
     529,   530,   532,   533,   536,   537,   539,   540,   542,   544,
     546,   547,   549,   551,   552,   554,   555,   557,   558,   560,
     561,   562,   563,   565,   566,   567,   568,   569,   571,   599,
     625,   653,   693,   705,   729,   763,   765,   773,   780,   781,
     783,   785,   788,   790,   805,   806,   814,   815,   819,   821,
     823,   825,   827,   829,   832,   839,   840,   842,   845,   847,
     848,   849,   853,   854,   855,   856,   857,   858,   859,   861,
     862,   863,   864,   865,   866,   867,   869,   870,   871,   872,
     873,   874,   875,   877,   878,   880,   881,   882,   883,   885,
     886,   887,   888,   889,   890,   891,   892,   894,   897,   901,
     910,   922,   941,   965,   992,   993,   994,   995,   996,   997,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1008,  1009,  1011,  1012,  1013,  1014,  1015,  1017,  1018,  1020,
    1021,  1022,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1035,  1036,  1038,  1039,  1040,  1042,  1043,  1047,
    1049,  1050,  1056,  1057,  1077,  1091,  1092,  1094,  1095,  1109,
    1110,  1120,  1121,  1130,  1131,  1139,  1140,  1150,  1158,  1174,
    1192,  1197,  1215,  1229,  1243,  1257,  1259,  1260,  1269,  1277,
    1286,  1287,  1295,  1304,  1305,  1313,  1321,  1330,  1331,  1332,
    1335,  1343,  1345,  1359,  1373,  1374,  1382,  1391,  1392,  1393,
    1407,  1408,  1410,  1423,  1438,  1441,  1452,  1477,  1501,  1525,
    1549,  1550,  1551,  1552,  1553,  1556,  1598,  1628,  1629,  1630,
    1631,  1632,  1633,  1636,  1638,  1639,  1641,  1643,  1651,  1659,
    1660,  1661,  1662,  1663,  1664,  1666,  1667,  1669,  1673,  1679,
    1683,  1684,  1690,  1691,  1694,  1695,  1697,  1699,  1701,  1702,
    1704,  1707,  1718,  1719,  1722,  1724,  1726,  1728,  1730,  1787,
    1849,  1850,  1853,  1854,  1855,  1856,  1857,  1858,  1860,  1862,
    1863,  1864,  1865,  1866,  1867,  1868,  1869,  1871,  1873,  1875,
    1876,  1877,  1878,  1879,  1880,  1881,  1883,  1884,  1886,  1894,
    1896,  1904,  1906,  1912,  1919,  1921,  1923,  1925,  1942,  1954,
    1966,  1967,  1968,  1969,  1970,  1972,  1974,  1986,  1987,  1990,
    2001,  2002,  2004,  2012,  2023,  2037,  2053,  2066,  2082,  2098,
    2115,  2123,  2134,  2148,  2165,  2178,  2194,  2211,  2229,  2231,
    2233,  2234,  2236,  2246,  2247,  2256,  2257,  2258,  2259,  2262,
    2263,  2264,  2265,  2266,  2267,  2268,  2269,  2272,  2274,  2275,
    2276,  2277,  2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,
    2287,  2288,  2289,  2290,  2291,  2292,  2293,  2294,  2295,  2296,
    2297,  2298,  2300,  2301,  2302,  2303,  2304,  2305,  2307,  2308,
    2309,  2310,  2311,  2312,  2313,  2314,  2315,  2317,  2318,  2319,
    2320,  2321,  2322,  2323,  2324,  2325,  2326,  2327,  2329,  2330,
    2331,  2332,  2333,  2334,  2335,  2336,  2337,  2340,  2341,  2342,
    2343,  2344,  2345,  2346,  2347,  2348,  2349,  2350,  2352,  2354,
    2355,  2357,  2358,  2360,  2361,  2363,  2364,  2367
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BOOLEAN", "BYTE",
  "SHORT", "INT", "LONG", "CHAR", "FLOAT", "DOUBLE", "COMMA",
  "QUESTIONMARK", "SEMICOLON", "OPENCURLY1", "CLOSECURLY1", "ANGULARLEFT",
  "ANGULARRIGHT", "OPENSQUARE", "CLOSESQUARE", "OPENPARAN", "CLOSEPARAN",
  "DOUBLECOLON", "TRIPLEDOT", "WS", "AT", "OVERRIDE", "EQUALS",
  "MULTIPLYEQUALS", "DIVIDEEQUALS", "MODEQUALS", "PLUSEQUALS",
  "MINUSEQUALS", "PLUS", "MINUS", "DIVIDE", "MULTIPLY", "MOD", "OR", "XOR",
  "COLON", "NOT", "COMPLEMENT", "AND", "DOT", "OROR", "ANDAND", "PLUSPLUS",
  "MINUSMINUS", "ANGULARLEFTANGULARLEFT", "ANGULARRIGHTANGULARRIGHT",
  "ANGULARRIGHTANGULARRIGHTANGULARRIGHT", "EQUALSEQUALS", "NOTEQUALS",
  "INTEGERLITERAL", "FLOATINGPOINTLITERAL", "BOOLEANLITERAL",
  "CHARACTERLITERAL", "STRINGLITERAL", "TEXTBLOCK", "NULLLITERAL",
  "EXTENDS", "SUPER", "CLASS", "PUBLIC", "PRIVATE", "IMPLEMENTS",
  "PERMITS", "PROTECTED", "STATIC", "FINAL", "TRANSIENT", "VOLATILE",
  "INSTANCEOF", "THIS", "VOID", "NEW", "THROW", "ASSERT", "VAR", "BREAK",
  "CONTINUE", "RETURN", "YIELD", "IF", "ELSE", "WHILE", "FOR1", "PRINTLN",
  "ABSTRACT", "SYNCHRONIZED", "NATIVE", "STRICTFP", "SWITCH", "DEFAULT",
  "PACKAGE", "DO", "GOTO", "IMPORT", "THROWS", "CASE", "ENUM", "CATCH",
  "TRY", "INTERFACE", "FINALLY", "CONST", "UNDERSCORE", "EXPORTS", "OPENS",
  "REQUIRES", "USES", "MODULE", "SEALED", "PROVIDES", "TO", "WITH", "OPEN",
  "RECORD", "TRANSITIVE", "ERROR", "ONCE", "NL", "NON_SEALED",
  "IDENTIFIER", "UNQUALIFIEDMETHODIDENTIFIER", "DOTCLASS", "EOFF",
  "$accept", "COMPILATIONUNIT", "TYPE", "PRIMITIVETYPE", "NUMERICTYPE",
  "INTEGRALTYPE", "FLOATINGTYPE", "REFERENCETYPE", "CLASSORINTERFACETYPE",
  "CLASSTYPE", "CLASSTYPE1", "DIMS", "METHODNAME", "EXPRESSIONNAME",
  "ORDINARYCOMPILATIONUNIT", "TOPLEVELCLASSORINTERFACEDECLARATION",
  "IMPORTDECLARATION", "CLASSDECLARATION", "NORMALCLASSDECLARATION",
  "CLASSNAME", "NORMALINTERFACEDECLARATION", "FOR", "OPENCURLY",
  "CLOSECURLY", "INTERFACEBODY", "INTERFACEMEMBERDECLARATIONS",
  "INTERFACEMEMBERDECLARATION", "INTERFACEDECLARATION", "TYPEPARAMETERS",
  "TYPEPARAMETERLIST", "TYPEPARAMETER", "TYPEBOUND", "ADDITIONALBOUND",
  "CLASSEXTENDS", "CLASSIMPLEMENTS", "INTERFACETYPELIST", "CLASSPERMITS",
  "TYPENAMES", "CLASSBODY", "CLASSBODYDECLARATIONS",
  "CLASSBODYDECLARATION", "CLASSMEMBERDECLARATION", "FIELDDECLARATION",
  "VARIABLEDECLARATORLIST", "VARIABLEDECLARATOR", "VARIABLEDECLARATORID",
  "VARIABLEINITIALIZER", "EXPRESSION", "ASSIGNMENTEXPRESSION",
  "ASSIGNMENT", "LEFTHANDSIDE", "ASSIGNMENTOPERATOR", "FIELDACCESS",
  "PRIMARY", "PRIMARYNONEWARRAY", "LITERAL", "CLASSLITERAL", "SQUARESTAR",
  "CLASSINSTANCECREATIONEXPRESSION",
  "UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION",
  "CLASSORINTERFACETYPETOINSTANTIATE", "ARGUMENTLIST", "METHODINVOCATION",
  "METHODREFERENCE", "ARRAYCREATIONEXPRESSION", "ARRAYINITIALIZER",
  "ARRAYINITIALIZER1", "DIMEXPRS", "DIMEXPR", "VARIABLEINITIALIZERLIST",
  "ARRAYACCESS", "CONDITIONALEXPRESSION", "CONDITIONALOREXPRESSION",
  "CONDITIONALANDEXPRESSION", "INCLUSIVEOREXPRESSION",
  "EXCLUSIVEOREXPRESSION", "ANDEXPRESSION", "EQUALITYEXPRESSION",
  "RELATIONALEXPRESSION", "SHIFTEXPRESSION", "ADDITIVEEXPRESSION",
  "MULTIPLICATIVEEXPRESSION", "UNARYEXPRESSION", "PREINCREMENTEXPRESSION",
  "PREDECREMENTEXPRESSION", "UNARYEXPRESSIONNOTPLUSMINUS",
  "POSTFIXEXPRESSION", "POSTINCREMENTEXPRESSION",
  "POSTDECREMENTEXPRESSION", "INSTANCEOFEXPRESSION", "METHODDECLARATION",
  "METHODHEADER", "THROWS2", "EXCEPTIONTYPELIST", "EXCEPTIONTYPE",
  "METHODDECLARATOR", "RECEIVERPARAMETER", "FORMALPARAMETERLIST",
  "FORMALPARAMETER", "VARIABLEARITYPARAMETER", "METHODBODY",
  "INSTANCEINITIALIZER", "STATICINITIALIZER", "BLOCK", "BLOCKSTATEMENTS",
  "BLOCKSTATEMENT", "LOCALCLASSORINTERFACEDECLARATION",
  "LOCALVARIABLEDECLARATIONSTATEMENT", "LOCALVARIABLEDECLARATION",
  "LOCALVARIABLETYPE", "STATEMENT", "STATEMENTWITHOUTTRAILINGSUBSTATEMENT",
  "EMPTYSTATEMENT", "EXPRESSIONSTATEMENT", "STATEMENTEXPRESSION",
  "ASSERTSTATEMENT", "BREAKSTATEMENT", "CONTINUESTATEMENT",
  "RETURNSTATEMENT", "THROWSTATEMENT", "YIELDSTATEMENT",
  "LABELEDSTATEMENT", "IFTHENSTATEMENT", "IFTHENELSESTATEMENT",
  "IFTHENELSESTATEMENTNOSHORTIF", "STATEMENTNOSHORTIF",
  "LABELEDSTATEMENTNOSHORTIF", "WHILESTATEMENTNOSHORTIF",
  "FORSTATEMENTNOSHORTIF", "WHILESTATEMENT", "FORSTATEMENT",
  "BASICFORSTATEMENT", "BASICFORSTATEMENTNOSHORTIF",
  "ENHANCEDFORSTATEMENT", "ENHANCEDFORSTATEMENTNOSHORTIF", "FORINIT",
  "FORUPDATE", "STATEMENTEXPRESSIONLIST", "CONSTRUCTORDECLARATION",
  "CONSTRUCTORDECLARATOR", "SIMPLETYPENAME", "CONSTRUCTORBODY",
  "EXPLICITCONSTRUCTORINVOCATION", "SUPER1", "SUPER2", "SUPER3",
  "FIELDMODIFIERS", "METHODMODIFIERS", "TYPEARGUMENTS", "TYPEARGUMENTLIST",
  "TYPEARGUMENT", "WILDCARD", "WILDCARDBOUNDS", "INTERFACETYPE", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-679)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-528)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2462,  -679,   -82,  -679,  -679,  -679,  -679,  -679,  -679,  -679,
      68,   -15,  -679,   126,  2612,  -679,  6213,  -679,  -679,  -679,
    -679,   739,  1191,  1664,   463,   210,   166,   143,    56,   504,
    -679,  -679,  -679,  -679,   197,  -679,  -679,  -679,  -679,  -679,
     237,   250,  -679,  -679,  -679,  -679,  -679,  -679,  -679,   257,
     277,  -679,  -679,  -679,  -679,  -679,  -679,  -679,   280,   284,
     295,   295,   302,   374,   310,   247,   210,  -679,  1841,  -679,
     249,   309,  -679,    10,  2133,  -679,   374,   310,   247,   210,
     463,   210,   504,   463,   210,   504,   463,   210,   504,   174,
     209,  -679,  -679,  -679,  -679,  -679,   317,  -679,  -679,   441,
     310,   247,   210,  -679,   247,   210,  -679,   210,  -679,  -679,
    -679,  -679,  -679,  -679,  -679,  -679,  -679,  -679,  -679,  -679,
     259,   210,   332,   449,   361,  -679,  -679,  -679,  -679,  -679,
    -679,  -679,  -679,  3434,  -679,  -679,   870,  1841,  -679,  -679,
    -679,  -679,   541,  -679,  -679,  -679,  -679,    63,   494,   969,
    2690,  2424,  1481,  3246,  -679,    31,  -679,   506,  -679,  -679,
     536,   332,  -679,  -679,  2133,  -679,  1154,  -679,  2027,  2768,
    1497,  -679,   310,   247,   210,  -679,   247,   210,  -679,   210,
    -679,   374,   310,   247,   210,  -679,  -679,   374,   310,   247,
     210,   374,   310,   247,   210,  -679,  -679,   374,   310,   247,
     210,   374,   310,   247,   210,  -679,  -679,   374,   310,   247,
     210,   403,  -679,   284,  -679,   295,   410,   247,   210,  -679,
     210,  -679,  -679,   210,  -679,  -679,  -679,  3908,  -679,  1892,
     423,   584,   480,  -679,   523,   423,    20,  -679,  5744,  5804,
    5804,  -679,  -679,  -679,  -679,  -679,  -679,  -679,   274,  1444,
    -679,   421,  2183,  5744,  5744,  -679,    12,    16,  3702,  5744,
     539,   554,  -679,  -679,   618,  -679,    48,   555,   560,   890,
    -679,   586,  -679,  -679,   705,   897,   331,   601,  -679,  -679,
     343,  -679,   411,  -679,  -679,   983,  -679,  -679,   579,   722,
     724,  -679,  3434,  -679,  -679,  -679,   642,   549,  -679,  -679,
    -679,  -679,   651,  -679,  -679,  -679,  -679,  -679,  -679,  -679,
    -679,  -679,  -679,  -679,  -679,  -679,  1332,  1081,  1340,   332,
     332,   659,  -679,  -679,  -679,  -679,  -679,   295,  3220,   210,
    -679,    81,   361,   541,    63,   361,   541,  -679,  -679,  -679,
    -679,   541,  -679,  -679,  -679,  -679,  -679,  -679,  -679,   549,
    -679,  -679,  -679,  -679,  -679,  -679,  -679,  -679,  -679,   541,
     678,  -679,   541,  -679,  -679,   361,  -679,   247,   210,  -679,
     210,  -679,  -679,   210,  -679,  -679,   310,   247,   210,  -679,
     247,   210,  -679,   210,  -679,  -679,  -679,   310,   247,   210,
    -679,   247,   210,  -679,   210,  -679,   310,   247,   210,  -679,
     247,   210,  -679,   210,  -679,  -679,  -679,   310,   247,   210,
    -679,   247,   210,  -679,   210,  -679,   310,   247,   210,  -679,
     247,   210,  -679,   210,  -679,  -679,  -679,   310,   247,   210,
    -679,   247,   210,  -679,   210,  -679,   661,   668,  -679,  -679,
    -679,   210,  -679,  -679,  -679,  -679,   541,  3359,  4155,  3786,
    3246,  1206,   208,   691,  -679,   694,   712,   549,  -679,  3765,
    -679,   703,  -679,    62,    20,  5804,  5804,  5804,  5804,  2614,
      48,   555,   718,  -679,  -679,  -679,  -679,  -679,    15,   695,
     709,   714,   700,   727,   243,   602,   753,   683,  -679,  -679,
    -679,  -679,   579,  -679,  -679,  -679,   145,    37,  -679,  -679,
    -679,  -679,   101,   103,   549,  -679,     9,   738,   743,   743,
     755,   649,   764,   173,  -679,   768,  -679,   778,  -679,   780,
     786,  5744,  5744,  3825,  3530,   141,  -679,   102,  -679,   111,
      17,  3888,  5744,    25,  1625,  -679,  -679,  -679,  -679,  -679,
    -679,  5744,   156,    29,  5744,  -679,  -679,  -679,  -679,  -679,
     787,   799,  -679,   423,   423,  1371,  -679,   800,  -679,   328,
     792,  1494,   368,  -679,   347,  3434,  3434,     0,  -679,  -679,
    2125,   263,   802,   314,  -679,  -679,   486,  -679,   210,  -679,
     489,  -679,  -679,   520,  -679,  -679,  -679,   572,  -679,   210,
    -679,  -679,  -679,   247,   210,  -679,   210,  -679,  -679,   210,
    -679,  -679,  -679,  -679,   247,   210,  -679,   210,  -679,  -679,
     210,  -679,  -679,   247,   210,  -679,   210,  -679,  -679,   210,
    -679,  -679,  -679,  -679,   247,   210,  -679,   210,  -679,  -679,
     210,  -679,  -679,   247,   210,  -679,   210,  -679,  -679,   210,
    -679,  -679,  -679,  -679,   247,   210,  -679,   210,  -679,  -679,
     210,  -679,  -679,   295,   781,  -679,  -679,   541,   541,   541,
     541,   787,    40,   334,  -679,   790,   801,  -679,   806,  -679,
    2999,  -679,  -679,  -679,  -679,   811,  -679,  -679,  -679,  -679,
    -679,  -679,  5744,  5804,  5804,  5804,  5804,  5804,  5804,  5804,
    3948,  4011,   295,  5804,  5804,  5804,  5804,  5804,  5804,  5804,
    5804,  -679,   707,   815,   716,   799,   728,  -679,   440,  -679,
    -679,  4071,   205,   743,  -679,   205,   743,  4134,  -679,   816,
    -679,  -679,  5744,  -679,  -679,  -679,  -679,   820,   821,   825,
    -679,   367,  -679,   177,   827,  -679,   721,  -679,  -679,  -679,
    -679,   216,  -679,  -679,   417,   832,   834,  -679,   733,  4194,
    1444,   818,  -679,   848,   852,  -679,  -679,   740,   847,  -679,
     746,   853,  -679,  -679,  -679,   872,   434,   295,  4257,  4317,
     260,    59,   140,  -679,  -679,  3434,   861,   864,    42,   761,
     178,  -679,  1873,  2275,  -679,  -679,  -679,  -679,  -679,  -679,
    -679,   210,  -679,  -679,  -679,  -679,  -679,   210,  -679,  -679,
    -679,   210,  -679,  -679,  -679,  -679,  -679,   210,  -679,  -679,
    -679,   210,  -679,  -679,  -679,  -679,  -679,   210,  -679,  -679,
    -679,  -679,   295,  -679,  -679,  -679,  -679,   712,   787,   822,
    1945,  -679,  -679,  -679,  -679,   891,   896,  -679,   869,   695,
     709,   714,   700,   727,   243,   243,  5804,   602,  5804,   602,
    -679,   753,   753,   753,   683,   683,  -679,  -679,  -679,  -679,
    4380,   892,   295,   295,  -679,     9,  -679,   894,  -679,   712,
    -679,  -679,   712,   210,   437,  4440,   903,  3617,  3530,  -679,
     184,   191,  4503,   910,  -679,  -679,  5744,  -679,  -679,  4563,
     912,  5867,   922,  5744,  4637,  6199,  -679,  4697,   917,  -679,
    2051,  -679,  -679,   926,   438,   927,   502,   398,   142,   921,
     179,   928,   185,  -679,  4760,  4820,   823,  -679,  -679,  -679,
     537,  -679,  -679,  -679,  -679,  -679,  -679,  -679,  -679,   712,
    -679,   787,   540,  -679,  3765,  5804,   602,   602,  -679,   552,
    4883,  -679,  -679,  -679,  -679,  -679,   210,   210,   561,  -679,
     930,   933,   641,   936,  -679,   857,  -679,   873,  -679,  -679,
    -679,  -679,  -679,  -679,  -679,   833,   940,   838,  -679,   596,
    4943,  -679,  -679,   599,  5006,  3530,   889,   852,  5890,   946,
    5950,   955,  -679,  -679,   603,  5066,  -679,   621,  -679,   967,
    -679,   968,  5129,   962,  5189,   963,  5252,   964,   973,   622,
     977,   623,  -679,  -679,   712,   787,  -679,  -679,  -679,  -679,
     624,  -679,  -679,   210,  5744,  5744,  3617,  1734,  3530,  -679,
    5312,   972,  -679,  -679,   635,  -679,  -679,   646,  -679,  3530,
    3530,   974,  3530,  3530,   975,  5973,  -679,  -679,   657,  -679,
    -679,  -679,   980,   666,  5375,   984,   669,  5435,   986,   673,
    5498,  -679,   989,  -679,   992,   712,  -679,  -679,   985,   997,
    -679,  5558,   979,  1009,  -679,  -679,   682,  5621,  -679,  -679,
    -679,  -679,  3530,  -679,  -679,  3530,  3530,  1004,  -679,  -679,
    1014,  1015,   688,  -679,  1018,  1027,   689,  -679,  1028,  1029,
     696,  -679,  -679,  3617,  3617,  6033,  1032,  5744,  5681,  -679,
    -679,   704,  -679,  -679,  -679,  3530,  -679,  -679,  1035,  -679,
    -679,  1038,  -679,  -679,  1041,   970,  -679,  3617,  1036,  6056,
    1037,  6116,  1043,  -679,  -679,  -679,  -679,  -679,  3617,  -679,
    3617,  3617,  1039,  3617,  3617,  1047,  6139,  -679,  -679,  -679,
    3617,  -679,  -679,  3617,  3617,  1049,  -679,  -679,  -679,  3617,
    -679
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    29,     0,   552,   553,   554,   558,   559,   567,   568,
       0,     0,     2,     0,     0,    26,     0,    28,    36,   178,
      31,     0,     0,     0,   101,     0,     0,     0,     0,     0,
       1,     3,    27,    30,     0,   555,   556,   557,   560,   561,
       0,     0,   564,   565,   566,   562,   563,   569,   570,     0,
       0,   573,   574,   575,   576,   577,   571,   572,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   167,     0,    37,
       0,     0,    32,     0,     0,   117,     0,     0,     0,     0,
     101,     0,     0,   101,     0,     0,   101,     0,     0,   183,
       0,   180,    20,   188,    19,   607,   189,   190,   193,   192,
       0,     0,     0,    48,     0,     0,    52,     0,    54,    55,
       7,    10,    11,    12,    13,    14,    15,    16,   206,   168,
       0,   558,     0,    20,     0,     4,     6,     8,     9,     5,
      17,    18,   205,     0,   195,   207,     0,     0,   197,   199,
     203,   204,     0,   200,   201,   426,   202,     0,     0,     0,
       0,     0,     0,     0,    34,     0,    24,     0,    25,   177,
       0,     0,   176,   169,     0,   171,     0,   173,     0,     0,
       0,   109,     0,     0,     0,   113,     0,     0,   115,     0,
     116,     0,     0,     0,     0,    38,   133,     0,     0,     0,
       0,     0,     0,     0,     0,    39,   149,     0,     0,     0,
       0,     0,     0,     0,     0,    40,   165,     0,     0,     0,
       0,     0,   182,     0,   179,     0,     0,     0,     0,    44,
       0,    46,    47,     0,    50,    51,    53,     0,   427,     0,
     396,   216,     0,   212,   215,   395,     7,   457,     0,     0,
       0,   249,   250,   251,   252,   253,   254,   255,     0,   559,
     241,     0,     0,     0,     0,   441,     0,     0,     0,     0,
       0,     0,   166,   435,   225,   440,     6,    18,     0,   378,
     436,     0,   429,   459,     0,   245,   377,   237,   239,   240,
     244,   265,   247,   248,   238,   246,   460,   461,     0,   462,
     463,   448,     0,   430,   432,   433,     0,     0,   434,   442,
     449,   450,     0,   451,   452,   453,   454,   455,   456,   443,
     444,   445,   446,   447,   490,   491,     0,     0,     0,     0,
       0,     0,   196,   198,   425,   385,   424,     0,     0,     0,
     516,     0,     0,     0,     0,     0,     0,   578,   579,   587,
     588,     0,   582,   583,   584,   585,   586,   580,   581,     0,
     593,   594,   595,   596,   597,   591,   589,   590,   592,     0,
       0,    33,     0,   170,   172,     0,   105,     0,     0,   107,
       0,   108,   111,     0,   112,   114,     0,     0,     0,    63,
       0,     0,    67,     0,    69,    70,   125,     0,     0,     0,
     129,     0,     0,   131,     0,   132,     0,     0,     0,    78,
       0,     0,    82,     0,    84,    85,   141,     0,     0,     0,
     145,     0,     0,   147,     0,   148,     0,     0,     0,    93,
       0,     0,    97,     0,    99,   100,   157,     0,     0,     0,
     161,     0,     0,   163,     0,   164,   184,     0,   181,   191,
     194,     0,    42,    43,    45,    49,     0,     0,     0,     0,
       0,     0,     0,     0,   400,     0,   217,     0,   211,     0,
     397,     0,   258,     0,     0,     0,     0,     0,     0,   379,
       0,     0,     0,   220,   222,   244,   247,   221,   335,   337,
     339,   341,   343,   345,   347,   350,   356,   360,   363,   367,
     368,   371,   374,   380,   381,   355,   379,   378,   245,   246,
     372,   373,     0,     0,     0,   259,     0,    20,   320,   321,
       0,     0,     0,     0,   468,     0,   470,     0,   473,     0,
       0,     0,     0,     0,     0,     0,   256,     0,   257,     0,
       0,     0,     0,     0,     0,   228,   229,   230,   231,   232,
     233,     0,     0,     0,     0,   382,   383,   428,   431,   437,
     216,   439,   458,   402,   399,     0,   406,   403,   404,     0,
     241,   225,   224,   531,   377,     0,     0,     0,   515,   519,
       0,     0,     0,     0,   417,   420,     0,   386,     0,   518,
       0,   387,   388,     0,   389,    35,   174,     0,   103,     0,
     104,   106,   110,     0,     0,    59,     0,    61,    62,     0,
      65,    66,    68,   121,     0,     0,   123,     0,   124,   127,
       0,   128,   130,     0,     0,    74,     0,    76,    77,     0,
      80,    81,    83,   137,     0,     0,   139,     0,   140,   143,
       0,   144,   146,     0,     0,    89,     0,    91,    92,     0,
      95,    96,    98,   153,     0,     0,   155,     0,   156,   159,
       0,   160,   162,     0,   185,    41,   390,     0,     0,     0,
       0,   407,     0,     0,   415,     0,     0,    21,     0,   213,
       0,   214,   218,   219,   263,     0,   262,   369,   370,   376,
     375,   243,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   309,     0,   235,     0,   438,   603,   601,     0,   599,
     602,     0,   318,   316,   327,   319,   317,     0,   277,     0,
     474,   466,     0,   469,   471,   472,   475,     0,     0,     0,
     476,     0,   242,     0,    24,   267,     0,   260,   261,   311,
     307,     0,   280,   278,     0,     0,    25,   266,     0,     0,
       0,   511,   513,     0,   510,   223,   308,     0,   234,   268,
       0,     0,   401,   398,   523,     0,     0,     0,     0,     0,
       0,     0,     0,   530,   529,     0,     0,     0,     0,     0,
     216,   419,     0,     0,   520,   209,   517,   210,   208,   175,
     102,     0,    57,    58,    60,    64,   119,     0,   120,   122,
     126,     0,    72,    73,    75,    79,   135,     0,   136,   138,
     142,     0,    87,    88,    90,    94,   151,     0,   152,   154,
     158,   186,     0,   391,   392,   393,   394,   410,   408,     0,
       0,    22,   325,   323,   330,     0,   324,   264,     0,   338,
     340,   342,   344,   346,   348,   349,     0,   351,     0,   352,
     384,   357,   358,   359,   361,   362,   365,   364,   366,   304,
       0,     0,     0,     0,   604,     0,   598,     0,   314,   312,
     328,   315,   313,   269,     0,     0,     0,     0,     0,   334,
       0,     0,     0,     0,   306,   303,     0,   281,   332,     0,
       0,     0,     0,     0,     0,     0,   302,     0,     0,   333,
       0,   524,   405,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   528,     0,     0,     0,   421,   422,   521,
       0,   418,    56,   118,    71,   134,    86,   150,   187,   412,
     416,   409,     0,   322,   326,     0,   354,   353,   294,     0,
       0,   605,   606,   600,   329,   270,   271,   273,     0,   467,
       0,     0,   225,     0,   477,   442,   482,     0,   481,   483,
     484,   487,   488,   489,   310,     0,   236,     0,   282,     0,
       0,   279,   286,     0,     0,     0,     0,   512,     0,     0,
       0,     0,   514,   290,     0,     0,   525,     0,   536,     0,
     532,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   423,   522,   411,   414,   331,   336,   295,   296,
       0,   272,   274,   275,     0,     0,     0,     0,     0,   305,
       0,     0,   283,   284,     0,   287,   288,     0,   492,     0,
       0,     0,     0,     0,     0,     0,   291,   292,     0,   526,
     537,   533,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   538,     0,   534,     0,   413,   297,   276,     0,     0,
     485,     0,   511,     0,   478,   298,     0,     0,   285,   289,
     493,   494,     0,   508,   496,     0,     0,     0,   293,   544,
       0,     0,     0,   540,     0,     0,     0,   548,     0,     0,
       0,   539,   535,     0,     0,     0,     0,     0,     0,   299,
     300,     0,   495,   497,   498,     0,   545,   546,     0,   541,
     542,     0,   549,   550,     0,     0,   486,     0,     0,     0,
       0,     0,     0,   301,   499,   547,   543,   551,     0,   500,
       0,     0,     0,     0,     0,     0,     0,   479,   501,   502,
       0,   509,   504,     0,     0,     0,   503,   505,   506,     0,
     507
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -679,  -679,   161,   807,   -54,  -679,  -679,  -495,    95,  2095,
    -679,  -477,  -679,   204,  -679,   589,  -679,   138,  -679,   476,
    -679,  -179,   -29,   -61,  2535,  -679,   898,    39,   677,  -679,
     858,  -679,  -679,  1118,  2276,  -679,  3005,  -679,  2187,  -679,
     935,  -679,  -679,  -271,   617,  -520,  -661,  1754,  -679,    -9,
    -679,  -679,  -223,   747,  -679,  -679,  -679,  -230,   158,  -515,
     566,  1998,   294,  -679,  -679,  -678,  -679,   570,  -396,  -679,
     777,   146,  -679,   399,   405,   402,   397,   404,   107,  -647,
      55,   104,  -217,   464,   631,  -679,   798,   945,  1090,  -679,
     -34,   119,  -211,  -679,   325,  -110,  -301,  -416,   311,  -679,
    -151,  -679,  -679,   -10,  -313,  -287,  -679,  -679,  -530,  -247,
    -278,   203,  -679,  -679,  -482,  -679,  -679,  -679,  -679,  -679,
    -679,  -679,  -679,  -679,  -679,  -311,  -679,  -679,  -679,  -679,
    -679,  -679,  -679,  -679,  -679,    78,  -557,  -527,  -679,   948,
     971,  -326,  -679,    54,    57,   357,  -679,   871,   -96,  -679,
     235,  -679,  -679,  -214
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,   161,   125,   470,   127,   128,   129,   130,   471,
      94,   456,   268,   269,    14,    15,    16,   270,    18,    25,
      19,   271,    68,   134,    75,   164,   165,    20,   166,    90,
      91,   212,   654,    64,    65,    96,    66,    99,    69,   137,
     138,   139,   140,   232,   233,   234,   671,   743,   473,   474,
     274,   541,   275,   276,   277,   278,   279,   527,   475,   281,
     510,   744,   476,   283,   284,   673,   835,   713,   714,   836,
     285,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     141,   142,   329,   557,   558,   235,   453,   573,   574,   575,
     325,   143,   144,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   956,   957,   958,   959,   960,   312,
     313,   314,   961,   315,   962,   753,   976,   977,   146,   147,
     148,   330,   566,   316,   317,   318,   152,   153,   511,   708,
     709,   710,   864,    97
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,   439,   504,   568,   751,   548,   463,   754,   579,   834,
     735,   707,   230,   163,   126,   565,   498,   498,   747,   454,
     126,   706,   500,   501,   460,   514,   551,   682,   759,   516,
     572,   712,   715,   506,   868,   663,   529,   871,   461,   133,
     167,   506,    24,   847,   849,   506,   157,    74,    74,    74,
      74,   781,   752,    74,    21,   532,    74,    22,   145,    74,
     683,   576,   776,   779,   580,   916,   461,   360,    21,    72,
      21,    22,   272,    22,   777,   506,   322,    67,   583,   266,
     675,   533,   126,   126,   110,   111,   112,   113,   114,   115,
     116,   117,   133,   739,   587,   126,   126,   126,   126,   126,
      73,   733,   569,   363,   133,   733,   126,   135,   133,    29,
     126,   228,   126,   133,   126,   126,   126,   506,   328,   506,
     675,   909,   149,   578,   273,   150,    30,   145,   168,   675,
     167,   169,   326,    92,   158,   733,   515,    26,    17,   766,
     517,   740,   781,    74,    74,    74,   462,    74,    74,   746,
      74,   570,    17,   758,    17,   158,   506,   506,    74,    74,
      74,    74,   327,   523,   550,   -23,   550,   -20,    74,    74,
      74,    74,   506,   126,   528,   126,   135,   126,    74,    74,
      74,    74,   577,   746,   827,   581,   721,    71,   676,   525,
     582,   149,    27,   506,   150,   126,   455,   850,   126,   936,
     506,   937,   911,   731,   993,    92,   132,   506,   584,   553,
     554,   586,   162,   722,    28,   732,   733,   733,   168,    67,
     213,   169,   829,   668,    67,   701,   214,   703,   737,   124,
      70,   547,   567,   705,   463,   211,   869,   738,   266,   872,
     529,   995,   498,   498,   498,   498,   730,   997,   677,   678,
     679,   680,   786,   775,   765,   735,   747,   759,   917,   690,
     691,    67,   154,   133,   758,   734,   883,   563,   333,   336,
     341,   526,   359,  1006,   266,   132,   506,   126,   548,   362,
     756,   447,   664,   273,   448,   227,   779,   333,   336,   341,
      27,   280,   884,   155,   265,   656,   502,   320,   124,   133,
     328,   718,   162,   890,   133,   328,   437,   133,   964,   898,
     332,   335,   133,   349,    62,   966,   692,   870,   503,   273,
     870,    80,   907,   326,    67,   783,   326,   320,   215,   365,
     133,   326,   665,   133,   732,   784,   733,   664,    74,    74,
     885,    74,   762,   763,    74,   783,   446,   509,   768,   326,
     502,   929,   326,   542,  -465,   828,  -465,    23,    74,    74,
      74,    82,    74,    74,  -465,    74,   920,   941,   942,   542,
     707,    23,   503,    23,    83,   543,    61,    62,    74,    74,
      74,    85,    74,    74,   734,    74,   532,   780,    67,   880,
     452,   772,   452,   126,   126,   126,   126,   126,    74,    74,
      74,    86,    74,    74,    88,    74,   702,   704,    89,   752,
     265,   881,   771,   982,   932,  -378,  -378,   133,   992,    92,
     880,  1031,  -464,  1034,  -464,   151,    98,   282,   886,   736,
     670,   170,  -464,   156,   741,    60,   326,   748,   887,   821,
      61,    62,   881,   497,   497,   783,   757,   760,   886,   886,
     280,   865,   216,   265,  1004,   901,   229,   866,   946,   989,
     498,   498,   498,   498,   498,   498,   498,   498,   498,  -527,
     498,   498,   498,   498,   498,   498,   498,   498,  1077,    59,
     266,   856,   857,   858,   987,   231,   280,  1062,   548,   265,
     754,   457,   571,   458,   151,   133,   752,   457,   752,   785,
     457,   126,   787,   504,   773,   774,   823,   824,   825,   826,
      81,   266,   266,   886,   331,   273,   126,    84,    67,   361,
      59,   170,   327,   991,    60,   273,    87,   436,  1055,    61,
      62,   457,   562,   788,   440,   752,   133,   133,  1118,   110,
     111,   112,   113,   114,   115,   116,   117,   505,   783,   328,
     459,   783,    59,   752,   324,    67,   273,   273,  1003,   521,
      74,  1005,  1132,   886,  1135,    60,   657,   658,   659,   660,
      61,    62,   886,  1008,   522,    74,    74,   530,    74,  1145,
     531,    74,  1013,   457,   449,   789,   282,   110,   111,   112,
     113,   114,   115,   116,   117,    74,    74,   286,    74,   954,
     963,    74,   455,    32,   451,    33,   534,   886,   928,   833,
     886,   122,   662,   752,   886,    74,    74,  1022,    74,   544,
    1025,    74,   282,   498,  1036,   498,   545,   546,   133,   133,
     133,   133,   783,   886,   886,   886,   523,   752,   -23,   752,
     -20,   670,  1039,  1052,  1054,  1056,   886,   326,   326,   326,
     326,   693,   694,   695,   752,   549,  1068,   886,   524,   523,
      92,   -23,   525,   -20,   552,  -379,  -379,  1069,   886,   497,
     497,   497,   497,   550,   908,   910,   912,   886,  1078,   555,
     886,  1016,   280,   670,   886,   525,   670,  1080,  -379,  -379,
    1084,   585,   280,   886,  1088,   265,   126,  1028,   953,   886,
     886,    63,   666,  1099,   -20,  1060,    76,   886,    92,  1108,
    1111,   653,   498,   667,   913,   886,   571,  1114,   698,   699,
     700,   266,   674,   280,   280,  1123,   265,   265,   126,   126,
     668,   778,   535,   536,   537,   538,   539,   540,   730,   681,
    1064,   684,   -20,   687,   526,   136,   133,   685,   851,   852,
     853,  1070,  1071,   686,  1073,  1074,   286,   181,  -277,   187,
     191,   711,   197,   201,   287,   207,   273,   526,    74,  -380,
    -380,  -381,  -381,   718,   933,   717,   126,   720,    74,   688,
     689,   723,  1115,  1116,   965,   967,   696,   697,    74,   862,
     863,   724,   286,   725,  1102,   844,   845,  1103,  1104,   726,
     854,   855,    34,    35,    36,   455,  1129,    37,    38,    39,
     457,   767,   769,   782,   136,   954,   963,  1137,   282,  1138,
    1139,   830,  1141,  1142,   822,   831,   136,  1124,   282,  1146,
     837,   859,  1147,  1148,   829,   860,   875,   953,  1150,  1028,
     861,   877,   878,    40,   879,   883,   126,   882,   133,   133,
    1064,   888,  1070,  1071,   889,  1073,  1074,   890,   893,   282,
     282,   894,  1102,   895,   896,  1103,  1104,   897,   273,   273,
     898,  1124,   899,   110,   111,   112,   113,   114,   115,   116,
     117,   914,   273,   900,   915,   918,   273,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   930,   497,   497,   497,
     497,   497,   497,   497,   497,   670,   119,   934,   532,   935,
    1029,   265,   940,   944,   953,   953,   949,  -224,  -224,  -224,
    -224,  -224,  -224,   287,  -226,  -226,  -226,  -226,  -226,  -226,
     970,   288,   974,   280,   533,   978,   265,   985,   953,   988,
     990,   994,  -480,   662,   662,   319,   133,  1002,   996,   953,
    1014,   953,   953,  1015,   953,   953,  1017,  1019,  1018,   287,
    1020,   953,  1021,   266,   953,   953,   273,  1032,  1035,   273,
     953,   273,   110,   111,   112,   113,   114,   115,   116,   117,
    1040,  1041,  1044,  1047,  1050,    59,  1051,   133,   286,   133,
    1053,   662,  1067,  1079,   123,  1072,  1075,  1083,   286,  1087,
     133,   133,  1091,   133,   133,  1092,  1093,   273,   273,   273,
    -227,  -227,  -227,  -227,  -227,  -227,   499,   499,  1094,  1097,
     273,   273,  1098,   273,   273,  1105,   273,  1106,  1107,   286,
     286,  1109,    34,    35,    36,   280,   280,    37,    38,    39,
    1110,  1112,  1113,   133,   122,  1119,   133,   133,  1125,   280,
     497,  1126,   497,   280,  1127,  1128,  1136,  1130,  1133,   508,
    1140,   662,   364,   273,   133,   133,   273,   273,  1143,   282,
    1149,   438,   323,    40,   669,   564,   133,   719,   289,   716,
     955,  1007,   839,   842,   273,   273,   273,   841,   133,   840,
     288,   843,   902,   123,   921,  1063,   273,   334,   450,   133,
     943,   133,   133,     0,   133,   133,     0,   321,   273,     0,
     273,   133,   273,     0,   133,   133,     0,     0,     0,   273,
     133,   273,   273,     0,   273,   273,   288,   273,     0,     0,
       0,   273,     0,   280,   273,   273,   280,     0,   280,   497,
     273,     0,     0,     0,    41,    42,    43,    77,     0,    44,
      45,    46,     0,     0,     0,   287,     0,   110,   111,   112,
     113,   114,   115,   116,   117,   287,     0,     0,     0,     0,
      47,   282,   282,    48,   280,   280,   280,     0,   265,     0,
       0,   100,     0,     0,     0,   282,     0,   280,   280,   282,
     280,   280,     0,   280,   172,     0,   287,   287,   182,     0,
     188,   192,     0,   198,   202,     0,   208,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,   955,
       0,     0,     0,   290,     0,     0,     0,   661,     0,   319,
     280,     0,     0,   280,   280,     0,     0,   289,     0,   286,
       0,     0,   499,   499,   499,   499,     0,     0,     0,     0,
       0,   280,   280,   280,    41,    42,    43,     0,     0,    44,
      45,    46,     0,   280,     0,     0,     0,     0,     0,   282,
       0,     0,   282,   289,   282,   280,   570,   280,    92,   280,
      47,     0,     0,    48,     0,     0,   280,     0,   280,   280,
       0,   280,   280,     0,   280,    49,   955,   955,   280,   376,
       0,   280,   280,     0,     0,   387,     0,   280,     0,   396,
     282,   282,   282,     0,     0,   407,     0,     0,     0,   416,
     955,     0,   288,   282,   282,   427,   282,   282,     0,   282,
      92,   955,   288,   955,   955,     0,   955,   955,     0,     0,
       0,   286,   286,   955,     0,     0,   955,   955,     0,     0,
       0,     0,   955,     0,     0,   286,     0,     0,     0,   286,
       0,     0,     0,   288,   288,     0,   282,     0,     0,   282,
     282,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   290,     0,     0,     0,     0,   282,   282,   282,
       0,     0,   764,     0,     0,    34,    35,    36,     0,   282,
      37,    38,    39,    50,    51,    52,   287,     0,    53,    54,
      55,   282,     0,   282,     0,   282,     0,     0,   290,     0,
       0,     0,   282,     0,   282,   282,     0,   282,   282,    56,
     282,     0,    57,     0,   282,     0,     0,   282,   282,   286,
       0,   570,   286,   282,   286,     0,     0,   110,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,     0,
     499,   499,   499,   499,   499,   499,   499,   499,   499,   289,
     499,   499,   499,   499,   499,   499,   499,   499,     0,   289,
     286,   286,   286,     0,   110,   111,   112,   113,   114,   115,
     116,   117,     0,   286,   286,    92,   286,   286,     0,   286,
     110,   111,   112,   113,   114,   115,   116,   117,   287,   287,
     289,   289,   523,    59,   -23,     0,   -20,     0,     0,     0,
       0,     0,   287,   255,     0,     0,   287,     0,     0,     0,
       0,     0,     0,     0,   524,     0,   286,     0,   770,   286,
     286,  -379,  -379,     0,     0,   342,   343,     0,     0,   344,
     345,   346,   347,   348,     0,     0,     0,   286,   286,   286,
      50,    51,    52,     0,     0,    53,    54,    55,    92,   286,
       0,     0,   122,   288,     0,     0,     0,     0,     0,     0,
       0,   286,     0,   286,     0,   286,    56,   339,   340,    57,
       0,     0,   286,     0,   286,   286,     0,   286,   286,     0,
     286,     0,     0,     0,   286,    92,   287,   286,   286,   287,
       0,   287,     0,   286,   290,     0,     0,     0,   -20,     0,
     526,    92,     0,   499,   290,   499,     0,     0,   236,   111,
     112,   113,   114,   115,   116,   117,     0,     0,   749,     0,
       0,     0,     0,     0,     0,   238,     0,   287,   287,   287,
       0,     0,     0,     0,     0,   290,   290,     0,     0,     0,
     287,   287,     0,   287,   287,     0,   287,     0,     0,     0,
       0,     0,   239,   240,     0,   288,   288,     0,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   288,
       0,     0,     0,   288,     0,   750,     0,     0,     0,   250,
     251,   252,     0,   287,   255,     0,   287,   287,     0,     0,
       0,     0,   499,     0,     0,     0,     0,     0,     0,     0,
     289,     0,     0,     0,   287,   287,   287,    50,    51,    52,
       0,     0,    53,    54,    55,     0,   287,   236,   111,   112,
     113,   114,   115,   116,   117,     0,     0,  1061,   287,   469,
     287,     0,   287,    56,   238,     0,    57,     0,     0,   287,
       0,   287,   287,     0,   287,   287,     0,   287,    58,     0,
       0,   287,     0,   288,   287,   287,   288,     0,   288,     0,
     287,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,     0,     0,
       0,     0,     0,     0,   750,     0,     0,     0,   250,   251,
     252,     0,     0,   255,   288,   288,   288,     0,     0,     0,
       0,     0,   289,   289,     0,     0,     0,   288,   288,     0,
     288,   288,     0,   288,     0,     0,   289,     0,     0,     0,
     289,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,     0,     0,   118,    67,   119,    59,   469,     0,
       0,     0,     0,     0,     0,   290,   120,     0,     0,     0,
     288,     0,     0,   288,   288,     0,   110,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,     0,     0,     0,
       0,   288,   288,   288,   919,   110,   111,   112,   113,   114,
     115,   116,   117,   288,     2,     3,     4,     0,     0,     5,
     121,     7,   451,     0,     0,   288,   122,   288,     0,   288,
     289,     0,     0,   289,     0,   289,   288,     0,   288,   288,
       8,   288,   288,     9,   288,     0,     0,     0,   288,     0,
       0,   288,   288,   570,     0,    11,     0,   288,   110,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,     0,
       0,   289,   289,   289,     0,   123,   931,   290,   290,     0,
       0,     0,     0,     0,   289,   289,     0,   289,   289,     0,
     289,   290,     0,     0,     0,   290,     0,     0,     0,     0,
       0,     0,   472,     0,     0,     0,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   512,   513,     0,
       0,     0,   519,   520,     0,   570,    92,   289,     0,     0,
     289,   289,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,   289,   289,
     289,     0,     0,    59,     0,     0,     0,     0,     0,     0,
     289,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   289,     0,   289,   290,   289,     0,   290,    92,
     290,     0,   986,   289,     0,   289,   289,     0,   289,   289,
       0,   289,     0,     0,     0,   289,     0,     0,   289,   289,
      34,    35,    36,     0,   289,    37,    38,    39,     0,     0,
       0,     0,   122,     0,     0,     0,   290,   290,   290,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   290,
     290,   570,   290,   290,     0,   290,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,   110,   111,   112,   113,
     114,   115,   116,   117,     0,     0,   159,     0,   119,    59,
       0,    92,     0,     0,     0,    93,    95,     0,   120,     0,
       0,     0,   290,   131,     0,   290,   290,     0,     0,   131,
       0,     0,     0,     0,     0,    92,     0,     0,     0,     0,
       0,     0,     0,   290,   290,   290,   110,   111,   112,   113,
     114,   115,   116,   117,     0,   290,     2,     3,     4,   506,
       0,     5,     6,     7,     0,     0,     0,   290,   122,   290,
       0,   290,     0,   672,     0,     0,     0,     0,   290,     0,
     290,   290,     8,   290,   290,     9,   290,   160,   267,     0,
     290,   131,   131,   290,   290,     0,     0,     0,     0,   290,
       0,     0,     0,     0,   131,   131,   131,   131,   131,    92,
     103,   106,   108,   109,     0,   131,     0,    92,     0,   131,
       0,   131,     0,   131,   131,   131,     0,     0,   185,     0,
       0,   195,     0,     0,   205,   727,   728,   729,   110,   111,
     112,   113,   114,   115,   116,   117,   745,   219,   221,   222,
       0,   224,   225,     0,   226,   755,     0,     0,   761,     0,
       0,     0,     0,     0,     0,    78,   131,   507,     0,     0,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,     0,   131,     0,   131,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     104,     0,     0,     0,   131,   570,     0,   131,     0,     0,
       0,     0,   173,   176,     0,     0,   183,     0,   189,   193,
       0,   199,   203,     0,   209,     0,     0,     0,   379,   382,
     384,   385,     0,     0,     0,     0,   217,     0,   399,   402,
     404,   405,     0,     0,     0,     0,     0,   267,   419,   422,
     424,   425,     0,     0,     0,     0,     0,     0,     0,    92,
       0,     0,     0,     0,   442,   443,     0,   444,     0,     0,
     445,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   556,   267,   672,     0,   131,   110,   111,   112,
     113,   114,   115,   116,   117,     0,   838,     0,     0,     0,
      59,     0,     0,     0,     0,     0,     0,     0,   367,     0,
       0,     0,     0,     0,     0,     0,     0,   377,   380,     0,
       0,     0,     0,   388,   391,   867,     0,   397,   400,     0,
       0,     0,     0,   408,   411,     1,   876,   417,   420,     0,
       0,     0,     0,   428,   431,     0,     0,    50,    51,    52,
       0,     0,    53,    54,    55,   337,   338,     0,     0,   122,
       0,     0,     0,   892,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    56,   339,   340,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     4,    58,     0,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   131,   131,   131,   131,     0,    92,     0,
       0,     8,     0,     0,     9,     0,     0,     0,     0,     0,
      10,     0,     0,   595,   597,   598,    11,   600,   601,     0,
     602,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   615,   617,   618,     0,   620,   621,    12,
     622,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,     0,   635,   637,   638,     0,   640,   641,     0,
     642,   171,   175,   178,   180,     0,     0,   186,     0,     0,
     196,     0,     0,   206,     0,     1,     0,     0,   655,   267,
       0,     0,   523,     0,   -23,     0,   -20,     0,     0,     0,
     971,  -225,  -225,  -225,  -225,  -225,  -225,   979,   981,     0,
     131,     0,   593,     0,     0,     0,     0,     0,   525,     0,
     267,   267,     0,   604,     0,   131,     0,     0,     0,     0,
       0,     0,   613,     0,     0,     2,     3,     4,     0,     0,
       5,     6,     7,   624,     0,     0,     0,     0,   672,     0,
       0,     0,   633,   110,   111,   112,   113,   114,   115,   116,
     117,     8,     0,   644,     9,     0,    59,   366,   369,   371,
      10,   372,   374,     0,   375,   874,    11,     0,     0,     0,
       0,     0,   386,   390,   393,   395,     0,     0,     0,     0,
       0,     0,   406,   410,   413,   415,     0,     0,   -20,    31,
     526,     0,   426,   430,   433,   435,     0,     0,    95,     0,
       0,     0,     0,    41,    42,    43,     0,     0,    44,    45,
      46,     0,     0,     0,     0,   122,   904,   906,  1058,  1059,
       0,   110,   111,   112,   113,   114,   115,   116,   117,    47,
     792,   793,    48,   794,    59,     0,   795,   131,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
     802,   803,     0,   804,     0,     0,   805,     0,     0,     0,
       0,     0,     0,     0,    92,  1096,     0,     0,     0,     0,
     812,   813,     0,   814,     0,     0,   815,     0,     0,     0,
       0,    41,    42,    43,     0,     0,    44,    45,    46,     0,
       0,     0,     0,   122,     0,   131,     0,     0,     0,     0,
       0,  1120,  1122,     0,     0,     0,     0,    47,   939,     0,
      48,     0,   556,     0,     0,     0,     0,     0,     0,     0,
     267,     0,     0,   948,     0,     0,     0,   131,   131,     0,
     969,     0,     0,     0,     0,     0,     0,   973,     0,     0,
       0,     0,    92,     0,     0,   984,     0,     0,     0,     0,
       0,     0,   588,   590,     0,   591,     0,     0,   592,     0,
       0,     0,   999,  1001,     0,     0,     0,    95,     0,     0,
       0,     0,   603,   606,   608,   131,   609,   611,     0,   612,
       0,     0,     0,     0,     0,     0,     0,     0,  1010,     0,
       0,     0,   623,   626,   628,     0,   629,   631,     0,   632,
       0,     0,     0,     0,     0,     0,     0,   131,   131,     0,
     131,     0,   643,   646,   648,     0,   649,   651,  1024,   652,
       0,     0,  1027,     0,     0,     0,     0,     0,   922,     0,
       0,     0,     0,  1038,     0,     0,     0,     0,   924,     0,
    1043,     0,  1046,     0,  1049,   131,     0,     0,   926,     0,
       0,     0,   464,   111,   112,   113,   114,   115,   116,   117,
     832,     0,     0,    67,   119,     0,     0,     0,  1066,   238,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   465,   466,    79,     0,     0,     0,     0,     0,
     467,   468,  1082,     0,     0,  1086,   239,   240,  1090,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     945,   248,     0,     0,     0,  1101,     0,     0,   102,   105,
     107,     0,     0,   250,   251,   252,     0,     0,     0,     0,
       0,   174,   177,   179,     0,   184,     0,   190,   194,     0,
     200,   204,     0,   210,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   218,   220,     0,     0,   223,
       0,     0,   267,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   469,   790,     0,     0,     0,     0,     0,
       0,     0,     0,  1011,  1012,     0,     0,     0,     0,   796,
     798,     0,   799,     0,     0,   800,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   806,
     808,     0,   809,     0,     0,   810,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   368,   370,   816,
     818,   373,   819,     0,     0,   820,   378,   381,   383,     0,
       0,     0,   389,   392,   394,     0,   398,   401,   403,     0,
    1057,     0,   409,   412,   414,     0,   418,   421,   423,     0,
       0,     0,   429,   432,   434,     0,     0,     0,     0,     0,
       0,     0,   441,   236,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   237,    67,   119,   506,     0,     0,     0,
     238,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,    59,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   559,     2,     3,     4,     0,     0,     5,     6,
     249,     0,     0,     0,   560,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,     0,   261,   262,   263,     8,
     350,   351,     9,     0,   352,   353,   354,     0,     0,     0,
       0,   122,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   923,     0,     0,   355,   356,   357,   358,     0,
       0,     0,   925,     0,   561,     0,     0,     0,     0,     0,
       0,     0,   927,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,   116,   117,
      92,     0,   589,     0,     0,    59,     0,     0,     0,     0,
       0,   594,   596,     0,     0,   599,     0,     0,     0,     0,
       0,     0,   605,   607,     0,     0,   610,     0,     0,     0,
       0,   614,   616,     0,     0,   619,     0,     0,     0,     0,
       0,     0,   625,   627,     0,     0,   630,     0,     0,     0,
       0,   634,   636,    35,    36,   639,     0,    37,    38,    39,
       0,     0,   645,   647,   122,     0,   650,   236,   111,   112,
     113,   114,   115,   116,   117,     0,     0,   237,    67,   119,
       0,     0,     0,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   239,   240,    92,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     2,     3,     4,
       0,     0,     5,     6,   249,     0,     0,     0,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,     0,
     261,   262,   263,     8,     0,     0,     9,     0,     0,     0,
       0,     0,     0,   464,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   237,    67,     0,     0,     0,     0,     0,
     238,     0,     0,     0,     0,     0,     0,     0,   264,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,     0,     0,     0,     0,   791,     0,
       0,     0,     0,     0,   250,   251,   252,   253,   254,   797,
     256,   257,   258,   259,   260,     0,   261,   262,   801,     0,
     464,   111,   112,   113,   114,   115,   116,   117,     0,   807,
     237,    67,     0,     0,     0,     0,     0,   238,   811,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   817,
       0,     0,     0,     0,   264,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,   251,   252,   253,   254,     0,   256,   257,   258,
     259,   950,     0,   951,   262,   464,   111,   112,   113,   114,
     115,   116,   117,     0,     0,   518,     0,     0,     0,     0,
       0,     0,   238,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   465,   466,     0,     0,     0,
       0,   952,     0,   467,   468,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,     0,     0,   464,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,    67,
       0,     0,     0,     0,     0,   238,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,   465,   466,
       0,     0,    59,     0,     0,     0,   467,   468,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   469,   248,   464,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   250,
     251,   252,     0,     0,   674,   238,     0,     0,     0,     0,
      51,    52,     0,     0,    53,    54,    55,     0,   465,   466,
       0,   122,     0,     0,     0,     0,   467,   468,     0,     0,
       0,     0,   239,   240,     0,    56,   339,   340,    57,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   469,
       0,   464,   111,   112,   113,   114,   115,   116,   117,   250,
     251,   252,     0,     0,     0,     0,     0,     0,   238,   742,
      92,   110,   111,   112,   113,   114,   115,   116,   117,     0,
       0,   465,   466,     0,    59,     0,     0,     0,     0,   467,
     468,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,   469,
     248,   464,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,   250,   251,   252,     0,     0,     0,   238,     0,
       0,     0,     3,     4,     0,   846,     5,     6,     7,     0,
       0,   465,   466,   122,     0,     0,     0,     0,     0,   467,
     468,     0,     0,     0,     0,   239,   240,     8,     0,     0,
       9,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   469,     0,   464,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,    92,     0,     0,     0,     0,     0,   848,     0,
       0,     0,     0,     0,   465,   466,     0,     0,     0,     0,
       0,     0,   467,   468,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   496,   248,   464,   111,   112,   113,   114,   115,
     116,   117,     0,     0,     0,   250,   251,   252,     0,     0,
     667,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   465,   466,     0,     0,     0,     0,
       0,     0,   467,   468,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   496,     0,   464,   111,   112,
     113,   114,   115,   116,   117,   250,   251,   252,     0,     0,
       0,     0,     0,     0,   238,   873,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,     0,   465,   466,     0,
       0,    59,     0,     0,     0,   467,   468,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   469,   248,   464,   111,   112,
     113,   114,   115,   116,   117,     0,     0,   891,   250,   251,
     252,     0,     0,     0,   238,     0,     0,     0,     0,    42,
      43,     0,     0,    44,    45,    46,     0,   465,   466,     0,
     122,     0,     0,     0,     0,   467,   468,     0,     0,     0,
       0,   239,   240,     0,    47,     0,     0,    48,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   469,     0,
     464,   111,   112,   113,   114,   115,   116,   117,   250,   251,
     252,     0,     0,     0,     0,     0,     0,   238,   903,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     465,   466,     0,     0,     0,     0,     0,     0,   467,   468,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,   469,   248,
     464,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,   250,   251,   252,     0,     0,     0,   238,   905,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     465,   466,     0,     0,     0,     0,     0,     0,   467,   468,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,   469,     0,   464,   111,   112,   113,   114,   115,   116,
     117,   250,   251,   252,     0,     0,     0,     0,     0,     0,
     238,   938,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   465,   466,     0,     0,     0,     0,     0,
       0,   467,   468,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   469,   248,   464,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,   947,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   465,   466,     0,     0,     0,     0,     0,
       0,   467,   468,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   469,     0,   464,   111,   112,   113,
     114,   115,   116,   117,   250,   251,   252,     0,     0,     0,
       0,     0,     0,   238,   968,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   465,   466,     0,     0,
       0,     0,     0,     0,   467,   468,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   469,   248,   464,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,   972,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   465,   466,     0,     0,
       0,     0,     0,     0,   467,   468,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   469,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   250,   251,   252,
     464,   111,   112,   113,   114,   115,   116,   117,     0,     0,
     980,     0,     0,     0,     0,     0,     0,   238,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     465,   466,     0,     0,     0,     0,     0,     0,   467,   468,
       0,     0,     0,     0,   239,   240,     0,   469,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
     464,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,   250,   251,   252,     0,     0,     0,   238,   983,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     465,   466,     0,     0,     0,     0,     0,     0,   467,   468,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,   469,     0,   464,   111,   112,   113,   114,   115,   116,
     117,   250,   251,   252,     0,     0,     0,     0,     0,     0,
     238,   998,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   465,   466,     0,     0,     0,     0,     0,
       0,   467,   468,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   469,   248,   464,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,  1000,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   465,   466,     0,     0,     0,     0,     0,
       0,   467,   468,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   469,     0,   464,   111,   112,   113,
     114,   115,   116,   117,   250,   251,   252,     0,     0,     0,
       0,     0,     0,   238,  1009,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   465,   466,     0,     0,
       0,     0,     0,     0,   467,   468,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   469,   248,   464,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,  1023,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   465,   466,     0,     0,
       0,     0,     0,     0,   467,   468,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   469,     0,   464,
     111,   112,   113,   114,   115,   116,   117,   250,   251,   252,
       0,     0,     0,     0,     0,     0,   238,  1026,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   465,
     466,     0,     0,     0,     0,     0,     0,   467,   468,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,   469,   248,   464,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,     0,   238,  1037,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   465,
     466,     0,     0,     0,     0,     0,     0,   467,   468,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     469,     0,   464,   111,   112,   113,   114,   115,   116,   117,
     250,   251,   252,     0,     0,     0,     0,     0,     0,   238,
    1042,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   465,   466,     0,     0,     0,     0,     0,     0,
     467,   468,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     469,   248,   464,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,   250,   251,   252,     0,     0,     0,   238,
    1045,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   465,   466,     0,     0,     0,     0,     0,     0,
     467,   468,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   469,     0,   464,   111,   112,   113,   114,
     115,   116,   117,   250,   251,   252,     0,     0,     0,     0,
       0,     0,   238,  1048,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   465,   466,     0,     0,     0,
       0,     0,     0,   467,   468,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,   469,   248,   464,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,   250,   251,   252,     0,
       0,     0,   238,  1065,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   465,   466,     0,     0,     0,
       0,     0,     0,   467,   468,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,   469,     0,   464,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,     0,
       0,     0,     0,     0,     0,   238,  1081,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   465,   466,
       0,     0,     0,     0,     0,     0,   467,   468,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   469,   248,   464,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   250,
     251,   252,     0,     0,     0,   238,  1085,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   465,   466,
       0,     0,     0,     0,     0,     0,   467,   468,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   469,
       0,   464,   111,   112,   113,   114,   115,   116,   117,   250,
     251,   252,     0,     0,     0,     0,     0,     0,   238,  1089,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   465,   466,     0,     0,     0,     0,     0,     0,   467,
     468,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,   469,
     248,   464,   111,   112,   113,   114,   115,   116,   117,     0,
       0,  1095,   250,   251,   252,     0,     0,     0,   238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   465,   466,     0,     0,     0,     0,     0,     0,   467,
     468,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   469,     0,   464,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,  1100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   465,   466,     0,     0,     0,     0,
       0,     0,   467,   468,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   469,   248,   464,   111,   112,   113,   114,   115,
     116,   117,     0,     0,  1121,   250,   251,   252,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   465,   466,     0,     0,     0,     0,
       0,     0,   467,   468,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   469,     0,   464,   111,   112,
     113,   114,   115,   116,   117,   250,   251,   252,     0,     0,
       0,     0,     0,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   465,   466,     0,
       0,     0,     0,     0,     0,   467,   468,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   469,   248,   464,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,   250,   251,
     252,     0,     0,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   465,   466,     0,
       0,     0,     0,     0,     0,   467,   468,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   469,     0,
     464,   111,   112,   113,   114,   115,   116,   117,   250,   251,
     252,     0,     0,     0,     0,     0,     0,   238,   975,     0,
       0,     0,     0,   464,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     238,  1030,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,   496,   248,
       0,     0,     0,     0,     0,     0,     0,   239,   240,     0,
       0,   250,   251,   252,   241,   242,   243,   244,   245,   246,
     247,     0,   248,   464,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,  1033,     0,     0,     0,     0,   464,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,     0,     0,     0,
       0,   469,     0,   238,  1076,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   469,     0,     0,     0,     0,     0,
     239,   240,     0,     0,   250,   251,   252,   241,   242,   243,
     244,   245,   246,   247,     0,   248,   464,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,  1117,     0,     0,     0,     0,   464,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,     0,     0,   469,     0,   238,  1131,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   469,     0,     0,
       0,     0,     0,   239,   240,     0,     0,   250,   251,   252,
     241,   242,   243,   244,   245,   246,   247,     0,   248,   464,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,     0,   238,  1134,     0,     0,
       0,     0,   464,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,     0,     0,     0,     0,   469,     0,   238,
    1144,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     469,     0,     0,     0,     0,     0,   239,   240,     0,     0,
     250,   251,   252,   241,   242,   243,   244,   245,   246,   247,
       0,   248,   464,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,   250,   251,   252,     0,     0,     0,   238,
       0,     0,     0,     0,     0,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     469,     0,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   469,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   251,   252,     2,     3,     4,     0,
       0,     5,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,     9,     0,     0,     0,     0,
       0,    10,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,   469
};

static const yytype_int16 yycheck[] =
{
      29,   215,   249,   329,   534,   292,   236,   534,   334,   670,
     525,   506,   122,    74,    68,   328,   239,   240,   533,   230,
      74,    12,   239,   240,   235,    13,   297,    12,   543,    13,
     331,   508,   509,    16,   712,   451,   266,   715,    18,    68,
      74,    16,   124,   690,   691,    16,    36,    76,    77,    78,
      79,   571,   534,    82,     0,    18,    85,     0,    68,    88,
      45,   332,    62,    23,   335,    23,    18,    36,    14,    13,
      16,    14,   133,    16,    74,    16,   137,    14,   349,   133,
      18,    44,   136,   137,     3,     4,     5,     6,     7,     8,
       9,    10,   121,    76,   365,   149,   150,   151,   152,   153,
      44,    76,    21,   164,   133,    76,   160,    68,   137,   124,
     164,   121,   166,   142,   168,   169,   170,    16,   147,    16,
      18,    62,    68,   334,   133,    68,     0,   137,    74,    18,
     164,    74,   142,   124,   124,    76,   124,    69,     0,   555,
     124,   124,   662,   172,   173,   174,   126,   176,   177,   124,
     179,    70,    14,   124,    16,   124,    16,    16,   187,   188,
     189,   190,    99,    18,   124,    20,   124,    22,   197,   198,
     199,   200,    16,   227,   126,   229,   137,   231,   207,   208,
     209,   210,   333,   124,   661,   336,    13,    44,   126,    44,
     341,   137,   124,    16,   137,   249,    18,   692,   252,   846,
      16,   848,    62,    62,    62,   124,    68,    16,   359,   319,
     320,   362,    74,    40,    10,    74,    76,    76,   164,    14,
      11,   164,    44,    18,    14,   124,    17,   124,   126,    68,
      26,   292,   328,   504,   464,    61,   713,   126,   292,   716,
     470,    62,   465,   466,   467,   468,   524,    62,   465,   466,
     467,   468,   578,   566,   555,   770,   771,   772,   778,    16,
      17,    14,    13,   292,   124,   124,   124,   328,   149,   150,
     151,   126,   153,   934,   328,   137,    16,   331,   565,   160,
     124,   227,    74,   292,   227,    26,    23,   168,   169,   170,
     124,   133,    76,    44,   133,   446,    22,   136,   137,   328,
     329,   124,   164,   124,   333,   334,   211,   336,   124,   124,
     149,   150,   341,   152,    67,   124,    73,   713,    44,   328,
     716,   124,    62,   333,    14,    11,   336,   166,    11,   168,
     359,   341,   124,   362,    74,    21,    76,    74,   367,   368,
     124,   370,   553,   554,   373,    11,   227,   252,    20,   359,
      22,   828,   362,    22,    11,    21,    13,     0,   387,   388,
     389,   124,   391,   392,    21,   394,   782,   862,   863,    22,
     865,    14,    44,    16,   124,    44,    66,    67,   407,   408,
     409,   124,   411,   412,   124,   414,    18,   124,    14,    22,
     229,    44,   231,   447,   448,   449,   450,   451,   427,   428,
     429,   124,   431,   432,   124,   434,   502,   503,   124,   891,
     249,    44,    44,   895,   830,    47,    48,   446,    20,   124,
      22,   978,    11,   980,    13,    68,   124,   133,    11,   525,
     459,    74,    21,   124,   530,    61,   446,   533,    21,   653,
      66,    67,    44,   239,   240,    11,   542,   543,    11,    11,
     292,    11,    11,   292,   931,    21,   124,    17,    21,    21,
     683,   684,   685,   686,   687,   688,   689,   690,   691,    20,
     693,   694,   695,   696,   697,   698,   699,   700,  1035,    16,
     534,   698,   699,   700,   900,   124,   328,  1017,   775,   328,
    1017,    11,   331,    13,   137,   524,   978,    11,   980,    13,
      11,   555,    13,   750,   565,   566,   657,   658,   659,   660,
      34,   565,   566,    11,    20,   524,   570,    41,    14,    13,
      16,   164,    99,    21,    61,   534,    50,   124,  1005,    66,
      67,    11,   328,    13,   124,  1017,   565,   566,  1095,     3,
       4,     5,     6,     7,     8,     9,    10,   126,    11,   578,
      27,    11,    16,  1035,    13,    14,   565,   566,    21,    20,
     589,    21,  1119,    11,  1121,    61,   447,   448,   449,   450,
      66,    67,    11,    21,    20,   604,   605,    22,   607,  1136,
      20,   610,    21,    11,   227,    13,   292,     3,     4,     5,
       6,     7,     8,     9,    10,   624,   625,   133,   627,   877,
     878,   630,    18,    14,    20,    16,    20,    11,   822,   670,
      11,    75,   451,  1095,    11,   644,   645,    21,   647,    18,
      21,   650,   328,   846,    21,   848,    47,    48,   657,   658,
     659,   660,    11,    11,    11,    11,    18,  1119,    20,  1121,
      22,   670,    21,    21,    21,    21,    11,   657,   658,   659,
     660,    49,    50,    51,  1136,    13,    21,    11,    40,    18,
     124,    20,    44,    22,    13,    47,    48,    21,    11,   465,
     466,   467,   468,   124,   770,   771,   772,    11,    21,    20,
      11,    40,   524,   712,    11,    44,   715,    21,    47,    48,
      21,    13,   534,    11,    21,   534,   750,   975,   877,    11,
      11,    24,    11,    21,    43,  1016,    29,    11,   124,    21,
      21,    43,   935,    19,   775,    11,   555,    21,    35,    36,
      37,   775,    19,   565,   566,    21,   565,   566,   782,   783,
      18,   570,    27,    28,    29,    30,    31,    32,  1016,    21,
    1018,    46,   124,    43,   126,    68,   775,    38,   693,   694,
     695,  1029,  1030,    39,  1032,  1033,   292,    80,    20,    82,
      83,    18,    85,    86,   133,    88,   775,   126,   797,    47,
      48,    47,    48,   124,   835,    20,   830,    13,   807,    52,
      53,    13,  1093,  1094,   880,   881,    33,    34,   817,    61,
      62,    13,   328,    13,  1072,   688,   689,  1075,  1076,    13,
     696,   697,    63,    64,    65,    18,  1117,    68,    69,    70,
      11,    11,    20,    11,   137,  1093,  1094,  1128,   524,  1130,
    1131,    20,  1133,  1134,    43,    19,   149,  1105,   534,  1140,
      19,   124,  1143,  1144,    44,    20,    20,  1016,  1149,  1117,
     124,    21,    21,   104,    19,   124,   900,    20,   877,   878,
    1128,    19,  1130,  1131,    20,  1133,  1134,   124,    40,   565,
     566,    13,  1140,    11,   124,  1143,  1144,    20,   877,   878,
     124,  1149,    19,     3,     4,     5,     6,     7,     8,     9,
      10,    20,   891,    11,    20,   124,   895,   683,   684,   685,
     686,   687,   688,   689,   690,   691,    74,   693,   694,   695,
     696,   697,   698,   699,   700,   934,    15,    11,    18,    40,
      21,   750,    20,    19,  1093,  1094,    13,    27,    28,    29,
      30,    31,    32,   292,    27,    28,    29,    30,    31,    32,
      20,   133,    20,   775,    44,    13,   775,    20,  1117,    13,
      13,    20,    85,   782,   783,    75,   975,   124,    20,  1128,
      20,  1130,  1131,    20,  1133,  1134,    20,   124,    85,   328,
      20,  1140,   124,  1017,  1143,  1144,   975,    21,    13,   978,
    1149,   980,     3,     4,     5,     6,     7,     8,     9,    10,
      13,    13,    20,    20,    20,    16,    13,  1016,   524,  1018,
      13,   830,    20,    13,   124,    21,    21,    13,   534,    13,
    1029,  1030,    13,  1032,  1033,    13,    21,  1016,  1017,  1018,
      27,    28,    29,    30,    31,    32,   239,   240,    21,    40,
    1029,  1030,    13,  1032,  1033,    21,  1035,    13,    13,   565,
     566,    13,    63,    64,    65,   877,   878,    68,    69,    70,
      13,    13,    13,  1072,    75,    13,  1075,  1076,    13,   891,
     846,    13,   848,   895,    13,    85,    13,    21,    21,   252,
      21,   900,   164,  1072,  1093,  1094,  1075,  1076,    21,   775,
      21,   213,   137,   104,   457,   328,  1105,   511,   133,   509,
     877,   935,   683,   686,  1093,  1094,  1095,   685,  1117,   684,
     292,   687,   767,   124,   783,  1017,  1105,   149,   227,  1128,
     865,  1130,  1131,    -1,  1133,  1134,    -1,   136,  1117,    -1,
    1119,  1140,  1121,    -1,  1143,  1144,    -1,    -1,    -1,  1128,
    1149,  1130,  1131,    -1,  1133,  1134,   328,  1136,    -1,    -1,
      -1,  1140,    -1,   975,  1143,  1144,   978,    -1,   980,   935,
    1149,    -1,    -1,    -1,    63,    64,    65,    29,    -1,    68,
      69,    70,    -1,    -1,    -1,   524,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,   534,    -1,    -1,    -1,    -1,
      89,   877,   878,    92,  1016,  1017,  1018,    -1,  1017,    -1,
      -1,    63,    -1,    -1,    -1,   891,    -1,  1029,  1030,   895,
    1032,  1033,    -1,  1035,    76,    -1,   565,   566,    80,    -1,
      82,    83,    -1,    85,    86,    -1,    88,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,  1016,
      -1,    -1,    -1,   133,    -1,    -1,    -1,    21,    -1,    75,
    1072,    -1,    -1,  1075,  1076,    -1,    -1,   292,    -1,   775,
      -1,    -1,   465,   466,   467,   468,    -1,    -1,    -1,    -1,
      -1,  1093,  1094,  1095,    63,    64,    65,    -1,    -1,    68,
      69,    70,    -1,  1105,    -1,    -1,    -1,    -1,    -1,   975,
      -1,    -1,   978,   328,   980,  1117,    70,  1119,   124,  1121,
      89,    -1,    -1,    92,    -1,    -1,  1128,    -1,  1130,  1131,
      -1,  1133,  1134,    -1,  1136,   104,  1093,  1094,  1140,   181,
      -1,  1143,  1144,    -1,    -1,   187,    -1,  1149,    -1,   191,
    1016,  1017,  1018,    -1,    -1,   197,    -1,    -1,    -1,   201,
    1117,    -1,   524,  1029,  1030,   207,  1032,  1033,    -1,  1035,
     124,  1128,   534,  1130,  1131,    -1,  1133,  1134,    -1,    -1,
      -1,   877,   878,  1140,    -1,    -1,  1143,  1144,    -1,    -1,
      -1,    -1,  1149,    -1,    -1,   891,    -1,    -1,    -1,   895,
      -1,    -1,    -1,   565,   566,    -1,  1072,    -1,    -1,  1075,
    1076,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,   292,    -1,    -1,    -1,    -1,  1093,  1094,  1095,
      -1,    -1,    21,    -1,    -1,    63,    64,    65,    -1,  1105,
      68,    69,    70,    63,    64,    65,   775,    -1,    68,    69,
      70,  1117,    -1,  1119,    -1,  1121,    -1,    -1,   328,    -1,
      -1,    -1,  1128,    -1,  1130,  1131,    -1,  1133,  1134,    89,
    1136,    -1,    92,    -1,  1140,    -1,    -1,  1143,  1144,   975,
      -1,    70,   978,  1149,   980,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
     683,   684,   685,   686,   687,   688,   689,   690,   691,   524,
     693,   694,   695,   696,   697,   698,   699,   700,    -1,   534,
    1016,  1017,  1018,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,  1029,  1030,   124,  1032,  1033,    -1,  1035,
       3,     4,     5,     6,     7,     8,     9,    10,   877,   878,
     565,   566,    18,    16,    20,    -1,    22,    -1,    -1,    -1,
      -1,    -1,   891,    79,    -1,    -1,   895,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,  1072,    -1,    44,  1075,
    1076,    47,    48,    -1,    -1,    64,    65,    -1,    -1,    68,
      69,    70,    71,    72,    -1,    -1,    -1,  1093,  1094,  1095,
      63,    64,    65,    -1,    -1,    68,    69,    70,   124,  1105,
      -1,    -1,    75,   775,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1117,    -1,  1119,    -1,  1121,    89,    90,    91,    92,
      -1,    -1,  1128,    -1,  1130,  1131,    -1,  1133,  1134,    -1,
    1136,    -1,    -1,    -1,  1140,   124,   975,  1143,  1144,   978,
      -1,   980,    -1,  1149,   524,    -1,    -1,    -1,   124,    -1,
     126,   124,    -1,   846,   534,   848,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,  1016,  1017,  1018,
      -1,    -1,    -1,    -1,    -1,   565,   566,    -1,    -1,    -1,
    1029,  1030,    -1,  1032,  1033,    -1,  1035,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,   877,   878,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   891,
      -1,    -1,    -1,   895,    -1,    70,    -1,    -1,    -1,    74,
      75,    76,    -1,  1072,    79,    -1,  1075,  1076,    -1,    -1,
      -1,    -1,   935,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     775,    -1,    -1,    -1,  1093,  1094,  1095,    63,    64,    65,
      -1,    -1,    68,    69,    70,    -1,  1105,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,  1117,   124,
    1119,    -1,  1121,    89,    20,    -1,    92,    -1,    -1,  1128,
      -1,  1130,  1131,    -1,  1133,  1134,    -1,  1136,   104,    -1,
      -1,  1140,    -1,   975,  1143,  1144,   978,    -1,   980,    -1,
    1149,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    79,  1016,  1017,  1018,    -1,    -1,    -1,
      -1,    -1,   877,   878,    -1,    -1,    -1,  1029,  1030,    -1,
    1032,  1033,    -1,  1035,    -1,    -1,   891,    -1,    -1,    -1,
     895,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,   124,    -1,
      -1,    -1,    -1,    -1,    -1,   775,    25,    -1,    -1,    -1,
    1072,    -1,    -1,  1075,  1076,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1093,  1094,  1095,    21,     3,     4,     5,     6,     7,
       8,     9,    10,  1105,    63,    64,    65,    -1,    -1,    68,
      69,    70,    20,    -1,    -1,  1117,    75,  1119,    -1,  1121,
     975,    -1,    -1,   978,    -1,   980,  1128,    -1,  1130,  1131,
      89,  1133,  1134,    92,  1136,    -1,    -1,    -1,  1140,    -1,
      -1,  1143,  1144,    70,    -1,   104,    -1,  1149,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,  1016,  1017,  1018,    -1,   124,    21,   877,   878,    -1,
      -1,    -1,    -1,    -1,  1029,  1030,    -1,  1032,  1033,    -1,
    1035,   891,    -1,    -1,    -1,   895,    -1,    -1,    -1,    -1,
      -1,    -1,   238,    -1,    -1,    -1,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   253,   254,    -1,
      -1,    -1,   258,   259,    -1,    70,   124,  1072,    -1,    -1,
    1075,  1076,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,  1093,  1094,
    1095,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,
    1105,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,  1117,    -1,  1119,   975,  1121,    -1,   978,   124,
     980,    -1,    21,  1128,    -1,  1130,  1131,    -1,  1133,  1134,
      -1,  1136,    -1,    -1,    -1,  1140,    -1,    -1,  1143,  1144,
      63,    64,    65,    -1,  1149,    68,    69,    70,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,  1016,  1017,  1018,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1029,
    1030,    70,  1032,  1033,    -1,  1035,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    -1,    15,    16,
      -1,   124,    -1,    -1,    -1,    60,    61,    -1,    25,    -1,
      -1,    -1,  1072,    68,    -1,  1075,  1076,    -1,    -1,    74,
      -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1093,  1094,  1095,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,  1105,    63,    64,    65,    16,
      -1,    68,    69,    70,    -1,    -1,    -1,  1117,    75,  1119,
      -1,  1121,    -1,   459,    -1,    -1,    -1,    -1,  1128,    -1,
    1130,  1131,    89,  1133,  1134,    92,  1136,    94,   133,    -1,
    1140,   136,   137,  1143,  1144,    -1,    -1,    -1,    -1,  1149,
      -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,   124,
      63,    64,    65,    66,    -1,   160,    -1,   124,    -1,   164,
      -1,   166,    -1,   168,   169,   170,    -1,    -1,    81,    -1,
      -1,    84,    -1,    -1,    87,   521,   522,   523,     3,     4,
       5,     6,     7,     8,     9,    10,   532,   100,   101,   102,
      -1,   104,   105,    -1,   107,   541,    -1,    -1,   544,    -1,
      -1,    -1,    -1,    -1,    -1,    29,   211,   124,    -1,    -1,
     215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   227,    -1,   229,    -1,   231,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    -1,    -1,    -1,   249,    70,    -1,   252,    -1,    -1,
      -1,    -1,    76,    77,    -1,    -1,    80,    -1,    82,    83,
      -1,    85,    86,    -1,    88,    -1,    -1,    -1,   181,   182,
     183,   184,    -1,    -1,    -1,    -1,   100,    -1,   191,   192,
     193,   194,    -1,    -1,    -1,    -1,    -1,   292,   201,   202,
     203,   204,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,    -1,   217,   218,    -1,   220,    -1,    -1,
     223,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   327,   328,   670,    -1,   331,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,   682,    -1,    -1,    -1,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   181,   182,    -1,
      -1,    -1,    -1,   187,   188,   711,    -1,   191,   192,    -1,
      -1,    -1,    -1,   197,   198,    13,   722,   201,   202,    -1,
      -1,    -1,    -1,   207,   208,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    70,    71,    72,    -1,    -1,    75,
      -1,    -1,    -1,   749,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,   104,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   447,   448,   449,   450,   451,    -1,   124,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,   376,   377,   378,   104,   380,   381,    -1,
     383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   396,   397,   398,    -1,   400,   401,   127,
     403,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   506,    -1,   416,   417,   418,    -1,   420,   421,    -1,
     423,    76,    77,    78,    79,    -1,    -1,    82,    -1,    -1,
      85,    -1,    -1,    88,    -1,    13,    -1,    -1,   441,   534,
      -1,    -1,    18,    -1,    20,    -1,    22,    -1,    -1,    -1,
     886,    27,    28,    29,    30,    31,    32,   893,   894,    -1,
     555,    -1,   376,    -1,    -1,    -1,    -1,    -1,    44,    -1,
     565,   566,    -1,   387,    -1,   570,    -1,    -1,    -1,    -1,
      -1,    -1,   396,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    70,   407,    -1,    -1,    -1,    -1,   934,    -1,
      -1,    -1,   416,     3,     4,     5,     6,     7,     8,     9,
      10,    89,    -1,   427,    92,    -1,    16,   172,   173,   174,
      98,   176,   177,    -1,   179,   717,   104,    -1,    -1,    -1,
      -1,    -1,   187,   188,   189,   190,    -1,    -1,    -1,    -1,
      -1,    -1,   197,   198,   199,   200,    -1,    -1,   124,   127,
     126,    -1,   207,   208,   209,   210,    -1,    -1,   653,    -1,
      -1,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    -1,    -1,    -1,    75,   768,   769,  1014,  1015,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    89,
     593,   594,    92,   596,    16,    -1,   599,   692,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,    -1,    -1,
     613,   614,    -1,   616,    -1,    -1,   619,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,  1061,    -1,    -1,    -1,    -1,
     633,   634,    -1,   636,    -1,    -1,   639,    -1,    -1,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    -1,    75,    -1,   750,    -1,    -1,    -1,    -1,
      -1,  1097,  1098,    -1,    -1,    -1,    -1,    89,   860,    -1,
      92,    -1,   767,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     775,    -1,    -1,   875,    -1,    -1,    -1,   782,   783,    -1,
     882,    -1,    -1,    -1,    -1,    -1,    -1,   889,    -1,    -1,
      -1,    -1,   124,    -1,    -1,   897,    -1,    -1,    -1,    -1,
      -1,    -1,   367,   368,    -1,   370,    -1,    -1,   373,    -1,
      -1,    -1,   914,   915,    -1,    -1,    -1,   822,    -1,    -1,
      -1,    -1,   387,   388,   389,   830,   391,   392,    -1,   394,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   940,    -1,
      -1,    -1,   407,   408,   409,    -1,   411,   412,    -1,   414,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   862,   863,    -1,
     865,    -1,   427,   428,   429,    -1,   431,   432,   970,   434,
      -1,    -1,   974,    -1,    -1,    -1,    -1,    -1,   791,    -1,
      -1,    -1,    -1,   985,    -1,    -1,    -1,    -1,   801,    -1,
     992,    -1,   994,    -1,   996,   900,    -1,    -1,   811,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    14,    15,    -1,    -1,    -1,  1020,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    29,    -1,    -1,    -1,    -1,    -1,
      41,    42,  1044,    -1,    -1,  1047,    47,    48,  1050,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     873,    62,    -1,    -1,    -1,  1067,    -1,    -1,    63,    64,
      65,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    -1,    80,    -1,    82,    83,    -1,
      85,    86,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,   101,    -1,    -1,   104,
      -1,    -1,  1017,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,   589,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   946,   947,    -1,    -1,    -1,    -1,   604,
     605,    -1,   607,    -1,    -1,   610,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   624,
     625,    -1,   627,    -1,    -1,   630,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   644,
     645,   176,   647,    -1,    -1,   650,   181,   182,   183,    -1,
      -1,    -1,   187,   188,   189,    -1,   191,   192,   193,    -1,
    1013,    -1,   197,   198,   199,    -1,   201,   202,   203,    -1,
      -1,    -1,   207,   208,   209,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   217,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    63,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    86,    87,    88,    89,
      64,    65,    92,    -1,    68,    69,    70,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   797,    -1,    -1,    89,    90,    91,    92,    -1,
      -1,    -1,   807,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   817,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
     124,    -1,   367,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,   376,   377,    -1,    -1,   380,    -1,    -1,    -1,    -1,
      -1,    -1,   387,   388,    -1,    -1,   391,    -1,    -1,    -1,
      -1,   396,   397,    -1,    -1,   400,    -1,    -1,    -1,    -1,
      -1,    -1,   407,   408,    -1,    -1,   411,    -1,    -1,    -1,
      -1,   416,   417,    64,    65,   420,    -1,    68,    69,    70,
      -1,    -1,   427,   428,    75,    -1,   431,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    14,    15,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,   124,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    63,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    -1,    -1,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      86,    87,    88,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    -1,    -1,    -1,    -1,   593,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,   604,
      80,    81,    82,    83,    84,    -1,    86,    87,   613,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,   624,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,   633,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   644,
      -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    -1,    80,    81,    82,
      83,    84,    -1,    86,    87,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,   124,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    74,    75,    76,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    33,    34,
      -1,    -1,    16,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   124,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    33,    34,
      -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    89,    90,    91,    92,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
     124,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    33,    34,    -1,    16,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   124,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    64,    65,    -1,    27,    68,    69,    70,    -1,
      -1,    33,    34,    75,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    89,    -1,    -1,
      92,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,   124,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    20,   124,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,   124,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,   124,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    33,    34,    -1,
      -1,    16,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,   124,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    74,    75,
      76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    64,
      65,    -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,
      75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    89,    -1,    -1,    92,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,   124,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,   124,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   124,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,   124,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   124,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,   124,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   124,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,   124,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,   124,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   124,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,   124,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   124,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,   124,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,   124,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
     124,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     124,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,   124,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,   124,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,   124,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   124,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   124,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    74,    75,    76,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,   124,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,   124,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    74,    75,    76,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,   124,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,   124,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,   124,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   124,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    74,    75,    76,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,    20,    21,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    74,    75,    76,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,    -1,    20,    21,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    74,    75,    76,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    20,
      21,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
     124,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      74,    75,    76,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    63,    64,    65,    -1,
      -1,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,
      -1,    -1,    -1,   124
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,    13,    63,    64,    65,    68,    69,    70,    89,    92,
      98,   104,   127,   129,   142,   143,   144,   145,   146,   148,
     155,   271,   272,   273,   124,   147,    69,   124,   141,   124,
       0,   127,   143,   143,    63,    64,    65,    68,    69,    70,
     104,    63,    64,    65,    68,    69,    70,    89,    92,   104,
      63,    64,    65,    68,    69,    70,    89,    92,   104,    16,
      61,    66,    67,   156,   161,   162,   164,    14,   150,   166,
     141,    44,    13,    44,   150,   152,   156,   161,   162,   164,
     124,   147,   124,   124,   147,   124,   124,   147,   124,   124,
     157,   158,   124,   137,   138,   137,   163,   281,   124,   165,
     161,   162,   164,   166,   162,   164,   166,   164,   166,   166,
       3,     4,     5,     6,     7,     8,     9,    10,    13,    15,
      25,    69,    75,   124,   130,   131,   132,   133,   134,   135,
     136,   137,   145,   150,   151,   155,   156,   167,   168,   169,
     170,   218,   219,   229,   230,   231,   266,   267,   268,   271,
     272,   273,   274,   275,    13,    44,   124,    36,   124,    13,
      94,   130,   145,   151,   153,   154,   156,   218,   271,   272,
     273,   152,   161,   162,   164,   152,   162,   164,   152,   164,
     152,   156,   161,   162,   164,   166,   152,   156,   161,   162,
     164,   156,   161,   162,   164,   166,   152,   156,   161,   162,
     164,   156,   161,   162,   164,   166,   152,   156,   161,   162,
     164,    61,   159,    11,    17,    11,    11,   162,   164,   166,
     164,   166,   166,   164,   166,   166,   166,    26,   231,   124,
     223,   124,   171,   172,   173,   223,     3,    13,    20,    47,
      48,    54,    55,    56,    57,    58,    59,    60,    62,    70,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    86,    87,    88,   124,   130,   132,   137,   140,   141,
     145,   149,   151,   177,   178,   180,   181,   182,   183,   184,
     186,   187,   190,   191,   192,   198,   211,   212,   214,   215,
     216,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   257,   258,   259,   261,   271,   272,   273,    75,
     130,   268,   151,   168,    13,   228,   231,    99,   150,   220,
     269,    20,   130,   219,   267,   130,   219,    71,    72,    90,
      91,   219,    64,    65,    68,    69,    70,    71,    72,   130,
      64,    65,    68,    69,    70,    89,    90,    91,    92,   219,
      36,    13,   219,   151,   154,   130,   152,   162,   164,   152,
     164,   152,   152,   164,   152,   152,   161,   162,   164,   166,
     162,   164,   166,   164,   166,   166,   152,   161,   162,   164,
     152,   162,   164,   152,   164,   152,   161,   162,   164,   166,
     162,   164,   166,   164,   166,   166,   152,   161,   162,   164,
     152,   162,   164,   152,   164,   152,   161,   162,   164,   166,
     162,   164,   166,   164,   166,   166,   152,   161,   162,   164,
     152,   162,   164,   152,   164,   152,   124,   136,   158,   281,
     124,   164,   166,   166,   166,   166,   219,   271,   272,   273,
     275,    20,   130,   224,   220,    18,   139,    11,    13,    27,
     220,    18,   126,   185,     3,    33,    34,    41,    42,   124,
     132,   137,   175,   176,   177,   186,   190,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   124,   141,   180,   198,
     210,   210,    22,    44,   237,   126,    16,   124,   131,   136,
     188,   276,   175,   175,    13,   124,    13,   124,    13,   175,
     175,    20,    20,    18,    40,    44,   126,   185,   126,   185,
      22,    20,    18,    44,    20,    27,    28,    29,    30,    31,
      32,   179,    22,    44,    18,    47,    48,   151,   233,    13,
     124,   171,    13,   223,   223,    20,   137,   221,   222,    62,
      74,   124,   141,   151,   181,   232,   270,   276,   269,    21,
      70,   130,   224,   225,   226,   227,   171,   228,   220,   269,
     171,   228,   228,   171,   228,    13,   228,   171,   152,   164,
     152,   152,   152,   162,   164,   166,   164,   166,   166,   164,
     166,   166,   166,   152,   162,   164,   152,   164,   152,   152,
     164,   152,   152,   162,   164,   166,   164,   166,   166,   164,
     166,   166,   166,   152,   162,   164,   152,   164,   152,   152,
     164,   152,   152,   162,   164,   166,   164,   166,   166,   164,
     166,   166,   166,   152,   162,   164,   152,   164,   152,   152,
     164,   152,   152,    43,   160,   166,   228,   219,   219,   219,
     219,    21,   130,   225,    74,   124,    11,    19,    18,   172,
     150,   174,   175,   193,    19,    18,   126,   210,   210,   210,
     210,    21,    12,    45,    46,    38,    39,    43,    52,    53,
      16,    17,    73,    49,    50,    51,    33,    34,    35,    36,
      37,   124,   276,   124,   276,   171,    12,   135,   277,   278,
     279,    18,   139,   195,   196,   139,   195,    20,   124,   188,
      13,    13,    40,    13,    13,    13,    13,   175,   175,   175,
     238,    62,    74,    76,   124,   187,   276,   126,   126,    76,
     124,   276,    21,   175,   189,   175,   124,   187,   276,    13,
      70,   236,   242,   263,   265,   175,   124,   276,   124,   187,
     276,   175,   220,   220,    21,   224,   225,    11,    20,    20,
      44,    44,    44,   151,   151,   232,    62,    74,   130,    23,
     124,   173,    11,    11,    21,    13,   269,    13,    13,    13,
     152,   164,   166,   166,   166,   166,   152,   164,   152,   152,
     152,   164,   166,   166,   166,   166,   152,   164,   152,   152,
     152,   164,   166,   166,   166,   166,   152,   164,   152,   152,
     152,   281,    43,   228,   228,   228,   228,   139,    21,    44,
      20,    19,    11,   151,   174,   194,   197,    19,   175,   201,
     202,   203,   204,   205,   206,   206,    27,   207,    27,   207,
     135,   208,   208,   208,   209,   209,   210,   210,   210,   124,
      20,   124,    61,    62,   280,    11,    17,   175,   193,   139,
     196,   193,   139,    21,   189,    20,   175,    21,    21,    19,
      22,    44,    20,   124,    76,   124,    11,    21,    19,    20,
     124,    13,   175,    40,    13,    11,   124,    20,   124,    19,
      11,    21,   222,    21,   189,    21,   189,    62,   276,    62,
     276,    62,   276,   151,    20,    20,    23,   173,   124,    21,
     225,   226,   166,   152,   166,   152,   166,   152,   281,   139,
      74,    21,   225,   151,    11,    40,   207,   207,    21,   189,
      20,   135,   135,   278,    19,   166,    21,    21,   189,    13,
      84,    86,   124,   149,   238,   239,   252,   253,   254,   255,
     256,   260,   262,   238,   124,   276,   124,   276,    21,   189,
      20,   175,    21,   189,    20,    21,   264,   265,    13,   175,
      13,   175,   242,    21,   189,    20,    21,   225,    13,    21,
      13,    21,    20,    62,    20,    62,    20,    62,    21,   189,
      21,   189,   124,    21,   139,    21,   174,   199,    21,    21,
     189,   166,   166,    21,    20,    20,    40,    20,    85,   124,
      20,   124,    21,    21,   189,    21,    21,   189,   238,    21,
      21,   264,    21,    21,   264,    13,    21,    21,   189,    21,
      13,    13,    21,   189,    20,    21,   189,    20,    21,   189,
      20,    13,    21,    13,    21,   139,    21,   166,   175,   175,
     253,    13,   236,   263,   238,    21,   189,    20,    21,    21,
     238,   238,    21,   238,   238,    21,    21,   264,    21,    13,
      21,    21,   189,    13,    21,    21,   189,    13,    21,    21,
     189,    13,    13,    21,    21,    13,   175,    40,    13,    21,
      21,   189,   238,   238,   238,    21,    13,    13,    21,    13,
      13,    21,    13,    13,    21,   253,   253,    21,   264,    13,
     175,    13,   175,    21,   238,    13,    13,    13,    85,   253,
      21,    21,   264,    21,    21,   264,    13,   253,   253,   253,
      21,   253,   253,    21,    21,   264,   253,   253,   253,    21,
     253
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   128,   129,   129,   130,   130,   131,   131,   132,   132,
     133,   133,   133,   133,   133,   134,   134,   135,   136,   137,
     138,   139,   139,   140,   141,   141,   142,   142,   143,   143,
     143,   143,   144,   144,   144,   144,   145,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   147,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   149,   150,   151,   152,
     152,   153,   153,   154,   154,   154,   154,   154,   155,   156,
     157,   157,   158,   158,   159,   159,   160,   160,   161,   162,
     163,   163,   164,   165,   165,   166,   166,   167,   167,   168,
     168,   168,   168,   169,   169,   169,   169,   169,   170,   170,
     170,   170,   171,   171,   172,   172,   173,   173,   174,   174,
     175,   176,   176,   177,   178,   178,   178,   178,   179,   179,
     179,   179,   179,   179,   180,   180,   180,   181,   181,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   183,
     183,   183,   183,   183,   183,   183,   184,   184,   184,   184,
     184,   184,   184,   185,   185,   186,   186,   186,   186,   187,
     187,   187,   187,   187,   187,   187,   187,   188,   189,   189,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   193,   193,   194,   194,   194,   195,   195,   196,
     197,   197,   198,   198,   198,   199,   199,   200,   200,   201,
     201,   202,   202,   203,   203,   204,   204,   205,   205,   205,
     206,   206,   206,   206,   206,   206,   207,   207,   207,   207,
     208,   208,   208,   209,   209,   209,   209,   210,   210,   210,
     210,   210,   211,   212,   213,   213,   213,   214,   214,   214,
     214,   214,   215,   216,   217,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   219,   219,   219,   219,   219,
     219,   219,   219,   220,   221,   221,   222,   223,   223,   223,
     223,   223,   223,   223,   223,   224,   224,   225,   225,   226,
     226,   226,   227,   227,   228,   228,   229,   230,   231,   231,
     232,   232,   233,   233,   233,   233,   234,   235,   236,   236,
     237,   237,   238,   238,   238,   238,   238,   238,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   240,   241,   242,
     242,   242,   242,   242,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   248,   249,   250,   251,   252,
     253,   253,   253,   253,   253,   254,   255,   256,   256,   257,
     258,   258,   259,   259,   259,   259,   259,   259,   259,   259,
     260,   260,   260,   260,   260,   260,   260,   260,   261,   262,
     263,   263,   264,   265,   265,   266,   266,   266,   266,   267,
     267,   267,   267,   267,   267,   267,   267,   268,   269,   269,
     269,   269,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   271,   271,   271,   271,   271,   271,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   276,   277,
     277,   278,   278,   279,   279,   280,   280,   281
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     1,     3,     3,     1,     2,     1,     1,
       2,     1,     3,     5,     4,     6,     1,     3,     4,     4,
       4,     7,     6,     6,     5,     6,     5,     5,     4,     6,
       5,     5,     4,     5,     4,     4,     8,     7,     7,     6,
       7,     6,     6,     5,     7,     6,     6,     5,     6,     5,
       5,     8,     7,     7,     6,     7,     6,     6,     5,     7,
       6,     6,     5,     6,     5,     5,     8,     7,     7,     6,
       7,     6,     6,     5,     7,     6,     6,     5,     6,     5,
       5,     1,     7,     6,     6,     5,     6,     5,     5,     4,
       6,     5,     5,     4,     5,     4,     4,     3,     8,     7,
       7,     6,     7,     6,     6,     5,     7,     6,     6,     5,
       6,     5,     5,     4,     8,     7,     7,     6,     7,     6,
       6,     5,     7,     6,     6,     5,     6,     5,     5,     4,
       8,     7,     7,     6,     7,     6,     6,     5,     7,     6,
       6,     5,     6,     5,     5,     4,     1,     1,     1,     2,
       3,     1,     2,     1,     3,     4,     1,     1,     1,     3,
       1,     3,     2,     1,     2,     3,     2,     3,     2,     2,
       1,     3,     2,     1,     3,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     3,     1,     3,     3,     1,     1,     2,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     5,     1,     1,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     3,     3,     2,     3,     1,     3,     3,     3,     4,
       5,     5,     6,     5,     6,     6,     7,     1,     1,     3,
       3,     4,     5,     6,     6,     7,     5,     6,     6,     7,
       5,     6,     6,     7,     5,     6,     6,     7,     7,     8,
       8,     9,     4,     4,     4,     6,     4,     3,     3,     3,
       5,     3,     4,     4,     4,     4,     3,     3,     3,     3,
       2,     2,     3,     2,     1,     1,     2,     1,     2,     3,
       1,     3,     4,     4,     4,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     4,     4,     1,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     2,     2,     3,     2,     3,     3,     3,     3,
       4,     5,     5,     5,     5,     2,     2,     3,     4,     3,
       3,     4,     3,     2,     1,     3,     1,     3,     4,     5,
       4,     6,     5,     7,     6,     2,     4,     1,     3,     2,
       1,     3,     3,     4,     1,     1,     1,     2,     3,     2,
       1,     2,     1,     1,     1,     1,     1,     2,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     2,     3,
       2,     3,     3,     2,     3,     3,     3,     5,     7,     7,
       1,     1,     1,     1,     1,     3,     5,     1,     1,     5,
       1,     1,     6,     7,     7,     8,     7,     8,     8,     9,
       6,     7,     7,     8,     7,     8,     8,     9,     7,     7,
       1,     1,     1,     1,     3,     3,     2,     4,     3,     3,
       4,     5,     6,     4,     5,     6,     7,     1,     4,     3,
       3,     2,     4,     5,     5,     6,     4,     5,     5,     6,
       6,     7,     7,     8,     6,     7,     7,     8,     6,     7,
       7,     8,     1,     1,     1,     2,     2,     2,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     1,
       3,     1,     1,     1,     2,     2,     2,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* COMPILATIONUNIT: EOFF  */
#line 241 "parser_1st.y"
                              {return 0;}
#line 3437 "parser_1st.tab.c"
    break;

  case 3: /* COMPILATIONUNIT: ORDINARYCOMPILATIONUNIT EOFF  */
#line 242 "parser_1st.y"
                                                     {
                    
                    return 0;
                }
#line 3446 "parser_1st.tab.c"
    break;

  case 4: /* TYPE: PRIMITIVETYPE  */
#line 247 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3452 "parser_1st.tab.c"
    break;

  case 5: /* TYPE: REFERENCETYPE  */
#line 248 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3458 "parser_1st.tab.c"
    break;

  case 6: /* PRIMITIVETYPE: NUMERICTYPE  */
#line 250 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3464 "parser_1st.tab.c"
    break;

  case 7: /* PRIMITIVETYPE: BOOLEAN  */
#line 251 "parser_1st.y"
                             {(yyval.val) = stringtochar("bool");}
#line 3470 "parser_1st.tab.c"
    break;

  case 8: /* NUMERICTYPE: INTEGRALTYPE  */
#line 253 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3476 "parser_1st.tab.c"
    break;

  case 9: /* NUMERICTYPE: FLOATINGTYPE  */
#line 254 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3482 "parser_1st.tab.c"
    break;

  case 10: /* INTEGRALTYPE: BYTE  */
#line 256 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3488 "parser_1st.tab.c"
    break;

  case 11: /* INTEGRALTYPE: SHORT  */
#line 257 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3494 "parser_1st.tab.c"
    break;

  case 12: /* INTEGRALTYPE: INT  */
#line 258 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3500 "parser_1st.tab.c"
    break;

  case 13: /* INTEGRALTYPE: LONG  */
#line 259 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3506 "parser_1st.tab.c"
    break;

  case 14: /* INTEGRALTYPE: CHAR  */
#line 260 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3512 "parser_1st.tab.c"
    break;

  case 15: /* FLOATINGTYPE: FLOAT  */
#line 262 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3518 "parser_1st.tab.c"
    break;

  case 16: /* FLOATINGTYPE: DOUBLE  */
#line 263 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3524 "parser_1st.tab.c"
    break;

  case 17: /* REFERENCETYPE: CLASSORINTERFACETYPE  */
#line 265 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3530 "parser_1st.tab.c"
    break;

  case 18: /* CLASSORINTERFACETYPE: CLASSTYPE  */
#line 267 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3536 "parser_1st.tab.c"
    break;

  case 19: /* CLASSTYPE: CLASSTYPE1  */
#line 269 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3542 "parser_1st.tab.c"
    break;

  case 20: /* CLASSTYPE1: IDENTIFIER  */
#line 271 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val); }
#line 3548 "parser_1st.tab.c"
    break;

  case 21: /* DIMS: OPENSQUARE CLOSESQUARE  */
#line 274 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3554 "parser_1st.tab.c"
    break;

  case 22: /* DIMS: DIMS OPENSQUARE CLOSESQUARE  */
#line 275 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3560 "parser_1st.tab.c"
    break;

  case 23: /* METHODNAME: IDENTIFIER  */
#line 277 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3571 "parser_1st.tab.c"
    break;

  case 24: /* EXPRESSIONNAME: IDENTIFIER DOT IDENTIFIER  */
#line 284 "parser_1st.y"
                                               {    
    /* makise */    /* check whether second identifier an object or a function. */
                                                    (yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    string  name = chartostring((yyvsp[-2].val)), name2 = chartostring((yyvsp[0].val));
                                                    // ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                    // if(get_symbol_table_function(name,name2,"type"))
                                                    objdetails detail = getobjdetails(name,name2);
                                                    if(detail.isfield){
                                                        ds[curr]["var"] = pref[chartostring((yyvsp[-2].val))]+chartostring((yyvsp[0].val));
                                                        ds[curr]["type"] = detail.field.typ.name;
                                                    }else{
                                                        object_error(name,name2,yylineno);
                                                    }
                                                    // ds[curr]["lineno"] = get_symbol_table(name,"lineno");
                                                    /* TODO */
}
#line 3593 "parser_1st.tab.c"
    break;

  case 25: /* EXPRESSIONNAME: EXPRESSIONNAME DOT IDENTIFIER  */
#line 301 "parser_1st.y"
                                                  {/*TODO*/}
#line 3599 "parser_1st.tab.c"
    break;

  case 28: /* TOPLEVELCLASSORINTERFACEDECLARATION: CLASSDECLARATION  */
#line 307 "parser_1st.y"
                                                          {  

    // assert(classfields.find(chartostring($1))==classfields.end());
    // assert(classmethods.find(chartostring($1))==classmethods.end());
    assert(listofclasses.find(chartostring((yyvsp[0].val)))==listofclasses.end());
    listofclasses.insert(chartostring((yyvsp[0].val)));

    // classfields[chartostring($1)]= fields;
    // classmethods[chartostring($1)]= methods;


    for (auto x : fields ){
        // preservedfields[{x.first, chartostring($1)}] = x.second;
        preservedsymboltable[{x.first, -1}].lineno = x.second.lineno;
        preservedsymboltable[{x.first, -1}].typ = x.second.typ;
        preservedsymboltable[{x.first, -1}].token = "identifier - field of" + chartostring((yyvsp[0].val)) ;
        
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
        preservedsymboltable[{x.first, -1}].token = "identifier - method of" + chartostring((yyvsp[0].val)) ;
        
        // preservedfields[{x.first, chartostring($1)}] = x.second;
        // cout<<x.first<<endl;
        // cout<<x.second.rettype.name <<x.second.rettype.dims <<endl;
        // for (auto y : x.second.argtype){
        //     cout<<y.name<<" "<<y.dims<<" ";

        // }
        // cout<<endl;
        
        
        }
     resetclass();}
#line 3647 "parser_1st.tab.c"
    break;

  case 36: /* CLASSDECLARATION: NORMALCLASSDECLARATION  */
#line 359 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);for(auto obj:object_list){
                        string pr = pref[obj.first];
                        vector<string> methods = getallmethods(obj.first,obj.second);
                        // vector<string> methods = {"f"};
                        for(auto method : methods){
                            // code.push_back(method);
                            // cout<<"methods "<<method<<"\n";
                           
                            add_func(code, pr, method_det[obj.second][method].start, method_det[obj.second][method].end);
                        }
                        
                    }object_list.clear();}
#line 3664 "parser_1st.tab.c"
    break;

  case 37: /* NORMALCLASSDECLARATION: CLASS CLASSNAME CLASSBODY  */
#line 373 "parser_1st.y"
                                                       {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));/*TODO begin class */}
#line 3670 "parser_1st.tab.c"
    break;

  case 38: /* NORMALCLASSDECLARATION: SUPER1 CLASS CLASSNAME CLASSBODY  */
#line 374 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val); if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3676 "parser_1st.tab.c"
    break;

  case 39: /* NORMALCLASSDECLARATION: SUPER2 CLASS CLASSNAME CLASSBODY  */
#line 375 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3682 "parser_1st.tab.c"
    break;

  case 40: /* NORMALCLASSDECLARATION: SUPER3 CLASS CLASSNAME CLASSBODY  */
#line 376 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3688 "parser_1st.tab.c"
    break;

  case 101: /* CLASSNAME: IDENTIFIER  */
#line 441 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val); curr_class = chartostring((yyval.val)); }
#line 3694 "parser_1st.tab.c"
    break;

  case 166: /* FOR: FOR1  */
#line 508 "parser_1st.y"
           {newscope();}
#line 3700 "parser_1st.tab.c"
    break;

  case 167: /* OPENCURLY: OPENCURLY1  */
#line 509 "parser_1st.y"
                          {newscope(); }
#line 3706 "parser_1st.tab.c"
    break;

  case 168: /* CLOSECURLY: CLOSECURLY1  */
#line 510 "parser_1st.y"
                          {popscope();}
#line 3712 "parser_1st.tab.c"
    break;

  case 208: /* FIELDDECLARATION: FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 571 "parser_1st.y"
                                                                             {
                                if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);

                    {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    
                                                                    
                                                                    
                    }
                        
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            assert(fields.find(x.first.name) == fields.end());
                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));

                            fields[x.first.name].access = generalmap[(yyvsp[-3].val)].modifiers;
                            /*CHECK TODO*/
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                                                        fields[x.first.name].lineno = yylineno;

                            classfields[curr_class][x.first.name] = fields[x.first.name];

                        }
                    }
#line 3745 "parser_1st.tab.c"
    break;

  case 209: /* FIELDDECLARATION: SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 599 "parser_1st.y"
                                                                    {
                                                    if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);

                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    
                                                                    
                                                                    
                    }
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            assert(fields.find(x.first.name) == fields.end());

                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));
                            fields[x.first.name].access = generalmap[(yyvsp[-3].val)].modifiers;
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                                                        fields[x.first.name].lineno = yylineno;
                                                        classfields[curr_class][x.first.name] = fields[x.first.name];


                        }
                    }
#line 3776 "parser_1st.tab.c"
    break;

  case 210: /* FIELDDECLARATION: SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 625 "parser_1st.y"
                                                                    {
                                                    if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);

                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));

                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($2)));
                                                                    // if((ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($2)))
                                                                    // typ_error();
                                                                    
                                                                    
                    }
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            assert(fields.find(x.first.name) == fields.end());

                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                            fields[x.first.name].access = generalmap[(yyvsp[-3].val)].modifiers;
                                                        fields[x.first.name].lineno = yylineno;
                                                                                    classfields[curr_class][x.first.name] = fields[x.first.name];


                        }
                    }
#line 3809 "parser_1st.tab.c"
    break;

  case 211: /* FIELDDECLARATION: TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 653 "parser_1st.y"
                                                              {
                        if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);


                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    else ds[curr]["start"] = numtostring(code.size());
                                                                    // code.push_back("start="+ds[curr]["start"]);
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($1)));
                                                                    for(auto i:ds2[curr2]["type"]){
                                                                        if(i!=chartostring((yyvsp[-2].val))){
                                                                            typ_error(chartostring((yyvsp[-2].val)),i,int(yylineno));
                                                                        }
                                                                    }
                                                                    
                                                                    
                    }
                        
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            
                            assert(fields.find(x.first.name) == fields.end());

                           fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));
                             reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                                                        fields[x.first.name].lineno = yylineno;
                                                                                    classfields[curr_class][x.first.name] = fields[x.first.name];


                        }
                    }
#line 3851 "parser_1st.tab.c"
    break;

  case 212: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATOR  */
#line 693 "parser_1st.y"
                                               {(yyval.val) = new_temp(); generalmap[(yyval.val)].typ = generalmap[(yyvsp[0].val)].typ; generalmap[(yyval.val)].vlist.push_back({generalmap[(yyvsp[0].val)].vid, generalmap[(yyvsp[0].val)].vinit});
{   
                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                                    if(ds[curr1].find("start")!=ds[curr1].end()){
                                                        ds[curr]["start"] = ds[curr1]["start"];
                                                        ds2[curr]["type"].push_back(ds[curr1]["type"]);
                                                    }
                                                    // ds[curr]["start"] = ds[curr1]["start"];
                                                    // assert(!(ds[curr1].find("type")!=ds[curr1].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"]));
                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
}
}
#line 3868 "parser_1st.tab.c"
    break;

  case 213: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR  */
#line 705 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[-2].val); if(generalmap[(yyvsp[0].val)].typ.name != "" && generalmap[(yyval.val)].typ.name != "" )assert(generalmap[(yyvsp[0].val)].typ.name == generalmap[(yyval.val)].typ.name); else generalmap[(yyval.val)].typ.name = max(generalmap[(yyvsp[0].val)].typ.name, generalmap[(yyval.val)].typ.name );  generalmap[(yyval.val)].vlist.push_back({generalmap[(yyvsp[0].val)].vid, generalmap[(yyvsp[0].val)].vinit});
                        {                           

                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
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
#line 3896 "parser_1st.tab.c"
    break;

  case 214: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER  */
#line 729 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit ;   generalmap[(yyval.val)].typ= generalmap[(yyvsp[0].val)].typ;                                   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));                 
                                                                            if(ds[curr3].find("class")!=ds[curr3].end()){
                                                                                ds[curr]["var"] = ds[curr1]["var"];
                                                                                string cls = ds[curr3]["var"];    // stores the class name after new
                                                                                // cout<<"class "<<cls<<"\n";
                                                                                object_list.push_back({ds[curr]["var"],cls}); // Add object to object list
                                                                                code.push_back(ds[curr]["var"]+" = "+"class ( "+cls+" )");
                                                                                pref[ds[ chartonum((yyval.val))]["var"]] = new_var2();
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
                                                                            generalmap[(yyval.val)].vinit.classname = generalmap[(yyvsp[0].val)].classname;
                                                                            generalmap[(yyval.val)].vinit.isnewclass = generalmap[(yyvsp[0].val)].isnewclass;

                                                                            
                                                                            // code.push_back("start="+ds[curr]["start"]);
                                                                            
                                                                            // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                            // code.push_back("hello");
                                                                            }
#line 3935 "parser_1st.tab.c"
    break;

  case 215: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID  */
#line 763 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];}
#line 3941 "parser_1st.tab.c"
    break;

  case 216: /* VARIABLEDECLARATORID: IDENTIFIER  */
#line 765 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));

}
#line 3954 "parser_1st.tab.c"
    break;

  case 217: /* VARIABLEDECLARATORID: IDENTIFIER DIMS  */
#line 773 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        int curr = chartonum((yyval.val));
                                    ds[curr]["var"] = chartostring((yyvsp[-1].val));
                        /*TODO*/
                        }
#line 3964 "parser_1st.tab.c"
    break;

  case 218: /* VARIABLEINITIALIZER: EXPRESSION  */
#line 780 "parser_1st.y"
                                    {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 3970 "parser_1st.tab.c"
    break;

  case 219: /* VARIABLEINITIALIZER: ARRAYINITIALIZER  */
#line 781 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 3976 "parser_1st.tab.c"
    break;

  case 220: /* EXPRESSION: ASSIGNMENTEXPRESSION  */
#line 783 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 3982 "parser_1st.tab.c"
    break;

  case 221: /* ASSIGNMENTEXPRESSION: CONDITIONALEXPRESSION  */
#line 785 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 3990 "parser_1st.tab.c"
    break;

  case 222: /* ASSIGNMENTEXPRESSION: ASSIGNMENT  */
#line 788 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);/*TODO CHECK multiple assign*/}
#line 3996 "parser_1st.tab.c"
    break;

  case 223: /* ASSIGNMENT: LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  */
#line 790 "parser_1st.y"
                                                           {
    
    // code.pb($1.val + $2.val + $3.val )
    // string t  =new_var();
    // code.pb(t + " = " + $1.val);
    // $$.val = t;
    (yyval.val) = (yyvsp[-2].val);
    int curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val)), curr2 = chartonum((yyvsp[-1].val));
    type_check(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    type_conversion(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    // code.push_back("hello");
    code.push_back(ds[curr1]["var"]+" "+ds[curr2]["op"]+" "+ds[curr3]["var"]);

}
#line 4015 "parser_1st.tab.c"
    break;

  case 224: /* LEFTHANDSIDE: EXPRESSIONNAME  */
#line 805 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 4021 "parser_1st.tab.c"
    break;

  case 225: /* LEFTHANDSIDE: IDENTIFIER  */
#line 806 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
#line 4034 "parser_1st.tab.c"
    break;

  case 226: /* LEFTHANDSIDE: FIELDACCESS  */
#line 814 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4040 "parser_1st.tab.c"
    break;

  case 227: /* LEFTHANDSIDE: ARRAYACCESS  */
#line 815 "parser_1st.y"
                                {   (yyval.val) = (yyvsp[0].val);
                                    ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"[ "+ds[chartonum((yyvsp[0].val))]["var"]+" ]";
                }
#line 4048 "parser_1st.tab.c"
    break;

  case 228: /* ASSIGNMENTOPERATOR: EQUALS  */
#line 819 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 4055 "parser_1st.tab.c"
    break;

  case 229: /* ASSIGNMENTOPERATOR: MULTIPLYEQUALS  */
#line 821 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 4062 "parser_1st.tab.c"
    break;

  case 230: /* ASSIGNMENTOPERATOR: DIVIDEEQUALS  */
#line 823 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 4069 "parser_1st.tab.c"
    break;

  case 231: /* ASSIGNMENTOPERATOR: MODEQUALS  */
#line 825 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 4076 "parser_1st.tab.c"
    break;

  case 232: /* ASSIGNMENTOPERATOR: PLUSEQUALS  */
#line 827 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 4083 "parser_1st.tab.c"
    break;

  case 233: /* ASSIGNMENTOPERATOR: MINUSEQUALS  */
#line 829 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 4090 "parser_1st.tab.c"
    break;

  case 234: /* FIELDACCESS: PRIMARY DOT IDENTIFIER  */
#line 832 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring((yyvsp[0].val));
                                        }else assert(0 && "unexpected type\n");
                                        }
#line 4102 "parser_1st.tab.c"
    break;

  case 237: /* PRIMARY: PRIMARYNONEWARRAY  */
#line 842 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            if(ds[chartonum((yyval.val))].find("array")!=ds[chartonum((yyval.val))].end())
                            ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"["+ds[chartonum((yyvsp[0].val))]["var"]+"]"; }
#line 4110 "parser_1st.tab.c"
    break;

  case 238: /* PRIMARY: ARRAYCREATIONEXPRESSION  */
#line 845 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4116 "parser_1st.tab.c"
    break;

  case 239: /* PRIMARYNONEWARRAY: LITERAL  */
#line 847 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4122 "parser_1st.tab.c"
    break;

  case 240: /* PRIMARYNONEWARRAY: CLASSLITERAL  */
#line 848 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4128 "parser_1st.tab.c"
    break;

  case 241: /* PRIMARYNONEWARRAY: THIS  */
#line 849 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 4137 "parser_1st.tab.c"
    break;

  case 243: /* PRIMARYNONEWARRAY: OPENPARAN EXPRESSION CLOSEPARAN  */
#line 854 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4143 "parser_1st.tab.c"
    break;

  case 244: /* PRIMARYNONEWARRAY: CLASSINSTANCECREATIONEXPRESSION  */
#line 855 "parser_1st.y"
                                                              {(yyval.val) = (yyvsp[0].val); generalmap[(yyval.val)].isnewclass = true;}
#line 4149 "parser_1st.tab.c"
    break;

  case 245: /* PRIMARYNONEWARRAY: FIELDACCESS  */
#line 856 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4155 "parser_1st.tab.c"
    break;

  case 246: /* PRIMARYNONEWARRAY: ARRAYACCESS  */
#line 857 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4161 "parser_1st.tab.c"
    break;

  case 247: /* PRIMARYNONEWARRAY: METHODINVOCATION  */
#line 858 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4167 "parser_1st.tab.c"
    break;

  case 249: /* LITERAL: INTEGERLITERAL  */
#line 861 "parser_1st.y"
                        {(yyval.val) = new_temp();  ds[chartonum((yyval.val))]["type"] = "int"; ds[chartonum((yyval.val))]["var"] = new_var(); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); tempinitval[ds[chartonum((yyval.val))]["var"]]= chartonum((yyvsp[0].val)); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4173 "parser_1st.tab.c"
    break;

  case 250: /* LITERAL: FLOATINGPOINTLITERAL  */
#line 862 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["start"] = numtostring(code.size());ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4179 "parser_1st.tab.c"
    break;

  case 251: /* LITERAL: BOOLEANLITERAL  */
#line 863 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4185 "parser_1st.tab.c"
    break;

  case 252: /* LITERAL: CHARACTERLITERAL  */
#line 864 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4191 "parser_1st.tab.c"
    break;

  case 253: /* LITERAL: STRINGLITERAL  */
#line 865 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4197 "parser_1st.tab.c"
    break;

  case 254: /* LITERAL: TEXTBLOCK  */
#line 866 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4203 "parser_1st.tab.c"
    break;

  case 255: /* LITERAL: NULLLITERAL  */
#line 867 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4209 "parser_1st.tab.c"
    break;

  case 265: /* CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
#line 880 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[0].val);}
#line 4215 "parser_1st.tab.c"
    break;

  case 269: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  */
#line 885 "parser_1st.y"
                                                                                                           {(yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-2].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-2].val))];  }
#line 4221 "parser_1st.tab.c"
    break;

  case 270: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  */
#line 886 "parser_1st.y"
                                                                                                                     {/*TODO*/}
#line 4227 "parser_1st.tab.c"
    break;

  case 271: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 887 "parser_1st.y"
                                                                                                                        {/*TODO*/}
#line 4233 "parser_1st.tab.c"
    break;

  case 272: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY  */
#line 888 "parser_1st.y"
                                                                                                                                  {/*TODO*/}
#line 4239 "parser_1st.tab.c"
    break;

  case 277: /* CLASSORINTERFACETYPETOINSTANTIATE: IDENTIFIER  */
#line 894 "parser_1st.y"
                                                {   (yyval.val) = new_temp(); ds[ chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val)); ds[ chartonum((yyval.val))]["class"] = "true";
                                                     }
#line 4246 "parser_1st.tab.c"
    break;

  case 278: /* ARGUMENTLIST: EXPRESSION  */
#line 897 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            ds2[chartonum((yyval.val))]["type"].push_back(ds[chartonum((yyvsp[0].val))]["type"]);
                            ds2[chartonum((yyval.val))]["var"].push_back(ds[chartonum((yyvsp[0].val))]["var"]);
                            }
#line 4255 "parser_1st.tab.c"
    break;

  case 279: /* ARGUMENTLIST: ARGUMENTLIST COMMA EXPRESSION  */
#line 901 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4268 "parser_1st.tab.c"
    break;

  case 280: /* METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  */
#line 910 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
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
#line 4285 "parser_1st.tab.c"
    break;

  case 281: /* METHODINVOCATION: METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 922 "parser_1st.y"
                                                                    {   (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
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
#line 4309 "parser_1st.tab.c"
    break;

  case 282: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 941 "parser_1st.y"
                                                                        {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val));
                                                        string name = chartostring((yyvsp[-4].val)), name2 = chartostring((yyvsp[-2].val));
                                                        objdetails detail = getobjdetails(name,name2);
                                                        string fname = "";
                                                        if(detail.ismethod&&not_static_check(detail.method.access)){
                                                            fname = pref[chartostring((yyvsp[-4].val))]+chartostring((yyvsp[-2].val));
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
#line 4338 "parser_1st.tab.c"
    break;

  case 283: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 965 "parser_1st.y"
                                                                                    {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr5 = chartonum((yyvsp[-1].val));
                                                        string name = chartostring((yyvsp[-5].val)), name2 = chartostring((yyvsp[-3].val));
                                                        objdetails detail = getobjdetails(name,name2);
                                                        string fname = "";
                                                        if(detail.ismethod&&not_static_check(detail.method.access)){
                                                            fname = pref[chartostring((yyvsp[-5].val))]+chartostring((yyvsp[-3].val));
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
                                                        for(auto i:ds2[curr5]["var"])
                                                        code.push_back("push param "+i);
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
}
#line 4370 "parser_1st.tab.c"
    break;

  case 312: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS  */
#line 1024 "parser_1st.y"
                                                         {/*NOT SUPPORTED*/}
#line 4376 "parser_1st.tab.c"
    break;

  case 313: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS DIMS  */
#line 1025 "parser_1st.y"
                                                                       {/*NOT SUPPORTED*/}
#line 4382 "parser_1st.tab.c"
    break;

  case 314: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER  */
#line 1026 "parser_1st.y"
                                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-2].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; assert (generalmap[(yyvsp[0].val)].vinit.dims.size() == temp[(yyvsp[-1].val)]); }
#line 4388 "parser_1st.tab.c"
    break;

  case 315: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER  */
#line 1027 "parser_1st.y"
                                                                               {/*NOT SUPPORTED*/}
#line 4394 "parser_1st.tab.c"
    break;

  case 316: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS  */
#line 1028 "parser_1st.y"
                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; reverse(all(generalmap[(yyval.val)].vinit.dims)); ds[chartonum((yyval.val))]["arr"] = "true"; ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ ds[chartonum((yyvsp[0].val))]["var"]+" * "+numtostring(gettypesize(chartostring((yyvsp[-1].val))))); ds[chartonum((yyval.val))]["type"] = chartostring((yyvsp[-1].val)); ds[chartonum((yyval.val))]["start"] = ds[chartonum((yyvsp[0].val))]["start"];}
#line 4400 "parser_1st.tab.c"
    break;

  case 317: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS  */
#line 1029 "parser_1st.y"
                                                                   {/*NOT SUPPORTED*/}
#line 4406 "parser_1st.tab.c"
    break;

  case 318: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS  */
#line 1030 "parser_1st.y"
                                                   {/*NOT SUPPORTED*/}
#line 4412 "parser_1st.tab.c"
    break;

  case 319: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS  */
#line 1031 "parser_1st.y"
                                                              {/*NOT SUPPORTED*/}
#line 4418 "parser_1st.tab.c"
    break;

  case 320: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE  */
#line 1032 "parser_1st.y"
                                               {/*TODO whats this*/}
#line 4424 "parser_1st.tab.c"
    break;

  case 321: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE  */
#line 1033 "parser_1st.y"
                                                         {/*TODO whats this*/}
#line 4430 "parser_1st.tab.c"
    break;

  case 322: /* ARRAYINITIALIZER: OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  */
#line 1035 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4436 "parser_1st.tab.c"
    break;

  case 323: /* ARRAYINITIALIZER: OPENCURLY CLOSECURLY  */
#line 1036 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4442 "parser_1st.tab.c"
    break;

  case 324: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST  */
#line 1038 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4448 "parser_1st.tab.c"
    break;

  case 325: /* ARRAYINITIALIZER1: COMMA  */
#line 1039 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=2;}
#line 4454 "parser_1st.tab.c"
    break;

  case 326: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST COMMA  */
#line 1040 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4460 "parser_1st.tab.c"
    break;

  case 327: /* DIMEXPRS: DIMEXPR  */
#line 1042 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[0].val))];}
#line 4466 "parser_1st.tab.c"
    break;

  case 328: /* DIMEXPRS: DIMEXPRS DIMEXPR  */
#line 1043 "parser_1st.y"
                             {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum((yyvsp[-1].val))]["var"]+" *"+ds[chartonum((yyvsp[0].val))]["type"]+" "+ds[ chartonum((yyvsp[0].val))]["var"]);
                              ds[ chartonum((yyval.val))]["var"] = t;  }
#line 4474 "parser_1st.tab.c"
    break;

  case 329: /* DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1047 "parser_1st.y"
                                            {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = varaddrstoint(ds[chartonum((yyvsp[-1].val))]["var"]); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-1].val))];}
#line 4480 "parser_1st.tab.c"
    break;

  case 330: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZER  */
#line 1049 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4486 "parser_1st.tab.c"
    break;

  case 331: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  */
#line 1050 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4492 "parser_1st.tab.c"
    break;

  case 333: /* ARRAYACCESS: PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1057 "parser_1st.y"
                                                                    {
                (yyval.val) = new_temp(); 
                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
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
             
                string exp = dimtoid[-bound];
                code.push_back(t+" = "+ds[curr1]["var"]+" * "+exp);
                code.push_back(ds[curr]["var"]+" = "+t+" + "+ds[curr3]["var"]); 
            }
#line 4517 "parser_1st.tab.c"
    break;

  case 334: /* ARRAYACCESS: IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1077 "parser_1st.y"
                                                                {
                (yyval.val) = new_temp();
                int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                string name = chartostring((yyvsp[-3].val));
                ds[curr]["dims"] = "0";
                ds[curr]["array"] = name;
                ds[curr]["start"] = ds[curr3]["start"];
                ds[curr]["var"] = ds[curr3]["var"];
                ds[curr]["type"] = symboltable[name].typ.name;
                if(ds[curr3]["type"]!="int"&&ds[curr3]["type"]!="long"&&ds[curr3]["type"]!="short"&&ds[curr3]["type"]!="byte")
                cout<<"Array index not integer\n";
                // code.push_back(ds[curr]["var"]+" = "+ds[curr3]["var"]);
            }
#line 4535 "parser_1st.tab.c"
    break;

  case 335: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  */
#line 1091 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4541 "parser_1st.tab.c"
    break;

  case 336: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  */
#line 1092 "parser_1st.y"
                                                                                                    {}
#line 4547 "parser_1st.tab.c"
    break;

  case 337: /* CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  */
#line 1094 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4553 "parser_1st.tab.c"
    break;

  case 338: /* CONDITIONALOREXPRESSION: CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  */
#line 1095 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
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
#line 4571 "parser_1st.tab.c"
    break;

  case 339: /* CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  */
#line 1109 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4577 "parser_1st.tab.c"
    break;

  case 340: /* CONDITIONALANDEXPRESSION: CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  */
#line 1110 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4591 "parser_1st.tab.c"
    break;

  case 341: /* INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  */
#line 1120 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4597 "parser_1st.tab.c"
    break;

  case 342: /* INCLUSIVEOREXPRESSION: INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  */
#line 1121 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4610 "parser_1st.tab.c"
    break;

  case 343: /* EXCLUSIVEOREXPRESSION: ANDEXPRESSION  */
#line 1130 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4616 "parser_1st.tab.c"
    break;

  case 344: /* EXCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  */
#line 1131 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4629 "parser_1st.tab.c"
    break;

  case 345: /* ANDEXPRESSION: EQUALITYEXPRESSION  */
#line 1139 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4635 "parser_1st.tab.c"
    break;

  case 346: /* ANDEXPRESSION: ANDEXPRESSION AND EQUALITYEXPRESSION  */
#line 1140 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4649 "parser_1st.tab.c"
    break;

  case 347: /* EQUALITYEXPRESSION: RELATIONALEXPRESSION  */
#line 1150 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
#line 4662 "parser_1st.tab.c"
    break;

  case 348: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  */
#line 1158 "parser_1st.y"
                                                                                {   (yyval.val) = new_temp();
                                                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
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
#line 4683 "parser_1st.tab.c"
    break;

  case 349: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  */
#line 1174 "parser_1st.y"
                                                                                {   
                                                                                    (yyval.val) = new_temp();
                                                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
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
#line 4705 "parser_1st.tab.c"
    break;

  case 350: /* RELATIONALEXPRESSION: SHIFTEXPRESSION  */
#line 1192 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4715 "parser_1st.tab.c"
    break;

  case 351: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  */
#line 1197 "parser_1st.y"
                                                                            {      // IS backpatching for $1 required?
                                                                                (yyval.val) = new_temp();
                                                                                // code.push_back("REL0 "+ds[chartonum($1)]["start"]);
                                                                                // code.push_back("REL1 "+ds[chartonum($3)]["start"]);
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
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
#line 4738 "parser_1st.tab.c"
    break;

  case 352: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  */
#line 1215 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
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
#line 4757 "parser_1st.tab.c"
    break;

  case 353: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  */
#line 1229 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[0].val));
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
#line 4776 "parser_1st.tab.c"
    break;

  case 354: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  */
#line 1243 "parser_1st.y"
                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[0].val));
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
#line 4795 "parser_1st.tab.c"
    break;

  case 356: /* SHIFTEXPRESSION: ADDITIVEEXPRESSION  */
#line 1259 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4801 "parser_1st.tab.c"
    break;

  case 357: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  */
#line 1260 "parser_1st.y"
                                                                                    {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4815 "parser_1st.tab.c"
    break;

  case 358: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1269 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4828 "parser_1st.tab.c"
    break;

  case 359: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1277 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4841 "parser_1st.tab.c"
    break;

  case 360: /* ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  */
#line 1286 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 4847 "parser_1st.tab.c"
    break;

  case 361: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  */
#line 1287 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4860 "parser_1st.tab.c"
    break;

  case 362: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  */
#line 1295 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4873 "parser_1st.tab.c"
    break;

  case 363: /* MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  */
#line 1304 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4879 "parser_1st.tab.c"
    break;

  case 364: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  */
#line 1305 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4892 "parser_1st.tab.c"
    break;

  case 365: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  */
#line 1313 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4905 "parser_1st.tab.c"
    break;

  case 366: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  */
#line 1321 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4918 "parser_1st.tab.c"
    break;

  case 367: /* UNARYEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1330 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4924 "parser_1st.tab.c"
    break;

  case 368: /* UNARYEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1331 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4930 "parser_1st.tab.c"
    break;

  case 369: /* UNARYEXPRESSION: PLUS UNARYEXPRESSION  */
#line 1332 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 4938 "parser_1st.tab.c"
    break;

  case 370: /* UNARYEXPRESSION: MINUS UNARYEXPRESSION  */
#line 1335 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4951 "parser_1st.tab.c"
    break;

  case 371: /* UNARYEXPRESSION: UNARYEXPRESSIONNOTPLUSMINUS  */
#line 1343 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 4957 "parser_1st.tab.c"
    break;

  case 372: /* PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  */
#line 1345 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
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
#line 4975 "parser_1st.tab.c"
    break;

  case 373: /* PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  */
#line 1359 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
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
#line 4993 "parser_1st.tab.c"
    break;

  case 374: /* UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  */
#line 1373 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4999 "parser_1st.tab.c"
    break;

  case 375: /* UNARYEXPRESSIONNOTPLUSMINUS: COMPLEMENT UNARYEXPRESSION  */
#line 1374 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5012 "parser_1st.tab.c"
    break;

  case 376: /* UNARYEXPRESSIONNOTPLUSMINUS: NOT UNARYEXPRESSION  */
#line 1382 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5025 "parser_1st.tab.c"
    break;

  case 377: /* POSTFIXEXPRESSION: PRIMARY  */
#line 1391 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5031 "parser_1st.tab.c"
    break;

  case 378: /* POSTFIXEXPRESSION: EXPRESSIONNAME  */
#line 1392 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5037 "parser_1st.tab.c"
    break;

  case 379: /* POSTFIXEXPRESSION: IDENTIFIER  */
#line 1393 "parser_1st.y"
                                {   (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    /* How to access symbol table entry of a terminal */
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    ds[curr]["identifier"] = "YES";
                                    // cout<<"\n\n\n";
                                    // for(auto i:code){
                                    //     cout<<i<<"\n";
                                    // }
                                    ds[curr]["start"] = numtostring(code.size());
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    // ds[curr]["var"] = 
                                    /* How to pass values from here? */
                  }
#line 5056 "parser_1st.tab.c"
    break;

  case 380: /* POSTFIXEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1407 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5062 "parser_1st.tab.c"
    break;

  case 381: /* POSTFIXEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1408 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5068 "parser_1st.tab.c"
    break;

  case 382: /* POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  */
#line 1410 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val));
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
#line 5085 "parser_1st.tab.c"
    break;

  case 383: /* POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  */
#line 1423 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val));
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
#line 5104 "parser_1st.tab.c"
    break;

  case 385: /* METHODDECLARATION: METHODHEADER METHODBODY  */
#line 1441 "parser_1st.y"
                                            {
    (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    
    for(auto i:ds2[chartonum((yyval.val))]["param"])
    code.push_back("pop param, "+ i);
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$1].name<<endl;
}
#line 5118 "parser_1st.tab.c"
    break;

  case 386: /* METHODDECLARATION: SUPER1 METHODHEADER METHODBODY  */
#line 1452 "parser_1st.y"
                                                      {
                        (yyval.val) =(yyvsp[-1].val);
                        method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
for(auto i:ds2[chartonum((yyval.val))]["param"])
                                        code.push_back("pop param, "+ i);
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
#line 5148 "parser_1st.tab.c"
    break;

  case 387: /* METHODDECLARATION: SUPER2 METHODHEADER METHODBODY  */
#line 1477 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    for(auto i:ds2[chartonum((yyval.val))]["param"])
                                        code.push_back("pop param, "+ i);
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
#line 5177 "parser_1st.tab.c"
    break;

  case 388: /* METHODDECLARATION: SUPER3 METHODHEADER METHODBODY  */
#line 1501 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    for(auto i:ds2[chartonum((yyval.val))]["param"])
                                        code.push_back("pop param, "+ i);
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
#line 5206 "parser_1st.tab.c"
    break;

  case 389: /* METHODDECLARATION: METHODMODIFIERS METHODHEADER METHODBODY  */
#line 1525 "parser_1st.y"
                                                               {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    for(auto i:ds2[chartonum((yyval.val))]["param"])
                                        code.push_back("pop param, "+ i);
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
#line 5235 "parser_1st.tab.c"
    break;

  case 395: /* METHODHEADER: TYPE METHODDECLARATOR  */
#line 1556 "parser_1st.y"
                                     { (yyval.val) = (yyvsp[0].val);  generalmap[(yyval.val)].typ.name = chartostring((yyvsp[-1].val)); 
tempnextscope(); 

assert(methods.find(generalmap[(yyvsp[0].val)].name) == methods.end());
    methods[generalmap[(yyvsp[0].val)].name].rettype = generalmap[(yyvsp[0].val)].typ;
    methods[generalmap[(yyvsp[0].val)].name].lineno = yylineno;
    
    vector <type> argtype;
     

    for (auto x : generalmap[(yyvsp[0].val)].farglist)
        {argtype.push_back(x.typ);
         }
    methods[generalmap[(yyvsp[0].val)].name].argtype = argtype;
        classmethods[curr_class][generalmap[(yyvsp[0].val)].name] = methods[generalmap[(yyvsp[0].val)].name];


for (auto x : generalmap[(yyval.val)].farglist){
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
        for(int ii=generalmap[(yyval.val)].farglist.size()-1 ; ii>=0; ii-- ){

                toffset -=   gettypesize(symboltable[generalmap[(yyval.val)].farglist[ii].vid.name].typ.name);
                              
        symboltable[generalmap[(yyval.val)].farglist[ii].vid.name].offset= toffset;
        }
        
        


        }
#line 5282 "parser_1st.tab.c"
    break;

  case 396: /* METHODHEADER: VOID METHODDECLARATOR  */
#line 1598 "parser_1st.y"
                                      { (yyval.val) = (yyvsp[0].val);  generalmap[(yyval.val)].typ.name = chartostring((yyvsp[-1].val)); 
            tempnextscope();

            assert(methods.find(generalmap[(yyvsp[0].val)].name) == methods.end());
    methods[generalmap[(yyvsp[0].val)].name].rettype = generalmap[(yyvsp[0].val)].typ;
    methods[generalmap[(yyvsp[0].val)].name].lineno = yylineno;
    
    vector <type> argtype;
     

    for (auto x : generalmap[(yyvsp[0].val)].farglist)
        {argtype.push_back(x.typ);
         }
    methods[generalmap[(yyvsp[0].val)].name].argtype = argtype;
        classmethods[curr_class][generalmap[(yyvsp[0].val)].name] = methods[generalmap[(yyvsp[0].val)].name];



for (auto x : generalmap[(yyval.val)].farglist){
symboltable[x.vid.name].typ.dims= x.vid.num;
        symboltable[x.vid.name].typ.name= x.typ.name;
        symboltable[x.vid.name].scope = scope;
        symboltable[x.vid.name].lineno = yylineno;
        symboltable[x.vid.name].token = "IDENTIFIER";

        // cout<<x.vid.name;
        printvarentry(symboltable[x.vid.name]);
        preservedsymboltable[{x.vid.name, scope}]= symboltable[x.vid.name];
        
        }}
#line 5317 "parser_1st.tab.c"
    break;

  case 407: /* METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1643 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));              
                                        method_det[curr_class][chartostring((yyvsp[-2].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        // cout<<"methodhead "<<ds[chartonum($$)]["method_name"]<<"\n";
                                        }
#line 5330 "parser_1st.tab.c"
    break;

  case 408: /* METHODDECLARATOR: IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 1651 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                method_det[curr_class][chartostring((yyvsp[-3].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-3].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        // for(auto i:ds2[curr3]["param"])
                                        // code.push_back("pop param, "+ i);
                                        ds2[curr]["param"] = ds2[curr3]["param"];}
#line 5343 "parser_1st.tab.c"
    break;

  case 417: /* FORMALPARAMETERLIST: FORMALPARAMETER  */
#line 1669 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 5352 "parser_1st.tab.c"
    break;

  case 418: /* FORMALPARAMETERLIST: FORMALPARAMETERLIST COMMA FORMALPARAMETER  */
#line 1673 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 5362 "parser_1st.tab.c"
    break;

  case 419: /* FORMALPARAMETER: TYPE VARIABLEDECLARATORID  */
#line 1679 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 5371 "parser_1st.tab.c"
    break;

  case 421: /* FORMALPARAMETER: FINAL TYPE VARIABLEDECLARATORID  */
#line 1684 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 5380 "parser_1st.tab.c"
    break;

  case 424: /* METHODBODY: BLOCK  */
#line 1694 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 5386 "parser_1st.tab.c"
    break;

  case 428: /* BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 1701 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val);  }
#line 5392 "parser_1st.tab.c"
    break;

  case 430: /* BLOCKSTATEMENTS: BLOCKSTATEMENT  */
#line 1704 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val);  
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
#line 5400 "parser_1st.tab.c"
    break;

  case 431: /* BLOCKSTATEMENTS: BLOCKSTATEMENTS BLOCKSTATEMENT  */
#line 1707 "parser_1st.y"
                                                  { (yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val)), curr2 = chartonum((yyvsp[0].val));
                                                    ds3[curr]["continuelist"] = merge(ds3[curr1]["continuelist"], ds3[curr2]["continuelist"]);
                                                    ds3[curr]["breaklist"] = merge(ds3[curr1]["breaklist"], ds3[curr2]["breaklist"]);
                                                    if(ds[curr1].find("start")!=ds[curr1].end())
                                                    ds[curr]["start"] = ds[curr1]["start"];
                                                     else if(ds[curr2].find("start")!=ds[curr2].end())
                                                     ds[curr]["start"] = ds[curr2]["start"];
                                                    // code.push_back("start = "+ds[curr]["start"]);
                }
#line 5415 "parser_1st.tab.c"
    break;

  case 433: /* BLOCKSTATEMENT: LOCALVARIABLEDECLARATIONSTATEMENT  */
#line 1719 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val); 
                
               }
#line 5423 "parser_1st.tab.c"
    break;

  case 434: /* BLOCKSTATEMENT: STATEMENT  */
#line 1722 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
               }
#line 5430 "parser_1st.tab.c"
    break;

  case 435: /* BLOCKSTATEMENT: PRINTLN  */
#line 1724 "parser_1st.y"
                            {code.push_back("print "+ chartostring((yyvsp[0].val)).substr(19,chartostring((yyvsp[0].val)).size() -21));}
#line 5436 "parser_1st.tab.c"
    break;

  case 437: /* LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  */
#line 1728 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 5442 "parser_1st.tab.c"
    break;

  case 438: /* LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1730 "parser_1st.y"
                                                                         {

                            if(generalmap[(yyvsp[0].val)].typ.name != "")assert(chartostring((yyvsp[-1].val))== generalmap[(yyvsp[0].val)].typ.name);
                            (yyval.val) = (yyvsp[0].val);
                            int curr = chartonum((yyval.val));
                                                    // assert(ds[curr].find("start")!=ds[curr].end());
                            // assert()
                            if(ds[curr].find("start")==ds[curr].end())
                            ds[curr]["start"] = numtostring(code.size());
                            string t = chartostring((yyvsp[-1].val));
                            for(auto t2:ds2[curr]["type"]){
                                if(!((t=="double"||t=="float")&&(t2=="int"||t2=="long"))){
                                    if(!((t=="double"&&t2=="float")||(t=="long"&&t2=="int")))
                                        if(t2!=chartostring((yyvsp[-1].val)))
                                        typ_error(chartostring((yyvsp[-1].val)),t2,int(yylineno));
                                    // }
                                }
                            }
                            for (auto x: generalmap[(yyvsp[0].val)].vlist){
                            
                            // cout<<x.first.name<<endl;
                            assert(symboltable.find(x.first.name) == symboltable.end());
                            /*ADD SIMILAR FOR FILEDS AND METHODS*/

                           symboltable[x.first.name].typ.dims= x.first.num;
                            symboltable[x.first.name].typ.name= chartostring((yyvsp[-1].val));
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
#line 5504 "parser_1st.tab.c"
    break;

  case 439: /* LOCALVARIABLEDECLARATION: LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1787 "parser_1st.y"
                                                                     {

                            if(generalmap[(yyvsp[0].val)].typ.name != "")assert(chartostring((yyvsp[-1].val))== generalmap[(yyvsp[0].val)].typ.name);
                            (yyval.val) = (yyvsp[0].val);
                            int curr = chartonum((yyval.val));
                                                    // assert(ds[curr].find("start")!=ds[curr].end());
                            // assert()
                            if(ds[curr].find("start")==ds[curr].end())
                            ds[curr]["start"] = numtostring(code.size());
                            string t = chartostring((yyvsp[-1].val));
                            for(auto t2:ds2[curr]["type"]){
                                if(!((t=="double"||t=="float")&&(t2=="int"||t2=="long"))){
                                    if(!((t=="double"&&t2=="float")||(t=="long"&&t2=="int")))
                                        if(t2!=chartostring((yyvsp[-1].val)))
                                        typ_error(chartostring((yyvsp[-1].val)),t2,int(yylineno));
                                    // }
                                }
                            }
                            
                            for (auto x: generalmap[(yyvsp[0].val)].vlist){
                            
                            // cout<<x.first.name<<endl;
                            assert(symboltable.find(x.first.name) == symboltable.end());
                            /*ADD SIMILAR FOR FILEDS AND METHODS*/

                           symboltable[x.first.name].typ.dims= x.first.num;
                            symboltable[x.first.name].typ.name= chartostring((yyvsp[-1].val));
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
#line 5570 "parser_1st.tab.c"
    break;

  case 440: /* LOCALVARIABLETYPE: TYPE  */
#line 1849 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 5576 "parser_1st.tab.c"
    break;

  case 441: /* LOCALVARIABLETYPE: VAR  */
#line 1850 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5582 "parser_1st.tab.c"
    break;

  case 442: /* STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1853 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
#line 5588 "parser_1st.tab.c"
    break;

  case 443: /* STATEMENT: LABELEDSTATEMENT  */
#line 1854 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5594 "parser_1st.tab.c"
    break;

  case 444: /* STATEMENT: IFTHENSTATEMENT  */
#line 1855 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5600 "parser_1st.tab.c"
    break;

  case 445: /* STATEMENT: IFTHENELSESTATEMENT  */
#line 1856 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5606 "parser_1st.tab.c"
    break;

  case 446: /* STATEMENT: WHILESTATEMENT  */
#line 1857 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5612 "parser_1st.tab.c"
    break;

  case 447: /* STATEMENT: FORSTATEMENT  */
#line 1858 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5618 "parser_1st.tab.c"
    break;

  case 448: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  */
#line 1860 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5624 "parser_1st.tab.c"
    break;

  case 449: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EMPTYSTATEMENT  */
#line 1862 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5630 "parser_1st.tab.c"
    break;

  case 450: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EXPRESSIONSTATEMENT  */
#line 1863 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5636 "parser_1st.tab.c"
    break;

  case 451: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: ASSERTSTATEMENT  */
#line 1864 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5642 "parser_1st.tab.c"
    break;

  case 452: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BREAKSTATEMENT  */
#line 1865 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5648 "parser_1st.tab.c"
    break;

  case 453: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: CONTINUESTATEMENT  */
#line 1866 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5654 "parser_1st.tab.c"
    break;

  case 454: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: RETURNSTATEMENT  */
#line 1867 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5660 "parser_1st.tab.c"
    break;

  case 455: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: THROWSTATEMENT  */
#line 1868 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5666 "parser_1st.tab.c"
    break;

  case 456: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: YIELDSTATEMENT  */
#line 1869 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5672 "parser_1st.tab.c"
    break;

  case 457: /* EMPTYSTATEMENT: SEMICOLON  */
#line 1871 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5678 "parser_1st.tab.c"
    break;

  case 458: /* EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  */
#line 1873 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val); }
#line 5684 "parser_1st.tab.c"
    break;

  case 459: /* STATEMENTEXPRESSION: ASSIGNMENT  */
#line 1875 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5690 "parser_1st.tab.c"
    break;

  case 460: /* STATEMENTEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1876 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5696 "parser_1st.tab.c"
    break;

  case 461: /* STATEMENTEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1877 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5702 "parser_1st.tab.c"
    break;

  case 462: /* STATEMENTEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1878 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5708 "parser_1st.tab.c"
    break;

  case 463: /* STATEMENTEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1879 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5714 "parser_1st.tab.c"
    break;

  case 464: /* STATEMENTEXPRESSION: METHODINVOCATION  */
#line 1880 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5720 "parser_1st.tab.c"
    break;

  case 465: /* STATEMENTEXPRESSION: CLASSINSTANCECREATIONEXPRESSION  */
#line 1881 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5726 "parser_1st.tab.c"
    break;

  case 468: /* BREAKSTATEMENT: BREAK SEMICOLON  */
#line 1886 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5739 "parser_1st.tab.c"
    break;

  case 470: /* CONTINUESTATEMENT: CONTINUE SEMICOLON  */
#line 1896 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5752 "parser_1st.tab.c"
    break;

  case 472: /* RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  */
#line 1906 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = ds[exp]["start"];
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5763 "parser_1st.tab.c"
    break;

  case 473: /* RETURNSTATEMENT: RETURN SEMICOLON  */
#line 1912 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 5774 "parser_1st.tab.c"
    break;

  case 477: /* IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1925 "parser_1st.y"
                                                                {   (yyval.val) = new_temp(); //Not keeping truelist and falselist corresponding to statements
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-2].val)), curr5 = chartonum((yyvsp[0].val));
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
#line 5795 "parser_1st.tab.c"
    break;

  case 478: /* IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT  */
#line 1942 "parser_1st.y"
                                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-4].val)), curr5 = chartonum((yyvsp[-2].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr3]["falselist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = merge(ds3[curr5]["continuelist"],ds3[curr7]["continuelist"]);
                                                                    ds3[curr]["breaklist"] = merge(ds3[curr5]["breaklist"],ds3[curr7]["breaklist"]);
                                                                    // ds3[curr]["truelist"] = vector<int>();
                                                                    // ds3[curr]["falselist"] = vector<int>();
}
#line 5811 "parser_1st.tab.c"
    break;

  case 479: /* IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF  */
#line 1954 "parser_1st.y"
                                                                                                                {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-4].val)), curr5 = chartonum((yyvsp[-2].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr3]["falselist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = merge(ds3[curr5]["continuelist"],ds3[curr7]["continuelist"]);
                                                                    ds3[curr]["breaklist"] = merge(ds3[curr5]["breaklist"],ds3[curr7]["breaklist"]);
                                                                    // ds3[curr]["truelist"] = vector<int>();
                                                                    // ds3[curr]["falselist"] = vector<int>();
}
#line 5827 "parser_1st.tab.c"
    break;

  case 480: /* STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1966 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5833 "parser_1st.tab.c"
    break;

  case 481: /* STATEMENTNOSHORTIF: LABELEDSTATEMENTNOSHORTIF  */
#line 1967 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5839 "parser_1st.tab.c"
    break;

  case 482: /* STATEMENTNOSHORTIF: IFTHENELSESTATEMENTNOSHORTIF  */
#line 1968 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5845 "parser_1st.tab.c"
    break;

  case 483: /* STATEMENTNOSHORTIF: WHILESTATEMENTNOSHORTIF  */
#line 1969 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5851 "parser_1st.tab.c"
    break;

  case 484: /* STATEMENTNOSHORTIF: FORSTATEMENTNOSHORTIF  */
#line 1970 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5857 "parser_1st.tab.c"
    break;

  case 486: /* WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1974 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-2].val)), curr5 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    backpatch(ds3[curr5]["continuelist"],stringtonum(ds[curr3]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                    backpatch(ds3[curr5]["breaklist"],code.size());
                                                                    // ds3[curr]["falselist"] = ds3[curr3]["falselist"];
}
#line 5873 "parser_1st.tab.c"
    break;

  case 487: /* FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  */
#line 1986 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); popscope();}
#line 5879 "parser_1st.tab.c"
    break;

  case 488: /* FORSTATEMENTNOSHORTIF: ENHANCEDFORSTATEMENTNOSHORTIF  */
#line 1987 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5885 "parser_1st.tab.c"
    break;

  case 489: /* WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1990 "parser_1st.y"
                                                                {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-2].val)), curr5 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    backpatch(ds3[curr5]["continuelist"],stringtonum(ds[curr3]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                    backpatch(ds3[curr5]["breaklist"],code.size());
}
#line 5900 "parser_1st.tab.c"
    break;

  case 490: /* FORSTATEMENT: BASICFORSTATEMENT  */
#line 2001 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5906 "parser_1st.tab.c"
    break;

  case 491: /* FORSTATEMENT: ENHANCEDFORSTATEMENT  */
#line 2002 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5912 "parser_1st.tab.c"
    break;

  case 492: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 2004 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 5925 "parser_1st.tab.c"
    break;

  case 493: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2012 "parser_1st.y"
                                                                                            {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr5 = chartonum((yyvsp[-2].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr7]["continuelist"],code.size()); 
                                                                    for(auto s:ds2[curr5]["code"])
                                                                    code.push_back(s);
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr7]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
}
#line 5941 "parser_1st.tab.c"
    break;

  case 494: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2023 "parser_1st.y"
                                                                                            {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-3].val)), curr7 = chartonum((yyvsp[0].val));
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
#line 5960 "parser_1st.tab.c"
    break;

  case 495: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2037 "parser_1st.y"
                                                                                                    {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-4].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
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
#line 5981 "parser_1st.tab.c"
    break;

  case 496: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 2053 "parser_1st.y"
                                                                                        {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[0].val));
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
#line 5999 "parser_1st.tab.c"
    break;

  case 497: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2066 "parser_1st.y"
                                                                                                    {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
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
#line 6020 "parser_1st.tab.c"
    break;

  case 498: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2082 "parser_1st.y"
                                                                                                    {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr5 = chartonum((yyvsp[-3].val)), curr8 = chartonum((yyvsp[0].val));
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
#line 6041 "parser_1st.tab.c"
    break;

  case 499: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2098 "parser_1st.y"
                                                                                                            {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-6].val)), curr5 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[-2].val)), curr9 = chartonum((yyvsp[0].val));
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
#line 6062 "parser_1st.tab.c"
    break;

  case 500: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2115 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6075 "parser_1st.tab.c"
    break;

  case 501: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2123 "parser_1st.y"
                                                                                                     {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr5 = chartonum((yyvsp[-2].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr7]["continuelist"],code.size()); 
                                                                    for(auto s:ds2[curr5]["code"])
                                                                    code.push_back(s);
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr7]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
}
#line 6091 "parser_1st.tab.c"
    break;

  case 502: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2134 "parser_1st.y"
                                                                                                     {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-3].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    
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
#line 6110 "parser_1st.tab.c"
    break;

  case 503: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2148 "parser_1st.y"
                                                                                                             {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-4].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    
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
#line 6132 "parser_1st.tab.c"
    break;

  case 504: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2165 "parser_1st.y"
                                                                                                 {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[0].val));
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
#line 6150 "parser_1st.tab.c"
    break;

  case 505: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2178 "parser_1st.y"
                                                                                                             {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
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
#line 6171 "parser_1st.tab.c"
    break;

  case 506: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2194 "parser_1st.y"
                                                                                                             {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr5 = chartonum((yyvsp[-3].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    
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
#line 6193 "parser_1st.tab.c"
    break;

  case 507: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2211 "parser_1st.y"
                                                                                                                     {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-6].val)), curr5 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[-2].val)), curr9 = chartonum((yyvsp[0].val));
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
#line 6214 "parser_1st.tab.c"
    break;

  case 510: /* FORINIT: STATEMENTEXPRESSIONLIST  */
#line 2233 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 6220 "parser_1st.tab.c"
    break;

  case 511: /* FORINIT: LOCALVARIABLEDECLARATION  */
#line 2234 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 6226 "parser_1st.tab.c"
    break;

  case 512: /* FORUPDATE: STATEMENTEXPRESSIONLIST  */
#line 2236 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 6240 "parser_1st.tab.c"
    break;

  case 513: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION  */
#line 2246 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 6246 "parser_1st.tab.c"
    break;

  case 514: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION  */
#line 2247 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 6258 "parser_1st.tab.c"
    break;

  case 552: /* SUPER1: PUBLIC  */
#line 2300 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6264 "parser_1st.tab.c"
    break;

  case 553: /* SUPER1: PRIVATE  */
#line 2301 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6270 "parser_1st.tab.c"
    break;

  case 554: /* SUPER1: PROTECTED  */
#line 2302 "parser_1st.y"
                    {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6276 "parser_1st.tab.c"
    break;

  case 555: /* SUPER1: SUPER1 PUBLIC  */
#line 2303 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6282 "parser_1st.tab.c"
    break;

  case 556: /* SUPER1: SUPER1 PRIVATE  */
#line 2304 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6288 "parser_1st.tab.c"
    break;

  case 557: /* SUPER1: SUPER1 PROTECTED  */
#line 2305 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6294 "parser_1st.tab.c"
    break;

  case 558: /* SUPER2: STATIC  */
#line 2307 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6300 "parser_1st.tab.c"
    break;

  case 559: /* SUPER2: FINAL  */
#line 2308 "parser_1st.y"
                 {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6306 "parser_1st.tab.c"
    break;

  case 560: /* SUPER2: SUPER1 STATIC  */
#line 2309 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6312 "parser_1st.tab.c"
    break;

  case 561: /* SUPER2: SUPER1 FINAL  */
#line 2310 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6318 "parser_1st.tab.c"
    break;

  case 562: /* SUPER2: SUPER2 STATIC  */
#line 2311 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6324 "parser_1st.tab.c"
    break;

  case 563: /* SUPER2: SUPER2 FINAL  */
#line 2312 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6330 "parser_1st.tab.c"
    break;

  case 564: /* SUPER2: SUPER2 PUBLIC  */
#line 2313 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6336 "parser_1st.tab.c"
    break;

  case 565: /* SUPER2: SUPER2 PRIVATE  */
#line 2314 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6342 "parser_1st.tab.c"
    break;

  case 566: /* SUPER2: SUPER2 PROTECTED  */
#line 2315 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6348 "parser_1st.tab.c"
    break;

  case 567: /* SUPER3: ABSTRACT  */
#line 2317 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6354 "parser_1st.tab.c"
    break;

  case 568: /* SUPER3: STRICTFP  */
#line 2318 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6360 "parser_1st.tab.c"
    break;

  case 569: /* SUPER3: SUPER2 ABSTRACT  */
#line 2319 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6366 "parser_1st.tab.c"
    break;

  case 570: /* SUPER3: SUPER2 STRICTFP  */
#line 2320 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6372 "parser_1st.tab.c"
    break;

  case 571: /* SUPER3: SUPER3 ABSTRACT  */
#line 2321 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6378 "parser_1st.tab.c"
    break;

  case 572: /* SUPER3: SUPER3 STRICTFP  */
#line 2322 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6384 "parser_1st.tab.c"
    break;

  case 573: /* SUPER3: SUPER3 PUBLIC  */
#line 2323 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6390 "parser_1st.tab.c"
    break;

  case 574: /* SUPER3: SUPER3 PRIVATE  */
#line 2324 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6396 "parser_1st.tab.c"
    break;

  case 575: /* SUPER3: SUPER3 PROTECTED  */
#line 2325 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6402 "parser_1st.tab.c"
    break;

  case 576: /* SUPER3: SUPER3 STATIC  */
#line 2326 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6408 "parser_1st.tab.c"
    break;

  case 577: /* SUPER3: SUPER3 FINAL  */
#line 2327 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6414 "parser_1st.tab.c"
    break;

  case 578: /* FIELDMODIFIERS: SUPER3 TRANSIENT  */
#line 2329 "parser_1st.y"
                                 {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6420 "parser_1st.tab.c"
    break;

  case 579: /* FIELDMODIFIERS: SUPER3 VOLATILE  */
#line 2330 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6426 "parser_1st.tab.c"
    break;

  case 580: /* FIELDMODIFIERS: FIELDMODIFIERS TRANSIENT  */
#line 2331 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6432 "parser_1st.tab.c"
    break;

  case 581: /* FIELDMODIFIERS: FIELDMODIFIERS VOLATILE  */
#line 2332 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6438 "parser_1st.tab.c"
    break;

  case 582: /* FIELDMODIFIERS: FIELDMODIFIERS PUBLIC  */
#line 2333 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6444 "parser_1st.tab.c"
    break;

  case 583: /* FIELDMODIFIERS: FIELDMODIFIERS PRIVATE  */
#line 2334 "parser_1st.y"
                                     {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6450 "parser_1st.tab.c"
    break;

  case 584: /* FIELDMODIFIERS: FIELDMODIFIERS PROTECTED  */
#line 2335 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6456 "parser_1st.tab.c"
    break;

  case 585: /* FIELDMODIFIERS: FIELDMODIFIERS STATIC  */
#line 2336 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6462 "parser_1st.tab.c"
    break;

  case 586: /* FIELDMODIFIERS: FIELDMODIFIERS FINAL  */
#line 2337 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6468 "parser_1st.tab.c"
    break;

  case 587: /* METHODMODIFIERS: SUPER3 SYNCHRONIZED  */
#line 2340 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6474 "parser_1st.tab.c"
    break;

  case 588: /* METHODMODIFIERS: SUPER3 NATIVE  */
#line 2341 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6480 "parser_1st.tab.c"
    break;

  case 589: /* METHODMODIFIERS: METHODMODIFIERS SYNCHRONIZED  */
#line 2342 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6486 "parser_1st.tab.c"
    break;

  case 590: /* METHODMODIFIERS: METHODMODIFIERS NATIVE  */
#line 2343 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6492 "parser_1st.tab.c"
    break;

  case 591: /* METHODMODIFIERS: METHODMODIFIERS ABSTRACT  */
#line 2344 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6498 "parser_1st.tab.c"
    break;

  case 592: /* METHODMODIFIERS: METHODMODIFIERS STRICTFP  */
#line 2345 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6504 "parser_1st.tab.c"
    break;

  case 593: /* METHODMODIFIERS: METHODMODIFIERS PUBLIC  */
#line 2346 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6510 "parser_1st.tab.c"
    break;

  case 594: /* METHODMODIFIERS: METHODMODIFIERS PRIVATE  */
#line 2347 "parser_1st.y"
                                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6516 "parser_1st.tab.c"
    break;

  case 595: /* METHODMODIFIERS: METHODMODIFIERS PROTECTED  */
#line 2348 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6522 "parser_1st.tab.c"
    break;

  case 596: /* METHODMODIFIERS: METHODMODIFIERS STATIC  */
#line 2349 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6528 "parser_1st.tab.c"
    break;

  case 597: /* METHODMODIFIERS: METHODMODIFIERS FINAL  */
#line 2350 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6534 "parser_1st.tab.c"
    break;

  case 601: /* TYPEARGUMENT: REFERENCETYPE  */
#line 2357 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 6540 "parser_1st.tab.c"
    break;

  case 602: /* TYPEARGUMENT: WILDCARD  */
#line 2358 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 6546 "parser_1st.tab.c"
    break;

  case 607: /* INTERFACETYPE: CLASSTYPE  */
#line 2367 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 6552 "parser_1st.tab.c"
    break;


#line 6556 "parser_1st.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2369 "parser_1st.y"



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
