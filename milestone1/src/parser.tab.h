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
    OPENCURLY = 269,               /* OPENCURLY  */
    CLOSECURLY = 270,              /* CLOSECURLY  */
    ANGULARLEFT = 271,             /* ANGULARLEFT  */
    ANGULARRIGHT = 272,            /* ANGULARRIGHT  */
    OPENSQUARE = 273,              /* OPENSQUARE  */
    CLOSESQUARE = 274,             /* CLOSESQUARE  */
    OPENPARAN = 275,               /* OPENPARAN  */
    CLOSEPARAN = 276,              /* CLOSEPARAN  */
    DOUBLECOLON = 277,             /* DOUBLECOLON  */
    TRIPLEDOT = 278,               /* TRIPLEDOT  */
    WS = 279,                      /* WS  */
    EQUALS = 280,                  /* EQUALS  */
    MULTIPLYEQUALS = 281,          /* MULTIPLYEQUALS  */
    DIVIDEEQUALS = 282,            /* DIVIDEEQUALS  */
    MODEQUALS = 283,               /* MODEQUALS  */
    PLUSEQUALS = 284,              /* PLUSEQUALS  */
    MINUSEQUALS = 285,             /* MINUSEQUALS  */
    PLUS = 286,                    /* PLUS  */
    MINUS = 287,                   /* MINUS  */
    DIVIDE = 288,                  /* DIVIDE  */
    MULTIPLY = 289,                /* MULTIPLY  */
    MOD = 290,                     /* MOD  */
    OR = 291,                      /* OR  */
    XOR = 292,                     /* XOR  */
    COLON = 293,                   /* COLON  */
    NOT = 294,                     /* NOT  */
    COMPLEMENT = 295,              /* COMPLEMENT  */
    AND = 296,                     /* AND  */
    DOT = 297,                     /* DOT  */
    OROR = 298,                    /* OROR  */
    ANDAND = 299,                  /* ANDAND  */
    PLUSPLUS = 300,                /* PLUSPLUS  */
    MINUSMINUS = 301,              /* MINUSMINUS  */
    ANGULARLEFTANGULARLEFT = 302,  /* ANGULARLEFTANGULARLEFT  */
    ANGULARRIGHTANGULARRIGHT = 303, /* ANGULARRIGHTANGULARRIGHT  */
    ANGULARRIGHTANGULARRIGHTANGULARRIGHT = 304, /* ANGULARRIGHTANGULARRIGHTANGULARRIGHT  */
    EQUALSEQUALS = 305,            /* EQUALSEQUALS  */
    NOTEQUALS = 306,               /* NOTEQUALS  */
    INTEGERLITERAL = 307,          /* INTEGERLITERAL  */
    FLOATINGPOINTLITERAL = 308,    /* FLOATINGPOINTLITERAL  */
    BOOLEANLITERAL = 309,          /* BOOLEANLITERAL  */
    CHARACTERLITERAL = 310,        /* CHARACTERLITERAL  */
    STRINGLITERAL = 311,           /* STRINGLITERAL  */
    TEXTBLOCK = 312,               /* TEXTBLOCK  */
    NULLLITERAL = 313,             /* NULLLITERAL  */
    EXTENDS = 314,                 /* EXTENDS  */
    SUPER = 315,                   /* SUPER  */
    CLASS = 316,                   /* CLASS  */
    PUBLIC = 317,                  /* PUBLIC  */
    PRIVATE = 318,                 /* PRIVATE  */
    IMPLEMENTS = 319,              /* IMPLEMENTS  */
    PERMITS = 320,                 /* PERMITS  */
    PROTECTED = 321,               /* PROTECTED  */
    STATIC = 322,                  /* STATIC  */
    FINAL = 323,                   /* FINAL  */
    TRANSIENT = 324,               /* TRANSIENT  */
    VOLATILE = 325,                /* VOLATILE  */
    INSTANCEOF = 326,              /* INSTANCEOF  */
    THIS = 327,                    /* THIS  */
    VOID = 328,                    /* VOID  */
    NEW = 329,                     /* NEW  */
    THROW = 330,                   /* THROW  */
    ASSERT = 331,                  /* ASSERT  */
    VAR = 332,                     /* VAR  */
    BREAK = 333,                   /* BREAK  */
    CONTINUE = 334,                /* CONTINUE  */
    RETURN = 335,                  /* RETURN  */
    YIELD = 336,                   /* YIELD  */
    IF = 337,                      /* IF  */
    ELSE = 338,                    /* ELSE  */
    WHILE = 339,                   /* WHILE  */
    FOR = 340,                     /* FOR  */
    ABSTRACT = 341,                /* ABSTRACT  */
    SYNCHRONIZED = 342,            /* SYNCHRONIZED  */
    NATIVE = 343,                  /* NATIVE  */
    STRICTFP = 344,                /* STRICTFP  */
    SWITCH = 345,                  /* SWITCH  */
    DEFAULT = 346,                 /* DEFAULT  */
    PACKAGE = 347,                 /* PACKAGE  */
    DO = 348,                      /* DO  */
    GOTO = 349,                    /* GOTO  */
    IMPORT = 350,                  /* IMPORT  */
    THROWS = 351,                  /* THROWS  */
    CASE = 352,                    /* CASE  */
    ENUM = 353,                    /* ENUM  */
    CATCH = 354,                   /* CATCH  */
    TRY = 355,                     /* TRY  */
    INTERFACE = 356,               /* INTERFACE  */
    FINALLY = 357,                 /* FINALLY  */
    CONST = 358,                   /* CONST  */
    UNDERSCORE = 359,              /* UNDERSCORE  */
    EXPORTS = 360,                 /* EXPORTS  */
    OPENS = 361,                   /* OPENS  */
    REQUIRES = 362,                /* REQUIRES  */
    USES = 363,                    /* USES  */
    MODULE = 364,                  /* MODULE  */
    SEALED = 365,                  /* SEALED  */
    PROVIDES = 366,                /* PROVIDES  */
    TO = 367,                      /* TO  */
    WITH = 368,                    /* WITH  */
    OPEN = 369,                    /* OPEN  */
    RECORD = 370,                  /* RECORD  */
    TRANSITIVE = 371,              /* TRANSITIVE  */
    ERROR = 372,                   /* ERROR  */
    ONCE = 373,                    /* ONCE  */
    NL = 374,                      /* NL  */
    NON_SEALED = 375,              /* NON_SEALED  */
    IDENTIFIER = 376,              /* IDENTIFIER  */
    UNQUALIFIEDMETHODIDENTIFIER = 377, /* UNQUALIFIEDMETHODIDENTIFIER  */
    DOTCLASS = 378,                /* DOTCLASS  */
    EOFF = 379                     /* EOFF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "parser.y"

    char* val;

#line 192 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
