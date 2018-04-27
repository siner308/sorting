// include
#include <stdio.h>
#include <malloc.h>

// define
#define BUF_MAX 1000
#define CREATE_NEW_NODE (node*)malloc(sizeof(node))

// typedef
typedef struct Node node;
struct Node{
	int key;
	node *Parent;
	node *Left;
	node *Right;
};

// function
node *findOnePiece(node*);
node *addNode(node*, node*, int);
node *deleteNode(node*, node*);
node *sortNode(node*);
void printAll(node*);
void freeAll(node*);

// main function
int main(void){
	// init
	node *root = 0;
	node *temp = 0;
	int key = 0;
	int nMenu = 0;
	int nHeight = 1;

	while (nMenu != 4){
		printf("1.Add 2.Delete 3.Print 4.Exit : ");
		scanf("%d", &nMenu);

		switch (nMenu){

		case 1: // Add
			printf("enter value : ");
			scanf("%d", &key);

			// init root
			if (!root){
				root = CREATE_NEW_NODE;

				root->key = key;
				root->Parent = NULL;
				root->Left = NULL;
				root->Right = NULL;
			}

			// add node
			else{
				temp = findOnePiece(root);
				root = addNode(root, temp, key);
			}

			break;

		case 2: // Delete
			temp = findOnePiece(root);
			root = deleteNode(root, temp);
			root = sortNode(root);

			break;

		case 3: // Print
			printAll(root);
			printf("\n");
			break;

		default:
			break;
		}
	}

	// Exit
	freeAll(root);

	return 0;
} // end of main

node *findOnePiece(node *root){
	node *temp = 0;
	int nHeight = 1; // maximum distance from root to terminal
	int nDepth = 0; // 
	int temp_num = 0;

	temp = root;

	// set height
	while (temp->Left != NULL){
		temp = temp->Left;
		nHeight++;
	}

	// set current depth
	nDepth = nHeight;

	// find onepiece
	while (temp != root){

		// left of parent
		if (temp == temp->Parent->Left){

			// there is right of parent
			if (temp->Parent->Right != NULL){
				temp = temp->Parent->Right;

				// go to left terminal
				while (temp->Left != NULL){
					temp = temp->Left;
					nDepth++;
				}

				// depth check
				if (nDepth != nHeight){
					return temp;
				}
			}

			// right is empty
			else{
				temp = temp->Parent;
				nDepth--;

				return temp;
			}
		}

		// right of parent
		else if (temp == temp->Parent->Right){

			while (temp == temp->Parent->Right){
				temp = temp->Parent;
				nDepth--;

				if (temp == root){
					return root;
				}
			}
		}

		else{
			printf("wrong access\n");
			return;
		}
	}

	if (temp == root){
		return root;
	}
}

node *addNode(node *root, node *temp, int key){
	node *new = 0;
	int temp_num = 0;

	new = CREATE_NEW_NODE;

	new->key = key;
	new->Left = NULL;
	new->Right = NULL;
	
	// add left node
	if ((temp->Left == NULL) && (temp->Right == NULL)){
		temp->Left = new;
		new->Parent = temp;
	}
	
	// add right node
	else if((temp->Left != NULL) && (temp->Right == NULL)){
		temp->Right = new;
		new->Parent = temp;
	}


	// full binary -> up height
	else if ((temp->Left != NULL) && (temp->Right != NULL) && (temp == root)){
		while (temp->Left != NULL){
			temp = temp->Left;
		}

		temp->Left = new;
		new->Parent = temp;
	}

	else {
		printf("wrong access\n");
		return;
	}

	// sorting
	while (new->key > new->Parent->key){
		temp_num = new->key;
		new->key = new->Parent->key;
		new->Parent->key = temp_num;

		new = new->Parent;

		if (new->Parent == NULL){
			break;
		}
	}

	return root;
}

node *deleteNode(node *root, node *temp){
	int temp_num = 0;

	// full binary -> delete right
	if (temp == root){
		while (temp->Right != NULL){
			temp = temp->Right;
		}

		temp_num = temp->key;
		temp->key = root->key;
		root->key = temp_num;

		temp->Parent->Right = NULL;
		free(temp);
	}

	// not full binary
	else{

		// delete right node
		if ((temp->Left != NULL) && (temp->Right != NULL)){
			temp = temp->Right;

			temp_num = temp->key;
			temp->key = root->key;
			root->key = temp_num;

			temp->Parent->Right = NULL;
			free(temp);
		}

		// delete left node
		else if((temp->Left != NULL) && (temp->Right == NULL)){
			temp = temp->Left;

			temp_num = temp->key;
			temp->key = root->key;
			root->key = temp_num;

			temp->Parent->Left = NULL;
			free(temp);
		}

		else{
			printf("wrong access\n");

		}
	}

	return root;
} // end of deleteNode

node *sortNode(node *root){
	node *temp;
	int temp_num = 0;
	
	// while root is bigger than children
	while ((root->key < root->Left->key) || (root->key < root->Right->key)){
		temp = root;

		// sorting left
		while (temp->key < temp->Left->key){
			temp_num = temp->key;
			temp->key = temp->Left->key;
			temp->Left->key = temp_num;

			temp = temp->Left;

			if (temp->Left == NULL){
				break;
			}
		}

		temp = root;

		// sorting right
		while (temp->key < temp->Right->key){
			temp_num = temp->key;
			temp->key = temp->Right->key;
			temp->Right->key = temp_num;

			temp = temp->Right;

			if (temp->Right == NULL){
				break;
			}
		}
	}

	return root;
}

void printAll(node* root){
	if (root){
		printf("%d ", root->key);
		printAll(root->Left);
		printAll(root->Right);
	}
	
} // end of printAll

void freeAll(node* root){
	if (root){
		//postTraversal
		freeAll(root->Left);
		freeAll(root->Right);
		free(root);
	}
}
