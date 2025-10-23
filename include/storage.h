#ifndef _storage_h 
#define _storage_h
#include "eventlist.h"
#include <stdio.h>

//method export;

EventNode *loadFile(FILE *file);
_Bool exportCSV(EventNode *eventList, const char *fileName);
#endif 
