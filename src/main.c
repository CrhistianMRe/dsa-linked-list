#include "stdio.h"
#include "../include/eventlist.h"
#include "../include/storage.h"
#include "../include/crud.h"
#include <endian.h>
#include <string.h>

static _Bool close = 1;
EventNode *eventlist = NULL;

void intHandler(int dummy){
    freeList(eventlist);
    close = 0;
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


    while(close) {
        char prompt[100] = {};

        printf("stlm>> ");
        fgets(prompt, sizeof(prompt), stdin);
        prompt[strcspn(prompt, "\n")] = 0;

        char *arg1 = strtok(prompt, " ");

        char *arg2 = strtok(NULL, "");

        _Bool handled = 0;

        //load
        if(!handled && strcmp(arg1, "load") == 0 && (arg2 != NULL) && (contains(arg2, ".txt") || contains(arg2, ".csv"))) {

            FILE *file = fopen(arg2, "r");

            if(file == NULL){
                printf("Error while opening file, use -help.\n");
                return 1;
            }

            printf("FILE FOUND!\n\n");

            eventlist = loadFile(file);
            printEventList(eventlist);
            handled = 1;
        } 

        //add
        if((contains(arg1, "add") && (arg2 != NULL) && containsAmountOfTimes(arg2, ',') == 5)) {
            int len = lengthEventList(eventlist);
            eventlist = addRecord(eventlist, arg2);
            if((lengthEventList(eventlist) == len + 1)) {
                printf("\nrecord added\n");
                printEventList(eventlist);
            } else {printf("\nrecord not added\n");}

            handled = 1;
        }

        //update
        if(strcmp(arg1, "update") == 0 && (arg2 != NULL)) {
            strtok(arg2, " ");
            char *arg3 = strtok(NULL, "");
            if(updateRecordField(eventlist, arg2, arg3)){
                printf("\nupdate succeded!\n");
                printEventList(eventlist);
            }else{printf("\nupdate failed!\n");};
            handled = 1;
        }

        //delete
        if(strcmp(arg1, "delete") == 0 && (arg2 != NULL)) {
            int len = lengthEventList(eventlist);
            eventlist = deleteRecord(eventlist, arg2);
            if(len != lengthEventList(eventlist)) {
                printf("\ndelete succeded!\n");
                printEventList(eventlist);
            }else{printf("\ndelete failed!\n");}
            handled = 1;
        }

        //range
        if (!handled && arg1 != NULL && strstr(arg1, "range")) {
            char *arg3 = strtok(NULL, " ");
            if (arg2 != NULL && arg3 != NULL) {
                rangePrint(eventlist, arg2, arg3);
                handled = 1;
            }
        }

        //find
        if(!handled && arg1 != NULL && strcmp(arg1, "find") == 0 && arg2 != NULL) {
            int count = findEvent(eventlist, arg2);
            printf("\nAmount of records found: %d\n", count);
            handled = 1;
        }

        if (!handled && arg1 && strcmp(arg1, "export") == 0 && arg2 != NULL) {
            exportCSV(eventlist, arg2);
            handled = 1;
        }

        if(!handled) printDef();
    }

    
        
    


    return 0;
}

