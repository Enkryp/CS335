%{
    #include<iostream> 
    using namespace std;
    #include "parser.tab.h"
    extern "C" int yylex();
    using namespace std;
    

%}
%option yylineno


ns      [^\*]
nsnl    [^\*\/]
let     [a-zA-Z_$]
dig     [0-9]
ledig   [a-zA-Z0-9_$]
nzd     [1-9]
digUn   [0-9_]+
digs    ([0-9]|([0-9][0-9_]*[0-9]))
hexdig  [0-9a-fA-F]
hexdigs [0-9a-fA-F]|([0-9a-fA-F][0-9a-fA-F_]*[0-9a-fA-F])
octdig  [0-7]
octdigs [0-7]|([0-7][0-7_]*[0-7])
bindigs [01]|([01][01_]*[01])
escape ((\\(b|s|t|n|f|r|\"|'|\\|[0-7]|([0-7][0-7])|([0-3][0-7][0-7])))|(\\u00[0-9a-fA-F][0-9a-fA-F]))
%%

<<EOF>>  {  return EOFF;}  

[ \t\f\r\n]     {/*whitespace*/ yylval.val = strdup(yytext);cerr<<yytext;}

"//"[^\r\n]*    {/* eol comment*/}


"/*"(("*"+{nsnl})|{ns})*"*"+"/"  {/*traditional comment*/}

".class" {yylval.val = strdup(yytext);cerr<<yytext; return(DOTCLASS);}
abstract  {yylval.val = strdup(yytext);cerr<<yytext; return(ABSTRACT);}
continue  {yylval.val = strdup(yytext);cerr<<yytext; return(CONTINUE);}
for  {yylval.val = strdup(yytext);cerr<<yytext; return(FOR);}
new  {yylval.val = strdup(yytext);cerr<<yytext; return(NEW);}
switch  {yylval.val = strdup(yytext);cerr<<yytext; return(SWITCH);}
assert  {yylval.val = strdup(yytext);cerr<<yytext; return(ASSERT);}
default  {yylval.val = strdup(yytext);cerr<<yytext; return(DEFAULT);}
if  {yylval.val = strdup(yytext);cerr<<yytext; return(IF);}
package  {yylval.val = strdup(yytext);cerr<<yytext; return(PACKAGE);}
synchronized  {yylval.val = strdup(yytext);cerr<<yytext; return(SYNCHRONIZED);}
boolean  {yylval.val = strdup(yytext);cerr<<yytext; return(BOOLEAN);}
do  {yylval.val = strdup(yytext);cerr<<yytext; return(DO);}
goto  {yylval.val = strdup(yytext);cerr<<yytext; return(GOTO);}
private  {yylval.val = strdup(yytext);cerr<<yytext; return(PRIVATE);}
this  {yylval.val = strdup(yytext);cerr<<yytext; return(THIS);}
break  {yylval.val = strdup(yytext);cerr<<yytext; return(BREAK);}
double  {yylval.val = strdup(yytext);cerr<<yytext; return(DOUBLE);}
implements  {yylval.val = strdup(yytext);cerr<<yytext; return(IMPLEMENTS);}
protected  {yylval.val = strdup(yytext);cerr<<yytext; return(PROTECTED);}
throw  {yylval.val = strdup(yytext);cerr<<yytext; return(THROW);}
byte  {yylval.val = strdup(yytext);cerr<<yytext; return(BYTE);}
else  {yylval.val = strdup(yytext);cerr<<yytext; return(ELSE);}
import  {yylval.val = strdup(yytext);cerr<<yytext; return(IMPORT);}
public  {yylval.val = strdup(yytext);cerr<<yytext; return(PUBLIC);}
throws  {yylval.val = strdup(yytext);cerr<<yytext; return(THROWS);}
case  {yylval.val = strdup(yytext);cerr<<yytext; return(CASE);}
enum  {yylval.val = strdup(yytext);cerr<<yytext; return(ENUM);}
instanceof  {yylval.val = strdup(yytext);cerr<<yytext; return(INSTANCEOF);}
return  {yylval.val = strdup(yytext);cerr<<yytext; return(RETURN);}
transient  {yylval.val = strdup(yytext);cerr<<yytext; return(TRANSIENT);}
catch  {yylval.val = strdup(yytext);cerr<<yytext; return(CATCH);}
extends  {yylval.val = strdup(yytext);cerr<<yytext; return(EXTENDS);}
int  {yylval.val = strdup(yytext);cerr<<yytext; return(INT);}
short  {yylval.val = strdup(yytext);cerr<<yytext; return(SHORT);}
try  {yylval.val = strdup(yytext);cerr<<yytext; return(TRY);}
char  {yylval.val = strdup(yytext);cerr<<yytext; return(CHAR);}
final  {yylval.val = strdup(yytext);cerr<<yytext; return(FINAL);}
interface  {yylval.val = strdup(yytext);cerr<<yytext; return(INTERFACE);}
static  {yylval.val = strdup(yytext);cerr<<yytext; return(STATIC);}
void  {yylval.val = strdup(yytext);cerr<<yytext; return(VOID);}
class  {yylval.val = strdup(yytext);cerr<<yytext; return(CLASS);}
finally  {yylval.val = strdup(yytext);cerr<<yytext; return(FINALLY);}
long  {yylval.val = strdup(yytext);cerr<<yytext; return(LONG);}
strictfp  {yylval.val = strdup(yytext);cerr<<yytext; return(STRICTFP);}
volatile  {yylval.val = strdup(yytext);cerr<<yytext; return(VOLATILE);}
const  {yylval.val = strdup(yytext);cerr<<yytext; return(CONST);}
float  {yylval.val = strdup(yytext);cerr<<yytext; return(FLOAT);}
native  {yylval.val = strdup(yytext);cerr<<yytext; return(NATIVE);}
super  {yylval.val = strdup(yytext);cerr<<yytext; return(SUPER);}
while  {yylval.val = strdup(yytext);cerr<<yytext; return(WHILE);}
_  {yylval.val = strdup(yytext);cerr<<yytext; return(UNDERSCORE);}




exports  {yylval.val = strdup(yytext);cerr<<yytext; return(EXPORTS);}
opens  {yylval.val = strdup(yytext);cerr<<yytext; return(OPENS);}
requires  {yylval.val = strdup(yytext);cerr<<yytext; return(REQUIRES);}
uses  {yylval.val = strdup(yytext);cerr<<yytext; return(USES);}
module  {yylval.val = strdup(yytext);cerr<<yytext; return(MODULE);}
permits  {yylval.val = strdup(yytext);cerr<<yytext; return(PERMITS);}
sealed  {yylval.val = strdup(yytext);cerr<<yytext; return(SEALED);}
var  {yylval.val = strdup(yytext);cerr<<yytext; return(VAR);}
non-sealed  {yylval.val = strdup(yytext);cerr<<yytext; return(NON_SEALED);}
provides  {yylval.val = strdup(yytext);cerr<<yytext; return(PROVIDES);}
to  {yylval.val = strdup(yytext);cerr<<yytext; return(TO);}
with  {yylval.val = strdup(yytext);cerr<<yytext; return(WITH);}
open  {yylval.val = strdup(yytext);cerr<<yytext; return(OPEN);}
record  {yylval.val = strdup(yytext);cerr<<yytext; return(RECORD);}
transitive  {yylval.val = strdup(yytext);cerr<<yytext; return(TRANSITIVE);}
yield  {yylval.val = strdup(yytext);cerr<<yytext; return(YIELD);}

true|false {yylval.val = strdup(yytext);cerr<<yytext; return(BOOLEANLITERAL);}
null {yylval.val = strdup(yytext);cerr<<yytext; return(NULLLITERAL);}


{let}{ledig}* {yylval.val = strdup(yytext);cerr<<yytext; return(IDENTIFIER);}


("0"|({nzd}({digs}?|("_"+{digs}))))[lL]?   {yylval.val = strdup(yytext);cerr<<yytext; return(INTEGERLITERAL); /*Decimal*/}

("0x"{hexdigs}|"0X"{hexdigs})[lL]?         {yylval.val = strdup(yytext);cerr<<yytext; return(INTEGERLITERAL); /*Hex*/}

("0"[_]*{octdigs})[lL]?                    {yylval.val = strdup(yytext);cerr<<yytext; return(INTEGERLITERAL); /*Octal*/}

("0b"{bindigs}|"0B"{bindigs})[lL]?         {yylval.val = strdup(yytext);cerr<<yytext; return(INTEGERLITERAL); /*Binary*/}

{digs}"."{digs}?([eE][+-]?{digs})?[fFdD]?   {yylval.val = strdup(yytext);cerr<<yytext; return(FLOATINGPOINTLITERAL); /*Float*/}
"."{digs}([eE][+-]?{digs})?[fFdD]?         {yylval.val = strdup(yytext);cerr<<yytext; return(FLOATINGPOINTLITERAL); /*float*/}
{digs}([eE][+-]?{digs})[fFdD]?             {yylval.val = strdup(yytext);cerr<<yytext; return(FLOATINGPOINTLITERAL); /*float*/}
{digs}([eE][+-]?{digs})?[fFdD]             {yylval.val = strdup(yytext);cerr<<yytext; return(FLOATINGPOINTLITERAL); /*float*/}


(((("0x"{hexdigs}|"0X"{hexdigs}))"."?)|(("0x"|"0X"){hexdigs}?"."{hexdigs}))([pP][+-]?{digs})([fFdD]?) {yylval.val = strdup(yytext);cerr<<yytext; return(FLOATINGPOINTLITERAL); /*hex float*/}


(\"\"\"[ \t\f]*([\n\r]|"\r\n")(([^\"\\]|(\"\"[^\"\\])|(\"[^\"\\])|{escape})*[^\\])?\"\"\")  {yylval.val = strdup(yytext);cerr<<yytext; return(TEXTBLOCK); /*text*/
// escape to be added
}

\'([^\r\n\'\\]|{escape})\'                             {yylval.val = strdup(yytext);cerr<<yytext; return(CHARACTERLITERAL); /*char*/
// escape to be added
}

\"([^\r\n\"\\]|{escape})*\"                            {yylval.val = strdup(yytext);cerr<<yytext; return(STRINGLITERAL); /*string*/
// escape to be added
}

\'[^\r\n\'\\][^\']                          {yylval.val = strdup(yytext);cerr<<yytext; return(ERROR);}
\'[^\']*[\r\n]                              {yylval.val = strdup(yytext);cerr<<yytext; return(ERROR);}
\"[^\""]*[\r\n]                              {yylval.val = strdup(yytext);cerr<<yytext; return(ERROR);}

","  {yylval.val = strdup(yytext);cerr<<yytext; return(COMMA);}
"?"  {yylval.val = strdup(yytext);cerr<<yytext; return(QUESTIONMARK);}
";"  {yylval.val = strdup(yytext);cerr<<yytext; return(SEMICOLON);}
"{"  {yylval.val = strdup(yytext);cerr<<yytext; return(OPENCURLY);}
"}"  {yylval.val = strdup(yytext);cerr<<yytext; return(CLOSECURLY);}
"<"  {yylval.val = strdup(yytext);cerr<<yytext; return(ANGULARLEFT);}
">"  {yylval.val = strdup(yytext);cerr<<yytext; return(ANGULARRIGHT);}
"["  {yylval.val = strdup(yytext);cerr<<yytext; return(OPENSQUARE);}
"]"  {yylval.val = strdup(yytext);cerr<<yytext; return(CLOSESQUARE);}
"("  {yylval.val = strdup(yytext);cerr<<yytext; return(OPENPARAN);}
")"  {yylval.val = strdup(yytext);cerr<<yytext; return(CLOSEPARAN);}
"::"  {yylval.val = strdup(yytext);cerr<<yytext; return(DOUBLECOLON);}
"="  {yylval.val = strdup(yytext);cerr<<yytext; return(EQUALS);}
"*="  {yylval.val = strdup(yytext);cerr<<yytext; return(MULTIPLYEQUALS);}
"/="  {yylval.val = strdup(yytext);cerr<<yytext; return(DIVIDEEQUALS);}
"%="  {yylval.val = strdup(yytext);cerr<<yytext; return(MODEQUALS);}
"+="  {yylval.val = strdup(yytext);cerr<<yytext; return(PLUSEQUALS);}
"-="  {yylval.val = strdup(yytext);cerr<<yytext; return(MINUSEQUALS);}
"+"  {yylval.val = strdup(yytext);cerr<<yytext; return(PLUS);}
"-"  {yylval.val = strdup(yytext);cerr<<yytext; return(MINUS);}
"/"  {yylval.val = strdup(yytext);cerr<<yytext; return(DIVIDE);}
"*"  {yylval.val = strdup(yytext);cerr<<yytext; return(MULTIPLY);}
"%"  {yylval.val = strdup(yytext);cerr<<yytext; return(MOD);}
"|"  {yylval.val = strdup(yytext);cerr<<yytext; return(OR);}
"^"  {yylval.val = strdup(yytext);cerr<<yytext; return(XOR);}
":"  {yylval.val = strdup(yytext);cerr<<yytext; return(COLON);}
"!"  {yylval.val = strdup(yytext);cerr<<yytext; return(NOT);}
"~"  {yylval.val = strdup(yytext);cerr<<yytext; return(COMPLEMENT);}
"&"  {yylval.val = strdup(yytext);cerr<<yytext; return(AND);}
"."  {yylval.val = strdup(yytext);cerr<<yytext; return(DOT);}
"||"  {yylval.val = strdup(yytext);cerr<<yytext; return(OROR);}
"&&"  {yylval.val = strdup(yytext);cerr<<yytext; return(ANDAND);}
"++"  {yylval.val = strdup(yytext);cerr<<yytext; return(PLUSPLUS);}
"--"  {yylval.val = strdup(yytext);cerr<<yytext; return(MINUSMINUS);}
"<<"  {yylval.val = strdup(yytext);cerr<<yytext; return(ANGULARLEFTANGULARLEFT);}
">>"  {yylval.val = strdup(yytext);cerr<<yytext; return(ANGULARRIGHTANGULARRIGHT);}
">>>"  {yylval.val = strdup(yytext);cerr<<yytext; return(ANGULARRIGHTANGULARRIGHTANGULARRIGHT);}
"=="  {yylval.val = strdup(yytext);cerr<<yytext; return(EQUALSEQUALS);}
"!="  {yylval.val = strdup(yytext);cerr<<yytext; return(NOTEQUALS);}


. {yylval.val = strdup(yytext);cerr<<yytext; return(ERROR);}



%%


int yywrap(){

    return 1;

}

