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
void selectionSort(Data a[], int n){
    int i, j, lowindex, lowkey;
    for(i = 0; i < n -1; i++){
        lowindex = i;
        lowkey = a[i].key;
        for(j = i + 1; j < n; j++){
            if(a[j].key < lowkey){
                lowkey = a[j].key;
                lowindex = j;
            }
        }
        swap(&a[i], &a[lowindex]);
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
    printf("Thuat toan Selection Sort\n");
    readData(a, &n);
    printf("Du lieu truoc khi sap xep:\n");
    printData(a, n);
    selectionSort(a, n);
    printf("Du lieu sau khi sap xep:\n");
    printData(a, n);
    return 0;
}
