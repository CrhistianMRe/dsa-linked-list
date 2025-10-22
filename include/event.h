#ifndef _event_h
#define _event_h

#define DATE_LENGTH 11

typedef struct Event{
    char *id;
    char date[DATE_LENGTH];
    char *vehicle;
    char *mission;
    char *site;
    char *status;
} Event;

void *assignEventValue(char *origin);
_Bool isInvalidDate(char date[11]);
_Bool isInvalidStatus(char *status);
#endif
