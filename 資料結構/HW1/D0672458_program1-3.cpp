#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 
int max(int i, int j){
	return (i > j) ?i : j;
}

int arraymax(int a[],int max_num){
	int i = 0;
	for(i = 0;i < sizeof(a)-1 && a[i] != NULL;i++)
		max_num = max(max_num,a[i]);
	return max_num;
}

int main(){
	const char *c;
	char str[1024] = {'\0'},str_num[100] = {'\0'};
	int i = 0,num_max = -1, num_count = 0, num[512] = {NULL}, str_count = -1,num_len = 0;

	printf("請輸入一組數字: "); 
	gets(str);
	while(str[++str_count] != '\0'){
		if(str_num[0] == '\0'){
		str_num[0] = str[str_count];
		}
		else if(str[str_count] != ' '){
			num_len++;
			str_num[num_len] = str[str_count];
		}
	
		if(str[str_count] == ' ' || str[str_count+1] == '\0'){
			num[num_count++] = atoi(str_num);
			for(i = 0;str_num[i] != '\0';i++)
				str_num[i] = '\0';
			num_len = 0;
			continue;
		}
	}
	num_max = arraymax(num,num_max);				
	printf("\n\n最大值: %d", num_max);
	return 0;
}
