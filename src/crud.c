#include "../include/crud.h"
#include "../include/event.h"
#include "../include/eventlist.h"
#include <stdio.h>
#include <string.h>

static char* ltrim(char *p){ while (p && *p==' ') p++; return p; }
static void  rtrim(char *p){ if(!p) return; size_t n=strlen(p); while(n&&p[n-1]==' ') p[--n]=0; }
static char* trim(char *p){ p=ltrim(p); rtrim(p); return p; }

_Bool addRecord(EventNode *eventList, char *record) {
    Event event = {0};
    int pos = 1;
    int initialCount = lengthEventList(eventList);
    char *col = NULL;
    
    while (pos < 7) {

        if(pos == 1) col = strtok(record, ",");
        if(pos > 1)  col = strtok(NULL, ",");

        if(!col) break;                 // defensive
        col = trim(col);                // <-- new (uses helper)

        if(pos == 2 && isInvalidDate(col)) pos = 99;
        if(pos == 6 && isInvalidStatus(col)) pos = 99;

        switch (pos) {
            case 1:
                event.id = assignEventValue(col);
                break;

            case 2:
                // was: strcpy(event.date, col);
                strncpy(event.date, col, DATE_LENGTH - 1);
                event.date[DATE_LENGTH - 1] = '\0';

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
        printEventList(eventList);
        return 1;
    }
    return 0;
    
}

// --- RANGE ---
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

// --- EXPORT ---
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
