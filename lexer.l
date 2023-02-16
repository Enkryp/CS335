%{
    #include <map>
    #include <string>
    #include <vector>
    #define ll long long
    #define pb push_back 
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


[ \t\f\r\n]     {/*whitespace*/ yylval.val = strdup(yytext); return(WS);}

"//"[^\r\n]*    {/* eol comment*/}


"/*"(("*"+{nsnl})|{ns})*"*"+"/"  {/*traditional comment*/}


abstract  {yylval.val = strdup(yytext); return(ABSTRACT);}
continue  {yylval.val = strdup(yytext); return(CONTINUE);}
for  {yylval.val = strdup(yytext); return(FOR);}
new  {yylval.val = strdup(yytext); return(NEW);}
switch  {yylval.val = strdup(yytext); return(SWITCH);}
assert  {yylval.val = strdup(yytext); return(ASSERT);}
default  {yylval.val = strdup(yytext); return(DEFAULT);}
if  {yylval.val = strdup(yytext); return(IF);}
package  {yylval.val = strdup(yytext); return(PACKAGE);}
synchronized  {yylval.val = strdup(yytext); return(SYNCHRONIZED);}
boolean  {yylval.val = strdup(yytext); return(BOOLEAN);}
do  {yylval.val = strdup(yytext); return(DO);}
goto  {yylval.val = strdup(yytext); return(GOTO);}
private  {yylval.val = strdup(yytext); return(PRIVATE);}
this  {yylval.val = strdup(yytext); return(THIS);}
break  {yylval.val = strdup(yytext); return(BREAK);}
double  {yylval.val = strdup(yytext); return(DOUBLE);}
implements  {yylval.val = strdup(yytext); return(IMPLEMENTS);}
protected  {yylval.val = strdup(yytext); return(PROTECTED);}
throw  {yylval.val = strdup(yytext); return(THROW);}
byte  {yylval.val = strdup(yytext); return(BYTE);}
else  {yylval.val = strdup(yytext); return(ELSE);}
import  {yylval.val = strdup(yytext); return(IMPORT);}
public  {yylval.val = strdup(yytext); return(PUBLIC);}
throws  {yylval.val = strdup(yytext); return(THROWS);}
case  {yylval.val = strdup(yytext); return(CASE);}
enum  {yylval.val = strdup(yytext); return(ENUM);}
instanceof  {yylval.val = strdup(yytext); return(INSTANCEOF);}
return  {yylval.val = strdup(yytext); return(RETURN);}
transient  {yylval.val = strdup(yytext); return(TRANSIENT);}
catch  {yylval.val = strdup(yytext); return(CATCH);}
extends  {yylval.val = strdup(yytext); return(EXTENDS);}
int  {yylval.val = strdup(yytext); return(INT);}
short  {yylval.val = strdup(yytext); return(SHORT);}
try  {yylval.val = strdup(yytext); return(TRY);}
char  {yylval.val = strdup(yytext); return(CHAR);}
final  {yylval.val = strdup(yytext); return(FINAL);}
interface  {yylval.val = strdup(yytext); return(INTERFACE);}
static  {yylval.val = strdup(yytext); return(STATIC);}
void  {yylval.val = strdup(yytext); return(VOID);}
class  {yylval.val = strdup(yytext); return(CLASS);}
finally  {yylval.val = strdup(yytext); return(FINALLY);}
long  {yylval.val = strdup(yytext); return(LONG);}
strictfp  {yylval.val = strdup(yytext); return(STRICTFP);}
volatile  {yylval.val = strdup(yytext); return(VOLATILE);}
const  {yylval.val = strdup(yytext); return(CONST);}
float  {yylval.val = strdup(yytext); return(FLOAT);}
native  {yylval.val = strdup(yytext); return(NATIVE);}
super  {yylval.val = strdup(yytext); return(SUPER);}
while  {yylval.val = strdup(yytext); return(WHILE);}
_  {yylval.val = strdup(yytext); return(_);}




exports  {yylval.val = strdup(yytext); return(EXPORTS);}
opens  {yylval.val = strdup(yytext); return(OPENS);}
requires  {yylval.val = strdup(yytext); return(REQUIRES);}
uses  {yylval.val = strdup(yytext); return(USES);}
module  {yylval.val = strdup(yytext); return(MODULE);}
permits  {yylval.val = strdup(yytext); return(PERMITS);}
sealed  {yylval.val = strdup(yytext); return(SEALED);}
var  {yylval.val = strdup(yytext); return(VAR);}
non-sealed  {yylval.val = strdup(yytext); return(NON-SEALED);}
provides  {yylval.val = strdup(yytext); return(PROVIDES);}
to  {yylval.val = strdup(yytext); return(TO);}
with  {yylval.val = strdup(yytext); return(WITH);}
open  {yylval.val = strdup(yytext); return(OPEN);}
record  {yylval.val = strdup(yytext); return(RECORD);}
transitive  {yylval.val = strdup(yytext); return(TRANSITIVE);}
yield  {yylval.val = strdup(yytext); return(YIELD);}


true|false|null {yylval.val = strdup(yytext); return(LITERAL);}


{let}{ledig}* {yylval.val = strdup(yytext); return(ID);}


("0"|({nzd}({digs}?|("_"+{digs}))))[lL]?   {yylval.val = strdup(yytext); return(LITERAL); /*Decimal*/}

("0x"{hexdigs}|"0X"{hexdigs})[lL]?         {yylval.val = strdup(yytext); return(LITERAL); /*Hex*/}

("0"[_]*{octdigs})[lL]?                    {yylval.val = strdup(yytext); return(LITERAL); /*Octal*/}

("0b"{bindigs}|"0B"{bindigs})[lL]?         {yylval.val = strdup(yytext); return(LITERAL); /*Binary*/}

{digs}"."{digs}?([eE][+-]?{digs})?[fFdD]?   {yylval.val = strdup(yytext); return(LITERAL); /*Float*/}
"."{digs}([eE][+-]?{digs})?[fFdD]?         {yylval.val = strdup(yytext); return(LITERAL); /*float*/}
{digs}([eE][+-]?{digs})[fFdD]?             {yylval.val = strdup(yytext); return(LITERAL); /*float*/}
{digs}([eE][+-]?{digs})?[fFdD]             {yylval.val = strdup(yytext); return(LITERAL); /*float*/}


(((("0x"{hexdigs}|"0X"{hexdigs}))"."?)|(("0x"|"0X"){hexdigs}?"."{hexdigs}))([pP][+-]?{digs})([fFdD]?) {yylval.val = strdup(yytext); return(LITERAL); /*hex float*/}



\"\"\"[ \t\f]*([\n\r]|"\r\n")([^\\\"]|\"[^\\\"]|\"\"[^\\\"])*\"\"\"   {yylval.val = strdup(yytext); return(LITERAL); /*text*/
// escape to be added
}

\'[^\r\n\'\\]\'                             {yylval.val = strdup(yytext); return(LITERAL); /*char*/
// escape to be added
}

\"[^\r\n\"\\]*\"                            {yylval.val = strdup(yytext); return(LITERAL); /*string*/
// escape to be added
}

\'[^\r\n\'\\][^\']                          {yylval.val = strdup(yytext); return(ERROR);}
\'[^\']*[\r\n]                              {yylval.val = strdup(yytext); return(ERROR);}
\"[^\""]*[\r\n]                              {yylval.val = strdup(yytext); return(ERROR);}

"("|")"|"{"|"}"|"["|"]"|";"|","|"."|"..."|"@"|"::" {yylval.val = strdup(yytext); return(SEPARATOR);}

"="|">"|"<"|"!"|"~"|"?"|":"|"->"|"=="|">="|"<="|"!="|"&&"|"||"|"++"|"--"|"+"|"-"|"*"|"/"|"&"|"|"|"^"|"%"|"<<"|">>"|">>>"|"+="|"-="|"*="|"/="|"&="|"|="|"^="|"%="|"<<="|">>="|">>>="     {

yylval.val = strdup(yytext); return(OPERATOR);}                            

<<EOF>>                                                         {  return once++ ? 0 : (NL) ; /*Return what you want*/}  

. {yylval.val = strdup(yytext); return(ERROR);}



%%


int yywrap(){

    return 1;

}

