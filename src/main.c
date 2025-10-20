#include "stdio.h"
#include "../include/eventlist.h"
#include "../include/storage.h"
#include <string.h>

static _Bool exit = 1;
static EventNode *eventlist = NULL;

void intHandler(int dummy){
    freeList(eventlist);
    exit= 0;
}

void printDef(){
    printf("\n-help for command list\n");
}

_Bool contains(char prompt[], char ext[]) {
    return strstr(prompt, ext) != NULL;
}

int main(int argc, char *argv[]) {


    while(exit){
        char prompt[100] = {};

        printf("stlm>> ");
        fgets(prompt, sizeof(prompt), stdin);
        prompt[strcspn(prompt, "\n")] = 0;

        char *arg1 = strtok(prompt, " ");

        char *arg2 = strtok(NULL, " ");

        if(contains(arg1, "load") && (contains(arg2, ".txt") || contains(arg2, ".csv"))) {

            FILE *file = fopen(arg2, "r");

            if(file == NULL){
                printf("Error while opening file, use -help.\n");
                return 1;
            }

            printf("FILE FOUND!\n\n");

            eventlist = loadFile(file);
            printEventList(eventlist);
        } else {printDef(); }

    }

    
        
    


    return 0;
}

