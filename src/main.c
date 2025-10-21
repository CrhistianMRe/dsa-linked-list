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

int containsAmountOfTimes(char s[], char expected) {
    int count = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == expected) count++;
    }
    return count;
}


int main(int argc, char *argv[]) {


    while(exit){
        char prompt[100] = {};

        printf("stlm>> ");
        if (!fgets(prompt, sizeof(prompt), stdin)) break;
        prompt[strcspn(prompt, "\n")] = 0;

        char *arg1 = strtok(prompt, " ");     // command
        char *rest = strtok(NULL, "");        // everything after 1st space (may be NULL)

        #define LTRIM(p) while ((p) && *(p) == ' ') (p)++

        _Bool handled = 0;

        // load <file>
        if (!handled && arg1 && strstr(arg1, "load") && rest) {
            LTRIM(rest);
            if (strstr(rest, ".csv") || strstr(rest, ".txt")) {
                FILE *file = fopen(rest, "r");
                if (!file) { printf("Error while opening file, use -help.\n"); }
                else {
                    printf("FILE FOUND!\n\n");
                    eventlist = loadFile(file);
                    printEventList(eventlist);
                    fclose(file);
                }
                handled = 1;
            }
        }

        // add <id,date,vehicle,mission,site,status>  (record may contain spaces)
        if (!handled && arg1 && strstr(arg1, "add") && rest) {
            LTRIM(rest);
            if (containsAmountOfTimes(rest, ',') == 5) {
                if (addRecord(eventlist, rest)) printf("\nrecord added\n");
                else printf("\nrecord not added\n");
                handled = 1;
            }
        }

        // range <start> <end>
        if (!handled && arg1 && strstr(arg1, "range") && rest) {
            char s[32]={0}, e[32]={0};
            if (sscanf(rest, "%31s %31s", s, e) == 2) {
                rangePrint(eventlist, s, e);
                handled = 1;
            }
        }

        // export <file>
        if (!handled && arg1 && strstr(arg1, "export") && rest) {
            LTRIM(rest);
            exportCSV(eventlist, rest);
            handled = 1;
        }

        if (!handled) printDef();
        
    }
    
    return 0;
}  
        

