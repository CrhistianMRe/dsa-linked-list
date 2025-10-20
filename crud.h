#ifndef _crud_h
#define _crud_h

#include 'eventlsit.h'
//method add;
//method update;
int deleteEvent(EventNode **head, const char *id);//method delete;
//method range;
int findEvents(EventNode *head, const char *keyword);
//method find;

#endif
