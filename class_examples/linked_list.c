#include <stdio.h>
#include <stdlib.h>

typedef struct node //giving the structure itself a temporary name
{
    int number;
    struct node *next; //referring to the temporary name inside of the structure in order to have a pointer thereto
}
node; //name of the structure

int main(void)
{
    //TODO: create an empty linked list
    node *list = NULL; //without explicitly initialising the variable, this points to a garbage value. specify that there is nothing at that value, and that is deliberate.
    //COMPLETE

    //TODO: add an element to the linked list
    node *n = malloc(sizeof(node)); //n is a temporary variable. allocating the size of a node which has enough memory to store an int and another pointer variable.
    if (n == NULL)
    {
        return 1; //protection against if there is not enough memory to malloc the node n. just not enough memory to make the node. it is not there, it is null.
    }
    n->number = 1;  //recall -> is the equivalent of the *. operators combined. * go to the location of the pointer and . access the variable therein.
    n->next = NULL; //the first element of the linked list has the number one, and a pointer that goes to NULL
    list = n; //the variable "list" is the variable that represents the whole list. now that you have an actual node to point to (n)
              //you are setting list, which is a pointer (in reality it is a node, but we don't care about its number value, just the address) equal to whatever n is, the address of our first node.
    //COMPLETE

    //TODO: add a second element to the linked list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list); //we free the list to avoid leaking memory
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;
    //COMPLETE

    //TODO: add a third element to the linked list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;
    //COMPLETE

    //TODO: Print out the values of the linked list
    //for a temporary pointer to the beginning of the list
    //as long as that temporary pointer does not equal null (pointing to a legitimate value)
    //update the temporary pointer to be whatever the value of the temporary pointers "next" field is
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    //COMPLETE

    //TODO: Free all the memory that you have allocated during the program.
    while (list != NULL)    //while the list is not null. we have three nodes in it so it is not null
    {
        node *tmp = list->next; //list represents the first node in the linked list. we have a temporary variable that captures the pointer value of the first node.
        free(list); //we free the first piece of memory, safe in knowing that we have stored that information in tmp, so the rest of the list will not be stranded
        list = tmp; //the first node is then equal to the pointer value of the next node.
    }
}