#include <stdio.h>
typedef struct{
    float dodai;
    int dau, cuoi;
}canh;
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
void inMT(canh a[][100], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n ;j++){
            printf(" %c%c = %5.2f", a[i][j].dau+65, a[i][j].cuoi+65, a[i][j].dodai);
        }
        printf("\n");
    }
}
void inPA(canh a[], int n){
    float tong = 0.0;
    printf("Phuong an\n");
    for(int i = 0; i < n; i++){
        printf(" %c%c = %.2f\n", a[i].dau+65, a[i].cuoi+65, a[i].dodai);
        tong+= a[i].dodai;
    }
    printf("Chu trinh\n");
    for(int i = 0; i < n; i++){
        printf(" %c", a[i].dau+65);
        printf(" ->");
    }
    printf(" %c", a[0].dau+65);
    printf("\nTong do dai chu trinh: %5.2f", tong);
}
float canhNN(canh a[][100], int n){
    float Cmin = 3.4e38;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n ;j++){
            if(i != j && a[i][j].dodai < Cmin){
                Cmin = a[i][j].dodai;
            }
        }
    } 
    return Cmin;
}
void nhanhcan(canh a[][100], int n, int i, int dau, float TGT, float *GNNTT, canh PA[], canh x[]){
    if(i == n-1){
        TGT += a[dau][x[0].dau].dodai;
        if(*GNNTT > TGT){
            *GNNTT = TGT;
            for(int j = 0; j < n-1; j++) PA[j] = x[j];
            PA[n-1] = a[dau][x[0].dau];
            return;
        }
    }
    for(int j = 0; j < n; j++){
        if(dau != j){
            int da_dung = 0;
            for(int k = 0; k < i; k++) if(x[k].dau == j || x[k].cuoi == j) {da_dung = 1; break;}
            
            if(!da_dung){
                float CD = TGT + (n-i)*canhNN(a, n);
                if(CD < *GNNTT){
                    x[i] = a[dau][j];
                    nhanhcan(a, n, i + 1, j, TGT + a[dau][j].dodai, GNNTT, PA, x);
                }
            }
        }
    }
}
int main(){
    canh a[100][100];
    int n;
    char tpxp;
    float GNNTT = 3.4e38, TGT = 0.0;
    docfile(a, &n);
    canh PA[n], x[n];
    inMT(a, n);
    printf("Chon thanh pho xuat phat: (tu A -> %c) ", n - 1 + 65);
    scanf(" %c", &tpxp);
    nhanhcan(a, n, 0, tpxp - 65, TGT, &GNNTT, PA, x);
    inPA(PA, n);
    return 0;
}
