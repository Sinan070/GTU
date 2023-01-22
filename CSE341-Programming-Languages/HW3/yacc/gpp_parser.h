#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30



typedef struct symbol{
    char idName[MAX];    
    double valueF;
}Symbol;

typedef struct fSymbol{
    char idName[MAX];
    double paramaterValueFs[3];
}FSymbol;

int yyerror (char *s);
int yylex();

int count = 0;

Symbol * symbolTable;
FSymbol *fSymbolTable;
void createSymbolTable()
{
    symbolTable = (Symbol*) malloc(sizeof(Symbol)*MAX);
}

void add(char* id, double valueF){
    int cmp = 0;
    for(int i = 0 ; i < count ; ++i){
        cmp = strcmp(id,symbolTable[i].idName);
        if(!cmp){
            symbolTable[count].valueF = valueF;
            i = count;        
        }
    }
    
    if(count == 0 || cmp !=0){
        //perror("gecti");
        strcpy(symbolTable[count].idName,id);
        symbolTable[count].valueF = valueF;
        ++count;
    }
    

}

double get(char *id){
    //fprintf(stderr , "%d", count);
    double retVal = 0.0;
    for(int i = 0 ; i < count ; ++i){
        int cmp = strcmp(id,symbolTable[i].idName);
        if(!cmp){
            retVal = symbolTable[i].valueF;
            i = count;        
        }
    }
    //fprintf(stderr, "%f", retVal);
    return retVal;
}












