#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define len 5

struct Gate{	//�s���޿�`��T 
	char gateName[len];
	int in_count;
	int delay;
};

struct index{	//�F�����I���� 
	int x;
	index *next;
};

struct Vertex{		//���I��T 
    char vex[len];
	int earliest;	//�̦��ɶ� 
	int latest;		//�̱߮ɶ� 
	int in_delay;	//inDegree���ɶ� 
	index *rear;	//�̫�@�ӾF�����I 
    index *outDegree;	//�F�����I�C 
	Vertex(){
		strcpy(vex,"");
		earliest = 0;
		latest = -1;
		in_delay = 0;
		rear = NULL;
		outDegree = NULL;
	}
};
													//var_count:�}�C�ثe���I�ƶq 
void buildGraph(FILE *fp,Vertex graph[],Gate gates[],int var_count,int gate_count){
	char outVar[len],gName[len],inVar[len];
	int i = 0,j = 0,k = 0,in_count = 0,delay = 0;	
	index *adj;				
	
	char g[gate_count][len];		//�]�������ε��c��gateName	strcmp�|�����NULL 
	for(i = 0;i < gate_count;i++)	//�D�n�O�٨S���t���O����N��� 
		strcpy(g[i],gates[i].gateName);	//�ҥH�ϥΤ@�}�C���s�N���ΦA�]�쵲�c�̧���F 
		
	while(fscanf(fp,"%s %s",outVar,gName) != EOF){
		for(i = 0;strcmp(gName,g[i]) != 0;i++);		//��Xgates�r���諸���� 
						
		in_count = gates[i].in_count;
		delay = gates[i].delay;
		
		for(i = 0;i < var_count;i++)		
			if(strcmp(graph[i].vex,outVar) == 0)	// i ��outVar�b�}�C������ 
				break;		
			
		if(strcmp(graph[i].vex,outVar) != 0){		//��outVar���ެO�_�b�}�C 
			strcpy(graph[var_count++].vex,outVar);	//���b���ܡA�s�W�s���I 
			i = var_count-1;
		} 
		graph[i].in_delay = delay;		//��J�䪺delay 
		
		for(j = 0;j < in_count;j++){
			fscanf(fp,"%s",inVar);
			for(k = 0;k < var_count;k++){		//�q�}�C�M��input���I 
				if(strcmp(inVar,graph[k].vex) == 0){	//���}�C���ަ�m 
					adj = (index*) malloc(sizeof(index));	//�s�W�F�����I�O���� 
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
				else if(k == var_count-1)	//input�S���[�i�Ϥ� 
					strcpy(graph[var_count++].vex,inVar);	//�[�i�Ϥ��A���I��+1 
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
	
	for(i = 0;i < graph_size;i++){			//�q���I�}�l���_�I��slatest 
		temp = graph[i].outDegree;
		while(temp){					//���C�ӾF�����I�M��X������ 
			if(temp->x == stackIndex){	//�O�_�s�b���F����X���� 
				latest = graph[stackIndex].latest;
				in_delay = graph[stackIndex].in_delay;
				if(graph[i].latest > latest - in_delay)		//latest�����p�� 
					graph[i].latest = latest - in_delay;	//�̱߳o�Ӯɶ��n��F 
				
				if(graph[i].earliest != 0)		//earliest = 0 = �_�Iinput
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
	
	if(latest != earliest)		//�̱ߩM�̦��ɶ��۵��~�OcriticalPath��vertex 
		return ;
	rear = (index*)malloc(sizeof(index));	//�ͦ����| 
	rear->x = in_index;
	rear->next = NULL;
		
	if(!path){
		path = rear;
		top = path;
	}	
	else
		top->next = rear;
	
	while(temp){			//���X�F�����I 
		adjIndex = temp->x;
		adjLatest = graph[adjIndex].latest;
		adjEarliest = graph[adjIndex].earliest;
		delay = graph[adjIndex].in_delay;
		//latest = earliest : ��������|�����I
		//latest - delay = �e�@���Ilatest : �O���I�������|�O�_��������| 
		if(adjLatest == adjEarliest && adjLatest - delay == latest)	
			criticalPath(graph,graph_size,in_size,adjIndex,max_delay,path,rear,fp);
		temp = temp->next;
	}
	if(latest == max_delay && earliest == max_delay){	//���X��X 
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

	 //Ū�� gate	��J�Ӽ�	delay 
	while(fscanf(fp,"%s %d %d",gates[i].gateName,&gates[i].in_count,&gates[i].delay) != EOF)
		i++;
		
	fclose(fp);
	
	fp = fopen("Circuit.txt","r");
	int count[3] = {'\0'};							// 0  in , 1  out , 2 gate 
	fscanf(fp,"%d %d %d",&count[0],&count[1],&count[2]);
	int in_out_size = count[0]+count[1], graph_size = 0;
	graph_size = count[0]+count[2];
	
	Vertex graph[graph_size];	//��Jvar + ��Xvar = var�`�� 
	int j = 0,max_delay = 0;
	char str[len];
	for(i = 0;i < in_out_size;i++){	//Ū����J�M��X�r��	 
		fscanf(fp,"%s",str);
		for(j = 0;j < i;j++)
			if(strcmp(graph[j].vex,str) == 0){
				in_out_size--;
				break;
			}
		if(i == j)
			strcpy(graph[i].vex,str);
	}

	buildGraph(fp,graph,gates,in_out_size,gate_count);	//�إ߾F���� 
	
	earlistTime(graph,graph_size);	//�p��̦��ɶ� 
	
	
	for(i = count[0];i < in_out_size;i++)
		if(max_delay < graph[i].earliest)		//����X���I���̤jdelay 
			max_delay = graph[i].earliest;
	
	for(i = 0;i < graph_size;i++)		//��l��latest 
		graph[i].latest = max_delay;
	

	for(i = count[0];i < in_out_size;i++)			//���X���ޤ@�ӭӶǤJ 
		latestTime(graph,graph_size,i);
	
	fclose(fp);
	fp = fopen("Output.txt","w");
	
	fprintf(fp,"%d\n",max_delay);	
	index *path = NULL,*top = NULL;
	for(i = 0;i < count[0];i++)		//�ǤJ�Ҧ���J������ 
		criticalPath(graph,graph_size,count[0],i,max_delay,path,top,fp);
	
	free(path);
	fclose(fp);
	return 0;
}






