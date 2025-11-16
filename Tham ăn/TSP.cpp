#include <stdio.h>

typedef struct{
    float doDai;
    int dau, cuoi;
}canh;
void swap(canh *a, canh *b){
    canh temp = *a;
    *a = *b;
    *b = temp;
}
void sort(canh *a, int n){
    for(int i = 0; i < n; i++){
        for(int j = n - 1; j > i; j--){
            if(a[j].doDai < a[j-1].doDai){
                swap(&a[j], &a[j-1]);
            }
        }
    }
}
void docfile(canh a[], int *n){
    FILE *f = fopen("TSP.txt", "r");
    fscanf(f, "%d", n);
    int k = 0;
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            float temp; 
            fscanf(f, "%f", &temp);
            if(i < j){
                a[k].doDai = temp;
                a[k].dau = i;
                a[k].cuoi = j;
                k++;
            }
        }
    }
    fclose(f);
}
void inDA(canh *a, int n, int laPA){
    float tong = 0.0;
    for(int i = 0; i < n; i++){
        printf("%d %c%c = %8.2f\n", i+1, a[i].dau+65, a[i].cuoi+65, a[i].doDai);
        tong+= a[i].doDai;
    }
    if(laPA) printf("Tong do dai: %8.2f\n", tong);
}
int laDinhCap3(canh *PA, int n, canh moi){
    int demDau = 0, demCuoi = 0;
    for(int i = 0; i < n; i++){
        if(moi.dau == PA[i].dau || moi.dau == PA[i].cuoi) demDau++;
        if(moi.cuoi == PA[i].dau || moi.cuoi == PA[i].cuoi) demCuoi++;
        if(demDau >= 2 || demCuoi >= 2) return 1;
    }
    return 0;
}
int findRoot(int u, int parent[]){
    while(u != parent[u]) u = parent[u];
    return u;
}
void greedy(canh *dscanh, int n, canh *PA){
    int parent[n], j = 0;

    for(int i = 0; i < n; i++) parent[i] = i;

    for(int i = 0; i < n*(n-1)/2 && j < n; i++){
        int rDau = findRoot(dscanh[i].dau, parent);
        int rCuoi = findRoot(dscanh[i].cuoi, parent);

        if((j < n - 1 && !laDinhCap3(PA, j, dscanh[i]) && rDau != rCuoi) || 
            (j == n - 1 && !laDinhCap3(PA, n - 1, dscanh[i]) && rDau == rCuoi)){
            PA[j++] = dscanh[i];
            if(j < n) parent[rDau] = rCuoi;
        }
    }
}
int main(){
    int n;
    canh dscanh[50];
    docfile(dscanh, &n);
    canh PA[50];
    sort(dscanh, n*(n-1)/2);
    printf("Danh sach cac do thi da sap xep\n");
    inDA(dscanh, n*(n-1)/2, 0);
    greedy(dscanh, n, PA);
    printf("Dap an\n");
    inDA(PA, n, 1);
    return 0;
}
