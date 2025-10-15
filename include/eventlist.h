#ifndef _eventlist_h
#define _eventlist_h
#include "event.h"

typedef struct _EventNode {
    Event event;
    struct _EventNode *next;
} EventNode;

int lengthEventList(EventNode *head);
void printEventList(EventNode *head);
EventNode *findTail(EventNode *head);

EventNode *createEventNode(Event event);
EventNode *appendEvent(EventNode *head, Event event);
EventNode *prependEvent(EventNode *head, Event event);
EventNode *searchEvent(EventNode *head, Event event);

Event getEvent(EventNode *head, int index);
#endif
