#ifndef _crud_h
#define _crud_h
#include "../include/eventlist.h"

EventNode *addRecord(EventNode *eventlist, char *record);

_Bool updateRecordField(EventNode *eventList, char *id, char *fieldWithValue);
//method delete;
//method range;
//method find;

#endif
