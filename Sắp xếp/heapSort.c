#include <stdio.h>

typedef struct{
    int key;
    float otherKey;
}Data;

void swap(Data *a, Data *b){
    Data temp = *a;
    *a = *b;
    *b = temp;
}
void PushDown(Data a[], int first, int last){
    int f = first;
    while(f <= (last - 1)/2){
        int L = 2*f+1, R = 2*f+2;
        if(last == L){
            if(a[f].key > a[L].key){
                swap(&a[f], &a[L]);
            }
            return;
        }
        if((a[f].key > a[L].key) && (a[L].key <= a[R].key)){
            swap(&a[f], &a[L]);
            f = L;
        }
        else if((a[f].key > a[R].key) && (a[L].key > a[R].key)){
            swap(&a[f], &a[R]);
            f = R;
        }
        else return;
    }
}
void heapSort(Data a[], int n){
    int i;
    for(i = (n - 2)/2; i >= 0; i--){
        PushDown(a, i, n - 1);
    }
    for(i = n - 1; i >= 2; i--){
        swap(&a[0], &a[i]);
        PushDown(a, 0, i - 1);
    }
}
void readData(Data a[], int *n){
    FILE *f;
    f = fopen("data.txt", "r");
    int i = 0;
    while(!feof(f)){
        fscanf(f, "%d%f", &a[i].key, &a[i].otherKey);
        i++;
    }
    *n = i;
    fclose(f);
}
void printData(Data a[], int n, int m){
    if(n < m){
        for(int i = 0; i < m; i++){
            printf("%3d%5d%8.2f\n",i+1, a[i].key, a[i].otherKey);
        }
    }
    else{
        for(int i = n - 1; i >= m; i--){
            printf("%3d%5d%8.2f\n",n - i, a[i].key, a[i].otherKey);
        }
    }
}
int main(){
    Data a[100];
    int n;
    printf("Thuat toan Heap Sort\n");
    readData(a, &n);
    printf("Du lieu truoc khi sap xep:\n");
    printData(a, 0, n);
    heapSort(a, n);
    printf("Du lieu sau khi sap xep Heap:\n");
    printData(a, 0, n);
    printf("Du lieu sau khi sap xep Heap tang dan:\n");
    printData(a, n, 0);
    return 0;
}
