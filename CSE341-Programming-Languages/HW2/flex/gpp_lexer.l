%{
#include <stdio.h>

%}

/* keywords*/
KW_AND "and"
KW_OR "or"
KW_NOT "not"
KW_EQUAL "equal"
KW_LESS "less"
KW_NIL "nil"
KW_LIST "list"
KW_APPEND "append"
KW_CONCAT "concat"
KW_SET "set"
KW_DEFFUN "deffun"
KW_FOR "for"
KW_IF "if"
KW_EXIT "exit"
KW_LOAD "load"
KW_DISP "disp"
KW_TRUE "true"
KW_FALSE "false"

/*operators*/

OP_PLUS "+"
OP_MINUS "-"
OP_DIV "/"
OP_MULT "*"
OP_OP "("
OP_CP ")"
OP_DBLMULT "**"
OP_COMMA ","



COMMENT ";".*
VALUEI  [0-9]|[1-9][[:digit:]]*
VALUEF [1-9]+"f"+[1:9]*
ID [a-zA-Z_][a-zA-Z0-9_]*
VALUESTR ["].*["]  



%%
<<EOF>> {yyterminate();}
{KW_AND}     {printf("%s : %s",yytext , "KW_AND\n");}
{KW_OR}      {printf("%s : %s",yytext ,"KW_OR\n");}
{KW_NOT}     {printf("%s : %s",yytext ,"KW_NOT\n");} 
{KW_EQUAL}   {printf("%s : %s",yytext ,"KW_EQUAL\n");} 
{KW_LESS}    {printf("%s : %s",yytext ,"KW_LESS\n");} 
{KW_NIL}     {printf("%s : %s",yytext ,"KW_NIL\n");} 
{KW_LIST}    {printf("%s : %s",yytext ,"KW_LIST\n");} 
{KW_APPEND}  {printf("%s : %s",yytext ,"KW_APPEND\n");} 
{KW_CONCAT}  {printf("%s : %s",yytext ,"KW_CONCAT\n");} 
{KW_SET}     {printf("%s : %s",yytext ,"KW_SET\n");} 
{KW_DEFFUN}  {printf("%s : %s",yytext ,"KW_DEFFUN\n");} 
{KW_FOR}     {printf("%s : %s",yytext ,"KW_FOR\n");} 
{KW_IF}      {printf("%s : %s",yytext ,"KW_IF\n");} 
{KW_EXIT}    {printf("%s : %s",yytext ,"KW_EXIT\n");} 
{KW_LOAD}    {printf("%s : %s",yytext ,"KW_LOAD\n");} 
{KW_DISP}    {printf("%s : %s",yytext ,"KW_DISP\n");} 
{KW_TRUE}    {printf("%s : %s",yytext ,"KW_TRUE\n");} 
{KW_FALSE}   {printf("%s : %s",yytext ,"KW_FALSE\n");} 

{OP_PLUS}           {printf("%s : %s",yytext ,"OP_PLUS\n");}
{OP_MINUS}           {printf("%s : %s",yytext ,"OP_MINUS\n");}
{OP_DIV}           {printf("%s : %s",yytext ,"OP_DIV\n");}
{OP_MULT}           {printf("%s : %s",yytext ,"OP_MULT\n");}
{OP_OP}           {printf("%s : %s",yytext ,"OP_OP\n");}
{OP_CP}           {printf("%s : %s",yytext ,"OP_CP\n");}
{OP_DBLMULT}           {printf("%s : %s",yytext ,"OP_DBLMULT\n");}
{OP_COMMA}       {printf("%s : %s",yytext ,"OP_COMMA\n");}
[[:space:]]|[[:space:]]+ 


{COMMENT}  {printf("%s : %s",yytext ,"COMMENT\n");}
{VALUEI}    {printf("%s : %s",yytext ,"VALUEI\n");}
{VALUEF}    {printf("%s : %s",yytext ,"VALUEF\n");}
{ID}        {printf("%s : %s",yytext ,"ID\n");}
{VALUESTR}    {printf("%s : %s",yytext ,"VALUESTR\n");}




"0"{VALUEI}+{ID}? {printf("%s : %s",yytext ,"Syntax Error\n");}
. {printf("%s : %s",yytext ,"Syntax Error\n");}



%%

int yywrap(){

}



