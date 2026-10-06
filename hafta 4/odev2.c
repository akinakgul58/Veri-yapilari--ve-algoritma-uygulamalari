#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

void pushWord(Word** top, char* text) {
    Word* newNode = (Word*)malloc(sizeof(Word));
    if (newNode == NULL) {
        printf("Bellek ayrilamadi!\n");
        return;
    }
    strncpy(newNode->text, text, sizeof(newNode->text) - 1);
    newNode->text[sizeof(newNode->text) - 1] = '\0';
    newNode->next = *top;
    *top = newNode;
}

void popWord(Word** top) {
    if (*top == NULL) {
        printf("Geri alinacak kelime yok.\n");
        return;
    }
    Word* temp = *top;
    *top = (*top)->next;
    free(temp);
}

void showWords(Word* top) {
    if (top == NULL) return;
    showWords(top->next);
    printf("%s ", top->text);
}

void freeAll(Word** top) {
    while (*top != NULL) {
        popWord(top);
    }
}

int main(void) {
    Word* top = NULL;
    char command[20];
    char text[50];

    printf("Komutlar: add <kelime>, undo, show, exit\n");

    while (1) {
        printf("> ");
        if (scanf("%19s", command) != 1) break;

        if (strcmp(command, "add") == 0) {
            if (scanf("%49s", text) == 1) {
                pushWord(&top, text);
            }
        } else if (strcmp(command, "undo") == 0) {
            popWord(&top);
        } else if (strcmp(command, "show") == 0) {
            if (top == NULL) {
                printf("(bos)");
            } else {
                showWords(top);
            }
            printf("\n");
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Gecersiz komut!\n");
        }
    }

    freeAll(&top);
    return 0;
}