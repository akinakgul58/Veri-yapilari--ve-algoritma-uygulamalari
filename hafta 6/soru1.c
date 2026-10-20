#include <stdio.h>
#include <stdlib.h>

typedef struct Dugum {
    int deger;
    struct Dugum *sol;
    struct Dugum *sag;
} Dugum;

Dugum *yeniDugum(int deger) {
    Dugum *d = (Dugum *)malloc(sizeof(Dugum));
    if (d == NULL) {
        printf("Bellek ayrilamadi!\n");
        exit(1);
    }
    d->deger = deger;
    d->sol = NULL;
    d->sag = NULL;
    return d;
}

Dugum *insert(Dugum *kok, int deger) {
    if (kok == NULL)
        return yeniDugum(deger);

    if (deger < kok->deger)
        kok->sol = insert(kok->sol, deger);
    else if (deger > kok->deger)
        kok->sag = insert(kok->sag, deger);

    return kok;
}

void inorder(Dugum *kok) {
    if (kok == NULL)
        return;
    inorder(kok->sol);
    printf("%d ", kok->deger);
    inorder(kok->sag);
}

void temizle(Dugum *kok) {
    if (kok == NULL)
        return;
    temizle(kok->sol);
    temizle(kok->sag);
    free(kok);
}

int main(void) {
    Dugum *kok = NULL;
    int degerler[] = {40, 20, 60, 10, 30, 50, 70};
    int n = sizeof(degerler) / sizeof(degerler[0]);

    for (int i = 0; i < n; i++)
        kok = insert(kok, degerler[i]);

    printf("Inorder: ");
    inorder(kok);
    printf("\n");

    temizle(kok);
    return 0;
}