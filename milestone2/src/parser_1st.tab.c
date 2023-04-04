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
#define YYLAST   6219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  154
/* YYNRULES -- Number of rules.  */
#define YYNRULES  607
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1148

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
     351,   352,   354,   355,   356,   357,   359,   372,   373,   374,
     375,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   440,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   507,   508,   509,   511,
     512,   514,   515,   517,   518,   519,   520,   521,   523,   526,
     528,   529,   531,   532,   535,   536,   538,   539,   541,   543,
     545,   546,   548,   550,   551,   553,   554,   556,   557,   559,
     560,   561,   562,   564,   565,   566,   567,   568,   570,   598,
     624,   652,   692,   704,   728,   761,   763,   771,   778,   779,
     781,   783,   786,   788,   803,   804,   812,   813,   817,   819,
     821,   823,   825,   827,   830,   837,   838,   840,   843,   845,
     846,   847,   851,   852,   853,   854,   855,   856,   857,   859,
     860,   861,   862,   863,   864,   865,   867,   868,   869,   870,
     871,   872,   873,   875,   876,   878,   879,   880,   881,   883,
     884,   885,   886,   887,   888,   889,   890,   892,   895,   899,
     908,   920,   939,   963,   988,   989,   990,   991,   992,   993,
     994,   995,   996,   997,   998,   999,  1000,  1001,  1002,  1003,
    1004,  1005,  1007,  1008,  1009,  1010,  1011,  1013,  1014,  1016,
    1017,  1018,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,
    1028,  1029,  1031,  1032,  1034,  1035,  1036,  1038,  1039,  1043,
    1045,  1046,  1052,  1053,  1070,  1084,  1085,  1087,  1088,  1102,
    1103,  1113,  1114,  1123,  1124,  1132,  1133,  1143,  1151,  1167,
    1185,  1190,  1208,  1222,  1236,  1250,  1252,  1253,  1262,  1270,
    1279,  1280,  1288,  1297,  1298,  1306,  1314,  1323,  1324,  1325,
    1328,  1336,  1338,  1352,  1366,  1367,  1375,  1384,  1385,  1386,
    1400,  1401,  1403,  1416,  1431,  1434,  1444,  1468,  1490,  1512,
    1534,  1535,  1536,  1537,  1538,  1541,  1583,  1613,  1614,  1615,
    1616,  1617,  1618,  1621,  1623,  1624,  1626,  1628,  1636,  1643,
    1644,  1645,  1646,  1647,  1648,  1650,  1651,  1653,  1657,  1663,
    1667,  1668,  1674,  1675,  1678,  1679,  1681,  1683,  1685,  1686,
    1688,  1691,  1702,  1703,  1706,  1708,  1710,  1712,  1714,  1771,
    1833,  1834,  1837,  1838,  1839,  1840,  1841,  1842,  1844,  1846,
    1847,  1848,  1849,  1850,  1851,  1852,  1853,  1855,  1857,  1859,
    1860,  1861,  1862,  1863,  1864,  1865,  1867,  1868,  1870,  1878,
    1880,  1888,  1890,  1896,  1903,  1905,  1907,  1909,  1926,  1938,
    1950,  1951,  1952,  1953,  1954,  1956,  1958,  1970,  1971,  1974,
    1985,  1986,  1988,  1996,  2007,  2021,  2037,  2050,  2066,  2082,
    2099,  2107,  2118,  2132,  2149,  2162,  2178,  2195,  2213,  2215,
    2217,  2218,  2220,  2230,  2231,  2240,  2241,  2242,  2243,  2246,
    2247,  2248,  2249,  2250,  2251,  2252,  2253,  2256,  2258,  2259,
    2260,  2261,  2263,  2264,  2265,  2266,  2267,  2268,  2269,  2270,
    2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,  2279,  2280,
    2281,  2282,  2284,  2285,  2286,  2287,  2288,  2289,  2291,  2292,
    2293,  2294,  2295,  2296,  2297,  2298,  2299,  2301,  2302,  2303,
    2304,  2305,  2306,  2307,  2308,  2309,  2310,  2311,  2313,  2314,
    2315,  2316,  2317,  2318,  2319,  2320,  2321,  2324,  2325,  2326,
    2327,  2328,  2329,  2330,  2331,  2332,  2333,  2334,  2336,  2338,
    2339,  2341,  2342,  2344,  2345,  2347,  2348,  2351
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

#define YYPACT_NINF (-794)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-528)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1584,  -794,   -46,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
     -42,   -33,  -794,   194,  2821,  -794,  2553,  -794,  -794,  -794,
    -794,   719,  1290,  2172,   282,   184,    94,   198,    62,   405,
    -794,  -794,  -794,  -794,   158,  -794,  -794,  -794,  -794,  -794,
     223,   228,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   287,
     306,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   313,   333,
     340,   340,   346,   392,   262,    60,   184,  -794,  2505,  -794,
     156,   351,  -794,    -5,  3227,  -794,   392,   262,    60,   184,
     405,   405,   405,   405,   405,   405,   185,   393,  -794,  -794,
    -794,  -794,  -794,   483,  -794,  -794,   488,   262,    60,   184,
    -794,    60,   184,  -794,   184,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,   481,   184,   387,
     503,   408,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    3334,  -794,  -794,   126,  2505,  -794,  -794,  -794,  -794,   138,
    -794,  -794,  -794,  -794,    51,   535,  1474,  2709,  1835,   964,
    3614,  -794,     1,  -794,   563,  -794,  -794,   867,   387,  -794,
    -794,  3227,  -794,  1576,  -794,  1762,  3995,  2164,  -794,   262,
      60,   184,  -794,    60,   184,  -794,   184,  -794,   392,   262,
      60,   184,  -794,  -794,   392,   262,    60,   184,   392,   262,
      60,   184,  -794,  -794,   392,   262,    60,   184,   392,   262,
      60,   184,  -794,  -794,   392,   262,    60,   184,   464,  -794,
     333,  -794,   340,   498,    60,   184,  -794,   184,  -794,  -794,
     184,  -794,  -794,  -794,  4118,  -794,  2107,   508,   534,   536,
    -794,   555,   508,    -9,  -794,  5532,  5595,  5595,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,   165,  2081,  -794,   490,  1804,
    5532,  5532,  -794,    13,    15,  3594,  5532,   551,   628,  -794,
    -794,   247,  -794,    17,   645,   666,   573,  -794,   671,  -794,
    -794,   685,   836,   256,   655,  -794,  -794,   415,  -794,   469,
    -794,  -794,   951,  -794,  -794,   337,   479,   589,  -794,  3334,
    -794,  -794,  -794,   681,   595,  -794,  -794,  -794,  -794,   711,
    -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,   876,  2070,  2275,   387,   387,   709,  -794,
    -794,  -794,  -794,  -794,   340,  3191,   184,  -794,   884,   408,
     138,    51,   408,   138,  -794,  -794,  -794,  -794,   138,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   595,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   138,   717,  -794,   138,
    -794,  -794,   408,  -794,    60,   184,  -794,   184,  -794,  -794,
     184,  -794,  -794,   262,    60,   184,  -794,    60,   184,  -794,
     184,  -794,  -794,  -794,   262,    60,   184,  -794,    60,   184,
    -794,   184,  -794,   262,    60,   184,  -794,    60,   184,  -794,
     184,  -794,  -794,  -794,   262,    60,   184,  -794,    60,   184,
    -794,   184,  -794,   262,    60,   184,  -794,    60,   184,  -794,
     184,  -794,  -794,  -794,   262,    60,   184,  -794,    60,   184,
    -794,   184,  -794,   689,   694,  -794,  -794,  -794,   184,  -794,
    -794,  -794,  -794,   138,  4364,  4241,  3861,  3614,  1205,    -8,
     727,  -794,   720,   722,   595,  -794,  1116,  -794,   730,  -794,
      20,    -9,  5595,  5595,  5595,  5595,  2455,    17,   645,   725,
    -794,  -794,  -794,  -794,  -794,   192,   695,   712,   713,   708,
     467,   242,   590,   648,   653,  -794,  -794,  -794,  -794,   337,
    -794,  -794,  -794,   248,   144,  -794,  -794,  -794,  -794,    29,
      39,   595,  -794,     4,   733,   737,   737,   736,   635,   747,
     348,  -794,   748,  -794,   749,  -794,   751,   753,  5532,  5532,
    1910,  3424,   157,  -794,    45,  -794,    53,   186,  3654,  5532,
     263,  5655,  -794,  -794,  -794,  -794,  -794,  -794,  5532,    61,
     291,  5532,  -794,  -794,  -794,  -794,  -794,   750,   756,  -794,
     508,   508,  1214,  -794,   761,  -794,   445,   754,  1709,   298,
    -794,   310,  3334,  3334,    10,  -794,  -794,  2277,   257,   770,
     196,  -794,  -794,   572,  -794,   184,  -794,   583,  -794,  -794,
     692,  -794,  -794,  -794,   693,  -794,   184,  -794,  -794,  -794,
      60,   184,  -794,   184,  -794,  -794,   184,  -794,  -794,  -794,
    -794,    60,   184,  -794,   184,  -794,  -794,   184,  -794,  -794,
      60,   184,  -794,   184,  -794,  -794,   184,  -794,  -794,  -794,
    -794,    60,   184,  -794,   184,  -794,  -794,   184,  -794,  -794,
      60,   184,  -794,   184,  -794,  -794,   184,  -794,  -794,  -794,
    -794,    60,   184,  -794,   184,  -794,  -794,   184,  -794,  -794,
     340,   743,  -794,  -794,   138,   138,   138,   138,   750,    36,
     211,  -794,   752,   771,  -794,   773,  -794,  3043,  -794,  -794,
    -794,  -794,   775,  -794,  -794,  -794,  -794,  -794,  -794,  5532,
    5595,  5595,  5595,  5595,  5595,  5595,  5595,  3717,  3777,   340,
    5595,  5595,  5595,  5595,  5595,  5595,  5595,  5595,  -794,   675,
     782,   679,   756,   660,  -794,   407,  -794,  -794,  3840,    69,
     737,  -794,    69,   737,  3900,  -794,   785,  -794,  -794,  5532,
    -794,  -794,  -794,  -794,   774,   787,   794,  -794,   379,  -794,
      65,   797,  -794,   702,  -794,  -794,  -794,  -794,    -6,  -794,
    -794,   292,   799,   808,  -794,   705,  3974,  2081,   790,  -794,
     818,   821,  -794,  -794,   710,   816,  -794,   715,   823,  -794,
    -794,  -794,   833,   357,   340,  4034,  4097,   296,   289,   400,
    -794,  -794,  3334,   828,   834,    37,   731,   293,  -794,  1293,
    2138,  -794,  -794,  -794,  -794,  -794,  -794,  -794,   184,  -794,
    -794,  -794,  -794,  -794,   184,  -794,  -794,  -794,   184,  -794,
    -794,  -794,  -794,  -794,   184,  -794,  -794,  -794,   184,  -794,
    -794,  -794,  -794,  -794,   184,  -794,  -794,  -794,  -794,   340,
    -794,  -794,  -794,  -794,   722,   750,   783,  1336,  -794,  -794,
    -794,  -794,   846,   838,  -794,   839,   695,   712,   713,   708,
     467,   242,   242,  5595,   590,  5595,   590,  -794,   648,   648,
     648,   653,   653,  -794,  -794,  -794,  -794,  4157,   858,   340,
     340,  -794,     4,  -794,   861,  -794,   722,  -794,  -794,   722,
     184,   430,  4220,   868,  3509,  3424,  -794,    72,   106,  4280,
     862,  -794,  -794,  5532,  -794,  -794,  4343,   864,  5763,   872,
    5532,  4403,  6095,  -794,  4466,   879,  -794,  1985,  -794,  -794,
     883,   458,   890,   472,   492,     2,   886,    35,   888,   190,
    -794,  4526,  4589,   780,  -794,  -794,  -794,   484,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -794,   722,  -794,   750,   485,
    -794,  1116,  5595,   590,   590,  -794,   489,  4649,  -794,  -794,
    -794,  -794,  -794,   184,   184,   524,  -794,   895,   915,  1425,
     927,  -794,   863,  -794,   866,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,   832,   939,   837,  -794,   539,  4712,  -794,  -794,
     540,  4772,  3424,   941,   821,  5786,   943,  5846,   952,  -794,
    -794,   545,  4835,  -794,   553,  -794,   953,  -794,   963,  4895,
     965,  4958,   967,  5018,   970,   980,   556,   981,   558,  -794,
    -794,   722,   750,  -794,  -794,  -794,  -794,   559,  -794,  -794,
     184,  5532,  5532,  3509,  5685,  3424,  -794,  5081,   979,  -794,
    -794,   576,  -794,  -794,   578,  -794,  3424,  3424,   982,  3424,
    3424,   983,  5869,  -794,  -794,   599,  -794,  -794,  -794,   992,
     603,  5141,   994,   608,  5204,   996,   610,  5264,  -794,   997,
    -794,   998,   722,  -794,  -794,   991,   995,  -794,  5338,   977,
    1005,  -794,  -794,   612,  5398,  -794,  -794,  -794,  -794,  3424,
    -794,  -794,  3424,  3424,   999,  -794,  -794,  1006,  1009,   623,
    -794,  1010,  1011,   657,  -794,  1013,  1014,   658,  -794,  -794,
    3509,  3509,  5929,  1017,  5532,  5472,  -794,  -794,   664,  -794,
    -794,  -794,  3424,  -794,  -794,  1029,  -794,  -794,  1032,  -794,
    -794,  1033,   962,  -794,  3509,  1028,  5952,  1031,  6012,  1042,
    -794,  -794,  -794,  -794,  -794,  3509,  -794,  3509,  3509,  1037,
    3509,  3509,  1038,  6035,  -794,  -794,  -794,  3509,  -794,  -794,
    3509,  3509,  1045,  -794,  -794,  -794,  3509,  -794
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
       0,     0,     0,     0,     0,     0,   183,     0,   180,    20,
     188,    19,   607,   189,   190,   193,   192,     0,     0,     0,
      48,     0,     0,    52,     0,    54,    55,     7,    10,    11,
      12,    13,    14,    15,    16,   206,   168,     0,   558,     0,
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
     212,   215,   395,     7,   457,     0,     0,     0,   249,   250,
     251,   252,   253,   254,   255,     0,   559,   241,     0,     0,
       0,     0,   441,     0,     0,     0,     0,     0,     0,   166,
     435,   225,   440,     6,    18,     0,   378,   436,     0,   429,
     459,     0,   245,   377,   237,   239,   240,   244,   265,   247,
     248,   238,   246,   460,   461,     0,   462,   463,   448,     0,
     430,   432,   433,     0,     0,   434,   442,   449,   450,     0,
     451,   452,   453,   454,   455,   456,   443,   444,   445,   446,
     447,   490,   491,     0,     0,     0,     0,     0,     0,   196,
     198,   425,   385,   424,     0,     0,     0,   516,     0,     0,
       0,     0,     0,     0,   578,   579,   587,   588,     0,   582,
     583,   584,   585,   586,   580,   581,     0,   593,   594,   595,
     596,   597,   591,   589,   590,   592,     0,     0,    33,     0,
     170,   172,     0,   105,     0,     0,   107,     0,   108,   111,
       0,   112,   114,     0,     0,     0,    63,     0,     0,    67,
       0,    69,    70,   125,     0,     0,     0,   129,     0,     0,
     131,     0,   132,     0,     0,     0,    78,     0,     0,    82,
       0,    84,    85,   141,     0,     0,     0,   145,     0,     0,
     147,     0,   148,     0,     0,     0,    93,     0,     0,    97,
       0,    99,   100,   157,     0,     0,     0,   161,     0,     0,
     163,     0,   164,   184,     0,   181,   191,   194,     0,    42,
      43,    45,    49,     0,     0,     0,     0,     0,     0,     0,
       0,   400,     0,   217,     0,   211,     0,   397,     0,   258,
       0,     0,     0,     0,     0,     0,   379,     0,     0,     0,
     220,   222,   244,   247,   221,   335,   337,   339,   341,   343,
     345,   347,   350,   356,   360,   363,   367,   368,   371,   374,
     380,   381,   355,   379,   378,   245,   246,   372,   373,     0,
       0,     0,   259,     0,    20,   320,   321,     0,     0,     0,
       0,   468,     0,   470,     0,   473,     0,     0,     0,     0,
       0,     0,     0,   256,     0,   257,     0,     0,     0,     0,
       0,     0,   228,   229,   230,   231,   232,   233,     0,     0,
       0,     0,   382,   383,   428,   431,   437,   216,   439,   458,
     402,   399,     0,   406,   403,   404,     0,   241,   225,   224,
     531,   377,     0,     0,     0,   515,   519,     0,     0,     0,
       0,   417,   420,     0,   386,     0,   518,     0,   387,   388,
       0,   389,    35,   174,     0,   103,     0,   104,   106,   110,
       0,     0,    59,     0,    61,    62,     0,    65,    66,    68,
     121,     0,     0,   123,     0,   124,   127,     0,   128,   130,
       0,     0,    74,     0,    76,    77,     0,    80,    81,    83,
     137,     0,     0,   139,     0,   140,   143,     0,   144,   146,
       0,     0,    89,     0,    91,    92,     0,    95,    96,    98,
     153,     0,     0,   155,     0,   156,   159,     0,   160,   162,
       0,   185,    41,   390,     0,     0,     0,     0,   407,     0,
       0,   415,     0,     0,    21,     0,   213,     0,   214,   218,
     219,   263,     0,   262,   369,   370,   376,   375,   243,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   309,     0,
     235,     0,   438,   603,   601,     0,   599,   602,     0,   318,
     316,   327,   319,   317,     0,   277,     0,   474,   466,     0,
     469,   471,   472,   475,     0,     0,     0,   476,     0,   242,
       0,    24,   267,     0,   260,   261,   311,   307,     0,   280,
     278,     0,     0,    25,   266,     0,     0,     0,   511,   513,
       0,   510,   223,   308,     0,   234,   268,     0,     0,   401,
     398,   523,     0,     0,     0,     0,     0,     0,     0,     0,
     530,   529,     0,     0,     0,     0,     0,   216,   419,     0,
       0,   520,   209,   517,   210,   208,   175,   102,     0,    57,
      58,    60,    64,   119,     0,   120,   122,   126,     0,    72,
      73,    75,    79,   135,     0,   136,   138,   142,     0,    87,
      88,    90,    94,   151,     0,   152,   154,   158,   186,     0,
     391,   392,   393,   394,   410,   408,     0,     0,    22,   325,
     323,   330,     0,   324,   264,     0,   338,   340,   342,   344,
     346,   348,   349,     0,   351,     0,   352,   384,   357,   358,
     359,   361,   362,   365,   364,   366,   304,     0,     0,     0,
       0,   604,     0,   598,     0,   314,   312,   328,   315,   313,
     269,     0,     0,     0,     0,     0,   334,     0,     0,     0,
       0,   306,   303,     0,   281,   332,     0,     0,     0,     0,
       0,     0,     0,   302,     0,     0,   333,     0,   524,   405,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     528,     0,     0,     0,   421,   422,   521,     0,   418,    56,
     118,    71,   134,    86,   150,   187,   412,   416,   409,     0,
     322,   326,     0,   354,   353,   294,     0,     0,   605,   606,
     600,   329,   270,   271,   273,     0,   467,     0,     0,   225,
       0,   477,   442,   482,     0,   481,   483,   484,   487,   488,
     489,   310,     0,   236,     0,   282,     0,     0,   279,   286,
       0,     0,     0,     0,   512,     0,     0,     0,     0,   514,
     290,     0,     0,   525,     0,   536,     0,   532,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   423,
     522,   411,   414,   331,   336,   295,   296,     0,   272,   274,
     275,     0,     0,     0,     0,     0,   305,     0,     0,   283,
     284,     0,   287,   288,     0,   492,     0,     0,     0,     0,
       0,     0,     0,   291,   292,     0,   526,   537,   533,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   538,     0,
     534,     0,   413,   297,   276,     0,     0,   485,     0,   511,
       0,   478,   298,     0,     0,   285,   289,   493,   494,     0,
     508,   496,     0,     0,     0,   293,   544,     0,     0,     0,
     540,     0,     0,     0,   548,     0,     0,     0,   539,   535,
       0,     0,     0,     0,     0,     0,   299,   300,     0,   495,
     497,   498,     0,   545,   546,     0,   541,   542,     0,   549,
     550,     0,     0,   486,     0,     0,     0,     0,     0,     0,
     301,   499,   547,   543,   551,     0,   500,     0,     0,     0,
       0,     0,     0,     0,   479,   501,   502,     0,   509,   504,
       0,     0,     0,   503,   505,   506,     0,   507
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -794,  -794,    80,   819,   -54,  -794,  -794,  -496,    26,  1569,
    -794,  -472,  -794,   237,  -794,   239,  -794,   429,  -794,  -794,
    -794,  -383,   -29,   -61,  2274,  -794,   906,   -32,   829,  -794,
     860,  -794,  -794,  1368,  2356,  -794,  2765,  -794,  1997,  -794,
     937,  -794,  -794,  -208,   618,  -551,  -659,  1071,  -794,   -77,
    -794,  -794,   -31,   758,  -794,  -794,  -794,  -143,   114,  -479,
     566,  2045,   259,  -794,  -794,  -326,  -794,   570,  -288,  -794,
    1810,   145,  -794,   398,   403,   397,   404,   406,    24,  -620,
       6,    34,  -179,   395,   544,  -794,   732,   908,  1177,  -794,
     -12,  -125,  -217,  -794,   317,  -101,  -316,  -429,   312,  -794,
      79,  -794,  -794,   122,  -314,  -285,  -794,  -794,  -530,  -243,
    1662,  -321,  -794,  -794,  -446,  -794,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,  -290,  -794,  -794,  -794,  -794,
    -794,  -794,  -794,  -794,  -794,    81,  -793,  -526,  -794,   947,
     971,  -302,  -794,    30,   183,   447,  -794,   873,  -319,  -794,
     238,  -794,  -794,  -210
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,   158,   122,   467,   124,   125,   126,   127,   468,
      91,   453,   265,   266,    14,    15,    16,   267,    18,    25,
      19,   268,    68,   131,    75,   161,   162,    20,   163,    87,
      88,   209,   651,    64,    65,    93,    66,    96,    69,   134,
     135,   136,   137,   229,   230,   231,   668,   740,   470,   471,
     271,   538,   272,   273,   274,   275,   276,   524,   472,   278,
     507,   741,   473,   280,   281,   670,   832,   710,   711,   833,
     282,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     138,   139,   326,   554,   555,   232,   450,   570,   571,   572,
     322,   140,   141,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   953,   954,   955,   956,   957,   309,
     310,   311,   958,   312,   959,   750,   973,   974,   143,   144,
     145,   327,   563,   313,   314,   315,   149,   150,   508,   705,
     706,   707,   861,    94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,   748,   436,   501,   545,   751,   564,   704,   831,   458,
     451,   562,   569,   160,   123,   457,   703,   778,   227,   660,
     123,   330,   333,   338,   565,   356,   511,    26,   513,   576,
      21,   154,   359,   709,   712,   458,   132,   357,   672,   130,
     330,   333,   338,   732,    21,   503,    21,    74,    74,    74,
      74,   744,    74,   270,    74,   503,    74,   497,   498,   776,
     913,   756,   164,   672,   990,    67,   661,   844,   846,   269,
     881,   672,   773,   319,    67,    72,   263,   503,    24,   123,
     123,   503,    27,    67,   774,   749,   548,   665,   503,   130,
     460,    29,   123,   123,   123,   123,   123,   992,   146,   443,
     360,   130,   132,   123,   165,   130,    73,   123,   778,   123,
     130,   123,   123,   123,   575,   325,   662,   459,   882,   155,
     526,   573,   503,   763,   577,   155,   880,    62,    89,   107,
     108,   109,   110,   111,   112,   113,   114,   512,   580,   514,
      74,    74,    74,   525,    74,    74,   673,    74,   121,   164,
     324,   321,    67,   698,   584,    74,    74,    74,    74,   887,
     547,   547,   529,   700,   146,    74,    74,    74,    74,   151,
     123,   734,   123,   503,   123,    74,    74,    74,    74,   735,
     699,   701,  1028,    22,  1031,   753,   824,   499,   530,   715,
     142,   165,   123,   847,    30,   123,   961,    22,    67,    22,
     152,   316,   503,   733,   679,   495,   495,   780,   738,   500,
     262,   745,   270,   317,   121,   550,   551,   781,    27,   728,
     754,   757,   780,   933,   914,   934,   329,   332,   544,   346,
     963,   729,   825,   730,   434,   263,   762,   680,   866,  1074,
     225,   869,    71,   317,   277,   362,   208,    28,   270,   772,
     120,   147,   994,    32,   444,    33,   142,   166,   687,   688,
     130,   323,   736,    70,   560,   520,   520,   -23,   -23,   -20,
     -20,   263,  1003,   783,   123,   506,    67,   545,   539,   503,
     776,   731,    80,   674,   675,   676,   677,   521,   732,   744,
     756,   522,   522,   702,  -379,  -379,   130,   325,    59,  1115,
     540,   130,   325,   883,   130,   503,   449,   503,   449,   130,
     737,   452,   503,   884,   895,   689,   529,   147,   460,   654,
     655,   656,   657,  1129,   526,  1132,   262,   130,    61,    62,
     130,   661,   539,   759,   760,    74,    74,   826,    74,   730,
    1142,    74,   768,    60,   166,  -378,  -378,    81,    61,    62,
     917,   906,    82,   926,   769,    74,    74,    74,   904,    74,
      74,   718,    74,   938,   939,   730,   704,   730,   780,   262,
     729,   -20,   730,   523,   523,    74,    74,    74,   898,    74,
      74,   777,    74,   865,   542,   543,   868,   743,   719,   279,
     123,   123,   123,   123,   123,    74,    74,    74,   929,    74,
      74,   877,    74,   277,   210,   262,    67,   445,   568,   574,
     211,    83,   578,   743,   130,   755,   503,   579,   862,    67,
     731,    59,   867,   878,   863,   867,  -465,   667,  -465,    17,
      84,   495,   495,   495,   495,   581,  -465,    85,   583,   277,
     818,   883,   749,    17,   270,    17,   979,    23,   905,   907,
     909,   943,   323,    60,   270,   323,  1001,    86,    61,    62,
     323,    23,   908,    23,    89,   765,    60,   499,   984,   883,
      95,    61,    62,   494,   494,   153,   730,   263,   323,   986,
    -464,   323,  -464,   883,  1059,   270,   270,   545,   751,   500,
    -464,   950,   130,   988,   212,   780,   780,   129,   123,   213,
     883,   770,   771,   159,   501,  1000,  1002,   224,   263,   263,
    1005,   226,   989,   123,   877,   148,   853,   854,   855,   685,
     686,   167,   653,  -527,   755,   283,  -380,  -380,   659,   749,
    1052,   749,   228,   130,   130,   883,   878,   107,   108,   109,
     110,   111,   112,   113,   114,  1010,   325,   454,   279,   455,
     883,   883,   452,   952,   448,   328,   883,    74,   962,   964,
    1019,  1022,   559,   129,   780,   323,  1033,   883,   749,   883,
     883,   518,    74,    74,  1036,    74,   358,  1049,    74,  1051,
    1053,   148,   456,   454,   279,   782,   749,   883,   433,   883,
     159,   529,    74,    74,   454,    74,   784,  1065,    74,  1066,
    -224,  -224,  -224,  -224,  -224,  -224,   830,   324,   167,   925,
     883,   262,    74,    74,   883,    74,   502,   530,    74,   883,
    1075,   883,   437,   883,  1077,   130,   130,   130,   130,  1081,
     950,  1085,   568,  1096,   883,   277,  -381,  -381,   667,   690,
     691,   692,   262,   262,  1105,   277,   749,   775,   519,   495,
     495,   495,   495,   495,   495,   495,   495,   495,    89,   495,
     495,   495,   495,   495,   495,   495,   495,   527,   883,   883,
     749,   446,   749,   541,   284,   883,   277,   277,  1108,  1111,
     667,   693,   694,   667,   283,  1120,   528,   749,   695,   696,
     697,   531,   952,   123,   546,   270,   848,   849,   850,   494,
     494,   494,   494,   454,   454,   785,   786,   950,   950,   841,
     842,   910,   532,   533,   534,   535,   536,   537,   263,   547,
     283,   859,   860,  1057,   549,   123,   123,   851,   852,   552,
     582,   950,   -20,   820,   821,   822,   823,   650,   663,   664,
     665,   681,   950,   130,   950,   950,   678,   950,   950,   671,
     682,   684,   683,  -277,   950,   708,   714,   950,   950,   715,
     717,   720,   721,   950,   722,    74,   723,   454,   452,   952,
     952,   930,   764,   123,   766,    74,   323,   323,   323,   323,
     279,   779,    34,    35,    36,    74,   819,    37,    38,    39,
     279,   827,   828,   952,   834,   874,   826,   270,   270,   856,
    1112,  1113,   857,   858,   952,   872,   952,   952,   875,   952,
     952,   270,   495,   876,   495,   270,   952,   879,   885,   952,
     952,   279,   279,    40,  1126,   952,   880,   262,   886,   887,
     890,   891,   892,   284,   893,  1134,   894,  1135,  1136,   895,
    1138,  1139,   896,   123,   897,   130,   130,  1143,   911,   931,
    1144,  1145,   262,    63,   912,   915,  1147,   927,    76,   659,
     659,   116,   285,  -226,  -226,  -226,  -226,  -226,  -226,   284,
     107,   108,   109,   110,   111,   112,   113,   114,   937,   932,
     941,   946,   967,    59,   971,   975,   277,   107,   108,   109,
     110,   111,   112,   113,   114,   270,   985,   133,   270,   982,
     270,   495,   667,   987,   999,   566,   991,   659,   993,   178,
     184,   188,   194,   198,   204,  1011,   283,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   283,   494,   494,   494,
     494,   494,   494,   494,   494,  1012,   270,   270,   270,    34,
      35,    36,   119,   130,    37,    38,    39,  1014,  -480,   270,
     270,  1015,   270,   270,   567,   270,  1016,   283,   283,  1017,
     263,  1018,  1026,   133,  1029,  1032,  1037,   107,   108,   109,
     110,   111,   112,   113,   114,   133,  1038,   659,  -227,  -227,
    -227,  -227,  -227,  -227,   130,  1041,   130,  1044,   277,   277,
    1047,    89,   270,  1048,  1050,   270,   270,   130,   130,  1064,
     130,   130,   277,  1069,  1072,  1076,   277,  1080,    89,  1084,
    1088,  1089,  1090,   270,   270,   270,  1091,  1094,  1095,  1103,
    1102,   285,  1104,  1106,  1107,   270,  1109,  1110,   339,   340,
    1116,   279,   341,   342,   343,   344,   345,   270,   286,   270,
     130,   270,  1122,   130,   130,  1123,  1124,  1125,   270,  1127,
     270,   270,  1130,   270,   270,  1133,   270,   285,  1137,  1140,
     270,   130,   130,   270,   270,   284,  1146,   361,   505,   270,
     435,   320,   666,   130,   716,   284,   713,  1004,   836,   838,
     494,   899,   494,   561,   837,   130,   277,   839,    89,   277,
     840,   277,   918,   331,   262,  1060,   130,   447,   130,   130,
     940,   130,   130,     0,   318,     0,   284,   284,   130,     0,
       0,   130,   130,     0,     0,     0,     0,   130,     0,   461,
     108,   109,   110,   111,   112,   113,   114,   277,   277,   277,
      67,     0,     0,   279,   279,     0,   235,     0,     0,     0,
     277,   277,     0,   277,   277,     0,   277,   279,     0,   462,
     463,   279,     0,     0,     0,     0,     0,   464,   465,     0,
       0,     0,     0,   236,   237,     0,     0,   283,     0,   494,
     238,   239,   240,   241,   242,   243,   244,     0,   245,     0,
       0,     0,     0,   277,     0,     0,   277,   277,     0,     0,
     247,   248,   249,     0,     0,     0,     0,   286,     0,     0,
       0,     0,     0,     0,   277,   277,   277,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   277,   107,   108,   109,
     110,   111,   112,   113,   114,     0,   658,     0,   277,     0,
     277,   279,   277,   286,   279,   761,   279,     0,     0,   277,
     466,   277,   277,     0,   277,   277,     0,   277,     0,     0,
       0,   277,     0,   285,   277,   277,     0,     0,     0,     0,
     277,     0,     0,   285,     0,     0,     0,     0,     0,   283,
     283,     0,   279,   279,   279,   567,     0,     0,     0,     0,
       0,     0,     0,   283,   567,   279,   279,   283,   279,   279,
       0,   279,     0,     0,   285,   285,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,   469,   287,     0,     0,
       0,     0,     0,     0,   916,     0,   284,     0,     0,     0,
       0,   509,   510,     0,     0,     0,   516,   517,   279,    89,
       0,   279,   279,     0,     0,     0,     0,     0,    89,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,   279,
     279,   279,     0,    41,    42,    43,     0,   928,    44,    45,
      46,   279,     0,   567,     0,     0,     0,   283,     0,     0,
     283,     0,   283,   279,     0,   279,     0,   279,     0,    47,
       0,     0,    48,     0,   279,     0,   279,   279,     0,   279,
     279,     0,   279,     0,    49,     0,   279,    77,     0,   279,
     279,     0,     0,     0,     0,   279,   567,     0,   283,   283,
     283,     0,     0,     0,     0,     0,     0,    89,   284,   284,
       0,   283,   283,     0,   283,   283,     0,   283,     0,   286,
       0,    97,   284,     0,     0,     0,   284,     0,     0,   286,
       0,     0,     0,   520,   169,   -23,     0,   -20,   179,   185,
     189,   195,   199,   205,     0,     0,     0,     0,     0,     0,
      89,     0,     0,     0,   283,  1013,   287,   283,   283,   522,
     286,   286,  -379,  -379,     0,     0,     0,   107,   108,   109,
     110,   111,   112,   113,   114,   283,   283,   283,     0,     0,
      59,     0,     0,     0,     0,     0,     0,   283,     0,     0,
       0,     0,   287,     0,   285,     0,     0,     0,     0,   283,
       0,   283,     0,   283,     0,     0,   284,     0,     0,   284,
     283,   284,   283,   283,     0,   283,   283,   669,   283,     0,
       0,     0,   283,     0,     0,   283,   283,    34,    35,    36,
       0,   283,    37,    38,    39,     0,   373,     0,     0,   119,
       0,   523,   384,     0,     0,     0,   393,   284,   284,   284,
       0,     0,   404,     0,     0,     0,   413,     0,     0,     0,
     284,   284,   424,   284,   284,     0,   284,     0,    40,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,   724,
     725,   726,     0,     0,     0,     0,     0,     1,   120,     0,
     742,     0,     0,     0,     0,     0,   285,   285,     0,   752,
       0,     0,   758,   284,     0,     0,   284,   284,     0,     0,
     285,     0,     0,     0,   285,     0,     0,     0,     0,    90,
      92,     0,     0,     0,   284,   284,   284,   128,     0,     0,
       0,     0,     0,   128,     0,     0,   284,     2,     3,     4,
       0,   316,     5,     6,     7,     0,     0,     0,   284,     0,
     284,     0,   284,     0,     0,     0,     0,     0,     0,   284,
       0,   284,   284,     8,   284,   284,     9,   284,     0,     0,
     286,   284,    10,     0,   284,   284,     0,     0,    11,     0,
     284,     0,     0,     0,     0,     0,     0,     0,   287,   264,
      89,     0,   128,   128,   285,     0,     0,   285,   287,   285,
       0,    12,     0,     0,     0,   128,   128,   128,   128,   128,
       0,     0,     0,     0,     0,     0,   128,   520,     0,   -23,
     128,   -20,   128,     0,   128,   128,   128,     0,   669,   287,
     287,     0,     0,     0,     0,   285,   285,   285,     0,   521,
     835,     0,     0,   767,     0,     0,  -379,  -379,   285,   285,
       0,   285,   285,     0,   285,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,   128,    59,   864,
       0,    92,   286,   286,     0,     0,     0,     0,     0,     0,
     873,     0,     0,   128,     0,   128,   286,   128,     0,     0,
     286,   285,     0,     0,   285,   285,     0,   107,   108,   109,
     110,   111,   112,   113,   114,   128,     0,   889,   128,     0,
     503,     0,   285,   285,   285,    34,    35,    36,     0,     0,
      37,    38,    39,   -20,   285,   523,     0,   119,   107,   108,
     109,   110,   111,   112,   113,   114,   285,     0,   285,     0,
     285,    59,     0,     0,     0,     0,     0,   285,   264,   285,
     285,     0,   285,   285,     0,   285,     0,     0,     0,   285,
       0,     0,   285,   285,     0,     0,     0,     0,   285,     0,
     286,     0,     0,   286,     0,   286,    89,     0,     0,     0,
       0,     0,     0,   553,   264,     0,     0,   128,    50,    51,
      52,     0,     0,    53,    54,    55,   334,   335,     0,     0,
     119,     0,     0,   461,   108,   109,   110,   111,   112,   113,
     114,   286,   286,   286,    56,   336,   337,    57,   504,   671,
     235,     0,     0,     0,   286,   286,     0,   286,   286,    58,
     286,     0,     0,   462,   463,     0,     0,     0,     0,   287,
       0,   464,   465,     0,   968,     0,     0,   236,   237,    89,
       0,   976,   978,     0,   238,   239,   240,   241,   242,   243,
     244,     0,   245,     0,     0,     0,     0,   286,     0,     0,
     286,   286,     0,     0,   247,   248,   249,     0,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,   286,   286,
     286,     0,   669,     0,     0,     0,   983,     0,     0,     0,
     286,     0,     0,   128,   128,   128,   128,   128,     0,     0,
       0,     0,   286,     0,   286,     0,   286,     0,     0,     0,
       0,     0,     0,   286,   466,   286,   286,     0,   286,   286,
       0,   286,     0,     0,     0,   286,   496,   496,   286,   286,
       0,   287,   287,     0,   286,   567,     0,     0,     0,     0,
     100,   103,   105,   106,     0,   287,     0,     0,     0,   287,
       0,     0,   128,     0,     0,     0,     0,   182,     0,   192,
       0,   202,  1055,  1056,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,   216,   218,   219,     0,   221,   222,
     264,   223,     0,     0,     0,     0,     0,     0,     0,    89,
     107,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,   128,     0,     0,     0,     0,     0,   448,     0,  1093,
       0,   264,   264,    41,    42,    43,   128,     0,    44,    45,
      46,   107,   108,   109,   110,   111,   112,   113,   114,   287,
       0,     0,   287,     0,   287,     0,     0,     0,     0,    47,
     252,     0,    48,     0,     0,  1117,  1119,   107,   108,   109,
     110,   111,   112,   113,   114,   376,   379,   381,   382,     0,
      59,     0,     0,   727,     0,   396,   399,   401,   402,     0,
     287,   287,   287,     0,     0,   416,   419,   421,   422,     0,
       0,     0,     0,   287,   287,    89,   287,   287,   567,   287,
       0,   439,   440,     0,   441,     0,     0,   442,     0,    92,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
       0,    89,    53,    54,    55,    50,    51,    52,     0,   119,
      53,    54,    55,     0,     0,     0,   287,     0,     0,   287,
     287,     0,     0,    56,   336,   337,    57,     0,   128,     0,
       0,    56,    89,     0,    57,     0,     0,   287,   287,   287,
       0,     0,   496,   496,   496,   496,    58,     0,     0,   287,
     107,   108,   109,   110,   111,   112,   113,   114,    89,     0,
       0,   287,     0,   287,     0,   287,     0,     0,     0,     0,
       0,     0,   287,     0,   287,   287,     0,   287,   287,     0,
     287,     0,     0,     0,   287,     0,   128,   287,   287,     0,
       0,     0,     0,   287,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   553,     0,     0,     0,     0,    50,    51,
      52,   264,     0,    53,    54,    55,     0,     0,   128,   128,
     168,   172,   175,   177,     0,   183,     0,   193,     0,   203,
       0,     0,     0,     0,    56,     0,     0,    57,     0,     0,
     592,   594,   595,     0,   597,   598,     0,   599,     0,     0,
       0,     0,     0,     0,     0,    78,     0,     0,    92,     0,
     612,   614,   615,     0,   617,   618,   128,   619,     0,     0,
       0,    89,     0,     0,     0,     0,     0,     0,     0,     0,
     632,   634,   635,     0,   637,   638,     0,   639,     0,    98,
     101,     0,     0,     0,     0,     0,     0,     0,   128,   128,
       0,   128,   170,   173,     0,   652,   180,   186,   190,   196,
     200,   206,     0,   363,   366,   368,     0,   369,   371,     0,
     372,     0,     0,   214,     0,     0,     0,     0,   383,   387,
     390,   392,     0,     0,     0,     0,   128,     0,   403,   407,
     410,   412,     0,   520,     0,   -23,     0,   -20,   423,   427,
     430,   432,  -225,  -225,  -225,  -225,  -225,  -225,     0,     0,
     496,   496,   496,   496,   496,   496,   496,   496,   496,   522,
     496,   496,   496,   496,   496,   496,   496,   496,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,   115,    67,
     116,    59,     0,     0,     0,   364,     0,     0,     0,     0,
     117,     0,     0,     0,   374,   377,   951,   960,     0,     0,
     385,   388,     0,     0,   394,   397,     0,     0,     0,     0,
     405,   408,     0,     0,   414,   417,     0,     0,     0,     0,
     425,   428,     0,     0,     0,     0,     1,     0,     2,     3,
       4,     0,     0,     5,   118,     7,     0,     0,     0,   -20,
     119,   523,     0,   264,     0,     0,     0,   789,   790,     0,
     791,     0,     0,   792,     8,     0,     0,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   799,   800,    11,
     801,     0,     0,   802,     0,     0,     2,     3,     4,     0,
       0,     5,     6,     7,     0,     0,     0,   809,   810,   120,
     811,     0,     0,   812,  1025,     0,     0,     0,   585,   587,
       0,   588,     8,     0,   589,     9,     0,     0,     0,     0,
       0,    10,     0,   496,     0,   496,     0,    11,   600,   603,
     605,     0,   606,   608,     0,   609,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   727,     0,  1061,   620,   623,
     625,     0,   626,   628,     0,   629,     0,     0,  1067,  1068,
       0,  1070,  1071,     0,     0,     0,     0,     0,   640,   643,
     645,     0,   646,   648,     0,   649,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,     0,     0,    59,     0,     0,     0,   590,
       0,  1099,     0,     0,  1100,  1101,     0,     0,     0,     0,
     601,     0,   496,     0,     0,     0,     0,     0,     0,   610,
       0,     0,   951,   960,     0,     0,     0,     0,     0,   871,
     621,     0,     0,     0,  1121,     0,     0,     0,     0,   630,
       0,     0,    41,    42,    43,     0,  1025,    44,    45,    46,
     641,     0,     0,     0,   119,   919,     0,  1061,     0,  1067,
    1068,     0,  1070,  1071,    79,   921,     0,     0,    47,  1099,
       0,    48,  1100,  1101,     0,   923,     0,     0,  1121,     0,
     901,   903,     0,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,   102,
     104,     0,     0,    89,     1,     0,     0,     0,     0,     0,
       0,   171,   174,   176,     0,   181,   187,   191,   197,   201,
     207,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     787,     0,   215,   217,     0,     0,   220,   942,     0,     0,
       0,     0,     0,     0,     0,   793,   795,     0,   796,     0,
       0,   797,     0,     0,     2,     3,     4,     0,     0,     5,
       6,     7,     0,     0,     0,   803,   805,     0,   806,     0,
       0,   807,   936,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     0,     9,     0,   813,   815,   945,   816,    10,
       0,   817,     0,     0,   966,    11,     0,     0,     0,     0,
       0,   970,     0,     0,   365,   367,     0,     0,   370,   981,
    1008,  1009,     0,   375,   378,   380,     0,     0,    31,   386,
     389,   391,     0,   395,   398,   400,   996,   998,     0,   406,
     409,   411,     0,   415,   418,   420,     0,     0,     0,   426,
     429,   431,     0,     0,     0,     0,     0,     0,     0,   438,
       0,     0,  1007,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1054,     0,     0,
       0,     0,  1021,     0,     0,     0,  1024,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1035,     0,     0,
       0,     0,     0,     0,  1040,     0,  1043,     0,  1046,     0,
       0,     0,     0,     0,     0,     0,   461,   108,   109,   110,
     111,   112,   113,   114,   829,     0,     0,    67,   116,     0,
       0,     0,  1063,   235,     0,     0,     0,     0,   920,     0,
       0,     0,     0,     0,     0,     0,   462,   463,   922,     0,
       0,     0,     0,     0,   464,   465,  1079,     0,   924,  1083,
     236,   237,  1087,     0,     0,     0,     0,   238,   239,   240,
     241,   242,   243,   244,     0,   245,     0,     0,     0,  1098,
       0,     0,     0,     0,     0,     0,     0,   247,   248,   249,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   586,
       0,     0,     0,     0,     0,     0,     0,     0,   591,   593,
       0,     0,   596,     0,     0,     0,     0,     0,     0,   602,
     604,     0,     0,   607,     0,     0,     0,     0,   611,   613,
       0,     0,   616,     0,     0,     0,     0,   466,     0,   622,
     624,     0,     0,   627,     0,     0,     0,     0,   631,   633,
       0,     0,   636,     0,     0,     0,     0,     0,     0,   642,
     644,     0,     0,   647,   233,   108,   109,   110,   111,   112,
     113,   114,     0,     0,   234,    67,   116,   503,     0,     0,
       0,   235,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     107,   108,   109,   110,   111,   112,   113,   114,   236,   237,
     156,     0,   116,    59,     0,   238,   239,   240,   241,   242,
     243,   244,   117,   556,     2,     3,     4,     0,     0,     5,
       6,   246,     0,     0,     0,   557,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,     0,   258,   259,   260,
       8,     0,     0,     9,     0,     0,     0,     0,     0,     0,
       2,     3,     4,     0,     0,     5,     6,     7,     0,     0,
       0,     0,   119,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   558,     8,     0,     0,     9,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   233,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   234,    67,   116,
       0,    89,     0,     0,   235,   788,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   794,     0,     0,     0,
       0,     0,     0,     0,     0,   798,     0,     0,     0,     0,
       0,   236,   237,     0,     0,     0,   804,     0,   238,   239,
     240,   241,   242,   243,   244,   808,   245,     2,     3,     4,
       0,     0,     5,     6,   246,     0,   814,     0,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,     0,
     258,   259,   260,     8,     0,     0,     9,   461,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   234,    67,     0,
       0,     0,     0,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   261,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   247,   248,
     249,   250,   251,     0,   253,   254,   255,   256,   257,     0,
     258,   259,   461,   108,   109,   110,   111,   112,   113,   114,
       0,     0,   234,    67,     0,     0,     0,     0,     0,   235,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   261,     0,
       0,     0,     0,     0,     0,     0,   236,   237,     0,     0,
       0,     0,     0,   238,   239,   240,   241,   242,   243,   244,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   247,   248,   249,   250,   251,     0,   253,
     254,   255,   256,   947,     0,   948,   259,   461,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   515,     0,     0,
       0,     0,     0,     0,   235,     0,     0,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   462,   463,     0,
      59,     0,     0,   949,     0,   464,   465,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,   461,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,   247,   248,
     249,     0,     0,     0,   235,   739,     0,     0,   347,   348,
       0,     0,   349,   350,   351,     0,     0,   462,   463,   119,
       0,     0,     0,     0,     0,   464,   465,     0,     0,     0,
       0,   236,   237,   352,   353,   354,   355,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,     0,   466,     0,
     461,   108,   109,   110,   111,   112,   113,   114,   247,   248,
     249,     0,     0,     0,     0,     0,     0,   235,    89,     0,
       0,     0,     0,     0,   843,     0,     0,     0,     0,     0,
     462,   463,     0,     0,     0,     0,     0,     0,   464,   465,
       0,     0,     0,     0,   236,   237,     0,     0,     0,     0,
       0,   238,   239,   240,   241,   242,   243,   244,   466,   245,
     461,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,   247,   248,   249,     0,     0,     0,   235,     0,     0,
       0,     0,     0,     0,   845,     0,     0,     0,     0,     0,
     462,   463,     0,     0,     0,     0,     0,     0,   464,   465,
       0,     0,     0,     0,   236,   237,     0,     0,     0,     0,
       0,   238,   239,   240,   241,   242,   243,   244,     0,   245,
       0,   493,     0,   461,   108,   109,   110,   111,   112,   113,
     114,   247,   248,   249,     0,     0,     0,     0,     0,   664,
     235,     0,     0,     0,   107,   108,   109,   110,   111,   112,
     113,   114,     0,   462,   463,     0,     0,    59,     0,     0,
       0,   464,   465,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,   493,   245,   461,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,   247,   248,   249,     0,     0,     0,
     235,   870,     0,     0,     0,    51,    52,     0,     0,    53,
      54,    55,     0,   462,   463,     0,   119,     0,     0,     0,
       0,   464,   465,     0,     0,     0,     0,   236,   237,     0,
      56,   336,   337,    57,   238,   239,   240,   241,   242,   243,
     244,     0,   245,     0,   466,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   247,   248,   249,   461,   108,   109,
     110,   111,   112,   113,   114,    89,     0,   888,     0,     0,
       0,     0,     0,     0,   235,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   113,   114,     0,   462,   463,     0,
       0,    59,     0,     0,     0,   464,   465,     0,     0,     0,
       0,   236,   237,     0,   466,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,   461,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,   247,   248,
     249,     0,     0,     0,   235,   900,     0,     0,    41,    42,
      43,     0,     0,    44,    45,    46,     0,   462,   463,     0,
     119,     0,     0,     0,     0,   464,   465,     0,     0,     0,
       0,   236,   237,     0,    47,     0,     0,    48,   238,   239,
     240,   241,   242,   243,   244,     0,   245,     0,   466,     0,
     461,   108,   109,   110,   111,   112,   113,   114,   247,   248,
     249,     0,     0,     0,     0,     0,     0,   235,   902,    89,
       0,   107,   108,   109,   110,   111,   112,   113,   114,     0,
     462,   463,     0,     0,    59,     0,     0,     0,   464,   465,
       0,     0,     0,     0,   236,   237,     0,     0,     0,     0,
       0,   238,   239,   240,   241,   242,   243,   244,   466,   245,
     461,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,   247,   248,   249,     0,     0,     0,   235,   935,     0,
       0,     0,     3,     4,     0,     0,     5,     6,     7,     0,
     462,   463,     0,   119,     0,     0,     0,     0,   464,   465,
       0,     0,     0,     0,   236,   237,     0,     8,     0,     0,
       9,   238,   239,   240,   241,   242,   243,   244,     0,   245,
       0,   466,     0,   461,   108,   109,   110,   111,   112,   113,
     114,   247,   248,   249,     0,     0,     0,     0,     0,     0,
     235,   944,    89,     0,   107,   108,   109,   110,   111,   112,
     113,   114,     0,   462,   463,     0,     0,    59,     0,     0,
       0,   464,   465,     0,     0,     0,     0,   236,   237,     0,
       0,     0,     0,     0,   238,   239,   240,   241,   242,   243,
     244,   466,   245,   461,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,   247,   248,   249,     0,     0,     0,
     235,   965,     0,     0,     0,    42,    43,     0,     0,    44,
      45,    46,     0,   462,   463,     0,   119,     0,     0,     0,
       0,   464,   465,     0,     0,     0,     0,   236,   237,     0,
      47,     0,     0,    48,   238,   239,   240,   241,   242,   243,
     244,     0,   245,     0,   466,     0,   461,   108,   109,   110,
     111,   112,   113,   114,   247,   248,   249,     0,     0,     0,
       0,     0,     0,   235,   969,    89,     0,   107,   108,   109,
     110,   111,   112,   113,   114,     0,   462,   463,     0,     0,
      59,     0,     0,     0,   464,   465,     0,     0,     0,     0,
     236,   237,     0,     0,     0,     0,     0,   238,   239,   240,
     241,   242,   243,   244,   466,   245,   461,   108,   109,   110,
     111,   112,   113,   114,     0,     0,   977,   247,   248,   249,
       0,     0,     0,   235,     0,     0,     0,     0,    35,    36,
       0,     0,    37,    38,    39,     0,   462,   463,     0,   119,
       0,     0,     0,     0,   464,   465,     0,     0,     0,     0,
     236,   237,     0,     0,     0,     0,     0,   238,   239,   240,
     241,   242,   243,   244,     0,   245,     0,   466,     0,   461,
     108,   109,   110,   111,   112,   113,   114,   247,   248,   249,
       0,     0,     0,     0,     0,     0,   235,   980,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   462,
     463,     0,     0,     0,     0,     0,     0,   464,   465,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,   466,   245,   461,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
     247,   248,   249,     0,     0,     0,   235,   995,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   462,
     463,     0,     0,     0,     0,     0,     0,   464,   465,     0,
       0,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,     0,
     466,     0,   461,   108,   109,   110,   111,   112,   113,   114,
     247,   248,   249,     0,     0,     0,     0,     0,     0,   235,
     997,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   462,   463,     0,     0,     0,     0,     0,     0,
     464,   465,     0,     0,     0,     0,   236,   237,     0,     0,
       0,     0,     0,   238,   239,   240,   241,   242,   243,   244,
     466,   245,   461,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,   247,   248,   249,     0,     0,     0,   235,
    1006,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   462,   463,     0,     0,     0,     0,     0,     0,
     464,   465,     0,     0,     0,     0,   236,   237,     0,     0,
       0,     0,     0,   238,   239,   240,   241,   242,   243,   244,
       0,   245,     0,   466,     0,   461,   108,   109,   110,   111,
     112,   113,   114,   247,   248,   249,     0,     0,     0,     0,
       0,     0,   235,  1020,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   462,   463,     0,     0,     0,
       0,     0,     0,   464,   465,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,   466,   245,   461,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   247,   248,   249,     0,
       0,     0,   235,  1023,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   462,   463,     0,     0,     0,
       0,     0,     0,   464,   465,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,     0,   466,     0,   461,   108,
     109,   110,   111,   112,   113,   114,   247,   248,   249,     0,
       0,     0,     0,     0,     0,   235,  1034,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   462,   463,
       0,     0,     0,     0,     0,     0,   464,   465,     0,     0,
       0,     0,   236,   237,     0,     0,     0,     0,     0,   238,
     239,   240,   241,   242,   243,   244,   466,   245,   461,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,   247,
     248,   249,     0,     0,     0,   235,  1039,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   462,   463,
       0,     0,     0,     0,     0,     0,   464,   465,     0,     0,
       0,     0,   236,   237,     0,     0,     0,     0,     0,   238,
     239,   240,   241,   242,   243,   244,     0,   245,     0,   466,
       0,   461,   108,   109,   110,   111,   112,   113,   114,   247,
     248,   249,     0,     0,     0,     0,     0,     0,   235,  1042,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   462,   463,     0,     0,     0,     0,     0,     0,   464,
     465,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,   466,
     245,   461,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,   247,   248,   249,     0,     0,     0,   235,  1045,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   462,   463,     0,     0,     0,     0,     0,     0,   464,
     465,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,     0,
     245,     0,   466,     0,   461,   108,   109,   110,   111,   112,
     113,   114,   247,   248,   249,     0,     0,     0,     0,     0,
       0,   235,  1062,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   462,   463,     0,     0,     0,     0,
       0,     0,   464,   465,     0,     0,     0,     0,   236,   237,
       0,     0,     0,     0,     0,   238,   239,   240,   241,   242,
     243,   244,   466,   245,   461,   108,   109,   110,   111,   112,
     113,   114,     0,     0,     0,   247,   248,   249,     0,     0,
       0,   235,  1078,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   462,   463,     0,     0,     0,     0,
       0,     0,   464,   465,     0,     0,     0,     0,   236,   237,
       0,     0,     0,     0,     0,   238,   239,   240,   241,   242,
     243,   244,     0,   245,     0,   466,     0,   461,   108,   109,
     110,   111,   112,   113,   114,   247,   248,   249,     0,     0,
       0,     0,     0,     0,   235,  1082,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   462,   463,     0,
       0,     0,     0,     0,     0,   464,   465,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,   466,   245,   461,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,   247,   248,
     249,     0,     0,     0,   235,  1086,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   462,   463,     0,
       0,     0,     0,     0,     0,   464,   465,     0,     0,     0,
       0,   236,   237,     0,     0,     0,     0,     0,   238,   239,
     240,   241,   242,   243,   244,     0,   245,     0,   466,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   247,   248,
     249,   461,   108,   109,   110,   111,   112,   113,   114,     0,
       0,  1092,     0,     0,     0,     0,     0,     0,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   462,   463,     0,     0,     0,     0,     0,     0,   464,
     465,     0,     0,     0,     0,   236,   237,     0,   466,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,     0,
     245,   461,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,   247,   248,   249,     0,     0,     0,   235,  1097,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   462,   463,     0,     0,     0,     0,     0,     0,   464,
     465,     0,     0,     0,     0,   236,   237,     0,     0,     0,
       0,     0,   238,   239,   240,   241,   242,   243,   244,     0,
     245,     0,   466,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   247,   248,   249,   461,   108,   109,   110,   111,
     112,   113,   114,     0,     0,  1118,     0,     0,     0,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   462,   463,     0,     0,     0,
       0,     0,     0,   464,   465,     0,     0,     0,     0,   236,
     237,     0,   466,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,   461,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   247,   248,   249,     0,
       0,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   462,   463,     0,     0,     0,
       0,     0,     0,   464,   465,     0,     0,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,     0,   466,     0,   461,   108,
     109,   110,   111,   112,   113,   114,   247,   248,   249,     0,
       0,     0,     0,     0,     0,   235,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   462,   463,
       0,     0,     0,     0,     0,     0,   464,   465,     0,     0,
       0,     0,   236,   237,     0,     0,     0,     0,     0,   238,
     239,   240,   241,   242,   243,   244,   466,   245,   233,   108,
     109,   110,   111,   112,   113,   114,     0,     0,   746,   247,
     248,   249,     0,     0,     0,   235,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   233,   108,
     109,   110,   111,   112,   113,   114,     0,     0,  1058,     0,
       0,     0,   236,   237,     0,   235,     0,     0,     0,   238,
     239,   240,   241,   242,   243,   244,     0,   245,     0,   493,
       0,     0,     0,     0,     0,   747,     0,     0,     0,   247,
     248,   249,   236,   237,   252,     0,     0,     0,     0,   238,
     239,   240,   241,   242,   243,   244,     0,   245,     0,     0,
       0,     0,     0,     0,     0,   747,     0,     0,     0,   247,
     248,   249,     0,     0,   252,     0,   461,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,     0,     0,   466,
       0,     0,     0,   235,   972,     0,     0,     0,     0,   461,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   235,  1027,     0,   466,
     236,   237,     0,     0,     0,     0,     0,   238,   239,   240,
     241,   242,   243,   244,     0,   245,     0,     0,     0,     0,
       0,     0,     0,   236,   237,     0,     0,   247,   248,   249,
     238,   239,   240,   241,   242,   243,   244,     0,   245,   461,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
     247,   248,   249,     0,     0,     0,   235,  1030,     0,     0,
       0,     0,   461,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,     0,     0,     0,     0,   466,     0,   235,
    1073,     0,     0,   236,   237,     0,     0,     0,     0,     0,
     238,   239,   240,   241,   242,   243,   244,     0,   245,     0,
     466,     0,     0,     0,     0,     0,   236,   237,     0,     0,
     247,   248,   249,   238,   239,   240,   241,   242,   243,   244,
       0,   245,   461,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,   247,   248,   249,     0,     0,     0,   235,
    1114,     0,     0,     0,     0,   461,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
     466,     0,   235,  1128,     0,     0,   236,   237,     0,     0,
       0,     0,     0,   238,   239,   240,   241,   242,   243,   244,
       0,   245,     0,   466,     0,     0,     0,     0,     0,   236,
     237,     0,     0,   247,   248,   249,   238,   239,   240,   241,
     242,   243,   244,     0,   245,   461,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   247,   248,   249,     0,
       0,     0,   235,  1131,     0,     0,     0,     0,   461,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,   466,     0,   235,  1141,     0,     0,   236,
     237,     0,     0,     0,     0,     0,   238,   239,   240,   241,
     242,   243,   244,     0,   245,     0,   466,     0,     0,     0,
       0,     0,   236,   237,     0,     0,   247,   248,   249,   238,
     239,   240,   241,   242,   243,   244,     0,   245,   461,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,   247,
     248,   249,     0,     0,     0,   235,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   466,     0,     0,     0,
       0,     0,   236,   237,     0,     0,     0,     0,     0,   238,
     239,   240,   241,   242,   243,   244,     0,   245,     0,   466,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   247,
     248,   249,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   466
};

static const yytype_int16 yycheck[] =
{
      29,   531,   212,   246,   289,   531,   325,   503,   667,    18,
     227,   325,   328,    74,    68,   232,    12,   568,   119,   448,
      74,   146,   147,   148,   326,   150,    13,    69,    13,   331,
       0,    36,   157,   505,   506,    18,    68,    36,    18,    68,
     165,   166,   167,   522,    14,    16,    16,    76,    77,    78,
      79,   530,    81,   130,    83,    16,    85,   236,   237,    23,
      23,   540,    74,    18,    62,    14,    74,   687,   688,   130,
      76,    18,    62,   134,    14,    13,   130,    16,   124,   133,
     134,    16,   124,    14,    74,   531,   294,    18,    16,   118,
     233,   124,   146,   147,   148,   149,   150,    62,    68,   224,
     161,   130,   134,   157,    74,   134,    44,   161,   659,   163,
     139,   165,   166,   167,   331,   144,   124,   126,   124,   124,
     263,   329,    16,   552,   332,   124,   124,    67,   124,     3,
       4,     5,     6,     7,     8,     9,    10,   124,   346,   124,
     169,   170,   171,   126,   173,   174,   126,   176,    68,   161,
      99,    13,    14,   124,   362,   184,   185,   186,   187,   124,
     124,   124,    18,   124,   134,   194,   195,   196,   197,    13,
     224,   126,   226,    16,   228,   204,   205,   206,   207,   126,
     499,   500,   975,     0,   977,   124,   658,    22,    44,   124,
      68,   161,   246,   689,     0,   249,   124,    14,    14,    16,
      44,    75,    16,   522,    12,   236,   237,    11,   527,    44,
     130,   530,   289,   133,   134,   316,   317,    21,   124,    62,
     539,   540,    11,   843,   775,   845,   146,   147,   289,   149,
     124,    74,    21,    76,   208,   289,   552,    45,   710,  1032,
     118,   713,    44,   163,   130,   165,    61,    10,   325,   563,
     124,    68,    62,    14,   224,    16,   134,    74,    16,    17,
     289,   139,    76,    26,   325,    18,    18,    20,    20,    22,
      22,   325,   931,   575,   328,   249,    14,   562,    22,    16,
      23,   124,   124,   462,   463,   464,   465,    40,   767,   768,
     769,    44,    44,   501,    47,    48,   325,   326,    16,  1092,
      44,   330,   331,    11,   333,    16,   226,    16,   228,   338,
     124,    18,    16,    21,   124,    73,    18,   134,   461,   444,
     445,   446,   447,  1116,   467,  1118,   246,   356,    66,    67,
     359,    74,    22,   550,   551,   364,   365,    44,   367,    76,
    1133,   370,    44,    61,   161,    47,    48,   124,    66,    67,
     779,    62,   124,   825,    44,   384,   385,   386,    62,   388,
     389,    13,   391,   859,   860,    76,   862,    76,    11,   289,
      74,   124,    76,   126,   126,   404,   405,   406,    21,   408,
     409,   124,   411,   709,    47,    48,   712,   124,    40,   130,
     444,   445,   446,   447,   448,   424,   425,   426,   827,   428,
     429,    22,   431,   289,    11,   325,    14,   224,   328,   330,
      17,   124,   333,   124,   443,   124,    16,   338,    11,    14,
     124,    16,   710,    44,    17,   713,    11,   456,    13,     0,
     124,   462,   463,   464,   465,   356,    21,   124,   359,   325,
     650,    11,   888,    14,   521,    16,   892,     0,   767,   768,
     769,    21,   330,    61,   531,   333,   928,   124,    66,    67,
     338,    14,    62,    16,   124,    20,    61,    22,   897,    11,
     124,    66,    67,   236,   237,   124,    76,   531,   356,    21,
      11,   359,    13,    11,  1014,   562,   563,   772,  1014,    44,
      21,   874,   521,    21,    11,    11,    11,    68,   552,    11,
      11,   562,   563,    74,   747,    21,    21,    26,   562,   563,
      21,   124,    20,   567,    22,    68,   695,   696,   697,    52,
      53,    74,   443,    20,   124,   130,    47,    48,   448,   975,
    1002,   977,   124,   562,   563,    11,    44,     3,     4,     5,
       6,     7,     8,     9,    10,    21,   575,    11,   289,    13,
      11,    11,    18,   874,    20,    20,    11,   586,   877,   878,
      21,    21,   325,   134,    11,   443,    21,    11,  1014,    11,
      11,    20,   601,   602,    21,   604,    13,    21,   607,    21,
      21,   134,    27,    11,   325,    13,  1032,    11,   124,    11,
     161,    18,   621,   622,    11,   624,    13,    21,   627,    21,
      27,    28,    29,    30,    31,    32,   667,    99,   161,   819,
      11,   531,   641,   642,    11,   644,   126,    44,   647,    11,
      21,    11,   124,    11,    21,   654,   655,   656,   657,    21,
    1013,    21,   552,    21,    11,   521,    47,    48,   667,    49,
      50,    51,   562,   563,    21,   531,  1092,   567,    20,   680,
     681,   682,   683,   684,   685,   686,   687,   688,   124,   690,
     691,   692,   693,   694,   695,   696,   697,    22,    11,    11,
    1116,   224,  1118,    18,   130,    11,   562,   563,    21,    21,
     709,    33,    34,   712,   289,    21,    20,  1133,    35,    36,
      37,    20,  1013,   747,    13,   772,   690,   691,   692,   462,
     463,   464,   465,    11,    11,    13,    13,  1090,  1091,   685,
     686,   772,    27,    28,    29,    30,    31,    32,   772,   124,
     325,    61,    62,  1013,    13,   779,   780,   693,   694,    20,
      13,  1114,    43,   654,   655,   656,   657,    43,    11,    19,
      18,    46,  1125,   772,  1127,  1128,    21,  1130,  1131,    19,
      38,    43,    39,    20,  1137,    18,    20,  1140,  1141,   124,
      13,    13,    13,  1146,    13,   794,    13,    11,    18,  1090,
    1091,   832,    11,   827,    20,   804,   654,   655,   656,   657,
     521,    11,    63,    64,    65,   814,    43,    68,    69,    70,
     531,    20,    19,  1114,    19,    21,    44,   874,   875,   124,
    1090,  1091,    20,   124,  1125,    20,  1127,  1128,    21,  1130,
    1131,   888,   843,    19,   845,   892,  1137,    20,    19,  1140,
    1141,   562,   563,   104,  1114,  1146,   124,   747,    20,   124,
      40,    13,    11,   289,   124,  1125,    20,  1127,  1128,   124,
    1130,  1131,    19,   897,    11,   874,   875,  1137,    20,    11,
    1140,  1141,   772,    24,    20,   124,  1146,    74,    29,   779,
     780,    15,   130,    27,    28,    29,    30,    31,    32,   325,
       3,     4,     5,     6,     7,     8,     9,    10,    20,    40,
      19,    13,    20,    16,    20,    13,   772,     3,     4,     5,
       6,     7,     8,     9,    10,   972,    13,    68,   975,    20,
     977,   932,   931,    13,   124,    21,    20,   827,    20,    80,
      81,    82,    83,    84,    85,    20,   521,   680,   681,   682,
     683,   684,   685,   686,   687,   688,   531,   690,   691,   692,
     693,   694,   695,   696,   697,    20,  1013,  1014,  1015,    63,
      64,    65,    75,   972,    68,    69,    70,    20,    85,  1026,
    1027,    85,  1029,  1030,    70,  1032,   124,   562,   563,    20,
    1014,   124,    21,   134,    21,    13,    13,     3,     4,     5,
       6,     7,     8,     9,    10,   146,    13,   897,    27,    28,
      29,    30,    31,    32,  1013,    20,  1015,    20,   874,   875,
      20,   124,  1069,    13,    13,  1072,  1073,  1026,  1027,    20,
    1029,  1030,   888,    21,    21,    13,   892,    13,   124,    13,
      13,    13,    21,  1090,  1091,  1092,    21,    40,    13,    13,
      21,   289,    13,    13,    13,  1102,    13,    13,    64,    65,
      13,   772,    68,    69,    70,    71,    72,  1114,   130,  1116,
    1069,  1118,    13,  1072,  1073,    13,    13,    85,  1125,    21,
    1127,  1128,    21,  1130,  1131,    13,  1133,   325,    21,    21,
    1137,  1090,  1091,  1140,  1141,   521,    21,   161,   249,  1146,
     210,   134,   454,  1102,   508,   531,   506,   932,   680,   682,
     843,   764,   845,   325,   681,  1114,   972,   683,   124,   975,
     684,   977,   780,   146,  1014,  1014,  1125,   224,  1127,  1128,
     862,  1130,  1131,    -1,   133,    -1,   562,   563,  1137,    -1,
      -1,  1140,  1141,    -1,    -1,    -1,    -1,  1146,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,  1013,  1014,  1015,
      14,    -1,    -1,   874,   875,    -1,    20,    -1,    -1,    -1,
    1026,  1027,    -1,  1029,  1030,    -1,  1032,   888,    -1,    33,
      34,   892,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,   772,    -1,   932,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,    -1,  1069,    -1,    -1,  1072,  1073,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,   289,    -1,    -1,
      -1,    -1,    -1,    -1,  1090,  1091,  1092,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,  1102,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    21,    -1,  1114,    -1,
    1116,   972,  1118,   325,   975,    21,   977,    -1,    -1,  1125,
     124,  1127,  1128,    -1,  1130,  1131,    -1,  1133,    -1,    -1,
      -1,  1137,    -1,   521,  1140,  1141,    -1,    -1,    -1,    -1,
    1146,    -1,    -1,   531,    -1,    -1,    -1,    -1,    -1,   874,
     875,    -1,  1013,  1014,  1015,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   888,    70,  1026,  1027,   892,  1029,  1030,
      -1,  1032,    -1,    -1,   562,   563,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,   235,   130,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,   772,    -1,    -1,    -1,
      -1,   250,   251,    -1,    -1,    -1,   255,   256,  1069,   124,
      -1,  1072,  1073,    -1,    -1,    -1,    -1,    -1,   124,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,  1090,
    1091,  1092,    -1,    63,    64,    65,    -1,    21,    68,    69,
      70,  1102,    -1,    70,    -1,    -1,    -1,   972,    -1,    -1,
     975,    -1,   977,  1114,    -1,  1116,    -1,  1118,    -1,    89,
      -1,    -1,    92,    -1,  1125,    -1,  1127,  1128,    -1,  1130,
    1131,    -1,  1133,    -1,   104,    -1,  1137,    29,    -1,  1140,
    1141,    -1,    -1,    -1,    -1,  1146,    70,    -1,  1013,  1014,
    1015,    -1,    -1,    -1,    -1,    -1,    -1,   124,   874,   875,
      -1,  1026,  1027,    -1,  1029,  1030,    -1,  1032,    -1,   521,
      -1,    63,   888,    -1,    -1,    -1,   892,    -1,    -1,   531,
      -1,    -1,    -1,    18,    76,    20,    -1,    22,    80,    81,
      82,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    -1,    -1,  1069,    40,   289,  1072,  1073,    44,
     562,   563,    47,    48,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,  1090,  1091,  1092,    -1,    -1,
      16,    -1,    -1,    -1,    -1,    -1,    -1,  1102,    -1,    -1,
      -1,    -1,   325,    -1,   772,    -1,    -1,    -1,    -1,  1114,
      -1,  1116,    -1,  1118,    -1,    -1,   972,    -1,    -1,   975,
    1125,   977,  1127,  1128,    -1,  1130,  1131,   456,  1133,    -1,
      -1,    -1,  1137,    -1,    -1,  1140,  1141,    63,    64,    65,
      -1,  1146,    68,    69,    70,    -1,   178,    -1,    -1,    75,
      -1,   126,   184,    -1,    -1,    -1,   188,  1013,  1014,  1015,
      -1,    -1,   194,    -1,    -1,    -1,   198,    -1,    -1,    -1,
    1026,  1027,   204,  1029,  1030,    -1,  1032,    -1,   104,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,   518,
     519,   520,    -1,    -1,    -1,    -1,    -1,    13,   124,    -1,
     529,    -1,    -1,    -1,    -1,    -1,   874,   875,    -1,   538,
      -1,    -1,   541,  1069,    -1,    -1,  1072,  1073,    -1,    -1,
     888,    -1,    -1,    -1,   892,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,  1090,  1091,  1092,    68,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,  1102,    63,    64,    65,
      -1,    75,    68,    69,    70,    -1,    -1,    -1,  1114,    -1,
    1116,    -1,  1118,    -1,    -1,    -1,    -1,    -1,    -1,  1125,
      -1,  1127,  1128,    89,  1130,  1131,    92,  1133,    -1,    -1,
     772,  1137,    98,    -1,  1140,  1141,    -1,    -1,   104,    -1,
    1146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   521,   130,
     124,    -1,   133,   134,   972,    -1,    -1,   975,   531,   977,
      -1,   127,    -1,    -1,    -1,   146,   147,   148,   149,   150,
      -1,    -1,    -1,    -1,    -1,    -1,   157,    18,    -1,    20,
     161,    22,   163,    -1,   165,   166,   167,    -1,   667,   562,
     563,    -1,    -1,    -1,    -1,  1013,  1014,  1015,    -1,    40,
     679,    -1,    -1,    44,    -1,    -1,    47,    48,  1026,  1027,
      -1,  1029,  1030,    -1,  1032,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,   208,    16,   708,
      -1,   212,   874,   875,    -1,    -1,    -1,    -1,    -1,    -1,
     719,    -1,    -1,   224,    -1,   226,   888,   228,    -1,    -1,
     892,  1069,    -1,    -1,  1072,  1073,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,   246,    -1,   746,   249,    -1,
      16,    -1,  1090,  1091,  1092,    63,    64,    65,    -1,    -1,
      68,    69,    70,   124,  1102,   126,    -1,    75,     3,     4,
       5,     6,     7,     8,     9,    10,  1114,    -1,  1116,    -1,
    1118,    16,    -1,    -1,    -1,    -1,    -1,  1125,   289,  1127,
    1128,    -1,  1130,  1131,    -1,  1133,    -1,    -1,    -1,  1137,
      -1,    -1,  1140,  1141,    -1,    -1,    -1,    -1,  1146,    -1,
     972,    -1,    -1,   975,    -1,   977,   124,    -1,    -1,    -1,
      -1,    -1,    -1,   324,   325,    -1,    -1,   328,    63,    64,
      65,    -1,    -1,    68,    69,    70,    71,    72,    -1,    -1,
      75,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,  1013,  1014,  1015,    89,    90,    91,    92,   124,    19,
      20,    -1,    -1,    -1,  1026,  1027,    -1,  1029,  1030,   104,
    1032,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,   772,
      -1,    41,    42,    -1,   883,    -1,    -1,    47,    48,   124,
      -1,   890,   891,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    -1,    -1,    -1,  1069,    -1,    -1,
    1072,  1073,    -1,    -1,    74,    75,    76,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,  1090,  1091,
    1092,    -1,   931,    -1,    -1,    -1,    21,    -1,    -1,    -1,
    1102,    -1,    -1,   444,   445,   446,   447,   448,    -1,    -1,
      -1,    -1,  1114,    -1,  1116,    -1,  1118,    -1,    -1,    -1,
      -1,    -1,    -1,  1125,   124,  1127,  1128,    -1,  1130,  1131,
      -1,  1133,    -1,    -1,    -1,  1137,   236,   237,  1140,  1141,
      -1,   874,   875,    -1,  1146,    70,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,   888,    -1,    -1,    -1,   892,
      -1,    -1,   503,    -1,    -1,    -1,    -1,    80,    -1,    82,
      -1,    84,  1011,  1012,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    97,    98,    99,    -1,   101,   102,
     531,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,   552,    -1,    -1,    -1,    -1,    -1,    20,    -1,  1058,
      -1,   562,   563,    63,    64,    65,   567,    -1,    68,    69,
      70,     3,     4,     5,     6,     7,     8,     9,    10,   972,
      -1,    -1,   975,    -1,   977,    -1,    -1,    -1,    -1,    89,
      79,    -1,    92,    -1,    -1,  1094,  1095,     3,     4,     5,
       6,     7,     8,     9,    10,   178,   179,   180,   181,    -1,
      16,    -1,    -1,   521,    -1,   188,   189,   190,   191,    -1,
    1013,  1014,  1015,    -1,    -1,   198,   199,   200,   201,    -1,
      -1,    -1,    -1,  1026,  1027,   124,  1029,  1030,    70,  1032,
      -1,   214,   215,    -1,   217,    -1,    -1,   220,    -1,   650,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      -1,   124,    68,    69,    70,    63,    64,    65,    -1,    75,
      68,    69,    70,    -1,    -1,    -1,  1069,    -1,    -1,  1072,
    1073,    -1,    -1,    89,    90,    91,    92,    -1,   689,    -1,
      -1,    89,   124,    -1,    92,    -1,    -1,  1090,  1091,  1092,
      -1,    -1,   462,   463,   464,   465,   104,    -1,    -1,  1102,
       3,     4,     5,     6,     7,     8,     9,    10,   124,    -1,
      -1,  1114,    -1,  1116,    -1,  1118,    -1,    -1,    -1,    -1,
      -1,    -1,  1125,    -1,  1127,  1128,    -1,  1130,  1131,    -1,
    1133,    -1,    -1,    -1,  1137,    -1,   747,  1140,  1141,    -1,
      -1,    -1,    -1,  1146,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   764,    -1,    -1,    -1,    -1,    63,    64,
      65,   772,    -1,    68,    69,    70,    -1,    -1,   779,   780,
      76,    77,    78,    79,    -1,    81,    -1,    83,    -1,    85,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,
     373,   374,   375,    -1,   377,   378,    -1,   380,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,   819,    -1,
     393,   394,   395,    -1,   397,   398,   827,   400,    -1,    -1,
      -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     413,   414,   415,    -1,   417,   418,    -1,   420,    -1,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   859,   860,
      -1,   862,    76,    77,    -1,   438,    80,    81,    82,    83,
      84,    85,    -1,   169,   170,   171,    -1,   173,   174,    -1,
     176,    -1,    -1,    97,    -1,    -1,    -1,    -1,   184,   185,
     186,   187,    -1,    -1,    -1,    -1,   897,    -1,   194,   195,
     196,   197,    -1,    18,    -1,    20,    -1,    22,   204,   205,
     206,   207,    27,    28,    29,    30,    31,    32,    -1,    -1,
     680,   681,   682,   683,   684,   685,   686,   687,   688,    44,
     690,   691,   692,   693,   694,   695,   696,   697,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    -1,    -1,    -1,   169,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,   178,   179,   874,   875,    -1,    -1,
     184,   185,    -1,    -1,   188,   189,    -1,    -1,    -1,    -1,
     194,   195,    -1,    -1,   198,   199,    -1,    -1,    -1,    -1,
     204,   205,    -1,    -1,    -1,    -1,    13,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    70,    -1,    -1,    -1,   124,
      75,   126,    -1,  1014,    -1,    -1,    -1,   590,   591,    -1,
     593,    -1,    -1,   596,    89,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   610,   611,   104,
     613,    -1,    -1,   616,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    70,    -1,    -1,    -1,   630,   631,   124,
     633,    -1,    -1,   636,   972,    -1,    -1,    -1,   364,   365,
      -1,   367,    89,    -1,   370,    92,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   843,    -1,   845,    -1,   104,   384,   385,
     386,    -1,   388,   389,    -1,   391,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1013,    -1,  1015,   404,   405,
     406,    -1,   408,   409,    -1,   411,    -1,    -1,  1026,  1027,
      -1,  1029,  1030,    -1,    -1,    -1,    -1,    -1,   424,   425,
     426,    -1,   428,   429,    -1,   431,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,   373,
      -1,  1069,    -1,    -1,  1072,  1073,    -1,    -1,    -1,    -1,
     384,    -1,   932,    -1,    -1,    -1,    -1,    -1,    -1,   393,
      -1,    -1,  1090,  1091,    -1,    -1,    -1,    -1,    -1,   714,
     404,    -1,    -1,    -1,  1102,    -1,    -1,    -1,    -1,   413,
      -1,    -1,    63,    64,    65,    -1,  1114,    68,    69,    70,
     424,    -1,    -1,    -1,    75,   788,    -1,  1125,    -1,  1127,
    1128,    -1,  1130,  1131,    29,   798,    -1,    -1,    89,  1137,
      -1,    92,  1140,  1141,    -1,   808,    -1,    -1,  1146,    -1,
     765,   766,    -1,   104,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    -1,    -1,   124,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    -1,    80,    81,    82,    83,    84,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     586,    -1,    97,    98,    -1,    -1,   101,   870,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   601,   602,    -1,   604,    -1,
      -1,   607,    -1,    -1,    63,    64,    65,    -1,    -1,    68,
      69,    70,    -1,    -1,    -1,   621,   622,    -1,   624,    -1,
      -1,   627,   857,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    -1,   641,   642,   872,   644,    98,
      -1,   647,    -1,    -1,   879,   104,    -1,    -1,    -1,    -1,
      -1,   886,    -1,    -1,   169,   170,    -1,    -1,   173,   894,
     943,   944,    -1,   178,   179,   180,    -1,    -1,   127,   184,
     185,   186,    -1,   188,   189,   190,   911,   912,    -1,   194,
     195,   196,    -1,   198,   199,   200,    -1,    -1,    -1,   204,
     205,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   214,
      -1,    -1,   937,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1010,    -1,    -1,
      -1,    -1,   967,    -1,    -1,    -1,   971,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   982,    -1,    -1,
      -1,    -1,    -1,    -1,   989,    -1,   991,    -1,   993,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    14,    15,    -1,
      -1,    -1,  1017,    20,    -1,    -1,    -1,    -1,   794,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,   804,    -1,
      -1,    -1,    -1,    -1,    41,    42,  1041,    -1,   814,  1044,
      47,    48,  1047,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,  1064,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   364,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,   374,
      -1,    -1,   377,    -1,    -1,    -1,    -1,    -1,    -1,   384,
     385,    -1,    -1,   388,    -1,    -1,    -1,    -1,   393,   394,
      -1,    -1,   397,    -1,    -1,    -1,    -1,   124,    -1,   404,
     405,    -1,    -1,   408,    -1,    -1,    -1,    -1,   413,   414,
      -1,    -1,   417,    -1,    -1,    -1,    -1,    -1,    -1,   424,
     425,    -1,    -1,   428,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    47,    48,
      13,    -1,    15,    16,    -1,    54,    55,    56,    57,    58,
      59,    60,    25,    62,    63,    64,    65,    -1,    -1,    68,
      69,    70,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    -1,    86,    87,    88,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    89,    -1,    -1,    92,
      -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    14,    15,
      -1,   124,    -1,    -1,    20,   590,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   601,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   610,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,   621,    -1,    54,    55,
      56,    57,    58,    59,    60,   630,    62,    63,    64,    65,
      -1,    -1,    68,    69,    70,    -1,   641,    -1,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      86,    87,    88,    89,    -1,    -1,    92,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    77,    78,    -1,    80,    81,    82,    83,    84,    -1,
      86,    87,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,    80,
      81,    82,    83,    84,    -1,    86,    87,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    33,    34,    -1,
      16,    -1,    -1,   124,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    20,    21,    -1,    -1,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    -1,    33,    34,    75,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    89,    90,    91,    92,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,   124,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    20,   124,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   124,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,   124,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    19,
      20,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    33,    34,    -1,    -1,    16,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   124,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    64,    65,    -1,    -1,    68,
      69,    70,    -1,    33,    34,    -1,    75,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      89,    90,    91,    92,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,     3,     4,     5,
       6,     7,     8,     9,    10,   124,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    33,    34,    -1,
      -1,    16,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,   124,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    20,    21,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,
      75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    89,    -1,    -1,    92,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,   124,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,   124,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      33,    34,    -1,    -1,    16,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,   124,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,
      -1,    -1,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      33,    34,    -1,    75,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    89,    -1,    -1,
      92,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,   124,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,   124,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    33,    34,    -1,    -1,    16,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   124,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    64,    65,    -1,    -1,    68,
      69,    70,    -1,    33,    34,    -1,    75,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      89,    -1,    -1,    92,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,   124,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,   124,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    33,    34,    -1,    -1,
      16,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   124,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    74,    75,    76,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,    75,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,   124,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,   124,    -1,
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
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,
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
       9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,   124,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,   124,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,   124,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,   124,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,   124,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   124,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    74,
      75,    76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    -1,
      -1,    -1,    47,    48,    -1,    20,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,
      75,    76,    47,    48,    79,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    79,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,   124,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,
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
      21,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    20,    21,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,   124,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    74,    75,    76,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    20,    21,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    20,    21,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    74,    75,    76,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124
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
     124,   124,   124,   124,   124,   124,   124,   157,   158,   124,
     137,   138,   137,   163,   281,   124,   165,   161,   162,   164,
     166,   162,   164,   166,   164,   166,   166,     3,     4,     5,
       6,     7,     8,     9,    10,    13,    15,    25,    69,    75,
     124,   130,   131,   132,   133,   134,   135,   136,   137,   145,
     150,   151,   155,   156,   167,   168,   169,   170,   218,   219,
     229,   230,   231,   266,   267,   268,   271,   272,   273,   274,
     275,    13,    44,   124,    36,   124,    13,    94,   130,   145,
     151,   153,   154,   156,   218,   271,   272,   273,   152,   161,
     162,   164,   152,   162,   164,   152,   164,   152,   156,   161,
     162,   164,   166,   152,   156,   161,   162,   164,   156,   161,
     162,   164,   166,   152,   156,   161,   162,   164,   156,   161,
     162,   164,   166,   152,   156,   161,   162,   164,    61,   159,
      11,    17,    11,    11,   162,   164,   166,   164,   166,   166,
     164,   166,   166,   166,    26,   231,   124,   223,   124,   171,
     172,   173,   223,     3,    13,    20,    47,    48,    54,    55,
      56,    57,    58,    59,    60,    62,    70,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    86,    87,
      88,   124,   130,   132,   137,   140,   141,   145,   149,   151,
     177,   178,   180,   181,   182,   183,   184,   186,   187,   190,
     191,   192,   198,   211,   212,   214,   215,   216,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   257,
     258,   259,   261,   271,   272,   273,    75,   130,   268,   151,
     168,    13,   228,   231,    99,   150,   220,   269,    20,   130,
     219,   267,   130,   219,    71,    72,    90,    91,   219,    64,
      65,    68,    69,    70,    71,    72,   130,    64,    65,    68,
      69,    70,    89,    90,    91,    92,   219,    36,    13,   219,
     151,   154,   130,   152,   162,   164,   152,   164,   152,   152,
     164,   152,   152,   161,   162,   164,   166,   162,   164,   166,
     164,   166,   166,   152,   161,   162,   164,   152,   162,   164,
     152,   164,   152,   161,   162,   164,   166,   162,   164,   166,
     164,   166,   166,   152,   161,   162,   164,   152,   162,   164,
     152,   164,   152,   161,   162,   164,   166,   162,   164,   166,
     164,   166,   166,   152,   161,   162,   164,   152,   162,   164,
     152,   164,   152,   124,   136,   158,   281,   124,   164,   166,
     166,   166,   166,   219,   271,   272,   273,   275,    20,   130,
     224,   220,    18,   139,    11,    13,    27,   220,    18,   126,
     185,     3,    33,    34,    41,    42,   124,   132,   137,   175,
     176,   177,   186,   190,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   124,   141,   180,   198,   210,   210,    22,
      44,   237,   126,    16,   124,   131,   136,   188,   276,   175,
     175,    13,   124,    13,   124,    13,   175,   175,    20,    20,
      18,    40,    44,   126,   185,   126,   185,    22,    20,    18,
      44,    20,    27,    28,    29,    30,    31,    32,   179,    22,
      44,    18,    47,    48,   151,   233,    13,   124,   171,    13,
     223,   223,    20,   137,   221,   222,    62,    74,   124,   141,
     151,   181,   232,   270,   276,   269,    21,    70,   130,   224,
     225,   226,   227,   171,   228,   220,   269,   171,   228,   228,
     171,   228,    13,   228,   171,   152,   164,   152,   152,   152,
     162,   164,   166,   164,   166,   166,   164,   166,   166,   166,
     152,   162,   164,   152,   164,   152,   152,   164,   152,   152,
     162,   164,   166,   164,   166,   166,   164,   166,   166,   166,
     152,   162,   164,   152,   164,   152,   152,   164,   152,   152,
     162,   164,   166,   164,   166,   166,   164,   166,   166,   166,
     152,   162,   164,   152,   164,   152,   152,   164,   152,   152,
      43,   160,   166,   228,   219,   219,   219,   219,    21,   130,
     225,    74,   124,    11,    19,    18,   172,   150,   174,   175,
     193,    19,    18,   126,   210,   210,   210,   210,    21,    12,
      45,    46,    38,    39,    43,    52,    53,    16,    17,    73,
      49,    50,    51,    33,    34,    35,    36,    37,   124,   276,
     124,   276,   171,    12,   135,   277,   278,   279,    18,   139,
     195,   196,   139,   195,    20,   124,   188,    13,    13,    40,
      13,    13,    13,    13,   175,   175,   175,   238,    62,    74,
      76,   124,   187,   276,   126,   126,    76,   124,   276,    21,
     175,   189,   175,   124,   187,   276,    13,    70,   236,   242,
     263,   265,   175,   124,   276,   124,   187,   276,   175,   220,
     220,    21,   224,   225,    11,    20,    20,    44,    44,    44,
     151,   151,   232,    62,    74,   130,    23,   124,   173,    11,
      11,    21,    13,   269,    13,    13,    13,   152,   164,   166,
     166,   166,   166,   152,   164,   152,   152,   152,   164,   166,
     166,   166,   166,   152,   164,   152,   152,   152,   164,   166,
     166,   166,   166,   152,   164,   152,   152,   152,   281,    43,
     228,   228,   228,   228,   139,    21,    44,    20,    19,    11,
     151,   174,   194,   197,    19,   175,   201,   202,   203,   204,
     205,   206,   206,    27,   207,    27,   207,   135,   208,   208,
     208,   209,   209,   210,   210,   210,   124,    20,   124,    61,
      62,   280,    11,    17,   175,   193,   139,   196,   193,   139,
      21,   189,    20,   175,    21,    21,    19,    22,    44,    20,
     124,    76,   124,    11,    21,    19,    20,   124,    13,   175,
      40,    13,    11,   124,    20,   124,    19,    11,    21,   222,
      21,   189,    21,   189,    62,   276,    62,   276,    62,   276,
     151,    20,    20,    23,   173,   124,    21,   225,   226,   166,
     152,   166,   152,   166,   152,   281,   139,    74,    21,   225,
     151,    11,    40,   207,   207,    21,   189,    20,   135,   135,
     278,    19,   166,    21,    21,   189,    13,    84,    86,   124,
     149,   238,   239,   252,   253,   254,   255,   256,   260,   262,
     238,   124,   276,   124,   276,    21,   189,    20,   175,    21,
     189,    20,    21,   264,   265,    13,   175,    13,   175,   242,
      21,   189,    20,    21,   225,    13,    21,    13,    21,    20,
      62,    20,    62,    20,    62,    21,   189,    21,   189,   124,
      21,   139,    21,   174,   199,    21,    21,   189,   166,   166,
      21,    20,    20,    40,    20,    85,   124,    20,   124,    21,
      21,   189,    21,    21,   189,   238,    21,    21,   264,    21,
      21,   264,    13,    21,    21,   189,    21,    13,    13,    21,
     189,    20,    21,   189,    20,    21,   189,    20,    13,    21,
      13,    21,   139,    21,   166,   175,   175,   253,    13,   236,
     263,   238,    21,   189,    20,    21,    21,   238,   238,    21,
     238,   238,    21,    21,   264,    21,    13,    21,    21,   189,
      13,    21,    21,   189,    13,    21,    21,   189,    13,    13,
      21,    21,    13,   175,    40,    13,    21,    21,   189,   238,
     238,   238,    21,    13,    13,    21,    13,    13,    21,    13,
      13,    21,   253,   253,    21,   264,    13,   175,    13,   175,
      21,   238,    13,    13,    13,    85,   253,    21,    21,   264,
      21,    21,   264,    13,   253,   253,   253,    21,   253,   253,
      21,    21,   264,   253,   253,   253,    21,   253
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
#line 3412 "parser_1st.tab.c"
    break;

  case 3: /* COMPILATIONUNIT: ORDINARYCOMPILATIONUNIT EOFF  */
#line 242 "parser_1st.y"
                                                     {
                    
                    return 0;
                }
#line 3421 "parser_1st.tab.c"
    break;

  case 4: /* TYPE: PRIMITIVETYPE  */
#line 247 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3427 "parser_1st.tab.c"
    break;

  case 5: /* TYPE: REFERENCETYPE  */
#line 248 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3433 "parser_1st.tab.c"
    break;

  case 6: /* PRIMITIVETYPE: NUMERICTYPE  */
#line 250 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3439 "parser_1st.tab.c"
    break;

  case 7: /* PRIMITIVETYPE: BOOLEAN  */
#line 251 "parser_1st.y"
                             {(yyval.val) = stringtochar("bool");}
#line 3445 "parser_1st.tab.c"
    break;

  case 8: /* NUMERICTYPE: INTEGRALTYPE  */
#line 253 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3451 "parser_1st.tab.c"
    break;

  case 9: /* NUMERICTYPE: FLOATINGTYPE  */
#line 254 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3457 "parser_1st.tab.c"
    break;

  case 10: /* INTEGRALTYPE: BYTE  */
#line 256 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3463 "parser_1st.tab.c"
    break;

  case 11: /* INTEGRALTYPE: SHORT  */
#line 257 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3469 "parser_1st.tab.c"
    break;

  case 12: /* INTEGRALTYPE: INT  */
#line 258 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3475 "parser_1st.tab.c"
    break;

  case 13: /* INTEGRALTYPE: LONG  */
#line 259 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3481 "parser_1st.tab.c"
    break;

  case 14: /* INTEGRALTYPE: CHAR  */
#line 260 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3487 "parser_1st.tab.c"
    break;

  case 15: /* FLOATINGTYPE: FLOAT  */
#line 262 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3493 "parser_1st.tab.c"
    break;

  case 16: /* FLOATINGTYPE: DOUBLE  */
#line 263 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3499 "parser_1st.tab.c"
    break;

  case 17: /* REFERENCETYPE: CLASSORINTERFACETYPE  */
#line 265 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3505 "parser_1st.tab.c"
    break;

  case 18: /* CLASSORINTERFACETYPE: CLASSTYPE  */
#line 267 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3511 "parser_1st.tab.c"
    break;

  case 19: /* CLASSTYPE: CLASSTYPE1  */
#line 269 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3517 "parser_1st.tab.c"
    break;

  case 20: /* CLASSTYPE1: IDENTIFIER  */
#line 271 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val); }
#line 3523 "parser_1st.tab.c"
    break;

  case 21: /* DIMS: OPENSQUARE CLOSESQUARE  */
#line 274 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3529 "parser_1st.tab.c"
    break;

  case 22: /* DIMS: DIMS OPENSQUARE CLOSESQUARE  */
#line 275 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3535 "parser_1st.tab.c"
    break;

  case 23: /* METHODNAME: IDENTIFIER  */
#line 277 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3546 "parser_1st.tab.c"
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
#line 3568 "parser_1st.tab.c"
    break;

  case 25: /* EXPRESSIONNAME: EXPRESSIONNAME DOT IDENTIFIER  */
#line 301 "parser_1st.y"
                                                  {/*TODO*/}
#line 3574 "parser_1st.tab.c"
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
#line 3622 "parser_1st.tab.c"
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
                    }}
#line 3638 "parser_1st.tab.c"
    break;

  case 37: /* NORMALCLASSDECLARATION: CLASS CLASSNAME CLASSBODY  */
#line 372 "parser_1st.y"
                                                       {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));/*TODO begin class */}
#line 3644 "parser_1st.tab.c"
    break;

  case 38: /* NORMALCLASSDECLARATION: SUPER1 CLASS IDENTIFIER CLASSBODY  */
#line 373 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val); if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3650 "parser_1st.tab.c"
    break;

  case 39: /* NORMALCLASSDECLARATION: SUPER2 CLASS IDENTIFIER CLASSBODY  */
#line 374 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3656 "parser_1st.tab.c"
    break;

  case 40: /* NORMALCLASSDECLARATION: SUPER3 CLASS IDENTIFIER CLASSBODY  */
#line 375 "parser_1st.y"
                                                                {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3662 "parser_1st.tab.c"
    break;

  case 101: /* CLASSNAME: IDENTIFIER  */
#line 440 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val); curr_class = chartostring((yyval.val)); }
#line 3668 "parser_1st.tab.c"
    break;

  case 166: /* FOR: FOR1  */
#line 507 "parser_1st.y"
           {newscope();}
#line 3674 "parser_1st.tab.c"
    break;

  case 167: /* OPENCURLY: OPENCURLY1  */
#line 508 "parser_1st.y"
                          {newscope(); }
#line 3680 "parser_1st.tab.c"
    break;

  case 168: /* CLOSECURLY: CLOSECURLY1  */
#line 509 "parser_1st.y"
                          {popscope();}
#line 3686 "parser_1st.tab.c"
    break;

  case 208: /* FIELDDECLARATION: FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 570 "parser_1st.y"
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
#line 3719 "parser_1st.tab.c"
    break;

  case 209: /* FIELDDECLARATION: SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 598 "parser_1st.y"
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
#line 3750 "parser_1st.tab.c"
    break;

  case 210: /* FIELDDECLARATION: SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 624 "parser_1st.y"
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
#line 3783 "parser_1st.tab.c"
    break;

  case 211: /* FIELDDECLARATION: TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 652 "parser_1st.y"
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
#line 3825 "parser_1st.tab.c"
    break;

  case 212: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATOR  */
#line 692 "parser_1st.y"
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
#line 3842 "parser_1st.tab.c"
    break;

  case 213: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR  */
#line 704 "parser_1st.y"
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
#line 3870 "parser_1st.tab.c"
    break;

  case 214: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER  */
#line 728 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit ;   generalmap[(yyval.val)].typ= generalmap[(yyvsp[0].val)].typ;                                   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));                 
                                                                            if(ds[curr3].find("class")!=ds[curr3].end()){
                                                                                ds[curr]["var"] = ds[curr1]["var"];
                                                                                string cls = ds[curr3]["var"];    // stores the class name after new
                                                                                // cout<<"class "<<cls<<"\n";
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
#line 3908 "parser_1st.tab.c"
    break;

  case 215: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID  */
#line 761 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];}
#line 3914 "parser_1st.tab.c"
    break;

  case 216: /* VARIABLEDECLARATORID: IDENTIFIER  */
#line 763 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));

}
#line 3927 "parser_1st.tab.c"
    break;

  case 217: /* VARIABLEDECLARATORID: IDENTIFIER DIMS  */
#line 771 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        int curr = chartonum((yyval.val));
                                    ds[curr]["var"] = chartostring((yyvsp[-1].val));
                        /*TODO*/
                        }
#line 3937 "parser_1st.tab.c"
    break;

  case 218: /* VARIABLEINITIALIZER: EXPRESSION  */
#line 778 "parser_1st.y"
                                    {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 3943 "parser_1st.tab.c"
    break;

  case 219: /* VARIABLEINITIALIZER: ARRAYINITIALIZER  */
#line 779 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 3949 "parser_1st.tab.c"
    break;

  case 220: /* EXPRESSION: ASSIGNMENTEXPRESSION  */
#line 781 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 3955 "parser_1st.tab.c"
    break;

  case 221: /* ASSIGNMENTEXPRESSION: CONDITIONALEXPRESSION  */
#line 783 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 3963 "parser_1st.tab.c"
    break;

  case 222: /* ASSIGNMENTEXPRESSION: ASSIGNMENT  */
#line 786 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);/*TODO CHECK multiple assign*/}
#line 3969 "parser_1st.tab.c"
    break;

  case 223: /* ASSIGNMENT: LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  */
#line 788 "parser_1st.y"
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
#line 3988 "parser_1st.tab.c"
    break;

  case 224: /* LEFTHANDSIDE: EXPRESSIONNAME  */
#line 803 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 3994 "parser_1st.tab.c"
    break;

  case 225: /* LEFTHANDSIDE: IDENTIFIER  */
#line 804 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
#line 4007 "parser_1st.tab.c"
    break;

  case 226: /* LEFTHANDSIDE: FIELDACCESS  */
#line 812 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4013 "parser_1st.tab.c"
    break;

  case 227: /* LEFTHANDSIDE: ARRAYACCESS  */
#line 813 "parser_1st.y"
                                {   (yyval.val) = (yyvsp[0].val);
                                    ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"[ "+ds[chartonum((yyvsp[0].val))]["var"]+" ]";
                }
#line 4021 "parser_1st.tab.c"
    break;

  case 228: /* ASSIGNMENTOPERATOR: EQUALS  */
#line 817 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 4028 "parser_1st.tab.c"
    break;

  case 229: /* ASSIGNMENTOPERATOR: MULTIPLYEQUALS  */
#line 819 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 4035 "parser_1st.tab.c"
    break;

  case 230: /* ASSIGNMENTOPERATOR: DIVIDEEQUALS  */
#line 821 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 4042 "parser_1st.tab.c"
    break;

  case 231: /* ASSIGNMENTOPERATOR: MODEQUALS  */
#line 823 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 4049 "parser_1st.tab.c"
    break;

  case 232: /* ASSIGNMENTOPERATOR: PLUSEQUALS  */
#line 825 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 4056 "parser_1st.tab.c"
    break;

  case 233: /* ASSIGNMENTOPERATOR: MINUSEQUALS  */
#line 827 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 4063 "parser_1st.tab.c"
    break;

  case 234: /* FIELDACCESS: PRIMARY DOT IDENTIFIER  */
#line 830 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring((yyvsp[0].val));
                                        }else assert(0 && "unexpected type\n");
                                        }
#line 4075 "parser_1st.tab.c"
    break;

  case 237: /* PRIMARY: PRIMARYNONEWARRAY  */
#line 840 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            if(ds[chartonum((yyval.val))].find("array")!=ds[chartonum((yyval.val))].end())
                            ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"["+ds[chartonum((yyvsp[0].val))]["var"]+"]"; }
#line 4083 "parser_1st.tab.c"
    break;

  case 238: /* PRIMARY: ARRAYCREATIONEXPRESSION  */
#line 843 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4089 "parser_1st.tab.c"
    break;

  case 239: /* PRIMARYNONEWARRAY: LITERAL  */
#line 845 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4095 "parser_1st.tab.c"
    break;

  case 240: /* PRIMARYNONEWARRAY: CLASSLITERAL  */
#line 846 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4101 "parser_1st.tab.c"
    break;

  case 241: /* PRIMARYNONEWARRAY: THIS  */
#line 847 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 4110 "parser_1st.tab.c"
    break;

  case 243: /* PRIMARYNONEWARRAY: OPENPARAN EXPRESSION CLOSEPARAN  */
#line 852 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4116 "parser_1st.tab.c"
    break;

  case 244: /* PRIMARYNONEWARRAY: CLASSINSTANCECREATIONEXPRESSION  */
#line 853 "parser_1st.y"
                                                              {(yyval.val) = (yyvsp[0].val); generalmap[(yyval.val)].isnewclass = true;}
#line 4122 "parser_1st.tab.c"
    break;

  case 245: /* PRIMARYNONEWARRAY: FIELDACCESS  */
#line 854 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4128 "parser_1st.tab.c"
    break;

  case 246: /* PRIMARYNONEWARRAY: ARRAYACCESS  */
#line 855 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4134 "parser_1st.tab.c"
    break;

  case 247: /* PRIMARYNONEWARRAY: METHODINVOCATION  */
#line 856 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4140 "parser_1st.tab.c"
    break;

  case 249: /* LITERAL: INTEGERLITERAL  */
#line 859 "parser_1st.y"
                        {(yyval.val) = new_temp();  ds[chartonum((yyval.val))]["type"] = "int"; ds[chartonum((yyval.val))]["var"] = new_var(); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); tempinitval[ds[chartonum((yyval.val))]["var"]]= chartonum((yyvsp[0].val)); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4146 "parser_1st.tab.c"
    break;

  case 250: /* LITERAL: FLOATINGPOINTLITERAL  */
#line 860 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["start"] = numtostring(code.size());ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4152 "parser_1st.tab.c"
    break;

  case 251: /* LITERAL: BOOLEANLITERAL  */
#line 861 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4158 "parser_1st.tab.c"
    break;

  case 252: /* LITERAL: CHARACTERLITERAL  */
#line 862 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4164 "parser_1st.tab.c"
    break;

  case 253: /* LITERAL: STRINGLITERAL  */
#line 863 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4170 "parser_1st.tab.c"
    break;

  case 254: /* LITERAL: TEXTBLOCK  */
#line 864 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4176 "parser_1st.tab.c"
    break;

  case 255: /* LITERAL: NULLLITERAL  */
#line 865 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4182 "parser_1st.tab.c"
    break;

  case 265: /* CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
#line 878 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[0].val);}
#line 4188 "parser_1st.tab.c"
    break;

  case 269: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  */
#line 883 "parser_1st.y"
                                                                                                           {(yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-2].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-2].val))];  }
#line 4194 "parser_1st.tab.c"
    break;

  case 270: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  */
#line 884 "parser_1st.y"
                                                                                                                     {/*TODO*/}
#line 4200 "parser_1st.tab.c"
    break;

  case 271: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 885 "parser_1st.y"
                                                                                                                        {/*TODO*/}
#line 4206 "parser_1st.tab.c"
    break;

  case 272: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY  */
#line 886 "parser_1st.y"
                                                                                                                                  {/*TODO*/}
#line 4212 "parser_1st.tab.c"
    break;

  case 277: /* CLASSORINTERFACETYPETOINSTANTIATE: IDENTIFIER  */
#line 892 "parser_1st.y"
                                                {   (yyval.val) = new_temp(); ds[ chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val)); ds[ chartonum((yyval.val))]["class"] = "true";
                                                     }
#line 4219 "parser_1st.tab.c"
    break;

  case 278: /* ARGUMENTLIST: EXPRESSION  */
#line 895 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            ds2[chartonum((yyval.val))]["type"].push_back(ds[chartonum((yyvsp[0].val))]["type"]);
                            ds2[chartonum((yyval.val))]["var"].push_back(ds[chartonum((yyvsp[0].val))]["var"]);
                            }
#line 4228 "parser_1st.tab.c"
    break;

  case 279: /* ARGUMENTLIST: ARGUMENTLIST COMMA EXPRESSION  */
#line 899 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4241 "parser_1st.tab.c"
    break;

  case 280: /* METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  */
#line 908 "parser_1st.y"
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
#line 4258 "parser_1st.tab.c"
    break;

  case 281: /* METHODINVOCATION: METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 920 "parser_1st.y"
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
#line 4282 "parser_1st.tab.c"
    break;

  case 282: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 939 "parser_1st.y"
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
#line 4311 "parser_1st.tab.c"
    break;

  case 283: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 963 "parser_1st.y"
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
                                                        ds[curr]["start"] = code.size();
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
}
#line 4341 "parser_1st.tab.c"
    break;

  case 312: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS  */
#line 1020 "parser_1st.y"
                                                         {/*NOT SUPPORTED*/}
#line 4347 "parser_1st.tab.c"
    break;

  case 313: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS DIMS  */
#line 1021 "parser_1st.y"
                                                                       {/*NOT SUPPORTED*/}
#line 4353 "parser_1st.tab.c"
    break;

  case 314: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER  */
#line 1022 "parser_1st.y"
                                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-2].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; assert (generalmap[(yyvsp[0].val)].vinit.dims.size() == temp[(yyvsp[-1].val)]); }
#line 4359 "parser_1st.tab.c"
    break;

  case 315: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER  */
#line 1023 "parser_1st.y"
                                                                               {/*NOT SUPPORTED*/}
#line 4365 "parser_1st.tab.c"
    break;

  case 316: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS  */
#line 1024 "parser_1st.y"
                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; ds[chartonum((yyval.val))]["arr"] = "true"; ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyvsp[0].val))]["var"]; ds[chartonum((yyval.val))]["type"] = chartostring((yyvsp[-1].val)); ds[chartonum((yyval.val))]["start"] = ds[chartonum((yyvsp[0].val))]["start"];}
#line 4371 "parser_1st.tab.c"
    break;

  case 317: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS  */
#line 1025 "parser_1st.y"
                                                                   {/*NOT SUPPORTED*/}
#line 4377 "parser_1st.tab.c"
    break;

  case 318: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS  */
#line 1026 "parser_1st.y"
                                                   {/*NOT SUPPORTED*/}
#line 4383 "parser_1st.tab.c"
    break;

  case 319: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS  */
#line 1027 "parser_1st.y"
                                                              {/*NOT SUPPORTED*/}
#line 4389 "parser_1st.tab.c"
    break;

  case 320: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE  */
#line 1028 "parser_1st.y"
                                               {/*TODO whats this*/}
#line 4395 "parser_1st.tab.c"
    break;

  case 321: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE  */
#line 1029 "parser_1st.y"
                                                         {/*TODO whats this*/}
#line 4401 "parser_1st.tab.c"
    break;

  case 322: /* ARRAYINITIALIZER: OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  */
#line 1031 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4407 "parser_1st.tab.c"
    break;

  case 323: /* ARRAYINITIALIZER: OPENCURLY CLOSECURLY  */
#line 1032 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4413 "parser_1st.tab.c"
    break;

  case 324: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST  */
#line 1034 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4419 "parser_1st.tab.c"
    break;

  case 325: /* ARRAYINITIALIZER1: COMMA  */
#line 1035 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=2;}
#line 4425 "parser_1st.tab.c"
    break;

  case 326: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST COMMA  */
#line 1036 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4431 "parser_1st.tab.c"
    break;

  case 327: /* DIMEXPRS: DIMEXPR  */
#line 1038 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[0].val))];}
#line 4437 "parser_1st.tab.c"
    break;

  case 328: /* DIMEXPRS: DIMEXPRS DIMEXPR  */
#line 1039 "parser_1st.y"
                             {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum((yyvsp[-1].val))]["var"]+" *"+ds[chartonum((yyvsp[0].val))]["type"]+" "+ds[ chartonum((yyvsp[0].val))]["var"]);
                              ds[ chartonum((yyval.val))]["var"] = t;  }
#line 4445 "parser_1st.tab.c"
    break;

  case 329: /* DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1043 "parser_1st.y"
                                            {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = varaddrstoint(ds[chartonum((yyvsp[-1].val))]["var"]); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-1].val))];}
#line 4451 "parser_1st.tab.c"
    break;

  case 330: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZER  */
#line 1045 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4457 "parser_1st.tab.c"
    break;

  case 331: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  */
#line 1046 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4463 "parser_1st.tab.c"
    break;

  case 333: /* ARRAYACCESS: PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1053 "parser_1st.y"
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
                code.push_back(t+" = "+ds[curr1]["var"]+" * "+numtostring(bound));
                code.push_back(ds[curr]["var"]+" = "+t+" + "+ds[curr3]["var"]); 
            }
#line 4485 "parser_1st.tab.c"
    break;

  case 334: /* ARRAYACCESS: IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1070 "parser_1st.y"
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
#line 4503 "parser_1st.tab.c"
    break;

  case 335: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  */
#line 1084 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4509 "parser_1st.tab.c"
    break;

  case 336: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  */
#line 1085 "parser_1st.y"
                                                                                                    {}
#line 4515 "parser_1st.tab.c"
    break;

  case 337: /* CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  */
#line 1087 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4521 "parser_1st.tab.c"
    break;

  case 338: /* CONDITIONALOREXPRESSION: CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  */
#line 1088 "parser_1st.y"
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
#line 4539 "parser_1st.tab.c"
    break;

  case 339: /* CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  */
#line 1102 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4545 "parser_1st.tab.c"
    break;

  case 340: /* CONDITIONALANDEXPRESSION: CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  */
#line 1103 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4559 "parser_1st.tab.c"
    break;

  case 341: /* INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  */
#line 1113 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4565 "parser_1st.tab.c"
    break;

  case 342: /* INCLUSIVEOREXPRESSION: INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  */
#line 1114 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4578 "parser_1st.tab.c"
    break;

  case 343: /* EXCLUSIVEOREXPRESSION: ANDEXPRESSION  */
#line 1123 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4584 "parser_1st.tab.c"
    break;

  case 344: /* EXCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  */
#line 1124 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4597 "parser_1st.tab.c"
    break;

  case 345: /* ANDEXPRESSION: EQUALITYEXPRESSION  */
#line 1132 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4603 "parser_1st.tab.c"
    break;

  case 346: /* ANDEXPRESSION: ANDEXPRESSION AND EQUALITYEXPRESSION  */
#line 1133 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4617 "parser_1st.tab.c"
    break;

  case 347: /* EQUALITYEXPRESSION: RELATIONALEXPRESSION  */
#line 1143 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
#line 4630 "parser_1st.tab.c"
    break;

  case 348: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  */
#line 1151 "parser_1st.y"
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
#line 4651 "parser_1st.tab.c"
    break;

  case 349: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  */
#line 1167 "parser_1st.y"
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
#line 4673 "parser_1st.tab.c"
    break;

  case 350: /* RELATIONALEXPRESSION: SHIFTEXPRESSION  */
#line 1185 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4683 "parser_1st.tab.c"
    break;

  case 351: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  */
#line 1190 "parser_1st.y"
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
#line 4706 "parser_1st.tab.c"
    break;

  case 352: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  */
#line 1208 "parser_1st.y"
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
#line 4725 "parser_1st.tab.c"
    break;

  case 353: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  */
#line 1222 "parser_1st.y"
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
#line 4744 "parser_1st.tab.c"
    break;

  case 354: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  */
#line 1236 "parser_1st.y"
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
#line 4763 "parser_1st.tab.c"
    break;

  case 356: /* SHIFTEXPRESSION: ADDITIVEEXPRESSION  */
#line 1252 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4769 "parser_1st.tab.c"
    break;

  case 357: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  */
#line 1253 "parser_1st.y"
                                                                                    {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4783 "parser_1st.tab.c"
    break;

  case 358: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1262 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4796 "parser_1st.tab.c"
    break;

  case 359: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1270 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4809 "parser_1st.tab.c"
    break;

  case 360: /* ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  */
#line 1279 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 4815 "parser_1st.tab.c"
    break;

  case 361: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  */
#line 1280 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4828 "parser_1st.tab.c"
    break;

  case 362: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  */
#line 1288 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4841 "parser_1st.tab.c"
    break;

  case 363: /* MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  */
#line 1297 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4847 "parser_1st.tab.c"
    break;

  case 364: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  */
#line 1298 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4860 "parser_1st.tab.c"
    break;

  case 365: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  */
#line 1306 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4873 "parser_1st.tab.c"
    break;

  case 366: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  */
#line 1314 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4886 "parser_1st.tab.c"
    break;

  case 367: /* UNARYEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1323 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4892 "parser_1st.tab.c"
    break;

  case 368: /* UNARYEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1324 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4898 "parser_1st.tab.c"
    break;

  case 369: /* UNARYEXPRESSION: PLUS UNARYEXPRESSION  */
#line 1325 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 4906 "parser_1st.tab.c"
    break;

  case 370: /* UNARYEXPRESSION: MINUS UNARYEXPRESSION  */
#line 1328 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4919 "parser_1st.tab.c"
    break;

  case 371: /* UNARYEXPRESSION: UNARYEXPRESSIONNOTPLUSMINUS  */
#line 1336 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 4925 "parser_1st.tab.c"
    break;

  case 372: /* PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  */
#line 1338 "parser_1st.y"
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
#line 4943 "parser_1st.tab.c"
    break;

  case 373: /* PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  */
#line 1352 "parser_1st.y"
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
#line 4961 "parser_1st.tab.c"
    break;

  case 374: /* UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  */
#line 1366 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4967 "parser_1st.tab.c"
    break;

  case 375: /* UNARYEXPRESSIONNOTPLUSMINUS: COMPLEMENT UNARYEXPRESSION  */
#line 1367 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4980 "parser_1st.tab.c"
    break;

  case 376: /* UNARYEXPRESSIONNOTPLUSMINUS: NOT UNARYEXPRESSION  */
#line 1375 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 4993 "parser_1st.tab.c"
    break;

  case 377: /* POSTFIXEXPRESSION: PRIMARY  */
#line 1384 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4999 "parser_1st.tab.c"
    break;

  case 378: /* POSTFIXEXPRESSION: EXPRESSIONNAME  */
#line 1385 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5005 "parser_1st.tab.c"
    break;

  case 379: /* POSTFIXEXPRESSION: IDENTIFIER  */
#line 1386 "parser_1st.y"
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
#line 5024 "parser_1st.tab.c"
    break;

  case 380: /* POSTFIXEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1400 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5030 "parser_1st.tab.c"
    break;

  case 381: /* POSTFIXEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1401 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5036 "parser_1st.tab.c"
    break;

  case 382: /* POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  */
#line 1403 "parser_1st.y"
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
#line 5053 "parser_1st.tab.c"
    break;

  case 383: /* POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  */
#line 1416 "parser_1st.y"
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
#line 5072 "parser_1st.tab.c"
    break;

  case 385: /* METHODDECLARATION: METHODHEADER METHODBODY  */
#line 1434 "parser_1st.y"
                                            {
    (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$1].name<<endl;
    
}
#line 5085 "parser_1st.tab.c"
    break;

  case 386: /* METHODDECLARATION: SUPER1 METHODHEADER METHODBODY  */
#line 1444 "parser_1st.y"
                                                      {
                        (yyval.val) =(yyvsp[-1].val);
                        method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5114 "parser_1st.tab.c"
    break;

  case 387: /* METHODDECLARATION: SUPER2 METHODHEADER METHODBODY  */
#line 1468 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5141 "parser_1st.tab.c"
    break;

  case 388: /* METHODDECLARATION: SUPER3 METHODHEADER METHODBODY  */
#line 1490 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5168 "parser_1st.tab.c"
    break;

  case 389: /* METHODDECLARATION: METHODMODIFIERS METHODHEADER METHODBODY  */
#line 1512 "parser_1st.y"
                                                               {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
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
#line 5195 "parser_1st.tab.c"
    break;

  case 395: /* METHODHEADER: TYPE METHODDECLARATOR  */
#line 1541 "parser_1st.y"
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
#line 5242 "parser_1st.tab.c"
    break;

  case 396: /* METHODHEADER: VOID METHODDECLARATOR  */
#line 1583 "parser_1st.y"
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
#line 5277 "parser_1st.tab.c"
    break;

  case 407: /* METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1628 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));              
                                        method_det[curr_class][chartostring((yyvsp[-2].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        // cout<<"methodhead "<<ds[chartonum($$)]["method_name"]<<"\n";
                                        }
#line 5290 "parser_1st.tab.c"
    break;

  case 408: /* METHODDECLARATOR: IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 1636 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                method_det[curr_class][chartostring((yyvsp[-3].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-3].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        for(auto i:ds2[curr3]["param"])
                                        code.push_back("pop param, "+ i);}
#line 5302 "parser_1st.tab.c"
    break;

  case 417: /* FORMALPARAMETERLIST: FORMALPARAMETER  */
#line 1653 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 5311 "parser_1st.tab.c"
    break;

  case 418: /* FORMALPARAMETERLIST: FORMALPARAMETERLIST COMMA FORMALPARAMETER  */
#line 1657 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 5321 "parser_1st.tab.c"
    break;

  case 419: /* FORMALPARAMETER: TYPE VARIABLEDECLARATORID  */
#line 1663 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 5330 "parser_1st.tab.c"
    break;

  case 421: /* FORMALPARAMETER: FINAL TYPE VARIABLEDECLARATORID  */
#line 1668 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 5339 "parser_1st.tab.c"
    break;

  case 424: /* METHODBODY: BLOCK  */
#line 1678 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 5345 "parser_1st.tab.c"
    break;

  case 428: /* BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 1685 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val);  }
#line 5351 "parser_1st.tab.c"
    break;

  case 430: /* BLOCKSTATEMENTS: BLOCKSTATEMENT  */
#line 1688 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val);  
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
#line 5359 "parser_1st.tab.c"
    break;

  case 431: /* BLOCKSTATEMENTS: BLOCKSTATEMENTS BLOCKSTATEMENT  */
#line 1691 "parser_1st.y"
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
#line 5374 "parser_1st.tab.c"
    break;

  case 433: /* BLOCKSTATEMENT: LOCALVARIABLEDECLARATIONSTATEMENT  */
#line 1703 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val); 
                
               }
#line 5382 "parser_1st.tab.c"
    break;

  case 434: /* BLOCKSTATEMENT: STATEMENT  */
#line 1706 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
               }
#line 5389 "parser_1st.tab.c"
    break;

  case 435: /* BLOCKSTATEMENT: PRINTLN  */
#line 1708 "parser_1st.y"
                            {code.push_back("print "+ chartostring((yyvsp[0].val)).substr(19,chartostring((yyvsp[0].val)).size() -21));}
#line 5395 "parser_1st.tab.c"
    break;

  case 437: /* LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  */
#line 1712 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 5401 "parser_1st.tab.c"
    break;

  case 438: /* LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1714 "parser_1st.y"
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
#line 5463 "parser_1st.tab.c"
    break;

  case 439: /* LOCALVARIABLEDECLARATION: LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1771 "parser_1st.y"
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
#line 5529 "parser_1st.tab.c"
    break;

  case 440: /* LOCALVARIABLETYPE: TYPE  */
#line 1833 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 5535 "parser_1st.tab.c"
    break;

  case 441: /* LOCALVARIABLETYPE: VAR  */
#line 1834 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5541 "parser_1st.tab.c"
    break;

  case 442: /* STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1837 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
#line 5547 "parser_1st.tab.c"
    break;

  case 443: /* STATEMENT: LABELEDSTATEMENT  */
#line 1838 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5553 "parser_1st.tab.c"
    break;

  case 444: /* STATEMENT: IFTHENSTATEMENT  */
#line 1839 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5559 "parser_1st.tab.c"
    break;

  case 445: /* STATEMENT: IFTHENELSESTATEMENT  */
#line 1840 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5565 "parser_1st.tab.c"
    break;

  case 446: /* STATEMENT: WHILESTATEMENT  */
#line 1841 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5571 "parser_1st.tab.c"
    break;

  case 447: /* STATEMENT: FORSTATEMENT  */
#line 1842 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5577 "parser_1st.tab.c"
    break;

  case 448: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  */
#line 1844 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5583 "parser_1st.tab.c"
    break;

  case 449: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EMPTYSTATEMENT  */
#line 1846 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5589 "parser_1st.tab.c"
    break;

  case 450: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EXPRESSIONSTATEMENT  */
#line 1847 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5595 "parser_1st.tab.c"
    break;

  case 451: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: ASSERTSTATEMENT  */
#line 1848 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5601 "parser_1st.tab.c"
    break;

  case 452: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BREAKSTATEMENT  */
#line 1849 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5607 "parser_1st.tab.c"
    break;

  case 453: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: CONTINUESTATEMENT  */
#line 1850 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5613 "parser_1st.tab.c"
    break;

  case 454: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: RETURNSTATEMENT  */
#line 1851 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5619 "parser_1st.tab.c"
    break;

  case 455: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: THROWSTATEMENT  */
#line 1852 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5625 "parser_1st.tab.c"
    break;

  case 456: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: YIELDSTATEMENT  */
#line 1853 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5631 "parser_1st.tab.c"
    break;

  case 457: /* EMPTYSTATEMENT: SEMICOLON  */
#line 1855 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5637 "parser_1st.tab.c"
    break;

  case 458: /* EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  */
#line 1857 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val); }
#line 5643 "parser_1st.tab.c"
    break;

  case 459: /* STATEMENTEXPRESSION: ASSIGNMENT  */
#line 1859 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5649 "parser_1st.tab.c"
    break;

  case 460: /* STATEMENTEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1860 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5655 "parser_1st.tab.c"
    break;

  case 461: /* STATEMENTEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1861 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5661 "parser_1st.tab.c"
    break;

  case 462: /* STATEMENTEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1862 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5667 "parser_1st.tab.c"
    break;

  case 463: /* STATEMENTEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1863 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5673 "parser_1st.tab.c"
    break;

  case 464: /* STATEMENTEXPRESSION: METHODINVOCATION  */
#line 1864 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5679 "parser_1st.tab.c"
    break;

  case 465: /* STATEMENTEXPRESSION: CLASSINSTANCECREATIONEXPRESSION  */
#line 1865 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5685 "parser_1st.tab.c"
    break;

  case 468: /* BREAKSTATEMENT: BREAK SEMICOLON  */
#line 1870 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5698 "parser_1st.tab.c"
    break;

  case 470: /* CONTINUESTATEMENT: CONTINUE SEMICOLON  */
#line 1880 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5711 "parser_1st.tab.c"
    break;

  case 472: /* RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  */
#line 1890 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5722 "parser_1st.tab.c"
    break;

  case 473: /* RETURNSTATEMENT: RETURN SEMICOLON  */
#line 1896 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 5733 "parser_1st.tab.c"
    break;

  case 477: /* IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1909 "parser_1st.y"
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
#line 5754 "parser_1st.tab.c"
    break;

  case 478: /* IFTHENELSESTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENT  */
#line 1926 "parser_1st.y"
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
#line 5770 "parser_1st.tab.c"
    break;

  case 479: /* IFTHENELSESTATEMENTNOSHORTIF: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF ELSE STATEMENTNOSHORTIF  */
#line 1938 "parser_1st.y"
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
#line 5786 "parser_1st.tab.c"
    break;

  case 480: /* STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1950 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5792 "parser_1st.tab.c"
    break;

  case 481: /* STATEMENTNOSHORTIF: LABELEDSTATEMENTNOSHORTIF  */
#line 1951 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5798 "parser_1st.tab.c"
    break;

  case 482: /* STATEMENTNOSHORTIF: IFTHENELSESTATEMENTNOSHORTIF  */
#line 1952 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5804 "parser_1st.tab.c"
    break;

  case 483: /* STATEMENTNOSHORTIF: WHILESTATEMENTNOSHORTIF  */
#line 1953 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5810 "parser_1st.tab.c"
    break;

  case 484: /* STATEMENTNOSHORTIF: FORSTATEMENTNOSHORTIF  */
#line 1954 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5816 "parser_1st.tab.c"
    break;

  case 486: /* WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1958 "parser_1st.y"
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
#line 5832 "parser_1st.tab.c"
    break;

  case 487: /* FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  */
#line 1970 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); popscope();}
#line 5838 "parser_1st.tab.c"
    break;

  case 488: /* FORSTATEMENTNOSHORTIF: ENHANCEDFORSTATEMENTNOSHORTIF  */
#line 1971 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5844 "parser_1st.tab.c"
    break;

  case 489: /* WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
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
}
#line 5859 "parser_1st.tab.c"
    break;

  case 490: /* FORSTATEMENT: BASICFORSTATEMENT  */
#line 1985 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5865 "parser_1st.tab.c"
    break;

  case 491: /* FORSTATEMENT: ENHANCEDFORSTATEMENT  */
#line 1986 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5871 "parser_1st.tab.c"
    break;

  case 492: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 1988 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 5884 "parser_1st.tab.c"
    break;

  case 493: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 1996 "parser_1st.y"
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
#line 5900 "parser_1st.tab.c"
    break;

  case 494: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2007 "parser_1st.y"
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
#line 5919 "parser_1st.tab.c"
    break;

  case 495: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2021 "parser_1st.y"
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
#line 5940 "parser_1st.tab.c"
    break;

  case 496: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 2037 "parser_1st.y"
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
#line 5958 "parser_1st.tab.c"
    break;

  case 497: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2050 "parser_1st.y"
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
#line 5979 "parser_1st.tab.c"
    break;

  case 498: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2066 "parser_1st.y"
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
#line 6000 "parser_1st.tab.c"
    break;

  case 499: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2082 "parser_1st.y"
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
#line 6021 "parser_1st.tab.c"
    break;

  case 500: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2099 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6034 "parser_1st.tab.c"
    break;

  case 501: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2107 "parser_1st.y"
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
#line 6050 "parser_1st.tab.c"
    break;

  case 502: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2118 "parser_1st.y"
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
#line 6069 "parser_1st.tab.c"
    break;

  case 503: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2132 "parser_1st.y"
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
#line 6091 "parser_1st.tab.c"
    break;

  case 504: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2149 "parser_1st.y"
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
#line 6109 "parser_1st.tab.c"
    break;

  case 505: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2162 "parser_1st.y"
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
#line 6130 "parser_1st.tab.c"
    break;

  case 506: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2178 "parser_1st.y"
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
#line 6152 "parser_1st.tab.c"
    break;

  case 507: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2195 "parser_1st.y"
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
#line 6173 "parser_1st.tab.c"
    break;

  case 510: /* FORINIT: STATEMENTEXPRESSIONLIST  */
#line 2217 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 6179 "parser_1st.tab.c"
    break;

  case 511: /* FORINIT: LOCALVARIABLEDECLARATION  */
#line 2218 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 6185 "parser_1st.tab.c"
    break;

  case 512: /* FORUPDATE: STATEMENTEXPRESSIONLIST  */
#line 2220 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 6199 "parser_1st.tab.c"
    break;

  case 513: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION  */
#line 2230 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 6205 "parser_1st.tab.c"
    break;

  case 514: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION  */
#line 2231 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 6217 "parser_1st.tab.c"
    break;

  case 552: /* SUPER1: PUBLIC  */
#line 2284 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6223 "parser_1st.tab.c"
    break;

  case 553: /* SUPER1: PRIVATE  */
#line 2285 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6229 "parser_1st.tab.c"
    break;

  case 554: /* SUPER1: PROTECTED  */
#line 2286 "parser_1st.y"
                    {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6235 "parser_1st.tab.c"
    break;

  case 555: /* SUPER1: SUPER1 PUBLIC  */
#line 2287 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6241 "parser_1st.tab.c"
    break;

  case 556: /* SUPER1: SUPER1 PRIVATE  */
#line 2288 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6247 "parser_1st.tab.c"
    break;

  case 557: /* SUPER1: SUPER1 PROTECTED  */
#line 2289 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6253 "parser_1st.tab.c"
    break;

  case 558: /* SUPER2: STATIC  */
#line 2291 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6259 "parser_1st.tab.c"
    break;

  case 559: /* SUPER2: FINAL  */
#line 2292 "parser_1st.y"
                 {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6265 "parser_1st.tab.c"
    break;

  case 560: /* SUPER2: SUPER1 STATIC  */
#line 2293 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6271 "parser_1st.tab.c"
    break;

  case 561: /* SUPER2: SUPER1 FINAL  */
#line 2294 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6277 "parser_1st.tab.c"
    break;

  case 562: /* SUPER2: SUPER2 STATIC  */
#line 2295 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6283 "parser_1st.tab.c"
    break;

  case 563: /* SUPER2: SUPER2 FINAL  */
#line 2296 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6289 "parser_1st.tab.c"
    break;

  case 564: /* SUPER2: SUPER2 PUBLIC  */
#line 2297 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6295 "parser_1st.tab.c"
    break;

  case 565: /* SUPER2: SUPER2 PRIVATE  */
#line 2298 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6301 "parser_1st.tab.c"
    break;

  case 566: /* SUPER2: SUPER2 PROTECTED  */
#line 2299 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6307 "parser_1st.tab.c"
    break;

  case 567: /* SUPER3: ABSTRACT  */
#line 2301 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6313 "parser_1st.tab.c"
    break;

  case 568: /* SUPER3: STRICTFP  */
#line 2302 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6319 "parser_1st.tab.c"
    break;

  case 569: /* SUPER3: SUPER2 ABSTRACT  */
#line 2303 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6325 "parser_1st.tab.c"
    break;

  case 570: /* SUPER3: SUPER2 STRICTFP  */
#line 2304 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6331 "parser_1st.tab.c"
    break;

  case 571: /* SUPER3: SUPER3 ABSTRACT  */
#line 2305 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6337 "parser_1st.tab.c"
    break;

  case 572: /* SUPER3: SUPER3 STRICTFP  */
#line 2306 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6343 "parser_1st.tab.c"
    break;

  case 573: /* SUPER3: SUPER3 PUBLIC  */
#line 2307 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6349 "parser_1st.tab.c"
    break;

  case 574: /* SUPER3: SUPER3 PRIVATE  */
#line 2308 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6355 "parser_1st.tab.c"
    break;

  case 575: /* SUPER3: SUPER3 PROTECTED  */
#line 2309 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6361 "parser_1st.tab.c"
    break;

  case 576: /* SUPER3: SUPER3 STATIC  */
#line 2310 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6367 "parser_1st.tab.c"
    break;

  case 577: /* SUPER3: SUPER3 FINAL  */
#line 2311 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6373 "parser_1st.tab.c"
    break;

  case 578: /* FIELDMODIFIERS: SUPER3 TRANSIENT  */
#line 2313 "parser_1st.y"
                                 {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6379 "parser_1st.tab.c"
    break;

  case 579: /* FIELDMODIFIERS: SUPER3 VOLATILE  */
#line 2314 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6385 "parser_1st.tab.c"
    break;

  case 580: /* FIELDMODIFIERS: FIELDMODIFIERS TRANSIENT  */
#line 2315 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6391 "parser_1st.tab.c"
    break;

  case 581: /* FIELDMODIFIERS: FIELDMODIFIERS VOLATILE  */
#line 2316 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6397 "parser_1st.tab.c"
    break;

  case 582: /* FIELDMODIFIERS: FIELDMODIFIERS PUBLIC  */
#line 2317 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6403 "parser_1st.tab.c"
    break;

  case 583: /* FIELDMODIFIERS: FIELDMODIFIERS PRIVATE  */
#line 2318 "parser_1st.y"
                                     {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6409 "parser_1st.tab.c"
    break;

  case 584: /* FIELDMODIFIERS: FIELDMODIFIERS PROTECTED  */
#line 2319 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6415 "parser_1st.tab.c"
    break;

  case 585: /* FIELDMODIFIERS: FIELDMODIFIERS STATIC  */
#line 2320 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6421 "parser_1st.tab.c"
    break;

  case 586: /* FIELDMODIFIERS: FIELDMODIFIERS FINAL  */
#line 2321 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6427 "parser_1st.tab.c"
    break;

  case 587: /* METHODMODIFIERS: SUPER3 SYNCHRONIZED  */
#line 2324 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6433 "parser_1st.tab.c"
    break;

  case 588: /* METHODMODIFIERS: SUPER3 NATIVE  */
#line 2325 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6439 "parser_1st.tab.c"
    break;

  case 589: /* METHODMODIFIERS: METHODMODIFIERS SYNCHRONIZED  */
#line 2326 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6445 "parser_1st.tab.c"
    break;

  case 590: /* METHODMODIFIERS: METHODMODIFIERS NATIVE  */
#line 2327 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6451 "parser_1st.tab.c"
    break;

  case 591: /* METHODMODIFIERS: METHODMODIFIERS ABSTRACT  */
#line 2328 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6457 "parser_1st.tab.c"
    break;

  case 592: /* METHODMODIFIERS: METHODMODIFIERS STRICTFP  */
#line 2329 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6463 "parser_1st.tab.c"
    break;

  case 593: /* METHODMODIFIERS: METHODMODIFIERS PUBLIC  */
#line 2330 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6469 "parser_1st.tab.c"
    break;

  case 594: /* METHODMODIFIERS: METHODMODIFIERS PRIVATE  */
#line 2331 "parser_1st.y"
                                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6475 "parser_1st.tab.c"
    break;

  case 595: /* METHODMODIFIERS: METHODMODIFIERS PROTECTED  */
#line 2332 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6481 "parser_1st.tab.c"
    break;

  case 596: /* METHODMODIFIERS: METHODMODIFIERS STATIC  */
#line 2333 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6487 "parser_1st.tab.c"
    break;

  case 597: /* METHODMODIFIERS: METHODMODIFIERS FINAL  */
#line 2334 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6493 "parser_1st.tab.c"
    break;

  case 601: /* TYPEARGUMENT: REFERENCETYPE  */
#line 2341 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 6499 "parser_1st.tab.c"
    break;

  case 602: /* TYPEARGUMENT: WILDCARD  */
#line 2342 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 6505 "parser_1st.tab.c"
    break;

  case 607: /* INTERFACETYPE: CLASSTYPE  */
#line 2351 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 6511 "parser_1st.tab.c"
    break;


#line 6515 "parser_1st.tab.c"

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

#line 2353 "parser_1st.y"



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
