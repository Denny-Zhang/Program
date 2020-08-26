#include<stdio.h>
#include<stdlib.h>

char i1[512][512]={'\0'};
char i[512][512] = {'\0'};

void print(FILE* f){
	for(int w = 0;w < 512;w++)
		for(int u=  0;u < 512;u++)
			fprintf(f,"%c",i1[w][u]);
}
void initialize(){
	for(int w = 0;w < 512;w++)
		for(int u=  0;u < 512;u++)
			i1[w][u] = '\0';
}
void mirror(int j){
	for(int w = 0;w < 512;w++){
		for(int u = 0;u < 512;u++){
			i1[w][u]=i[w][j--];
			if(j < 0)
				j = 511;
		}
	}
}
void flip(int j){
	for(int w = 0;w < 512;w++){
		j--;
		for(int u = 0;u < 512;u++){
			i1[w][u]=i[j][u];
		}
	}

}
void rotate(int j){
	for(int w = 0;w < 512;w++){
		j--;
		for(int u = 0;u < 512;u++){
			i1[w][u] = i[u][j];
		}
	}
}
void negative(){
	for(int w = 0;w < 512;w++){
		for(int u = 0;u < 512;u++){
			i1[w][u] = 255-i[w][u];
		}
	}
}
void blurry(){
	for(int w = 0;w < 512;w++){
		for(int u = 0;u < 512;u++){
			i1[w][u] = i[w][u];
		}
	}
	for(int w = 1;w < 511;w++){
		for(int u = 1;u < 511;u++){
			if(w % 2 == 1 && u % 2 == 1)
				i1[w][u] = (i[w-1][u-1]+i[w-1][u]+i[w-1][u+1]+i[w][u-1]+i[w][u]+i[w][u+1]+i[w+1][u-1]+i[w+1][u]+i[w+1][u+1])/'9'-'0';
			else if(w % 2 == 0 && u % 2 == 0 )
				i1[w][u] = (i[w-1][u-1]+i[w-1][u]+i[w-1][u+1]+i[w][u-1]+i[w][u]+i[w][u+1]+i[w+1][u-1]+i[w+1][u]+i[w+1][u+1])/'9'-'0';
		}
	}
}
void main(){
	char c;
	int a = 0,b = 0,j = 511;

	FILE* fs = fopen("lena","rb"); 

	while(feof(fs)==0){
		fscanf(fs,"%c",&c);
	
		if(c=='\n')
			continue;

		i[a][b++] = c;

		if(a == 511 && b == 512){
			b = 511;
			break;
		}
		if(b == 512){
			b = 0;
			if(a < 511)
				a++;
		}
	}
	fclose(fs);

	FILE* f1 = fopen("鏡像","ab");
	mirror(j);
	print(f1);
	fclose(f1);
	initialize();

	FILE* f2 = fopen("翻轉","ab");
	flip(j);
	print(f2);
	fclose(f2);
	initialize();
	
	FILE* f3 = fopen("旋轉","ab");
	rotate(j);
	print(f3);
	fclose(f3);
	initialize();

	FILE* f4 = fopen("負片","ab");
	negative();
	print(f4);
	fclose(f4);
	initialize();

	FILE *f5 = fopen("模糊","ab");
	blurry();
	print(f5);
	fclose(f5);

}