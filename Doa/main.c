#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR_SCREEN system("cls")
#else
    #define CLEAR_SCREEN system("clear")
#endif

typedef struct {
    int id;
    int priority;
} Request;

typedef struct {
    Request* requests;
    int size;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->requests = (Request*)malloc(capacity * sizeof(Request));
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void destroyQueue(Queue* queue) {
    free(queue->requests);
    free(queue);
}

int isFull(Queue* queue) {
    return queue->size == queue->capacity;
}

int isEmpty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, int id, int priority) {
    if (isFull(queue)) {
        printf("Queue is full. Request cannot be added.\n");
        return;
    }

    Request newRequest;
    newRequest.id = id;
    newRequest.priority = priority;

    int i;
    for (i = queue->size - 1; i >= 0 && queue->requests[i].priority <= priority; i--) {
        queue->requests[i + 1] = queue->requests[i];
    }

    queue->requests[i + 1] = newRequest;
    queue->size++;
}

void dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("There are no requests to be processed!\n");
        return;
    }

    Request processedRequest = queue->requests[0];

    for (int i = 0; i < queue->size - 1; i++) {
        queue->requests[i] = queue->requests[i + 1];
    }

    queue->size--;

    printf("Processed request ID:%d, priority:%d\n", processedRequest.id, processedRequest.priority);
}

void printQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("There are no pending requests to be listed!\n");
        return;
    }

    printf("Pending requests to be processed: ");
    for (int i = 0; i < queue->size; i++) {
        printf("(ID:%d, priority:%d) ", queue->requests[i].id, queue->requests[i].priority);
    }
    printf("\n");
}

void changePriority(Queue* queue, int requestId, int newPriority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->requests[i].id == requestId) {
            queue->requests[i].priority = newPriority;
            printf("Request ID:%d's priority has been updated to %d\n", requestId, newPriority);
            return;
        }
    }

    printf("Request with ID %d not found in the queue\n", requestId);
}

int main() {
    Queue* queue = createQueue(10);
    int choice;

    do {
        CLEAR_SCREEN;
		printf("-AtlasCO. Software-\n");
		printf("--------------------------\n");
        printf("     |  Menu  |\n");
        printf("--------------------------\n");
        printf("|1. Add new request       |\n");
        printf("|2. Print waiting requests|\n");
        printf("|3. Process request       |\n");
        printf("|4. Change priority       |\n");
        printf("|0. Exit                  |\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("--------------------------\n");

        switch (choice) {
            case 1: {
                int priority;
                printf("Please enter request priority (between 1 and 10): ");
                scanf("%d", &priority);
                enqueue(queue, queue->size + 100, priority);
                break;
            }
            case 2:
                printQueue(queue);
                break;
            case 3:
                dequeue(queue);
                break;
            case 4: {
                int requestId, newPriority;
                printf("Please enter the ID of the request to change priority: ");
                scanf("%d", &requestId);
                printf("Please enter the new priority: ");
                scanf("%d", &newPriority);
                changePriority(queue, requestId, newPriority);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\nPress any key to continue...");
        getchar();
        getchar(); 

    } while (choice != 0);

    destroyQueue(queue);
    return 0;
}

