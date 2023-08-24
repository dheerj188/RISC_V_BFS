#include<stdio.h>
#include "trees.h"
#include<stdlib.h>

void enqueue(Nqueue *head,Node node){
    Nqueue *next = head->next;
    Nqueue *new = (Nqueue *)malloc(sizeof(Nqueue));
    //printf("New location @ %p\n",new);
    if (new==NULL){
        printf("An error in mem allocation occured! Exiting..");
        return;
    }
    else{
        new->node = node;
        new->next = NULL;
    }
    while (next!=NULL){
        head = next;
        next = head->next;
    }
    head->next = new;
    return;
}

void dequeue(Nqueue **head_ptr){
   if(*(head_ptr)==NULL){
    printf("Queue is already empty!");
    return;
   }

   else{
    //Nqueue **head_ptr = (Nqueue **)malloc(sizeof(Nqueue*));
    Nqueue *temp = (*head_ptr)->next;
    Nqueue *del = (*head_ptr);
    *head_ptr = temp;
    free(del);
    return;
   } 
}

void traverse(Nqueue *head){
    while (head!=NULL){
        //printf("current addr: %p value: %d next_elements addr: %p \n",head,head->elem,head->next);
        printf("Node elem = %c\n",head->node.elem);
        head = head->next;
    }
    printf("\n");
    return;
}

Node * link_nodes_to(Node *child1,Node *child2,char parent_val){
    Node *parent_node = (Node *)malloc(sizeof(Node));
    parent_node->c1 = child1;
    parent_node->c2 = child2;
    parent_node->elem = parent_val;
    if(child1!=NULL){
        child1->p = parent_node;
    }
    if(child2!=NULL){
        child2->p = parent_node;
    }
    return parent_node;
}

char * BFS(Node *root,char elem){
    Nqueue *queue = (Nqueue *)malloc(sizeof(Nqueue));
    char *path = (char *)malloc((int) sizeof(char)*10);
    Node *child1 = root->c1;
    Node *child2 = root->c2;
    Node *backtrack_node;
    char check = root->elem;
    queue->node = *(root);
    queue->next = NULL;
    while (check != elem){
        if (child1 != NULL){
            enqueue(queue,*(child1));
        }
        if (child2 != NULL){
            enqueue(queue,*(child2));
        }
        dequeue(&queue);
        check = queue->node.elem;
        child1 = queue->node.c1;
        child2 = queue->node.c2;
    }
    *(path) = queue->node.elem;
    int i = 1;
    backtrack_node = queue->node.p;
    while (backtrack_node != NULL){
        *(path + i) = backtrack_node->elem;
        backtrack_node = backtrack_node->p;
        i++;
    }
    *(path+i) = '\0';    
    while (queue != NULL){
	    dequeue(&queue); //Remove all elements from the queue and free up the memory.
    }
    return path;
}

void display_path(char *str){
    char *ptr = str;
    int i=0;
    while((*ptr)!='\0'){
        ptr++;
        i++;
    }
    int j = 1;
    while(j<=i){
        printf("%c ",*(ptr-j));
        j++;
    }
    printf("\n");
    return;
}
