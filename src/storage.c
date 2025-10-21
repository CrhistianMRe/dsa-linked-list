#include "stdio.h"
#include "../include/event.h"
#include "../include/eventlist.h"
#include <stdio.h>
#include <string.h>


static int read = 0;

void skipRecord(FILE *file){
    read = 0;
    fscanf(file, "\n");;
}

EventNode *loadFile(FILE *file){

    EventNode *eventList = NULL;
    _Bool skipLine = 0;
    Event event = {0};

    do {
        char temp[257] = {0};

        read += fscanf(file, "%256[^,\n],", temp);

        //missing record validation
        if(strlen(temp) == 0) {
            skipRecord(file);
        }

        if(read == 2 && isInvalidDate(temp)) skipRecord(file);
        if(read == 6 && isInvalidStatus(temp)) skipRecord(file);

        switch (read) {
            case 1:
                event.id = assignEventValue(temp);
                break;
            case 2:
                // was: strcpy(event.date, temp);
                strncpy(event.date, temp, DATE_LENGTH - 1);
                event.date[DATE_LENGTH - 1] = '\0';
                break;
            case 3:
                event.vehicle = assignEventValue(temp);
                break;
            case 4:
                event.mission = assignEventValue(temp);
                break;
            case 5:
                event.site = assignEventValue(temp);
                break;
            case 6:
                event.status = assignEventValue(temp);
        }

        if(read == 6 && !feof(file)){
            eventList = appendEvent(eventList, event);
            fscanf(file, "\n");
            read = 0;
            memset(&event, 0, sizeof(event));
            skipLine = 0;
        }

    } while (!feof(file));

    quickSortByDate(eventList, 0, lengthEventList(eventList)-1);
    return eventList;
}
