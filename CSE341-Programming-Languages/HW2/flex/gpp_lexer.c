#include <stdio.h>


extern int yylex(void);
extern FILE* yyin;
extern char* yytext;

int main(int argc, char** argv){

argv++, argc--;
	if(argc > 0){ 
		yyin = fopen(argv[0], "r");
        if(yyin == NULL){
            perror("FILE COULD NOT OPEN ");
            return 0;
        }
		yylex();
        fclose(yyin);
	}
	else{	
		yyin = stdin;
        while(1) {
			yylex();
		} 
	}
	
	return 1 ;
    
}