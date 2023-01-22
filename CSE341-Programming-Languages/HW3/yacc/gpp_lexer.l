%{
#include "y.tab.h"
#include "string.h"
extern YYSTYPE yylval;
double getNumerator();
double getDenumerator();
double findValueF();
%}


/* keywords*/
KW_AND "and"
KW_OR "or"
KW_NOT "not"
KW_EQUAL "equal"
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
KW_WHILE "while"
KW_DEFV "defvar"
/*operators*/

OP_PLUS "+"
OP_MINUS "-"
OP_DIV "/"
OP_MULT "*"
OP_OP "("
OP_CP ")"
OP_DBLMULT "**"
OP_COMMA ","
OP_EQ "eq"
OP_GT "gt"

COMMENT ";".*
VALUEI  [0-9]|[1-9][[:digit:]]*
VALUEF [1-9]*["f"][1-9]*
ID [a-zA-Z_][a-zA-Z0-9_]*  
VALUESTR ["].*["]  


%%

<<EOF>> {yyterminate();}
(\r\n|\r|\n) {return 0;}
{KW_AND}      {return KW_AND;}
{KW_OR}      {return KW_OR;}
{KW_NOT}     {return KW_NOT;} 
{KW_EQUAL}   {return KW_EQUAL;}  
{KW_NIL}     {return KW_NIL;}  
{KW_LIST}    {} 
{KW_APPEND}  {} 
{KW_CONCAT}  {} 
{KW_SET}     {return KW_SET;} 
{KW_DEFFUN}  {return KW_DEFFUN;} 
{KW_FOR}     {return KW_FOR;} 
{KW_IF}      {return KW_IF;} 
{KW_EXIT}    {return KW_EXIT;} 
{KW_LOAD}    {return KW_LOAD;} 
{KW_DISP}    {return KW_DISP;} 
{KW_TRUE}    {return KW_TRUE;} 
{KW_FALSE}   {return KW_FALSE;} 
{KW_WHILE}   {return KW_WHILE;}
{KW_DEFV}    {return KW_DEFV;}

{OP_PLUS}          {return OP_PLUS;}
{OP_MINUS}         {return OP_MINUS;}
{OP_DIV}           {return OP_DIV;}
{OP_MULT}          {return OP_MULT;}
{OP_OP}            {return OP_OP;}
{OP_CP}            {return OP_CP;}
{OP_COMMA}         {return OP_COMMA;}
{OP_EQ}            {return OP_EQ;}
{OP_GT}            {return OP_GT;}

{COMMENT}  {return COMMENT;} 
{VALUEI}    {return VALUEI;}
{VALUEF}    {yylval.valueF= findValueF();return VALUEF;}
{ID}        {strcpy(yylval.idName, yytext);return ID;}
{VALUESTR}    {return VALUESTR;}
[[:space:]]+ 		/* ignore space */

"0"{VALUEI}+{ID}? {printf("Syntax Error\n"); return 0;}
. {printf("Syntax Error\n"); return 0;}



%%

double getNumerator(){
    char *token = strtok(yytext, "f");
    char *end;
    double ret =strtod(token,&end);

    //fprintf(stderr,"%f",ret);
    return ret; 
}
double getDenumerator(){
    char *token = strtok(NULL,"f");
    char *end;
    double ret =strtod(token,&end);
    //fprintf(stderr,"%f",ret);
    return ret;
}

double findValueF(){
    
    double ret = (getNumerator() / getDenumerator());
    return ret;
}

int yywrap(){

}






