#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_QUEUE_SIZE 10
int global_clock = 0;
typedef struct Customer {
	char id[20]; 					// �Ȥ� id
	int arr_time;					 // �Ȥ��F�Ȧ�ɶ�
	int ser_time;						// �Ȥ᧹���~�ȭn��h�֮ɶ�
	Customer *next;
}Customer;

typedef struct TellerQueue {		// �H Linked-list ��������Circular Queue�C
	int status; 					// status, 0: close, 1:�u�ѤU�@��Ȥ�A�Y�Nclose, 2: open
	Customer *front; 						// front pointer�A���V�Ĥ@��element ��index
	Customer *rear; 						// rear pointer�A���V�̫�@��element ���U�@��index
	int count; 						// queue ���b�ƶ����H��
	int current_served_time; 		// �ثe�b�B�z�~�Ȫ��ȤH�w�g�᪺�ɶ�
}TellerQueue;

void ReadOneRecord(TellerQueue *counter[], int win_count, int openWin);	//Ū���Ĥ@��Ʀr�t�m���f 
void UpdateQueueStatus(TellerQueue *counter[],int new_arr_time);		//global_clock���N�ܷs����F�ɶ��A�ç�s�C�Ӧ�C�����A�A��X�B�z����front 
int GetTheShortestQueueId(TellerQueue *counter[]);						//�ѳ̤p�Ʀr���f�}�l�p��H�Ƴ̤֪����f 
void InsertCustomer(int closeWin,int shortest_Q,Customer *secondCustomer,TellerQueue *counter[]);				//�������f�ɡA���s�ƦCfront�᪺�ȤH��H�Ƴ̤֪����f 
void InsertNewCustomer(int shortest_Q,char new_id[],int new_arr_time,int new_ser_time,TellerQueue *counter[]);	//�s�W�ȤH��H�Ƴ̤֪����f				

int main(){
	TellerQueue *counter[MAX_QUEUE_SIZE] = {NULL};
	Customer *secondCustomer;
	char str[30] = {'\0'}, new_id[20] = {'\0'};
	int i = 0, new_arr_time = 0, new_ser_time = 0, shortest_Q = 0, total_clock = 0;
	
	scanf("%s",str);	//��J�ɮ� 
	puts("");				
	FILE *fp;					
	if(!(fp = fopen(str,"r")))
		printf("File can't be open !!'");
	else{
		while((fgets(str,30,fp)) != NULL){		//�@��Ū��30�Ӧr�� 
			if(global_clock == 0 && atoi(str) <= 10){	//Ū���Ĥ@��A���f�ƶq����j��10 
				ReadOneRecord(counter,atoi(str),0);		//�t�m���f���O����ê�l�� 
				fgets(str,30,fp);			//Ū�J�Ĥ@��3���� 
			}
			else if(global_clock == 0 && atoi(str) > 10){	
				printf("Error:���f�ƶq���o�W�L10��");
				return 1;	
			}
			
			sscanf(str,"%s %d %d",new_id, &new_arr_time, &new_ser_time);	//���O�s��str�����T���� 
			UpdateQueueStatus(counter,new_arr_time);	//��s�C�ӵ��f�����A 
		
			if(new_id[0] == '@'){					//�Ĥ@����ƬO'@'�N�}�ҵ��f 
				if(counter[new_ser_time] == NULL)
					ReadOneRecord(counter,1,new_ser_time); 	//�ĤT�ӰѼƬO�����f���X 
				else
					counter[new_ser_time] -> status = 2;
			}
			else if (new_id[0] == '#'){					//�Ĥ@����ƬO'#'�N�������f 
				if(counter[new_ser_time] != NULL && counter[new_ser_time] -> front != NULL){
					counter[new_ser_time] -> status = 1;	//�̫�@��ȤH �Anew_ser_time �O���f���X
					while(counter[new_ser_time] -> front -> next != NULL){			//front�᭱���ȤH�ݭn���s�ƹ�A�Y���ȤH���� 
						secondCustomer = counter[new_ser_time] -> front -> next;	//front�᭱���ȤH 
						shortest_Q = GetTheShortestQueueId(counter);				//�ƶ��H�Ƴ̤֪����f�A�]�O�̤p���X�� 
						InsertCustomer(new_ser_time, shortest_Q, secondCustomer, counter); //���s�ƶ��A�ç���C��count�ƶq 
					}
				}
				else if(counter[new_ser_time] != NULL && counter[new_ser_time] -> front == NULL)		//�L�ȤH 
					counter[new_ser_time] -> status = 0;
			}
			else{												//�Ĥ@����Ƭ��Ȥ�W�r 
				shortest_Q = GetTheShortestQueueId (counter);	
				InsertNewCustomer( shortest_Q, new_id , new_arr_time, new_ser_time, counter); //�s�W�Ȥ��H�Ƴ̤֥B���X�̤p�����f 
			}
		
		}
		
		int max_wait_clock = 0, queue_clock = 0;
		Customer *nextCustomer;
		for(i = 0;i < MAX_QUEUE_SIZE;i++){				//�����̫�B�J�A��X�̫�@�ӫȤH���}��global_clock�~�����X�����ȤH 
			if(counter[i] != NULL && counter[i] -> status != 0 && counter[i] -> front != NULL) {	//���f���t�m�O����~���ˬd���A�A�b�ݦ��L�B�z���ȤH 
				nextCustomer = counter[i] -> front;		
				queue_clock = (nextCustomer -> ser_time) - (counter[i] -> current_served_time);	//�ȤH���A�Ȯɶ� - �w�A�Ȯɶ� = ���A�Ȯɶ� 
				while(nextCustomer != counter[i] -> rear){			//�q�ĤG�ӫȤH��̫�@�ӫȤH�����A�Ȯɶ��ۥ[ 
					nextCustomer = nextCustomer -> next;
					queue_clock += nextCustomer -> ser_time;
				}
				if(max_wait_clock < queue_clock)			//��X�٭n�A�ȳ̤[�����f���ɶ� 
						max_wait_clock = queue_clock;
				queue_clock = 0;				//��l�ơA���F�p��U�ӵ��f�٭n�A�Ȫ��ɶ� 
			}
		}
		total_clock = global_clock + max_wait_clock;	//�ثe�ɶ� + �̫�@��ȤH���ݩM�A�Ȫ��ɶ� = �̫�@��ȤH���}���ɶ� 
		UpdateQueueStatus(counter,total_clock);			//��X��̫�@��ȤH���}���ɶ��I +1
	}
	return 1;
}

void ReadOneRecord(TellerQueue *counter[], int win_count, int openWin){
	int i = 0;
	
	if(openWin == 0){		//�Ĥ@���� = �t�m���f�ƶq 
		for(i = 0;i < win_count;i++){
			counter[i] = (TellerQueue *) malloc(sizeof(TellerQueue));
			counter[i] -> front = NULL;
			counter[i] -> rear = NULL;
			counter[i] -> count = 0;
			counter[i] -> current_served_time = 0;
			counter[i] -> status = 2;
		}
	}
	else if(counter[openWin] != NULL){	//����Ĥ@���Ʀ�'@'��ܶ}�ҵ��f�AopenWin�����f�s�� 
			counter[openWin] = (TellerQueue *) malloc(sizeof(TellerQueue));
			counter[openWin] -> front = NULL;
			counter[openWin] -> rear = NULL;
			counter[openWin] -> count = 0;
			counter[openWin] -> current_served_time = 0;
			counter[openWin] -> status = 2;	
	}
}

void UpdateQueueStatus(TellerQueue *counter[],int new_arr_time){
	int i = 0, j = 0, arr = 0, ser = 0, wait = 0;
	Customer *temp;
	
	for(;global_clock <= new_arr_time;global_clock++){ 	//global_clock�C�C+1�쵥��s����F�ɶ� �A�æb�C�Ӯɶ��I�w��C�ӵ��f���B�z 
		for(i = 0;i < MAX_QUEUE_SIZE;i++){				//�C�Ӯɶ��I���n��s�C�ӵ��f 
			if(counter[i] != NULL && counter[i] -> status != 0 && counter[i] -> front != NULL){	//���f�n���t�m�O����åB���������A�]�ܤ֭n���@��A�Ȫ��ȤH					 
				if(global_clock > counter[i] -> front -> arr_time)	//global_clock�j��Q�A�Ȥ����ȤH����F�ɶ�				
					(counter[i] -> current_served_time)++;			//�ŦX����N�O�C�Ӯɶ��I���n+1			
				arr = counter[i] -> front -> arr_time;
				ser = counter[i] -> front -> ser_time;
				
				if(global_clock > arr && counter[i] -> current_served_time == counter[i] -> front -> ser_time) // �p�ⵥ�ݮɶ��A�D�n�O�H�ثe�A�Ȯɶ��n���󶷪A�Ȯɶ��A�N��n���}�A�i�H�p�ⵥ�ݮɶ��F 				
					wait = global_clock - arr - ser;	//���}�ɶ� - ��F�ɶ� - �A�Ȯɶ� = ���ݮɶ�	
					
				if(global_clock ==  (arr + ser + wait) && counter[i] -> current_served_time == counter[i] -> front -> ser_time){	//�O�_�����A�� 
					printf("%s %d %d\n", counter[i] -> front -> id, global_clock, i);	//��X���}���ȤH 
					counter[i] -> current_served_time = 0;	//��l�ƥثe�A�Ȯɶ��A�ȤH�w���} 
					temp = counter[i] -> front;
					if(counter[i] -> status == 2 && temp -> next != NULL)	//�ŦX�A���A��2�A�S�H�N���VNULL 
						counter[i] -> front = temp -> next;
					else if(counter[i] -> status == 2 && temp -> next == NULL){
						counter[i] -> front = NULL;
						counter[i] -> rear = NULL;
					}
					else if(counter[i] -> status == 1){ //�n�������f�F 
						counter[i] -> status = 0;
						counter[i] -> front = NULL;
						counter[i] -> rear = NULL;
					}
					(counter[i] -> count)--;	//�����f���}�F�@��ȤH 
					temp -> next = NULL;
					free(temp);
				}
			}
		}
	}
	if(counter[0] -> status != 2)	//0�����f�û��O�}�� 
		counter[0] -> status = 2;
}

int GetTheShortestQueueId(TellerQueue *counter[]){
	int i = 0, min = 0;
	
	for(i = 1;i < MAX_QUEUE_SIZE;i++){	//�q�̧C���f�}�l����H�� 
		if(counter[i] != NULL && counter[i] -> status == 2){
			if(counter[min] -> count > counter[i] -> count)
				min = i;
		}
	}
	return min;
}

void InsertCustomer(int closeWin,int shortest_Q,Customer *secondCustomer,TellerQueue *counter[]){
	
	if(secondCustomer == counter[closeWin] -> rear)		//�u�Ѥ@��ȤH�ݭn���s�ƶ� 
		counter[closeWin] -> rear = counter[closeWin] -> front;
		
	counter[closeWin] -> front -> next = secondCustomer -> next;	//�Ĥ@��node��next���V�ĤT��node 	
	secondCustomer  -> next = NULL;
	(counter[closeWin] -> count)--;		//�ĤG��ȤH���s�ƶ� 


	if(counter[shortest_Q] -> count > 0)		//���A�Ȥ����ȤH 
		counter[shortest_Q] -> rear -> next = secondCustomer; //�ƶ���H�Ƴ̤֪����f 
	else										//�S���ȤH�Afront = NULL 
		counter[shortest_Q] -> front = secondCustomer;
	counter[shortest_Q] -> rear = secondCustomer;
	(counter[shortest_Q] -> count)++;	//�s�W���s�ƶ����ȤH 
}

void InsertNewCustomer(int shortest_Q,char new_id[],int new_arr_time,int new_ser_time,TellerQueue *counter[]){
	Customer *newCustomer;
	newCustomer = (Customer *) malloc(sizeof(Customer));	
	strcpy(newCustomer -> id,new_id);			//��l�ƫȤH��� 
	newCustomer -> arr_time = new_arr_time;
	newCustomer -> ser_time = new_ser_time;
	newCustomer -> next = NULL;
	
	if(counter[shortest_Q] -> count == 0){		//�Y���f���S�H�ɡA�s�W�Ĥ@��ȤH(node)�Afront�Mrear���V�P�@��node 
		counter[shortest_Q] -> front = newCustomer;
		counter[shortest_Q] -> rear = newCustomer;
	}
	else{			//���f�w�A�Ȥ��A�u�n����rear���� 
		counter[shortest_Q] -> rear -> next = newCustomer;
		counter[shortest_Q] -> rear = newCustomer;
	} 
	(counter[shortest_Q] -> count)++;	//�s�W�@��s�ȤH 
}
