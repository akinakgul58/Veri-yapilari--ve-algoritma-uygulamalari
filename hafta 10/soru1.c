#include <stdio.h>

#define N 5

const char *sehir[N] = {"Istanbul", "Ankara", "Izmir", "Bursa", "Antalya"};

int graf[N][N] = {
    { 0, 1, 0, 1, 0 },
    { 1, 0, 1, 0, 1 },
    { 0, 1, 0, 0, 0 },
    { 1, 0, 0, 0, 1 },
    { 0, 1, 0, 1, 0 }
};

void bfs(int baslangic) {
    int ziyaret[N] = {0};
    int kuyruk[N];
    int bas = 0, son = 0;

    ziyaret[baslangic] = 1;
    kuyruk[son++] = baslangic;

    printf("BFS: ");
    while (bas < son) {
        int u = kuyruk[bas++];
        printf("%s ", sehir[u]);

        for (int v = 0; v < N; v++) {
            if (graf[u][v] && !ziyaret[v]) {
                ziyaret[v] = 1;
                kuyruk[son++] = v;
            }
        }
    }
    printf("\n");
}

void dfs_ziyaret(int u, int ziyaret[]) {
    ziyaret[u] = 1;
    printf("%s ", sehir[u]);

    for (int v = 0; v < N; v++) {
        if (graf[u][v] && !ziyaret[v]) {
            dfs_ziyaret(v, ziyaret);
        }
    }
}

void dfs(int baslangic) {
    int ziyaret[N] = {0};
    printf("DFS: ");
    dfs_ziyaret(baslangic, ziyaret);
    printf("\n");
}

int main(void) {
    bfs(0);
    dfs(0);
    return 0;
}