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
    }
    bool tempincscope = false;
    void newscope(){
        if(tempincscope){tempincscope=false; return;}
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
        
        cerr<< "gettypefromsymtable"<<endl;
        cerr<< a<<endl;
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
        if(s=="boolean")return 11;
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



    

#line 250 "parser_1st.tab.c"

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
  YYSYMBOL_FOR = 87,                       /* FOR  */
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
  YYSYMBOL_OPENCURLY = 147,                /* OPENCURLY  */
  YYSYMBOL_CLOSECURLY = 148,               /* CLOSECURLY  */
  YYSYMBOL_INTERFACEBODY = 149,            /* INTERFACEBODY  */
  YYSYMBOL_INTERFACEMEMBERDECLARATIONS = 150, /* INTERFACEMEMBERDECLARATIONS  */
  YYSYMBOL_INTERFACEMEMBERDECLARATION = 151, /* INTERFACEMEMBERDECLARATION  */
  YYSYMBOL_INTERFACEDECLARATION = 152,     /* INTERFACEDECLARATION  */
  YYSYMBOL_TYPEPARAMETERS = 153,           /* TYPEPARAMETERS  */
  YYSYMBOL_TYPEPARAMETERLIST = 154,        /* TYPEPARAMETERLIST  */
  YYSYMBOL_TYPEPARAMETER = 155,            /* TYPEPARAMETER  */
  YYSYMBOL_TYPEBOUND = 156,                /* TYPEBOUND  */
  YYSYMBOL_ADDITIONALBOUND = 157,          /* ADDITIONALBOUND  */
  YYSYMBOL_CLASSEXTENDS = 158,             /* CLASSEXTENDS  */
  YYSYMBOL_CLASSIMPLEMENTS = 159,          /* CLASSIMPLEMENTS  */
  YYSYMBOL_INTERFACETYPELIST = 160,        /* INTERFACETYPELIST  */
  YYSYMBOL_CLASSPERMITS = 161,             /* CLASSPERMITS  */
  YYSYMBOL_TYPENAMES = 162,                /* TYPENAMES  */
  YYSYMBOL_CLASSBODY = 163,                /* CLASSBODY  */
  YYSYMBOL_CLASSBODYDECLARATIONS = 164,    /* CLASSBODYDECLARATIONS  */
  YYSYMBOL_CLASSBODYDECLARATION = 165,     /* CLASSBODYDECLARATION  */
  YYSYMBOL_CLASSMEMBERDECLARATION = 166,   /* CLASSMEMBERDECLARATION  */
  YYSYMBOL_FIELDDECLARATION = 167,         /* FIELDDECLARATION  */
  YYSYMBOL_VARIABLEDECLARATORLIST = 168,   /* VARIABLEDECLARATORLIST  */
  YYSYMBOL_VARIABLEDECLARATOR = 169,       /* VARIABLEDECLARATOR  */
  YYSYMBOL_VARIABLEDECLARATORID = 170,     /* VARIABLEDECLARATORID  */
  YYSYMBOL_VARIABLEINITIALIZER = 171,      /* VARIABLEINITIALIZER  */
  YYSYMBOL_EXPRESSION = 172,               /* EXPRESSION  */
  YYSYMBOL_ASSIGNMENTEXPRESSION = 173,     /* ASSIGNMENTEXPRESSION  */
  YYSYMBOL_ASSIGNMENT = 174,               /* ASSIGNMENT  */
  YYSYMBOL_LEFTHANDSIDE = 175,             /* LEFTHANDSIDE  */
  YYSYMBOL_ASSIGNMENTOPERATOR = 176,       /* ASSIGNMENTOPERATOR  */
  YYSYMBOL_FIELDACCESS = 177,              /* FIELDACCESS  */
  YYSYMBOL_PRIMARY = 178,                  /* PRIMARY  */
  YYSYMBOL_PRIMARYNONEWARRAY = 179,        /* PRIMARYNONEWARRAY  */
  YYSYMBOL_LITERAL = 180,                  /* LITERAL  */
  YYSYMBOL_CLASSLITERAL = 181,             /* CLASSLITERAL  */
  YYSYMBOL_SQUARESTAR = 182,               /* SQUARESTAR  */
  YYSYMBOL_CLASSINSTANCECREATIONEXPRESSION = 183, /* CLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION = 184, /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
  YYSYMBOL_CLASSORINTERFACETYPETOINSTANTIATE = 185, /* CLASSORINTERFACETYPETOINSTANTIATE  */
  YYSYMBOL_ARGUMENTLIST = 186,             /* ARGUMENTLIST  */
  YYSYMBOL_METHODINVOCATION = 187,         /* METHODINVOCATION  */
  YYSYMBOL_METHODREFERENCE = 188,          /* METHODREFERENCE  */
  YYSYMBOL_ARRAYCREATIONEXPRESSION = 189,  /* ARRAYCREATIONEXPRESSION  */
  YYSYMBOL_ARRAYINITIALIZER = 190,         /* ARRAYINITIALIZER  */
  YYSYMBOL_ARRAYINITIALIZER1 = 191,        /* ARRAYINITIALIZER1  */
  YYSYMBOL_DIMEXPRS = 192,                 /* DIMEXPRS  */
  YYSYMBOL_DIMEXPR = 193,                  /* DIMEXPR  */
  YYSYMBOL_VARIABLEINITIALIZERLIST = 194,  /* VARIABLEINITIALIZERLIST  */
  YYSYMBOL_ARRAYACCESS = 195,              /* ARRAYACCESS  */
  YYSYMBOL_CONDITIONALEXPRESSION = 196,    /* CONDITIONALEXPRESSION  */
  YYSYMBOL_CONDITIONALOREXPRESSION = 197,  /* CONDITIONALOREXPRESSION  */
  YYSYMBOL_CONDITIONALANDEXPRESSION = 198, /* CONDITIONALANDEXPRESSION  */
  YYSYMBOL_INCLUSIVEOREXPRESSION = 199,    /* INCLUSIVEOREXPRESSION  */
  YYSYMBOL_EXCLUSIVEOREXPRESSION = 200,    /* EXCLUSIVEOREXPRESSION  */
  YYSYMBOL_ANDEXPRESSION = 201,            /* ANDEXPRESSION  */
  YYSYMBOL_EQUALITYEXPRESSION = 202,       /* EQUALITYEXPRESSION  */
  YYSYMBOL_RELATIONALEXPRESSION = 203,     /* RELATIONALEXPRESSION  */
  YYSYMBOL_SHIFTEXPRESSION = 204,          /* SHIFTEXPRESSION  */
  YYSYMBOL_ADDITIVEEXPRESSION = 205,       /* ADDITIVEEXPRESSION  */
  YYSYMBOL_MULTIPLICATIVEEXPRESSION = 206, /* MULTIPLICATIVEEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSION = 207,          /* UNARYEXPRESSION  */
  YYSYMBOL_PREINCREMENTEXPRESSION = 208,   /* PREINCREMENTEXPRESSION  */
  YYSYMBOL_PREDECREMENTEXPRESSION = 209,   /* PREDECREMENTEXPRESSION  */
  YYSYMBOL_UNARYEXPRESSIONNOTPLUSMINUS = 210, /* UNARYEXPRESSIONNOTPLUSMINUS  */
  YYSYMBOL_POSTFIXEXPRESSION = 211,        /* POSTFIXEXPRESSION  */
  YYSYMBOL_POSTINCREMENTEXPRESSION = 212,  /* POSTINCREMENTEXPRESSION  */
  YYSYMBOL_POSTDECREMENTEXPRESSION = 213,  /* POSTDECREMENTEXPRESSION  */
  YYSYMBOL_INSTANCEOFEXPRESSION = 214,     /* INSTANCEOFEXPRESSION  */
  YYSYMBOL_METHODDECLARATION = 215,        /* METHODDECLARATION  */
  YYSYMBOL_METHODHEADER = 216,             /* METHODHEADER  */
  YYSYMBOL_THROWS2 = 217,                  /* THROWS2  */
  YYSYMBOL_EXCEPTIONTYPELIST = 218,        /* EXCEPTIONTYPELIST  */
  YYSYMBOL_EXCEPTIONTYPE = 219,            /* EXCEPTIONTYPE  */
  YYSYMBOL_METHODDECLARATOR = 220,         /* METHODDECLARATOR  */
  YYSYMBOL_RECEIVERPARAMETER = 221,        /* RECEIVERPARAMETER  */
  YYSYMBOL_FORMALPARAMETERLIST = 222,      /* FORMALPARAMETERLIST  */
  YYSYMBOL_FORMALPARAMETER = 223,          /* FORMALPARAMETER  */
  YYSYMBOL_VARIABLEARITYPARAMETER = 224,   /* VARIABLEARITYPARAMETER  */
  YYSYMBOL_METHODBODY = 225,               /* METHODBODY  */
  YYSYMBOL_INSTANCEINITIALIZER = 226,      /* INSTANCEINITIALIZER  */
  YYSYMBOL_STATICINITIALIZER = 227,        /* STATICINITIALIZER  */
  YYSYMBOL_BLOCK = 228,                    /* BLOCK  */
  YYSYMBOL_BLOCKSTATEMENTS = 229,          /* BLOCKSTATEMENTS  */
  YYSYMBOL_BLOCKSTATEMENT = 230,           /* BLOCKSTATEMENT  */
  YYSYMBOL_LOCALCLASSORINTERFACEDECLARATION = 231, /* LOCALCLASSORINTERFACEDECLARATION  */
  YYSYMBOL_LOCALVARIABLEDECLARATIONSTATEMENT = 232, /* LOCALVARIABLEDECLARATIONSTATEMENT  */
  YYSYMBOL_LOCALVARIABLEDECLARATION = 233, /* LOCALVARIABLEDECLARATION  */
  YYSYMBOL_LOCALVARIABLETYPE = 234,        /* LOCALVARIABLETYPE  */
  YYSYMBOL_STATEMENT = 235,                /* STATEMENT  */
  YYSYMBOL_STATEMENTWITHOUTTRAILINGSUBSTATEMENT = 236, /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
  YYSYMBOL_EMPTYSTATEMENT = 237,           /* EMPTYSTATEMENT  */
  YYSYMBOL_EXPRESSIONSTATEMENT = 238,      /* EXPRESSIONSTATEMENT  */
  YYSYMBOL_STATEMENTEXPRESSION = 239,      /* STATEMENTEXPRESSION  */
  YYSYMBOL_ASSERTSTATEMENT = 240,          /* ASSERTSTATEMENT  */
  YYSYMBOL_BREAKSTATEMENT = 241,           /* BREAKSTATEMENT  */
  YYSYMBOL_CONTINUESTATEMENT = 242,        /* CONTINUESTATEMENT  */
  YYSYMBOL_RETURNSTATEMENT = 243,          /* RETURNSTATEMENT  */
  YYSYMBOL_THROWSTATEMENT = 244,           /* THROWSTATEMENT  */
  YYSYMBOL_YIELDSTATEMENT = 245,           /* YIELDSTATEMENT  */
  YYSYMBOL_LABELEDSTATEMENT = 246,         /* LABELEDSTATEMENT  */
  YYSYMBOL_IFTHENSTATEMENT = 247,          /* IFTHENSTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENT = 248,      /* IFTHENELSESTATEMENT  */
  YYSYMBOL_IFTHENELSESTATEMENTNOSHORTIF = 249, /* IFTHENELSESTATEMENTNOSHORTIF  */
  YYSYMBOL_STATEMENTNOSHORTIF = 250,       /* STATEMENTNOSHORTIF  */
  YYSYMBOL_LABELEDSTATEMENTNOSHORTIF = 251, /* LABELEDSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENTNOSHORTIF = 252,  /* WHILESTATEMENTNOSHORTIF  */
  YYSYMBOL_FORSTATEMENTNOSHORTIF = 253,    /* FORSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENT = 254,           /* WHILESTATEMENT  */
  YYSYMBOL_FORSTATEMENT = 255,             /* FORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENT = 256,        /* BASICFORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENTNOSHORTIF = 257, /* BASICFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_ENHANCEDFORSTATEMENT = 258,     /* ENHANCEDFORSTATEMENT  */
  YYSYMBOL_ENHANCEDFORSTATEMENTNOSHORTIF = 259, /* ENHANCEDFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_FORINIT = 260,                  /* FORINIT  */
  YYSYMBOL_FORUPDATE = 261,                /* FORUPDATE  */
  YYSYMBOL_STATEMENTEXPRESSIONLIST = 262,  /* STATEMENTEXPRESSIONLIST  */
  YYSYMBOL_CONSTRUCTORDECLARATION = 263,   /* CONSTRUCTORDECLARATION  */
  YYSYMBOL_CONSTRUCTORDECLARATOR = 264,    /* CONSTRUCTORDECLARATOR  */
  YYSYMBOL_SIMPLETYPENAME = 265,           /* SIMPLETYPENAME  */
  YYSYMBOL_CONSTRUCTORBODY = 266,          /* CONSTRUCTORBODY  */
  YYSYMBOL_EXPLICITCONSTRUCTORINVOCATION = 267, /* EXPLICITCONSTRUCTORINVOCATION  */
  YYSYMBOL_SUPER1 = 268,                   /* SUPER1  */
  YYSYMBOL_SUPER2 = 269,                   /* SUPER2  */
  YYSYMBOL_SUPER3 = 270,                   /* SUPER3  */
  YYSYMBOL_FIELDMODIFIERS = 271,           /* FIELDMODIFIERS  */
  YYSYMBOL_METHODMODIFIERS = 272,          /* METHODMODIFIERS  */
  YYSYMBOL_TYPEARGUMENTS = 273,            /* TYPEARGUMENTS  */
  YYSYMBOL_TYPEARGUMENTLIST = 274,         /* TYPEARGUMENTLIST  */
  YYSYMBOL_TYPEARGUMENT = 275,             /* TYPEARGUMENT  */
  YYSYMBOL_WILDCARD = 276,                 /* WILDCARD  */
  YYSYMBOL_WILDCARDBOUNDS = 277,           /* WILDCARDBOUNDS  */
  YYSYMBOL_INTERFACETYPE = 278             /* INTERFACETYPE  */
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
#define YYLAST   6191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  152
/* YYNRULES -- Number of rules.  */
#define YYNRULES  604
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1145

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
       0,   210,   210,   211,   213,   214,   216,   217,   219,   220,
     222,   223,   224,   225,   226,   228,   229,   231,   233,   235,
     237,   240,   241,   243,   250,   258,   261,   262,   264,   287,
     288,   289,   291,   292,   293,   294,   296,   299,   300,   301,
     302,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   435,   436,   438,   439,   441,
     442,   444,   445,   446,   447,   448,   450,   453,   455,   456,
     458,   459,   462,   463,   465,   466,   468,   470,   472,   473,
     475,   477,   478,   480,   481,   483,   484,   486,   487,   488,
     489,   491,   492,   493,   494,   495,   497,   516,   534,   552,
     576,   586,   604,   612,   614,   622,   628,   629,   631,   633,
     636,   638,   652,   653,   661,   662,   664,   666,   668,   670,
     672,   674,   677,   684,   685,   687,   688,   690,   691,   692,
     696,   697,   698,   699,   700,   701,   702,   704,   705,   706,
     707,   708,   709,   710,   712,   713,   714,   715,   716,   717,
     718,   720,   721,   723,   724,   725,   726,   728,   729,   730,
     731,   732,   733,   734,   735,   737,   739,   740,   749,   760,
     775,   787,   803,   804,   805,   806,   807,   808,   809,   810,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     822,   823,   824,   825,   826,   828,   829,   831,   832,   833,
     835,   836,   837,   838,   839,   840,   841,   842,   843,   844,
     846,   847,   849,   850,   851,   853,   854,   856,   858,   859,
     865,   866,   867,   869,   870,   872,   873,   887,   888,   898,
     899,   908,   909,   917,   918,   928,   934,   950,   968,   973,
     988,  1002,  1016,  1030,  1032,  1033,  1042,  1050,  1059,  1060,
    1068,  1077,  1078,  1086,  1094,  1103,  1104,  1105,  1108,  1116,
    1118,  1132,  1146,  1147,  1155,  1164,  1165,  1166,  1176,  1177,
    1179,  1192,  1207,  1210,  1226,  1244,  1259,  1274,  1289,  1290,
    1291,  1292,  1293,  1296,  1308,  1320,  1321,  1322,  1323,  1324,
    1325,  1328,  1330,  1331,  1333,  1335,  1340,  1345,  1346,  1347,
    1348,  1349,  1350,  1352,  1353,  1355,  1359,  1365,  1369,  1370,
    1376,  1377,  1380,  1381,  1383,  1385,  1387,  1388,  1390,  1391,
    1398,  1399,  1400,  1402,  1404,  1406,  1407,  1428,  1429,  1432,
    1433,  1434,  1435,  1436,  1437,  1439,  1440,  1441,  1442,  1443,
    1444,  1445,  1446,  1447,  1449,  1451,  1453,  1454,  1455,  1456,
    1457,  1458,  1459,  1461,  1462,  1464,  1472,  1474,  1482,  1484,
    1490,  1497,  1499,  1501,  1503,  1519,  1531,  1543,  1544,  1545,
    1546,  1547,  1549,  1551,  1563,  1564,  1567,  1578,  1579,  1581,
    1589,  1600,  1613,  1629,  1642,  1658,  1674,  1691,  1699,  1710,
    1723,  1739,  1752,  1768,  1784,  1802,  1804,  1806,  1807,  1809,
    1819,  1820,  1829,  1830,  1831,  1832,  1835,  1836,  1837,  1838,
    1839,  1840,  1841,  1842,  1845,  1847,  1848,  1849,  1850,  1852,
    1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,  1862,
    1863,  1864,  1865,  1866,  1867,  1868,  1869,  1870,  1871,  1873,
    1874,  1875,  1876,  1877,  1878,  1880,  1881,  1882,  1883,  1884,
    1885,  1886,  1887,  1888,  1890,  1891,  1892,  1893,  1894,  1895,
    1896,  1897,  1898,  1899,  1900,  1902,  1903,  1904,  1905,  1906,
    1907,  1908,  1909,  1910,  1913,  1914,  1915,  1916,  1917,  1918,
    1919,  1920,  1921,  1922,  1923,  1925,  1927,  1928,  1930,  1931,
    1933,  1934,  1936,  1937,  1940
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
  "CONTINUE", "RETURN", "YIELD", "IF", "ELSE", "WHILE", "FOR", "ABSTRACT",
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
  "NORMALINTERFACEDECLARATION", "OPENCURLY", "CLOSECURLY", "INTERFACEBODY",
  "INTERFACEMEMBERDECLARATIONS", "INTERFACEMEMBERDECLARATION",
  "INTERFACEDECLARATION", "TYPEPARAMETERS", "TYPEPARAMETERLIST",
  "TYPEPARAMETER", "TYPEBOUND", "ADDITIONALBOUND", "CLASSEXTENDS",
  "CLASSIMPLEMENTS", "INTERFACETYPELIST", "CLASSPERMITS", "TYPENAMES",
  "CLASSBODY", "CLASSBODYDECLARATIONS", "CLASSBODYDECLARATION",
  "CLASSMEMBERDECLARATION", "FIELDDECLARATION", "VARIABLEDECLARATORLIST",
  "VARIABLEDECLARATOR", "VARIABLEDECLARATORID", "VARIABLEINITIALIZER",
  "EXPRESSION", "ASSIGNMENTEXPRESSION", "ASSIGNMENT", "LEFTHANDSIDE",
  "ASSIGNMENTOPERATOR", "FIELDACCESS", "PRIMARY", "PRIMARYNONEWARRAY",
  "LITERAL", "CLASSLITERAL", "SQUARESTAR",
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

#define YYPACT_NINF (-830)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-525)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1890,  -830,   -83,  -830,  -830,  -830,  -830,  -830,  -830,  -830,
     152,   -66,  -830,   207,  2020,  -830,  1898,  -830,  -830,  -830,
    -830,   907,  1629,  2037,   256,   140,   242,   201,   256,  -830,
    -830,  -830,  -830,   171,  -830,  -830,  -830,  -830,  -830,   214,
     227,  -830,  -830,  -830,  -830,  -830,  -830,  -830,   268,   273,
    -830,  -830,  -830,  -830,  -830,  -830,  -830,   276,  -830,   281,
     299,   299,   362,  3059,   365,    95,    32,   491,  -830,   230,
     386,  -830,     5,   784,  -830,   365,    95,    32,   491,   256,
     256,   256,   256,   256,   256,   265,   406,  -830,  -830,  -830,
    -830,  -830,   477,  -830,  -830,   501,  -830,  -830,  -830,  -830,
    -830,  -830,  -830,  -830,  -830,  -830,   498,   491,   393,   509,
     446,  -830,  -830,  -830,  -830,  -830,  -830,  -830,  -830,  3342,
    -830,  -830,  1204,  3059,  -830,  -830,  -830,  -830,   422,  -830,
    -830,  -830,  -830,    10,   525,  4122,  3683,  5778,  1598,   748,
      95,    32,   491,  -830,    32,   491,  -830,   491,  -830,  -830,
    -830,    49,  -830,   576,  -830,  -830,   127,   393,  -830,  -830,
     784,  -830,  1277,  -830,  2605,  3878,  1114,  -830,    95,    32,
     491,  -830,    32,   491,  -830,   491,  -830,   365,    95,    32,
     491,  -830,  -830,   365,    95,    32,   491,   365,    95,    32,
     491,  -830,  -830,   365,    95,    32,   491,   365,    95,    32,
     491,  -830,  -830,   365,    95,    32,   491,   451,  -830,   281,
    -830,   299,   471,  3193,  -830,   440,   514,   474,   231,  -830,
     588,   514,    27,  -830,  5699,  5759,  5759,  -830,  -830,  -830,
    -830,  -830,  -830,  -830,   291,  1563,  -830,   496,  1783,  5699,
    5699,  -830,    15,    25,  3661,  5699,   620,   642,   650,   621,
    -830,    54,   596,   663,   504,  -830,  -830,  -830,   676,   929,
     305,   669,  -830,  -830,   441,  -830,   452,  -830,  -830,  1106,
    -830,  -830,   409,   473,   533,  -830,  3342,  -830,  -830,  -830,
     697,   599,  -830,  -830,  -830,  -830,   726,  -830,  -830,  -830,
    -830,  -830,  -830,  -830,  -830,  -830,  -830,  -830,  -830,  -830,
    1011,  1971,  2067,   393,   393,   709,  -830,  -830,  -830,  -830,
    -830,   299,  2229,   491,  -830,   624,   446,   422,    10,   446,
     422,  -830,  -830,  -830,  -830,   422,  -830,  -830,  -830,  -830,
    -830,  -830,  -830,   599,  -830,  -830,  -830,  -830,  -830,  -830,
    -830,  -830,  -830,   422,    32,   491,  -830,   491,  -830,  -830,
     491,  -830,  -830,  -830,   728,  -830,   422,  -830,  -830,   446,
    -830,    32,   491,  -830,   491,  -830,  -830,   491,  -830,  -830,
      95,    32,   491,  -830,    32,   491,  -830,   491,  -830,  -830,
    -830,    95,    32,   491,  -830,    32,   491,  -830,   491,  -830,
      95,    32,   491,  -830,    32,   491,  -830,   491,  -830,  -830,
    -830,    95,    32,   491,  -830,    32,   491,  -830,   491,  -830,
      95,    32,   491,  -830,    32,   491,  -830,   491,  -830,  -830,
    -830,    95,    32,   491,  -830,    32,   491,  -830,   491,  -830,
     700,   702,  -830,  -830,  -830,   422,  4367,  4244,  3756,   748,
     646,   -40,   760,  -830,   753,   756,   599,  -830,  3735,  -830,
     759,  -830,    56,    27,  5759,  5759,  5759,  5759,   706,    54,
     596,   758,  -830,  -830,  -830,  -830,  -830,    57,   734,   744,
     745,   742,   696,   215,   537,   573,   677,  -830,  -830,  -830,
    -830,   409,  -830,  -830,  -830,   186,   307,  -830,  -830,  -830,
    -830,    61,    68,   599,  -830,     3,   766,   778,   778,   782,
     680,   785,    79,  -830,   791,  -830,   793,  -830,   794,   795,
    5699,  5699,  1578,  3795,  3431,   111,  -830,    76,  -830,    78,
      77,  3857,  5699,   153,  -830,  -830,  -830,  -830,  -830,  -830,
    5699,    82,   236,  5699,  -830,  -830,  -830,  -830,  -830,   792,
     808,  -830,   514,   514,   934,  -830,   809,  -830,   342,   802,
     888,   443,  -830,   397,  3342,  3342,   267,  -830,  -830,   405,
      -1,   813,   260,  -830,  -830,   459,  -830,   491,  -830,   704,
    -830,  -830,   707,  -830,   491,  -830,  -830,  -830,  -830,  -830,
    -830,   710,  -830,   491,  -830,  -830,  -830,    32,   491,  -830,
     491,  -830,  -830,   491,  -830,  -830,  -830,  -830,    32,   491,
    -830,   491,  -830,  -830,   491,  -830,  -830,    32,   491,  -830,
     491,  -830,  -830,   491,  -830,  -830,  -830,  -830,    32,   491,
    -830,   491,  -830,  -830,   491,  -830,  -830,    32,   491,  -830,
     491,  -830,  -830,   491,  -830,  -830,  -830,  -830,    32,   491,
    -830,   491,  -830,  -830,   491,  -830,  -830,   299,   783,  -830,
     422,   422,   422,   422,   792,    36,   355,  -830,   781,   807,
    -830,   811,  -830,  3601,  -830,  -830,  -830,  -830,   814,  -830,
    -830,  -830,  -830,  -830,  -830,  5699,  5759,  5759,  5759,  5759,
    5759,  5759,  5759,  3917,  3979,   299,  5759,  5759,  5759,  5759,
    5759,  5759,  5759,  5759,  -830,   705,   812,   711,   808,   698,
    -830,   549,  -830,  -830,  4039,    19,   778,  -830,    19,   778,
    4101,  -830,   815,  -830,  -830,  5699,  -830,  -830,  -830,  -830,
     819,   820,  4161,  1563,   805,  -830,   829,   839,   832,  -830,
     411,  -830,   102,   835,  -830,   735,  -830,  -830,  -830,  -830,
      75,  -830,  -830,   381,   841,   843,  -830,   741,  -830,  -830,
     743,   848,  -830,   746,   854,  -830,  -830,  -830,   863,   482,
     299,  4223,  4283,   245,   193,   262,  -830,  -830,  3342,   858,
     868,    89,   774,   312,  -830,   942,  1797,  -830,  -830,  -830,
    -830,  -830,  -830,  -830,  -830,   491,  -830,  -830,  -830,  -830,
    -830,   491,  -830,  -830,  -830,   491,  -830,  -830,  -830,  -830,
    -830,   491,  -830,  -830,  -830,   491,  -830,  -830,  -830,  -830,
    -830,   491,  -830,  -830,  -830,  -830,   299,  -830,  -830,  -830,
    -830,   756,   792,   825,  1046,  -830,  -830,  -830,  -830,   886,
     891,  -830,   864,   734,   744,   745,   742,   696,   215,   215,
    5759,   537,  5759,   537,  -830,   573,   573,   573,   677,   677,
    -830,  -830,  -830,  -830,  4345,   883,   299,   299,  -830,     3,
    -830,   890,  -830,   756,  -830,  -830,   756,   491,   490,  4405,
     892,  3516,  3431,  5851,   904,  5699,  4479,  1442,  -830,   177,
     217,  4539,   900,  -830,  -830,  5699,  -830,  -830,  4601,   903,
    -830,  4661,   905,  -830,  1386,  -830,  -830,   913,   493,   914,
     502,   383,   -19,   909,    48,   944,   124,  -830,  4723,  4783,
     844,  -830,  -830,  -830,   529,  -830,  -830,  -830,  -830,  -830,
    -830,  -830,  -830,   756,  -830,   792,   531,  -830,  3735,  5759,
     537,   537,  -830,   538,  4845,  -830,  -830,  -830,  -830,  -830,
     491,   491,   540,  -830,   946,   958,   959,   976,  -830,   849,
    -830,   877,  -830,  -830,  -830,  -830,  -830,  -830,  3431,   961,
     839,  5882,   964,  5913,   967,  -830,  -830,   865,   975,   874,
    -830,   543,  4905,  -830,  -830,   547,  4967,  -830,   554,  5027,
    -830,   556,  -830,   986,  -830,   992,  5089,   988,  5149,   989,
    5211,   994,  1005,   561,  1008,   574,  -830,  -830,   756,   792,
    -830,  -830,  -830,  -830,   581,  -830,  -830,   491,  5699,  5699,
    2514,  3516,  3431,  -830,  3431,  3431,  1001,  3431,  3431,  1009,
    5944,  -830,  5271,  1015,  -830,  -830,   598,  -830,  -830,   615,
    -830,  -830,   626,  -830,  -830,  -830,  1026,   627,  5333,  1027,
     652,  5393,  1031,   653,  5455,  -830,  1033,  -830,  1035,   756,
    -830,  -830,  1037,  1040,  5515,  1022,  1051,  -830,  -830,  -830,
    -830,  3431,  -830,  -830,  3431,  3431,  1045,  -830,   655,  5577,
    -830,  -830,  -830,  -830,  1056,  1058,   660,  -830,  1059,  1060,
     667,  -830,  1069,  1074,   668,  -830,  -830,  3516,  3516,  5975,
    1076,  5699,  5637,  -830,  -830,  -830,  3431,  -830,  -830,   675,
    -830,  -830,  1079,  -830,  -830,  1082,  -830,  -830,  1085,  1017,
    -830,  3516,  1083,  6006,  1084,  6037,  1090,  -830,  -830,  -830,
    -830,  -830,  3516,  -830,  3516,  3516,  1086,  3516,  3516,  1087,
    6068,  -830,  -830,  -830,  3516,  -830,  -830,  3516,  3516,  1092,
    -830,  -830,  -830,  3516,  -830
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    29,     0,   549,   550,   551,   555,   556,   564,   565,
       0,     0,     2,     0,     0,    26,     0,    28,    36,   176,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       3,    27,    30,     0,   552,   553,   554,   557,   558,     0,
       0,   561,   562,   563,   559,   560,   566,   567,     0,     0,
     570,   571,   572,   573,   574,   568,   569,     0,   165,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
       0,    32,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   181,     0,   178,    20,   186,
      19,   604,   187,   188,   191,   190,     7,    10,    11,    12,
      13,    14,    15,    16,   204,   166,     0,   555,     0,    20,
       0,     4,     6,     8,     9,     5,    17,    18,   203,     0,
     193,   205,     0,     0,   195,   197,   201,   202,     0,   198,
     199,   424,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,    52,     0,    54,    55,
      34,     0,    24,     0,    25,   175,     0,     0,   174,   167,
       0,   169,     0,   171,     0,     0,     0,   108,     0,     0,
       0,   112,     0,     0,   114,     0,   115,     0,     0,     0,
       0,    38,   132,     0,     0,     0,     0,     0,     0,     0,
       0,    39,   148,     0,     0,     0,     0,     0,     0,     0,
       0,    40,   164,     0,     0,     0,     0,     0,   180,     0,
     177,     0,     0,     0,   425,     0,   394,   214,     0,   210,
     213,   393,     7,   454,     0,     0,     0,   247,   248,   249,
     250,   251,   252,   253,     0,   556,   239,     0,     0,     0,
       0,   438,     0,     0,     0,     0,     0,     0,     0,   223,
     437,     6,    18,     0,   376,   433,   427,   456,     0,   243,
     375,   235,   237,   238,   242,   263,   245,   246,   236,   244,
     457,   458,     0,   459,   460,   445,     0,   428,   430,   431,
       0,     0,   432,   439,   446,   447,     0,   448,   449,   450,
     451,   452,   453,   440,   441,   442,   443,   444,   487,   488,
       0,     0,     0,     0,     0,     0,   194,   196,   423,   383,
     422,     0,     0,     0,   513,     0,     0,     0,     0,     0,
       0,   575,   576,   584,   585,     0,   579,   580,   581,   582,
     583,   577,   578,     0,   590,   591,   592,   593,   594,   588,
     586,   587,   589,     0,     0,     0,    44,     0,    46,    47,
       0,    50,    51,    53,     0,    33,     0,   168,   170,     0,
     104,     0,     0,   106,     0,   107,   110,     0,   111,   113,
       0,     0,     0,    63,     0,     0,    67,     0,    69,    70,
     124,     0,     0,     0,   128,     0,     0,   130,     0,   131,
       0,     0,     0,    78,     0,     0,    82,     0,    84,    85,
     140,     0,     0,     0,   144,     0,     0,   146,     0,   147,
       0,     0,     0,    93,     0,     0,    97,     0,    99,   100,
     156,     0,     0,     0,   160,     0,     0,   162,     0,   163,
     182,     0,   179,   189,   192,     0,     0,     0,     0,     0,
       0,     0,     0,   398,     0,   215,     0,   209,     0,   395,
       0,   256,     0,     0,     0,     0,     0,     0,   377,     0,
       0,     0,   218,   220,   242,   245,   219,   333,   335,   337,
     339,   341,   343,   345,   348,   354,   358,   361,   365,   366,
     369,   372,   378,   379,   353,   377,   376,   243,   244,   370,
     371,     0,     0,     0,   257,     0,    20,   318,   319,     0,
       0,     0,     0,   465,     0,   467,     0,   470,     0,     0,
       0,     0,     0,     0,     0,     0,   254,     0,   255,     0,
       0,     0,     0,     0,   226,   227,   228,   229,   230,   231,
       0,     0,     0,     0,   380,   381,   426,   429,   434,   214,
     436,   455,   400,   397,     0,   404,   401,   402,     0,   239,
     223,   222,   528,   375,     0,     0,     0,   512,   516,     0,
       0,     0,     0,   415,   418,     0,   384,     0,   515,     0,
     385,   386,     0,   387,     0,    42,    43,    45,    49,    35,
     172,     0,   102,     0,   103,   105,   109,     0,     0,    59,
       0,    61,    62,     0,    65,    66,    68,   120,     0,     0,
     122,     0,   123,   126,     0,   127,   129,     0,     0,    74,
       0,    76,    77,     0,    80,    81,    83,   136,     0,     0,
     138,     0,   139,   142,     0,   143,   145,     0,     0,    89,
       0,    91,    92,     0,    95,    96,    98,   152,     0,     0,
     154,     0,   155,   158,     0,   159,   161,     0,   183,   388,
       0,     0,     0,     0,   405,     0,     0,   413,     0,     0,
      21,     0,   211,     0,   212,   216,   217,   261,     0,   260,
     367,   368,   374,   373,   241,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   307,     0,   233,     0,   435,   600,
     598,     0,   596,   599,     0,   316,   314,   325,   317,   315,
       0,   275,     0,   471,   463,     0,   466,   468,   469,   472,
       0,     0,     0,     0,   508,   510,     0,   507,     0,   473,
       0,   240,     0,    24,   265,     0,   258,   259,   309,   305,
       0,   278,   276,     0,     0,    25,   264,     0,   221,   306,
       0,   232,   266,     0,     0,   399,   396,   520,     0,     0,
       0,     0,     0,     0,     0,     0,   527,   526,     0,     0,
       0,     0,     0,   214,   417,     0,     0,   517,   207,   514,
     208,   206,    41,   173,   101,     0,    57,    58,    60,    64,
     118,     0,   119,   121,   125,     0,    72,    73,    75,    79,
     134,     0,   135,   137,   141,     0,    87,    88,    90,    94,
     150,     0,   151,   153,   157,   184,     0,   389,   390,   391,
     392,   408,   406,     0,     0,    22,   323,   321,   328,     0,
     322,   262,     0,   336,   338,   340,   342,   344,   346,   347,
       0,   349,     0,   350,   382,   355,   356,   357,   359,   360,
     363,   362,   364,   302,     0,     0,     0,     0,   601,     0,
     595,     0,   312,   310,   326,   313,   311,   267,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   332,     0,
       0,     0,     0,   304,   301,     0,   279,   330,     0,     0,
     300,     0,     0,   331,     0,   521,   403,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   525,     0,     0,
       0,   419,   420,   518,     0,   416,    56,   117,    71,   133,
      86,   149,   185,   410,   414,   407,     0,   320,   324,     0,
     352,   351,   292,     0,     0,   602,   603,   597,   327,   268,
     269,   271,     0,   464,     0,     0,     0,   223,   474,   439,
     479,     0,   478,   480,   481,   484,   485,   486,     0,     0,
     509,     0,     0,     0,     0,   511,   308,     0,   234,     0,
     280,     0,     0,   277,   284,     0,     0,   288,     0,     0,
     522,     0,   533,     0,   529,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   421,   519,   409,   412,
     329,   334,   293,   294,     0,   270,   272,   273,     0,     0,
       0,     0,     0,   489,     0,     0,     0,     0,     0,     0,
       0,   303,     0,     0,   281,   282,     0,   285,   286,     0,
     289,   290,     0,   523,   534,   530,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   535,     0,   531,     0,   411,
     295,   274,     0,     0,     0,   508,     0,   482,   475,   490,
     491,     0,   505,   493,     0,     0,     0,   296,     0,     0,
     283,   287,   291,   541,     0,     0,     0,   537,     0,     0,
       0,   545,     0,     0,     0,   536,   532,     0,     0,     0,
       0,     0,     0,   492,   494,   495,     0,   297,   298,     0,
     542,   543,     0,   538,   539,     0,   546,   547,     0,     0,
     483,     0,     0,     0,     0,     0,     0,   496,   299,   544,
     540,   548,     0,   497,     0,     0,     0,     0,     0,     0,
       0,   476,   498,   499,     0,   506,   501,     0,     0,     0,
     500,   502,   503,     0,   504
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -830,  -830,   302,   873,  1909,  -830,  -830,  -475,    80,  1617,
    -830,  -491,  -830,   203,  -830,   716,  -830,   183,  -830,  -830,
     -28,   -59,  2360,  -830,   965,    26,  1292,  -830,   918,  -830,
    -830,   618,  2912,  -830,  2845,  -830,  2012,  -830,  1006,  -830,
    -830,  -213,   682,  -530,  -651,  1405,  -830,   -96,  -830,  -830,
    1801,   827,  -830,  -830,  -830,  -193,   130,  -462,   631,  2299,
     213,  -830,  -830,  -627,  -830,   645,  -364,  -830,  2015,   220,
    -830,   470,   475,   478,   472,   479,    84,  -652,     4,    72,
    -217,   399,   419,  -830,   600,   751,   887,  -830,   -10,   -49,
    -195,  -830,   398,   -81,  -290,  -423,   377,  -830,  -281,  -830,
    -830,   -52,  -293,  -271,  -830,  -830,  -511,  -225,  1758,  -829,
    -830,  -830,  -510,  -830,  -830,  -830,  -830,  -830,  -830,  -830,
    -830,  -830,  -830,  -581,  -830,  -830,  -830,  -830,  -830,  -830,
    -830,  -830,  -830,   147,  -769,  -508,  -830,  1025,  1039,  -300,
    -830,    51,    66,    97,  -830,   949,  -296,  -830,   306,  -830,
    -830,  -208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,   157,   111,   459,   113,   114,   115,   116,   460,
      90,   445,   253,   254,    14,    15,    16,   255,    18,    19,
      63,   120,    74,   160,   161,    20,   162,    86,    87,   208,
     648,    65,    66,    92,    67,    95,    68,   123,   124,   125,
     126,   218,   219,   220,   664,   742,   462,   463,   258,   530,
     259,   260,   261,   262,   263,   517,   464,   265,   499,   743,
     465,   267,   268,   666,   829,   706,   707,   830,   269,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   127,   128,
     313,   546,   547,   221,   442,   562,   563,   564,   309,   129,
     130,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   950,   951,   952,   953,   954,   296,   297,   298,
     955,   299,   956,   726,   959,   960,   132,   133,   134,   314,
     555,   300,   301,   302,   138,   139,   500,   701,   702,   703,
     858,    93
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,   724,   725,   433,   727,   537,   705,   708,   489,   490,
     493,   131,   828,   557,   159,   699,   556,   656,   568,   554,
     700,   443,   772,   257,    58,   561,   449,   216,   503,   452,
     774,   841,   843,    58,   657,   119,   566,   661,   505,   570,
      24,   153,   949,   987,   571,   450,    58,    73,    73,    73,
      73,    21,    73,   734,    73,   214,    73,    28,   519,   772,
     256,   746,   573,   163,   306,    21,    22,    21,   540,   675,
     752,   131,   450,   657,   668,   580,   310,   495,   862,   119,
      22,   865,    22,   658,   495,   354,   317,   320,   325,   121,
     343,   119,   714,   495,   668,   119,   668,    23,   495,    62,
     119,   357,   676,   565,   882,   312,   569,   356,   311,    58,
     989,    23,   910,    23,   135,   317,   320,   325,   495,   715,
     572,   759,   773,   567,   164,   774,    88,   495,   154,   136,
      96,    97,    98,    99,   100,   101,   102,   103,   504,   165,
      73,    73,    73,    59,    73,    73,   581,    73,   506,   121,
     163,   883,   451,   738,   649,    73,    73,    73,    73,   539,
     137,    61,    62,   821,   435,    73,    73,    73,    73,   495,
     166,   889,   154,   730,   135,    73,    73,    73,    73,   518,
     257,   669,   949,    17,   694,   731,   991,   732,   930,   136,
     931,   696,  1016,   495,  1019,   695,   697,    17,   884,    17,
     739,   736,   108,   737,   513,   749,   -23,    29,   -20,   495,
     844,   164,   539,    27,    71,   863,   257,   536,   866,   735,
     137,    25,   542,   543,   740,   711,   165,   747,    69,   732,
     515,   683,   684,   495,   733,   750,   753,   670,   671,   672,
     673,   911,   446,   150,   447,    72,   118,   892,   119,   264,
      88,  1066,   495,   552,   758,   903,   158,   166,   949,   949,
     452,   495,   768,    26,   436,   310,   519,   779,   310,   732,
      58,   776,    59,   310,   151,    26,   745,  1000,   495,   437,
     698,   777,   949,   537,   119,   312,    70,   431,   685,   119,
     312,   310,   119,   949,    79,   949,   949,   119,   949,   949,
     966,   734,   746,   752,   310,   949,   118,   901,   949,   949,
     438,   516,   732,   491,   949,   119,   745,    60,   498,   731,
    1112,   732,    61,    62,   905,   522,   207,   531,   119,   769,
     444,   923,   266,    73,    73,   492,    73,    80,   732,    73,
     968,   770,   864,   158,  1126,   864,  1129,   755,   756,   532,
      81,   523,   914,    73,    73,    73,   823,    73,    73,   751,
      73,  1139,   761,   725,   491,   110,   776,   965,   733,   817,
     818,   819,   820,    73,    73,    73,   822,    73,    73,    58,
      73,   935,   936,   310,   700,   751,   492,   650,   651,   652,
     653,    82,   885,    73,    73,    73,    83,    73,    73,    84,
      73,   926,   886,   986,    85,   879,   264,   119,    96,    97,
      98,    99,   100,   101,   102,   103,   257,   209,   257,   531,
     663,   250,    88,   210,   304,   110,    60,   880,   486,   486,
    1057,    61,    62,   879,   998,   308,    58,   316,   319,   815,
     333,   765,   264,    96,    97,    98,    99,   100,   101,   102,
     103,   725,  -462,   725,  -462,   880,   534,   535,   257,   257,
     440,   522,  -462,  -461,   304,  -461,   359,   902,   904,   906,
     446,   981,   778,  -461,   850,   851,   852,    96,    97,    98,
      99,   100,   101,   102,   103,    94,   119,   764,   211,   266,
    -376,  -376,   444,   776,   440,   766,   767,   537,   493,  1055,
     725,   885,   727,   895,   885,    58,  1109,  1110,  1049,   152,
     725,   940,   212,   885,   983,   551,   215,   441,   270,   441,
    -378,  -378,   522,   985,   213,   266,   119,   119,    88,  -524,
    1123,  -222,  -222,  -222,  -222,  -222,  -222,   250,   271,   312,
     776,  1131,   776,  1132,  1133,   315,  1135,  1136,   523,   885,
     997,   885,   999,  1140,   885,    73,  1141,  1142,   885,  1002,
     859,  1007,  1144,    88,  1024,   885,   860,   776,  1027,   217,
      73,    73,   885,    73,   430,  1030,    73,  1033,   250,   725,
    -379,  -379,  1046,   967,   969,   885,   686,   687,   688,   355,
      73,    73,   885,    73,   434,  1048,    73,    88,   310,   310,
     310,   310,  1050,   725,   827,   725,   689,   690,   922,   885,
      73,    73,   311,    73,   250,   448,    73,   560,   520,  1070,
     725,   494,   119,   119,   119,   119,   885,    96,    97,    98,
      99,   100,   101,   102,   103,   663,  1071,   885,   885,   513,
     510,   -23,   264,   -20,   264,   558,    76,  1072,  1074,    96,
      97,    98,    99,   100,   101,   102,   103,   486,   486,   486,
     486,   514,   511,   885,   885,   515,   885,   654,  -377,  -377,
     512,   885,   257,  1078,  1082,   270,  1097,   663,   885,   885,
     663,  1102,   140,   521,   264,   264,   885,   533,  1105,  1108,
     845,   846,   847,   168,   559,   271,  1118,   178,   184,   188,
     194,   198,   204,   524,   525,   526,   527,   528,   529,   907,
     538,   270,   691,   692,   693,   446,   559,   780,   446,   272,
     781,   446,   539,   783,   513,   266,   -23,   266,   -20,   544,
      31,   271,    32,  -223,  -223,  -223,  -223,  -223,  -223,   541,
     119,   579,   655,   -20,   -20,   647,   516,    88,   681,   682,
     515,    96,    97,    98,    99,   100,   101,   102,   103,   856,
     857,   848,   849,    73,    59,   838,   839,   266,   266,    88,
     927,   659,   660,    73,   661,   257,   257,   257,   667,   674,
     677,   257,   678,    73,   679,   680,  -275,    96,    97,    98,
      99,   100,   101,   102,   103,   370,   704,   155,   713,   105,
      59,   381,   710,   711,   716,   390,   717,   718,   719,   106,
     444,   401,   334,   335,   250,   410,   336,   337,   338,   446,
     760,   421,   762,   108,   775,   823,   816,   824,   853,   -20,
     825,   516,   854,   831,   855,   869,   339,   340,   341,   342,
     871,   872,   876,   119,   119,   875,   560,     2,     3,     4,
     877,   878,     5,     6,     7,   881,   250,   250,   882,   108,
     887,   771,   257,   888,   889,   257,   890,   257,   891,   892,
     273,    88,     8,   893,   894,     9,   272,   156,   908,   486,
     486,   486,   486,   486,   486,   486,   486,   486,   909,   486,
     486,   486,   486,   486,   486,   486,   486,   912,   264,   924,
     663,   105,   928,   934,   929,   943,   513,    88,   -23,   938,
     -20,   270,   272,   270,   257,   257,   257,   961,   257,   257,
     972,   257,   257,   976,   257,   979,   982,   984,   514,   988,
     119,   271,   763,   271,  -477,  -377,  -377,    96,    97,    98,
      99,   100,   101,   102,   103,    96,    97,    98,    99,   100,
     101,   102,   103,   270,   270,   757,  -224,  -224,  -224,  -224,
    -224,  -224,  1012,   913,   990,   257,  1008,   996,   257,   257,
      33,    34,    35,   271,   271,    36,    37,    38,  1009,  1010,
    1020,   266,  1014,   119,   119,  1017,   119,   119,  1021,   119,
     119,   257,   257,   257,   513,  1022,   -23,  1023,   -20,  1034,
     257,   264,   264,   264,   559,  1035,   274,   264,  1038,  1041,
      39,   -20,   559,   516,  1044,   257,  1011,   257,  1045,   257,
     515,  1047,  1061,  -377,  -377,   250,   257,   273,   257,   257,
    1064,   257,   257,   119,   257,  1069,   119,   119,   257,  1073,
    1077,   257,   257,   486,  1081,   486,  1085,   257,  1086,    96,
      97,    98,    99,   100,   101,   102,   103,    88,  1087,   119,
     119,  1088,  1091,   273,  1092,    88,  1096,   925,   119,  1100,
     250,  1101,  1103,  1104,    33,    34,    35,   655,   655,    36,
      37,    38,  1106,   119,   266,   266,   266,  1107,   264,  1113,
     266,   264,  1119,   264,   119,  1120,   119,   119,  1121,   119,
     119,   516,  1122,  1130,  1124,  1127,   119,  1134,  1137,   119,
     119,   497,   272,  1143,   272,   119,   559,    96,    97,    98,
      99,   100,   101,   102,   103,   358,   655,   432,   662,   307,
      59,   712,   486,  -225,  -225,  -225,  -225,  -225,  -225,   553,
     264,   264,   264,   709,   264,   264,   833,   264,   264,  1001,
     264,   836,   834,   915,   272,   272,   835,  1056,   896,   837,
     318,   305,   439,   274,     0,   937,     0,   270,     0,    88,
       0,   266,     0,     0,   266,     0,   266,    49,    50,    51,
       0,     0,    52,    53,    54,     0,     0,   271,     0,   108,
       0,   264,     0,     0,   264,   264,   655,     0,     0,   274,
       0,     0,    55,   323,   324,    56,     0,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,   264,   264,   264,
       0,     0,     0,   266,   266,   266,   264,   266,   266,     0,
     266,   266,     0,   266,     0,     0,     0,    88,     0,     0,
       0,   264,     0,   264,     0,   264,     0,     0,     0,     0,
       0,     0,   264,     0,   264,   264,     0,   264,   264,     0,
     264,     0,     0,   273,   264,   273,     0,   264,   264,     0,
     270,   270,   270,   264,   266,     0,   270,   266,   266,   303,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
     271,   271,   271,     0,     0,     0,   271,     0,     0,     0,
     266,   266,   266,     0,     0,   273,   273,     0,     0,   266,
       0,     0,   250,     0,     0,     0,    64,     0,     0,     0,
      75,     0,     0,     0,   266,     0,   266,   109,   266,     0,
       0,     0,     0,     0,     0,   266,     0,   266,   266,     0,
     266,   266,     0,   266,     0,     0,     0,   266,     0,     0,
     266,   266,   303,     0,     0,   122,   266,   270,     0,     0,
     270,     0,   270,     0,     0,     0,     0,     0,   272,     0,
       0,   177,   183,   187,   193,   197,   203,   271,     0,     0,
     271,     0,   271,     0,     0,     0,     0,     0,     0,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,   274,
      88,   274,     0,     0,     0,     0,     0,   980,     0,   270,
     270,   270,     0,   270,   270,   122,   270,   270,     0,   270,
       0,     0,     0,     0,     0,     0,     0,   122,     0,   271,
     271,   271,     0,   271,   271,     0,   271,   271,     0,   271,
       0,   274,   274,     0,     0,   453,    97,    98,    99,   100,
     101,   102,   103,     0,     0,     0,   559,     0,     0,     0,
     270,     0,   224,   270,   270,     0,     0,     0,     0,     0,
       0,   272,   272,   272,     0,     0,     0,   272,     0,     0,
     271,     0,     0,   271,   271,     0,   270,   270,   270,   225,
     226,     0,     0,     0,     0,   270,   227,   228,   229,   230,
     231,   232,   233,     0,   234,     0,   271,   271,   271,    88,
     270,     0,   270,     0,   270,   271,   236,   237,   238,   273,
       0,   270,     0,   270,   270,     0,   270,   270,     0,   270,
     271,     0,   271,   270,   271,     0,   270,   270,     0,     0,
       0,   271,   270,   271,   271,     0,   271,   271,     0,   271,
       0,     0,     0,   271,     0,     0,   271,   271,   272,     0,
       0,   272,   271,   272,     0,   458,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,   222,    97,    98,    99,   100,   101,   102,   103,     0,
       0,   722,     0,     0,     0,     0,     0,     0,   224,     0,
       0,    96,    97,    98,    99,   100,   101,   102,   103,     0,
     272,   272,   272,     0,   272,   272,     0,   272,   272,     0,
     272,     0,   273,   273,   273,   225,   226,     0,   273,   461,
       0,     0,   227,   228,   229,   230,   231,   232,   233,     0,
     234,     0,   241,     0,   501,   502,     0,     0,   723,   508,
     509,     0,   236,   237,   238,   274,     0,   241,     0,     0,
       0,   272,   326,   327,   272,   272,   328,   329,   330,   331,
     332,     0,     0,     0,     0,     0,     0,    89,    91,     0,
     117,     0,     0,     0,     0,     0,    88,   272,   272,   272,
     117,     0,    40,    41,    42,     0,   272,    43,    44,    45,
       0,   458,     0,     0,     0,     0,     0,     0,     0,   273,
       0,   272,   273,   272,   273,   272,     0,    46,     0,     0,
      47,    88,   272,     0,   272,   272,     0,   272,   272,     0,
     272,     0,    48,     0,   272,     0,   252,   272,   272,   117,
     117,     0,     0,   272,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   117,   117,   117,   117,     0,   274,   274,
     274,   273,   273,   273,   274,   273,   273,     0,   273,   273,
       0,   273,     0,   117,     0,     0,     0,   117,     0,   117,
       0,   117,   117,   117,     0,     0,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,   495,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,   273,     0,     0,   273,   273,     0,     0,     0,
       0,     0,     0,     0,   117,     0,     0,     0,    91,     0,
     117,     0,   117,     0,   117,     0,     0,     0,   273,   273,
     273,     0,     0,     0,     0,   274,     0,   273,   274,     0,
     274,     0,   117,   665,     0,   117,     0,     0,     0,     0,
       0,     0,   273,     0,   273,     0,   273,   559,     0,     0,
       0,     0,     0,   273,     0,   273,   273,     0,   273,   273,
       0,   273,     0,     0,     0,   273,     0,     0,   273,   273,
       0,     0,     0,   252,   273,     0,     0,   274,   274,   274,
       0,   274,   274,     1,   274,   274,   496,   274,     0,     0,
       0,     1,     0,     0,     0,   720,   721,     0,   728,     0,
      88,     0,     0,     0,     0,     0,     0,   744,   545,   252,
       0,     0,   117,     0,     0,   748,     0,     0,   754,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   274,     0,
       0,   274,   274,     2,     3,     4,     0,     0,     5,     6,
       7,     2,     3,     4,     0,     0,     5,     6,     7,     0,
       0,     0,   112,     0,   274,   274,   274,     0,     8,     0,
       0,     9,   112,   274,     0,     0,     8,    10,     0,     9,
       0,     0,     0,    11,     0,    10,     0,     0,   274,     0,
     274,    11,   274,     0,     0,     0,     0,     0,     0,   274,
       0,   274,   274,     0,   274,   274,    12,   274,     0,     0,
       0,   274,     0,     0,   274,   274,   487,   487,   251,     0,
     274,   112,   112,     1,    40,    41,    42,     0,     0,    43,
      44,    45,     0,     0,   112,   112,   112,   112,   112,     0,
       0,     0,     0,   117,   117,   117,   117,   117,     0,    46,
       0,     0,    47,     0,     0,   112,     0,     0,   665,   112,
       0,   112,     0,   112,   112,   112,   143,   146,   148,   149,
     832,     0,     0,     2,     3,     4,     0,     0,     5,     6,
       7,   181,     0,   191,     0,   201,     0,     0,     0,     0,
      49,    50,    51,     0,     0,    52,    53,    54,     8,   861,
       0,     9,   117,     0,     0,     0,     0,    10,     0,     0,
     870,     0,   112,    11,   112,    55,   112,   874,    56,   252,
      49,    50,    51,     0,     0,    52,    53,    54,     0,     0,
      57,     0,     0,     0,   112,     0,    30,   112,     0,     0,
       0,     0,   346,   348,   349,    55,   351,   352,    56,   353,
       0,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   252,   252,     0,     0,     0,   117,     0,     0,     0,
       0,     0,     0,     0,     0,   251,     0,     0,     0,   373,
     376,   378,   379,     0,     0,     0,     0,     0,     0,   393,
     396,   398,   399,     0,     0,     0,     0,     0,     0,   413,
     416,   418,   419,     0,     0,     0,     0,     0,     0,     0,
       0,   251,     0,     0,   112,     0,     0,     0,     0,     0,
       0,     0,   222,    97,    98,    99,   100,   101,   102,   103,
     488,   488,   223,    58,   105,   495,     0,     0,     0,   224,
       0,     0,     0,     0,     0,   487,   487,   487,   487,     0,
       0,     0,     0,     0,    91,     0,     0,     0,     0,     0,
       0,     0,   729,     0,     0,     0,   225,   226,     0,     0,
     962,   964,     0,   227,   228,   229,   230,   231,   232,   233,
     973,   548,     2,     3,     4,     0,     0,     5,     6,   235,
       0,     0,   117,   549,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,     0,   247,   248,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   665,     0,     0,     0,     0,     0,     0,
     117,     0,     0,     0,     0,   112,   112,   112,   112,   112,
       0,     0,   550,     0,     0,     0,   575,   576,     0,   577,
       0,     0,   578,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   545,     0,     0,
       0,     0,   589,   591,   592,   252,   594,   595,     0,   596,
       0,     0,   117,   117,     0,     0,     0,     0,     0,     0,
       0,     0,   609,   611,   612,     0,   614,   615,     0,   616,
       0,     0,     0,  1052,  1053,     0,     0,     0,     0,     0,
       0,   251,   629,   631,   632,     0,   634,   635,     0,   636,
       0,     0,     0,    91,     0,   167,   171,   174,   176,     0,
     182,   117,   192,     0,   202,     0,     0,     0,     0,     0,
       0,     0,     0,   112,     0,     0,     0,     0,     0,  1090,
       0,     0,     0,   251,   251,     0,     0,     0,   112,   488,
     488,   488,   488,   117,   117,     0,   117,   487,   487,   487,
     487,   487,   487,   487,   487,   487,     0,   487,   487,   487,
     487,   487,   487,   487,   487,     0,  1114,  1116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,     0,     0,     0,     0,     0,   222,    97,    98,
      99,   100,   101,   102,   103,     0,     0,  1054,   360,   363,
     365,     0,   366,   368,   224,   369,     0,     0,     0,     0,
       0,     0,     0,   380,   384,   387,   389,     0,     0,     0,
       0,     0,     0,   400,   404,   407,   409,     0,     0,     0,
       0,   225,   226,   420,   424,   427,   429,     0,   227,   228,
     229,   230,   231,   232,   233,     0,   234,     0,     0,     0,
       0,     0,     0,     0,   723,     0,   782,     0,   236,   237,
     238,     0,     0,   241,     0,     0,     0,     0,     0,   786,
     787,     0,   788,     0,     0,   789,     0,     0,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   796,
     797,    59,   798,     0,     0,   799,     0,   252,     0,   948,
     957,     0,   112,     0,     0,     0,     0,   458,     0,   806,
     807,   487,   808,   487,     0,   809,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      35,     0,     0,    36,    37,    38,     0,   251,     0,     0,
     108,     0,     0,     0,   112,   112,     0,     0,     0,     0,
       0,   488,   488,   488,   488,   488,   488,   488,   488,   488,
       0,   488,   488,   488,   488,   488,   488,   488,   488,     0,
       0,     0,     0,     0,     0,     0,  1013,     0,     0,     0,
       0,   582,   584,     0,   585,     0,     0,   586,    88,     0,
     487,     0,     0,   112,     0,     0,     0,     0,     0,     0,
       0,   597,   600,   602,     0,   603,   605,     0,   606,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   617,   620,   622,     0,   623,   625,     0,   626,   729,
    1058,     0,  1059,  1060,     0,  1062,  1063,     0,     0,     0,
       0,   637,   640,   642,     0,   643,   645,     0,   646,     0,
       0,     0,     0,     0,     0,     0,     0,   916,     0,     0,
       0,     0,     0,   112,     0,     0,     0,   918,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   920,     0,  1093,
       0,     0,  1094,  1095,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   948,   957,     0,     0,     0,
       0,     0,     0,     0,  1117,   488,     0,   488,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1013,
       0,     0,     0,    78,     0,     0,     0,     0,     0,   939,
    1058,     0,  1059,  1060,     0,  1062,  1063,     0,     0,     0,
       0,     0,  1093,     0,     0,  1094,  1095,     0,     0,     0,
       0,  1117,     0,     0,     0,     0,     0,     0,     0,   142,
     145,   147,     0,     0,     0,     0,     0,     0,     0,   251,
     170,   173,   175,     0,   180,   186,   190,   196,   200,   206,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      77,     0,     0,   784,   488,     0,     0,     0,     0,     0,
       0,     0,  1005,  1006,     0,     0,     0,     0,   790,   792,
       0,   793,     0,     0,   794,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   141,   144,   800,   802,
       0,   803,     0,     0,   804,   345,   347,   169,   172,   350,
       0,   179,   185,   189,   195,   199,   205,     0,   810,   812,
       0,   813,     0,     0,   814,     0,     0,     0,     0,   868,
       0,     0,     0,   362,   364,     0,     0,   367,     0,  1051,
       0,     0,   372,   375,   377,     0,     0,     0,   383,   386,
     388,     0,   392,   395,   397,     0,     0,     0,   403,   406,
     408,     0,   412,   415,   417,     0,     0,     0,   423,   426,
     428,     0,   344,     0,     0,     0,     0,     0,     0,     0,
     898,   900,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,   104,    58,   105,    59,     0,     0,     0,     0,
     361,     0,     0,     0,   106,     0,     0,     0,     0,   371,
     374,     0,     0,     0,     0,   382,   385,     0,     0,   391,
     394,     0,     0,     0,     0,   402,   405,     0,     0,   411,
     414,     0,     0,     0,     0,   422,   425,     0,     0,     0,
       0,     0,     2,     3,     4,     0,     0,     5,   107,     7,
       0,     0,     0,     0,   108,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     0,
       9,   917,     0,   933,     0,     0,     0,     0,     0,     0,
       0,   919,    11,     0,     0,     0,     0,     0,   942,     0,
       0,   921,     0,     0,     0,     0,     0,     0,     0,     0,
     971,     0,   109,     0,     0,     0,     0,   975,     0,   574,
     978,     0,     0,     0,     0,     0,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,   583,   993,   995,    59,
       0,     0,     0,     0,     0,   588,   590,     0,     0,   593,
       0,     0,     0,     0,     0,     0,   599,   601,     0,     0,
     604,     0,     0,  1004,     0,   608,   610,     0,     0,   613,
       0,     0,     0,     0,     0,     0,   619,   621,     0,     0,
     624,     0,     0,     0,     0,   628,   630,     3,     4,   633,
       0,     5,     6,     7,     0,     0,   639,   641,   108,     0,
     644,  1026,     0,     0,     0,  1029,     0,     0,  1032,     0,
       0,     8,   587,     0,     9,  1037,     0,  1040,     0,  1043,
       0,     0,     0,   598,     0,     0,     0,     0,     0,     0,
       0,     0,   607,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   618,     0,     0,    88,     0,     0,     0,
       0,  1068,   627,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   638,     0,     0,     0,  1076,     0,     0,
    1080,     0,     0,  1084,     0,   222,    97,    98,    99,   100,
     101,   102,   103,     0,     0,   223,    58,   105,     0,     0,
       0,     0,   224,     0,     0,     0,     0,     0,  1099,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   225,
     226,     0,     0,     0,     0,     0,   227,   228,   229,   230,
     231,   232,   233,     0,   234,     2,     3,     4,     0,     0,
       5,     6,   235,     0,     0,     0,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,     0,   247,   248,
       8,     0,   785,     9,   453,    97,    98,    99,   100,   101,
     102,   103,     0,   791,   223,    58,     0,     0,     0,     0,
       0,   224,   795,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   801,     0,   249,     0,     0,     0,     0,
       0,     0,   805,     0,     0,     0,     0,     0,   225,   226,
       0,     0,     0,   811,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   236,   237,   238,   239,   240,
       0,   242,   243,   244,   245,   246,     0,   247,   248,   453,
      97,    98,    99,   100,   101,   102,   103,     0,     0,   223,
      58,     0,     0,     0,     0,     0,   224,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   249,     0,     0,     0,     0,     0,
       0,     0,     0,   225,   226,     0,     0,     0,     0,     0,
     227,   228,   229,   230,   231,   232,   233,     0,   234,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,   237,   238,   239,   240,     0,   242,   243,   244,   245,
     944,     0,   945,   946,   453,    97,    98,    99,   100,   101,
     102,   103,   826,     0,     0,    58,   105,     0,     0,     0,
       0,   224,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   454,   455,     0,     0,     0,   947,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   453,    97,    98,    99,   100,   101,
     102,   103,     0,     0,   507,   236,   237,   238,     0,     0,
       0,   224,     0,     0,     0,     0,    96,    97,    98,    99,
     100,   101,   102,   103,   454,   455,     0,     0,     0,    59,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   458,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   236,   237,   238,   453,    97,
      98,    99,   100,   101,   102,   103,    40,    41,    42,    58,
       0,    43,    44,    45,     0,   224,     0,     0,   108,    96,
      97,    98,    99,   100,   101,   102,   103,     0,   454,   455,
       0,    46,    59,     0,    47,     0,   456,   457,     0,     0,
       0,     0,   225,   226,   458,     0,    48,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   453,    97,
      98,    99,   100,   101,   102,   103,    88,     0,     0,   236,
     237,   238,     0,     0,   667,   224,     0,     0,     0,     0,
      50,    51,     0,     0,    52,    53,    54,     0,   454,   455,
       0,   108,     0,     0,     0,     0,   456,   457,     0,     0,
       0,     0,   225,   226,    55,   323,   324,    56,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   458,     0,
     453,    97,    98,    99,   100,   101,   102,   103,     0,   236,
     237,   238,     0,     0,     0,     0,     0,   224,   741,    88,
       0,    96,    97,    98,    99,   100,   101,   102,   103,     0,
     454,   455,     0,     0,    59,     0,     0,     0,   456,   457,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   458,   234,
     453,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,   236,   237,   238,     0,     0,     0,   224,     0,     0,
       0,    40,    41,    42,   840,     0,    43,    44,    45,     0,
     454,   455,     0,   108,     0,     0,     0,     0,   456,   457,
       0,     0,     0,     0,   225,   226,    46,     0,     0,    47,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     458,     0,   453,    97,    98,    99,   100,   101,   102,   103,
       0,   236,   237,   238,     0,     0,     0,     0,     0,   224,
       0,    88,     0,     0,     0,     0,   842,     0,     0,     0,
       0,     0,   454,   455,     0,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
     485,   234,   453,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   236,   237,   238,     0,     0,   660,   224,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   454,   455,     0,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   485,     0,   453,    97,    98,    99,   100,   101,
     102,   103,     0,   236,   237,   238,     0,     0,     0,     0,
       0,   224,   867,     0,     0,    96,    97,    98,    99,   100,
     101,   102,   103,     0,   454,   455,     0,     0,    59,     0,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,   458,   234,   453,    97,    98,    99,   100,   101,
     102,   103,     0,     0,   873,   236,   237,   238,     0,     0,
       0,   224,     0,     0,     0,    33,    34,    35,     0,     0,
      36,    37,    38,     0,   454,   455,     0,   108,     0,     0,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   458,    39,   453,    97,    98,    99,
     100,   101,   102,   103,     0,   236,   237,   238,     0,     0,
       0,     0,     0,   224,   897,   109,     0,    96,    97,    98,
      99,   100,   101,   102,   103,     0,   454,   455,     0,     0,
      59,     0,     0,     0,   456,   457,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,   458,   234,   453,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   236,   237,   238,
       0,     0,     0,   224,   899,     0,     0,     0,    41,    42,
       0,     0,    43,    44,    45,     0,   454,   455,     0,   108,
       0,     0,     0,     0,   456,   457,     0,     0,     0,     0,
     225,   226,    46,     0,     0,    47,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   458,     0,   453,    97,
      98,    99,   100,   101,   102,   103,     0,   236,   237,   238,
       0,     0,     0,     0,     0,   224,   932,    88,     0,     0,
      96,    97,    98,    99,   100,   101,   102,   103,   454,   455,
       0,     0,     0,    59,     0,     0,   456,   457,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,   458,   234,   453,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   236,
     237,   238,     0,     0,     0,   224,   941,     0,     0,     0,
       0,    34,    35,     0,     0,    36,    37,    38,   454,   455,
       0,     0,   108,     0,     0,     0,   456,   457,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   458,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   236,
     237,   238,   453,    97,    98,    99,   100,   101,   102,   103,
      88,     0,   963,     0,     0,     0,     0,     0,     0,   224,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   454,   455,     0,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,   458,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   453,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   236,   237,   238,     0,     0,     0,   224,
     970,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   454,   455,     0,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   458,     0,   453,    97,    98,    99,   100,   101,
     102,   103,     0,   236,   237,   238,     0,     0,     0,     0,
       0,   224,   974,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   454,   455,     0,     0,     0,     0,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,   458,   234,   453,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,   236,   237,   238,     0,     0,
       0,   224,   977,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   454,   455,     0,     0,     0,     0,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   458,     0,   453,    97,    98,    99,
     100,   101,   102,   103,     0,   236,   237,   238,     0,     0,
       0,     0,     0,   224,   992,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   454,   455,     0,     0,
       0,     0,     0,     0,   456,   457,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,   458,   234,   453,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   236,   237,   238,
       0,     0,     0,   224,   994,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   454,   455,     0,     0,
       0,     0,     0,     0,   456,   457,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   458,     0,   453,    97,
      98,    99,   100,   101,   102,   103,     0,   236,   237,   238,
       0,     0,     0,     0,     0,   224,  1003,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   454,   455,
       0,     0,     0,     0,     0,     0,   456,   457,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,   458,   234,   453,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,   236,
     237,   238,     0,     0,     0,   224,  1025,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   454,   455,
       0,     0,     0,     0,     0,     0,   456,   457,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   458,     0,
     453,    97,    98,    99,   100,   101,   102,   103,     0,   236,
     237,   238,     0,     0,     0,     0,     0,   224,  1028,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     454,   455,     0,     0,     0,     0,     0,     0,   456,   457,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   458,   234,
     453,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,   236,   237,   238,     0,     0,     0,   224,  1031,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     454,   455,     0,     0,     0,     0,     0,     0,   456,   457,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     458,     0,   453,    97,    98,    99,   100,   101,   102,   103,
       0,   236,   237,   238,     0,     0,     0,     0,     0,   224,
    1036,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   454,   455,     0,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
     458,   234,   453,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   236,   237,   238,     0,     0,     0,   224,
    1039,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   454,   455,     0,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   458,     0,   453,    97,    98,    99,   100,   101,
     102,   103,     0,   236,   237,   238,     0,     0,     0,     0,
       0,   224,  1042,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   454,   455,     0,     0,     0,     0,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,   458,   234,   453,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,   236,   237,   238,     0,     0,
       0,   224,  1067,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   454,   455,     0,     0,     0,     0,
       0,     0,   456,   457,     0,     0,     0,     0,   225,   226,
       0,     0,     0,     0,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,   458,     0,   453,    97,    98,    99,
     100,   101,   102,   103,     0,   236,   237,   238,     0,     0,
       0,     0,     0,   224,  1075,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   454,   455,     0,     0,
       0,     0,     0,     0,   456,   457,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,   458,   234,   453,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   236,   237,   238,
       0,     0,     0,   224,  1079,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   454,   455,     0,     0,
       0,     0,     0,     0,   456,   457,     0,     0,     0,     0,
     225,   226,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   232,   233,     0,   234,   458,     0,   453,    97,
      98,    99,   100,   101,   102,   103,     0,   236,   237,   238,
       0,     0,     0,     0,     0,   224,  1083,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   454,   455,
       0,     0,     0,     0,     0,     0,   456,   457,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,   458,   234,   453,    97,
      98,    99,   100,   101,   102,   103,     0,     0,  1089,   236,
     237,   238,     0,     0,     0,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   454,   455,
       0,     0,     0,     0,     0,     0,   456,   457,     0,     0,
       0,     0,   225,   226,     0,     0,     0,     0,     0,   227,
     228,   229,   230,   231,   232,   233,     0,   234,   458,     0,
     453,    97,    98,    99,   100,   101,   102,   103,     0,   236,
     237,   238,     0,     0,     0,     0,     0,   224,  1098,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     454,   455,     0,     0,     0,     0,     0,     0,   456,   457,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,   458,   234,
     453,    97,    98,    99,   100,   101,   102,   103,     0,     0,
    1115,   236,   237,   238,     0,     0,     0,   224,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     454,   455,     0,     0,     0,     0,     0,     0,   456,   457,
       0,     0,     0,     0,   225,   226,     0,     0,     0,     0,
       0,   227,   228,   229,   230,   231,   232,   233,     0,   234,
     458,     0,   453,    97,    98,    99,   100,   101,   102,   103,
       0,   236,   237,   238,     0,     0,     0,     0,     0,   224,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   454,   455,     0,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
     458,   234,   453,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,   236,   237,   238,     0,     0,     0,   224,
       0,    96,    97,    98,    99,   100,   101,   102,   103,     0,
       0,     0,   454,   455,    59,     0,     0,     0,     0,     0,
     456,   457,     0,     0,     0,     0,   225,   226,     0,     0,
       0,     0,     0,   227,   228,   229,   230,   231,   232,   233,
       0,   234,   458,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   236,   237,   238,     0,     0,     0,     0,
       0,    49,    50,    51,     0,     0,    52,    53,    54,   321,
     322,     0,     0,   108,   453,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,    55,   323,   324,    56,
       0,   224,   958,     0,     0,     0,     0,     0,     0,     0,
       0,    57,   485,     0,     0,   453,    97,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,     0,   225,   226,
       0,    88,   224,  1015,     0,   227,   228,   229,   230,   231,
     232,   233,     0,   234,     0,     0,   453,    97,    98,    99,
     100,   101,   102,   103,     0,   236,   237,   238,     0,   225,
     226,     0,     0,   224,  1018,     0,   227,   228,   229,   230,
     231,   232,   233,     0,   234,     0,     0,   453,    97,    98,
      99,   100,   101,   102,   103,     0,   236,   237,   238,     0,
     225,   226,     0,     0,   224,  1065,     0,   227,   228,   229,
     230,   231,   232,   233,   458,   234,     0,     0,   453,    97,
      98,    99,   100,   101,   102,   103,     0,   236,   237,   238,
       0,   225,   226,     0,     0,   224,  1111,     0,   227,   228,
     229,   230,   231,   232,   233,   458,   234,     0,     0,   453,
      97,    98,    99,   100,   101,   102,   103,     0,   236,   237,
     238,     0,   225,   226,     0,     0,   224,  1125,     0,   227,
     228,   229,   230,   231,   232,   233,   458,   234,     0,     0,
     453,    97,    98,    99,   100,   101,   102,   103,     0,   236,
     237,   238,     0,   225,   226,     0,     0,   224,  1128,     0,
     227,   228,   229,   230,   231,   232,   233,   458,   234,     0,
       0,   453,    97,    98,    99,   100,   101,   102,   103,     0,
     236,   237,   238,     0,   225,   226,     0,     0,   224,  1138,
       0,   227,   228,   229,   230,   231,   232,   233,   458,   234,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   236,   237,   238,     0,   225,   226,     0,     0,     0,
       0,     0,   227,   228,   229,   230,   231,   232,   233,   458,
     234,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,   237,   238,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     458,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   458
};

static const yytype_int16 yycheck[] =
{
      28,   512,   512,   211,   512,   276,   497,   498,   225,   226,
     235,    63,   663,   313,    73,    12,   312,   440,   318,   312,
     495,   216,    23,   119,    14,   315,   221,   108,    13,   222,
     560,   683,   684,    14,    74,    63,   317,    18,    13,   320,
     123,    36,   871,    62,   325,    18,    14,    75,    76,    77,
      78,     0,    80,   515,    82,   107,    84,   123,   251,    23,
     119,   523,   343,    73,   123,    14,     0,    16,   281,    12,
     532,   123,    18,    74,    18,   356,   128,    16,   705,   107,
      14,   708,    16,   123,    16,    36,   135,   136,   137,    63,
     139,   119,    13,    16,    18,   123,    18,     0,    16,    67,
     128,   160,    45,   316,   123,   133,   319,   156,    98,    14,
      62,    14,    23,    16,    63,   164,   165,   166,    16,    40,
     333,   544,   123,   318,    73,   655,   123,    16,   123,    63,
       3,     4,     5,     6,     7,     8,     9,    10,   123,    73,
     168,   169,   170,    16,   172,   173,   359,   175,   123,   123,
     160,    76,   125,    76,   435,   183,   184,   185,   186,   123,
      63,    66,    67,   654,   213,   193,   194,   195,   196,    16,
      73,   123,   123,    62,   123,   203,   204,   205,   206,   125,
     276,   125,  1011,     0,   123,    74,    62,    76,   840,   123,
     842,   123,   961,    16,   963,   491,   492,    14,   123,    16,
     123,   125,    75,   125,    18,   123,    20,     0,    22,    16,
     685,   160,   123,    10,    13,   706,   312,   276,   709,   515,
     123,    69,   303,   304,   520,   123,   160,   523,    25,    76,
      44,    16,    17,    16,   123,   531,   532,   454,   455,   456,
     457,   771,    11,    13,    13,    44,    63,   123,   276,   119,
     123,  1020,    16,   312,   544,    62,    73,   160,  1087,  1088,
     453,    16,   555,   123,   213,   317,   459,   567,   320,    76,
      14,    11,    16,   325,    44,   123,   123,   928,    16,   213,
     493,    21,  1111,   554,   312,   313,    44,   207,    73,   317,
     318,   343,   320,  1122,   123,  1124,  1125,   325,  1127,  1128,
     123,   763,   764,   765,   356,  1134,   123,    62,  1137,  1138,
     213,   125,    76,    22,  1143,   343,   123,    61,   238,    74,
    1089,    76,    66,    67,    62,    18,    61,    22,   356,    62,
      18,   822,   119,   361,   362,    44,   364,   123,    76,   367,
     123,    74,   706,   160,  1113,   709,  1115,   542,   543,    44,
     123,    44,   775,   381,   382,   383,    44,   385,   386,   123,
     388,  1130,    20,   873,    22,    63,    11,   877,   123,   650,
     651,   652,   653,   401,   402,   403,    21,   405,   406,    14,
     408,   856,   857,   435,   859,   123,    44,   436,   437,   438,
     439,   123,    11,   421,   422,   423,   123,   425,   426,   123,
     428,   824,    21,    20,   123,    22,   276,   435,     3,     4,
       5,     6,     7,     8,     9,    10,   512,    11,   514,    22,
     448,   119,   123,    17,   122,   123,    61,    44,   225,   226,
    1011,    66,    67,    22,   925,    13,    14,   135,   136,   647,
     138,    44,   312,     3,     4,     5,     6,     7,     8,     9,
      10,   961,    11,   963,    13,    44,    47,    48,   554,   555,
      20,    18,    21,    11,   162,    13,   164,   763,   764,   765,
      11,   894,    13,    21,   691,   692,   693,     3,     4,     5,
       6,     7,     8,     9,    10,   123,   514,    44,    11,   276,
      47,    48,    18,    11,    20,   554,   555,   768,   723,  1010,
    1010,    11,  1010,    21,    11,    14,  1087,  1088,   999,   123,
    1020,    21,    11,    11,    21,   312,   123,   215,   119,   217,
      47,    48,    18,    21,    26,   312,   554,   555,   123,    20,
    1111,    27,    28,    29,    30,    31,    32,   235,   119,   567,
      11,  1122,    11,  1124,  1125,    20,  1127,  1128,    44,    11,
      21,    11,    21,  1134,    11,   583,  1137,  1138,    11,    21,
      11,    21,  1143,   123,    21,    11,    17,    11,    21,   123,
     598,   599,    11,   601,   123,    21,   604,    21,   276,  1089,
      47,    48,    21,   879,   880,    11,    49,    50,    51,    13,
     618,   619,    11,   621,   123,    21,   624,   123,   650,   651,
     652,   653,    21,  1113,   663,  1115,    33,    34,   816,    11,
     638,   639,    98,   641,   312,    27,   644,   315,    22,    21,
    1130,   125,   650,   651,   652,   653,    11,     3,     4,     5,
       6,     7,     8,     9,    10,   663,    21,    11,    11,    18,
      20,    20,   512,    22,   514,    21,    28,    21,    21,     3,
       4,     5,     6,     7,     8,     9,    10,   454,   455,   456,
     457,    40,    20,    11,    11,    44,    11,    21,    47,    48,
      20,    11,   768,    21,    21,   276,    21,   705,    11,    11,
     708,    21,    64,    20,   554,   555,    11,    18,    21,    21,
     686,   687,   688,    75,    70,   276,    21,    79,    80,    81,
      82,    83,    84,    27,    28,    29,    30,    31,    32,   768,
      13,   312,    35,    36,    37,    11,    70,    13,    11,   119,
      13,    11,   123,    13,    18,   512,    20,   514,    22,    20,
      14,   312,    16,    27,    28,    29,    30,    31,    32,    13,
     768,    13,   440,    43,   123,    43,   125,   123,    52,    53,
      44,     3,     4,     5,     6,     7,     8,     9,    10,    61,
      62,   689,   690,   791,    16,   681,   682,   554,   555,   123,
     829,    11,    19,   801,    18,   871,   872,   873,    19,    21,
      46,   877,    38,   811,    39,    43,    20,     3,     4,     5,
       6,     7,     8,     9,    10,   177,    18,    13,    13,    15,
      16,   183,    20,   123,    13,   187,    13,    13,    13,    25,
      18,   193,    64,    65,   512,   197,    68,    69,    70,    11,
      11,   203,    20,    75,    11,    44,    43,    20,   123,   123,
      19,   125,    20,    19,   123,    20,    88,    89,    90,    91,
      21,    21,    13,   871,   872,    40,   544,    63,    64,    65,
      11,    19,    68,    69,    70,    20,   554,   555,   123,    75,
      19,   559,   958,    20,   123,   961,   123,   963,    20,   123,
     119,   123,    88,    19,    11,    91,   276,    93,    20,   676,
     677,   678,   679,   680,   681,   682,   683,   684,    20,   686,
     687,   688,   689,   690,   691,   692,   693,   123,   768,    74,
     928,    15,    11,    20,    40,    13,    18,   123,    20,    19,
      22,   512,   312,   514,  1010,  1011,  1012,    13,  1014,  1015,
      20,  1017,  1018,    20,  1020,    20,    13,    13,    40,    20,
     958,   512,    44,   514,    85,    47,    48,     3,     4,     5,
       6,     7,     8,     9,    10,     3,     4,     5,     6,     7,
       8,     9,    10,   554,   555,    21,    27,    28,    29,    30,
      31,    32,    85,    21,    20,  1061,    20,   123,  1064,  1065,
      63,    64,    65,   554,   555,    68,    69,    70,    20,    20,
      13,   768,    21,  1011,  1012,    21,  1014,  1015,   123,  1017,
    1018,  1087,  1088,  1089,    18,    20,    20,   123,    22,    13,
    1096,   871,   872,   873,    70,    13,   119,   877,    20,    20,
     103,   123,    70,   125,    20,  1111,    40,  1113,    13,  1115,
      44,    13,    21,    47,    48,   723,  1122,   276,  1124,  1125,
      21,  1127,  1128,  1061,  1130,    20,  1064,  1065,  1134,    13,
      13,  1137,  1138,   840,    13,   842,    13,  1143,    13,     3,
       4,     5,     6,     7,     8,     9,    10,   123,    21,  1087,
    1088,    21,    40,   312,    13,   123,    21,    21,  1096,    13,
     768,    13,    13,    13,    63,    64,    65,   775,   776,    68,
      69,    70,    13,  1111,   871,   872,   873,    13,   958,    13,
     877,   961,    13,   963,  1122,    13,  1124,  1125,    13,  1127,
    1128,   125,    85,    13,    21,    21,  1134,    21,    21,  1137,
    1138,   238,   512,    21,   514,  1143,    70,     3,     4,     5,
       6,     7,     8,     9,    10,   160,   824,   209,   446,   123,
      16,   500,   929,    27,    28,    29,    30,    31,    32,   312,
    1010,  1011,  1012,   498,  1014,  1015,   676,  1017,  1018,   929,
    1020,   679,   677,   776,   554,   555,   678,  1010,   760,   680,
     135,   122,   213,   276,    -1,   859,    -1,   768,    -1,   123,
      -1,   958,    -1,    -1,   961,    -1,   963,    63,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    -1,   768,    -1,    75,
      -1,  1061,    -1,    -1,  1064,  1065,   894,    -1,    -1,   312,
      -1,    -1,    88,    89,    90,    91,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,  1087,  1088,  1089,
      -1,    -1,    -1,  1010,  1011,  1012,  1096,  1014,  1015,    -1,
    1017,  1018,    -1,  1020,    -1,    -1,    -1,   123,    -1,    -1,
      -1,  1111,    -1,  1113,    -1,  1115,    -1,    -1,    -1,    -1,
      -1,    -1,  1122,    -1,  1124,  1125,    -1,  1127,  1128,    -1,
    1130,    -1,    -1,   512,  1134,   514,    -1,  1137,  1138,    -1,
     871,   872,   873,  1143,  1061,    -1,   877,  1064,  1065,    75,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
     871,   872,   873,    -1,    -1,    -1,   877,    -1,    -1,    -1,
    1087,  1088,  1089,    -1,    -1,   554,   555,    -1,    -1,  1096,
      -1,    -1,  1010,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      28,    -1,    -1,    -1,  1111,    -1,  1113,   123,  1115,    -1,
      -1,    -1,    -1,    -1,    -1,  1122,    -1,  1124,  1125,    -1,
    1127,  1128,    -1,  1130,    -1,    -1,    -1,  1134,    -1,    -1,
    1137,  1138,    75,    -1,    -1,    63,  1143,   958,    -1,    -1,
     961,    -1,   963,    -1,    -1,    -1,    -1,    -1,   768,    -1,
      -1,    79,    80,    81,    82,    83,    84,   958,    -1,    -1,
     961,    -1,   963,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,   512,
     123,   514,    -1,    -1,    -1,    -1,    -1,    21,    -1,  1010,
    1011,  1012,    -1,  1014,  1015,   123,  1017,  1018,    -1,  1020,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,  1010,
    1011,  1012,    -1,  1014,  1015,    -1,  1017,  1018,    -1,  1020,
      -1,   554,   555,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    70,    -1,    -1,    -1,
    1061,    -1,    20,  1064,  1065,    -1,    -1,    -1,    -1,    -1,
      -1,   871,   872,   873,    -1,    -1,    -1,   877,    -1,    -1,
    1061,    -1,    -1,  1064,  1065,    -1,  1087,  1088,  1089,    47,
      48,    -1,    -1,    -1,    -1,  1096,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,  1087,  1088,  1089,   123,
    1111,    -1,  1113,    -1,  1115,  1096,    74,    75,    76,   768,
      -1,  1122,    -1,  1124,  1125,    -1,  1127,  1128,    -1,  1130,
    1111,    -1,  1113,  1134,  1115,    -1,  1137,  1138,    -1,    -1,
      -1,  1122,  1143,  1124,  1125,    -1,  1127,  1128,    -1,  1130,
      -1,    -1,    -1,  1134,    -1,    -1,  1137,  1138,   958,    -1,
      -1,   961,  1143,   963,    -1,   123,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
    1010,  1011,  1012,    -1,  1014,  1015,    -1,  1017,  1018,    -1,
    1020,    -1,   871,   872,   873,    47,    48,    -1,   877,   224,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,    79,    -1,   239,   240,    -1,    -1,    70,   244,
     245,    -1,    74,    75,    76,   768,    -1,    79,    -1,    -1,
      -1,  1061,    64,    65,  1064,  1065,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      63,    -1,    -1,    -1,    -1,    -1,   123,  1087,  1088,  1089,
      73,    -1,    63,    64,    65,    -1,  1096,    68,    69,    70,
      -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   958,
      -1,  1111,   961,  1113,   963,  1115,    -1,    88,    -1,    -1,
      91,   123,  1122,    -1,  1124,  1125,    -1,  1127,  1128,    -1,
    1130,    -1,   103,    -1,  1134,    -1,   119,  1137,  1138,   122,
     123,    -1,    -1,  1143,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   135,   136,   137,   138,   139,    -1,   871,   872,
     873,  1010,  1011,  1012,   877,  1014,  1015,    -1,  1017,  1018,
      -1,  1020,    -1,   156,    -1,    -1,    -1,   160,    -1,   162,
      -1,   164,   165,   166,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,  1061,    -1,    -1,  1064,  1065,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   207,    -1,    -1,    -1,   211,    -1,
     213,    -1,   215,    -1,   217,    -1,    -1,    -1,  1087,  1088,
    1089,    -1,    -1,    -1,    -1,   958,    -1,  1096,   961,    -1,
     963,    -1,   235,   448,    -1,   238,    -1,    -1,    -1,    -1,
      -1,    -1,  1111,    -1,  1113,    -1,  1115,    70,    -1,    -1,
      -1,    -1,    -1,  1122,    -1,  1124,  1125,    -1,  1127,  1128,
      -1,  1130,    -1,    -1,    -1,  1134,    -1,    -1,  1137,  1138,
      -1,    -1,    -1,   276,  1143,    -1,    -1,  1010,  1011,  1012,
      -1,  1014,  1015,    13,  1017,  1018,   123,  1020,    -1,    -1,
      -1,    13,    -1,    -1,    -1,   510,   511,    -1,   513,    -1,
     123,    -1,    -1,    -1,    -1,    -1,    -1,   522,   311,   312,
      -1,    -1,   315,    -1,    -1,   530,    -1,    -1,   533,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1061,    -1,
      -1,  1064,  1065,    63,    64,    65,    -1,    -1,    68,    69,
      70,    63,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    63,    -1,  1087,  1088,  1089,    -1,    88,    -1,
      -1,    91,    73,  1096,    -1,    -1,    88,    97,    -1,    91,
      -1,    -1,    -1,   103,    -1,    97,    -1,    -1,  1111,    -1,
    1113,   103,  1115,    -1,    -1,    -1,    -1,    -1,    -1,  1122,
      -1,  1124,  1125,    -1,  1127,  1128,   126,  1130,    -1,    -1,
      -1,  1134,    -1,    -1,  1137,  1138,   225,   226,   119,    -1,
    1143,   122,   123,    13,    63,    64,    65,    -1,    -1,    68,
      69,    70,    -1,    -1,   135,   136,   137,   138,   139,    -1,
      -1,    -1,    -1,   436,   437,   438,   439,   440,    -1,    88,
      -1,    -1,    91,    -1,    -1,   156,    -1,    -1,   663,   160,
      -1,   162,    -1,   164,   165,   166,    64,    65,    66,    67,
     675,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      70,    79,    -1,    81,    -1,    83,    -1,    -1,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    70,    88,   704,
      -1,    91,   495,    -1,    -1,    -1,    -1,    97,    -1,    -1,
     715,    -1,   213,   103,   215,    88,   217,   722,    91,   512,
      63,    64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,
     103,    -1,    -1,    -1,   235,    -1,   126,   238,    -1,    -1,
      -1,    -1,   140,   141,   142,    88,   144,   145,    91,   147,
      -1,   544,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   554,   555,    -1,    -1,    -1,   559,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   276,    -1,    -1,    -1,   177,
     178,   179,   180,    -1,    -1,    -1,    -1,    -1,    -1,   187,
     188,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,   197,
     198,   199,   200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   312,    -1,    -1,   315,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
     225,   226,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,   454,   455,   456,   457,    -1,
      -1,    -1,    -1,    -1,   647,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   514,    -1,    -1,    -1,    47,    48,    -1,    -1,
     875,   876,    -1,    54,    55,    56,    57,    58,    59,    60,
     885,    62,    63,    64,    65,    -1,    -1,    68,    69,    70,
      -1,    -1,   685,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    86,    87,    88,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   928,    -1,    -1,    -1,    -1,    -1,    -1,
     723,    -1,    -1,    -1,    -1,   436,   437,   438,   439,   440,
      -1,    -1,   123,    -1,    -1,    -1,   344,   345,    -1,   347,
      -1,    -1,   350,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   760,    -1,    -1,
      -1,    -1,   370,   371,   372,   768,   374,   375,    -1,   377,
      -1,    -1,   775,   776,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   390,   391,   392,    -1,   394,   395,    -1,   397,
      -1,    -1,    -1,  1008,  1009,    -1,    -1,    -1,    -1,    -1,
      -1,   512,   410,   411,   412,    -1,   414,   415,    -1,   417,
      -1,    -1,    -1,   816,    -1,    75,    76,    77,    78,    -1,
      80,   824,    82,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   544,    -1,    -1,    -1,    -1,    -1,  1054,
      -1,    -1,    -1,   554,   555,    -1,    -1,    -1,   559,   454,
     455,   456,   457,   856,   857,    -1,   859,   676,   677,   678,
     679,   680,   681,   682,   683,   684,    -1,   686,   687,   688,
     689,   690,   691,   692,   693,    -1,  1091,  1092,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   894,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,   168,   169,
     170,    -1,   172,   173,    20,   175,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   183,   184,   185,   186,    -1,    -1,    -1,
      -1,    -1,    -1,   193,   194,   195,   196,    -1,    -1,    -1,
      -1,    47,    48,   203,   204,   205,   206,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   574,    -1,    74,    75,
      76,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,   587,
     588,    -1,   590,    -1,    -1,   593,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,   607,
     608,    16,   610,    -1,    -1,   613,    -1,  1010,    -1,   871,
     872,    -1,   723,    -1,    -1,    -1,    -1,   123,    -1,   627,
     628,   840,   630,   842,    -1,   633,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    70,    -1,   768,    -1,    -1,
      75,    -1,    -1,    -1,   775,   776,    -1,    -1,    -1,    -1,
      -1,   676,   677,   678,   679,   680,   681,   682,   683,   684,
      -1,   686,   687,   688,   689,   690,   691,   692,   693,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   958,    -1,    -1,    -1,
      -1,   361,   362,    -1,   364,    -1,    -1,   367,   123,    -1,
     929,    -1,    -1,   824,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   381,   382,   383,    -1,   385,   386,    -1,   388,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   401,   402,   403,    -1,   405,   406,    -1,   408,  1011,
    1012,    -1,  1014,  1015,    -1,  1017,  1018,    -1,    -1,    -1,
      -1,   421,   422,   423,    -1,   425,   426,    -1,   428,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   785,    -1,    -1,
      -1,    -1,    -1,   894,    -1,    -1,    -1,   795,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   805,    -1,  1061,
      -1,    -1,  1064,  1065,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1087,  1088,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1096,   840,    -1,   842,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1111,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,   867,
    1122,    -1,  1124,  1125,    -1,  1127,  1128,    -1,    -1,    -1,
      -1,    -1,  1134,    -1,    -1,  1137,  1138,    -1,    -1,    -1,
      -1,  1143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1010,
      75,    76,    77,    -1,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,   583,   929,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   940,   941,    -1,    -1,    -1,    -1,   598,   599,
      -1,   601,    -1,    -1,   604,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,   618,   619,
      -1,   621,    -1,    -1,   624,   140,   141,    75,    76,   144,
      -1,    79,    80,    81,    82,    83,    84,    -1,   638,   639,
      -1,   641,    -1,    -1,   644,    -1,    -1,    -1,    -1,   710,
      -1,    -1,    -1,   168,   169,    -1,    -1,   172,    -1,  1007,
      -1,    -1,   177,   178,   179,    -1,    -1,    -1,   183,   184,
     185,    -1,   187,   188,   189,    -1,    -1,    -1,   193,   194,
     195,    -1,   197,   198,   199,    -1,    -1,    -1,   203,   204,
     205,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     761,   762,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
     168,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,   177,
     178,    -1,    -1,    -1,    -1,   183,   184,    -1,    -1,   187,
     188,    -1,    -1,    -1,    -1,   193,   194,    -1,    -1,   197,
     198,    -1,    -1,    -1,    -1,   203,   204,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,    70,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      91,   791,    -1,   854,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   801,   103,    -1,    -1,    -1,    -1,    -1,   869,    -1,
      -1,   811,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     881,    -1,   123,    -1,    -1,    -1,    -1,   888,    -1,   344,
     891,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,   361,   908,   909,    16,
      -1,    -1,    -1,    -1,    -1,   370,   371,    -1,    -1,   374,
      -1,    -1,    -1,    -1,    -1,    -1,   381,   382,    -1,    -1,
     385,    -1,    -1,   934,    -1,   390,   391,    -1,    -1,   394,
      -1,    -1,    -1,    -1,    -1,    -1,   401,   402,    -1,    -1,
     405,    -1,    -1,    -1,    -1,   410,   411,    64,    65,   414,
      -1,    68,    69,    70,    -1,    -1,   421,   422,    75,    -1,
     425,   972,    -1,    -1,    -1,   976,    -1,    -1,   979,    -1,
      -1,    88,   370,    -1,    91,   986,    -1,   988,    -1,   990,
      -1,    -1,    -1,   381,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   390,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   401,    -1,    -1,   123,    -1,    -1,    -1,
      -1,  1022,   410,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   421,    -1,    -1,    -1,  1038,    -1,    -1,
    1041,    -1,    -1,  1044,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    15,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,  1069,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    63,    64,    65,    -1,    -1,
      68,    69,    70,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    86,    87,
      88,    -1,   587,    91,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,   598,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,   607,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   618,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,   627,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,   638,    -1,    54,    55,    56,    57,    58,
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
       9,    10,    11,    -1,    -1,    14,    15,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,   123,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    74,    75,    76,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    33,    34,    -1,    -1,    -1,    16,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,   123,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,     3,     4,
       5,     6,     7,     8,     9,    10,    63,    64,    65,    14,
      -1,    68,    69,    70,    -1,    20,    -1,    -1,    75,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    33,    34,
      -1,    88,    16,    -1,    91,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,   123,    -1,   103,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,     3,     4,
       5,     6,     7,     8,     9,    10,   123,    -1,    -1,    74,
      75,    76,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    33,    34,
      -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    88,    89,    90,    91,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,   123,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    20,    21,   123,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      33,    34,    -1,    -1,    16,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   123,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    63,    64,    65,    27,    -1,    68,    69,    70,    -1,
      33,    34,    -1,    75,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    88,    -1,    -1,    91,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
     123,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    20,
      -1,   123,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     123,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   123,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    20,    21,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    33,    34,    -1,    -1,    16,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,   123,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    74,    75,    76,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    70,    -1,    33,    34,    -1,    75,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,   123,   103,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    20,    21,   123,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    33,    34,    -1,    -1,
      16,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   123,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,    75,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    88,    -1,    -1,    91,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,   123,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    20,    21,   123,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    33,    34,
      -1,    -1,    -1,    16,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   123,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    64,    65,    -1,    -1,    68,    69,    70,    33,    34,
      -1,    -1,    75,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      75,    76,     3,     4,     5,     6,     7,     8,     9,    10,
     123,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,   123,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,     3,     4,     5,     6,     7,     8,     9,    10,
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
      57,    58,    59,    60,    -1,    62,   123,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   123,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    74,
      75,    76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
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
      13,    74,    75,    76,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
     123,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     123,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    33,    34,    16,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    70,    71,
      72,    -1,    -1,    75,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   123,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,   123,    20,    21,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    74,    75,    76,    -1,    47,
      48,    -1,    -1,    20,    21,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    74,    75,    76,    -1,
      47,    48,    -1,    -1,    20,    21,    -1,    54,    55,    56,
      57,    58,    59,    60,   123,    62,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    74,    75,    76,
      -1,    47,    48,    -1,    -1,    20,    21,    -1,    54,    55,
      56,    57,    58,    59,    60,   123,    62,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    74,    75,
      76,    -1,    47,    48,    -1,    -1,    20,    21,    -1,    54,
      55,    56,    57,    58,    59,    60,   123,    62,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    74,
      75,    76,    -1,    47,    48,    -1,    -1,    20,    21,    -1,
      54,    55,    56,    57,    58,    59,    60,   123,    62,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      74,    75,    76,    -1,    47,    48,    -1,    -1,    20,    21,
      -1,    54,    55,    56,    57,    58,    59,    60,   123,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   123,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   123
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,    13,    63,    64,    65,    68,    69,    70,    88,    91,
      97,   103,   126,   128,   141,   142,   143,   144,   145,   146,
     152,   268,   269,   270,   123,    69,   123,   140,   123,     0,
     126,   142,   142,    63,    64,    65,    68,    69,    70,   103,
      63,    64,    65,    68,    69,    70,    88,    91,   103,    63,
      64,    65,    68,    69,    70,    88,    91,   103,    14,    16,
      61,    66,    67,   147,   153,   158,   159,   161,   163,   140,
      44,    13,    44,   147,   149,   153,   158,   159,   161,   123,
     123,   123,   123,   123,   123,   123,   154,   155,   123,   136,
     137,   136,   160,   278,   123,   162,     3,     4,     5,     6,
       7,     8,     9,    10,    13,    15,    25,    69,    75,   123,
     129,   130,   131,   132,   133,   134,   135,   136,   144,   147,
     148,   152,   153,   164,   165,   166,   167,   215,   216,   226,
     227,   228,   263,   264,   265,   268,   269,   270,   271,   272,
     158,   159,   161,   163,   159,   161,   163,   161,   163,   163,
      13,    44,   123,    36,   123,    13,    93,   129,   144,   148,
     150,   151,   153,   215,   268,   269,   270,   149,   158,   159,
     161,   149,   159,   161,   149,   161,   149,   153,   158,   159,
     161,   163,   149,   153,   158,   159,   161,   153,   158,   159,
     161,   163,   149,   153,   158,   159,   161,   153,   158,   159,
     161,   163,   149,   153,   158,   159,   161,    61,   156,    11,
      17,    11,    11,    26,   228,   123,   220,   123,   168,   169,
     170,   220,     3,    13,    20,    47,    48,    54,    55,    56,
      57,    58,    59,    60,    62,    70,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    86,    87,   123,
     129,   131,   136,   139,   140,   144,   148,   174,   175,   177,
     178,   179,   180,   181,   183,   184,   187,   188,   189,   195,
     208,   209,   211,   212,   213,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   254,   255,   256,   258,
     268,   269,   270,    75,   129,   265,   148,   165,    13,   225,
     228,    98,   147,   217,   266,    20,   129,   216,   264,   129,
     216,    71,    72,    89,    90,   216,    64,    65,    68,    69,
      70,    71,    72,   129,    64,    65,    68,    69,    70,    88,
      89,    90,    91,   216,   159,   161,   163,   161,   163,   163,
     161,   163,   163,   163,    36,    13,   216,   148,   151,   129,
     149,   159,   161,   149,   161,   149,   149,   161,   149,   149,
     158,   159,   161,   163,   159,   161,   163,   161,   163,   163,
     149,   158,   159,   161,   149,   159,   161,   149,   161,   149,
     158,   159,   161,   163,   159,   161,   163,   161,   163,   163,
     149,   158,   159,   161,   149,   159,   161,   149,   161,   149,
     158,   159,   161,   163,   159,   161,   163,   161,   163,   163,
     149,   158,   159,   161,   149,   159,   161,   149,   161,   149,
     123,   135,   155,   278,   123,   216,   268,   269,   270,   272,
      20,   129,   221,   217,    18,   138,    11,    13,    27,   217,
      18,   125,   182,     3,    33,    34,    41,    42,   123,   131,
     136,   172,   173,   174,   183,   187,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   123,   140,   177,   195,   207,
     207,    22,    44,   234,   125,    16,   123,   130,   135,   185,
     273,   172,   172,    13,   123,    13,   123,    13,   172,   172,
      20,    20,    20,    18,    40,    44,   125,   182,   125,   182,
      22,    20,    18,    44,    27,    28,    29,    30,    31,    32,
     176,    22,    44,    18,    47,    48,   148,   230,    13,   123,
     168,    13,   220,   220,    20,   136,   218,   219,    62,    74,
     123,   140,   148,   178,   229,   267,   273,   266,    21,    70,
     129,   221,   222,   223,   224,   168,   225,   217,   266,   168,
     225,   225,   168,   225,   161,   163,   163,   163,   163,    13,
     225,   168,   149,   161,   149,   149,   149,   159,   161,   163,
     161,   163,   163,   161,   163,   163,   163,   149,   159,   161,
     149,   161,   149,   149,   161,   149,   149,   159,   161,   163,
     161,   163,   163,   161,   163,   163,   163,   149,   159,   161,
     149,   161,   149,   149,   161,   149,   149,   159,   161,   163,
     161,   163,   163,   161,   163,   163,   163,   149,   159,   161,
     149,   161,   149,   149,   161,   149,   149,    43,   157,   225,
     216,   216,   216,   216,    21,   129,   222,    74,   123,    11,
      19,    18,   169,   147,   171,   172,   190,    19,    18,   125,
     207,   207,   207,   207,    21,    12,    45,    46,    38,    39,
      43,    52,    53,    16,    17,    73,    49,    50,    51,    33,
      34,    35,    36,    37,   123,   273,   123,   273,   168,    12,
     134,   274,   275,   276,    18,   138,   192,   193,   138,   192,
      20,   123,   185,    13,    13,    40,    13,    13,    13,    13,
     172,   172,    13,    70,   233,   239,   260,   262,   172,   235,
      62,    74,    76,   123,   184,   273,   125,   125,    76,   123,
     273,    21,   172,   186,   172,   123,   184,   273,   172,   123,
     273,   123,   184,   273,   172,   217,   217,    21,   221,   222,
      11,    20,    20,    44,    44,    44,   148,   148,   229,    62,
      74,   129,    23,   123,   170,    11,    11,    21,    13,   266,
      13,    13,   163,    13,   149,   161,   163,   163,   163,   163,
     149,   161,   149,   149,   149,   161,   163,   163,   163,   163,
     149,   161,   149,   149,   149,   161,   163,   163,   163,   163,
     149,   161,   149,   149,   149,   278,    43,   225,   225,   225,
     225,   138,    21,    44,    20,    19,    11,   148,   171,   191,
     194,    19,   172,   198,   199,   200,   201,   202,   203,   203,
      27,   204,    27,   204,   134,   205,   205,   205,   206,   206,
     207,   207,   207,   123,    20,   123,    61,    62,   277,    11,
      17,   172,   190,   138,   193,   190,   138,    21,   186,    20,
     172,    21,    21,    13,   172,    40,    13,    11,    19,    22,
      44,    20,   123,    76,   123,    11,    21,    19,    20,   123,
     123,    20,   123,    19,    11,    21,   219,    21,   186,    21,
     186,    62,   273,    62,   273,    62,   273,   148,    20,    20,
      23,   170,   123,    21,   222,   223,   163,   149,   163,   149,
     163,   149,   278,   138,    74,    21,   222,   148,    11,    40,
     204,   204,    21,   186,    20,   134,   134,   275,    19,   163,
      21,    21,   186,    13,    84,    86,    87,   123,   235,   236,
     249,   250,   251,   252,   253,   257,   259,   235,    21,   261,
     262,    13,   172,    13,   172,   239,   123,   273,   123,   273,
      21,   186,    20,   172,    21,   186,    20,    21,   186,    20,
      21,   222,    13,    21,    13,    21,    20,    62,    20,    62,
      20,    62,    21,   186,    21,   186,   123,    21,   138,    21,
     171,   196,    21,    21,   186,   163,   163,    21,    20,    20,
      20,    40,    85,   235,    21,    21,   261,    21,    21,   261,
      13,   123,    20,   123,    21,    21,   186,    21,    21,   186,
      21,    21,   186,    21,    13,    13,    21,   186,    20,    21,
     186,    20,    21,   186,    20,    13,    21,    13,    21,   138,
      21,   163,   172,   172,    13,   233,   260,   250,   235,   235,
     235,    21,   235,   235,    21,    21,   261,    21,   186,    20,
      21,    21,    21,    13,    21,    21,   186,    13,    21,    21,
     186,    13,    21,    21,   186,    13,    13,    21,    21,    13,
     172,    40,    13,   235,   235,   235,    21,    21,    21,   186,
      13,    13,    21,    13,    13,    21,    13,    13,    21,   250,
     250,    21,   261,    13,   172,    13,   172,   235,    21,    13,
      13,    13,    85,   250,    21,    21,   261,    21,    21,   261,
      13,   250,   250,   250,    21,   250,   250,    21,    21,   261,
     250,   250,   250,    21,   250
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
     146,   146,   146,   146,   146,   147,   148,   149,   149,   150,
     150,   151,   151,   151,   151,   151,   152,   153,   154,   154,
     155,   155,   156,   156,   157,   157,   158,   159,   160,   160,
     161,   162,   162,   163,   163,   164,   164,   165,   165,   165,
     165,   166,   166,   166,   166,   166,   167,   167,   167,   167,
     168,   168,   169,   169,   170,   170,   171,   171,   172,   173,
     173,   174,   175,   175,   175,   175,   176,   176,   176,   176,
     176,   176,   177,   177,   177,   178,   178,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   180,   180,   180,
     180,   180,   180,   180,   181,   181,   181,   181,   181,   181,
     181,   182,   182,   183,   183,   183,   183,   184,   184,   184,
     184,   184,   184,   184,   184,   185,   186,   186,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     190,   190,   191,   191,   191,   192,   192,   193,   194,   194,
     195,   195,   195,   196,   196,   197,   197,   198,   198,   199,
     199,   200,   200,   201,   201,   202,   202,   202,   203,   203,
     203,   203,   203,   203,   204,   204,   204,   204,   205,   205,
     205,   206,   206,   206,   206,   207,   207,   207,   207,   207,
     208,   209,   210,   210,   210,   211,   211,   211,   211,   211,
     212,   213,   214,   215,   215,   215,   215,   215,   215,   215,
     215,   215,   215,   216,   216,   216,   216,   216,   216,   216,
     216,   217,   218,   218,   219,   220,   220,   220,   220,   220,
     220,   220,   220,   221,   221,   222,   222,   223,   223,   223,
     224,   224,   225,   225,   226,   227,   228,   228,   229,   229,
     230,   230,   230,   231,   232,   233,   233,   234,   234,   235,
     235,   235,   235,   235,   235,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   237,   238,   239,   239,   239,   239,
     239,   239,   239,   240,   240,   241,   241,   242,   242,   243,
     243,   244,   245,   246,   247,   248,   249,   250,   250,   250,
     250,   250,   251,   252,   253,   253,   254,   255,   255,   256,
     256,   256,   256,   256,   256,   256,   256,   257,   257,   257,
     257,   257,   257,   257,   257,   258,   259,   260,   260,   261,
     262,   262,   263,   263,   263,   263,   264,   264,   264,   264,
     264,   264,   264,   264,   265,   266,   266,   266,   266,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   268,
     268,   268,   268,   268,   268,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   273,   274,   274,   275,   275,
     276,   276,   277,   277,   278
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
       5,     6,     5,     5,     4,     1,     1,     2,     3,     1,
       2,     1,     3,     4,     1,     1,     1,     3,     1,     3,
       2,     1,     2,     3,     2,     3,     2,     2,     1,     3,
       2,     1,     3,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     3,
       1,     3,     3,     1,     1,     2,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     5,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     3,     3,
       3,     2,     3,     1,     3,     3,     3,     4,     5,     5,
       6,     5,     6,     6,     7,     1,     1,     3,     3,     4,
       5,     6,     6,     7,     5,     6,     6,     7,     5,     6,
       6,     7,     5,     6,     6,     7,     7,     8,     8,     9,
       4,     4,     4,     6,     4,     3,     3,     3,     5,     3,
       4,     4,     4,     4,     3,     3,     3,     3,     2,     2,
       3,     2,     1,     1,     2,     1,     2,     3,     1,     3,
       4,     4,     4,     1,     5,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     4,     4,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     1,     2,     2,     1,
       2,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       2,     2,     3,     2,     3,     3,     3,     3,     4,     5,
       5,     5,     5,     2,     2,     3,     4,     3,     3,     4,
       3,     2,     1,     3,     1,     3,     4,     5,     4,     6,
       5,     7,     6,     2,     4,     1,     3,     2,     1,     3,
       3,     4,     1,     1,     1,     2,     3,     2,     1,     2,
       1,     1,     1,     1,     2,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     5,     2,     3,     2,     3,     3,
       2,     3,     3,     3,     5,     7,     7,     1,     1,     1,
       1,     1,     3,     5,     1,     1,     5,     1,     1,     6,
       7,     7,     8,     7,     8,     8,     9,     6,     7,     7,
       8,     7,     8,     8,     9,     7,     7,     1,     1,     1,
       1,     3,     3,     2,     4,     3,     3,     4,     5,     6,
       4,     5,     6,     7,     1,     4,     3,     3,     2,     4,
       5,     5,     6,     4,     5,     5,     6,     6,     7,     7,
       8,     6,     7,     7,     8,     6,     7,     7,     8,     1,
       1,     1,     2,     2,     2,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     1,     3,     1,     1,
       1,     2,     2,     2,     1
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
#line 210 "parser_1st.y"
                              {return 0;}
#line 3374 "parser_1st.tab.c"
    break;

  case 3: /* COMPILATIONUNIT: ORDINARYCOMPILATIONUNIT EOFF  */
#line 211 "parser_1st.y"
                                                     {return 0;}
#line 3380 "parser_1st.tab.c"
    break;

  case 4: /* TYPE: PRIMITIVETYPE  */
#line 213 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3386 "parser_1st.tab.c"
    break;

  case 5: /* TYPE: REFERENCETYPE  */
#line 214 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3392 "parser_1st.tab.c"
    break;

  case 6: /* PRIMITIVETYPE: NUMERICTYPE  */
#line 216 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3398 "parser_1st.tab.c"
    break;

  case 7: /* PRIMITIVETYPE: BOOLEAN  */
#line 217 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 3404 "parser_1st.tab.c"
    break;

  case 8: /* NUMERICTYPE: INTEGRALTYPE  */
#line 219 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3410 "parser_1st.tab.c"
    break;

  case 9: /* NUMERICTYPE: FLOATINGTYPE  */
#line 220 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3416 "parser_1st.tab.c"
    break;

  case 10: /* INTEGRALTYPE: BYTE  */
#line 222 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3422 "parser_1st.tab.c"
    break;

  case 11: /* INTEGRALTYPE: SHORT  */
#line 223 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3428 "parser_1st.tab.c"
    break;

  case 12: /* INTEGRALTYPE: INT  */
#line 224 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3434 "parser_1st.tab.c"
    break;

  case 13: /* INTEGRALTYPE: LONG  */
#line 225 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3440 "parser_1st.tab.c"
    break;

  case 14: /* INTEGRALTYPE: CHAR  */
#line 226 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3446 "parser_1st.tab.c"
    break;

  case 15: /* FLOATINGTYPE: FLOAT  */
#line 228 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3452 "parser_1st.tab.c"
    break;

  case 16: /* FLOATINGTYPE: DOUBLE  */
#line 229 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3458 "parser_1st.tab.c"
    break;

  case 17: /* REFERENCETYPE: CLASSORINTERFACETYPE  */
#line 231 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3464 "parser_1st.tab.c"
    break;

  case 18: /* CLASSORINTERFACETYPE: CLASSTYPE  */
#line 233 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3470 "parser_1st.tab.c"
    break;

  case 19: /* CLASSTYPE: CLASSTYPE1  */
#line 235 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3476 "parser_1st.tab.c"
    break;

  case 20: /* CLASSTYPE1: IDENTIFIER  */
#line 237 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3482 "parser_1st.tab.c"
    break;

  case 21: /* DIMS: OPENSQUARE CLOSESQUARE  */
#line 240 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3488 "parser_1st.tab.c"
    break;

  case 22: /* DIMS: DIMS OPENSQUARE CLOSESQUARE  */
#line 241 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3494 "parser_1st.tab.c"
    break;

  case 23: /* METHODNAME: IDENTIFIER  */
#line 243 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3505 "parser_1st.tab.c"
    break;

  case 24: /* EXPRESSIONNAME: IDENTIFIER DOT IDENTIFIER  */
#line 250 "parser_1st.y"
                                               {    /*$$ = new_temp();
                                                    int curr = chartonum($$);
                                                    string  name = chartostring($1), name2 = chartostring($3);
                                                    ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                    ds[curr]["var"] = name+"."+name2;
                                                    // ds[curr]["lineno"] = get_symbol_table(name,"lineno");
                                                    TODO*/
}
#line 3518 "parser_1st.tab.c"
    break;

  case 25: /* EXPRESSIONNAME: EXPRESSIONNAME DOT IDENTIFIER  */
#line 258 "parser_1st.y"
                                                  {/*TODO*/}
#line 3524 "parser_1st.tab.c"
    break;

  case 28: /* TOPLEVELCLASSORINTERFACEDECLARATION: CLASSDECLARATION  */
#line 264 "parser_1st.y"
                                                          {   
    for (auto x : fields ){
        cout<<x.first;
        cout<<x.second.typ.name;
        cout<<x.second.typ.dims;
        for(auto y : x.second.dims){
            cout<<"["<<y<<"]";
        }
cout<<endl;
    }
    cout<<"meth";
    for(auto x : methods){
        cout<<x.first<<endl;
        cout<<x.second.rettype.name <<x.second.rettype.dims <<endl;
        for (auto y : x.second.argtype){
            cout<<y.name<<" "<<y.dims<<" ";

        }
        cout<<endl;
        
        
        }
     resetclass();}
#line 3552 "parser_1st.tab.c"
    break;

  case 37: /* NORMALCLASSDECLARATION: CLASS IDENTIFIER CLASSBODY  */
#line 299 "parser_1st.y"
                                                        {if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));/*TODO begin class */}
#line 3558 "parser_1st.tab.c"
    break;

  case 38: /* NORMALCLASSDECLARATION: SUPER1 CLASS IDENTIFIER CLASSBODY  */
#line 300 "parser_1st.y"
                                                                {if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3564 "parser_1st.tab.c"
    break;

  case 39: /* NORMALCLASSDECLARATION: SUPER2 CLASS IDENTIFIER CLASSBODY  */
#line 301 "parser_1st.y"
                                                                {if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3570 "parser_1st.tab.c"
    break;

  case 40: /* NORMALCLASSDECLARATION: SUPER3 CLASS IDENTIFIER CLASSBODY  */
#line 302 "parser_1st.y"
                                                                {if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3576 "parser_1st.tab.c"
    break;

  case 165: /* OPENCURLY: OPENCURLY1  */
#line 435 "parser_1st.y"
                          {newscope(); }
#line 3582 "parser_1st.tab.c"
    break;

  case 166: /* CLOSECURLY: CLOSECURLY1  */
#line 436 "parser_1st.y"
                          {popscope();}
#line 3588 "parser_1st.tab.c"
    break;

  case 206: /* FIELDDECLARATION: FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 497 "parser_1st.y"
                                                                             {
                    {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring((yyvsp[-2].val))));
                                                                    
                                                                    
                    }
                        
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            assert(fields.find(x.first.name) == fields.end());
                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));
                            /*CHECK TODO*/
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                        }
                    }
#line 3612 "parser_1st.tab.c"
    break;

  case 207: /* FIELDDECLARATION: SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 516 "parser_1st.y"
                                                                    {
                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring((yyvsp[-2].val))));
                                                                    
                                                                    
                    }
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            assert(fields.find(x.first.name) == fields.end());

                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                        }
                    }
#line 3635 "parser_1st.tab.c"
    break;

  case 208: /* FIELDDECLARATION: SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 534 "parser_1st.y"
                                                                    {
                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring((yyvsp[-2].val))));
                                                                    
                                                                    
                    }
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            assert(fields.find(x.first.name) == fields.end());

                            fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));
                            reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                        }
                    }
#line 3658 "parser_1st.tab.c"
    break;

  case 209: /* FIELDDECLARATION: TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 552 "parser_1st.y"
                                                              {

                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring((yyvsp[-2].val))));
                                                                    
                                                                    
                    }
                        
                        for (auto x: generalmap[(yyvsp[-1].val)].vlist){
                            
                            assert(fields.find(x.first.name) == fields.end());

                           fields[x.first.name].typ.dims= x.first.num;
                            fields[x.first.name].typ.name= chartostring((yyvsp[-2].val));
                             reverse(all(x.second.dims));
                            fields[x.first.name].dims = x.second.dims;
                        }
                    }
#line 3684 "parser_1st.tab.c"
    break;

  case 210: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATOR  */
#line 576 "parser_1st.y"
                                               {(yyval.val) = new_temp(); generalmap[(yyval.val)].vlist.push_back({generalmap[(yyvsp[0].val)].vid, generalmap[(yyvsp[0].val)].vinit});
{   
                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                                    if(ds[curr1].find("start")!=ds[curr1].end()){
                                                        ds[curr]["start"] = ds[curr1]["start"];
                                                        ds[curr]["type"] = ds[curr1]["type"];
                                                    }
                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
}
}
#line 3699 "parser_1st.tab.c"
    break;

  case 211: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR  */
#line 586 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[-2].val); generalmap[(yyval.val)].vlist.push_back({generalmap[(yyvsp[0].val)].vid, generalmap[(yyvsp[0].val)].vinit});
                        {  
                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                                    if(ds[curr1].find("start")!=ds[curr1].end()){
                                                        ds[curr]["start"] = ds[curr1]["start"];
                                                        ds[curr]["type"] = ds[curr1]["type"];
                                                    }
                                                    else if(ds[curr3].find("start")!=ds[curr3].end()){
                                                        ds[curr]["start"] = ds[curr3]["start"];
                                                        ds[curr]["type"] = ds[curr1]["type"];
                                                    }
                                                    ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                    assert(!(ds[curr3].find("type")!=ds[curr3].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"]));
                                                    // error("Incompatible types");

}
}
#line 3721 "parser_1st.tab.c"
    break;

  case 212: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER  */
#line 604 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit ;                                           int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["start"] = code.size();
                                                                            ds[curr]["type"] = ds[curr3]["type"];
                                                                            
                                                                            // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                            // code.push_back("hello");
                                                                            code.push_back(ds[curr1]["var"]+"="+ds[curr3]["var"]);
                                                                            }
#line 3734 "parser_1st.tab.c"
    break;

  case 213: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID  */
#line 612 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];}
#line 3740 "parser_1st.tab.c"
    break;

  case 214: /* VARIABLEDECLARATORID: IDENTIFIER  */
#line 614 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));

}
#line 3753 "parser_1st.tab.c"
    break;

  case 215: /* VARIABLEDECLARATORID: IDENTIFIER DIMS  */
#line 622 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        
                        /*TODO*/
                        }
#line 3762 "parser_1st.tab.c"
    break;

  case 216: /* VARIABLEINITIALIZER: EXPRESSION  */
#line 628 "parser_1st.y"
                                    {(yyval.val) = new_temp(); generalmap[(yyval.val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 3768 "parser_1st.tab.c"
    break;

  case 217: /* VARIABLEINITIALIZER: ARRAYINITIALIZER  */
#line 629 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 3774 "parser_1st.tab.c"
    break;

  case 218: /* EXPRESSION: ASSIGNMENTEXPRESSION  */
#line 631 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 3780 "parser_1st.tab.c"
    break;

  case 219: /* ASSIGNMENTEXPRESSION: CONDITIONALEXPRESSION  */
#line 633 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 3788 "parser_1st.tab.c"
    break;

  case 220: /* ASSIGNMENTEXPRESSION: ASSIGNMENT  */
#line 636 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);}
#line 3794 "parser_1st.tab.c"
    break;

  case 221: /* ASSIGNMENT: LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  */
#line 638 "parser_1st.y"
                                                           {
    
    // code.pb($1.val + $2.val + $3.val )
    // string t  =new_var();
    // code.pb(t + " = " + $1.val);
    // $$.val = t;
    (yyval.val) = (yyvsp[-2].val);
    int curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val)), curr2 = chartonum((yyvsp[-1].val));
    type_check(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    type_conversion(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    code.push_back(ds[curr1]["var"]+ds[curr2]["op"]+ds[curr3]["var"]);

}
#line 3812 "parser_1st.tab.c"
    break;

  case 222: /* LEFTHANDSIDE: EXPRESSIONNAME  */
#line 652 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 3818 "parser_1st.tab.c"
    break;

  case 223: /* LEFTHANDSIDE: IDENTIFIER  */
#line 653 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = code.size();
                }
#line 3831 "parser_1st.tab.c"
    break;

  case 224: /* LEFTHANDSIDE: FIELDACCESS  */
#line 661 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 3837 "parser_1st.tab.c"
    break;

  case 226: /* ASSIGNMENTOPERATOR: EQUALS  */
#line 664 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 3844 "parser_1st.tab.c"
    break;

  case 227: /* ASSIGNMENTOPERATOR: MULTIPLYEQUALS  */
#line 666 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 3851 "parser_1st.tab.c"
    break;

  case 228: /* ASSIGNMENTOPERATOR: DIVIDEEQUALS  */
#line 668 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 3858 "parser_1st.tab.c"
    break;

  case 229: /* ASSIGNMENTOPERATOR: MODEQUALS  */
#line 670 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 3865 "parser_1st.tab.c"
    break;

  case 230: /* ASSIGNMENTOPERATOR: PLUSEQUALS  */
#line 672 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 3872 "parser_1st.tab.c"
    break;

  case 231: /* ASSIGNMENTOPERATOR: MINUSEQUALS  */
#line 674 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 3879 "parser_1st.tab.c"
    break;

  case 232: /* FIELDACCESS: PRIMARY DOT IDENTIFIER  */
#line 677 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring((yyvsp[0].val));
                                        }else assert(0 && "unexpected type\n");
                                        }
#line 3891 "parser_1st.tab.c"
    break;

  case 235: /* PRIMARY: PRIMARYNONEWARRAY  */
#line 687 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 3897 "parser_1st.tab.c"
    break;

  case 236: /* PRIMARY: ARRAYCREATIONEXPRESSION  */
#line 688 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 3903 "parser_1st.tab.c"
    break;

  case 237: /* PRIMARYNONEWARRAY: LITERAL  */
#line 690 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 3909 "parser_1st.tab.c"
    break;

  case 238: /* PRIMARYNONEWARRAY: CLASSLITERAL  */
#line 691 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 3915 "parser_1st.tab.c"
    break;

  case 239: /* PRIMARYNONEWARRAY: THIS  */
#line 692 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 3924 "parser_1st.tab.c"
    break;

  case 241: /* PRIMARYNONEWARRAY: OPENPARAN EXPRESSION CLOSEPARAN  */
#line 697 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 3930 "parser_1st.tab.c"
    break;

  case 243: /* PRIMARYNONEWARRAY: FIELDACCESS  */
#line 699 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 3936 "parser_1st.tab.c"
    break;

  case 245: /* PRIMARYNONEWARRAY: METHODINVOCATION  */
#line 701 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 3942 "parser_1st.tab.c"
    break;

  case 247: /* LITERAL: INTEGERLITERAL  */
#line 704 "parser_1st.y"
                        {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "byte"; ds[chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val));}
#line 3948 "parser_1st.tab.c"
    break;

  case 248: /* LITERAL: FLOATINGPOINTLITERAL  */
#line 705 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val));}
#line 3954 "parser_1st.tab.c"
    break;

  case 249: /* LITERAL: BOOLEANLITERAL  */
#line 706 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool"; ds[chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val));}
#line 3960 "parser_1st.tab.c"
    break;

  case 250: /* LITERAL: CHARACTERLITERAL  */
#line 707 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char"; ds[chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val));}
#line 3966 "parser_1st.tab.c"
    break;

  case 251: /* LITERAL: STRINGLITERAL  */
#line 708 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String"; ds[chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val));}
#line 3972 "parser_1st.tab.c"
    break;

  case 252: /* LITERAL: TEXTBLOCK  */
#line 709 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String"; ds[chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val));}
#line 3978 "parser_1st.tab.c"
    break;

  case 253: /* LITERAL: NULLLITERAL  */
#line 710 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null"; ds[chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val));}
#line 3984 "parser_1st.tab.c"
    break;

  case 276: /* ARGUMENTLIST: EXPRESSION  */
#line 739 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 3990 "parser_1st.tab.c"
    break;

  case 277: /* ARGUMENTLIST: ARGUMENTLIST COMMA EXPRESSION  */
#line 740 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4003 "parser_1st.tab.c"
    break;

  case 278: /* METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  */
#line 749 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                                        string name = ds[curr1]["var"];
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = methods[name].rettype.name;
                                                        vector<string> types;
                                                        type_check_function(name,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+"= call, "+name);
}
#line 4019 "parser_1st.tab.c"
    break;

  case 279: /* METHODINVOCATION: METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 760 "parser_1st.y"
                                                                    {   (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
                                                        string name = ds[curr1]["var"] ;
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = methods[name].rettype.name;
                                                        vector<string> types;
                                                        for(auto i:ds2[curr3]["type"])
                                                        types.push_back(i);
                                                        type_check_function(name,types);    // takes in name of function and types of parameters
                                                        for(auto i:ds2[curr3]["var"])
                                                        code.push_back("push param "+i);
                                                        ds[curr]["start"] = ds[curr3]["start"];
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+"= call, "+name);
}
#line 4039 "parser_1st.tab.c"
    break;

  case 280: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 775 "parser_1st.y"
                                                                        {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        // int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3);
                                                        // string name = ds[curr1]["var"], name2 = ds[curr3]["var"];
                                                        // ds[curr]["var"] = new_var();
                                                        // ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                        // vector<string> types;
                                                        // type_check_function_obj(name,name2,types);    // takes in name of function and types of parameters
                                                        // ds[curr]["start"] = code.size();
                                                        // if(ds[curr]["type"]!="void")
                                                        // code.push_back(ds[curr]["var"]+"= call, "+name);
}
#line 4056 "parser_1st.tab.c"
    break;

  case 281: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 787 "parser_1st.y"
                                                                                    {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        // int curr = chartonum($$), curr1 = chartonum($1), curr3 = chartonum($3), curr5 = chartonum($5);
                                                        // string name = ds[curr1]["var"], name2 = ds[curr3]["var"];
                                                        // ds[curr]["var"] = new_var();
                                                        // ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                        // vector<string> types;
                                                        // for(auto i:ds2[curr5]["type"])
                                                        // types.push_back(i);
                                                        // type_check_function_obj(name,name2,types);    // takes in name of function and types of parameters
                                                        // for(auto i:ds2[curr5]["var"])
                                                        // code.push_back("push param "+i);
                                                        // ds[curr]["start"] = ds[curr5]["start"];
                                                        // if(ds[curr]["type"]!="void")
                                                        // code.push_back(ds[curr]["var"]+"= call, "+name);
}
#line 4077 "parser_1st.tab.c"
    break;

  case 320: /* ARRAYINITIALIZER: OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  */
#line 846 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4083 "parser_1st.tab.c"
    break;

  case 321: /* ARRAYINITIALIZER: OPENCURLY CLOSECURLY  */
#line 847 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4089 "parser_1st.tab.c"
    break;

  case 322: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST  */
#line 849 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4095 "parser_1st.tab.c"
    break;

  case 323: /* ARRAYINITIALIZER1: COMMA  */
#line 850 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=1;}
#line 4101 "parser_1st.tab.c"
    break;

  case 324: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST COMMA  */
#line 851 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4107 "parser_1st.tab.c"
    break;

  case 328: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZER  */
#line 858 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4113 "parser_1st.tab.c"
    break;

  case 329: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  */
#line 859 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4119 "parser_1st.tab.c"
    break;

  case 333: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  */
#line 869 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4125 "parser_1st.tab.c"
    break;

  case 334: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  */
#line 870 "parser_1st.y"
                                                                                                    {}
#line 4131 "parser_1st.tab.c"
    break;

  case 335: /* CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  */
#line 872 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4137 "parser_1st.tab.c"
    break;

  case 336: /* CONDITIONALOREXPRESSION: CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  */
#line 873 "parser_1st.y"
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
#line 4155 "parser_1st.tab.c"
    break;

  case 337: /* CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  */
#line 887 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4161 "parser_1st.tab.c"
    break;

  case 338: /* CONDITIONALANDEXPRESSION: CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  */
#line 888 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4175 "parser_1st.tab.c"
    break;

  case 339: /* INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  */
#line 898 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4181 "parser_1st.tab.c"
    break;

  case 340: /* INCLUSIVEOREXPRESSION: INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  */
#line 899 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + "|" + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4194 "parser_1st.tab.c"
    break;

  case 341: /* EXCLUSIVEOREXPRESSION: ANDEXPRESSION  */
#line 908 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4200 "parser_1st.tab.c"
    break;

  case 342: /* EXCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  */
#line 909 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + "^" + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4213 "parser_1st.tab.c"
    break;

  case 343: /* ANDEXPRESSION: EQUALITYEXPRESSION  */
#line 917 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4219 "parser_1st.tab.c"
    break;

  case 344: /* ANDEXPRESSION: ANDEXPRESSION AND EQUALITYEXPRESSION  */
#line 918 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + "&" + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4233 "parser_1st.tab.c"
    break;

  case 345: /* EQUALITYEXPRESSION: RELATIONALEXPRESSION  */
#line 928 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds[curr].find("truelist")==ds[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                        }
#line 4244 "parser_1st.tab.c"
    break;

  case 346: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  */
#line 934 "parser_1st.y"
                                                                                {   (yyval.val) = new_temp();
                                                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                    type_check(ds[curr1]["type"],ds[curr3]["type"],"==");
                                                                                    backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                    backpatch(ds3[curr1]["falselist"],stringtonum(ds[curr3]["start"]));
                                                                                    backpatch(ds3[curr3]["truelist"],code.size());
                                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                                    ds[curr]["type"] = "bool";
                                                                                    ds[curr]["var"] = new_var();
                                                                                    code.push_back(ds[curr]["var"]);
                                                                                    code.push_back("if "+ds[curr1]["var"]+"=="+ds[curr3]["var"]+" goto ");
                                                                                    ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                    code.push_back("goto ");
                                                                                    ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                    ds[curr]["start"] = ds[curr1]["start"];
                   }
#line 4265 "parser_1st.tab.c"
    break;

  case 347: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  */
#line 950 "parser_1st.y"
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
                                                                                    code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"!="+ds[curr3]["var"]);
                                                                                    code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                    ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                    code.push_back("goto ");
                                                                                    ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                    ds[curr]["start"] = ds[curr1]["start"];
                   }
#line 4287 "parser_1st.tab.c"
    break;

  case 348: /* RELATIONALEXPRESSION: SHIFTEXPRESSION  */
#line 968 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds[curr].find("truelist")==ds[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4297 "parser_1st.tab.c"
    break;

  case 349: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  */
#line 973 "parser_1st.y"
                                                                            {      // IS backpatching for $1 required?
                                                                                (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"<"+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
#line 4317 "parser_1st.tab.c"
    break;

  case 350: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  */
#line 988 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+">"+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
#line 4336 "parser_1st.tab.c"
    break;

  case 351: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  */
#line 1002 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">=");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+">="+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
#line 4355 "parser_1st.tab.c"
    break;

  case 352: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  */
#line 1016 "parser_1st.y"
                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<=");
                                                                                ds[curr]["type"] = "bool";
                                                                                ds[curr]["var"] = new_var();
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"<="+ds[curr3]["var"]);
                                                                                ds3[curr]["falselist"] = vector<int>();
                                                                                ds3[curr]["truelist"] = vector<int>();
                                                                                code.push_back("if "+ds[curr]["var"]+" goto ");
                                                                                ds3[curr]["truelist"].push_back(code.size()-1);
                                                                                code.push_back("goto ");
                                                                                ds3[curr]["falselist"].push_back(code.size()-1);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                     }
#line 4374 "parser_1st.tab.c"
    break;

  case 354: /* SHIFTEXPRESSION: ADDITIVEEXPRESSION  */
#line 1032 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4380 "parser_1st.tab.c"
    break;

  case 355: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  */
#line 1033 "parser_1st.y"
                                                                                    {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4394 "parser_1st.tab.c"
    break;

  case 356: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1042 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4407 "parser_1st.tab.c"
    break;

  case 357: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1050 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4420 "parser_1st.tab.c"
    break;

  case 358: /* ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  */
#line 1059 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 4426 "parser_1st.tab.c"
    break;

  case 359: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  */
#line 1060 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" + "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4439 "parser_1st.tab.c"
    break;

  case 360: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  */
#line 1068 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" - "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4452 "parser_1st.tab.c"
    break;

  case 361: /* MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  */
#line 1077 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4458 "parser_1st.tab.c"
    break;

  case 362: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  */
#line 1078 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"*"+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4471 "parser_1st.tab.c"
    break;

  case 363: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  */
#line 1086 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"/"+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4484 "parser_1st.tab.c"
    break;

  case 364: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  */
#line 1094 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+"%"+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4497 "parser_1st.tab.c"
    break;

  case 365: /* UNARYEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1103 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4503 "parser_1st.tab.c"
    break;

  case 366: /* UNARYEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1104 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4509 "parser_1st.tab.c"
    break;

  case 367: /* UNARYEXPRESSION: PLUS UNARYEXPRESSION  */
#line 1105 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 4517 "parser_1st.tab.c"
    break;

  case 368: /* UNARYEXPRESSION: MINUS UNARYEXPRESSION  */
#line 1108 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = -"+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4530 "parser_1st.tab.c"
    break;

  case 369: /* UNARYEXPRESSION: UNARYEXPRESSIONNOTPLUSMINUS  */
#line 1116 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 4536 "parser_1st.tab.c"
    break;

  case 370: /* PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  */
#line 1118 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    assert(0&& "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+"+1");
                                                code.push_back(ds[curr2]["var"]+"="+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] += 1;  /* Modify the actual underlying variable */
                    }
#line 4554 "parser_1st.tab.c"
    break;

  case 371: /* PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  */
#line 1132 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+"-1");
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr2]["var"]+ "="+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] -= 1;
                    }
#line 4572 "parser_1st.tab.c"
    break;

  case 372: /* UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  */
#line 1146 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4578 "parser_1st.tab.c"
    break;

  case 373: /* UNARYEXPRESSIONNOTPLUSMINUS: COMPLEMENT UNARYEXPRESSION  */
#line 1147 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~"+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4591 "parser_1st.tab.c"
    break;

  case 374: /* UNARYEXPRESSIONNOTPLUSMINUS: NOT UNARYEXPRESSION  */
#line 1155 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = !"+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4604 "parser_1st.tab.c"
    break;

  case 375: /* POSTFIXEXPRESSION: PRIMARY  */
#line 1164 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4610 "parser_1st.tab.c"
    break;

  case 376: /* POSTFIXEXPRESSION: EXPRESSIONNAME  */
#line 1165 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4616 "parser_1st.tab.c"
    break;

  case 377: /* POSTFIXEXPRESSION: IDENTIFIER  */
#line 1166 "parser_1st.y"
                                {   (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    /* How to access symbol table entry of a terminal */
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    ds[curr]["identifier"] = "YES";
                                    ds[curr]["start"] = code.size();
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    // ds[curr]["var"] = 
                                    /* How to pass values from here? */
                  }
#line 4631 "parser_1st.tab.c"
    break;

  case 378: /* POSTFIXEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1176 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4637 "parser_1st.tab.c"
    break;

  case 379: /* POSTFIXEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1177 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4643 "parser_1st.tab.c"
    break;

  case 380: /* POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  */
#line 1179 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val));
                                                type_check_unary(ds[curr1]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                code.push_back(ds[curr1]["var"]+ "="+ ds[curr]["var"]+"+1");
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
}
#line 4660 "parser_1st.tab.c"
    break;

  case 381: /* POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  */
#line 1192 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val));
                                                type_check_unary(ds[curr1]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                code.push_back(ds[curr1]["var"]+ "="+ ds[curr]["var"]+"-1");
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                // ds[curr]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
                                                // ds[curr1]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
}
#line 4679 "parser_1st.tab.c"
    break;

  case 383: /* METHODDECLARATION: METHODHEADER METHODBODY  */
#line 1210 "parser_1st.y"
                                            {
    (yyval.val) =(yyvsp[-1].val);
    code.push_back("end func");
    cerr<<"method declaration"<<generalmap[(yyvsp[-1].val)].name<<endl;
    assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());
    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
    vector <type> argtype;
     

    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
         }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 4699 "parser_1st.tab.c"
    break;

  case 384: /* METHODDECLARATION: SUPER1 METHODHEADER METHODBODY  */
#line 1226 "parser_1st.y"
                                                      {
                        (yyval.val) =(yyvsp[-2].val);
    code.push_back("end func");
    cerr<<"method declaration"<<generalmap[(yyvsp[-1].val)].name<<endl;

    assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
    vector <type> argtype;


    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
         
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 4722 "parser_1st.tab.c"
    break;

  case 385: /* METHODDECLARATION: SUPER2 METHODHEADER METHODBODY  */
#line 1244 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-2].val);
    code.push_back("end func");
    cerr<<"method declaration"<<generalmap[(yyvsp[-1].val)].name<<endl;
        assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());
      

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
    vector <type> argtype;
    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
        
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 4742 "parser_1st.tab.c"
    break;

  case 386: /* METHODDECLARATION: SUPER3 METHODHEADER METHODBODY  */
#line 1259 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-2].val);
    code.push_back("end func");
    cerr<<"method declaration"<<generalmap[(yyvsp[-1].val)].name<<endl;
        assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
    vector <type> argtype;

    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
        
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 4762 "parser_1st.tab.c"
    break;

  case 387: /* METHODDECLARATION: METHODMODIFIERS METHODHEADER METHODBODY  */
#line 1274 "parser_1st.y"
                                                               {(yyval.val) =(yyvsp[-2].val);
    code.push_back("end func");
    cerr<<"method declaration"<<generalmap[(yyvsp[-1].val)].name<<endl;
        assert(methods.find(generalmap[(yyvsp[-1].val)].name) == methods.end());

    methods[generalmap[(yyvsp[-1].val)].name].rettype = generalmap[(yyvsp[-1].val)].typ;
    vector <type> argtype;

    for (auto x : generalmap[(yyvsp[-1].val)].farglist)
        {argtype.push_back(x.typ);
        
        }
    methods[generalmap[(yyvsp[-1].val)].name].argtype = argtype;

}
#line 4782 "parser_1st.tab.c"
    break;

  case 393: /* METHODHEADER: TYPE METHODDECLARATOR  */
#line 1296 "parser_1st.y"
                                     { (yyval.val) = (yyvsp[0].val);  generalmap[(yyval.val)].typ.name = chartostring((yyvsp[-1].val)); 
tempnextscope();
for (auto x : generalmap[(yyval.val)].farglist){
symboltable[x.vid.name].typ.dims= x.vid.num;
        symboltable[x.vid.name].typ.name= x.typ.name;
        symboltable[x.vid.name].scope = scope;

        cout<<x.vid.name;
        printvarentry(symboltable[x.vid.name]);
        preservedsymboltable[{x.vid.name, scope}]= symboltable[x.vid.name];
        
        }}
#line 4799 "parser_1st.tab.c"
    break;

  case 394: /* METHODHEADER: VOID METHODDECLARATOR  */
#line 1308 "parser_1st.y"
                                      { (yyval.val) = (yyvsp[0].val);  generalmap[(yyval.val)].typ.name = chartostring((yyvsp[-1].val)); 
            tempnextscope();
for (auto x : generalmap[(yyval.val)].farglist){
symboltable[x.vid.name].typ.dims= x.vid.num;
        symboltable[x.vid.name].typ.name= x.typ.name;
        symboltable[x.vid.name].scope = scope;

        cout<<x.vid.name;
        printvarentry(symboltable[x.vid.name]);
        preservedsymboltable[{x.vid.name, scope}]= symboltable[x.vid.name];
        
        }}
#line 4816 "parser_1st.tab.c"
    break;

  case 405: /* METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1335 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));
                                        ds[curr]["start"] = code.size();
                                        code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        }
#line 4826 "parser_1st.tab.c"
    break;

  case 406: /* METHODDECLARATOR: IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 1340 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                                        ds[curr]["start"] = code.size();
                                        code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        for(auto i:ds2[curr3]["param"])
                                        code.push_back("pop param, "+ i);}
#line 4836 "parser_1st.tab.c"
    break;

  case 415: /* FORMALPARAMETERLIST: FORMALPARAMETER  */
#line 1355 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 4845 "parser_1st.tab.c"
    break;

  case 416: /* FORMALPARAMETERLIST: FORMALPARAMETERLIST COMMA FORMALPARAMETER  */
#line 1359 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 4855 "parser_1st.tab.c"
    break;

  case 417: /* FORMALPARAMETER: TYPE VARIABLEDECLARATORID  */
#line 1365 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 4864 "parser_1st.tab.c"
    break;

  case 419: /* FORMALPARAMETER: FINAL TYPE VARIABLEDECLARATORID  */
#line 1370 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 4873 "parser_1st.tab.c"
    break;

  case 422: /* METHODBODY: BLOCK  */
#line 1380 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 4879 "parser_1st.tab.c"
    break;

  case 426: /* BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 1387 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val);}
#line 4885 "parser_1st.tab.c"
    break;

  case 428: /* BLOCKSTATEMENTS: BLOCKSTATEMENT  */
#line 1390 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val);}
#line 4891 "parser_1st.tab.c"
    break;

  case 429: /* BLOCKSTATEMENTS: BLOCKSTATEMENTS BLOCKSTATEMENT  */
#line 1391 "parser_1st.y"
                                                  { (yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val)), curr2 = chartonum((yyvsp[0].val));
                                                    ds3[curr]["continuelist"] = merge(ds3[curr1]["continuelist"], ds3[curr2]["continuelist"]);
                                                    ds3[curr]["breaklist"] = merge(ds3[curr1]["breaklist"], ds3[curr2]["breaklist"]);
                                                    ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4902 "parser_1st.tab.c"
    break;

  case 431: /* BLOCKSTATEMENT: LOCALVARIABLEDECLARATIONSTATEMENT  */
#line 1399 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 4908 "parser_1st.tab.c"
    break;

  case 432: /* BLOCKSTATEMENT: STATEMENT  */
#line 1400 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4914 "parser_1st.tab.c"
    break;

  case 434: /* LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  */
#line 1404 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4920 "parser_1st.tab.c"
    break;

  case 435: /* LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1406 "parser_1st.y"
                                                                         {(yyval.val) = (yyvsp[0].val);}
#line 4926 "parser_1st.tab.c"
    break;

  case 436: /* LOCALVARIABLEDECLARATION: LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1407 "parser_1st.y"
                                                                     {
                            (yyval.val) = (yyvsp[0].val);
                            cerr<<"local variable declaration"<<endl;
                            for (auto x: generalmap[(yyvsp[0].val)].vlist){
                            
                            cout<<x.first.name<<endl;
                            assert(symboltable.find(x.first.name) == symboltable.end());
                            /*ADD SIMILAR FOR FILEDS AND METHODS*/

                           symboltable[x.first.name].typ.dims= x.first.num;
                            symboltable[x.first.name].typ.name= chartostring((yyvsp[-1].val));
                             reverse(all(x.second.dims));
                            symboltable[x.first.name].dims = x.second.dims;
                            symboltable[x.first.name].scope = scope;

                            cout<<x.first.name;
                            printvarentry(symboltable[x.first.name]);
                            // preservedsymboltable[{x.first.name,scope}] = symboltable[x.first.name];
                        }
                        }
#line 4951 "parser_1st.tab.c"
    break;

  case 437: /* LOCALVARIABLETYPE: TYPE  */
#line 1428 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 4957 "parser_1st.tab.c"
    break;

  case 438: /* LOCALVARIABLETYPE: VAR  */
#line 1429 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4963 "parser_1st.tab.c"
    break;

  case 439: /* STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1432 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4969 "parser_1st.tab.c"
    break;

  case 440: /* STATEMENT: LABELEDSTATEMENT  */
#line 1433 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4975 "parser_1st.tab.c"
    break;

  case 441: /* STATEMENT: IFTHENSTATEMENT  */
#line 1434 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4981 "parser_1st.tab.c"
    break;

  case 442: /* STATEMENT: IFTHENELSESTATEMENT  */
#line 1435 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4987 "parser_1st.tab.c"
    break;

  case 443: /* STATEMENT: WHILESTATEMENT  */
#line 1436 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4993 "parser_1st.tab.c"
    break;

  case 444: /* STATEMENT: FORSTATEMENT  */
#line 1437 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4999 "parser_1st.tab.c"
    break;

  case 445: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  */
#line 1439 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5005 "parser_1st.tab.c"
    break;

  case 446: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EMPTYSTATEMENT  */
#line 1440 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5011 "parser_1st.tab.c"
    break;

  case 447: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EXPRESSIONSTATEMENT  */
#line 1441 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5017 "parser_1st.tab.c"
    break;

  case 448: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: ASSERTSTATEMENT  */
#line 1442 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5023 "parser_1st.tab.c"
    break;

  case 449: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BREAKSTATEMENT  */
#line 1443 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5029 "parser_1st.tab.c"
    break;

  case 450: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: CONTINUESTATEMENT  */
#line 1444 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5035 "parser_1st.tab.c"
    break;

  case 451: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: RETURNSTATEMENT  */
#line 1445 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5041 "parser_1st.tab.c"
    break;

  case 452: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: THROWSTATEMENT  */
#line 1446 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5047 "parser_1st.tab.c"
    break;

  case 453: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: YIELDSTATEMENT  */
#line 1447 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5053 "parser_1st.tab.c"
    break;

  case 454: /* EMPTYSTATEMENT: SEMICOLON  */
#line 1449 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5059 "parser_1st.tab.c"
    break;

  case 455: /* EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  */
#line 1451 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val);}
#line 5065 "parser_1st.tab.c"
    break;

  case 456: /* STATEMENTEXPRESSION: ASSIGNMENT  */
#line 1453 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5071 "parser_1st.tab.c"
    break;

  case 457: /* STATEMENTEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1454 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5077 "parser_1st.tab.c"
    break;

  case 458: /* STATEMENTEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1455 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5083 "parser_1st.tab.c"
    break;

  case 459: /* STATEMENTEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1456 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5089 "parser_1st.tab.c"
    break;

  case 460: /* STATEMENTEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1457 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5095 "parser_1st.tab.c"
    break;

  case 461: /* STATEMENTEXPRESSION: METHODINVOCATION  */
#line 1458 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5101 "parser_1st.tab.c"
    break;

  case 462: /* STATEMENTEXPRESSION: CLASSINSTANCECREATIONEXPRESSION  */
#line 1459 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5107 "parser_1st.tab.c"
    break;

  case 465: /* BREAKSTATEMENT: BREAK SEMICOLON  */
#line 1464 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = code.size();
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5120 "parser_1st.tab.c"
    break;

  case 467: /* CONTINUESTATEMENT: CONTINUE SEMICOLON  */
#line 1474 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = code.size();
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5133 "parser_1st.tab.c"
    break;

  case 469: /* RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  */
#line 1484 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = code.size();
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5144 "parser_1st.tab.c"
    break;

  case 470: /* RETURNSTATEMENT: RETURN SEMICOLON  */
#line 1490 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = code.size();
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 5155 "parser_1st.tab.c"
    break;

  case 474: /* IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1503 "parser_1st.y"
                                                                {   (yyval.val) = new_temp(); //Not keeping truelist and falselist corresponding to statements
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-2].val)), curr5 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    backpatch(ds3[curr3]["falselist"],code.size());
                                                                    ds[curr]["start"] = ds[curr3]["start"];
                                                                    code.push_back("Inside if then statement");
                                                                    // code.push_back(ds[curr]["start"]);
                                                                    // cout<<"Inside if then statement\n";
                                                                    // cout<<ds[curr]["start"]<<"\n";
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = ds3[curr5]["continuelist"];
                                                                    ds3[curr]["breaklist"] = ds3[curr5]["breaklist"];
                                                                    // ds3[curr]["falselist"] = ds3[curr3]["falselist"];
                                                                    // ds3[curr]["truelist"] = vector<int>();
}
#line 5175 "parser_1st.tab.c"
    break;

  case 475: /* IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT  */
#line 1519 "parser_1st.y"
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
#line 5191 "parser_1st.tab.c"
    break;

  case 476: /* IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF  */
#line 1531 "parser_1st.y"
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
#line 5207 "parser_1st.tab.c"
    break;

  case 477: /* STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1543 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5213 "parser_1st.tab.c"
    break;

  case 478: /* STATEMENTNOSHORTIF: LABELEDSTATEMENTNOSHORTIF  */
#line 1544 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5219 "parser_1st.tab.c"
    break;

  case 479: /* STATEMENTNOSHORTIF: IFTHENELSESTATEMENTNOSHORTIF  */
#line 1545 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5225 "parser_1st.tab.c"
    break;

  case 480: /* STATEMENTNOSHORTIF: WHILESTATEMENTNOSHORTIF  */
#line 1546 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5231 "parser_1st.tab.c"
    break;

  case 481: /* STATEMENTNOSHORTIF: FORSTATEMENTNOSHORTIF  */
#line 1547 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5237 "parser_1st.tab.c"
    break;

  case 483: /* WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1551 "parser_1st.y"
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
#line 5253 "parser_1st.tab.c"
    break;

  case 484: /* FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  */
#line 1563 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5259 "parser_1st.tab.c"
    break;

  case 485: /* FORSTATEMENTNOSHORTIF: ENHANCEDFORSTATEMENTNOSHORTIF  */
#line 1564 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5265 "parser_1st.tab.c"
    break;

  case 486: /* WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1567 "parser_1st.y"
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
#line 5280 "parser_1st.tab.c"
    break;

  case 487: /* FORSTATEMENT: BASICFORSTATEMENT  */
#line 1578 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5286 "parser_1st.tab.c"
    break;

  case 488: /* FORSTATEMENT: ENHANCEDFORSTATEMENT  */
#line 1579 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5292 "parser_1st.tab.c"
    break;

  case 489: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 1581 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 5305 "parser_1st.tab.c"
    break;

  case 490: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1589 "parser_1st.y"
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
#line 5321 "parser_1st.tab.c"
    break;

  case 491: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 1600 "parser_1st.y"
                                                                                            {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-3].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size()); 
}
#line 5339 "parser_1st.tab.c"
    break;

  case 492: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1613 "parser_1st.y"
                                                                                                    {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-4].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
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
#line 5360 "parser_1st.tab.c"
    break;

  case 493: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 1629 "parser_1st.y"
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
#line 5378 "parser_1st.tab.c"
    break;

  case 494: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1642 "parser_1st.y"
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
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    // backpatch(ds3[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds3[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    // backpatch(ds3[curr4]["falselist"],code.size());
}
#line 5399 "parser_1st.tab.c"
    break;

  case 495: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 1658 "parser_1st.y"
                                                                                                    {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr5 = chartonum((yyvsp[-3].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr5]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
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
#line 5420 "parser_1st.tab.c"
    break;

  case 496: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1674 "parser_1st.y"
                                                                                                            {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-6].val)), curr5 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[-2].val)), curr9 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr5]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
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
#line 5441 "parser_1st.tab.c"
    break;

  case 497: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1691 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 5454 "parser_1st.tab.c"
    break;

  case 498: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1699 "parser_1st.y"
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
#line 5470 "parser_1st.tab.c"
    break;

  case 499: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1710 "parser_1st.y"
                                                                                                     {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-3].val)), curr7 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr4]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr4]["truelist"],stringtonum(ds[curr7]["start"]));
                                                                    backpatch(ds3[curr7]["continuelist"],stringtonum(ds[curr]["start"])); 
                                                                    backpatch(ds3[curr7]["breaklist"],code.size()); 
                                                                    backpatch(ds3[curr4]["falselist"],code.size()); 
}
#line 5488 "parser_1st.tab.c"
    break;

  case 500: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1723 "parser_1st.y"
                                                                                                             {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-4].val)), curr6 = chartonum((yyvsp[-2].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr4]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
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
#line 5509 "parser_1st.tab.c"
    break;

  case 501: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1739 "parser_1st.y"
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
#line 5527 "parser_1st.tab.c"
    break;

  case 502: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1752 "parser_1st.y"
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
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    // backpatch(ds3[curr4]["truelist"],ds[curr7]["start"]);
                                                                    backpatch(ds3[curr8]["continuelist"],gotoupdate); 
                                                                    backpatch(ds3[curr8]["breaklist"],code.size()); 
                                                                    // backpatch(ds3[curr4]["falselist"],code.size());
}
#line 5548 "parser_1st.tab.c"
    break;

  case 503: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1768 "parser_1st.y"
                                                                                                             {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-5].val)), curr5 = chartonum((yyvsp[-3].val)), curr8 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr5]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
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
#line 5569 "parser_1st.tab.c"
    break;

  case 504: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1784 "parser_1st.y"
                                                                                                                     {      /* For update code should be after forbody code */
                                                                                            (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-6].val)), curr5 = chartonum((yyvsp[-4].val)), curr7 = chartonum((yyvsp[-2].val)), curr9 = chartonum((yyvsp[0].val));
                                                                    if(ds[curr5]["type"]!="boolean")
                                                                    assert(0 && "Exp Error");
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
#line 5590 "parser_1st.tab.c"
    break;

  case 507: /* FORINIT: STATEMENTEXPRESSIONLIST  */
#line 1806 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 5596 "parser_1st.tab.c"
    break;

  case 508: /* FORINIT: LOCALVARIABLEDECLARATION  */
#line 1807 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5602 "parser_1st.tab.c"
    break;

  case 509: /* FORUPDATE: STATEMENTEXPRESSIONLIST  */
#line 1809 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 5616 "parser_1st.tab.c"
    break;

  case 510: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION  */
#line 1819 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 5622 "parser_1st.tab.c"
    break;

  case 511: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION  */
#line 1820 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 5634 "parser_1st.tab.c"
    break;

  case 598: /* TYPEARGUMENT: REFERENCETYPE  */
#line 1930 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 5640 "parser_1st.tab.c"
    break;

  case 599: /* TYPEARGUMENT: WILDCARD  */
#line 1931 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 5646 "parser_1st.tab.c"
    break;

  case 604: /* INTERFACETYPE: CLASSTYPE  */
#line 1940 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 5652 "parser_1st.tab.c"
    break;


#line 5656 "parser_1st.tab.c"

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

#line 1942 "parser_1st.y"



int main(int argc, char** argv){
        newscope();
    yyparse();
    cout<<"CODE:\n";

    for (auto x : code){
        cout<<x<<endl;
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
