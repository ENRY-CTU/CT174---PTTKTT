#include <stdio.h>
void readFile(int a[][50], int *n){
	FILE *f = fopen("tamgiacso.txt", "r");
	int i = 0;
	while(!feof(f)){
		for(int j = 0; j <= i; j++){
			fscanf(f, "%d", &a[i][j]);
		}
		i++;
	}
	*n = i;
	fclose(f);
}
void printTriangle(int a[][50], int n){
	printf("Tam giac so da cho: \n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}
}
void printKQ(int PA[], int n){
	printf("Phuong an la duong di qua cac so: \n");
	int tong = PA[n-1];
	for(int i = 0; i < n-1; i++){
		printf("%d ->", PA[i]);
		tong+= PA[i];
	}
	printf("%d\n", PA[n-1]);
	printf("Tong cac so tren duong di la: %d", tong);
}
int colIndex(int F[][50], int i, int j) {
    int left = (j > 0) ? F[i-1][j-1] : -1;
    int mid = (j < i) ? F[i-1][j] : -1;
    int right = (j < i-1) ? F[i-1][j+1] : -1;
    
    int max_val = left, max_idx = j-1;
    
    if (mid > max_val) { max_val = mid; max_idx = j; }
    if (right > max_val) { max_val = right; max_idx = j+1; }
    
    return max_idx;
}
void taoBang(int a[][50], int n, int F[][50]){
	F[0][0] = a[0][0];
	F[1][0] = F[0][0] + a[1][0];
	F[1][1] = F[0][0] + a[1][1];
	for(int i = 2; i < n; i++){
		for(int j = 0; j <= i; j++){
			int k = colIndex(F, i, j);
			F[i][j] = F[i-1][k] + a[i][j];
		}
	}
}
void inBang(int F[][50], int n){
	printf("Bang quy hoach dong:\n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){
			printf("%5d", F[i][j]);
		}
		printf("\n");
	}
}
void traBang(int a[][50], int n, int F[][50], int PA[]){
	int Max = F[n-1][0], k = 0;
	for(int j = 1; j < n; j++){
		if(F[n-1][j] > Max){
			Max = F[n-1][j];
			k = j;
		}
	}
	for(int i = n - 1; i >= 0; i--){
		PA[i] = a[i][k];
		k = colIndex(F, i, k);
	}
}
int main(){
	int a[50][50], n = 0, F[50][50], PA[50];
	readFile(a, &n);
	printTriangle(a, n);
	taoBang(a, n , F);
	inBang(F, n);
	traBang(a, n , F , PA);
	printKQ(PA, n);
	return 0;
}
