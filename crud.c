// crud.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "crud.h"


static void freeEventFields(Event *e) {
    free(e->id);
    free(e->vehicle);
    free(e->mission);
    free(e->site);
    free(e->status);
    e->id = e->vehicle = e->mission = e->site = e->status = NULL;

   // helper

    static int contains_ci(const char *hay, const char *needle) {
    if (!hay || !needle || !*needle) return 0;
    for (const char *p = hay; *p; ++p) {
        const char *a = p, *b = needle;
        while (*a && *b && tolower((unsigned char)*a) == tolower((unsigned char)*b)) {
            ++a; ++b;
        }
        if (*b == '\0') return 1;
    }
    return 0;
}
//add
Node* add_event(Node *head, Event newEvent) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return head;
    }

    newNode->data = newEvent;
    newNode->next = NULL;

    // Insert at head if list is empty or new date is earlier
    if (!head || compare_dates(newEvent.date, head->data.date) < 0) {
        newNode->next = head;
        return newNode;
    }

    // Find insertion point
    Node *current = head;
    while (current->next && compare_dates(newEvent.date, current->next->data.date) > 0) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    return head;
}
//update
void update_event(Node *head, const char *id, char *updates[]) {
    Node *cur = head;
    while (cur) {
        if (strcmp(cur->data.id, id) == 0) {
            for (int i = 0; updates[i]; i++) {
                char *eq = strchr(updates[i], '=');
                if (!eq) continue;

                *eq = '\0';
                char *field = updates[i];
                char *value = eq + 1;

                if (strcmp(field, "date") == 0 && is_valid_date(value))
                    strcpy(cur->data.date, value);
                else if (strcmp(field, "vehicle") == 0)
                    strcpy(cur->data.vehicle, value);
                else if (strcmp(field, "mission") == 0)
                    strcpy(cur->data.mission, value);
                else if (strcmp(field, "site") == 0)
                    strcpy(cur->data.site, value);
                else if (strcmp(field, "status") == 0 && is_valid_status(value))
                    strcpy(cur->data.status, value);
                else
                    printf("Invalid field or value: %s=%s\n", field, value);
            }
            printf("Record %s updated.\n", id);
            return;
        }
        cur = cur->next;
    }
    printf("Record with ID %s not found.\n", id);
}

// delete implementation
int deleteEvent(EventNode **head, const char *id){
    if (!head || !*head || !id) return 0;

    EventNode *current = *head;
    EventNode *previous = NULL;

while (current != NULL) {
        IF (current->event.id && strcmp(current ->event.id, id) == 0){
            IF (previous == Null){
                *head = current -> next;
            }
            else{
                previous -> next = current -> next:
            }
            freeEventFields(&current->event);
            free(current);
            return 1; //went throgh
            }
            previous = current;
            current = current -> next;
        }
        return 0; //ehvent no found
        }

        // find implementation
int findEvents(EventNode *head, const char *keyword) {
    if (!keyword || !*keyword) return 0;

    int count = 0;
    while (head != NULL) {
        if (strstr(head->event.mission, keyword) || strstr(head->event.vehicle, keyword)) {
            printf("%s,%s,%s,%s,%s,%s\n",
                   head->event.id,
                   head->event.date,
                   head->event.vehicle,
                   head->event.mission,
                   head->event.site,
                   head->event.status);
            count++;
        }
        head = head->next;
    }
    return count;
}

}
