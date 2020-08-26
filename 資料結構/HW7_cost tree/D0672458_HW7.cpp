#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
struct tree{
	int data;
	int inOrder_loc;				//記錄在中序的位置 
	tree *left_child;
	tree *right_child;
};

int* allocMem(int *,int ,int* );			//可變動陣列長度 
tree *build_binaryTree(int *,int *,int);
tree *insert_node(tree *, char, int);
void skew(tree *, int *, int*);

int main(){
	int *size, delay = 0,i = 0, a = 0;	
	int *postOrder, *inOrder;
	
	FILE *fp = fopen("Input.txt","r");
	
	size = &a;
	while(fscanf(fp,"%d",&delay) != EOF){
		inOrder = allocMem(inOrder,delay,size);
	
		if(fgetc(fp) == '\n'){
			a = 0;
			while(fscanf(fp,"%d",&delay) != EOF){
				postOrder = allocMem(postOrder,delay,size);
				if(fgetc(fp) == '\n')
					break;
			}
			break;
		}
	}
	tree *root = build_binaryTree(postOrder,inOrder, a);	//建立二元樹 
	tree *path = root;
	int *longest = NULL, *shortest = NULL;
	longest = (int*)malloc(sizeof(int));
	shortest = (int*)malloc(sizeof(int));
	*longest = 0;
	*shortest = 0;
	while(path!=NULL){
		*longest = *longest + path->data;
		*shortest = *shortest + path->data;
		path = path->left_child;
	}
	skew(root,longest,shortest);
	printf("Delayed time (longest path) = %d\n",*longest);
	printf("Delayed time (shortest path) = %d\n",*shortest);
	fclose(fp);
	system("pause");
	return 1;
}

int* allocMem(int *arr,int delay,int* size){
	
	if(!(*size))
		arr = (int *) malloc(sizeof(int));
	else
		arr = (int *) realloc(arr,((*size)+1) * sizeof(int));
	arr[(*size)] = delay;
	(*size)++;
	return arr;
}

tree *build_binaryTree(int* post, int* in,int size){
	
	tree *root = NULL;
	
	char *addr;
	int in_loc;
	int i = 0, j = 0;
	
	for(i = size-1;i >= 0;i--){
		for(j = 0;j < size;j++)
			if(post[i] == in[j]){
				in_loc = j;					//中序記憶體相對位置
				break;
			}
		if(!root)					//沒有根結點 
			root = insert_node(root,post[i], in_loc);	//新增根新節點 
		else
			insert_node(root,post[i], in_loc);	//新增新節點
	}
	return root;
}

tree *insert_node(tree *root, char data,int in_loc){
	
	tree *new_node, *current, *parent;
	new_node = (tree*) malloc(sizeof(tree));	//初始化 
	new_node->data = data;
	new_node->inOrder_loc = in_loc;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	
	if(!root){
		return new_node;	//新節點為根結點 
	}
	else{
		current = root;		//從根結點開始 
		while(current != NULL){
			parent = current;
			if(current->inOrder_loc > new_node->inOrder_loc)	//新節點的中序位置在目前節點的左邊 
				current = current->left_child;
			else												//其他則在右邊 
				current = current->right_child;
		}
		if(parent->inOrder_loc > new_node->inOrder_loc)		//新節點的中序位置在父節點的左邊 
			parent->left_child = new_node;
		else
			parent->right_child = new_node;	
	}
	return NULL;
}

void skew(tree *root, int *longest, int *shortest){
	static int accumulative_delay = 0;
	accumulative_delay += root->data;
	
	if(root->left_child == NULL && root->right_child == NULL){
		if(*longest < accumulative_delay)
			*longest = accumulative_delay;
		if(*shortest > accumulative_delay)
			*shortest = accumulative_delay;
//	結束
	}
	else{
		if(root->left_child != NULL){
			skew(root->left_child,longest,shortest);
			accumulative_delay -= root->left_child->data;
		}
		if(root->right_child != NULL){
			skew(root->right_child,longest,shortest);
			accumulative_delay -= root->right_child->data;
		}
	//	遞迴 
	}
	
}






