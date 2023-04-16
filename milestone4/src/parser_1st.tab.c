/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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

    


    

#line 280 "parser_1st.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_1ST_TAB_H_INCLUDED
# define YY_YY_PARSER_1ST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOLEAN = 258,
    BYTE = 259,
    SHORT = 260,
    INT = 261,
    LONG = 262,
    CHAR = 263,
    FLOAT = 264,
    DOUBLE = 265,
    COMMA = 266,
    QUESTIONMARK = 267,
    SEMICOLON = 268,
    OPENCURLY1 = 269,
    CLOSECURLY1 = 270,
    ANGULARLEFT = 271,
    ANGULARRIGHT = 272,
    OPENSQUARE = 273,
    CLOSESQUARE = 274,
    OPENPARAN = 275,
    CLOSEPARAN = 276,
    DOUBLECOLON = 277,
    TRIPLEDOT = 278,
    WS = 279,
    AT = 280,
    OVERRIDE = 281,
    EQUALS = 282,
    MULTIPLYEQUALS = 283,
    DIVIDEEQUALS = 284,
    MODEQUALS = 285,
    PLUSEQUALS = 286,
    MINUSEQUALS = 287,
    PLUS = 288,
    MINUS = 289,
    DIVIDE = 290,
    MULTIPLY = 291,
    MOD = 292,
    OR = 293,
    XOR = 294,
    COLON = 295,
    NOT = 296,
    COMPLEMENT = 297,
    AND = 298,
    DOT = 299,
    OROR = 300,
    ANDAND = 301,
    PLUSPLUS = 302,
    MINUSMINUS = 303,
    ANGULARLEFTANGULARLEFT = 304,
    ANGULARRIGHTANGULARRIGHT = 305,
    ANGULARRIGHTANGULARRIGHTANGULARRIGHT = 306,
    EQUALSEQUALS = 307,
    NOTEQUALS = 308,
    INTEGERLITERAL = 309,
    FLOATINGPOINTLITERAL = 310,
    BOOLEANLITERAL = 311,
    CHARACTERLITERAL = 312,
    STRINGLITERAL = 313,
    TEXTBLOCK = 314,
    NULLLITERAL = 315,
    EXTENDS = 316,
    SUPER = 317,
    CLASS = 318,
    PUBLIC = 319,
    PRIVATE = 320,
    IMPLEMENTS = 321,
    PERMITS = 322,
    PROTECTED = 323,
    STATIC = 324,
    FINAL = 325,
    TRANSIENT = 326,
    VOLATILE = 327,
    INSTANCEOF = 328,
    THIS = 329,
    VOID = 330,
    NEW = 331,
    THROW = 332,
    ASSERT = 333,
    VAR = 334,
    BREAK = 335,
    CONTINUE = 336,
    RETURN = 337,
    YIELD = 338,
    IF = 339,
    ELSE = 340,
    WHILE = 341,
    FOR1 = 342,
    PRINTLN = 343,
    ABSTRACT = 344,
    SYNCHRONIZED = 345,
    NATIVE = 346,
    STRICTFP = 347,
    SWITCH = 348,
    DEFAULT = 349,
    PACKAGE = 350,
    DO = 351,
    GOTO = 352,
    IMPORT = 353,
    THROWS = 354,
    CASE = 355,
    ENUM = 356,
    CATCH = 357,
    TRY = 358,
    INTERFACE = 359,
    FINALLY = 360,
    CONST = 361,
    UNDERSCORE = 362,
    EXPORTS = 363,
    OPENS = 364,
    REQUIRES = 365,
    USES = 366,
    MODULE = 367,
    SEALED = 368,
    PROVIDES = 369,
    TO = 370,
    WITH = 371,
    OPEN = 372,
    RECORD = 373,
    TRANSITIVE = 374,
    ERROR = 375,
    ONCE = 376,
    NL = 377,
    NON_SEALED = 378,
    IDENTIFIER = 379,
    UNQUALIFIEDMETHODIDENTIFIER = 380,
    DOTCLASS = 381,
    EOFF = 382
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 210 "parser_1st.y"

    char* val;

#line 464 "parser_1st.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_1ST_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYLAST   6100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  128
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  155
/* YYNRULES -- Number of rules.  */
#define YYNRULES  608
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1148

#define YYUNDEFTOK  2
#define YYMAXUTOK   382


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
    1711,  1714,  1725,  1726,  1729,  1731,  1733,  1735,  1737,  1794,
    1856,  1857,  1860,  1861,  1862,  1863,  1864,  1865,  1867,  1869,
    1870,  1871,  1872,  1873,  1874,  1875,  1876,  1878,  1880,  1882,
    1883,  1884,  1885,  1886,  1887,  1888,  1890,  1891,  1893,  1901,
    1903,  1911,  1913,  1919,  1926,  1928,  1930,  1932,  1949,  1964,
    1991,  2003,  2004,  2005,  2006,  2007,  2009,  2011,  2023,  2024,
    2027,  2038,  2039,  2041,  2049,  2060,  2074,  2090,  2103,  2119,
    2135,  2152,  2160,  2171,  2185,  2202,  2215,  2231,  2248,  2266,
    2268,  2270,  2271,  2273,  2283,  2284,  2293,  2294,  2295,  2296,
    2299,  2300,  2301,  2302,  2303,  2304,  2305,  2306,  2309,  2311,
    2312,  2313,  2314,  2316,  2317,  2318,  2319,  2320,  2321,  2322,
    2323,  2324,  2325,  2326,  2327,  2328,  2329,  2330,  2331,  2332,
    2333,  2334,  2335,  2337,  2338,  2339,  2340,  2341,  2342,  2344,
    2345,  2346,  2347,  2348,  2349,  2350,  2351,  2352,  2354,  2355,
    2356,  2357,  2358,  2359,  2360,  2361,  2362,  2363,  2364,  2366,
    2367,  2368,  2369,  2370,  2371,  2372,  2373,  2374,  2377,  2378,
    2379,  2380,  2381,  2382,  2383,  2384,  2385,  2386,  2387,  2389,
    2391,  2392,  2394,  2395,  2397,  2398,  2400,  2401,  2404
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOLEAN", "BYTE", "SHORT", "INT",
  "LONG", "CHAR", "FLOAT", "DOUBLE", "COMMA", "QUESTIONMARK", "SEMICOLON",
  "OPENCURLY1", "CLOSECURLY1", "ANGULARLEFT", "ANGULARRIGHT", "OPENSQUARE",
  "CLOSESQUARE", "OPENPARAN", "CLOSEPARAN", "DOUBLECOLON", "TRIPLEDOT",
  "WS", "AT", "OVERRIDE", "EQUALS", "MULTIPLYEQUALS", "DIVIDEEQUALS",
  "MODEQUALS", "PLUSEQUALS", "MINUSEQUALS", "PLUS", "MINUS", "DIVIDE",
  "MULTIPLY", "MOD", "OR", "XOR", "COLON", "NOT", "COMPLEMENT", "AND",
  "DOT", "OROR", "ANDAND", "PLUSPLUS", "MINUSMINUS",
  "ANGULARLEFTANGULARLEFT", "ANGULARRIGHTANGULARRIGHT",
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
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382
};
# endif

#define YYPACT_NINF (-798)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-529)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     732,  -798,   -55,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
      95,   -24,  -798,   167,  1966,  -798,  2146,  -798,  -798,  -798,
    -798,   395,  1397,  2195,   346,   115,   137,   235,    47,   377,
    -798,  -798,  -798,  -798,   166,  -798,  -798,  -798,  -798,  -798,
     211,   227,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   246,
     266,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   278,   284,
     297,   297,   304,   288,   259,   149,   115,  -798,  1540,  -798,
     192,   338,  -798,     0,  5976,  -798,   288,   259,   149,   115,
     346,   115,   377,   346,   115,   377,   346,   115,   377,   407,
      53,  -798,  -798,  -798,  -798,  -798,   305,  -798,  -798,   345,
     259,   149,   115,  -798,   149,   115,  -798,   115,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
     445,   115,   351,   462,   364,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  3347,  -798,  -798,   974,  1540,  -798,  -798,
    -798,  -798,   419,  -798,  -798,  -798,  -798,    67,   475,  4344,
    3729,  5643,  1305,  3975,  -798,    50,  -798,   510,  -798,  -798,
     871,   351,  -798,  -798,  5976,  -798,  1120,  -798,  4724,  4221,
    3606,  -798,   259,   149,   115,  -798,   149,   115,  -798,   115,
    -798,   288,   259,   149,   115,  -798,  -798,   288,   259,   149,
     115,   288,   259,   149,   115,  -798,  -798,   288,   259,   149,
     115,   288,   259,   149,   115,  -798,  -798,   288,   259,   149,
     115,   443,  -798,   284,  -798,   297,   449,   149,   115,  -798,
     115,  -798,  -798,   115,  -798,  -798,  -798,  4478,  -798,  1220,
     485,   886,   286,  -798,   566,   485,    26,  -798,  5564,  5624,
    5624,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   205,  1844,
    -798,   478,  1716,  5564,  5564,  -798,    17,    25,  3522,  5564,
     587,   593,  -798,  -798,  1663,  -798,    56,   599,   596,  1631,
    -798,   609,  -798,  -798,  1113,  1132,   232,   624,  -798,  -798,
     403,  -798,   491,  -798,  -798,  1154,  -798,  -798,   453,   460,
     481,  -798,  3347,  -798,  -798,  -798,   632,   537,  -798,  -798,
    -798,  -798,   635,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,   572,  -798,  -798,  -798,  -798,   683,   965,  1499,
     351,   351,   650,  -798,  -798,  -798,  -798,  -798,   297,  3203,
     115,  -798,  1320,   364,   419,    67,   364,   419,  -798,  -798,
    -798,  -798,   419,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
     537,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,
     419,   661,  -798,   419,  -798,  -798,   364,  -798,   149,   115,
    -798,   115,  -798,  -798,   115,  -798,  -798,   259,   149,   115,
    -798,   149,   115,  -798,   115,  -798,  -798,  -798,   259,   149,
     115,  -798,   149,   115,  -798,   115,  -798,   259,   149,   115,
    -798,   149,   115,  -798,   115,  -798,  -798,  -798,   259,   149,
     115,  -798,   149,   115,  -798,   115,  -798,   259,   149,   115,
    -798,   149,   115,  -798,   115,  -798,  -798,  -798,   259,   149,
     115,  -798,   149,   115,  -798,   115,  -798,   633,   644,  -798,
    -798,  -798,   115,  -798,  -798,  -798,  -798,   419,  1874,  4601,
    4098,  3975,  1401,   129,   680,  -798,   674,   677,   537,  -798,
    3585,  -798,   684,  -798,    70,    26,  5624,  5624,  5624,  5624,
    1988,    56,   599,   690,  -798,  -798,  -798,  -798,  -798,    39,
     658,   676,   678,   672,   584,   241,   575,   631,   604,  -798,
    -798,  -798,  -798,   453,  -798,  -798,  -798,   169,    28,  -798,
    -798,  -798,  -798,    59,   101,   537,  -798,    10,   699,   705,
     705,   706,   606,   712,   184,  -798,   715,  -798,   721,  -798,
     724,   727,  5564,  5564,  3645,  2405,    27,  -798,   102,  -798,
     139,     9,  3708,  5564,    52,  2739,  -798,  -798,  -798,  -798,
    -798,  -798,  5564,   186,   172,  5564,  -798,  -798,  -798,  -798,
    -798,   725,   733,  -798,  2405,   485,   485,  1502,  -798,   739,
    -798,   321,   736,  1845,   405,  -798,   247,  3347,  3347,   255,
    -798,  -798,  1852,   264,   748,   337,  -798,  -798,   509,  -798,
     115,  -798,   539,  -798,  -798,   557,  -798,  -798,  -798,   577,
    -798,   115,  -798,  -798,  -798,   149,   115,  -798,   115,  -798,
    -798,   115,  -798,  -798,  -798,  -798,   149,   115,  -798,   115,
    -798,  -798,   115,  -798,  -798,   149,   115,  -798,   115,  -798,
    -798,   115,  -798,  -798,  -798,  -798,   149,   115,  -798,   115,
    -798,  -798,   115,  -798,  -798,   149,   115,  -798,   115,  -798,
    -798,   115,  -798,  -798,  -798,  -798,   149,   115,  -798,   115,
    -798,  -798,   115,  -798,  -798,   297,   719,  -798,  -798,   419,
     419,   419,   419,   725,    38,   371,  -798,   720,   745,  -798,
     750,  -798,  2603,  -798,  -798,  -798,  -798,   754,  -798,  -798,
    -798,  -798,  -798,  -798,  5564,  5624,  5624,  5624,  5624,  5624,
    5624,  5624,  3768,  3831,   297,  5624,  5624,  5624,  5624,  5624,
    5624,  5624,  5624,  -798,   651,   756,   656,   733,   617,  -798,
     319,  -798,  -798,  3891,   359,   705,  -798,   359,   705,  3954,
    -798,   757,  -798,  -798,  5564,  -798,  -798,  -798,  -798,   761,
     762,   765,  -798,   300,  -798,   194,   766,  -798,   664,  -798,
    -798,  -798,  -798,   -34,  -798,  -798,   418,   770,   773,  -798,
     666,  4014,  1844,   758,  -798,   772,   788,  -798,  -798,   679,
     786,  -798,   685,   791,  -798,  -798,  -798,  -798,   800,   424,
     297,  4077,  4137,   295,    61,    77,  -798,  -798,  3347,   794,
     795,   132,   694,   244,  -798,  1577,  1751,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,   115,  -798,  -798,  -798,  -798,  -798,
     115,  -798,  -798,  -798,   115,  -798,  -798,  -798,  -798,  -798,
     115,  -798,  -798,  -798,   115,  -798,  -798,  -798,  -798,  -798,
     115,  -798,  -798,  -798,  -798,   297,  -798,  -798,  -798,  -798,
     677,   725,   746,  1647,  -798,  -798,  -798,  -798,   804,   812,
    -798,   785,   658,   676,   678,   672,   584,   241,   241,  5624,
     575,  5624,   575,  -798,   631,   631,   631,   604,   604,  -798,
    -798,  -798,  -798,  4200,   806,   297,   297,  -798,    10,  -798,
     808,  -798,   677,  -798,  -798,   677,   115,   429,  4260,   815,
    3437,  2405,  -798,   195,   196,  4323,   813,  -798,  -798,  5564,
    -798,  -798,  4383,   817,  2271,   822,  5564,  4457,  2772,  -798,
    4517,   819,  -798,  1683,  -798,  -798,   829,   435,   832,   459,
     365,   -17,   826,    76,   827,   183,  -798,  4580,  4640,   731,
    -798,  -798,  -798,   463,  -798,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,   677,  -798,   725,   498,  -798,  3585,  5624,   575,
     575,  -798,   513,  4703,  -798,  -798,  -798,  -798,  -798,   115,
     115,   515,  -798,   828,   946,   836,  -798,   777,  -798,   779,
    -798,  -798,  -798,  -798,  -798,  -798,  -798,  -798,   741,   837,
     742,  -798,   516,  4763,  -798,  -798,   524,  4826,  2405,   848,
     788,  5716,   849,  5748,   858,  -798,  -798,   533,  4886,  -798,
     535,  -798,   860,  -798,   869,  4949,   863,  5009,   864,  5072,
     868,   884,   536,   888,   538,  -798,  -798,   677,   725,  -798,
    -798,  -798,  -798,   542,  -798,  -798,   115,  5564,  3437,  3004,
    3437,  -798,  5132,   882,  -798,  -798,   544,  -798,  -798,   550,
    -798,  2405,  2405,   889,  2405,  2405,   892,  5779,  -798,  -798,
     553,  -798,  -798,  -798,   890,   555,  5195,   894,   561,  5255,
     896,   568,  5318,  -798,   914,  -798,   923,   677,  -798,  -798,
     916,  -798,  5378,   865,   925,  -798,  -798,   570,  5441,  -798,
    -798,  -798,  -798,  2405,  -798,  -798,  2405,  2405,   918,  -798,
    -798,   929,   930,   585,  -798,   931,   932,   594,  -798,   934,
     935,   598,  -798,  -798,  3437,  5809,   937,  5564,  5501,  -798,
    -798,   601,  -798,  -798,  -798,  2405,  -798,  -798,   938,  -798,
    -798,   939,  -798,  -798,   942,  -798,  3437,   940,  5839,   941,
    5870,   947,  -798,  -798,  -798,  -798,  -798,  -798,  3437,  3437,
     948,  3437,  3437,   949,  5902,  -798,  -798,  3437,  -798,  -798,
    3437,  3437,   950,  -798,  -798,  -798,  3437,  -798
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
     241,     0,     0,     0,     0,   441,     0,     0,     0,     0,
       0,     0,   166,   435,   225,   440,     6,    18,     0,   378,
     436,     0,   429,   459,     0,   245,   377,   237,   239,   240,
     244,   265,   247,   248,   238,   246,   460,   461,     0,   462,
     463,   448,     0,   430,   432,   433,     0,     0,   434,   442,
     449,   450,     0,   451,   452,   453,   454,   455,   456,   443,
     444,   445,     0,   446,   447,   491,   492,     0,     0,     0,
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
     437,   216,   439,   458,     0,   402,   399,     0,   406,   403,
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
       0,     0,     0,   309,     0,   235,     0,   438,   604,   602,
       0,   600,   603,     0,   318,   316,   327,   319,   317,     0,
     277,     0,   474,   466,     0,   469,   471,   472,   475,     0,
       0,     0,   476,     0,   242,     0,    24,   267,     0,   260,
     261,   311,   307,     0,   280,   278,     0,     0,    25,   266,
       0,     0,     0,   512,   514,     0,   511,   223,   308,     0,
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
     273,     0,   467,     0,   225,     0,   477,   442,   483,     0,
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
    -798,  -798,  1645,   707,   -54,  -798,  -798,  -490,  -131,  1939,
    -798,  -498,  -798,  1229,  -798,   646,  -798,    57,  -798,   376,
    -798,  -460,   -29,   -70,  2497,  -798,   799,   -28,  1122,  -798,
     759,  -798,  -798,   653,  2169,  -798,  2773,  -798,  2120,  -798,
     830,  -798,  -798,  -231,   518,  -542,  -665,  -230,  -798,  -120,
    -798,  -798,   233,   663,  -798,  -798,  -798,  -201,    60,  -507,
     461,  2050,   138,  -798,  -798,  -248,  -798,   477,  -229,  -798,
    1050,    63,  -798,   312,   313,   317,   325,   326,    -7,  -659,
     -42,    -9,  -185,   318,   502,  -798,   696,   928,  1006,  -798,
     -22,    82,  -209,  -798,   237,   -35,  -314,  -411,   230,  -798,
    -119,  -798,  -798,   -10,  -313,  -287,  -798,  -798,  -532,  -247,
     287,  -419,  -798,  -798,  -526,  -798,  -798,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -374,  -324,  -798,  -798,  -798,
    -798,  -798,  -798,  -798,  -798,  -798,     3,  -797,  -529,  -798,
     874,   895,  -320,  -798,    62,   140,   411,  -798,   797,  -297,
    -798,   171,  -798,  -798,  -214
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,   161,   125,   471,   127,   128,   129,   130,   472,
      94,   457,   268,   269,    14,    15,    16,   270,    18,    25,
      19,   271,    68,   134,    75,   164,   165,    20,   166,    90,
      91,   212,   656,    64,    65,    96,    66,    99,    69,   137,
     138,   139,   140,   232,   233,   234,   673,   745,   474,   475,
     274,   542,   275,   276,   277,   278,   279,   528,   476,   281,
     511,   746,   477,   283,   284,   675,   838,   715,   716,   839,
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
      74,   440,   505,   753,   163,   549,   756,   837,   473,   754,
     570,   714,   717,   273,   126,   581,   567,   709,   574,   737,
     126,   455,   708,   513,   514,   507,   461,   749,   520,   521,
     515,   784,   569,   850,   852,   464,   157,   761,   517,   133,
     135,   665,   887,   507,   462,   996,   533,    74,    74,    74,
      74,   684,   167,    74,   501,   502,    74,    17,   145,    74,
      72,   782,    21,   272,   213,   530,   552,   323,   507,    24,
     214,    17,   534,    17,   462,   507,    21,   507,    21,   266,
     438,    67,   126,   126,   685,   741,   361,   230,   677,   733,
     888,    73,   133,   507,   364,   126,   126,   126,   126,   126,
      29,   734,   578,   735,   133,   582,   126,   886,   133,   135,
     126,   228,   126,   133,   126,   126,   126,   507,   329,   585,
     677,   510,   784,   912,   158,   132,   580,   145,   735,    67,
     149,   162,   327,   742,    92,   589,   168,   735,   998,   914,
      22,   516,   167,    74,    74,    74,   769,    74,    74,   518,
      74,   736,   463,   735,    22,   919,    22,   677,    74,    74,
      74,    74,   551,    67,    26,   830,   328,    30,    74,    74,
      74,    74,   273,   126,   158,   126,   748,   126,    74,    74,
      74,    74,   529,   703,  1033,   748,  1036,   524,   507,   -23,
     939,   -20,   940,   280,   132,   126,   678,   723,   126,   149,
     893,   760,   507,   666,   853,   154,   704,   706,   150,   273,
     507,   507,   507,   526,   169,   579,    62,   872,   583,    27,
     875,   162,   548,   584,   724,   705,   168,   503,   739,   738,
     674,   334,   337,   342,   743,   360,   155,   750,   266,   920,
    1078,   586,   363,   768,   588,  1000,   759,   762,   735,   504,
     334,   337,   342,   667,   543,   778,   551,   692,   693,   565,
     789,    27,   456,   133,   464,   740,   737,   749,   761,   543,
     530,   282,  1009,    67,   707,   266,   544,   150,   126,    71,
     549,   679,   680,   681,   682,   555,   556,   782,   832,   448,
      80,   775,   729,   730,   731,   527,   760,   458,  1117,   459,
     133,   329,    67,   747,   169,   133,   329,   901,   133,   447,
     758,   507,   757,   133,   694,   763,   215,   779,   720,   967,
     969,  1130,   883,  1133,   327,    61,    62,   327,   658,   780,
     868,   133,   327,   932,   133,    82,   869,  1142,   666,    74,
      74,   771,    74,   503,   884,    74,   765,   766,   786,    60,
     327,    83,   280,   327,    61,    62,   216,   910,   787,    74,
      74,    74,    59,    74,    74,   504,    74,   449,   754,   734,
      85,   735,   985,    67,   923,   944,   945,   670,   709,    74,
      74,    74,   786,    74,    74,   995,    74,   883,   783,   280,
      86,    67,   831,    59,   126,   126,   126,   126,   126,    74,
      74,    74,    88,    74,    74,   273,    74,    60,    89,   884,
      81,    23,    61,    62,  -465,   273,  -465,    84,   133,   736,
     955,    92,   935,   533,  -465,    23,    87,    23,    98,   889,
     282,   672,   325,    67,   273,   786,  1007,   327,    60,   890,
     889,   824,   674,    61,    62,   904,   889,   273,   273,   774,
     949,   286,  -378,  -378,   841,   754,   992,   754,    34,    35,
      36,   957,   156,    37,    38,    39,   871,   282,   211,   874,
     889,   227,   499,   499,   786,   229,   911,   913,   915,   151,
     994,   266,  -528,   870,  1006,   170,   873,  1063,   231,   873,
     756,   549,   990,   754,   879,   332,   133,   776,   777,    40,
     546,   547,  -464,   126,  -464,   505,   959,  -380,  -380,   786,
    1057,   754,  -464,   266,   266,   859,   860,   861,   126,  1008,
     458,   895,   788,   362,   889,   133,   889,   889,  -381,  -381,
     659,   660,   661,   662,  1011,   889,  1016,  1024,   133,   133,
     826,   827,   828,   829,   889,  1027,   786,   889,   151,   889,
     458,   329,   790,   889,  1038,   889,  1041,  1054,   955,  1056,
     955,   889,    74,  1058,   889,  1069,   889,   437,   458,   754,
     791,  1070,   889,   441,  1079,   170,  1081,    74,    74,   889,
      74,   889,  1085,    74,   328,   280,   968,   970,   458,  1089,
     792,  1099,   754,   460,   754,   280,   889,    74,    74,   957,
      74,   957,   836,    74,   506,   889,  1108,   522,   754,   889,
     286,   931,   889,   523,   280,  1111,   532,    74,    74,  1114,
      74,   531,  1122,    74,   695,   696,   697,   280,   280,   535,
     133,   133,   133,   133,   955,   287,   690,   691,   450,   700,
     701,   702,   545,   672,   959,   550,   959,   286,   553,   327,
     327,   327,   327,   854,   855,   856,   955,   554,   273,   974,
      32,   551,    33,   282,   698,   699,   982,   984,   955,   955,
     557,   955,   955,   282,   587,   957,   -20,   955,   865,   866,
     955,   955,    77,   847,   848,   672,   955,   655,   672,   857,
     858,   668,   282,   669,  1061,   670,  1065,   957,   126,   499,
     499,   499,   499,   676,   686,   282,   282,   674,   916,   957,
     957,   683,   957,   957,   687,   689,   100,   688,   957,  -277,
     959,   957,   957,   713,   266,   722,   719,   957,   725,   172,
     720,   126,   126,   182,   726,   188,   192,   727,   198,   202,
     728,   208,   959,   456,   458,     1,    34,    35,    36,   133,
     770,    37,    38,    39,   959,   959,   772,   959,   959,   785,
     273,   273,   825,   959,   832,   833,   959,   959,   936,   834,
    1115,    74,   959,   840,   273,   862,   863,   878,   273,   126,
     864,    74,   880,   881,   882,   897,   885,  1060,   886,   891,
     893,    74,  1127,   892,   287,     2,     3,     4,   896,   898,
       5,     6,     7,   899,  1135,  1136,   900,  1138,  1139,   901,
     902,   903,   732,  1143,   917,   918,  1144,  1145,   921,   119,
     933,     8,  1147,   937,     9,   938,   943,   947,   952,   288,
      10,   287,  1096,   973,   377,   981,    11,   977,   280,   988,
     388,   764,   991,   286,   397,   993,   997,   999,  1017,   126,
     408,   133,   133,   286,   417,  1005,  1019,  1022,   273,    12,
     428,   273,  -481,   273,  1020,  1021,  1023,  1119,  1121,  1031,
    1034,  1037,   286,  1042,   110,   111,   112,   113,   114,   115,
     116,   117,  1043,  1046,  1049,   286,   286,    59,  1052,   110,
     111,   112,   113,   114,   115,   116,   117,  1053,   273,   273,
     273,  1055,  1068,  1080,   456,  1097,   452,  1084,   672,  1088,
    1073,   273,   273,  1076,   273,   273,   282,   273,   499,   499,
     499,   499,   499,   499,   499,   499,   499,  1092,   499,   499,
     499,   499,   499,   499,   499,   499,  1093,  1094,  1098,  1105,
     280,   280,  1106,  1107,  1109,  1110,   122,  1112,  1113,   133,
    1118,  1124,  1125,   273,   280,  1126,   273,   273,   280,   509,
    1134,  1128,  1131,   365,   524,   266,   -23,   324,   -20,  1137,
    1140,  1146,   439,   721,   273,   273,   671,   110,   111,   112,
     113,   114,   115,   116,   117,   273,  1018,   718,   288,   133,
     526,   133,   566,  -379,  -379,    92,   273,   842,   273,   843,
     273,  1010,   133,   133,   844,   133,   133,   905,   273,   273,
      92,   273,   273,   845,   273,   846,   924,   273,   282,   282,
     273,   273,  1064,   335,   451,   288,   273,   287,    41,    42,
      43,   322,   282,    44,    45,    46,   282,   287,   280,   946,
       0,   280,     0,   280,   133,     0,     0,   133,   133,   320,
       0,     0,     0,     0,    47,     0,   287,    48,     0,     0,
       0,   289,     0,     0,     0,   133,     0,     0,     0,   287,
     287,     0,   527,     0,     0,     0,   133,     0,   280,   280,
     280,     0,   499,     0,   499,     0,     0,   133,     0,     0,
       0,   280,   280,     0,   280,   280,   286,   280,   123,   133,
     133,     0,   133,   133,     0,     0,     0,     0,   133,     0,
       0,   133,   133,     0,     0,     0,   282,   133,     0,   282,
       0,   282,     0,   110,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   280,     0,     0,   280,   280,     0,   290,
     536,   537,   538,   539,   540,   541,    63,     0,     0,     0,
       0,    76,     0,     0,   280,   280,   282,   282,   282,  -226,
    -226,  -226,  -226,  -226,  -226,   280,     0,   956,   966,   282,
     282,   499,   282,   282,     0,   282,   280,     0,   280,     0,
     280,  -227,  -227,  -227,  -227,  -227,  -227,     0,   280,   280,
     136,   280,   280,     0,   280,   320,     0,   280,   286,   286,
     280,   280,   181,     0,   187,   191,   280,   197,   201,     0,
     207,   282,   286,     0,   282,   282,   286,     0,     0,     0,
     289,   288,     0,   110,   111,   112,   113,   114,   115,   116,
     117,   288,   282,   282,     0,     0,     0,     0,     0,    28,
     452,     0,     0,   282,    92,     0,     0,     0,     0,     0,
     288,     0,     0,     0,   282,    70,   282,   289,   282,   136,
       0,     0,     0,   288,   288,  1030,   282,   282,     0,   282,
     282,   136,   282,     0,     0,   282,     0,     0,   282,   282,
     287,     0,     0,     0,   282,     0,     0,     0,     0,   500,
     500,     0,     0,     0,     0,     0,   286,     0,   290,   286,
       0,   286,     0,     0,     0,   732,     0,   764,   110,   111,
     112,   113,   114,   115,   116,   117,     0,     0,  1071,  1072,
       0,  1074,  1075,   110,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,     0,   290,   286,   286,   286,     0,
       0,   571,     0,     0,    92,     0,     0,     0,     0,   286,
     286,     0,   286,   286,     0,   286,     0,     0,     0,     0,
    1102,     0,     0,  1103,  1104,     0,     0,     0,     0,   343,
     344,     0,     0,   345,   346,   347,   348,   349,     0,     0,
       0,   966,   287,   287,     0,     0,     0,     0,     0,     0,
     572,   286,  1123,     0,   286,   286,   287,     0,     0,     0,
     287,     0,     0,  1030,   110,   111,   112,   113,   114,   115,
     116,   117,   286,   286,     0,  1071,  1072,     0,  1074,  1075,
       0,     0,   663,   286,  1102,     0,     0,  1103,  1104,    92,
       0,     0,     0,  1123,   286,     0,   286,     0,   286,     0,
       0,     0,     0,     0,    92,     0,   286,   286,     0,   286,
     286,     0,   286,   289,     0,   286,     0,     0,   286,   286,
      41,    42,    43,   289,   286,    44,    45,    46,   498,   498,
       0,   572,     0,     0,   288,     0,     0,     0,     0,     0,
     287,     0,   289,   287,     0,   287,    47,     0,     0,    48,
       0,     0,     0,     0,     0,   289,   289,     0,     0,     0,
       0,    49,     0,     0,     0,   110,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,   500,   500,   500,   500,
     287,   287,   287,   767,     0,    92,     0,     0,     0,     0,
       0,   290,     0,   287,   287,     0,   287,   287,     0,   287,
       0,   290,     0,   110,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   118,    67,   119,    59,     0,   564,     0,
     290,     0,    50,    51,    52,   120,     0,    53,    54,    55,
       0,     0,   572,   290,   290,   287,   288,   288,   287,   287,
     110,   111,   112,   113,   114,   115,   116,   117,    56,     0,
     288,    57,     0,     0,   288,     0,   287,   287,   922,     0,
       0,     0,     0,     2,     3,     4,     0,   287,     5,   121,
       7,     0,     0,     0,     0,   122,     0,     0,   287,     0,
     287,     0,   287,     0,     0,     0,    92,     0,     0,     8,
     287,   287,     9,   287,   287,     0,   287,     0,     0,   287,
       0,     0,   287,   287,    11,     0,     0,   572,   287,   533,
     110,   111,   112,   113,   114,   115,   116,   117,  -224,  -224,
    -224,  -224,  -224,  -224,   123,     0,     0,     0,   934,     0,
       0,     0,     0,     0,   288,   534,     0,   288,     0,   288,
       0,   524,     0,   -23,     0,   -20,   110,   111,   112,   113,
     114,   115,   116,   117,     0,   498,   498,   498,   498,     0,
       0,    92,     0,   525,   989,     0,   289,   526,     0,     0,
    -379,  -379,     0,   124,   288,   288,   288,   572,     0,   110,
     111,   112,   113,   114,   115,   116,   117,   288,   288,     0,
     288,   288,   507,   288,     0,   500,   500,   500,   500,   500,
     500,   500,   500,   500,     0,   500,   500,   500,   500,   500,
     500,   500,   500,   572,   110,   111,   112,   113,   114,   115,
     116,   117,     0,     0,     0,     0,     0,     0,     0,   288,
       0,    92,   288,   288,     0,     0,     0,     0,   265,     0,
       0,   321,   124,     0,   290,     0,     0,   -20,     0,   527,
     288,   288,     0,     0,   333,   336,     0,   350,     0,     0,
       0,   288,     0,     0,     0,     0,     0,    92,   289,   289,
       0,   321,   288,   366,   288,     0,   288,     0,     0,     0,
       0,   572,   289,     0,   288,   288,   289,   288,   288,     0,
     288,     0,     0,   288,     0,     0,   288,   288,     0,     0,
     508,     0,   288,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   116,   117,   110,   111,   112,   113,   114,
     115,   116,   117,   524,     0,   -23,     0,   -20,     0,     0,
       0,     0,     0,     0,   453,    92,   453,   110,   111,   112,
     113,   114,   115,   116,   117,   525,   290,   290,     0,   773,
      59,     0,  -379,  -379,   265,     0,     0,     0,     0,   500,
     290,   500,     0,     0,   290,     0,   289,     0,     0,   289,
       0,   289,     0,     0,   498,   498,   498,   498,   498,   498,
     498,   498,   498,   255,   498,   498,   498,   498,   498,   498,
     498,   498,     0,     0,     0,     0,     0,   265,    35,    36,
       0,     0,    37,    38,    39,     0,   289,   289,   289,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   289,
     289,     0,   289,   289,     0,   289,     0,     0,    92,   -20,
       0,   527,     0,     0,   265,     0,    92,   573,     0,     1,
       0,     0,     0,     0,   290,     0,     0,   290,   500,   290,
       0,     0,     0,     0,     0,     0,     0,     0,    92,    93,
      95,   289,     0,     0,   289,   289,   524,   131,   -23,     0,
     -20,     0,     0,   131,     0,  -225,  -225,  -225,  -225,  -225,
    -225,     0,   289,   289,   290,   290,   290,     0,     0,     2,
       3,     4,   526,   289,     5,     6,     7,   290,   290,     0,
     290,   290,     0,   290,   289,     0,   289,     0,   289,     0,
       0,     0,     0,     0,     0,     8,   289,   289,     9,   289,
     289,     0,   289,     0,    10,   289,     0,     0,   289,   289,
      11,     0,   267,     0,   289,   131,   131,     0,   498,   290,
     498,     0,   290,   290,     0,     0,     0,     0,   131,   131,
     131,   131,   131,    31,     0,     0,     0,   664,     0,   131,
     290,   290,     0,   131,     0,   131,     0,   131,   131,   131,
       0,   290,   -20,     0,   527,     0,     0,     0,     0,     0,
       0,     0,   290,     0,   290,     0,   290,     0,     0,     0,
       0,     0,     0,     0,   290,   290,     0,   290,   290,     0,
     290,     0,     0,   290,     0,     0,   290,   290,     0,     0,
     131,     0,   290,     0,    95,     0,     0,     0,     0,     1,
       0,     0,     0,     0,     0,     0,   131,   498,   131,     0,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     265,     0,     0,   103,   106,   108,   109,     0,   131,     0,
       0,   131,     0,     0,     0,     0,     0,     0,    78,     0,
       0,   185,   573,     0,   195,     0,     0,   205,     0,     2,
       3,     4,   265,   265,     5,     6,     7,   781,     0,     0,
     219,   221,   222,     0,   224,   225,     0,   226,     0,     0,
       0,   267,   101,   104,     0,     8,     0,     0,     9,     0,
       0,     0,     0,     0,    10,   173,   176,     0,     0,   183,
      11,   189,   193,     0,   199,   203,     0,   209,    50,    51,
      52,     0,     0,    53,    54,    55,     0,   558,   267,   217,
       0,   131,     0,     0,   465,   111,   112,   113,   114,   115,
     116,   117,     0,     0,    56,     0,     0,    57,     0,     0,
       0,   238,   978,     0,     0,     0,     0,     0,     0,    58,
       0,   380,   383,   385,   386,     0,     0,     0,     0,     0,
       0,   400,   403,   405,   406,     0,     0,     0,   239,   240,
       0,   420,   423,   425,   426,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,     0,     0,   443,   444,     0,
     445,   368,     0,   446,     0,   250,   251,   252,     0,     0,
     378,   381,     0,     0,     0,     0,   389,   392,     0,     0,
     398,   401,     0,     0,     0,     0,   409,   412,     0,     0,
     418,   421,     0,     0,     0,     0,   429,   432,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   131,   131,
     131,   131,     0,     0,     0,   470,     0,   265,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,   237,    67,
       0,     0,     0,   265,     0,   238,     0,     0,     0,     0,
     664,   664,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,     0,
       0,     0,     0,     0,   267,     0,     0,     0,   664,   250,
     251,   252,   253,   254,     0,   256,   257,   258,   259,   260,
       0,   261,   262,     0,     0,     0,   131,   597,   599,   600,
       0,   602,   603,     0,   604,     0,   267,   267,     0,     0,
       0,   131,     0,     0,     0,     0,     0,   617,   619,   620,
       0,   622,   623,     0,   624,     0,     0,     0,     0,   264,
       0,     0,     0,     0,     0,     0,     0,   637,   639,   640,
       0,   642,   643,     0,   644,     0,   595,     0,   664,     0,
       0,     0,     0,     0,     0,     0,     0,   606,     0,     0,
       0,     0,   657,     0,     0,     0,   615,     0,     0,     0,
       0,     0,     0,   171,   175,   178,   180,   626,     0,   186,
       0,     0,   196,     0,     0,   206,   635,     0,     0,     0,
       0,     0,     0,     0,    95,     0,     0,   646,     0,     0,
       0,     0,     0,     0,     0,     0,   465,   111,   112,   113,
     114,   115,   116,   117,   835,     0,     0,    67,   119,     0,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,     0,     0,   466,   467,     0,     0,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   265,   248,     0,     0,     0,   367,
     370,   372,     0,   373,   375,     0,   376,   250,   251,   252,
       0,     0,     0,     0,   387,   391,   394,   396,     0,     0,
       0,   131,     0,     0,   407,   411,   414,   416,     0,     0,
       0,     0,     0,     0,   427,   431,   434,   436,     0,   558,
       0,     0,     0,     0,     0,   795,   796,   267,   797,     0,
       0,   798,     0,     0,   131,   131,     0,   470,     0,     0,
       0,     0,     0,     0,     0,   805,   806,     0,   807,     0,
       0,   808,   236,   111,   112,   113,   114,   115,   116,   117,
       0,     0,   751,     0,     0,   815,   816,     0,   817,   238,
       0,   818,     0,     0,    95,     0,     0,     0,     0,   877,
       0,     0,   131,     0,     0,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,   239,   240,     0,     0,
       0,     0,   238,   241,   242,   243,   244,   245,   246,   247,
       0,   248,    79,     0,   131,   131,     0,   131,     0,   752,
       0,     0,     0,   250,   251,   252,     0,     0,   255,   239,
     240,   907,   909,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,   102,   105,   107,     0,
       0,     0,   131,     0,     0,     0,   250,   251,   252,   174,
     177,   179,     0,   184,     0,   190,   194,     0,   200,   204,
       0,   210,     0,   470,     0,   590,   592,     0,   593,     0,
       0,   594,     0,   218,   220,     0,     0,   223,     0,     0,
       0,     0,     0,     0,     0,   605,   608,   610,     0,   611,
     613,     0,   614,     0,     0,     0,   470,     0,     0,     0,
       0,     0,     0,     0,     0,   625,   628,   630,     0,   631,
     633,     0,   634,   942,   925,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   927,   645,   648,   650,   951,   651,
     653,     0,   654,     0,   929,   972,     0,     0,     0,     0,
       0,     0,   976,     0,     0,   369,   371,     0,     0,   374,
     987,     0,     0,     0,   379,   382,   384,     0,   267,     0,
     390,   393,   395,     0,   399,   402,   404,  1002,  1004,     0,
     410,   413,   415,     0,   419,   422,   424,     0,     0,     0,
     430,   433,   435,     0,     0,     0,     0,     0,     0,     0,
     442,     0,     0,  1013,     0,     0,   948,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   236,   111,   112,
     113,   114,   115,   116,   117,     0,     0,  1062,     0,     0,
       0,     0,     0,  1026,   238,     0,     0,  1029,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1040,     0,
       0,     0,     0,     0,     0,  1045,     0,  1048,     0,  1051,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,     0,  1014,
    1015,     0,  1067,     0,   752,     0,     0,     0,   250,   251,
     252,     0,     0,   255,     0,     0,     0,     0,   793,     0,
       0,     0,     0,     0,     0,     0,  1083,     0,     0,  1087,
       0,     0,  1091,   799,   801,     0,   802,     0,     0,   803,
       0,     0,     0,     0,     0,     0,     0,     0,  1101,     0,
       0,     0,     0,   809,   811,     0,   812,     0,   470,   813,
       0,     0,     0,     0,     0,     0,  1059,     0,     0,     0,
       0,   591,     0,   819,   821,     0,   822,     0,     0,   823,
     596,   598,     0,     0,   601,     0,     0,     0,     0,     0,
       0,   607,   609,     0,     0,   612,     0,     0,     0,     0,
     616,   618,     0,     0,   621,     0,     0,     0,     0,     0,
       0,   627,   629,     0,     0,   632,     0,     0,     0,     0,
     636,   638,     0,     0,   641,     0,     0,     0,     0,     0,
       0,   647,   649,     0,     0,   652,   236,   111,   112,   113,
     114,   115,   116,   117,     0,     0,   237,    67,   119,   507,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   561,     2,     3,     4,     0,
       0,     5,     6,   249,     0,     0,     0,   562,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,     0,   261,
     262,   263,     8,     0,     0,     9,     0,   926,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   928,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   930,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   563,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,   111,   112,   113,   114,   115,   116,   117,     0,     0,
     237,    67,   119,     0,     0,     0,     0,   238,   794,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   800,
       0,     0,     0,     0,     0,     0,     0,     0,   804,     0,
       0,     0,     0,     0,   239,   240,     0,     0,     0,   810,
       0,   241,   242,   243,   244,   245,   246,   247,   814,   248,
       2,     3,     4,     0,     0,     5,     6,   249,     0,   820,
       0,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,     0,   261,   262,   263,     8,     0,     0,     9,
     465,   111,   112,   113,   114,   115,   116,   117,     0,     0,
     237,    67,     0,     0,     0,     0,     0,   238,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   264,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,   251,   252,   253,   254,     0,   256,   257,   258,
     259,   260,     0,   953,   262,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,   519,     0,     0,     0,     0,
       0,     0,   238,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,   954,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,     0,     0,   465,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,    67,
       0,     0,     0,     0,     0,   238,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   116,   117,     0,   466,   467,
       0,     0,    59,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   470,   248,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   250,
     251,   252,     0,     0,   676,   238,     0,     0,     0,    50,
      51,    52,     0,     0,    53,    54,    55,     0,   466,   467,
       0,   122,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,    56,   340,   341,    57,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   470,
       0,   465,   111,   112,   113,   114,   115,   116,   117,   250,
     251,   252,     0,     0,     0,     0,     0,     0,   238,   744,
      92,     0,   110,   111,   112,   113,   114,   115,   116,   117,
       0,   466,   467,     0,     0,    59,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,   470,
     248,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,   250,   251,   252,     0,     0,     0,   238,     0,
       0,     0,    41,    42,    43,   849,     0,    44,    45,    46,
       0,   466,   467,     0,   122,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,    47,     0,
       0,    48,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   470,    49,   465,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,     0,    92,     0,     0,     0,     0,   851,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   497,   248,   465,   111,   112,   113,   114,   115,
     116,   117,     0,     0,     0,   250,   251,   252,     0,     0,
     669,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   497,     0,   465,   111,   112,
     113,   114,   115,   116,   117,   250,   251,   252,     0,     0,
       0,     0,     0,     0,   238,   876,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,     0,   466,   467,     0,
       0,    59,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   470,   248,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,   894,   250,   251,
     252,     0,     0,     0,   238,     0,     0,     0,     0,   351,
     352,     0,     0,   353,   354,   355,     0,   466,   467,     0,
     122,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,   356,   357,   358,   359,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   470,     0,
     465,   111,   112,   113,   114,   115,   116,   117,   250,   251,
     252,     0,     0,     0,     0,     0,     0,   238,   906,    92,
       0,   110,   111,   112,   113,   114,   115,   116,   117,     0,
     466,   467,     0,     0,    59,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     0,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,   470,   248,
     465,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,   250,   251,   252,     0,     0,     0,   238,   908,     0,
       0,     0,    51,    52,     0,     0,    53,    54,    55,     0,
     466,   467,     0,   122,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,    56,   340,   341,
      57,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,   470,     0,   465,   111,   112,   113,   114,   115,   116,
     117,   250,   251,   252,     0,     0,     0,     0,     0,     0,
     238,   941,    92,     0,   110,   111,   112,   113,   114,   115,
     116,   117,     0,   466,   467,     0,     0,    59,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   470,   248,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,   950,     0,     0,    41,    42,    43,     0,     0,    44,
      45,    46,     0,   466,   467,     0,   122,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
      47,     0,     0,    48,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   470,     0,   465,   111,   112,   113,
     114,   115,   116,   117,   250,   251,   252,     0,     0,     0,
       0,     0,     0,   238,   971,    92,     0,   110,   111,   112,
     113,   114,   115,   116,   117,     0,   466,   467,     0,     0,
      59,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   470,   248,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,   975,     0,     0,    34,    35,    36,
       0,     0,    37,    38,    39,     0,   466,   467,     0,   122,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   470,    40,     0,
       0,     0,     0,     0,     0,     0,     0,   250,   251,   252,
     465,   111,   112,   113,   114,   115,   116,   117,   123,     0,
     983,     0,     0,     0,     0,     0,     0,   238,     0,     0,
       0,   110,   111,   112,   113,   114,   115,   116,   117,     0,
     466,   467,     0,     0,    59,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,   470,     0,     0,
       0,   241,   242,   243,   244,   245,   246,   247,     0,   248,
     465,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,   250,   251,   252,     0,     0,     0,   238,   986,     0,
       0,     0,     3,     4,     0,     0,     5,     6,     7,     0,
     466,   467,     0,   122,     0,     0,     0,     0,   468,   469,
       0,     0,     0,     0,   239,   240,     0,     8,     0,     0,
       9,   241,   242,   243,   244,   245,   246,   247,     0,   248,
       0,   470,     0,   465,   111,   112,   113,   114,   115,   116,
     117,   250,   251,   252,     0,     0,     0,     0,     0,     0,
     238,  1001,    92,     0,   110,   111,   112,   113,   114,   115,
     116,   117,     0,   466,   467,     0,     0,    59,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
       0,     0,     0,     0,   241,   242,   243,   244,   245,   246,
     247,   470,   248,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,     0,   250,   251,   252,     0,     0,     0,
     238,  1003,     0,     0,     0,    42,    43,     0,     0,    44,
      45,    46,     0,   466,   467,     0,   122,     0,     0,     0,
       0,   468,   469,     0,     0,     0,     0,   239,   240,     0,
      47,     0,     0,    48,   241,   242,   243,   244,   245,   246,
     247,     0,   248,     0,   470,     0,   465,   111,   112,   113,
     114,   115,   116,   117,   250,   251,   252,     0,     0,     0,
       0,     0,     0,   238,  1012,    92,     0,   110,   111,   112,
     113,   114,   115,   116,   117,     0,   466,   467,     0,     0,
      59,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,   470,   248,   465,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   250,   251,   252,
       0,     0,     0,   238,  1025,     0,     0,    34,    35,    36,
       0,     0,    37,    38,    39,     0,   466,   467,     0,   122,
       0,     0,     0,     0,   468,   469,     0,     0,     0,     0,
     239,   240,     0,     0,     0,     0,     0,   241,   242,   243,
     244,   245,   246,   247,     0,   248,     0,   470,     0,   465,
     111,   112,   113,   114,   115,   116,   117,   250,   251,   252,
       0,     0,     0,     0,     0,     0,   238,  1028,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   466,
     467,     0,     0,     0,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,   470,   248,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
     250,   251,   252,     0,     0,     0,   238,  1039,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   466,
     467,     0,     0,     0,     0,     0,     0,   468,   469,     0,
       0,     0,     0,   239,   240,     0,     0,     0,     0,     0,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
     470,     0,   465,   111,   112,   113,   114,   115,   116,   117,
     250,   251,   252,     0,     0,     0,     0,     0,     0,   238,
    1044,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,   467,     0,     0,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     470,   248,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,   250,   251,   252,     0,     0,     0,   238,
    1047,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   466,   467,     0,     0,     0,     0,     0,     0,
     468,   469,     0,     0,     0,     0,   239,   240,     0,     0,
       0,     0,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   470,     0,   465,   111,   112,   113,   114,
     115,   116,   117,   250,   251,   252,     0,     0,     0,     0,
       0,     0,   238,  1050,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,   470,   248,   465,   111,   112,   113,   114,
     115,   116,   117,     0,     0,     0,   250,   251,   252,     0,
       0,     0,   238,  1066,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   466,   467,     0,     0,     0,
       0,     0,     0,   468,   469,     0,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,     0,   248,     0,   470,     0,   465,   111,
     112,   113,   114,   115,   116,   117,   250,   251,   252,     0,
       0,     0,     0,     0,     0,   238,  1082,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,   467,
       0,     0,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,   470,   248,   465,   111,
     112,   113,   114,   115,   116,   117,     0,     0,     0,   250,
     251,   252,     0,     0,     0,   238,  1086,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,   467,
       0,     0,     0,     0,     0,     0,   468,   469,     0,     0,
       0,     0,   239,   240,     0,     0,     0,     0,     0,   241,
     242,   243,   244,   245,   246,   247,     0,   248,     0,   470,
       0,   465,   111,   112,   113,   114,   115,   116,   117,   250,
     251,   252,     0,     0,     0,     0,     0,     0,   238,  1090,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,   470,
     248,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,  1095,   250,   251,   252,     0,     0,     0,   238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   466,   467,     0,     0,     0,     0,     0,     0,   468,
     469,     0,     0,     0,     0,   239,   240,     0,     0,     0,
       0,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   470,     0,   465,   111,   112,   113,   114,   115,
     116,   117,   250,   251,   252,     0,     0,     0,     0,     0,
       0,   238,  1100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,   470,   248,   465,   111,   112,   113,   114,   115,
     116,   117,     0,     0,  1120,   250,   251,   252,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   467,     0,     0,     0,     0,
       0,     0,   468,   469,     0,     0,     0,     0,   239,   240,
       0,     0,     0,     0,     0,   241,   242,   243,   244,   245,
     246,   247,     0,   248,     0,   470,     0,   465,   111,   112,
     113,   114,   115,   116,   117,   250,   251,   252,     0,     0,
       0,     0,     0,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   466,   467,     0,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,   470,   248,   465,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,   250,   251,
     252,     0,     0,     0,   238,     0,   110,   111,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   466,   467,    59,
       0,     0,     0,     0,     0,   468,   469,     0,     0,     0,
       0,   239,   240,     0,     0,     0,     0,     0,   241,   242,
     243,   244,   245,   246,   247,     0,   248,     0,   470,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   250,   251,
     252,     0,     0,     0,     0,     0,    50,    51,    52,     0,
       0,    53,    54,    55,   338,   339,     0,     0,   122,   465,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,    56,   340,   341,    57,   238,  1032,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,   497,     0,
       0,   465,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,     0,   239,   240,     0,     0,    92,   238,  1035,
     241,   242,   243,   244,   245,   246,   247,     0,   248,     0,
       0,     0,   465,   111,   112,   113,   114,   115,   116,   117,
     250,   251,   252,     0,     0,   239,   240,     0,     0,   238,
    1077,     0,   241,   242,   243,   244,   245,   246,   247,     0,
     248,     0,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,   250,   251,   252,     0,   239,   240,     0,   238,
    1116,     0,     0,   241,   242,   243,   244,   245,   246,   247,
     470,   248,   465,   111,   112,   113,   114,   115,   116,   117,
       0,     0,     0,   250,   251,   252,   239,   240,     0,   238,
    1129,     0,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,   470,   465,   111,   112,   113,   114,   115,   116,
     117,     0,     0,   250,   251,   252,   239,   240,     0,     0,
     238,  1132,     0,   241,   242,   243,   244,   245,   246,   247,
       0,   248,     0,   470,     0,   465,   111,   112,   113,   114,
     115,   116,   117,   250,   251,   252,     0,   239,   240,     0,
       0,     0,   238,  1141,   241,   242,   243,   244,   245,   246,
     247,     0,   248,   470,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   250,   251,   252,     0,     0,   239,
     240,     0,     0,     0,     0,     0,   241,   242,   243,   244,
     245,   246,   247,   470,   248,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   250,   251,   252,   110,
     111,   112,   113,   114,   115,   116,   117,     0,     0,   159,
       0,   119,    59,     0,   470,     0,     0,     0,     0,     0,
       0,   120,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   470,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       3,     4,     0,     0,     5,     6,     7,     0,     0,     0,
       0,   122,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     0,     9,     0,
     160,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92
};

static const yytype_int16 yycheck[] =
{
      29,   215,   249,   535,    74,   292,   535,   672,   238,   535,
     330,   509,   510,   133,    68,   335,   329,   507,   332,   526,
      74,   230,    12,   253,   254,    16,   235,   534,   258,   259,
      13,   573,   329,   692,   693,   236,    36,   544,    13,    68,
      68,   452,    76,    16,    18,    62,    18,    76,    77,    78,
      79,    12,    74,    82,   239,   240,    85,     0,    68,    88,
      13,    23,     0,   133,    11,   266,   297,   137,    16,   124,
      17,    14,    44,    16,    18,    16,    14,    16,    16,   133,
     211,    14,   136,   137,    45,    76,    36,   122,    18,    62,
     124,    44,   121,    16,   164,   149,   150,   151,   152,   153,
     124,    74,   333,    76,   133,   336,   160,   124,   137,   137,
     164,   121,   166,   142,   168,   169,   170,    16,   147,   350,
      18,   252,   664,    62,   124,    68,   335,   137,    76,    14,
      68,    74,   142,   124,   124,   366,    74,    76,    62,    62,
       0,   124,   164,   172,   173,   174,   557,   176,   177,   124,
     179,   124,   126,    76,    14,    23,    16,    18,   187,   188,
     189,   190,   124,    14,    69,   663,    99,     0,   197,   198,
     199,   200,   292,   227,   124,   229,   124,   231,   207,   208,
     209,   210,   126,   124,   981,   124,   983,    18,    16,    20,
     849,    22,   851,   133,   137,   249,   126,    13,   252,   137,
     124,   124,    16,    74,   694,    13,   503,   504,    68,   329,
      16,    16,    16,    44,    74,   334,    67,   715,   337,   124,
     718,   164,   292,   342,    40,   124,   164,    22,   126,   526,
     460,   149,   150,   151,   531,   153,    44,   534,   292,   781,
    1037,   360,   160,   557,   363,    62,   543,   544,    76,    44,
     168,   169,   170,   124,    22,   568,   124,    16,    17,   329,
     580,   124,    18,   292,   465,   126,   773,   774,   775,    22,
     471,   133,   937,    14,   505,   329,    44,   137,   332,    44,
     567,   466,   467,   468,   469,   320,   321,    23,    44,   227,
     124,    44,   522,   523,   524,   126,   124,    11,  1095,    13,
     329,   330,    14,   533,   164,   334,   335,   124,   337,   227,
     124,    16,   542,   342,    73,   545,    11,    62,   124,   124,
     124,  1118,    22,  1120,   334,    66,    67,   337,   447,    74,
      11,   360,   342,   831,   363,   124,    17,  1134,    74,   368,
     369,    20,   371,    22,    44,   374,   555,   556,    11,    61,
     360,   124,   292,   363,    66,    67,    11,    62,    21,   388,
     389,   390,    16,   392,   393,    44,   395,   227,   894,    74,
     124,    76,   898,    14,   785,   865,   866,    18,   868,   408,
     409,   410,    11,   412,   413,    20,   415,    22,   124,   329,
     124,    14,    21,    16,   448,   449,   450,   451,   452,   428,
     429,   430,   124,   432,   433,   525,   435,    61,   124,    44,
      34,     0,    66,    67,    11,   535,    13,    41,   447,   124,
     880,   124,   833,    18,    21,    14,    50,    16,   124,    11,
     292,   460,    13,    14,   554,    11,   934,   447,    61,    21,
      11,   655,   672,    66,    67,    21,    11,   567,   568,    44,
      21,   133,    47,    48,   684,   981,    21,   983,    63,    64,
      65,   880,   124,    68,    69,    70,   714,   329,    61,   717,
      11,    26,   239,   240,    11,   124,   773,   774,   775,    68,
      21,   535,    20,   713,    21,    74,   715,  1019,   124,   718,
    1019,   778,   903,  1019,   724,    20,   525,   567,   568,   104,
      47,    48,    11,   557,    13,   752,   880,    47,    48,    11,
    1008,  1037,    21,   567,   568,   700,   701,   702,   572,    21,
      11,   751,    13,    13,    11,   554,    11,    11,    47,    48,
     448,   449,   450,   451,    21,    11,    21,    21,   567,   568,
     659,   660,   661,   662,    11,    21,    11,    11,   137,    11,
      11,   580,    13,    11,    21,    11,    21,    21,  1018,    21,
    1020,    11,   591,    21,    11,    21,    11,   124,    11,  1095,
      13,    21,    11,   124,    21,   164,    21,   606,   607,    11,
     609,    11,    21,   612,    99,   525,   883,   884,    11,    21,
      13,    21,  1118,    27,  1120,   535,    11,   626,   627,  1018,
     629,  1020,   672,   632,   126,    11,    21,    20,  1134,    11,
     292,   825,    11,    20,   554,    21,    20,   646,   647,    21,
     649,    22,    21,   652,    49,    50,    51,   567,   568,    20,
     659,   660,   661,   662,  1094,   133,    52,    53,   227,    35,
      36,    37,    18,   672,  1018,    13,  1020,   329,    13,   659,
     660,   661,   662,   695,   696,   697,  1116,    85,   778,   889,
      14,   124,    16,   525,    33,    34,   896,   897,  1128,  1129,
      20,  1131,  1132,   535,    13,  1094,    43,  1137,    61,    62,
    1140,  1141,    29,   690,   691,   714,  1146,    43,   717,   698,
     699,    11,   554,    19,  1018,    18,  1020,  1116,   752,   466,
     467,   468,   469,    19,    46,   567,   568,   937,   778,  1128,
    1129,    21,  1131,  1132,    38,    43,    63,    39,  1137,    20,
    1094,  1140,  1141,    18,   778,    13,    20,  1146,    13,    76,
     124,   785,   786,    80,    13,    82,    83,    13,    85,    86,
      13,    88,  1116,    18,    11,    13,    63,    64,    65,   778,
      11,    68,    69,    70,  1128,  1129,    20,  1131,  1132,    11,
     880,   881,    43,  1137,    44,    20,  1140,  1141,   838,    19,
    1094,   800,  1146,    19,   894,   124,    20,    20,   898,   833,
     124,   810,    21,    21,    19,    13,    20,  1017,   124,    19,
     124,   820,  1116,    20,   292,    63,    64,    65,    40,    11,
      68,    69,    70,   124,  1128,  1129,    20,  1131,  1132,   124,
      19,    11,   525,  1137,    20,    20,  1140,  1141,   124,    15,
      74,    89,  1146,    11,    92,    40,    20,    19,    13,   133,
      98,   329,  1062,    20,   181,    13,   104,    20,   778,    20,
     187,   554,    13,   525,   191,    13,    20,    20,    20,   903,
     197,   880,   881,   535,   201,   124,    20,    20,   978,   127,
     207,   981,    85,   983,    85,   124,   124,  1097,  1098,    21,
      21,    13,   554,    13,     3,     4,     5,     6,     7,     8,
       9,    10,    13,    20,    20,   567,   568,    16,    20,     3,
       4,     5,     6,     7,     8,     9,    10,    13,  1018,  1019,
    1020,    13,    20,    13,    18,    40,    20,    13,   937,    13,
      21,  1031,  1032,    21,  1034,  1035,   778,  1037,   685,   686,
     687,   688,   689,   690,   691,   692,   693,    13,   695,   696,
     697,   698,   699,   700,   701,   702,    13,    21,    13,    21,
     880,   881,    13,    13,    13,    13,    75,    13,    13,   978,
      13,    13,    13,  1073,   894,    13,  1076,  1077,   898,   252,
      13,    21,    21,   164,    18,  1019,    20,   137,    22,    21,
      21,    21,   213,   512,  1094,  1095,   458,     3,     4,     5,
       6,     7,     8,     9,    10,  1105,    40,   510,   292,  1018,
      44,  1020,   329,    47,    48,   124,  1116,   685,  1118,   686,
    1120,   938,  1031,  1032,   687,  1034,  1035,   770,  1128,  1129,
     124,  1131,  1132,   688,  1134,   689,   786,  1137,   880,   881,
    1140,  1141,  1019,   149,   227,   329,  1146,   525,    63,    64,
      65,   136,   894,    68,    69,    70,   898,   535,   978,   868,
      -1,   981,    -1,   983,  1073,    -1,    -1,  1076,  1077,    75,
      -1,    -1,    -1,    -1,    89,    -1,   554,    92,    -1,    -1,
      -1,   133,    -1,    -1,    -1,  1094,    -1,    -1,    -1,   567,
     568,    -1,   126,    -1,    -1,    -1,  1105,    -1,  1018,  1019,
    1020,    -1,   849,    -1,   851,    -1,    -1,  1116,    -1,    -1,
      -1,  1031,  1032,    -1,  1034,  1035,   778,  1037,   124,  1128,
    1129,    -1,  1131,  1132,    -1,    -1,    -1,    -1,  1137,    -1,
      -1,  1140,  1141,    -1,    -1,    -1,   978,  1146,    -1,   981,
      -1,   983,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,  1073,    -1,    -1,  1076,  1077,    -1,   133,
      27,    28,    29,    30,    31,    32,    24,    -1,    -1,    -1,
      -1,    29,    -1,    -1,  1094,  1095,  1018,  1019,  1020,    27,
      28,    29,    30,    31,    32,  1105,    -1,   880,   881,  1031,
    1032,   938,  1034,  1035,    -1,  1037,  1116,    -1,  1118,    -1,
    1120,    27,    28,    29,    30,    31,    32,    -1,  1128,  1129,
      68,  1131,  1132,    -1,  1134,    75,    -1,  1137,   880,   881,
    1140,  1141,    80,    -1,    82,    83,  1146,    85,    86,    -1,
      88,  1073,   894,    -1,  1076,  1077,   898,    -1,    -1,    -1,
     292,   525,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,   535,  1094,  1095,    -1,    -1,    -1,    -1,    -1,    10,
      20,    -1,    -1,  1105,   124,    -1,    -1,    -1,    -1,    -1,
     554,    -1,    -1,    -1,  1116,    26,  1118,   329,  1120,   137,
      -1,    -1,    -1,   567,   568,   978,  1128,  1129,    -1,  1131,
    1132,   149,  1134,    -1,    -1,  1137,    -1,    -1,  1140,  1141,
     778,    -1,    -1,    -1,  1146,    -1,    -1,    -1,    -1,   239,
     240,    -1,    -1,    -1,    -1,    -1,   978,    -1,   292,   981,
      -1,   983,    -1,    -1,    -1,  1018,    -1,  1020,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,  1031,  1032,
      -1,  1034,  1035,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,   329,  1018,  1019,  1020,    -1,
      -1,    21,    -1,    -1,   124,    -1,    -1,    -1,    -1,  1031,
    1032,    -1,  1034,  1035,    -1,  1037,    -1,    -1,    -1,    -1,
    1073,    -1,    -1,  1076,  1077,    -1,    -1,    -1,    -1,    64,
      65,    -1,    -1,    68,    69,    70,    71,    72,    -1,    -1,
      -1,  1094,   880,   881,    -1,    -1,    -1,    -1,    -1,    -1,
      70,  1073,  1105,    -1,  1076,  1077,   894,    -1,    -1,    -1,
     898,    -1,    -1,  1116,     3,     4,     5,     6,     7,     8,
       9,    10,  1094,  1095,    -1,  1128,  1129,    -1,  1131,  1132,
      -1,    -1,    21,  1105,  1137,    -1,    -1,  1140,  1141,   124,
      -1,    -1,    -1,  1146,  1116,    -1,  1118,    -1,  1120,    -1,
      -1,    -1,    -1,    -1,   124,    -1,  1128,  1129,    -1,  1131,
    1132,    -1,  1134,   525,    -1,  1137,    -1,    -1,  1140,  1141,
      63,    64,    65,   535,  1146,    68,    69,    70,   239,   240,
      -1,    70,    -1,    -1,   778,    -1,    -1,    -1,    -1,    -1,
     978,    -1,   554,   981,    -1,   983,    89,    -1,    -1,    92,
      -1,    -1,    -1,    -1,    -1,   567,   568,    -1,    -1,    -1,
      -1,   104,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,   466,   467,   468,   469,
    1018,  1019,  1020,    21,    -1,   124,    -1,    -1,    -1,    -1,
      -1,   525,    -1,  1031,  1032,    -1,  1034,  1035,    -1,  1037,
      -1,   535,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,   329,    -1,
     554,    -1,    63,    64,    65,    25,    -1,    68,    69,    70,
      -1,    -1,    70,   567,   568,  1073,   880,   881,  1076,  1077,
       3,     4,     5,     6,     7,     8,     9,    10,    89,    -1,
     894,    92,    -1,    -1,   898,    -1,  1094,  1095,    21,    -1,
      -1,    -1,    -1,    63,    64,    65,    -1,  1105,    68,    69,
      70,    -1,    -1,    -1,    -1,    75,    -1,    -1,  1116,    -1,
    1118,    -1,  1120,    -1,    -1,    -1,   124,    -1,    -1,    89,
    1128,  1129,    92,  1131,  1132,    -1,  1134,    -1,    -1,  1137,
      -1,    -1,  1140,  1141,   104,    -1,    -1,    70,  1146,    18,
       3,     4,     5,     6,     7,     8,     9,    10,    27,    28,
      29,    30,    31,    32,   124,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,   978,    44,    -1,   981,    -1,   983,
      -1,    18,    -1,    20,    -1,    22,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,   466,   467,   468,   469,    -1,
      -1,   124,    -1,    40,    21,    -1,   778,    44,    -1,    -1,
      47,    48,    -1,    68,  1018,  1019,  1020,    70,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,  1031,  1032,    -1,
    1034,  1035,    16,  1037,    -1,   685,   686,   687,   688,   689,
     690,   691,   692,   693,    -1,   695,   696,   697,   698,   699,
     700,   701,   702,    70,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1073,
      -1,   124,  1076,  1077,    -1,    -1,    -1,    -1,   133,    -1,
      -1,   136,   137,    -1,   778,    -1,    -1,   124,    -1,   126,
    1094,  1095,    -1,    -1,   149,   150,    -1,   152,    -1,    -1,
      -1,  1105,    -1,    -1,    -1,    -1,    -1,   124,   880,   881,
      -1,   166,  1116,   168,  1118,    -1,  1120,    -1,    -1,    -1,
      -1,    70,   894,    -1,  1128,  1129,   898,  1131,  1132,    -1,
    1134,    -1,    -1,  1137,    -1,    -1,  1140,  1141,    -1,    -1,
     124,    -1,  1146,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,     3,     4,     5,     6,     7,
       8,     9,    10,    18,    -1,    20,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,   229,   124,   231,     3,     4,     5,
       6,     7,     8,     9,    10,    40,   880,   881,    -1,    44,
      16,    -1,    47,    48,   249,    -1,    -1,    -1,    -1,   849,
     894,   851,    -1,    -1,   898,    -1,   978,    -1,    -1,   981,
      -1,   983,    -1,    -1,   685,   686,   687,   688,   689,   690,
     691,   692,   693,    79,   695,   696,   697,   698,   699,   700,
     701,   702,    -1,    -1,    -1,    -1,    -1,   292,    64,    65,
      -1,    -1,    68,    69,    70,    -1,  1018,  1019,  1020,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1031,
    1032,    -1,  1034,  1035,    -1,  1037,    -1,    -1,   124,   124,
      -1,   126,    -1,    -1,   329,    -1,   124,   332,    -1,    13,
      -1,    -1,    -1,    -1,   978,    -1,    -1,   981,   938,   983,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    60,
      61,  1073,    -1,    -1,  1076,  1077,    18,    68,    20,    -1,
      22,    -1,    -1,    74,    -1,    27,    28,    29,    30,    31,
      32,    -1,  1094,  1095,  1018,  1019,  1020,    -1,    -1,    63,
      64,    65,    44,  1105,    68,    69,    70,  1031,  1032,    -1,
    1034,  1035,    -1,  1037,  1116,    -1,  1118,    -1,  1120,    -1,
      -1,    -1,    -1,    -1,    -1,    89,  1128,  1129,    92,  1131,
    1132,    -1,  1134,    -1,    98,  1137,    -1,    -1,  1140,  1141,
     104,    -1,   133,    -1,  1146,   136,   137,    -1,   849,  1073,
     851,    -1,  1076,  1077,    -1,    -1,    -1,    -1,   149,   150,
     151,   152,   153,   127,    -1,    -1,    -1,   452,    -1,   160,
    1094,  1095,    -1,   164,    -1,   166,    -1,   168,   169,   170,
      -1,  1105,   124,    -1,   126,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1116,    -1,  1118,    -1,  1120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1128,  1129,    -1,  1131,  1132,    -1,
    1134,    -1,    -1,  1137,    -1,    -1,  1140,  1141,    -1,    -1,
     211,    -1,  1146,    -1,   215,    -1,    -1,    -1,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    -1,   227,   938,   229,    -1,
     231,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     535,    -1,    -1,    63,    64,    65,    66,    -1,   249,    -1,
      -1,   252,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    81,   557,    -1,    84,    -1,    -1,    87,    -1,    63,
      64,    65,   567,   568,    68,    69,    70,   572,    -1,    -1,
     100,   101,   102,    -1,   104,   105,    -1,   107,    -1,    -1,
      -1,   292,    63,    64,    -1,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    76,    77,    -1,    -1,    80,
     104,    82,    83,    -1,    85,    86,    -1,    88,    63,    64,
      65,    -1,    -1,    68,    69,    70,    -1,   328,   329,   100,
      -1,   332,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      -1,   181,   182,   183,   184,    -1,    -1,    -1,    -1,    -1,
      -1,   191,   192,   193,   194,    -1,    -1,    -1,    47,    48,
      -1,   201,   202,   203,   204,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    -1,    -1,    -1,   217,   218,    -1,
     220,   172,    -1,   223,    -1,    74,    75,    76,    -1,    -1,
     181,   182,    -1,    -1,    -1,    -1,   187,   188,    -1,    -1,
     191,   192,    -1,    -1,    -1,    -1,   197,   198,    -1,    -1,
     201,   202,    -1,    -1,    -1,    -1,   207,   208,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   448,   449,   450,
     451,   452,    -1,    -1,    -1,   124,    -1,   752,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      -1,    -1,    -1,   778,    -1,    20,    -1,    -1,    -1,    -1,
     785,   786,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   507,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,   535,    -1,    -1,    -1,   833,    74,
      75,    76,    77,    78,    -1,    80,    81,    82,    83,    84,
      -1,    86,    87,    -1,    -1,    -1,   557,   377,   378,   379,
      -1,   381,   382,    -1,   384,    -1,   567,   568,    -1,    -1,
      -1,   572,    -1,    -1,    -1,    -1,    -1,   397,   398,   399,
      -1,   401,   402,    -1,   404,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   417,   418,   419,
      -1,   421,   422,    -1,   424,    -1,   377,    -1,   903,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   388,    -1,    -1,
      -1,    -1,   442,    -1,    -1,    -1,   397,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,   408,    -1,    82,
      -1,    -1,    85,    -1,    -1,    88,   417,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   655,    -1,    -1,   428,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    14,    15,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   694,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,  1019,    62,    -1,    -1,    -1,   172,
     173,   174,    -1,   176,   177,    -1,   179,    74,    75,    76,
      -1,    -1,    -1,    -1,   187,   188,   189,   190,    -1,    -1,
      -1,   752,    -1,    -1,   197,   198,   199,   200,    -1,    -1,
      -1,    -1,    -1,    -1,   207,   208,   209,   210,    -1,   770,
      -1,    -1,    -1,    -1,    -1,   595,   596,   778,   598,    -1,
      -1,   601,    -1,    -1,   785,   786,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   615,   616,    -1,   618,    -1,
      -1,   621,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    -1,    -1,   635,   636,    -1,   638,    20,
      -1,   641,    -1,    -1,   825,    -1,    -1,    -1,    -1,   719,
      -1,    -1,   833,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    20,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    29,    -1,   865,   866,    -1,   868,    -1,    70,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    79,    47,
      48,   771,   772,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    62,    -1,    63,    64,    65,    -1,
      -1,    -1,   903,    -1,    -1,    -1,    74,    75,    76,    76,
      77,    78,    -1,    80,    -1,    82,    83,    -1,    85,    86,
      -1,    88,    -1,   124,    -1,   368,   369,    -1,   371,    -1,
      -1,   374,    -1,   100,   101,    -1,    -1,   104,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   388,   389,   390,    -1,   392,
     393,    -1,   395,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   408,   409,   410,    -1,   412,
     413,    -1,   415,   863,   794,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   804,   428,   429,   430,   878,   432,
     433,    -1,   435,    -1,   814,   885,    -1,    -1,    -1,    -1,
      -1,    -1,   892,    -1,    -1,   172,   173,    -1,    -1,   176,
     900,    -1,    -1,    -1,   181,   182,   183,    -1,  1019,    -1,
     187,   188,   189,    -1,   191,   192,   193,   917,   918,    -1,
     197,   198,   199,    -1,   201,   202,   203,    -1,    -1,    -1,
     207,   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     217,    -1,    -1,   943,    -1,    -1,   876,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    -1,    -1,
      -1,    -1,    -1,   973,    20,    -1,    -1,   977,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   988,    -1,
      -1,    -1,    -1,    -1,    -1,   995,    -1,   997,    -1,   999,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,    -1,   949,
     950,    -1,  1022,    -1,    70,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    79,    -1,    -1,    -1,    -1,   591,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1046,    -1,    -1,  1049,
      -1,    -1,  1052,   606,   607,    -1,   609,    -1,    -1,   612,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1068,    -1,
      -1,    -1,    -1,   626,   627,    -1,   629,    -1,   124,   632,
      -1,    -1,    -1,    -1,    -1,    -1,  1016,    -1,    -1,    -1,
      -1,   368,    -1,   646,   647,    -1,   649,    -1,    -1,   652,
     377,   378,    -1,    -1,   381,    -1,    -1,    -1,    -1,    -1,
      -1,   388,   389,    -1,    -1,   392,    -1,    -1,    -1,    -1,
     397,   398,    -1,    -1,   401,    -1,    -1,    -1,    -1,    -1,
      -1,   408,   409,    -1,    -1,   412,    -1,    -1,    -1,    -1,
     417,   418,    -1,    -1,   421,    -1,    -1,    -1,    -1,    -1,
      -1,   428,   429,    -1,    -1,   432,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    65,    -1,
      -1,    68,    69,    70,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    -1,    86,
      87,    88,    89,    -1,    -1,    92,    -1,   800,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   810,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   820,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    15,    -1,    -1,    -1,    -1,    20,   595,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   606,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   615,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,   626,
      -1,    54,    55,    56,    57,    58,    59,    60,   635,    62,
      63,    64,    65,    -1,    -1,    68,    69,    70,    -1,   646,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    -1,    86,    87,    88,    89,    -1,    -1,    92,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      75,    76,    -1,    -1,    19,    20,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    33,    34,
      -1,    75,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    89,    90,    91,    92,    54,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,   124,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    74,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
     124,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    33,    34,    -1,    -1,    16,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,   124,
      62,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    63,    64,    65,    27,    -1,    68,    69,    70,
      -1,    33,    34,    -1,    75,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    48,    -1,    89,    -1,
      -1,    92,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,   124,   104,     3,     4,     5,     6,     7,     8,
       9,    10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,   124,    -1,    -1,    -1,    -1,    27,    -1,
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
      -1,    47,    48,    -1,    89,    90,    91,    92,    54,    55,
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
      -1,    -1,    -1,    -1,    47,    48,    -1,    89,    90,    91,
      92,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      -1,   124,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,   124,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    33,    34,    -1,    -1,    16,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,   124,    62,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      20,    21,    -1,    -1,    63,    64,    65,    -1,    -1,    68,
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
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    33,    34,    -1,    75,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    -1,   124,   104,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
       3,     4,     5,     6,     7,     8,     9,    10,   124,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      33,    34,    -1,    -1,    16,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    -1,   124,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
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
       7,     8,     9,    10,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    20,    21,    -1,    -1,    63,    64,    65,
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
      76,    -1,    -1,    -1,    20,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    33,    34,    16,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    70,    71,    72,    -1,    -1,    75,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   124,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,   124,    20,    21,
      54,    55,    56,    57,    58,    59,    60,    -1,    62,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      74,    75,    76,    -1,    -1,    47,    48,    -1,    -1,    20,
      21,    -1,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    74,    75,    76,    -1,    47,    48,    -1,    20,
      21,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
     124,    62,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    74,    75,    76,    47,    48,    -1,    20,
      21,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,   124,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    74,    75,    76,    47,    48,    -1,    -1,
      20,    21,    -1,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    -1,   124,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    74,    75,    76,    -1,    47,    48,    -1,
      -1,    -1,    20,    21,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,   124,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,   124,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      -1,    15,    16,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
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
     175,   175,   238,    62,    74,    76,   124,   187,   277,   126,
     126,    76,   124,   277,    21,   175,   189,   175,   124,   187,
     277,    13,    70,   236,   242,   264,   266,   175,   124,   277,
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

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 241 "parser_1st.y"
                              {return 0;}
#line 3493 "parser_1st.tab.c"
    break;

  case 3:
#line 242 "parser_1st.y"
                                                     {
                    
                    return 0;
                }
#line 3502 "parser_1st.tab.c"
    break;

  case 4:
#line 247 "parser_1st.y"
                          { (yyval.val)=(yyvsp[0].val); }
#line 3508 "parser_1st.tab.c"
    break;

  case 5:
#line 248 "parser_1st.y"
                              {(yyval.val) = (yyvsp[0].val);/*TODO*/}
#line 3514 "parser_1st.tab.c"
    break;

  case 6:
#line 250 "parser_1st.y"
                                {(yyval.val)=(yyvsp[0].val);}
#line 3520 "parser_1st.tab.c"
    break;

  case 7:
#line 251 "parser_1st.y"
                             {(yyval.val) = stringtochar("bool");}
#line 3526 "parser_1st.tab.c"
    break;

  case 8:
#line 253 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3532 "parser_1st.tab.c"
    break;

  case 9:
#line 254 "parser_1st.y"
                                 {(yyval.val)=(yyvsp[0].val);}
#line 3538 "parser_1st.tab.c"
    break;

  case 10:
#line 256 "parser_1st.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3544 "parser_1st.tab.c"
    break;

  case 11:
#line 257 "parser_1st.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 3550 "parser_1st.tab.c"
    break;

  case 12:
#line 258 "parser_1st.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3556 "parser_1st.tab.c"
    break;

  case 13:
#line 259 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3562 "parser_1st.tab.c"
    break;

  case 14:
#line 260 "parser_1st.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3568 "parser_1st.tab.c"
    break;

  case 15:
#line 262 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3574 "parser_1st.tab.c"
    break;

  case 16:
#line 263 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3580 "parser_1st.tab.c"
    break;

  case 17:
#line 265 "parser_1st.y"
                                         {(yyval.val)=(yyvsp[0].val);}
#line 3586 "parser_1st.tab.c"
    break;

  case 18:
#line 267 "parser_1st.y"
                                      {(yyval.val)=(yyvsp[0].val);}
#line 3592 "parser_1st.tab.c"
    break;

  case 19:
#line 269 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val);}
#line 3598 "parser_1st.tab.c"
    break;

  case 20:
#line 271 "parser_1st.y"
                           {(yyval.val)=(yyvsp[0].val); }
#line 3604 "parser_1st.tab.c"
    break;

  case 21:
#line 274 "parser_1st.y"
                                   {(yyval.val)=new_temp(); temp[(yyval.val)]= 1;}
#line 3610 "parser_1st.tab.c"
    break;

  case 22:
#line 275 "parser_1st.y"
                                        {(yyval.val)= new_temp(); temp[(yyval.val)]=temp[(yyvsp[-2].val)]+1;}
#line 3616 "parser_1st.tab.c"
    break;

  case 23:
#line 277 "parser_1st.y"
                            {    (yyval.val) = new_temp();
                                ll curr1 = chartonum((yyval.val));
                                ds[curr1]["type"] = methods[chartostring((yyvsp[0].val))].rettype.name;
                                // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                ds[curr1]["var"] = chartostring((yyvsp[0].val));
                            }
#line 3627 "parser_1st.tab.c"
    break;

  case 24:
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
#line 3649 "parser_1st.tab.c"
    break;

  case 25:
#line 301 "parser_1st.y"
                                                  {/*TODO*/}
#line 3655 "parser_1st.tab.c"
    break;

  case 28:
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
#line 3703 "parser_1st.tab.c"
    break;

  case 36:
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
#line 3720 "parser_1st.tab.c"
    break;

  case 37:
#line 373 "parser_1st.y"
                                                       {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="") assert(checkclassname== chartostring((yyvsp[-1].val)));/*TODO begin class */}
#line 3726 "parser_1st.tab.c"
    break;

  case 38:
#line 374 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val); if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3732 "parser_1st.tab.c"
    break;

  case 39:
#line 375 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3738 "parser_1st.tab.c"
    break;

  case 40:
#line 376 "parser_1st.y"
                                                               {(yyval.val) = (yyvsp[-1].val);if(checkclassname!="")assert(checkclassname== chartostring((yyvsp[-2].val)));}
#line 3744 "parser_1st.tab.c"
    break;

  case 101:
#line 441 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val); curr_class = chartostring((yyval.val)); }
#line 3750 "parser_1st.tab.c"
    break;

  case 166:
#line 508 "parser_1st.y"
           {newscope();}
#line 3756 "parser_1st.tab.c"
    break;

  case 167:
#line 509 "parser_1st.y"
                          {newscope(); }
#line 3762 "parser_1st.tab.c"
    break;

  case 168:
#line 510 "parser_1st.y"
                          {popscope();}
#line 3768 "parser_1st.tab.c"
    break;

  case 208:
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
#line 3801 "parser_1st.tab.c"
    break;

  case 209:
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
#line 3832 "parser_1st.tab.c"
    break;

  case 210:
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
#line 3865 "parser_1st.tab.c"
    break;

  case 211:
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
#line 3907 "parser_1st.tab.c"
    break;

  case 212:
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
#line 3924 "parser_1st.tab.c"
    break;

  case 213:
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
#line 3952 "parser_1st.tab.c"
    break;

  case 214:
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
#line 3993 "parser_1st.tab.c"
    break;

  case 215:
#line 765 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)];}
#line 3999 "parser_1st.tab.c"
    break;

  case 216:
#line 767 "parser_1st.y"
                                       {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[0].val)); 
 int curr = chartonum((yyval.val));

                                            // ds[curr]["type"] = gettypefromsymtable(chartostring($1));
                                            // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                            ds[curr]["var"] = chartostring((yyvsp[0].val));

}
#line 4012 "parser_1st.tab.c"
    break;

  case 217:
#line 775 "parser_1st.y"
                                             {(yyval.val) = new_temp(); generalmap[(yyval.val)].vid.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vid.num = temp[(yyvsp[0].val)];
                        int curr = chartonum((yyval.val));
                                    ds[curr]["var"] = chartostring((yyvsp[-1].val));
                        /*TODO*/
                        }
#line 4022 "parser_1st.tab.c"
    break;

  case 218:
#line 782 "parser_1st.y"
                                    {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[0].val)]; ds[chartonum((yyval.val))] = ds[chartonum((yyvsp[0].val))]; }
#line 4028 "parser_1st.tab.c"
    break;

  case 219:
#line 783 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[0].val);}
#line 4034 "parser_1st.tab.c"
    break;

  case 220:
#line 785 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4040 "parser_1st.tab.c"
    break;

  case 221:
#line 787 "parser_1st.y"
                                                  {
                            (yyval.val) = (yyvsp[0].val);
                        }
#line 4048 "parser_1st.tab.c"
    break;

  case 222:
#line 790 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[0].val);/*TODO CHECK multiple assign*/}
#line 4054 "parser_1st.tab.c"
    break;

  case 223:
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
#line 4073 "parser_1st.tab.c"
    break;

  case 224:
#line 807 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[0].val);}
#line 4079 "parser_1st.tab.c"
    break;

  case 225:
#line 808 "parser_1st.y"
                               {    (yyval.val) = new_temp();
                                    int curr = chartonum((yyval.val));
                                    ds[curr]["type"] = gettypefromsymtable(chartostring((yyvsp[0].val)));
                                    // ds[curr]["lineno"] = get_symbol_table(chartostring($1),"lineno");
                                    ds[curr]["var"] = chartostring((yyvsp[0].val));
                                    /* look here */
                                    ds[curr]["start"] = numtostring(code.size());
                }
#line 4092 "parser_1st.tab.c"
    break;

  case 226:
#line 816 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 4098 "parser_1st.tab.c"
    break;

  case 227:
#line 817 "parser_1st.y"
                                {   (yyval.val) = (yyvsp[0].val);
                                    ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"[ "+ds[chartonum((yyvsp[0].val))]["var"]+" ]";
                }
#line 4106 "parser_1st.tab.c"
    break;

  case 228:
#line 821 "parser_1st.y"
                              {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "=";}
#line 4113 "parser_1st.tab.c"
    break;

  case 229:
#line 823 "parser_1st.y"
                                      {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "*=";}
#line 4120 "parser_1st.tab.c"
    break;

  case 230:
#line 825 "parser_1st.y"
                                     {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "/=";}
#line 4127 "parser_1st.tab.c"
    break;

  case 231:
#line 827 "parser_1st.y"
                                  {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "%=";}
#line 4134 "parser_1st.tab.c"
    break;

  case 232:
#line 829 "parser_1st.y"
                                   {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "+=";}
#line 4141 "parser_1st.tab.c"
    break;

  case 233:
#line 831 "parser_1st.y"
                                    {(yyval.val) = new_temp();int curr = chartonum((yyval.val));
                                ds[curr]["op"] = "-=";}
#line 4148 "parser_1st.tab.c"
    break;

  case 234:
#line 834 "parser_1st.y"
                                    {(yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                                        ds[curr]["start"] = ds[curr1]["start"];
                                        if(ds[curr1]["this"]==chartostring("YES")){
                                            ds[curr]["var"] = chartostring("this.")+chartostring((yyvsp[0].val));
                                        }else assert(0 && "unexpected type\n");
                                        }
#line 4160 "parser_1st.tab.c"
    break;

  case 237:
#line 844 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            if(ds[chartonum((yyval.val))].find("array")!=ds[chartonum((yyval.val))].end())
                            ds[chartonum((yyval.val))]["var"] = ds[chartonum((yyval.val))]["array"]+"["+ds[chartonum((yyvsp[0].val))]["var"]+"]"; }
#line 4168 "parser_1st.tab.c"
    break;

  case 238:
#line 847 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4174 "parser_1st.tab.c"
    break;

  case 239:
#line 849 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 4180 "parser_1st.tab.c"
    break;

  case 240:
#line 850 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4186 "parser_1st.tab.c"
    break;

  case 241:
#line 851 "parser_1st.y"
                                {(yyval.val) = new_temp();    /* Ignoring this as need to send object reference to function as well */
                            int curr = chartonum((yyval.val));
                            ds[curr]["this"] = chartostring("YES");
                            }
#line 4195 "parser_1st.tab.c"
    break;

  case 243:
#line 856 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 4201 "parser_1st.tab.c"
    break;

  case 244:
#line 857 "parser_1st.y"
                                                              {(yyval.val) = (yyvsp[0].val); generalmap[(yyval.val)].isnewclass = true;}
#line 4207 "parser_1st.tab.c"
    break;

  case 245:
#line 858 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4213 "parser_1st.tab.c"
    break;

  case 246:
#line 859 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4219 "parser_1st.tab.c"
    break;

  case 247:
#line 860 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4225 "parser_1st.tab.c"
    break;

  case 249:
#line 863 "parser_1st.y"
                        {(yyval.val) = new_temp();  ds[chartonum((yyval.val))]["type"] = "int"; ds[chartonum((yyval.val))]["var"] = new_var(); ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); tempinitval[ds[chartonum((yyval.val))]["var"]]= chartonum((yyvsp[0].val)); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4231 "parser_1st.tab.c"
    break;

  case 250:
#line 864 "parser_1st.y"
                                     {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "float"; ds[chartonum((yyval.val))]["start"] = numtostring(code.size());ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4237 "parser_1st.tab.c"
    break;

  case 251:
#line 865 "parser_1st.y"
                               {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "bool";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4243 "parser_1st.tab.c"
    break;

  case 252:
#line 866 "parser_1st.y"
                                 {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "char";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4249 "parser_1st.tab.c"
    break;

  case 253:
#line 867 "parser_1st.y"
                              {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4255 "parser_1st.tab.c"
    break;

  case 254:
#line 868 "parser_1st.y"
                          {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "String";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4261 "parser_1st.tab.c"
    break;

  case 255:
#line 869 "parser_1st.y"
                            {(yyval.val) = new_temp(); ds[chartonum((yyval.val))]["type"] = "null";ds[chartonum((yyval.val))]["start"] = numtostring(code.size()); ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ chartostring((yyvsp[0].val)));}
#line 4267 "parser_1st.tab.c"
    break;

  case 265:
#line 882 "parser_1st.y"
                                                                            {(yyval.val) = (yyvsp[0].val);}
#line 4273 "parser_1st.tab.c"
    break;

  case 269:
#line 887 "parser_1st.y"
                                                                                                           {(yyval.val) = new_temp(); generalmap[(yyval.val)].isnewclass = true; generalmap[(yyval.val)].classname = ds[ chartonum((yyvsp[-2].val))]["var"]; ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-2].val))];  }
#line 4279 "parser_1st.tab.c"
    break;

  case 270:
#line 888 "parser_1st.y"
                                                                                                                     {/*TODO*/}
#line 4285 "parser_1st.tab.c"
    break;

  case 271:
#line 889 "parser_1st.y"
                                                                                                                        {/*TODO*/}
#line 4291 "parser_1st.tab.c"
    break;

  case 272:
#line 890 "parser_1st.y"
                                                                                                                                  {/*TODO*/}
#line 4297 "parser_1st.tab.c"
    break;

  case 277:
#line 896 "parser_1st.y"
                                                {   (yyval.val) = new_temp(); ds[ chartonum((yyval.val))]["var"] = chartostring((yyvsp[0].val)); ds[ chartonum((yyval.val))]["class"] = "true";
                                                     }
#line 4304 "parser_1st.tab.c"
    break;

  case 278:
#line 899 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);
                            ds2[chartonum((yyval.val))]["type"].push_back(ds[chartonum((yyvsp[0].val))]["type"]);
                            ds2[chartonum((yyval.val))]["var"].push_back(ds[chartonum((yyvsp[0].val))]["var"]);
                            }
#line 4313 "parser_1st.tab.c"
    break;

  case 279:
#line 903 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                ds[curr]["start"] = ds[curr1]["start"];
                                                ds2[curr1]["type"].push_back(ds[curr3]["type"]);
                                                ds2[curr]["type"] = ds2[curr1]["type"];
                                                ds2[curr1]["var"].push_back(ds[curr3]["var"]);
                                                ds2[curr]["var"] = ds2[curr1]["var"];
                                                }
#line 4326 "parser_1st.tab.c"
    break;

  case 280:
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
#line 4343 "parser_1st.tab.c"
    break;

  case 281:
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
#line 4367 "parser_1st.tab.c"
    break;

  case 282:
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
#line 4396 "parser_1st.tab.c"
    break;

  case 283:
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
#line 4428 "parser_1st.tab.c"
    break;

  case 312:
#line 1026 "parser_1st.y"
                                                         {/*NOT SUPPORTED*/}
#line 4434 "parser_1st.tab.c"
    break;

  case 313:
#line 1027 "parser_1st.y"
                                                                       {/*NOT SUPPORTED*/}
#line 4440 "parser_1st.tab.c"
    break;

  case 314:
#line 1028 "parser_1st.y"
                                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-2].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; assert (generalmap[(yyvsp[0].val)].vinit.dims.size() == temp[(yyvsp[-1].val)]); }
#line 4446 "parser_1st.tab.c"
    break;

  case 315:
#line 1029 "parser_1st.y"
                                                                               {/*NOT SUPPORTED*/}
#line 4452 "parser_1st.tab.c"
    break;

  case 316:
#line 1030 "parser_1st.y"
                                                        { (yyval.val) = new_temp();  generalmap[(yyval.val)].typ.name= chartostring((yyvsp[-1].val));  generalmap[(yyval.val)].vinit = generalmap[(yyvsp[0].val)].vinit; reverse(all(generalmap[(yyval.val)].vinit.dims)); ds[chartonum((yyval.val))]["arr"] = "true"; ds[chartonum((yyval.val))]["var"] = new_var(); code.push_back(ds[chartonum((yyval.val))]["var"]+ " = "+ ds[chartonum((yyvsp[0].val))]["var"]+" * "+numtostring(gettypesize(chartostring((yyvsp[-1].val))))); ds[chartonum((yyval.val))]["type"] = chartostring((yyvsp[-1].val)); ds[chartonum((yyval.val))]["start"] = ds[chartonum((yyvsp[0].val))]["start"];}
#line 4458 "parser_1st.tab.c"
    break;

  case 317:
#line 1031 "parser_1st.y"
                                                                   {/*NOT SUPPORTED*/}
#line 4464 "parser_1st.tab.c"
    break;

  case 318:
#line 1032 "parser_1st.y"
                                                   {/*NOT SUPPORTED*/}
#line 4470 "parser_1st.tab.c"
    break;

  case 319:
#line 1033 "parser_1st.y"
                                                              {/*NOT SUPPORTED*/}
#line 4476 "parser_1st.tab.c"
    break;

  case 320:
#line 1034 "parser_1st.y"
                                               {/*TODO whats this*/}
#line 4482 "parser_1st.tab.c"
    break;

  case 321:
#line 1035 "parser_1st.y"
                                                         {/*TODO whats this*/}
#line 4488 "parser_1st.tab.c"
    break;

  case 322:
#line 1037 "parser_1st.y"
                                                              {(yyval.val)=(yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyval.val)].num); generalmap[(yyval.val)].num=0;}
#line 4494 "parser_1st.tab.c"
    break;

  case 323:
#line 1038 "parser_1st.y"
                                             {(yyval.val)=new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(0);}
#line 4500 "parser_1st.tab.c"
    break;

  case 324:
#line 1040 "parser_1st.y"
                                               {(yyval.val)= (yyvsp[0].val);}
#line 4506 "parser_1st.tab.c"
    break;

  case 325:
#line 1041 "parser_1st.y"
                              {(yyval.val) = new_temp(); generalmap[(yyval.val)].num=2;}
#line 4512 "parser_1st.tab.c"
    break;

  case 326:
#line 1042 "parser_1st.y"
                                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].num++;}
#line 4518 "parser_1st.tab.c"
    break;

  case 327:
#line 1044 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[0].val))];}
#line 4524 "parser_1st.tab.c"
    break;

  case 328:
#line 1045 "parser_1st.y"
                             {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].vinit.dims.push_back(generalmap[(yyvsp[0].val)].num); string t = new_var(); 
                              code.push_back(t+" = "+ds[ chartonum((yyvsp[-1].val))]["var"]+" *"+ds[chartonum((yyvsp[0].val))]["type"]+" "+ds[ chartonum((yyvsp[0].val))]["var"]);
                              ds[ chartonum((yyval.val))]["var"] = t;  }
#line 4532 "parser_1st.tab.c"
    break;

  case 329:
#line 1049 "parser_1st.y"
                                            {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = varaddrstoint(ds[chartonum((yyvsp[-1].val))]["var"]); ds[ chartonum((yyval.val))] = ds[ chartonum((yyvsp[-1].val))];}
#line 4538 "parser_1st.tab.c"
    break;

  case 330:
#line 1051 "parser_1st.y"
                                                {(yyval.val)=(yyvsp[0].val); generalmap[(yyval.val)].num=1;}
#line 4544 "parser_1st.tab.c"
    break;

  case 331:
#line 1052 "parser_1st.y"
                                                                              {(yyval.val)=(yyvsp[-2].val); generalmap[(yyval.val)].num++; assert(generalmap[(yyval.val)].vinit.dims == generalmap[(yyvsp[0].val)].vinit.dims);}
#line 4550 "parser_1st.tab.c"
    break;

  case 333:
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
#line 4578 "parser_1st.tab.c"
    break;

  case 334:
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
#line 4596 "parser_1st.tab.c"
    break;

  case 335:
#line 1096 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4602 "parser_1st.tab.c"
    break;

  case 336:
#line 1097 "parser_1st.y"
                                                                                                    {}
#line 4608 "parser_1st.tab.c"
    break;

  case 337:
#line 1099 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4614 "parser_1st.tab.c"
    break;

  case 338:
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
#line 4632 "parser_1st.tab.c"
    break;

  case 339:
#line 1114 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); }
#line 4638 "parser_1st.tab.c"
    break;

  case 340:
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
#line 4652 "parser_1st.tab.c"
    break;

  case 341:
#line 1125 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[0].val);}
#line 4658 "parser_1st.tab.c"
    break;

  case 342:
#line 1126 "parser_1st.y"
                                                                        {    (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"|");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " | " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4671 "parser_1st.tab.c"
    break;

  case 343:
#line 1135 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val); }
#line 4677 "parser_1st.tab.c"
    break;

  case 344:
#line 1136 "parser_1st.y"
                                                                {           (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"^");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " ^ " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                      }
#line 4690 "parser_1st.tab.c"
    break;

  case 345:
#line 1144 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); }
#line 4696 "parser_1st.tab.c"
    break;

  case 346:
#line 1145 "parser_1st.y"
                                                        {   (yyval.val) = new_temp();
                                                                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                            ds[curr]["var"] = new_var();
                                                                            type_check(ds[curr1]["type"],ds[curr3]["type"],"&");
                                                                            code.push_back(ds[curr]["var"] + " = " + ds[curr1]["var"] + " & " + ds[curr3]["var"]);
                                                                            ds[curr]["type"] = "int";
                                                                            ds[curr]["start"] = ds[curr1]["start"];
                                                                            
                      }
#line 4710 "parser_1st.tab.c"
    break;

  case 347:
#line 1155 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }
                                            
                                                                                // cout<<"truelist "<<ds3[curr]["truelist"].size()<<"\n";
                                        }
#line 4723 "parser_1st.tab.c"
    break;

  case 348:
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
#line 4744 "parser_1st.tab.c"
    break;

  case 349:
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
#line 4766 "parser_1st.tab.c"
    break;

  case 350:
#line 1197 "parser_1st.y"
                                        {   (yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val));
                                            if(ds3[curr].find("truelist")==ds3[curr].end()){
                                                ds3[curr]["truelist"] = vector<int>();
                                                ds3[curr]["falselist"] = vector<int>();
                                            }}
#line 4776 "parser_1st.tab.c"
    break;

  case 351:
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
#line 4799 "parser_1st.tab.c"
    break;

  case 352:
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
#line 4818 "parser_1st.tab.c"
    break;

  case 353:
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
#line 4837 "parser_1st.tab.c"
    break;

  case 354:
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
#line 4856 "parser_1st.tab.c"
    break;

  case 356:
#line 1264 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 4862 "parser_1st.tab.c"
    break;

  case 357:
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
#line 4876 "parser_1st.tab.c"
    break;

  case 358:
#line 1274 "parser_1st.y"
                                                                                        {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4889 "parser_1st.tab.c"
    break;

  case 359:
#line 1282 "parser_1st.y"
                                                                                                {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],">>>");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" >>> "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4902 "parser_1st.tab.c"
    break;

  case 360:
#line 1291 "parser_1st.y"
                                                {   (yyval.val) = (yyvsp[0].val); }
#line 4908 "parser_1st.tab.c"
    break;

  case 361:
#line 1292 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"+");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" +"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4921 "parser_1st.tab.c"
    break;

  case 362:
#line 1300 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"-");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" -"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4934 "parser_1st.tab.c"
    break;

  case 363:
#line 1309 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 4940 "parser_1st.tab.c"
    break;

  case 364:
#line 1310 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"*");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" *"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4953 "parser_1st.tab.c"
    break;

  case 365:
#line 1318 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"/");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" /"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4966 "parser_1st.tab.c"
    break;

  case 366:
#line 1326 "parser_1st.y"
                                                                                    {   (yyval.val) = new_temp();
                                                                                int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)), curr3 = chartonum((yyvsp[0].val));
                                                                                type_check(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                ds[curr]["var"] = new_var();
                                                                                ds[curr]["type"] = type_conversion(ds[curr1]["type"],ds[curr3]["type"],"%");
                                                                                code.push_back(ds[curr]["var"]+" = "+ds[curr1]["var"]+" %"+ds[curr]["type"]+" "+ds[curr3]["var"]);
                                                                                ds[curr]["start"] = ds[curr1]["start"];
                }
#line 4979 "parser_1st.tab.c"
    break;

  case 367:
#line 1335 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 4985 "parser_1st.tab.c"
    break;

  case 368:
#line 1336 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 4991 "parser_1st.tab.c"
    break;

  case 369:
#line 1337 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                            type_check_unary(ds[curr2]["type"],"+");}
#line 4999 "parser_1st.tab.c"
    break;

  case 370:
#line 1340 "parser_1st.y"
                                                {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"-");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = - "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5012 "parser_1st.tab.c"
    break;

  case 371:
#line 1348 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5018 "parser_1st.tab.c"
    break;

  case 372:
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
#line 5036 "parser_1st.tab.c"
    break;

  case 373:
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
#line 5054 "parser_1st.tab.c"
    break;

  case 374:
#line 1378 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5060 "parser_1st.tab.c"
    break;

  case 375:
#line 1379 "parser_1st.y"
                                                            {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"~");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ~ "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5073 "parser_1st.tab.c"
    break;

  case 376:
#line 1387 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                                int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                                type_check_unary(ds[curr2]["type"],"!");
                                                ds[curr]["var"] = new_var();
                                                code.push_back(ds[curr]["var"]+" = ! "+ds[curr2]["var"]);
                                                ds[curr]["type"] = ds[curr2]["type"];
                                                ds[curr]["start"] = ds[curr2]["start"];
                    }
#line 5086 "parser_1st.tab.c"
    break;

  case 377:
#line 1396 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5092 "parser_1st.tab.c"
    break;

  case 378:
#line 1397 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);}
#line 5098 "parser_1st.tab.c"
    break;

  case 379:
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
#line 5117 "parser_1st.tab.c"
    break;

  case 380:
#line 1412 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5123 "parser_1st.tab.c"
    break;

  case 381:
#line 1413 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5129 "parser_1st.tab.c"
    break;

  case 382:
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
#line 5146 "parser_1st.tab.c"
    break;

  case 383:
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
#line 5165 "parser_1st.tab.c"
    break;

  case 385:
#line 1446 "parser_1st.y"
                                            {
    (yyval.val) =(yyvsp[-1].val);
    method_det[curr_class][ds[chartonum((yyval.val))]["method_name"]].end = code.size(); 
    
    for(auto i:ds2[chartonum((yyval.val))]["param"])
    code.push_back("pop param, "+ i);
    code.push_back("end func");
    // cout<<"method declaration"<<generalmap[$1].name<<endl;
}
#line 5179 "parser_1st.tab.c"
    break;

  case 386:
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
#line 5209 "parser_1st.tab.c"
    break;

  case 387:
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
#line 5238 "parser_1st.tab.c"
    break;

  case 388:
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
#line 5267 "parser_1st.tab.c"
    break;

  case 389:
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
#line 5296 "parser_1st.tab.c"
    break;

  case 395:
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
#line 5345 "parser_1st.tab.c"
    break;

  case 396:
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
#line 5380 "parser_1st.tab.c"
    break;

  case 407:
#line 1650 "parser_1st.y"
                                                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-2].val));
 int curr = chartonum((yyval.val));              
                                        method_det[curr_class][chartostring((yyvsp[-2].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-2].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-2].val)));
                                        // cout<<"methodhead "<<ds[chartonum($$)]["method_name"]<<"\n";
                                        }
#line 5393 "parser_1st.tab.c"
    break;

  case 408:
#line 1658 "parser_1st.y"
                                                                        {(yyval.val) = new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-1].val)]; generalmap[(yyval.val)].num = 0; generalmap[(yyval.val)].name = chartostring((yyvsp[-3].val));int curr = chartonum((yyval.val)), curr3 = chartonum((yyvsp[-1].val));
                method_det[curr_class][chartostring((yyvsp[-3].val))].start = code.size(); 
                                        ds[curr]["start"] = numtostring(code.size());
                                        ds[curr]["method_name"] = chartostring((yyvsp[-3].val));
                                        code.push_back("begin func "+chartostring((yyvsp[-3].val)));
                                        // for(auto i:ds2[curr3]["param"])
                                        // code.push_back("pop param, "+ i);
                                        ds2[curr]["param"] = ds2[curr3]["param"];}
#line 5406 "parser_1st.tab.c"
    break;

  case 417:
#line 1676 "parser_1st.y"
                                     { (yyval.val) = new_temp(); generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);                                        int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr]["param"] = vector<string>();
                                        ds2[curr]["param"].push_back(ds[curr1]["var"]);}
#line 5415 "parser_1st.tab.c"
    break;

  case 418:
#line 1680 "parser_1st.y"
                                                                  {(yyval.val)= new_temp(); generalmap[(yyval.val)]= generalmap[(yyvsp[-2].val)]; generalmap[(yyval.val)].farglist.push_back(generalmap[(yyvsp[0].val)].farg);   int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val)),curr3 = chartonum((yyvsp[0].val));
                                        // ds[curr]["var"] = ds[curr2]["var"];
                                        ds2[curr1]["param"].push_back(ds[curr3]["var"]);
                                        ds2[curr]["param"] = ds2[curr1]["param"];
                                        }
#line 5425 "parser_1st.tab.c"
    break;

  case 419:
#line 1686 "parser_1st.y"
                                            { (yyval.val) = new_temp(); generalmap[(yyval.val)].farg.typ.name = chartostring((yyvsp[-1].val)); generalmap[(yyval.val)].farg.typ.dims = generalmap[(yyvsp[0].val)].vid.num; generalmap[(yyval.val)].farg.vid = generalmap[(yyvsp[0].val)].vid;
     int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[0].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
                                        }
#line 5434 "parser_1st.tab.c"
    break;

  case 421:
#line 1691 "parser_1st.y"
                                                    {   (yyval.val) = new_temp();
                                        int curr = chartonum((yyval.val)), curr2 = chartonum((yyvsp[-1].val));
                                        ds[curr]["var"] = ds[curr2]["var"];
}
#line 5443 "parser_1st.tab.c"
    break;

  case 424:
#line 1701 "parser_1st.y"
                    {(yyval.val) = (yyvsp[0].val);}
#line 5449 "parser_1st.tab.c"
    break;

  case 428:
#line 1708 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val);  }
#line 5455 "parser_1st.tab.c"
    break;

  case 430:
#line 1711 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[0].val);  
                                                    // code.push_back("start = "+ds[chartonum($$)]["start"]);
}
#line 5463 "parser_1st.tab.c"
    break;

  case 431:
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
#line 5478 "parser_1st.tab.c"
    break;

  case 433:
#line 1726 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val); 
                
               }
#line 5486 "parser_1st.tab.c"
    break;

  case 434:
#line 1729 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
               }
#line 5493 "parser_1st.tab.c"
    break;

  case 435:
#line 1731 "parser_1st.y"
                            {code.push_back("print "+ chartostring((yyvsp[0].val)).substr(19,chartostring((yyvsp[0].val)).size() -21));}
#line 5499 "parser_1st.tab.c"
    break;

  case 437:
#line 1735 "parser_1st.y"
                                                                        {(yyval.val) = (yyvsp[-1].val);}
#line 5505 "parser_1st.tab.c"
    break;

  case 438:
#line 1737 "parser_1st.y"
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
#line 5567 "parser_1st.tab.c"
    break;

  case 439:
#line 1794 "parser_1st.y"
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
#line 5633 "parser_1st.tab.c"
    break;

  case 440:
#line 1856 "parser_1st.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 5639 "parser_1st.tab.c"
    break;

  case 441:
#line 1857 "parser_1st.y"
                            {(yyval.val) = (yyvsp[0].val);}
#line 5645 "parser_1st.tab.c"
    break;

  case 442:
#line 1860 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size()); }
#line 5651 "parser_1st.tab.c"
    break;

  case 443:
#line 1861 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5657 "parser_1st.tab.c"
    break;

  case 444:
#line 1862 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5663 "parser_1st.tab.c"
    break;

  case 445:
#line 1863 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5669 "parser_1st.tab.c"
    break;

  case 446:
#line 1864 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5675 "parser_1st.tab.c"
    break;

  case 447:
#line 1865 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val); int curr = chartonum((yyval.val)); if(ds[curr].find("start")==ds[curr].end()) ds[curr]["start"] = numtostring(code.size());}
#line 5681 "parser_1st.tab.c"
    break;

  case 448:
#line 1867 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5687 "parser_1st.tab.c"
    break;

  case 449:
#line 1869 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5693 "parser_1st.tab.c"
    break;

  case 450:
#line 1870 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5699 "parser_1st.tab.c"
    break;

  case 451:
#line 1871 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5705 "parser_1st.tab.c"
    break;

  case 452:
#line 1872 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5711 "parser_1st.tab.c"
    break;

  case 453:
#line 1873 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5717 "parser_1st.tab.c"
    break;

  case 454:
#line 1874 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5723 "parser_1st.tab.c"
    break;

  case 455:
#line 1875 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5729 "parser_1st.tab.c"
    break;

  case 456:
#line 1876 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5735 "parser_1st.tab.c"
    break;

  case 457:
#line 1878 "parser_1st.y"
                            {(yyval.val) = new_temp();}
#line 5741 "parser_1st.tab.c"
    break;

  case 458:
#line 1880 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[-1].val); }
#line 5747 "parser_1st.tab.c"
    break;

  case 459:
#line 1882 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);}
#line 5753 "parser_1st.tab.c"
    break;

  case 460:
#line 1883 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5759 "parser_1st.tab.c"
    break;

  case 461:
#line 1884 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5765 "parser_1st.tab.c"
    break;

  case 462:
#line 1885 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5771 "parser_1st.tab.c"
    break;

  case 463:
#line 1886 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5777 "parser_1st.tab.c"
    break;

  case 464:
#line 1887 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 5783 "parser_1st.tab.c"
    break;

  case 465:
#line 1888 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5789 "parser_1st.tab.c"
    break;

  case 468:
#line 1893 "parser_1st.y"
                                    {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["breaklist"] = vector<int>();
                                            ds3[curr]["breaklist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5802 "parser_1st.tab.c"
    break;

  case 470:
#line 1903 "parser_1st.y"
                                        {   (yyval.val) = new_temp();
                                            int curr = chartonum((yyval.val));
                                            ds3[curr]["continuelist"] = vector<int>();
                                            ds3[curr]["continuelist"].push_back(code.size());
                                            ds[curr]["start"] = numtostring(code.size());
                                            code.push_back("goto ");
                                            ds[curr]["type"] = "null";
}
#line 5815 "parser_1st.tab.c"
    break;

  case 472:
#line 1913 "parser_1st.y"
                                                {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val)), exp = chartonum((yyvsp[-1].val));
                                                    ds[curr]["start"] = ds[exp]["start"];
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return "+ds[exp]["var"]);
                                                }
#line 5826 "parser_1st.tab.c"
    break;

  case 473:
#line 1919 "parser_1st.y"
                                        {(yyval.val) = new_temp();
                                                    int curr = chartonum((yyval.val));
                                                    ds[curr]["start"] = numtostring(code.size());
                                                    ds[curr]["type"]= "null";
                                                    code.push_back("return");
                                                }
#line 5837 "parser_1st.tab.c"
    break;

  case 477:
#line 1932 "parser_1st.y"
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
#line 5858 "parser_1st.tab.c"
    break;

  case 478:
#line 1949 "parser_1st.y"
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
#line 5877 "parser_1st.tab.c"
    break;

  case 479:
#line 1964 "parser_1st.y"
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
#line 5908 "parser_1st.tab.c"
    break;

  case 480:
#line 1991 "parser_1st.y"
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
#line 5924 "parser_1st.tab.c"
    break;

  case 481:
#line 2003 "parser_1st.y"
                                                            {(yyval.val) = (yyvsp[0].val);}
#line 5930 "parser_1st.tab.c"
    break;

  case 482:
#line 2004 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val);}
#line 5936 "parser_1st.tab.c"
    break;

  case 483:
#line 2005 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);}
#line 5942 "parser_1st.tab.c"
    break;

  case 484:
#line 2006 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5948 "parser_1st.tab.c"
    break;

  case 485:
#line 2007 "parser_1st.y"
                                                {(yyval.val) = (yyvsp[0].val);}
#line 5954 "parser_1st.tab.c"
    break;

  case 487:
#line 2011 "parser_1st.y"
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
#line 5970 "parser_1st.tab.c"
    break;

  case 488:
#line 2023 "parser_1st.y"
                                                    {(yyval.val) = (yyvsp[0].val); popscope();}
#line 5976 "parser_1st.tab.c"
    break;

  case 489:
#line 2024 "parser_1st.y"
                                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 5982 "parser_1st.tab.c"
    break;

  case 490:
#line 2027 "parser_1st.y"
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
#line 5997 "parser_1st.tab.c"
    break;

  case 491:
#line 2038 "parser_1st.y"
                                {(yyval.val) = (yyvsp[0].val);popscope();}
#line 6003 "parser_1st.tab.c"
    break;

  case 492:
#line 2039 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[0].val);popscope();}
#line 6009 "parser_1st.tab.c"
    break;

  case 493:
#line 2041 "parser_1st.y"
                                                                            {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6022 "parser_1st.tab.c"
    break;

  case 494:
#line 2049 "parser_1st.y"
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
#line 6038 "parser_1st.tab.c"
    break;

  case 495:
#line 2060 "parser_1st.y"
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
#line 6057 "parser_1st.tab.c"
    break;

  case 496:
#line 2074 "parser_1st.y"
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
#line 6078 "parser_1st.tab.c"
    break;

  case 497:
#line 2090 "parser_1st.y"
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
#line 6096 "parser_1st.tab.c"
    break;

  case 498:
#line 2103 "parser_1st.y"
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
#line 6117 "parser_1st.tab.c"
    break;

  case 499:
#line 2119 "parser_1st.y"
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
#line 6138 "parser_1st.tab.c"
    break;

  case 500:
#line 2135 "parser_1st.y"
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
#line 6159 "parser_1st.tab.c"
    break;

  case 501:
#line 2152 "parser_1st.y"
                                                                                              {   (yyval.val) = new_temp();
                                                                    int curr = chartonum((yyval.val)), curr6 = chartonum((yyvsp[0].val));
                                                                    backpatch(ds3[curr6]["continuelist"],stringtonum(ds[curr6]["start"])); 
                                                                    ds[curr]["type"] = "null";
                                                                    ds[curr]["start"] = ds[curr6]["start"];
                                                                    code.push_back("goto "+ds[curr]["start"]);
                                                                    backpatch(ds3[curr6]["breaklist"],code.size()); 
}
#line 6172 "parser_1st.tab.c"
    break;

  case 502:
#line 2160 "parser_1st.y"
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
#line 6188 "parser_1st.tab.c"
    break;

  case 503:
#line 2171 "parser_1st.y"
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
#line 6207 "parser_1st.tab.c"
    break;

  case 504:
#line 2185 "parser_1st.y"
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
#line 6229 "parser_1st.tab.c"
    break;

  case 505:
#line 2202 "parser_1st.y"
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
#line 6247 "parser_1st.tab.c"
    break;

  case 506:
#line 2215 "parser_1st.y"
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
#line 6268 "parser_1st.tab.c"
    break;

  case 507:
#line 2231 "parser_1st.y"
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
#line 6290 "parser_1st.tab.c"
    break;

  case 508:
#line 2248 "parser_1st.y"
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
#line 6311 "parser_1st.tab.c"
    break;

  case 511:
#line 2270 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);}
#line 6317 "parser_1st.tab.c"
    break;

  case 512:
#line 2271 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[0].val);}
#line 6323 "parser_1st.tab.c"
    break;

  case 513:
#line 2273 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[0].val);
                                        int curr = chartonum((yyval.val));
                                        ds2[curr]["code"] = vector<string>();
                                        for(int i=stringtonum(ds[curr]["start"]);i<code.size();i++){
                                            ds2[curr]["code"].push_back(code[i]);
                                        }
                                        for(int i=0;i<ds2[curr]["code"].size();i++)
                                        code.pop_back();
                                        }
#line 6337 "parser_1st.tab.c"
    break;

  case 514:
#line 2283 "parser_1st.y"
                                             {(yyval.val) = (yyvsp[0].val);}
#line 6343 "parser_1st.tab.c"
    break;

  case 515:
#line 2284 "parser_1st.y"
                                                                              {

                            (yyval.val) = new_temp();
                            int curr = chartonum((yyval.val)), curr1 = chartonum((yyvsp[-2].val));
                            ds[curr]["start"] = ds[curr1]["start"];

                        }
#line 6355 "parser_1st.tab.c"
    break;

  case 553:
#line 2337 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6361 "parser_1st.tab.c"
    break;

  case 554:
#line 2338 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6367 "parser_1st.tab.c"
    break;

  case 555:
#line 2339 "parser_1st.y"
                    {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6373 "parser_1st.tab.c"
    break;

  case 556:
#line 2340 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6379 "parser_1st.tab.c"
    break;

  case 557:
#line 2341 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6385 "parser_1st.tab.c"
    break;

  case 558:
#line 2342 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6391 "parser_1st.tab.c"
    break;

  case 559:
#line 2344 "parser_1st.y"
                {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6397 "parser_1st.tab.c"
    break;

  case 560:
#line 2345 "parser_1st.y"
                 {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6403 "parser_1st.tab.c"
    break;

  case 561:
#line 2346 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6409 "parser_1st.tab.c"
    break;

  case 562:
#line 2347 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6415 "parser_1st.tab.c"
    break;

  case 563:
#line 2348 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6421 "parser_1st.tab.c"
    break;

  case 564:
#line 2349 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6427 "parser_1st.tab.c"
    break;

  case 565:
#line 2350 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6433 "parser_1st.tab.c"
    break;

  case 566:
#line 2351 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6439 "parser_1st.tab.c"
    break;

  case 567:
#line 2352 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6445 "parser_1st.tab.c"
    break;

  case 568:
#line 2354 "parser_1st.y"
                  {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6451 "parser_1st.tab.c"
    break;

  case 569:
#line 2355 "parser_1st.y"
                   {(yyval.val) = new_temp(); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6457 "parser_1st.tab.c"
    break;

  case 570:
#line 2356 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6463 "parser_1st.tab.c"
    break;

  case 571:
#line 2357 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6469 "parser_1st.tab.c"
    break;

  case 572:
#line 2358 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6475 "parser_1st.tab.c"
    break;

  case 573:
#line 2359 "parser_1st.y"
                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6481 "parser_1st.tab.c"
    break;

  case 574:
#line 2360 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6487 "parser_1st.tab.c"
    break;

  case 575:
#line 2361 "parser_1st.y"
                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6493 "parser_1st.tab.c"
    break;

  case 576:
#line 2362 "parser_1st.y"
                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6499 "parser_1st.tab.c"
    break;

  case 577:
#line 2363 "parser_1st.y"
                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6505 "parser_1st.tab.c"
    break;

  case 578:
#line 2364 "parser_1st.y"
                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6511 "parser_1st.tab.c"
    break;

  case 579:
#line 2366 "parser_1st.y"
                                 {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6517 "parser_1st.tab.c"
    break;

  case 580:
#line 2367 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6523 "parser_1st.tab.c"
    break;

  case 581:
#line 2368 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6529 "parser_1st.tab.c"
    break;

  case 582:
#line 2369 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6535 "parser_1st.tab.c"
    break;

  case 583:
#line 2370 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6541 "parser_1st.tab.c"
    break;

  case 584:
#line 2371 "parser_1st.y"
                                     {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6547 "parser_1st.tab.c"
    break;

  case 585:
#line 2372 "parser_1st.y"
                                       {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6553 "parser_1st.tab.c"
    break;

  case 586:
#line 2373 "parser_1st.y"
                                    {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6559 "parser_1st.tab.c"
    break;

  case 587:
#line 2374 "parser_1st.y"
                                   {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6565 "parser_1st.tab.c"
    break;

  case 588:
#line 2377 "parser_1st.y"
                                      {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6571 "parser_1st.tab.c"
    break;

  case 589:
#line 2378 "parser_1st.y"
                                {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6577 "parser_1st.tab.c"
    break;

  case 590:
#line 2379 "parser_1st.y"
                                               {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6583 "parser_1st.tab.c"
    break;

  case 591:
#line 2380 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6589 "parser_1st.tab.c"
    break;

  case 592:
#line 2381 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6595 "parser_1st.tab.c"
    break;

  case 593:
#line 2382 "parser_1st.y"
                                           {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6601 "parser_1st.tab.c"
    break;

  case 594:
#line 2383 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6607 "parser_1st.tab.c"
    break;

  case 595:
#line 2384 "parser_1st.y"
                                          {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6613 "parser_1st.tab.c"
    break;

  case 596:
#line 2385 "parser_1st.y"
                                            {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6619 "parser_1st.tab.c"
    break;

  case 597:
#line 2386 "parser_1st.y"
                                         {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6625 "parser_1st.tab.c"
    break;

  case 598:
#line 2387 "parser_1st.y"
                                        {(yyval.val) = (yyvsp[-1].val); generalmap[(yyval.val)].modifiers.push_back(chartostring((yyvsp[0].val)));}
#line 6631 "parser_1st.tab.c"
    break;

  case 602:
#line 2394 "parser_1st.y"
                                  {(yyval.val)=(yyvsp[0].val);}
#line 6637 "parser_1st.tab.c"
    break;

  case 603:
#line 2395 "parser_1st.y"
                             {(yyval.val)=(yyvsp[0].val);}
#line 6643 "parser_1st.tab.c"
    break;

  case 608:
#line 2404 "parser_1st.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 6649 "parser_1st.tab.c"
    break;


#line 6653 "parser_1st.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2406 "parser_1st.y"



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
