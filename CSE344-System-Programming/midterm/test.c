#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 3
#define MAX_WORD_LEN 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int split_string_into(char *input, char ** words){
    int word_count = 0;
    int retval;

    char *token = strtok(input, " ");
    while (token != NULL && word_count < 3) {
        strncpy(words[word_count], token, strlen(token));
        word_count++;
        token = strtok(NULL, " ");
    }

    if (!(word_count == 2 || (word_count == 3 && isdigit(words[2][0])))) {
        retval = -1;
        
    }
    return retval;
    
}




int main() {
    char str[] = "Hello world asd";
    char * words[3];
    for (size_t i = 0; i < 3; i++)
    {
        words[i] = (char*)malloc(sizeof(char)*256);
    }
    
    
    if(split_string_into(str, words) == 0){
        printf("aq");
        for (int i = 0; i < 3; i++)
        {
            printf("%s ", words[i]);            
        }
    }
    else{
        printf("aq");
    }
    

    

    return 0;
}
/*
int main(){

    char ** words;
    int i;
    char str[100]= {"test test2 5"};
    for (i = 0; i < 3; i++)
    {
        words[i] = (char *)malloc(sizeof(char)*256);
    }
    
    split_string(str, words);
    for (i = 0; i < 3; i++)
    {
        printf("%s ",words[i]);
    }

    return 0;

}*/