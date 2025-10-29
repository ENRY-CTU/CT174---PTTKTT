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
void InsertionSort(Data a[], int n){
    int i,j;
    for(i = 1; i < n; i++){
        j = i;
        while(j > 0 && (a[j].key < a[j-1].key)){
            swap(&a[j], &a[j-1]);
            j--;
        }
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
    printf("Thuat toan Insertion Sort\n");
    readData(a, &n);
    printf("Du lieu truoc khi sap xep:\n");
    printData(a, n);
    InsertionSort(a, n);
    printf("Du lieu sau khi sap xep:\n");
    printData(a, n);
    return 0;
}
