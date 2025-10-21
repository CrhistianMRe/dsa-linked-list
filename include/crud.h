#ifndef _crud_h
#define _crud_h
#include "../include/eventlist.h"

_Bool addRecord(EventNode *eventlist, char *record);

//method update;
//method delete;
//method range;
// range: print events with start_date <= date <= end_date (inclusive)
void rangePrint(EventNode *eventList, const char *startDate, const char *endDate);

// export: write current list to CSV (header + rows). returns 1 on success, 0 on error
_Bool exportCSV(EventNode *eventList, const char *fileName);

//method find;

#endif
