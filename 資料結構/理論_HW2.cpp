#include<stdio.h>
#include<stdlib.h>

int main(){
	int n = 5;
	int i = 0, j = 0, a[n][n], b[3*n-2];
	for(i = 0;i < 3*n-2;i++){
		b[i] = rand()%10;
		printf("%d ",b[i]);
	}
	puts("");
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++){
			if(i == j || j == i+1 || j == i-1 && i != 0)
				a[i][j] = b[2*(i+1)+(j+1)-3];			
			else
				a[i][j] = 0;
			printf(" %d ,",a[i][j]);
			
		}
	
	 
	return 0;
}

