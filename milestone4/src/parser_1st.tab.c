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
        polymethods.clear();
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

    


    

#line 282 "parser_1st.tab.c"

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
#define YYLAST   6471

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  155
/* YYNRULES -- Number of rules.  */
#define YYNRULES  608
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
       0,   242,   242,   243,   248,   249,   251,   252,   254,   255,
     257,   258,   259,   260,   261,   263,   264,   266,   268,   270,
     272,   275,   276,   278,   285,   302,   305,   306,   308,   364,
     365,   366,   368,   369,   370,   371,   373,   391,   394,   395,
     396,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   461,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   528,   529,   530,   532,
     533,   535,   536,   538,   539,   540,   541,   542,   544,   547,
     549,   550,   552,   553,   556,   557,   559,   560,   562,   564,
     566,   567,   569,   571,   572,   574,   575,   577,   578,   580,
     581,   582,   583,   585,   586,   587,   588,   589,   591,   645,
     697,   748,   793,   806,   831,   878,   880,   889,   897,   898,
     900,   902,   905,   907,   923,   924,   932,   933,   943,   945,
     947,   949,   951,   953,   956,   963,   964,   966,   978,   980,
     981,   982,   986,   987,   988,   989,   990,   991,   992,   994,
     995,   996,   997,   998,   999,  1000,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1010,  1011,  1013,  1014,  1015,  1016,  1018,
    1039,  1040,  1063,  1064,  1065,  1066,  1067,  1069,  1072,  1076,
    1085,  1097,  1117,  1142,  1169,  1170,  1171,  1172,  1173,  1174,
    1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,  1183,  1184,
    1185,  1186,  1188,  1189,  1190,  1191,  1192,  1194,  1195,  1197,
    1198,  1199,  1201,  1202,  1203,  1204,  1205,  1209,  1210,  1211,
    1212,  1213,  1215,  1216,  1218,  1219,  1220,  1222,  1223,  1227,
    1229,  1230,  1236,  1237,  1260,  1278,  1279,  1281,  1282,  1296,
    1297,  1307,  1308,  1317,  1318,  1326,  1327,  1337,  1345,  1361,
    1379,  1384,  1402,  1416,  1430,  1444,  1446,  1447,  1456,  1464,
    1473,  1474,  1482,  1491,  1492,  1500,  1508,  1517,  1518,  1519,
    1522,  1530,  1532,  1548,  1564,  1565,  1573,  1582,  1583,  1584,
    1598,  1599,  1601,  1616,  1633,  1636,  1650,  1676,  1702,  1728,
    1755,  1756,  1757,  1758,  1759,  1762,  1807,  1837,  1838,  1839,
    1840,  1841,  1842,  1845,  1847,  1848,  1850,  1852,  1862,  1873,
    1874,  1875,  1876,  1877,  1878,  1880,  1881,  1883,  1887,  1893,
    1897,  1898,  1904,  1905,  1908,  1909,  1911,  1913,  1915,  1916,
    1918,  1921,  1933,  1935,  1938,  1940,  1942,  1996,  2052,  2053,
    2056,  2057,  2058,  2059,  2060,  2061,  2062,  2063,  2066,  2068,
    2069,  2070,  2071,  2072,  2073,  2074,  2075,  2077,  2079,  2081,
    2082,  2083,  2084,  2085,  2086,  2087,  2089,  2090,  2092,  2100,
    2102,  2110,  2112,  2118,  2125,  2127,  2129,  2131,  2148,  2163,
    2190,  2202,  2203,  2204,  2205,  2206,  2208,  2210,  2222,  2223,
    2226,  2237,  2238,  2240,  2248,  2259,  2273,  2289,  2302,  2318,
    2334,  2351,  2359,  2370,  2384,  2401,  2414,  2430,  2447,  2465,
    2467,  2469,  2470,  2472,  2482,  2483,  2492,  2493,  2499,  2500,
    2509,  2524,  2612,  2613,  2614,  2615,  2616,  2617,  2620,  2622,
    2623,  2624,  2625,  2627,  2628,  2629,  2630,  2631,  2632,  2633,
    2634,  2635,  2636,  2637,  2638,  2639,  2640,  2641,  2642,  2643,
    2644,  2645,  2646,  2648,  2649,  2650,  2651,  2652,  2653,  2655,
    2656,  2657,  2658,  2659,  2660,  2661,  2662,  2663,  2665,  2666,
    2667,  2668,  2669,  2670,  2671,  2672,  2673,  2674,  2675,  2677,
    2678,  2679,  2680,  2681,  2682,  2683,  2684,  2685,  2688,  2689,
    2690,  2691,  2692,  2693,  2694,  2695,  2696,  2697,  2698,  2700,
    2702,  2703,  2705,  2706,  2708,  2709,  2711,  2712,  2715
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

#define YYPACT_NINF (-914)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-529)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1455,  -914,   -59,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
     -27,    -2,  -914,   157,  1940,  -914,  2129,  -914,  -914,  -914,
    -914,  1092,   656,   700,   362,   216,   114,   170,    44,   627,
    -914,  -914,  -914,  -914,   148,  -914,  -914,  -914,  -914,  -914,
     234,   243,  -914,  -914,  -914,  -914,  -914,  -914,  -914,   278,
     281,  -914,  -914,  -914,  -914,  -914,  -914,  -914,   284,   298,
     384,   384,   391,   324,    68,   188,   216,  -914,  2336,  -914,
     199,   410,  -914,     1,  6323,  -914,   324,    68,   188,   216,
     362,   216,   627,   362,   216,   627,   362,   216,   627,   379,
     106,  -914,  -914,  -914,  -914,  -914,   530,  -914,  -914,   537,
      68,   188,   216,  -914,   188,   216,  -914,   216,  -914,  -914,
    -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
     542,   216,   448,   589,   505,  -914,  -914,  -914,  -914,  -914,
    -914,  -914,  -914,  3228,  -914,  -914,   515,  2336,  -914,  -914,
    -914,  -914,   489,  -914,  -914,  -914,  -914,    47,   671,  1266,
    2766,  5959,  1983,  3534,  -914,    80,  -914,   636,  -914,  -914,
     313,   448,  -914,  -914,  6323,  -914,   960,  -914,  1756,  4126,
    3757,  -914,    68,   188,   216,  -914,   188,   216,  -914,   216,
    -914,   324,    68,   188,   216,  -914,  -914,   324,    68,   188,
     216,   324,    68,   188,   216,  -914,  -914,   324,    68,   188,
     216,   324,    68,   188,   216,  -914,  -914,   324,    68,   188,
     216,   549,  -914,   298,  -914,   384,   625,   188,   216,  -914,
     216,  -914,  -914,   216,  -914,  -914,  -914,  4249,  -914,  1472,
     597,   456,   443,  -914,   726,   597,    14,  -914,  5715,  5775,
    5775,  -914,  -914,  -914,  -914,  -914,  -914,  -914,    56,   910,
    -914,   645,  1250,  5715,  5715,  -914,    17,    18,  3673,  5715,
     738,   755,  -914,   771,   635,  -914,    23,   765,   774,  1542,
    -914,   782,  -914,  -914,   839,  1011,   189,   792,  -914,  -914,
     396,  -914,   437,  -914,  -914,  1198,  -914,  -914,    90,   422,
     541,  -914,  3228,  -914,  -914,  -914,   802,   699,  -914,  -914,
    -914,  -914,   813,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
    -914,  -914,   754,  -914,  -914,  -914,  -914,   868,   820,   989,
     448,   448,   822,  -914,  -914,  -914,  -914,  -914,   384,  2733,
     216,  -914,   552,   505,   489,    47,   505,   489,  -914,  -914,
    -914,  -914,   489,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
     699,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
     489,   827,  -914,   489,  -914,  -914,   505,  -914,   188,   216,
    -914,   216,  -914,  -914,   216,  -914,  -914,    68,   188,   216,
    -914,   188,   216,  -914,   216,  -914,  -914,  -914,    68,   188,
     216,  -914,   188,   216,  -914,   216,  -914,    68,   188,   216,
    -914,   188,   216,  -914,   216,  -914,  -914,  -914,    68,   188,
     216,  -914,   188,   216,  -914,   216,  -914,    68,   188,   216,
    -914,   188,   216,  -914,   216,  -914,  -914,  -914,    68,   188,
     216,  -914,   188,   216,  -914,   216,  -914,   801,   804,  -914,
    -914,  -914,   216,  -914,  -914,  -914,  -914,   489,  4495,  4372,
    3879,  3534,   733,   -34,   834,  -914,   831,   830,   699,  -914,
    3736,  -914,   840,  -914,    26,    14,  5775,  5775,  5775,  5775,
    1855,    23,   765,   841,  -914,  -914,  -914,  -914,  -914,   291,
     814,   823,   825,   833,   614,   242,   376,   572,   693,  -914,
    -914,  -914,  -914,    90,  -914,  -914,  -914,   111,   371,  -914,
    -914,  -914,  -914,    38,    52,   699,  -914,     6,   853,   856,
     856,   858,   756,   869,   196,  -914,   874,  -914,   878,  -914,
     880,   881,  5715,  5715,  5715,  3796,  3442,    27,  -914,    49,
    -914,    65,    30,  3859,  5715,    96,  5849,  -914,  -914,  -914,
    -914,  -914,  -914,  5715,    53,   108,  5715,  -914,  -914,  -914,
    -914,  -914,   877,   885,  -914,  3442,   597,   597,   920,  -914,
     887,  -914,   424,   879,  1324,   394,  -914,   343,  3228,  3228,
     252,  -914,  -914,   289,   258,   890,   269,  -914,  -914,   464,
    -914,   216,  -914,   667,  -914,  -914,   739,  -914,  -914,  -914,
     800,  -914,   216,  -914,  -914,  -914,   188,   216,  -914,   216,
    -914,  -914,   216,  -914,  -914,  -914,  -914,   188,   216,  -914,
     216,  -914,  -914,   216,  -914,  -914,   188,   216,  -914,   216,
    -914,  -914,   216,  -914,  -914,  -914,  -914,   188,   216,  -914,
     216,  -914,  -914,   216,  -914,  -914,   188,   216,  -914,   216,
    -914,  -914,   216,  -914,  -914,  -914,  -914,   188,   216,  -914,
     216,  -914,  -914,   216,  -914,  -914,   384,   860,  -914,  -914,
     489,   489,   489,   489,   877,    40,   316,  -914,   862,   884,
    -914,   889,  -914,  2961,  -914,  -914,  -914,  -914,   891,  -914,
    -914,  -914,  -914,  -914,  -914,  5715,  5775,  5775,  5775,  5775,
    5775,  5775,  5775,  3919,  3982,   384,  5775,  5775,  5775,  5775,
    5775,  5775,  5775,  5775,  -914,   798,   922,   847,   885,   623,
    -914,   345,  -914,  -914,  4042,   265,   856,  -914,   265,   856,
    4105,  -914,   953,  -914,  -914,  5715,  -914,  -914,  -914,  -914,
     954,   955,   958,   963,   910,  -914,   370,  -914,    69,   966,
    -914,   850,  -914,  -914,  -914,  -914,   178,  -914,  -914,   400,
     968,   971,  -914,   864,  4165,   956,  -914,   980,   984,  -914,
    -914,   875,   981,  -914,   876,   985,  -914,  -914,  -914,  -914,
     999,   495,   384,  4228,  4288,   120,   151,   271,  -914,  -914,
    3228,   987,   992,    92,   896,   380,  -914,   951,   941,  -914,
    -914,  -914,  -914,  -914,  -914,  -914,   216,  -914,  -914,  -914,
    -914,  -914,   216,  -914,  -914,  -914,   216,  -914,  -914,  -914,
    -914,  -914,   216,  -914,  -914,  -914,   216,  -914,  -914,  -914,
    -914,  -914,   216,  -914,  -914,  -914,  -914,   384,  -914,  -914,
    -914,  -914,   830,   877,   939,  1286,  -914,  -914,  -914,  -914,
    1007,  1003,  -914,   983,   814,   823,   825,   833,   614,   242,
     242,  5775,   376,  5775,   376,  -914,   572,   572,   572,   693,
     693,  -914,  -914,  -914,  -914,  4351,  1005,   384,   384,  -914,
       6,  -914,  1010,  -914,   830,  -914,  -914,   830,   216,   525,
    4411,  1017,  3587,  3442,  -914,  -914,    91,   105,  4474,  1012,
    -914,  -914,  5715,  -914,  -914,  4534,  1016,  6032,  1018,  5715,
    4608,  6347,  -914,  4668,  1025,  -914,  1305,  -914,  -914,  1033,
     526,  1035,   532,   485,   183,  1029,   200,  1036,   222,  -914,
    4731,  4791,   936,  -914,  -914,  -914,   553,  -914,  -914,  -914,
    -914,  -914,  -914,  -914,  -914,   830,  -914,   877,   556,  -914,
    3736,  5775,   376,   376,  -914,   565,  4854,  -914,  -914,  -914,
    -914,  -914,   216,   216,   576,  -914,  1041,  1584,  1042,  -914,
     979,  -914,   982,  -914,  -914,  -914,  -914,  -914,  -914,  -914,
    -914,   945,  1053,   952,  -914,   582,  4914,  -914,  -914,   596,
    4977,  3442,  1056,   984,  6064,  1059,  6095,  1073,  -914,  -914,
     602,  5037,  -914,   609,  -914,  1075,  -914,  1076,  5100,  1071,
    5160,  1072,  5223,  1074,  1082,   615,  1088,   617,  -914,  -914,
     830,   877,  -914,  -914,  -914,  -914,   624,  -914,  -914,   216,
    5715,  3587,  5882,  3587,  -914,  5283,  1084,  -914,  -914,   629,
    -914,  -914,   631,  -914,  3442,  3442,  1086,  3442,  3442,  1087,
    6125,  -914,  -914,   640,  -914,  -914,  -914,  1096,   653,  5346,
    1100,   676,  5406,  1103,   706,  5469,  -914,  1104,  -914,  1106,
     830,  -914,  -914,  1107,  -914,  5529,  1090,  1114,  -914,  -914,
     735,  5592,  -914,  -914,  -914,  -914,  3442,  -914,  -914,  3442,
    3442,  1110,  -914,  -914,  1119,  1120,   736,  -914,  1121,  1124,
     767,  -914,  1127,  1129,   775,  -914,  -914,  3587,  6155,  1130,
    5715,  5652,  -914,  -914,   784,  -914,  -914,  -914,  3442,  -914,
    -914,  1131,  -914,  -914,  1132,  -914,  -914,  1134,  -914,  3587,
    1128,  6186,  1133,  6218,  1139,  -914,  -914,  -914,  -914,  -914,
    -914,  3587,  3587,  1138,  3587,  3587,  1142,  6249,  -914,  -914,
    3587,  -914,  -914,  3587,  3587,  1143,  -914,  -914,  -914,  3587,
    -914
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
       0,     0,   166,     0,   225,   438,     6,    18,     0,   378,
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
       0,     0,     0,     0,     0,     0,     0,     0,   256,     0,
     257,     0,     0,     0,     0,     0,     0,   228,   229,   230,
     231,   232,   233,     0,     0,     0,     0,   382,   383,   428,
     431,   435,   216,   437,   458,     0,   402,   399,     0,   406,
     403,   404,     0,   241,   225,   224,   532,   377,     0,     0,
       0,   516,   520,     0,     0,     0,     0,   417,   420,     0,
     386,     0,   519,     0,   387,   388,     0,   389,    35,   174,
       0,   103,     0,   104,   106,   110,     0,     0,    59,     0,
      61,    62,     0,    65,    66,    68,   121,     0,     0,   123,
       0,   124,   127,     0,   128,   130,     0,     0,    74,     0,
      76,    77,     0,    80,    81,    83,   137,     0,     0,   139,
       0,   140,   143,     0,   144,   146,     0,     0,    89,     0,
      91,    92,     0,    95,    96,    98,   153,     0,     0,   155,
       0,   156,   159,     0,   160,   162,     0,   185,    41,   390,
       0,     0,     0,     0,   407,     0,     0,   415,     0,     0,
      21,     0,   213,     0,   214,   218,   219,   263,     0,   262,
     369,   370,   376,   375,   243,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   309,     0,   235,     0,   436,   604,
     602,     0,   600,   603,     0,   318,   316,   327,   319,   317,
       0,   277,     0,   474,   466,     0,   469,   471,   472,   475,
       0,     0,     0,     0,     0,   476,     0,   242,     0,    24,
     267,     0,   260,   261,   311,   307,     0,   280,   278,     0,
       0,    25,   266,     0,     0,   512,   514,     0,   511,   223,
     308,     0,   234,   268,     0,     0,   478,   401,   398,   524,
       0,     0,     0,     0,     0,     0,     0,     0,   531,   530,
       0,     0,     0,     0,     0,   216,   419,     0,     0,   521,
     209,   518,   210,   208,   175,   102,     0,    57,    58,    60,
      64,   119,     0,   120,   122,   126,     0,    72,    73,    75,
      79,   135,     0,   136,   138,   142,     0,    87,    88,    90,
      94,   151,     0,   152,   154,   158,   186,     0,   391,   392,
     393,   394,   410,   408,     0,     0,    22,   325,   323,   330,
       0,   324,   264,     0,   338,   340,   342,   344,   346,   348,
     349,     0,   351,     0,   352,   384,   357,   358,   359,   361,
     362,   365,   364,   366,   304,     0,     0,     0,     0,   605,
       0,   599,     0,   314,   312,   328,   315,   313,   269,     0,
       0,     0,     0,     0,   446,   334,     0,     0,     0,     0,
     306,   303,     0,   281,   332,     0,     0,     0,     0,     0,
       0,     0,   302,     0,     0,   333,     0,   525,   405,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   529,
       0,     0,     0,   421,   422,   522,     0,   418,    56,   118,
      71,   134,    86,   150,   187,   412,   416,   409,     0,   322,
     326,     0,   354,   353,   294,     0,     0,   606,   607,   601,
     329,   270,   271,   273,     0,   467,     0,   225,     0,   477,
     440,   483,     0,   480,   482,   484,   485,   488,   489,   490,
     310,     0,   236,     0,   282,     0,     0,   279,   286,     0,
       0,     0,     0,   513,     0,     0,     0,     0,   515,   290,
       0,     0,   526,     0,   537,     0,   533,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   423,   523,
     411,   414,   331,   336,   295,   296,     0,   272,   274,   275,
       0,     0,     0,     0,   305,     0,     0,   283,   284,     0,
     287,   288,     0,   493,     0,     0,     0,     0,     0,     0,
       0,   291,   292,     0,   527,   538,   534,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   539,     0,   535,     0,
     413,   297,   276,     0,   486,     0,   512,     0,   479,   298,
       0,     0,   285,   289,   494,   495,     0,   509,   497,     0,
       0,     0,   293,   545,     0,     0,     0,   541,     0,     0,
       0,   549,     0,     0,     0,   540,   536,     0,     0,     0,
       0,     0,   299,   300,     0,   496,   498,   499,     0,   546,
     547,     0,   542,   543,     0,   550,   551,     0,   487,     0,
       0,     0,     0,     0,     0,   301,   500,   548,   544,   552,
     501,     0,     0,     0,     0,     0,     0,     0,   502,   503,
       0,   510,   505,     0,     0,     0,   504,   506,   507,     0,
     508
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -914,  -914,    37,   915,   648,  -914,  -914,  -497,    78,   283,
    -914,  -498,  -914,    12,  -914,   632,  -914,    58,  -914,   504,
    -914,  -858,   -29,   -73,  2525,  -914,  1004,   -17,   694,  -914,
     959,  -914,  -914,  1723,  2969,  -914,  3012,  -914,  2465,  -914,
    1032,  -914,  -914,  -252,   713,  -566,  -670,   312,  -914,   101,
    -914,  -914,  1146,   844,  -914,  -914,  -914,  -200,   366,  -465,
     663,   647,   557,  -914,  -914,  -390,  -914,   666,  -322,  -914,
    1474,   237,  -914,   493,   500,   502,   499,   503,   115,  -584,
     124,   133,  -219,   829,   996,  -914,  1167,  1334,  1501,  -914,
      28,   -74,  -207,  -914,   420,   -95,  -316,  -439,   409,  -914,
    -308,  -914,  -914,   167,  -312,  -290,  -914,  -914,  -531,  -234,
    1413,  -472,  -914,  -914,  -529,  -914,  -914,  -914,  -914,  -914,
    -914,  -914,  -914,  -914,  -914,  -116,    51,  -914,  -914,  -914,
    -914,  -914,  -914,  -914,  -914,  -914,   179,  -913,  -530,  -914,
    1058,  1066,  -321,  -914,    19,   517,   528,  -914,   978,  -304,
    -914,   338,  -914,  -914,  -211
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,   265,   125,   471,   127,   128,   129,   130,   472,
      94,   457,   268,   269,    14,    15,    16,   270,    18,    25,
      19,   271,    68,   134,    75,   164,   165,    20,   166,    90,
      91,   212,   657,    64,    65,    96,    66,    99,    69,   137,
     138,   139,   140,   232,   233,   234,   674,   748,   474,   475,
     274,   543,   275,   276,   277,   278,   279,   529,   476,   281,
     511,   749,   477,   283,   284,   676,   840,   716,   717,   841,
     285,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     141,   142,   330,   560,   561,   235,   454,   576,   577,   578,
     326,   143,   144,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   961,   312,   963,   964,   965,   966,
     313,   314,   315,   967,   316,   968,   757,   982,   983,   146,
     147,   148,   331,   569,   317,   318,   319,   152,   153,   512,
     711,   712,   713,   869,    97
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,   163,   550,   839,   440,   755,   758,   756,   786,   571,
     710,   715,   718,   666,   582,   505,   575,   568,   709,    21,
     501,   502,    28,   455,   958,   570,   580,   230,   461,   584,
     515,   517,   462,    21,   585,    21,   464,   157,    70,   133,
     667,   462,    26,   507,   678,   553,   507,    74,    74,    74,
      74,   135,   587,    74,   507,   589,    74,    72,    17,    74,
     272,    67,   740,   784,   323,    24,   531,   678,   507,   507,
     752,  1036,    17,  1039,    17,   334,   337,   342,   503,   360,
     763,   579,    67,   678,   583,   507,   363,   149,    73,   736,
     668,   364,   133,   168,   334,   337,   342,    27,   586,   786,
     504,   737,   167,   738,   133,   124,   744,   507,   133,   852,
     854,   161,   507,   133,   590,   922,   361,   213,   329,   771,
     135,   507,    29,   214,   507,   158,   132,  1081,   581,   525,
      92,   -23,   162,   -20,    61,    62,   507,   547,   548,   659,
     463,   516,   518,    74,    74,    74,   328,    74,    74,   530,
      74,   739,   679,   447,   745,   527,   149,    30,    74,    74,
      74,    74,   704,   958,   552,   958,   832,   507,    74,    74,
      74,    74,   738,   321,   124,   742,   706,   760,    74,    74,
      74,    74,   913,   168,   738,  1120,   333,   336,   161,   350,
     161,   743,   167,   721,   737,   132,   738,   161,   855,   705,
     707,   161,    67,   321,   158,   366,   161,   161,  1133,   724,
    1136,   544,   154,   915,    71,   970,   552,   923,   874,   549,
     751,   877,   162,   741,  1145,   556,   557,   738,   746,   972,
      67,   753,   762,   545,   273,   145,   725,   528,    27,   958,
     761,   764,   770,   155,   739,   999,   448,   680,   681,   682,
     683,   498,   498,   708,   890,    62,   566,   780,   693,   694,
     791,   958,  1001,   133,   161,   464,   453,   942,   453,   943,
    1012,   531,    80,   958,   958,   751,   958,   958,   550,    67,
     788,   784,   958,   671,  1003,   958,   958,   507,   228,   438,
     789,   958,   110,   111,   112,   113,   114,   115,   116,   117,
     133,   329,   891,   685,   145,   133,   329,   889,   133,   327,
     740,   752,   763,   133,   781,   695,   110,   111,   112,   113,
     114,   115,   116,   117,   896,   873,   782,   788,   876,    59,
     510,   133,   667,   917,   133,   935,   686,   833,    67,    74,
      74,   565,    74,    93,    95,    74,   904,   738,   926,   767,
     768,   131,   828,   829,   830,   831,   870,   131,    82,    74,
      74,    74,   871,    74,    74,   544,    74,    83,   756,   574,
     947,   948,   988,   710,   660,   661,   662,   663,    59,    74,
      74,    74,   785,    74,    74,    60,    74,   777,   122,   534,
      61,    62,   886,   273,   875,   762,   938,   875,   456,    74,
      74,    74,    85,    74,    74,    86,    74,  -465,    88,  -465,
     960,   892,   534,    92,   887,   535,   267,  -465,   133,   131,
     131,   893,    89,    60,   834,   696,   697,   698,    61,    62,
     273,   673,   131,   131,   131,   131,   131,    92,   776,  1010,
     211,  -378,  -378,   131,   773,   826,   503,   131,  -464,   131,
    -464,   131,   131,   131,   458,   756,   459,   756,  -464,   110,
     111,   112,   113,   114,   115,   116,   117,   993,   504,  -380,
    -380,   914,   916,   918,   456,   458,   452,   790,   498,   498,
     498,   498,   861,   862,   863,   161,   161,   161,   161,   665,
     550,  1066,   758,   756,   131,   778,   779,   133,    95,   280,
     505,   327,   325,    67,   327,   998,   788,   886,    92,   327,
     131,   756,   131,  1060,   131,    98,   907,    22,   110,   111,
     112,   113,   114,   115,   116,   117,   133,   327,    23,   887,
     327,    22,   131,    22,   156,   131,   892,   892,    81,   133,
     133,   215,    23,   892,    23,    84,   952,   995,   216,   960,
     473,   960,   329,   997,    87,   110,   111,   112,   113,   114,
     115,   116,   117,    74,   788,   513,   514,   788,   227,   756,
     520,   521,   229,   572,  1009,   267,   892,  1011,    74,    74,
      92,    74,   971,   973,    74,   150,  1014,   892,  -381,  -381,
     320,   169,   756,   892,   756,   574,   151,  1019,    74,    74,
     838,    74,   170,  1027,    74,   699,   700,   892,   756,  -528,
     783,   559,   267,   892,   327,   131,   934,  1030,    74,    74,
     788,    74,   573,  1041,    74,   960,   892,   273,   892,   231,
    1044,   133,   133,   133,   133,   892,  1057,   273,  1059,   123,
     892,    67,   892,    59,   673,  1061,    32,   960,    33,   362,
    1072,   892,  1073,   525,   150,   -23,   273,   -20,   280,   960,
     960,  1082,   960,   960,   892,   151,   691,   692,   960,   273,
     273,   960,   960,   437,  1084,   526,    92,   960,   458,   527,
     792,   169,  -379,  -379,   867,   868,   673,   892,    60,   673,
     282,   332,   170,    61,    62,   280,   328,  1088,   498,   498,
     498,   498,   498,   498,   498,   498,   498,   919,   498,   498,
     498,   498,   498,   498,   498,   498,   126,   892,    63,    41,
      42,    43,   126,    76,    44,    45,    46,  1092,   701,   702,
     703,   131,   131,   131,   131,   131,   110,   111,   112,   113,
     114,   115,   116,   117,   449,    47,   892,   892,    48,   441,
     458,   133,   793,   460,   664,   450,  1102,  1111,   522,   -20,
      49,   528,   136,    50,    51,    52,   962,   939,    53,    54,
      55,   506,   675,    74,   181,   523,   187,   191,   892,   197,
     201,   266,   207,    74,   126,   126,   892,   532,  1114,    56,
     131,   524,    57,    74,   533,   892,  1117,   126,   126,   126,
     126,   126,   536,   573,    58,  1125,   849,   850,   126,   267,
     546,   458,   126,   794,   126,   551,   126,   126,   126,   267,
     856,   857,   858,   552,   665,   665,   554,   327,   327,   327,
     327,   136,   859,   860,   730,   731,   732,   733,   267,   555,
     588,   131,   558,   136,   -20,   669,   750,   656,   671,   282,
     670,   267,   267,   133,   133,   759,   131,    92,   765,   677,
     687,   688,   684,   498,   689,   498,   537,   538,   539,   540,
     541,   542,   665,  -277,   714,   126,   690,   126,   720,   126,
     721,   273,   723,    41,    42,    43,   282,   726,    44,    45,
      46,   727,   280,   728,   729,   456,   458,   126,   772,   774,
     126,   787,   280,   827,   835,   962,   834,   962,   836,    47,
     842,   673,    48,   110,   111,   112,   113,   114,   115,   116,
     117,   280,   864,   110,   111,   112,   113,   114,   115,   116,
     117,    34,    35,    36,   280,   280,    37,    38,    39,    95,
     266,   769,   865,   665,   110,   111,   112,   113,   114,   115,
     116,   117,   133,   498,   110,   111,   112,   113,   114,   115,
     116,   117,   286,   110,   111,   112,   113,   114,   115,   116,
     117,   866,   925,   880,   889,   882,   883,   266,   131,   884,
     126,   962,   885,   273,   273,   675,   888,   894,   896,   255,
     573,   895,   133,   900,   133,   901,   899,   843,   273,   902,
     904,   903,   273,   962,   905,   133,   133,   920,   133,   133,
     906,   573,   921,   936,   940,   962,   962,   131,   962,   962,
     924,   573,   119,   941,   962,   946,   872,   962,   962,   950,
     955,   984,   976,   962,    92,   320,   980,   881,  -226,  -226,
    -226,  -226,  -226,  -226,    92,   991,   994,   133,   996,  1000,
     133,   133,    50,    51,    52,   559,  1002,    53,    54,    55,
    1008,  1020,  1022,   267,  -481,    92,   898,  1023,   133,  1024,
     131,   131,  1064,  1025,  1068,    92,  1026,  1034,    56,   133,
    1037,    57,   273,   282,    92,   273,  1040,   273,  1045,  1046,
     133,  1049,  1052,   282,  1055,  1056,   126,   126,   126,   126,
     126,  1058,   133,   133,  1071,   133,   133,  1076,  1079,  1083,
      95,   133,   282,  1087,   133,   133,  1091,  1095,   131,  1096,
     133,   286,   273,   273,   273,   282,   282,  1101,  1097,   287,
    1100,  1108,  1109,  1110,  1112,   273,   273,  1113,   273,   273,
    1115,   273,  1116,  1121,  1127,  1128,   280,  1129,  1118,  1131,
     131,   131,  1137,   131,  1134,    34,    35,    36,   286,  1140,
      37,    38,    39,  1143,  1149,   267,   267,   509,   365,   324,
    1130,   672,   439,   567,   266,   722,   719,   273,  1013,   844,
     273,   273,  1138,  1139,   266,  1141,  1142,   845,   847,   131,
     846,  1146,   908,   848,  1147,  1148,    40,   927,   273,   273,
    1150,  1067,   322,   266,   977,   451,   126,   335,   949,   273,
       0,   985,   987,     0,     0,     0,   266,   266,     0,     0,
     273,   126,   273,     0,   273,  -227,  -227,  -227,  -227,  -227,
    -227,     0,   273,   273,     0,   273,   273,     0,   273,     0,
       0,   273,     0,     0,   273,   273,     0,     0,   280,   280,
     273,     0,   675,   110,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   280,   267,     0,   507,   280,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,    59,     0,     0,     0,     0,     0,   287,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     288,     0,     0,     0,   267,   267,   267,   937,   110,   111,
     112,   113,   114,   115,   116,   117,     0,   267,   267,     0,
     267,   267,     0,     0,     0,   287,   992,     0,     0,    34,
      35,    36,  1063,     0,    37,    38,    39,   282,     0,     0,
       0,   122,   525,     0,   -23,     0,   -20,   280,     0,     0,
     280,     0,   280,     0,     0,   286,   573,     0,     0,   267,
       0,     0,   267,   267,   526,   286,     0,   879,   775,     0,
      40,  -379,  -379,     0,   508,   573,     0,  1099,     0,     0,
     267,     0,   126,     0,   286,   499,   499,   280,   280,   280,
     123,   267,     0,     0,     0,     0,     0,   286,   286,     0,
     280,   280,   267,   280,   280,     0,   280,     0,     0,     0,
      92,     0,  1122,  1124,   267,   267,     0,   267,   267,     0,
     910,   912,     0,   267,     0,     0,   267,   267,   266,    92,
       0,     0,   267,     0,     0,   126,   126,     0,     0,   282,
     282,     0,   280,     0,     0,   280,   280,     0,   -20,     0,
     528,     0,     0,     0,   282,     0,     0,     0,   282,   288,
       0,     0,     0,   280,   280,     0,     0,   289,     1,     0,
       0,     0,     0,     0,   280,   110,   111,   112,   113,   114,
     115,   116,   117,   126,     0,   280,     0,   280,     0,   280,
       0,     0,   452,     0,     0,     0,   288,   280,   280,     0,
     280,   280,     0,   280,     0,     0,   280,     0,     0,   280,
     280,     0,   945,     0,     0,   280,     0,     0,     2,     3,
       4,     0,   287,     5,     6,     7,     0,   954,     0,     0,
     266,   266,   287,     0,     0,   975,     0,     0,   282,     0,
       0,   282,   979,   282,     8,     0,     0,     9,     0,     0,
     990,   287,     0,    10,   126,     0,     0,     0,     0,    11,
     534,     0,     0,     0,   287,   287,     0,  1005,  1007,  -224,
    -224,  -224,  -224,  -224,  -224,     0,     0,     0,   282,   282,
     282,     0,    12,     0,     0,     0,   535,     0,     0,     0,
       0,   282,   282,  1016,   282,   282,    92,   282,     0,     0,
       0,     0,   525,     0,   -23,     0,   -20,     0,     0,   286,
       0,     0,   499,   499,   499,   499,     0,     0,     0,     0,
       0,     0,     0,  1029,  1021,     0,   289,  1032,   527,   266,
       0,  -379,  -379,   282,   290,     0,   282,   282,  1043,     0,
       0,     0,     0,     0,     0,  1048,     0,  1051,     0,  1054,
       0,     0,     0,     0,   282,   282,     0,     0,     0,     0,
       0,     0,     0,   289,     0,   282,     0,     0,     0,   266,
     266,   266,  1070,     0,     0,     0,   282,     0,   282,     0,
     282,     0,   266,   266,     0,   266,   266,     0,   282,   282,
       0,   282,   282,   288,   282,     0,  1086,   282,     0,  1090,
     282,   282,  1094,   288,     0,     0,   282,     0,   -20,     0,
     528,   286,   286,   500,   500,     0,     0,     0,  1104,     0,
       0,     0,   288,     0,   266,     0,   286,   266,   266,     0,
     286,     0,     0,     0,     0,   288,   288,     0,     0,     0,
       0,     0,     0,     0,     0,   266,     0,     0,     0,     0,
       0,     0,    77,     0,     0,     0,   266,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,   266,     0,     0,
       0,     0,    59,     0,     0,     0,   287,     0,     0,   266,
     266,     0,   266,   266,     0,     0,   100,     0,   266,     0,
       0,   266,   266,   290,     0,     0,     0,   266,     0,   172,
       0,     0,     0,   182,     0,   188,   192,     0,   198,   202,
     286,   208,     0,   286,     0,   286,     0,     0,     0,    34,
      35,    36,     0,     0,    37,    38,    39,     0,     0,     0,
     290,   122,   499,   499,   499,   499,   499,   499,   499,   499,
     499,     0,   499,   499,   499,   499,   499,   499,   499,   499,
     286,   286,   286,     0,     0,     0,     0,     0,     0,     0,
     289,     0,     0,   286,   286,     0,   286,   286,     0,   286,
     289,     0,     0,   525,     0,   -23,     0,   -20,   287,   287,
      92,     0,  -225,  -225,  -225,  -225,  -225,  -225,     0,   289,
       0,     0,     0,   287,     0,     0,     0,   287,     0,   527,
       0,     0,   289,   289,   377,   286,     0,     0,   286,   286,
     388,     0,     0,     0,   397,     0,     0,     0,     0,     0,
     408,     0,     0,     0,   417,     0,   286,   286,     0,     0,
     428,     0,     0,     0,     0,     0,     0,   286,     0,   735,
     500,   500,   500,   500,     0,     0,     0,   288,   286,     0,
     286,     0,   286,     1,     0,     0,     0,     0,     0,     0,
     286,   286,     0,   286,   286,     0,   286,     0,   766,   286,
       0,     0,   286,   286,     0,     0,     0,   287,   286,   -20,
     287,   528,   287,     0,     0,     0,   110,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   499,     0,   499,
       0,     0,     0,     2,     3,     4,     0,     0,     5,     6,
       7,     0,     0,     0,     0,     0,     0,   287,   287,   287,
       0,     0,     0,     0,     0,     0,     0,   290,     0,     8,
     287,   287,     9,   287,   287,     0,   287,   290,    10,     0,
       0,     0,     0,     0,    11,     0,     0,   343,   344,   288,
     288,   345,   346,   347,   348,   349,   290,     0,     0,     0,
       0,     0,     0,     0,   288,     0,     0,    31,   288,   290,
     290,     0,   287,     0,     0,   287,   287,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   499,     0,     0,
       0,     0,     0,   287,   287,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   287,     0,     0,    92,     0,     0,
       0,     0,     0,     0,   289,   287,     0,   287,     0,   287,
       0,     0,     0,     0,     0,     0,     0,   287,   287,     0,
     287,   287,     0,   287,     0,     0,   287,     0,     0,   287,
     287,     0,     1,     0,     0,   287,     0,     0,   288,     0,
       0,   288,     0,   288,     0,     0,     0,     0,     0,     0,
     500,   500,   500,   500,   500,   500,   500,   500,   500,     0,
     500,   500,   500,   500,   500,   500,   500,   500,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   288,   288,
     288,     0,     2,     3,     4,     0,     0,     5,     6,     7,
       0,   288,   288,     0,   288,   288,     0,   288,     0,     0,
       0,     0,     0,     0,     0,     0,   289,   289,     8,     0,
       0,     9,     0,     0,     0,     0,     0,    10,     0,     0,
       0,   289,     0,    11,     0,   289,     0,     0,     0,     0,
       0,     0,     0,   288,     0,     0,   288,   288,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   288,   288,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   288,     0,     0,     0,     0,
       0,   290,     0,     0,     0,     0,   288,     0,   288,     0,
     288,     0,     0,     0,     0,   959,   969,     0,   288,   288,
       0,   288,   288,     0,   288,     0,     0,   288,     0,     0,
     288,   288,     0,     0,     0,   289,   288,     0,   289,     0,
     289,     0,     0,     0,     0,   500,     0,   500,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,   118,
      67,   119,    59,     0,     0,   289,   289,   289,     0,     0,
       0,   120,     0,     0,     0,     0,     0,     0,   289,   289,
       0,   289,   289,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,   290,   290,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1033,     0,     0,     0,   290,     2,
       3,     4,   290,     0,     5,   121,     7,     0,     0,     0,
     289,   122,     0,   289,   289,   500,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     0,     9,     0,
       0,   289,   289,     0,   735,     0,   766,     0,     0,     0,
      11,     0,   289,     0,     0,     0,     0,  1074,  1075,     0,
    1077,  1078,     0,   289,     0,   289,     0,   289,     0,     0,
     123,     0,     0,     0,     0,   289,   289,     0,   289,   289,
       0,   289,     0,     0,   289,     0,     0,   289,   289,     0,
       0,     0,   290,   289,     0,   290,     0,   290,     0,  1105,
       0,     0,  1106,  1107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     969,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1126,   290,   290,   290,     0,     0,     0,   103,   106,
     108,   109,  1033,     0,     0,   290,   290,     0,   290,   290,
       0,   290,     0,     0,  1074,  1075,   185,  1077,  1078,   195,
       0,     0,   205,  1105,     0,     0,  1106,  1107,     0,     0,
       0,     0,  1126,     0,     0,   219,   221,   222,     0,   224,
     225,     0,   226,     0,     0,     0,     0,   290,     0,     0,
     290,   290,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   290,   290,
       0,   171,   175,   178,   180,     0,     0,   186,     0,   290,
     196,     0,     0,   206,     0,     0,     0,     0,     0,     0,
     290,     0,   290,     0,   290,     0,     0,     0,     0,     0,
       0,     0,   290,   290,     0,   290,   290,     0,   290,     0,
       0,   290,     0,     0,   290,   290,   380,   383,   385,   386,
     290,     0,     0,     0,     0,     0,   400,   403,   405,   406,
       0,     0,     0,     0,     0,     0,   420,   423,   425,   426,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   443,   444,     0,   445,     0,     0,   446,     0,
       0,     0,     0,     0,     0,     0,     0,   367,   370,   372,
       0,   373,   375,     0,   376,     0,     0,     0,     0,     0,
       0,     0,   387,   391,   394,   396,     0,     0,     0,     0,
       0,     0,   407,   411,   414,   416,     0,     0,     0,     0,
       0,     0,   427,   431,   434,   436,   236,   111,   112,   113,
     114,   115,   116,   117,     0,     0,   237,    67,   119,   507,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     239,   240,    59,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   562,     2,     3,     4,     0,
       0,     5,     6,   249,     0,     0,     0,   563,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,     0,   261,
     262,   263,     8,     0,     0,     9,     0,     0,     0,    41,
      42,    43,     0,     0,    44,    45,    46,     0,     0,     0,
       0,   122,   598,   600,   601,     0,   603,   604,     0,   605,
       0,     0,     0,     0,     0,    47,     0,   564,    48,     0,
       0,     0,   618,   620,   621,     0,   623,   624,     0,   625,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   638,   640,   641,     0,   643,   644,     0,   645,
      92,     0,     0,   591,   593,     0,   594,     0,     0,   595,
       0,     0,     0,     0,     0,     0,     0,   658,     0,     0,
       0,     0,     0,   606,   609,   611,     0,   612,   614,     0,
     615,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   626,   629,   631,     0,   632,   634,     0,
     635,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   646,   649,   651,     0,   652,   654,     0,
     655,     0,     0,     0,   465,   111,   112,   113,   114,   115,
     116,   117,   837,     0,     0,    67,   119,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,    78,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   104,     0,   250,   251,   252,     0,     0,
       0,    79,     0,     0,     0,   173,   176,     0,     0,   183,
       0,   189,   193,     0,   199,   203,     0,   209,     0,     0,
       0,   797,   798,     0,   799,     0,     0,   800,     0,   217,
       0,     0,     0,     0,     0,   102,   105,   107,     0,     0,
       0,   807,   808,     0,   809,   470,     0,   810,   174,   177,
     179,     0,   184,     0,   190,   194,     0,   200,   204,     0,
     210,   817,   818,     0,   819,     0,     0,   820,     0,     0,
       0,     0,   218,   220,     0,     0,   223,   795,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   801,   803,     0,   804,     0,     0,   805,     0,
       0,   368,     0,     0,     0,     0,     0,     0,     0,     0,
     378,   381,   811,   813,     0,   814,   389,   392,   815,     0,
     398,   401,     0,     0,     0,     0,   409,   412,     0,     0,
     418,   421,   821,   823,     0,   824,   429,   432,   825,     0,
       0,     0,     0,     0,   369,   371,     0,     0,   374,     0,
       0,     0,     0,   379,   382,   384,     0,     0,     0,   390,
     393,   395,     0,   399,   402,   404,     0,     0,     0,   410,
     413,   415,     0,   419,   422,   424,     0,     0,     0,   430,
     433,   435,     0,     0,     0,     0,     0,     0,     0,   442,
       0,   236,   111,   112,   113,   114,   115,   116,   117,     0,
       0,   237,    67,   119,     0,     0,     0,     0,   238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   928,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   930,     0,     0,     0,   239,   240,     0,     0,     0,
       0,   932,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     2,     3,     4,     0,     0,     5,     6,   249,     0,
       0,     0,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,     0,   261,   262,   263,     8,     0,     0,
       9,     0,     0,     0,     0,     0,     0,   929,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   931,     0,     0,
       0,     0,     0,   951,     0,     0,   596,   933,     0,     0,
       0,     0,   264,     0,     0,     0,     0,   607,     0,     0,
       0,     0,     0,     0,     0,     0,   616,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   627,     0,     0,
     592,     0,     0,     0,     0,     0,   636,     0,     0,   597,
     599,     0,     0,   602,     0,     0,     0,   647,     0,     0,
     608,   610,     0,     0,   613,     0,     0,     0,     0,   617,
     619,     0,     0,   622,     0,     0,     0,  1017,  1018,     0,
     628,   630,     0,     0,   633,     0,     0,     0,     0,   637,
     639,     0,     0,   642,     0,     0,     0,     0,     0,     0,
     648,   650,     0,     0,   653,   236,   111,   112,   113,   114,
     115,   116,   117,     0,     0,   237,    67,     0,     0,     0,
       0,     0,   238,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1062,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,     0,     0,     0,     0,
       0,     0,   734,     0,     0,     0,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,     0,   261,   262,
     263,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   264,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,   111,   112,   113,   114,   115,   116,   117,   351,   352,
     237,    67,   353,   354,   355,     0,     0,   238,   796,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   802,
       0,     0,     0,   356,   357,   358,   359,     0,   806,     0,
       0,     0,     0,     0,   239,   240,     0,     0,     0,   812,
       0,   241,   242,   243,   244,   245,   246,   247,   816,   248,
       0,     0,     0,     0,     0,     0,     0,   734,    92,   822,
       0,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,     0,   956,   262,   263,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,   519,     0,     0,     0,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   466,   467,     0,     0,
       0,   957,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,     0,     0,   465,
     111,   112,   113,   114,   115,   116,   117,   250,   251,   252,
      67,     0,     0,     0,     0,     0,   238,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   116,   117,     0,   466,
     467,     0,     0,    59,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,   470,   248,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,   677,   238,     0,     0,     0,
      50,    51,    52,     0,     0,    53,    54,    55,     0,   466,
     467,     0,   122,     0,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,    56,   340,   341,    57,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     470,     0,   465,   111,   112,   113,   114,   115,   116,   117,
     250,   251,   252,     0,     0,     0,     0,     0,     0,   238,
     747,    92,   110,   111,   112,   113,   114,   115,   116,   117,
       0,     0,   466,   467,     0,    59,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     470,   248,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,   250,   251,   252,     0,     0,     0,   238,
       0,     0,     0,    51,    52,     0,   851,    53,    54,    55,
       0,     0,   466,   467,   122,     0,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,    56,   340,
     341,    57,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   470,     0,   465,   111,   112,   113,   114,
     115,   116,   117,   250,   251,   252,     0,     0,     0,     0,
       0,     0,   238,    92,     0,     0,     0,     0,     0,   853,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,   497,   248,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,   250,   251,   252,     0,
       0,   670,   238,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,   497,     0,   465,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,     0,
       0,     0,     0,     0,     0,   238,   878,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,   466,   467,
       0,     0,    59,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   470,   248,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,   897,   250,
     251,   252,     0,     0,     0,   238,     0,     0,     0,    41,
      42,    43,     0,     0,    44,    45,    46,     0,   466,   467,
       0,   122,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,    47,     0,     0,    48,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   470,
       0,   465,   111,   112,   113,   114,   115,   116,   117,   250,
     251,   252,     0,     0,     0,     0,     0,     0,   238,   909,
      92,     0,   110,   111,   112,   113,   114,   115,   116,   117,
       0,   466,   467,     0,     0,    59,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,   470,
     248,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,   250,   251,   252,     0,     0,     0,   238,   911,
       0,     0,     0,     3,     4,     0,     0,     5,     6,     7,
       0,   466,   467,     0,   122,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     8,     0,
       0,     9,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   470,     0,   465,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,   944,    92,     0,   110,   111,   112,   113,   114,
     115,   116,   117,     0,   466,   467,     0,     0,    59,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   470,   248,   465,   111,   112,   113,   114,   115,
     116,   117,     0,     0,     0,   250,   251,   252,     0,     0,
       0,   238,   953,     0,     0,     0,    42,    43,     0,     0,
      44,    45,    46,     0,   466,   467,     0,   122,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,    47,     0,     0,    48,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   470,     0,   465,   111,   112,
     113,   114,   115,   116,   117,   250,   251,   252,     0,     0,
       0,     0,     0,     0,   238,   974,    92,     0,   110,   111,
     112,   113,   114,   115,   116,   117,     0,   466,   467,     0,
       0,    59,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   470,   248,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,   250,   251,
     252,     0,     0,     0,   238,   978,     0,     0,     0,    35,
      36,     0,     0,    37,    38,    39,     0,   466,   467,     0,
     122,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   470,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   250,   251,
     252,   465,   111,   112,   113,   114,   115,   116,   117,    92,
       0,   986,     0,     0,     0,     0,     0,     0,   238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,   470,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,   250,   251,   252,     0,     0,     0,   238,   989,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   470,     0,   465,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,  1004,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   470,   248,   465,   111,   112,   113,   114,   115,
     116,   117,     0,     0,     0,   250,   251,   252,     0,     0,
       0,   238,  1006,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   470,     0,   465,   111,   112,
     113,   114,   115,   116,   117,   250,   251,   252,     0,     0,
       0,     0,     0,     0,   238,  1015,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,   467,     0,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   470,   248,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,   250,   251,
     252,     0,     0,     0,   238,  1028,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,   467,     0,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   470,     0,
     465,   111,   112,   113,   114,   115,   116,   117,   250,   251,
     252,     0,     0,     0,     0,     0,     0,   238,  1031,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     466,   467,     0,     0,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,   470,   248,
     465,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,   250,   251,   252,     0,     0,     0,   238,  1042,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     466,   467,     0,     0,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,   470,     0,   465,   111,   112,   113,   114,   115,   116,
     117,   250,   251,   252,     0,     0,     0,     0,     0,     0,
     238,  1047,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   466,   467,     0,     0,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   470,   248,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,  1050,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   466,   467,     0,     0,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   470,     0,   465,   111,   112,   113,
     114,   115,   116,   117,   250,   251,   252,     0,     0,     0,
       0,     0,     0,   238,  1053,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   466,   467,     0,     0,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   470,   248,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,  1069,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   466,   467,     0,     0,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   470,     0,   465,
     111,   112,   113,   114,   115,   116,   117,   250,   251,   252,
       0,     0,     0,     0,     0,     0,   238,  1085,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   466,
     467,     0,     0,     0,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,   470,   248,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,     0,   238,  1089,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   466,
     467,     0,     0,     0,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     470,     0,   465,   111,   112,   113,   114,   115,   116,   117,
     250,   251,   252,     0,     0,     0,     0,     0,     0,   238,
    1093,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,   467,     0,     0,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     470,   248,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,  1098,   250,   251,   252,     0,     0,     0,   238,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,   467,     0,     0,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   470,     0,   465,   111,   112,   113,   114,
     115,   116,   117,   250,   251,   252,     0,     0,     0,     0,
       0,     0,   238,  1103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,   470,   248,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,  1123,   250,   251,   252,     0,
       0,     0,   238,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,   470,     0,   465,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,     0,
       0,     0,     0,     0,     0,   238,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,   467,
       0,     0,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   470,   248,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   250,
     251,   252,     0,     0,     0,   238,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,   467,
       0,     0,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   470,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   250,
     251,   252,   236,   111,   112,   113,   114,   115,   116,   117,
       0,     0,   754,     0,     0,     0,     0,     0,     0,   238,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   236,   111,   112,   113,   114,
     115,   116,   117,     0,     0,  1065,   239,   240,     0,   497,
       0,     0,   238,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,     0,     0,     0,     0,     0,     0,   734,
       0,     0,     0,   250,   251,   252,     0,     0,   255,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,     0,     0,     0,     0,
       0,     0,   734,     0,     0,     0,   250,   251,   252,     0,
       0,   255,   110,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,   470,     0,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   470,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,     0,     0,    53,    54,    55,
     338,   339,     0,     0,   122,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,     0,     0,    56,   340,
     341,    57,   238,   981,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,     0,     0,     0,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,   239,
     240,     0,     0,    92,   238,  1035,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,     0,     0,   465,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,     0,
       0,   239,   240,     0,     0,   238,  1038,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,   250,   251,
     252,     0,   239,   240,     0,   238,  1080,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   470,   248,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   250,
     251,   252,   239,   240,     0,   238,  1119,     0,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,   470,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,   250,
     251,   252,   239,   240,     0,     0,   238,  1132,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   470,
       0,   465,   111,   112,   113,   114,   115,   116,   117,   250,
     251,   252,     0,   239,   240,     0,     0,     0,   238,  1135,
     241,   242,   243,   244,   245,   246,   247,     0,   248,   470,
       0,     0,   465,   111,   112,   113,   114,   115,   116,   117,
     250,   251,   252,     0,     0,   239,   240,     0,     0,   238,
    1144,     0,   241,   242,   243,   244,   245,   246,   247,   470,
     248,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   250,   251,   252,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     470,   248,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   251,   252,   110,   111,   112,   113,
     114,   115,   116,   117,     0,     0,   159,     0,   119,    59,
       0,     0,   470,     0,     0,     0,     0,     0,   120,     0,
     465,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   238,     0,     0,
       0,     0,     0,   470,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     4,     0,
       0,     5,     6,     7,   239,   240,     0,     0,   122,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,     0,     8,     0,     0,     9,     0,   160,     0,     0,
       0,   250,   251,   252,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   470
};

static const yytype_int16 yycheck[] =
{
      29,    74,   292,   673,   215,   536,   536,   536,   574,   330,
     507,   509,   510,   452,   335,   249,   332,   329,    12,     0,
     239,   240,    10,   230,   882,   329,   334,   122,   235,   337,
      13,    13,    18,    14,   342,    16,   236,    36,    26,    68,
      74,    18,    69,    16,    18,   297,    16,    76,    77,    78,
      79,    68,   360,    82,    16,   363,    85,    13,     0,    88,
     133,    14,   527,    23,   137,   124,   266,    18,    16,    16,
     535,   984,    14,   986,    16,   149,   150,   151,    22,   153,
     545,   333,    14,    18,   336,    16,   160,    68,    44,    62,
     124,   164,   121,    74,   168,   169,   170,   124,   350,   665,
      44,    74,    74,    76,   133,    68,    76,    16,   137,   693,
     694,    74,    16,   142,   366,    23,    36,    11,   147,   558,
     137,    16,   124,    17,    16,   124,    68,  1040,   335,    18,
     124,    20,    74,    22,    66,    67,    16,    47,    48,   447,
     126,   124,   124,   172,   173,   174,    99,   176,   177,   126,
     179,   124,   126,   227,   124,    44,   137,     0,   187,   188,
     189,   190,   124,  1021,   124,  1023,   664,    16,   197,   198,
     199,   200,    76,   136,   137,   126,   124,   124,   207,   208,
     209,   210,    62,   164,    76,  1098,   149,   150,   151,   152,
     153,   126,   164,   124,    74,   137,    76,   160,   695,   503,
     504,   164,    14,   166,   124,   168,   169,   170,  1121,    13,
    1123,    22,    13,    62,    44,   124,   124,   783,   716,   292,
     124,   719,   164,   527,  1137,   320,   321,    76,   532,   124,
      14,   535,   124,    44,   133,    68,    40,   126,   124,  1097,
     544,   545,   558,    44,   124,    62,   227,   466,   467,   468,
     469,   239,   240,   505,    76,    67,   329,   569,    16,    17,
     581,  1119,    62,   292,   227,   465,   229,   851,   231,   853,
     940,   471,   124,  1131,  1132,   124,  1134,  1135,   568,    14,
      11,    23,  1140,    18,    62,  1143,  1144,    16,   121,   211,
      21,  1149,     3,     4,     5,     6,     7,     8,     9,    10,
     329,   330,   124,    12,   137,   334,   335,   124,   337,   142,
     775,   776,   777,   342,    62,    73,     3,     4,     5,     6,
       7,     8,     9,    10,   124,   715,    74,    11,   718,    16,
     252,   360,    74,    62,   363,   833,    45,    21,    14,   368,
     369,   329,   371,    60,    61,   374,   124,    76,   787,   556,
     557,    68,   660,   661,   662,   663,    11,    74,   124,   388,
     389,   390,    17,   392,   393,    22,   395,   124,   897,   332,
     867,   868,   901,   870,   448,   449,   450,   451,    16,   408,
     409,   410,   124,   412,   413,    61,   415,    44,    75,    18,
      66,    67,    22,   292,   716,   124,   835,   719,    18,   428,
     429,   430,   124,   432,   433,   124,   435,    11,   124,    13,
     882,    11,    18,   124,    44,    44,   133,    21,   447,   136,
     137,    21,   124,    61,    44,    49,    50,    51,    66,    67,
     329,   460,   149,   150,   151,   152,   153,   124,    44,   937,
      61,    47,    48,   160,    20,   656,    22,   164,    11,   166,
      13,   168,   169,   170,    11,   984,    13,   986,    21,     3,
       4,     5,     6,     7,     8,     9,    10,   906,    44,    47,
      48,   775,   776,   777,    18,    11,    20,    13,   466,   467,
     468,   469,   701,   702,   703,   448,   449,   450,   451,   452,
     780,  1022,  1022,  1022,   211,   568,   569,   526,   215,   133,
     734,   334,    13,    14,   337,    20,    11,    22,   124,   342,
     227,  1040,   229,  1011,   231,   124,    21,     0,     3,     4,
       5,     6,     7,     8,     9,    10,   555,   360,     0,    44,
     363,    14,   249,    16,   124,   252,    11,    11,    34,   568,
     569,    11,    14,    11,    16,    41,    21,    21,    11,  1021,
     238,  1023,   581,    21,    50,     3,     4,     5,     6,     7,
       8,     9,    10,   592,    11,   253,   254,    11,    26,  1098,
     258,   259,   124,    21,    21,   292,    11,    21,   607,   608,
     124,   610,   886,   887,   613,    68,    21,    11,    47,    48,
      75,    74,  1121,    11,  1123,   558,    68,    21,   627,   628,
     673,   630,    74,    21,   633,    33,    34,    11,  1137,    20,
     573,   328,   329,    11,   447,   332,   827,    21,   647,   648,
      11,   650,    70,    21,   653,  1097,    11,   526,    11,   124,
      21,   660,   661,   662,   663,    11,    21,   536,    21,   124,
      11,    14,    11,    16,   673,    21,    14,  1119,    16,    13,
      21,    11,    21,    18,   137,    20,   555,    22,   292,  1131,
    1132,    21,  1134,  1135,    11,   137,    52,    53,  1140,   568,
     569,  1143,  1144,   124,    21,    40,   124,  1149,    11,    44,
      13,   164,    47,    48,    61,    62,   715,    11,    61,   718,
     133,    20,   164,    66,    67,   329,    99,    21,   686,   687,
     688,   689,   690,   691,   692,   693,   694,   780,   696,   697,
     698,   699,   700,   701,   702,   703,    68,    11,    24,    63,
      64,    65,    74,    29,    68,    69,    70,    21,    35,    36,
      37,   448,   449,   450,   451,   452,     3,     4,     5,     6,
       7,     8,     9,    10,   227,    89,    11,    11,    92,   124,
      11,   780,    13,    27,    21,   227,    21,    21,    20,   124,
     104,   126,    68,    63,    64,    65,   882,   840,    68,    69,
      70,   126,   460,   802,    80,    20,    82,    83,    11,    85,
      86,   133,    88,   812,   136,   137,    11,    22,    21,    89,
     507,    20,    92,   822,    20,    11,    21,   149,   150,   151,
     152,   153,    20,    70,   104,    21,   691,   692,   160,   526,
      18,    11,   164,    13,   166,    13,   168,   169,   170,   536,
     696,   697,   698,   124,   787,   788,    13,   660,   661,   662,
     663,   137,   699,   700,   522,   523,   524,   525,   555,    85,
      13,   558,    20,   149,    43,    11,   534,    43,    18,   292,
      19,   568,   569,   882,   883,   543,   573,   124,   546,    19,
      46,    38,    21,   851,    39,   853,    27,    28,    29,    30,
      31,    32,   835,    20,    18,   227,    43,   229,    20,   231,
     124,   780,    13,    63,    64,    65,   329,    13,    68,    69,
      70,    13,   526,    13,    13,    18,    11,   249,    11,    20,
     252,    11,   536,    43,    20,  1021,    44,  1023,    19,    89,
      19,   940,    92,     3,     4,     5,     6,     7,     8,     9,
      10,   555,   124,     3,     4,     5,     6,     7,     8,     9,
      10,    63,    64,    65,   568,   569,    68,    69,    70,   656,
     292,    21,    20,   906,     3,     4,     5,     6,     7,     8,
       9,    10,   981,   941,     3,     4,     5,     6,     7,     8,
       9,    10,   133,     3,     4,     5,     6,     7,     8,     9,
      10,   124,    21,    20,   124,    21,    21,   329,   695,    21,
     332,  1097,    19,   882,   883,   673,    20,    19,   124,    79,
      70,    20,  1021,    13,  1023,    11,    40,   685,   897,   124,
     124,    20,   901,  1119,    19,  1034,  1035,    20,  1037,  1038,
      11,    70,    20,    74,    11,  1131,  1132,   734,  1134,  1135,
     124,    70,    15,    40,  1140,    20,   714,  1143,  1144,    19,
      13,    13,    20,  1149,   124,    75,    20,   725,    27,    28,
      29,    30,    31,    32,   124,    20,    13,  1076,    13,    20,
    1079,  1080,    63,    64,    65,   772,    20,    68,    69,    70,
     124,    20,    20,   780,    85,   124,   754,    85,  1097,   124,
     787,   788,  1021,    20,  1023,   124,   124,    21,    89,  1108,
      21,    92,   981,   526,   124,   984,    13,   986,    13,    13,
    1119,    20,    20,   536,    20,    13,   448,   449,   450,   451,
     452,    13,  1131,  1132,    20,  1134,  1135,    21,    21,    13,
     827,  1140,   555,    13,  1143,  1144,    13,    13,   835,    13,
    1149,   292,  1021,  1022,  1023,   568,   569,    13,    21,   133,
      40,    21,    13,    13,    13,  1034,  1035,    13,  1037,  1038,
      13,  1040,    13,    13,    13,    13,   780,    13,  1097,    21,
     867,   868,    13,   870,    21,    63,    64,    65,   329,    21,
      68,    69,    70,    21,    21,   882,   883,   252,   164,   137,
    1119,   458,   213,   329,   526,   512,   510,  1076,   941,   686,
    1079,  1080,  1131,  1132,   536,  1134,  1135,   687,   689,   906,
     688,  1140,   772,   690,  1143,  1144,   104,   788,  1097,  1098,
    1149,  1022,   136,   555,   892,   227,   558,   149,   870,  1108,
      -1,   899,   900,    -1,    -1,    -1,   568,   569,    -1,    -1,
    1119,   573,  1121,    -1,  1123,    27,    28,    29,    30,    31,
      32,    -1,  1131,  1132,    -1,  1134,  1135,    -1,  1137,    -1,
      -1,  1140,    -1,    -1,  1143,  1144,    -1,    -1,   882,   883,
    1149,    -1,   940,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,   897,   981,    -1,    16,   901,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,   292,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
     133,    -1,    -1,    -1,  1021,  1022,  1023,    21,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,  1034,  1035,    -1,
    1037,  1038,    -1,    -1,    -1,   329,    21,    -1,    -1,    63,
      64,    65,  1020,    -1,    68,    69,    70,   780,    -1,    -1,
      -1,    75,    18,    -1,    20,    -1,    22,   981,    -1,    -1,
     984,    -1,   986,    -1,    -1,   526,    70,    -1,    -1,  1076,
      -1,    -1,  1079,  1080,    40,   536,    -1,   720,    44,    -1,
     104,    47,    48,    -1,   124,    70,    -1,  1065,    -1,    -1,
    1097,    -1,   734,    -1,   555,   239,   240,  1021,  1022,  1023,
     124,  1108,    -1,    -1,    -1,    -1,    -1,   568,   569,    -1,
    1034,  1035,  1119,  1037,  1038,    -1,  1040,    -1,    -1,    -1,
     124,    -1,  1100,  1101,  1131,  1132,    -1,  1134,  1135,    -1,
     773,   774,    -1,  1140,    -1,    -1,  1143,  1144,   780,   124,
      -1,    -1,  1149,    -1,    -1,   787,   788,    -1,    -1,   882,
     883,    -1,  1076,    -1,    -1,  1079,  1080,    -1,   124,    -1,
     126,    -1,    -1,    -1,   897,    -1,    -1,    -1,   901,   292,
      -1,    -1,    -1,  1097,  1098,    -1,    -1,   133,    13,    -1,
      -1,    -1,    -1,    -1,  1108,     3,     4,     5,     6,     7,
       8,     9,    10,   835,    -1,  1119,    -1,  1121,    -1,  1123,
      -1,    -1,    20,    -1,    -1,    -1,   329,  1131,  1132,    -1,
    1134,  1135,    -1,  1137,    -1,    -1,  1140,    -1,    -1,  1143,
    1144,    -1,   865,    -1,    -1,  1149,    -1,    -1,    63,    64,
      65,    -1,   526,    68,    69,    70,    -1,   880,    -1,    -1,
     882,   883,   536,    -1,    -1,   888,    -1,    -1,   981,    -1,
      -1,   984,   895,   986,    89,    -1,    -1,    92,    -1,    -1,
     903,   555,    -1,    98,   906,    -1,    -1,    -1,    -1,   104,
      18,    -1,    -1,    -1,   568,   569,    -1,   920,   921,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,  1021,  1022,
    1023,    -1,   127,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,  1034,  1035,   946,  1037,  1038,   124,  1040,    -1,    -1,
      -1,    -1,    18,    -1,    20,    -1,    22,    -1,    -1,   780,
      -1,    -1,   466,   467,   468,   469,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   976,    40,    -1,   292,   980,    44,   981,
      -1,    47,    48,  1076,   133,    -1,  1079,  1080,   991,    -1,
      -1,    -1,    -1,    -1,    -1,   998,    -1,  1000,    -1,  1002,
      -1,    -1,    -1,    -1,  1097,  1098,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   329,    -1,  1108,    -1,    -1,    -1,  1021,
    1022,  1023,  1025,    -1,    -1,    -1,  1119,    -1,  1121,    -1,
    1123,    -1,  1034,  1035,    -1,  1037,  1038,    -1,  1131,  1132,
      -1,  1134,  1135,   526,  1137,    -1,  1049,  1140,    -1,  1052,
    1143,  1144,  1055,   536,    -1,    -1,  1149,    -1,   124,    -1,
     126,   882,   883,   239,   240,    -1,    -1,    -1,  1071,    -1,
      -1,    -1,   555,    -1,  1076,    -1,   897,  1079,  1080,    -1,
     901,    -1,    -1,    -1,    -1,   568,   569,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1097,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    -1,  1108,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,  1119,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,   780,    -1,    -1,  1131,
    1132,    -1,  1134,  1135,    -1,    -1,    63,    -1,  1140,    -1,
      -1,  1143,  1144,   292,    -1,    -1,    -1,  1149,    -1,    76,
      -1,    -1,    -1,    80,    -1,    82,    83,    -1,    85,    86,
     981,    88,    -1,   984,    -1,   986,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,    -1,
     329,    75,   686,   687,   688,   689,   690,   691,   692,   693,
     694,    -1,   696,   697,   698,   699,   700,   701,   702,   703,
    1021,  1022,  1023,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     526,    -1,    -1,  1034,  1035,    -1,  1037,  1038,    -1,  1040,
     536,    -1,    -1,    18,    -1,    20,    -1,    22,   882,   883,
     124,    -1,    27,    28,    29,    30,    31,    32,    -1,   555,
      -1,    -1,    -1,   897,    -1,    -1,    -1,   901,    -1,    44,
      -1,    -1,   568,   569,   181,  1076,    -1,    -1,  1079,  1080,
     187,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,
     197,    -1,    -1,    -1,   201,    -1,  1097,  1098,    -1,    -1,
     207,    -1,    -1,    -1,    -1,    -1,    -1,  1108,    -1,   526,
     466,   467,   468,   469,    -1,    -1,    -1,   780,  1119,    -1,
    1121,    -1,  1123,    13,    -1,    -1,    -1,    -1,    -1,    -1,
    1131,  1132,    -1,  1134,  1135,    -1,  1137,    -1,   555,  1140,
      -1,    -1,  1143,  1144,    -1,    -1,    -1,   981,  1149,   124,
     984,   126,   986,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,   851,    -1,   853,
      -1,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,  1021,  1022,  1023,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   526,    -1,    89,
    1034,  1035,    92,  1037,  1038,    -1,  1040,   536,    98,    -1,
      -1,    -1,    -1,    -1,   104,    -1,    -1,    64,    65,   882,
     883,    68,    69,    70,    71,    72,   555,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   897,    -1,    -1,   127,   901,   568,
     569,    -1,  1076,    -1,    -1,  1079,  1080,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   941,    -1,    -1,
      -1,    -1,    -1,  1097,  1098,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1108,    -1,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,   780,  1119,    -1,  1121,    -1,  1123,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1131,  1132,    -1,
    1134,  1135,    -1,  1137,    -1,    -1,  1140,    -1,    -1,  1143,
    1144,    -1,    13,    -1,    -1,  1149,    -1,    -1,   981,    -1,
      -1,   984,    -1,   986,    -1,    -1,    -1,    -1,    -1,    -1,
     686,   687,   688,   689,   690,   691,   692,   693,   694,    -1,
     696,   697,   698,   699,   700,   701,   702,   703,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1021,  1022,
    1023,    -1,    63,    64,    65,    -1,    -1,    68,    69,    70,
      -1,  1034,  1035,    -1,  1037,  1038,    -1,  1040,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   882,   883,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,   897,    -1,   104,    -1,   901,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1076,    -1,    -1,  1079,  1080,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1097,  1098,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1108,    -1,    -1,    -1,    -1,
      -1,   780,    -1,    -1,    -1,    -1,  1119,    -1,  1121,    -1,
    1123,    -1,    -1,    -1,    -1,   882,   883,    -1,  1131,  1132,
      -1,  1134,  1135,    -1,  1137,    -1,    -1,  1140,    -1,    -1,
    1143,  1144,    -1,    -1,    -1,   981,  1149,    -1,   984,    -1,
     986,    -1,    -1,    -1,    -1,   851,    -1,   853,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      14,    15,    16,    -1,    -1,  1021,  1022,  1023,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,  1034,  1035,
      -1,  1037,  1038,    -1,  1040,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   882,   883,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   981,    -1,    -1,    -1,   897,    63,
      64,    65,   901,    -1,    68,    69,    70,    -1,    -1,    -1,
    1076,    75,    -1,  1079,  1080,   941,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    -1,
      -1,  1097,  1098,    -1,  1021,    -1,  1023,    -1,    -1,    -1,
     104,    -1,  1108,    -1,    -1,    -1,    -1,  1034,  1035,    -1,
    1037,  1038,    -1,  1119,    -1,  1121,    -1,  1123,    -1,    -1,
     124,    -1,    -1,    -1,    -1,  1131,  1132,    -1,  1134,  1135,
      -1,  1137,    -1,    -1,  1140,    -1,    -1,  1143,  1144,    -1,
      -1,    -1,   981,  1149,    -1,   984,    -1,   986,    -1,  1076,
      -1,    -1,  1079,  1080,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1097,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1108,  1021,  1022,  1023,    -1,    -1,    -1,    63,    64,
      65,    66,  1119,    -1,    -1,  1034,  1035,    -1,  1037,  1038,
      -1,  1040,    -1,    -1,  1131,  1132,    81,  1134,  1135,    84,
      -1,    -1,    87,  1140,    -1,    -1,  1143,  1144,    -1,    -1,
      -1,    -1,  1149,    -1,    -1,   100,   101,   102,    -1,   104,
     105,    -1,   107,    -1,    -1,    -1,    -1,  1076,    -1,    -1,
    1079,  1080,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1097,  1098,
      -1,    76,    77,    78,    79,    -1,    -1,    82,    -1,  1108,
      85,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
    1119,    -1,  1121,    -1,  1123,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1131,  1132,    -1,  1134,  1135,    -1,  1137,    -1,
      -1,  1140,    -1,    -1,  1143,  1144,   181,   182,   183,   184,
    1149,    -1,    -1,    -1,    -1,    -1,   191,   192,   193,   194,
      -1,    -1,    -1,    -1,    -1,    -1,   201,   202,   203,   204,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   217,   218,    -1,   220,    -1,    -1,   223,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,
      -1,   176,   177,    -1,   179,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   187,   188,   189,   190,    -1,    -1,    -1,    -1,
      -1,    -1,   197,   198,   199,   200,    -1,    -1,    -1,    -1,
      -1,    -1,   207,   208,   209,   210,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      47,    48,    16,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    65,    -1,
      -1,    68,    69,    70,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    -1,    86,
      87,    88,    89,    -1,    -1,    92,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,    -1,
      -1,    75,   377,   378,   379,    -1,   381,   382,    -1,   384,
      -1,    -1,    -1,    -1,    -1,    89,    -1,   124,    92,    -1,
      -1,    -1,   397,   398,   399,    -1,   401,   402,    -1,   404,
     104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   417,   418,   419,    -1,   421,   422,    -1,   424,
     124,    -1,    -1,   368,   369,    -1,   371,    -1,    -1,   374,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   442,    -1,    -1,
      -1,    -1,    -1,   388,   389,   390,    -1,   392,   393,    -1,
     395,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   408,   409,   410,    -1,   412,   413,    -1,
     415,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   428,   429,   430,    -1,   432,   433,    -1,
     435,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    14,    15,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    29,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    -1,    74,    75,    76,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    76,    77,    -1,    -1,    80,
      -1,    82,    83,    -1,    85,    86,    -1,    88,    -1,    -1,
      -1,   596,   597,    -1,   599,    -1,    -1,   602,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,    -1,
      -1,   616,   617,    -1,   619,   124,    -1,   622,    76,    77,
      78,    -1,    80,    -1,    82,    83,    -1,    85,    86,    -1,
      88,   636,   637,    -1,   639,    -1,    -1,   642,    -1,    -1,
      -1,    -1,   100,   101,    -1,    -1,   104,   592,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   607,   608,    -1,   610,    -1,    -1,   613,    -1,
      -1,   172,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     181,   182,   627,   628,    -1,   630,   187,   188,   633,    -1,
     191,   192,    -1,    -1,    -1,    -1,   197,   198,    -1,    -1,
     201,   202,   647,   648,    -1,   650,   207,   208,   653,    -1,
      -1,    -1,    -1,    -1,   172,   173,    -1,    -1,   176,    -1,
      -1,    -1,    -1,   181,   182,   183,    -1,    -1,    -1,   187,
     188,   189,    -1,   191,   192,   193,    -1,    -1,    -1,   197,
     198,   199,    -1,   201,   202,   203,    -1,    -1,    -1,   207,
     208,   209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   217,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   796,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   806,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,   816,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    63,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    86,    87,    88,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    -1,   802,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   812,    -1,    -1,
      -1,    -1,    -1,   878,    -1,    -1,   377,   822,    -1,    -1,
      -1,    -1,   124,    -1,    -1,    -1,    -1,   388,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   408,    -1,    -1,
     368,    -1,    -1,    -1,    -1,    -1,   417,    -1,    -1,   377,
     378,    -1,    -1,   381,    -1,    -1,    -1,   428,    -1,    -1,
     388,   389,    -1,    -1,   392,    -1,    -1,    -1,    -1,   397,
     398,    -1,    -1,   401,    -1,    -1,    -1,   952,   953,    -1,
     408,   409,    -1,    -1,   412,    -1,    -1,    -1,    -1,   417,
     418,    -1,    -1,   421,    -1,    -1,    -1,    -1,    -1,    -1,
     428,   429,    -1,    -1,   432,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1019,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    64,    65,
      13,    14,    68,    69,    70,    -1,    -1,    20,   596,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   607,
      -1,    -1,    -1,    89,    90,    91,    92,    -1,   616,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,   627,
      -1,    54,    55,    56,    57,    58,    59,    60,   636,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,   124,   647,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    -1,    86,    87,    88,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,   124,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    74,    75,    76,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    33,
      34,    -1,    -1,    16,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,   124,    62,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    19,    20,    -1,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    70,    -1,    33,
      34,    -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    -1,    89,    90,    91,    92,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
     124,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      21,   124,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    33,    34,    -1,    16,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     124,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    64,    65,    -1,    27,    68,    69,    70,
      -1,    -1,    33,    34,    75,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    89,    90,
      91,    92,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,   124,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    20,   124,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,   124,    62,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,   124,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    33,    34,
      -1,    -1,    16,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   124,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    74,
      75,    76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    33,    34,
      -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    89,    -1,    -1,    92,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
     124,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    33,    34,    -1,    -1,    16,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   124,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    64,    65,    -1,    -1,    68,    69,    70,
      -1,    33,    34,    -1,    75,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    89,    -1,
      -1,    92,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,   124,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    21,   124,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    33,    34,    -1,    -1,    16,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,   124,    62,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    64,    65,    -1,    -1,
      68,    69,    70,    -1,    33,    34,    -1,    75,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      -1,    89,    -1,    -1,    92,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,   124,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    74,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,   124,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    33,    34,    -1,
      -1,    16,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,   124,    62,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,    64,
      65,    -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,
      75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,     3,     4,     5,     6,     7,     8,     9,    10,   124,
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
       8,     9,    10,    -1,    -1,    13,    74,    75,    76,    -1,
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
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      75,    76,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    47,    48,    -1,   124,
      -1,    -1,    20,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    79,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    79,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,   124,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,    70,
      71,    72,    -1,    -1,    75,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    92,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,   124,    20,    21,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    74,    75,    76,    -1,
      -1,    47,    48,    -1,    -1,    20,    21,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    74,    75,
      76,    -1,    47,    48,    -1,    20,    21,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,   124,    62,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    74,
      75,    76,    47,    48,    -1,    20,    21,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,   124,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    74,
      75,    76,    47,    48,    -1,    -1,    20,    21,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    74,
      75,    76,    -1,    47,    48,    -1,    -1,    -1,    20,    21,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,   124,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      74,    75,    76,    -1,    -1,    47,    48,    -1,    -1,    20,
      21,    -1,    54,    55,    56,    57,    58,    59,    60,   124,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     124,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    -1,    15,    16,
      -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    25,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    70,    47,    48,    -1,    -1,    75,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,    -1,    89,    -1,    -1,    92,    -1,    94,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124
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
     175,   175,    20,    20,    20,    18,    40,    44,   126,   185,
     126,   185,    22,    20,    18,    44,    20,    27,    28,    29,
      30,    31,    32,   179,    22,    44,    18,    47,    48,   151,
     233,    13,   124,   171,    13,    85,   223,   223,    20,   137,
     221,   222,    62,    74,   124,   141,   151,   181,   232,   271,
     277,   270,    21,    70,   130,   224,   225,   226,   227,   171,
     228,   220,   270,   171,   228,   228,   171,   228,    13,   228,
     171,   152,   164,   152,   152,   152,   162,   164,   166,   164,
     166,   166,   164,   166,   166,   166,   152,   162,   164,   152,
     164,   152,   152,   164,   152,   152,   162,   164,   166,   164,
     166,   166,   164,   166,   166,   166,   152,   162,   164,   152,
     164,   152,   152,   164,   152,   152,   162,   164,   166,   164,
     166,   166,   164,   166,   166,   166,   152,   162,   164,   152,
     164,   152,   152,   164,   152,   152,    43,   160,   166,   228,
     219,   219,   219,   219,    21,   130,   225,    74,   124,    11,
      19,    18,   172,   150,   174,   175,   193,    19,    18,   126,
     210,   210,   210,   210,    21,    12,    45,    46,    38,    39,
      43,    52,    53,    16,    17,    73,    49,    50,    51,    33,
      34,    35,    36,    37,   124,   277,   124,   277,   171,    12,
     135,   278,   279,   280,    18,   139,   195,   196,   139,   195,
      20,   124,   188,    13,    13,    40,    13,    13,    13,    13,
     175,   175,   175,   175,    70,   238,    62,    74,    76,   124,
     187,   277,   126,   126,    76,   124,   277,    21,   175,   189,
     175,   124,   187,   277,    13,   236,   242,   264,   266,   175,
     124,   277,   124,   187,   277,   175,   238,   220,   220,    21,
     224,   225,    11,    20,    20,    44,    44,    44,   151,   151,
     232,    62,    74,   130,    23,   124,   173,    11,    11,    21,
      13,   270,    13,    13,    13,   152,   164,   166,   166,   166,
     166,   152,   164,   152,   152,   152,   164,   166,   166,   166,
     166,   152,   164,   152,   152,   152,   164,   166,   166,   166,
     166,   152,   164,   152,   152,   152,   282,    43,   228,   228,
     228,   228,   139,    21,    44,    20,    19,    11,   151,   174,
     194,   197,    19,   175,   201,   202,   203,   204,   205,   206,
     206,    27,   207,    27,   207,   135,   208,   208,   208,   209,
     209,   210,   210,   210,   124,    20,   124,    61,    62,   281,
      11,    17,   175,   193,   139,   196,   193,   139,    21,   189,
      20,   175,    21,    21,    21,    19,    22,    44,    20,   124,
      76,   124,    11,    21,    19,    20,   124,    13,   175,    40,
      13,    11,   124,    20,   124,    19,    11,    21,   222,    21,
     189,    21,   189,    62,   277,    62,   277,    62,   277,   151,
      20,    20,    23,   173,   124,    21,   225,   226,   166,   152,
     166,   152,   166,   152,   282,   139,    74,    21,   225,   151,
      11,    40,   207,   207,    21,   189,    20,   135,   135,   279,
      19,   166,    21,    21,   189,    13,    86,   124,   149,   238,
     239,   252,   253,   254,   255,   256,   257,   261,   263,   238,
     124,   277,   124,   277,    21,   189,    20,   175,    21,   189,
      20,    21,   265,   266,    13,   175,    13,   175,   242,    21,
     189,    20,    21,   225,    13,    21,    13,    21,    20,    62,
      20,    62,    20,    62,    21,   189,    21,   189,   124,    21,
     139,    21,   174,   199,    21,    21,   189,   166,   166,    21,
      20,    40,    20,    85,   124,    20,   124,    21,    21,   189,
      21,    21,   189,   238,    21,    21,   265,    21,    21,   265,
      13,    21,    21,   189,    21,    13,    13,    21,   189,    20,
      21,   189,    20,    21,   189,    20,    13,    21,    13,    21,
     139,    21,   166,   175,   254,    13,   236,   264,   254,    21,
     189,    20,    21,    21,   238,   238,    21,   238,   238,    21,
      21,   265,    21,    13,    21,    21,   189,    13,    21,    21,
     189,    13,    21,    21,   189,    13,    13,    21,    13,   175,
      40,    13,    21,    21,   189,   238,   238,   238,    21,    13,
      13,    21,    13,    13,    21,    13,    13,    21,   254,    21,
     265,    13,   175,    13,   175,    21,   238,    13,    13,    13,
     254,    21,    21,   265,    21,    21,   265,    13,   254,   254,
      21,   254,   254,    21,    21,   265,   254,   254,   254,    21,
     254
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
       1,     1,     1,     1,     1,     1,     4,     1,     1,     1,
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
#line 242 "parser_1st.y"
                              {return 0;}
#line 3469 "parser_1st.tab.c"
    break;

  case 3: /* COMPILATIONUNIT: ORDINARYCOMPILATIONUNIT EOFF  */
#line 243 "parser_1st.y"
                                                     {
                    
                    return 0;
                }
#line 3478 "parser_1st.tab.c"
    break;

  case 4: /* TYPE: PRIMITIVETYPE  */
#line 248 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3484 "parser_1st.tab.c"
    break;

  case 5: /* TYPE: REFERENCETYPE  */
#line 249 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3490 "parser_1st.tab.c"
    break;

  case 6: /* PRIMITIVETYPE: NUMERICTYPE  */
#line 251 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3496 "parser_1st.tab.c"
    break;

  case 7: /* PRIMITIVETYPE: BOOLEAN  */
#line 252 "parser_1st.y"
                             {(yyval.val) = stringtochar("bool");}
#line 3502 "parser_1st.tab.c"
    break;

  case 8: /* NUMERICTYPE: INTEGRALTYPE  */
#line 254 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3508 "parser_1st.tab.c"
    break;

  case 9: /* NUMERICTYPE: FLOATINGTYPE  */
#line 255 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3514 "parser_1st.tab.c"
    break;

  case 10: /* INTEGRALTYPE: BYTE  */
#line 257 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3520 "parser_1st.tab.c"
    break;

  case 11: /* INTEGRALTYPE: SHORT  */
#line 258 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3526 "parser_1st.tab.c"
    break;

  case 12: /* INTEGRALTYPE: INT  */
#line 259 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3532 "parser_1st.tab.c"
    break;

  case 13: /* INTEGRALTYPE: LONG  */
#line 260 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3538 "parser_1st.tab.c"
    break;

  case 14: /* INTEGRALTYPE: CHAR  */
#line 261 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3544 "parser_1st.tab.c"
    break;

  case 15: /* FLOATINGTYPE: FLOAT  */
#line 263 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3550 "parser_1st.tab.c"
    break;

  case 16: /* FLOATINGTYPE: DOUBLE  */
#line 264 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3556 "parser_1st.tab.c"
    break;

  case 17: /* REFERENCETYPE: CLASSORINTERFACETYPE  */
#line 266 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3562 "parser_1st.tab.c"
    break;

  case 18: /* CLASSORINTERFACETYPE: CLASSTYPE  */
#line 268 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3568 "parser_1st.tab.c"
    break;

  case 19: /* CLASSTYPE: CLASSTYPE1  */
#line 270 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3574 "parser_1st.tab.c"
    break;

  case 20: /* CLASSTYPE1: IDENTIFIER  */
#line 272 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val); }
#line 3580 "parser_1st.tab.c"
    break;

  case 21: /* DIMS: OPENSQUARE CLOSESQUARE  */
#line 275 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3586 "parser_1st.tab.c"
    break;

  case 22: /* DIMS: DIMS OPENSQUARE CLOSESQUARE  */
#line 276 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3592 "parser_1st.tab.c"
    break;

  case 23: /* METHODNAME: IDENTIFIER  */
#line 278 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3603 "parser_1st.tab.c"
    break;

  case 24: /* EXPRESSIONNAME: IDENTIFIER DOT IDENTIFIER  */
#line 285 "parser_1st.y"
                                               {    
    /* makise */    /* check whether second identifier an object or a function. */
                                                    (yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    string  name = chartostring((yyvsp[-2].val)), name2 = chartostring((yyvsp[0].val));
                                                    // ds[curr]["type"] = get_symbol_table(name,name2,"type");
                                                    // if(get_symbol_table_function(name,name2,"type"))
                                                    objdetails detail = getobjdetails(name,name2);
                                                    if(detail.isfield){
                                                        ds[curr]["var"] = chartostring((yyvsp[-2].val))+"."+chartostring((yyvsp[0].val));
                                                        ds[curr]["type"] = detail.field.typ.name;
                                                    }else{
                                                        object_error(name,name2,yylineno);
                                                    }
                                                    // ds[curr]["lineno"] = get_symbol_table(name,"lineno");
                                                    /* TODO */
}
#line 3625 "parser_1st.tab.c"
    break;

  case 25: /* EXPRESSIONNAME: EXPRESSIONNAME DOT IDENTIFIER  */
#line 302 "parser_1st.y"
                                                  {/*TODO*/}
#line 3631 "parser_1st.tab.c"
    break;

  case 28: /* TOPLEVELCLASSORINTERFACEDECLARATION: CLASSDECLARATION  */
#line 308 "parser_1st.y"
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
        int iik=0;
        for(auto x : polymethods){
            for (auto y : x.second){
                preservedsymboltable[{x.first, -iik}].lineno = y.lineno;
                preservedsymboltable[{x.first, -iik}].typ = y.rettype;
                preservedsymboltable[{x.first, -iik}].token = "identifier - method of" + chartostring((yyvsp[0].val)) ;
                iik++;
            }
              
        
        }

     resetclass();}
#line 3692 "parser_1st.tab.c"
    break;

  case 36: /* CLASSDECLARATION: NORMALCLASSDECLARATION  */
#line 373 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);

                    //     for(auto obj:object_list){
                    //     string pr = obj.third;
                    //     vector<string> methods = getallmethods(obj.first,obj.second);
                    //     // vector<string> methods = {"f"};
                    //     for(auto method : methods){
                    //         // code.push_back(method);
                    //         // cout<<"methods "<<method<<"\n";
                           
                    //         add_func(code, pr, method_det[obj.second][method].start, method_det[obj.second][method].end);
                    //     }
                        
                    // }
                    // object_list.clear();static_name.clear();
                    }
#line 3713 "parser_1st.tab.c"
    break;

  case 37: /* NORMALCLASSDECLARATION: CLASS CLASSNAME CLASSBODY  */
#line 391 "parser_1st.y"
                                                       {(yyval.val) = (yyvsp[-1].val);
                                if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));
                                code.push_back("end class");/*TODO begin class */}
#line 3721 "parser_1st.tab.c"
    break;

  case 38: /* NORMALCLASSDECLARATION: SUPER1 CLASS CLASSNAME CLASSBODY  */
#line 394 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val); if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));code.push_back("end class");}
#line 3727 "parser_1st.tab.c"
    break;

  case 39: /* NORMALCLASSDECLARATION: SUPER2 CLASS CLASSNAME CLASSBODY  */
#line 395 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));code.push_back("end class");}
#line 3733 "parser_1st.tab.c"
    break;

  case 40: /* NORMALCLASSDECLARATION: SUPER3 CLASS CLASSNAME CLASSBODY  */
#line 396 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));code.push_back("end class");}
#line 3739 "parser_1st.tab.c"
    break;

  case 101: /* CLASSNAME: IDENTIFIER  */
#line 461 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val); curr_class = chartostring((yyval.val)); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); code.push_back("begin class "+curr_class); }
#line 3745 "parser_1st.tab.c"
    break;

  case 166: /* FOR: FOR1  */
#line 528 "parser_1st.y"
           {newscope();}
#line 3751 "parser_1st.tab.c"
    break;

  case 167: /* OPENCURLY: OPENCURLY1  */
#line 529 "parser_1st.y"
                          {newscope(); }
#line 3757 "parser_1st.tab.c"
    break;

  case 168: /* CLOSECURLY: CLOSECURLY1  */
#line 530 "parser_1st.y"
                          {popscope();}
#line 3763 "parser_1st.tab.c"
    break;

  case 208: /* FIELDDECLARATION: FIELDMODIFIERS TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 591 "parser_1st.y"
                                                                             {
                                if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);

                    {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                                     int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                                     int start = code.size();
                                                                                     if(ds[curr2].find("start")!=ds[curr2].end()){
                                                                                        start = stringtonum(ds[curr2]["start"]);
                                                                                     }
                                                                    int flag = 0;
                                                                    for(auto i:generalmap[(yyvsp[-3].val)].modifiers){
                                                                        if(i=="static"){
                                                                            add_static(code,start,ds2[curr2]["var_name"]);
                                                                            flag = 1;
                                                                            break;
                                                                        }
                                                                    }
                                                                    if(flag){
                                                                        for(auto name:ds2[curr2]["var_name"])
                                                                        static_name.insert(name);
                                                                    }
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    else ds[curr]["start"] = numtostring(code.size());
                                                                    // code.push_back("start="+ds[curr]["start"]);
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($1)));
                                                                    for(auto i:ds2[curr2]["type"]){
                                                                        // if(i!=chartostring($1)){
                                                                            type_check(yylineno, chartostring((yyvsp[-2].val)),i,"=");
                                                                        // }
                                                                    }
                                                                    
                                                                    
                                                                    
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
#line 3822 "parser_1st.tab.c"
    break;

  case 209: /* FIELDDECLARATION: SUPER1 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 645 "parser_1st.y"
                                                                    {
                                                    if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);

                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                                     int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                                     int start = code.size();
                                                                                     if(ds[curr2].find("start")!=ds[curr2].end()){
                                                                                        start = stringtonum(ds[curr2]["start"]);
                                                                                     }
                                                                int flag = 0;
                                                                    for(auto i:generalmap[(yyvsp[-3].val)].modifiers){
                                                                        if(i=="static"){
                                                                            add_static(code,start,ds2[curr2]["var_name"]);
                                                                            flag = 1;
                                                                            break;
                                                                        }
                                                                    }
                                                                    if(flag){
                                                                        for(auto name:ds2[curr2]["var_name"])
                                                                        static_name.insert(name);
                                                                    }
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    else ds[curr]["start"] = numtostring(code.size());
                                                                    // code.push_back("start="+ds[curr]["start"]);
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($1)));
                                                                    for(auto i:ds2[curr2]["type"]){
                                                                        // if(i!=chartostring($1)){
                                                                            type_check(yylineno, chartostring((yyvsp[-2].val)),i,"=");
                                                                        // }
                                                                    }
                                                                    
                                                                    
                                                                    
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
#line 3879 "parser_1st.tab.c"
    break;

  case 210: /* FIELDDECLARATION: SUPER2 TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 697 "parser_1st.y"
                                                                    {
                                                    if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);

                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                                     int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                                     int start = code.size();
                                                                                     if(ds[curr2].find("start")!=ds[curr2].end()){
                                                                                        start = stringtonum(ds[curr2]["start"]);
                                                                                     }
                                                                 int flag = 0;
                                                                    for(auto i:generalmap[(yyvsp[-3].val)].modifiers){
                                                                        if(i=="static"){
                                                                            add_static(code,start,ds2[curr2]["var_name"]);
                                                                            flag = 1;
                                                                            break;
                                                                        }
                                                                    }
                                                                    if(flag){
                                                                        for(auto name:ds2[curr2]["var_name"])
                                                                        static_name.insert(name);
                                                                    }
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    else ds[curr]["start"] = numtostring(code.size());
                                                                    // code.push_back("start="+ds[curr]["start"]);
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($1)));
                                                                    for(auto i:ds2[curr2]["type"]){
                                                                        // if(i!=chartostring($1)){
                                                                            type_check(yylineno, chartostring((yyvsp[-2].val)),i,"=");
                                                                        // }
                                                                    }
                                                                    
                                                                    
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
#line 3935 "parser_1st.tab.c"
    break;

  case 211: /* FIELDDECLARATION: TYPE VARIABLEDECLARATORLIST SEMICOLON  */
#line 748 "parser_1st.y"
                                                               {
                        if(generalmap[(yyvsp[-1].val)].typ.name != "")assert(chartostring((yyvsp[-2].val))== generalmap[(yyvsp[-1].val)].typ.name);


                        {   (yyval.val) = new_temp();
                        // TYPE CHECK
                                                                    int  curr2 = chartonum((yyvsp[-1].val)), curr = chartonum((yyval.val));
                                                                    int start = code.size();
                                                                                     if(ds[curr2].find("start")!=ds[curr2].end()){
                                                                                        start = stringtonum(ds[curr2]["start"]);
                                                                                     }
                                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
                                                                    // if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    add_non_static(code,start,ds2[curr2]["var_name"]);
                                                                    if(ds[curr2].find("start")!=ds[curr2].end())
                                                                    ds[curr]["start"] = ds[curr2]["start"];
                                                                    else ds[curr]["start"] = numtostring(code.size());
                                                                    // code.push_back("start="+ds[curr]["start"]);
                                                                    // assert(!(ds[curr2].find("type")!=ds[curr2].end()&&ds[curr2]["type"]!=chartostring($1)));
                                                                    for(auto i:ds2[curr2]["type"]){
                                                                        // if(i!=chartostring($1)){
                                                                            type_check(yylineno, chartostring((yyvsp[-2].val)),i,"=");
                                                                        // }
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
#line 3982 "parser_1st.tab.c"
    break;

  case 212: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATOR  */
#line 793 "parser_1st.y"
                                               {(yyval.val) = new_temp(); generalmap[(yyval.val)].typ = generalmap[(yyvsp[0].val)].typ; generalmap[(yyval.val)].vlist.push_back({generalmap[(yyvsp[0].val)].vid, generalmap[(yyvsp[0].val)].vinit});
{   
                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                                    if(ds[curr1].find("start")!=ds[curr1].end()){
                                                        ds[curr]["start"] = ds[curr1]["start"];
                                                        ds2[curr]["type"].push_back(ds[curr1]["type"]);
                                                    }
                                                        ds2[curr]["var_name"].push_back(ds[curr1]["var_name"]);
                                                    // ds[curr]["start"] = ds[curr1]["start"];
                                                    // assert(!(ds[curr1].find("type")!=ds[curr1].end()&&ds[curr1].find("type")!=ds[curr1].end()&&ds[curr3]["type"]!=ds[curr1]["type"]));
                                                    // ds[curr]["lineno"] = ds[curr1]["lineno"];
}
}
#line 4000 "parser_1st.tab.c"
    break;

  case 213: /* VARIABLEDECLARATORLIST: VARIABLEDECLARATORLIST COMMA VARIABLEDECLARATOR  */
#line 806 "parser_1st.y"
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
                                                        ds2[curr]["var_name"].push_back(ds[curr3]["var_name"]);
                                                    // assert(ds[curr].find("start")!=ds[curr].end());
                                                    // error("Incompatible types");

}
}
#line 4029 "parser_1st.tab.c"
    break;

  case 214: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID EQUALS VARIABLEINITIALIZER  */
#line 831 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit ;   generalmap[(yyval.val)].typ= generalmap[(yyvsp[0].val)].typ;                                   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));                                     ds[curr]["var_name"] = ds[curr1]["var_name"];
                                                                            if(ds[curr3].find("class")!=ds[curr3].end()){
                                                                                ds[curr]["var"] = ds[curr1]["var"];
                                                                                string cls = ds[curr3]["var"];    // stores the class name after new
                                                                                if(ds[curr3].find("start")==ds[curr3].end())
                                                                                ds[curr]["start"] = numtostring(code.size());
                                                                                else ds[curr]["start"] = ds[curr3]["start"];
                                                                                code.push_back(ds[curr]["var"]+" = "+"class ( "+cls+" )");
                                                                                // Constructor call after declaring object
                                                                                if(ds[curr3].find("isconstructor")!=ds[curr3].end()){
                                                                                    for(auto i:ds2[curr3]["cons_code"])
                                                                                    code.push_back(i);
                                                                                    code.push_back("call, "+ds[curr]["var"]+"."+cls);
                                                                                }
                                                                                // pref[ds[ chartonum($$)]["var"]] = new_var2();
                                                                                // pref[ds[ chartonum($$)]["var"]] = ds[chartonum($3)]["pref"];
                                                                                // if(ds[curr3].find("isconstructor")!=ds[curr3].end())
                                                                                // code.push_back("call, "+pref[ds[ chartonum($$)]["var"]]+cls);
                                                                                // object_list.push_back({ds[curr]["var"],cls,pref[ds[ chartonum($$)]["var"]]}); // Add object to object list
                                                                            }
                                                                            else if(ds[curr3].find("arr")!=ds[curr3].end()){
                                                                                if(ds[curr3].find("start")==ds[curr3].end())
                                                                                ds[curr]["start"] = numtostring(code.size());
                                                                                else ds[curr]["start"] = ds[curr3]["start"];
                                                                                ds[curr]["type"] = ds[curr3]["type"];
                                                                                code.push_back(ds[curr1]["var"]+" = array! ( "+ds[curr3]["var"]+" )");

                                                                               
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
#line 4081 "parser_1st.tab.c"
    break;

  case 215: /* VARIABLEDECLARATOR: VARIABLEDECLARATORID  */
#line 878 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];ds[chartonum((yyval.val))]["var_name"] = ds[chartonum((yyvsp[0].val))]["var_name"];}
#line 4087 "parser_1st.tab.c"
    break;

  case 216: /* VARIABLEDECLARATORID: IDENTIFIER  */
#line 880 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));
                                            ds[curr]["var_name"] = ds[curr]["var"];

}
#line 4101 "parser_1st.tab.c"
    break;

  case 217: /* VARIABLEDECLARATORID: IDENTIFIER DIMS  */
#line 889 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        int curr = chartonum((yyval.val));
                                    ds[curr]["var"] = chartostring((yyvsp[-1].val));
                                    ds[curr]["var_name"] = ds[curr]["var"];
                        /*TODO*/
                        }
#line 4112 "parser_1st.tab.c"
    break;

  case 218: /* VARIABLEINITIALIZER: EXPRESSION  */
#line 897 "parser_1st.y"
                                    {(yyval.val) = new_temp();ds2[chartonum((yyval.val))] = ds2[chartonum((yyvsp[0].val))]; generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 4118 "parser_1st.tab.c"
    break;

  case 219: /* VARIABLEINITIALIZER: ARRAYINITIALIZER  */
#line 898 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 4124 "parser_1st.tab.c"
    break;

  case 220: /* EXPRESSION: ASSIGNMENTEXPRESSION  */
#line 900 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4130 "parser_1st.tab.c"
    break;

  case 221: /* ASSIGNMENTEXPRESSION: CONDITIONALEXPRESSION  */
#line 902 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 4138 "parser_1st.tab.c"
    break;

  case 222: /* ASSIGNMENTEXPRESSION: ASSIGNMENT  */
#line 905 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);/*TODO CHECK multiple assign*/}
#line 4144 "parser_1st.tab.c"
    break;

  case 223: /* ASSIGNMENT: LEFTHANDSIDE ASSIGNMENTOPERATOR EXPRESSION  */
#line 907 "parser_1st.y"
                                                           {
    
    // code.pb($1.val + $2.val + $3.val )
    // string t  =new_var();
    // code.pb(t + " = " + $1.val);
    // $$.val = t;
    (yyval.val) = (yyvsp[-2].val);
    int curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val)), curr2 = chartonum((yyvsp[-1].val));
    type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    // cout<<ds[curr1]["type"]<<" "<<ds[curr3]["type"]<<"\n";
    type_conversion(ds[curr1]["type"],ds[curr3]["type"],ds[curr2]["op"]);
    // code.push_back("hello");
    code.push_back(ds[curr1]["var"]+" "+ds[curr2]["op"]+" "+ds[curr3]["var"]);

}
#line 4164 "parser_1st.tab.c"
    break;

  case 224: /* LEFTHANDSIDE: EXPRESSIONNAME  */
#line 923 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 4170 "parser_1st.tab.c"
    break;

  case 225: /* LEFTHANDSIDE: IDENTIFIER  */
#line 924 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
#line 4183 "parser_1st.tab.c"
    break;

  case 226: /* LEFTHANDSIDE: FIELDACCESS  */
#line 932 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4189 "parser_1st.tab.c"
    break;

  case 227: /* LEFTHANDSIDE: ARRAYACCESS  */
#line 933 "parser_1st.y"
                                {   (yyval.val) = (yyvsp[0].val);
                // ds[chartonum($$)] = ds[chartonum($1)];
                                    // ds[chartonum($$)]["var"]  = new_var();
                                    // code.push_back(ds[chartonum($$)]["var"]+" = "+ds[chartonum($$)]["array"]+" [ "+ds[chartonum($1)]["var"]+" ]");
                                    string t = new_var(), t2 = new_var();
                                    code.push_back(t+" = 8");
                                    code.push_back(t2+" = "+ds[chartonum((yyvsp[0].val))]["var"]+" *int "+t);
                                    ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+" [ "+t2+" ]";
                }
#line 4203 "parser_1st.tab.c"
    break;

  case 228: /* ASSIGNMENTOPERATOR: EQUALS  */
#line 943 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 4210 "parser_1st.tab.c"
    break;

  case 229: /* ASSIGNMENTOPERATOR: MULTIPLYEQUALS  */
#line 945 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 4217 "parser_1st.tab.c"
    break;

  case 230: /* ASSIGNMENTOPERATOR: DIVIDEEQUALS  */
#line 947 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 4224 "parser_1st.tab.c"
    break;

  case 231: /* ASSIGNMENTOPERATOR: MODEQUALS  */
#line 949 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 4231 "parser_1st.tab.c"
    break;

  case 232: /* ASSIGNMENTOPERATOR: PLUSEQUALS  */
#line 951 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 4238 "parser_1st.tab.c"
    break;

  case 233: /* ASSIGNMENTOPERATOR: MINUSEQUALS  */
#line 953 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 4245 "parser_1st.tab.c"
    break;

  case 234: /* FIELDACCESS: PRIMARY DOT IDENTIFIER  */
#line 956 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = numtostring(code.size());
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));
                                        }
                                        }
#line 4257 "parser_1st.tab.c"
    break;

  case 237: /* PRIMARY: PRIMARYNONEWARRAY  */
#line 966 "parser_1st.y"
                            {
                            if(ds[chartonum((yyvsp[0].val))].find("array")!=ds[chartonum((yyvsp[0].val))].end()){
                                    (yyval.val) = new_temp();
                                    ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))];
                                    string t = new_var(), t2 = new_var();
                                    code.push_back(t+" = 8");
                                    code.push_back(t2+" = "+ds[chartonum((yyvsp[0].val))]["var"]+" *int "+t);
                                    ds[chartonum((yyval.val))]["var"]  = new_var();
                                    code.push_back(ds[chartonum((yyval.val))]["var"]+" = "+ds[chartonum((yyval.val))]["array"]+" [ "+t2+" ]");
                            }else (yyval.val) = (yyvsp[0].val);
                            // ds[chartonum($$)]["var"] = ds[chartonum($$)]["array"]+"["+ds[chartonum($1)]["var"]+"]"; 
                            }
#line 4274 "parser_1st.tab.c"
    break;

  case 238: /* PRIMARY: ARRAYCREATIONEXPRESSION  */
#line 978 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4280 "parser_1st.tab.c"
    break;

  case 239: /* PRIMARYNONEWARRAY: LITERAL  */
#line 980 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4286 "parser_1st.tab.c"
    break;

  case 240: /* PRIMARYNONEWARRAY: CLASSLITERAL  */
#line 981 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4292 "parser_1st.tab.c"
    break;

  case 241: /* PRIMARYNONEWARRAY: THIS  */
#line 982 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 4301 "parser_1st.tab.c"
    break;

  case 243: /* PRIMARYNONEWARRAY: OPENPARAN EXPRESSION CLOSEPARAN  */
#line 987 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4307 "parser_1st.tab.c"
    break;

  case 244: /* PRIMARYNONEWARRAY: CLASSINSTANCECREATIONEXPRESSION  */
#line 988 "parser_1st.y"
                                                              {(yyval.val) = (yyvsp[0].val); generalmap[(yyval.val)].isnewclass = true;}
#line 4313 "parser_1st.tab.c"
    break;

  case 245: /* PRIMARYNONEWARRAY: FIELDACCESS  */
#line 989 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4319 "parser_1st.tab.c"
    break;

  case 246: /* PRIMARYNONEWARRAY: ARRAYACCESS  */
#line 990 "parser_1st.y"
                                    {(yyval.val)=(yyvsp[0].val);}
#line 4325 "parser_1st.tab.c"
    break;

  case 247: /* PRIMARYNONEWARRAY: METHODINVOCATION  */
#line 991 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4331 "parser_1st.tab.c"
    break;

  case 249: /* LITERAL: INTEGERLITERAL  */
#line 994 "parser_1st.y"
                        {(yyval.val) = new_temp();  ds[chartonum((yyval.val))]["type"] = "byte"; ds[chartonum((yyval.val))]["var"] = new_var(); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); tempinitval[ds[chartonum((yyval.val))]["var"]]= chartonum((yyvsp[0].val)); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4337 "parser_1st.tab.c"
    break;

  case 250: /* LITERAL: FLOATINGPOINTLITERAL  */
#line 995 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["start"] = numtostring(code.size());ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4343 "parser_1st.tab.c"
    break;

  case 251: /* LITERAL: BOOLEANLITERAL  */
#line 996 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4349 "parser_1st.tab.c"
    break;

  case 252: /* LITERAL: CHARACTERLITERAL  */
#line 997 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4355 "parser_1st.tab.c"
    break;

  case 253: /* LITERAL: STRINGLITERAL  */
#line 998 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4361 "parser_1st.tab.c"
    break;

  case 254: /* LITERAL: TEXTBLOCK  */
#line 999 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4367 "parser_1st.tab.c"
    break;

  case 255: /* LITERAL: NULLLITERAL  */
#line 1000 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4373 "parser_1st.tab.c"
    break;

  case 265: /* CLASSINSTANCECREATIONEXPRESSION: UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION  */
#line 1013 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[0].val); }
#line 4379 "parser_1st.tab.c"
    break;

  case 269: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN  */
#line 1018 "parser_1st.y"
                                                                                                           {(yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-2].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-2].val))]; 

                                                        int curr = chartonum((yyval.val));
                                                        // cout<<"passses here\n";
                                                        // string name = chartostring($1), name2 = chartostring($3);
                                                        string class_name = ds[chartonum((yyvsp[-2].val))]["var"];
                                                            vector<string> types;
                                                   /*CONS*/     consinfo detail = getconstructordetails(class_name);
                                                        // ds[curr]["pref"] = new_var2();
                                                        ds[curr]["start"] = numtostring(code.size());
                                                        if(detail.isconstructor){    // pref is still not initialised here
                                                            type_check_function_obj(yylineno,detail.cons.argtype,types);     // takes in name of function and types of parameters
                                                            ds[curr]["isconstructor"] = "true";
                                                            // cout<<"YES\n";
                                                            // ds2[curr].push_back("call, "+ds[curr]["pref"]+ds[chartonum($$)][var]);
                                                        }else{
                                                            // cout<<"NO\n";
                                                            // object_error_func(name,name2,yylineno);
                                                            // Using default constructor
                                                        }
                                             }
#line 4405 "parser_1st.tab.c"
    break;

  case 270: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN CLOSEPARAN CLASSBODY  */
#line 1039 "parser_1st.y"
                                                                                                                     {/*TODO*/}
#line 4411 "parser_1st.tab.c"
    break;

  case 271: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 1040 "parser_1st.y"
                                                                                                                        {
                                                (yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-3].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-3].val))]; 

                                                        int curr = chartonum((yyval.val)), curr4 = chartonum((yyvsp[-1].val));
                                                        string class_name = ds[chartonum((yyvsp[-3].val))]["var"];
                                                        // string name = chartostring($1), name2 = chartostring($3);
                                                            vector<string> types;
                                                            for(auto i:ds2[curr4]["type"])
                                                            types.push_back(i);
                                            /*CONS*/     consinfo detail = getconstructordetails(class_name);
                                                        // ds[curr]["pref"] = new_var2();
                                                        if(detail.isconstructor){    // pref is still not initialised here
                                                            type_check_function_obj(yylineno,detail.cons.argtype,types);    // takes in name of function and types of parameters
                                                            ds[curr]["start"] = ds[curr4]["start"];
                                                            ds[curr]["isconstructor"] = "true";
                                                            for(auto i:ds2[curr4]["var"])
                                                            ds2[curr]["cons_code"].push_back("push param "+i);
                                                            // code.push_back("call, "+ds[curr]["pref"]+ds[chartonum($$)][var]);
                                                        }else{
                                                            object_error_constructor(class_name,yylineno);
                                                            // Using default constructor
                                                        }
                                            }
#line 4439 "parser_1st.tab.c"
    break;

  case 272: /* UNQUALIFIEDCLASSINSTANCECREATIONEXPRESSION: NEW CLASSORINTERFACETYPETOINSTANTIATE OPENPARAN ARGUMENTLIST CLOSEPARAN CLASSBODY  */
#line 1063 "parser_1st.y"
                                                                                                                                  {/*TODO*/}
#line 4445 "parser_1st.tab.c"
    break;

  case 277: /* CLASSORINTERFACETYPETOINSTANTIATE: IDENTIFIER  */
#line 1069 "parser_1st.y"
                                                {   (yyval.val) = new_temp(); ds[ chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val)); ds[ chartonum((yyval.val))]["class"] = "true";
                                                     }
#line 4452 "parser_1st.tab.c"
    break;

  case 278: /* ARGUMENTLIST: EXPRESSION  */
#line 1072 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            ds2[chartonum((yyval.val))]["type"].push_back(ds[chartonum((yyvsp[0].val))]["type"]);
                            ds2[chartonum((yyval.val))]["var"].push_back(ds[chartonum((yyvsp[0].val))]["var"]);
                            }
#line 4461 "parser_1st.tab.c"
    break;

  case 279: /* ARGUMENTLIST: ARGUMENTLIST COMMA EXPRESSION  */
#line 1076 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4474 "parser_1st.tab.c"
    break;

  case 280: /* METHODINVOCATION: METHODNAME OPENPARAN CLOSEPARAN  */
#line 1085 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                                        string name = ds[curr1]["var"];
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = methods[name].rettype.name;
                                                        vector<string> types;
                                                        type_check_function(name,types,yylineno);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = numtostring(code.size());
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+curr_class+"_"+name);
                                                        else code.push_back("call, "+curr_class+"_"+name);
}
#line 4491 "parser_1st.tab.c"
    break;

  case 281: /* METHODINVOCATION: METHODNAME OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 1097 "parser_1st.y"
                                                                    {   (yyval.val) = new_temp();
                                                        // cout<<"passes here\n";
                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
                                                        string name = ds[curr1]["var"] ;
                                                        ds[curr]["type"] = methods[name].rettype.name;
                                                        vector<string> types;
                                                        // cout<<"type2 : "<<ds2[curr3]["type"].size()<<"\n";
                                                        for(auto i:ds2[curr3]["type"]){
                                                            types.push_back(i);
                                                        }
                                                        type_check_function(name,types,yylineno);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = ds[curr3]["start"];
                                                        for(auto i:ds2[curr3]["var"])
                                                        code.push_back("push param "+i);
                                                        if(ds[curr]["type"]!="void"){
                                                        ds[curr]["var"] = new_var();
                                                        code.push_back(ds[curr]["var"]+" = call, "+curr_class+"_"+name);
                                                        }
                                                        else code.push_back("call, "+curr_class+"_"+name);
}
#line 4516 "parser_1st.tab.c"
    break;

  case 282: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1117 "parser_1st.y"
                                                                        {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val));
                                                        vector<string> types;
                                                        string name = chartostring((yyvsp[-4].val)), name2 = chartostring((yyvsp[-2].val));
                                                        objdetails detail = getobjdetails(name,name2);    //support polymorphism by characterising function by class name, func name and types of arguments.
                                                        string fname = "";
                                                        if(detail.ismethod&&not_static_check(detail.method.access)){
                                                            // fname = pref[chartostring($1)]+chartostring($3);
                                                            fname = chartostring((yyvsp[-4].val))+"."+chartostring((yyvsp[-2].val));
                                                            // ds[curr]["type"] = detail.field.typ.name;
                                                        }else{
                                                            object_error_func(name,name2,yylineno);
                                                        }
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = detail.method.rettype.name;
                                                        // cout<<""
                                                        // code.push_back(ds[curr]["type"]);
                                                        type_check_function_obj(yylineno,detail.method.argtype,types);    // takes in name of function and types of parameters
                                                        // cout<<"curr var "<<ds[curr]["var"]<<"\n";
                                                        ds[curr]["start"] = numtostring(code.size());
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
}
#line 4546 "parser_1st.tab.c"
    break;

  case 283: /* METHODINVOCATION: IDENTIFIER DOT IDENTIFIER OPENPARAN ARGUMENTLIST CLOSEPARAN  */
#line 1142 "parser_1st.y"
                                                                                    {   /* Method invocation using object?  */
                                                          (yyval.val) = new_temp();
                                                        int curr = chartonum((yyval.val)), curr5 = chartonum((yyvsp[-1].val));
                                                        string name = chartostring((yyvsp[-5].val)), name2 = chartostring((yyvsp[-3].val));
                                                        vector<string> types;
                                                        for(auto i:ds2[curr5]["type"]){
                                                            types.push_back(i);
                                                        }
                                                        objdetails detail = getobjdetails(name,name2);    //support polymorphism by characterising function by class name, func name and types of arguments.
                                                        string fname = "";
                                                        if(detail.ismethod&&not_static_check(detail.method.access)){
                                                            fname = chartostring((yyvsp[-5].val))+"."+chartostring((yyvsp[-3].val));
                                                            // ds[curr]["type"] = detail.field.typ.name;
                                                        }else{
                                                            object_error_func(name,name2,yylineno);
                                                        }
                                                        ds[curr]["var"] = new_var();
                                                        ds[curr]["type"] = detail.method.rettype.name;;
                                                        // cout<<"curr typed "<<ds[curr]["type"]<<"\n";
                                                        type_check_function_obj(yylineno,detail.method.argtype,types);    // takes in name of function and types of parameters
                                                        ds[curr]["start"] = ds[curr5]["start"];
                                                        for(auto i:ds2[curr5]["var"])
                                                        code.push_back("push param "+i);
                                                        if(ds[curr]["type"]!="void")
                                                        code.push_back(ds[curr]["var"]+" = call, "+fname);
                                                        else code.push_back("call, "+fname);
}
#line 4578 "parser_1st.tab.c"
    break;

  case 312: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS DIMS  */
#line 1201 "parser_1st.y"
                                                         {/*NOT SUPPORTED*/}
#line 4584 "parser_1st.tab.c"
    break;

  case 313: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS DIMS  */
#line 1202 "parser_1st.y"
                                                                       {/*NOT SUPPORTED*/}
#line 4590 "parser_1st.tab.c"
    break;

  case 314: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS ARRAYINITIALIZER  */
#line 1203 "parser_1st.y"
                                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-2].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; assert (generalmap[(yyvsp[0].val)].vinit.dims.size() == temp[(yyvsp[-1].val)]); }
#line 4596 "parser_1st.tab.c"
    break;

  case 315: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS ARRAYINITIALIZER  */
#line 1204 "parser_1st.y"
                                                                               {/*NOT SUPPORTED*/}
#line 4602 "parser_1st.tab.c"
    break;

  case 316: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMEXPRS  */
#line 1205 "parser_1st.y"
                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; reverse(all(generalmap[(yyval.val)].vinit.dims)); ds[chartonum((yyval.val))]["arr"] = "true"; ds[chartonum((yyval.val))]["var"] = new_var(); string t = new_var(); 
                        code.push_back(t+" = 8"); 
                        // code.push_back(t+" = "+numtostring(gettypesize(chartostring($2)))); 
                        code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ ds[chartonum((yyvsp[0].val))]["var"]+" *int "+t); ds[chartonum((yyval.val))]["type"] = chartostring((yyvsp[-1].val)); ds[chartonum((yyval.val))]["start"] = ds[chartonum((yyvsp[0].val))]["start"];}
#line 4611 "parser_1st.tab.c"
    break;

  case 317: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMEXPRS  */
#line 1209 "parser_1st.y"
                                                                   {/*NOT SUPPORTED*/}
#line 4617 "parser_1st.tab.c"
    break;

  case 318: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE DIMS  */
#line 1210 "parser_1st.y"
                                                   {/*NOT SUPPORTED*/}
#line 4623 "parser_1st.tab.c"
    break;

  case 319: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE DIMS  */
#line 1211 "parser_1st.y"
                                                              {/*NOT SUPPORTED*/}
#line 4629 "parser_1st.tab.c"
    break;

  case 320: /* ARRAYCREATIONEXPRESSION: NEW PRIMITIVETYPE  */
#line 1212 "parser_1st.y"
                                               {/*TODO whats this*/}
#line 4635 "parser_1st.tab.c"
    break;

  case 321: /* ARRAYCREATIONEXPRESSION: NEW CLASSORINTERFACETYPE  */
#line 1213 "parser_1st.y"
                                                         {/*TODO whats this*/}
#line 4641 "parser_1st.tab.c"
    break;

  case 322: /* ARRAYINITIALIZER: OPENCURLY ARRAYINITIALIZER1 CLOSECURLY  */
#line 1215 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4647 "parser_1st.tab.c"
    break;

  case 323: /* ARRAYINITIALIZER: OPENCURLY CLOSECURLY  */
#line 1216 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4653 "parser_1st.tab.c"
    break;

  case 324: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST  */
#line 1218 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4659 "parser_1st.tab.c"
    break;

  case 325: /* ARRAYINITIALIZER1: COMMA  */
#line 1219 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=2;}
#line 4665 "parser_1st.tab.c"
    break;

  case 326: /* ARRAYINITIALIZER1: VARIABLEINITIALIZERLIST COMMA  */
#line 1220 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4671 "parser_1st.tab.c"
    break;

  case 327: /* DIMEXPRS: DIMEXPR  */
#line 1222 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[0].val))];}
#line 4677 "parser_1st.tab.c"
    break;

  case 328: /* DIMEXPRS: DIMEXPRS DIMEXPR  */
#line 1223 "parser_1st.y"
                             {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum((yyvsp[-1].val))]["var"]+" *"+ds[chartonum((yyvsp[0].val))]["type"]+" "+ds[ chartonum((yyvsp[0].val))]["var"]);
                              ds[ chartonum((yyval.val))]["var"] = t;  }
#line 4685 "parser_1st.tab.c"
    break;

  case 329: /* DIMEXPR: OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1227 "parser_1st.y"
                                            {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = varaddrstoint(ds[chartonum((yyvsp[-1].val))]["var"]); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-1].val))];}
#line 4691 "parser_1st.tab.c"
    break;

  case 330: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZER  */
#line 1229 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4697 "parser_1st.tab.c"
    break;

  case 331: /* VARIABLEINITIALIZERLIST: VARIABLEINITIALIZERLIST COMMA VARIABLEINITIALIZER  */
#line 1230 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4703 "parser_1st.tab.c"
    break;

  case 333: /* ARRAYACCESS: PRIMARYNONEWARRAY OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1237 "parser_1st.y"
                                                                    {
                (yyval.val) = new_temp(); 
                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[-1].val));
                if(ds[curr3]["type"]!="int"&&ds[curr3]["type"]!="long"&&ds[curr3]["type"]!="short"&&ds[curr3]["type"]!="byte")
                cout<<"Array index not integer\n";
                ds[curr] = ds[curr1];   
                int i = stringtonum(ds[curr]["dims"])+1;
        
                ds[curr]["dims"] = numtostring(stringtonum(ds[curr]["dims"])+1);
                string t = new_var();
                // cout<<"index"<<i<<"\n";
                // cout<<ds[curr]["array"]<<"\n";
                // cout<<symboltable[ds[curr]["array"]].dims.size()<<"\n";
                int bound = getdim(ds[curr]["array"],i);
             
                string exp = dimtoid[-bound];
                code.push_back(t+" = "+ds[curr1]["var"]+" *int "+exp);
                ds[curr]["var"] = new_var();
                // string ttt= new_var();
                code.push_back(ds[curr]["var"]+" = "+t+" + "+ds[curr3]["var"]);

                // code.push_back(ds[curr]["var"]+" = "+ttt+" * "+numtostring(gettypesize(ds[curr3]["var"]))); 
            }
#line 4731 "parser_1st.tab.c"
    break;

  case 334: /* ARRAYACCESS: IDENTIFIER OPENSQUARE EXPRESSION CLOSESQUARE  */
#line 1260 "parser_1st.y"
                                                                {
                (yyval.val) = new_temp();
                int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                string name = chartostring((yyvsp[-3].val));
                ds[curr]["dims"] = "0";
                ds[curr]["array"] = name;
                ds[curr]["start"] = ds[curr3]["start"];
                // string t = new_var();
                ds[curr]["var"] = ds[curr3]["var"];
                // code.push_back(t+" = 8");
                // code.push_back(t+" = "+numtostring(gettypesize(ds[curr3]["var"])));
                // code.push_back(ds[curr]["var"]+" = "+ds[curr3]["var"]+" *int "+t);
                ds[curr]["type"] = gettypenew(name);
                if(ds[curr3]["type"]!="int"&&ds[curr3]["type"]!="long"&&ds[curr3]["type"]!="short"&&ds[curr3]["type"]!="byte")
                cout<<"Array index not integer\n";
                // code.push_back(ds[curr]["var"]+" = "+ds[curr3]["var"]);
            }
#line 4753 "parser_1st.tab.c"
    break;

  case 335: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION  */
#line 1278 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4759 "parser_1st.tab.c"
    break;

  case 336: /* CONDITIONALEXPRESSION: CONDITIONALOREXPRESSION QUESTIONMARK EXPRESSION COLON CONDITIONALEXPRESSION  */
#line 1279 "parser_1st.y"
                                                                                                    {}
#line 4765 "parser_1st.tab.c"
    break;

  case 337: /* CONDITIONALOREXPRESSION: CONDITIONALANDEXPRESSION  */
#line 1281 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4771 "parser_1st.tab.c"
    break;

  case 338: /* CONDITIONALOREXPRESSION: CONDITIONALOREXPRESSION OROR CONDITIONALANDEXPRESSION  */
#line 1282 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["falselist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"||");
                                                                                        ds3[curr]["falselist"] = ds3[curr3]["falselist"];
                                                                                        ds3[curr]["truelist"] = merge(ds3[curr1]["truelist"],ds3[curr3]["truelist"]);
                                                                                        // backpatch(ds3[curr1]["truelist"],code.size());
                                                                                        // backpatch(ds3[curr3]["truelist"],code.size());
                                                                                        // ds[curr]["var"] = new_var();
                                                                                        // code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" || "+ds[curr3]["var"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4789 "parser_1st.tab.c"
    break;

  case 339: /* CONDITIONALANDEXPRESSION: INCLUSIVEOREXPRESSION  */
#line 1296 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4795 "parser_1st.tab.c"
    break;

  case 340: /* CONDITIONALANDEXPRESSION: CONDITIONALANDEXPRESSION ANDAND INCLUSIVEOREXPRESSION  */
#line 1297 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                        backpatch(ds3[curr1]["truelist"],stringtonum(ds[curr3]["start"]));
                                                                                        type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"&&");
                                                                                        ds3[curr]["truelist"] = ds3[curr3]["truelist"];
                                                                                        ds3[curr]["falselist"] = merge(ds3[curr1]["falselist"],ds3[curr3]["falselist"]);
                                                                                        // ds2[curr]["code"] = ds2[curr1]["code"] + "\n" + ds2[curr3]["code"];
                                                                                        ds[curr]["type"] = "bool";
                                                                                        ds[curr]["start"] = ds[curr1]["start"];}
#line 4809 "parser_1st.tab.c"
    break;

  case 341: /* INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION  */
#line 1307 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4815 "parser_1st.tab.c"
    break;

  case 342: /* INCLUSIVEOREXPRESSION: INCLUSIVEOREXPRESSION OR EXCLUSIVEOREXPRESSION  */
#line 1308 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4828 "parser_1st.tab.c"
    break;

  case 343: /* EXCLUSIVEOREXPRESSION: ANDEXPRESSION  */
#line 1317 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4834 "parser_1st.tab.c"
    break;

  case 344: /* EXCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION XOR ANDEXPRESSION  */
#line 1318 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4847 "parser_1st.tab.c"
    break;

  case 345: /* ANDEXPRESSION: EQUALITYEXPRESSION  */
#line 1326 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4853 "parser_1st.tab.c"
    break;

  case 346: /* ANDEXPRESSION: ANDEXPRESSION AND EQUALITYEXPRESSION  */
#line 1327 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4867 "parser_1st.tab.c"
    break;

  case 347: /* EQUALITYEXPRESSION: RELATIONALEXPRESSION  */
#line 1337 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
#line 4880 "parser_1st.tab.c"
    break;

  case 348: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION EQUALSEQUALS RELATIONALEXPRESSION  */
#line 1345 "parser_1st.y"
                                                                                {   (yyval.val) = new_temp();
                                                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                    type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"==");
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
#line 4901 "parser_1st.tab.c"
    break;

  case 349: /* EQUALITYEXPRESSION: EQUALITYEXPRESSION NOTEQUALS RELATIONALEXPRESSION  */
#line 1361 "parser_1st.y"
                                                                                {   
                                                                                    (yyval.val) = new_temp();
                                                                                    int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                    type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"!=");
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
#line 4923 "parser_1st.tab.c"
    break;

  case 350: /* RELATIONALEXPRESSION: SHIFTEXPRESSION  */
#line 1379 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4933 "parser_1st.tab.c"
    break;

  case 351: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT SHIFTEXPRESSION  */
#line 1384 "parser_1st.y"
                                                                            {      // IS backpatching for $1 required?
                                                                                (yyval.val) = new_temp();
                                                                                // code.push_back("REL0 "+ds[chartonum($1)]["start"]);
                                                                                // code.push_back("REL1 "+ds[chartonum($3)]["start"]);
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"<");
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
#line 4956 "parser_1st.tab.c"
    break;

  case 352: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT SHIFTEXPRESSION  */
#line 1402 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],">");
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
#line 4975 "parser_1st.tab.c"
    break;

  case 353: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARRIGHT EQUALS SHIFTEXPRESSION  */
#line 1416 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],">=");
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
#line 4994 "parser_1st.tab.c"
    break;

  case 354: /* RELATIONALEXPRESSION: RELATIONALEXPRESSION ANGULARLEFT EQUALS SHIFTEXPRESSION  */
#line 1430 "parser_1st.y"
                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-3].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"<=");
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
#line 5013 "parser_1st.tab.c"
    break;

  case 356: /* SHIFTEXPRESSION: ADDITIVEEXPRESSION  */
#line 1446 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 5019 "parser_1st.tab.c"
    break;

  case 357: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARLEFTANGULARLEFT ADDITIVEEXPRESSION  */
#line 1447 "parser_1st.y"
                                                                                    {   // Invariant : each non terminal corresponds to certain code in 3ac. Maintain the final variable in that 3ac, its type and the start of the code corresponding to that non terminal
                                                                                    (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"<<");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" << "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5033 "parser_1st.tab.c"
    break;

  case 358: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1456 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5046 "parser_1st.tab.c"
    break;

  case 359: /* SHIFTEXPRESSION: SHIFTEXPRESSION ANGULARRIGHTANGULARRIGHTANGULARRIGHT ADDITIVEEXPRESSION  */
#line 1464 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5059 "parser_1st.tab.c"
    break;

  case 360: /* ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION  */
#line 1473 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 5065 "parser_1st.tab.c"
    break;

  case 361: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION PLUS MULTIPLICATIVEEXPRESSION  */
#line 1474 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5078 "parser_1st.tab.c"
    break;

  case 362: /* ADDITIVEEXPRESSION: ADDITIVEEXPRESSION MINUS MULTIPLICATIVEEXPRESSION  */
#line 1482 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5091 "parser_1st.tab.c"
    break;

  case 363: /* MULTIPLICATIVEEXPRESSION: UNARYEXPRESSION  */
#line 1491 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5097 "parser_1st.tab.c"
    break;

  case 364: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MULTIPLY UNARYEXPRESSION  */
#line 1492 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5110 "parser_1st.tab.c"
    break;

  case 365: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION DIVIDE UNARYEXPRESSION  */
#line 1500 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5123 "parser_1st.tab.c"
    break;

  case 366: /* MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION MOD UNARYEXPRESSION  */
#line 1508 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(yylineno, ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 5136 "parser_1st.tab.c"
    break;

  case 367: /* UNARYEXPRESSION: PREINCREMENTEXPRESSION  */
#line 1517 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5142 "parser_1st.tab.c"
    break;

  case 368: /* UNARYEXPRESSION: PREDECREMENTEXPRESSION  */
#line 1518 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5148 "parser_1st.tab.c"
    break;

  case 369: /* UNARYEXPRESSION: PLUS UNARYEXPRESSION  */
#line 1519 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 5156 "parser_1st.tab.c"
    break;

  case 370: /* UNARYEXPRESSION: MINUS UNARYEXPRESSION  */
#line 1522 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5169 "parser_1st.tab.c"
    break;

  case 371: /* UNARYEXPRESSION: UNARYEXPRESSIONNOTPLUSMINUS  */
#line 1530 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5175 "parser_1st.tab.c"
    break;

  case 372: /* PREINCREMENTEXPRESSION: PLUSPLUS UNARYEXPRESSION  */
#line 1532 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    assert(0&& "Not an identifier");
                                                }
                                                string t = new_var();
                                                code.push_back(t+" = 1");
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+" +int "+t);
                                                code.push_back(ds[curr2]["var"]+" = "+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] += 1;  /* Modify the actual underlying variable */
                    }
#line 5195 "parser_1st.tab.c"
    break;

  case 373: /* PREDECREMENTEXPRESSION: MINUSMINUS UNARYEXPRESSION  */
#line 1548 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr2].find("identifier")==ds[curr2].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                string t = new_var();
                                                code.push_back(t+" = -1");
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr2]["var"]+" +int "+t);
                                                code.push_back(ds[curr2]["var"]+ " = "+ ds[curr]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                                                // symtable[ds[curr]["identifier"]] -= 1;
                    }
#line 5215 "parser_1st.tab.c"
    break;

  case 374: /* UNARYEXPRESSIONNOTPLUSMINUS: POSTFIXEXPRESSION  */
#line 1564 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5221 "parser_1st.tab.c"
    break;

  case 375: /* UNARYEXPRESSIONNOTPLUSMINUS: COMPLEMENT UNARYEXPRESSION  */
#line 1565 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5234 "parser_1st.tab.c"
    break;

  case 376: /* UNARYEXPRESSIONNOTPLUSMINUS: NOT UNARYEXPRESSION  */
#line 1573 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5247 "parser_1st.tab.c"
    break;

  case 377: /* POSTFIXEXPRESSION: PRIMARY  */
#line 1582 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5253 "parser_1st.tab.c"
    break;

  case 378: /* POSTFIXEXPRESSION: EXPRESSIONNAME  */
#line 1583 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5259 "parser_1st.tab.c"
    break;

  case 379: /* POSTFIXEXPRESSION: IDENTIFIER  */
#line 1584 "parser_1st.y"
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
#line 5278 "parser_1st.tab.c"
    break;

  case 380: /* POSTFIXEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 1598 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5284 "parser_1st.tab.c"
    break;

  case 381: /* POSTFIXEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 1599 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5290 "parser_1st.tab.c"
    break;

  case 382: /* POSTINCREMENTEXPRESSION: POSTFIXEXPRESSION PLUSPLUS  */
#line 1601 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val));
                                                type_check_unary(ds[curr1]["type"],"++");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                string t = new_var();
                                                code.push_back(t+" = 1");
                                                code.push_back(ds[curr1]["var"]+ " = "+ ds[curr]["var"]+" +int "+t);
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
}
#line 5309 "parser_1st.tab.c"
    break;

  case 383: /* POSTDECREMENTEXPRESSION: POSTFIXEXPRESSION MINUSMINUS  */
#line 1616 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-1].val));
                                                type_check_unary(ds[curr1]["type"],"--");
                                                ds[curr]["var"] = new_var();
                                                if(ds[curr1].find("identifier")==ds[curr1].end()){
                                                    assert(0 && "Not an identifier");
                                                }
                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]);
                                                string t = new_var();
                                                code.push_back(t+" = -1");
                                                code.push_back(ds[curr1]["var"]+ " = "+ ds[curr]["var"]+" +int "+t);
                                                ds[curr]["type"] = ds[curr1]["type"];
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                // ds[curr]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
                                                // ds[curr1]["val"] = numtostring(stringtonum(ds[curr1]["val"]));
}
#line 5330 "parser_1st.tab.c"
    break;

  case 385: /* METHODDECLARATION: METHODHEADER METHODBODY  */
#line 1636 "parser_1st.y"
                                            {   
    (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    classmethods[curr_class][generalmap[(yyvsp[-1].val)].name] = methods[generalmap[(yyvsp[-1].val)].name];
    classpolymethods[curr_class][generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);

    polymethods[generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);
    
    
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$1].name<<endl;
}
#line 5347 "parser_1st.tab.c"
    break;

  case 386: /* METHODDECLARATION: SUPER1 METHODHEADER METHODBODY  */
#line 1650 "parser_1st.y"
                                                      {
                        (yyval.val) =(yyvsp[-1].val);
                        method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;

    // assert(methods.find(generalmap[$2].name) == methods.end());

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    // vector <type> argtype;
    // methods[generalmap[$2].name].lineno = yylineno;
    
    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;
    classmethods[curr_class][generalmap[(yyvsp[-1].val)].name] = methods[generalmap[(yyvsp[-1].val)].name];
    classpolymethods[curr_class][generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);
    polymethods[generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);


    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
         
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    //     classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];

}
#line 5378 "parser_1st.tab.c"
    break;

  case 387: /* METHODDECLARATION: SUPER2 METHODHEADER METHODBODY  */
#line 1676 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;
    //     assert(methods.find(generalmap[$2].name) == methods.end());
      

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    //     methods[generalmap[$2].name].lineno = yylineno;

    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;
    classmethods[curr_class][generalmap[(yyvsp[-1].val)].name] = methods[generalmap[(yyvsp[-1].val)].name];
    classpolymethods[curr_class][generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);

    polymethods[generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);

    // vector <type> argtype;
    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
        
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    // classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


}
#line 5409 "parser_1st.tab.c"
    break;

  case 388: /* METHODDECLARATION: SUPER3 METHODHEADER METHODBODY  */
#line 1702 "parser_1st.y"
                                                      {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;
    //     assert(methods.find(generalmap[$2].name) == methods.end());

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    //     methods[generalmap[$2].name].lineno = yylineno;

    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;
    classmethods[curr_class][generalmap[(yyvsp[-1].val)].name] = methods[generalmap[(yyvsp[-1].val)].name];
    classpolymethods[curr_class][generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);

    polymethods[generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);

    // vector <type> argtype;

    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
        
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    //     classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


}
#line 5440 "parser_1st.tab.c"
    break;

  case 389: /* METHODDECLARATION: METHODMODIFIERS METHODHEADER METHODBODY  */
#line 1728 "parser_1st.y"
                                                               {(yyval.val) =(yyvsp[-1].val);
                    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size();
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$2].name<<endl;
    //     assert(methods.find(generalmap[$2].name) == methods.end());

    // methods[generalmap[$2].name].rettype = generalmap[$2].typ;
    //     methods[generalmap[$2].name].lineno = yylineno;

    methods[generalmap[(yyvsp[-1].val)].name].access = generalmap[(yyvsp[-2].val)].modifiers;
    classmethods[curr_class][generalmap[(yyvsp[-1].val)].name] = methods[generalmap[(yyvsp[-1].val)].name];
    classpolymethods[curr_class][generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);


    polymethods[generalmap[(yyvsp[-1].val)].name].push_back(methods[generalmap[(yyvsp[-1].val)].name]);

    // vector <type> argtype;

    // for (auto x : generalmap[$2].farglist)
    //     {argtype.push_back(x.typ);
        
    //     }
    // methods[generalmap[$2].name].argtype = argtype;
    //     classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];


}
#line 5472 "parser_1st.tab.c"
    break;

  case 395: /* METHODHEADER: TYPE METHODDECLARATOR  */
#line 1762 "parser_1st.y"
                                     { (yyval.val) = (yyvsp[0].val);  generalmap[(yyval.val)].typ.name = chartostring((yyvsp[-1].val)); 
tempnextscope(); 

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
#line 5522 "parser_1st.tab.c"
    break;

  case 396: /* METHODHEADER: VOID METHODDECLARATOR  */
#line 1807 "parser_1st.y"
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
#line 5557 "parser_1st.tab.c"
    break;

  case 407: /* METHODDECLARATOR: IDENTIFIER OPENPARAN CLOSEPARAN  */
#line 1852 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));              
                                        method_det[curr_class][chartostring((yyvsp[-2].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
                                        if(chartostring((yyvsp[-2].val))!="main")
                                        code.push_back("begin func "+curr_class+"_"+chartostring((yyvsp[-2].val)));
                                        else code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        // cout<<"methodhead "<<ds[chartonum($$)]["method_name"]<<"\n";
                                        }
#line 5572 "parser_1st.tab.c"
    break;

  case 408: /* METHODDECLARATOR: IDENTIFIER OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 1862 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                method_det[curr_class][chartostring((yyvsp[-3].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-3].val));
                                        if(chartostring((yyvsp[-3].val))!="main")
                                        code.push_back("begin func "+curr_class+"_"+chartostring((yyvsp[-3].val)));
                                        else code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        reverse(ds2[curr3]["param"].begin(),ds2[curr3]["param"].end());
                                        for(auto i:ds2[curr3]["param"])
                                        code.push_back("pop param, "+ i);
                                        ds2[curr]["param"] = ds2[curr3]["param"];}
#line 5588 "parser_1st.tab.c"
    break;

  case 417: /* FORMALPARAMETERLIST: FORMALPARAMETER  */
#line 1883 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 5597 "parser_1st.tab.c"
    break;

  case 418: /* FORMALPARAMETERLIST: FORMALPARAMETERLIST COMMA FORMALPARAMETER  */
#line 1887 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 5607 "parser_1st.tab.c"
    break;

  case 419: /* FORMALPARAMETER: TYPE VARIABLEDECLARATORID  */
#line 1893 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 5616 "parser_1st.tab.c"
    break;

  case 421: /* FORMALPARAMETER: FINAL TYPE VARIABLEDECLARATORID  */
#line 1898 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 5625 "parser_1st.tab.c"
    break;

  case 424: /* METHODBODY: BLOCK  */
#line 1908 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 5631 "parser_1st.tab.c"
    break;

  case 428: /* BLOCK: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 1915 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); }
#line 5637 "parser_1st.tab.c"
    break;

  case 430: /* BLOCKSTATEMENTS: BLOCKSTATEMENT  */
#line 1918 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val); 
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
#line 5645 "parser_1st.tab.c"
    break;

  case 431: /* BLOCKSTATEMENTS: BLOCKSTATEMENTS BLOCKSTATEMENT  */
#line 1921 "parser_1st.y"
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
#line 5661 "parser_1st.tab.c"
    break;

  case 433: /* BLOCKSTATEMENT: STATEMENT  */
#line 1935 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); 
               }
#line 5668 "parser_1st.tab.c"
    break;

  case 435: /* LOCALVARIABLEDECLARATIONSTATEMENT: LOCALVARIABLEDECLARATION SEMICOLON  */
#line 1940 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 5674 "parser_1st.tab.c"
    break;

  case 436: /* LOCALVARIABLEDECLARATION: FINAL LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1942 "parser_1st.y"
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
                                type_check(yylineno, t,t2,"=");
                            }
                            // for(auto i:ds2[curr]["decl_code"])  // adding code for local decl only when 
                            // code.push_back(i);                  
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
#line 5733 "parser_1st.tab.c"
    break;

  case 437: /* LOCALVARIABLEDECLARATION: LOCALVARIABLETYPE VARIABLEDECLARATORLIST  */
#line 1996 "parser_1st.y"
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
                                type_check(yylineno, t,t2,"=");
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
#line 5793 "parser_1st.tab.c"
    break;

  case 438: /* LOCALVARIABLETYPE: TYPE  */
#line 2052 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 5799 "parser_1st.tab.c"
    break;

  case 439: /* LOCALVARIABLETYPE: VAR  */
#line 2053 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5805 "parser_1st.tab.c"
    break;

  case 440: /* STATEMENT: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 2056 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
#line 5811 "parser_1st.tab.c"
    break;

  case 441: /* STATEMENT: LABELEDSTATEMENT  */
#line 2057 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5817 "parser_1st.tab.c"
    break;

  case 442: /* STATEMENT: IFTHENSTATEMENT  */
#line 2058 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5823 "parser_1st.tab.c"
    break;

  case 443: /* STATEMENT: IFTHENELSESTATEMENT  */
#line 2059 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5829 "parser_1st.tab.c"
    break;

  case 444: /* STATEMENT: WHILESTATEMENT  */
#line 2060 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5835 "parser_1st.tab.c"
    break;

  case 445: /* STATEMENT: FORSTATEMENT  */
#line 2061 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5841 "parser_1st.tab.c"
    break;

  case 446: /* STATEMENT: PRINTLN OPENPARAN EXPRESSION CLOSEPARAN  */
#line 2062 "parser_1st.y"
                                                            {(yyval.val) = new_temp();int curr = chartonum((yyval.val));ds[curr]["start"] = ds[chartonum((yyvsp[-1].val))]["start"];code.push_back("print "+ ds[chartonum((yyvsp[-1].val))]["var"]);   }
#line 5847 "parser_1st.tab.c"
    break;

  case 447: /* STATEMENT: LOCALVARIABLEDECLARATIONSTATEMENT  */
#line 2063 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());
               }
#line 5854 "parser_1st.tab.c"
    break;

  case 448: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BLOCK  */
#line 2066 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5860 "parser_1st.tab.c"
    break;

  case 449: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EMPTYSTATEMENT  */
#line 2068 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5866 "parser_1st.tab.c"
    break;

  case 450: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: EXPRESSIONSTATEMENT  */
#line 2069 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5872 "parser_1st.tab.c"
    break;

  case 451: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: ASSERTSTATEMENT  */
#line 2070 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5878 "parser_1st.tab.c"
    break;

  case 452: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: BREAKSTATEMENT  */
#line 2071 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5884 "parser_1st.tab.c"
    break;

  case 453: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: CONTINUESTATEMENT  */
#line 2072 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5890 "parser_1st.tab.c"
    break;

  case 454: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: RETURNSTATEMENT  */
#line 2073 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5896 "parser_1st.tab.c"
    break;

  case 455: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: THROWSTATEMENT  */
#line 2074 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5902 "parser_1st.tab.c"
    break;

  case 456: /* STATEMENTWITHOUTTRAILINGSUBSTATEMENT: YIELDSTATEMENT  */
#line 2075 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5908 "parser_1st.tab.c"
    break;

  case 457: /* EMPTYSTATEMENT: SEMICOLON  */
#line 2077 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5914 "parser_1st.tab.c"
    break;

  case 458: /* EXPRESSIONSTATEMENT: STATEMENTEXPRESSION SEMICOLON  */
#line 2079 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val); }
#line 5920 "parser_1st.tab.c"
    break;

  case 459: /* STATEMENTEXPRESSION: ASSIGNMENT  */
#line 2081 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5926 "parser_1st.tab.c"
    break;

  case 460: /* STATEMENTEXPRESSION: PREINCREMENTEXPRESSION  */
#line 2082 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5932 "parser_1st.tab.c"
    break;

  case 461: /* STATEMENTEXPRESSION: PREDECREMENTEXPRESSION  */
#line 2083 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5938 "parser_1st.tab.c"
    break;

  case 462: /* STATEMENTEXPRESSION: POSTINCREMENTEXPRESSION  */
#line 2084 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5944 "parser_1st.tab.c"
    break;

  case 463: /* STATEMENTEXPRESSION: POSTDECREMENTEXPRESSION  */
#line 2085 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5950 "parser_1st.tab.c"
    break;

  case 464: /* STATEMENTEXPRESSION: METHODINVOCATION  */
#line 2086 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5956 "parser_1st.tab.c"
    break;

  case 465: /* STATEMENTEXPRESSION: CLASSINSTANCECREATIONEXPRESSION  */
#line 2087 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5962 "parser_1st.tab.c"
    break;

  case 468: /* BREAKSTATEMENT: BREAK SEMICOLON  */
#line 2092 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5975 "parser_1st.tab.c"
    break;

  case 470: /* CONTINUESTATEMENT: CONTINUE SEMICOLON  */
#line 2102 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5988 "parser_1st.tab.c"
    break;

  case 472: /* RETURNSTATEMENT: RETURN EXPRESSION SEMICOLON  */
#line 2112 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = ds[exp]["start"];
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5999 "parser_1st.tab.c"
    break;

  case 473: /* RETURNSTATEMENT: RETURN SEMICOLON  */
#line 2118 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 6010 "parser_1st.tab.c"
    break;

  case 477: /* IFTHENSTATEMENT: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 2131 "parser_1st.y"
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
#line 6031 "parser_1st.tab.c"
    break;

  case 478: /* IFTHENELSESTATEMENT: TEMP ELSE STATEMENT  */
#line 2148 "parser_1st.y"
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
#line 6050 "parser_1st.tab.c"
    break;

  case 479: /* IFTHENELSESTATEMENTNOSHORTIF: TEMP ELSE STATEMENTNOSHORTIF  */
#line 2163 "parser_1st.y"
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
#line 6081 "parser_1st.tab.c"
    break;

  case 480: /* TEMP: IF OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2190 "parser_1st.y"
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
#line 6097 "parser_1st.tab.c"
    break;

  case 481: /* STATEMENTNOSHORTIF: STATEMENTWITHOUTTRAILINGSUBSTATEMENT  */
#line 2202 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 6103 "parser_1st.tab.c"
    break;

  case 482: /* STATEMENTNOSHORTIF: LABELEDSTATEMENTNOSHORTIF  */
#line 2203 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 6109 "parser_1st.tab.c"
    break;

  case 483: /* STATEMENTNOSHORTIF: IFTHENELSESTATEMENTNOSHORTIF  */
#line 2204 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 6115 "parser_1st.tab.c"
    break;

  case 484: /* STATEMENTNOSHORTIF: WHILESTATEMENTNOSHORTIF  */
#line 2205 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 6121 "parser_1st.tab.c"
    break;

  case 485: /* STATEMENTNOSHORTIF: FORSTATEMENTNOSHORTIF  */
#line 2206 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 6127 "parser_1st.tab.c"
    break;

  case 487: /* WHILESTATEMENTNOSHORTIF: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2210 "parser_1st.y"
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
#line 6143 "parser_1st.tab.c"
    break;

  case 488: /* FORSTATEMENTNOSHORTIF: BASICFORSTATEMENTNOSHORTIF  */
#line 2222 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); popscope();}
#line 6149 "parser_1st.tab.c"
    break;

  case 489: /* FORSTATEMENTNOSHORTIF: ENHANCEDFORSTATEMENTNOSHORTIF  */
#line 2223 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 6155 "parser_1st.tab.c"
    break;

  case 490: /* WHILESTATEMENT: WHILE OPENPARAN EXPRESSION CLOSEPARAN STATEMENT  */
#line 2226 "parser_1st.y"
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
#line 6170 "parser_1st.tab.c"
    break;

  case 491: /* FORSTATEMENT: BASICFORSTATEMENT  */
#line 2237 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);popscope();}
#line 6176 "parser_1st.tab.c"
    break;

  case 492: /* FORSTATEMENT: ENHANCEDFORSTATEMENT  */
#line 2238 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 6182 "parser_1st.tab.c"
    break;

  case 493: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 2240 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6195 "parser_1st.tab.c"
    break;

  case 494: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2248 "parser_1st.y"
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
#line 6211 "parser_1st.tab.c"
    break;

  case 495: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2259 "parser_1st.y"
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
#line 6230 "parser_1st.tab.c"
    break;

  case 496: /* BASICFORSTATEMENT: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2273 "parser_1st.y"
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
#line 6251 "parser_1st.tab.c"
    break;

  case 497: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENT  */
#line 2289 "parser_1st.y"
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
#line 6269 "parser_1st.tab.c"
    break;

  case 498: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2302 "parser_1st.y"
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
#line 6290 "parser_1st.tab.c"
    break;

  case 499: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENT  */
#line 2318 "parser_1st.y"
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
#line 6311 "parser_1st.tab.c"
    break;

  case 500: /* BASICFORSTATEMENT: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENT  */
#line 2334 "parser_1st.y"
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
#line 6332 "parser_1st.tab.c"
    break;

  case 501: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2351 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp(); 
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6345 "parser_1st.tab.c"
    break;

  case 502: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2359 "parser_1st.y"
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
#line 6361 "parser_1st.tab.c"
    break;

  case 503: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2370 "parser_1st.y"
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
#line 6380 "parser_1st.tab.c"
    break;

  case 504: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2384 "parser_1st.y"
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
#line 6402 "parser_1st.tab.c"
    break;

  case 505: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2401 "parser_1st.y"
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
#line 6420 "parser_1st.tab.c"
    break;

  case 506: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2414 "parser_1st.y"
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
#line 6441 "parser_1st.tab.c"
    break;

  case 507: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2430 "parser_1st.y"
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
#line 6463 "parser_1st.tab.c"
    break;

  case 508: /* BASICFORSTATEMENTNOSHORTIF: FOR OPENPARAN FORINIT SEMICOLON EXPRESSION SEMICOLON FORUPDATE CLOSEPARAN STATEMENTNOSHORTIF  */
#line 2447 "parser_1st.y"
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
#line 6484 "parser_1st.tab.c"
    break;

  case 511: /* FORINIT: STATEMENTEXPRESSIONLIST  */
#line 2469 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 6490 "parser_1st.tab.c"
    break;

  case 512: /* FORINIT: LOCALVARIABLEDECLARATION  */
#line 2470 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 6496 "parser_1st.tab.c"
    break;

  case 513: /* FORUPDATE: STATEMENTEXPRESSIONLIST  */
#line 2472 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 6510 "parser_1st.tab.c"
    break;

  case 514: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSION  */
#line 2482 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 6516 "parser_1st.tab.c"
    break;

  case 515: /* STATEMENTEXPRESSIONLIST: STATEMENTEXPRESSIONLIST COMMA STATEMENTEXPRESSION  */
#line 2483 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 6528 "parser_1st.tab.c"
    break;

  case 517: /* CONSTRUCTORDECLARATION: CONSTRUCTORDECLARATOR CONSTRUCTORBODY  */
#line 2493 "parser_1st.y"
                                                                    {
                             (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    
    code.push_back("end func");
                        }
#line 6539 "parser_1st.tab.c"
    break;

  case 519: /* CONSTRUCTORDECLARATION: SUPER1 CONSTRUCTORDECLARATOR CONSTRUCTORBODY  */
#line 2500 "parser_1st.y"
                                                                         {
                             (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    
   
    code.push_back("end func");
                        }
#line 6551 "parser_1st.tab.c"
    break;

  case 520: /* CONSTRUCTORDECLARATOR: SIMPLETYPENAME OPENPARAN CLOSEPARAN  */
#line 2509 "parser_1st.y"
                                                           {
    tempnextscope();
    if(chartostring((yyvsp[-2].val))!=curr_class){
        cout<<"Error: invalid method declaration; return type required at line number "<<yylineno<<"\n"; exit(0);
    }
    auto  ttt = new constsig();
    constructors[chartostring((yyvsp[-2].val))].push_back(*ttt);

    (yyval.val) = new_temp();
    int curr = chartonum((yyval.val));              
    method_det[curr_class][chartostring((yyvsp[-2].val))].start = code.size(); 
    ds[curr]["start"] = numtostring(code.size());
    ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
    code.push_back("begin func "+chartostring((yyvsp[-2].val))+"_"+chartostring((yyvsp[-2].val)));
}
#line 6571 "parser_1st.tab.c"
    break;

  case 521: /* CONSTRUCTORDECLARATOR: SIMPLETYPENAME OPENPARAN FORMALPARAMETERLIST CLOSEPARAN  */
#line 2524 "parser_1st.y"
                                                                                {





// METHODHEADER: TYPE METHODDECLARATOR  { $$ = $2;  
tempnextscope(); 

//     methods[generalmap[$2].name].rettype = generalmap[$2].typ;
//     methods[generalmap[$2].name].lineno = yylineno;
    
//     vector <type> argtype;
     

//     for (auto x : generalmap[$2].farglist)
//         {argtype.push_back(x.typ);
//          }
//     methods[generalmap[$2].name].argtype = argtype;
//         classmethods[curr_class][generalmap[$2].name] = methods[generalmap[$2].name];

    




        





                        if(chartostring((yyvsp[-3].val))!=curr_class){
                            cout<<"Error: invalid method declaration; return type required at line number "<<yylineno<<"\n"; exit(0);
                        } (yyval.val) = new_temp();

                        generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)];

                        auto  ttt = new constsig();
                        for (auto x : generalmap[(yyvsp[-1].val)].farglist){
                            
                            ttt->argtype.push_back(x.typ);
                        }
                        
                        constructors[chartostring((yyvsp[-3].val))].push_back(*ttt);

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
        
        







                        int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                        method_det[curr_class][chartostring((yyvsp[-3].val))].start = code.size(); 
                        ds[curr]["start"] = numtostring(code.size());
                        ds[curr]["method_name"] = chartostring((yyvsp[-3].val));
                        code.push_back("begin func "+chartostring((yyvsp[-3].val))+"_"+chartostring((yyvsp[-3].val)));
                        reverse(ds2[curr3]["param"].begin(),ds2[curr3]["param"].end());
                        for(auto i:ds2[curr3]["param"])
                        code.push_back("pop param, "+ i);
                        // ds2[curr]["param"] = ds2[curr3]["param"];

                    }
#line 6664 "parser_1st.tab.c"
    break;

  case 531: /* CONSTRUCTORBODY: OPENCURLY BLOCKSTATEMENTS CLOSECURLY  */
#line 2624 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[-1].val);}
#line 6670 "parser_1st.tab.c"
    break;

  case 553: /* SUPER1: PUBLIC  */
#line 2648 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6676 "parser_1st.tab.c"
    break;

  case 554: /* SUPER1: PRIVATE  */
#line 2649 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6682 "parser_1st.tab.c"
    break;

  case 555: /* SUPER1: PROTECTED  */
#line 2650 "parser_1st.y"
                    {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6688 "parser_1st.tab.c"
    break;

  case 556: /* SUPER1: SUPER1 PUBLIC  */
#line 2651 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6694 "parser_1st.tab.c"
    break;

  case 557: /* SUPER1: SUPER1 PRIVATE  */
#line 2652 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6700 "parser_1st.tab.c"
    break;

  case 558: /* SUPER1: SUPER1 PROTECTED  */
#line 2653 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6706 "parser_1st.tab.c"
    break;

  case 559: /* SUPER2: STATIC  */
#line 2655 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6712 "parser_1st.tab.c"
    break;

  case 560: /* SUPER2: FINAL  */
#line 2656 "parser_1st.y"
                 {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6718 "parser_1st.tab.c"
    break;

  case 561: /* SUPER2: SUPER1 STATIC  */
#line 2657 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6724 "parser_1st.tab.c"
    break;

  case 562: /* SUPER2: SUPER1 FINAL  */
#line 2658 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6730 "parser_1st.tab.c"
    break;

  case 563: /* SUPER2: SUPER2 STATIC  */
#line 2659 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6736 "parser_1st.tab.c"
    break;

  case 564: /* SUPER2: SUPER2 FINAL  */
#line 2660 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6742 "parser_1st.tab.c"
    break;

  case 565: /* SUPER2: SUPER2 PUBLIC  */
#line 2661 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6748 "parser_1st.tab.c"
    break;

  case 566: /* SUPER2: SUPER2 PRIVATE  */
#line 2662 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6754 "parser_1st.tab.c"
    break;

  case 567: /* SUPER2: SUPER2 PROTECTED  */
#line 2663 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6760 "parser_1st.tab.c"
    break;

  case 568: /* SUPER3: ABSTRACT  */
#line 2665 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6766 "parser_1st.tab.c"
    break;

  case 569: /* SUPER3: STRICTFP  */
#line 2666 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6772 "parser_1st.tab.c"
    break;

  case 570: /* SUPER3: SUPER2 ABSTRACT  */
#line 2667 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6778 "parser_1st.tab.c"
    break;

  case 571: /* SUPER3: SUPER2 STRICTFP  */
#line 2668 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6784 "parser_1st.tab.c"
    break;

  case 572: /* SUPER3: SUPER3 ABSTRACT  */
#line 2669 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6790 "parser_1st.tab.c"
    break;

  case 573: /* SUPER3: SUPER3 STRICTFP  */
#line 2670 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6796 "parser_1st.tab.c"
    break;

  case 574: /* SUPER3: SUPER3 PUBLIC  */
#line 2671 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6802 "parser_1st.tab.c"
    break;

  case 575: /* SUPER3: SUPER3 PRIVATE  */
#line 2672 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6808 "parser_1st.tab.c"
    break;

  case 576: /* SUPER3: SUPER3 PROTECTED  */
#line 2673 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6814 "parser_1st.tab.c"
    break;

  case 577: /* SUPER3: SUPER3 STATIC  */
#line 2674 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6820 "parser_1st.tab.c"
    break;

  case 578: /* SUPER3: SUPER3 FINAL  */
#line 2675 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6826 "parser_1st.tab.c"
    break;

  case 579: /* FIELDMODIFIERS: SUPER3 TRANSIENT  */
#line 2677 "parser_1st.y"
                                 {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6832 "parser_1st.tab.c"
    break;

  case 580: /* FIELDMODIFIERS: SUPER3 VOLATILE  */
#line 2678 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6838 "parser_1st.tab.c"
    break;

  case 581: /* FIELDMODIFIERS: FIELDMODIFIERS TRANSIENT  */
#line 2679 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6844 "parser_1st.tab.c"
    break;

  case 582: /* FIELDMODIFIERS: FIELDMODIFIERS VOLATILE  */
#line 2680 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6850 "parser_1st.tab.c"
    break;

  case 583: /* FIELDMODIFIERS: FIELDMODIFIERS PUBLIC  */
#line 2681 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6856 "parser_1st.tab.c"
    break;

  case 584: /* FIELDMODIFIERS: FIELDMODIFIERS PRIVATE  */
#line 2682 "parser_1st.y"
                                     {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6862 "parser_1st.tab.c"
    break;

  case 585: /* FIELDMODIFIERS: FIELDMODIFIERS PROTECTED  */
#line 2683 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6868 "parser_1st.tab.c"
    break;

  case 586: /* FIELDMODIFIERS: FIELDMODIFIERS STATIC  */
#line 2684 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6874 "parser_1st.tab.c"
    break;

  case 587: /* FIELDMODIFIERS: FIELDMODIFIERS FINAL  */
#line 2685 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6880 "parser_1st.tab.c"
    break;

  case 588: /* METHODMODIFIERS: SUPER3 SYNCHRONIZED  */
#line 2688 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6886 "parser_1st.tab.c"
    break;

  case 589: /* METHODMODIFIERS: SUPER3 NATIVE  */
#line 2689 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6892 "parser_1st.tab.c"
    break;

  case 590: /* METHODMODIFIERS: METHODMODIFIERS SYNCHRONIZED  */
#line 2690 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6898 "parser_1st.tab.c"
    break;

  case 591: /* METHODMODIFIERS: METHODMODIFIERS NATIVE  */
#line 2691 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6904 "parser_1st.tab.c"
    break;

  case 592: /* METHODMODIFIERS: METHODMODIFIERS ABSTRACT  */
#line 2692 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6910 "parser_1st.tab.c"
    break;

  case 593: /* METHODMODIFIERS: METHODMODIFIERS STRICTFP  */
#line 2693 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6916 "parser_1st.tab.c"
    break;

  case 594: /* METHODMODIFIERS: METHODMODIFIERS PUBLIC  */
#line 2694 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6922 "parser_1st.tab.c"
    break;

  case 595: /* METHODMODIFIERS: METHODMODIFIERS PRIVATE  */
#line 2695 "parser_1st.y"
                                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6928 "parser_1st.tab.c"
    break;

  case 596: /* METHODMODIFIERS: METHODMODIFIERS PROTECTED  */
#line 2696 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6934 "parser_1st.tab.c"
    break;

  case 597: /* METHODMODIFIERS: METHODMODIFIERS STATIC  */
#line 2697 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6940 "parser_1st.tab.c"
    break;

  case 598: /* METHODMODIFIERS: METHODMODIFIERS FINAL  */
#line 2698 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6946 "parser_1st.tab.c"
    break;

  case 602: /* TYPEARGUMENT: REFERENCETYPE  */
#line 2705 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 6952 "parser_1st.tab.c"
    break;

  case 603: /* TYPEARGUMENT: WILDCARD  */
#line 2706 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 6958 "parser_1st.tab.c"
    break;

  case 608: /* INTERFACETYPE: CLASSTYPE  */
#line 2715 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 6964 "parser_1st.tab.c"
    break;


#line 6968 "parser_1st.tab.c"

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

#line 2717 "parser_1st.y"



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
