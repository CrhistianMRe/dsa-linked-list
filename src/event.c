#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../include/event.h"

void *assignEventValue(char *origin) {
    char *result = NULL;
    if(strlen(origin) != 0 ){
        result = malloc(strlen(origin) + 1);
        strcpy(result, origin);
    }
    return result;
}

_Bool isInvalidDate(char date[10]) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if(isdigit(date[i])  || (date[i] == '-')) count ++;
    }
    return count != 10;
}

_Bool isInvalidStatus(char *status) {
    const char *array[5] = {"Scheduled", "Success", "Failure", "Delayed", "Cancelled"};
    for (int i = 0; i < 5; i++) {
        if(strcmp(array[i], status) == 0) return 0;
    }
    return 1;
}

