#include "../include/eventlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lengthEventList(EventNode *head){
    int count = 0;
    EventNode *cur_node = head;
    while (cur_node != NULL) {
        cur_node = cur_node->next;
        count++;
    }
    return count;
}

void printEventList(EventNode *head) {
    EventNode *cur = head;
    while (cur != NULL) {
        printf("%s,", cur->event.id);
        printf("%s,", cur->event.date);
        printf("%s,", cur->event.vehicle);
        printf("%s,", cur->event.mission);
        printf("%s,", cur->event.site);
        printf("%s", cur->event.status);
        printf("\n");
        cur = cur-> next;
    }
}

void freeList(EventNode *head){
    EventNode *cur = head;
    EventNode *temp = NULL;
    if(cur == NULL){
        printf("Not possible to free list\n");
        return;
    }
    while (cur != NULL) {
        temp = cur->next;
        free(cur->event.id);
        free(cur->event.mission);
        free(cur->event.vehicle);
        free(cur->event.site);
        free(cur->event.status);
        free(cur);
        cur = temp;
    }
}

EventNode *findTail(EventNode *head) {
    EventNode *cur = head;
    if (cur == NULL) return NULL; 
    while (cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}

EventNode *createEventNode(Event event) {
    EventNode *n = (EventNode*) malloc(sizeof(EventNode));
    n->event.id = event.id;
    for(int i = 0; i < 10; i++){
        n->event.date[i] = event.date[i];
    }
    n->event.vehicle = event.vehicle;
    n->event.mission = event.mission;
    n->event.site = event.site;
    n->event.status = event.status;
    n->next = NULL;
    return n;
}

EventNode *appendEvent(EventNode *head, Event event) {
    EventNode *newNode = createEventNode(event);
    if (head == NULL) {
        return newNode;
    }
    EventNode *tail = findTail(head);
    tail->next = newNode;
    return head;
}

EventNode *prependEvent(EventNode *head, Event event){
    EventNode *new_node = createEventNode(event);
    new_node->next = head;
    return new_node;
}

_Bool isEventEqual(EventNode *current, Event event){
    int count = 0;

    if(strcmp(current->event.id, event.id) == 0) count++;
    if(strcmp(current->event.date, event.date) == 0) count ++;
    if(strcmp(current->event.vehicle, event.vehicle) == 0) count ++;
    if(strcmp(current->event.mission, event.mission) == 0) count ++;
    if(strcmp(current->event.site, event.site) == 0) count ++;
    if(strcmp(current->event.status, event.status) == 0) count ++;

    return count == 6;
}

EventNode *searchEvent(EventNode *head, Event event){
    EventNode *cur = head;
    while (cur != NULL) {
        if (isEventEqual(cur, event)) {
            return cur;
        } else {
            cur = cur->next;
        }
    }
    return NULL;
}

Event getEvent(EventNode *head, int index) {
    Event emptyEvent = {"notfound", "notfound00", "notfound", "notfound", "notfound", "notfound"};
    int i;
    EventNode *cur = head;
    if (head == NULL || index<0) {
        return emptyEvent;
    }
    for (i=0; i<index; i++) {
        if (cur == NULL) { break; }
        cur = cur->next;
    }
    if (i < index) {
        return emptyEvent;
    }
    return cur->event;
}

EventNode *getEventNodeById(EventNode *head, char *id) {
    int length = lengthEventList(head);
    EventNode *cur = head;
    if (head == NULL || length<0) {
        return NULL;
    }
    for (int i=0; i<length; i++) {
        if (cur == NULL) { break; }
        if(strcmp(cur->event.id, id) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

EventNode *getEventNode(EventNode *head, int index) {
    EventNode *emptyEvent = {0};
    int i;
    EventNode *cur = head;
    if (head == NULL || index<0) {
        return emptyEvent;
    }
    for (i=0; i<index; i++) {
        if (cur == NULL) { break; }
        cur = cur->next;
    }
    if (i < index) {
        return emptyEvent;
    }
    return cur;
}

int partition(EventNode *head, int low, int high) {
    Event pivot = getEvent(head, high);
    int i = low -1;
    Event temp = {};
    for (int j = low; j < high; j++) {
        //pivot is greater
        if(strcmp(getEvent(head, j).date, pivot.date) < 0) {
            i += 1;
            temp = getEvent(head, i);
            getEventNode(head, i)->event = getEvent(head, j);
            getEventNode(head, j)->event = temp;
        }
    }
    int rightIndex = i+1;
    Event temp2 = {};
    temp2 = pivot;
    getEventNode(head, high)->event = getEvent(head, rightIndex);
    getEventNode(head, rightIndex)->event = temp2;
    return rightIndex;
}

//quicksort practice
void quickSortByDate(EventNode *head, int low, int high) {
    if(low < high) {
        int middleIndex = partition(head, low, high);
        quickSortByDate(head, low, middleIndex -1);
        quickSortByDate(head, middleIndex +1 , high);
    }
}







