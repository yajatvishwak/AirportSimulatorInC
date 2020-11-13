#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "queues.c"

void land(flights *landing)
{
    printf("Flight Landing id: %s \n", dequeue(&landing->next));
}
void takeoff(flights *takingOff)
{
    printf("Flight Taking Off id: %s \n", dequeue(&takingOff->next));
}
int randoms()
{
    int i;
    int upper = 10;
    int lower = 1;
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void generateFlightID(char *s, const int len)
{
    static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXZ";
    static const char num[] = "0123456789";
    int k = 0;
    for (int i = 0; i < len / 2; i++)
    {
        s[k] = alpha[rand() % (sizeof(alpha) - 1)];
        k++;
    }
    for (int i = 0; i < len / 2; i++)
    {
        s[k] = num[rand() % (sizeof(num) - 1)];
        k++;
    }

    s[len] = 0;
}

void refill(flights *queue)
{
    char s[50];
    generateFlightID(s, 5);
    printf("Refilling\n");
    for (int i = 0; i < randoms() % 50; i++)
    {
        enqueue(s, queue);
        generateFlightID(s, 5);
    }
    printList(queue);
}
void refillU(flights *queue)
{
    char s[50];
    generateFlightID(s, 5);
    printf("Refilling\n");
    for (int i = 0; i < randoms() % 5; i++)
    {
        enqueue(s, queue);
        generateFlightID(s, 5);
    }
    printList(queue);
}
void main()
{
    srand(time(0));
    int counterTakeoff = 0;
    int counterLanding = 0;
    int interval = 1;
    flights *takeoffQueue = malloc(sizeof(flights));
    strcpy(takeoffQueue->ID, "TakeOff");
    flights *landingQueue = malloc(sizeof(flights));
    strcpy(landingQueue->ID, "Landing");

    printf("This is an Airport Simulator. It uses 2 Queues implemented in Linked List. \n");
    printf("It demonstrates how a system can effectively control air traffic.\n");
    printf("In this implementation we assume that there is one runway on a heavy traffic airport.\nThe goal is to see how queues can help to organise the incoming and outgoing flights");
    printf("\n \n \n");
    refill(takeoffQueue);
    refill(landingQueue);
    printf("\n \n \n");
    printf("Press 1 to start \n");
    int c = 0;
    scanf("%d", &c);
    while (c == 1 || c == 2)
    {
        if (c == 1)
        {
            if (getCount(takeoffQueue) <= 2)
            {
                printf("Warning: Refilling Take Off due to low flight count \n");
                refillU(takeoffQueue);
            }
            if (getCount(landingQueue) <= 2)
            {
                printf("Warning: Refilling Landing  due to low flight count \n");
                refillU(landingQueue);
            }

            printf("Time Interval is %d\n", interval);

            float scoreLanding = (float)0.45 * getCount(landingQueue);
            float scoreTakeoff = (float)0.55 * getCount(takeoffQueue); // giving more weight to taking fdd
            int selection = 0;                                         // 1 means take off, 0 means landing
            if (scoreLanding < scoreTakeoff)
            {
                selection = 1;
            }
            if (selection == 1)
            {

                printf("Flight Taking Off:  %s \n", dequeue(&takeoffQueue->next));
                printList(takeoffQueue);
                counterTakeoff++;
            }
            else
            {

                printf("Flight Landing:  %s \n", dequeue(&landingQueue->next));
                printList(landingQueue);
                counterLanding++;
            }

            printf("Press 1 to continue...\n");
            printf("Press 2 to refill...\n");
            scanf("%d", &c);
            interval++;
            printf("\n \n ");
        }
        else if (c == 2)
        {
            refillU(takeoffQueue);
            refillU(landingQueue);
            printf("Press 1 to continue...\n");
            scanf("%d", &c);
        }
        else
        {
            break;
        }
    }
}