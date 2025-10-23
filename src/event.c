#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <../include/event.h>

void *assignEventValue(char *origin) {
    char *result;
    if(strlen(origin) != 0 ){
        result = malloc(strlen(origin) + 1);
        strcpy(result, origin);
    }
    return result;
}


_Bool isInvalidDateRange(const char date[11]) {
    char yearStr[5] = {0}, monthStr[3] = {0}, dayStr[3] = {0};
    
    strncpy(yearStr, &date[0], 4);
    strncpy(monthStr, &date[5], 2);
    strncpy(dayStr, &date[8], 2);
    
    char *endptr;

    long year = strtol(yearStr, &endptr, 10);
    if (*endptr != '\0' || year < 1) return 1;

    long month = strtol(monthStr, &endptr, 10);
    if (*endptr != '\0' || month < 1 || month > 12) return 1;

    long day = strtol(dayStr, &endptr, 10);
    if (*endptr != '\0' || day < 1 || day > 31) return 1;

    return 0; 
}


_Bool isInvalidDate(char date[11]) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if(isdigit(date[i])  || (date[i] == '-')) count ++;
    }
    if(isInvalidDateRange(date)) count = 99;
    return count != 10;
}

_Bool isInvalidStatus(char *status) {
    const char *array[5] = {"Scheduled", "Success", "Failure", "Delayed", "Cancelled"};
    for (int i = 0; i < 5; i++) {
        if(strcmp(array[i], status) == 0) return 0;
    }
    return 1;
}

