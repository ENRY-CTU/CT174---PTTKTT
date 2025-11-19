#include <stdio.h>
#include <malloc.h>

typedef struct{
	char name[50];
	int TL, GT, PA;
}Item;

typedef int bang[50][100];

Item *ReadFile(int *W, int *n){
	FILE *f = fopen("CaiBalo1.txt", "r");
	fscanf(f, "%d", W);
	Item *a = (Item*)malloc(sizeof(Item));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%d%[^\n]", &a[i].TL, &a[i].GT, &a[i].name);
		a[i].PA = 0;
		i++;
		a = (Item*)realloc(a, sizeof(Item) * (i + 1));
	}
	*n = i;
	fclose(f);
	return a;
}

void inDS(Item *a, int n, int W){
	int i, TongGT = 0, TongTL = 0;
	printf("\nPhuong an Cai Ba Lo 1 dung pp Quy Hoach Dong\n");
	for(i = 0; i < n; i++){
		printf("%-5d %-25s %-5d %-5d %-5d\n", i + 1, a[i].name, a[i].TL, a[i].GT, a[i].PA);
		TongTL+= a[i].PA * a[i].TL;
		TongGT+= a[i].PA * a[i].GT;
	}
	printf("Tong trong luong balo: %d\n", W);
	printf("Tong trong luong: %d\n", TongTL);
	printf("Tong gia tri balo: %d\n", TongGT);
}
void taoBang(Item *a, int n, int W, bang F, bang X){
	int xk, yk, k;
	int FMax, XMax, V;
	//Dien dong dau
	for(V = 0; V <= W ;V++){
		X[0][V] = V / a[0].TL;
		F[0][V] = X[0][V] * a[0].GT;
	}
	//Dien cac dong con lai
	for(k = 1; k < n; k++){
		for(V = 0; V <= W; V++){
			FMax = F[k - 1][V];
			XMax = 0;
			yk = V / a[k].TL;
			for(xk = 1; xk <= yk; xk++){
				if(F[k - 1][V - xk * a[k].TL] + xk * a[k].GT > FMax){
					FMax = F[k - 1][V - xk * a[k].TL] + xk * a[k].GT;
					XMax = xk;
				}
			}
			F[k][V] = FMax;
			X[k][V] = XMax;
		}
	}
}
void inBang(int n, int W, bang F, bang X){
	int V, k;
	for(k = 0; k < n; k++){
		for(V = 0; V <= W; V++){
			printf("|%4d%2d", F[k][V], X[k][V]);
		}
		printf("\n");
	}
}
void traBang(Item *a, int n, int W, bang X){
	int V,k;
	V = W;
	for(k = n - 1; k >= 0; k--){
		a[k].PA = X[k][V];
		V = V - X[k][V] * a[k].TL;
	}
}
int main(){
	int n, W;
	bang F,X;
	Item *a = ReadFile(&W, &n);
	taoBang(a, n, W, F, X);
	inBang(n, W, F, X);
	printf("\n");
	traBang(a, n, W, X);
	inDS(a, n , W);
	free(a);
	return 0;
}
