#include <stdio.h>
typedef struct{
    float dodai;
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
            if(a[j].dodai > a[j-1].dodai){
                swap(&a[j], &a[j-1]);
            }
        }
    }
}
void docfile(canh a[][100], int *n){
    FILE *f = fopen("TSP.txt", "r");
    fscanf(f, "%d", n);
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            fscanf(f, "%f", &a[i][j].dodai);
            a[i][j].dau = i;
            a[i][j].cuoi = j; 
        }
    }
    fclose(f);
}
float canhNN(canh a[][100], int n){
    float cMin = 3.4e38;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j && a[i][j].dodai < cMin){
                cMin = a[i][j].dodai;
            }
        }
    }
    return cMin;
}
void nhanhcan(canh a[][100], int n, int i, int dau, float TGT, float *GNNTT, canh x[], canh PA[]) {
    if(i == n-1) {
        TGT += a[dau][x[0].dau].dodai;
        if(TGT < *GNNTT) {
            *GNNTT = TGT;
            for(int j = 0; j < n-1; j++) PA[j] = x[j];
            PA[n-1] = a[dau][x[0].dau];
        }
        return;
    }
    for(int j = 0; j < n; j++) {
        if(dau != j) {
            int da_dung = 0;
            for(int k = 0; k < i; k++) if(x[k].dau == j || x[k].cuoi == j) { da_dung = 1; break; }
            
            if(!da_dung) {
                float CD = TGT + a[dau][j].dodai + (n-i-1)*canhNN(a,n);
                if(CD < *GNNTT) {
                    x[i] = a[dau][j];
                    nhanhcan(a, n, i+1, j, TGT + a[dau][j].dodai, GNNTT, x, PA);
                }
            }
        }
    }
}
void inPA(canh PA[], int n){
    float tong = 0.0;
    printf("Phuong an:\n");
    for(int i = 0; i < n; i++){
        tong += PA[i].dodai;
        printf(" Canh %c%c = %5.2f\n", PA[i].dau+65, PA[i].cuoi+65, PA[i].dodai);
    }
    printf("CHU TRINH: ");
    for(int i = 0; i < n; i++){
        printf("%c ", PA[i].dau+65);
        printf("-> ");
    }
    printf("%c", PA[0].dau+65);
    printf("\nTong do dai cac canh: %5.2f\n", tong);
}
int main(){
    canh a[100][100];
    int n;
    docfile(a, &n);
    char tpxp;
    printf("Thanh pho xuat phat (A-%c): ", n-1+65);
    scanf(" %c", &tpxp);
    canh PA[n], x[n];
    float GNNTT = 3.4e38;
    nhanhcan(a, n, 0, tpxp-65, 0, &GNNTT, x, PA);
    inPA(PA, n);
    return 0;
}
