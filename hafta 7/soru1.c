#include <stdio.h>
#include <stdlib.h>

typedef struct Dugum {
    int deger;
    struct Dugum *sol;
    struct Dugum *sag;
} Dugum;

Dugum* yeniDugum(int deger) {
    Dugum *d = (Dugum*)malloc(sizeof(Dugum));
    d->deger = deger;
    d->sol = d->sag = NULL;
    return d;
}

Dugum* ekle(Dugum *kok, int deger) {
    if (kok == NULL)
        return yeniDugum(deger);
    if (deger < kok->deger)
        kok->sol = ekle(kok->sol, deger);
    else if (deger > kok->deger)
        kok->sag = ekle(kok->sag, deger);
    return kok;
}

int ara(Dugum *kok, int hedef) {
    if (kok == NULL)
        return 0;

    printf("Ziyaret edilen dugum: %d\n", kok->deger);

    if (hedef == kok->deger)
        return 1;
    else if (hedef < kok->deger)
        return ara(kok->sol, hedef);
    else
        return ara(kok->sag, hedef);
}

int yukseklik(Dugum *kok) {
    if (kok == NULL)
        return 0;
    int sol = yukseklik(kok->sol);
    int sag = yukseklik(kok->sag);
    return 1 + (sol > sag ? sol : sag);
}

void temizle(Dugum *kok) {
    if (kok == NULL) return;
    temizle(kok->sol);
    temizle(kok->sag);
    free(kok);
}

int main() {
    Dugum *kok = NULL;
    int hazineler[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    int n = sizeof(hazineler) / sizeof(hazineler[0]);

    for (int i = 0; i < n; i++)
        kok = ekle(kok, hazineler[i]);

    int sayi;
    printf("Bir sayi girin: ");
    scanf("%d", &sayi);

    if (ara(kok, sayi))
        printf("Hazine bulundu!\n");
    else
        printf("Bosuna kazdin!\n");

    printf("\nAgac yuksekligi: %d\n", yukseklik(kok));
    printf("En kotu durumda hazineyi bulmak icin %d adim gerekir.\n", yukseklik(kok));

    temizle(kok);
    return 0;
}