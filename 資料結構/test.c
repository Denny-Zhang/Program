#include<stdio.h>
#include<stdlib.h>

void main(){
	
	int *a,*b,c = 10;
	a = &c;
	b = a;
	c = 20;
	printf("%d",*b);
	
	return ;
}
