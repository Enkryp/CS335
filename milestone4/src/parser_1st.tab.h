/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 189 "parser_1st.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_1ST_TAB_H_INCLUDED  */
