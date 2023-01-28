#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node{
    char data;
    Node* next;
};

int main(void)
{
    Node* head = (Node*)malloc(sizeof(Node));
    Node* i = (Node*)malloc(sizeof(Node));
    Node* j = (Node*)malloc(sizeof(Node));
    Node* k = (Node*)malloc(sizeof(Node));


    head->next = i;
    i->data = 'A';
    i->next = j;
    j->data = 'B';
    j->next = k;
    k->data = 'C';
    k->next = NULL;

    Node* cursor = (Node*)malloc(sizeof(Node));
    cursor->next = i;
    head->next = NULL;




}