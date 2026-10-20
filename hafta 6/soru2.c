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


int search(Dugum *kok, int deger) {
    if (kok == NULL)
        return 0;
    if (deger == kok->deger)
        return 1;
    if (deger < kok->deger)
        return search(kok->sol, deger);
    return search(kok->sag, deger);
}


int findMin(Dugum *kok) {
    while (kok->sol != NULL)
        kok = kok->sol;
    return kok->deger;
}

void temizle(Dugum *kok) {
    if (kok == NULL)
        return;
    temizle(kok->sol);
    temizle(kok->sag);
    free(kok);
}

int main(void) {
    Dugum *root = NULL;
    int numbers[] = {40, 20, 60, 10, 30, 50, 70};
    for (int i = 0; i < 7; i++)
        root = insert(root, numbers[i]);

    if (search(root, 30))
        printf("30 agacta bulundu.\n");
    else
        printf("30 agacta bulunamadi.\n");

    if (search(root, 90))
        printf("90 agacta bulundu.\n");
    else
        printf("90 agacta bulunamadi.\n");

    if (root != NULL)
        printf("En kucuk eleman: %d\n", findMin(root));

    temizle(root);
    return 0;
}