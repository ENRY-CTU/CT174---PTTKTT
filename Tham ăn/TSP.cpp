#include <stdio.h>
#include <malloc.h>

typedef struct {
    float doDai;
    int dau, cuoi;
} canh;
void swap(canh *x, canh *y) {
    canh tmp = *x;
    *x = *y;
    *y = tmp;
}
void bubbleSort(canh a[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = n-1; j > i; j--)
            if (a[j].doDai < a[j-1].doDai)
                swap(&a[j], &a[j-1]);
}
void readFromFile(canh a[], int *n) {
    FILE* f = fopen("TSP.txt", "r");
    if (!f) { printf("Loi Mo File"); return; }
    
    fscanf(f, "%d", n);
    int k = 0;
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            float temp;
            fscanf(f, "%f", &temp);
            if (i < j) {
                a[k].doDai = temp;
                a[k].dau = i;
                a[k].cuoi = j;
                k++;
            }
        }
    }
    fclose(f);
}
void inDSCanh(canh a[], int m, int laPA) {
    float tong = 0.0;
    for (int i = 0; i < m; i++) {
        printf("%3d %c%c = %8.2f\n", i+1, a[i].dau+65, a[i].cuoi+65, a[i].doDai);
        tong += a[i].doDai;
    }
    if (laPA) printf("Tong do dai: %8.2f\n", tong);
}
int laDinhCap3(canh PA[], int k, canh moi) {
    int demDau = 0, demCuoi = 0;
    for (int i = 0; i < k; i++) {
        if (moi.dau == PA[i].dau || moi.dau == PA[i].cuoi) demDau++;
        if (moi.cuoi == PA[i].dau || moi.cuoi == PA[i].cuoi) demCuoi++;
        if (demDau >= 2 || demCuoi >= 2) return 1;
    }
    return 0;
}
int findRoot(int u, int parent[]) {
    while (u != parent[u]) u = parent[u];
    return u;
}
void Greedy(canh dsCanh[], int n, canh PA[]) {
    int parent[n], j = 0;
    for (int i = 0; i < n; i++) parent[i] = i;
    
    for (int i = 0; i < n*(n-1)/2 && j < n; i++) {
        int rDau = findRoot(dsCanh[i].dau, parent);
        int rCuoi = findRoot(dsCanh[i].cuoi, parent);
        
        if ((j < n-1 && !laDinhCap3(PA, j, dsCanh[i]) && rDau != rCuoi) ||
            (j == n-1 && !laDinhCap3(PA, n-1, dsCanh[i]) && rDau == rCuoi)) {
            PA[j++] = dsCanh[i];
            if (j < n) parent[rDau] = rCuoi;
        }
    }
}
int main() {
    canh dsCanh[200];
    int n;
    readFromFile(dsCanh, &n);
    canh PA[n];
    bubbleSort(dsCanh, n*(n-1)/2);
    printf("Danh Sach Cac Canh (Da Sap Xep):\n");
    inDSCanh(dsCanh, n*(n-1)/2, 0);  
    Greedy(dsCanh, n, PA);
    printf("\nPHUONG AN:\n");
    inDSCanh(PA, n, 1);
    return 0;
   }
