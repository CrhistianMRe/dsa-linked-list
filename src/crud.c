#include "../include/crud.h"
#include "../include/event.h"
#include "../include/eventlist.h"
#include <string.h>

EventNode *addRecord(EventNode *eventList, char *record) {
    Event event = {0};
    int pos = 1;
    int initialCount = lengthEventList(eventList);
    char *col = NULL;
    

    while (pos < 7) {

        if(pos == 1) col = strtok(record, " , ");
        if(pos > 1) col = strtok(NULL, " , ");

        if(pos == 2 && isInvalidDate(col)) pos = 99;
        if(pos == 6 && isInvalidStatus(col)) pos = 99;

        switch (pos) {
            case 1:
                event.id = assignEventValue(col);
                break;
            case 2:
                strcpy(event.date, col);
                break;
            case 3:
                event.vehicle = assignEventValue(col);
                break;
            case 4:
                event.mission = assignEventValue(col);
                break;
            case 5:
                event.site = assignEventValue(col);
                break;
            case 6:
                event.status = assignEventValue(col);
                eventList = appendEvent(eventList, event);
        }
        pos++;
    }

    if((initialCount +1) == lengthEventList(eventList)) {
        quickSortByDate(eventList, 0, lengthEventList(eventList)-1);
        return eventList;
    }
    return NULL;
}

