#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
struct tree{
	char data;
	int inOrder_loc;				//�O���b���Ǫ���m 
	tree *left_child;
	tree *right_child;
};

tree *build_binaryTree(char *,char *);
tree *insert_node(tree *, char, int);
void print_postOrder(tree *, FILE *);

int main(){
	int size = 0;
	
	FILE *fp = fopen("Input.txt","r");	//Ū�� 
	
	fscanf(fp,"%d", &size);
	if(size <= 0 && size >= 50){
	 	puts("�`�I�Ƥj��0 & �p�󵥩�50");
	 	return 1;
	}	
	char preOrder[size] = {'\0'}, inOrder[size] = {'\0'};
	fscanf(fp,"%s	%s",preOrder,inOrder);
	
	tree *root = build_binaryTree(preOrder,inOrder);	//�إߤG���� 
	fclose(fp);
	
	FILE *fw = fopen("Output.txt","w");		//�g�� 
	print_postOrder(root, fw);		//��X�ɮ� 
	fclose(fw);
	
	return 1;
}

tree *build_binaryTree(char pre[], char in[]){
	
	tree *root = NULL;
	
	char *addr;
	int in_loc;
	int i = 0;
	
	for(i = 0;i < strlen(pre);i++){
		addr = strchr(in,pre[i]);			//�e�Ǧr��(Root)�b���Ǧr�ꤤ�����ަ�m 
		in_loc = addr - in;					//���ǰO����۹��m
		if(!root)					//�S���ڵ��I 
			root = insert_node(root,pre[i], in_loc);	//�s�W�ڷs�`�I 
		else
			insert_node(root,pre[i], in_loc);	//�s�W�s�`�I
	}
	return root;
}

tree *insert_node(tree *root, char data,int in_loc){
	
	tree *new_node, *current, *parent;
	new_node = (tree*) malloc(sizeof(tree));	//��l�� 
	new_node->data = data;
	new_node->inOrder_loc = in_loc;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	
	if(!root){
		return new_node;	//�s�`�I���ڵ��I 
	}
	else{
		current = root;		//�q�ڵ��I�}�l 
		while(current != NULL){
			parent = current;
			if(current->inOrder_loc > new_node->inOrder_loc)	//�s�`�I�����Ǧ�m�b�ثe�`�I������ 
				current = current->left_child;
			else												//��L�h�b�k�� 
				current = current->right_child;
		}
		if(parent->inOrder_loc > new_node->inOrder_loc)		//�s�`�I�����Ǧ�m�b���`�I������ 
			parent->left_child = new_node;
		else
			parent->right_child = new_node;	
	}
	return NULL;
}

void print_postOrder(tree *ptr, FILE *fw){		//��Ǩ��X 
	if(ptr){
		print_postOrder(ptr->left_child,fw);
		print_postOrder(ptr->right_child,fw);
		fprintf(fw,"%c",ptr->data);
	}
}




