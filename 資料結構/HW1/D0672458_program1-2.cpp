#include <stdio.h> 
#include <stdlib.h>

int ack(int i, int j){
	if(i == 0)
		return j+1;
	if(i > 0 && j == 0)
		return ack(i-1,1);
	return ack(i-1, ack(i,j-1));
}
int main(){
	char i[10],j[10];
	int r = 0, i_trans = 0,j_trans = 0;
	
	while(1){
		printf("請輸入數字: i = ");
		scanf("%s",&i);
		if(i[0] < '0' || i[0] > '9')
			exit(0);
		printf("請輸入數字: j = ");
		scanf("%s",&j);
		
		if(j[0] < '0' || j[0] > '9')
			exit(0);
		i_trans = atoi(i);
		j_trans = atoi(j);
		r = ack(i_trans, j_trans);	
		printf("A(%d,%d) = %d\n", i_trans, j_trans, r);
	}
	return 0;
}
