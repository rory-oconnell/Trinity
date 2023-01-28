#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>          // included this as it dismissed some errors that were appearing in the submission.

int comparisions;           // Total comparisons made in the program
int bst_words;              // Number of times the word_count is searched for
int bst_names;              // Number of times names are searched for
int duplicate_IDs_fixed;    // In the scenario where the hash function generates the same hash for two books, this counter will track then being fixed
int count;                  // Whenever a book is added to a node on the tree, this is incremented
int additions;              // Whenever the bstdb_add function is invoked, this is incremented

typedef struct tree_node tree_node;     // Declaration of the struct used to represent a book in the BST

struct tree_node
{
    char *name;                         // Name of the book
    int word_count;                     // Number of words in the book
    int doc_id;                     // Unique ID that will be generated by a hash function
    tree_node *left;                    // Pointer to the left branch, dictated by the doc_id
    tree_node *right;                   // Pointer to the right branch, dictated by the doc_id
};
tree_node *root;                        // Pointer of the root node


int bstdb_init ( void )
{
    if(1) {
        root = NULL;                    // Initialising variables
        duplicate_IDs_fixed = 0;
        comparisions = 0;
        bst_names = 0;
        additions = 0;
        bst_words= 0;
        count = 0;
        return 1;
    }
    else return 0;
}

int book_hash(char* s)
{
    int hash = 0;
    while (*s) {
        hash = (32*( hash+ *s)) % 1000000;
        s++;
    }
    return hash;
}

tree_node * new_node(char *name, int word, int id)
{
    tree_node *temp_book = (tree_node*)malloc(sizeof(tree_node));
    temp_book->left = NULL;
    temp_book->right = NULL;
    temp_book->doc_id = id;
    temp_book->name = name;
    temp_book->word_count =word;

    return temp_book;
}

int bstdb_add ( char *name, int word_count )
{
    additions++;                            // Each time the add function is invoked, one gets added to additions
    int id = book_hash(name);

    tree_node * new_book = new_node(name, word_count, id);

    if (root == NULL)
        {
            root = new_book;
            count++;
            return (root->doc_id);
        }

    tree_node * search_cursor = root;
    tree_node * holder_cursor = root;

    // This is the search portion of the function that finds the node that is NULL
    while (search_cursor != NULL)
    {
        holder_cursor = search_cursor;
        if (new_book->doc_id < search_cursor->doc_id)
        {
            search_cursor = search_cursor->left;
        }
        else if (new_book->doc_id > search_cursor->doc_id)
        {
            search_cursor = search_cursor->right;
        }
        else if (new_book->doc_id == search_cursor->doc_id)
        {
            new_book->doc_id++;
            duplicate_IDs_fixed++;

        }
    }

    // Upon exiting this while loop, we will have established that the search_cursor is NULL
    // And the holder_cursor will contain the last value of interest in the BST
    // Segmentation fault encountered here --- Fixed

    if (new_book->doc_id < holder_cursor->doc_id)
    {
        holder_cursor->left = new_book;
        count++;
        return (holder_cursor->left->doc_id);
    }
     else if (new_book->doc_id > holder_cursor->doc_id)
    {
        holder_cursor->right = new_book;
        count++;
        return (holder_cursor->right->doc_id);
    }
    else {return -1;}
}


tree_node* tree_search(tree_node* root, int id)
{
    if (id == root->doc_id)    // If the things being serached for is the root, return the root
    {
        return root;
    }
    else if(id < root->doc_id && root->left != NULL) // Search left
    {
        comparisions++;
        return tree_search(root->left, id);
    }
    else if (id > root->doc_id && root->right != NULL) // Search right
    {
        comparisions++;
        return tree_search(root->right, id);
    }
    else {
        return NULL;
    }
}


int bstdb_get_word_count ( int doc_id )
{
    bst_words++;
    tree_node *book = (tree_node*)malloc(sizeof(tree_node));
    book = tree_search(root, doc_id);
    if (book->doc_id == doc_id)
    {
        return (book->word_count);
    }
    else return -1;
}

char* bstdb_get_name ( int doc_id )    // Code from the bstdb_get_word_count function is just reused here
{
    bst_names++;
    tree_node *book = (tree_node*)malloc(sizeof(tree_node));
    book = tree_search(root, doc_id);
    if (book != NULL)
    {
        return (book->name);
    }
    else return NULL;
}

void print_sorted(tree_node * root)     // Very analagous code from Task 1
{
    if (root != NULL)
    {
        print_sorted(root->left);                               // Finding the NULL at the end of the left branch recursively
        printf("%i \t %s \n", root->doc_id, root->name);    // When we reach the NULL, print on the way back up
        print_sorted(root->right);                              // Then explore the right branch
    }
}

// Tree balance means that the difference between the left subtree and the right subtree
// Cannot be greater than one. Must be less than or equal to one. Single node is a
// balanced subtree also. Example, left subtree height one, right subtree height two.
// abs(1 - 2) = 1 which is a balanced tree. So we can write this out a bit more explicitly.
// if (abs(leftSubtreeHeight - rightSubtreeHeight) <= 1) {printf("Tree balanced.")}
// else printf("Tree is not balanced.").
// How to establish the tree height. Recursively as are you balanced and what is you height?
// Nodes that are connected to NULL pointers will return -1. For final nodes abs(-1-(-1)) = 0

int height(tree_node *root)             // Calculates the height of the tree recursively
{
    if (root == NULL) return -1;
    int lh = height(root->left);
    int rh = height(root->right);
    return lh > rh ? lh + 1 : rh + 1;
}

int treeBalanced(int left_height, int right_height)
{
    if (abs(left_height - right_height) <= 1){return 1;}
    else return 0;
}

void bstdb_stat( void )
{
    double average_searches = (double)comparisions/(bst_words + bst_names);    // Total comparisons made divided by the sum of the number of searches made for word_counts and titles
    printf("Avg comparisions per search: %lf \n", average_searches);

    // Comparison of whether the number of things read matches the number of things added.
    if (count == additions)
    {
        printf("List is of the expected size.\n");
    }
    else {
        printf("List is not of the expected size.\n");
    }
    int leftH;
    int rightH;

    leftH = 1 + (height(root->left));       // We add one to account for the root node that is missing from the calculation
    rightH = 1 + (height(root->right));

    int balBool = treeBalanced(leftH, rightH);
    if (balBool == 1){printf("Tree is balanced");
    }
    else if (balBool == 0){printf("Tree is not balanced\n");
    }
    printf("%i left nodes\n", leftH);
    printf("%i right nodes\n", rightH);

}

void tree_delete(tree_node* root)   // Highly analagous to Part 1
{
    if (root == NULL) return;		// Initially checks to see if the node being looked at is NULL
    tree_delete(root->left);		// Check the left branch first
    tree_delete(root->right);		// Check right branch next
    free(root);						// free memory when other steps have been exhausted
}

void bstdb_quit ( void )
{
    tree_delete(root);
}