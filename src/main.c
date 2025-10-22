#include "stdio.h"
#include "../include/eventlist.h"
#include "../include/storage.h"
#include "../include/crud.h"
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

int containsAmountOfTimes(char prompt[], char expected) {
    int count = 0;
    for (int i = 0; i < strlen(prompt) + 1; i++) {
        char single = prompt[i];
        if(strchr(&single, expected) != NULL) count++;
    }
    return count;
}

int main(int argc, char *argv[]) {


    while(exit){
        char prompt[100] = {};

        printf("stlm>> ");
        fgets(prompt, sizeof(prompt), stdin);
        prompt[strcspn(prompt, "\n")] = 0;

        char *arg1 = strtok(prompt, " ");

        char *arg2 = strtok(NULL, " ");

        //load
        if(contains(arg1, "load") && (arg2 != NULL) && (contains(arg2, ".txt") || contains(arg2, ".csv"))) {

            FILE *file = fopen(arg2, "r");

            if(file == NULL){
                printf("Error while opening file, use -help.\n");
                return 1;
            }

            printf("FILE FOUND!\n\n");

            eventlist = loadFile(file);
            printEventList(eventlist);

        } else {printDef(); }

        //add
        if((contains(arg1, "add") && (arg2 != NULL) && containsAmountOfTimes(arg2, ',') == 5)) {
            int len = lengthEventList(eventlist);
            eventlist = addRecord(eventlist, arg2);
            if((lengthEventList(eventlist) == len + 1)) {
                printf("\nrecord added\n");
                printEventList(eventlist);
            } else {printf("\nrecord not added\n");}
        }



    }

    
        
    


    return 0;
}

