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
  YYSYMBOL_TEMP = 253,                     /* TEMP  */
  YYSYMBOL_STATEMENTNOSHORTIF = 254,       /* STATEMENTNOSHORTIF  */
  YYSYMBOL_LABELEDSTATEMENTNOSHORTIF = 255, /* LABELEDSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENTNOSHORTIF = 256,  /* WHILESTATEMENTNOSHORTIF  */
  YYSYMBOL_FORSTATEMENTNOSHORTIF = 257,    /* FORSTATEMENTNOSHORTIF  */
  YYSYMBOL_WHILESTATEMENT = 258,           /* WHILESTATEMENT  */
  YYSYMBOL_FORSTATEMENT = 259,             /* FORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENT = 260,        /* BASICFORSTATEMENT  */
  YYSYMBOL_BASICFORSTATEMENTNOSHORTIF = 261, /* BASICFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_ENHANCEDFORSTATEMENT = 262,     /* ENHANCEDFORSTATEMENT  */
  YYSYMBOL_ENHANCEDFORSTATEMENTNOSHORTIF = 263, /* ENHANCEDFORSTATEMENTNOSHORTIF  */
  YYSYMBOL_FORINIT = 264,                  /* FORINIT  */
  YYSYMBOL_FORUPDATE = 265,                /* FORUPDATE  */
  YYSYMBOL_STATEMENTEXPRESSIONLIST = 266,  /* STATEMENTEXPRESSIONLIST  */
  YYSYMBOL_CONSTRUCTORDECLARATION = 267,   /* CONSTRUCTORDECLARATION  */
  YYSYMBOL_CONSTRUCTORDECLARATOR = 268,    /* CONSTRUCTORDECLARATOR  */
  YYSYMBOL_SIMPLETYPENAME = 269,           /* SIMPLETYPENAME  */
  YYSYMBOL_CONSTRUCTORBODY = 270,          /* CONSTRUCTORBODY  */
  YYSYMBOL_EXPLICITCONSTRUCTORINVOCATION = 271, /* EXPLICITCONSTRUCTORINVOCATION  */
  YYSYMBOL_SUPER1 = 272,                   /* SUPER1  */
  YYSYMBOL_SUPER2 = 273,                   /* SUPER2  */
  YYSYMBOL_SUPER3 = 274,                   /* SUPER3  */
  YYSYMBOL_FIELDMODIFIERS = 275,           /* FIELDMODIFIERS  */
  YYSYMBOL_METHODMODIFIERS = 276,          /* METHODMODIFIERS  */
  YYSYMBOL_TYPEARGUMENTS = 277,            /* TYPEARGUMENTS  */
  YYSYMBOL_TYPEARGUMENTLIST = 278,         /* TYPEARGUMENTLIST  */
  YYSYMBOL_TYPEARGUMENT = 279,             /* TYPEARGUMENT  */
  YYSYMBOL_WILDCARD = 280,                 /* WILDCARD  */
  YYSYMBOL_WILDCARDBOUNDS = 281,           /* WILDCARDBOUNDS  */
  YYSYMBOL_INTERFACETYPE = 282             /* INTERFACETYPE  */
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
#define YYLAST   6576

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  155
/* YYNRULES -- Number of rules.  */
#define YYNRULES  608
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
     625,   653,   693,   705,   729,   765,   767,   775,   782,   783,
     785,   787,   790,   792,   807,   808,   816,   817,   821,   823,
     825,   827,   829,   831,   834,   841,   842,   844,   847,   849,
     850,   851,   855,   856,   857,   858,   859,   860,   861,   863,
     864,   865,   866,   867,   868,   869,   871,   872,   873,   874,
     875,   876,   877,   879,   880,   882,   883,   884,   885,   887,
     888,   889,   890,   891,   892,   893,   894,   896,   899,   903,
     912,   924,   943,   967,   994,   995,   996,   997,   998,   999,
    1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,  1009,
    1010,  1011,  1013,  1014,  1015,  1016,  1017,  1019,  1020,  1022,
    1023,  1024,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,
    1034,  1035,  1037,  1038,  1040,  1041,  1042,  1044,  1045,  1049,
    1051,  1052,  1058,  1059,  1082,  1096,  1097,  1099,  1100,  1114,
    1115,  1125,  1126,  1135,  1136,  1144,  1145,  1155,  1163,  1179,
    1197,  1202,  1220,  1234,  1248,  1262,  1264,  1265,  1274,  1282,
    1291,  1292,  1300,  1309,  1310,  1318,  1326,  1335,  1336,  1337,
    1340,  1348,  1350,  1364,  1378,  1379,  1387,  1396,  1397,  1398,
    1412,  1413,  1415,  1428,  1443,  1446,  1457,  1482,  1506,  1530,
    1554,  1555,  1556,  1557,  1558,  1561,  1605,  1635,  1636,  1637,
    1638,  1639,  1640,  1643,  1645,  1646,  1648,  1650,  1658,  1666,
    1667,  1668,  1669,  1670,  1671,  1673,  1674,  1676,  1680,  1686,
    1690,  1691,  1697,  1698,  1701,  1702,  1704,  1706,  1708,  1709,
    1711,  1714,  1725,  1727,  1730,  1732,  1734,  1791,  1853,  1854,
    1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,  1868,  1870,
    1871,  1872,  1873,  1874,  1875,  1876,  1877,  1879,  1881,  1883,
    1884,  1885,  1886,  1887,  1888,  1889,  1891,  1892,  1894,  1902,
    1904,  1912,  1914,  1920,  1927,  1929,  1931,  1933,  1950,  1965,
    1992,  2004,  2005,  2006,  2007,  2008,  2010,  2012,  2024,  2025,
    2028,  2039,  2040,  2042,  2050,  2061,  2075,  2091,  2104,  2120,
    2136,  2153,  2161,  2172,  2186,  2203,  2216,  2232,  2249,  2267,
    2269,  2271,  2272,  2274,  2284,  2285,  2294,  2295,  2296,  2297,
    2300,  2301,  2302,  2303,  2304,  2305,  2306,  2307,  2310,  2312,
    2313,  2314,  2315,  2317,  2318,  2319,  2320,  2321,  2322,  2323,
    2324,  2325,  2326,  2327,  2328,  2329,  2330,  2331,  2332,  2333,
    2334,  2335,  2336,  2338,  2339,  2340,  2341,  2342,  2343,  2345,
    2346,  2347,  2348,  2349,  2350,  2351,  2352,  2353,  2355,  2356,
    2357,  2358,  2359,  2360,  2361,  2362,  2363,  2364,  2365,  2367,
    2368,  2369,  2370,  2371,  2372,  2373,  2374,  2375,  2378,  2379,
    2380,  2381,  2382,  2383,  2384,  2385,  2386,  2387,  2388,  2390,
    2392,  2393,  2395,  2396,  2398,  2399,  2401,  2402,  2405
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
  "IFTHENELSESTATEMENTNOSHORTIF", "TEMP", "STATEMENTNOSHORTIF",
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

#define YYPACT_NINF (-766)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-529)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1375,  -766,   -55,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
     -18,    32,  -766,   164,  1988,  -766,  2452,  -766,  -766,  -766,
    -766,   665,  1056,  1719,   397,   182,   179,   273,   173,   354,
    -766,  -766,  -766,  -766,   202,  -766,  -766,  -766,  -766,  -766,
     211,   254,  -766,  -766,  -766,  -766,  -766,  -766,  -766,   258,
     271,  -766,  -766,  -766,  -766,  -766,  -766,  -766,   284,   286,
     295,   295,   326,   379,   290,    43,   182,  -766,  6078,  -766,
     225,   330,  -766,    16,  3516,  -766,   379,   290,    43,   182,
     397,   182,   354,   397,   182,   354,   397,   182,   354,   288,
     385,  -766,  -766,  -766,  -766,  -766,   347,  -766,  -766,   457,
     290,    43,   182,  -766,    43,   182,  -766,   182,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
     476,   182,   391,   503,   422,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  3480,  -766,  -766,  1147,  6078,  -766,  -766,
    -766,  -766,    71,  -766,  -766,  -766,  -766,    12,   543,  4311,
    1009,  2371,  1487,  3336,  -766,    84,  -766,   536,  -766,  -766,
     947,   391,  -766,  -766,  3516,  -766,  1224,  -766,   818,  4177,
    3807,  -766,   290,    43,   182,  -766,    43,   182,  -766,   182,
    -766,   379,   290,    43,   182,  -766,  -766,   379,   290,    43,
     182,   379,   290,    43,   182,  -766,  -766,   379,   290,    43,
     182,   379,   290,    43,   182,  -766,  -766,   379,   290,    43,
     182,   455,  -766,   286,  -766,   295,   488,    43,   182,  -766,
     182,  -766,  -766,   182,  -766,  -766,  -766,  4434,  -766,  1641,
     542,   527,   471,  -766,   566,   542,    26,  -766,  5848,  5911,
    5911,  -766,  -766,  -766,  -766,  -766,  -766,  -766,    39,  1516,
    -766,   444,  1763,  5848,  5848,  -766,    14,    15,  3847,  5848,
     608,   624,  -766,  -766,   547,  -766,    37,   630,   657,   578,
    -766,   672,  -766,  -766,   939,   956,   270,   632,  -766,  -766,
     316,  -766,   438,  -766,  -766,   968,  -766,  -766,   389,   395,
     494,  -766,  3480,  -766,  -766,  -766,   699,   590,  -766,  -766,
    -766,  -766,   713,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,   658,  -766,  -766,  -766,  -766,   861,   748,   800,
     391,   391,   725,  -766,  -766,  -766,  -766,  -766,   295,  3310,
     182,  -766,   551,   422,    71,    12,   422,    71,  -766,  -766,
    -766,  -766,    71,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
     590,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,
      71,   734,  -766,    71,  -766,  -766,   422,  -766,    43,   182,
    -766,   182,  -766,  -766,   182,  -766,  -766,   290,    43,   182,
    -766,    43,   182,  -766,   182,  -766,  -766,  -766,   290,    43,
     182,  -766,    43,   182,  -766,   182,  -766,   290,    43,   182,
    -766,    43,   182,  -766,   182,  -766,  -766,  -766,   290,    43,
     182,  -766,    43,   182,  -766,   182,  -766,   290,    43,   182,
    -766,    43,   182,  -766,   182,  -766,  -766,  -766,   290,    43,
     182,  -766,    43,   182,  -766,   182,  -766,   716,   719,  -766,
    -766,  -766,   182,  -766,  -766,  -766,  -766,    71,  2159,  4557,
    3930,  3336,   972,   -31,   756,  -766,   758,   757,   590,  -766,
    3910,  -766,   775,  -766,    40,    26,  5911,  5911,  5911,  5911,
    1599,    37,   630,   769,  -766,  -766,  -766,  -766,  -766,   198,
     751,   761,   764,   766,   523,   278,   733,   582,   771,  -766,
    -766,  -766,  -766,   389,  -766,  -766,  -766,    46,    59,  -766,
    -766,  -766,  -766,     4,    63,   590,  -766,     2,   795,   801,
     801,   809,   696,   817,   222,  -766,   819,  -766,   825,  -766,
     826,   832,  5848,  5848,  3970,  3615,    79,  -766,    80,  -766,
      83,    73,  2297,  5848,   116,  5971,  -766,  -766,  -766,  -766,
    -766,  -766,  5848,   100,   118,  5848,  -766,  -766,  -766,  -766,
    -766,   828,   838,  -766,  3615,   542,   542,  1303,  -766,   839,
    -766,    53,   834,   620,   329,  -766,   297,  3480,  3480,   224,
    -766,  -766,  1870,    22,   844,   239,  -766,  -766,   577,  -766,
     182,  -766,   588,  -766,  -766,   636,  -766,  -766,  -766,   663,
    -766,   182,  -766,  -766,  -766,    43,   182,  -766,   182,  -766,
    -766,   182,  -766,  -766,  -766,  -766,    43,   182,  -766,   182,
    -766,  -766,   182,  -766,  -766,    43,   182,  -766,   182,  -766,
    -766,   182,  -766,  -766,  -766,  -766,    43,   182,  -766,   182,
    -766,  -766,   182,  -766,  -766,    43,   182,  -766,   182,  -766,
    -766,   182,  -766,  -766,  -766,  -766,    43,   182,  -766,   182,
    -766,  -766,   182,  -766,  -766,   295,   814,  -766,  -766,    71,
      71,    71,    71,   828,    49,   364,  -766,   823,   851,  -766,
     854,  -766,  3787,  -766,  -766,  -766,  -766,   855,  -766,  -766,
    -766,  -766,  -766,  -766,  5848,  5911,  5911,  5911,  5911,  5911,
    5911,  5911,  4033,  4093,   295,  5911,  5911,  5911,  5911,  5911,
    5911,  5911,  5911,  -766,   753,   859,   760,   838,   628,  -766,
     411,  -766,  -766,  4156,   336,   801,  -766,   336,   801,  4216,
    -766,   860,  -766,  -766,  5848,  -766,  -766,  -766,  -766,   864,
     869,   878,  1516,  -766,   302,  -766,   103,   879,  -766,   776,
    -766,  -766,  -766,  -766,     0,  -766,  -766,   396,   882,   883,
    -766,   778,  4290,   866,  -766,   899,   904,  -766,  -766,   792,
     897,  -766,   796,   902,  -766,  -766,  -766,  -766,   916,   412,
     295,  4350,  4413,   185,    18,    38,  -766,  -766,  3480,   912,
     914,    64,   811,   234,  -766,  1324,  1831,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,   182,  -766,  -766,  -766,  -766,  -766,
     182,  -766,  -766,  -766,   182,  -766,  -766,  -766,  -766,  -766,
     182,  -766,  -766,  -766,   182,  -766,  -766,  -766,  -766,  -766,
     182,  -766,  -766,  -766,  -766,   295,  -766,  -766,  -766,  -766,
     757,   828,   863,  1412,  -766,  -766,  -766,  -766,   923,   928,
    -766,   900,   751,   761,   764,   766,   523,   278,   278,  5911,
     733,  5911,   733,  -766,   582,   582,   582,   771,   771,  -766,
    -766,  -766,  -766,  4473,   921,   295,   295,  -766,     2,  -766,
     924,  -766,   757,  -766,  -766,   757,   182,   413,  4536,   931,
    3701,  3615,  -766,   113,   166,  4596,   942,  -766,  -766,  5848,
    -766,  -766,  4659,   944,  6102,   935,  5848,  4719,  6452,  -766,
    4782,   952,  -766,  1508,  -766,  -766,   961,   445,   977,   446,
     233,    -2,   981,   158,   987,   159,  -766,  4842,  4905,   884,
    -766,  -766,  -766,   451,  -766,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,   757,  -766,   828,   458,  -766,  3910,  5911,   733,
     733,  -766,   460,  4965,  -766,  -766,  -766,  -766,  -766,   182,
     182,   474,  -766,   991,   639,  1000,  -766,   936,  -766,   941,
    -766,  -766,  -766,  -766,  -766,  -766,  -766,  -766,   903,  1004,
     905,  -766,   529,  5028,  -766,  -766,   532,  5088,  3615,  1007,
     904,  6180,  1011,  6203,  1017,  -766,  -766,   560,  5151,  -766,
     563,  -766,  1020,  -766,  1021,  5211,  1015,  5274,  1018,  5334,
    1019,  1027,   571,  1028,   593,  -766,  -766,   757,   828,  -766,
    -766,  -766,  -766,   634,  -766,  -766,   182,  5848,  3701,  6001,
    3701,  -766,  5397,  1023,  -766,  -766,   635,  -766,  -766,   637,
    -766,  3615,  3615,  1024,  3615,  3615,  1025,  6263,  -766,  -766,
     642,  -766,  -766,  -766,  1036,   659,  5457,  1037,   670,  5520,
    1038,   682,  5580,  -766,  1044,  -766,  1045,   757,  -766,  -766,
    1039,  -766,  5654,  1022,  1046,  -766,  -766,   702,  5714,  -766,
    -766,  -766,  -766,  3615,  -766,  -766,  3615,  3615,  1040,  -766,
    -766,  1050,  1051,   704,  -766,  1053,  1054,   727,  -766,  1055,
    1057,   731,  -766,  -766,  3701,  6286,  1062,  5848,  5788,  -766,
    -766,   755,  -766,  -766,  -766,  3615,  -766,  -766,  1067,  -766,
    -766,  1068,  -766,  -766,  1069,  -766,  3701,  1064,  6346,  1065,
    6369,  1075,  -766,  -766,  -766,  -766,  -766,  -766,  3701,  3701,
    1071,  3701,  3701,  1072,  6429,  -766,  -766,  3701,  -766,  -766,
    3701,  3701,  1073,  -766,  -766,  -766,  3701,  -766
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,    29,     0,   553,   554,   555,   559,   560,   568,   569,
       0,     0,     2,     0,     0,    26,     0,    28,    36,   178,
      31,     0,     0,     0,   101,     0,     0,     0,     0,     0,
       1,     3,    27,    30,     0,   556,   557,   558,   561,   562,
       0,     0,   565,   566,   567,   563,   564,   570,   571,     0,
       0,   574,   575,   576,   577,   578,   572,   573,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   167,     0,    37,
       0,     0,    32,     0,     0,   117,     0,     0,     0,     0,
     101,     0,     0,   101,     0,     0,   101,     0,     0,   183,
       0,   180,    20,   188,    19,   608,   189,   190,   193,   192,
       0,     0,     0,    48,     0,     0,    52,     0,    54,    55,
       7,    10,    11,    12,    13,    14,    15,    16,   206,   168,
       0,   559,     0,    20,     0,     4,     6,     8,     9,     5,
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
       0,   249,   250,   251,   252,   253,   254,   255,     0,   560,
     241,     0,     0,     0,     0,   439,     0,     0,     0,     0,
       0,     0,   166,   446,   225,   438,     6,    18,     0,   378,
     434,     0,   429,   459,     0,   245,   377,   237,   239,   240,
     244,   265,   247,   248,   238,   246,   460,   461,     0,   462,
     463,   448,     0,   430,   432,   447,     0,     0,   433,   440,
     449,   450,     0,   451,   452,   453,   454,   455,   456,   441,
     442,   443,     0,   444,   445,   491,   492,     0,     0,     0,
       0,     0,     0,   196,   198,   425,   385,   424,     0,     0,
       0,   517,     0,     0,     0,     0,     0,     0,   579,   580,
     588,   589,     0,   583,   584,   585,   586,   587,   581,   582,
       0,   594,   595,   596,   597,   598,   592,   590,   591,   593,
       0,     0,    33,     0,   170,   172,     0,   105,     0,     0,
     107,     0,   108,   111,     0,   112,   114,     0,     0,     0,
      63,     0,     0,    67,     0,    69,    70,   125,     0,     0,
       0,   129,     0,     0,   131,     0,   132,     0,     0,     0,
      78,     0,     0,    82,     0,    84,    85,   141,     0,     0,
       0,   145,     0,     0,   147,     0,   148,     0,     0,     0,
      93,     0,     0,    97,     0,    99,   100,   157,     0,     0,
       0,   161,     0,     0,   163,     0,   164,   184,     0,   181,
     191,   194,     0,    42,    43,    45,    49,     0,     0,     0,
       0,     0,     0,     0,     0,   400,     0,   217,     0,   211,
       0,   397,     0,   258,     0,     0,     0,     0,     0,     0,
     379,     0,     0,     0,   220,   222,   244,   247,   221,   335,
     337,   339,   341,   343,   345,   347,   350,   356,   360,   363,
     367,   368,   371,   374,   380,   381,   355,   379,   378,   245,
     246,   372,   373,     0,     0,     0,   259,     0,    20,   320,
     321,     0,     0,     0,     0,   468,     0,   470,     0,   473,
       0,     0,     0,     0,     0,     0,     0,   256,     0,   257,
       0,     0,     0,     0,     0,     0,   228,   229,   230,   231,
     232,   233,     0,     0,     0,     0,   382,   383,   428,   431,
     435,   216,   437,   458,     0,   402,   399,     0,   406,   403,
     404,     0,   241,   225,   224,   532,   377,     0,     0,     0,
     516,   520,     0,     0,     0,     0,   417,   420,     0,   386,
       0,   519,     0,   387,   388,     0,   389,    35,   174,     0,
     103,     0,   104,   106,   110,     0,     0,    59,     0,    61,
      62,     0,    65,    66,    68,   121,     0,     0,   123,     0,
     124,   127,     0,   128,   130,     0,     0,    74,     0,    76,
      77,     0,    80,    81,    83,   137,     0,     0,   139,     0,
     140,   143,     0,   144,   146,     0,     0,    89,     0,    91,
      92,     0,    95,    96,    98,   153,     0,     0,   155,     0,
     156,   159,     0,   160,   162,     0,   185,    41,   390,     0,
       0,     0,     0,   407,     0,     0,   415,     0,     0,    21,
       0,   213,     0,   214,   218,   219,   263,     0,   262,   369,
     370,   376,   375,   243,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   309,     0,   235,     0,   436,   604,   602,
       0,   600,   603,     0,   318,   316,   327,   319,   317,     0,
     277,     0,   474,   466,     0,   469,   471,   472,   475,     0,
       0,     0,     0,   476,     0,   242,     0,    24,   267,     0,
     260,   261,   311,   307,     0,   280,   278,     0,     0,    25,
     266,     0,     0,   512,   514,     0,   511,   223,   308,     0,
     234,   268,     0,     0,   478,   401,   398,   524,     0,     0,
       0,     0,     0,     0,     0,     0,   531,   530,     0,     0,
       0,     0,     0,   216,   419,     0,     0,   521,   209,   518,
     210,   208,   175,   102,     0,    57,    58,    60,    64,   119,
       0,   120,   122,   126,     0,    72,    73,    75,    79,   135,
       0,   136,   138,   142,     0,    87,    88,    90,    94,   151,
       0,   152,   154,   158,   186,     0,   391,   392,   393,   394,
     410,   408,     0,     0,    22,   325,   323,   330,     0,   324,
     264,     0,   338,   340,   342,   344,   346,   348,   349,     0,
     351,     0,   352,   384,   357,   358,   359,   361,   362,   365,
     364,   366,   304,     0,     0,     0,     0,   605,     0,   599,
       0,   314,   312,   328,   315,   313,   269,     0,     0,     0,
       0,     0,   334,     0,     0,     0,     0,   306,   303,     0,
     281,   332,     0,     0,     0,     0,     0,     0,     0,   302,
       0,     0,   333,     0,   525,   405,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   529,     0,     0,     0,
     421,   422,   522,     0,   418,    56,   118,    71,   134,    86,
     150,   187,   412,   416,   409,     0,   322,   326,     0,   354,
     353,   294,     0,     0,   606,   607,   601,   329,   270,   271,
     273,     0,   467,     0,   225,     0,   477,   440,   483,     0,
     480,   482,   484,   485,   488,   489,   490,   310,     0,   236,
       0,   282,     0,     0,   279,   286,     0,     0,     0,     0,
     513,     0,     0,     0,     0,   515,   290,     0,     0,   526,
       0,   537,     0,   533,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   423,   523,   411,   414,   331,
     336,   295,   296,     0,   272,   274,   275,     0,     0,     0,
       0,   305,     0,     0,   283,   284,     0,   287,   288,     0,
     493,     0,     0,     0,     0,     0,     0,     0,   291,   292,
       0,   527,   538,   534,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   539,     0,   535,     0,   413,   297,   276,
       0,   486,     0,   512,     0,   479,   298,     0,     0,   285,
     289,   494,   495,     0,   509,   497,     0,     0,     0,   293,
     545,     0,     0,     0,   541,     0,     0,     0,   549,     0,
       0,     0,   540,   536,     0,     0,     0,     0,     0,   299,
     300,     0,   496,   498,   499,     0,   546,   547,     0,   542,
     543,     0,   550,   551,     0,   487,     0,     0,     0,     0,
       0,     0,   301,   500,   548,   544,   552,   501,     0,     0,
       0,     0,     0,     0,     0,   502,   503,     0,   510,   505,
       0,     0,     0,   504,   506,   507,     0,   508
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -766,  -766,    62,   837,   604,  -766,  -766,  -494,    23,   337,
    -766,  -479,  -766,     9,  -766,   351,  -766,   151,  -766,   375,
    -766,  -336,   -29,   -59,  2406,  -766,   933,   134,   436,  -766,
     892,  -766,  -766,  1196,  3084,  -766,  3041,  -766,  2567,  -766,
     958,  -766,  -766,  -143,   651,  -537,  -669,   194,  -766,   469,
    -766,  -766,   492,   781,  -766,  -766,  -766,  -220,   681,  -463,
     602,  1959,   812,  -766,  -766,  -234,  -766,   606,  -198,  -766,
    1337,   180,  -766,   442,   448,   441,   447,   443,    30,  -675,
     146,    52,  -202,   973,  1117,  -766,  1291,  1435,  1606,  -766,
      -7,  -128,  -223,  -766,   360,  -116,  -328,  -442,   350,  -766,
    -272,  -766,  -766,   -35,  -327,  -287,  -766,  -766,  -527,  -238,
    1943,  -218,  -766,  -766,  -259,  -766,  -766,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,   129,  -702,  -766,  -766,  -766,
    -766,  -766,  -766,  -766,  -766,  -766,   119,  -765,  -526,  -766,
     988,  1006,  -306,  -766,   109,   117,   121,  -766,   913,  -247,
    -766,   275,  -766,  -766,  -214
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,   265,   125,   471,   127,   128,   129,   130,   472,
      94,   457,   268,   269,    14,    15,    16,   270,    18,    25,
      19,   271,    68,   134,    75,   164,   165,    20,   166,    90,
      91,   212,   656,    64,    65,    96,    66,    99,    69,   137,
     138,   139,   140,   232,   233,   234,   673,   746,   474,   475,
     274,   542,   275,   276,   277,   278,   279,   528,   476,   281,
     511,   747,   477,   283,   284,   675,   838,   715,   716,   839,
     285,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     141,   142,   330,   559,   560,   235,   454,   575,   576,   577,
     326,   143,   144,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   958,   312,   960,   961,   962,   963,
     313,   314,   315,   964,   316,   965,   755,   979,   980,   146,
     147,   148,   331,   568,   317,   318,   319,   152,   153,   512,
     710,   711,   712,   867,    97
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,   440,   567,   837,   574,   549,   230,   455,   753,   756,
     665,   505,   461,   709,   708,   163,   464,   850,   852,    28,
     507,   334,   337,   342,   570,   360,    67,   515,   517,   581,
     714,   717,   363,   145,   507,    70,   784,   501,   502,   133,
     334,   337,   342,   666,   462,   782,   530,    74,    74,    74,
      74,    26,   157,    74,   507,   462,    74,    67,   677,    74,
     996,   503,   579,   738,   524,   583,   -23,   167,   -20,    24,
     584,   750,   782,   771,   272,   503,   887,   533,   323,   507,
     912,   761,   569,   504,   325,    67,   228,   919,   586,   507,
     526,   588,   133,   667,   736,   507,   666,   504,   677,   447,
     914,   677,   145,   534,   133,   364,    27,   327,   133,    21,
      62,   328,   580,   133,   736,   769,   507,    22,   329,   507,
     361,    23,   886,    21,   888,    21,    92,   784,   703,   507,
     124,    22,   507,    22,   507,    23,   161,    23,   516,   518,
     158,   734,   749,    74,    74,    74,   783,    74,    74,   742,
      74,    17,   463,   735,   552,   736,    29,   167,    74,    74,
      74,    74,   760,   529,    30,    17,   678,    17,    74,    74,
      74,    74,   527,   551,   939,   658,   940,   149,    74,    74,
      74,    74,   507,   168,   830,   150,    72,   705,   551,   151,
     578,   169,   736,   582,   736,   170,    67,   743,   321,   124,
     853,   507,   135,   737,   555,   556,   740,   585,   158,   741,
     684,   333,   336,   161,   350,   161,  1033,    73,  1036,   132,
     998,  1000,   161,   589,   758,   162,   161,   720,   321,   768,
     366,   161,   161,   548,   438,   723,   872,   967,   154,   875,
     749,   778,   760,   685,   920,   464,   149,   910,   498,   498,
     786,   530,   456,   995,   150,   883,   704,   706,   151,   735,
     787,   736,   724,   133,   679,   680,   681,   682,  1009,   155,
     565,   135,  1078,   168,   789,   510,   754,   884,   832,   739,
     549,   169,   893,   901,   744,   170,   779,   751,   132,   161,
     969,   453,   543,   453,   692,   693,   759,   762,   780,   327,
     133,   329,   327,    27,    67,   133,   329,   327,   133,   737,
     738,   750,   761,   133,   544,   162,  1061,    71,  1065,   543,
     659,   660,   661,   662,   883,   327,    80,  -465,   327,  -465,
    1117,   133,   765,   766,   133,    82,   448,  -465,   564,    74,
      74,   775,    74,   923,   449,    74,   884,   533,   450,   211,
      67,   694,   932,  1130,   670,  1133,    61,    62,   215,    74,
      74,    74,   707,    74,    74,    32,    74,    33,    67,  1142,
      59,   944,   945,   774,   709,   786,  -378,  -378,    83,    74,
      74,    74,    85,    74,    74,   831,    74,   826,   827,   828,
     829,   935,  1115,    67,   573,    86,   213,    93,    95,    74,
      74,    74,   214,    74,    74,   131,    74,   889,    88,    81,
      89,   131,   327,    59,  1127,    60,    84,   890,   133,    92,
      61,    62,   868,   786,   889,    87,  1135,  1136,   869,  1138,
    1139,   672,   473,   904,   949,  1143,   546,   547,  1144,  1145,
      60,   824,  -380,  -380,  1147,    61,    62,   513,   514,  -464,
      98,  -464,   520,   521,   156,  1007,   889,   889,    60,  -464,
      63,   990,   786,    61,    62,    76,   992,   994,   216,   786,
     267,   889,  1006,   131,   131,   498,   498,   498,   498,  1008,
     871,  1011,   458,   874,   459,   889,   131,   131,   131,   131,
     131,   549,  1063,   756,   505,  1016,   133,   131,   859,   860,
     861,   131,   227,   131,   136,   131,   131,   131,   776,   777,
     161,   161,   161,   161,   664,   229,   181,   873,   187,   191,
     873,   197,   201,  -528,   207,   133,   911,   913,   915,  1057,
     110,   111,   112,   113,   114,   115,   116,   117,   133,   133,
     889,  -381,  -381,   889,   955,   456,   231,   452,   131,   362,
    1024,   329,    95,  1027,   110,   111,   112,   113,   114,   115,
     116,   117,    74,   332,   131,   524,   131,   -23,   131,   -20,
     506,   889,   571,   136,   786,   690,   691,    74,    74,   437,
      74,  1038,   889,    74,  1041,   136,   131,   525,   458,   131,
     788,   526,  1054,   460,  -379,  -379,   533,    74,    74,   458,
      74,   790,   273,    74,   889,  -224,  -224,  -224,  -224,  -224,
    -224,   931,   441,   836,  1056,   698,   699,    74,    74,   573,
      74,   572,   534,    74,   327,   327,   327,   327,   522,   267,
     133,   133,   133,   133,   781,   754,   968,   970,   524,   985,
     -23,   328,   -20,   672,   523,   889,   889,   458,   889,   791,
     545,    92,   531,   889,   674,  1058,  1069,   524,  1070,   -23,
     525,   -20,   957,  1079,   773,   558,   267,  -379,  -379,   131,
     889,   -20,   126,   527,   458,    92,   792,   532,   126,  1018,
    1081,   889,   955,   526,   955,   672,  -379,  -379,   672,   865,
     866,  1085,   535,   889,   498,   498,   498,   498,   498,   498,
     498,   498,   498,  1089,   498,   498,   498,   498,   498,   498,
     498,   498,   550,   889,   551,   889,   729,   730,   731,   916,
     847,   848,   754,  1099,   754,  1108,   553,   748,    34,    35,
      36,   499,   499,    37,    38,    39,   757,   266,   889,   763,
     126,   126,   889,   554,   -20,   557,   527,   587,  1111,   133,
     857,   858,  1114,   126,   126,   126,   126,   126,   955,   -20,
     754,   273,   655,   -20,   126,   527,   889,   668,   126,    40,
     126,    74,   126,   126,   126,   670,  1122,   669,   754,   936,
     955,    74,   695,   696,   697,   131,   131,   131,   131,   131,
     683,    74,   955,   955,   676,   955,   955,   686,   273,   687,
     957,   955,   957,   688,   955,   955,   700,   701,   702,   689,
     955,    41,    42,    43,   280,  -277,    44,    45,    46,   713,
     720,   110,   111,   112,   113,   114,   115,   116,   117,   719,
     722,   126,   725,   126,    59,   126,   754,    47,   726,   727,
      48,   854,   855,   856,   131,   728,   456,   664,   664,   458,
     770,   133,   133,   126,   772,   785,   126,   825,   498,   754,
     498,   754,   267,    50,    51,    52,   674,   832,    53,    54,
      55,   833,   267,   834,   840,   754,   957,   862,   841,   863,
     878,    34,    35,    36,   864,   880,    37,    38,    39,    56,
     881,   267,    57,   122,   131,   664,   266,   882,   957,   885,
     886,   891,   893,   892,   267,   267,   896,   870,   672,   131,
     957,   957,   897,   957,   957,   898,   899,   900,   879,   957,
     901,   902,   957,   957,    34,    35,    36,   903,   957,    37,
      38,    39,   917,   266,   918,   921,   126,   933,   119,   937,
     938,   943,    92,   947,   952,   282,   895,   498,   981,   133,
     110,   111,   112,   113,   114,   115,   116,   117,   499,   499,
     499,   499,   973,    59,   977,   664,   536,   537,   538,   539,
     540,   541,   988,   280,   991,   110,   111,   112,   113,   114,
     115,   116,   117,  -226,  -226,  -226,  -226,  -226,  -226,   133,
     993,   133,    95,   663,   273,  -227,  -227,  -227,  -227,  -227,
    -227,   997,   133,   133,   273,   133,   133,   999,  1005,   959,
     280,  1017,   110,   111,   112,   113,   114,   115,   116,   117,
    1019,  -481,   122,   273,  1022,    59,  1020,  1021,  1031,  1023,
    1037,   131,  1034,  1042,  1043,  1046,   273,   273,  1049,  1052,
    1053,  1055,   572,  1068,   133,  1073,  1076,   133,   133,  1080,
    1084,  1088,   126,   126,   126,   126,   126,  1092,  1093,  1098,
    1094,  1105,  1097,  1106,  1107,   133,  1109,  1110,  1112,   131,
    1113,    92,    41,    42,    43,  1118,   133,    44,    45,    46,
    1124,  1125,  1126,   974,   122,  1128,  1131,   133,  1134,   509,
     982,   984,  1137,  1140,  1146,   324,    92,   365,    47,   133,
     133,    48,   133,   133,   282,   439,   286,   558,   133,   671,
     566,   133,   133,    49,   721,   267,   718,   133,  1010,    41,
      42,    43,   131,   131,    44,    45,    46,   842,   844,   266,
     905,   674,   846,    92,   843,   845,   924,   335,  1064,   266,
     451,   282,   322,   946,     0,    47,     0,   959,    48,   959,
     110,   111,   112,   113,   114,   115,   116,   117,   266,     0,
      49,   126,    95,     0,     0,     0,     0,     0,     0,     0,
     131,   266,   266,     0,     0,     0,   126,   499,   499,   499,
     499,   499,   499,   499,   499,   499,     0,   499,   499,   499,
     499,   499,   499,   499,   499,     0,     0,     0,     0,     0,
       0,     0,   131,   131,     0,   131,   280,     0,     0,     0,
       0,  1060,     0,     0,     0,     0,   280,   267,   267,     0,
       0,     0,   320,   959,     0,    77,     0,   110,   111,   112,
     113,   114,   115,   116,   117,   280,     0,     0,     0,     0,
     131,     0,     0,     0,     0,   959,     0,   273,   280,   280,
     287,     0,     0,     0,     0,     0,  1096,   959,   959,   100,
     959,   959,     0,     0,     0,   286,   959,     0,     0,   959,
     959,   123,   172,     0,     0,   959,   182,     0,   188,   192,
       0,   198,   202,     0,   208,     0,     0,     0,     0,     0,
       0,  1119,  1121,     0,     0,     0,     0,     0,     0,   320,
       0,     0,   286,     0,     0,     0,   110,   111,   112,   113,
     114,   115,   116,   117,     0,   267,     0,     0,     0,     0,
       0,     0,     0,     0,   767,     0,     0,   110,   111,   112,
     113,   114,   115,   116,   117,     0,   126,   282,     0,     0,
       0,   499,     0,   499,     0,   922,     0,   282,    92,   273,
     273,     0,     0,     0,     0,   267,   267,   267,     0,     0,
       0,     0,     0,   273,     0,     0,   282,   273,   267,   267,
       0,   267,   267,   572,     0,     0,     0,   377,     0,   282,
     282,     0,   266,   388,     0,     0,     0,   397,     1,   126,
     126,     0,     0,   408,   572,     0,     0,   417,     0,     0,
       0,     0,     0,   428,     0,     0,     0,     0,     0,   287,
     267,     0,     0,   267,   267,   110,   111,   112,   113,   114,
     115,   116,   117,     0,   288,     0,     0,    92,     0,     0,
     499,   267,     0,   934,     0,     0,     0,   126,     2,     3,
       4,     0,   267,     5,     6,     7,   287,   273,    92,     0,
     273,     0,   273,   267,     0,     0,     0,     0,     0,   280,
       0,     0,     0,     0,     8,   267,   267,     9,   267,   267,
       0,     0,     0,    10,   267,     0,     0,   267,   267,    11,
       0,     0,   572,   267,   266,   266,     0,   273,   273,   273,
     110,   111,   112,   113,   114,   115,   116,   117,   286,     0,
     273,   273,    12,   273,   273,     0,   273,   126,   286,     0,
       0,   110,   111,   112,   113,   114,   115,   116,   117,   110,
     111,   112,   113,   114,   115,   116,   117,   286,     0,   989,
       0,     0,     0,     0,     0,     0,    92,     0,     0,     0,
     286,   286,   273,     0,     0,   273,   273,     0,     0,     0,
       0,   343,   344,     0,     0,   345,   346,   347,   348,   349,
       0,   280,   280,   273,   273,     0,     0,     0,   289,     0,
       0,     0,     0,     0,   273,   280,   500,   500,   572,   280,
       0,     0,   266,   288,     0,   273,     0,   273,     0,   273,
     282,     0,     0,     0,     0,   255,     0,   273,   273,     0,
     273,   273,     0,   273,     0,     0,   273,     0,     0,   273,
     273,    92,     0,     0,     0,   273,     0,   524,     0,   -23,
     288,   -20,   266,   266,   266,     0,  -225,  -225,  -225,  -225,
    -225,  -225,    92,     0,     0,   266,   266,     0,   266,   266,
      92,     0,   287,   526,   110,   111,   112,   113,   114,   115,
     116,   117,   287,     0,     0,     0,     0,     0,     0,   280,
       0,   452,   280,     0,   280,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,     0,     0,   266,     0,     0,
     266,   266,     0,     0,   287,   287,     0,     0,     0,     0,
       0,     0,   282,   282,     0,     0,     0,     0,   266,   280,
     280,   280,     0,     0,     0,     0,   282,     0,     0,   266,
     282,     0,   280,   280,     0,   280,   280,     0,   280,     0,
     266,     0,     0,   -20,     0,   527,     0,   289,     0,     0,
       0,     0,   266,   266,     0,   266,   266,     0,     0,   290,
       0,   266,     0,     0,   266,   266,     0,     0,     0,     0,
     266,   286,     0,     0,   280,     0,     0,   280,   280,     0,
       0,     0,     0,     0,   289,    92,   110,   111,   112,   113,
     114,   115,   116,   117,     0,   280,   280,     0,     0,   507,
       0,     0,    50,    51,    52,     0,   280,    53,    54,    55,
     282,     0,     0,   282,     0,   282,     0,   280,     0,   280,
       0,   280,     0,   500,   500,   500,   500,     0,    56,   280,
     280,    57,   280,   280,     0,   280,   288,     0,   280,     0,
       0,   280,   280,    58,     0,     0,   288,   280,     0,     0,
     282,   282,   282,     0,   110,   111,   112,   113,   114,   115,
     116,   117,     0,   282,   282,   288,   282,   282,     0,   282,
       0,     0,     0,   286,   286,     0,     0,     0,   288,   288,
       0,     0,     0,     0,     0,     0,     0,   286,     0,     0,
       0,   286,     0,   110,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,     0,   282,     0,   508,   282,   282,
       0,     0,     0,     0,     0,   287,     0,     0,   290,     0,
       0,   572,     0,     0,     0,     0,   282,   282,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   282,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   282,     0,
     282,     0,   282,     0,     0,   290,     0,     0,     0,     0,
     282,   282,     0,   282,   282,     0,   282,     0,     0,   282,
       0,   286,   282,   282,   286,    92,   286,     0,   282,     0,
     289,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     289,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,   286,   286,   286,    92,     0,     0,   287,   287,     0,
       0,     1,   289,   289,   286,   286,     0,   286,   286,     0,
     286,   287,     0,     0,     0,   287,     0,     0,     0,     0,
       0,     0,   500,   500,   500,   500,   500,   500,   500,   500,
     500,     0,   500,   500,   500,   500,   500,   500,   500,   500,
       0,     0,     0,     0,     0,     0,   286,     0,     0,   286,
     286,     2,     3,     4,     0,     0,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,   286,   286,   288,
       0,     0,     0,     0,     0,     0,     0,     8,   286,     0,
       9,     0,     0,     0,     0,     0,    10,     0,     0,   286,
       0,   286,    11,   286,     0,   287,     0,     0,   287,     0,
     287,   286,   286,     0,   286,   286,     0,   286,     0,     0,
     286,     0,     0,   286,   286,    31,     0,     0,     0,   286,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   290,     0,     0,     0,   287,   287,   287,     0,     0,
       0,   290,     0,     0,     0,     0,     0,     0,   287,   287,
       0,   287,   287,     0,   287,     0,     0,     0,     0,     0,
     290,     0,   110,   111,   112,   113,   114,   115,   116,   117,
       0,   288,   288,   290,   290,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   288,   500,     0,   500,   288,
     287,     0,     0,   287,   287,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   287,   287,   289,     0,     0,     0,     0,     0,     0,
       0,     0,   287,    35,    36,     0,     0,    37,    38,    39,
       0,     0,     0,   287,   122,   287,     0,   287,     0,     0,
       0,     0,     0,     0,     0,   287,   287,     0,   287,   287,
       0,   287,     0,     0,   287,     0,     0,   287,   287,     0,
       0,     0,     0,   287,     0,     0,     0,     0,     0,   288,
       0,     0,   288,     0,   288,   500,     0,     0,     0,     0,
       0,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     465,   111,   112,   113,   114,   115,   116,   117,     0,   288,
     288,   288,     0,     0,     0,   289,   289,   238,   745,     0,
       0,     0,   288,   288,     0,   288,   288,     0,   288,   289,
     466,   467,     0,   289,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,     0,     0,     0,   288,     0,     0,   288,   288,     0,
       0,   250,   251,   252,   110,   111,   112,   113,   114,   115,
     116,   117,     0,     0,   290,   288,   288,    59,     0,     0,
       0,     0,     0,     0,     0,     0,   288,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   288,     0,   288,
       0,   288,     0,   289,     0,     0,   289,     0,   289,   288,
     288,   470,   288,   288,     0,   288,     0,     0,   288,     0,
       0,   288,   288,     0,    50,    51,    52,   288,     0,    53,
      54,    55,   338,   339,     0,     0,   122,     0,     0,     0,
       0,     0,     0,   289,   289,   289,     0,     0,     0,     0,
      56,   340,   341,    57,     0,     1,   289,   289,   733,   289,
     289,     0,   289,     0,     0,    58,     0,     0,     0,     0,
       0,     0,   171,   175,   178,   180,   290,   290,   186,     0,
       0,   196,     0,     0,   206,    92,     0,   764,     0,     0,
     290,     0,     0,     0,   290,     0,     0,     0,   289,     0,
       0,   289,   289,     0,     0,     2,     3,     4,     0,     0,
       5,     6,     7,     0,     0,     0,     0,     0,     0,   289,
     289,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     289,     8,     0,     0,     9,     0,     0,     0,     0,     0,
      10,   289,     0,   289,     0,   289,    11,     0,     0,     0,
       0,     0,     0,   289,   289,     0,   289,   289,     0,   289,
       0,     0,   289,     0,     0,   289,   289,     0,   367,   370,
     372,   289,   373,   375,   290,   376,     0,   290,     0,   290,
       0,     0,     0,   387,   391,   394,   396,     0,     0,     0,
       0,     0,     0,   407,   411,   414,   416,     0,     0,     0,
       0,     0,     0,   427,   431,   434,   436,     0,     0,     0,
       0,     0,     0,     0,   290,   290,   290,     0,     0,     0,
     103,   106,   108,   109,     0,     0,     0,   290,   290,     0,
     290,   290,     0,   290,     0,     0,     0,     0,   185,     0,
       0,   195,     0,     0,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   219,   221,   222,
       0,   224,   225,     0,   226,     0,     0,     0,   877,   290,
       0,     0,   290,   290,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     290,   290,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   290,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   290,     0,   290,     0,   290,     0,     0,     0,
     907,   909,     0,     0,   290,   290,     0,   290,   290,     0,
     290,     0,     0,   290,     0,     0,   290,   290,   380,   383,
     385,   386,   290,     0,     0,     0,     0,     0,   400,   403,
     405,   406,     0,     0,     0,     0,     0,     0,   420,   423,
     425,   426,     0,     0,   590,   592,     0,   593,     0,     0,
     594,     0,     0,     0,   443,   444,     0,   445,     0,     0,
     446,     0,     0,     0,   605,   608,   610,     0,   611,   613,
       0,   614,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   625,   628,   630,     0,   631,   633,
       0,   634,   942,   956,   966,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   645,   648,   650,   951,   651,   653,
       0,   654,     0,     0,   972,     0,     0,     0,     0,     0,
       0,   976,     0,     0,     0,     0,     0,     0,     0,   987,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1002,  1004,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1013,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1030,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1026,     0,     0,     0,  1029,     0,     0,     0,
       0,     0,     0,     0,   597,   599,   600,  1040,   602,   603,
       0,   604,     0,     0,  1045,     0,  1048,     0,  1051,     0,
       0,   733,     0,   764,   617,   619,   620,     0,   622,   623,
       0,   624,     0,     0,  1071,  1072,     0,  1074,  1075,     0,
       0,  1067,     0,     0,   637,   639,   640,     0,   642,   643,
       0,   644,     0,     0,     0,     0,     0,   793,     0,     0,
       0,     0,     0,     0,     0,  1083,     0,     0,  1087,   657,
       0,  1091,   799,   801,     0,   802,  1102,     0,   803,  1103,
    1104,     0,     0,     0,     0,     0,     0,  1101,     0,     0,
       0,     0,   809,   811,     0,   812,     0,   966,   813,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1123,     0,
       0,     0,   819,   821,     0,   822,     0,     0,   823,  1030,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      79,  1071,  1072,     0,  1074,  1075,     0,     0,     0,     0,
    1102,     0,     0,  1103,  1104,     0,     0,     0,     0,  1123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   102,   105,   107,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,   174,   177,   179,
       0,   184,     0,   190,   194,     0,   200,   204,     0,   210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   218,   220,     0,     0,   223,     0,   101,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   176,   795,   796,   183,   797,   189,   193,   798,   199,
     203,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   805,   806,   217,   807,     0,     0,   808,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   815,   816,     0,   817,   926,     0,   818,     0,
       0,     0,     0,   369,   371,     0,   928,   374,     0,     0,
       0,     0,   379,   382,   384,     0,   930,     0,   390,   393,
     395,     0,   399,   402,   404,     0,     0,     0,   410,   413,
     415,     0,   419,   422,   424,     0,     0,     0,   430,   433,
     435,     0,     0,     0,     0,     0,   368,     0,   442,     0,
       0,     0,     0,     0,     0,   378,   381,     0,     0,     0,
       0,   389,   392,     0,     0,   398,   401,     0,     0,     0,
       0,   409,   412,     0,     0,   418,   421,     0,     0,     0,
       0,   429,   432,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   236,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   237,    67,   119,   507,     0,     0,     0,
     238,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,    59,     0,     0,     0,     0,   239,   240,     0,
       0,   925,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   927,   561,     2,     3,     4,     0,     0,     5,     6,
     249,   929,     0,     0,   562,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,     0,   261,   262,   263,     8,
     351,   352,     9,     0,   353,   354,   355,     0,     0,   591,
       0,   122,     0,     0,     0,     0,     0,     0,   596,   598,
       0,     0,   601,     0,     0,   356,   357,   358,   359,   607,
     609,     0,     0,   612,   563,     0,     0,     0,   616,   618,
       0,     0,   621,   948,     0,     0,     0,     0,     0,   627,
     629,     0,     0,   632,     0,     0,     0,     0,   636,   638,
      92,   595,   641,     0,     0,     0,     0,     0,     0,   647,
     649,     0,   606,   652,     0,     0,     0,     0,     0,     0,
       0,   615,     0,   236,   111,   112,   113,   114,   115,   116,
     117,     0,   626,   237,    67,   119,     0,     0,     0,     0,
     238,   635,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   646,     0,     0,     0,  1014,  1015,     0,   110,
     111,   112,   113,   114,   115,   116,   117,   239,   240,   159,
       0,   119,    59,     0,   241,   242,   243,   244,   245,   246,
     247,   120,   248,     2,     3,     4,     0,     0,     5,     6,
     249,     0,     0,     0,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,     0,   261,   262,   263,     8,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     2,
       3,     4,     0,  1059,     5,     6,     7,     0,     0,     0,
       0,   122,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   264,     8,     0,     0,     9,     0,
     160,     0,     0,     0,     0,     0,     0,     0,   236,   111,
     112,   113,   114,   115,   116,   117,     0,     0,   237,    67,
       0,     0,     0,     0,     0,   238,   794,     0,     0,     0,
      92,     0,     0,     0,     0,     0,     0,   800,     0,     0,
       0,     0,     0,     0,     0,     0,   804,     0,     0,     0,
       0,     0,   239,   240,     0,     0,     0,   810,     0,   241,
     242,   243,   244,   245,   246,   247,   814,   248,     0,     0,
       0,     0,     0,     0,     0,   732,     0,   820,     0,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
       0,   261,   262,   263,   236,   111,   112,   113,   114,   115,
     116,   117,     0,     0,   237,    67,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   264,
       0,     0,     0,     0,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,     0,     0,     0,     0,     0,
       0,   732,     0,     0,     0,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,     0,   953,   262,   263,
     465,   111,   112,   113,   114,   115,   116,   117,   835,     0,
       0,    67,   119,     0,     0,     0,     0,   238,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,     0,     0,
     466,   467,     0,    59,     0,   954,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
     465,   111,   112,   113,   114,   115,   116,   117,     0,     0,
     519,   250,   251,   252,     0,     0,     0,   238,     0,     0,
      50,    51,    52,     0,     0,    53,    54,    55,     0,     0,
     466,   467,   122,     0,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,    56,   340,   341,    57,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,   470,     0,   465,   111,   112,   113,   114,   115,   116,
     117,   250,   251,   252,    67,     0,     0,     0,     0,     0,
     238,    92,     0,   110,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   466,   467,     0,    59,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   470,   248,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,   676,
     238,     0,     0,     0,    51,    52,     0,     0,    53,    54,
      55,     0,     0,   466,   467,   122,     0,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,    56,
     340,   341,    57,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   470,     0,   465,   111,   112,   113,
     114,   115,   116,   117,   250,   251,   252,     0,     0,     0,
       0,     0,     0,   238,    92,     0,     0,     0,     0,     0,
     849,     0,     0,     0,     0,     0,   466,   467,     0,     0,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   470,   248,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
     851,     0,     0,     0,     0,     0,   466,   467,     0,     0,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   497,     0,   465,
     111,   112,   113,   114,   115,   116,   117,   250,   251,   252,
       0,     0,     0,     0,     0,   669,   238,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,     0,   466,
     467,     0,     0,    59,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,   497,   248,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,     0,   238,   876,     0,     0,
      41,    42,    43,     0,     0,    44,    45,    46,     0,   466,
     467,     0,   122,     0,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,    47,     0,     0,    48,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     470,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     250,   251,   252,   465,   111,   112,   113,   114,   115,   116,
     117,    92,     0,   894,     0,     0,     0,     0,     0,     0,
     238,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,     0,   466,   467,     0,     0,    59,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
     470,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,   906,     0,     0,    34,    35,    36,     0,     0,    37,
      38,    39,     0,   466,   467,     0,   122,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   470,    40,   465,   111,   112,   113,
     114,   115,   116,   117,   250,   251,   252,     0,     0,     0,
       0,     0,     0,   238,   908,   123,     0,   110,   111,   112,
     113,   114,   115,   116,   117,     0,   466,   467,     0,     0,
      59,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   470,   248,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,   941,     0,     0,     0,     3,     4,
       0,     0,     5,     6,     7,     0,   466,   467,     0,   122,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     8,     0,     0,     9,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   470,     0,   465,
     111,   112,   113,   114,   115,   116,   117,   250,   251,   252,
       0,     0,     0,     0,     0,     0,   238,   950,    92,     0,
     110,   111,   112,   113,   114,   115,   116,   117,     0,   466,
     467,     0,     0,    59,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,   470,   248,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,     0,   238,   971,     0,     0,
       0,    42,    43,     0,     0,    44,    45,    46,     0,   466,
     467,     0,   122,     0,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,    47,     0,     0,    48,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     470,     0,   465,   111,   112,   113,   114,   115,   116,   117,
     250,   251,   252,     0,     0,     0,     0,     0,     0,   238,
     975,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,   467,     0,     0,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     470,   248,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,   983,   250,   251,   252,     0,     0,     0,   238,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,   467,     0,     0,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   470,     0,   465,   111,   112,   113,   114,
     115,   116,   117,   250,   251,   252,     0,     0,     0,     0,
       0,     0,   238,   986,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,   470,   248,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,   250,   251,   252,     0,
       0,     0,   238,  1001,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,   470,     0,   465,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,     0,
       0,     0,     0,     0,     0,   238,  1003,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,   467,
       0,     0,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   470,   248,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   250,
     251,   252,     0,     0,     0,   238,  1012,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,   467,
       0,     0,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   470,
       0,   465,   111,   112,   113,   114,   115,   116,   117,   250,
     251,   252,     0,     0,     0,     0,     0,     0,   238,  1025,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,   470,
     248,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,   250,   251,   252,     0,     0,     0,   238,  1028,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   470,     0,   465,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,  1039,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   470,   248,   465,   111,   112,   113,   114,   115,
     116,   117,     0,     0,     0,   250,   251,   252,     0,     0,
       0,   238,  1044,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   470,     0,   465,   111,   112,
     113,   114,   115,   116,   117,   250,   251,   252,     0,     0,
       0,     0,     0,     0,   238,  1047,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,   467,     0,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   470,   248,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,   250,   251,
     252,     0,     0,     0,   238,  1050,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,   467,     0,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   470,     0,
     465,   111,   112,   113,   114,   115,   116,   117,   250,   251,
     252,     0,     0,     0,     0,     0,     0,   238,  1066,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     466,   467,     0,     0,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,   470,   248,
     465,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,   250,   251,   252,     0,     0,     0,   238,  1082,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     466,   467,     0,     0,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,   470,     0,   465,   111,   112,   113,   114,   115,   116,
     117,   250,   251,   252,     0,     0,     0,     0,     0,     0,
     238,  1086,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   466,   467,     0,     0,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   470,   248,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,  1090,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   466,   467,     0,     0,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   470,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   250,   251,   252,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,  1095,     0,     0,
       0,     0,     0,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,   467,     0,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,   470,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,   250,   251,
     252,     0,     0,     0,   238,  1100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,   467,     0,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   470,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   250,   251,
     252,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,  1120,     0,     0,     0,     0,     0,     0,   238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,   470,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,   250,   251,   252,     0,     0,     0,   238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   470,     0,   465,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   470,   248,   236,   111,   112,   113,   114,   115,
     116,   117,     0,     0,   752,   250,   251,   252,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,   111,   112,   113,   114,   115,
     116,   117,     0,     0,  1062,     0,     0,     0,   239,   240,
       0,   238,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   497,     0,     0,     0,     0,
       0,   732,     0,     0,     0,   250,   251,   252,   239,   240,
     255,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,     0,     0,     0,     0,     0,
       0,   732,     0,     0,     0,   250,   251,   252,     0,     0,
     255,   110,   111,   112,   113,   114,   115,   116,   117,     0,
       0,   118,    67,   119,    59,   470,     0,     0,     0,     0,
       0,     0,     0,   120,     0,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   238,   978,     0,   470,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     4,     0,     0,     5,   121,     7,   239,
     240,     0,     0,   122,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,     0,     8,     0,     0,
       9,     0,     0,     0,     0,     0,   250,   251,   252,     0,
       0,     0,    11,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     238,  1032,   123,     0,     0,     0,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   238,  1035,     0,   470,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,     0,     0,     0,     0,     0,     0,
     239,   240,     0,     0,   250,   251,   252,   241,   242,   243,
     244,   245,   246,   247,     0,   248,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,  1077,     0,     0,     0,     0,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,     0,     0,   470,     0,   238,  1116,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   470,     0,     0,
       0,     0,     0,   239,   240,     0,     0,   250,   251,   252,
     241,   242,   243,   244,   245,   246,   247,     0,   248,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,     0,   238,  1129,     0,     0,
       0,     0,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,     0,     0,     0,     0,   470,     0,   238,
    1132,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     470,     0,     0,     0,     0,     0,   239,   240,     0,     0,
     250,   251,   252,   241,   242,   243,   244,   245,   246,   247,
       0,   248,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,   250,   251,   252,     0,     0,     0,   238,
    1141,     0,     0,     0,     0,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,     0,     0,     0,     0,
     470,     0,   238,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   470,     0,     0,     0,     0,     0,   239,
     240,     0,     0,   250,   251,   252,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   250,   251,   252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   470,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   470
};

static const yytype_int16 yycheck[] =
{
      29,   215,   329,   672,   332,   292,   122,   230,   535,   535,
     452,   249,   235,   507,    12,    74,   236,   692,   693,    10,
      16,   149,   150,   151,   330,   153,    14,    13,    13,   335,
     509,   510,   160,    68,    16,    26,   573,   239,   240,    68,
     168,   169,   170,    74,    18,    23,   266,    76,    77,    78,
      79,    69,    36,    82,    16,    18,    85,    14,    18,    88,
      62,    22,   334,   526,    18,   337,    20,    74,    22,   124,
     342,   534,    23,    20,   133,    22,    76,    18,   137,    16,
      62,   544,   329,    44,    13,    14,   121,    23,   360,    16,
      44,   363,   121,   124,    76,    16,    74,    44,    18,   227,
      62,    18,   137,    44,   133,   164,   124,   142,   137,     0,
      67,    99,   335,   142,    76,   557,    16,     0,   147,    16,
      36,     0,   124,    14,   124,    16,   124,   664,   124,    16,
      68,    14,    16,    16,    16,    14,    74,    16,   124,   124,
     124,    62,   124,   172,   173,   174,   124,   176,   177,    76,
     179,     0,   126,    74,   297,    76,   124,   164,   187,   188,
     189,   190,   124,   126,     0,    14,   126,    16,   197,   198,
     199,   200,   126,   124,   849,   447,   851,    68,   207,   208,
     209,   210,    16,    74,   663,    68,    13,   124,   124,    68,
     333,    74,    76,   336,    76,    74,    14,   124,   136,   137,
     694,    16,    68,   124,   320,   321,   126,   350,   124,   126,
      12,   149,   150,   151,   152,   153,   981,    44,   983,    68,
      62,    62,   160,   366,   124,    74,   164,   124,   166,   557,
     168,   169,   170,   292,   211,    13,   715,   124,    13,   718,
     124,   568,   124,    45,   781,   465,   137,    62,   239,   240,
      11,   471,    18,    20,   137,    22,   503,   504,   137,    74,
      21,    76,    40,   292,   466,   467,   468,   469,   937,    44,
     329,   137,  1037,   164,   580,   252,   535,    44,    44,   526,
     567,   164,   124,   124,   531,   164,    62,   534,   137,   227,
     124,   229,    22,   231,    16,    17,   543,   544,    74,   334,
     329,   330,   337,   124,    14,   334,   335,   342,   337,   124,
     773,   774,   775,   342,    44,   164,  1018,    44,  1020,    22,
     448,   449,   450,   451,    22,   360,   124,    11,   363,    13,
    1095,   360,   555,   556,   363,   124,   227,    21,   329,   368,
     369,    44,   371,   785,   227,   374,    44,    18,   227,    61,
      14,    73,   831,  1118,    18,  1120,    66,    67,    11,   388,
     389,   390,   505,   392,   393,    14,   395,    16,    14,  1134,
      16,   865,   866,    44,   868,    11,    47,    48,   124,   408,
     409,   410,   124,   412,   413,    21,   415,   659,   660,   661,
     662,   833,  1094,    14,   332,   124,    11,    60,    61,   428,
     429,   430,    17,   432,   433,    68,   435,    11,   124,    34,
     124,    74,   447,    16,  1116,    61,    41,    21,   447,   124,
      66,    67,    11,    11,    11,    50,  1128,  1129,    17,  1131,
    1132,   460,   238,    21,    21,  1137,    47,    48,  1140,  1141,
      61,   655,    47,    48,  1146,    66,    67,   253,   254,    11,
     124,    13,   258,   259,   124,   934,    11,    11,    61,    21,
      24,   903,    11,    66,    67,    29,    21,    21,    11,    11,
     133,    11,    21,   136,   137,   466,   467,   468,   469,    21,
     714,    21,    11,   717,    13,    11,   149,   150,   151,   152,
     153,   778,  1019,  1019,   732,    21,   525,   160,   700,   701,
     702,   164,    26,   166,    68,   168,   169,   170,   567,   568,
     448,   449,   450,   451,   452,   124,    80,   715,    82,    83,
     718,    85,    86,    20,    88,   554,   773,   774,   775,  1008,
       3,     4,     5,     6,     7,     8,     9,    10,   567,   568,
      11,    47,    48,    11,   880,    18,   124,    20,   211,    13,
      21,   580,   215,    21,     3,     4,     5,     6,     7,     8,
       9,    10,   591,    20,   227,    18,   229,    20,   231,    22,
     126,    11,    21,   137,    11,    52,    53,   606,   607,   124,
     609,    21,    11,   612,    21,   149,   249,    40,    11,   252,
      13,    44,    21,    27,    47,    48,    18,   626,   627,    11,
     629,    13,   133,   632,    11,    27,    28,    29,    30,    31,
      32,   825,   124,   672,    21,    33,    34,   646,   647,   557,
     649,    70,    44,   652,   659,   660,   661,   662,    20,   292,
     659,   660,   661,   662,   572,   894,   883,   884,    18,   898,
      20,    99,    22,   672,    20,    11,    11,    11,    11,    13,
      18,   124,    22,    11,   460,    21,    21,    18,    21,    20,
      40,    22,   880,    21,    44,   328,   329,    47,    48,   332,
      11,   124,    68,   126,    11,   124,    13,    20,    74,    40,
      21,    11,  1018,    44,  1020,   714,    47,    48,   717,    61,
      62,    21,    20,    11,   685,   686,   687,   688,   689,   690,
     691,   692,   693,    21,   695,   696,   697,   698,   699,   700,
     701,   702,    13,    11,   124,    11,   522,   523,   524,   778,
     690,   691,   981,    21,   983,    21,    13,   533,    63,    64,
      65,   239,   240,    68,    69,    70,   542,   133,    11,   545,
     136,   137,    11,    85,   124,    20,   126,    13,    21,   778,
     698,   699,    21,   149,   150,   151,   152,   153,  1094,    43,
    1019,   292,    43,   124,   160,   126,    11,    11,   164,   104,
     166,   800,   168,   169,   170,    18,    21,    19,  1037,   838,
    1116,   810,    49,    50,    51,   448,   449,   450,   451,   452,
      21,   820,  1128,  1129,    19,  1131,  1132,    46,   329,    38,
    1018,  1137,  1020,    39,  1140,  1141,    35,    36,    37,    43,
    1146,    63,    64,    65,   133,    20,    68,    69,    70,    18,
     124,     3,     4,     5,     6,     7,     8,     9,    10,    20,
      13,   227,    13,   229,    16,   231,  1095,    89,    13,    13,
      92,   695,   696,   697,   507,    13,    18,   785,   786,    11,
      11,   880,   881,   249,    20,    11,   252,    43,   849,  1118,
     851,  1120,   525,    63,    64,    65,   672,    44,    68,    69,
      70,    20,   535,    19,    19,  1134,  1094,   124,   684,    20,
      20,    63,    64,    65,   124,    21,    68,    69,    70,    89,
      21,   554,    92,    75,   557,   833,   292,    19,  1116,    20,
     124,    19,   124,    20,   567,   568,    40,   713,   937,   572,
    1128,  1129,    13,  1131,  1132,    11,   124,    20,   724,  1137,
     124,    19,  1140,  1141,    63,    64,    65,    11,  1146,    68,
      69,    70,    20,   329,    20,   124,   332,    74,    15,    11,
      40,    20,   124,    19,    13,   133,   752,   938,    13,   978,
       3,     4,     5,     6,     7,     8,     9,    10,   466,   467,
     468,   469,    20,    16,    20,   903,    27,    28,    29,    30,
      31,    32,    20,   292,    13,     3,     4,     5,     6,     7,
       8,     9,    10,    27,    28,    29,    30,    31,    32,  1018,
      13,  1020,   655,    21,   525,    27,    28,    29,    30,    31,
      32,    20,  1031,  1032,   535,  1034,  1035,    20,   124,   880,
     329,    20,     3,     4,     5,     6,     7,     8,     9,    10,
      20,    85,    75,   554,    20,    16,    85,   124,    21,   124,
      13,   694,    21,    13,    13,    20,   567,   568,    20,    20,
      13,    13,    70,    20,  1073,    21,    21,  1076,  1077,    13,
      13,    13,   448,   449,   450,   451,   452,    13,    13,    13,
      21,    21,    40,    13,    13,  1094,    13,    13,    13,   732,
      13,   124,    63,    64,    65,    13,  1105,    68,    69,    70,
      13,    13,    13,   889,    75,    21,    21,  1116,    13,   252,
     896,   897,    21,    21,    21,   137,   124,   164,    89,  1128,
    1129,    92,  1131,  1132,   292,   213,   133,   770,  1137,   458,
     329,  1140,  1141,   104,   512,   778,   510,  1146,   938,    63,
      64,    65,   785,   786,    68,    69,    70,   685,   687,   525,
     770,   937,   689,   124,   686,   688,   786,   149,  1019,   535,
     227,   329,   136,   868,    -1,    89,    -1,  1018,    92,  1020,
       3,     4,     5,     6,     7,     8,     9,    10,   554,    -1,
     104,   557,   825,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     833,   567,   568,    -1,    -1,    -1,   572,   685,   686,   687,
     688,   689,   690,   691,   692,   693,    -1,   695,   696,   697,
     698,   699,   700,   701,   702,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   865,   866,    -1,   868,   525,    -1,    -1,    -1,
      -1,  1017,    -1,    -1,    -1,    -1,   535,   880,   881,    -1,
      -1,    -1,    75,  1094,    -1,    29,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,   554,    -1,    -1,    -1,    -1,
     903,    -1,    -1,    -1,    -1,  1116,    -1,   778,   567,   568,
     133,    -1,    -1,    -1,    -1,    -1,  1062,  1128,  1129,    63,
    1131,  1132,    -1,    -1,    -1,   292,  1137,    -1,    -1,  1140,
    1141,   124,    76,    -1,    -1,  1146,    80,    -1,    82,    83,
      -1,    85,    86,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,  1097,  1098,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      -1,    -1,   329,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,   978,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,   732,   525,    -1,    -1,
      -1,   849,    -1,   851,    -1,    21,    -1,   535,   124,   880,
     881,    -1,    -1,    -1,    -1,  1018,  1019,  1020,    -1,    -1,
      -1,    -1,    -1,   894,    -1,    -1,   554,   898,  1031,  1032,
      -1,  1034,  1035,    70,    -1,    -1,    -1,   181,    -1,   567,
     568,    -1,   778,   187,    -1,    -1,    -1,   191,    13,   785,
     786,    -1,    -1,   197,    70,    -1,    -1,   201,    -1,    -1,
      -1,    -1,    -1,   207,    -1,    -1,    -1,    -1,    -1,   292,
    1073,    -1,    -1,  1076,  1077,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,   133,    -1,    -1,   124,    -1,    -1,
     938,  1094,    -1,    21,    -1,    -1,    -1,   833,    63,    64,
      65,    -1,  1105,    68,    69,    70,   329,   978,   124,    -1,
     981,    -1,   983,  1116,    -1,    -1,    -1,    -1,    -1,   778,
      -1,    -1,    -1,    -1,    89,  1128,  1129,    92,  1131,  1132,
      -1,    -1,    -1,    98,  1137,    -1,    -1,  1140,  1141,   104,
      -1,    -1,    70,  1146,   880,   881,    -1,  1018,  1019,  1020,
       3,     4,     5,     6,     7,     8,     9,    10,   525,    -1,
    1031,  1032,   127,  1034,  1035,    -1,  1037,   903,   535,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,     3,
       4,     5,     6,     7,     8,     9,    10,   554,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,
     567,   568,  1073,    -1,    -1,  1076,  1077,    -1,    -1,    -1,
      -1,    64,    65,    -1,    -1,    68,    69,    70,    71,    72,
      -1,   880,   881,  1094,  1095,    -1,    -1,    -1,   133,    -1,
      -1,    -1,    -1,    -1,  1105,   894,   239,   240,    70,   898,
      -1,    -1,   978,   292,    -1,  1116,    -1,  1118,    -1,  1120,
     778,    -1,    -1,    -1,    -1,    79,    -1,  1128,  1129,    -1,
    1131,  1132,    -1,  1134,    -1,    -1,  1137,    -1,    -1,  1140,
    1141,   124,    -1,    -1,    -1,  1146,    -1,    18,    -1,    20,
     329,    22,  1018,  1019,  1020,    -1,    27,    28,    29,    30,
      31,    32,   124,    -1,    -1,  1031,  1032,    -1,  1034,  1035,
     124,    -1,   525,    44,     3,     4,     5,     6,     7,     8,
       9,    10,   535,    -1,    -1,    -1,    -1,    -1,    -1,   978,
      -1,    20,   981,    -1,   983,    -1,    -1,    -1,    -1,    -1,
      -1,   554,    -1,    -1,    -1,    -1,    -1,  1073,    -1,    -1,
    1076,  1077,    -1,    -1,   567,   568,    -1,    -1,    -1,    -1,
      -1,    -1,   880,   881,    -1,    -1,    -1,    -1,  1094,  1018,
    1019,  1020,    -1,    -1,    -1,    -1,   894,    -1,    -1,  1105,
     898,    -1,  1031,  1032,    -1,  1034,  1035,    -1,  1037,    -1,
    1116,    -1,    -1,   124,    -1,   126,    -1,   292,    -1,    -1,
      -1,    -1,  1128,  1129,    -1,  1131,  1132,    -1,    -1,   133,
      -1,  1137,    -1,    -1,  1140,  1141,    -1,    -1,    -1,    -1,
    1146,   778,    -1,    -1,  1073,    -1,    -1,  1076,  1077,    -1,
      -1,    -1,    -1,    -1,   329,   124,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,  1094,  1095,    -1,    -1,    16,
      -1,    -1,    63,    64,    65,    -1,  1105,    68,    69,    70,
     978,    -1,    -1,   981,    -1,   983,    -1,  1116,    -1,  1118,
      -1,  1120,    -1,   466,   467,   468,   469,    -1,    89,  1128,
    1129,    92,  1131,  1132,    -1,  1134,   525,    -1,  1137,    -1,
      -1,  1140,  1141,   104,    -1,    -1,   535,  1146,    -1,    -1,
    1018,  1019,  1020,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,  1031,  1032,   554,  1034,  1035,    -1,  1037,
      -1,    -1,    -1,   880,   881,    -1,    -1,    -1,   567,   568,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   894,    -1,    -1,
      -1,   898,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,  1073,    -1,   124,  1076,  1077,
      -1,    -1,    -1,    -1,    -1,   778,    -1,    -1,   292,    -1,
      -1,    70,    -1,    -1,    -1,    -1,  1094,  1095,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1116,    -1,
    1118,    -1,  1120,    -1,    -1,   329,    -1,    -1,    -1,    -1,
    1128,  1129,    -1,  1131,  1132,    -1,  1134,    -1,    -1,  1137,
      -1,   978,  1140,  1141,   981,   124,   983,    -1,  1146,    -1,
     525,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     535,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   554,
      -1,  1018,  1019,  1020,   124,    -1,    -1,   880,   881,    -1,
      -1,    13,   567,   568,  1031,  1032,    -1,  1034,  1035,    -1,
    1037,   894,    -1,    -1,    -1,   898,    -1,    -1,    -1,    -1,
      -1,    -1,   685,   686,   687,   688,   689,   690,   691,   692,
     693,    -1,   695,   696,   697,   698,   699,   700,   701,   702,
      -1,    -1,    -1,    -1,    -1,    -1,  1073,    -1,    -1,  1076,
    1077,    63,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1094,  1095,   778,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,  1105,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,  1116,
      -1,  1118,   104,  1120,    -1,   978,    -1,    -1,   981,    -1,
     983,  1128,  1129,    -1,  1131,  1132,    -1,  1134,    -1,    -1,
    1137,    -1,    -1,  1140,  1141,   127,    -1,    -1,    -1,  1146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   525,    -1,    -1,    -1,  1018,  1019,  1020,    -1,    -1,
      -1,   535,    -1,    -1,    -1,    -1,    -1,    -1,  1031,  1032,
      -1,  1034,  1035,    -1,  1037,    -1,    -1,    -1,    -1,    -1,
     554,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,   880,   881,   567,   568,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   894,   849,    -1,   851,   898,
    1073,    -1,    -1,  1076,  1077,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1094,  1095,   778,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1105,    64,    65,    -1,    -1,    68,    69,    70,
      -1,    -1,    -1,  1116,    75,  1118,    -1,  1120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1128,  1129,    -1,  1131,  1132,
      -1,  1134,    -1,    -1,  1137,    -1,    -1,  1140,  1141,    -1,
      -1,    -1,    -1,  1146,    -1,    -1,    -1,    -1,    -1,   978,
      -1,    -1,   981,    -1,   983,   938,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,  1018,
    1019,  1020,    -1,    -1,    -1,   880,   881,    20,    21,    -1,
      -1,    -1,  1031,  1032,    -1,  1034,  1035,    -1,  1037,   894,
      33,    34,    -1,   898,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    -1,    -1,    -1,  1073,    -1,    -1,  1076,  1077,    -1,
      -1,    74,    75,    76,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,   778,  1094,  1095,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1116,    -1,  1118,
      -1,  1120,    -1,   978,    -1,    -1,   981,    -1,   983,  1128,
    1129,   124,  1131,  1132,    -1,  1134,    -1,    -1,  1137,    -1,
      -1,  1140,  1141,    -1,    63,    64,    65,  1146,    -1,    68,
      69,    70,    71,    72,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,  1018,  1019,  1020,    -1,    -1,    -1,    -1,
      89,    90,    91,    92,    -1,    13,  1031,  1032,   525,  1034,
    1035,    -1,  1037,    -1,    -1,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,   880,   881,    82,    -1,
      -1,    85,    -1,    -1,    88,   124,    -1,   554,    -1,    -1,
     894,    -1,    -1,    -1,   898,    -1,    -1,    -1,  1073,    -1,
      -1,  1076,  1077,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,  1094,
    1095,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1105,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,  1116,    -1,  1118,    -1,  1120,   104,    -1,    -1,    -1,
      -1,    -1,    -1,  1128,  1129,    -1,  1131,  1132,    -1,  1134,
      -1,    -1,  1137,    -1,    -1,  1140,  1141,    -1,   172,   173,
     174,  1146,   176,   177,   978,   179,    -1,   981,    -1,   983,
      -1,    -1,    -1,   187,   188,   189,   190,    -1,    -1,    -1,
      -1,    -1,    -1,   197,   198,   199,   200,    -1,    -1,    -1,
      -1,    -1,    -1,   207,   208,   209,   210,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1018,  1019,  1020,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,  1031,  1032,    -1,
    1034,  1035,    -1,  1037,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    84,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,   102,
      -1,   104,   105,    -1,   107,    -1,    -1,    -1,   719,  1073,
      -1,    -1,  1076,  1077,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1094,  1095,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1116,    -1,  1118,    -1,  1120,    -1,    -1,    -1,
     771,   772,    -1,    -1,  1128,  1129,    -1,  1131,  1132,    -1,
    1134,    -1,    -1,  1137,    -1,    -1,  1140,  1141,   181,   182,
     183,   184,  1146,    -1,    -1,    -1,    -1,    -1,   191,   192,
     193,   194,    -1,    -1,    -1,    -1,    -1,    -1,   201,   202,
     203,   204,    -1,    -1,   368,   369,    -1,   371,    -1,    -1,
     374,    -1,    -1,    -1,   217,   218,    -1,   220,    -1,    -1,
     223,    -1,    -1,    -1,   388,   389,   390,    -1,   392,   393,
      -1,   395,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   408,   409,   410,    -1,   412,   413,
      -1,   415,   863,   880,   881,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   428,   429,   430,   878,   432,   433,
      -1,   435,    -1,    -1,   885,    -1,    -1,    -1,    -1,    -1,
      -1,   892,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   900,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   917,   918,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   943,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   978,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   973,    -1,    -1,    -1,   977,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   377,   378,   379,   988,   381,   382,
      -1,   384,    -1,    -1,   995,    -1,   997,    -1,   999,    -1,
      -1,  1018,    -1,  1020,   397,   398,   399,    -1,   401,   402,
      -1,   404,    -1,    -1,  1031,  1032,    -1,  1034,  1035,    -1,
      -1,  1022,    -1,    -1,   417,   418,   419,    -1,   421,   422,
      -1,   424,    -1,    -1,    -1,    -1,    -1,   591,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1046,    -1,    -1,  1049,   442,
      -1,  1052,   606,   607,    -1,   609,  1073,    -1,   612,  1076,
    1077,    -1,    -1,    -1,    -1,    -1,    -1,  1068,    -1,    -1,
      -1,    -1,   626,   627,    -1,   629,    -1,  1094,   632,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1105,    -1,
      -1,    -1,   646,   647,    -1,   649,    -1,    -1,   652,  1116,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,  1128,  1129,    -1,  1131,  1132,    -1,    -1,    -1,    -1,
    1137,    -1,    -1,  1140,  1141,    -1,    -1,    -1,    -1,  1146,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    76,    77,    78,
      -1,    80,    -1,    82,    83,    -1,    85,    86,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   100,   101,    -1,    -1,   104,    -1,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,   595,   596,    80,   598,    82,    83,   601,    85,
      86,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   615,   616,   100,   618,    -1,    -1,   621,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   635,   636,    -1,   638,   800,    -1,   641,    -1,
      -1,    -1,    -1,   172,   173,    -1,   810,   176,    -1,    -1,
      -1,    -1,   181,   182,   183,    -1,   820,    -1,   187,   188,
     189,    -1,   191,   192,   193,    -1,    -1,    -1,   197,   198,
     199,    -1,   201,   202,   203,    -1,    -1,    -1,   207,   208,
     209,    -1,    -1,    -1,    -1,    -1,   172,    -1,   217,    -1,
      -1,    -1,    -1,    -1,    -1,   181,   182,    -1,    -1,    -1,
      -1,   187,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,
      -1,   197,   198,    -1,    -1,   201,   202,    -1,    -1,    -1,
      -1,   207,   208,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,   794,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   804,    62,    63,    64,    65,    -1,    -1,    68,    69,
      70,   814,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    86,    87,    88,    89,
      64,    65,    92,    -1,    68,    69,    70,    -1,    -1,   368,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,   377,   378,
      -1,    -1,   381,    -1,    -1,    89,    90,    91,    92,   388,
     389,    -1,    -1,   392,   124,    -1,    -1,    -1,   397,   398,
      -1,    -1,   401,   876,    -1,    -1,    -1,    -1,    -1,   408,
     409,    -1,    -1,   412,    -1,    -1,    -1,    -1,   417,   418,
     124,   377,   421,    -1,    -1,    -1,    -1,    -1,    -1,   428,
     429,    -1,   388,   432,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   397,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,   408,    13,    14,    15,    -1,    -1,    -1,    -1,
      20,   417,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   428,    -1,    -1,    -1,   949,   950,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    47,    48,    13,
      -1,    15,    16,    -1,    54,    55,    56,    57,    58,    59,
      60,    25,    62,    63,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    -1,    -1,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    86,    87,    88,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    -1,  1016,    68,    69,    70,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,    89,    -1,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,   595,    -1,    -1,    -1,
     124,    -1,    -1,    -1,    -1,    -1,    -1,   606,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   615,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,   626,    -1,    54,
      55,    56,    57,    58,    59,    60,   635,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,   646,    -1,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    86,    87,    88,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    -1,    86,    87,    88,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    14,    15,    -1,    -1,    -1,    -1,    20,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      33,    34,    -1,    16,    -1,   124,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    74,    75,    76,    -1,    -1,    -1,    20,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,
      33,    34,    75,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    89,    90,    91,    92,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,   124,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    74,    75,    76,    14,    -1,    -1,    -1,    -1,    -1,
      20,   124,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    33,    34,    -1,    16,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   124,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    19,
      20,    -1,    -1,    -1,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    -1,    33,    34,    75,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    89,
      90,    91,    92,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,   124,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    20,   124,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   124,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,   124,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    33,
      34,    -1,    -1,    16,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,   124,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    70,    -1,    33,
      34,    -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    89,    -1,    -1,    92,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
     124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,     3,     4,     5,     6,     7,     8,     9,
      10,   124,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    33,    34,    -1,    -1,    16,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
     124,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    63,    64,    65,    -1,    -1,    68,
      69,    70,    -1,    33,    34,    -1,    75,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,   124,   104,     3,     4,     5,     6,
       7,     8,     9,    10,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,   124,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    33,    34,    -1,    -1,
      16,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,   124,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,    75,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    89,    -1,    -1,    92,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,   124,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,   124,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    33,
      34,    -1,    -1,    16,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,   124,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,    64,    65,    -1,    -1,    68,    69,    70,    -1,    33,
      34,    -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    89,    -1,    -1,    92,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
     124,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      21,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     124,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    74,    75,    76,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
       3,     4,     5,     6,     7,     8,     9,    10,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,
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
      60,    -1,    62,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,   124,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,     3,     4,     5,
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
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,   124,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,   124,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    74,    75,    76,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    -1,    -1,    -1,    47,    48,
      -1,    20,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    74,    75,    76,    47,    48,
      79,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      79,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    16,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    70,    47,
      48,    -1,    -1,    75,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,   104,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,   124,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    -1,   124,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      21,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    20,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,   124,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    74,    75,    76,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,    13,    63,    64,    65,    68,    69,    70,    89,    92,
      98,   104,   127,   129,   142,   143,   144,   145,   146,   148,
     155,   272,   273,   274,   124,   147,    69,   124,   141,   124,
       0,   127,   143,   143,    63,    64,    65,    68,    69,    70,
     104,    63,    64,    65,    68,    69,    70,    89,    92,   104,
      63,    64,    65,    68,    69,    70,    89,    92,   104,    16,
      61,    66,    67,   156,   161,   162,   164,    14,   150,   166,
     141,    44,    13,    44,   150,   152,   156,   161,   162,   164,
     124,   147,   124,   124,   147,   124,   124,   147,   124,   124,
     157,   158,   124,   137,   138,   137,   163,   282,   124,   165,
     161,   162,   164,   166,   162,   164,   166,   164,   166,   166,
       3,     4,     5,     6,     7,     8,     9,    10,    13,    15,
      25,    69,    75,   124,   130,   131,   132,   133,   134,   135,
     136,   137,   145,   150,   151,   155,   156,   167,   168,   169,
     170,   218,   219,   229,   230,   231,   267,   268,   269,   272,
     273,   274,   275,   276,    13,    44,   124,    36,   124,    13,
      94,   130,   145,   151,   153,   154,   156,   218,   272,   273,
     274,   152,   161,   162,   164,   152,   162,   164,   152,   164,
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
     250,   251,   253,   258,   259,   260,   262,   272,   273,   274,
      75,   130,   269,   151,   168,    13,   228,   231,    99,   150,
     220,   270,    20,   130,   219,   268,   130,   219,    71,    72,
      90,    91,   219,    64,    65,    68,    69,    70,    71,    72,
     130,    64,    65,    68,    69,    70,    89,    90,    91,    92,
     219,    36,    13,   219,   151,   154,   130,   152,   162,   164,
     152,   164,   152,   152,   164,   152,   152,   161,   162,   164,
     166,   162,   164,   166,   164,   166,   166,   152,   161,   162,
     164,   152,   162,   164,   152,   164,   152,   161,   162,   164,
     166,   162,   164,   166,   164,   166,   166,   152,   161,   162,
     164,   152,   162,   164,   152,   164,   152,   161,   162,   164,
     166,   162,   164,   166,   164,   166,   166,   152,   161,   162,
     164,   152,   162,   164,   152,   164,   152,   124,   136,   158,
     282,   124,   164,   166,   166,   166,   166,   219,   272,   273,
     274,   276,    20,   130,   224,   220,    18,   139,    11,    13,
      27,   220,    18,   126,   185,     3,    33,    34,    41,    42,
     124,   132,   137,   175,   176,   177,   186,   190,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   124,   141,   180,
     198,   210,   210,    22,    44,   237,   126,    16,   124,   131,
     136,   188,   277,   175,   175,    13,   124,    13,   124,    13,
     175,   175,    20,    20,    18,    40,    44,   126,   185,   126,
     185,    22,    20,    18,    44,    20,    27,    28,    29,    30,
      31,    32,   179,    22,    44,    18,    47,    48,   151,   233,
      13,   124,   171,    13,    85,   223,   223,    20,   137,   221,
     222,    62,    74,   124,   141,   151,   181,   232,   271,   277,
     270,    21,    70,   130,   224,   225,   226,   227,   171,   228,
     220,   270,   171,   228,   228,   171,   228,    13,   228,   171,
     152,   164,   152,   152,   152,   162,   164,   166,   164,   166,
     166,   164,   166,   166,   166,   152,   162,   164,   152,   164,
     152,   152,   164,   152,   152,   162,   164,   166,   164,   166,
     166,   164,   166,   166,   166,   152,   162,   164,   152,   164,
     152,   152,   164,   152,   152,   162,   164,   166,   164,   166,
     166,   164,   166,   166,   166,   152,   162,   164,   152,   164,
     152,   152,   164,   152,   152,    43,   160,   166,   228,   219,
     219,   219,   219,    21,   130,   225,    74,   124,    11,    19,
      18,   172,   150,   174,   175,   193,    19,    18,   126,   210,
     210,   210,   210,    21,    12,    45,    46,    38,    39,    43,
      52,    53,    16,    17,    73,    49,    50,    51,    33,    34,
      35,    36,    37,   124,   277,   124,   277,   171,    12,   135,
     278,   279,   280,    18,   139,   195,   196,   139,   195,    20,
     124,   188,    13,    13,    40,    13,    13,    13,    13,   175,
     175,   175,    70,   238,    62,    74,    76,   124,   187,   277,
     126,   126,    76,   124,   277,    21,   175,   189,   175,   124,
     187,   277,    13,   236,   242,   264,   266,   175,   124,   277,
     124,   187,   277,   175,   238,   220,   220,    21,   224,   225,
      11,    20,    20,    44,    44,    44,   151,   151,   232,    62,
      74,   130,    23,   124,   173,    11,    11,    21,    13,   270,
      13,    13,    13,   152,   164,   166,   166,   166,   166,   152,
     164,   152,   152,   152,   164,   166,   166,   166,   166,   152,
     164,   152,   152,   152,   164,   166,   166,   166,   166,   152,
     164,   152,   152,   152,   282,    43,   228,   228,   228,   228,
     139,    21,    44,    20,    19,    11,   151,   174,   194,   197,
      19,   175,   201,   202,   203,   204,   205,   206,   206,    27,
     207,    27,   207,   135,   208,   208,   208,   209,   209,   210,
     210,   210,   124,    20,   124,    61,    62,   281,    11,    17,
     175,   193,   139,   196,   193,   139,    21,   189,    20,   175,
      21,    21,    19,    22,    44,    20,   124,    76,   124,    11,
      21,    19,    20,   124,    13,   175,    40,    13,    11,   124,
      20,   124,    19,    11,    21,   222,    21,   189,    21,   189,
      62,   277,    62,   277,    62,   277,   151,    20,    20,    23,
     173,   124,    21,   225,   226,   166,   152,   166,   152,   166,
     152,   282,   139,    74,    21,   225,   151,    11,    40,   207,
     207,    21,   189,    20,   135,   135,   279,    19,   166,    21,
      21,   189,    13,    86,   124,   149,   238,   239,   252,   253,
     254,   255,   256,   257,   261,   263,   238,   124,   277,   124,
     277,    21,   189,    20,   175,    21,   189,    20,    21,   265,
     266,    13,   175,    13,   175,   242,    21,   189,    20,    21,
     225,    13,    21,    13,    21,    20,    62,    20,    62,    20,
      62,    21,   189,    21,   189,   124,    21,   139,    21,   174,
     199,    21,    21,   189,   166,   166,    21,    20,    40,    20,
      85,   124,    20,   124,    21,    21,   189,    21,    21,   189,
     238,    21,    21,   265,    21,    21,   265,    13,    21,    21,
     189,    21,    13,    13,    21,   189,    20,    21,   189,    20,
      21,   189,    20,    13,    21,    13,    21,   139,    21,   166,
     175,   254,    13,   236,   264,   254,    21,   189,    20,    21,
      21,   238,   238,    21,   238,   238,    21,    21,   265,    21,
      13,    21,    21,   189,    13,    21,    21,   189,    13,    21,
      21,   189,    13,    13,    21,    13,   175,    40,    13,    21,
      21,   189,   238,   238,   238,    21,    13,    13,    21,    13,
      13,    21,    13,    13,    21,   254,    21,   265,    13,   175,
      13,   175,    21,   238,    13,    13,    13,   254,    21,    21,
     265,    21,    21,   265,    13,   254,   254,    21,   254,   254,
      21,    21,   265,   254,   254,   254,    21,   254
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
     232,   232,   233,   233,   234,   235,   236,   236,   237,   237,
     238,   238,   238,   238,   238,   238,   238,   238,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   240,   241,   242,
     242,   242,   242,   242,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   254,   254,   254,   254,   255,   256,   257,   257,
     258,   259,   259,   260,   260,   260,   260,   260,   260,   260,
     260,   261,   261,   261,   261,   261,   261,   261,   261,   262,
     263,   264,   264,   265,   266,   266,   267,   267,   267,   267,
     268,   268,   268,   268,   268,   268,   268,   268,   269,   270,
     270,   270,   270,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   272,   272,   272,   272,   272,   272,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   274,   274,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   277,
     278,   278,   279,   279,   280,   280,   281,   281,   282
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
       1,     2,     1,     1,     1,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     2,     3,
       2,     3,     3,     2,     3,     3,     3,     5,     3,     3,
       5,     1,     1,     1,     1,     1,     3,     5,     1,     1,
       5,     1,     1,     6,     7,     7,     8,     7,     8,     8,
       9,     6,     7,     7,     8,     7,     8,     8,     9,     7,
       7,     1,     1,     1,     1,     3,     3,     2,     4,     3,
       3,     4,     5,     6,     4,     5,     6,     7,     1,     4,
       3,     3,     2,     4,     5,     5,     6,     4,     5,     5,
       6,     6,     7,     7,     8,     6,     7,     7,     8,     6,
       7,     7,     8,     1,     1,     1,     2,     2,     2,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       1,     3,     1,     1,     1,     2,     2,     2,     1
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
#line 3485 "parser_1st.tab.c"
    break;

  case 3: /* COMPILATIONUNIT: ORDINARYCOMPILATIONUNIT EOFF  */
#line 242 "parser_1st.y"
                                                     {
                    
                    return 0;
                }
#line 3494 "parser_1st.tab.c"
    break;

  case 4: /* TYPE: PRIMITIVETYPE  */
#line 247 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3500 "parser_1st.tab.c"
    break;

  case 5: /* TYPE: REFERENCETYPE  */
#line 248 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3506 "parser_1st.tab.c"
    break;

  case 6: /* PRIMITIVETYPE: NUMERICTYPE  */
#line 250 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3512 "parser_1st.tab.c"
    break;

  case 7: /* PRIMITIVETYPE: BOOLEAN  */
#line 251 "parser_1st.y"
                             {(yyval.val) = stringtochar("bool");}
#line 3518 "parser_1st.tab.c"
    break;

  case 8: /* NUMERICTYPE: INTEGRALTYPE  */
#line 253 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3524 "parser_1st.tab.c"
    break;

  case 9: /* NUMERICTYPE: FLOATINGTYPE  */
#line 254 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3530 "parser_1st.tab.c"
    break;

  case 10: /* INTEGRALTYPE: BYTE  */
#line 256 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3536 "parser_1st.tab.c"
    break;

  case 11: /* INTEGRALTYPE: SHORT  */
#line 257 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3542 "parser_1st.tab.c"
    break;

  case 12: /* INTEGRALTYPE: INT  */
#line 258 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3548 "parser_1st.tab.c"
    break;

  case 13: /* INTEGRALTYPE: LONG  */
#line 259 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3554 "parser_1st.tab.c"
    break;

  case 14: /* INTEGRALTYPE: CHAR  */
#line 260 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3560 "parser_1st.tab.c"
    break;

  case 15: /* FLOATINGTYPE: FLOAT  */
#line 262 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3566 "parser_1st.tab.c"
    break;

  case 16: /* FLOATINGTYPE: DOUBLE  */
#line 263 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3572 "parser_1st.tab.c"
    break;

  case 17: /* REFERENCETYPE: CLASSORINTERFACETYPE  */
#line 265 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3578 "parser_1st.tab.c"
    break;

  case 18: /* CLASSORINTERFACETYPE: CLASSTYPE  */
#line 267 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3584 "parser_1st.tab.c"
    break;

  case 19: /* CLASSTYPE: CLASSTYPE1  */
#line 269 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3590 "parser_1st.tab.c"
    break;

  case 20: /* CLASSTYPE1: IDENTIFIER  */
#line 271 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val); }
#line 3596 "parser_1st.tab.c"
    break;

  case 21: /* DIMS: OPENSQUARE CLOSESQUARE  */
#line 274 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3602 "parser_1st.tab.c"
    break;

  case 22: /* DIMS: DIMS OPENSQUARE CLOSESQUARE  */
#line 275 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3608 "parser_1st.tab.c"
    break;

  case 23: /* METHODNAME: IDENTIFIER  */
#line 277 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3619 "parser_1st.tab.c"
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
#line 3641 "parser_1st.tab.c"
    break;

  case 25: /* EXPRESSIONNAME: EXPRESSIONNAME DOT IDENTIFIER  */
#line 301 "parser_1st.y"
                                                  {/*TODO*/}
#line 3647 "parser_1st.tab.c"
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
#line 3695 "parser_1st.tab.c"
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
#line 3712 "parser_1st.tab.c"
    break;

  case 37: /* NORMALCLASSDECLARATION: CLASS CLASSNAME CLASSBODY  */
#line 373 "parser_1st.y"
                                                       {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));/*TODO begin class */}
#line 3718 "parser_1st.tab.c"
    break;

  case 38: /* NORMALCLASSDECLARATION: SUPER1 CLASS CLASSNAME CLASSBODY  */
#line 374 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val); if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3724 "parser_1st.tab.c"
    break;

  case 39: /* NORMALCLASSDECLARATION: SUPER2 CLASS CLASSNAME CLASSBODY  */
#line 375 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3730 "parser_1st.tab.c"
    break;

  case 40: /* NORMALCLASSDECLARATION: SUPER3 CLASS CLASSNAME CLASSBODY  */
#line 376 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3736 "parser_1st.tab.c"
    break;

  case 101: /* CLASSNAME: IDENTIFIER  */
#line 441 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val); curr_class = chartostring((yyval.val)); }
#line 3742 "parser_1st.tab.c"
    break;

  case 166: /* FOR: FOR1  */
#line 508 "parser_1st.y"
           {newscope();}
#line 3748 "parser_1st.tab.c"
    break;

  case 167: /* OPENCURLY: OPENCURLY1  */
#line 509 "parser_1st.y"
                          {newscope(); }
#line 3754 "parser_1st.tab.c"
    break;

  case 168: /* CLOSECURLY: CLOSECURLY1  */
#line 510 "parser_1st.y"
                          {popscope();}
#line 3760 "parser_1st.tab.c"
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
#line 3793 "parser_1st.tab.c"
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
#line 3824 "parser_1st.tab.c"
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
#line 3857 "parser_1st.tab.c"
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
#line 3899 "parser_1st.tab.c"
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
#line 3916 "parser_1st.tab.c"
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
#line 3944 "parser_1st.tab.c"
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
#line 3985 "parser_1st.tab.c"
    break;

  case 215: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID  */
#line 765 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];}
#line 3991 "parser_1st.tab.c"
    break;

  case 216: /* VARIABLEDECLARATORID: IDENTIFIER  */
#line 767 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));

}
#line 4004 "parser_1st.tab.c"
    break;

  case 217: /* VARIABLEDECLARATORID: IDENTIFIER DIMS  */
#line 775 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        int curr = chartonum((yyval.val));
                                    ds[curr]["var"] = chartostring((yyvsp[-1].val));
                        /*TODO*/
                        }
#line 4014 "parser_1st.tab.c"
    break;

  case 218: /* VARIABLEINITIALIZER: EXPRESSION  */
#line 782 "parser_1st.y"
                                    {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 4020 "parser_1st.tab.c"
    break;

  case 219: /* VARIABLEINITIALIZER: ARRAYINITIALIZER  */
#line 783 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 4026 "parser_1st.tab.c"
    break;

  case 220: /* EXPRESSION: ASSIGNMENTEXPRESSION  */
#line 785 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4032 "parser_1st.tab.c"
    break;

  case 221: /* ASSIGNMENTEXPRESSION: CONDITIONALEXPRESSION  */
#line 787 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 4040 "parser_1st.tab.c"
    break;

  case 222: /* ASSIGNMENTEXPRESSION: ASSIGNMENT  */
#line 790 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);/*TODO CHECK multiple assign*/}
#line 4046 "parser_1st.tab.c"
    break;

  case 223: /* ASSIGNMENT: LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  */
#line 792 "parser_1st.y"
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
#line 4065 "parser_1st.tab.c"
    break;

  case 224: /* LEFTHANDSIDE: EXPRESSIONNAME  */
#line 807 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 4071 "parser_1st.tab.c"
    break;

  case 225: /* LEFTHANDSIDE: IDENTIFIER  */
#line 808 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
#line 4084 "parser_1st.tab.c"
    break;

  case 226: /* LEFTHANDSIDE: FIELDACCESS  */
#line 816 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4090 "parser_1st.tab.c"
    break;

  case 227: /* LEFTHANDSIDE: ARRAYACCESS  */
#line 817 "parser_1st.y"
                                {   (yyval.val) = (yyvsp[0].val);
                                    ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"[ "+ds[chartonum((yyvsp[0].val))]["var"]+" ]";
                }
#line 4098 "parser_1st.tab.c"
    break;

  case 228: /* ASSIGNMENTOPERATOR: EQUALS  */
#line 821 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 4105 "parser_1st.tab.c"
    break;

  case 229: /* ASSIGNMENTOPERATOR: MULTIPLYEQUALS  */
#line 823 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 4112 "parser_1st.tab.c"
    break;

  case 230: /* ASSIGNMENTOPERATOR: DIVIDEEQUALS  */
#line 825 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 4119 "parser_1st.tab.c"
    break;

  case 231: /* ASSIGNMENTOPERATOR: MODEQUALS  */
#line 827 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 4126 "parser_1st.tab.c"
    break;

  case 232: /* ASSIGNMENTOPERATOR: PLUSEQUALS  */
#line 829 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 4133 "parser_1st.tab.c"
    break;

  case 233: /* ASSIGNMENTOPERATOR: MINUSEQUALS  */
#line 831 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 4140 "parser_1st.tab.c"
    break;

  case 234: /* FIELDACCESS: PRIMARY DOT IDENTIFIER  */
#line 834 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring((yyvsp[0].val));
                                        }else assert(0 && "unexpected type\n");
                                        }
#line 4152 "parser_1st.tab.c"
    break;

  case 237: /* PRIMARY: PRIMARYNONEWARRAY  */
#line 844 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            if(ds[chartonum((yyval.val))].find("array")!=ds[chartonum((yyval.val))].end())
                            ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"["+ds[chartonum((yyvsp[0].val))]["var"]+"]"; }
#line 4160 "parser_1st.tab.c"
    break;

  case 238: /* PRIMARY: ARRAYCREATIONEXPRESSION  */
#line 847 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4166 "parser_1st.tab.c"
    break;

  case 239: /* PRIMARYNONEWARRAY: LITERAL  */
#line 849 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4172 "parser_1st.tab.c"
    break;

  case 240: /* PRIMARYNONEWARRAY: CLASSLITERAL  */
#line 850 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4178 "parser_1st.tab.c"
    break;

  case 241: /* PRIMARYNONEWARRAY: THIS  */
#line 851 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 4187 "parser_1st.tab.c"
    break;

  case 243: /* PRIMARYNONEWARRAY: OPENPARAN EXPRESSION CLOSEPARAN  */
#line 856 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4193 "parser_1st.tab.c"
    break;

  case 244: /* PRIMARYNONEWARRAY: CLASSINSTANCECREATIONEXPRESSION  */
#line 857 "parser_1st.y"
                                                              {(yyval.val) = (yyvsp[0].val); generalmap[(yyval.val)].isnewclass = true;}
#line 4199 "parser_1st.tab.c"
    break;

  case 245: /* PRIMARYNONEWARRAY: FIELDACCESS  */
#line 858 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4205 "parser_1st.tab.c"
    break;

  case 246: /* PRIMARYNONEWARRAY: ARRAYACCESS  */
#line 859 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4211 "parser_1st.tab.c"
    break;

  case 247: /* PRIMARYNONEWARRAY: METHODINVOCATION  */
#line 860 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4217 "parser_1st.tab.c"
    break;

  case 249: /* LITERAL: INTEGERLITERAL  */
#line 863 "parser_1st.y"
                        {(yyval.val) = new_temp();  ds[chartonum((yyval.val))]["type"] = "int"; ds[chartonum((yyval.val))]["var"] = new_var(); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); tempinitval[ds[chartonum((yyval.val))]["var"]]= chartonum((yyvsp[0].val)); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4223 "parser_1st.tab.c"
    break;

  case 250: /* LITERAL: FLOATINGPOINTLITERAL  */
#line 864 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["start"] = numtostring(code.size());ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4229 "parser_1st.tab.c"
    break;

  case 251: /* LITERAL: BOOLEANLITERAL  */
#line 865 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4235 "parser_1st.tab.c"
    break;

  case 252: /* LITERAL: CHARACTERLITERAL  */
#line 866 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4241 "parser_1st.tab.c"
    break;

  case 253: /* LITERAL: STRINGLITERAL  */
#line 867 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4247 "parser_1st.tab.c"
    break;

  case 254: /* LITERAL: TEXTBLOCK  */
#line 868 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4253 "parser_1st.tab.c"
    break;

  case 255: /* LITERAL: NULLLITERAL  */
#line 869 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4259 "parser_1st.tab.c"
    break;

  case 265: /* CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
#line 882 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[0].val);}
#line 4265 "parser_1st.tab.c"
    break;

  case 269: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  */
#line 887 "parser_1st.y"
                                                                                                           {(yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-2].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-2].val))];  }
#line 4271 "parser_1st.tab.c"
    break;

  case 270: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  */
#line 888 "parser_1st.y"
                                                                                                                     {/*TODO*/}
#line 4277 "parser_1st.tab.c"
    break;

  case 271: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 889 "parser_1st.y"
                                                                                                                        {/*TODO*/}
#line 4283 "parser_1st.tab.c"
    break;

  case 272: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY  */
#line 890 "parser_1st.y"
                                                                                                                                  {/*TODO*/}
#line 4289 "parser_1st.tab.c"
    break;

  case 277: /* CLASSORINTERFACETYPETOINSTANTIATE: IDENTIFIER  */
#line 896 "parser_1st.y"
                                                {   (yyval.val) = new_temp(); ds[ chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val)); ds[ chartonum((yyval.val))]["class"] = "true";
                                                     }
#line 4296 "parser_1st.tab.c"
    break;

  case 278: /* ARGUMENTLIST: EXPRESSION  */
#line 899 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            ds2[chartonum((yyval.val))]["type"].push_back(ds[chartonum((yyvsp[0].val))]["type"]);
                            ds2[chartonum((yyval.val))]["var"].push_back(ds[chartonum((yyvsp[0].val))]["var"]);
                            }
#line 4305 "parser_1st.tab.c"
    break;

  case 279: /* ARGUMENTLIST: ARGUMENTLIST COMMA EXPRESSION  */
#line 903 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4318 "parser_1st.tab.c"
    break;

  case 280: /* METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  */
#line 912 "parser_1st.y"
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
#line 4335 "parser_1st.tab.c"
    break;

  case 281: /* METHODINVOCATION: METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 924 "parser_1st.y"
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
#line 4359 "parser_1st.tab.c"
    break;

  case 282: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 943 "parser_1st.y"
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
#line 4388 "parser_1st.tab.c"
    break;

  case 283: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 967 "parser_1st.y"
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
#line 4420 "parser_1st.tab.c"
    break;

  case 312: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS  */
#line 1026 "parser_1st.y"
                                                         {/*NOT SUPPORTED*/}
#line 4426 "parser_1st.tab.c"
    break;

  case 313: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS DIMS  */
#line 1027 "parser_1st.y"
                                                                       {/*NOT SUPPORTED*/}
#line 4432 "parser_1st.tab.c"
    break;

  case 314: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER  */
#line 1028 "parser_1st.y"
                                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-2].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; assert (generalmap[(yyvsp[0].val)].vinit.dims.size() == temp[(yyvsp[-1].val)]); }
#line 4438 "parser_1st.tab.c"
    break;

  case 315: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER  */
#line 1029 "parser_1st.y"
                                                                               {/*NOT SUPPORTED*/}
#line 4444 "parser_1st.tab.c"
    break;

  case 316: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS  */
#line 1030 "parser_1st.y"
                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; reverse(all(generalmap[(yyval.val)].vinit.dims)); ds[chartonum((yyval.val))]["arr"] = "true"; ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ ds[chartonum((yyvsp[0].val))]["var"]+" * "+numtostring(gettypesize(chartostring((yyvsp[-1].val))))); ds[chartonum((yyval.val))]["type"] = chartostring((yyvsp[-1].val)); ds[chartonum((yyval.val))]["start"] = ds[chartonum((yyvsp[0].val))]["start"];}
#line 4450 "parser_1st.tab.c"
    break;

  case 317: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS  */
#line 1031 "parser_1st.y"
                                                                   {/*NOT SUPPORTED*/}
#line 4456 "parser_1st.tab.c"
    break;

  case 318: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS  */
#line 1032 "parser_1st.y"
                                                   {/*NOT SUPPORTED*/}
#line 4462 "parser_1st.tab.c"
    break;

  case 319: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS  */
#line 1033 "parser_1st.y"
                                                              {/*NOT SUPPORTED*/}
#line 4468 "parser_1st.tab.c"
    break;

  case 320: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE  */
#line 1034 "parser_1st.y"
                                               {/*TODO whats this*/}
#line 4474 "parser_1st.tab.c"
    break;

  case 321: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE  */
#line 1035 "parser_1st.y"
                                                         {/*TODO whats this*/}
#line 4480 "parser_1st.tab.c"
    break;

  case 322: /* ARRAYINITIALIZER: OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  */
#line 1037 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4486 "parser_1st.tab.c"
    break;

  case 323: /* ARRAYINITIALIZER: OPENCURLY CLOSECURLY  */
#line 1038 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4492 "parser_1st.tab.c"
    break;

  case 324: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST  */
#line 1040 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4498 "parser_1st.tab.c"
    break;

  case 325: /* ARRAYINITIALIZER1: COMMA  */
#line 1041 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=2;}
#line 4504 "parser_1st.tab.c"
    break;

  case 326: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST COMMA  */
#line 1042 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4510 "parser_1st.tab.c"
    break;

  case 327: /* DIMEXPRS: DIMEXPR  */
#line 1044 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[0].val))];}
#line 4516 "parser_1st.tab.c"
    break;

  case 328: /* DIMEXPRS: DIMEXPRS DIMEXPR  */
#line 1045 "parser_1st.y"
                             {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum((yyvsp[-1].val))]["var"]+" *"+ds[chartonum((yyvsp[0].val))]["type"]+" "+ds[ chartonum((yyvsp[0].val))]["var"]);
                              ds[ chartonum((yyval.val))]["var"] = t;  }
#line 4524 "parser_1st.tab.c"
    break;

  case 329: /* DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1049 "parser_1st.y"
                                            {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = varaddrstoint(ds[chartonum((yyvsp[-1].val))]["var"]); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-1].val))];}
#line 4530 "parser_1st.tab.c"
    break;

  case 330: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZER  */
#line 1051 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4536 "parser_1st.tab.c"
    break;

  case 331: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  */
#line 1052 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4542 "parser_1st.tab.c"
    break;

  case 333: /* ARRAYACCESS: PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1059 "parser_1st.y"
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
                string ttt= new_var();
                code.push_back(ttt+" = "+t+" + "+ds[curr3]["var"]);

                code.push_back(ds[curr]["var"]+" = "+ttt+" * "+numtostring(gettypesize(ds[curr3]["var"]))); 
            }
#line 4570 "parser_1st.tab.c"
    break;

  case 334: /* ARRAYACCESS: IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1082 "parser_1st.y"
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
#line 4588 "parser_1st.tab.c"
    break;

  case 335: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  */
#line 1096 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4594 "parser_1st.tab.c"
    break;

  case 336: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  */
#line 1097 "parser_1st.y"
                                                                                                    {}
#line 4600 "parser_1st.tab.c"
    break;

  case 337: /* CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  */
#line 1099 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4606 "parser_1st.tab.c"
    break;

  case 338: /* CONDITIONALOREXPRESSION: CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  */
#line 1100 "parser_1st.y"
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
#line 4624 "parser_1st.tab.c"
    break;

  case 339: /* CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  */
#line 1114 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4630 "parser_1st.tab.c"
    break;

  case 340: /* CONDITIONALANDEXPRESSION: CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  */
#line 1115 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4644 "parser_1st.tab.c"
    break;

  case 341: /* INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  */
#line 1125 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4650 "parser_1st.tab.c"
    break;

  case 342: /* INCLUSIVEOREXPRESSION: INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  */
#line 1126 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4663 "parser_1st.tab.c"
    break;

  case 343: /* EXCLUSIVEOREXPRESSION: ANDEXPRESSION  */
#line 1135 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4669 "parser_1st.tab.c"
    break;

  case 344: /* EXCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  */
#line 1136 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4682 "parser_1st.tab.c"
    break;

  case 345: /* ANDEXPRESSION: EQUALITYEXPRESSION  */
#line 1144 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4688 "parser_1st.tab.c"
    break;

  case 346: /* ANDEXPRESSION: ANDEXPRESSION AND EQUALITYEXPRESSION  */
#line 1145 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4702 "parser_1st.tab.c"
    break;

  case 347: /* EQUALITYEXPRESSION: RELATIONALEXPRESSION  */
#line 1155 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
#line 4715 "parser_1st.tab.c"
    break;

  case 348: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  */
#line 1163 "parser_1st.y"
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
#line 4736 "parser_1st.tab.c"
    break;

  case 349: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  */
#line 1179 "parser_1st.y"
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
#line 4758 "parser_1st.tab.c"
    break;

  case 350: /* RELATIONALEXPRESSION: SHIFTEXPRESSION  */
#line 1197 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4768 "parser_1st.tab.c"
    break;

  case 351: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  */
#line 1202 "parser_1st.y"
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
#line 4791 "parser_1st.tab.c"
    break;

  case 352: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  */
#line 1220 "parser_1st.y"
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
#line 4810 "parser_1st.tab.c"
    break;

  case 353: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  */
#line 1234 "parser_1st.y"
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
#line 4829 "parser_1st.tab.c"
    break;

  case 354: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  */
#line 1248 "parser_1st.y"
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
#line 4848 "parser_1st.tab.c"
    break;

  case 356: /* SHIFTEXPRESSION: ADDITIVEEXPRESSION  */
#line 1264 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4854 "parser_1st.tab.c"
    break;

  case 357: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  */
#line 1265 "parser_1st.y"
                                                                                    {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4868 "parser_1st.tab.c"
    break;

  case 358: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1274 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4881 "parser_1st.tab.c"
    break;

  case 359: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1282 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4894 "parser_1st.tab.c"
    break;

  case 360: /* ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  */
#line 1291 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 4900 "parser_1st.tab.c"
    break;

  case 361: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  */
#line 1292 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4913 "parser_1st.tab.c"
    break;

  case 362: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  */
#line 1300 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4926 "parser_1st.tab.c"
    break;

  case 363: /* MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  */
#line 1309 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4932 "parser_1st.tab.c"
    break;

  case 364: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  */
#line 1310 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4945 "parser_1st.tab.c"
    break;

  case 365: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  */
#line 1318 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4958 "parser_1st.tab.c"
    break;

  case 366: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  */
#line 1326 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4971 "parser_1st.tab.c"
    break;

  case 367: /* UNARYEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1335 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4977 "parser_1st.tab.c"
    break;

  case 368: /* UNARYEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1336 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4983 "parser_1st.tab.c"
    break;

  case 369: /* UNARYEXPRESSION: PLUS UNARYEXPRESSION  */
#line 1337 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 4991 "parser_1st.tab.c"
    break;

  case 370: /* UNARYEXPRESSION: MINUS UNARYEXPRESSION  */
#line 1340 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5004 "parser_1st.tab.c"
    break;

  case 371: /* UNARYEXPRESSION: UNARYEXPRESSIONNOTPLUSMINUS  */
#line 1348 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5010 "parser_1st.tab.c"
    break;

  case 372: /* PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  */
#line 1350 "parser_1st.y"
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
#line 5028 "parser_1st.tab.c"
    break;

  case 373: /* PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  */
#line 1364 "parser_1st.y"
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
#line 5046 "parser_1st.tab.c"
    break;

  case 374: /* UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  */
#line 1378 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5052 "parser_1st.tab.c"
    break;

  case 375: /* UNARYEXPRESSIONNOTPLUSMINUS: COMPLEMENT UNARYEXPRESSION  */
#line 1379 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5065 "parser_1st.tab.c"
    break;

  case 376: /* UNARYEXPRESSIONNOTPLUSMINUS: NOT UNARYEXPRESSION  */
#line 1387 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5078 "parser_1st.tab.c"
    break;

  case 377: /* POSTFIXEXPRESSION: PRIMARY  */
#line 1396 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5084 "parser_1st.tab.c"
    break;

  case 378: /* POSTFIXEXPRESSION: EXPRESSIONNAME  */
#line 1397 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5090 "parser_1st.tab.c"
    break;

  case 379: /* POSTFIXEXPRESSION: IDENTIFIER  */
#line 1398 "parser_1st.y"
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
#line 5109 "parser_1st.tab.c"
    break;

  case 380: /* POSTFIXEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1412 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5115 "parser_1st.tab.c"
    break;

  case 381: /* POSTFIXEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1413 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5121 "parser_1st.tab.c"
    break;

  case 382: /* POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  */
#line 1415 "parser_1st.y"
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
#line 5138 "parser_1st.tab.c"
    break;

  case 383: /* POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  */
#line 1428 "parser_1st.y"
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
#line 5157 "parser_1st.tab.c"
    break;

  case 385: /* METHODDECLARATION: METHODHEADER METHODBODY  */
#line 1446 "parser_1st.y"
                                            {
    (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    
    for(auto i:ds2[chartonum((yyval.val))]["param"])
    code.push_back("pop param, "+ i);
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$1].name<<endl;
}
#line 5171 "parser_1st.tab.c"
    break;

  case 386: /* METHODDECLARATION: SUPER1 METHODHEADER METHODBODY  */
#line 1457 "parser_1st.y"
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
#line 5201 "parser_1st.tab.c"
    break;

  case 387: /* METHODDECLARATION: SUPER2 METHODHEADER METHODBODY  */
#line 1482 "parser_1st.y"
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
#line 5230 "parser_1st.tab.c"
    break;

  case 388: /* METHODDECLARATION: SUPER3 METHODHEADER METHODBODY  */
#line 1506 "parser_1st.y"
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
#line 5259 "parser_1st.tab.c"
    break;

  case 389: /* METHODDECLARATION: METHODMODIFIERS METHODHEADER METHODBODY  */
#line 1530 "parser_1st.y"
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
#line 5288 "parser_1st.tab.c"
    break;

  case 395: /* METHODHEADER: TYPE METHODDECLARATOR  */
#line 1561 "parser_1st.y"
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
        // preservedsymboltable[{x.vid.name, scope}]= symboltable[x.vid.name];
        
        }
        //  in reverse
        ll toffset=0;
        for(int ii=generalmap[(yyval.val)].farglist.size()-1 ; ii>=0; ii-- ){

                toffset -=   gettypesize(symboltable[generalmap[(yyval.val)].farglist[ii].vid.name].typ.name);
                              
        symboltable[generalmap[(yyval.val)].farglist[ii].vid.name].offset= toffset;
        preservedsymboltable[{generalmap[(yyval.val)].farglist[ii].vid.name, scope}]= symboltable[generalmap[(yyval.val)].farglist[ii].vid.name];

        }
        
        


        }
#line 5337 "parser_1st.tab.c"
    break;

  case 396: /* METHODHEADER: VOID METHODDECLARATOR  */
#line 1605 "parser_1st.y"
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
#line 5372 "parser_1st.tab.c"
    break;

  case 407: /* METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1650 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));              
                                        method_det[curr_class][chartostring((yyvsp[-2].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        // cout<<"methodhead "<<ds[chartonum($$)]["method_name"]<<"\n";
                                        }
#line 5385 "parser_1st.tab.c"
    break;

  case 408: /* METHODDECLARATOR: IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 1658 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                method_det[curr_class][chartostring((yyvsp[-3].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-3].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        // for(auto i:ds2[curr3]["param"])
                                        // code.push_back("pop param, "+ i);
                                        ds2[curr]["param"] = ds2[curr3]["param"];}
#line 5398 "parser_1st.tab.c"
    break;

  case 417: /* FORMALPARAMETERLIST: FORMALPARAMETER  */
#line 1676 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 5407 "parser_1st.tab.c"
    break;

  case 418: /* FORMALPARAMETERLIST: FORMALPARAMETERLIST COMMA FORMALPARAMETER  */
#line 1680 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 5417 "parser_1st.tab.c"
    break;

  case 419: /* FORMALPARAMETER: TYPE VARIABLEDECLARATORID  */
#line 1686 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 5426 "parser_1st.tab.c"
    break;

  case 421: /* FORMALPARAMETER: FINAL TYPE VARIABLEDECLARATORID  */
#line 1691 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 5435 "parser_1st.tab.c"
    break;

  case 424: /* METHODBODY: BLOCK  */
#line 1701 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 5441 "parser_1st.tab.c"
    break;

  case 428: /* BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 1708 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val);  }
#line 5447 "parser_1st.tab.c"
    break;

  case 430: /* BLOCKSTATEMENTS: BLOCKSTATEMENT  */
#line 1711 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val);  
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
#line 5455 "parser_1st.tab.c"
    break;

  case 431: /* BLOCKSTATEMENTS: BLOCKSTATEMENTS BLOCKSTATEMENT  */
#line 1714 "parser_1st.y"
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
#line 5470 "parser_1st.tab.c"
    break;

  case 433: /* BLOCKSTATEMENT: STATEMENT  */
#line 1727 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
               }
#line 5477 "parser_1st.tab.c"
    break;

  case 435: /* LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  */
#line 1732 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 5483 "parser_1st.tab.c"
    break;

  case 436: /* LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1734 "parser_1st.y"
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
#line 5545 "parser_1st.tab.c"
    break;

  case 437: /* LOCALVARIABLEDECLARATION: LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1791 "parser_1st.y"
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
#line 5611 "parser_1st.tab.c"
    break;

  case 438: /* LOCALVARIABLETYPE: TYPE  */
#line 1853 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 5617 "parser_1st.tab.c"
    break;

  case 439: /* LOCALVARIABLETYPE: VAR  */
#line 1854 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5623 "parser_1st.tab.c"
    break;

  case 440: /* STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 1857 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
#line 5629 "parser_1st.tab.c"
    break;

  case 441: /* STATEMENT: LABELEDSTATEMENT  */
#line 1858 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5635 "parser_1st.tab.c"
    break;

  case 442: /* STATEMENT: IFTHENSTATEMENT  */
#line 1859 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5641 "parser_1st.tab.c"
    break;

  case 443: /* STATEMENT: IFTHENELSESTATEMENT  */
#line 1860 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5647 "parser_1st.tab.c"
    break;

  case 444: /* STATEMENT: WHILESTATEMENT  */
#line 1861 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5653 "parser_1st.tab.c"
    break;

  case 445: /* STATEMENT: FORSTATEMENT  */
#line 1862 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5659 "parser_1st.tab.c"
    break;

  case 446: /* STATEMENT: PRINTLN  */
#line 1863 "parser_1st.y"
                            {(yyval.val) = new_temp();ds[chartonum((yyval.val))]["start"] = numtostring(code.size());code.push_back("print "+ chartostring((yyvsp[0].val)).substr(19,chartostring((yyvsp[0].val)).size() -21));   }
#line 5665 "parser_1st.tab.c"
    break;

  case 447: /* STATEMENT: LOCALVARIABLEDECLARATIONSTATEMENT  */
#line 1864 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val); 
                
               }
#line 5673 "parser_1st.tab.c"
    break;

  case 448: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  */
#line 1868 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5679 "parser_1st.tab.c"
    break;

  case 449: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EMPTYSTATEMENT  */
#line 1870 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5685 "parser_1st.tab.c"
    break;

  case 450: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EXPRESSIONSTATEMENT  */
#line 1871 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5691 "parser_1st.tab.c"
    break;

  case 451: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: ASSERTSTATEMENT  */
#line 1872 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5697 "parser_1st.tab.c"
    break;

  case 452: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BREAKSTATEMENT  */
#line 1873 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5703 "parser_1st.tab.c"
    break;

  case 453: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: CONTINUESTATEMENT  */
#line 1874 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5709 "parser_1st.tab.c"
    break;

  case 454: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: RETURNSTATEMENT  */
#line 1875 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5715 "parser_1st.tab.c"
    break;

  case 455: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: THROWSTATEMENT  */
#line 1876 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5721 "parser_1st.tab.c"
    break;

  case 456: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: YIELDSTATEMENT  */
#line 1877 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5727 "parser_1st.tab.c"
    break;

  case 457: /* EMPTYSTATEMENT: SEMICOLON  */
#line 1879 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5733 "parser_1st.tab.c"
    break;

  case 458: /* EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  */
#line 1881 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val); }
#line 5739 "parser_1st.tab.c"
    break;

  case 459: /* STATEMENTEXPRESSION: ASSIGNMENT  */
#line 1883 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5745 "parser_1st.tab.c"
    break;

  case 460: /* STATEMENTEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1884 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5751 "parser_1st.tab.c"
    break;

  case 461: /* STATEMENTEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1885 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5757 "parser_1st.tab.c"
    break;

  case 462: /* STATEMENTEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1886 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5763 "parser_1st.tab.c"
    break;

  case 463: /* STATEMENTEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1887 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5769 "parser_1st.tab.c"
    break;

  case 464: /* STATEMENTEXPRESSION: METHODINVOCATION  */
#line 1888 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5775 "parser_1st.tab.c"
    break;

  case 465: /* STATEMENTEXPRESSION: CLASSINSTANCECREATIONEXPRESSION  */
#line 1889 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5781 "parser_1st.tab.c"
    break;

  case 468: /* BREAKSTATEMENT: BREAK SEMICOLON  */
#line 1894 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5794 "parser_1st.tab.c"
    break;

  case 470: /* CONTINUESTATEMENT: CONTINUE SEMICOLON  */
#line 1904 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5807 "parser_1st.tab.c"
    break;

  case 472: /* RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  */
#line 1914 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = ds[exp]["start"];
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5818 "parser_1st.tab.c"
    break;

  case 473: /* RETURNSTATEMENT: RETURN SEMICOLON  */
#line 1920 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 5829 "parser_1st.tab.c"
    break;

  case 477: /* IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 1933 "parser_1st.y"
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
#line 5850 "parser_1st.tab.c"
    break;

  case 478: /* IFTHENELSESTATEMENT: TEMP ELSE STATEMENT  */
#line 1950 "parser_1st.y"
                                           {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr1]["falselist"],stringtonum(ds[curr3]["start"]));
                                                                    backpatch(ds3[curr1]["endlist"],code.size());
                                                                    // backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    // backpatch(ds3[curr5]["endlist"],code.size());
                                                                    // backpatch(ds3[curr7]["endlist"],code.size());
                                                                    ds[curr]["start"] = ds[curr1]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = merge(ds3[curr1]["continuelist"],ds3[curr3]["continuelist"]);
                                                                    ds3[curr]["breaklist"] = merge(ds3[curr1]["breaklist"],ds3[curr3]["breaklist"]);
                                                                    // ds3[curr]["truelist"] = vector<int>();
                                                                    // ds3[curr]["falselist"] = vector<int>();
}
#line 5869 "parser_1st.tab.c"
    break;

  case 479: /* IFTHENELSESTATEMENTNOSHORTIF: TEMP ELSE STATEMENTNOSHORTIF  */
#line 1965 "parser_1st.y"
                                                                {   (yyval.val) = new_temp();
                                                                    // int curr = chartonum($$), curr3 = chartonum($3), curr5 = chartonum($5), curr7 = chartonum($7);
                                                                    // backpatch(ds3[curr3]["falselist"],stringtonum(ds[curr7]["start"]));
                                                                    // backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    // // backpatch(ds3[curr5]["endlist"],code.size());
                                                                    // // backpatch(ds3[curr7]["endlist"],code.size());
                                                                    // ds[curr]["start"] = ds[curr3]["start"];
                                                                    // ds[curr]["type"] = "null";
                                                                    // ds3[curr]["continuelist"] = merge(ds3[curr5]["continuelist"],ds3[curr7]["continuelist"]);
                                                                    // ds3[curr]["breaklist"] = merge(ds3[curr5]["breaklist"],ds3[curr7]["breaklist"]);
                                                                    // // ds3[curr]["truelist"] = vector<int>();
                                                                    // // ds3[curr]["falselist"] = vector<int>();
                                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr1]["falselist"],stringtonum(ds[curr3]["start"]));
                                                                    backpatch(ds3[curr1]["endlist"],code.size());
                                                                    // backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
                                                                    // backpatch(ds3[curr5]["endlist"],code.size());
                                                                    // backpatch(ds3[curr7]["endlist"],code.size());
                                                                    ds[curr]["start"] = ds[curr1]["start"];
                                                                    ds[curr]["type"] = "null";
                                                                    ds3[curr]["continuelist"] = merge(ds3[curr1]["continuelist"],ds3[curr3]["continuelist"]);
                                                                    ds3[curr]["breaklist"] = merge(ds3[curr1]["breaklist"],ds3[curr3]["breaklist"]);
                                                                    // ds3[curr]["truelist"] = vector<int>();
                                                                    // ds3[curr]["falselist"] = vector<int>();

}
#line 5900 "parser_1st.tab.c"
    break;

  case 480: /* TEMP: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 1992 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-2].val)), curr5 = chartonum((yyvsp[0].val));
ds[curr]["start"] = ds[curr3]["start"];
backpatch(ds3[curr3]["truelist"],stringtonum(ds[curr5]["start"]));
ds3[curr]["falselist"] = ds3[curr3]["falselist"];
ds3[curr]["breaklist"] = ds3[curr5]["breaklist"];
ds3[curr]["continuelist"] = ds3[curr5]["continuelist"];
ds3[curr]["endlist"] = vector<int>();
ds3[curr]["endlist"].push_back(code.size());
code.push_back("goto ");
}
#line 5916 "parser_1st.tab.c"
    break;

  case 481: /* STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 2004 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5922 "parser_1st.tab.c"
    break;

  case 482: /* STATEMENTNOSHORTIF: LABELEDSTATEMENTNOSHORTIF  */
#line 2005 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5928 "parser_1st.tab.c"
    break;

  case 483: /* STATEMENTNOSHORTIF: IFTHENELSESTATEMENTNOSHORTIF  */
#line 2006 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5934 "parser_1st.tab.c"
    break;

  case 484: /* STATEMENTNOSHORTIF: WHILESTATEMENTNOSHORTIF  */
#line 2007 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5940 "parser_1st.tab.c"
    break;

  case 485: /* STATEMENTNOSHORTIF: FORSTATEMENTNOSHORTIF  */
#line 2008 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5946 "parser_1st.tab.c"
    break;

  case 487: /* WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2012 "parser_1st.y"
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
#line 5962 "parser_1st.tab.c"
    break;

  case 488: /* FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  */
#line 2024 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); popscope();}
#line 5968 "parser_1st.tab.c"
    break;

  case 489: /* FORSTATEMENTNOSHORTIF: ENHANCEDFORSTATEMENTNOSHORTIF  */
#line 2025 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5974 "parser_1st.tab.c"
    break;

  case 490: /* WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 2028 "parser_1st.y"
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
#line 5989 "parser_1st.tab.c"
    break;

  case 491: /* FORSTATEMENT: BASICFORSTATEMENT  */
#line 2039 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5995 "parser_1st.tab.c"
    break;

  case 492: /* FORSTATEMENT: ENHANCEDFORSTATEMENT  */
#line 2040 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 6001 "parser_1st.tab.c"
    break;

  case 493: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 2042 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6014 "parser_1st.tab.c"
    break;

  case 494: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2050 "parser_1st.y"
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
#line 6030 "parser_1st.tab.c"
    break;

  case 495: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2061 "parser_1st.y"
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
#line 6049 "parser_1st.tab.c"
    break;

  case 496: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2075 "parser_1st.y"
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
#line 6070 "parser_1st.tab.c"
    break;

  case 497: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 2091 "parser_1st.y"
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
#line 6088 "parser_1st.tab.c"
    break;

  case 498: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2104 "parser_1st.y"
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
#line 6109 "parser_1st.tab.c"
    break;

  case 499: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2120 "parser_1st.y"
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
#line 6130 "parser_1st.tab.c"
    break;

  case 500: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2136 "parser_1st.y"
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
#line 6151 "parser_1st.tab.c"
    break;

  case 501: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2153 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp(); 
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6164 "parser_1st.tab.c"
    break;

  case 502: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2161 "parser_1st.y"
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
#line 6180 "parser_1st.tab.c"
    break;

  case 503: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2172 "parser_1st.y"
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
#line 6199 "parser_1st.tab.c"
    break;

  case 504: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2186 "parser_1st.y"
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
#line 6221 "parser_1st.tab.c"
    break;

  case 505: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2203 "parser_1st.y"
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
#line 6239 "parser_1st.tab.c"
    break;

  case 506: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2216 "parser_1st.y"
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
#line 6260 "parser_1st.tab.c"
    break;

  case 507: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2232 "parser_1st.y"
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
#line 6282 "parser_1st.tab.c"
    break;

  case 508: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2249 "parser_1st.y"
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
#line 6303 "parser_1st.tab.c"
    break;

  case 511: /* FORINIT: STATEMENTEXPRESSIONLIST  */
#line 2271 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 6309 "parser_1st.tab.c"
    break;

  case 512: /* FORINIT: LOCALVARIABLEDECLARATION  */
#line 2272 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 6315 "parser_1st.tab.c"
    break;

  case 513: /* FORUPDATE: STATEMENTEXPRESSIONLIST  */
#line 2274 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 6329 "parser_1st.tab.c"
    break;

  case 514: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION  */
#line 2284 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 6335 "parser_1st.tab.c"
    break;

  case 515: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION  */
#line 2285 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 6347 "parser_1st.tab.c"
    break;

  case 553: /* SUPER1: PUBLIC  */
#line 2338 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6353 "parser_1st.tab.c"
    break;

  case 554: /* SUPER1: PRIVATE  */
#line 2339 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6359 "parser_1st.tab.c"
    break;

  case 555: /* SUPER1: PROTECTED  */
#line 2340 "parser_1st.y"
                    {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6365 "parser_1st.tab.c"
    break;

  case 556: /* SUPER1: SUPER1 PUBLIC  */
#line 2341 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6371 "parser_1st.tab.c"
    break;

  case 557: /* SUPER1: SUPER1 PRIVATE  */
#line 2342 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6377 "parser_1st.tab.c"
    break;

  case 558: /* SUPER1: SUPER1 PROTECTED  */
#line 2343 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6383 "parser_1st.tab.c"
    break;

  case 559: /* SUPER2: STATIC  */
#line 2345 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6389 "parser_1st.tab.c"
    break;

  case 560: /* SUPER2: FINAL  */
#line 2346 "parser_1st.y"
                 {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6395 "parser_1st.tab.c"
    break;

  case 561: /* SUPER2: SUPER1 STATIC  */
#line 2347 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6401 "parser_1st.tab.c"
    break;

  case 562: /* SUPER2: SUPER1 FINAL  */
#line 2348 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6407 "parser_1st.tab.c"
    break;

  case 563: /* SUPER2: SUPER2 STATIC  */
#line 2349 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6413 "parser_1st.tab.c"
    break;

  case 564: /* SUPER2: SUPER2 FINAL  */
#line 2350 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6419 "parser_1st.tab.c"
    break;

  case 565: /* SUPER2: SUPER2 PUBLIC  */
#line 2351 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6425 "parser_1st.tab.c"
    break;

  case 566: /* SUPER2: SUPER2 PRIVATE  */
#line 2352 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6431 "parser_1st.tab.c"
    break;

  case 567: /* SUPER2: SUPER2 PROTECTED  */
#line 2353 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6437 "parser_1st.tab.c"
    break;

  case 568: /* SUPER3: ABSTRACT  */
#line 2355 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6443 "parser_1st.tab.c"
    break;

  case 569: /* SUPER3: STRICTFP  */
#line 2356 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6449 "parser_1st.tab.c"
    break;

  case 570: /* SUPER3: SUPER2 ABSTRACT  */
#line 2357 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6455 "parser_1st.tab.c"
    break;

  case 571: /* SUPER3: SUPER2 STRICTFP  */
#line 2358 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6461 "parser_1st.tab.c"
    break;

  case 572: /* SUPER3: SUPER3 ABSTRACT  */
#line 2359 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6467 "parser_1st.tab.c"
    break;

  case 573: /* SUPER3: SUPER3 STRICTFP  */
#line 2360 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6473 "parser_1st.tab.c"
    break;

  case 574: /* SUPER3: SUPER3 PUBLIC  */
#line 2361 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6479 "parser_1st.tab.c"
    break;

  case 575: /* SUPER3: SUPER3 PRIVATE  */
#line 2362 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6485 "parser_1st.tab.c"
    break;

  case 576: /* SUPER3: SUPER3 PROTECTED  */
#line 2363 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6491 "parser_1st.tab.c"
    break;

  case 577: /* SUPER3: SUPER3 STATIC  */
#line 2364 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6497 "parser_1st.tab.c"
    break;

  case 578: /* SUPER3: SUPER3 FINAL  */
#line 2365 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6503 "parser_1st.tab.c"
    break;

  case 579: /* FIELDMODIFIERS: SUPER3 TRANSIENT  */
#line 2367 "parser_1st.y"
                                 {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6509 "parser_1st.tab.c"
    break;

  case 580: /* FIELDMODIFIERS: SUPER3 VOLATILE  */
#line 2368 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6515 "parser_1st.tab.c"
    break;

  case 581: /* FIELDMODIFIERS: FIELDMODIFIERS TRANSIENT  */
#line 2369 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6521 "parser_1st.tab.c"
    break;

  case 582: /* FIELDMODIFIERS: FIELDMODIFIERS VOLATILE  */
#line 2370 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6527 "parser_1st.tab.c"
    break;

  case 583: /* FIELDMODIFIERS: FIELDMODIFIERS PUBLIC  */
#line 2371 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6533 "parser_1st.tab.c"
    break;

  case 584: /* FIELDMODIFIERS: FIELDMODIFIERS PRIVATE  */
#line 2372 "parser_1st.y"
                                     {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6539 "parser_1st.tab.c"
    break;

  case 585: /* FIELDMODIFIERS: FIELDMODIFIERS PROTECTED  */
#line 2373 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6545 "parser_1st.tab.c"
    break;

  case 586: /* FIELDMODIFIERS: FIELDMODIFIERS STATIC  */
#line 2374 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6551 "parser_1st.tab.c"
    break;

  case 587: /* FIELDMODIFIERS: FIELDMODIFIERS FINAL  */
#line 2375 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6557 "parser_1st.tab.c"
    break;

  case 588: /* METHODMODIFIERS: SUPER3 SYNCHRONIZED  */
#line 2378 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6563 "parser_1st.tab.c"
    break;

  case 589: /* METHODMODIFIERS: SUPER3 NATIVE  */
#line 2379 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6569 "parser_1st.tab.c"
    break;

  case 590: /* METHODMODIFIERS: METHODMODIFIERS SYNCHRONIZED  */
#line 2380 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6575 "parser_1st.tab.c"
    break;

  case 591: /* METHODMODIFIERS: METHODMODIFIERS NATIVE  */
#line 2381 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6581 "parser_1st.tab.c"
    break;

  case 592: /* METHODMODIFIERS: METHODMODIFIERS ABSTRACT  */
#line 2382 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6587 "parser_1st.tab.c"
    break;

  case 593: /* METHODMODIFIERS: METHODMODIFIERS STRICTFP  */
#line 2383 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6593 "parser_1st.tab.c"
    break;

  case 594: /* METHODMODIFIERS: METHODMODIFIERS PUBLIC  */
#line 2384 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6599 "parser_1st.tab.c"
    break;

  case 595: /* METHODMODIFIERS: METHODMODIFIERS PRIVATE  */
#line 2385 "parser_1st.y"
                                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6605 "parser_1st.tab.c"
    break;

  case 596: /* METHODMODIFIERS: METHODMODIFIERS PROTECTED  */
#line 2386 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6611 "parser_1st.tab.c"
    break;

  case 597: /* METHODMODIFIERS: METHODMODIFIERS STATIC  */
#line 2387 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6617 "parser_1st.tab.c"
    break;

  case 598: /* METHODMODIFIERS: METHODMODIFIERS FINAL  */
#line 2388 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6623 "parser_1st.tab.c"
    break;

  case 602: /* TYPEARGUMENT: REFERENCETYPE  */
#line 2395 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 6629 "parser_1st.tab.c"
    break;

  case 603: /* TYPEARGUMENT: WILDCARD  */
#line 2396 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 6635 "parser_1st.tab.c"
    break;

  case 608: /* INTERFACETYPE: CLASSTYPE  */
#line 2405 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 6641 "parser_1st.tab.c"
    break;


#line 6645 "parser_1st.tab.c"

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

#line 2407 "parser_1st.y"



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
      if(!verbose)  {freopen("/dev/null", "w", stderr);
      }
      else yydebug = 1;

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

    cout2<<"Token, Name(Lexeme), Type, Line Number, Scope, Dims(If array), ScopeINFO(Child), ScopeINFO(Parent), Offsets\n";

    for (auto x : preservedsymboltable){
        cout2<< x.second.token << ", " << x.first.first << ", " << x.second.typ.name << ", " << x.second.lineno << ", " << x.first.second << ", " << x.second.typ.dims << ", "<<x.second.offset << endl;

    }
   
    

    for(auto x : parentscope){
        cout2<<", , , , , , "<<x.first<<", "<<x.second<<", "<<endl;
    }



  

}
