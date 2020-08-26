#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define len 5

struct Gate{	//存取邏輯匝資訊 
	char gateName[len];
	int in_count;
	int delay;
};

struct index{	//鄰接頂點索引 
	int x;
	index *next;
};

struct Vertex{		//頂點資訊 
    char vex[len];
	int earliest;	//最早時間 
	int latest;		//最晚時間 
	int in_delay;	//inDegree的時間 
	index *rear;	//最後一個鄰接頂點 
    index *outDegree;	//鄰接頂點列 
	Vertex(){
		strcpy(vex,"");
		earliest = 0;
		latest = -1;
		in_delay = 0;
		rear = NULL;
		outDegree = NULL;
	}
};
													//var_count:陣列目前頂點數量 
void buildGraph(FILE *fp,Vertex graph[],Gate gates[],int var_count,int gate_count){
	char outVar[len],gName[len],inVar[len];
	int i = 0,j = 0,k = 0,in_count = 0,delay = 0;	
	index *adj;				
	
	char g[gate_count][len];		//因為直接用結構的gateName	strcmp會抓取到NULL 
	for(i = 0;i < gate_count;i++)	//主要是還沒分配完記憶體就抓取 
		strcpy(g[i],gates[i].gateName);	//所以使用一陣列先存就不用再跑到結構裡抓取了 
		
	while(fscanf(fp,"%s %s",outVar,gName) != EOF){
		for(i = 0;strcmp(gName,g[i]) != 0;i++);		//抓出gates字串比對的索引 
						
		in_count = gates[i].in_count;
		delay = gates[i].delay;
		
		for(i = 0;i < var_count;i++)		
			if(strcmp(graph[i].vex,outVar) == 0)	// i 為outVar在陣列的索引 
				break;		
			
		if(strcmp(graph[i].vex,outVar) != 0){		//此outVar索引是否在陣列 
			strcpy(graph[var_count++].vex,outVar);	//不在的話，新增新頂點 
			i = var_count-1;
		} 
		graph[i].in_delay = delay;		//輸入邊的delay 
		
		for(j = 0;j < in_count;j++){
			fscanf(fp,"%s",inVar);
			for(k = 0;k < var_count;k++){		//從陣列尋找input頂點 
				if(strcmp(inVar,graph[k].vex) == 0){	//找到陣列索引位置 
					adj = (index*) malloc(sizeof(index));	//新增鄰接頂點記憶體 
					adj->x = i;
					adj->next = NULL;
					if(!graph[k].outDegree){
						graph[k].outDegree = adj;
						graph[k].rear = adj;
					}
					else{
						graph[k].rear->next = adj;
						graph[k].rear = adj;
					}
					break;
				}
				else if(k == var_count-1)	//input沒有加進圖中 
					strcpy(graph[var_count++].vex,inVar);	//加進圖中，頂點數+1 
			}
		}
	}
	/* 
	index *op;
	for(i = 0;i < var_count;i++){ 
		printf("%d %s %d",i,graph[i].vex,var_count);
		if(graph[i].outDegree)	
			op = graph[i].outDegree;
		
		while(op){				
			printf(" %d",op->x);
			op = op->next;
		}
		puts("");
	} 
	*/ 
}

void earlistTime(Vertex *graph, int graph_size){
	int i = 0, adjVex = 0,edge_delay = 0,vex_ear = 0;
	index *temp;
	
	for(i = 0;i < graph_size;i++){
		temp = graph[i].outDegree;
		vex_ear = graph[i].earliest;
		while(temp){
			adjVex = temp->x;
			edge_delay = graph[adjVex].in_delay;
			if(graph[adjVex].earliest < vex_ear + edge_delay)
				graph[adjVex].earliest = vex_ear + edge_delay;
			temp = temp->next;
		}
	}
	
}

void latestTime(Vertex *graph,int graph_size,int stackIndex){
	int i = 0, latest = 0,in_delay = 0;
	index *temp;
	
	for(i = 0;i < graph_size;i++){			//從終點開始往起點更新latest 
		temp = graph[i].outDegree;
		while(temp){					//比對每個鄰接頂點和輸出的索引 
			if(temp->x == stackIndex){	//是否存在此鄰接輸出索引 
				latest = graph[stackIndex].latest;
				in_delay = graph[stackIndex].in_delay;
				if(graph[i].latest > latest - in_delay)		//latest取較小值 
					graph[i].latest = latest - in_delay;	//最晚這個時間要抵達 
				
				if(graph[i].earliest != 0)		//earliest = 0 = 起點input
					latestTime(graph,graph_size,i);
			}
			temp = temp->next;	
		}
	}
}

void criticalPath(Vertex *graph,int graph_size,int in_size,int in_index,int max_delay,index *path,index *top,FILE *fp){
	int latest = graph[in_index].latest,earliest = graph[in_index].earliest;
	index *temp = graph[in_index].outDegree, *rear = NULL,*pre = NULL;
	int adjIndex = 0,adjLatest = 0,adjEarliest = 0,delay = 0;
	
	if(latest != earliest)		//最晚和最早時間相等才是criticalPath的vertex 
		return ;
	rear = (index*)malloc(sizeof(index));	//生成路徑 
	rear->x = in_index;
	rear->next = NULL;
		
	if(!path){
		path = rear;
		top = path;
	}	
	else
		top->next = rear;
	
	while(temp){			//走訪鄰接頂點 
		adjIndex = temp->x;
		adjLatest = graph[adjIndex].latest;
		adjEarliest = graph[adjIndex].earliest;
		delay = graph[adjIndex].in_delay;
		//latest = earliest : 為關鍵路徑的頂點
		//latest - delay = 前一個點latest : 是頂點間的路徑是否為關鍵路徑 
		if(adjLatest == adjEarliest && adjLatest - delay == latest)	
			criticalPath(graph,graph_size,in_size,adjIndex,max_delay,path,rear,fp);
		temp = temp->next;
	}
	if(latest == max_delay && earliest == max_delay){	//走訪輸出 
		pre = path;
		while(pre->next != NULL){
			fprintf(fp,"%s ",graph[pre->x].vex);
			pre = pre->next;
		}
		fprintf(fp,"%s\n",graph[pre->x].vex);
	}
	top->next = NULL;
	free(rear);
}

int main(){
	FILE *fp = fopen("Gates.txt","r");
	int gate_count = 0, i = 0;
	fscanf(fp,"%d",&gate_count);		
	Gate gates[gate_count];

	 //讀取 gate	輸入個數	delay 
	while(fscanf(fp,"%s %d %d",gates[i].gateName,&gates[i].in_count,&gates[i].delay) != EOF)
		i++;
		
	fclose(fp);
	
	fp = fopen("Circuit.txt","r");
	int count[3] = {'\0'};							// 0  in , 1  out , 2 gate 
	fscanf(fp,"%d %d %d",&count[0],&count[1],&count[2]);
	int in_out_size = count[0]+count[1], graph_size = 0;
	graph_size = count[0]+count[2];
	
	Vertex graph[graph_size];	//輸入var + 輸出var = var總數 
	int j = 0,max_delay = 0;
	char str[len];
	for(i = 0;i < in_out_size;i++){	//讀取輸入和輸出字串	 
		fscanf(fp,"%s",str);
		for(j = 0;j < i;j++)
			if(strcmp(graph[j].vex,str) == 0){
				in_out_size--;
				break;
			}
		if(i == j)
			strcpy(graph[i].vex,str);
	}

	buildGraph(fp,graph,gates,in_out_size,gate_count);	//建立鄰接圖 
	
	earlistTime(graph,graph_size);	//計算最早時間 
	
	
	for(i = count[0];i < in_out_size;i++)
		if(max_delay < graph[i].earliest)		//取輸出頂點的最大delay 
			max_delay = graph[i].earliest;
	
	for(i = 0;i < graph_size;i++)		//初始化latest 
		graph[i].latest = max_delay;
	

	for(i = count[0];i < in_out_size;i++)			//把輸出索引一個個傳入 
		latestTime(graph,graph_size,i);
	
	fclose(fp);
	fp = fopen("Output.txt","w");
	
	fprintf(fp,"%d\n",max_delay);	
	index *path = NULL,*top = NULL;
	for(i = 0;i < count[0];i++)		//傳入所有輸入的索引 
		criticalPath(graph,graph_size,count[0],i,max_delay,path,top,fp);
	
	free(path);
	fclose(fp);
	return 0;
}






