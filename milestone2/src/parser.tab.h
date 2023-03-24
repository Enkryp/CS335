/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BOOLEAN = 258,                 /* BOOLEAN  */
    BYTE = 259,                    /* BYTE  */
    SHORT = 260,                   /* SHORT  */
    INT = 261,                     /* INT  */
    LONG = 262,                    /* LONG  */
    CHAR = 263,                    /* CHAR  */
    FLOAT = 264,                   /* FLOAT  */
    DOUBLE = 265,                  /* DOUBLE  */
    COMMA = 266,                   /* COMMA  */
    QUESTIONMARK = 267,            /* QUESTIONMARK  */
    SEMICOLON = 268,               /* SEMICOLON  */
    OPENCURLY1 = 269,              /* OPENCURLY1  */
    CLOSECURLY1 = 270,             /* CLOSECURLY1  */
    ANGULARLEFT = 271,             /* ANGULARLEFT  */
    ANGULARRIGHT = 272,            /* ANGULARRIGHT  */
    OPENSQUARE = 273,              /* OPENSQUARE  */
    CLOSESQUARE = 274,             /* CLOSESQUARE  */
    OPENPARAN = 275,               /* OPENPARAN  */
    CLOSEPARAN = 276,              /* CLOSEPARAN  */
    DOUBLECOLON = 277,             /* DOUBLECOLON  */
    TRIPLEDOT = 278,               /* TRIPLEDOT  */
    WS = 279,                      /* WS  */
    AT = 280,                      /* AT  */
    OVERRIDE = 281,                /* OVERRIDE  */
    EQUALS = 282,                  /* EQUALS  */
    MULTIPLYEQUALS = 283,          /* MULTIPLYEQUALS  */
    DIVIDEEQUALS = 284,            /* DIVIDEEQUALS  */
    MODEQUALS = 285,               /* MODEQUALS  */
    PLUSEQUALS = 286,              /* PLUSEQUALS  */
    MINUSEQUALS = 287,             /* MINUSEQUALS  */
    PLUS = 288,                    /* PLUS  */
    MINUS = 289,                   /* MINUS  */
    DIVIDE = 290,                  /* DIVIDE  */
    MULTIPLY = 291,                /* MULTIPLY  */
    MOD = 292,                     /* MOD  */
    OR = 293,                      /* OR  */
    XOR = 294,                     /* XOR  */
    COLON = 295,                   /* COLON  */
    NOT = 296,                     /* NOT  */
    COMPLEMENT = 297,              /* COMPLEMENT  */
    AND = 298,                     /* AND  */
    DOT = 299,                     /* DOT  */
    OROR = 300,                    /* OROR  */
    ANDAND = 301,                  /* ANDAND  */
    PLUSPLUS = 302,                /* PLUSPLUS  */
    MINUSMINUS = 303,              /* MINUSMINUS  */
    ANGULARLEFTANGULARLEFT = 304,  /* ANGULARLEFTANGULARLEFT  */
    ANGULARRIGHTANGULARRIGHT = 305, /* ANGULARRIGHTANGULARRIGHT  */
    ANGULARRIGHTANGULARRIGHTANGULARRIGHT = 306, /* ANGULARRIGHTANGULARRIGHTANGULARRIGHT  */
    EQUALSEQUALS = 307,            /* EQUALSEQUALS  */
    NOTEQUALS = 308,               /* NOTEQUALS  */
    INTEGERLITERAL = 309,          /* INTEGERLITERAL  */
    FLOATINGPOINTLITERAL = 310,    /* FLOATINGPOINTLITERAL  */
    BOOLEANLITERAL = 311,          /* BOOLEANLITERAL  */
    CHARACTERLITERAL = 312,        /* CHARACTERLITERAL  */
    STRINGLITERAL = 313,           /* STRINGLITERAL  */
    TEXTBLOCK = 314,               /* TEXTBLOCK  */
    NULLLITERAL = 315,             /* NULLLITERAL  */
    EXTENDS = 316,                 /* EXTENDS  */
    SUPER = 317,                   /* SUPER  */
    CLASS = 318,                   /* CLASS  */
    PUBLIC = 319,                  /* PUBLIC  */
    PRIVATE = 320,                 /* PRIVATE  */
    IMPLEMENTS = 321,              /* IMPLEMENTS  */
    PERMITS = 322,                 /* PERMITS  */
    PROTECTED = 323,               /* PROTECTED  */
    STATIC = 324,                  /* STATIC  */
    FINAL = 325,                   /* FINAL  */
    TRANSIENT = 326,               /* TRANSIENT  */
    VOLATILE = 327,                /* VOLATILE  */
    INSTANCEOF = 328,              /* INSTANCEOF  */
    THIS = 329,                    /* THIS  */
    VOID = 330,                    /* VOID  */
    NEW = 331,                     /* NEW  */
    THROW = 332,                   /* THROW  */
    ASSERT = 333,                  /* ASSERT  */
    VAR = 334,                     /* VAR  */
    BREAK = 335,                   /* BREAK  */
    CONTINUE = 336,                /* CONTINUE  */
    RETURN = 337,                  /* RETURN  */
    YIELD = 338,                   /* YIELD  */
    IF = 339,                      /* IF  */
    ELSE = 340,                    /* ELSE  */
    WHILE = 341,                   /* WHILE  */
    FOR = 342,                     /* FOR  */
    ABSTRACT = 343,                /* ABSTRACT  */
    SYNCHRONIZED = 344,            /* SYNCHRONIZED  */
    NATIVE = 345,                  /* NATIVE  */
    STRICTFP = 346,                /* STRICTFP  */
    SWITCH = 347,                  /* SWITCH  */
    DEFAULT = 348,                 /* DEFAULT  */
    PACKAGE = 349,                 /* PACKAGE  */
    DO = 350,                      /* DO  */
    GOTO = 351,                    /* GOTO  */
    IMPORT = 352,                  /* IMPORT  */
    THROWS = 353,                  /* THROWS  */
    CASE = 354,                    /* CASE  */
    ENUM = 355,                    /* ENUM  */
    CATCH = 356,                   /* CATCH  */
    TRY = 357,                     /* TRY  */
    INTERFACE = 358,               /* INTERFACE  */
    FINALLY = 359,                 /* FINALLY  */
    CONST = 360,                   /* CONST  */
    UNDERSCORE = 361,              /* UNDERSCORE  */
    EXPORTS = 362,                 /* EXPORTS  */
    OPENS = 363,                   /* OPENS  */
    REQUIRES = 364,                /* REQUIRES  */
    USES = 365,                    /* USES  */
    MODULE = 366,                  /* MODULE  */
    SEALED = 367,                  /* SEALED  */
    PROVIDES = 368,                /* PROVIDES  */
    TO = 369,                      /* TO  */
    WITH = 370,                    /* WITH  */
    OPEN = 371,                    /* OPEN  */
    RECORD = 372,                  /* RECORD  */
    TRANSITIVE = 373,              /* TRANSITIVE  */
    ERROR = 374,                   /* ERROR  */
    ONCE = 375,                    /* ONCE  */
    NL = 376,                      /* NL  */
    NON_SEALED = 377,              /* NON_SEALED  */
    IDENTIFIER = 378,              /* IDENTIFIER  */
    UNQUALIFIEDMETHODIDENTIFIER = 379, /* UNQUALIFIEDMETHODIDENTIFIER  */
    DOTCLASS = 380,                /* DOTCLASS  */
    EOFF = 381                     /* EOFF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 46 "parser.y"

    char* val;

#line 194 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
