#ifndef _event_h
#define _event_h

#define DATE_LENGTH 10

typedef struct Event{
    char *id;
    char date[DATE_LENGTH];
    char *vehicle;
    char *mission;
    char *site;
    char *status;
} Event;

#endif
