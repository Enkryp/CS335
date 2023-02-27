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

%%


[ \t\f\r\n]     {/*whitespace*/ yylval.val = strdup(yytext);cout<<yytext;}

"//"[^\r\n]*    {/* eol comment*/}


"/*"(("*"+{nsnl})|{ns})*"*"+"/"  {/*traditional comment*/}


abstract  {yylval.val = strdup(yytext);cout<<yytext; return(ABSTRACT);}
continue  {yylval.val = strdup(yytext);cout<<yytext; return(CONTINUE);}
for  {yylval.val = strdup(yytext);cout<<yytext; return(FOR);}
new  {yylval.val = strdup(yytext);cout<<yytext; return(NEW);}
switch  {yylval.val = strdup(yytext);cout<<yytext; return(SWITCH);}
assert  {yylval.val = strdup(yytext);cout<<yytext; return(ASSERT);}
default  {yylval.val = strdup(yytext);cout<<yytext; return(DEFAULT);}
if  {yylval.val = strdup(yytext);cout<<yytext; return(IF);}
package  {yylval.val = strdup(yytext);cout<<yytext; return(PACKAGE);}
synchronized  {yylval.val = strdup(yytext);cout<<yytext; return(SYNCHRONIZED);}
boolean  {yylval.val = strdup(yytext);cout<<yytext; return(BOOLEAN);}
do  {yylval.val = strdup(yytext);cout<<yytext; return(DO);}
goto  {yylval.val = strdup(yytext);cout<<yytext; return(GOTO);}
private  {yylval.val = strdup(yytext);cout<<yytext; return(PRIVATE);}
this  {yylval.val = strdup(yytext);cout<<yytext; return(THIS);}
break  {yylval.val = strdup(yytext);cout<<yytext; return(BREAK);}
double  {yylval.val = strdup(yytext);cout<<yytext; return(DOUBLE);}
implements  {yylval.val = strdup(yytext);cout<<yytext; return(IMPLEMENTS);}
protected  {yylval.val = strdup(yytext);cout<<yytext; return(PROTECTED);}
throw  {yylval.val = strdup(yytext);cout<<yytext; return(THROW);}
byte  {yylval.val = strdup(yytext);cout<<yytext; return(BYTE);}
else  {yylval.val = strdup(yytext);cout<<yytext; return(ELSE);}
import  {yylval.val = strdup(yytext);cout<<yytext; return(IMPORT);}
public  {yylval.val = strdup(yytext);cout<<yytext; return(PUBLIC);}
throws  {yylval.val = strdup(yytext);cout<<yytext; return(THROWS);}
case  {yylval.val = strdup(yytext);cout<<yytext; return(CASE);}
enum  {yylval.val = strdup(yytext);cout<<yytext; return(ENUM);}
instanceof  {yylval.val = strdup(yytext);cout<<yytext; return(INSTANCEOF);}
return  {yylval.val = strdup(yytext);cout<<yytext; return(RETURN);}
transient  {yylval.val = strdup(yytext);cout<<yytext; return(TRANSIENT);}
catch  {yylval.val = strdup(yytext);cout<<yytext; return(CATCH);}
extends  {yylval.val = strdup(yytext);cout<<yytext; return(EXTENDS);}
int  {yylval.val = strdup(yytext);cout<<yytext; return(INT);}
short  {yylval.val = strdup(yytext);cout<<yytext; return(SHORT);}
try  {yylval.val = strdup(yytext);cout<<yytext; return(TRY);}
char  {yylval.val = strdup(yytext);cout<<yytext; return(CHAR);}
final  {yylval.val = strdup(yytext);cout<<yytext; return(FINAL);}
interface  {yylval.val = strdup(yytext);cout<<yytext; return(INTERFACE);}
static  {yylval.val = strdup(yytext);cout<<yytext; return(STATIC);}
void  {yylval.val = strdup(yytext);cout<<yytext; return(VOID);}
class  {yylval.val = strdup(yytext);cout<<yytext; return(CLASS);}
finally  {yylval.val = strdup(yytext);cout<<yytext; return(FINALLY);}
long  {yylval.val = strdup(yytext);cout<<yytext; return(LONG);}
strictfp  {yylval.val = strdup(yytext);cout<<yytext; return(STRICTFP);}
volatile  {yylval.val = strdup(yytext);cout<<yytext; return(VOLATILE);}
const  {yylval.val = strdup(yytext);cout<<yytext; return(CONST);}
float  {yylval.val = strdup(yytext);cout<<yytext; return(FLOAT);}
native  {yylval.val = strdup(yytext);cout<<yytext; return(NATIVE);}
super  {yylval.val = strdup(yytext);cout<<yytext; return(SUPER);}
while  {yylval.val = strdup(yytext);cout<<yytext; return(WHILE);}
_  {yylval.val = strdup(yytext);cout<<yytext; return(UNDERSCORE);}




exports  {yylval.val = strdup(yytext);cout<<yytext; return(EXPORTS);}
opens  {yylval.val = strdup(yytext);cout<<yytext; return(OPENS);}
requires  {yylval.val = strdup(yytext);cout<<yytext; return(REQUIRES);}
uses  {yylval.val = strdup(yytext);cout<<yytext; return(USES);}
module  {yylval.val = strdup(yytext);cout<<yytext; return(MODULE);}
permits  {yylval.val = strdup(yytext);cout<<yytext; return(PERMITS);}
sealed  {yylval.val = strdup(yytext);cout<<yytext; return(SEALED);}
var  {yylval.val = strdup(yytext);cout<<yytext; return(VAR);}
non-sealed  {yylval.val = strdup(yytext);cout<<yytext; return(NON_SEALED);}
provides  {yylval.val = strdup(yytext);cout<<yytext; return(PROVIDES);}
to  {yylval.val = strdup(yytext);cout<<yytext; return(TO);}
with  {yylval.val = strdup(yytext);cout<<yytext; return(WITH);}
open  {yylval.val = strdup(yytext);cout<<yytext; return(OPEN);}
record  {yylval.val = strdup(yytext);cout<<yytext; return(RECORD);}
transitive  {yylval.val = strdup(yytext);cout<<yytext; return(TRANSITIVE);}
yield  {yylval.val = strdup(yytext);cout<<yytext; return(YIELD);}

true|false {yylval.val = strdup(yytext);cout<<yytext; return(BOOLEANLITERAL);}
null {yylval.val = strdup(yytext);cout<<yytext; return(NULLLITERAL);}


{let}{ledig}* {yylval.val = strdup(yytext);cout<<yytext; return(IDENTIFIER);}


("0"|({nzd}({digs}?|("_"+{digs}))))[lL]?   {yylval.val = strdup(yytext);cout<<yytext; return(INTEGERLITERAL); /*Decimal*/}

("0x"{hexdigs}|"0X"{hexdigs})[lL]?         {yylval.val = strdup(yytext);cout<<yytext; return(INTEGERLITERAL); /*Hex*/}

("0"[_]*{octdigs})[lL]?                    {yylval.val = strdup(yytext);cout<<yytext; return(INTEGERLITERAL); /*Octal*/}

("0b"{bindigs}|"0B"{bindigs})[lL]?         {yylval.val = strdup(yytext);cout<<yytext; return(INTEGERLITERAL); /*Binary*/}

{digs}"."{digs}?([eE][+-]?{digs})?[fFdD]?   {yylval.val = strdup(yytext);cout<<yytext; return(FLOATINGPOINTLITERAL); /*Float*/}
"."{digs}([eE][+-]?{digs})?[fFdD]?         {yylval.val = strdup(yytext);cout<<yytext; return(FLOATINGPOINTLITERAL); /*float*/}
{digs}([eE][+-]?{digs})[fFdD]?             {yylval.val = strdup(yytext);cout<<yytext; return(FLOATINGPOINTLITERAL); /*float*/}
{digs}([eE][+-]?{digs})?[fFdD]             {yylval.val = strdup(yytext);cout<<yytext; return(FLOATINGPOINTLITERAL); /*float*/}


(((("0x"{hexdigs}|"0X"{hexdigs}))"."?)|(("0x"|"0X"){hexdigs}?"."{hexdigs}))([pP][+-]?{digs})([fFdD]?) {yylval.val = strdup(yytext);cout<<yytext; return(FLOATINGPOINTLITERAL); /*hex float*/}



\"\"\"[ \t\f]*([\n\r]|"\r\n")([^\\\"]|\"[^\\\"]|\"\"[^\\\"])*\"\"\"   {yylval.val = strdup(yytext);cout<<yytext; return(TEXTBLOCK); /*text*/
// escape to be added
}

\'[^\r\n\'\\]\'                             {yylval.val = strdup(yytext);cout<<yytext; return(CHARACTERLITERAL); /*char*/
// escape to be added
}

\"[^\r\n\"\\]*\"                            {yylval.val = strdup(yytext);cout<<yytext; return(STRINGLITERAL); /*string*/
// escape to be added
}

\'[^\r\n\'\\][^\']                          {yylval.val = strdup(yytext);cout<<yytext; return(ERROR);}
\'[^\']*[\r\n]                              {yylval.val = strdup(yytext);cout<<yytext; return(ERROR);}
\"[^\""]*[\r\n]                              {yylval.val = strdup(yytext);cout<<yytext; return(ERROR);}

","  {yylval.val = strdup(yytext);cout<<yytext; return(COMMA);}
"?"  {yylval.val = strdup(yytext);cout<<yytext; return(QUESTIONMARK);}
";"  {yylval.val = strdup(yytext);cout<<yytext; return(SEMICOLON);}
"{"  {yylval.val = strdup(yytext);cout<<yytext; return(OPENCURLY);}
"}"  {yylval.val = strdup(yytext);cout<<yytext; return(CLOSECURLY);}
"<"  {yylval.val = strdup(yytext);cout<<yytext; return(ANGULARLEFT);}
">"  {yylval.val = strdup(yytext);cout<<yytext; return(ANGULARRIGHT);}
"["  {yylval.val = strdup(yytext);cout<<yytext; return(OPENSQUARE);}
"]"  {yylval.val = strdup(yytext);cout<<yytext; return(CLOSESQUARE);}
"("  {yylval.val = strdup(yytext);cout<<yytext; return(OPENPARAN);}
")"  {yylval.val = strdup(yytext);cout<<yytext; return(CLOSEPARAN);}
"::"  {yylval.val = strdup(yytext);cout<<yytext; return(DOUBLECOLON);}
"="  {yylval.val = strdup(yytext);cout<<yytext; return(EQUALS);}
"*="  {yylval.val = strdup(yytext);cout<<yytext; return(MULTIPLYEQUALS);}
"/="  {yylval.val = strdup(yytext);cout<<yytext; return(DIVIDEEQUALS);}
"%="  {yylval.val = strdup(yytext);cout<<yytext; return(MODEQUALS);}
"+="  {yylval.val = strdup(yytext);cout<<yytext; return(PLUSEQUALS);}
"-="  {yylval.val = strdup(yytext);cout<<yytext; return(MINUSEQUALS);}
"+"  {yylval.val = strdup(yytext);cout<<yytext; return(PLUS);}
"-"  {yylval.val = strdup(yytext);cout<<yytext; return(MINUS);}
"/"  {yylval.val = strdup(yytext);cout<<yytext; return(DIVIDE);}
"*"  {yylval.val = strdup(yytext);cout<<yytext; return(MULTIPLY);}
"%"  {yylval.val = strdup(yytext);cout<<yytext; return(MOD);}
"|"  {yylval.val = strdup(yytext);cout<<yytext; return(OR);}
"^"  {yylval.val = strdup(yytext);cout<<yytext; return(XOR);}
":"  {yylval.val = strdup(yytext);cout<<yytext; return(COLON);}
"!"  {yylval.val = strdup(yytext);cout<<yytext; return(NOT);}
"~"  {yylval.val = strdup(yytext);cout<<yytext; return(COMPLEMENT);}
"&"  {yylval.val = strdup(yytext);cout<<yytext; return(AND);}
"."  {yylval.val = strdup(yytext);cout<<yytext; return(DOT);}
"||"  {yylval.val = strdup(yytext);cout<<yytext; return(OROR);}
"&&"  {yylval.val = strdup(yytext);cout<<yytext; return(ANDAND);}
"++"  {yylval.val = strdup(yytext);cout<<yytext; return(PLUSPLUS);}
"--"  {yylval.val = strdup(yytext);cout<<yytext; return(MINUSMINUS);}
"<<"  {yylval.val = strdup(yytext);cout<<yytext; return(ANGULARLEFTANGULARLEFT);}
">>"  {yylval.val = strdup(yytext);cout<<yytext; return(ANGULARRIGHTANGULARRIGHT);}
">>>"  {yylval.val = strdup(yytext);cout<<yytext; return(ANGULARRIGHTANGULARRIGHTANGULARRIGHT);}
"=="  {yylval.val = strdup(yytext);cout<<yytext; return(EQUALSEQUALS);}
"!="  {yylval.val = strdup(yytext);cout<<yytext; return(NOTEQUALS);}

<<EOF>>                                                         {  return EOFF;}  

. {yylval.val = strdup(yytext);cout<<yytext; return(ERROR);}



%%


int yywrap(){

    return 1;

}

