#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct axis{
	int ibug;
	int jbug;
	axis(int x, int y){
		ibug = x;
		jbug = y;
	}
};

int main(int argc,char *argv[]){
	if(argc == 5){			//只接受5個參數 
		int i = 0, j = 0, k = 0, ran = -1, row = atoi(argv[1]), col = atoi(argv[2]), init_row_loc = atoi(argv[3]), init_col_loc = atoi(argv[4]);
		int array_size[row+2][col+2] = {0}, count[row][col] = {0}, non_zero = 0, moves_count = 0;
		axis cockroach(init_row_loc, init_col_loc);
		int imove[8] = {-1,0,1,1,1,0,-1,-1}, jmove[8] = {1,1,1,0,-1,-1,-1,0};
		
		if(init_row_loc > row || init_col_loc > col){ 	//起始位置不得超過最大位置 
			puts("起始位置太大!!");
			return 0;
		}
		else if(row <= 2 || row > 40 || col<= 2 || col > 20){		//限制陣列大小 
			puts("陣列最大為40*20，最小為3*3!!");
			return 0;
		}
			
		srand(time(NULL));			//random 隨時間而改變 
		 
		for(i = 0;i < row+2;i++)			//array_size多兩行列，外圍設-1，並初始化 
			for(j = 0;j < col+2;j++){
				if(i == 0 || j == 0 || i == row+1 || j == col+1)
					array_size[i][j] = -1;
				else
					array_size[i][j] = 0;
			}
		for(j = 0;j < row;j++)				//初始化count 
			for(k = 0;k < col;k++)
				count[j][k] = 0;
				
		count[init_row_loc-1][init_col_loc-1]++;		//初始位置+1，XY軸方向為X軸向下Y軸向右 
				
		for(i = 0;i < 50000;i++){			//最多跑5萬次 
			ran = rand()%8;					//隨機亂數0~7 
			switch(ran){			//根據亂數移動位置並計數，遇到-1就重新取亂數 
				case 0:
					if(array_size[cockroach.ibug+imove[0]][cockroach.jbug+jmove[0]] == -1)
						continue;
					cockroach.ibug += imove[0];
					cockroach.jbug += jmove[0];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;
				case 1:
					if(array_size[cockroach.ibug+imove[1]][cockroach.jbug+jmove[1]] == -1)
						continue;
					cockroach.ibug += imove[1];
					cockroach.jbug += jmove[1];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;
				case 2:
					if(array_size[cockroach.ibug+imove[2]][cockroach.jbug+jmove[2]] == -1)
						continue;
					cockroach.ibug += imove[2];
					cockroach.jbug += jmove[2];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;	
				case 3:
					if(array_size[cockroach.ibug+imove[3]][cockroach.jbug+jmove[3]] == -1)
						continue;
					cockroach.ibug += imove[3];
					cockroach.jbug += jmove[3];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;
				case 4:
					if(array_size[cockroach.ibug+imove[4]][cockroach.jbug+jmove[4]] == -1)
						continue;
					cockroach.ibug += imove[4];
					cockroach.jbug += jmove[4];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;
				case 5:
					if(array_size[cockroach.ibug+imove[5]][cockroach.jbug+jmove[5]] == -1)
						continue;
					cockroach.ibug += imove[5];
					cockroach.jbug += jmove[5];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;
				case 6:
					if(array_size[cockroach.ibug+imove[6]][cockroach.jbug+jmove[6]] == -1)
						continue;
					cockroach.ibug += imove[6];
					cockroach.jbug += jmove[6];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;
				case 7:
					if(array_size[cockroach.ibug+imove[7]][cockroach.jbug+jmove[7]] == -1)
						continue;
					cockroach.ibug += imove[7];
					cockroach.jbug += jmove[7];
					count[cockroach.ibug-1][cockroach.jbug-1]++;
					moves_count++;
					break;
			}
			if(i>= row * col-1){			//最少要移動row*col-1次才能存在過每個位置 
				for(j = 0;j < row;j++){
					for(k = 0;k < col;k++)
						if(count[j][k] == 0)	//如果位置一遇到0就跳出	 
							break;
						else
							non_zero++;			//計算非0位置的數量 
				}
				if(non_zero == row*col){		//如果沒有為0的位置跳出最外圍的for迴圈 
					break;
				}
					
				else
					non_zero = 0;				//全部位置不全為非0，重新計數 
			}
				
		}
		FILE *fp;
		fp = fopen("D0672458_program2.txt","w");	//建寫檔 
		
		fprintf(fp,"\nThe total number of moves : %d\n\n", moves_count);	//輸出移動次數 
		for(i = 0;i < row;i++)						//格式化輸出count陣列 
			for(j = 0;j < col;j++){
				fprintf(fp,"%5d ", count[i][j]);
				if(j != col-1)
					fprintf(fp,", ");
				else
					fprintf(fp,"\n");
			}
	}
	else						//輸入的參數數目不為5 
		printf("Error!");		

	return 0;
}
