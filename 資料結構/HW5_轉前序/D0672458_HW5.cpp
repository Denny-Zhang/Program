#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
struct tree{
	char data;
	int inOrder_loc;				//記錄在中序的位置 
	tree *left_child;
	tree *right_child;
};

tree *build_binaryTree(char *,char *);
tree *insert_node(tree *, char, int);
void print_preOrder(tree *, FILE *);

int main(){
	int size = 0;
	
	FILE *fp = fopen("Input.txt","r");	//讀檔 
	if(!fp)
		printf("File can not be opened!");
	fscanf(fp,"%d", &size);
	if(size <= 0 && size >= 50){
	 	puts("節點數大於0 & 小於等於50");
	 	return 1;
	}	
	char postOrder[size] = {'\0'}, inOrder[size] = {'\0'};
	fscanf(fp,"%s	%s",postOrder,inOrder);
	
	tree *root = build_binaryTree(postOrder,inOrder);	//建立二元樹 
	fclose(fp);
	
	FILE *fw = fopen("Output.txt","w");		//寫檔 
	
	print_preOrder(root, fw);		//輸出檔案 
	fclose(fw);
	system("pause");
	return 1;
}

tree *build_binaryTree(char post[], char in[]){
	
	tree *root = NULL;
	
	char *addr;
	int in_loc;
	int i = 0;
	
	for(i = strlen(post)-1;i >= 0;i--){
		addr = strchr(in,post[i]);			//後序字元(Root)在中序字串中的索引位置 
		in_loc = addr - in;					//中序記憶體相對位置
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

void print_preOrder(tree *ptr, FILE *fw){		//前序走訪 
	if(ptr){
		fprintf(fw,"%c",ptr->data);
		print_preOrder(ptr->left_child,fw);
		print_preOrder(ptr->right_child,fw);
	}
}
