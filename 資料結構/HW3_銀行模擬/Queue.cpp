#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_QUEUE_SIZE 10
int global_clock = 0;
typedef struct Customer {
	char id[20]; 					// 客戶 id
	int arr_time;					 // 客戶到達銀行時間
	int ser_time;						// 客戶完成業務要花多少時間
	Customer *next;
}Customer;

typedef struct TellerQueue {		// 以 Linked-list 型式模擬Circular Queue。
	int status; 					// status, 0: close, 1:只剩下一位客戶，即將close, 2: open
	Customer *front; 						// front pointer，指向第一個element 的index
	Customer *rear; 						// rear pointer，指向最後一個element 的下一個index
	int count; 						// queue 中在排隊的人數
	int current_served_time; 		// 目前在處理業務的客人已經花的時間
}TellerQueue;

void ReadOneRecord(TellerQueue *counter[], int win_count, int openWin);	//讀取第一行數字配置窗口 
void UpdateQueueStatus(TellerQueue *counter[],int new_arr_time);		//global_clock迭代至新的抵達時間，並更新每個佇列的狀態，輸出處理完的front 
int GetTheShortestQueueId(TellerQueue *counter[]);						//由最小數字窗口開始計算人數最少的窗口 
void InsertCustomer(int closeWin,int shortest_Q,Customer *secondCustomer,TellerQueue *counter[]);				//關閉窗口時，重新排列front後的客人到人數最少的窗口 
void InsertNewCustomer(int shortest_Q,char new_id[],int new_arr_time,int new_ser_time,TellerQueue *counter[]);	//新增客人到人數最少的窗口				

int main(){
	TellerQueue *counter[MAX_QUEUE_SIZE] = {NULL};
	Customer *secondCustomer;
	char str[30] = {'\0'}, new_id[20] = {'\0'};
	int i = 0, new_arr_time = 0, new_ser_time = 0, shortest_Q = 0, total_clock = 0;
	
	scanf("%s",str);	//輸入檔案 
	puts("");				
	FILE *fp;					
	if(!(fp = fopen(str,"r")))
		printf("File can't be open !!'");
	else{
		while((fgets(str,30,fp)) != NULL){		//一行讀取30個字元 
			if(global_clock == 0 && atoi(str) <= 10){	//讀取第一行，窗口數量不能大於10 
				ReadOneRecord(counter,atoi(str),0);		//配置窗口的記憶體並初始化 
				fgets(str,30,fp);			//讀入第一筆3欄資料 
			}
			else if(global_clock == 0 && atoi(str) > 10){	
				printf("Error:窗口數量不得超過10個");
				return 1;	
			}
			
			sscanf(str,"%s %d %d",new_id, &new_arr_time, &new_ser_time);	//分別存取str中的三欄資料 
			UpdateQueueStatus(counter,new_arr_time);	//更新每個窗口的狀態 
		
			if(new_id[0] == '@'){					//第一筆資料是'@'就開啟窗口 
				if(counter[new_ser_time] == NULL)
					ReadOneRecord(counter,1,new_ser_time); 	//第三個參數是當成窗口號碼 
				else
					counter[new_ser_time] -> status = 2;
			}
			else if (new_id[0] == '#'){					//第一筆資料是'#'就關閉窗口 
				if(counter[new_ser_time] != NULL && counter[new_ser_time] -> front != NULL){
					counter[new_ser_time] -> status = 1;	//最後一位客人 ，new_ser_time 是窗口號碼
					while(counter[new_ser_time] -> front -> next != NULL){			//front後面的客人需要重新排對，若有客人的話 
						secondCustomer = counter[new_ser_time] -> front -> next;	//front後面的客人 
						shortest_Q = GetTheShortestQueueId(counter);				//排隊人數最少的窗口，也是最小號碼的 
						InsertCustomer(new_ser_time, shortest_Q, secondCustomer, counter); //重新排隊，並更改佇列的count數量 
					}
				}
				else if(counter[new_ser_time] != NULL && counter[new_ser_time] -> front == NULL)		//無客人 
					counter[new_ser_time] -> status = 0;
			}
			else{												//第一筆資料為客戶名字 
				shortest_Q = GetTheShortestQueueId (counter);	
				InsertNewCustomer( shortest_Q, new_id , new_arr_time, new_ser_time, counter); //新增客戶到人數最少且號碼最小的窗口 
			}
		
		}
		
		int max_wait_clock = 0, queue_clock = 0;
		Customer *nextCustomer;
		for(i = 0;i < MAX_QUEUE_SIZE;i++){				//此為最後步驟，找出最後一個客人離開的global_clock才能夠輸出全部客人 
			if(counter[i] != NULL && counter[i] -> status != 0 && counter[i] -> front != NULL) {	//窗口有配置記憶體才能檢查狀態，在看有無處理的客人 
				nextCustomer = counter[i] -> front;		
				queue_clock = (nextCustomer -> ser_time) - (counter[i] -> current_served_time);	//客人須服務時間 - 已服務時間 = 未服務時間 
				while(nextCustomer != counter[i] -> rear){			//從第二個客人到最後一個客人的須服務時間相加 
					nextCustomer = nextCustomer -> next;
					queue_clock += nextCustomer -> ser_time;
				}
				if(max_wait_clock < queue_clock)			//找出還要服務最久的窗口的時間 
						max_wait_clock = queue_clock;
				queue_clock = 0;				//初始化，為了計算下個窗口還要服務的時間 
			}
		}
		total_clock = global_clock + max_wait_clock;	//目前時間 + 最後一位客人等待和服務的時間 = 最後一位客人離開的時間 
		UpdateQueueStatus(counter,total_clock);			//輸出到最後一位客人離開的時間點 +1
	}
	return 1;
}

void ReadOneRecord(TellerQueue *counter[], int win_count, int openWin){
	int i = 0;
	
	if(openWin == 0){		//第一行資料 = 配置窗口數量 
		for(i = 0;i < win_count;i++){
			counter[i] = (TellerQueue *) malloc(sizeof(TellerQueue));
			counter[i] -> front = NULL;
			counter[i] -> rear = NULL;
			counter[i] -> count = 0;
			counter[i] -> current_served_time = 0;
			counter[i] -> status = 2;
		}
	}
	else if(counter[openWin] != NULL){	//之後第一欄資料有'@'表示開啟窗口，openWin為窗口編號 
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
	
	for(;global_clock <= new_arr_time;global_clock++){ 	//global_clock慢慢+1到等於新的抵達時間 ，並在每個時間點針對每個窗口做處理 
		for(i = 0;i < MAX_QUEUE_SIZE;i++){				//每個時間點都要更新每個窗口 
			if(counter[i] != NULL && counter[i] -> status != 0 && counter[i] -> front != NULL){	//窗口要有配置記憶體並且不能關閉，也至少要有一位服務的客人					 
				if(global_clock > counter[i] -> front -> arr_time)	//global_clock大於被服務中的客人的抵達時間				
					(counter[i] -> current_served_time)++;			//符合條件就是每個時間點都要+1			
				arr = counter[i] -> front -> arr_time;
				ser = counter[i] -> front -> ser_time;
				
				if(global_clock > arr && counter[i] -> current_served_time == counter[i] -> front -> ser_time) // 計算等待時間，主要是以目前服務時間要等於須服務時間，代表要離開，可以計算等待時間了 				
					wait = global_clock - arr - ser;	//離開時間 - 抵達時間 - 服務時間 = 等待時間	
					
				if(global_clock ==  (arr + ser + wait) && counter[i] -> current_served_time == counter[i] -> front -> ser_time){	//是否完成服務 
					printf("%s %d %d\n", counter[i] -> front -> id, global_clock, i);	//輸出離開的客人 
					counter[i] -> current_served_time = 0;	//初始化目前服務時間，客人已離開 
					temp = counter[i] -> front;
					if(counter[i] -> status == 2 && temp -> next != NULL)	//符合，狀態為2，沒人就指向NULL 
						counter[i] -> front = temp -> next;
					else if(counter[i] -> status == 2 && temp -> next == NULL){
						counter[i] -> front = NULL;
						counter[i] -> rear = NULL;
					}
					else if(counter[i] -> status == 1){ //要關閉窗口了 
						counter[i] -> status = 0;
						counter[i] -> front = NULL;
						counter[i] -> rear = NULL;
					}
					(counter[i] -> count)--;	//此窗口離開了一位客人 
					temp -> next = NULL;
					free(temp);
				}
			}
		}
	}
	if(counter[0] -> status != 2)	//0號窗口永遠是開著 
		counter[0] -> status = 2;
}

int GetTheShortestQueueId(TellerQueue *counter[]){
	int i = 0, min = 0;
	
	for(i = 1;i < MAX_QUEUE_SIZE;i++){	//從最低窗口開始比較人數 
		if(counter[i] != NULL && counter[i] -> status == 2){
			if(counter[min] -> count > counter[i] -> count)
				min = i;
		}
	}
	return min;
}

void InsertCustomer(int closeWin,int shortest_Q,Customer *secondCustomer,TellerQueue *counter[]){
	
	if(secondCustomer == counter[closeWin] -> rear)		//只剩一位客人需要重新排隊 
		counter[closeWin] -> rear = counter[closeWin] -> front;
		
	counter[closeWin] -> front -> next = secondCustomer -> next;	//第一個node的next指向第三個node 	
	secondCustomer  -> next = NULL;
	(counter[closeWin] -> count)--;		//第二位客人重新排隊 


	if(counter[shortest_Q] -> count > 0)		//有服務中的客人 
		counter[shortest_Q] -> rear -> next = secondCustomer; //排隊到人數最少的窗口 
	else										//沒有客人，front = NULL 
		counter[shortest_Q] -> front = secondCustomer;
	counter[shortest_Q] -> rear = secondCustomer;
	(counter[shortest_Q] -> count)++;	//新增重新排隊的客人 
}

void InsertNewCustomer(int shortest_Q,char new_id[],int new_arr_time,int new_ser_time,TellerQueue *counter[]){
	Customer *newCustomer;
	newCustomer = (Customer *) malloc(sizeof(Customer));	
	strcpy(newCustomer -> id,new_id);			//初始化客人資料 
	newCustomer -> arr_time = new_arr_time;
	newCustomer -> ser_time = new_ser_time;
	newCustomer -> next = NULL;
	
	if(counter[shortest_Q] -> count == 0){		//若窗口都沒人時，新增第一位客人(node)，front和rear指向同一個node 
		counter[shortest_Q] -> front = newCustomer;
		counter[shortest_Q] -> rear = newCustomer;
	}
	else{			//窗口已服務中，只要改變rear指標 
		counter[shortest_Q] -> rear -> next = newCustomer;
		counter[shortest_Q] -> rear = newCustomer;
	} 
	(counter[shortest_Q] -> count)++;	//新增一位新客人 
}
