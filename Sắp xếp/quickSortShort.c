#include <stdio.h>
typedef struct{int key;float otherKey;}Data;

void swap(Data*a,Data*b){Data t=*a;*a=*b;*b=t;}

int findPivot(Data a[],int l,int r){
    int f=a[l].key,k=l+1;
    while(k<=r&&a[k].key==f)k++;
    return k>r?-1:(a[k].key>f?k:l);
}

int Partition(Data a[],int i,int j,int p){
    int L=i,R=j;
    while(L<=R){
        while(a[L].key<p)L++;
        while(a[R].key>=p)R--;
        if(L<R)swap(&a[L],&a[R]);
    }
    return L;
}

void quickSort(Data a[],int i,int j){
    int p=findPivot(a,i,j);
    if(p!=-1){
        int pv=a[p].key,k=Partition(a,i,j,pv);
        quickSort(a,i,k-1);
        quickSort(a,k,j);
    }
}

void readData(Data a[],int*n){
    FILE*f=fopen("data.txt","r");
    int i=0;
    while(fscanf(f,"%d%f",&a[i].key,&a[i].otherKey)==2)i++;
    *n=i;
    fclose(f);
}

void printData(Data a[],int n){
    for(int i=0;i<n;i++)
        printf("%3d%5d%8.2f\n",i+1,a[i].key,a[i].otherKey);
}

int main(){
    Data a[100];
    int n;
    printf("Thuat toan Quick Sort\n");
    readData(a,&n);
    printf("Du lieu truoc khi sap xep:\n");
    printData(a,n);
    quickSort(a,0,n-1);
    printf("Du lieu sau khi sap xep:\n");
    printData(a,n);
    return 0;
}
