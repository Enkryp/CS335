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
        curoffset = scopeoffset.top();
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

    


    

#line 275 "parser_1st.tab.c"

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
  YYSYMBOL_NORMALINTERFACEDECLARATION = 146, /* NORMALINTERFACEDECLARATION  */
  YYSYMBOL_FOR = 147,                      /* FOR  */
  YYSYMBOL_OPENCURLY = 148,                /* OPENCURLY  */
  YYSYMBOL_CLOSECURLY = 149,               /* CLOSECURLY  */
  YYSYMBOL_INTERFACEBODY = 150,            /* INTERFACEBODY  */
  YYSYMBOL_INTERFACEMEMBERDECLARATIONS = 151, /* INTERFACEMEMBERDECLARATIONS  */
  YYSYMBOL_INTERFACEMEMBERDECLARATION = 152, /* INTERFACEMEMBERDECLARATION  */
  YYSYMBOL_INTERFACEDECLARATION = 153,     /* INTERFACEDECLARATION  */
  YYSYMBOL_TYPEPARAMETERS = 154,           /* TYPEPARAMETERS  */
  YYSYMBOL_TYPEPARAMETERLIST = 155,        /* TYPEPARAMETERLIST  */
  YYSYMBOL_TYPEPARAMETER = 156,            /* TYPEPARAMETER  */
  YYSYMBOL_TYPEBOUND = 157,                /* TYPEBOUND  */
  YYSYMBOL_ADDITIONALBOUND = 158,          /* ADDITIONALBOUND  */
  YYSYMBOL_CLASSEXTENDS = 159,             /* CLASSEXTENDS  */
  YYSYMBOL_CLASSIMPLEMENTS = 160,          /* CLASSIMPLEMENTS  */
  YYSYMBOL_INTERFACETYPELIST = 161,        /* INTERFACETYPELIST  */
  YYSYMBOL_CLASSPERMITS = 162,             /* CLASSPERMITS  */
  YYSYMBOL_TYPENAMES = 163,                /* TYPENAMES  */
  YYSYMBOL_CLASSBODY = 164,                /* CLASSBODY  */
  YYSYMBOL_CLASSBODYDECLARATIONS = 165,    /* CLASSBODYDECLARATIONS  */
  YYSYMBOL_CLASSBODYDECLARATION = 166,     /* CLASSBODYDECLARATION  */
  YYSYMBOL_CLASSMEMBERDECLARATION = 167,   /* CLASSMEMBERDECLARATION  */
  YYSYMBOL_FIELDDECLARATION = 168,         /* FIELDDECLARATION  */
  YYSYMBOL_VARIABLEDECLARATORLIST = 169,   /* VARIABLEDECLARATORLIST  */
  YYSYMBOL_VARIABLEDECLARATOR = 170,       /* VARIABLEDECLARATOR  */
  YYSYMBOL_VARIABLEDECLARATORID = 171,     /* VARIABLEDECLARATORID  */
  YYSYMBOL_VARIABLEINITIALIZER = 172,      /* VARIABLEINITIALIZER  */
  YYSYMBOL_EXPRESSION = 173,               /* EXPRESSION  */
  YYSYMBOL_ASSIGNMENTEXPRESSION = 174,     /* ASSIGNMENTEXPRESSION  */
  YYSYMBOL_ASSIGNMENT = 175,               /* ASSIGNMENT  */
  YYSYMBOL_LEFTHANDSIDE = 176,             /* LEFTHANDSIDE  */
  YYSYMBOL_ASSIGNMENTOPERATOR = 177,       /* ASSIGNMENTOPERATOR  */
  YYSYMBOL_FIELDACCESS = 178,              /* FIELDACCESS  */
  YYSYMBOL_PRIMARY = 179,                  /* PRIMARY  */
  YYSYMBOL_PRIMARYNONEWARRAY = 180,        /* PRIMARYNONEWARRAY  */
  YYSYMBOL_LITERAL = 181,                  /* LITERAL  */
  YYSYMBOL_CLASSLITERAL = 182,             /* CLASSLITERAL  */
  YYSYMBOL_SQUARESTAR = 183,               /* SQUARESTAR  */
  YYSYMBOL_CLASSINSTANCECREATIONEXPRESSION = 184, /* CLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION = 185, /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_CLASSORINTERFACETYPETOINSTANTIATE = 186, /* CLASSORINTERFACETYPETOINSTANTIATE  */
  YYSYMBOL_ARGUMENTLIST = 187,             /* ARGUMENTLIST  */
  YYSYMBOL_METHODINVOCATION = 188,         /* METHODINVOCATION  */
  YYSYMBOL_METHODREFERENCE = 189,          /* METHODREFERENCE  */
  YYSYMBOL_ARRAYCREATIONEXPRESSION = 190,  /* ARRAYCREATIONEXPRESSION  */
  YYSYMBOL_ARRAYINITIALIZER = 191,         /* ARRAYINITIALIZER  */
  YYSYMBOL_ARRAYINITIALIZER1 = 192,        /* ARRAYINITIALIZER1  */
  YYSYMBOL_DIMEXPRS = 193,                 /* DIMEXPRS  */
  YYSYMBOL_DIMEXPR = 194,                  /* DIMEXPR  */
  YYSYMBOL_VARIABLEINITIALIZERLIST = 195,  /* VARIABLEINITIALIZERLIST  */
  YYSYMBOL_ARRAYACCESS = 196,              /* ARRAYACCESS  */
  YYSYMBOL_CONDITIONALEXPRESSION = 197,    /* CONDITIONALEXPRESSION  */
  YYSYMBOL_CONDITIONALOREXPRESSION = 198,  /* CONDITIONALOREXPRESSION  */
  YYSYMBOL_CONDITIONALANDEXPRESSION = 199, /* CONDITIONALANDEXPRESSION  */
  YYSYMBOL_INCLUSIVEOREXPRESSION = 200,    /* INCLUSIVEOREXPRESSION  */
  YYSYMBOL_EXCLUSIVEOREXPRESSION = 201,    /* EXCLUSIVEOREXPRESSION  */
  YYSYMBOL_ANDEXPRESSION = 202,            /* ANDEXPRESSION  */
  YYSYMBOL_EQUALITYEXPRESSION = 203,       /* EQUALITYEXPRESSION  */
  YYSYMBOL_RELATIONALEXPRESSION = 204,     /* RELATIONALEXPRESSION  */
  YYSYMBOL_SHIFTEXPRESSION = 205,          /* SHIFTEXPRESSION  */
  YYSYMBOL_ADDITIVEEXPRESSION = 206,       /* ADDITIVEEXPRESSION  */
  YYSYMBOL_MULTIPLICATIVEEXPRESSION = 207, /* MULTIPLICATIVEEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSION = 208,          /* UNARYEXPRESSION  */
  YYSYMBOL_PREINCREMENTEXPRESSION = 209,   /* PREINCREMENTEXPRESSION  */
  YYSYMBOL_PREDECREMENTEXPRESSION = 210,   /* PREDECREMENTEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSIONNOTPLUSMINUS = 211, /* UNARYEXPRESSIONNOTPLUSMINUS  */
  YYSYMBOL_POSTFIXEXPRESSION = 212,        /* POSTFIXEXPRESSION  */
  YYSYMBOL_POSTINCREMENTEXPRESSION = 213,  /* POSTINCREMENTEXPRESSION  */
  YYSYMBOL_POSTDECREMENTEXPRESSION = 214,  /* POSTDECREMENTEXPRESSION  */
  YYSYMBOL_INSTANCEOFEXPRESSION = 215,     /* INSTANCEOFEXPRESSION  */
  YYSYMBOL_METHODDECLARATION = 216,        /* METHODDECLARATION  */
  YYSYMBOL_METHODHEADER = 217,             /* METHODHEADER  */
  YYSYMBOL_THROWS2 = 218,                  /* THROWS2  */
  YYSYMBOL_EXCEPTIONTYPELIST = 219,        /* EXCEPTIONTYPELIST  */
  YYSYMBOL_EXCEPTIONTYPE = 220,            /* EXCEPTIONTYPE  */
  YYSYMBOL_METHODDECLARATOR = 221,         /* METHODDECLARATOR  */
  YYSYMBOL_RECEIVERPARAMETER = 222,        /* RECEIVERPARAMETER  */
  YYSYMBOL_FORMALPARAMETERLIST = 223,      /* FORMALPARAMETERLIST  */
  YYSYMBOL_FORMALPARAMETER = 224,          /* FORMALPARAMETER  */
  YYSYMBOL_VARIABLEARITYPARAMETER = 225,   /* VARIABLEARITYPARAMETER  */
  YYSYMBOL_METHODBODY = 226,               /* METHODBODY  */
  YYSYMBOL_INSTANCEINITIALIZER = 227,      /* INSTANCEINITIALIZER  */
  YYSYMBOL_STATICINITIALIZER = 228,        /* STATICINITIALIZER  */
  YYSYMBOL_BLOCK = 229,                    /* BLOCK  */
  YYSYMBOL_BLOCKSTATEMENTS = 230,          /* BLOCKSTATEMENTS  */
  YYSYMBOL_BLOCKSTATEMENT = 231,           /* BLOCKSTATEMENT  */
  YYSYMBOL_LOCALCLASSORINTERFACEDECLARATION = 232, /* LOCALCLASSORINTERFACEDECLARATION  */
  YYSYMBOL_LOCALVARIABLEDECLARATIONSTATEMENT = 233, /* LOCALVARIABLEDECLARATIONSTATEMENT  */
  YYSYMBOL_LOCALVARIABLEDECLARATION = 234, /* LOCALVARIABLEDECLARATION  */
  YYSYMBOL_LOCALVARIABLETYPE = 235,        /* LOCALVARIABLETYPE  */
  YYSYMBOL_STATEMENT = 236,                /* STATEMENT  */
  YYSYMBOL_STATEMENTWITHOUTTRAILINGSUBSTATEMENT = 237, /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
  YYSYMBOL_EMPTYSTATEMENT = 238,           /* EMPTYSTATEMENT  */
  YYSYMBOL_EXPRESSIONSTATEMENT = 239,      /* EXPRESSIONSTATEMENT  */
  YYSYMBOL_STATEMENTEXPRESSION = 240,      /* STATEMENTEXPRESSION  */
  YYSYMBOL_ASSERTSTATEMENT = 241,          /* ASSERTSTATEMENT  */
  YYSYMBOL_BREAKSTATEMENT = 242,           /* BREAKSTATEMENT  */
  YYSYMBOL_CONTINUESTATEMENT = 243,        /* CONTINUESTATEMENT  */
  YYSYMBOL_RETURNSTATEMENT = 244,          /* RETURNSTATEMENT  */
  YYSYMBOL_THROWSTATEMENT = 245,           /* THROWSTATEMENT  */
  YYSYMBOL_YIELDSTATEMENT = 246,           /* YIELDSTATEMENT  */
  YYSYMBOL_LABELEDSTATEMENT = 247,         /* LABELEDSTATEMENT  */
  YYSYMBOL_IFTHENSTATEMENT = 248,          /* IFTHENSTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENT = 249,      /* IFTHENELSESTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENTNOSHORTIF = 250, /* IFTHENELSESTATEMENTNOSHORTIF  */
  YYSYMBOL_STATEMENTNOSHORTIF = 251,       /* STATEMENTNOSHORTIF  */
  YYSYMBOL_LABELEDSTATEMENTNOSHORTIF = 252, /* LABELEDSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENTNOSHORTIF = 253,  /* WHILESTATEMENTNOSHORTIF  */
  YYSYMBOL_FORSTATEMENTNOSHORTIF = 254,    /* FORSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENT = 255,           /* WHILESTATEMENT  */
  YYSYMBOL_FORSTATEMENT = 256,             /* FORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENT = 257,        /* BASICFORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENTNOSHORTIF = 258, /* BASICFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_ENHANCEDFORSTATEMENT = 259,     /* ENHANCEDFORSTATEMENT  */
  YYSYMBOL_ENHANCEDFORSTATEMENTNOSHORTIF = 260, /* ENHANCEDFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_FORINIT = 261,                  /* FORINIT  */
  YYSYMBOL_FORUPDATE = 262,                /* FORUPDATE  */
  YYSYMBOL_STATEMENTEXPRESSIONLIST = 263,  /* STATEMENTEXPRESSIONLIST  */
  YYSYMBOL_CONSTRUCTORDECLARATION = 264,   /* CONSTRUCTORDECLARATION  */
  YYSYMBOL_CONSTRUCTORDECLARATOR = 265,    /* CONSTRUCTORDECLARATOR  */
  YYSYMBOL_SIMPLETYPENAME = 266,           /* SIMPLETYPENAME  */
  YYSYMBOL_CONSTRUCTORBODY = 267,          /* CONSTRUCTORBODY  */
  YYSYMBOL_EXPLICITCONSTRUCTORINVOCATION = 268, /* EXPLICITCONSTRUCTORINVOCATION  */
  YYSYMBOL_SUPER1 = 269,                   /* SUPER1  */
  YYSYMBOL_SUPER2 = 270,                   /* SUPER2  */
  YYSYMBOL_SUPER3 = 271,                   /* SUPER3  */
  YYSYMBOL_FIELDMODIFIERS = 272,           /* FIELDMODIFIERS  */
  YYSYMBOL_METHODMODIFIERS = 273,          /* METHODMODIFIERS  */
  YYSYMBOL_TYPEARGUMENTS = 274,            /* TYPEARGUMENTS  */
  YYSYMBOL_TYPEARGUMENTLIST = 275,         /* TYPEARGUMENTLIST  */
  YYSYMBOL_TYPEARGUMENT = 276,             /* TYPEARGUMENT  */
  YYSYMBOL_WILDCARD = 277,                 /* WILDCARD  */
  YYSYMBOL_WILDCARDBOUNDS = 278,           /* WILDCARDBOUNDS  */
  YYSYMBOL_INTERFACETYPE = 279             /* INTERFACETYPE  */
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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   6248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  153
/* YYNRULES -- Number of rules.  */
#define YYNRULES  605
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1146

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
       0,   235,   235,   236,   249,   250,   252,   253,   255,   256,
     258,   259,   260,   261,   262,   264,   265,   267,   269,   271,
     273,   276,   277,   279,   286,   303,   306,   307,   309,   350,
     351,   352,   354,   355,   356,   357,   359,   362,   363,   364,
     365,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   497,   498,   499,   501,   502,
     504,   505,   507,   508,   509,   510,   511,   513,   516,   518,
     519,   521,   522,   525,   526,   528,   529,   531,   533,   535,
     536,   538,   540,   541,   543,   544,   546,   547,   549,   550,
     551,   552,   554,   555,   556,   557,   558,   560,   586,   610,
     636,   674,   686,   710,   742,   744,   752,   759,   760,   762,
     764,   767,   769,   784,   785,   793,   794,   798,   800,   802,
     804,   806,   808,   811,   818,   819,   821,   824,   826,   827,
     828,   832,   833,   834,   835,   836,   837,   838,   840,   841,
     842,   843,   844,   845,   846,   848,   849,   850,   851,   852,
     853,   854,   856,   857,   859,   860,   861,   862,   864,   865,
     866,   867,   868,   869,   870,   871,   873,   876,   880,   889,
     901,   920,   942,   966,   967,   968,   969,   970,   971,   972,
     973,   974,   975,   976,   977,   978,   979,   980,   981,   982,
     983,   985,   986,   987,   988,   989,   991,   992,   994,   995,
     996,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,
    1007,  1009,  1010,  1012,  1013,  1014,  1016,  1017,  1021,  1023,
    1024,  1030,  1031,  1048,  1062,  1063,  1065,  1066,  1080,  1081,
    1091,  1092,  1101,  1102,  1110,  1111,  1121,  1129,  1145,  1163,
    1168,  1186,  1200,  1214,  1228,  1230,  1231,  1240,  1248,  1257,
    1258,  1266,  1275,  1276,  1284,  1292,  1301,  1302,  1303,  1306,
    1314,  1316,  1330,  1344,  1345,  1353,  1362,  1363,  1364,  1378,
    1379,  1381,  1394,  1409,  1412,  1431,  1453,  1473,  1493,  1513,
    1514,  1515,  1516,  1517,  1520,  1534,  1548,  1549,  1550,  1551,
    1552,  1553,  1556,  1558,  1559,  1561,  1563,  1570,  1576,  1577,
    1578,  1579,  1580,  1581,  1583,  1584,  1586,  1590,  1596,  1600,
    1601,  1607,  1608,  1611,  1612,  1614,  1616,  1618,  1619,  1621,
    1624,  1635,  1636,  1639,  1642,  1644,  1646,  1702,  1761,  1762,
    1765,  1766,  1767,  1768,  1769,  1770,  1772,  1774,  1775,  1776,
    1777,  1778,  1779,  1780,  1781,  1783,  1785,  1787,  1788,  1789,
    1790,  1791,  1792,  1793,  1795,  1796,  1798,  1806,  1808,  1816,
    1818,  1824,  1831,  1833,  1835,  1837,  1854,  1866,  1878,  1879,
    1880,  1881,  1882,  1884,  1886,  1898,  1899,  1902,  1913,  1914,
    1916,  1924,  1935,  1949,  1965,  1978,  1994,  2010,  2027,  2035,
    2046,  2060,  2077,  2090,  2106,  2123,  2141,  2143,  2145,  2146,
    2148,  2158,  2159,  2168,  2169,  2170,  2171,  2174,  2175,  2176,
    2177,  2178,  2179,  2180,  2181,  2184,  2186,  2187,  2188,  2189,
    2191,  2192,  2193,  2194,  2195,  2196,  2197,  2198,  2199,  2200,
    2201,  2202,  2203,  2204,  2205,  2206,  2207,  2208,  2209,  2210,
    2212,  2213,  2214,  2215,  2216,  2217,  2219,  2220,  2221,  2222,
    2223,  2224,  2225,  2226,  2227,  2229,  2230,  2231,  2232,  2233,
    2234,  2235,  2236,  2237,  2238,  2239,  2241,  2242,  2243,  2244,
    2245,  2246,  2247,  2248,  2249,  2252,  2253,  2254,  2255,  2256,
    2257,  2258,  2259,  2260,  2261,  2262,  2264,  2266,  2267,  2269,
    2270,  2272,  2273,  2275,  2276,  2279
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
  "NORMALINTERFACEDECLARATION", "FOR", "OPENCURLY", "CLOSECURLY",
  "INTERFACEBODY", "INTERFACEMEMBERDECLARATIONS",
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

#define YYPACT_NINF (-804)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-526)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     674,  -804,   -93,  -804,  -804,  -804,  -804,  -804,  -804,  -804,
     161,   -77,  -804,    78,  2035,  -804,   876,  -804,  -804,  -804,
    -804,  1443,   717,  1001,   283,   -54,   177,    57,   283,  -804,
    -804,  -804,  -804,   105,  -804,  -804,  -804,  -804,  -804,   109,
     134,  -804,  -804,  -804,  -804,  -804,  -804,  -804,   165,   173,
    -804,  -804,  -804,  -804,  -804,  -804,  -804,   185,  -804,   204,
     220,   220,   254,  1269,   286,   192,    49,   368,  -804,    74,
     279,  -804,    91,  3305,  -804,   286,   192,    49,   368,   283,
     283,   283,   283,   283,   283,   350,   315,  -804,  -804,  -804,
    -804,  -804,   407,  -804,  -804,   430,  -804,  -804,  -804,  -804,
    -804,  -804,  -804,  -804,  -804,  -804,   399,   368,   347,   472,
     373,  -804,  -804,  -804,  -804,  -804,  -804,  -804,  -804,  3412,
    -804,  -804,  1260,  1269,  -804,  -804,  -804,  -804,   393,  -804,
    -804,  -804,  -804,    31,   480,   580,  3766,  2210,  1451,  4011,
     192,    49,   368,  -804,    49,   368,  -804,   368,  -804,  -804,
    -804,   155,  -804,   490,  -804,  -804,   744,   347,  -804,  -804,
    3305,  -804,  1795,  -804,   653,  4266,  1968,  -804,   192,    49,
     368,  -804,    49,   368,  -804,   368,  -804,   286,   192,    49,
     368,  -804,  -804,   286,   192,    49,   368,   286,   192,    49,
     368,  -804,  -804,   286,   192,    49,   368,   286,   192,    49,
     368,  -804,  -804,   286,   192,    49,   368,   385,  -804,   204,
    -804,   220,   388,  4388,  -804,  1203,   417,   446,   349,  -804,
     496,   417,    11,  -804,  5671,  5733,  5733,  -804,  -804,  -804,
    -804,  -804,  -804,  -804,    38,  1780,  -804,   401,  1810,  5671,
    5671,  -804,    15,    27,  3671,  5671,   546,   553,  -804,  1126,
    -804,    39,   573,   589,   794,  -804,   595,  -804,  -804,   979,
    1090,   273,   616,  -804,  -804,   448,  -804,   484,  -804,  -804,
    1162,  -804,  -804,   397,   410,   483,  -804,  3412,  -804,  -804,
    -804,   625,   518,  -804,  -804,  -804,  -804,   641,  -804,  -804,
    -804,  -804,  -804,  -804,  -804,  -804,  -804,  -804,  -804,  -804,
    -804,  1013,   787,   839,   347,   347,   693,  -804,  -804,  -804,
    -804,  -804,   220,  3269,   368,  -804,   911,   373,   393,    31,
     373,   393,  -804,  -804,  -804,  -804,   393,  -804,  -804,  -804,
    -804,  -804,  -804,  -804,   518,  -804,  -804,  -804,  -804,  -804,
    -804,  -804,  -804,  -804,   393,    49,   368,  -804,   368,  -804,
    -804,   368,  -804,  -804,  -804,   660,  -804,   393,  -804,  -804,
     373,  -804,    49,   368,  -804,   368,  -804,  -804,   368,  -804,
    -804,   192,    49,   368,  -804,    49,   368,  -804,   368,  -804,
    -804,  -804,   192,    49,   368,  -804,    49,   368,  -804,   368,
    -804,   192,    49,   368,  -804,    49,   368,  -804,   368,  -804,
    -804,  -804,   192,    49,   368,  -804,    49,   368,  -804,   368,
    -804,   192,    49,   368,  -804,    49,   368,  -804,   368,  -804,
    -804,  -804,   192,    49,   368,  -804,    49,   368,  -804,   368,
    -804,   649,   686,  -804,  -804,  -804,   393,   952,  4510,  4144,
    4011,  1427,   191,   722,  -804,   721,   737,   518,  -804,  3745,
    -804,   738,  -804,    54,    11,  5733,  5733,  5733,  5733,  2389,
      39,   573,   735,  -804,  -804,  -804,  -804,  -804,    47,   712,
     723,   724,   725,   491,    20,   427,   545,   354,  -804,  -804,
    -804,  -804,   397,  -804,  -804,  -804,    55,   200,  -804,  -804,
    -804,  -804,    58,    69,   518,  -804,    46,   749,   752,   752,
     755,   665,   759,   249,  -804,   765,  -804,   766,  -804,   770,
     776,  5671,  5671,  3103,  3501,   157,  -804,    68,  -804,    72,
     106,  3805,  5671,   178,  2484,  -804,  -804,  -804,  -804,  -804,
    -804,  5671,    81,   184,  5671,  -804,  -804,  -804,  -804,  -804,
     772,   780,  -804,   417,   417,  1461,  -804,   783,  -804,   298,
     775,  1281,   320,  -804,   280,  3412,  3412,   162,  -804,  -804,
    1952,   187,   790,   304,  -804,  -804,   360,  -804,   368,  -804,
     548,  -804,  -804,   593,  -804,   368,  -804,  -804,  -804,  -804,
    -804,  -804,   622,  -804,   368,  -804,  -804,  -804,    49,   368,
    -804,   368,  -804,  -804,   368,  -804,  -804,  -804,  -804,    49,
     368,  -804,   368,  -804,  -804,   368,  -804,  -804,    49,   368,
    -804,   368,  -804,  -804,   368,  -804,  -804,  -804,  -804,    49,
     368,  -804,   368,  -804,  -804,   368,  -804,  -804,    49,   368,
    -804,   368,  -804,  -804,   368,  -804,  -804,  -804,  -804,    49,
     368,  -804,   368,  -804,  -804,   368,  -804,  -804,   220,   760,
    -804,   393,   393,   393,   393,   772,    10,   382,  -804,   754,
     782,  -804,   785,  -804,  2729,  -804,  -804,  -804,  -804,   788,
    -804,  -804,  -804,  -804,  -804,  -804,  5671,  5733,  5733,  5733,
    5733,  5733,  5733,  5733,  3867,  3927,   220,  5733,  5733,  5733,
    5733,  5733,  5733,  5733,  5733,  -804,   683,   791,   690,   780,
     585,  -804,   340,  -804,  -804,  3989,    50,   752,  -804,    50,
     752,  4049,  -804,   798,  -804,  -804,  5671,  -804,  -804,  -804,
    -804,   807,   810,   815,  -804,   319,  -804,    90,   816,  -804,
     726,  -804,  -804,  -804,  -804,    86,  -804,  -804,   408,   818,
     826,  -804,   731,  4123,  1780,   795,  -804,   834,   848,  -804,
    -804,   739,   841,  -804,   740,   846,  -804,  -804,  -804,   855,
     409,   220,  4183,  4245,   257,   384,   406,  -804,  -804,  3412,
     854,   856,    60,   756,   250,  -804,  1556,  1931,  -804,  -804,
    -804,  -804,  -804,  -804,  -804,  -804,   368,  -804,  -804,  -804,
    -804,  -804,   368,  -804,  -804,  -804,   368,  -804,  -804,  -804,
    -804,  -804,   368,  -804,  -804,  -804,   368,  -804,  -804,  -804,
    -804,  -804,   368,  -804,  -804,  -804,  -804,   220,  -804,  -804,
    -804,  -804,   737,   772,   806,  1611,  -804,  -804,  -804,  -804,
     866,   871,  -804,   843,   712,   723,   724,   725,   491,    20,
      20,  5733,   427,  5733,   427,  -804,   545,   545,   545,   354,
     354,  -804,  -804,  -804,  -804,  4305,   867,   220,   220,  -804,
      46,  -804,   869,  -804,   737,  -804,  -804,   737,   368,   415,
    4367,   878,  3586,  3501,  -804,    94,    99,  4427,   872,  -804,
    -804,  5671,  -804,  -804,  4489,   873,  5793,   882,  5671,  4549,
    6125,  -804,  4611,   880,  -804,  1639,  -804,  -804,   885,   426,
     899,   460,   366,   122,   902,   125,   903,   140,  -804,  4671,
    4733,   801,  -804,  -804,  -804,   498,  -804,  -804,  -804,  -804,
    -804,  -804,  -804,  -804,   737,  -804,   772,   511,  -804,  3745,
    5733,   427,   427,  -804,   513,  4793,  -804,  -804,  -804,  -804,
    -804,   368,   368,   526,  -804,   905,   906,   365,   913,  -804,
     844,  -804,   849,  -804,  -804,  -804,  -804,  -804,  -804,  -804,
     808,   923,   827,  -804,   547,  4855,  -804,  -804,   554,  4915,
    3501,   932,   848,  5816,   942,  5876,   958,  -804,  -804,   559,
    4977,  -804,   592,  -804,   961,  -804,   962,  5037,   945,  5099,
     957,  5159,   960,   965,   599,   971,   619,  -804,  -804,   737,
     772,  -804,  -804,  -804,  -804,   631,  -804,  -804,   368,  5671,
    5671,  3586,  2885,  3501,  -804,  5221,   969,  -804,  -804,   655,
    -804,  -804,   656,  -804,  3501,  3501,   972,  3501,  3501,   977,
    5899,  -804,  -804,   661,  -804,  -804,  -804,   990,   663,  5281,
     991,   664,  5343,  1002,   668,  5403,  -804,  1005,  -804,  1006,
     737,  -804,  -804,  1004,  1007,  -804,  5477,   950,  1010,  -804,
    -804,   669,  5537,  -804,  -804,  -804,  -804,  3501,  -804,  -804,
    3501,  3501,  1008,  -804,  -804,  1017,  1018,   703,  -804,  1019,
    1020,   709,  -804,  1024,  1028,   714,  -804,  -804,  3586,  3586,
    5959,  1032,  5671,  5611,  -804,  -804,   715,  -804,  -804,  -804,
    3501,  -804,  -804,  1033,  -804,  -804,  1035,  -804,  -804,  1038,
     941,  -804,  3586,  1036,  5982,  1046,  6042,  1043,  -804,  -804,
    -804,  -804,  -804,  3586,  -804,  3586,  3586,  1052,  3586,  3586,
    1053,  6065,  -804,  -804,  -804,  3586,  -804,  -804,  3586,  3586,
    1058,  -804,  -804,  -804,  3586,  -804
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    29,     0,   550,   551,   552,   556,   557,   565,   566,
       0,     0,     2,     0,     0,    26,     0,    28,    36,   177,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       3,    27,    30,     0,   553,   554,   555,   558,   559,     0,
       0,   562,   563,   564,   560,   561,   567,   568,     0,     0,
     571,   572,   573,   574,   575,   569,   570,     0,   166,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
       0,    32,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,     0,   179,    20,   187,
      19,   605,   188,   189,   192,   191,     7,    10,    11,    12,
      13,    14,    15,    16,   205,   167,     0,   556,     0,    20,
       0,     4,     6,     8,     9,     5,    17,    18,   204,     0,
     194,   206,     0,     0,   196,   198,   202,   203,     0,   199,
     200,   425,   201,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,    52,     0,    54,    55,
      34,     0,    24,     0,    25,   176,     0,     0,   175,   168,
       0,   170,     0,   172,     0,     0,     0,   108,     0,     0,
       0,   112,     0,     0,   114,     0,   115,     0,     0,     0,
       0,    38,   132,     0,     0,     0,     0,     0,     0,     0,
       0,    39,   148,     0,     0,     0,     0,     0,     0,     0,
       0,    40,   164,     0,     0,     0,     0,     0,   181,     0,
     178,     0,     0,     0,   426,     0,   395,   215,     0,   211,
     214,   394,     7,   455,     0,     0,     0,   248,   249,   250,
     251,   252,   253,   254,     0,   557,   240,     0,     0,     0,
       0,   439,     0,     0,     0,     0,     0,     0,   165,   224,
     438,     6,    18,     0,   377,   434,     0,   428,   457,     0,
     244,   376,   236,   238,   239,   243,   264,   246,   247,   237,
     245,   458,   459,     0,   460,   461,   446,     0,   429,   431,
     432,     0,     0,   433,   440,   447,   448,     0,   449,   450,
     451,   452,   453,   454,   441,   442,   443,   444,   445,   488,
     489,     0,     0,     0,     0,     0,     0,   195,   197,   424,
     384,   423,     0,     0,     0,   514,     0,     0,     0,     0,
       0,     0,   576,   577,   585,   586,     0,   580,   581,   582,
     583,   584,   578,   579,     0,   591,   592,   593,   594,   595,
     589,   587,   588,   590,     0,     0,     0,    44,     0,    46,
      47,     0,    50,    51,    53,     0,    33,     0,   169,   171,
       0,   104,     0,     0,   106,     0,   107,   110,     0,   111,
     113,     0,     0,     0,    63,     0,     0,    67,     0,    69,
      70,   124,     0,     0,     0,   128,     0,     0,   130,     0,
     131,     0,     0,     0,    78,     0,     0,    82,     0,    84,
      85,   140,     0,     0,     0,   144,     0,     0,   146,     0,
     147,     0,     0,     0,    93,     0,     0,    97,     0,    99,
     100,   156,     0,     0,     0,   160,     0,     0,   162,     0,
     163,   183,     0,   180,   190,   193,     0,     0,     0,     0,
       0,     0,     0,     0,   399,     0,   216,     0,   210,     0,
     396,     0,   257,     0,     0,     0,     0,     0,     0,   378,
       0,     0,     0,   219,   221,   243,   246,   220,   334,   336,
     338,   340,   342,   344,   346,   349,   355,   359,   362,   366,
     367,   370,   373,   379,   380,   354,   378,   377,   244,   245,
     371,   372,     0,     0,     0,   258,     0,    20,   319,   320,
       0,     0,     0,     0,   466,     0,   468,     0,   471,     0,
       0,     0,     0,     0,     0,     0,   255,     0,   256,     0,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,     0,     0,     0,     0,   381,   382,   427,   430,   435,
     215,   437,   456,   401,   398,     0,   405,   402,   403,     0,
     240,   224,   223,   529,   376,     0,     0,     0,   513,   517,
       0,     0,     0,     0,   416,   419,     0,   385,     0,   516,
       0,   386,   387,     0,   388,     0,    42,    43,    45,    49,
      35,   173,     0,   102,     0,   103,   105,   109,     0,     0,
      59,     0,    61,    62,     0,    65,    66,    68,   120,     0,
       0,   122,     0,   123,   126,     0,   127,   129,     0,     0,
      74,     0,    76,    77,     0,    80,    81,    83,   136,     0,
       0,   138,     0,   139,   142,     0,   143,   145,     0,     0,
      89,     0,    91,    92,     0,    95,    96,    98,   152,     0,
       0,   154,     0,   155,   158,     0,   159,   161,     0,   184,
     389,     0,     0,     0,     0,   406,     0,     0,   414,     0,
       0,    21,     0,   212,     0,   213,   217,   218,   262,     0,
     261,   368,   369,   375,   374,   242,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   308,     0,   234,     0,   436,
     601,   599,     0,   597,   600,     0,   317,   315,   326,   318,
     316,     0,   276,     0,   472,   464,     0,   467,   469,   470,
     473,     0,     0,     0,   474,     0,   241,     0,    24,   266,
       0,   259,   260,   310,   306,     0,   279,   277,     0,     0,
      25,   265,     0,     0,     0,   509,   511,     0,   508,   222,
     307,     0,   233,   267,     0,     0,   400,   397,   521,     0,
       0,     0,     0,     0,     0,     0,     0,   528,   527,     0,
       0,     0,     0,     0,   215,   418,     0,     0,   518,   208,
     515,   209,   207,    41,   174,   101,     0,    57,    58,    60,
      64,   118,     0,   119,   121,   125,     0,    72,    73,    75,
      79,   134,     0,   135,   137,   141,     0,    87,    88,    90,
      94,   150,     0,   151,   153,   157,   185,     0,   390,   391,
     392,   393,   409,   407,     0,     0,    22,   324,   322,   329,
       0,   323,   263,     0,   337,   339,   341,   343,   345,   347,
     348,     0,   350,     0,   351,   383,   356,   357,   358,   360,
     361,   364,   363,   365,   303,     0,     0,     0,     0,   602,
       0,   596,     0,   313,   311,   327,   314,   312,   268,     0,
       0,     0,     0,     0,   333,     0,     0,     0,     0,   305,
     302,     0,   280,   331,     0,     0,     0,     0,     0,     0,
       0,   301,     0,     0,   332,     0,   522,   404,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   526,     0,
       0,     0,   420,   421,   519,     0,   417,    56,   117,    71,
     133,    86,   149,   186,   411,   415,   408,     0,   321,   325,
       0,   353,   352,   293,     0,     0,   603,   604,   598,   328,
     269,   270,   272,     0,   465,     0,     0,   224,     0,   475,
     440,   480,     0,   479,   481,   482,   485,   486,   487,   309,
       0,   235,     0,   281,     0,     0,   278,   285,     0,     0,
       0,     0,   510,     0,     0,     0,     0,   512,   289,     0,
       0,   523,     0,   534,     0,   530,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   422,   520,   410,
     413,   330,   335,   294,   295,     0,   271,   273,   274,     0,
       0,     0,     0,     0,   304,     0,     0,   282,   283,     0,
     286,   287,     0,   490,     0,     0,     0,     0,     0,     0,
       0,   290,   291,     0,   524,   535,   531,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   536,     0,   532,     0,
     412,   296,   275,     0,     0,   483,     0,   509,     0,   476,
     297,     0,     0,   284,   288,   491,   492,     0,   506,   494,
       0,     0,     0,   292,   542,     0,     0,     0,   538,     0,
       0,     0,   546,     0,     0,     0,   537,   533,     0,     0,
       0,     0,     0,     0,   298,   299,     0,   493,   495,   496,
       0,   543,   544,     0,   539,   540,     0,   547,   548,     0,
       0,   484,     0,     0,     0,     0,     0,     0,   300,   497,
     545,   541,   549,     0,   498,     0,     0,     0,     0,     0,
       0,     0,   477,   499,   500,     0,   507,   502,     0,     0,
       0,   501,   503,   504,     0,   505
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -804,  -804,   -10,   853,  1950,  -804,  -804,  -488,  -103,  1709,
    -804,  -484,  -804,    17,  -804,   672,  -804,    80,  -804,  -804,
    -296,   -28,   -57,  2262,  -804,   926,   149,  2089,  -804,   884,
    -804,  -804,   789,  2634,  -804,  2845,  -804,  2225,  -804,   964,
    -804,  -804,  -171,   647,  -537,  -659,   666,  -804,   -76,  -804,
    -804,   909,   786,  -804,  -804,  -804,  -213,   115,  -489,   601,
    2207,   285,  -804,  -804,  -266,  -804,   597,  -245,  -804,  1638,
     175,  -804,   429,   425,   444,   428,   449,    63,  -653,  -204,
      41,  -205,   414,   600,  -804,   767,   939,  1109,  -804,    35,
      -5,  -198,  -804,   348,   -89,  -306,  -428,   352,  -804,  -237,
    -804,  -804,   -52,  -301,  -276,  -804,  -804,  -521,  -231,  -507,
      24,  -804,  -804,  -463,  -804,  -804,  -804,  -804,  -804,  -804,
    -804,  -804,  -804,  -804,  -587,  -804,  -804,  -804,  -804,  -804,
    -804,  -804,  -804,  -804,   113,  -803,  -518,  -804,   996,  1011,
    -297,  -804,    25,    51,   123,  -804,   919,  -211,  -804,   277,
    -804,  -804,  -209
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,   157,   111,   460,   113,   114,   115,   116,   461,
      90,   446,   253,   254,    14,    15,    16,   255,    18,    19,
     256,    63,   120,    74,   160,   161,    20,   162,    86,    87,
     208,   649,    65,    66,    92,    67,    95,    68,   123,   124,
     125,   126,   218,   219,   220,   665,   737,   463,   464,   259,
     531,   260,   261,   262,   263,   264,   517,   465,   266,   500,
     738,   466,   268,   269,   667,   830,   707,   708,   831,   270,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   127,
     128,   314,   547,   548,   221,   443,   563,   564,   565,   310,
     129,   130,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   951,   952,   953,   954,   955,   297,   298,
     299,   956,   300,   957,   747,   971,   972,   132,   133,   134,
     315,   556,   301,   302,   303,   138,   139,   501,   702,   703,
     704,   859,    93
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,   538,   434,   745,   494,   829,   748,   724,   701,   453,
     562,   131,   555,   657,   706,   709,   159,   558,   444,   216,
     490,   491,   569,   450,   775,    21,   729,    27,   504,   451,
      24,   842,   844,   773,   741,   119,   684,   685,   519,    21,
     506,    21,    69,   258,   753,    58,    28,    73,    73,    73,
      73,    22,    73,   110,    73,   214,    73,   451,   700,   676,
     492,   746,   257,    58,    58,    22,   307,    22,   662,    26,
      71,   131,   669,   513,   496,   -23,   311,   -20,    29,   119,
      17,   567,   493,   911,   571,   496,   669,   150,   135,   572,
     669,   119,   677,   686,    17,   119,    17,   496,   164,   515,
     119,    72,   557,   358,   432,   313,   496,   574,   163,   250,
     496,   541,   305,   110,   136,   496,    62,   760,   151,   775,
     581,   568,   496,    23,   165,   317,   320,   153,   334,   312,
     318,   321,   326,   540,   344,   499,   452,    23,   505,    23,
      73,    73,    73,   118,    73,    73,   566,    73,   135,   570,
     507,   357,   305,   158,   360,    73,    73,    73,    73,   318,
     321,   326,   879,   573,   518,    73,    73,    73,    73,    88,
    1026,   822,  1029,   496,   136,    73,    73,    73,    73,   670,
     516,   695,   733,   540,   988,   164,   137,   990,   931,   582,
     932,   355,   697,   731,   496,   163,   166,   732,   845,   650,
     496,   258,   992,   118,   750,   442,    58,   442,   436,   880,
     773,   165,   121,   712,   154,   543,   544,   959,   522,   725,
     537,    70,   961,   864,   770,   250,   867,  1072,    79,   734,
      25,   726,    80,   727,   265,   912,   771,   258,   437,   759,
     158,   453,   487,   487,   523,   878,   137,   519,   885,   119,
     671,   672,   673,   674,   727,   769,   553,    81,    61,    62,
     727,   658,   715,   893,   438,   658,   311,   250,   445,   311,
    1001,   780,   121,   496,   311,   729,   741,   753,   154,   538,
     728,   696,   698,   166,    26,   119,   313,  1113,    82,   716,
     119,   313,   311,   119,   824,   532,    83,    58,   119,    59,
      58,   740,   532,   250,   730,   311,   561,   752,    84,   735,
     774,  1127,   742,  1130,   659,   777,   119,   533,   762,   902,
     492,   751,   754,   699,   766,   778,   209,    85,  1140,   119,
     552,   726,   210,   727,    73,    73,   439,    73,   522,   924,
      73,   875,   493,    88,    60,   756,   757,    60,   915,    61,
      62,   860,    61,    62,    73,    73,    73,   861,    73,    73,
     447,    73,   448,   876,   765,   949,   958,  -377,  -377,   936,
     937,   447,   701,   779,    73,    73,    73,    94,    73,    73,
     728,    73,    58,   513,   311,   -23,   987,   -20,   875,   692,
     693,   694,   265,   777,    73,    73,    73,   927,    73,    73,
     496,    73,   152,   823,   267,  1011,   309,    58,   119,   515,
     876,   207,  -378,  -378,   818,   819,   820,   821,   211,   881,
     777,   664,   496,   746,  1055,   213,   881,   977,   265,   882,
     896,   656,   651,   652,   653,   654,   941,   881,   258,   816,
     863,   212,   999,   866,   535,   536,   904,   984,   258,    96,
      97,    98,    99,   100,   101,   102,   103,  -379,  -379,  -463,
     727,  -463,   865,  1023,   445,   865,   441,   982,   906,  -463,
     215,   881,   487,   487,   487,   487,   687,   688,   689,   258,
     258,   986,   727,   846,   847,   848,   119,   851,   852,   853,
     516,  1057,  -525,   538,   748,  -462,   217,  -462,   767,   768,
     316,  1110,  1111,   356,   724,  -462,  1059,   740,   431,   777,
     746,   435,   746,   494,   250,   312,  1050,  1065,  1066,   998,
    1068,  1069,   777,   449,   881,  1124,   495,   119,   119,   752,
    -380,  -380,  1000,   271,  1003,   561,  1132,   881,  1133,  1134,
     313,  1136,  1137,   682,   683,   250,   250,  1008,  1141,   746,
     772,  1142,  1143,   903,   905,   907,    73,  1145,   881,   447,
    1097,   781,   267,  1098,  1099,   881,   511,   746,  1017,    88,
     881,    73,    73,   512,    73,  1020,   948,    73,   690,   691,
    1031,   949,   958,    96,    97,    98,    99,   100,   101,   102,
     103,    73,    73,  1119,    73,   520,    59,    73,   267,   311,
     311,   311,   311,   777,   447,  1023,   782,   828,   923,   521,
     881,    73,    73,  1034,    73,   524,  1059,    73,  1065,  1066,
    1047,  1068,  1069,   119,   119,   119,   119,   746,  1097,   265,
     881,  1098,  1099,   447,   534,   784,   664,  1119,   539,   265,
    1049,   540,   881,    33,    34,    35,   857,   858,    36,    37,
      38,   746,  1051,   746,   542,   108,    96,    97,    98,    99,
     100,   101,   102,   103,   960,   962,   881,   881,   746,    59,
     265,   265,   881,   580,   881,   881,  1063,  1064,   664,   881,
     881,   664,  1073,    39,  1075,  1079,    31,     1,    32,  1083,
    1094,   271,   -20,   258,   487,   487,   487,   487,   487,   487,
     487,   487,   487,   109,   487,   487,   487,   487,   487,   487,
     487,   487,   908,   545,   881,   948,    33,    34,    35,   272,
     881,    36,    37,    38,  1103,   881,   881,   271,   108,   648,
    1106,   849,   850,   660,   250,  1109,  1118,     2,     3,     4,
     661,   119,     5,     6,     7,   839,   840,    96,    97,    98,
      99,   100,   101,   102,   103,   662,   675,   668,   678,   250,
      59,   679,     8,   680,    73,     9,   656,   656,   681,  -276,
     705,    10,   714,   928,    73,   711,    88,    11,   717,   718,
      40,    41,    42,   719,    73,    43,    44,    45,   712,   720,
     445,   447,   948,   948,   761,   763,   258,   258,   824,   267,
      12,   776,   825,   817,   826,    46,   854,   832,    47,   267,
     258,   855,   522,   856,   258,   656,   948,    76,   870,   108,
      48,  -223,  -223,  -223,  -223,  -223,  -223,   948,   872,   948,
     948,   873,   948,   948,   874,   888,   877,   883,   523,   948,
     267,   267,   948,   948,   119,   119,   884,   889,   948,   878,
      40,    41,    42,   140,   885,    43,    44,    45,   487,   890,
     487,   892,   891,   893,   168,   894,   895,    88,   178,   184,
     188,   194,   198,   204,   909,    46,   910,   272,    47,   913,
     925,   105,   929,   930,   265,   656,   273,   935,   939,     1,
     462,   944,   965,   969,   258,   973,   950,   258,   983,   258,
     980,   664,    49,    50,    51,   502,   503,    52,    53,    54,
     509,   510,   985,   272,    96,    97,    98,    99,   100,   101,
     102,   103,   989,   991,   997,  1009,  1010,    55,   271,  -478,
      56,  1014,   559,  1012,  1013,   258,   258,   258,   271,     2,
       3,     4,   119,  1015,     5,     6,     7,   487,   258,   258,
    1016,   258,   258,  1024,   258,    96,    97,    98,    99,   100,
     101,   102,   103,  1027,     8,  1039,   371,     9,    59,   271,
     271,  1030,   382,    10,  1035,  1036,   391,  1042,  1046,    11,
    1045,   560,   402,   119,  1048,   119,   411,   265,   265,  1062,
    1092,   258,   422,  1067,   258,   258,   119,   119,  1070,   119,
     119,   265,   250,  1074,  1078,   265,   525,   526,   527,   528,
     529,   530,   258,   258,   258,  1082,    34,    35,  1086,  1087,
      36,    37,    38,  1093,   258,  1088,  1123,   108,  1089,  1100,
    1101,  1102,  1104,  1105,    88,   950,   258,  1107,   258,   119,
     258,  1108,   119,   119,   273,  1114,  1120,   258,  1121,   258,
     258,  1122,   258,   258,   267,   258,  1131,  1125,   274,   258,
     119,   119,   258,   258,    49,    50,    51,  1128,   258,    52,
      53,    54,   119,  1135,  1138,    88,    33,    34,    35,  1144,
     273,    36,    37,    38,   119,   265,   359,   308,   265,    55,
     265,   498,    56,   433,   663,   119,   710,   119,   119,   554,
     119,   119,   713,   835,    57,  1002,   834,   119,   837,   897,
     119,   119,   950,   950,   272,   666,   119,  -225,  -225,  -225,
    -225,  -225,  -225,   836,   272,  1058,   265,   265,   265,   916,
     838,   319,   440,   306,   488,   488,   950,   938,     0,   265,
     265,     0,   265,   265,   513,   265,   -23,   950,   -20,   950,
     950,     0,   950,   950,     0,   272,   272,   267,   267,   950,
       0,     0,   950,   950,     0,     0,   514,     0,   950,     0,
     515,   267,     0,  -378,  -378,   267,     0,   721,   722,   723,
       0,     0,   265,   271,     0,   265,   265,     0,   739,  -226,
    -226,  -226,  -226,  -226,  -226,     0,     0,   749,     0,     0,
     755,     0,     0,   265,   265,   265,    96,    97,    98,    99,
     100,   101,   102,   103,     0,   265,   274,     0,     0,     0,
       0,     0,     0,   441,     0,     0,     0,   265,   275,   265,
       0,   265,     0,     0,     0,     0,     0,     0,   265,     0,
     265,   265,     0,   265,   265,     0,   265,     0,     0,   -20,
     265,   516,   274,   265,   265,   267,     0,     0,   267,   265,
     267,     0,     0,    96,    97,    98,    99,   100,   101,   102,
     103,     0,    96,    97,    98,    99,   100,   101,   102,   103,
       0,   273,   104,    58,   105,    59,   271,   271,     0,     0,
       0,   273,     0,     0,   106,     0,   267,   267,   267,   513,
     271,   -23,     0,   -20,   271,     0,     0,     0,     0,   267,
     267,     0,   267,   267,     0,   267,     0,     0,     0,     0,
       0,   514,   273,   273,     0,   764,    88,     0,  -378,  -378,
     666,     0,     2,     3,     4,   304,     0,     5,   107,     7,
       0,     0,   833,     0,   108,     0,     0,     0,     0,     0,
       0,     0,   267,     0,     0,   267,   267,     8,     0,     0,
       9,     0,     0,     0,   488,   488,   488,   488,     0,   272,
       0,   862,    11,   267,   267,   267,     0,     0,     0,     0,
       0,     0,   871,   109,   271,   267,   275,   271,     0,   271,
       0,     0,   109,     0,     0,     0,     0,   267,     0,   267,
       0,   267,     0,     0,   -20,     0,   516,     0,   267,   887,
     267,   267,     0,   267,   267,     0,   267,     0,     0,     0,
     267,     0,   275,   267,   267,   271,   271,   271,     0,   267,
      96,    97,    98,    99,   100,   101,   102,   103,   271,   271,
       0,   271,   271,     0,   271,     0,     0,     0,   655,     0,
       0,     0,     0,   274,    96,    97,    98,    99,   100,   101,
     102,   103,     0,   274,    96,    97,    98,    99,   100,   101,
     102,   103,   272,   272,     0,     0,     0,     0,     0,     0,
       0,   271,   758,     0,   271,   271,   272,     0,     0,     0,
     272,     0,     0,     0,   274,   274,     0,   560,     0,     0,
       0,     0,   271,   271,   271,     0,    33,    34,    35,     0,
       0,    36,    37,    38,   271,   327,   328,     0,     0,   329,
     330,   331,   332,   333,     0,     0,   271,     0,   271,     0,
     271,   560,     0,     0,     0,     0,   273,   271,     0,   271,
     271,     0,   271,   271,     0,   271,    39,   966,     0,   271,
      88,     0,   271,   271,   974,   976,     0,     0,   271,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
     272,     0,     0,   272,    88,   272,     0,   914,     0,     0,
       0,     0,     0,     0,    88,     0,   488,   488,   488,   488,
     488,   488,   488,   488,   488,   666,   488,   488,   488,   488,
     488,   488,   488,   488,     0,     0,     0,     0,     0,     0,
       0,   272,   272,   272,    96,    97,    98,    99,   100,   101,
     102,   103,     0,   275,   272,   272,   560,   272,   272,     0,
     272,     0,   926,   275,     0,     0,     0,     0,     0,   273,
     273,     0,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   273,     0,     0,     0,   273,     0,     0,
     981,     0,     0,     0,   275,   275,     0,   272,     0,     0,
     272,   272,     0,     0,     0,  1053,  1054,     0,     0,    88,
       0,   560,     0,     0,     0,     0,     0,     0,   272,   272,
     272,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     272,     0,     0,     0,     0,     0,     0,     0,   274,   560,
       0,     0,   272,     0,   272,     0,   272,     0,     0,     0,
       0,     0,  1091,   272,     0,   272,   272,     0,   272,   272,
       0,   272,     0,     0,    88,   272,     0,   273,   272,   272,
     273,     0,   273,     0,   272,     0,     0,     0,     0,     0,
     488,     0,   488,     0,     0,     0,     0,     0,  1115,  1117,
       0,     0,    88,     0,     0,     0,     0,     0,     0,    89,
      91,     0,   117,     0,     0,     0,     0,     0,   273,   273,
     273,     0,   117,    96,    97,    98,    99,   100,   101,   102,
     103,   273,   273,     0,   273,   273,     0,   273,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,   274,   274,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,   274,   496,     0,   252,   274,
       0,   117,   117,     0,   273,     0,     0,   273,   273,   488,
       0,     0,     0,     0,   117,   117,   117,   117,   117,     0,
       0,     0,     0,     0,     0,   273,   273,   273,     0,   241,
       0,     0,     0,   489,   489,   117,     0,   273,     0,   117,
     304,   117,     0,   117,   117,   117,     0,     0,   275,   273,
       0,   273,     0,   273,     0,     0,     0,     0,     0,     0,
     273,     0,   273,   273,     0,   273,   273,     0,   273,     0,
       0,     0,   273,    88,     0,   273,   273,     0,     0,   274,
       0,   273,   274,     0,   274,     0,   117,     0,    88,     0,
      91,     0,   117,     0,   117,     0,   117,     0,     0,     0,
       0,     0,     0,   497,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,   117,     0,     0,   117,     0,     0,
     274,   274,   274,     0,     0,    96,    97,    98,    99,   100,
     101,   102,   103,   274,   274,     0,   274,   274,     0,   274,
       0,    96,    97,    98,    99,   100,   101,   102,   103,     0,
       0,   275,   275,     0,    59,     0,   252,     0,     0,     0,
       0,     0,     0,     0,     0,   275,     0,     0,     0,   275,
       0,   560,     0,     0,     0,     0,   274,     0,     0,   274,
     274,     0,     0,   112,     0,     0,     0,     0,     0,     0,
       0,   546,   252,   112,     0,   117,     0,   274,   274,   274,
       0,    49,    50,    51,     0,     0,    52,    53,    54,   274,
       0,     0,     0,   108,     0,     0,     0,     0,     1,     0,
       0,   274,     0,   274,    88,   274,    55,   324,   325,    56,
       0,     0,   274,     0,   274,   274,     0,   274,   274,   251,
     274,     0,   112,   112,   274,    88,     0,   274,   274,   275,
       0,     0,   275,   274,   275,   112,   112,   112,   112,   112,
       0,    88,     0,   489,   489,   489,   489,     0,     2,     3,
       4,     0,     0,     5,     6,     7,   112,     0,     0,     0,
     112,     0,   112,    64,   112,   112,   112,    75,     0,     0,
     275,   275,   275,     8,     0,     0,     9,     0,     0,     0,
       0,     0,    10,   275,   275,     0,   275,   275,    11,   275,
       0,     0,     0,     0,     0,     0,   117,   117,   117,   117,
     117,     0,   122,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,   112,     0,   112,     0,   112,   177,   183,
     187,   193,   197,   203,     0,     0,   275,     0,     0,   275,
     275,     0,     0,     0,     0,   112,     0,     0,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   275,   275,   275,
       0,     0,     0,     0,     0,   117,     0,     0,     0,   275,
       0,     0,   122,    96,    97,    98,    99,   100,   101,   102,
     103,   275,     0,   275,   122,   275,    59,   251,     0,     0,
       0,     0,   275,   252,   275,   275,     0,   275,   275,     0,
     275,     0,     0,     0,   275,     0,     0,   275,   275,     0,
       0,     0,     0,   275,   117,     0,     0,     0,     0,     0,
       0,     0,     0,   251,   252,   252,   112,     0,     0,   117,
       0,     0,     0,    49,    50,    51,     0,     0,    52,    53,
      54,   322,   323,     0,     0,   108,     0,     0,     0,   143,
     146,   148,   149,     0,     0,     0,     0,     0,    55,   324,
     325,    56,     0,     0,   181,     0,   191,     0,   201,     0,
       0,     0,     0,    57,     0,   489,   489,   489,   489,   489,
     489,   489,   489,   489,     0,   489,   489,   489,   489,   489,
     489,   489,   489,    88,     0,     0,     0,   167,   171,   174,
     176,     0,   182,     0,   192,     0,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    91,     0,     0,
       0,     0,     0,     0,     0,   347,   349,   350,     0,   352,
     353,     0,   354,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   112,   112,
     112,   112,     0,     0,     0,   117,     0,     0,     0,     0,
       0,     0,   374,   377,   379,   380,     0,   513,     0,   -23,
       0,   -20,   394,   397,   399,   400,  -224,  -224,  -224,  -224,
    -224,  -224,   414,   417,   419,   420,     0,     0,     0,     0,
     361,   364,   366,   515,   367,   369,     0,   370,     0,     0,
       0,     0,     0,     0,     0,   381,   385,   388,   390,     0,
       0,     0,     0,   117,     0,   401,   405,   408,   410,     0,
       0,     0,     0,     0,     0,   421,   425,   428,   430,     0,
     546,     0,     0,     0,   251,     0,     0,     0,   252,   489,
       0,   489,     0,     0,     0,   117,   117,   222,    97,    98,
      99,   100,   101,   102,   103,   112,     0,   743,     0,     0,
       0,     0,     0,     0,   224,   251,   251,     0,     0,     0,
     112,     0,   -20,     0,   516,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,     0,     0,     0,
       0,   225,   226,     0,   117,     0,     0,     0,   227,   228,
     229,   230,   231,   232,   233,     0,   234,     0,     0,     0,
       0,     0,     0,     0,   744,     0,     0,     0,   236,   237,
     238,     0,     0,   241,     0,     0,   117,   117,   489,   117,
     576,   577,     0,   578,     0,     0,   579,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   590,   592,   593,     0,
     595,   596,     0,   597,   117,     0,     0,   459,     0,     0,
       0,     0,     0,     0,     0,     0,   610,   612,   613,     0,
     615,   616,     0,   617,   583,   585,     0,   586,     0,     0,
     587,     0,     0,     0,     0,     0,   630,   632,   633,     0,
     635,   636,     0,   637,   598,   601,   603,     0,   604,   606,
       0,   607,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    77,     0,   618,   621,   623,     0,   624,   626,
       0,   627,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   638,   641,   643,     0,   644,   646,
       0,   647,     0,     0,   112,     0,     0,     0,   141,   144,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   169,
     172,     0,     0,   179,   185,   189,   195,   199,   205,   251,
       0,   252,     0,     0,     0,     0,   112,   112,     0,     0,
       0,     0,   454,    97,    98,    99,   100,   101,   102,   103,
     827,     0,     0,    58,   105,     0,     0,     0,     0,   224,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,   456,     0,     0,     0,     0,     0,     0,
     457,   458,     0,     0,   345,   112,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,     0,     0,     0,     0,     0,     0,     0,     0,
     783,     0,   362,   236,   237,   238,     0,     0,     0,     0,
       0,   372,   375,   787,   788,     0,   789,   383,   386,   790,
       0,   392,   395,     0,     0,     0,     0,   403,   406,     0,
       0,   412,   415,   797,   798,     0,   799,   423,   426,   800,
       0,     0,     0,     0,     0,   112,   785,     0,     0,     0,
       0,     0,   459,   807,   808,     0,   809,     0,     0,   810,
       0,   791,   793,     0,   794,     0,     0,   795,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,     0,
       0,   801,   803,     0,   804,     0,     0,   805,   222,    97,
      98,    99,   100,   101,   102,   103,     0,     0,  1056,     0,
       0,   811,   813,     0,   814,   224,     0,   815,     0,   142,
     145,   147,     0,     0,     0,     0,     0,     0,   869,     0,
     170,   173,   175,     0,   180,   186,   190,   196,   200,   206,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,     0,     0,
       0,     0,     0,     0,     0,   744,     0,     0,     0,   236,
     237,   238,   251,     0,   241,     0,     0,     0,     0,   899,
     901,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   346,   348,     0,     0,   351,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   588,     0,     0,   459,     0,
       0,   917,     0,   363,   365,     0,   599,   368,     0,     0,
       0,   919,   373,   376,   378,   608,     0,     0,   384,   387,
     389,   921,   393,   396,   398,     0,   619,     0,   404,   407,
     409,     0,   413,   416,   418,   628,     0,     0,   424,   427,
     429,     0,     0,     0,   918,     0,   639,     0,     0,     0,
       0,     0,   934,     0,   920,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   922,     0,     0,   943,     0,     0,
       0,     0,     0,     0,   964,     0,     0,     0,     0,     0,
       0,   968,     0,   940,     0,     0,     0,     0,     0,   979,
       0,     0,     0,     0,     0,     0,   454,    97,    98,    99,
     100,   101,   102,   103,     0,     0,   994,   996,     0,     0,
       0,     0,   668,   224,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,  1005,     0,   457,   458,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,  1006,  1007,     0,     0,
       0,     0,  1019,     0,     0,     0,  1022,   236,   237,   238,
       0,     0,     0,     0,     0,     0,     0,  1033,     0,     0,
     575,     0,     0,     0,  1038,     0,  1041,     0,  1044,     0,
       0,     0,     0,     0,     0,     0,     0,   584,     0,     0,
       0,     0,     0,     0,     0,     0,   589,   591,     0,     0,
     594,     0,  1061,     0,     0,     0,   459,   600,   602,     0,
       0,   605,     0,  1052,     0,     0,   609,   611,     0,     0,
     614,     0,     0,     0,     0,     0,  1077,   620,   622,  1081,
       0,   625,  1085,     0,     0,     0,   629,   631,     0,     0,
     634,     0,     0,     0,     0,     0,     0,   640,   642,  1096,
       0,   645,   222,    97,    98,    99,   100,   101,   102,   103,
       0,     0,   223,    58,   105,   496,     0,     0,     0,   224,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,   225,   226,   155,     0,
     105,    59,     0,   227,   228,   229,   230,   231,   232,   233,
     106,   549,     2,     3,     4,     0,     0,     5,     6,   235,
       0,     0,     0,   550,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,     0,   247,   248,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       4,     0,     0,     5,     6,     7,     0,     0,     0,     0,
     108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   551,     8,     0,     0,     9,     0,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   222,    97,    98,    99,   100,
     101,   102,   103,     0,     0,   223,    58,   105,    88,     0,
       0,     0,   224,   786,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   792,     0,     0,     0,     0,     0,
       0,     0,     0,   796,     0,     0,     0,     0,     0,   225,
     226,     0,     0,     0,   802,     0,   227,   228,   229,   230,
     231,   232,   233,   806,   234,     2,     3,     4,     0,     0,
       5,     6,   235,     0,   812,     0,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,     0,   247,   248,
       8,     0,     0,     9,   454,    97,    98,    99,   100,   101,
     102,   103,     0,     0,   223,    58,     0,     0,     0,     0,
       0,   224,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   249,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   236,   237,   238,   239,   240,
       0,   242,   243,   244,   245,   246,     0,   247,   248,   454,
      97,    98,    99,   100,   101,   102,   103,     0,     0,   223,
      58,     0,     0,     0,     0,     0,   224,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   249,     0,     0,     0,     0,     0,
       0,     0,     0,   225,   226,     0,     0,     0,     0,     0,
     227,   228,   229,   230,   231,   232,   233,     0,   234,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,   237,   238,   239,   240,     0,   242,   243,   244,   245,
     945,     0,   946,   248,   454,    97,    98,    99,   100,   101,
     102,   103,     0,     0,   508,     0,     0,     0,     0,     0,
       0,   224,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,   947,
       0,     0,   457,   458,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   236,   237,   238,   454,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,    58,
       0,     0,     0,     0,     0,   224,     0,     0,     0,    96,
      97,    98,    99,   100,   101,   102,   103,     0,   455,   456,
       0,     0,    59,     0,     0,     0,   457,   458,     0,     0,
       0,     0,   225,   226,   459,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   454,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   236,
     237,   238,     0,     0,     0,   224,   736,     0,     0,    40,
      41,    42,     0,     0,    43,    44,    45,     0,   455,   456,
       0,   108,     0,     0,     0,     0,   457,   458,     0,     0,
       0,     0,   225,   226,    46,     0,     0,    47,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   459,    48,
     454,    97,    98,    99,   100,   101,   102,   103,     0,   236,
     237,   238,     0,     0,     0,     0,     0,   224,     0,    88,
       0,     0,     0,     0,   841,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   459,   234,
     454,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,   236,   237,   238,     0,     0,     0,   224,     0,     0,
       0,     0,     0,     0,   843,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     486,     0,   454,    97,    98,    99,   100,   101,   102,   103,
       0,   236,   237,   238,     0,     0,     0,     0,   661,   224,
       0,     0,     0,     0,    96,    97,    98,    99,   100,   101,
     102,   103,   455,   456,     0,     0,     0,    59,     0,     0,
     457,   458,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
     486,   234,   454,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   236,   237,   238,     0,     0,     0,   224,
     868,     0,     0,     0,     0,   335,   336,     0,     0,   337,
     338,   339,   455,   456,     0,     0,   108,     0,     0,     0,
     457,   458,     0,     0,     0,     0,   225,   226,     0,   340,
     341,   342,   343,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   459,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   236,   237,   238,   454,    97,    98,    99,
     100,   101,   102,   103,    88,     0,   886,     0,     0,     0,
       0,     0,     0,   224,     0,     0,     0,    96,    97,    98,
      99,   100,   101,   102,   103,     0,   455,   456,     0,     0,
      59,     0,     0,     0,   457,   458,     0,     0,     0,     0,
     225,   226,   459,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   454,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   236,   237,   238,
       0,     0,     0,   224,   898,     0,     0,     0,    50,    51,
       0,     0,    52,    53,    54,     0,   455,   456,     0,   108,
       0,     0,     0,     0,   457,   458,     0,     0,     0,     0,
     225,   226,    55,   324,   325,    56,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   459,     0,   454,    97,
      98,    99,   100,   101,   102,   103,     0,   236,   237,   238,
       0,     0,     0,     0,     0,   224,   900,    88,     0,    96,
      97,    98,    99,   100,   101,   102,   103,     0,   455,   456,
       0,     0,    59,     0,     0,     0,   457,   458,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,   459,   234,   454,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   236,
     237,   238,     0,     0,     0,   224,   933,     0,     0,    40,
      41,    42,     0,     0,    43,    44,    45,     0,   455,   456,
       0,   108,     0,     0,     0,     0,   457,   458,     0,     0,
       0,     0,   225,   226,    46,     0,     0,    47,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   459,     0,
     454,    97,    98,    99,   100,   101,   102,   103,     0,   236,
     237,   238,     0,     0,     0,     0,     0,   224,   942,    88,
       0,    96,    97,    98,    99,   100,   101,   102,   103,     0,
     455,   456,     0,     0,    59,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   459,   234,
     454,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,   236,   237,   238,     0,     0,     0,   224,   963,     0,
       0,     0,     3,     4,     0,     0,     5,     6,     7,     0,
     455,   456,     0,   108,     0,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,     8,     0,     0,     9,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     459,     0,   454,    97,    98,    99,   100,   101,   102,   103,
       0,   236,   237,   238,     0,     0,     0,     0,     0,   224,
     967,    88,     0,    96,    97,    98,    99,   100,   101,   102,
     103,     0,   455,   456,     0,     0,    59,     0,     0,     0,
     457,   458,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
     459,   234,   454,    97,    98,    99,   100,   101,   102,   103,
       0,     0,   975,   236,   237,   238,     0,     0,     0,   224,
       0,     0,     0,     0,    41,    42,     0,     0,    43,    44,
      45,     0,   455,   456,     0,   108,     0,     0,     0,     0,
     457,   458,     0,     0,     0,     0,   225,   226,    46,     0,
       0,    47,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   459,     0,   454,    97,    98,    99,   100,   101,
     102,   103,     0,   236,   237,   238,     0,     0,     0,     0,
       0,   224,   978,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,   459,   234,   454,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,   236,   237,   238,     0,     0,
       0,   224,   993,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   459,     0,   454,    97,    98,    99,
     100,   101,   102,   103,     0,   236,   237,   238,     0,     0,
       0,     0,     0,   224,   995,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,     0,     0,   457,   458,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,   459,   234,   454,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   236,   237,   238,
       0,     0,     0,   224,  1004,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,     0,     0,   457,   458,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   459,     0,   454,    97,
      98,    99,   100,   101,   102,   103,     0,   236,   237,   238,
       0,     0,     0,     0,     0,   224,  1018,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   455,   456,
       0,     0,     0,     0,     0,     0,   457,   458,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,   459,   234,   454,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   236,
     237,   238,     0,     0,     0,   224,  1021,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   455,   456,
       0,     0,     0,     0,     0,     0,   457,   458,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   459,     0,
     454,    97,    98,    99,   100,   101,   102,   103,     0,   236,
     237,   238,     0,     0,     0,     0,     0,   224,  1032,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   459,   234,
     454,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,   236,   237,   238,     0,     0,     0,   224,  1037,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     459,     0,   454,    97,    98,    99,   100,   101,   102,   103,
       0,   236,   237,   238,     0,     0,     0,     0,     0,   224,
    1040,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,   456,     0,     0,     0,     0,     0,     0,
     457,   458,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
     459,   234,   454,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   236,   237,   238,     0,     0,     0,   224,
    1043,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,   456,     0,     0,     0,     0,     0,     0,
     457,   458,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   459,     0,   454,    97,    98,    99,   100,   101,
     102,   103,     0,   236,   237,   238,     0,     0,     0,     0,
       0,   224,  1060,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,   459,   234,   454,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,   236,   237,   238,     0,     0,
       0,   224,  1076,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   459,     0,   454,    97,    98,    99,
     100,   101,   102,   103,     0,   236,   237,   238,     0,     0,
       0,     0,     0,   224,  1080,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,     0,     0,   457,   458,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,   459,   234,   454,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   236,   237,   238,
       0,     0,     0,   224,  1084,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,     0,     0,   457,   458,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   459,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   236,   237,   238,
     454,    97,    98,    99,   100,   101,   102,   103,     0,     0,
    1090,     0,     0,     0,     0,     0,     0,   224,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,   459,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     454,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,   236,   237,   238,     0,     0,     0,   224,  1095,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,   457,   458,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     459,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   236,   237,   238,   454,    97,    98,    99,   100,   101,
     102,   103,     0,     0,  1116,     0,     0,     0,     0,     0,
       0,   224,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,     0,     0,     0,   225,   226,
     459,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   454,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,   236,   237,   238,     0,     0,
       0,   224,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   459,     0,   454,    97,    98,    99,
     100,   101,   102,   103,     0,   236,   237,   238,     0,     0,
       0,     0,     0,   224,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,     0,     0,   457,   458,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,   459,   234,   454,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   236,   237,   238,
       0,     0,     0,   224,   970,     0,     0,     0,     0,   454,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   224,  1025,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   486,     0,     0,     0,
       0,     0,     0,   225,   226,     0,     0,   236,   237,   238,
     227,   228,   229,   230,   231,   232,   233,     0,   234,   454,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
     236,   237,   238,     0,     0,     0,   224,  1028,     0,     0,
       0,     0,   454,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,     0,     0,     0,   459,     0,     0,   224,
    1071,     0,     0,   225,   226,     0,     0,     0,     0,     0,
     227,   228,   229,   230,   231,   232,   233,     0,   234,   459,
       0,     0,     0,     0,     0,     0,   225,   226,     0,     0,
     236,   237,   238,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   454,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   236,   237,   238,     0,     0,     0,   224,
    1112,     0,     0,     0,     0,   454,    97,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,     0,     0,   459,
       0,     0,   224,  1126,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   459,     0,     0,     0,     0,     0,     0,   225,
     226,     0,     0,   236,   237,   238,   227,   228,   229,   230,
     231,   232,   233,     0,   234,   454,    97,    98,    99,   100,
     101,   102,   103,     0,     0,     0,   236,   237,   238,     0,
       0,     0,   224,  1129,     0,     0,     0,     0,   454,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,   459,     0,     0,   224,  1139,     0,     0,   225,
     226,     0,     0,     0,     0,     0,   227,   228,   229,   230,
     231,   232,   233,     0,   234,   459,     0,     0,     0,     0,
       0,     0,   225,   226,     0,     0,   236,   237,   238,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   454,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   236,
     237,   238,     0,     0,     0,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   459,     0,     0,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   459,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   236,
     237,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   459
};

static const yytype_int16 yycheck[] =
{
      28,   277,   211,   524,   235,   664,   524,   514,   496,   222,
     316,    63,   313,   441,   498,   499,    73,   314,   216,   108,
     225,   226,   319,   221,   561,     0,   515,    10,    13,    18,
     123,   684,   685,    23,   523,    63,    16,    17,   251,    14,
      13,    16,    25,   119,   533,    14,   123,    75,    76,    77,
      78,     0,    80,    63,    82,   107,    84,    18,    12,    12,
      22,   524,   119,    14,    14,    14,   123,    16,    18,   123,
      13,   123,    18,    18,    16,    20,   128,    22,     0,   107,
       0,   318,    44,    23,   321,    16,    18,    13,    63,   326,
      18,   119,    45,    73,    14,   123,    16,    16,    73,    44,
     128,    44,   313,   160,   207,   133,    16,   344,    73,   119,
      16,   282,   122,   123,    63,    16,    67,   545,    44,   656,
     357,   319,    16,     0,    73,   135,   136,    36,   138,    98,
     135,   136,   137,   123,   139,   238,   125,    14,   123,    16,
     168,   169,   170,    63,   172,   173,   317,   175,   123,   320,
     123,   156,   162,    73,   164,   183,   184,   185,   186,   164,
     165,   166,    76,   334,   125,   193,   194,   195,   196,   123,
     973,   655,   975,    16,   123,   203,   204,   205,   206,   125,
     125,   123,    76,   123,    62,   160,    63,    62,   841,   360,
     843,    36,   123,   125,    16,   160,    73,   125,   686,   436,
      16,   277,    62,   123,   123,   215,    14,   217,   213,   123,
      23,   160,    63,   123,   123,   304,   305,   123,    18,    62,
     277,    44,   123,   707,    62,   235,   710,  1030,   123,   123,
      69,    74,   123,    76,   119,   772,    74,   313,   213,   545,
     160,   454,   225,   226,    44,   123,   123,   460,   123,   277,
     455,   456,   457,   458,    76,   556,   313,   123,    66,    67,
      76,    74,    13,   123,   213,    74,   318,   277,    18,   321,
     929,   568,   123,    16,   326,   764,   765,   766,   123,   555,
     123,   492,   493,   160,   123,   313,   314,  1090,   123,    40,
     318,   319,   344,   321,    44,    22,   123,    14,   326,    16,
      14,   123,    22,   313,   515,   357,   316,   123,   123,   520,
     123,  1114,   523,  1116,   123,    11,   344,    44,    20,    62,
      22,   532,   533,   494,    44,    21,    11,   123,  1131,   357,
     313,    74,    17,    76,   362,   363,   213,   365,    18,   823,
     368,    22,    44,   123,    61,   543,   544,    61,   776,    66,
      67,    11,    66,    67,   382,   383,   384,    17,   386,   387,
      11,   389,    13,    44,    44,   872,   873,    47,    48,   857,
     858,    11,   860,    13,   402,   403,   404,   123,   406,   407,
     123,   409,    14,    18,   436,    20,    20,    22,    22,    35,
      36,    37,   277,    11,   422,   423,   424,   825,   426,   427,
      16,   429,   123,    21,   119,    40,    13,    14,   436,    44,
      44,    61,    47,    48,   651,   652,   653,   654,    11,    11,
      11,   449,    16,   886,  1011,    26,    11,   890,   313,    21,
      21,   441,   437,   438,   439,   440,    21,    11,   514,   648,
     706,    11,   926,   709,    47,    48,    62,    21,   524,     3,
       4,     5,     6,     7,     8,     9,    10,    47,    48,    11,
      76,    13,   707,   970,    18,   710,    20,   895,    62,    21,
     123,    11,   455,   456,   457,   458,    49,    50,    51,   555,
     556,    21,    76,   687,   688,   689,   514,   692,   693,   694,
     125,  1012,    20,   769,  1012,    11,   123,    13,   555,   556,
      20,  1088,  1089,    13,  1011,    21,  1013,   123,   123,    11,
     973,   123,   975,   744,   524,    98,  1000,  1024,  1025,    21,
    1027,  1028,    11,    27,    11,  1112,   125,   555,   556,   123,
      47,    48,    21,   119,    21,   545,  1123,    11,  1125,  1126,
     568,  1128,  1129,    52,    53,   555,   556,    21,  1135,  1012,
     560,  1138,  1139,   764,   765,   766,   584,  1144,    11,    11,
    1067,    13,   277,  1070,  1071,    11,    20,  1030,    21,   123,
      11,   599,   600,    20,   602,    21,   872,   605,    33,    34,
      21,  1088,  1089,     3,     4,     5,     6,     7,     8,     9,
      10,   619,   620,  1100,   622,    22,    16,   625,   313,   651,
     652,   653,   654,    11,    11,  1112,    13,   664,   817,    20,
      11,   639,   640,    21,   642,    20,  1123,   645,  1125,  1126,
      21,  1128,  1129,   651,   652,   653,   654,  1090,  1135,   514,
      11,  1138,  1139,    11,    18,    13,   664,  1144,    13,   524,
      21,   123,    11,    63,    64,    65,    61,    62,    68,    69,
      70,  1114,    21,  1116,    13,    75,     3,     4,     5,     6,
       7,     8,     9,    10,   875,   876,    11,    11,  1131,    16,
     555,   556,    11,    13,    11,    11,    21,    21,   706,    11,
      11,   709,    21,   103,    21,    21,    14,    13,    16,    21,
      21,   277,    43,   769,   677,   678,   679,   680,   681,   682,
     683,   684,   685,   123,   687,   688,   689,   690,   691,   692,
     693,   694,   769,    20,    11,  1011,    63,    64,    65,   119,
      11,    68,    69,    70,    21,    11,    11,   313,    75,    43,
      21,   690,   691,    11,   744,    21,    21,    63,    64,    65,
      19,   769,    68,    69,    70,   682,   683,     3,     4,     5,
       6,     7,     8,     9,    10,    18,    21,    19,    46,   769,
      16,    38,    88,    39,   792,    91,   776,   777,    43,    20,
      18,    97,    13,   830,   802,    20,   123,   103,    13,    13,
      63,    64,    65,    13,   812,    68,    69,    70,   123,    13,
      18,    11,  1088,  1089,    11,    20,   872,   873,    44,   514,
     126,    11,    20,    43,    19,    88,   123,    19,    91,   524,
     886,    20,    18,   123,   890,   825,  1112,    28,    20,    75,
     103,    27,    28,    29,    30,    31,    32,  1123,    21,  1125,
    1126,    21,  1128,  1129,    19,    40,    20,    19,    44,  1135,
     555,   556,  1138,  1139,   872,   873,    20,    13,  1144,   123,
      63,    64,    65,    64,   123,    68,    69,    70,   841,    11,
     843,    20,   123,   123,    75,    19,    11,   123,    79,    80,
      81,    82,    83,    84,    20,    88,    20,   277,    91,   123,
      74,    15,    11,    40,   769,   895,   119,    20,    19,    13,
     224,    13,    20,    20,   970,    13,   872,   973,    13,   975,
      20,   929,    63,    64,    65,   239,   240,    68,    69,    70,
     244,   245,    13,   313,     3,     4,     5,     6,     7,     8,
       9,    10,    20,    20,   123,    20,    20,    88,   514,    85,
      91,   123,    21,    20,    85,  1011,  1012,  1013,   524,    63,
      64,    65,   970,    20,    68,    69,    70,   930,  1024,  1025,
     123,  1027,  1028,    21,  1030,     3,     4,     5,     6,     7,
       8,     9,    10,    21,    88,    20,   177,    91,    16,   555,
     556,    13,   183,    97,    13,    13,   187,    20,    13,   103,
      20,    70,   193,  1011,    13,  1013,   197,   872,   873,    20,
      40,  1067,   203,    21,  1070,  1071,  1024,  1025,    21,  1027,
    1028,   886,  1012,    13,    13,   890,    27,    28,    29,    30,
      31,    32,  1088,  1089,  1090,    13,    64,    65,    13,    13,
      68,    69,    70,    13,  1100,    21,    85,    75,    21,    21,
      13,    13,    13,    13,   123,  1011,  1112,    13,  1114,  1067,
    1116,    13,  1070,  1071,   277,    13,    13,  1123,    13,  1125,
    1126,    13,  1128,  1129,   769,  1131,    13,    21,   119,  1135,
    1088,  1089,  1138,  1139,    63,    64,    65,    21,  1144,    68,
      69,    70,  1100,    21,    21,   123,    63,    64,    65,    21,
     313,    68,    69,    70,  1112,   970,   160,   123,   973,    88,
     975,   238,    91,   209,   447,  1123,   499,  1125,  1126,   313,
    1128,  1129,   501,   678,   103,   930,   677,  1135,   680,   761,
    1138,  1139,  1088,  1089,   514,   449,  1144,    27,    28,    29,
      30,    31,    32,   679,   524,  1012,  1011,  1012,  1013,   777,
     681,   135,   213,   122,   225,   226,  1112,   860,    -1,  1024,
    1025,    -1,  1027,  1028,    18,  1030,    20,  1123,    22,  1125,
    1126,    -1,  1128,  1129,    -1,   555,   556,   872,   873,  1135,
      -1,    -1,  1138,  1139,    -1,    -1,    40,    -1,  1144,    -1,
      44,   886,    -1,    47,    48,   890,    -1,   511,   512,   513,
      -1,    -1,  1067,   769,    -1,  1070,  1071,    -1,   522,    27,
      28,    29,    30,    31,    32,    -1,    -1,   531,    -1,    -1,
     534,    -1,    -1,  1088,  1089,  1090,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,  1100,   277,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,  1112,   119,  1114,
      -1,  1116,    -1,    -1,    -1,    -1,    -1,    -1,  1123,    -1,
    1125,  1126,    -1,  1128,  1129,    -1,  1131,    -1,    -1,   123,
    1135,   125,   313,  1138,  1139,   970,    -1,    -1,   973,  1144,
     975,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,   514,    13,    14,    15,    16,   872,   873,    -1,    -1,
      -1,   524,    -1,    -1,    25,    -1,  1011,  1012,  1013,    18,
     886,    20,    -1,    22,   890,    -1,    -1,    -1,    -1,  1024,
    1025,    -1,  1027,  1028,    -1,  1030,    -1,    -1,    -1,    -1,
      -1,    40,   555,   556,    -1,    44,   123,    -1,    47,    48,
     664,    -1,    63,    64,    65,    75,    -1,    68,    69,    70,
      -1,    -1,   676,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1067,    -1,    -1,  1070,  1071,    88,    -1,    -1,
      91,    -1,    -1,    -1,   455,   456,   457,   458,    -1,   769,
      -1,   705,   103,  1088,  1089,  1090,    -1,    -1,    -1,    -1,
      -1,    -1,   716,   123,   970,  1100,   277,   973,    -1,   975,
      -1,    -1,   123,    -1,    -1,    -1,    -1,  1112,    -1,  1114,
      -1,  1116,    -1,    -1,   123,    -1,   125,    -1,  1123,   743,
    1125,  1126,    -1,  1128,  1129,    -1,  1131,    -1,    -1,    -1,
    1135,    -1,   313,  1138,  1139,  1011,  1012,  1013,    -1,  1144,
       3,     4,     5,     6,     7,     8,     9,    10,  1024,  1025,
      -1,  1027,  1028,    -1,  1030,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,   514,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,   524,     3,     4,     5,     6,     7,     8,
       9,    10,   872,   873,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1067,    21,    -1,  1070,  1071,   886,    -1,    -1,    -1,
     890,    -1,    -1,    -1,   555,   556,    -1,    70,    -1,    -1,
      -1,    -1,  1088,  1089,  1090,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    70,  1100,    64,    65,    -1,    -1,    68,
      69,    70,    71,    72,    -1,    -1,  1112,    -1,  1114,    -1,
    1116,    70,    -1,    -1,    -1,    -1,   769,  1123,    -1,  1125,
    1126,    -1,  1128,  1129,    -1,  1131,   103,   881,    -1,  1135,
     123,    -1,  1138,  1139,   888,   889,    -1,    -1,  1144,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
     970,    -1,    -1,   973,   123,   975,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,   123,    -1,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   929,   687,   688,   689,   690,
     691,   692,   693,   694,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1011,  1012,  1013,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,   514,  1024,  1025,    70,  1027,  1028,    -1,
    1030,    -1,    21,   524,    -1,    -1,    -1,    -1,    -1,   872,
     873,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,   886,    -1,    -1,    -1,   890,    -1,    -1,
      21,    -1,    -1,    -1,   555,   556,    -1,  1067,    -1,    -1,
    1070,  1071,    -1,    -1,    -1,  1009,  1010,    -1,    -1,   123,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,  1088,  1089,
    1090,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   769,    70,
      -1,    -1,  1112,    -1,  1114,    -1,  1116,    -1,    -1,    -1,
      -1,    -1,  1056,  1123,    -1,  1125,  1126,    -1,  1128,  1129,
      -1,  1131,    -1,    -1,   123,  1135,    -1,   970,  1138,  1139,
     973,    -1,   975,    -1,  1144,    -1,    -1,    -1,    -1,    -1,
     841,    -1,   843,    -1,    -1,    -1,    -1,    -1,  1092,  1093,
      -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    63,    -1,    -1,    -1,    -1,    -1,  1011,  1012,
    1013,    -1,    73,     3,     4,     5,     6,     7,     8,     9,
      10,  1024,  1025,    -1,  1027,  1028,    -1,  1030,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,   872,   873,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,   886,    16,    -1,   119,   890,
      -1,   122,   123,    -1,  1067,    -1,    -1,  1070,  1071,   930,
      -1,    -1,    -1,    -1,   135,   136,   137,   138,   139,    -1,
      -1,    -1,    -1,    -1,    -1,  1088,  1089,  1090,    -1,    79,
      -1,    -1,    -1,   225,   226,   156,    -1,  1100,    -1,   160,
      75,   162,    -1,   164,   165,   166,    -1,    -1,   769,  1112,
      -1,  1114,    -1,  1116,    -1,    -1,    -1,    -1,    -1,    -1,
    1123,    -1,  1125,  1126,    -1,  1128,  1129,    -1,  1131,    -1,
      -1,    -1,  1135,   123,    -1,  1138,  1139,    -1,    -1,   970,
      -1,  1144,   973,    -1,   975,    -1,   207,    -1,   123,    -1,
     211,    -1,   213,    -1,   215,    -1,   217,    -1,    -1,    -1,
      -1,    -1,    -1,   123,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,   235,    -1,    -1,   238,    -1,    -1,
    1011,  1012,  1013,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,  1024,  1025,    -1,  1027,  1028,    -1,  1030,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,   872,   873,    -1,    16,    -1,   277,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   886,    -1,    -1,    -1,   890,
      -1,    70,    -1,    -1,    -1,    -1,  1067,    -1,    -1,  1070,
    1071,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   312,   313,    73,    -1,   316,    -1,  1088,  1089,  1090,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    70,  1100,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    13,    -1,
      -1,  1112,    -1,  1114,   123,  1116,    88,    89,    90,    91,
      -1,    -1,  1123,    -1,  1125,  1126,    -1,  1128,  1129,   119,
    1131,    -1,   122,   123,  1135,   123,    -1,  1138,  1139,   970,
      -1,    -1,   973,  1144,   975,   135,   136,   137,   138,   139,
      -1,   123,    -1,   455,   456,   457,   458,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    70,   156,    -1,    -1,    -1,
     160,    -1,   162,    24,   164,   165,   166,    28,    -1,    -1,
    1011,  1012,  1013,    88,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    97,  1024,  1025,    -1,  1027,  1028,   103,  1030,
      -1,    -1,    -1,    -1,    -1,    -1,   437,   438,   439,   440,
     441,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   126,    -1,   213,    -1,   215,    -1,   217,    79,    80,
      81,    82,    83,    84,    -1,    -1,  1067,    -1,    -1,  1070,
    1071,    -1,    -1,    -1,    -1,   235,    -1,    -1,   238,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1088,  1089,  1090,
      -1,    -1,    -1,    -1,    -1,   496,    -1,    -1,    -1,  1100,
      -1,    -1,   123,     3,     4,     5,     6,     7,     8,     9,
      10,  1112,    -1,  1114,   135,  1116,    16,   277,    -1,    -1,
      -1,    -1,  1123,   524,  1125,  1126,    -1,  1128,  1129,    -1,
    1131,    -1,    -1,    -1,  1135,    -1,    -1,  1138,  1139,    -1,
      -1,    -1,    -1,  1144,   545,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   313,   555,   556,   316,    -1,    -1,   560,
      -1,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      70,    71,    72,    -1,    -1,    75,    -1,    -1,    -1,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    -1,    79,    -1,    81,    -1,    83,    -1,
      -1,    -1,    -1,   103,    -1,   677,   678,   679,   680,   681,
     682,   683,   684,   685,    -1,   687,   688,   689,   690,   691,
     692,   693,   694,   123,    -1,    -1,    -1,    75,    76,    77,
      78,    -1,    80,    -1,    82,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   648,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,   141,   142,    -1,   144,
     145,    -1,   147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   437,   438,   439,
     440,   441,    -1,    -1,    -1,   686,    -1,    -1,    -1,    -1,
      -1,    -1,   177,   178,   179,   180,    -1,    18,    -1,    20,
      -1,    22,   187,   188,   189,   190,    27,    28,    29,    30,
      31,    32,   197,   198,   199,   200,    -1,    -1,    -1,    -1,
     168,   169,   170,    44,   172,   173,    -1,   175,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   183,   184,   185,   186,    -1,
      -1,    -1,    -1,   744,    -1,   193,   194,   195,   196,    -1,
      -1,    -1,    -1,    -1,    -1,   203,   204,   205,   206,    -1,
     761,    -1,    -1,    -1,   524,    -1,    -1,    -1,   769,   841,
      -1,   843,    -1,    -1,    -1,   776,   777,     3,     4,     5,
       6,     7,     8,     9,    10,   545,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,   555,   556,    -1,    -1,    -1,
     560,    -1,   123,    -1,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   817,    -1,    -1,    -1,
      -1,    47,    48,    -1,   825,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    79,    -1,    -1,   857,   858,   930,   860,
     345,   346,    -1,   348,    -1,    -1,   351,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   371,   372,   373,    -1,
     375,   376,    -1,   378,   895,    -1,    -1,   123,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   391,   392,   393,    -1,
     395,   396,    -1,   398,   362,   363,    -1,   365,    -1,    -1,
     368,    -1,    -1,    -1,    -1,    -1,   411,   412,   413,    -1,
     415,   416,    -1,   418,   382,   383,   384,    -1,   386,   387,
      -1,   389,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,   402,   403,   404,    -1,   406,   407,
      -1,   409,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   422,   423,   424,    -1,   426,   427,
      -1,   429,    -1,    -1,   744,    -1,    -1,    -1,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,   769,
      -1,  1012,    -1,    -1,    -1,    -1,   776,   777,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    14,    15,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,   140,   825,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     575,    -1,   168,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,   177,   178,   588,   589,    -1,   591,   183,   184,   594,
      -1,   187,   188,    -1,    -1,    -1,    -1,   193,   194,    -1,
      -1,   197,   198,   608,   609,    -1,   611,   203,   204,   614,
      -1,    -1,    -1,    -1,    -1,   895,   584,    -1,    -1,    -1,
      -1,    -1,   123,   628,   629,    -1,   631,    -1,    -1,   634,
      -1,   599,   600,    -1,   602,    -1,    -1,   605,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   619,   620,    -1,   622,    -1,    -1,   625,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    -1,
      -1,   639,   640,    -1,   642,    20,    -1,   645,    -1,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,   711,    -1,
      75,    76,    77,    -1,    79,    80,    81,    82,    83,    84,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,
      75,    76,  1012,    -1,    79,    -1,    -1,    -1,    -1,   762,
     763,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,   141,    -1,    -1,   144,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   371,    -1,    -1,   123,    -1,
      -1,   786,    -1,   168,   169,    -1,   382,   172,    -1,    -1,
      -1,   796,   177,   178,   179,   391,    -1,    -1,   183,   184,
     185,   806,   187,   188,   189,    -1,   402,    -1,   193,   194,
     195,    -1,   197,   198,   199,   411,    -1,    -1,   203,   204,
     205,    -1,    -1,    -1,   792,    -1,   422,    -1,    -1,    -1,
      -1,    -1,   855,    -1,   802,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   812,    -1,    -1,   870,    -1,    -1,
      -1,    -1,    -1,    -1,   877,    -1,    -1,    -1,    -1,    -1,
      -1,   884,    -1,   868,    -1,    -1,    -1,    -1,    -1,   892,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,   909,   910,    -1,    -1,
      -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,   935,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,   941,   942,    -1,    -1,
      -1,    -1,   965,    -1,    -1,    -1,   969,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   980,    -1,    -1,
     345,    -1,    -1,    -1,   987,    -1,   989,    -1,   991,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   362,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   371,   372,    -1,    -1,
     375,    -1,  1015,    -1,    -1,    -1,   123,   382,   383,    -1,
      -1,   386,    -1,  1008,    -1,    -1,   391,   392,    -1,    -1,
     395,    -1,    -1,    -1,    -1,    -1,  1039,   402,   403,  1042,
      -1,   406,  1045,    -1,    -1,    -1,   411,   412,    -1,    -1,
     415,    -1,    -1,    -1,    -1,    -1,    -1,   422,   423,  1062,
      -1,   426,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    47,    48,    13,    -1,
      15,    16,    -1,    54,    55,    56,    57,    58,    59,    60,
      25,    62,    63,    64,    65,    -1,    -1,    68,    69,    70,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    86,    87,    88,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    70,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,    88,    -1,    -1,    91,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    15,   123,    -1,
      -1,    -1,    20,   588,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   599,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   608,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,   619,    -1,    54,    55,    56,    57,
      58,    59,    60,   628,    62,    63,    64,    65,    -1,    -1,
      68,    69,    70,    -1,   639,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    86,    87,
      88,    -1,    -1,    91,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      -1,    80,    81,    82,    83,    84,    -1,    86,    87,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    78,    -1,    80,    81,    82,    83,
      84,    -1,    86,    87,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,   123,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    33,    34,
      -1,    -1,    16,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,   123,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    33,    34,
      -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    88,    -1,    -1,    91,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,   123,   103,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    20,    -1,   123,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   123,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
     123,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    19,    20,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    33,    34,    -1,    -1,    -1,    16,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     123,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,    64,    65,    -1,    -1,    68,
      69,    70,    33,    34,    -1,    -1,    75,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    88,
      89,    90,    91,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,     3,     4,     5,     6,
       7,     8,     9,    10,   123,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    33,    34,    -1,    -1,
      16,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,   123,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,    75,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    88,    89,    90,    91,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,   123,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    20,    21,   123,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    33,    34,
      -1,    -1,    16,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   123,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    33,    34,
      -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    88,    -1,    -1,    91,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,   123,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    20,    21,   123,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      33,    34,    -1,    -1,    16,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   123,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      33,    34,    -1,    75,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    88,    -1,    -1,    91,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
     123,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    20,
      21,   123,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    33,    34,    -1,    -1,    16,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     123,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    74,    75,    76,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    33,    34,    -1,    75,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    88,    -1,
      -1,    91,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   123,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    20,    21,   123,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,   123,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,   123,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   123,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,   123,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   123,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,   123,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   123,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
     123,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     123,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   123,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,   123,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,   123,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   123,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,   123,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,   123,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
     123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
     123,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,   123,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   123,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,   123,    -1,    -1,    -1,
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
      97,   103,   126,   128,   141,   142,   143,   144,   145,   146,
     153,   269,   270,   271,   123,    69,   123,   140,   123,     0,
     126,   142,   142,    63,    64,    65,    68,    69,    70,   103,
      63,    64,    65,    68,    69,    70,    88,    91,   103,    63,
      64,    65,    68,    69,    70,    88,    91,   103,    14,    16,
      61,    66,    67,   148,   154,   159,   160,   162,   164,   140,
      44,    13,    44,   148,   150,   154,   159,   160,   162,   123,
     123,   123,   123,   123,   123,   123,   155,   156,   123,   136,
     137,   136,   161,   279,   123,   163,     3,     4,     5,     6,
       7,     8,     9,    10,    13,    15,    25,    69,    75,   123,
     129,   130,   131,   132,   133,   134,   135,   136,   144,   148,
     149,   153,   154,   165,   166,   167,   168,   216,   217,   227,
     228,   229,   264,   265,   266,   269,   270,   271,   272,   273,
     159,   160,   162,   164,   160,   162,   164,   162,   164,   164,
      13,    44,   123,    36,   123,    13,    93,   129,   144,   149,
     151,   152,   154,   216,   269,   270,   271,   150,   159,   160,
     162,   150,   160,   162,   150,   162,   150,   154,   159,   160,
     162,   164,   150,   154,   159,   160,   162,   154,   159,   160,
     162,   164,   150,   154,   159,   160,   162,   154,   159,   160,
     162,   164,   150,   154,   159,   160,   162,    61,   157,    11,
      17,    11,    11,    26,   229,   123,   221,   123,   169,   170,
     171,   221,     3,    13,    20,    47,    48,    54,    55,    56,
      57,    58,    59,    60,    62,    70,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    86,    87,   123,
     129,   131,   136,   139,   140,   144,   147,   149,   175,   176,
     178,   179,   180,   181,   182,   184,   185,   188,   189,   190,
     196,   209,   210,   212,   213,   214,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   255,   256,   257,
     259,   269,   270,   271,    75,   129,   266,   149,   166,    13,
     226,   229,    98,   148,   218,   267,    20,   129,   217,   265,
     129,   217,    71,    72,    89,    90,   217,    64,    65,    68,
      69,    70,    71,    72,   129,    64,    65,    68,    69,    70,
      88,    89,    90,    91,   217,   160,   162,   164,   162,   164,
     164,   162,   164,   164,   164,    36,    13,   217,   149,   152,
     129,   150,   160,   162,   150,   162,   150,   150,   162,   150,
     150,   159,   160,   162,   164,   160,   162,   164,   162,   164,
     164,   150,   159,   160,   162,   150,   160,   162,   150,   162,
     150,   159,   160,   162,   164,   160,   162,   164,   162,   164,
     164,   150,   159,   160,   162,   150,   160,   162,   150,   162,
     150,   159,   160,   162,   164,   160,   162,   164,   162,   164,
     164,   150,   159,   160,   162,   150,   160,   162,   150,   162,
     150,   123,   135,   156,   279,   123,   217,   269,   270,   271,
     273,    20,   129,   222,   218,    18,   138,    11,    13,    27,
     218,    18,   125,   183,     3,    33,    34,    41,    42,   123,
     131,   136,   173,   174,   175,   184,   188,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   123,   140,   178,   196,
     208,   208,    22,    44,   235,   125,    16,   123,   130,   135,
     186,   274,   173,   173,    13,   123,    13,   123,    13,   173,
     173,    20,    20,    18,    40,    44,   125,   183,   125,   183,
      22,    20,    18,    44,    20,    27,    28,    29,    30,    31,
      32,   177,    22,    44,    18,    47,    48,   149,   231,    13,
     123,   169,    13,   221,   221,    20,   136,   219,   220,    62,
      74,   123,   140,   149,   179,   230,   268,   274,   267,    21,
      70,   129,   222,   223,   224,   225,   169,   226,   218,   267,
     169,   226,   226,   169,   226,   162,   164,   164,   164,   164,
      13,   226,   169,   150,   162,   150,   150,   150,   160,   162,
     164,   162,   164,   164,   162,   164,   164,   164,   150,   160,
     162,   150,   162,   150,   150,   162,   150,   150,   160,   162,
     164,   162,   164,   164,   162,   164,   164,   164,   150,   160,
     162,   150,   162,   150,   150,   162,   150,   150,   160,   162,
     164,   162,   164,   164,   162,   164,   164,   164,   150,   160,
     162,   150,   162,   150,   150,   162,   150,   150,    43,   158,
     226,   217,   217,   217,   217,    21,   129,   223,    74,   123,
      11,    19,    18,   170,   148,   172,   173,   191,    19,    18,
     125,   208,   208,   208,   208,    21,    12,    45,    46,    38,
      39,    43,    52,    53,    16,    17,    73,    49,    50,    51,
      33,    34,    35,    36,    37,   123,   274,   123,   274,   169,
      12,   134,   275,   276,   277,    18,   138,   193,   194,   138,
     193,    20,   123,   186,    13,    13,    40,    13,    13,    13,
      13,   173,   173,   173,   236,    62,    74,    76,   123,   185,
     274,   125,   125,    76,   123,   274,    21,   173,   187,   173,
     123,   185,   274,    13,    70,   234,   240,   261,   263,   173,
     123,   274,   123,   185,   274,   173,   218,   218,    21,   222,
     223,    11,    20,    20,    44,    44,    44,   149,   149,   230,
      62,    74,   129,    23,   123,   171,    11,    11,    21,    13,
     267,    13,    13,   164,    13,   150,   162,   164,   164,   164,
     164,   150,   162,   150,   150,   150,   162,   164,   164,   164,
     164,   150,   162,   150,   150,   150,   162,   164,   164,   164,
     164,   150,   162,   150,   150,   150,   279,    43,   226,   226,
     226,   226,   138,    21,    44,    20,    19,    11,   149,   172,
     192,   195,    19,   173,   199,   200,   201,   202,   203,   204,
     204,    27,   205,    27,   205,   134,   206,   206,   206,   207,
     207,   208,   208,   208,   123,    20,   123,    61,    62,   278,
      11,    17,   173,   191,   138,   194,   191,   138,    21,   187,
      20,   173,    21,    21,    19,    22,    44,    20,   123,    76,
     123,    11,    21,    19,    20,   123,    13,   173,    40,    13,
      11,   123,    20,   123,    19,    11,    21,   220,    21,   187,
      21,   187,    62,   274,    62,   274,    62,   274,   149,    20,
      20,    23,   171,   123,    21,   223,   224,   164,   150,   164,
     150,   164,   150,   279,   138,    74,    21,   223,   149,    11,
      40,   205,   205,    21,   187,    20,   134,   134,   276,    19,
     164,    21,    21,   187,    13,    84,    86,   123,   147,   236,
     237,   250,   251,   252,   253,   254,   258,   260,   236,   123,
     274,   123,   274,    21,   187,    20,   173,    21,   187,    20,
      21,   262,   263,    13,   173,    13,   173,   240,    21,   187,
      20,    21,   223,    13,    21,    13,    21,    20,    62,    20,
      62,    20,    62,    21,   187,    21,   187,   123,    21,   138,
      21,   172,   197,    21,    21,   187,   164,   164,    21,    20,
      20,    40,    20,    85,   123,    20,   123,    21,    21,   187,
      21,    21,   187,   236,    21,    21,   262,    21,    21,   262,
      13,    21,    21,   187,    21,    13,    13,    21,   187,    20,
      21,   187,    20,    21,   187,    20,    13,    21,    13,    21,
     138,    21,   164,   173,   173,   251,    13,   234,   261,   236,
      21,   187,    20,    21,    21,   236,   236,    21,   236,   236,
      21,    21,   262,    21,    13,    21,    21,   187,    13,    21,
      21,   187,    13,    21,    21,   187,    13,    13,    21,    21,
      13,   173,    40,    13,    21,    21,   187,   236,   236,   236,
      21,    13,    13,    21,    13,    13,    21,    13,    13,    21,
     251,   251,    21,   262,    13,   173,    13,   173,    21,   236,
      13,    13,    13,    85,   251,    21,    21,   262,    21,    21,
     262,    13,   251,   251,   251,    21,   251,   251,    21,    21,
     262,   251,   251,   251,    21,   251
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
     145,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   147,   148,   149,   150,   150,
     151,   151,   152,   152,   152,   152,   152,   153,   154,   155,
     155,   156,   156,   157,   157,   158,   158,   159,   160,   161,
     161,   162,   163,   163,   164,   164,   165,   165,   166,   166,
     166,   166,   167,   167,   167,   167,   167,   168,   168,   168,
     168,   169,   169,   170,   170,   171,   171,   172,   172,   173,
     174,   174,   175,   176,   176,   176,   176,   177,   177,   177,
     177,   177,   177,   178,   178,   178,   179,   179,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   181,   181,
     181,   181,   181,   181,   181,   182,   182,   182,   182,   182,
     182,   182,   183,   183,   184,   184,   184,   184,   185,   185,
     185,   185,   185,   185,   185,   185,   186,   187,   187,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   191,   191,   192,   192,   192,   193,   193,   194,   195,
     195,   196,   196,   196,   197,   197,   198,   198,   199,   199,
     200,   200,   201,   201,   202,   202,   203,   203,   203,   204,
     204,   204,   204,   204,   204,   205,   205,   205,   205,   206,
     206,   206,   207,   207,   207,   207,   208,   208,   208,   208,
     208,   209,   210,   211,   211,   211,   212,   212,   212,   212,
     212,   213,   214,   215,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   217,   217,   217,   217,   217,   217,
     217,   217,   218,   219,   219,   220,   221,   221,   221,   221,
     221,   221,   221,   221,   222,   222,   223,   223,   224,   224,
     224,   225,   225,   226,   226,   227,   228,   229,   229,   230,
     230,   231,   231,   231,   232,   233,   234,   234,   235,   235,
     236,   236,   236,   236,   236,   236,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   238,   239,   240,   240,   240,
     240,   240,   240,   240,   241,   241,   242,   242,   243,   243,
     244,   244,   245,   246,   247,   248,   249,   250,   251,   251,
     251,   251,   251,   252,   253,   254,   254,   255,   256,   256,
     257,   257,   257,   257,   257,   257,   257,   257,   258,   258,
     258,   258,   258,   258,   258,   258,   259,   260,   261,   261,
     262,   263,   263,   264,   264,   264,   264,   265,   265,   265,
     265,   265,   265,   265,   265,   266,   267,   267,   267,   267,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     269,   269,   269,   269,   269,   269,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   274,   275,   275,   276,
     276,   277,   277,   278,   278,   279
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
       5,     7,     6,     6,     5,     6,     5,     5,     4,     6,
       5,     5,     4,     5,     4,     4,     3,     8,     7,     7,
       6,     7,     6,     6,     5,     7,     6,     6,     5,     6,
       5,     5,     4,     8,     7,     7,     6,     7,     6,     6,
       5,     7,     6,     6,     5,     6,     5,     5,     4,     8,
       7,     7,     6,     7,     6,     6,     5,     7,     6,     6,
       5,     6,     5,     5,     4,     1,     1,     1,     2,     3,
       1,     2,     1,     3,     4,     1,     1,     1,     3,     1,
       3,     2,     1,     2,     3,     2,     3,     2,     2,     1,
       3,     2,     1,     3,     2,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     4,
       3,     1,     3,     3,     1,     1,     2,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     5,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     3,
       3,     3,     2,     3,     1,     3,     3,     3,     4,     5,
       5,     6,     5,     6,     6,     7,     1,     1,     3,     3,
       4,     5,     6,     6,     7,     5,     6,     6,     7,     5,
       6,     6,     7,     5,     6,     6,     7,     7,     8,     8,
       9,     4,     4,     4,     6,     4,     3,     3,     3,     5,
       3,     4,     4,     4,     4,     3,     3,     3,     3,     2,
       2,     3,     2,     1,     1,     2,     1,     2,     3,     1,
       3,     4,     4,     4,     1,     5,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     4,     4,     1,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     1,     2,     2,
       1,     2,     2,     1,     2,     2,     1,     1,     1,     1,
       1,     2,     2,     3,     2,     3,     3,     3,     3,     4,
       5,     5,     5,     5,     2,     2,     3,     4,     3,     3,
       4,     3,     2,     1,     3,     1,     3,     4,     5,     4,
       6,     5,     7,     6,     2,     4,     1,     3,     2,     1,
       3,     3,     4,     1,     1,     1,     2,     3,     2,     1,
       2,     1,     1,     1,     1,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     2,     3,     2,     3,
       3,     2,     3,     3,     3,     5,     7,     7,     1,     1,
       1,     1,     1,     3,     5,     1,     1,     5,     1,     1,
       6,     7,     7,     8,     7,     8,     8,     9,     6,     7,
       7,     8,     7,     8,     8,     9,     7,     7,     1,     1,
       1,     1,     3,     3,     2,     4,     3,     3,     4,     5,
       6,     4,     5,     6,     7,     1,     4,     3,     3,     2,
       4,     5,     5,     6,     4,     5,     5,     6,     6,     7,
       7,     8,     6,     7,     7,     8,     6,     7,     7,     8,
       1,     1,     1,     2,     2,     2,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     1,     3,     1,
       1,     1,     2,     2,     2,     1
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
#line 235 "parser_1st.y"
                              {return 0;}
#line 3410 "parser_1st.tab.c"
    break;

  case 3: /* COMPILATIONUNIT: ORDINARYCOMPILATIONUNIT EOFF  */
#line 236 "parser_1st.y"
                                                     {
                    for(auto obj:object_list){
                        string pr = pref[obj];
                        // vector<string> methods = getallmethods(obj);
                        vector<string> methods = {"f"};
                        for(auto method : methods){
                            // code.push_back(method);
                            add_func(code, pr, method_det[method].start, method_det[method].end);
                        }
                    }
                    return 0;
                }
#line 3427 "parser_1st.tab.c"
    break;

  case 4: /* TYPE: PRIMITIVETYPE  */
#line 249 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3433 "parser_1st.tab.c"
    break;

  case 5: /* TYPE: REFERENCETYPE  */
#line 250 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3439 "parser_1st.tab.c"
    break;

  case 6: /* PRIMITIVETYPE: NUMERICTYPE  */
#line 252 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3445 "parser_1st.tab.c"
    break;

  case 7: /* PRIMITIVETYPE: BOOLEAN  */
#line 253 "parser_1st.y"
                             {(yyval.val) = stringtochar("bool");}
#line 3451 "parser_1st.tab.c"
    break;

  case 8: /* NUMERICTYPE: INTEGRALTYPE  */
#line 255 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3457 "parser_1st.tab.c"
    break;

  case 9: /* NUMERICTYPE: FLOATINGTYPE  */
#line 256 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3463 "parser_1st.tab.c"
    break;

  case 10: /* INTEGRALTYPE: BYTE  */
#line 258 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3469 "parser_1st.tab.c"
    break;

  case 11: /* INTEGRALTYPE: SHORT  */
#line 259 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3475 "parser_1st.tab.c"
    break;

  case 12: /* INTEGRALTYPE: INT  */
#line 260 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3481 "parser_1st.tab.c"
    break;

  case 13: /* INTEGRALTYPE: LONG  */
#line 261 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3487 "parser_1st.tab.c"
    break;

  case 14: /* INTEGRALTYPE: CHAR  */
#line 262 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3493 "parser_1st.tab.c"
    break;

  case 15: /* FLOATINGTYPE: FLOAT  */
#line 264 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3499 "parser_1st.tab.c"
    break;

  case 16: /* FLOATINGTYPE: DOUBLE  */
#line 265 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3505 "parser_1st.tab.c"
    break;

  case 17: /* REFERENCETYPE: CLASSORINTERFACETYPE  */
#line 267 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3511 "parser_1st.tab.c"
    break;

  case 18: /* CLASSORINTERFACETYPE: CLASSTYPE  */
#line 269 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3517 "parser_1st.tab.c"
    break;

  case 19: /* CLASSTYPE: CLASSTYPE1  */
#line 271 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3523 "parser_1st.tab.c"
    break;

  case 20: /* CLASSTYPE1: IDENTIFIER  */
#line 273 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val); }
#line 3529 "parser_1st.tab.c"
    break;

  case 21: /* DIMS: OPENSQUARE CLOSESQUARE  */
#line 276 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3535 "parser_1st.tab.c"
    break;

  case 22: /* DIMS: DIMS OPENSQUARE CLOSESQUARE  */
#line 277 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3541 "parser_1st.tab.c"
    break;

  case 23: /* METHODNAME: IDENTIFIER  */
#line 279 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3552 "parser_1st.tab.c"
    break;

  case 24: /* EXPRESSIONNAME: IDENTIFIER DOT IDENTIFIER  */
#line 286 "parser_1st.y"
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
#line 3574 "parser_1st.tab.c"
    break;

  case 25: /* EXPRESSIONNAME: EXPRESSIONNAME DOT IDENTIFIER  */
#line 303 "parser_1st.y"
                                                  {/*TODO*/}
#line 3580 "parser_1st.tab.c"
    break;

  case 28: /* TOPLEVELCLASSORINTERFACEDECLARATION: CLASSDECLARATION  */
#line 309 "parser_1st.y"
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
#line 3626 "parser_1st.tab.c"
    break;

  case 36: /* CLASSDECLARATION: NORMALCLASSDECLARATION  */
#line 359 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 3632 "parser_1st.tab.c"
    break;

  case 37: /* NORMALCLASSDECLARATION: CLASS IDENTIFIER CLASSBODY  */
#line 362 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));/*TODO begin class */}
#line 3638 "parser_1st.tab.c"
    break;

  case 38: /* NORMALCLASSDECLARATION: SUPER1 CLASS IDENTIFIER CLASSBODY  */
#line 363 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val); if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3644 "parser_1st.tab.c"
    break;

  case 39: /* NORMALCLASSDECLARATION: SUPER2 CLASS IDENTIFIER CLASSBODY  */
#line 364 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3650 "parser_1st.tab.c"
    break;

  case 40: /* NORMALCLASSDECLARATION: SUPER3 CLASS IDENTIFIER CLASSBODY  */
#line 365 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3656 "parser_1st.tab.c"
    break;

  case 165: /* FOR: FOR1  */
#line 497 "parser_1st.y"
           {newscope();}
#line 3662 "parser_1st.tab.c"
    break;

  case 166: /* OPENCURLY: OPENCURLY1  */
#line 498 "parser_1st.y"
                          {newscope(); }
#line 3668 "parser_1st.tab.c"
    break;

  case 167: /* CLOSECURLY: CLOSECURLY1  */
#line 499 "parser_1st.y"
                          {popscope();}
#line 3674 "parser_1st.tab.c"
    break;

  case 207: /* FIELDDECLARATION: FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 560 "parser_1st.y"
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
#line 3705 "parser_1st.tab.c"
    break;

  case 208: /* FIELDDECLARATION: SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 586 "parser_1st.y"
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
#line 3734 "parser_1st.tab.c"
    break;

  case 209: /* FIELDDECLARATION: SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 610 "parser_1st.y"
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
#line 3765 "parser_1st.tab.c"
    break;

  case 210: /* FIELDDECLARATION: TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 636 "parser_1st.y"
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
#line 3805 "parser_1st.tab.c"
    break;

  case 211: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATOR  */
#line 674 "parser_1st.y"
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
#line 3822 "parser_1st.tab.c"
    break;

  case 212: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR  */
#line 686 "parser_1st.y"
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
#line 3850 "parser_1st.tab.c"
    break;

  case 213: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER  */
#line 710 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit ;   generalmap[(yyval.val)].typ= generalmap[(yyvsp[0].val)].typ;                                   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));                 
                                                                            if(ds[curr3].find("class")!=ds[curr3].end()){
                                                                                ds[curr]["var"] = ds[curr1]["var"];
                                                                                object_list.push_back(ds[curr]["var"]); // Add object to object list
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
#line 3887 "parser_1st.tab.c"
    break;

  case 214: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID  */
#line 742 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];}
#line 3893 "parser_1st.tab.c"
    break;

  case 215: /* VARIABLEDECLARATORID: IDENTIFIER  */
#line 744 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));

}
#line 3906 "parser_1st.tab.c"
    break;

  case 216: /* VARIABLEDECLARATORID: IDENTIFIER DIMS  */
#line 752 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        int curr = chartonum((yyval.val));
                                    ds[curr]["var"] = chartostring((yyvsp[-1].val));
                        /*TODO*/
                        }
#line 3916 "parser_1st.tab.c"
    break;

  case 217: /* VARIABLEINITIALIZER: EXPRESSION  */
#line 759 "parser_1st.y"
                                    {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 3922 "parser_1st.tab.c"
    break;

  case 218: /* VARIABLEINITIALIZER: ARRAYINITIALIZER  */
#line 760 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 3928 "parser_1st.tab.c"
    break;

  case 219: /* EXPRESSION: ASSIGNMENTEXPRESSION  */
#line 762 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 3934 "parser_1st.tab.c"
    break;

  case 220: /* ASSIGNMENTEXPRESSION: CONDITIONALEXPRESSION  */
#line 764 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 3942 "parser_1st.tab.c"
    break;

  case 221: /* ASSIGNMENTEXPRESSION: ASSIGNMENT  */
#line 767 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);/*TODO CHECK multiple assign*/}
#line 3948 "parser_1st.tab.c"
    break;

  case 222: /* ASSIGNMENT: LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  */
#line 769 "parser_1st.y"
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
#line 3967 "parser_1st.tab.c"
    break;

  case 223: /* LEFTHANDSIDE: EXPRESSIONNAME  */
#line 784 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 3973 "parser_1st.tab.c"
    break;

  case 224: /* LEFTHANDSIDE: IDENTIFIER  */
#line 785 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
#line 3986 "parser_1st.tab.c"
    break;

  case 225: /* LEFTHANDSIDE: FIELDACCESS  */
#line 793 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 3992 "parser_1st.tab.c"
    break;

  case 226: /* LEFTHANDSIDE: ARRAYACCESS  */
#line 794 "parser_1st.y"
                                {   (yyval.val) = (yyvsp[0].val);
                                    ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"[ "+ds[chartonum((yyvsp[0].val))]["var"]+" ]";
                }
#line 4000 "parser_1st.tab.c"
    break;

  case 227: /* ASSIGNMENTOPERATOR: EQUALS  */
#line 798 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 4007 "parser_1st.tab.c"
    break;

  case 228: /* ASSIGNMENTOPERATOR: MULTIPLYEQUALS  */
#line 800 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 4014 "parser_1st.tab.c"
    break;

  case 229: /* ASSIGNMENTOPERATOR: DIVIDEEQUALS  */
#line 802 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 4021 "parser_1st.tab.c"
    break;

  case 230: /* ASSIGNMENTOPERATOR: MODEQUALS  */
#line 804 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 4028 "parser_1st.tab.c"
    break;

  case 231: /* ASSIGNMENTOPERATOR: PLUSEQUALS  */
#line 806 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 4035 "parser_1st.tab.c"
    break;

  case 232: /* ASSIGNMENTOPERATOR: MINUSEQUALS  */
#line 808 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 4042 "parser_1st.tab.c"
    break;

  case 233: /* FIELDACCESS: PRIMARY DOT IDENTIFIER  */
#line 811 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring((yyvsp[0].val));
                                        }else assert(0 && "unexpected type\n");
                                        }
#line 4054 "parser_1st.tab.c"
    break;

  case 236: /* PRIMARY: PRIMARYNONEWARRAY  */
#line 821 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            if(ds[chartonum((yyval.val))].find("array")!=ds[chartonum((yyval.val))].end())
                            ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"["+ds[chartonum((yyvsp[0].val))]["var"]+"]"; }
#line 4062 "parser_1st.tab.c"
    break;

  case 237: /* PRIMARY: ARRAYCREATIONEXPRESSION  */
#line 824 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4068 "parser_1st.tab.c"
    break;

  case 238: /* PRIMARYNONEWARRAY: LITERAL  */
#line 826 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4074 "parser_1st.tab.c"
    break;

  case 239: /* PRIMARYNONEWARRAY: CLASSLITERAL  */
#line 827 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4080 "parser_1st.tab.c"
    break;

  case 240: /* PRIMARYNONEWARRAY: THIS  */
#line 828 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 4089 "parser_1st.tab.c"
    break;

  case 242: /* PRIMARYNONEWARRAY: OPENPARAN EXPRESSION CLOSEPARAN  */
#line 833 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4095 "parser_1st.tab.c"
    break;

  case 243: /* PRIMARYNONEWARRAY: CLASSINSTANCECREATIONEXPRESSION  */
#line 834 "parser_1st.y"
                                                              {(yyval.val) = (yyvsp[0].val); generalmap[(yyval.val)].isnewclass = true;}
#line 4101 "parser_1st.tab.c"
    break;

  case 244: /* PRIMARYNONEWARRAY: FIELDACCESS  */
#line 835 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4107 "parser_1st.tab.c"
    break;

  case 245: /* PRIMARYNONEWARRAY: ARRAYACCESS  */
#line 836 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4113 "parser_1st.tab.c"
    break;

  case 246: /* PRIMARYNONEWARRAY: METHODINVOCATION  */
#line 837 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4119 "parser_1st.tab.c"
    break;

  case 248: /* LITERAL: INTEGERLITERAL  */
#line 840 "parser_1st.y"
                        {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "int"; ds[chartonum((yyval.val))]["var"] = new_var(); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4125 "parser_1st.tab.c"
    break;

  case 249: /* LITERAL: FLOATINGPOINTLITERAL  */
#line 841 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["start"] = numtostring(code.size());ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4131 "parser_1st.tab.c"
    break;

  case 250: /* LITERAL: BOOLEANLITERAL  */
#line 842 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4137 "parser_1st.tab.c"
    break;

  case 251: /* LITERAL: CHARACTERLITERAL  */
#line 843 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4143 "parser_1st.tab.c"
    break;

  case 252: /* LITERAL: STRINGLITERAL  */
#line 844 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4149 "parser_1st.tab.c"
    break;

  case 253: /* LITERAL: TEXTBLOCK  */
#line 845 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4155 "parser_1st.tab.c"
    break;

  case 254: /* LITERAL: NULLLITERAL  */
#line 846 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4161 "parser_1st.tab.c"
    break;

  case 264: /* CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
#line 859 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[0].val);}
#line 4167 "parser_1st.tab.c"
    break;

  case 268: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  */
#line 864 "parser_1st.y"
                                                                                                           {(yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-2].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-2].val))];  }
#line 4173 "parser_1st.tab.c"
    break;

  case 269: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  */
#line 865 "parser_1st.y"
                                                                                                                     {/*TODO*/}
#line 4179 "parser_1st.tab.c"
    break;

  case 270: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 866 "parser_1st.y"
                                                                                                                        {/*TODO*/}
#line 4185 "parser_1st.tab.c"
    break;

  case 271: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY  */
#line 867 "parser_1st.y"
                                                                                                                                  {/*TODO*/}
#line 4191 "parser_1st.tab.c"
    break;

  case 276: /* CLASSORINTERFACETYPETOINSTANTIATE: IDENTIFIER  */
#line 873 "parser_1st.y"
                                                {   (yyval.val) = new_temp(); ds[ chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val)); ds[ chartonum((yyval.val))]["class"] = "true";
                                                     }
#line 4198 "parser_1st.tab.c"
    break;

  case 277: /* ARGUMENTLIST: EXPRESSION  */
#line 876 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            ds2[chartonum((yyval.val))]["type"].push_back(ds[chartonum((yyvsp[0].val))]["type"]);
                            ds2[chartonum((yyval.val))]["var"].push_back(ds[chartonum((yyvsp[0].val))]["var"]);
                            }
#line 4207 "parser_1st.tab.c"
    break;

  case 278: /* ARGUMENTLIST: ARGUMENTLIST COMMA EXPRESSION  */
#line 880 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4220 "parser_1st.tab.c"
    break;

  case 279: /* METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  */
#line 889 "parser_1st.y"
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
#line 4237 "parser_1st.tab.c"
    break;

  case 280: /* METHODINVOCATION: METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 901 "parser_1st.y"
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
#line 4261 "parser_1st.tab.c"
    break;

  case 281: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 920 "parser_1st.y"
                                                                        {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val));
                                                        string name = chartostring((yyvsp[-4].val)), name2 = chartostring((yyvsp[-2].val));
                                                        objdetails detail = getobjdetails(name,name2);
                                                        string fname = "";
                                                        if(detail.ismethod){
                                                            fname = pref[chartostring((yyvsp[-4].val))]+chartostring((yyvsp[-2].val));
                                                            // ds[curr]["type"] = detail.field.typ.name;
                                                        }else{
                                                            object_error_func(name,name2,yylineno);
                                                        }
                                                        // ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = detail.method.rettype.name;
                                                        // code.push_back(ds[curr]["type"]);
                                                        vector<string> types;
                                                        type_check_function(name2,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
}
#line 4288 "parser_1st.tab.c"
    break;

  case 282: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 942 "parser_1st.y"
                                                                                    {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr5 = chartonum((yyvsp[-1].val));
                                                        string name = chartostring((yyvsp[-5].val)), name2 = chartostring((yyvsp[-3].val));
                                                        objdetails detail = getobjdetails(name,name2);
                                                        string fname = "";
                                                        if(detail.ismethod){
                                                            fname = pref[chartostring((yyvsp[-5].val))]+chartostring((yyvsp[-3].val));
                                                            // ds[curr]["type"] = detail.field.typ.name;
                                                        }else{
                                                            object_error_func(name,name2,yylineno);
                                                        }
                                                        // ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = methods[name].rettype.name;
                                                        vector<string> types;
                                                        for(auto i:ds2[curr5]["type"]){
                                                            types.push_back(i);
                                                        }
                                                        type_check_function(name2,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
}
#line 4317 "parser_1st.tab.c"
    break;

  case 311: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS  */
#line 998 "parser_1st.y"
                                                         {/*NOT SUPPORTED*/}
#line 4323 "parser_1st.tab.c"
    break;

  case 312: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS DIMS  */
#line 999 "parser_1st.y"
                                                                       {/*NOT SUPPORTED*/}
#line 4329 "parser_1st.tab.c"
    break;

  case 313: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER  */
#line 1000 "parser_1st.y"
                                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-2].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; assert (generalmap[(yyvsp[0].val)].vinit.dims.size() == temp[(yyvsp[-1].val)]); }
#line 4335 "parser_1st.tab.c"
    break;

  case 314: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER  */
#line 1001 "parser_1st.y"
                                                                               {/*NOT SUPPORTED*/}
#line 4341 "parser_1st.tab.c"
    break;

  case 315: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS  */
#line 1002 "parser_1st.y"
                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; ds[chartonum((yyval.val))]["arr"] = "true"; ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyvsp[0].val))]["var"]; ds[chartonum((yyval.val))]["type"] = chartostring((yyvsp[-1].val)); ds[chartonum((yyval.val))]["start"] = ds[chartonum((yyvsp[0].val))]["start"];}
#line 4347 "parser_1st.tab.c"
    break;

  case 316: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS  */
#line 1003 "parser_1st.y"
                                                                   {/*NOT SUPPORTED*/}
#line 4353 "parser_1st.tab.c"
    break;

  case 317: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS  */
#line 1004 "parser_1st.y"
                                                   {/*NOT SUPPORTED*/}
#line 4359 "parser_1st.tab.c"
    break;

  case 318: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS  */
#line 1005 "parser_1st.y"
                                                              {/*NOT SUPPORTED*/}
#line 4365 "parser_1st.tab.c"
    break;

  case 319: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE  */
#line 1006 "parser_1st.y"
                                               {/*TODO whats this*/}
#line 4371 "parser_1st.tab.c"
    break;

  case 320: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE  */
#line 1007 "parser_1st.y"
                                                         {/*TODO whats this*/}
#line 4377 "parser_1st.tab.c"
    break;

  case 321: /* ARRAYINITIALIZER: OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  */
#line 1009 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4383 "parser_1st.tab.c"
    break;

  case 322: /* ARRAYINITIALIZER: OPENCURLY CLOSECURLY  */
#line 1010 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4389 "parser_1st.tab.c"
    break;

  case 323: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST  */
#line 1012 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4395 "parser_1st.tab.c"
    break;

  case 324: /* ARRAYINITIALIZER1: COMMA  */
#line 1013 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=2;}
#line 4401 "parser_1st.tab.c"
    break;

  case 325: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST COMMA  */
#line 1014 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4407 "parser_1st.tab.c"
    break;

  case 326: /* DIMEXPRS: DIMEXPR  */
#line 1016 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[0].val))];}
#line 4413 "parser_1st.tab.c"
    break;

  case 327: /* DIMEXPRS: DIMEXPRS DIMEXPR  */
#line 1017 "parser_1st.y"
                             {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum((yyvsp[-1].val))]["var"]+" *"+ds[chartonum((yyvsp[0].val))]["type"]+" "+ds[ chartonum((yyvsp[0].val))]["var"]);
                              ds[ chartonum((yyval.val))]["var"] = t;  }
#line 4421 "parser_1st.tab.c"
    break;

  case 328: /* DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1021 "parser_1st.y"
                                            {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = varaddrstoint(ds[chartonum((yyvsp[-1].val))]["var"]); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-1].val))];}
#line 4427 "parser_1st.tab.c"
    break;

  case 329: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZER  */
#line 1023 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4433 "parser_1st.tab.c"
    break;

  case 330: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  */
#line 1024 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4439 "parser_1st.tab.c"
    break;

  case 332: /* ARRAYACCESS: PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1031 "parser_1st.y"
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
#line 4461 "parser_1st.tab.c"
    break;

  case 333: /* ARRAYACCESS: IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1048 "parser_1st.y"
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
#line 4479 "parser_1st.tab.c"
    break;

  case 334: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  */
#line 1062 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4485 "parser_1st.tab.c"
    break;

  case 335: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  */
#line 1063 "parser_1st.y"
                                                                                                    {}
#line 4491 "parser_1st.tab.c"
    break;

  case 336: /* CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  */
#line 1065 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4497 "parser_1st.tab.c"
    break;

  case 337: /* CONDITIONALOREXPRESSION: CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  */
#line 1066 "parser_1st.y"
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
#line 4515 "parser_1st.tab.c"
    break;

  case 338: /* CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  */
#line 1080 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4521 "parser_1st.tab.c"
    break;

  case 339: /* CONDITIONALANDEXPRESSION: CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  */
#line 1081 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4535 "parser_1st.tab.c"
    break;

  case 340: /* INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  */
#line 1091 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4541 "parser_1st.tab.c"
    break;

  case 341: /* INCLUSIVEOREXPRESSION: INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  */
#line 1092 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4554 "parser_1st.tab.c"
    break;

  case 342: /* EXCLUSIVEOREXPRESSION: ANDEXPRESSION  */
#line 1101 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4560 "parser_1st.tab.c"
    break;

  case 343: /* EXCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  */
#line 1102 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4573 "parser_1st.tab.c"
    break;

  case 344: /* ANDEXPRESSION: EQUALITYEXPRESSION  */
#line 1110 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4579 "parser_1st.tab.c"
    break;

  case 345: /* ANDEXPRESSION: ANDEXPRESSION AND EQUALITYEXPRESSION  */
#line 1111 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4593 "parser_1st.tab.c"
    break;

  case 346: /* EQUALITYEXPRESSION: RELATIONALEXPRESSION  */
#line 1121 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
#line 4606 "parser_1st.tab.c"
    break;

  case 347: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  */
#line 1129 "parser_1st.y"
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
#line 4627 "parser_1st.tab.c"
    break;

  case 348: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  */
#line 1145 "parser_1st.y"
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
#line 4649 "parser_1st.tab.c"
    break;

  case 349: /* RELATIONALEXPRESSION: SHIFTEXPRESSION  */
#line 1163 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4659 "parser_1st.tab.c"
    break;

  case 350: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  */
#line 1168 "parser_1st.y"
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
#line 4682 "parser_1st.tab.c"
    break;

  case 351: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  */
#line 1186 "parser_1st.y"
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
#line 4701 "parser_1st.tab.c"
    break;

  case 352: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  */
#line 1200 "parser_1st.y"
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
#line 4720 "parser_1st.tab.c"
    break;

  case 353: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  */
#line 1214 "parser_1st.y"
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
#line 4739 "parser_1st.tab.c"
    break;

  case 355: /* SHIFTEXPRESSION: ADDITIVEEXPRESSION  */
#line 1230 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4745 "parser_1st.tab.c"
    break;

  case 356: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  */
#line 1231 "parser_1st.y"
                                                                                    {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4759 "parser_1st.tab.c"
    break;

  case 357: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1240 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4772 "parser_1st.tab.c"
    break;

  case 358: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1248 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4785 "parser_1st.tab.c"
    break;

  case 359: /* ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  */
#line 1257 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 4791 "parser_1st.tab.c"
    break;

  case 360: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  */
#line 1258 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4804 "parser_1st.tab.c"
    break;

  case 361: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  */
#line 1266 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4817 "parser_1st.tab.c"
    break;

  case 362: /* MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  */
#line 1275 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4823 "parser_1st.tab.c"
    break;

  case 363: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  */
#line 1276 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4836 "parser_1st.tab.c"
    break;

  case 364: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  */
#line 1284 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4849 "parser_1st.tab.c"
    break;

  case 365: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  */
#line 1292 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4862 "parser_1st.tab.c"
    break;

  case 366: /* UNARYEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1301 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4868 "parser_1st.tab.c"
    break;

  case 367: /* UNARYEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1302 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4874 "parser_1st.tab.c"
    break;

  case 368: /* UNARYEXPRESSION: PLUS UNARYEXPRESSION  */
#line 1303 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 4882 "parser_1st.tab.c"
    break;

  case 369: /* UNARYEXPRESSION: MINUS UNARYEXPRESSION  */
#line 1306 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4895 "parser_1st.tab.c"
    break;

  case 370: /* UNARYEXPRESSION: UNARYEXPRESSIONNOTPLUSMINUS  */
#line 1314 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 4901 "parser_1st.tab.c"
    break;

  case 371: /* PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  */
#line 1316 "parser_1st.y"
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
#line 4919 "parser_1st.tab.c"
    break;

  case 372: /* PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  */
#line 1330 "parser_1st.y"
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
#line 4937 "parser_1st.tab.c"
    break;

  case 373: /* UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  */
#line 1344 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4943 "parser_1st.tab.c"
    break;

  case 374: /* UNARYEXPRESSIONNOTPLUSMINUS: COMPLEMENT UNARYEXPRESSION  */
#line 1345 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4956 "parser_1st.tab.c"
    break;

  case 375: /* UNARYEXPRESSIONNOTPLUSMINUS: NOT UNARYEXPRESSION  */
#line 1353 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4969 "parser_1st.tab.c"
    break;

  case 376: /* POSTFIXEXPRESSION: PRIMARY  */
#line 1362 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4975 "parser_1st.tab.c"
    break;

  case 377: /* POSTFIXEXPRESSION: EXPRESSIONNAME  */
#line 1363 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4981 "parser_1st.tab.c"
    break;

  case 378: /* POSTFIXEXPRESSION: IDENTIFIER  */
#line 1364 "parser_1st.y"
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
#line 5000 "parser_1st.tab.c"
    break;

  case 379: /* POSTFIXEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1378 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5006 "parser_1st.tab.c"
    break;

  case 380: /* POSTFIXEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1379 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5012 "parser_1st.tab.c"
    break;

  case 381: /* POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  */
#line 1381 "parser_1st.y"
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
#line 5029 "parser_1st.tab.c"
    break;

  case 382: /* POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  */
#line 1394 "parser_1st.y"
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
#line 5048 "parser_1st.tab.c"
    break;

  case 384: /* METHODDECLARATION: METHODHEADER METHODBODY  */
#line 1412 "parser_1st.y"
                                            {
    (yyval.val) =(yyvsp[-1].val);
    method_det[ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5071 "parser_1st.tab.c"
    break;

  case 385: /* METHODDECLARATION: SUPER1 METHODHEADER METHODBODY  */
#line 1431 "parser_1st.y"
                                                      {
                        (yyval.val) =(yyvsp[-1].val);
                        method_det[ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5098 "parser_1st.tab.c"
    break;

  case 386: /* METHODDECLARATION: SUPER2 METHODHEADER METHODBODY  */
#line 1453 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5123 "parser_1st.tab.c"
    break;

  case 387: /* METHODDECLARATION: SUPER3 METHODHEADER METHODBODY  */
#line 1473 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5148 "parser_1st.tab.c"
    break;

  case 388: /* METHODDECLARATION: METHODMODIFIERS METHODHEADER METHODBODY  */
#line 1493 "parser_1st.y"
                                                               {(yyval.val) =(yyvsp[-1].val);
                    method_det[ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5173 "parser_1st.tab.c"
    break;

  case 394: /* METHODHEADER: TYPE METHODDECLARATOR  */
#line 1520 "parser_1st.y"
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
#line 5192 "parser_1st.tab.c"
    break;

  case 395: /* METHODHEADER: VOID METHODDECLARATOR  */
#line 1534 "parser_1st.y"
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
#line 5211 "parser_1st.tab.c"
    break;

  case 406: /* METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1563 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));              
                                        method_det[chartostring((yyvsp[-2].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        }
#line 5223 "parser_1st.tab.c"
    break;

  case 407: /* METHODDECLARATOR: IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 1570 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                method_det[chartostring((yyvsp[-3].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        for(auto i:ds2[curr3]["param"])
                                        code.push_back("pop param, "+ i);}
#line 5234 "parser_1st.tab.c"
    break;

  case 416: /* FORMALPARAMETERLIST: FORMALPARAMETER  */
#line 1586 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 5243 "parser_1st.tab.c"
    break;

  case 417: /* FORMALPARAMETERLIST: FORMALPARAMETERLIST COMMA FORMALPARAMETER  */
#line 1590 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 5253 "parser_1st.tab.c"
    break;

  case 418: /* FORMALPARAMETER: TYPE VARIABLEDECLARATORID  */
#line 1596 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 5262 "parser_1st.tab.c"
    break;

  case 420: /* FORMALPARAMETER: FINAL TYPE VARIABLEDECLARATORID  */
#line 1601 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 5271 "parser_1st.tab.c"
    break;

  case 423: /* METHODBODY: BLOCK  */
#line 1611 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 5277 "parser_1st.tab.c"
    break;

  case 427: /* BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 1618 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val);  }
#line 5283 "parser_1st.tab.c"
    break;

  case 429: /* BLOCKSTATEMENTS: BLOCKSTATEMENT  */
#line 1621 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val);  
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
#line 5291 "parser_1st.tab.c"
    break;

  case 430: /* BLOCKSTATEMENTS: BLOCKSTATEMENTS BLOCKSTATEMENT  */
#line 1624 "parser_1st.y"
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
#line 5306 "parser_1st.tab.c"
    break;

  case 432: /* BLOCKSTATEMENT: LOCALVARIABLEDECLARATIONSTATEMENT  */
#line 1636 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val); 
                
               }
#line 5314 "parser_1st.tab.c"
    break;

  case 433: /* BLOCKSTATEMENT: STATEMENT  */
#line 1639 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
               }
#line 5321 "parser_1st.tab.c"
    break;

  case 435: /* LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  */
#line 1644 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 5327 "parser_1st.tab.c"
    break;

  case 436: /* LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1646 "parser_1st.y"
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
                                    auto g = dimtoid[-x];
                                    cerr<<g;
                                    assert(isnum(g) && "only constant direct expressions supported");
                                    ft = stringtonum(g);


                                }
                                arrsize *= ft;
                                cerr<<ft<<" ";

                            }
                              curoffset += arrsize* gettypesize(symboltable[x.first.name].typ.name);
                            // TODO support class sizes

                            // cout<<x.first.name;
                            // TODO: printvarentry needed
                            printvarentry(symboltable[x.first.name]);
                            preservedsymboltable[{x.first.name,scope}] = symboltable[x.first.name];
                        }
                        }
#line 5388 "parser_1st.tab.c"
    break;

  case 437: /* LOCALVARIABLEDECLARATION: LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1702 "parser_1st.y"
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
                                    auto g = dimtoid[-x];
                                   cerr<<g;

                                    assert(isnum(g) && "only constant direct expressions supported");
                                    ft = stringtonum(g);


                                }
                                arrsize *= ft;
                                cerr<<ft<<" ";

                            }
                            
                            curoffset += arrsize* gettypesize(symboltable[x.first.name].typ.name);
                            // TODO support class sizes

                            // cout<<x.first.name;
                            printvarentry(symboltable[x.first.name]);
                            preservedsymboltable[{x.first.name,scope}] = symboltable[x.first.name];
                        }
                        }
#line 5451 "parser_1st.tab.c"
    break;

  case 438: /* LOCALVARIABLETYPE: TYPE  */
#line 1761 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 5457 "parser_1st.tab.c"
    break;

  case 439: /* LOCALVARIABLETYPE: VAR  */
#line 1762 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5463 "parser_1st.tab.c"
    break;

  case 440: /* STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1765 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
#line 5469 "parser_1st.tab.c"
    break;

  case 441: /* STATEMENT: LABELEDSTATEMENT  */
#line 1766 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5475 "parser_1st.tab.c"
    break;

  case 442: /* STATEMENT: IFTHENSTATEMENT  */
#line 1767 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5481 "parser_1st.tab.c"
    break;

  case 443: /* STATEMENT: IFTHENELSESTATEMENT  */
#line 1768 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5487 "parser_1st.tab.c"
    break;

  case 444: /* STATEMENT: WHILESTATEMENT  */
#line 1769 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5493 "parser_1st.tab.c"
    break;

  case 445: /* STATEMENT: FORSTATEMENT  */
#line 1770 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5499 "parser_1st.tab.c"
    break;

  case 446: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  */
#line 1772 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5505 "parser_1st.tab.c"
    break;

  case 447: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EMPTYSTATEMENT  */
#line 1774 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5511 "parser_1st.tab.c"
    break;

  case 448: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EXPRESSIONSTATEMENT  */
#line 1775 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5517 "parser_1st.tab.c"
    break;

  case 449: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: ASSERTSTATEMENT  */
#line 1776 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5523 "parser_1st.tab.c"
    break;

  case 450: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BREAKSTATEMENT  */
#line 1777 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5529 "parser_1st.tab.c"
    break;

  case 451: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: CONTINUESTATEMENT  */
#line 1778 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5535 "parser_1st.tab.c"
    break;

  case 452: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: RETURNSTATEMENT  */
#line 1779 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5541 "parser_1st.tab.c"
    break;

  case 453: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: THROWSTATEMENT  */
#line 1780 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5547 "parser_1st.tab.c"
    break;

  case 454: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: YIELDSTATEMENT  */
#line 1781 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5553 "parser_1st.tab.c"
    break;

  case 455: /* EMPTYSTATEMENT: SEMICOLON  */
#line 1783 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5559 "parser_1st.tab.c"
    break;

  case 456: /* EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  */
#line 1785 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val); }
#line 5565 "parser_1st.tab.c"
    break;

  case 457: /* STATEMENTEXPRESSION: ASSIGNMENT  */
#line 1787 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5571 "parser_1st.tab.c"
    break;

  case 458: /* STATEMENTEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1788 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5577 "parser_1st.tab.c"
    break;

  case 459: /* STATEMENTEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1789 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5583 "parser_1st.tab.c"
    break;

  case 460: /* STATEMENTEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1790 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5589 "parser_1st.tab.c"
    break;

  case 461: /* STATEMENTEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1791 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5595 "parser_1st.tab.c"
    break;

  case 462: /* STATEMENTEXPRESSION: METHODINVOCATION  */
#line 1792 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5601 "parser_1st.tab.c"
    break;

  case 463: /* STATEMENTEXPRESSION: CLASSINSTANCECREATIONEXPRESSION  */
#line 1793 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5607 "parser_1st.tab.c"
    break;

  case 466: /* BREAKSTATEMENT: BREAK SEMICOLON  */
#line 1798 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5620 "parser_1st.tab.c"
    break;

  case 468: /* CONTINUESTATEMENT: CONTINUE SEMICOLON  */
#line 1808 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5633 "parser_1st.tab.c"
    break;

  case 470: /* RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  */
#line 1818 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5644 "parser_1st.tab.c"
    break;

  case 471: /* RETURNSTATEMENT: RETURN SEMICOLON  */
#line 1824 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 5655 "parser_1st.tab.c"
    break;

  case 475: /* IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1837 "parser_1st.y"
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
#line 5676 "parser_1st.tab.c"
    break;

  case 476: /* IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT  */
#line 1854 "parser_1st.y"
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
#line 5692 "parser_1st.tab.c"
    break;

  case 477: /* IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF  */
#line 1866 "parser_1st.y"
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
#line 5708 "parser_1st.tab.c"
    break;

  case 478: /* STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1878 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5714 "parser_1st.tab.c"
    break;

  case 479: /* STATEMENTNOSHORTIF: LABELEDSTATEMENTNOSHORTIF  */
#line 1879 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5720 "parser_1st.tab.c"
    break;

  case 480: /* STATEMENTNOSHORTIF: IFTHENELSESTATEMENTNOSHORTIF  */
#line 1880 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5726 "parser_1st.tab.c"
    break;

  case 481: /* STATEMENTNOSHORTIF: WHILESTATEMENTNOSHORTIF  */
#line 1881 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5732 "parser_1st.tab.c"
    break;

  case 482: /* STATEMENTNOSHORTIF: FORSTATEMENTNOSHORTIF  */
#line 1882 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5738 "parser_1st.tab.c"
    break;

  case 484: /* WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1886 "parser_1st.y"
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
#line 5754 "parser_1st.tab.c"
    break;

  case 485: /* FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  */
#line 1898 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); popscope();}
#line 5760 "parser_1st.tab.c"
    break;

  case 486: /* FORSTATEMENTNOSHORTIF: ENHANCEDFORSTATEMENTNOSHORTIF  */
#line 1899 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5766 "parser_1st.tab.c"
    break;

  case 487: /* WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1902 "parser_1st.y"
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
#line 5781 "parser_1st.tab.c"
    break;

  case 488: /* FORSTATEMENT: BASICFORSTATEMENT  */
#line 1913 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5787 "parser_1st.tab.c"
    break;

  case 489: /* FORSTATEMENT: ENHANCEDFORSTATEMENT  */
#line 1914 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5793 "parser_1st.tab.c"
    break;

  case 490: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 1916 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 5806 "parser_1st.tab.c"
    break;

  case 491: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1924 "parser_1st.y"
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
#line 5822 "parser_1st.tab.c"
    break;

  case 492: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 1935 "parser_1st.y"
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
#line 5841 "parser_1st.tab.c"
    break;

  case 493: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1949 "parser_1st.y"
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
#line 5862 "parser_1st.tab.c"
    break;

  case 494: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 1965 "parser_1st.y"
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
#line 5880 "parser_1st.tab.c"
    break;

  case 495: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1978 "parser_1st.y"
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
#line 5901 "parser_1st.tab.c"
    break;

  case 496: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 1994 "parser_1st.y"
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
#line 5922 "parser_1st.tab.c"
    break;

  case 497: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2010 "parser_1st.y"
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
#line 5943 "parser_1st.tab.c"
    break;

  case 498: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2027 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 5956 "parser_1st.tab.c"
    break;

  case 499: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2035 "parser_1st.y"
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
#line 5972 "parser_1st.tab.c"
    break;

  case 500: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2046 "parser_1st.y"
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
#line 5991 "parser_1st.tab.c"
    break;

  case 501: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2060 "parser_1st.y"
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
#line 6013 "parser_1st.tab.c"
    break;

  case 502: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2077 "parser_1st.y"
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
#line 6031 "parser_1st.tab.c"
    break;

  case 503: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2090 "parser_1st.y"
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
#line 6052 "parser_1st.tab.c"
    break;

  case 504: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2106 "parser_1st.y"
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
#line 6074 "parser_1st.tab.c"
    break;

  case 505: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2123 "parser_1st.y"
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
#line 6095 "parser_1st.tab.c"
    break;

  case 508: /* FORINIT: STATEMENTEXPRESSIONLIST  */
#line 2145 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 6101 "parser_1st.tab.c"
    break;

  case 509: /* FORINIT: LOCALVARIABLEDECLARATION  */
#line 2146 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 6107 "parser_1st.tab.c"
    break;

  case 510: /* FORUPDATE: STATEMENTEXPRESSIONLIST  */
#line 2148 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 6121 "parser_1st.tab.c"
    break;

  case 511: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION  */
#line 2158 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 6127 "parser_1st.tab.c"
    break;

  case 512: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION  */
#line 2159 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 6139 "parser_1st.tab.c"
    break;

  case 550: /* SUPER1: PUBLIC  */
#line 2212 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6145 "parser_1st.tab.c"
    break;

  case 551: /* SUPER1: PRIVATE  */
#line 2213 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6151 "parser_1st.tab.c"
    break;

  case 552: /* SUPER1: PROTECTED  */
#line 2214 "parser_1st.y"
                    {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6157 "parser_1st.tab.c"
    break;

  case 553: /* SUPER1: SUPER1 PUBLIC  */
#line 2215 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6163 "parser_1st.tab.c"
    break;

  case 554: /* SUPER1: SUPER1 PRIVATE  */
#line 2216 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6169 "parser_1st.tab.c"
    break;

  case 555: /* SUPER1: SUPER1 PROTECTED  */
#line 2217 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6175 "parser_1st.tab.c"
    break;

  case 556: /* SUPER2: STATIC  */
#line 2219 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6181 "parser_1st.tab.c"
    break;

  case 557: /* SUPER2: FINAL  */
#line 2220 "parser_1st.y"
                 {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6187 "parser_1st.tab.c"
    break;

  case 558: /* SUPER2: SUPER1 STATIC  */
#line 2221 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6193 "parser_1st.tab.c"
    break;

  case 559: /* SUPER2: SUPER1 FINAL  */
#line 2222 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6199 "parser_1st.tab.c"
    break;

  case 560: /* SUPER2: SUPER2 STATIC  */
#line 2223 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6205 "parser_1st.tab.c"
    break;

  case 561: /* SUPER2: SUPER2 FINAL  */
#line 2224 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6211 "parser_1st.tab.c"
    break;

  case 562: /* SUPER2: SUPER2 PUBLIC  */
#line 2225 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6217 "parser_1st.tab.c"
    break;

  case 563: /* SUPER2: SUPER2 PRIVATE  */
#line 2226 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6223 "parser_1st.tab.c"
    break;

  case 564: /* SUPER2: SUPER2 PROTECTED  */
#line 2227 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6229 "parser_1st.tab.c"
    break;

  case 565: /* SUPER3: ABSTRACT  */
#line 2229 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6235 "parser_1st.tab.c"
    break;

  case 566: /* SUPER3: STRICTFP  */
#line 2230 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6241 "parser_1st.tab.c"
    break;

  case 567: /* SUPER3: SUPER2 ABSTRACT  */
#line 2231 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6247 "parser_1st.tab.c"
    break;

  case 568: /* SUPER3: SUPER2 STRICTFP  */
#line 2232 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6253 "parser_1st.tab.c"
    break;

  case 569: /* SUPER3: SUPER3 ABSTRACT  */
#line 2233 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6259 "parser_1st.tab.c"
    break;

  case 570: /* SUPER3: SUPER3 STRICTFP  */
#line 2234 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6265 "parser_1st.tab.c"
    break;

  case 571: /* SUPER3: SUPER3 PUBLIC  */
#line 2235 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6271 "parser_1st.tab.c"
    break;

  case 572: /* SUPER3: SUPER3 PRIVATE  */
#line 2236 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6277 "parser_1st.tab.c"
    break;

  case 573: /* SUPER3: SUPER3 PROTECTED  */
#line 2237 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6283 "parser_1st.tab.c"
    break;

  case 574: /* SUPER3: SUPER3 STATIC  */
#line 2238 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6289 "parser_1st.tab.c"
    break;

  case 575: /* SUPER3: SUPER3 FINAL  */
#line 2239 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6295 "parser_1st.tab.c"
    break;

  case 576: /* FIELDMODIFIERS: SUPER3 TRANSIENT  */
#line 2241 "parser_1st.y"
                                 {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6301 "parser_1st.tab.c"
    break;

  case 577: /* FIELDMODIFIERS: SUPER3 VOLATILE  */
#line 2242 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6307 "parser_1st.tab.c"
    break;

  case 578: /* FIELDMODIFIERS: FIELDMODIFIERS TRANSIENT  */
#line 2243 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6313 "parser_1st.tab.c"
    break;

  case 579: /* FIELDMODIFIERS: FIELDMODIFIERS VOLATILE  */
#line 2244 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6319 "parser_1st.tab.c"
    break;

  case 580: /* FIELDMODIFIERS: FIELDMODIFIERS PUBLIC  */
#line 2245 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6325 "parser_1st.tab.c"
    break;

  case 581: /* FIELDMODIFIERS: FIELDMODIFIERS PRIVATE  */
#line 2246 "parser_1st.y"
                                     {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6331 "parser_1st.tab.c"
    break;

  case 582: /* FIELDMODIFIERS: FIELDMODIFIERS PROTECTED  */
#line 2247 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6337 "parser_1st.tab.c"
    break;

  case 583: /* FIELDMODIFIERS: FIELDMODIFIERS STATIC  */
#line 2248 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6343 "parser_1st.tab.c"
    break;

  case 584: /* FIELDMODIFIERS: FIELDMODIFIERS FINAL  */
#line 2249 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6349 "parser_1st.tab.c"
    break;

  case 585: /* METHODMODIFIERS: SUPER3 SYNCHRONIZED  */
#line 2252 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6355 "parser_1st.tab.c"
    break;

  case 586: /* METHODMODIFIERS: SUPER3 NATIVE  */
#line 2253 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6361 "parser_1st.tab.c"
    break;

  case 587: /* METHODMODIFIERS: METHODMODIFIERS SYNCHRONIZED  */
#line 2254 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6367 "parser_1st.tab.c"
    break;

  case 588: /* METHODMODIFIERS: METHODMODIFIERS NATIVE  */
#line 2255 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6373 "parser_1st.tab.c"
    break;

  case 589: /* METHODMODIFIERS: METHODMODIFIERS ABSTRACT  */
#line 2256 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6379 "parser_1st.tab.c"
    break;

  case 590: /* METHODMODIFIERS: METHODMODIFIERS STRICTFP  */
#line 2257 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6385 "parser_1st.tab.c"
    break;

  case 591: /* METHODMODIFIERS: METHODMODIFIERS PUBLIC  */
#line 2258 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6391 "parser_1st.tab.c"
    break;

  case 592: /* METHODMODIFIERS: METHODMODIFIERS PRIVATE  */
#line 2259 "parser_1st.y"
                                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6397 "parser_1st.tab.c"
    break;

  case 593: /* METHODMODIFIERS: METHODMODIFIERS PROTECTED  */
#line 2260 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6403 "parser_1st.tab.c"
    break;

  case 594: /* METHODMODIFIERS: METHODMODIFIERS STATIC  */
#line 2261 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6409 "parser_1st.tab.c"
    break;

  case 595: /* METHODMODIFIERS: METHODMODIFIERS FINAL  */
#line 2262 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6415 "parser_1st.tab.c"
    break;

  case 599: /* TYPEARGUMENT: REFERENCETYPE  */
#line 2269 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 6421 "parser_1st.tab.c"
    break;

  case 600: /* TYPEARGUMENT: WILDCARD  */
#line 2270 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 6427 "parser_1st.tab.c"
    break;

  case 605: /* INTERFACETYPE: CLASSTYPE  */
#line 2279 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 6433 "parser_1st.tab.c"
    break;


#line 6437 "parser_1st.tab.c"

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

#line 2281 "parser_1st.y"



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

    cout2<<"Token, Name(Lexeme), Type, Line Number, Scope, Dims(If array), ScopeINFO(Child), ScopeINFO(Parent) \n";

    for (auto x : preservedsymboltable){
        cout2<< x.second.token << ", " << x.first.first << ", " << x.second.typ.name << ", " << x.second.lineno << ", " << x.first.second << ", " << x.second.typ.dims << endl;

    }
   
    

    for(auto x : parentscope){
        cout2<<", , , , , , "<<x.first<<", "<<x.second<<endl;
    }



  

}
