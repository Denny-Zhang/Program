#include<stdio.h>
#include<stdlib.h>

#define LCHILD(x) x*2+1							//傳回左小孩索引 
#define RCHILD(x) x*2+2							//傳回右小孩索引 
#define PARENT(x) (x % 2)? x/2: (x-1)/2			//傳回父節點索引 

struct node{						//存取數列資料 
	int data;
};

struct minHeap{						//動態陣列實作堆積樹 
	int size;
	node *entry;
};

int accumulator(minHeap*);						//累加器 
void swap(node*, node*);						//兩值交換 
void heapify(minHeap*, int);					//堆積化 
minHeap* buildMinHeap(minHeap*,int*, int);		//建立堆積樹 
minHeap* insertNode(minHeap*, int);				//插入新節點 
minHeap* deleteNode(minHeap*);					//刪除樹根節點 
	
	
int main(int argc,char *argv[]){
	
	FILE *fp = fopen(argv[1], "r");
	int num = 0, i = 0, total = 0, *array = NULL, size = 0;
	char c = '\0';
	minHeap *heap;
	
	while((fscanf(fp,"%d",&num)) != EOF){
		c = fgetc(fp);				//可以讀取換行 
			
		if(size == 0){				//size = 0 表示新的數列 
			size = num;
			array = (int *) malloc(size * sizeof(int));		//動態配置陣列	
		}
		else{
			array[i++] = num;		//數字加進陣列 
		}	
		switch(c){
			case ' ':
				continue;
			case '\n':
				if(size == 1){
					puts("0");			//只有一個數字就輸出0 
				}
				else{
					heap = buildMinHeap(heap,array,size);
					total = accumulator(heap);
					printf("%d\n",total);
				}
				i = 0;			//初始化 
				size = 0;
				total = 0;
				break;
		}
	}
	free(array);
	fclose(fp);
	system("pause");
	return 0;
} 	

int accumulator(minHeap *heap){
	int i = 0, cost = 0, totalCost = 0;
	
	while(heap->size){							//heap->size不為0 
		for(i = 0;i < 2;i++){					//進行兩次刪除做一次插入 
			cost += (heap->entry[0].data);		//累加兩次 
			heap = deleteNode(heap);
		}
		heap = insertNode(heap,cost);		
		totalCost += cost;						//總累加數 
		cost = 0;
	}
	return totalCost;
}

void swap(node *a, node *b){
	node temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(minHeap *heap, int i){
	int min = i;
	//左、右小孩的索引不能超出堆積範圍，並且選出最小索引位置 
	if(LCHILD(i) < heap->size && heap->entry[i].data > heap->entry[LCHILD(i)].data)		 
		min = LCHILD(i);
	if(RCHILD(i) < heap->size && heap->entry[min].data > heap->entry[RCHILD(i)].data)
		min = RCHILD(i);
		
	if(min != i){			//不等於代表有交換 
		swap(&(heap->entry[i]),&(heap->entry[min]));
		heapify(heap,min);		//遞迴與下面的孩子比較直到沒有孩子 或 已經是最小值索引 
	}
	
}

minHeap* buildMinHeap(minHeap *heap,int *array, int size){
	int i = 0;
	node newNode;
	heap = (minHeap *) malloc(sizeof(minHeap));		//新堆積樹初始化 
	heap->entry = NULL;
	heap->size = 0;			
	
	for(i = 0;i < size;i++){			//整個陣列都加到堆積 
		if(heap->size)					//是否為空 
			heap->entry = (node *) realloc(heap->entry,(heap->size+1) * sizeof(node));
		else
			heap->entry = (node *) malloc(sizeof(node));		
	
		newNode.data = array[i];
		heap->entry[(heap->size)++] = newNode;
	}

	for(i = PARENT((heap->size-1));i >= 0;i--)		//從最後一個非終端節點開始往前做堆積化 
		heapify(heap,i);
	return heap;
}

minHeap* insertNode(minHeap *heap, int data){
	
	if(heap->size == 0)		//為空就不需要再加入新的節點 
		return heap;
		
	if(heap->size)			//動態配置新長度的記憶體	
		heap->entry = (node *)realloc(heap->entry,(heap->size+1) * sizeof(node));
	
	node newNode;
	newNode.data = data;
	
	int i = (heap->size)++;			//多一個位置 

	while(i && heap->entry[PARENT(i)].data > data){	//直到為樹根 或 插入的資料比父節點大 
		heap->entry[i] = heap->entry[PARENT(i)];
		i = PARENT(i);
	}
	heap->entry[i].data = data;			//插入新資料 
	return heap;
}

minHeap* deleteNode(minHeap *heap){
	if(heap->size){
		heap->entry[0] = heap->entry[--(heap->size)];	//把最後一個節點放到樹根 
		heap->entry = (node *) realloc(heap->entry, heap->size * sizeof(node));	//縮小記憶體配置 
		heapify(heap,0);		//對樹根做堆積化 
	}
	return heap;
}











