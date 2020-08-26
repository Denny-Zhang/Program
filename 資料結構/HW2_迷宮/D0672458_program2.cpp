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
	if(argc == 5){			//�u����5�ӰѼ� 
		int i = 0, j = 0, k = 0, ran = -1, row = atoi(argv[1]), col = atoi(argv[2]), init_row_loc = atoi(argv[3]), init_col_loc = atoi(argv[4]);
		int array_size[row+2][col+2] = {0}, count[row][col] = {0}, non_zero = 0, moves_count = 0;
		axis cockroach(init_row_loc, init_col_loc);
		int imove[8] = {-1,0,1,1,1,0,-1,-1}, jmove[8] = {1,1,1,0,-1,-1,-1,0};
		
		if(init_row_loc > row || init_col_loc > col){ 	//�_�l��m���o�W�L�̤j��m 
			puts("�_�l��m�Ӥj!!");
			return 0;
		}
		else if(row <= 2 || row > 40 || col<= 2 || col > 20){		//����}�C�j�p 
			puts("�}�C�̤j��40*20�A�̤p��3*3!!");
			return 0;
		}
			
		srand(time(NULL));			//random �H�ɶ��ӧ��� 
		 
		for(i = 0;i < row+2;i++)			//array_size�h���C�A�~��]-1�A�ê�l�� 
			for(j = 0;j < col+2;j++){
				if(i == 0 || j == 0 || i == row+1 || j == col+1)
					array_size[i][j] = -1;
				else
					array_size[i][j] = 0;
			}
		for(j = 0;j < row;j++)				//��l��count 
			for(k = 0;k < col;k++)
				count[j][k] = 0;
				
		count[init_row_loc-1][init_col_loc-1]++;		//��l��m+1�AXY�b��V��X�b�V�UY�b�V�k 
				
		for(i = 0;i < 50000;i++){			//�̦h�]5�U�� 
			ran = rand()%8;					//�H���ü�0~7 
			switch(ran){			//�ھڶüƲ��ʦ�m�íp�ơA�J��-1�N���s���ü� 
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
			if(i>= row * col-1){			//�̤֭n����row*col-1���~��s�b�L�C�Ӧ�m 
				for(j = 0;j < row;j++){
					for(k = 0;k < col;k++)
						if(count[j][k] == 0)	//�p�G��m�@�J��0�N���X	 
							break;
						else
							non_zero++;			//�p��D0��m���ƶq 
				}
				if(non_zero == row*col){		//�p�G�S����0����m���X�̥~��for�j�� 
					break;
				}
					
				else
					non_zero = 0;				//������m�������D0�A���s�p�� 
			}
				
		}
		FILE *fp;
		fp = fopen("D0672458_program2.txt","w");	//�ؼg�� 
		
		fprintf(fp,"\nThe total number of moves : %d\n\n", moves_count);	//��X���ʦ��� 
		for(i = 0;i < row;i++)						//�榡�ƿ�Xcount�}�C 
			for(j = 0;j < col;j++){
				fprintf(fp,"%5d ", count[i][j]);
				if(j != col-1)
					fprintf(fp,", ");
				else
					fprintf(fp,"\n");
			}
	}
	else						//��J���ѼƼƥؤ���5 
		printf("Error!");		

	return 0;
}
