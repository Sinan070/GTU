%{
#include <stdio.h>
#include <stdlib.h>
#include "gpp_parser.h"
extern FILE *yyin;
%}


%union {
     double valueF;
     char idName[30];
     int valueBinary;
};

%start INPUT
%token KW_AND KW_OR KW_NOT KW_EQUAL 
%token KW_NIL KW_SET KW_DEFFUN KW_FOR KW_WHILE KW_DEFV 
%token KW_IF KW_EXIT KW_LOAD KW_DISP 

%token KW_LIST KW_APPEND KW_CONCAT 
%token OP_PLUS OP_MINUS OP_DIV OP_MULT
%token OP_OP OP_CP OP_DBLMULT OP_COMMA OP_EQ OP_GT
%token VALUESTR VALUEI

%token COMMENT SPACE

%token <valueF> VALUEF 
%token <idName> ID
%token KW_TRUE<valueBinary> KW_FALSE<valueBinary> 

%type <valueF> INPUT 
//%type <idName>FUNCTION 
%type <valueF> EXP
%type <valueF> EXPLIST
%type <valueF> ASG
//%type <valueF> FCALL
%type <valueBinary> EXPB
%left OP_PLUS OP_MINUS OP_MULT OP_DIV






%%

INPUT   : //FUNCTION {printf("SYNTAX OK. \nResult: %f\n" $1);}      
        EXP {printf("SYNTAX OK. \nResult: %f\n", $1);}
        |EXPLIST 
        ; 
EXP     : OP_OP OP_PLUS EXP EXP OP_CP   {$$ = $3 + $4;}
        | OP_OP OP_MINUS EXP EXP OP_CP  {$$ = $3 - $4;}
        | OP_OP OP_MULT EXP EXP OP_CP   {$$ = $3 * $4;}
        | OP_OP OP_DIV EXP EXP OP_CP    {$$ = $3 / $4;}
        | ID    {$$ = get($1);} 
        | VALUEF  {$$ = $1;}
       // | FCALL 
        | ASG     {$$ = $1; }
        | OP_OP KW_IF EXPB EXPLIST EXPLIST OP_CP {$$ = ($3 == 1) ? $4 : $5;}
        | OP_OP KW_WHILE EXPB EXPLIST OP_CP  {while($3 == 1){
                                $$ = $4;    
        }}  
        | OP_OP KW_DEFV ID EXP OP_CP       {$$ = $4; add($3 , $4);}
              

EXPLIST     : EXP {$$ = $1; printf("SYNTAX OK. \nResult: %f\n", $1); $$ = $1;}
            | EXPLIST  EXP {printf("SYNTAX OK. \nResult: %f\n", $2); $$ = $2;}

ASG     : OP_OP KW_SET ID EXP OP_CP {$$ = $4; add($3,$4);}


/*FUNCTION    : OP_OP KW_DEFFUN ID OP_OP OP_CP OP_OP EXPLIST OP_CP {$$ = 1.0; .} 
            | OP_OP KW_DEFFUN ID OP_OP ID OP_CP OP_OP EXPLIST OP_CP {$$ = 1.0;}
            | OP_OP KW_DEFFUN ID OP_OP ID ID OP_CP OP_OP EXPLIST OP_CP {$$ = 1.0;}
            | OP_OP KW_DEFFUN ID OP_OP ID ID ID OP_CP OP_OP EXPLIST OP_CP {$$ = 1.0;}
*/

/*FCALL   : OP_OP ID OP_CP
        | OP_OP ID EXP OP_CP
        | OP_OP ID EXP EXP OP_CP
        | OP_OP ID EXP EXP EXP OP_CP
*/

EXPB    : OP_OP OP_EQ EXP EXP OP_CP {$$ = ($3==$4) ?  1 : 0;}
        | OP_OP OP_GT EXP EXP OP_CP  {$$ = ($3>$4) ?  1 : 0;}
        | KW_TRUE {$$ = 1;} 
        | KW_FALSE {$$ = 0;}
        | OP_OP KW_AND EXPB EXPB OP_CP {$$ = ($3 & $4);}
        | OP_OP KW_OR EXPB EXPB OP_CP {$$ = ($3 | $4);}
        | OP_OP KW_NOT EXPB OP_CP       {$$ = (!($3));}



%%



int yyerror(char *s) {
    printf("SYNTAX ERROR. Expression not recognized\n");
    exit(-1);
}



int main(int argc, char **argv){
createSymbolTable();
argv++, argc--;
if(argc > 0){ 
	yyin = fopen(argv[0], "r");
        if(yyin == NULL){
            perror("Error opening file: ");
            return 0;
        }
        yyparse();
}
else{
        yyin = stdin;
        fprintf(stdout,"$ ");
        while(1) {
                
                yyparse();
                fprintf(stdout,"$ ");
        } 
}
	
	return 0;
}
 

