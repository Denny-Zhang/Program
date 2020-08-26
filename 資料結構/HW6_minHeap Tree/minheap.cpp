#include<stdio.h>
#include<stdlib.h>

#define LCHILD(x) x*2+1							//�Ǧ^���p�į��� 
#define RCHILD(x) x*2+2							//�Ǧ^�k�p�į��� 
#define PARENT(x) (x % 2)? x/2: (x-1)/2			//�Ǧ^���`�I���� 

struct node{						//�s���ƦC��� 
	int data;
};

struct minHeap{						//�ʺA�}�C��@��n�� 
	int size;
	node *entry;
};

int accumulator(minHeap*);						//�֥[�� 
void swap(node*, node*);						//��ȥ洫 
void heapify(minHeap*, int);					//��n�� 
minHeap* buildMinHeap(minHeap*,int*, int);		//�إ߰�n�� 
minHeap* insertNode(minHeap*, int);				//���J�s�`�I 
minHeap* deleteNode(minHeap*);					//�R����ڸ`�I 
	
	
int main(int argc,char *argv[]){
	
	FILE *fp = fopen(argv[1], "r");
	int num = 0, i = 0, total = 0, *array = NULL, size = 0;
	char c = '\0';
	minHeap *heap;
	
	while((fscanf(fp,"%d",&num)) != EOF){
		c = fgetc(fp);				//�i�HŪ������ 
			
		if(size == 0){				//size = 0 ��ܷs���ƦC 
			size = num;
			array = (int *) malloc(size * sizeof(int));		//�ʺA�t�m�}�C	
		}
		else{
			array[i++] = num;		//�Ʀr�[�i�}�C 
		}	
		switch(c){
			case ' ':
				continue;
			case '\n':
				if(size == 1){
					puts("0");			//�u���@�ӼƦr�N��X0 
				}
				else{
					heap = buildMinHeap(heap,array,size);
					total = accumulator(heap);
					printf("%d\n",total);
				}
				i = 0;			//��l�� 
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
	
	while(heap->size){							//heap->size����0 
		for(i = 0;i < 2;i++){					//�i��⦸�R�����@�����J 
			cost += (heap->entry[0].data);		//�֥[�⦸ 
			heap = deleteNode(heap);
		}
		heap = insertNode(heap,cost);		
		totalCost += cost;						//�`�֥[�� 
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
	//���B�k�p�Ī����ޤ���W�X��n�d��A�åB��X�̤p���ަ�m 
	if(LCHILD(i) < heap->size && heap->entry[i].data > heap->entry[LCHILD(i)].data)		 
		min = LCHILD(i);
	if(RCHILD(i) < heap->size && heap->entry[min].data > heap->entry[RCHILD(i)].data)
		min = RCHILD(i);
		
	if(min != i){			//������N���洫 
		swap(&(heap->entry[i]),&(heap->entry[min]));
		heapify(heap,min);		//���j�P�U�����Ĥl�������S���Ĥl �� �w�g�O�̤p�ȯ��� 
	}
	
}

minHeap* buildMinHeap(minHeap *heap,int *array, int size){
	int i = 0;
	node newNode;
	heap = (minHeap *) malloc(sizeof(minHeap));		//�s��n���l�� 
	heap->entry = NULL;
	heap->size = 0;			
	
	for(i = 0;i < size;i++){			//��Ӱ}�C���[���n 
		if(heap->size)					//�O�_���� 
			heap->entry = (node *) realloc(heap->entry,(heap->size+1) * sizeof(node));
		else
			heap->entry = (node *) malloc(sizeof(node));		
	
		newNode.data = array[i];
		heap->entry[(heap->size)++] = newNode;
	}

	for(i = PARENT((heap->size-1));i >= 0;i--)		//�q�̫�@�ӫD�׺ݸ`�I�}�l���e����n�� 
		heapify(heap,i);
	return heap;
}

minHeap* insertNode(minHeap *heap, int data){
	
	if(heap->size == 0)		//���ŴN���ݭn�A�[�J�s���`�I 
		return heap;
		
	if(heap->size)			//�ʺA�t�m�s���ת��O����	
		heap->entry = (node *)realloc(heap->entry,(heap->size+1) * sizeof(node));
	
	node newNode;
	newNode.data = data;
	
	int i = (heap->size)++;			//�h�@�Ӧ�m 

	while(i && heap->entry[PARENT(i)].data > data){	//���쬰��� �� ���J����Ƥ���`�I�j 
		heap->entry[i] = heap->entry[PARENT(i)];
		i = PARENT(i);
	}
	heap->entry[i].data = data;			//���J�s��� 
	return heap;
}

minHeap* deleteNode(minHeap *heap){
	if(heap->size){
		heap->entry[0] = heap->entry[--(heap->size)];	//��̫�@�Ӹ`�I����� 
		heap->entry = (node *) realloc(heap->entry, heap->size * sizeof(node));	//�Y�p�O����t�m 
		heapify(heap,0);		//���ڰ���n�� 
	}
	return heap;
}











