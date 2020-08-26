#include <stdio.h> 
#include <stdlib.h>


int fib_i(int n){
	int n1 = 0, n2 = 1, r = 0, i = 0;
	r = n;
	for(i = 1;i < n;i++){
		r = n1 + n2;
		n1 = n2;
		n2 = r;
	}
	return r;
}

int fib_r(int n){
	if(n == 0)
		return 0;
	if(n == 1)
		return 1;
	return (fib_r(n-1)+fib_r(n-2));
}

int main(){
	char n[10];
	int i = 0, r = 0, n_trans = 0;
	
	while(1){
		printf("½Ð¿é¤J¼Æ¦r:");
		scanf("%s",&n);
		if(n[0] < '0' || n[0] > '9')
			exit(0);
		n_trans = atoi(n);
		if(n_trans < 2){
			printf("error!\n");
			continue;
		}
		r = fib_r(n_trans);
		i = fib_i(n_trans);
		printf("F(%d)(recur.) = %d\n", n_trans, r);
		printf("F(%d)(iter.) = %d\n", n_trans, i);
	}
	return 0;
}


