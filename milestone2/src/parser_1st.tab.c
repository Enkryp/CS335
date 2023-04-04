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
    //     // cerr<<"Expected value of type "+a+" at line number "+lineno+". Instead found value of type "+b+"\n";
    //     exit(0);
    // }
    void typ_error(string a, string b, int lineno){
        cerr<<"Expected value of type "+a+" at line number "<<lineno<<". Instead found value of type "+b+"\n";
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
            cerr<<x<<endl;
        }
        // cerr<<scopes.size()<<endl;
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
        
        // cerr<< "gettypefromsymtable"<<endl;
        // cerr<< a<<endl;
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
        cerr<<s<<" at: "<<yylineno<<endl;
        exit(0);
    }
    map<char*,ll> temp;
    ll gid=0;
    char * new_temp(){
        ll num=gid++;
        num*=10;
        return numtochar(num);
    }

    


    

#line 279 "parser_1st.tab.c"

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
  YYSYMBOL_ABSTRACT = 88,                  /* ABSTRACT  */
  YYSYMBOL_SYNCHRONIZED = 89,              /* SYNCHRONIZED  */
  YYSYMBOL_NATIVE = 90,                    /* NATIVE  */
  YYSYMBOL_STRICTFP = 91,                  /* STRICTFP  */
  YYSYMBOL_SWITCH = 92,                    /* SWITCH  */
  YYSYMBOL_DEFAULT = 93,                   /* DEFAULT  */
  YYSYMBOL_PACKAGE = 94,                   /* PACKAGE  */
  YYSYMBOL_DO = 95,                        /* DO  */
  YYSYMBOL_GOTO = 96,                      /* GOTO  */
  YYSYMBOL_IMPORT = 97,                    /* IMPORT  */
  YYSYMBOL_THROWS = 98,                    /* THROWS  */
  YYSYMBOL_CASE = 99,                      /* CASE  */
  YYSYMBOL_ENUM = 100,                     /* ENUM  */
  YYSYMBOL_CATCH = 101,                    /* CATCH  */
  YYSYMBOL_TRY = 102,                      /* TRY  */
  YYSYMBOL_INTERFACE = 103,                /* INTERFACE  */
  YYSYMBOL_FINALLY = 104,                  /* FINALLY  */
  YYSYMBOL_CONST = 105,                    /* CONST  */
  YYSYMBOL_UNDERSCORE = 106,               /* UNDERSCORE  */
  YYSYMBOL_EXPORTS = 107,                  /* EXPORTS  */
  YYSYMBOL_OPENS = 108,                    /* OPENS  */
  YYSYMBOL_REQUIRES = 109,                 /* REQUIRES  */
  YYSYMBOL_USES = 110,                     /* USES  */
  YYSYMBOL_MODULE = 111,                   /* MODULE  */
  YYSYMBOL_SEALED = 112,                   /* SEALED  */
  YYSYMBOL_PROVIDES = 113,                 /* PROVIDES  */
  YYSYMBOL_TO = 114,                       /* TO  */
  YYSYMBOL_WITH = 115,                     /* WITH  */
  YYSYMBOL_OPEN = 116,                     /* OPEN  */
  YYSYMBOL_RECORD = 117,                   /* RECORD  */
  YYSYMBOL_TRANSITIVE = 118,               /* TRANSITIVE  */
  YYSYMBOL_ERROR = 119,                    /* ERROR  */
  YYSYMBOL_ONCE = 120,                     /* ONCE  */
  YYSYMBOL_NL = 121,                       /* NL  */
  YYSYMBOL_NON_SEALED = 122,               /* NON_SEALED  */
  YYSYMBOL_IDENTIFIER = 123,               /* IDENTIFIER  */
  YYSYMBOL_UNQUALIFIEDMETHODIDENTIFIER = 124, /* UNQUALIFIEDMETHODIDENTIFIER  */
  YYSYMBOL_DOTCLASS = 125,                 /* DOTCLASS  */
  YYSYMBOL_EOFF = 126,                     /* EOFF  */
  YYSYMBOL_YYACCEPT = 127,                 /* $accept  */
  YYSYMBOL_COMPILATIONUNIT = 128,          /* COMPILATIONUNIT  */
  YYSYMBOL_TYPE = 129,                     /* TYPE  */
  YYSYMBOL_PRIMITIVETYPE = 130,            /* PRIMITIVETYPE  */
  YYSYMBOL_NUMERICTYPE = 131,              /* NUMERICTYPE  */
  YYSYMBOL_INTEGRALTYPE = 132,             /* INTEGRALTYPE  */
  YYSYMBOL_FLOATINGTYPE = 133,             /* FLOATINGTYPE  */
  YYSYMBOL_REFERENCETYPE = 134,            /* REFERENCETYPE  */
  YYSYMBOL_CLASSORINTERFACETYPE = 135,     /* CLASSORINTERFACETYPE  */
  YYSYMBOL_CLASSTYPE = 136,                /* CLASSTYPE  */
  YYSYMBOL_CLASSTYPE1 = 137,               /* CLASSTYPE1  */
  YYSYMBOL_DIMS = 138,                     /* DIMS  */
  YYSYMBOL_METHODNAME = 139,               /* METHODNAME  */
  YYSYMBOL_EXPRESSIONNAME = 140,           /* EXPRESSIONNAME  */
  YYSYMBOL_ORDINARYCOMPILATIONUNIT = 141,  /* ORDINARYCOMPILATIONUNIT  */
  YYSYMBOL_TOPLEVELCLASSORINTERFACEDECLARATION = 142, /* TOPLEVELCLASSORINTERFACEDECLARATION  */
  YYSYMBOL_IMPORTDECLARATION = 143,        /* IMPORTDECLARATION  */
  YYSYMBOL_CLASSDECLARATION = 144,         /* CLASSDECLARATION  */
  YYSYMBOL_NORMALCLASSDECLARATION = 145,   /* NORMALCLASSDECLARATION  */
  YYSYMBOL_CLASSNAME = 146,                /* CLASSNAME  */
  YYSYMBOL_NORMALINTERFACEDECLARATION = 147, /* NORMALINTERFACEDECLARATION  */
  YYSYMBOL_FOR = 148,                      /* FOR  */
  YYSYMBOL_OPENCURLY = 149,                /* OPENCURLY  */
  YYSYMBOL_CLOSECURLY = 150,               /* CLOSECURLY  */
  YYSYMBOL_INTERFACEBODY = 151,            /* INTERFACEBODY  */
  YYSYMBOL_INTERFACEMEMBERDECLARATIONS = 152, /* INTERFACEMEMBERDECLARATIONS  */
  YYSYMBOL_INTERFACEMEMBERDECLARATION = 153, /* INTERFACEMEMBERDECLARATION  */
  YYSYMBOL_INTERFACEDECLARATION = 154,     /* INTERFACEDECLARATION  */
  YYSYMBOL_TYPEPARAMETERS = 155,           /* TYPEPARAMETERS  */
  YYSYMBOL_TYPEPARAMETERLIST = 156,        /* TYPEPARAMETERLIST  */
  YYSYMBOL_TYPEPARAMETER = 157,            /* TYPEPARAMETER  */
  YYSYMBOL_TYPEBOUND = 158,                /* TYPEBOUND  */
  YYSYMBOL_ADDITIONALBOUND = 159,          /* ADDITIONALBOUND  */
  YYSYMBOL_CLASSEXTENDS = 160,             /* CLASSEXTENDS  */
  YYSYMBOL_CLASSIMPLEMENTS = 161,          /* CLASSIMPLEMENTS  */
  YYSYMBOL_INTERFACETYPELIST = 162,        /* INTERFACETYPELIST  */
  YYSYMBOL_CLASSPERMITS = 163,             /* CLASSPERMITS  */
  YYSYMBOL_TYPENAMES = 164,                /* TYPENAMES  */
  YYSYMBOL_CLASSBODY = 165,                /* CLASSBODY  */
  YYSYMBOL_CLASSBODYDECLARATIONS = 166,    /* CLASSBODYDECLARATIONS  */
  YYSYMBOL_CLASSBODYDECLARATION = 167,     /* CLASSBODYDECLARATION  */
  YYSYMBOL_CLASSMEMBERDECLARATION = 168,   /* CLASSMEMBERDECLARATION  */
  YYSYMBOL_FIELDDECLARATION = 169,         /* FIELDDECLARATION  */
  YYSYMBOL_VARIABLEDECLARATORLIST = 170,   /* VARIABLEDECLARATORLIST  */
  YYSYMBOL_VARIABLEDECLARATOR = 171,       /* VARIABLEDECLARATOR  */
  YYSYMBOL_VARIABLEDECLARATORID = 172,     /* VARIABLEDECLARATORID  */
  YYSYMBOL_VARIABLEINITIALIZER = 173,      /* VARIABLEINITIALIZER  */
  YYSYMBOL_EXPRESSION = 174,               /* EXPRESSION  */
  YYSYMBOL_ASSIGNMENTEXPRESSION = 175,     /* ASSIGNMENTEXPRESSION  */
  YYSYMBOL_ASSIGNMENT = 176,               /* ASSIGNMENT  */
  YYSYMBOL_LEFTHANDSIDE = 177,             /* LEFTHANDSIDE  */
  YYSYMBOL_ASSIGNMENTOPERATOR = 178,       /* ASSIGNMENTOPERATOR  */
  YYSYMBOL_FIELDACCESS = 179,              /* FIELDACCESS  */
  YYSYMBOL_PRIMARY = 180,                  /* PRIMARY  */
  YYSYMBOL_PRIMARYNONEWARRAY = 181,        /* PRIMARYNONEWARRAY  */
  YYSYMBOL_LITERAL = 182,                  /* LITERAL  */
  YYSYMBOL_CLASSLITERAL = 183,             /* CLASSLITERAL  */
  YYSYMBOL_SQUARESTAR = 184,               /* SQUARESTAR  */
  YYSYMBOL_CLASSINSTANCECREATIONEXPRESSION = 185, /* CLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION = 186, /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_CLASSORINTERFACETYPETOINSTANTIATE = 187, /* CLASSORINTERFACETYPETOINSTANTIATE  */
  YYSYMBOL_ARGUMENTLIST = 188,             /* ARGUMENTLIST  */
  YYSYMBOL_METHODINVOCATION = 189,         /* METHODINVOCATION  */
  YYSYMBOL_METHODREFERENCE = 190,          /* METHODREFERENCE  */
  YYSYMBOL_ARRAYCREATIONEXPRESSION = 191,  /* ARRAYCREATIONEXPRESSION  */
  YYSYMBOL_ARRAYINITIALIZER = 192,         /* ARRAYINITIALIZER  */
  YYSYMBOL_ARRAYINITIALIZER1 = 193,        /* ARRAYINITIALIZER1  */
  YYSYMBOL_DIMEXPRS = 194,                 /* DIMEXPRS  */
  YYSYMBOL_DIMEXPR = 195,                  /* DIMEXPR  */
  YYSYMBOL_VARIABLEINITIALIZERLIST = 196,  /* VARIABLEINITIALIZERLIST  */
  YYSYMBOL_ARRAYACCESS = 197,              /* ARRAYACCESS  */
  YYSYMBOL_CONDITIONALEXPRESSION = 198,    /* CONDITIONALEXPRESSION  */
  YYSYMBOL_CONDITIONALOREXPRESSION = 199,  /* CONDITIONALOREXPRESSION  */
  YYSYMBOL_CONDITIONALANDEXPRESSION = 200, /* CONDITIONALANDEXPRESSION  */
  YYSYMBOL_INCLUSIVEOREXPRESSION = 201,    /* INCLUSIVEOREXPRESSION  */
  YYSYMBOL_EXCLUSIVEOREXPRESSION = 202,    /* EXCLUSIVEOREXPRESSION  */
  YYSYMBOL_ANDEXPRESSION = 203,            /* ANDEXPRESSION  */
  YYSYMBOL_EQUALITYEXPRESSION = 204,       /* EQUALITYEXPRESSION  */
  YYSYMBOL_RELATIONALEXPRESSION = 205,     /* RELATIONALEXPRESSION  */
  YYSYMBOL_SHIFTEXPRESSION = 206,          /* SHIFTEXPRESSION  */
  YYSYMBOL_ADDITIVEEXPRESSION = 207,       /* ADDITIVEEXPRESSION  */
  YYSYMBOL_MULTIPLICATIVEEXPRESSION = 208, /* MULTIPLICATIVEEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSION = 209,          /* UNARYEXPRESSION  */
  YYSYMBOL_PREINCREMENTEXPRESSION = 210,   /* PREINCREMENTEXPRESSION  */
  YYSYMBOL_PREDECREMENTEXPRESSION = 211,   /* PREDECREMENTEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSIONNOTPLUSMINUS = 212, /* UNARYEXPRESSIONNOTPLUSMINUS  */
  YYSYMBOL_POSTFIXEXPRESSION = 213,        /* POSTFIXEXPRESSION  */
  YYSYMBOL_POSTINCREMENTEXPRESSION = 214,  /* POSTINCREMENTEXPRESSION  */
  YYSYMBOL_POSTDECREMENTEXPRESSION = 215,  /* POSTDECREMENTEXPRESSION  */
  YYSYMBOL_INSTANCEOFEXPRESSION = 216,     /* INSTANCEOFEXPRESSION  */
  YYSYMBOL_METHODDECLARATION = 217,        /* METHODDECLARATION  */
  YYSYMBOL_METHODHEADER = 218,             /* METHODHEADER  */
  YYSYMBOL_THROWS2 = 219,                  /* THROWS2  */
  YYSYMBOL_EXCEPTIONTYPELIST = 220,        /* EXCEPTIONTYPELIST  */
  YYSYMBOL_EXCEPTIONTYPE = 221,            /* EXCEPTIONTYPE  */
  YYSYMBOL_METHODDECLARATOR = 222,         /* METHODDECLARATOR  */
  YYSYMBOL_RECEIVERPARAMETER = 223,        /* RECEIVERPARAMETER  */
  YYSYMBOL_FORMALPARAMETERLIST = 224,      /* FORMALPARAMETERLIST  */
  YYSYMBOL_FORMALPARAMETER = 225,          /* FORMALPARAMETER  */
  YYSYMBOL_VARIABLEARITYPARAMETER = 226,   /* VARIABLEARITYPARAMETER  */
  YYSYMBOL_METHODBODY = 227,               /* METHODBODY  */
  YYSYMBOL_INSTANCEINITIALIZER = 228,      /* INSTANCEINITIALIZER  */
  YYSYMBOL_STATICINITIALIZER = 229,        /* STATICINITIALIZER  */
  YYSYMBOL_BLOCK = 230,                    /* BLOCK  */
  YYSYMBOL_BLOCKSTATEMENTS = 231,          /* BLOCKSTATEMENTS  */
  YYSYMBOL_BLOCKSTATEMENT = 232,           /* BLOCKSTATEMENT  */
  YYSYMBOL_LOCALCLASSORINTERFACEDECLARATION = 233, /* LOCALCLASSORINTERFACEDECLARATION  */
  YYSYMBOL_LOCALVARIABLEDECLARATIONSTATEMENT = 234, /* LOCALVARIABLEDECLARATIONSTATEMENT  */
  YYSYMBOL_LOCALVARIABLEDECLARATION = 235, /* LOCALVARIABLEDECLARATION  */
  YYSYMBOL_LOCALVARIABLETYPE = 236,        /* LOCALVARIABLETYPE  */
  YYSYMBOL_STATEMENT = 237,                /* STATEMENT  */
  YYSYMBOL_STATEMENTWITHOUTTRAILINGSUBSTATEMENT = 238, /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
  YYSYMBOL_EMPTYSTATEMENT = 239,           /* EMPTYSTATEMENT  */
  YYSYMBOL_EXPRESSIONSTATEMENT = 240,      /* EXPRESSIONSTATEMENT  */
  YYSYMBOL_STATEMENTEXPRESSION = 241,      /* STATEMENTEXPRESSION  */
  YYSYMBOL_ASSERTSTATEMENT = 242,          /* ASSERTSTATEMENT  */
  YYSYMBOL_BREAKSTATEMENT = 243,           /* BREAKSTATEMENT  */
  YYSYMBOL_CONTINUESTATEMENT = 244,        /* CONTINUESTATEMENT  */
  YYSYMBOL_RETURNSTATEMENT = 245,          /* RETURNSTATEMENT  */
  YYSYMBOL_THROWSTATEMENT = 246,           /* THROWSTATEMENT  */
  YYSYMBOL_YIELDSTATEMENT = 247,           /* YIELDSTATEMENT  */
  YYSYMBOL_LABELEDSTATEMENT = 248,         /* LABELEDSTATEMENT  */
  YYSYMBOL_IFTHENSTATEMENT = 249,          /* IFTHENSTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENT = 250,      /* IFTHENELSESTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENTNOSHORTIF = 251, /* IFTHENELSESTATEMENTNOSHORTIF  */
  YYSYMBOL_STATEMENTNOSHORTIF = 252,       /* STATEMENTNOSHORTIF  */
  YYSYMBOL_LABELEDSTATEMENTNOSHORTIF = 253, /* LABELEDSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENTNOSHORTIF = 254,  /* WHILESTATEMENTNOSHORTIF  */
  YYSYMBOL_FORSTATEMENTNOSHORTIF = 255,    /* FORSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENT = 256,           /* WHILESTATEMENT  */
  YYSYMBOL_FORSTATEMENT = 257,             /* FORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENT = 258,        /* BASICFORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENTNOSHORTIF = 259, /* BASICFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_ENHANCEDFORSTATEMENT = 260,     /* ENHANCEDFORSTATEMENT  */
  YYSYMBOL_ENHANCEDFORSTATEMENTNOSHORTIF = 261, /* ENHANCEDFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_FORINIT = 262,                  /* FORINIT  */
  YYSYMBOL_FORUPDATE = 263,                /* FORUPDATE  */
  YYSYMBOL_STATEMENTEXPRESSIONLIST = 264,  /* STATEMENTEXPRESSIONLIST  */
  YYSYMBOL_CONSTRUCTORDECLARATION = 265,   /* CONSTRUCTORDECLARATION  */
  YYSYMBOL_CONSTRUCTORDECLARATOR = 266,    /* CONSTRUCTORDECLARATOR  */
  YYSYMBOL_SIMPLETYPENAME = 267,           /* SIMPLETYPENAME  */
  YYSYMBOL_CONSTRUCTORBODY = 268,          /* CONSTRUCTORBODY  */
  YYSYMBOL_EXPLICITCONSTRUCTORINVOCATION = 269, /* EXPLICITCONSTRUCTORINVOCATION  */
  YYSYMBOL_SUPER1 = 270,                   /* SUPER1  */
  YYSYMBOL_SUPER2 = 271,                   /* SUPER2  */
  YYSYMBOL_SUPER3 = 272,                   /* SUPER3  */
  YYSYMBOL_FIELDMODIFIERS = 273,           /* FIELDMODIFIERS  */
  YYSYMBOL_METHODMODIFIERS = 274,          /* METHODMODIFIERS  */
  YYSYMBOL_TYPEARGUMENTS = 275,            /* TYPEARGUMENTS  */
  YYSYMBOL_TYPEARGUMENTLIST = 276,         /* TYPEARGUMENTLIST  */
  YYSYMBOL_TYPEARGUMENT = 277,             /* TYPEARGUMENT  */
  YYSYMBOL_WILDCARD = 278,                 /* WILDCARD  */
  YYSYMBOL_WILDCARDBOUNDS = 279,           /* WILDCARDBOUNDS  */
  YYSYMBOL_INTERFACETYPE = 280             /* INTERFACETYPE  */
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
#define YYLAST   6288

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  154
/* YYNRULES -- Number of rules.  */
#define YYNRULES  606
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1147

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   381


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
     125,   126
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   239,   239,   240,   245,   246,   248,   249,   251,   252,
     254,   255,   256,   257,   258,   260,   261,   263,   265,   267,
     269,   272,   273,   275,   282,   299,   302,   303,   305,   346,
     347,   348,   350,   351,   352,   353,   355,   368,   369,   370,
     371,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   436,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   503,   504,   505,   507,
     508,   510,   511,   513,   514,   515,   516,   517,   519,   522,
     524,   525,   527,   528,   531,   532,   534,   535,   537,   539,
     541,   542,   544,   546,   547,   549,   550,   552,   553,   555,
     556,   557,   558,   560,   561,   562,   563,   564,   566,   592,
     616,   642,   680,   692,   716,   749,   751,   759,   766,   767,
     769,   771,   774,   776,   791,   792,   800,   801,   805,   807,
     809,   811,   813,   815,   818,   825,   826,   828,   831,   833,
     834,   835,   839,   840,   841,   842,   843,   844,   845,   847,
     848,   849,   850,   851,   852,   853,   855,   856,   857,   858,
     859,   860,   861,   863,   864,   866,   867,   868,   869,   871,
     872,   873,   874,   875,   876,   877,   878,   880,   883,   887,
     896,   908,   927,   951,   976,   977,   978,   979,   980,   981,
     982,   983,   984,   985,   986,   987,   988,   989,   990,   991,
     992,   993,   995,   996,   997,   998,   999,  1001,  1002,  1004,
    1005,  1006,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,
    1016,  1017,  1019,  1020,  1022,  1023,  1024,  1026,  1027,  1031,
    1033,  1034,  1040,  1041,  1058,  1072,  1073,  1075,  1076,  1090,
    1091,  1101,  1102,  1111,  1112,  1120,  1121,  1131,  1139,  1155,
    1173,  1178,  1196,  1210,  1224,  1238,  1240,  1241,  1250,  1258,
    1267,  1268,  1276,  1285,  1286,  1294,  1302,  1311,  1312,  1313,
    1316,  1324,  1326,  1340,  1354,  1355,  1363,  1372,  1373,  1374,
    1388,  1389,  1391,  1404,  1419,  1422,  1442,  1464,  1484,  1504,
    1524,  1525,  1526,  1527,  1528,  1531,  1558,  1572,  1573,  1574,
    1575,  1576,  1577,  1580,  1582,  1583,  1585,  1587,  1595,  1602,
    1603,  1604,  1605,  1606,  1607,  1609,  1610,  1612,  1616,  1622,
    1626,  1627,  1633,  1634,  1637,  1638,  1640,  1642,  1644,  1645,
    1647,  1650,  1661,  1662,  1665,  1668,  1670,  1672,  1731,  1794,
    1795,  1798,  1799,  1800,  1801,  1802,  1803,  1805,  1807,  1808,
    1809,  1810,  1811,  1812,  1813,  1814,  1816,  1818,  1820,  1821,
    1822,  1823,  1824,  1825,  1826,  1828,  1829,  1831,  1839,  1841,
    1849,  1851,  1857,  1864,  1866,  1868,  1870,  1887,  1899,  1911,
    1912,  1913,  1914,  1915,  1917,  1919,  1931,  1932,  1935,  1946,
    1947,  1949,  1957,  1968,  1982,  1998,  2011,  2027,  2043,  2060,
    2068,  2079,  2093,  2110,  2123,  2139,  2156,  2174,  2176,  2178,
    2179,  2181,  2191,  2192,  2201,  2202,  2203,  2204,  2207,  2208,
    2209,  2210,  2211,  2212,  2213,  2214,  2217,  2219,  2220,  2221,
    2222,  2224,  2225,  2226,  2227,  2228,  2229,  2230,  2231,  2232,
    2233,  2234,  2235,  2236,  2237,  2238,  2239,  2240,  2241,  2242,
    2243,  2245,  2246,  2247,  2248,  2249,  2250,  2252,  2253,  2254,
    2255,  2256,  2257,  2258,  2259,  2260,  2262,  2263,  2264,  2265,
    2266,  2267,  2268,  2269,  2270,  2271,  2272,  2274,  2275,  2276,
    2277,  2278,  2279,  2280,  2281,  2282,  2285,  2286,  2287,  2288,
    2289,  2290,  2291,  2292,  2293,  2294,  2295,  2297,  2299,  2300,
    2302,  2303,  2305,  2306,  2308,  2309,  2312
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
  "CONTINUE", "RETURN", "YIELD", "IF", "ELSE", "WHILE", "FOR1", "ABSTRACT",
  "SYNCHRONIZED", "NATIVE", "STRICTFP", "SWITCH", "DEFAULT", "PACKAGE",
  "DO", "GOTO", "IMPORT", "THROWS", "CASE", "ENUM", "CATCH", "TRY",
  "INTERFACE", "FINALLY", "CONST", "UNDERSCORE", "EXPORTS", "OPENS",
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

#define YYPACT_NINF (-824)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-527)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2819,  -824,   -26,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
     -32,    63,  -824,    22,  3555,  -824,  2019,  -824,  -824,  -824,
    -824,   813,   431,   783,   275,   191,   101,   272,   174,   356,
    -824,  -824,  -824,  -824,   283,  -824,  -824,  -824,  -824,  -824,
     297,   312,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   316,
     343,  -824,  -824,  -824,  -824,  -824,  -824,  -824,   348,   355,
     363,   363,   370,   285,   248,    18,   191,  -824,  1293,  -824,
     209,   400,  -824,    -2,  2096,  -824,   285,   248,    18,   191,
     356,   356,   356,   356,   356,   356,   468,   302,  -824,  -824,
    -824,  -824,  -824,   524,  -824,  -824,   565,   248,    18,   191,
    -824,    18,   191,  -824,   191,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,   589,   191,   485,
     609,   513,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    3172,  -824,  -824,  1467,  1293,  -824,  -824,  -824,  -824,   398,
    -824,  -824,  -824,  -824,   111,   649,  1485,  1723,  1912,    65,
    2950,  -824,    60,  -824,   651,  -824,  -824,   749,   485,  -824,
    -824,  2096,  -824,  1744,  -824,  1573,  1766,  2526,  -824,   248,
      18,   191,  -824,    18,   191,  -824,   191,  -824,   285,   248,
      18,   191,  -824,  -824,   285,   248,    18,   191,   285,   248,
      18,   191,  -824,  -824,   285,   248,    18,   191,   285,   248,
      18,   191,  -824,  -824,   285,   248,    18,   191,   561,  -824,
     355,  -824,   363,   584,    18,   191,  -824,   191,  -824,  -824,
     191,  -824,  -824,  -824,  2452,  -824,   555,   637,   964,   491,
    -824,   716,   637,    76,  -824,  5592,  5652,  5652,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   253,  1072,  -824,   626,  2065,
    5592,  5592,  -824,    20,    29,  3554,  5592,   743,   748,  -824,
    1074,  -824,    82,   747,   750,  1162,  -824,   751,  -824,  -824,
     798,   979,   261,   755,  -824,  -824,   403,  -824,   421,  -824,
    -824,  1125,  -824,  -824,   470,   507,   534,  -824,  3172,  -824,
    -824,  -824,   762,   653,  -824,  -824,  -824,  -824,   764,  -824,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,   875,  1256,  1364,   485,   485,   761,  -824,  -824,
    -824,  -824,  -824,   363,  2418,   191,  -824,  1213,   513,   398,
     111,   513,   398,  -824,  -824,  -824,  -824,   398,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   653,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   398,   769,  -824,   398,  -824,
    -824,   513,  -824,    18,   191,  -824,   191,  -824,  -824,   191,
    -824,  -824,   248,    18,   191,  -824,    18,   191,  -824,   191,
    -824,  -824,  -824,   248,    18,   191,  -824,    18,   191,  -824,
     191,  -824,   248,    18,   191,  -824,    18,   191,  -824,   191,
    -824,  -824,  -824,   248,    18,   191,  -824,    18,   191,  -824,
     191,  -824,   248,    18,   191,  -824,    18,   191,  -824,   191,
    -824,  -824,  -824,   248,    18,   191,  -824,    18,   191,  -824,
     191,  -824,   742,   744,  -824,  -824,  -824,   191,  -824,  -824,
    -824,  -824,   398,  1895,  3414,  3202,  2950,  1271,   224,   775,
    -824,   774,   770,   653,  -824,  3628,  -824,   779,  -824,    88,
      76,  5652,  5652,  5652,  5652,   718,    82,   747,   778,  -824,
    -824,  -824,  -824,  -824,   265,   754,   767,   763,   765,   549,
     234,   671,   608,   636,  -824,  -824,  -824,  -824,   470,  -824,
    -824,  -824,    37,   304,  -824,  -824,  -824,  -824,    67,    96,
     653,  -824,    15,   792,   797,   797,   799,   695,   810,    38,
    -824,   818,  -824,   820,  -824,   822,   823,  5592,  5592,  3688,
    3380,    46,  -824,   100,  -824,   106,    47,  3750,  5592,    72,
    5726,  -824,  -824,  -824,  -824,  -824,  -824,  5592,    98,    74,
    5592,  -824,  -824,  -824,  -824,  -824,   821,   829,  -824,   637,
     637,  1439,  -824,   838,  -824,   305,   830,  1577,   480,  -824,
     347,  3172,  3172,     3,  -824,  -824,  2141,   200,   843,   309,
    -824,  -824,   677,  -824,   191,  -824,   680,  -824,  -824,   684,
    -824,  -824,  -824,   705,  -824,   191,  -824,  -824,  -824,    18,
     191,  -824,   191,  -824,  -824,   191,  -824,  -824,  -824,  -824,
      18,   191,  -824,   191,  -824,  -824,   191,  -824,  -824,    18,
     191,  -824,   191,  -824,  -824,   191,  -824,  -824,  -824,  -824,
      18,   191,  -824,   191,  -824,  -824,   191,  -824,  -824,    18,
     191,  -824,   191,  -824,  -824,   191,  -824,  -824,  -824,  -824,
      18,   191,  -824,   191,  -824,  -824,   191,  -824,  -824,   363,
     814,  -824,  -824,   398,   398,   398,   398,   821,     8,   352,
    -824,   815,   840,  -824,   839,  -824,  2689,  -824,  -824,  -824,
    -824,   845,  -824,  -824,  -824,  -824,  -824,  -824,  5592,  5652,
    5652,  5652,  5652,  5652,  5652,  5652,  3810,  3872,   363,  5652,
    5652,  5652,  5652,  5652,  5652,  5652,  5652,  -824,   746,   853,
     757,   829,   619,  -824,   369,  -824,  -824,  3932,   303,   797,
    -824,   303,   797,  3994,  -824,   864,  -824,  -824,  5592,  -824,
    -824,  -824,  -824,   844,   866,   869,  -824,   381,  -824,   157,
     871,  -824,   766,  -824,  -824,  -824,  -824,    31,  -824,  -824,
     376,   884,   888,  -824,   781,  4054,  1072,   870,  -824,   896,
     901,  -824,  -824,   800,   904,  -824,   809,   914,  -824,  -824,
    -824,   923,   416,   363,  4116,  4176,    87,   123,   295,  -824,
    -824,  3172,   926,   927,   137,   832,   344,  -824,  1875,  2323,
    -824,  -824,  -824,  -824,  -824,  -824,  -824,   191,  -824,  -824,
    -824,  -824,  -824,   191,  -824,  -824,  -824,   191,  -824,  -824,
    -824,  -824,  -824,   191,  -824,  -824,  -824,   191,  -824,  -824,
    -824,  -824,  -824,   191,  -824,  -824,  -824,  -824,   363,  -824,
    -824,  -824,  -824,   770,   821,   867,  2020,  -824,  -824,  -824,
    -824,   938,   947,  -824,   920,   754,   767,   763,   765,   549,
     234,   234,  5652,   671,  5652,   671,  -824,   608,   608,   608,
     636,   636,  -824,  -824,  -824,  -824,  4238,   941,   363,   363,
    -824,    15,  -824,   943,  -824,   770,  -824,  -824,   770,   191,
     453,  4298,   962,  3467,  3380,  -824,   164,   166,  4360,   956,
    -824,  -824,  5592,  -824,  -824,  4420,   957,  5833,   965,  5592,
    4494,  6165,  -824,  4554,   959,  -824,  2236,  -824,  -824,   968,
     454,   973,   456,   346,    66,   969,    97,   970,   140,  -824,
    4616,  4676,   879,  -824,  -824,  -824,   494,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   770,  -824,   821,   495,  -824,
    3628,  5652,   671,   671,  -824,   510,  4738,  -824,  -824,  -824,
    -824,  -824,   191,   191,   519,  -824,   978,   983,   284,   984,
    -824,   908,  -824,   931,  -824,  -824,  -824,  -824,  -824,  -824,
    -824,   894,   998,   899,  -824,   525,  4798,  -824,  -824,   527,
    4860,  3380,  1002,   901,  5856,  1005,  5916,  1006,  -824,  -824,
     530,  4920,  -824,   531,  -824,  1014,  -824,  1015,  4982,  1009,
    5042,  1012,  5104,  1013,  1021,   532,  1024,   546,  -824,  -824,
     770,   821,  -824,  -824,  -824,  -824,   557,  -824,  -824,   191,
    5592,  5592,  3467,  5756,  3380,  -824,  5164,  1025,  -824,  -824,
     558,  -824,  -824,   559,  -824,  3380,  3380,  1023,  3380,  3380,
    1027,  5939,  -824,  -824,   574,  -824,  -824,  -824,  1041,   577,
    5226,  1044,   582,  5286,  1045,   595,  5348,  -824,  1052,  -824,
    1053,   770,  -824,  -824,  1046,  1048,  -824,  5408,  1030,  1058,
    -824,  -824,   602,  5470,  -824,  -824,  -824,  -824,  3380,  -824,
    -824,  3380,  3380,  1062,  -824,  -824,  1060,  1073,   610,  -824,
    1076,  1078,   611,  -824,  1080,  1086,   622,  -824,  -824,  3467,
    3467,  5999,  1089,  5592,  5530,  -824,  -824,   644,  -824,  -824,
    -824,  3380,  -824,  -824,  1090,  -824,  -824,  1091,  -824,  -824,
    1095,  1028,  -824,  3467,  1088,  6022,  1094,  6082,  1099,  -824,
    -824,  -824,  -824,  -824,  3467,  -824,  3467,  3467,  1096,  3467,
    3467,  1098,  6105,  -824,  -824,  -824,  3467,  -824,  -824,  3467,
    3467,  1104,  -824,  -824,  -824,  3467,  -824
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    29,     0,   551,   552,   553,   557,   558,   566,   567,
       0,     0,     2,     0,     0,    26,     0,    28,    36,   178,
      31,     0,     0,     0,   101,     0,     0,     0,     0,     0,
       1,     3,    27,    30,     0,   554,   555,   556,   559,   560,
       0,     0,   563,   564,   565,   561,   562,   568,   569,     0,
       0,   572,   573,   574,   575,   576,   570,   571,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   167,     0,    37,
       0,     0,    32,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   183,     0,   180,    20,
     188,    19,   606,   189,   190,   193,   192,     0,     0,     0,
      48,     0,     0,    52,     0,    54,    55,     7,    10,    11,
      12,    13,    14,    15,    16,   206,   168,     0,   557,     0,
      20,     0,     4,     6,     8,     9,     5,    17,    18,   205,
       0,   195,   207,     0,     0,   197,   199,   203,   204,     0,
     200,   201,   426,   202,     0,     0,     0,     0,     0,     0,
       0,    34,     0,    24,     0,    25,   177,     0,     0,   176,
     169,     0,   171,     0,   173,     0,     0,     0,   109,     0,
       0,     0,   113,     0,     0,   115,     0,   116,     0,     0,
       0,     0,    38,   133,     0,     0,     0,     0,     0,     0,
       0,     0,    39,   149,     0,     0,     0,     0,     0,     0,
       0,     0,    40,   165,     0,     0,     0,     0,     0,   182,
       0,   179,     0,     0,     0,     0,    44,     0,    46,    47,
       0,    50,    51,    53,     0,   427,     0,   396,   216,     0,
     212,   215,   395,     7,   456,     0,     0,     0,   249,   250,
     251,   252,   253,   254,   255,     0,   558,   241,     0,     0,
       0,     0,   440,     0,     0,     0,     0,     0,     0,   166,
     225,   439,     6,    18,     0,   378,   435,     0,   429,   458,
       0,   245,   377,   237,   239,   240,   244,   265,   247,   248,
     238,   246,   459,   460,     0,   461,   462,   447,     0,   430,
     432,   433,     0,     0,   434,   441,   448,   449,     0,   450,
     451,   452,   453,   454,   455,   442,   443,   444,   445,   446,
     489,   490,     0,     0,     0,     0,     0,     0,   196,   198,
     425,   385,   424,     0,     0,     0,   515,     0,     0,     0,
       0,     0,     0,   577,   578,   586,   587,     0,   581,   582,
     583,   584,   585,   579,   580,     0,   592,   593,   594,   595,
     596,   590,   588,   589,   591,     0,     0,    33,     0,   170,
     172,     0,   105,     0,     0,   107,     0,   108,   111,     0,
     112,   114,     0,     0,     0,    63,     0,     0,    67,     0,
      69,    70,   125,     0,     0,     0,   129,     0,     0,   131,
       0,   132,     0,     0,     0,    78,     0,     0,    82,     0,
      84,    85,   141,     0,     0,     0,   145,     0,     0,   147,
       0,   148,     0,     0,     0,    93,     0,     0,    97,     0,
      99,   100,   157,     0,     0,     0,   161,     0,     0,   163,
       0,   164,   184,     0,   181,   191,   194,     0,    42,    43,
      45,    49,     0,     0,     0,     0,     0,     0,     0,     0,
     400,     0,   217,     0,   211,     0,   397,     0,   258,     0,
       0,     0,     0,     0,     0,   379,     0,     0,     0,   220,
     222,   244,   247,   221,   335,   337,   339,   341,   343,   345,
     347,   350,   356,   360,   363,   367,   368,   371,   374,   380,
     381,   355,   379,   378,   245,   246,   372,   373,     0,     0,
       0,   259,     0,    20,   320,   321,     0,     0,     0,     0,
     467,     0,   469,     0,   472,     0,     0,     0,     0,     0,
       0,     0,   256,     0,   257,     0,     0,     0,     0,     0,
       0,   228,   229,   230,   231,   232,   233,     0,     0,     0,
       0,   382,   383,   428,   431,   436,   216,   438,   457,   402,
     399,     0,   406,   403,   404,     0,   241,   225,   224,   530,
     377,     0,     0,     0,   514,   518,     0,     0,     0,     0,
     417,   420,     0,   386,     0,   517,     0,   387,   388,     0,
     389,    35,   174,     0,   103,     0,   104,   106,   110,     0,
       0,    59,     0,    61,    62,     0,    65,    66,    68,   121,
       0,     0,   123,     0,   124,   127,     0,   128,   130,     0,
       0,    74,     0,    76,    77,     0,    80,    81,    83,   137,
       0,     0,   139,     0,   140,   143,     0,   144,   146,     0,
       0,    89,     0,    91,    92,     0,    95,    96,    98,   153,
       0,     0,   155,     0,   156,   159,     0,   160,   162,     0,
     185,    41,   390,     0,     0,     0,     0,   407,     0,     0,
     415,     0,     0,    21,     0,   213,     0,   214,   218,   219,
     263,     0,   262,   369,   370,   376,   375,   243,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   309,     0,   235,
       0,   437,   602,   600,     0,   598,   601,     0,   318,   316,
     327,   319,   317,     0,   277,     0,   473,   465,     0,   468,
     470,   471,   474,     0,     0,     0,   475,     0,   242,     0,
      24,   267,     0,   260,   261,   311,   307,     0,   280,   278,
       0,     0,    25,   266,     0,     0,     0,   510,   512,     0,
     509,   223,   308,     0,   234,   268,     0,     0,   401,   398,
     522,     0,     0,     0,     0,     0,     0,     0,     0,   529,
     528,     0,     0,     0,     0,     0,   216,   419,     0,     0,
     519,   209,   516,   210,   208,   175,   102,     0,    57,    58,
      60,    64,   119,     0,   120,   122,   126,     0,    72,    73,
      75,    79,   135,     0,   136,   138,   142,     0,    87,    88,
      90,    94,   151,     0,   152,   154,   158,   186,     0,   391,
     392,   393,   394,   410,   408,     0,     0,    22,   325,   323,
     330,     0,   324,   264,     0,   338,   340,   342,   344,   346,
     348,   349,     0,   351,     0,   352,   384,   357,   358,   359,
     361,   362,   365,   364,   366,   304,     0,     0,     0,     0,
     603,     0,   597,     0,   314,   312,   328,   315,   313,   269,
       0,     0,     0,     0,     0,   334,     0,     0,     0,     0,
     306,   303,     0,   281,   332,     0,     0,     0,     0,     0,
       0,     0,   302,     0,     0,   333,     0,   523,   405,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   527,
       0,     0,     0,   421,   422,   520,     0,   418,    56,   118,
      71,   134,    86,   150,   187,   412,   416,   409,     0,   322,
     326,     0,   354,   353,   294,     0,     0,   604,   605,   599,
     329,   270,   271,   273,     0,   466,     0,     0,   225,     0,
     476,   441,   481,     0,   480,   482,   483,   486,   487,   488,
     310,     0,   236,     0,   282,     0,     0,   279,   286,     0,
       0,     0,     0,   511,     0,     0,     0,     0,   513,   290,
       0,     0,   524,     0,   535,     0,   531,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   423,   521,
     411,   414,   331,   336,   295,   296,     0,   272,   274,   275,
       0,     0,     0,     0,     0,   305,     0,     0,   283,   284,
       0,   287,   288,     0,   491,     0,     0,     0,     0,     0,
       0,     0,   291,   292,     0,   525,   536,   532,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   537,     0,   533,
       0,   413,   297,   276,     0,     0,   484,     0,   510,     0,
     477,   298,     0,     0,   285,   289,   492,   493,     0,   507,
     495,     0,     0,     0,   293,   543,     0,     0,     0,   539,
       0,     0,     0,   547,     0,     0,     0,   538,   534,     0,
       0,     0,     0,     0,     0,   299,   300,     0,   494,   496,
     497,     0,   544,   545,     0,   540,   541,     0,   548,   549,
       0,     0,   485,     0,     0,     0,     0,     0,     0,   301,
     498,   546,   542,   550,     0,   499,     0,     0,     0,     0,
       0,     0,     0,   478,   500,   501,     0,   508,   503,     0,
       0,     0,   502,   504,   505,     0,   506
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -824,  -824,   -54,   880,  2191,  -824,  -824,  -494,   104,  2067,
    -824,  -464,  -824,    19,  -824,   725,  -824,   405,  -824,  -824,
    -824,  -540,   -29,   -48,  2471,  -824,   974,    -8,   846,  -824,
     910,  -824,  -824,   837,  2969,  -824,  2946,  -824,  2186,  -824,
     996,  -824,  -824,  -229,   678,  -531,  -651,  1288,  -824,   -77,
    -824,  -824,  -235,   812,  -824,  -824,  -824,  -227,   114,  -501,
     627,   674,   259,  -824,  -824,  -423,  -824,   632,   -74,  -824,
     -33,   207,  -824,   462,   464,   467,   477,   466,    42,  -663,
      39,    68,  -226,   395,   544,  -824,   732,   921,  1066,  -824,
     132,   520,  -211,  -824,   399,  -101,  -302,  -434,   386,  -824,
    -271,  -824,  -824,    78,  -305,  -283,  -824,  -824,  -523,  -243,
    -234,    34,  -824,  -824,  -487,  -824,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,  -323,  -824,  -824,  -824,  -824,
    -824,  -824,  -824,  -824,  -824,   154,  -823,  -521,  -824,  1022,
    1036,  -313,  -824,    30,   184,   216,  -824,   948,  -257,  -824,
     310,  -824,  -824,  -208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,   158,   122,   466,   124,   125,   126,   127,   467,
      91,   452,   264,   265,    14,    15,    16,   266,    18,    25,
      19,   267,    68,   131,    75,   161,   162,    20,   163,    87,
      88,   209,   650,    64,    65,    93,    66,    96,    69,   134,
     135,   136,   137,   229,   230,   231,   667,   739,   469,   470,
     270,   537,   271,   272,   273,   274,   275,   523,   471,   277,
     506,   740,   472,   279,   280,   669,   831,   709,   710,   832,
     281,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     138,   139,   325,   553,   554,   232,   449,   569,   570,   571,
     321,   140,   141,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   952,   953,   954,   955,   956,   308,
     309,   310,   957,   311,   958,   749,   972,   973,   143,   144,
     145,   326,   562,   312,   313,   314,   149,   150,   507,   704,
     705,   706,   860,    94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,   494,   494,   500,   435,   544,   459,   747,   703,   750,
     496,   497,   564,   659,   121,   830,   450,   575,   227,   561,
     731,   456,    30,   843,   845,   568,   160,   702,   743,    28,
      21,   775,    67,   510,   154,   525,   777,    26,   755,   130,
     708,   711,   512,   748,    21,    70,    21,    74,    74,    74,
      74,   717,    74,   269,    74,   519,    74,   -23,   573,   -20,
     132,   577,   502,   502,   547,   772,   578,   563,   107,   108,
     109,   110,   111,   112,   113,   114,   261,   773,   718,   316,
     121,   521,   268,   502,   580,    62,   318,   582,   502,   130,
     502,    27,   328,   331,   457,   345,   356,    24,   146,   572,
     457,   130,   576,   502,   165,   130,   671,   880,   727,   316,
     130,   361,   502,   359,   502,   324,   579,   762,   671,   574,
     728,   155,   729,   735,   671,    67,   132,   777,   989,   338,
     339,   546,   583,   340,   341,   342,   343,   344,    89,   502,
      74,    74,    74,   511,    74,    74,   142,    74,   729,   903,
     729,  1027,   513,  1030,   881,    74,    74,    74,    74,   991,
     912,   728,   522,   729,   146,    74,    74,    74,    74,   730,
     736,   652,   448,   502,   448,    74,    74,    74,    74,   932,
     502,   933,   502,   155,    22,   905,    29,    72,    89,   879,
     697,   165,   261,   823,   846,   742,   225,   754,    22,   729,
      22,   458,   993,   495,   495,    67,   164,   524,  1073,   323,
     730,   269,   142,   672,   549,   550,    23,   322,    73,   699,
     886,   752,   151,   775,    27,   733,   494,   494,   494,   494,
      23,   734,    23,   459,   261,   673,   674,   675,   676,   525,
     543,   698,   700,   913,   276,   865,   742,   269,   868,   761,
     686,   687,   147,   152,   443,   493,   493,   771,   166,   130,
     546,   782,    67,   894,   732,   731,   743,   755,  1114,   737,
     261,   701,   744,   567,   660,   498,   559,   678,   544,  1002,
     714,   753,   756,   538,   148,   864,   726,   960,   867,   962,
     167,    59,  1128,   164,  1131,   130,   324,   499,   660,    67,
     130,   324,   519,   130,   -23,   539,   -20,   688,   130,  1141,
     679,   502,   433,   210,    61,    62,    71,    67,   147,   211,
     779,   664,   528,   776,  1012,   764,   130,   498,   521,   130,
     780,  -379,  -379,   949,    74,    74,    60,    74,   758,   759,
      74,    61,    62,   558,   916,   166,    60,   661,   529,   499,
     148,    61,    62,   505,    74,    74,    74,   907,    74,    74,
     925,    74,   451,   779,   937,   938,   988,   703,   876,   538,
      67,   729,    59,   824,    74,    74,    74,   167,    74,    74,
     861,    74,   819,   820,   821,   822,   862,   882,   825,   278,
     877,   768,   928,   658,    74,    74,    74,   883,    74,    74,
     748,    74,   276,   876,   978,    17,    80,   322,   444,   522,
     322,   320,    67,   130,  -464,   322,  -464,    60,   754,    17,
      81,    17,    61,    62,  -464,   877,   666,   779,   495,   495,
     495,   495,  -463,   322,  -463,    82,   322,   897,   276,    83,
     445,   817,  -463,   269,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   269,   494,   494,   494,   494,   494,   494,
     494,   494,   983,  1000,   882,   882,    84,   882,   852,   853,
     854,    85,   949,   129,   942,   985,   261,   987,    86,   159,
     493,   493,   493,   493,   269,   269,    89,   748,   544,   748,
    1058,   130,   750,    95,    41,    42,    43,   567,   528,    44,
      45,    46,   453,   500,   454,   779,   779,   261,   261,   904,
     906,   908,   774,   769,   770,   999,  1001,   541,   542,    47,
     322,   882,    48,   153,   767,   282,   748,  -378,  -378,   208,
     882,  1004,   130,   130,    49,   212,   882,  1051,   882,   129,
    1009,   882,   779,   882,   748,   324,  1018,   278,  1021,   949,
     949,  1032,  1035,  1048,  -380,  -380,    74,   882,   107,   108,
     109,   110,   111,   112,   113,   114,   159,  1050,   882,   882,
     882,    74,    74,   949,    74,   447,   213,    74,  1052,  1064,
    1065,  -381,  -381,   278,   949,   882,   949,   949,   882,   949,
     949,    74,    74,   882,    74,  1074,   949,    74,  1076,   949,
     949,   684,   685,  1080,   748,   949,   882,   494,   226,   494,
     924,    74,    74,   882,    74,   224,  1084,    74,   829,   961,
     963,   882,   882,  1095,   130,   130,   130,   130,   748,  -526,
     748,  1104,  1107,   882,   276,   866,   228,   666,   866,   950,
     959,   692,   693,  1110,   276,   748,   495,   495,   495,   495,
     495,   495,   495,   495,   495,   882,   495,   495,   495,   495,
     495,   495,   495,   495,   357,  1119,   329,   332,   337,   327,
     355,   694,   695,   696,   283,   276,   276,   358,    89,   666,
     858,   859,   666,   282,   432,   329,   332,   337,   453,  1056,
     781,   453,   261,   783,   269,   453,   494,   784,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   436,   493,   493,
     493,   493,   493,   493,   493,   493,   453,   261,   785,   282,
     689,   690,   691,   909,   658,   658,   840,   841,   847,   848,
     849,   322,   322,   322,   322,   323,   519,  1024,   -23,    32,
     -20,    33,   130,   455,   442,  -225,  -225,  -225,  -225,  -225,
    -225,   501,   107,   108,   109,   110,   111,   112,   113,   114,
     850,   851,   521,   517,    74,    59,  1111,  1112,   518,   526,
     527,   530,   658,   540,    74,   545,   546,   548,   726,   278,
    1060,   551,   581,   929,    74,   -20,   662,   649,   664,   278,
    1125,  1066,  1067,   663,  1069,  1070,   269,   269,   670,   677,
     680,  1133,   682,  1134,  1135,   681,  1137,  1138,   683,   495,
     269,   495,  -277,  1142,   269,   707,  1143,  1144,   714,   713,
     278,   278,  1146,   716,   119,   531,   532,   533,   534,   535,
     536,   719,   283,   720,  1098,   721,   722,  1099,  1100,   451,
     453,   -20,   658,   522,   130,   130,    50,    51,    52,   763,
     765,    53,    54,    55,   778,   950,   959,   818,   827,   825,
     826,   493,   284,   493,   833,   873,    77,  1120,   283,   855,
      63,    56,    89,   856,    57,    76,    34,    35,    36,  1024,
     857,    37,    38,    39,   871,   276,    58,   874,   875,   879,
    1060,   878,  1066,  1067,   269,  1069,  1070,   269,   495,   269,
      97,   666,  1098,   884,   886,  1099,  1100,   951,   885,   890,
     889,  1120,   891,   169,   133,   282,    40,   179,   185,   189,
     195,   199,   205,   892,   893,   282,   178,   184,   188,   194,
     198,   204,   894,   895,   896,   269,   269,   269,    34,    35,
      36,   926,   130,    37,    38,    39,   910,   911,   269,   269,
     493,   269,   269,   116,   269,   914,   282,   282,   930,   261,
     931,   936,   940,   653,   654,   655,   656,   107,   108,   109,
     110,   111,   112,   113,   114,   945,   966,   970,   974,   981,
     133,   984,   451,   130,   447,   130,   986,   276,   276,   990,
     992,   269,   133,  -479,   269,   269,   130,   130,  1010,   130,
     130,   276,   998,  1011,  1013,   276,  -226,  -226,  -226,  -226,
    -226,  -226,   269,   269,   269,   372,  1014,  1015,  1016,  1031,
     284,   383,  1017,  1025,   269,   392,  1028,  1036,  1037,  1040,
     278,   403,  1043,  1046,  1047,   412,   269,  1049,   269,   130,
     269,   423,   130,   130,  1068,  1063,   951,   269,  1071,   269,
     269,   285,   269,   269,  1075,   269,   284,  1079,  1083,   269,
     130,   130,   269,   269,   283,  1087,  1088,  1089,   269,  1090,
    1093,  1094,   130,  1102,   283,   107,   108,   109,   110,   111,
     112,   113,   114,  1101,   130,   276,  1103,    89,   276,  1105,
     276,  1106,   519,  1108,   -23,   130,   -20,   130,   130,  1109,
     130,   130,  1115,  1121,  1122,   283,   283,   130,  1123,  1126,
     130,   130,  1132,  1124,   520,  1129,   130,  1136,   521,  1139,
     434,  -379,  -379,   951,   951,  1145,   276,   276,   276,   504,
     319,   665,   278,   278,   715,   360,   560,   712,  1003,   276,
     276,   835,   276,   276,   836,   276,   278,   951,   837,   839,
     278,   252,  -227,  -227,  -227,  -227,  -227,  -227,   951,   838,
     951,   951,   898,   951,   951,   917,   282,  1059,   330,   317,
     951,   939,   446,   951,   951,     0,     0,     0,     0,   951,
     528,     0,   276,     0,     0,   276,   276,     0,     0,  -224,
    -224,  -224,  -224,  -224,  -224,    89,   286,   -20,     0,   522,
       0,     0,     0,   276,   276,   276,   529,     0,     0,   285,
       0,     0,     0,     0,     0,   276,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,   276,     0,   276,
     278,   276,     0,   278,   565,   278,     0,     0,   276,     0,
     276,   276,     0,   276,   276,   285,   276,     0,     0,     0,
     276,     0,   284,   276,   276,     0,     0,     0,     0,   276,
       0,     0,   284,     0,     0,     0,     0,     0,   282,   282,
       0,   278,   278,   278,   107,   108,   109,   110,   111,   112,
     113,   114,   282,   566,   278,   278,   282,   278,   278,     0,
     278,     0,   657,   284,   284,     0,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,   115,    67,   116,    59,
       0,     0,     0,     0,     0,   283,     0,     0,   117,    41,
      42,    43,     0,     0,    44,    45,    46,   278,     0,     0,
     278,   278,     0,     0,     0,     0,    89,     0,     0,     0,
       0,   566,     0,     0,    47,     0,     0,    48,   278,   278,
     278,     0,     0,     0,   286,     0,     2,     3,     4,     0,
     278,     5,   118,     7,     0,     0,   282,     0,   119,   282,
       0,   282,   278,     0,   278,     0,   278,     0,     0,     0,
       0,     8,     0,   278,     9,   278,   278,   870,   278,   278,
     286,   278,     0,     0,    89,   278,    11,     0,   278,   278,
       0,     0,     0,     0,   278,     0,     0,   282,   282,   282,
       0,     0,     0,     0,     0,     0,   120,   283,   283,     0,
     282,   282,     0,   282,   282,     0,   282,    50,    51,    52,
       0,   283,    53,    54,    55,   283,     0,     0,   900,   902,
       0,   285,   107,   108,   109,   110,   111,   112,   113,   114,
       0,   285,    56,     0,     0,    57,     0,     0,     0,     0,
     760,     0,     0,   282,     0,     0,   282,   282,     0,     0,
     107,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,     0,   285,   285,   282,   282,   282,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   282,     0,     0,     0,
       0,    59,     0,   284,     0,     0,     0,     0,   282,   566,
     282,     0,   282,     0,     0,   283,     0,     0,   283,   282,
     283,   282,   282,   468,   282,   282,     0,   282,     0,     0,
     935,   282,     0,     0,   282,   282,     0,     0,   508,   509,
     282,     0,   315,   515,   516,   944,     0,     0,    34,    35,
      36,     0,   965,    37,    38,    39,   283,   283,   283,   969,
     119,     0,    89,     0,     0,     0,     0,   980,     0,   283,
     283,     0,   283,   283,     0,   283,   107,   108,   109,   110,
     111,   112,   113,   114,   995,   997,   286,     0,    40,    59,
     120,     0,     0,     0,     0,   519,   286,   -23,     0,   -20,
       0,     0,     0,     0,     0,   284,   284,     0,   120,     0,
    1006,     0,   283,     0,     0,   283,   283,   520,     0,   284,
       0,   766,     0,   284,  -379,  -379,     0,   286,   286,     0,
       0,     0,     0,   283,   283,   283,    34,    35,    36,     0,
    1020,    37,    38,    39,  1023,   283,     0,     0,   119,     0,
       0,     0,     0,     0,     0,  1034,     0,   283,     0,   283,
       0,   283,  1039,     0,  1042,     0,  1045,     0,   283,     0,
     283,   283,     0,   283,   283,     0,   283,     0,     0,     0,
     283,     0,     0,   283,   283,     0,     0,     0,     0,   283,
    1062,     0,   285,     0,     0,     0,    89,     0,     0,     0,
     -20,     0,   522,   284,     0,     0,   284,     0,   284,     0,
       0,     0,     0,     0,  1078,     0,     0,  1082,     0,     0,
    1086,     0,     0,     0,     0,     0,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,  1097,     0,    59,
       0,     0,     0,   668,   284,   284,   284,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   284,   284,     0,
     284,   284,     0,   284,     0,     0,     0,     0,     0,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
       0,     0,    59,     0,     0,     0,    41,    42,    43,     0,
       0,    44,    45,    46,   285,   285,     0,     0,   119,     0,
     284,     0,     0,   284,   284,   723,   724,   725,   285,     0,
       0,    47,   285,     0,    48,     0,   741,     0,     0,   315,
       0,   284,   284,   284,     0,   751,    49,     0,   757,    41,
      42,    43,     0,   284,    44,    45,    46,   286,     0,     0,
       0,   119,     0,     0,     0,   284,    89,   284,     0,   284,
       0,     0,     0,     0,    47,     0,   284,    48,   284,   284,
       0,   284,   284,     0,   284,     0,     0,    89,   284,     0,
       0,   284,   284,     0,     0,     0,     0,   284,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,    89,
       0,     0,   285,     0,     0,   285,   915,   285,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,     0,
       0,    59,     0,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,     0,    59,     0,
       0,     0,     0,   285,   285,   285,     0,     0,     0,   286,
     286,     0,     0,     0,     0,   566,   285,   285,     0,   285,
     285,     0,   285,   286,   668,     0,     0,   286,     0,    35,
      36,     0,     0,    37,    38,    39,   834,     0,     0,     0,
     119,     0,     0,     0,     0,    50,    51,    52,     0,     0,
      53,    54,    55,   333,   334,     0,     0,   119,     0,   285,
       0,     0,   285,   285,     0,   863,     0,     0,    89,     0,
      56,   335,   336,    57,     0,     0,   872,     0,     0,     0,
     285,   285,   285,     0,     0,    58,     0,     0,    89,     0,
       0,     0,   285,   107,   108,   109,   110,   111,   112,   113,
     114,     0,     1,   888,   285,    89,   285,   286,   285,     0,
     286,   927,   286,     0,     0,   285,     0,   285,   285,     0,
     285,   285,     0,   285,     0,     0,     0,   285,     0,     0,
     285,   285,     0,     0,     0,     0,   285,     0,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,   286,   286,
     286,   502,     2,     3,     4,     0,     0,     5,     6,     7,
     566,   286,   286,     0,   286,   286,     0,   286,     0,   107,
     108,   109,   110,   111,   112,   113,   114,     8,     0,   156,
       9,   116,    59,     0,     0,     0,    10,     0,     0,     0,
       0,   117,    11,     0,     0,     0,     0,    90,    92,     0,
       0,     0,     0,     0,   286,   128,     0,   286,   286,     0,
       0,   128,     0,    89,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,     0,   286,   286,   286,     0,     2,
       3,     4,     0,     0,     5,     6,     7,   286,     0,     0,
     967,   119,     0,     0,     0,     0,     0,   975,   977,   286,
       0,   286,     0,   286,     8,     0,     0,     9,   503,   157,
     286,     0,   286,   286,     0,   286,   286,   263,   286,     0,
     128,   128,   286,     0,     0,   286,   286,     0,     0,     0,
       0,   286,     0,   128,   128,   128,   128,   128,   668,    89,
       0,     0,     0,     0,   128,     0,     0,     0,   128,     0,
     128,     0,   128,   128,   128,     0,     0,     0,     0,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,   100,
     103,   105,   106,     0,     0,     0,     0,   982,     0,   123,
       0,     0,     0,     0,    89,   123,   182,     0,   192,     0,
     202,     0,     0,     0,     0,   128,     0,     0,     0,    92,
       0,     0,     0,   216,   218,   219,     0,   221,   222,     0,
     223,   128,     0,   128,     0,   128,     0,     0,  1054,  1055,
       0,     0,     0,     0,     0,     0,   566,     0,     0,     0,
       0,     0,     0,   128,     0,     0,   128,     0,     0,     0,
       0,   262,     0,     0,   123,   123,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,   123,   123,   123,
     123,   123,     0,     0,     0,  1092,     0,     0,   123,     0,
       0,     0,   123,     0,   123,   263,   123,   123,   123,    89,
       0,     0,     0,     0,   375,   378,   380,   381,     0,     0,
       0,     0,     0,     0,   395,   398,   400,   401,     0,     0,
       0,  1116,  1118,     0,   415,   418,   420,   421,     0,     0,
     552,   263,     0,   566,   128,     0,     0,     0,     0,     0,
     438,   439,     0,   440,     0,     0,   441,     0,     0,     0,
       0,     0,     0,     0,     0,   123,     0,   123,     0,   123,
       0,   233,   108,   109,   110,   111,   112,   113,   114,     0,
       0,   234,    67,   116,   502,     0,     0,   123,   235,     0,
     123,     0,     0,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,   236,   237,     0,    59,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,   262,
     555,     2,     3,     4,     0,     0,     5,     6,   246,     0,
       0,     0,   556,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,     0,   258,   259,     8,     0,     0,     9,
     128,   128,   128,   128,   128,   262,     3,     4,   123,     0,
       5,     6,     7,     0,     0,     0,     0,   119,     0,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
       8,   557,    59,     9,     0,     0,     0,   168,   172,   175,
     177,     0,   183,     0,   193,     0,   203,     0,   591,   593,
     594,     0,   596,   597,     0,   598,     0,     0,     0,   128,
       0,     0,     0,     0,     0,    89,     0,     0,   611,   613,
     614,     0,   616,   617,     0,   618,     0,     0,     0,    50,
      51,    52,     0,     0,    53,    54,    55,   263,   631,   633,
     634,   119,   636,   637,     0,   638,     0,     0,     0,     0,
       0,     0,     0,     0,    56,   335,   336,    57,   128,     0,
       0,     0,     0,   651,     0,     0,     0,     0,   263,   263,
       0,     0,     0,   128,   123,   123,   123,   123,   123,     0,
     362,   365,   367,     0,   368,   370,     0,   371,     0,    89,
       0,     0,     0,     0,     0,   382,   386,   389,   391,     0,
       0,     0,     0,     0,     0,   402,   406,   409,   411,     0,
       0,     0,     0,     0,     0,   422,   426,   429,   431,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   460,   108,   109,   110,   111,   112,   113,   114,
     828,     0,     0,    67,   116,     0,     0,     0,     0,   235,
       0,     0,     0,     0,     0,     0,    92,     0,     0,     0,
       0,   262,   461,   462,     0,     0,     0,     0,     0,     0,
     463,   464,     0,     0,     0,     0,   236,   237,     0,     0,
       0,     0,   123,   238,   239,   240,   241,   242,   243,   244,
       0,   245,   262,   262,     0,   128,     0,   123,     0,     0,
       0,     0,     0,   247,   248,   249,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   788,   789,     0,   790,     0,
       0,   791,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   798,   799,     0,   800,     0,
       0,   801,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   465,   128,     0,   808,   809,     0,   810,     0,
       0,   811,     0,     0,     0,     0,     0,     0,     0,     0,
     552,     0,     1,     0,   584,   586,     0,   587,   263,     0,
     588,     0,     0,     0,     0,   128,   128,     0,     0,     0,
       0,     0,     0,     0,   599,   602,   604,     0,   605,   607,
       0,   608,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   619,   622,   624,     0,   625,   627,
       0,   628,     2,     3,     4,    92,     0,     5,     6,     7,
       0,     0,     0,   128,   639,   642,   644,     0,   645,   647,
       0,   648,     0,     0,     0,     0,     0,     8,     0,     0,
       9,     0,     0,     0,     0,     0,    10,     0,     0,     0,
       0,     0,    11,     0,     0,   128,   128,     0,   128,     0,
       0,     0,     0,     0,     0,     0,     0,   123,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,     0,     0,   107,   108,   109,   110,   111,   112,   113,
     114,     0,   262,   128,     0,     0,    59,     0,     0,   123,
     123,     0,     0,   918,     0,    79,     0,     0,     0,     0,
       0,     0,     0,   920,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   922,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
     102,   104,     0,     0,   346,   347,     0,   123,   348,   349,
     350,     0,   171,   174,   176,   119,   181,   187,   191,   197,
     201,   207,    98,   101,     0,     0,     0,     0,   351,   352,
     353,   354,     0,   215,   217,   170,   173,   220,     0,   180,
     186,   190,   196,   200,   206,   941,   786,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   214,     0,     0,     0,
       0,   792,   794,    89,   795,     0,     0,   796,     0,     0,
     263,     0,     0,     0,     0,     0,     0,   123,     0,     0,
       0,   802,   804,     0,   805,     0,     0,   806,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   812,   814,     0,   815,   364,   366,   816,     0,   369,
       0,     0,     0,     0,   374,   377,   379,     0,  1007,  1008,
     385,   388,   390,     0,   394,   397,   399,     0,   363,     0,
     405,   408,   410,     0,   414,   417,   419,   373,   376,     0,
     425,   428,   430,   384,   387,     0,     0,   393,   396,     0,
     437,     0,     0,   404,   407,     0,     0,   413,   416,     0,
       0,     0,     0,   424,   427,   233,   108,   109,   110,   111,
     112,   113,   114,     0,     0,   234,    67,   116,     0,     0,
       0,     0,   235,     0,     0,  1053,     0,     0,     0,     0,
       0,     0,     0,     0,   262,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,     0,    59,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,     2,     3,     4,     0,     0,
       5,     6,   246,     0,     0,     0,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,     0,   258,   259,
       8,     0,     0,     9,   919,     0,    51,    52,     0,     0,
      53,    54,    55,     0,   921,     0,     0,   119,     0,     0,
       0,     0,     0,     0,   923,     0,     0,     0,     0,     0,
      56,   335,   336,    57,     0,   260,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   585,
       0,     0,     0,     0,     0,     0,     0,     0,   590,   592,
       0,     0,   595,     0,     0,    89,     0,     0,     0,   601,
     603,     0,     0,   606,     0,     0,     0,     0,   610,   612,
       0,   589,   615,     0,     0,     0,     0,     0,     0,   621,
     623,     0,   600,   626,     0,     0,     0,     0,   630,   632,
       0,   609,   635,     0,     0,     0,     0,     0,     0,   641,
     643,     0,   620,   646,     0,     0,     0,     0,     0,     0,
       0,   629,     0,   460,   108,   109,   110,   111,   112,   113,
     114,     0,   640,   234,    67,     0,     0,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   236,   237,     0,
      59,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,     0,   245,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   247,   248,   249,   250,   251,     0,
     253,   254,   255,   256,   257,     0,   258,   259,     0,     0,
     460,   108,   109,   110,   111,   112,   113,   114,    42,    43,
     234,    67,    44,    45,    46,     0,     0,   235,     0,   119,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    47,   260,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,   236,   237,     0,     0,     0,     0,
       0,   238,   239,   240,   241,   242,   243,   244,     0,   245,
       0,     0,     0,     0,     0,   787,     0,    89,     0,     0,
       0,   247,   248,   249,   250,   251,   793,   253,   254,   255,
     256,   946,     0,   947,   259,   797,     0,   460,   108,   109,
     110,   111,   112,   113,   114,     0,   803,   514,     1,     0,
       0,     0,     0,     0,   235,   807,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   813,   461,   462,     0,
     948,     0,     0,     0,     0,   463,   464,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,     0,     2,     3,
       4,     0,     0,     5,     6,     7,     0,     0,   247,   248,
     249,   460,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,    67,     8,     0,     0,     9,     0,   235,     0,
       0,     0,    10,     0,     0,     0,     0,     0,    11,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,   465,     0,     0,
       0,    31,   238,   239,   240,   241,   242,   243,   244,     0,
     245,   460,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,   247,   248,   249,     0,     0,   670,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,     0,
     245,   465,     0,   460,   108,   109,   110,   111,   112,   113,
     114,     0,   247,   248,   249,     0,     0,     0,     0,     0,
     235,   738,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,   465,   245,   460,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,   247,   248,   249,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,   842,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,     0,   245,   465,     0,   460,   108,   109,   110,   111,
     112,   113,   114,     0,   247,   248,   249,     0,     0,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,   844,
       0,     0,     0,     0,     0,   461,   462,     0,     0,     0,
       0,     0,     0,   463,   464,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,   492,   245,   460,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   247,   248,   249,     0,
       0,   663,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   461,   462,     0,     0,     0,
       0,     0,     0,   463,   464,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,   492,     0,   460,   108,   109,
     110,   111,   112,   113,   114,     0,   247,   248,   249,     0,
       0,     0,     0,     0,   235,   869,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,   462,     0,
       0,     0,     0,     0,     0,   463,   464,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,   465,   245,   460,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   887,   247,   248,
     249,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,   462,     0,
       0,     0,     0,     0,     0,   463,   464,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,   465,     0,   460,
     108,   109,   110,   111,   112,   113,   114,     0,   247,   248,
     249,     0,     0,     0,     0,     0,   235,   899,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
     462,     0,     0,     0,     0,     0,     0,   463,   464,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,   465,   245,   460,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
     247,   248,   249,     0,     0,     0,   235,   901,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
     462,     0,     0,     0,     0,     0,     0,   463,   464,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,   465,
       0,   460,   108,   109,   110,   111,   112,   113,   114,     0,
     247,   248,   249,     0,     0,     0,     0,     0,   235,   934,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,   465,
     245,   460,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,   247,   248,   249,     0,     0,     0,   235,   943,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,     0,
     245,   465,     0,   460,   108,   109,   110,   111,   112,   113,
     114,     0,   247,   248,   249,     0,     0,     0,     0,     0,
     235,   964,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,   465,   245,   460,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,   247,   248,   249,     0,     0,     0,
     235,   968,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,     0,   245,   465,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   247,   248,   249,   460,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   976,     0,     0,
       0,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,   462,     0,
       0,     0,     0,     0,     0,   463,   464,     0,     0,     0,
       0,   236,   237,   465,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,   460,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,   247,   248,
     249,     0,     0,     0,   235,   979,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,   462,     0,
       0,     0,     0,     0,     0,   463,   464,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,   465,     0,   460,
     108,   109,   110,   111,   112,   113,   114,     0,   247,   248,
     249,     0,     0,     0,     0,     0,   235,   994,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
     462,     0,     0,     0,     0,     0,     0,   463,   464,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,   465,   245,   460,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
     247,   248,   249,     0,     0,     0,   235,   996,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
     462,     0,     0,     0,     0,     0,     0,   463,   464,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,   465,
       0,   460,   108,   109,   110,   111,   112,   113,   114,     0,
     247,   248,   249,     0,     0,     0,     0,     0,   235,  1005,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,   465,
     245,   460,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,   247,   248,   249,     0,     0,     0,   235,  1019,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,     0,
     245,   465,     0,   460,   108,   109,   110,   111,   112,   113,
     114,     0,   247,   248,   249,     0,     0,     0,     0,     0,
     235,  1022,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,   465,   245,   460,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,   247,   248,   249,     0,     0,     0,
     235,  1033,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,     0,   245,   465,     0,   460,   108,   109,   110,   111,
     112,   113,   114,     0,   247,   248,   249,     0,     0,     0,
       0,     0,   235,  1038,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   461,   462,     0,     0,     0,
       0,     0,     0,   463,   464,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,   465,   245,   460,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   247,   248,   249,     0,
       0,     0,   235,  1041,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   461,   462,     0,     0,     0,
       0,     0,     0,   463,   464,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,   465,     0,   460,   108,   109,
     110,   111,   112,   113,   114,     0,   247,   248,   249,     0,
       0,     0,     0,     0,   235,  1044,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,   462,     0,
       0,     0,     0,     0,     0,   463,   464,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,   465,   245,   460,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,   247,   248,
     249,     0,     0,     0,   235,  1061,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,   462,     0,
       0,     0,     0,     0,     0,   463,   464,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,   465,     0,   460,
     108,   109,   110,   111,   112,   113,   114,     0,   247,   248,
     249,     0,     0,     0,     0,     0,   235,  1077,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
     462,     0,     0,     0,     0,     0,     0,   463,   464,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,   465,   245,   460,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
     247,   248,   249,     0,     0,     0,   235,  1081,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
     462,     0,     0,     0,     0,     0,     0,   463,   464,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,   465,
       0,   460,   108,   109,   110,   111,   112,   113,   114,     0,
     247,   248,   249,     0,     0,     0,     0,     0,   235,  1085,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,   465,
     245,   460,   108,   109,   110,   111,   112,   113,   114,     0,
       0,  1091,   247,   248,   249,     0,     0,     0,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   461,   462,     0,     0,     0,     0,     0,     0,   463,
     464,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,     0,
     245,   465,     0,   460,   108,   109,   110,   111,   112,   113,
     114,     0,   247,   248,   249,     0,     0,     0,     0,     0,
     235,  1096,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,   465,   245,   460,   108,   109,   110,   111,   112,   113,
     114,     0,     0,  1117,   247,   248,   249,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   461,   462,     0,     0,     0,     0,     0,
       0,   463,   464,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,     0,   245,   465,     0,   460,   108,   109,   110,   111,
     112,   113,   114,     0,   247,   248,   249,     0,     0,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   461,   462,     0,     0,     0,
       0,     0,     0,   463,   464,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,   465,   245,   460,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   247,   248,   249,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   461,   462,     0,     0,     0,
       0,     0,     0,   463,   464,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,   465,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   247,   248,   249,   233,
     108,   109,   110,   111,   112,   113,   114,     0,     0,   745,
       0,     0,     0,     0,     0,     0,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   233,
     108,   109,   110,   111,   112,   113,   114,     0,     0,  1057,
       0,     0,     0,   236,   237,   492,   235,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,     0,
       0,     0,     0,     0,     0,     0,   746,     0,     0,     0,
     247,   248,   249,   236,   237,   252,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,     0,
       0,     0,     0,     0,     0,     0,   746,     0,     0,     0,
     247,   248,   249,     0,     0,   252,   460,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,     0,     0,   465,
       0,     0,     0,   235,   971,     0,     0,     0,     0,   460,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   235,  1026,     0,   465,
     236,   237,     0,     0,     0,     0,     0,   238,   239,   240,
     241,   242,   243,   244,     0,   245,     0,     0,     0,     0,
       0,     0,     0,   236,   237,     0,     0,   247,   248,   249,
     238,   239,   240,   241,   242,   243,   244,     0,   245,   460,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
     247,   248,   249,     0,     0,     0,   235,  1029,     0,     0,
       0,     0,   460,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,     0,     0,     0,   465,     0,     0,   235,
    1072,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,   465,
       0,     0,     0,     0,     0,     0,   236,   237,     0,     0,
     247,   248,   249,   238,   239,   240,   241,   242,   243,   244,
       0,   245,   460,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,   247,   248,   249,     0,     0,     0,   235,
    1113,     0,     0,     0,     0,   460,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,   465,
       0,     0,   235,  1127,     0,     0,   236,   237,     0,     0,
       0,     0,     0,   238,   239,   240,   241,   242,   243,   244,
       0,   245,   465,     0,     0,     0,     0,     0,     0,   236,
     237,     0,     0,   247,   248,   249,   238,   239,   240,   241,
     242,   243,   244,     0,   245,   460,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   247,   248,   249,     0,
       0,     0,   235,  1130,     0,     0,     0,     0,   460,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,     0,
       0,     0,   465,     0,     0,   235,  1140,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,   465,     0,     0,     0,     0,
       0,     0,   236,   237,     0,     0,   247,   248,   249,   238,
     239,   240,   241,   242,   243,   244,     0,   245,   460,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,   247,
     248,   249,     0,     0,     0,   235,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   465,     0,     0,     0,     0,
       0,     0,   236,   237,     0,     0,     0,     0,     0,   238,
     239,   240,   241,   242,   243,   244,     0,   245,   465,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   247,
     248,   249,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   465
};

static const yytype_int16 yycheck[] =
{
      29,   236,   237,   246,   212,   288,   233,   530,   502,   530,
     236,   237,   325,   447,    68,   666,   227,   330,   119,   324,
     521,   232,     0,   686,   687,   327,    74,    12,   529,    10,
       0,    23,    14,    13,    36,   262,   567,    69,   539,    68,
     504,   505,    13,   530,    14,    26,    16,    76,    77,    78,
      79,    13,    81,   130,    83,    18,    85,    20,   329,    22,
      68,   332,    16,    16,   293,    62,   337,   324,     3,     4,
       5,     6,     7,     8,     9,    10,   130,    74,    40,   133,
     134,    44,   130,    16,   355,    67,   134,   358,    16,   118,
      16,   123,   146,   147,    18,   149,    36,   123,    68,   328,
      18,   130,   331,    16,    74,   134,    18,    76,    62,   163,
     139,   165,    16,   161,    16,   144,   345,   551,    18,   330,
      74,   123,    76,    76,    18,    14,   134,   658,    62,    64,
      65,   123,   361,    68,    69,    70,    71,    72,   123,    16,
     169,   170,   171,   123,   173,   174,    68,   176,    76,    62,
      76,   974,   123,   976,   123,   184,   185,   186,   187,    62,
      23,    74,   125,    76,   134,   194,   195,   196,   197,   123,
     123,   442,   226,    16,   228,   204,   205,   206,   207,   842,
      16,   844,    16,   123,     0,    62,   123,    13,   123,   123,
     123,   161,   246,   657,   688,   123,   118,   123,    14,    76,
      16,   125,    62,   236,   237,    14,    74,   125,  1031,    98,
     123,   288,   134,   125,   315,   316,     0,   139,    44,   123,
     123,   123,    13,    23,   123,   125,   461,   462,   463,   464,
      14,   125,    16,   460,   288,   461,   462,   463,   464,   466,
     288,   498,   499,   774,   130,   709,   123,   324,   712,   551,
      16,    17,    68,    44,   224,   236,   237,   562,    74,   288,
     123,   574,    14,   123,   521,   766,   767,   768,  1091,   526,
     324,   500,   529,   327,    74,    22,   324,    12,   561,   930,
     123,   538,   539,    22,    68,   708,   520,   123,   711,   123,
      74,    16,  1115,   161,  1117,   324,   325,    44,    74,    14,
     329,   330,    18,   332,    20,    44,    22,    73,   337,  1132,
      45,    16,   208,    11,    66,    67,    44,    14,   134,    17,
      11,    18,    18,   123,    40,    20,   355,    22,    44,   358,
      21,    47,    48,   873,   363,   364,    61,   366,   549,   550,
     369,    66,    67,   324,   778,   161,    61,   123,    44,    44,
     134,    66,    67,   249,   383,   384,   385,    62,   387,   388,
     824,   390,    18,    11,   858,   859,    20,   861,    22,    22,
      14,    76,    16,    21,   403,   404,   405,   161,   407,   408,
      11,   410,   653,   654,   655,   656,    17,    11,    44,   130,
      44,    44,   826,   447,   423,   424,   425,    21,   427,   428,
     887,   430,   288,    22,   891,     0,   123,   329,   224,   125,
     332,    13,    14,   442,    11,   337,    13,    61,   123,    14,
     123,    16,    66,    67,    21,    44,   455,    11,   461,   462,
     463,   464,    11,   355,    13,   123,   358,    21,   324,   123,
     224,   649,    21,   520,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   530,   689,   690,   691,   692,   693,   694,
     695,   696,   896,   927,    11,    11,   123,    11,   694,   695,
     696,   123,  1012,    68,    21,    21,   530,    21,   123,    74,
     461,   462,   463,   464,   561,   562,   123,   974,   771,   976,
    1013,   520,  1013,   123,    63,    64,    65,   551,    18,    68,
      69,    70,    11,   746,    13,    11,    11,   561,   562,   766,
     767,   768,   566,   561,   562,    21,    21,    47,    48,    88,
     442,    11,    91,   123,    44,   130,  1013,    47,    48,    61,
      11,    21,   561,   562,   103,    11,    11,  1001,    11,   134,
      21,    11,    11,    11,  1031,   574,    21,   288,    21,  1089,
    1090,    21,    21,    21,    47,    48,   585,    11,     3,     4,
       5,     6,     7,     8,     9,    10,   161,    21,    11,    11,
      11,   600,   601,  1113,   603,    20,    11,   606,    21,    21,
      21,    47,    48,   324,  1124,    11,  1126,  1127,    11,  1129,
    1130,   620,   621,    11,   623,    21,  1136,   626,    21,  1139,
    1140,    52,    53,    21,  1091,  1145,    11,   842,   123,   844,
     818,   640,   641,    11,   643,    26,    21,   646,   666,   876,
     877,    11,    11,    21,   653,   654,   655,   656,  1115,    20,
    1117,    21,    21,    11,   520,   709,   123,   666,   712,   873,
     874,    33,    34,    21,   530,  1132,   679,   680,   681,   682,
     683,   684,   685,   686,   687,    11,   689,   690,   691,   692,
     693,   694,   695,   696,    13,    21,   146,   147,   148,    20,
     150,    35,    36,    37,   130,   561,   562,   157,   123,   708,
      61,    62,   711,   288,   123,   165,   166,   167,    11,  1012,
      13,    11,   746,    13,   771,    11,   931,    13,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   123,   689,   690,
     691,   692,   693,   694,   695,   696,    11,   771,    13,   324,
      49,    50,    51,   771,   778,   779,   684,   685,   689,   690,
     691,   653,   654,   655,   656,    98,    18,   971,    20,    14,
      22,    16,   771,    27,   224,    27,    28,    29,    30,    31,
      32,   125,     3,     4,     5,     6,     7,     8,     9,    10,
     692,   693,    44,    20,   793,    16,  1089,  1090,    20,    22,
      20,    20,   826,    18,   803,    13,   123,    13,  1012,   520,
    1014,    20,    13,   831,   813,    43,    11,    43,    18,   530,
    1113,  1025,  1026,    19,  1028,  1029,   873,   874,    19,    21,
      46,  1124,    39,  1126,  1127,    38,  1129,  1130,    43,   842,
     887,   844,    20,  1136,   891,    18,  1139,  1140,   123,    20,
     561,   562,  1145,    13,    75,    27,    28,    29,    30,    31,
      32,    13,   288,    13,  1068,    13,    13,  1071,  1072,    18,
      11,   123,   896,   125,   873,   874,    63,    64,    65,    11,
      20,    68,    69,    70,    11,  1089,  1090,    43,    19,    44,
      20,   842,   130,   844,    19,    21,    29,  1101,   324,   123,
      24,    88,   123,    20,    91,    29,    63,    64,    65,  1113,
     123,    68,    69,    70,    20,   771,   103,    21,    19,   123,
    1124,    20,  1126,  1127,   971,  1129,  1130,   974,   931,   976,
      63,   930,  1136,    19,   123,  1139,  1140,   873,    20,    13,
      40,  1145,    11,    76,    68,   520,   103,    80,    81,    82,
      83,    84,    85,   123,    20,   530,    80,    81,    82,    83,
      84,    85,   123,    19,    11,  1012,  1013,  1014,    63,    64,
      65,    74,   971,    68,    69,    70,    20,    20,  1025,  1026,
     931,  1028,  1029,    15,  1031,   123,   561,   562,    11,  1013,
      40,    20,    19,   443,   444,   445,   446,     3,     4,     5,
       6,     7,     8,     9,    10,    13,    20,    20,    13,    20,
     134,    13,    18,  1012,    20,  1014,    13,   873,   874,    20,
      20,  1068,   146,    85,  1071,  1072,  1025,  1026,    20,  1028,
    1029,   887,   123,    20,    20,   891,    27,    28,    29,    30,
      31,    32,  1089,  1090,  1091,   178,    85,   123,    20,    13,
     288,   184,   123,    21,  1101,   188,    21,    13,    13,    20,
     771,   194,    20,    20,    13,   198,  1113,    13,  1115,  1068,
    1117,   204,  1071,  1072,    21,    20,  1012,  1124,    21,  1126,
    1127,   130,  1129,  1130,    13,  1132,   324,    13,    13,  1136,
    1089,  1090,  1139,  1140,   520,    13,    13,    21,  1145,    21,
      40,    13,  1101,    13,   530,     3,     4,     5,     6,     7,
       8,     9,    10,    21,  1113,   971,    13,   123,   974,    13,
     976,    13,    18,    13,    20,  1124,    22,  1126,  1127,    13,
    1129,  1130,    13,    13,    13,   561,   562,  1136,    13,    21,
    1139,  1140,    13,    85,    40,    21,  1145,    21,    44,    21,
     210,    47,    48,  1089,  1090,    21,  1012,  1013,  1014,   249,
     134,   453,   873,   874,   507,   161,   324,   505,   931,  1025,
    1026,   679,  1028,  1029,   680,  1031,   887,  1113,   681,   683,
     891,    79,    27,    28,    29,    30,    31,    32,  1124,   682,
    1126,  1127,   763,  1129,  1130,   779,   771,  1013,   146,   133,
    1136,   861,   224,  1139,  1140,    -1,    -1,    -1,    -1,  1145,
      18,    -1,  1068,    -1,    -1,  1071,  1072,    -1,    -1,    27,
      28,    29,    30,    31,    32,   123,   130,   123,    -1,   125,
      -1,    -1,    -1,  1089,  1090,  1091,    44,    -1,    -1,   288,
      -1,    -1,    -1,    -1,    -1,  1101,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,  1113,    -1,  1115,
     971,  1117,    -1,   974,    21,   976,    -1,    -1,  1124,    -1,
    1126,  1127,    -1,  1129,  1130,   324,  1132,    -1,    -1,    -1,
    1136,    -1,   520,  1139,  1140,    -1,    -1,    -1,    -1,  1145,
      -1,    -1,   530,    -1,    -1,    -1,    -1,    -1,   873,   874,
      -1,  1012,  1013,  1014,     3,     4,     5,     6,     7,     8,
       9,    10,   887,    70,  1025,  1026,   891,  1028,  1029,    -1,
    1031,    -1,    21,   561,   562,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,   771,    -1,    -1,    25,    63,
      64,    65,    -1,    -1,    68,    69,    70,  1068,    -1,    -1,
    1071,  1072,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    88,    -1,    -1,    91,  1089,  1090,
    1091,    -1,    -1,    -1,   288,    -1,    63,    64,    65,    -1,
    1101,    68,    69,    70,    -1,    -1,   971,    -1,    75,   974,
      -1,   976,  1113,    -1,  1115,    -1,  1117,    -1,    -1,    -1,
      -1,    88,    -1,  1124,    91,  1126,  1127,   713,  1129,  1130,
     324,  1132,    -1,    -1,   123,  1136,   103,    -1,  1139,  1140,
      -1,    -1,    -1,    -1,  1145,    -1,    -1,  1012,  1013,  1014,
      -1,    -1,    -1,    -1,    -1,    -1,   123,   873,   874,    -1,
    1025,  1026,    -1,  1028,  1029,    -1,  1031,    63,    64,    65,
      -1,   887,    68,    69,    70,   891,    -1,    -1,   764,   765,
      -1,   520,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,   530,    88,    -1,    -1,    91,    -1,    -1,    -1,    -1,
      21,    -1,    -1,  1068,    -1,    -1,  1071,  1072,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,   561,   562,  1089,  1090,  1091,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,  1101,    -1,    -1,    -1,
      -1,    16,    -1,   771,    -1,    -1,    -1,    -1,  1113,    70,
    1115,    -1,  1117,    -1,    -1,   971,    -1,    -1,   974,  1124,
     976,  1126,  1127,   235,  1129,  1130,    -1,  1132,    -1,    -1,
     856,  1136,    -1,    -1,  1139,  1140,    -1,    -1,   250,   251,
    1145,    -1,    75,   255,   256,   871,    -1,    -1,    63,    64,
      65,    -1,   878,    68,    69,    70,  1012,  1013,  1014,   885,
      75,    -1,   123,    -1,    -1,    -1,    -1,   893,    -1,  1025,
    1026,    -1,  1028,  1029,    -1,  1031,     3,     4,     5,     6,
       7,     8,     9,    10,   910,   911,   520,    -1,   103,    16,
     123,    -1,    -1,    -1,    -1,    18,   530,    20,    -1,    22,
      -1,    -1,    -1,    -1,    -1,   873,   874,    -1,   123,    -1,
     936,    -1,  1068,    -1,    -1,  1071,  1072,    40,    -1,   887,
      -1,    44,    -1,   891,    47,    48,    -1,   561,   562,    -1,
      -1,    -1,    -1,  1089,  1090,  1091,    63,    64,    65,    -1,
     966,    68,    69,    70,   970,  1101,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,   981,    -1,  1113,    -1,  1115,
      -1,  1117,   988,    -1,   990,    -1,   992,    -1,  1124,    -1,
    1126,  1127,    -1,  1129,  1130,    -1,  1132,    -1,    -1,    -1,
    1136,    -1,    -1,  1139,  1140,    -1,    -1,    -1,    -1,  1145,
    1016,    -1,   771,    -1,    -1,    -1,   123,    -1,    -1,    -1,
     123,    -1,   125,   971,    -1,    -1,   974,    -1,   976,    -1,
      -1,    -1,    -1,    -1,  1040,    -1,    -1,  1043,    -1,    -1,
    1046,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,  1063,    -1,    16,
      -1,    -1,    -1,   455,  1012,  1013,  1014,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,  1025,  1026,    -1,
    1028,  1029,    -1,  1031,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    70,   873,   874,    -1,    -1,    75,    -1,
    1068,    -1,    -1,  1071,  1072,   517,   518,   519,   887,    -1,
      -1,    88,   891,    -1,    91,    -1,   528,    -1,    -1,    75,
      -1,  1089,  1090,  1091,    -1,   537,   103,    -1,   540,    63,
      64,    65,    -1,  1101,    68,    69,    70,   771,    -1,    -1,
      -1,    75,    -1,    -1,    -1,  1113,   123,  1115,    -1,  1117,
      -1,    -1,    -1,    -1,    88,    -1,  1124,    91,  1126,  1127,
      -1,  1129,  1130,    -1,  1132,    -1,    -1,   123,  1136,    -1,
      -1,  1139,  1140,    -1,    -1,    -1,    -1,  1145,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,   123,
      -1,    -1,   971,    -1,    -1,   974,    21,   976,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    -1,  1012,  1013,  1014,    -1,    -1,    -1,   873,
     874,    -1,    -1,    -1,    -1,    70,  1025,  1026,    -1,  1028,
    1029,    -1,  1031,   887,   666,    -1,    -1,   891,    -1,    64,
      65,    -1,    -1,    68,    69,    70,   678,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    70,    71,    72,    -1,    -1,    75,    -1,  1068,
      -1,    -1,  1071,  1072,    -1,   707,    -1,    -1,   123,    -1,
      88,    89,    90,    91,    -1,    -1,   718,    -1,    -1,    -1,
    1089,  1090,  1091,    -1,    -1,   103,    -1,    -1,   123,    -1,
      -1,    -1,  1101,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    13,   745,  1113,   123,  1115,   971,  1117,    -1,
     974,    21,   976,    -1,    -1,  1124,    -1,  1126,  1127,    -1,
    1129,  1130,    -1,  1132,    -1,    -1,    -1,  1136,    -1,    -1,
    1139,  1140,    -1,    -1,    -1,    -1,  1145,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,  1012,  1013,
    1014,    16,    63,    64,    65,    -1,    -1,    68,    69,    70,
      70,  1025,  1026,    -1,  1028,  1029,    -1,  1031,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    88,    -1,    13,
      91,    15,    16,    -1,    -1,    -1,    97,    -1,    -1,    -1,
      -1,    25,   103,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,  1068,    68,    -1,  1071,  1072,    -1,
      -1,    74,    -1,   123,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,  1089,  1090,  1091,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,  1101,    -1,    -1,
     882,    75,    -1,    -1,    -1,    -1,    -1,   889,   890,  1113,
      -1,  1115,    -1,  1117,    88,    -1,    -1,    91,   123,    93,
    1124,    -1,  1126,  1127,    -1,  1129,  1130,   130,  1132,    -1,
     133,   134,  1136,    -1,    -1,  1139,  1140,    -1,    -1,    -1,
      -1,  1145,    -1,   146,   147,   148,   149,   150,   930,   123,
      -1,    -1,    -1,    -1,   157,    -1,    -1,    -1,   161,    -1,
     163,    -1,   165,   166,   167,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    21,    -1,    68,
      -1,    -1,    -1,    -1,   123,    74,    80,    -1,    82,    -1,
      84,    -1,    -1,    -1,    -1,   208,    -1,    -1,    -1,   212,
      -1,    -1,    -1,    97,    98,    99,    -1,   101,   102,    -1,
     104,   224,    -1,   226,    -1,   228,    -1,    -1,  1010,  1011,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    -1,   246,    -1,    -1,   249,    -1,    -1,    -1,
      -1,   130,    -1,    -1,   133,   134,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,   146,   147,   148,
     149,   150,    -1,    -1,    -1,  1057,    -1,    -1,   157,    -1,
      -1,    -1,   161,    -1,   163,   288,   165,   166,   167,   123,
      -1,    -1,    -1,    -1,   178,   179,   180,   181,    -1,    -1,
      -1,    -1,    -1,    -1,   188,   189,   190,   191,    -1,    -1,
      -1,  1093,  1094,    -1,   198,   199,   200,   201,    -1,    -1,
     323,   324,    -1,    70,   327,    -1,    -1,    -1,    -1,    -1,
     214,   215,    -1,   217,    -1,    -1,   220,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   224,    -1,   226,    -1,   228,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    16,    -1,    -1,   246,    20,    -1,
     249,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    47,    48,    -1,    16,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   288,
      62,    63,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    86,    87,    88,    -1,    -1,    91,
     443,   444,   445,   446,   447,   324,    64,    65,   327,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    75,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      88,   123,    16,    91,    -1,    -1,    -1,    76,    77,    78,
      79,    -1,    81,    -1,    83,    -1,    85,    -1,   372,   373,
     374,    -1,   376,   377,    -1,   379,    -1,    -1,    -1,   502,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,   392,   393,
     394,    -1,   396,   397,    -1,   399,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,   530,   412,   413,
     414,    75,   416,   417,    -1,   419,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,   551,    -1,
      -1,    -1,    -1,   437,    -1,    -1,    -1,    -1,   561,   562,
      -1,    -1,    -1,   566,   443,   444,   445,   446,   447,    -1,
     169,   170,   171,    -1,   173,   174,    -1,   176,    -1,   123,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,   187,    -1,
      -1,    -1,    -1,    -1,    -1,   194,   195,   196,   197,    -1,
      -1,    -1,    -1,    -1,    -1,   204,   205,   206,   207,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    14,    15,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,   649,    -1,    -1,    -1,
      -1,   530,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,   551,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   561,   562,    -1,   688,    -1,   566,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   589,   590,    -1,   592,    -1,
      -1,   595,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   609,   610,    -1,   612,    -1,
      -1,   615,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,   746,    -1,   629,   630,    -1,   632,    -1,
      -1,   635,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     763,    -1,    13,    -1,   363,   364,    -1,   366,   771,    -1,
     369,    -1,    -1,    -1,    -1,   778,   779,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   383,   384,   385,    -1,   387,   388,
      -1,   390,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   403,   404,   405,    -1,   407,   408,
      -1,   410,    63,    64,    65,   818,    -1,    68,    69,    70,
      -1,    -1,    -1,   826,   423,   424,   425,    -1,   427,   428,
      -1,   430,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,
      -1,    -1,   103,    -1,    -1,   858,   859,    -1,   861,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   746,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,   771,   896,    -1,    -1,    16,    -1,    -1,   778,
     779,    -1,    -1,   787,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   797,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   807,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    64,    65,    -1,   826,    68,    69,
      70,    -1,    76,    77,    78,    75,    80,    81,    82,    83,
      84,    85,    63,    64,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    97,    98,    76,    77,   101,    -1,    80,
      81,    82,    83,    84,    85,   869,   585,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,
      -1,   600,   601,   123,   603,    -1,    -1,   606,    -1,    -1,
    1013,    -1,    -1,    -1,    -1,    -1,    -1,   896,    -1,    -1,
      -1,   620,   621,    -1,   623,    -1,    -1,   626,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   640,   641,    -1,   643,   169,   170,   646,    -1,   173,
      -1,    -1,    -1,    -1,   178,   179,   180,    -1,   942,   943,
     184,   185,   186,    -1,   188,   189,   190,    -1,   169,    -1,
     194,   195,   196,    -1,   198,   199,   200,   178,   179,    -1,
     204,   205,   206,   184,   185,    -1,    -1,   188,   189,    -1,
     214,    -1,    -1,   194,   195,    -1,    -1,   198,   199,    -1,
      -1,    -1,    -1,   204,   205,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    15,    -1,    -1,
      -1,    -1,    20,    -1,    -1,  1009,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1013,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    63,    64,    65,    -1,    -1,
      68,    69,    70,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    86,    87,
      88,    -1,    -1,    91,   793,    -1,    64,    65,    -1,    -1,
      68,    69,    70,    -1,   803,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    -1,    -1,   813,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   363,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,   373,
      -1,    -1,   376,    -1,    -1,   123,    -1,    -1,    -1,   383,
     384,    -1,    -1,   387,    -1,    -1,    -1,    -1,   392,   393,
      -1,   372,   396,    -1,    -1,    -1,    -1,    -1,    -1,   403,
     404,    -1,   383,   407,    -1,    -1,    -1,    -1,   412,   413,
      -1,   392,   416,    -1,    -1,    -1,    -1,    -1,    -1,   423,
     424,    -1,   403,   427,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   412,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,   423,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    47,    48,    -1,
      16,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,
      80,    81,    82,    83,    84,    -1,    86,    87,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    64,    65,
      13,    14,    68,    69,    70,    -1,    -1,    20,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,   123,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    -1,    -1,    -1,    -1,   589,    -1,   123,    -1,    -1,
      -1,    74,    75,    76,    77,    78,   600,    80,    81,    82,
      83,    84,    -1,    86,    87,   609,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,   620,    13,    13,    -1,
      -1,    -1,    -1,    -1,    20,   629,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   640,    33,    34,    -1,
     123,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    70,    -1,    -1,    74,    75,
      76,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    14,    88,    -1,    -1,    91,    -1,    20,    -1,
      -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,   103,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,   123,    -1,    -1,
      -1,   126,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,   123,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   123,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,   123,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,   123,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,   123,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,   123,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    74,    75,
      76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,   123,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,   123,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,   123,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   123,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,   123,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   123,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,   123,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,   123,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,   123,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,   123,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,   123,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   123,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,   123,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   123,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,   123,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,   123,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,   123,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,   123,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,   123,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,   123,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,   123,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   123,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    74,    75,    76,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,   123,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   123,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    74,    75,    76,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,   123,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,   123,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      -1,    -1,    -1,    47,    48,   123,    20,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      74,    75,    76,    47,    48,    79,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    79,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,   123,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    74,    75,    76,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    20,
      21,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,   123,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      74,    75,    76,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    20,    21,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   123,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    74,    75,    76,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    20,    21,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,   123,    -1,    -1,    20,    21,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    74,    75,    76,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,    13,    63,    64,    65,    68,    69,    70,    88,    91,
      97,   103,   126,   128,   141,   142,   143,   144,   145,   147,
     154,   270,   271,   272,   123,   146,    69,   123,   140,   123,
       0,   126,   142,   142,    63,    64,    65,    68,    69,    70,
     103,    63,    64,    65,    68,    69,    70,    88,    91,   103,
      63,    64,    65,    68,    69,    70,    88,    91,   103,    16,
      61,    66,    67,   155,   160,   161,   163,    14,   149,   165,
     140,    44,    13,    44,   149,   151,   155,   160,   161,   163,
     123,   123,   123,   123,   123,   123,   123,   156,   157,   123,
     136,   137,   136,   162,   280,   123,   164,   160,   161,   163,
     165,   161,   163,   165,   163,   165,   165,     3,     4,     5,
       6,     7,     8,     9,    10,    13,    15,    25,    69,    75,
     123,   129,   130,   131,   132,   133,   134,   135,   136,   144,
     149,   150,   154,   155,   166,   167,   168,   169,   217,   218,
     228,   229,   230,   265,   266,   267,   270,   271,   272,   273,
     274,    13,    44,   123,    36,   123,    13,    93,   129,   144,
     150,   152,   153,   155,   217,   270,   271,   272,   151,   160,
     161,   163,   151,   161,   163,   151,   163,   151,   155,   160,
     161,   163,   165,   151,   155,   160,   161,   163,   155,   160,
     161,   163,   165,   151,   155,   160,   161,   163,   155,   160,
     161,   163,   165,   151,   155,   160,   161,   163,    61,   158,
      11,    17,    11,    11,   161,   163,   165,   163,   165,   165,
     163,   165,   165,   165,    26,   230,   123,   222,   123,   170,
     171,   172,   222,     3,    13,    20,    47,    48,    54,    55,
      56,    57,    58,    59,    60,    62,    70,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    86,    87,
     123,   129,   131,   136,   139,   140,   144,   148,   150,   176,
     177,   179,   180,   181,   182,   183,   185,   186,   189,   190,
     191,   197,   210,   211,   213,   214,   215,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   256,   257,
     258,   260,   270,   271,   272,    75,   129,   267,   150,   167,
      13,   227,   230,    98,   149,   219,   268,    20,   129,   218,
     266,   129,   218,    71,    72,    89,    90,   218,    64,    65,
      68,    69,    70,    71,    72,   129,    64,    65,    68,    69,
      70,    88,    89,    90,    91,   218,    36,    13,   218,   150,
     153,   129,   151,   161,   163,   151,   163,   151,   151,   163,
     151,   151,   160,   161,   163,   165,   161,   163,   165,   163,
     165,   165,   151,   160,   161,   163,   151,   161,   163,   151,
     163,   151,   160,   161,   163,   165,   161,   163,   165,   163,
     165,   165,   151,   160,   161,   163,   151,   161,   163,   151,
     163,   151,   160,   161,   163,   165,   161,   163,   165,   163,
     165,   165,   151,   160,   161,   163,   151,   161,   163,   151,
     163,   151,   123,   135,   157,   280,   123,   163,   165,   165,
     165,   165,   218,   270,   271,   272,   274,    20,   129,   223,
     219,    18,   138,    11,    13,    27,   219,    18,   125,   184,
       3,    33,    34,    41,    42,   123,   131,   136,   174,   175,
     176,   185,   189,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   123,   140,   179,   197,   209,   209,    22,    44,
     236,   125,    16,   123,   130,   135,   187,   275,   174,   174,
      13,   123,    13,   123,    13,   174,   174,    20,    20,    18,
      40,    44,   125,   184,   125,   184,    22,    20,    18,    44,
      20,    27,    28,    29,    30,    31,    32,   178,    22,    44,
      18,    47,    48,   150,   232,    13,   123,   170,    13,   222,
     222,    20,   136,   220,   221,    62,    74,   123,   140,   150,
     180,   231,   269,   275,   268,    21,    70,   129,   223,   224,
     225,   226,   170,   227,   219,   268,   170,   227,   227,   170,
     227,    13,   227,   170,   151,   163,   151,   151,   151,   161,
     163,   165,   163,   165,   165,   163,   165,   165,   165,   151,
     161,   163,   151,   163,   151,   151,   163,   151,   151,   161,
     163,   165,   163,   165,   165,   163,   165,   165,   165,   151,
     161,   163,   151,   163,   151,   151,   163,   151,   151,   161,
     163,   165,   163,   165,   165,   163,   165,   165,   165,   151,
     161,   163,   151,   163,   151,   151,   163,   151,   151,    43,
     159,   165,   227,   218,   218,   218,   218,    21,   129,   224,
      74,   123,    11,    19,    18,   171,   149,   173,   174,   192,
      19,    18,   125,   209,   209,   209,   209,    21,    12,    45,
      46,    38,    39,    43,    52,    53,    16,    17,    73,    49,
      50,    51,    33,    34,    35,    36,    37,   123,   275,   123,
     275,   170,    12,   134,   276,   277,   278,    18,   138,   194,
     195,   138,   194,    20,   123,   187,    13,    13,    40,    13,
      13,    13,    13,   174,   174,   174,   237,    62,    74,    76,
     123,   186,   275,   125,   125,    76,   123,   275,    21,   174,
     188,   174,   123,   186,   275,    13,    70,   235,   241,   262,
     264,   174,   123,   275,   123,   186,   275,   174,   219,   219,
      21,   223,   224,    11,    20,    20,    44,    44,    44,   150,
     150,   231,    62,    74,   129,    23,   123,   172,    11,    11,
      21,    13,   268,    13,    13,    13,   151,   163,   165,   165,
     165,   165,   151,   163,   151,   151,   151,   163,   165,   165,
     165,   165,   151,   163,   151,   151,   151,   163,   165,   165,
     165,   165,   151,   163,   151,   151,   151,   280,    43,   227,
     227,   227,   227,   138,    21,    44,    20,    19,    11,   150,
     173,   193,   196,    19,   174,   200,   201,   202,   203,   204,
     205,   205,    27,   206,    27,   206,   134,   207,   207,   207,
     208,   208,   209,   209,   209,   123,    20,   123,    61,    62,
     279,    11,    17,   174,   192,   138,   195,   192,   138,    21,
     188,    20,   174,    21,    21,    19,    22,    44,    20,   123,
      76,   123,    11,    21,    19,    20,   123,    13,   174,    40,
      13,    11,   123,    20,   123,    19,    11,    21,   221,    21,
     188,    21,   188,    62,   275,    62,   275,    62,   275,   150,
      20,    20,    23,   172,   123,    21,   224,   225,   165,   151,
     165,   151,   165,   151,   280,   138,    74,    21,   224,   150,
      11,    40,   206,   206,    21,   188,    20,   134,   134,   277,
      19,   165,    21,    21,   188,    13,    84,    86,   123,   148,
     237,   238,   251,   252,   253,   254,   255,   259,   261,   237,
     123,   275,   123,   275,    21,   188,    20,   174,    21,   188,
      20,    21,   263,   264,    13,   174,    13,   174,   241,    21,
     188,    20,    21,   224,    13,    21,    13,    21,    20,    62,
      20,    62,    20,    62,    21,   188,    21,   188,   123,    21,
     138,    21,   173,   198,    21,    21,   188,   165,   165,    21,
      20,    20,    40,    20,    85,   123,    20,   123,    21,    21,
     188,    21,    21,   188,   237,    21,    21,   263,    21,    21,
     263,    13,    21,    21,   188,    21,    13,    13,    21,   188,
      20,    21,   188,    20,    21,   188,    20,    13,    21,    13,
      21,   138,    21,   165,   174,   174,   252,    13,   235,   262,
     237,    21,   188,    20,    21,    21,   237,   237,    21,   237,
     237,    21,    21,   263,    21,    13,    21,    21,   188,    13,
      21,    21,   188,    13,    21,    21,   188,    13,    13,    21,
      21,    13,   174,    40,    13,    21,    21,   188,   237,   237,
     237,    21,    13,    13,    21,    13,    13,    21,    13,    13,
      21,   252,   252,    21,   263,    13,   174,    13,   174,    21,
     237,    13,    13,    13,    85,   252,    21,    21,   263,    21,
      21,   263,    13,   252,   252,   252,    21,   252,   252,    21,
      21,   263,   252,   252,   252,    21,   252
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   127,   128,   128,   129,   129,   130,   130,   131,   131,
     132,   132,   132,   132,   132,   133,   133,   134,   135,   136,
     137,   138,   138,   139,   140,   140,   141,   141,   142,   142,
     142,   142,   143,   143,   143,   143,   144,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   146,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   148,   149,   150,   151,
     151,   152,   152,   153,   153,   153,   153,   153,   154,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   160,   161,
     162,   162,   163,   164,   164,   165,   165,   166,   166,   167,
     167,   167,   167,   168,   168,   168,   168,   168,   169,   169,
     169,   169,   170,   170,   171,   171,   172,   172,   173,   173,
     174,   175,   175,   176,   177,   177,   177,   177,   178,   178,
     178,   178,   178,   178,   179,   179,   179,   180,   180,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   182,
     182,   182,   182,   182,   182,   182,   183,   183,   183,   183,
     183,   183,   183,   184,   184,   185,   185,   185,   185,   186,
     186,   186,   186,   186,   186,   186,   186,   187,   188,   188,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   192,   192,   193,   193,   193,   194,   194,   195,
     196,   196,   197,   197,   197,   198,   198,   199,   199,   200,
     200,   201,   201,   202,   202,   203,   203,   204,   204,   204,
     205,   205,   205,   205,   205,   205,   206,   206,   206,   206,
     207,   207,   207,   208,   208,   208,   208,   209,   209,   209,
     209,   209,   210,   211,   212,   212,   212,   213,   213,   213,
     213,   213,   214,   215,   216,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   218,   218,   218,   218,   218,
     218,   218,   218,   219,   220,   220,   221,   222,   222,   222,
     222,   222,   222,   222,   222,   223,   223,   224,   224,   225,
     225,   225,   226,   226,   227,   227,   228,   229,   230,   230,
     231,   231,   232,   232,   232,   233,   234,   235,   235,   236,
     236,   237,   237,   237,   237,   237,   237,   238,   238,   238,
     238,   238,   238,   238,   238,   238,   239,   240,   241,   241,
     241,   241,   241,   241,   241,   242,   242,   243,   243,   244,
     244,   245,   245,   246,   247,   248,   249,   250,   251,   252,
     252,   252,   252,   252,   253,   254,   255,   255,   256,   257,
     257,   258,   258,   258,   258,   258,   258,   258,   258,   259,
     259,   259,   259,   259,   259,   259,   259,   260,   261,   262,
     262,   263,   264,   264,   265,   265,   265,   265,   266,   266,
     266,   266,   266,   266,   266,   266,   267,   268,   268,   268,
     268,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   270,   270,   270,   270,   270,   270,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   275,   276,   276,
     277,   277,   278,   278,   279,   279,   280
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
       1,     2,     1,     1,     1,     1,     2,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     5,     2,     3,     2,
       3,     3,     2,     3,     3,     3,     5,     7,     7,     1,
       1,     1,     1,     1,     3,     5,     1,     1,     5,     1,
       1,     6,     7,     7,     8,     7,     8,     8,     9,     6,
       7,     7,     8,     7,     8,     8,     9,     7,     7,     1,
       1,     1,     1,     3,     3,     2,     4,     3,     3,     4,
       5,     6,     4,     5,     6,     7,     1,     4,     3,     3,
       2,     4,     5,     5,     6,     4,     5,     5,     6,     6,
       7,     7,     8,     6,     7,     7,     8,     6,     7,     7,
       8,     1,     1,     1,     2,     2,     2,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     1,     3,
       1,     1,     1,     2,     2,     2,     1
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
#line 239 "parser_1st.y"
                              {return 0;}
#line 3423 "parser_1st.tab.c"
    break;

  case 3: /* COMPILATIONUNIT: ORDINARYCOMPILATIONUNIT EOFF  */
#line 240 "parser_1st.y"
                                                     {
                    
                    return 0;
                }
#line 3432 "parser_1st.tab.c"
    break;

  case 4: /* TYPE: PRIMITIVETYPE  */
#line 245 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3438 "parser_1st.tab.c"
    break;

  case 5: /* TYPE: REFERENCETYPE  */
#line 246 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3444 "parser_1st.tab.c"
    break;

  case 6: /* PRIMITIVETYPE: NUMERICTYPE  */
#line 248 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3450 "parser_1st.tab.c"
    break;

  case 7: /* PRIMITIVETYPE: BOOLEAN  */
#line 249 "parser_1st.y"
                             {(yyval.val) = stringtochar("bool");}
#line 3456 "parser_1st.tab.c"
    break;

  case 8: /* NUMERICTYPE: INTEGRALTYPE  */
#line 251 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3462 "parser_1st.tab.c"
    break;

  case 9: /* NUMERICTYPE: FLOATINGTYPE  */
#line 252 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3468 "parser_1st.tab.c"
    break;

  case 10: /* INTEGRALTYPE: BYTE  */
#line 254 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3474 "parser_1st.tab.c"
    break;

  case 11: /* INTEGRALTYPE: SHORT  */
#line 255 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3480 "parser_1st.tab.c"
    break;

  case 12: /* INTEGRALTYPE: INT  */
#line 256 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3486 "parser_1st.tab.c"
    break;

  case 13: /* INTEGRALTYPE: LONG  */
#line 257 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3492 "parser_1st.tab.c"
    break;

  case 14: /* INTEGRALTYPE: CHAR  */
#line 258 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3498 "parser_1st.tab.c"
    break;

  case 15: /* FLOATINGTYPE: FLOAT  */
#line 260 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3504 "parser_1st.tab.c"
    break;

  case 16: /* FLOATINGTYPE: DOUBLE  */
#line 261 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3510 "parser_1st.tab.c"
    break;

  case 17: /* REFERENCETYPE: CLASSORINTERFACETYPE  */
#line 263 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3516 "parser_1st.tab.c"
    break;

  case 18: /* CLASSORINTERFACETYPE: CLASSTYPE  */
#line 265 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3522 "parser_1st.tab.c"
    break;

  case 19: /* CLASSTYPE: CLASSTYPE1  */
#line 267 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3528 "parser_1st.tab.c"
    break;

  case 20: /* CLASSTYPE1: IDENTIFIER  */
#line 269 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val); }
#line 3534 "parser_1st.tab.c"
    break;

  case 21: /* DIMS: OPENSQUARE CLOSESQUARE  */
#line 272 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3540 "parser_1st.tab.c"
    break;

  case 22: /* DIMS: DIMS OPENSQUARE CLOSESQUARE  */
#line 273 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3546 "parser_1st.tab.c"
    break;

  case 23: /* METHODNAME: IDENTIFIER  */
#line 275 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3557 "parser_1st.tab.c"
    break;

  case 24: /* EXPRESSIONNAME: IDENTIFIER DOT IDENTIFIER  */
#line 282 "parser_1st.y"
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
#line 3579 "parser_1st.tab.c"
    break;

  case 25: /* EXPRESSIONNAME: EXPRESSIONNAME DOT IDENTIFIER  */
#line 299 "parser_1st.y"
                                                  {/*TODO*/}
#line 3585 "parser_1st.tab.c"
    break;

  case 28: /* TOPLEVELCLASSORINTERFACEDECLARATION: CLASSDECLARATION  */
#line 305 "parser_1st.y"
                                                          {  

    assert(classfields.find(chartostring((yyvsp[0].val)))==classfields.end());
    assert(classmethods.find(chartostring((yyvsp[0].val)))==classmethods.end());

    classfields[chartostring((yyvsp[0].val))]= fields;
    classmethods[chartostring((yyvsp[0].val))]= methods;


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
#line 3631 "parser_1st.tab.c"
    break;

  case 36: /* CLASSDECLARATION: NORMALCLASSDECLARATION  */
#line 355 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);for(auto obj:object_list){
                        string pr = pref[obj.first];
                        vector<string> methods = getallmethods(obj.first,obj.second);
                        // vector<string> methods = {"f"};
                        for(auto method : methods){
                            // code.push_back(method);
                            // cout<<"methods "<<method<<"\n";

                            add_func(code, pr, method_det[obj.second][method].start, method_det[obj.second][method].end);
                        }
                    }}
#line 3647 "parser_1st.tab.c"
    break;

  case 37: /* NORMALCLASSDECLARATION: CLASS CLASSNAME CLASSBODY  */
#line 368 "parser_1st.y"
                                                       {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));/*TODO begin class */}
#line 3653 "parser_1st.tab.c"
    break;

  case 38: /* NORMALCLASSDECLARATION: SUPER1 CLASS IDENTIFIER CLASSBODY  */
#line 369 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val); if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3659 "parser_1st.tab.c"
    break;

  case 39: /* NORMALCLASSDECLARATION: SUPER2 CLASS IDENTIFIER CLASSBODY  */
#line 370 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3665 "parser_1st.tab.c"
    break;

  case 40: /* NORMALCLASSDECLARATION: SUPER3 CLASS IDENTIFIER CLASSBODY  */
#line 371 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3671 "parser_1st.tab.c"
    break;

  case 101: /* CLASSNAME: IDENTIFIER  */
#line 436 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val); curr_class = chartostring((yyval.val)); }
#line 3677 "parser_1st.tab.c"
    break;

  case 166: /* FOR: FOR1  */
#line 503 "parser_1st.y"
           {newscope();}
#line 3683 "parser_1st.tab.c"
    break;

  case 167: /* OPENCURLY: OPENCURLY1  */
#line 504 "parser_1st.y"
                          {newscope(); }
#line 3689 "parser_1st.tab.c"
    break;

  case 168: /* CLOSECURLY: CLOSECURLY1  */
#line 505 "parser_1st.y"
                          {popscope();}
#line 3695 "parser_1st.tab.c"
    break;

  case 208: /* FIELDDECLARATION: FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 566 "parser_1st.y"
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

                        }
                    }
#line 3726 "parser_1st.tab.c"
    break;

  case 209: /* FIELDDECLARATION: SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 592 "parser_1st.y"
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

                        }
                    }
#line 3755 "parser_1st.tab.c"
    break;

  case 210: /* FIELDDECLARATION: SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 616 "parser_1st.y"
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

                        }
                    }
#line 3786 "parser_1st.tab.c"
    break;

  case 211: /* FIELDDECLARATION: TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 642 "parser_1st.y"
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

                        }
                    }
#line 3826 "parser_1st.tab.c"
    break;

  case 212: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATOR  */
#line 680 "parser_1st.y"
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
#line 3843 "parser_1st.tab.c"
    break;

  case 213: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR  */
#line 692 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[-2].val); if(generalmap[(yyvsp[0].val)].typ.name != "" && generalmap[(yyval.val)].typ.name != "" )assert(generalmap[(yyvsp[0].val)].typ.name == generalmap[(yyval.val)].typ.name); else generalmap[(yyval.val)].typ.name = max(generalmap[(yyvsp[0].val)].typ.name, generalmap[(yyval.val)].typ.name );  generalmap[(yyval.val)].vlist.push_back({generalmap[(yyvsp[0].val)].vid, generalmap[(yyvsp[0].val)].vinit});
                        {                           

                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                    // assert(!(ds[curr3].find("type")!=ds[curr3].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"]));

                                                    // if((ds[curr3].find("type")!=ds[curr3].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"])){
                                                    //     cerr<<ds[curr3]["type"]<<" "<<ds[curr1]["type"]<<"\n";
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
#line 3871 "parser_1st.tab.c"
    break;

  case 214: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER  */
#line 716 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit ;   generalmap[(yyval.val)].typ= generalmap[(yyvsp[0].val)].typ;                                   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));                 
                                                                            if(ds[curr3].find("class")!=ds[curr3].end()){
                                                                                ds[curr]["var"] = ds[curr1]["var"];
                                                                                string cls = ds[curr3]["var"];    // stores the class name after new
                                                                                cout<<"class "<<cls<<"\n";
                                                                                object_list.push_back({ds[curr]["var"],cls}); // Add object to object list
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
#line 3909 "parser_1st.tab.c"
    break;

  case 215: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID  */
#line 749 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];}
#line 3915 "parser_1st.tab.c"
    break;

  case 216: /* VARIABLEDECLARATORID: IDENTIFIER  */
#line 751 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));

}
#line 3928 "parser_1st.tab.c"
    break;

  case 217: /* VARIABLEDECLARATORID: IDENTIFIER DIMS  */
#line 759 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        int curr = chartonum((yyval.val));
                                    ds[curr]["var"] = chartostring((yyvsp[-1].val));
                        /*TODO*/
                        }
#line 3938 "parser_1st.tab.c"
    break;

  case 218: /* VARIABLEINITIALIZER: EXPRESSION  */
#line 766 "parser_1st.y"
                                    {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 3944 "parser_1st.tab.c"
    break;

  case 219: /* VARIABLEINITIALIZER: ARRAYINITIALIZER  */
#line 767 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 3950 "parser_1st.tab.c"
    break;

  case 220: /* EXPRESSION: ASSIGNMENTEXPRESSION  */
#line 769 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 3956 "parser_1st.tab.c"
    break;

  case 221: /* ASSIGNMENTEXPRESSION: CONDITIONALEXPRESSION  */
#line 771 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 3964 "parser_1st.tab.c"
    break;

  case 222: /* ASSIGNMENTEXPRESSION: ASSIGNMENT  */
#line 774 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);/*TODO CHECK multiple assign*/}
#line 3970 "parser_1st.tab.c"
    break;

  case 223: /* ASSIGNMENT: LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  */
#line 776 "parser_1st.y"
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
#line 3989 "parser_1st.tab.c"
    break;

  case 224: /* LEFTHANDSIDE: EXPRESSIONNAME  */
#line 791 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 3995 "parser_1st.tab.c"
    break;

  case 225: /* LEFTHANDSIDE: IDENTIFIER  */
#line 792 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
#line 4008 "parser_1st.tab.c"
    break;

  case 226: /* LEFTHANDSIDE: FIELDACCESS  */
#line 800 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4014 "parser_1st.tab.c"
    break;

  case 227: /* LEFTHANDSIDE: ARRAYACCESS  */
#line 801 "parser_1st.y"
                                {   (yyval.val) = (yyvsp[0].val);
                                    ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"[ "+ds[chartonum((yyvsp[0].val))]["var"]+" ]";
                }
#line 4022 "parser_1st.tab.c"
    break;

  case 228: /* ASSIGNMENTOPERATOR: EQUALS  */
#line 805 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 4029 "parser_1st.tab.c"
    break;

  case 229: /* ASSIGNMENTOPERATOR: MULTIPLYEQUALS  */
#line 807 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 4036 "parser_1st.tab.c"
    break;

  case 230: /* ASSIGNMENTOPERATOR: DIVIDEEQUALS  */
#line 809 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 4043 "parser_1st.tab.c"
    break;

  case 231: /* ASSIGNMENTOPERATOR: MODEQUALS  */
#line 811 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 4050 "parser_1st.tab.c"
    break;

  case 232: /* ASSIGNMENTOPERATOR: PLUSEQUALS  */
#line 813 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 4057 "parser_1st.tab.c"
    break;

  case 233: /* ASSIGNMENTOPERATOR: MINUSEQUALS  */
#line 815 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 4064 "parser_1st.tab.c"
    break;

  case 234: /* FIELDACCESS: PRIMARY DOT IDENTIFIER  */
#line 818 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring((yyvsp[0].val));
                                        }else assert(0 && "unexpected type\n");
                                        }
#line 4076 "parser_1st.tab.c"
    break;

  case 237: /* PRIMARY: PRIMARYNONEWARRAY  */
#line 828 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            if(ds[chartonum((yyval.val))].find("array")!=ds[chartonum((yyval.val))].end())
                            ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"["+ds[chartonum((yyvsp[0].val))]["var"]+"]"; }
#line 4084 "parser_1st.tab.c"
    break;

  case 238: /* PRIMARY: ARRAYCREATIONEXPRESSION  */
#line 831 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4090 "parser_1st.tab.c"
    break;

  case 239: /* PRIMARYNONEWARRAY: LITERAL  */
#line 833 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4096 "parser_1st.tab.c"
    break;

  case 240: /* PRIMARYNONEWARRAY: CLASSLITERAL  */
#line 834 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4102 "parser_1st.tab.c"
    break;

  case 241: /* PRIMARYNONEWARRAY: THIS  */
#line 835 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 4111 "parser_1st.tab.c"
    break;

  case 243: /* PRIMARYNONEWARRAY: OPENPARAN EXPRESSION CLOSEPARAN  */
#line 840 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4117 "parser_1st.tab.c"
    break;

  case 244: /* PRIMARYNONEWARRAY: CLASSINSTANCECREATIONEXPRESSION  */
#line 841 "parser_1st.y"
                                                              {(yyval.val) = (yyvsp[0].val); generalmap[(yyval.val)].isnewclass = true;}
#line 4123 "parser_1st.tab.c"
    break;

  case 245: /* PRIMARYNONEWARRAY: FIELDACCESS  */
#line 842 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4129 "parser_1st.tab.c"
    break;

  case 246: /* PRIMARYNONEWARRAY: ARRAYACCESS  */
#line 843 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4135 "parser_1st.tab.c"
    break;

  case 247: /* PRIMARYNONEWARRAY: METHODINVOCATION  */
#line 844 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4141 "parser_1st.tab.c"
    break;

  case 249: /* LITERAL: INTEGERLITERAL  */
#line 847 "parser_1st.y"
                        {(yyval.val) = new_temp();  ds[chartonum((yyval.val))]["type"] = "int"; ds[chartonum((yyval.val))]["var"] = new_var(); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); tempinitval[ds[chartonum((yyval.val))]["var"]]= chartonum((yyvsp[0].val)); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4147 "parser_1st.tab.c"
    break;

  case 250: /* LITERAL: FLOATINGPOINTLITERAL  */
#line 848 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["start"] = numtostring(code.size());ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4153 "parser_1st.tab.c"
    break;

  case 251: /* LITERAL: BOOLEANLITERAL  */
#line 849 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4159 "parser_1st.tab.c"
    break;

  case 252: /* LITERAL: CHARACTERLITERAL  */
#line 850 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4165 "parser_1st.tab.c"
    break;

  case 253: /* LITERAL: STRINGLITERAL  */
#line 851 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4171 "parser_1st.tab.c"
    break;

  case 254: /* LITERAL: TEXTBLOCK  */
#line 852 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4177 "parser_1st.tab.c"
    break;

  case 255: /* LITERAL: NULLLITERAL  */
#line 853 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4183 "parser_1st.tab.c"
    break;

  case 265: /* CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
#line 866 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[0].val);}
#line 4189 "parser_1st.tab.c"
    break;

  case 269: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  */
#line 871 "parser_1st.y"
                                                                                                           {(yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-2].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-2].val))];  }
#line 4195 "parser_1st.tab.c"
    break;

  case 270: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  */
#line 872 "parser_1st.y"
                                                                                                                     {/*TODO*/}
#line 4201 "parser_1st.tab.c"
    break;

  case 271: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 873 "parser_1st.y"
                                                                                                                        {/*TODO*/}
#line 4207 "parser_1st.tab.c"
    break;

  case 272: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY  */
#line 874 "parser_1st.y"
                                                                                                                                  {/*TODO*/}
#line 4213 "parser_1st.tab.c"
    break;

  case 277: /* CLASSORINTERFACETYPETOINSTANTIATE: IDENTIFIER  */
#line 880 "parser_1st.y"
                                                {   (yyval.val) = new_temp(); ds[ chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val)); ds[ chartonum((yyval.val))]["class"] = "true";
                                                     }
#line 4220 "parser_1st.tab.c"
    break;

  case 278: /* ARGUMENTLIST: EXPRESSION  */
#line 883 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            ds2[chartonum((yyval.val))]["type"].push_back(ds[chartonum((yyvsp[0].val))]["type"]);
                            ds2[chartonum((yyval.val))]["var"].push_back(ds[chartonum((yyvsp[0].val))]["var"]);
                            }
#line 4229 "parser_1st.tab.c"
    break;

  case 279: /* ARGUMENTLIST: ARGUMENTLIST COMMA EXPRESSION  */
#line 887 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4242 "parser_1st.tab.c"
    break;

  case 280: /* METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  */
#line 896 "parser_1st.y"
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
#line 4259 "parser_1st.tab.c"
    break;

  case 281: /* METHODINVOCATION: METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 908 "parser_1st.y"
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
#line 4283 "parser_1st.tab.c"
    break;

  case 282: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 927 "parser_1st.y"
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
#line 4312 "parser_1st.tab.c"
    break;

  case 283: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 951 "parser_1st.y"
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
                                                        cout<<"curr typed "<<ds[curr]["type"]<<"\n";
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
#line 4342 "parser_1st.tab.c"
    break;

  case 312: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS  */
#line 1008 "parser_1st.y"
                                                         {/*NOT SUPPORTED*/}
#line 4348 "parser_1st.tab.c"
    break;

  case 313: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS DIMS  */
#line 1009 "parser_1st.y"
                                                                       {/*NOT SUPPORTED*/}
#line 4354 "parser_1st.tab.c"
    break;

  case 314: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER  */
#line 1010 "parser_1st.y"
                                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-2].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; assert (generalmap[(yyvsp[0].val)].vinit.dims.size() == temp[(yyvsp[-1].val)]); }
#line 4360 "parser_1st.tab.c"
    break;

  case 315: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER  */
#line 1011 "parser_1st.y"
                                                                               {/*NOT SUPPORTED*/}
#line 4366 "parser_1st.tab.c"
    break;

  case 316: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS  */
#line 1012 "parser_1st.y"
                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; ds[chartonum((yyval.val))]["arr"] = "true"; ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyvsp[0].val))]["var"]; ds[chartonum((yyval.val))]["type"] = chartostring((yyvsp[-1].val)); ds[chartonum((yyval.val))]["start"] = ds[chartonum((yyvsp[0].val))]["start"];}
#line 4372 "parser_1st.tab.c"
    break;

  case 317: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS  */
#line 1013 "parser_1st.y"
                                                                   {/*NOT SUPPORTED*/}
#line 4378 "parser_1st.tab.c"
    break;

  case 318: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS  */
#line 1014 "parser_1st.y"
                                                   {/*NOT SUPPORTED*/}
#line 4384 "parser_1st.tab.c"
    break;

  case 319: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS  */
#line 1015 "parser_1st.y"
                                                              {/*NOT SUPPORTED*/}
#line 4390 "parser_1st.tab.c"
    break;

  case 320: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE  */
#line 1016 "parser_1st.y"
                                               {/*TODO whats this*/}
#line 4396 "parser_1st.tab.c"
    break;

  case 321: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE  */
#line 1017 "parser_1st.y"
                                                         {/*TODO whats this*/}
#line 4402 "parser_1st.tab.c"
    break;

  case 322: /* ARRAYINITIALIZER: OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  */
#line 1019 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4408 "parser_1st.tab.c"
    break;

  case 323: /* ARRAYINITIALIZER: OPENCURLY CLOSECURLY  */
#line 1020 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4414 "parser_1st.tab.c"
    break;

  case 324: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST  */
#line 1022 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4420 "parser_1st.tab.c"
    break;

  case 325: /* ARRAYINITIALIZER1: COMMA  */
#line 1023 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=2;}
#line 4426 "parser_1st.tab.c"
    break;

  case 326: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST COMMA  */
#line 1024 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4432 "parser_1st.tab.c"
    break;

  case 327: /* DIMEXPRS: DIMEXPR  */
#line 1026 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[0].val))];}
#line 4438 "parser_1st.tab.c"
    break;

  case 328: /* DIMEXPRS: DIMEXPRS DIMEXPR  */
#line 1027 "parser_1st.y"
                             {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum((yyvsp[-1].val))]["var"]+" *"+ds[chartonum((yyvsp[0].val))]["type"]+" "+ds[ chartonum((yyvsp[0].val))]["var"]);
                              ds[ chartonum((yyval.val))]["var"] = t;  }
#line 4446 "parser_1st.tab.c"
    break;

  case 329: /* DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1031 "parser_1st.y"
                                            {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = varaddrstoint(ds[chartonum((yyvsp[-1].val))]["var"]); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-1].val))];}
#line 4452 "parser_1st.tab.c"
    break;

  case 330: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZER  */
#line 1033 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4458 "parser_1st.tab.c"
    break;

  case 331: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  */
#line 1034 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4464 "parser_1st.tab.c"
    break;

  case 333: /* ARRAYACCESS: PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1041 "parser_1st.y"
                                                                    {
                (yyval.val) = new_temp(); 
                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
                if(ds[curr3]["type"]!="int"&&ds[curr3]["type"]!="long"&&ds[curr3]["type"]!="short"&&ds[curr3]["type"]!="byte")
                cerr<<"Array index not integer\n";
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
#line 4486 "parser_1st.tab.c"
    break;

  case 334: /* ARRAYACCESS: IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1058 "parser_1st.y"
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
                cerr<<"Array index not integer\n";
                // code.push_back(ds[curr]["var"]+" = "+ds[curr3]["var"]);
            }
#line 4504 "parser_1st.tab.c"
    break;

  case 335: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  */
#line 1072 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4510 "parser_1st.tab.c"
    break;

  case 336: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  */
#line 1073 "parser_1st.y"
                                                                                                    {}
#line 4516 "parser_1st.tab.c"
    break;

  case 337: /* CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  */
#line 1075 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4522 "parser_1st.tab.c"
    break;

  case 338: /* CONDITIONALOREXPRESSION: CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  */
#line 1076 "parser_1st.y"
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
#line 4540 "parser_1st.tab.c"
    break;

  case 339: /* CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  */
#line 1090 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4546 "parser_1st.tab.c"
    break;

  case 340: /* CONDITIONALANDEXPRESSION: CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  */
#line 1091 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4560 "parser_1st.tab.c"
    break;

  case 341: /* INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  */
#line 1101 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4566 "parser_1st.tab.c"
    break;

  case 342: /* INCLUSIVEOREXPRESSION: INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  */
#line 1102 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4579 "parser_1st.tab.c"
    break;

  case 343: /* EXCLUSIVEOREXPRESSION: ANDEXPRESSION  */
#line 1111 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4585 "parser_1st.tab.c"
    break;

  case 344: /* EXCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  */
#line 1112 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4598 "parser_1st.tab.c"
    break;

  case 345: /* ANDEXPRESSION: EQUALITYEXPRESSION  */
#line 1120 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4604 "parser_1st.tab.c"
    break;

  case 346: /* ANDEXPRESSION: ANDEXPRESSION AND EQUALITYEXPRESSION  */
#line 1121 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4618 "parser_1st.tab.c"
    break;

  case 347: /* EQUALITYEXPRESSION: RELATIONALEXPRESSION  */
#line 1131 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
#line 4631 "parser_1st.tab.c"
    break;

  case 348: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  */
#line 1139 "parser_1st.y"
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
#line 4652 "parser_1st.tab.c"
    break;

  case 349: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  */
#line 1155 "parser_1st.y"
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
#line 4674 "parser_1st.tab.c"
    break;

  case 350: /* RELATIONALEXPRESSION: SHIFTEXPRESSION  */
#line 1173 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4684 "parser_1st.tab.c"
    break;

  case 351: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  */
#line 1178 "parser_1st.y"
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
#line 4707 "parser_1st.tab.c"
    break;

  case 352: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  */
#line 1196 "parser_1st.y"
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
#line 4726 "parser_1st.tab.c"
    break;

  case 353: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  */
#line 1210 "parser_1st.y"
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
#line 4745 "parser_1st.tab.c"
    break;

  case 354: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  */
#line 1224 "parser_1st.y"
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
#line 4764 "parser_1st.tab.c"
    break;

  case 356: /* SHIFTEXPRESSION: ADDITIVEEXPRESSION  */
#line 1240 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4770 "parser_1st.tab.c"
    break;

  case 357: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  */
#line 1241 "parser_1st.y"
                                                                                    {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4784 "parser_1st.tab.c"
    break;

  case 358: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1250 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4797 "parser_1st.tab.c"
    break;

  case 359: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1258 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4810 "parser_1st.tab.c"
    break;

  case 360: /* ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  */
#line 1267 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 4816 "parser_1st.tab.c"
    break;

  case 361: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  */
#line 1268 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4829 "parser_1st.tab.c"
    break;

  case 362: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  */
#line 1276 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4842 "parser_1st.tab.c"
    break;

  case 363: /* MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  */
#line 1285 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4848 "parser_1st.tab.c"
    break;

  case 364: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  */
#line 1286 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4861 "parser_1st.tab.c"
    break;

  case 365: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  */
#line 1294 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4874 "parser_1st.tab.c"
    break;

  case 366: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  */
#line 1302 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4887 "parser_1st.tab.c"
    break;

  case 367: /* UNARYEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1311 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4893 "parser_1st.tab.c"
    break;

  case 368: /* UNARYEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1312 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4899 "parser_1st.tab.c"
    break;

  case 369: /* UNARYEXPRESSION: PLUS UNARYEXPRESSION  */
#line 1313 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 4907 "parser_1st.tab.c"
    break;

  case 370: /* UNARYEXPRESSION: MINUS UNARYEXPRESSION  */
#line 1316 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4920 "parser_1st.tab.c"
    break;

  case 371: /* UNARYEXPRESSION: UNARYEXPRESSIONNOTPLUSMINUS  */
#line 1324 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 4926 "parser_1st.tab.c"
    break;

  case 372: /* PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  */
#line 1326 "parser_1st.y"
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
#line 4944 "parser_1st.tab.c"
    break;

  case 373: /* PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  */
#line 1340 "parser_1st.y"
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
#line 4962 "parser_1st.tab.c"
    break;

  case 374: /* UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  */
#line 1354 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4968 "parser_1st.tab.c"
    break;

  case 375: /* UNARYEXPRESSIONNOTPLUSMINUS: COMPLEMENT UNARYEXPRESSION  */
#line 1355 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4981 "parser_1st.tab.c"
    break;

  case 376: /* UNARYEXPRESSIONNOTPLUSMINUS: NOT UNARYEXPRESSION  */
#line 1363 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4994 "parser_1st.tab.c"
    break;

  case 377: /* POSTFIXEXPRESSION: PRIMARY  */
#line 1372 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5000 "parser_1st.tab.c"
    break;

  case 378: /* POSTFIXEXPRESSION: EXPRESSIONNAME  */
#line 1373 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5006 "parser_1st.tab.c"
    break;

  case 379: /* POSTFIXEXPRESSION: IDENTIFIER  */
#line 1374 "parser_1st.y"
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
#line 5025 "parser_1st.tab.c"
    break;

  case 380: /* POSTFIXEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1388 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5031 "parser_1st.tab.c"
    break;

  case 381: /* POSTFIXEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1389 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5037 "parser_1st.tab.c"
    break;

  case 382: /* POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  */
#line 1391 "parser_1st.y"
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
#line 5054 "parser_1st.tab.c"
    break;

  case 383: /* POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  */
#line 1404 "parser_1st.y"
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
#line 5073 "parser_1st.tab.c"
    break;

  case 385: /* METHODDECLARATION: METHODHEADER METHODBODY  */
#line 1422 "parser_1st.y"
                                            {
    (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    
    code.push_back("end func");
    // cerr<<"method declaration"<<generalmap[$1].name<<endl;
    assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());
    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
    methods[generalmap[(yyvsp[-1].val)].name].lineno = yylineno;
    
    vector <type> argtype;
     

    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
         }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 5097 "parser_1st.tab.c"
    break;

  case 386: /* METHODDECLARATION: SUPER1 METHODHEADER METHODBODY  */
#line 1442 "parser_1st.y"
                                                      {
                        (yyval.val) =(yyvsp[-1].val);
                        method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cerr<<"method declaration"<<generalmap[$2].name<<endl;

    assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
    vector <type> argtype;
    methods[generalmap[(yyvsp[-1].val)].name].lineno = yylineno;
    
    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;


    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
         
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 5124 "parser_1st.tab.c"
    break;

  case 387: /* METHODDECLARATION: SUPER2 METHODHEADER METHODBODY  */
#line 1464 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cerr<<"method declaration"<<generalmap[$2].name<<endl;
        assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());
      

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
        methods[generalmap[(yyvsp[-1].val)].name].lineno = yylineno;

    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;

    vector <type> argtype;
    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
        
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 5149 "parser_1st.tab.c"
    break;

  case 388: /* METHODDECLARATION: SUPER3 METHODHEADER METHODBODY  */
#line 1484 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cerr<<"method declaration"<<generalmap[$2].name<<endl;
        assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
        methods[generalmap[(yyvsp[-1].val)].name].lineno = yylineno;

    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;

    vector <type> argtype;

    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
        
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 5174 "parser_1st.tab.c"
    break;

  case 389: /* METHODDECLARATION: METHODMODIFIERS METHODHEADER METHODBODY  */
#line 1504 "parser_1st.y"
                                                               {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cerr<<"method declaration"<<generalmap[$2].name<<endl;
        assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
        methods[generalmap[(yyvsp[-1].val)].name].lineno = yylineno;

    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;

    vector <type> argtype;

    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
        
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 5199 "parser_1st.tab.c"
    break;

  case 395: /* METHODHEADER: TYPE METHODDECLARATOR  */
#line 1531 "parser_1st.y"
                                     { (yyval.val) = (yyvsp[0].val);  generalmap[(yyval.val)].typ.name = chartostring((yyvsp[-1].val)); 
tempnextscope(); 
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
#line 5231 "parser_1st.tab.c"
    break;

  case 396: /* METHODHEADER: VOID METHODDECLARATOR  */
#line 1558 "parser_1st.y"
                                      { (yyval.val) = (yyvsp[0].val);  generalmap[(yyval.val)].typ.name = chartostring((yyvsp[-1].val)); 
            tempnextscope();
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
#line 5250 "parser_1st.tab.c"
    break;

  case 407: /* METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1587 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));              
                                        method_det[curr_class][chartostring((yyvsp[-2].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        // cout<<"methodhead "<<ds[chartonum($$)]["method_name"]<<"\n";
                                        }
#line 5263 "parser_1st.tab.c"
    break;

  case 408: /* METHODDECLARATOR: IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 1595 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                method_det[curr_class][chartostring((yyvsp[-3].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-3].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        for(auto i:ds2[curr3]["param"])
                                        code.push_back("pop param, "+ i);}
#line 5275 "parser_1st.tab.c"
    break;

  case 417: /* FORMALPARAMETERLIST: FORMALPARAMETER  */
#line 1612 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 5284 "parser_1st.tab.c"
    break;

  case 418: /* FORMALPARAMETERLIST: FORMALPARAMETERLIST COMMA FORMALPARAMETER  */
#line 1616 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 5294 "parser_1st.tab.c"
    break;

  case 419: /* FORMALPARAMETER: TYPE VARIABLEDECLARATORID  */
#line 1622 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 5303 "parser_1st.tab.c"
    break;

  case 421: /* FORMALPARAMETER: FINAL TYPE VARIABLEDECLARATORID  */
#line 1627 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 5312 "parser_1st.tab.c"
    break;

  case 424: /* METHODBODY: BLOCK  */
#line 1637 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 5318 "parser_1st.tab.c"
    break;

  case 428: /* BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 1644 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val);  }
#line 5324 "parser_1st.tab.c"
    break;

  case 430: /* BLOCKSTATEMENTS: BLOCKSTATEMENT  */
#line 1647 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val);  
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
#line 5332 "parser_1st.tab.c"
    break;

  case 431: /* BLOCKSTATEMENTS: BLOCKSTATEMENTS BLOCKSTATEMENT  */
#line 1650 "parser_1st.y"
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
#line 5347 "parser_1st.tab.c"
    break;

  case 433: /* BLOCKSTATEMENT: LOCALVARIABLEDECLARATIONSTATEMENT  */
#line 1662 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val); 
                
               }
#line 5355 "parser_1st.tab.c"
    break;

  case 434: /* BLOCKSTATEMENT: STATEMENT  */
#line 1665 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
               }
#line 5362 "parser_1st.tab.c"
    break;

  case 436: /* LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  */
#line 1670 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 5368 "parser_1st.tab.c"
    break;

  case 437: /* LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1672 "parser_1st.y"
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
                                    cerr<<g;
                                    assert(isnum(g) && "only constant direct expressions supported");
                                    ft = stringtonum(g);


                                }
                                arrsize *= ft;
                                cerr<<ft<<" ";

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
#line 5432 "parser_1st.tab.c"
    break;

  case 438: /* LOCALVARIABLEDECLARATION: LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1731 "parser_1st.y"
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
                                   cerr<<g;

                                    assert(isnum(g) && "only constant direct expressions supported");
                                    ft = stringtonum(g);


                                }
                                arrsize *= ft;
                                cerr<<ft<<" ";

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
#line 5499 "parser_1st.tab.c"
    break;

  case 439: /* LOCALVARIABLETYPE: TYPE  */
#line 1794 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 5505 "parser_1st.tab.c"
    break;

  case 440: /* LOCALVARIABLETYPE: VAR  */
#line 1795 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5511 "parser_1st.tab.c"
    break;

  case 441: /* STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1798 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
#line 5517 "parser_1st.tab.c"
    break;

  case 442: /* STATEMENT: LABELEDSTATEMENT  */
#line 1799 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5523 "parser_1st.tab.c"
    break;

  case 443: /* STATEMENT: IFTHENSTATEMENT  */
#line 1800 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5529 "parser_1st.tab.c"
    break;

  case 444: /* STATEMENT: IFTHENELSESTATEMENT  */
#line 1801 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5535 "parser_1st.tab.c"
    break;

  case 445: /* STATEMENT: WHILESTATEMENT  */
#line 1802 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5541 "parser_1st.tab.c"
    break;

  case 446: /* STATEMENT: FORSTATEMENT  */
#line 1803 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5547 "parser_1st.tab.c"
    break;

  case 447: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  */
#line 1805 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5553 "parser_1st.tab.c"
    break;

  case 448: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EMPTYSTATEMENT  */
#line 1807 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5559 "parser_1st.tab.c"
    break;

  case 449: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EXPRESSIONSTATEMENT  */
#line 1808 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5565 "parser_1st.tab.c"
    break;

  case 450: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: ASSERTSTATEMENT  */
#line 1809 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5571 "parser_1st.tab.c"
    break;

  case 451: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BREAKSTATEMENT  */
#line 1810 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5577 "parser_1st.tab.c"
    break;

  case 452: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: CONTINUESTATEMENT  */
#line 1811 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5583 "parser_1st.tab.c"
    break;

  case 453: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: RETURNSTATEMENT  */
#line 1812 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5589 "parser_1st.tab.c"
    break;

  case 454: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: THROWSTATEMENT  */
#line 1813 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5595 "parser_1st.tab.c"
    break;

  case 455: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: YIELDSTATEMENT  */
#line 1814 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5601 "parser_1st.tab.c"
    break;

  case 456: /* EMPTYSTATEMENT: SEMICOLON  */
#line 1816 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5607 "parser_1st.tab.c"
    break;

  case 457: /* EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  */
#line 1818 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val); }
#line 5613 "parser_1st.tab.c"
    break;

  case 458: /* STATEMENTEXPRESSION: ASSIGNMENT  */
#line 1820 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5619 "parser_1st.tab.c"
    break;

  case 459: /* STATEMENTEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1821 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5625 "parser_1st.tab.c"
    break;

  case 460: /* STATEMENTEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1822 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5631 "parser_1st.tab.c"
    break;

  case 461: /* STATEMENTEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1823 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5637 "parser_1st.tab.c"
    break;

  case 462: /* STATEMENTEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1824 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5643 "parser_1st.tab.c"
    break;

  case 463: /* STATEMENTEXPRESSION: METHODINVOCATION  */
#line 1825 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5649 "parser_1st.tab.c"
    break;

  case 464: /* STATEMENTEXPRESSION: CLASSINSTANCECREATIONEXPRESSION  */
#line 1826 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5655 "parser_1st.tab.c"
    break;

  case 467: /* BREAKSTATEMENT: BREAK SEMICOLON  */
#line 1831 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5668 "parser_1st.tab.c"
    break;

  case 469: /* CONTINUESTATEMENT: CONTINUE SEMICOLON  */
#line 1841 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5681 "parser_1st.tab.c"
    break;

  case 471: /* RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  */
#line 1851 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5692 "parser_1st.tab.c"
    break;

  case 472: /* RETURNSTATEMENT: RETURN SEMICOLON  */
#line 1857 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 5703 "parser_1st.tab.c"
    break;

  case 476: /* IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1870 "parser_1st.y"
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
#line 5724 "parser_1st.tab.c"
    break;

  case 477: /* IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT  */
#line 1887 "parser_1st.y"
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
#line 5740 "parser_1st.tab.c"
    break;

  case 478: /* IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF  */
#line 1899 "parser_1st.y"
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
#line 5756 "parser_1st.tab.c"
    break;

  case 479: /* STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1911 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5762 "parser_1st.tab.c"
    break;

  case 480: /* STATEMENTNOSHORTIF: LABELEDSTATEMENTNOSHORTIF  */
#line 1912 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5768 "parser_1st.tab.c"
    break;

  case 481: /* STATEMENTNOSHORTIF: IFTHENELSESTATEMENTNOSHORTIF  */
#line 1913 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5774 "parser_1st.tab.c"
    break;

  case 482: /* STATEMENTNOSHORTIF: WHILESTATEMENTNOSHORTIF  */
#line 1914 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5780 "parser_1st.tab.c"
    break;

  case 483: /* STATEMENTNOSHORTIF: FORSTATEMENTNOSHORTIF  */
#line 1915 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5786 "parser_1st.tab.c"
    break;

  case 485: /* WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1919 "parser_1st.y"
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
#line 5802 "parser_1st.tab.c"
    break;

  case 486: /* FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  */
#line 1931 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); popscope();}
#line 5808 "parser_1st.tab.c"
    break;

  case 487: /* FORSTATEMENTNOSHORTIF: ENHANCEDFORSTATEMENTNOSHORTIF  */
#line 1932 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5814 "parser_1st.tab.c"
    break;

  case 488: /* WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1935 "parser_1st.y"
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
#line 5829 "parser_1st.tab.c"
    break;

  case 489: /* FORSTATEMENT: BASICFORSTATEMENT  */
#line 1946 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5835 "parser_1st.tab.c"
    break;

  case 490: /* FORSTATEMENT: ENHANCEDFORSTATEMENT  */
#line 1947 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5841 "parser_1st.tab.c"
    break;

  case 491: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 1949 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 5854 "parser_1st.tab.c"
    break;

  case 492: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1957 "parser_1st.y"
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
#line 5870 "parser_1st.tab.c"
    break;

  case 493: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 1968 "parser_1st.y"
                                                                                            {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-3].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
                                                                    // assert(0 && "Exp Error");
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size()); 
}
#line 5889 "parser_1st.tab.c"
    break;

  case 494: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1982 "parser_1st.y"
                                                                                                    {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-4].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
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
#line 5910 "parser_1st.tab.c"
    break;

  case 495: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 1998 "parser_1st.y"
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
#line 5928 "parser_1st.tab.c"
    break;

  case 496: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2011 "parser_1st.y"
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
#line 5949 "parser_1st.tab.c"
    break;

  case 497: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2027 "parser_1st.y"
                                                                                                    {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr5 = chartonum((yyvsp[-3].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
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
#line 5970 "parser_1st.tab.c"
    break;

  case 498: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2043 "parser_1st.y"
                                                                                                            {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-6].val)), curr5 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[-2].val)), curr9 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
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
#line 5991 "parser_1st.tab.c"
    break;

  case 499: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2060 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6004 "parser_1st.tab.c"
    break;

  case 500: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2068 "parser_1st.y"
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
#line 6020 "parser_1st.tab.c"
    break;

  case 501: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2079 "parser_1st.y"
                                                                                                     {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-3].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size()); 
}
#line 6039 "parser_1st.tab.c"
    break;

  case 502: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2093 "parser_1st.y"
                                                                                                             {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-4].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    
                                                                    if(ds[curr4]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr4]["type"]<<"\n";exit(0);}
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
#line 6061 "parser_1st.tab.c"
    break;

  case 503: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2110 "parser_1st.y"
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
#line 6079 "parser_1st.tab.c"
    break;

  case 504: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2123 "parser_1st.y"
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
#line 6100 "parser_1st.tab.c"
    break;

  case 505: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2139 "parser_1st.y"
                                                                                                             {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr5 = chartonum((yyvsp[-3].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
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
#line 6122 "parser_1st.tab.c"
    break;

  case 506: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2156 "parser_1st.y"
                                                                                                                     {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-6].val)), curr5 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[-2].val)), curr9 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr5]["type"]!="bool")
                                                                    {cerr<<"Expected bool type inside for expression. Got "<<ds[curr5]["type"]<<"\n";exit(0);}
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
#line 6143 "parser_1st.tab.c"
    break;

  case 509: /* FORINIT: STATEMENTEXPRESSIONLIST  */
#line 2178 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 6149 "parser_1st.tab.c"
    break;

  case 510: /* FORINIT: LOCALVARIABLEDECLARATION  */
#line 2179 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 6155 "parser_1st.tab.c"
    break;

  case 511: /* FORUPDATE: STATEMENTEXPRESSIONLIST  */
#line 2181 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 6169 "parser_1st.tab.c"
    break;

  case 512: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION  */
#line 2191 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 6175 "parser_1st.tab.c"
    break;

  case 513: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION  */
#line 2192 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 6187 "parser_1st.tab.c"
    break;

  case 551: /* SUPER1: PUBLIC  */
#line 2245 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6193 "parser_1st.tab.c"
    break;

  case 552: /* SUPER1: PRIVATE  */
#line 2246 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6199 "parser_1st.tab.c"
    break;

  case 553: /* SUPER1: PROTECTED  */
#line 2247 "parser_1st.y"
                    {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6205 "parser_1st.tab.c"
    break;

  case 554: /* SUPER1: SUPER1 PUBLIC  */
#line 2248 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6211 "parser_1st.tab.c"
    break;

  case 555: /* SUPER1: SUPER1 PRIVATE  */
#line 2249 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6217 "parser_1st.tab.c"
    break;

  case 556: /* SUPER1: SUPER1 PROTECTED  */
#line 2250 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6223 "parser_1st.tab.c"
    break;

  case 557: /* SUPER2: STATIC  */
#line 2252 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6229 "parser_1st.tab.c"
    break;

  case 558: /* SUPER2: FINAL  */
#line 2253 "parser_1st.y"
                 {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6235 "parser_1st.tab.c"
    break;

  case 559: /* SUPER2: SUPER1 STATIC  */
#line 2254 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6241 "parser_1st.tab.c"
    break;

  case 560: /* SUPER2: SUPER1 FINAL  */
#line 2255 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6247 "parser_1st.tab.c"
    break;

  case 561: /* SUPER2: SUPER2 STATIC  */
#line 2256 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6253 "parser_1st.tab.c"
    break;

  case 562: /* SUPER2: SUPER2 FINAL  */
#line 2257 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6259 "parser_1st.tab.c"
    break;

  case 563: /* SUPER2: SUPER2 PUBLIC  */
#line 2258 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6265 "parser_1st.tab.c"
    break;

  case 564: /* SUPER2: SUPER2 PRIVATE  */
#line 2259 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6271 "parser_1st.tab.c"
    break;

  case 565: /* SUPER2: SUPER2 PROTECTED  */
#line 2260 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6277 "parser_1st.tab.c"
    break;

  case 566: /* SUPER3: ABSTRACT  */
#line 2262 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6283 "parser_1st.tab.c"
    break;

  case 567: /* SUPER3: STRICTFP  */
#line 2263 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6289 "parser_1st.tab.c"
    break;

  case 568: /* SUPER3: SUPER2 ABSTRACT  */
#line 2264 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6295 "parser_1st.tab.c"
    break;

  case 569: /* SUPER3: SUPER2 STRICTFP  */
#line 2265 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6301 "parser_1st.tab.c"
    break;

  case 570: /* SUPER3: SUPER3 ABSTRACT  */
#line 2266 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6307 "parser_1st.tab.c"
    break;

  case 571: /* SUPER3: SUPER3 STRICTFP  */
#line 2267 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6313 "parser_1st.tab.c"
    break;

  case 572: /* SUPER3: SUPER3 PUBLIC  */
#line 2268 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6319 "parser_1st.tab.c"
    break;

  case 573: /* SUPER3: SUPER3 PRIVATE  */
#line 2269 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6325 "parser_1st.tab.c"
    break;

  case 574: /* SUPER3: SUPER3 PROTECTED  */
#line 2270 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6331 "parser_1st.tab.c"
    break;

  case 575: /* SUPER3: SUPER3 STATIC  */
#line 2271 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6337 "parser_1st.tab.c"
    break;

  case 576: /* SUPER3: SUPER3 FINAL  */
#line 2272 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6343 "parser_1st.tab.c"
    break;

  case 577: /* FIELDMODIFIERS: SUPER3 TRANSIENT  */
#line 2274 "parser_1st.y"
                                 {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6349 "parser_1st.tab.c"
    break;

  case 578: /* FIELDMODIFIERS: SUPER3 VOLATILE  */
#line 2275 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6355 "parser_1st.tab.c"
    break;

  case 579: /* FIELDMODIFIERS: FIELDMODIFIERS TRANSIENT  */
#line 2276 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6361 "parser_1st.tab.c"
    break;

  case 580: /* FIELDMODIFIERS: FIELDMODIFIERS VOLATILE  */
#line 2277 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6367 "parser_1st.tab.c"
    break;

  case 581: /* FIELDMODIFIERS: FIELDMODIFIERS PUBLIC  */
#line 2278 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6373 "parser_1st.tab.c"
    break;

  case 582: /* FIELDMODIFIERS: FIELDMODIFIERS PRIVATE  */
#line 2279 "parser_1st.y"
                                     {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6379 "parser_1st.tab.c"
    break;

  case 583: /* FIELDMODIFIERS: FIELDMODIFIERS PROTECTED  */
#line 2280 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6385 "parser_1st.tab.c"
    break;

  case 584: /* FIELDMODIFIERS: FIELDMODIFIERS STATIC  */
#line 2281 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6391 "parser_1st.tab.c"
    break;

  case 585: /* FIELDMODIFIERS: FIELDMODIFIERS FINAL  */
#line 2282 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6397 "parser_1st.tab.c"
    break;

  case 586: /* METHODMODIFIERS: SUPER3 SYNCHRONIZED  */
#line 2285 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6403 "parser_1st.tab.c"
    break;

  case 587: /* METHODMODIFIERS: SUPER3 NATIVE  */
#line 2286 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6409 "parser_1st.tab.c"
    break;

  case 588: /* METHODMODIFIERS: METHODMODIFIERS SYNCHRONIZED  */
#line 2287 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6415 "parser_1st.tab.c"
    break;

  case 589: /* METHODMODIFIERS: METHODMODIFIERS NATIVE  */
#line 2288 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6421 "parser_1st.tab.c"
    break;

  case 590: /* METHODMODIFIERS: METHODMODIFIERS ABSTRACT  */
#line 2289 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6427 "parser_1st.tab.c"
    break;

  case 591: /* METHODMODIFIERS: METHODMODIFIERS STRICTFP  */
#line 2290 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6433 "parser_1st.tab.c"
    break;

  case 592: /* METHODMODIFIERS: METHODMODIFIERS PUBLIC  */
#line 2291 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6439 "parser_1st.tab.c"
    break;

  case 593: /* METHODMODIFIERS: METHODMODIFIERS PRIVATE  */
#line 2292 "parser_1st.y"
                                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6445 "parser_1st.tab.c"
    break;

  case 594: /* METHODMODIFIERS: METHODMODIFIERS PROTECTED  */
#line 2293 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6451 "parser_1st.tab.c"
    break;

  case 595: /* METHODMODIFIERS: METHODMODIFIERS STATIC  */
#line 2294 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6457 "parser_1st.tab.c"
    break;

  case 596: /* METHODMODIFIERS: METHODMODIFIERS FINAL  */
#line 2295 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6463 "parser_1st.tab.c"
    break;

  case 600: /* TYPEARGUMENT: REFERENCETYPE  */
#line 2302 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 6469 "parser_1st.tab.c"
    break;

  case 601: /* TYPEARGUMENT: WILDCARD  */
#line 2303 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 6475 "parser_1st.tab.c"
    break;

  case 606: /* INTERFACETYPE: CLASSTYPE  */
#line 2312 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 6481 "parser_1st.tab.c"
    break;


#line 6485 "parser_1st.tab.c"

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

#line 2314 "parser_1st.y"



int main(int argc, char** argv){
        newscope();
    yyparse();
    // type_check_function_strong();

    ofstream cout1("3ac.txt");
    // cout<<"CODE:\n";

    for (int i=0; i< code.size(); i++){
        cout1<<i<<" "<<code[i]<<endl;
    }
    ofstream cout2("symtable.csv");

    cout2<<"Token, Name(Lexeme), Type, Line Number, Scope, Dims(If array), ScopeINFO(Child), ScopeINFO(Parent) << Offsets\n";

    for (auto x : preservedsymboltable){
        cout2<< x.second.token << ", " << x.first.first << ", " << x.second.typ.name << ", " << x.second.lineno << ", " << x.first.second << ", " << x.second.typ.dims << ", "<<x.second.offset << endl;

    }
   
    

    for(auto x : parentscope){
        cout2<<", , , , , , "<<x.first<<", "<<x.second<<", "<<endl;
    }



  

}
