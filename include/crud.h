#ifndef _crud_h
#define _crud_h
#include "../include/eventlist.h"

EventNode *addRecord(EventNode *eventlist, char *record);

_Bool updateRecordField(EventNode *eventList, char *id, char *fieldWithValue);

EventNode *deleteRecord(EventNode *eventList, char *id);

void rangePrint(EventNode *eventList, const char *startDate, const char *endDate);

int findEvent(EventNode *head, const char *keyword);

#endif
