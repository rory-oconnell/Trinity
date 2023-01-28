#ifndef BST_H_
#define BST_H_

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


#endif