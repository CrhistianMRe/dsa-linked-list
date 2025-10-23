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

    EventNode *eventList = {};
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
                strcpy(event.date, temp);
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

_Bool exportCSV(EventNode *eventList, const char *fileName) {
    FILE *f = fopen(fileName, "w");
    if (!f) { printf("ERROR export\n"); return 0; }

    // header
    fprintf(f, "id,date,vehicle,mission,site,status\n");

    // rows in current order (already chronological by your sorter)
    for (EventNode *cur = eventList; cur != NULL; cur = cur->next) {
        fprintf(f, "%s,%s,%s,%s,%s,%s\n",
                cur->event.id,
                cur->event.date,
                cur->event.vehicle,
                cur->event.mission,
                cur->event.site,
                cur->event.status);
    }
    fclose(f);
    printf("OK\n");
    return 1;
}
