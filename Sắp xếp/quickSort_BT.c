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
int findPivot(Data a[], int left, int right){
    int firstkey;
    int k;
    k = left + 1;
    firstkey = a[left].key;
    while((k <= right) && (a[k].key == firstkey)){
        k++;
    }
    if(k > right) return -1;
    else{
        if(a[k].key < firstkey) return k;
        else return left;
    }
}
int Partition(Data a[], int i, int j, int pivot){
    int L, R;
    L = i;
    R = j;
    while(L <= R){
        while(a[L].key <= pivot) L++;
        while(a[R].key > pivot) R--;
        if(L < R){
            swap(&a[L], &a[R]);
        }
    }
    return L;
}
void quickSort(Data a[], int i, int j){
    int pivot, pivotindex, k;
    pivotindex = findPivot(a, i, j);
    if(pivotindex != -1){
        pivot = a[pivotindex].key;
        k = Partition(a, i, j, pivot);
        quickSort(a, i, k - 1);
        quickSort(a, k, j);
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
void printData(Data a[], int n){
    for(int i = 0; i < n; i++){
        printf("%3d%5d%8.2f\n",i+1, a[i].key, a[i].otherKey);
    }
}
int main(){
    Data a[100];
    int n;
    printf("Thuat toan Quick Sort\n");
    readData(a, &n);
    printf("Du lieu truoc khi sap xep:\n");
    printData(a, n);
    quickSort(a, 0, n - 1 );
    printf("Du lieu sau khi sap xep:\n");
    printData(a, n);
    return 0;
}
