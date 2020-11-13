#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Queues in linked lists
typedef struct flight
{
    char ID[50];
    struct flight *next;
} flights;

void enqueue(char flightID[50], flights *head)
{
    flights *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(flights));
    strcpy(current->next->ID, flightID);
    current->next->next = NULL;
}
char *dequeue(flights **head)
{
    flights *nextFlight = NULL;
    char *currentID;

    if (*head == NULL)
    {
        return NULL;
    }
    else
    {
        nextFlight = (*head)->next;
        strcpy(currentID, (*head)->ID);
        free(*head);
        *head = nextFlight;
        return currentID;
    }
}
int getCount(flights *head)
{
    flights *present = head->next;
    int counter = 1;
    while (present->next != NULL)
    {
        counter++;
        present = present->next;
    }
    return counter;
}

void printList(flights *list)
{
    printf("------------------------\n");
    flights *present = list;
    int count = 1;
    while (present->next != NULL)
    {
        printf("| Plane ID #%d: %s \t|\n", count, present->ID);
        count++;
        present = present->next;
    }
    printf("| Plane ID #%d: %s \t|\n", count, present->ID);
    printf("------------------------\n");
}
// void main()
// {
//     flights *Queue = malloc(sizeof(flights));
//     strcpy(Queue->ID, "QUEUE");
//     enqueue("f1", Queue);
//     enqueue("f2", Queue);
//     enqueue("f3", Queue);
//     printList(Queue);
//     char *name1 = dequeue(&Queue->next);
//     printf("Poping flight : %s\n", name1);
//     printList(Queue);
// }