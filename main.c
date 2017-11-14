#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
};

void printList(struct Node* head){
    while (head != NULL){
        printf("%d\n", head->data);
        head = head->next;
    }
}

void push(struct Node** head, int new_data){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head);
    new_node->prev = NULL;

    if ((*head) != NULL)
        (*head)->prev = new_node;

    (*head) = new_node;
}

void swap(struct Node* a, struct Node* b){
    int tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}

/** Insertion Sort */
void insertOrden(struct Node** head, struct Node* newNode){
    struct Node* actual;
    if (*head == NULL)
        *head = newNode;

    else if ((*head)->data >= newNode->data){
        newNode->next = *head;
        newNode->next->prev = newNode;
        *head = newNode;
    }
    else {
        actual = *head;

        while (actual->next != NULL && actual->next->data < newNode->data)
            actual = actual->next;

        newNode->next = actual->next;


        if (actual->next != NULL)
            newNode->next->prev = newNode;

        actual->next = newNode;
        newNode->prev = actual;
    }
}

void insertionSort(struct Node** head){
    struct Node* sorted = NULL;
    struct Node* actual = *head;
    while (actual != NULL){
        struct Node* next = actual->next;
        actual->prev = actual->next = NULL;
        insertOrden(&sorted, actual);
        actual = next;
    }
    *head = sorted;
}
/***/

/** Bubble Sort */
void bubbleSortAux(struct Node* head){
    while(head->next!=NULL){
        if(head->data > head->next->data){
            swap(head,head->next);
        }
        head=head->next;
        bubbleSortAux(head);
    }
}
void bubbleAux(struct Node* head, int n){
    if (n == 0){
        bubbleSortAux(head);
    } else {
        bubbleSortAux(head);
        bubbleAux(head, 0);
    }
}
void bubbleSort(struct Node* head){
    bubbleAux(head, 3);
}
/***/

/*** Merge Sort */
//Lista1 = mergeSort(Lista1);
struct Node* split(struct Node* head){
    struct Node* fast = head, *slow = head;
    while (fast->next && fast->next->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    struct Node* tmp = slow->next;
    slow->next = NULL;
    return tmp;
}

struct Node* merge(struct Node* prim, struct Node* sec){
    if(!prim)
        return sec;

    if(!sec)
        return prim;

    if (prim->data < sec->data){
        prim->next = merge(prim->next, sec);
        prim->next->prev = prim;
        prim->prev = NULL;
        return prim;
    } else {
        sec->next = merge(prim, sec->next);
        sec->next->prev = sec;
        sec->prev = NULL;
        return sec;
    }
}

struct Node* mergeSort(struct Node* head){
    if (!head || !head->next)
        return head;

    struct Node* sec = split(head);
    head = mergeSort(head);
    sec = mergeSort(sec);

    return merge(head, sec);
}
/***/

/*** Quick Sort */
struct Node* lastNode(struct Node* head){
    while (head && head->next)
        head = head->next;
    return head;
}

struct Node* partition(struct Node* l, struct Node* h){
    int x = h->data;
    struct Node* i = l->prev;
    for (struct Node* j = l; j != h; j = j->next){
        if (j->data <= x){
            i = (i == NULL)? l: i->next;
            swap(i, j);
        }
    }
    i = (i == NULL)? l : i->next;
    swap(i, h);
    return i;
}

void _quickSort(struct Node* l, struct Node* h){
    if (h != NULL && l != h && l != h->next){
        struct Node* p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}

void quickSort(struct Node* head){
    struct Node* h = lastNode(head);
    _quickSort(head, h);
}
/***/

int main(){
    struct Node* Lista1 = NULL;

    push(&Lista1, 3);
    push(&Lista1, 63);
    push(&Lista1, 64);
    push(&Lista1, 56);
    push(&Lista1, 5);
    push(&Lista1, 9);
    push(&Lista1, 52);
    push(&Lista1, 577);

    quickSort(Lista1);

    printList(Lista1);
}