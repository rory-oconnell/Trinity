#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>					// Standard functions throwing errors, included this to dismiss them

// FLOCCINAUCINIHILIPILIFICATION

int TOTAL_SPACE = 256;
int i = 0;														// Counter used to help load the letters

typedef struct Tree_Node            							// Declaration of Tree_Node struct
{
	struct Tree_Node *left;         							// Pointer left
	struct Tree_Node *right;        							// Pointer right
	char data;                      							// Holds data
}
Tree_Node;
void tree_insert ( Tree_Node* root, char data );
Tree_Node* create_bst (char data[]);
Tree_Node* tree_search ( Tree_Node* root, char data );
void tree_print_sorted ( Tree_Node* root );
void tree_delete ( Tree_Node* root );

int main(void)
{
	char word[TOTAL_SPACE];										// Creating a space to hold the input
	printf("Raw Data:\n");
	fgets(word, TOTAL_SPACE, stdin);		                    // Getting input from the user
	printf("\n");

	Tree_Node* root = create_bst(word);							// This is the creation of the BST

    char input;
	scanf("%c", &input);		                    			// Getting input from the user
	printf("\n");

	Tree_Node* location = tree_search(root, input);

	if (location == NULL)
	{
		printf("%c is not in the dataset\n", input);
	}
	else (printf("%c found\n", input));

	printf("Sorted Data:\n");
	tree_print_sorted(root);

	tree_delete(root);

}

// Creates a new node in the tree in the appropriate position for a binary search tree.
void tree_insert(Tree_Node* root, char data)
{
	if (data < root->data)
	{
		if (root->left == NULL)									// If the data is less than the root data
		{
			root->left = (Tree_Node*)malloc(sizeof(Tree_Node));	// Same node creation code as from above
			root->left->data = data;
			root->left->left = NULL;
			root->left->right = NULL;
		}
		else (tree_insert(root->left, data));					// Recursive call of the insert function
	}
	else														// If the data is greater than or equal to the root data
	{
		if (root->right == NULL)
		{
			root->right = (Tree_Node*)malloc(sizeof(Tree_Node));// Same node creation code as from above
			root->right->data = data;
			root->right->left = NULL;
			root->right->right = NULL;
		}
		else (tree_insert(root->right, data));					// Recursive call of the insert function
	}
}

Tree_Node* create_bst (char data[])
{
	Tree_Node *root = (Tree_Node*)malloc(sizeof(Tree_Node));    // Root node creation
	root->data = data[0];     									// The data in root is the first item from the user input
	root->left = NULL; 											// Setting left pointer to NULL
	root->right = NULL;											// Setting right pointer to NULL
	i++;														// Increment the global counter

	while (isalnum(data[i]))									// Wondering if I can replace this with a do while...
    {
	 	tree_insert(root, data[i]);
	 	i++;
	}
	return root;
}

Tree_Node* tree_search(Tree_Node* root, char data)
{
	if (data == root->data){return root;}
	else if (data < root->data && root->left != NULL){tree_search(root->left, data);}
	else if (data >= root->data && root->right != NULL){tree_search(root->right, data);}
	else return NULL;
}

// Traverse the tree, printing the data held in every node, in smallest-to-greatest sorted order.
void tree_print_sorted(Tree_Node* root)
{
	if (root->left != NULL){tree_print_sorted(root->left);}		// If the left pointer is not NULL, something smaller exists which should be printed first

	else if (root->left == NULL && root->right == NULL)			// If we reach a leaf, return to the branch node
	{
		printf("%c", root->data);
		return;
	}

	printf("%c", root->data);
	if (root->right != NULL){tree_print_sorted(root->right);}	// Only
}

// Delete every node in the tree without creating a memory leak.
// Check notes for part in lecture where the order of deletion was given

// - Traverse to node with no branches and delete.

void tree_delete(Tree_Node* root)
{
    if (root == NULL) return;		// Initially checks to see if the node being looked at is NULL
    tree_delete(root->left);		// Check the left branch first
    tree_delete(root->right);		// Check right branch next
    free(root);						// Free memory when other steps have been exhausted
}