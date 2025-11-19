#include <stdio.h>
#include <malloc.h>

typedef struct{
    char Name[50];
    int TL, GT, PA;
    float DG;
}DoVat;

DoVat *ReadFile(int *n, int *TLBalo){
    FILE *f;
    f = fopen("CaiBalo1.txt", "r");
    DoVat *dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    fscanf(f, "%d", TLBalo);
    int i = 0;
    while(!feof(f)){
        fscanf(f, "\n%d %d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].Name);
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].PA = 0;
        i++;
        dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat) * (i + 1));
    }
    *n = i;
    fclose(f);
    return dsdv;
}

void swap(DoVat *a, DoVat *b){
    DoVat temp = *a;
    *a = *b;
    *b = temp;
}

void sort(DoVat *a, int n){
    for(int i = 0; i < n - 2; i++){
        for(int j = n - 1; j >= i+1; j--){
            if(a[j].DG > a[j-1].DG){
                swap(&a[j], &a[j-1]);
            }
        }
    }
}

void inDS(DoVat *a, int n){
    int i, k;
    float TongGT=0, TongTL=0;
    printf("Bai toan tham an Cai Ba lo 1\n");
    printf("|---|-------------------------------|---------|---------|---------|-----------|\n");
    printf("|STT|           Ten Do Vat          | T Luong | Gia Tri | Don Gia | So Luong |\n");
    printf("|---|-------------------------------|---------|---------|---------|-----------|\n");
    for(i = 0, k = 1; i < n; i++){
            printf("|%-3d", k++);
            printf("|%-31s", a[i].Name);
            printf("|%-9d", a[i].TL);
            printf("|%-9d", a[i].GT);
            printf("|%-9.2f", a[i].DG);
            printf("|%-11d|\n", a[i].PA);
            TongGT = TongGT + a[i].PA * a[i].GT;
            TongTL = TongTL + a[i].PA * a[i].TL;
    }
    printf("|---|-------------------------------|---------|---------|---------|-----------|\n");
    printf("Tong trong luong: %.2f\n", TongTL);
    printf("Tong gia tri do vat: %.2f\n", TongGT);
}

void greedy(DoVat *a, int n, int TLBalo){
    for(int i = 0; i < n; i++){
        a[i].PA = TLBalo / a[i].TL;
        TLBalo -= a[i].PA * a[i].TL;
    }
}

int main(){
    int n, TLBalo;
    DoVat *dsdv = ReadFile(&n, &TLBalo);
    sort(dsdv, n);
    greedy(dsdv, n, TLBalo);
    inDS(dsdv, n);
    free(dsdv);
    return 0;
}
