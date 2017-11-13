#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* prev, next;
};

struct Node* getNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}