#include "../include/crud.h"
#include "../include/event.h"
#include "../include/eventlist.h"
#include <stdio.h>
#include <stdlib.h>
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

_Bool updateRecordField(EventNode *eventList, char *id, char *fieldWithValue) {
    EventNode *eventFound = getEventNodeById(eventList, id);
    char *field = strtok(fieldWithValue, " = ");
    char *value = strtok(NULL, " = ");
    if(eventFound != NULL && field != NULL && value != NULL) {

        if(strcmp(field, "id") == 0) {
            free(eventFound->event.id);
            eventFound->event.id = assignEventValue(value);
            return 1;
        }

        if(strcmp(field, "date") == 0 && !isInvalidDate(value)) {
            strcpy(eventFound->event.date, value);
            return 1;
        }

        if(strcmp(field, "vehicle") == 0) {
            free(eventFound->event.vehicle);
            eventFound->event.vehicle = assignEventValue(value);
            return 1;
        }

        if(strcmp(field, "mission") == 0) {
            free(eventFound->event.mission);
            eventFound->event.mission = assignEventValue(value);
            return 1;
        }

        if(strcmp(field, "site") == 0) {
            free(eventFound->event.site);
            eventFound->event.site = assignEventValue(value);
            return 1;
        }

        if(strcmp(field, "status") == 0 && !isInvalidStatus(value)) {
            free(eventFound->event.status);
            eventFound->event.status = assignEventValue(value);
            return 1;
        }
    }
    return 0;
};

EventNode *deleteRecord(EventNode *eventList, char *id) {
    EventNode *newEventList = NULL;
    EventNode *cur = eventList;
    EventNode *deletedNode = NULL;
    int l = lengthEventList(eventList);

    if(getEventNodeById(eventList, id) == NULL) return eventList;

    for (int i = 0; i < l; i++) {
        if(!(strcmp(cur->event.id, id) == 0)) {
            newEventList = appendEvent(newEventList, cur->event);
        }else{
            deletedNode = cur;
        }
        cur = cur->next;
    }
    if(deletedNode != NULL) {
        free(deletedNode->event.id);
        free(deletedNode->event.mission);
        free(deletedNode->event.status);
        free(deletedNode->event.site);
        free(deletedNode->event.vehicle);
        free(deletedNode);
        return newEventList;
    }
    return eventList;
}

void rangePrint(EventNode *eventList, const char *startDate, const char *endDate) {
    if (eventList == NULL) return;

    // validate inputs using existing helper
    if (isInvalidDate((char*)startDate) || isInvalidDate((char*)endDate)) {
        printf("ERROR range invalid date\n");
        return;
    }
    // dates are YYYY-MM-DD; strcmp is valid lexical comparator
    if (strcmp(startDate, endDate) > 0) {
        printf("ERROR range start_after_end\n");
        return;
    }

    // list is sorted by date in your codebase (quickSortByDate), so single pass is enough
    for (EventNode *cur = eventList; cur != NULL; cur = cur->next) {
        if (strcmp(cur->event.date, startDate) < 0) continue;
        if (strcmp(cur->event.date, endDate) > 0) break;
        printf("%s,%s,%s,%s,%s,%s\n",
               cur->event.id,
               cur->event.date,
               cur->event.vehicle,
               cur->event.mission,
               cur->event.site,
               cur->event.status);
    }
}

