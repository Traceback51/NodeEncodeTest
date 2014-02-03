#include <stdio.h>
#include <stdlib.h>

typedef struct treenode {
	char id;
	char isdata;
	struct treenode *parent;
	struct treenode *left;
	struct treenode *right;
} NODE;

void destroy_tree(NODE *node);
int add_node(NODE **node, char id, NODE *parent);
void print_tree(NODE *node, int pad);

int main() {
	NODE *root = NULL;
	int i;
	
	for(i = 0; i < 3; i++) {
		add_node(&root, i, NULL);
	}
	
	print_tree(root, 0);
	destroy_tree(root);
	
	return 0;
}

int add_node(NODE **node, char id, NODE *parent) {
	if(!(*node)) {
		*node = malloc(sizeof(NODE));
		(*node)->id = id;
		(*node)->isdata = 1;
		(*node)->parent = parent;
		(*node)->left = NULL;
		(*node)->right = NULL;
		
		if(parent && parent->isdata) {
			parent->isdata = 0;
			
			if(!parent->left) {
				add_node(&parent->left, parent->id, parent);
			}
			else {
				add_node(&parent->right, parent->id, parent);
			}
			
			parent->id = 0;
		}
		return 0;
	}
	else {
		if(id > (*node)->id) {
			return add_node(&(*node)->right, id, (*node));
		}
		else if(id < (*node)->id) {
			return add_node(&(*node)->left, id, (*node));
		}
		else {
			return 1;
		}
	}
}

void print_tree(NODE *node, int pad) {
	if(node) {
		int i;
		for(i = 0; i < pad; i++) printf("\t");
		if(node->isdata)
			printf("0x%x\n",node->id);
		else
			printf("<PAD>\n");
		
		if(node->left) {
			print_tree(node->left, pad+1);
		}
		if(node->right) {
			print_tree(node->right, pad+1);
		}
	}
}

void destroy_tree(NODE *node) {
	if(node->left != NULL) {
		destroy_tree(node->left);
	}
	
	if(node->right != NULL) {
		destroy_tree(node->right);
	}
	
	free(node);
	
	return;
}
