#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hasta {
    int id;
    char isim[50];
    char durum[20];
    struct Hasta *next;
} Hasta;

typedef struct {
    Hasta *front;
    Hasta *rear;
} Kuyruk;

typedef struct {
    Hasta *top;
} Yigin;

typedef struct {
    Hasta *head;
    Hasta *tail;
} Gecmis;

Hasta *hastaOlustur(int id, const char *isim) {
    Hasta *h = (Hasta *)malloc(sizeof(Hasta));
    if (h == NULL) {
        printf("Bellek ayrilamadi!\n");
        exit(1);
    }
    h->id = id;
    strncpy(h->isim, isim, sizeof(h->isim) - 1);
    h->isim[sizeof(h->isim) - 1] = '\0';
    strcpy(h->durum, "bekliyor");
    h->next = NULL;
    return h;
}

void enqueue(Kuyruk *q, Hasta *h) {
    h->next = NULL;
    strcpy(h->durum, "bekliyor");
    if (q->rear == NULL) {
        q->front = q->rear = h;
    } else {
        q->rear->next = h;
        q->rear = h;
    }
}

Hasta *dequeue(Kuyruk *q) {
    if (q->front == NULL) {
        printf("Hata: Bekleme kuyrugu bos!\n");
        return NULL;
    }
    Hasta *h = q->front;
    q->front = h->next;
    if (q->front == NULL)
        q->rear = NULL;
    h->next = NULL;
    return h;
}

void push(Yigin *s, Hasta *h) {
    strcpy(h->durum, "muayenede");
    h->next = s->top;
    s->top = h;
}

Hasta *pop(Yigin *s) {
    if (s->top == NULL) {
        printf("Hata: Muayene odasi bos!\n");
        return NULL;
    }
    Hasta *h = s->top;
    s->top = h->next;
    h->next = NULL;
    return h;
}

void gecmiseEkle(Gecmis *g, Hasta *h) {
    strcpy(h->durum, "tamamlandi");
    h->next = NULL;
    if (g->head == NULL) {
        g->head = g->tail = h;
    } else {
        g->tail->next = h;
        g->tail = h;
    }
}

void listele(Hasta *bas, const char *baslik, const char *bosMesaj) {
    printf("--- %s ---\n", baslik);
    if (bas == NULL) {
        printf("%s\n", bosMesaj);
        return;
    }
    for (Hasta *p = bas; p != NULL; p = p->next)
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", p->id, p->isim, p->durum);
}

void durumYazdir(Kuyruk *q, Yigin *s, Gecmis *g) {
    listele(q->front, "Bekleyen Hastalar", "Hasta yok.");
    listele(s->top, "Muayene Odasindaki Hastalar", "Hasta yok.");
    listele(g->head, "Tamamlanan Hastalar", "Hasta yok.");
}

void muayeneyeAl(Kuyruk *q, Yigin *s) {
    Hasta *h = dequeue(q);
    if (h != NULL) {
        push(s, h);
        printf("%s muayeneye alindi.\n", h->isim);
    }
}

void muayeneyiTamamla(Yigin *s, Gecmis *g) {
    Hasta *h = pop(s);
    if (h != NULL) {
        gecmiseEkle(g, h);
        printf("%s muayenesi tamamlandi.\n", h->isim);
    }
}

void zincirTemizle(Hasta *bas) {
    while (bas != NULL) {
        Hasta *tmp = bas;
        bas = bas->next;
        free(tmp);
    }
}

int main(void) {
    Kuyruk kuyruk = {NULL, NULL};
    Yigin yigin = {NULL};
    Gecmis gecmis = {NULL, NULL};

    printf("=== Baslangic Durumu ===\n");
    durumYazdir(&kuyruk, &yigin, &gecmis);

    printf("\n=== Hastalar Kaydediliyor ===\n");
    enqueue(&kuyruk, hastaOlustur(1, "Ahmet"));
    enqueue(&kuyruk, hastaOlustur(2, "Mehmet"));
    enqueue(&kuyruk, hastaOlustur(3, "Ayse"));
    durumYazdir(&kuyruk, &yigin, &gecmis);

    printf("\n=== Hasta Aktarim Islemleri ===\n");
    muayeneyeAl(&kuyruk, &yigin);
    muayeneyiTamamla(&yigin, &gecmis);
    muayeneyeAl(&kuyruk, &yigin);
    muayeneyiTamamla(&yigin, &gecmis);

    printf("\n=== Tum Islemler Sonrasi ===\n");
    durumYazdir(&kuyruk, &yigin, &gecmis);

    printf("\n=== Bos Kontrol Testi ===\n");
    muayeneyiTamamla(&yigin, &gecmis);

    zincirTemizle(kuyruk.front);
    zincirTemizle(yigin.top);
    zincirTemizle(gecmis.head);
    return 0;
}