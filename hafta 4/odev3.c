#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;

void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    if (newJob == NULL) {
        printf("Bellek ayrilamadi!\n");
        return;
    }
    strncpy(newJob->fileName, fileName, sizeof(newJob->fileName) - 1);
    newJob->fileName[sizeof(newJob->fileName) - 1] = '\0';
    newJob->next = NULL;

    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob;
    } else {
        q->rear->next = newJob;
        q->rear = newJob;
    }
    printf("'%s' kuyruga eklendi.\n", newJob->fileName);
}

void processNextJob(Queue* q) {
    if (q->front == NULL) {
        printf("Kuyruk bos, yazdirilacak is yok.\n");
        return;
    }
    PrintJob* temp = q->front;
    printf("Yazdiriliyor: %s\n", temp->fileName);
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Kuyruk bos.\n");
        return;
    }
    PrintJob* current = q.front;
    int i = 1;
    printf("Yazdirma kuyrugu:\n");
    while (current != NULL) {
        printf("%d. %s\n", i++, current->fileName);
        current = current->next;
    }
}

void freeQueue(Queue* q) {
    while (q->front != NULL) {
        PrintJob* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}

int main(void) {
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    int choice;
    char fileName[50];

    do {
        printf("\n1) Yeni dosya ekle\n2) Yazdir\n3) Kuyrugu goster\n0) Cikis\nSecim: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Dosya adi: ");
                scanf("%49s", fileName);
                enqueuePrintJob(&q, fileName);
                break;
            case 2:
                processNextJob(&q);
                break;
            case 3:
                showQueue(q);
                break;
            case 0:
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while (choice != 0);

    freeQueue(&q);
    return 0;
}