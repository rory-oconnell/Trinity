#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
struct Node{
    char data;
    Node* next;
};

void add_node(Node** list, char d){
    Node* newNode = (Node*)malloc( sizeof( Node ) );
    newNode->data = d;
    newNode->next = *list;
    *list=newNode; // and not list = &newNode; as you can't change a parameter in C

}

void remove_node(Node** list, char d){ //recursive
    if(list){
        Node* current = *list;
        if(current){
            if(current->data == d){
                printf("found it!\n");
                *list = current->next;
                free(current);
                printf("removed it!\n");
            }else{
                remove_node(&current->next,d);
            }

        }
    }
}

void remove_node2(Node** list, char d){ // iterative
        Node* previous = NULL;
        Node* current = *list;
        Node* next = NULL;
        while(current){ // deals with both the cases where we have found it and teh case where it's not in the list
            next = current->next;
            if(current->data == d ){
                printf("found it!\n");
                if(previous){
                    previous->next = next;
                }else{
                    *list = next;
                }

                free(current);
                printf("removed it!\n");
                current=NULL; // or break;
            } else{ // the current node doesn't match
                previous = current;
                current= next;
            }

        }

}

void delete_list(Node** list){ // recursive
    if(list){
        if(*list){
            Node* next = (*list)->next;
            printf("About to delete: %c\n", (*list)->data);
            free(*list);
            *list = NULL;
            printf("Done\n");
            delete_list(&next);
        }
    }


}

void delete_list2(Node** list){ // iterative
    if(list){ // there is a list!
        Node* current = *list;
        while(current){

            Node* next = current->next;
            printf("About to delete: %c\n", current->data);
            free(current);
            printf("Done\n");
            current = next;
        }
    }


}

void print_list (Node* list){
    Node* node = list;
    while(node!=NULL){
        printf("Node: %c\n", node->data);
        node = node ->next;

    }
}

int list_size(Node* list){
    int size=0;
    while(list){
        list=list->next;
        size++;
    }
    printf("Size: %i\n", size);
    return size;
}

void reverse_list(Node** list){
    int numberLinksReversed = 0;
    Node* previous = NULL;
    Node* current = NULL;
    Node* next = NULL;

    if(list){
        current = *list;

        while(current){
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
            numberLinksReversed++;
        }
    }
    printf("%i links were changed \n",numberLinksReversed);
    *list = previous;
}

void add_node2(Node* head, char d, int offset){ // where memory has already been allocated - ptr to size instead offset so you don't need to update the size
Node* newNode= head + offset*sizeof(Node);
newNode->data = d;
newNode->next = head + (offset+1)*sizeof(Node);
}




int main()
{
    Node* head = NULL;
    add_node(&head,'a');
    add_node(&head,'b');
    add_node(&head,'c');

    print_list(head);
    list_size(head);
    printf("about to reverse\n");
    reverse_list(&head);
    print_list(head);

    remove_node2(&head, 'a');
    print_list(head);

    delete_list2(&head);
    printf("Done Deleting \n");


    // allocate the memory upfront
    int MAX_NUMBER_NODES = 20;
    Node* head2 = (Node*) malloc(MAX_NUMBER_NODES* sizeof(Node) );
    int size = 0;
    add_node2(head2,'f',size);
    size++;
    add_node2(head2,'g',size);
    size++;

    // this way we can iterate over the memory directly to traverse the list
    for (int i =0;i<size;i++){
        printf("Node: %c\n", (head2+i*sizeof(Node))->data);
    }

    return 0;
}