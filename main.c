#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
struct Node* rndList(int largo){
    struct Node* list = NULL;
    int numero;
    time_t hora = time(NULL);
    srand((unsigned int) hora);
    for (int i = 0; i < largo; ++i) {
        numero = rand()%10000;
        push(&list, numero);
    }
    return list;
}
struct Node* invertList(int largo){
    struct Node* list = NULL;
    for (int i = 0; i < largo; ++i) {
        push(&list, i);
    }
    return list;
}
struct Node* sortList(int largo){
    struct Node* list = NULL;
    while (largo != 0){
        push(&list, largo);
        largo--;
    }
    return list;
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
void bubbleSort(struct Node* head){
    int swapped, i;
    struct Node* ptr1;
    struct Node* lptr = NULL;
    if (ptr1 == NULL)
        return;

    do{
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr){
            if (ptr1->data > ptr1->next->data){
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }while (swapped);
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

/*** Selection Sort */
void selectionSort(struct Node* head){
    struct Node* h = head, *i, *j;
    for (i = h; i != NULL && i->next != NULL; i = i->next){
        struct Node* min;
        min = i;
        for(j = i->next; j != NULL; j = j->next){
            if(j->data < min->data)
                min = j;
        }
        if (min != i){
            swap(min, i);
        }
    }
    //head = &h;
}
/***/

void testBubble(){
    //mejor caso
    struct Node** bestCase = (struct Node**)malloc(5*sizeof(struct Node));
    int ptrmover = 0;
    for (int i = 10; i <= 100000; i*=10) {
        *(bestCase + ptrmover) = sortList(i);
        ptrmover++;
    }
    int count = 10;
    long time;
    clock_t start, end;
    long segBest[5];
    int elemtBest[5];
    for (int j = 0; j < 5; ++j) {
        start = clock();
        bubbleSort(*(bestCase+j));
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segBest[j] = time;
        elemtBest[j] = count;
        count*=10;
    }
    count = 10;
    FILE* bestfile;
    bestfile = fopen("BubbleSort_Peor.csv", "w");
    if (bestfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if(i+1 == 5){
                fprintf(bestfile, "%d",elemtBest[i]);
            } else {
                fprintf(bestfile, "%d,",elemtBest[i]);
            }
        }
        fprintf(bestfile,"\n");
        for (int j = 0; j < 5; ++j) {
            if(j+1 == 5){
                fprintf(bestfile, "%ld",segBest[j]);
            } else {
                fprintf(bestfile, "%ld,",segBest[j]);
            }
        }
    }
    fclose(bestfile);
    free(bestCase);

    //Caso promedio
    struct Node** promCase = (struct Node**)malloc(5*sizeof(struct Node));
    int promIndex = 0;
    for (int m = 10; m <= 100000; m*=10) {
        *(promCase + promIndex) = rndList(m);
        promIndex++;
    }
    long segProm[5];
    int elemtProm[5];
    for (int k = 0; k < 5; ++k) {
        start = clock();
        bubbleSort(*(promCase+k));
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segProm[k] = time;
        elemtProm[k] = count;
        count*=10;
    }
    count = 10;
    FILE* promfile;
    promfile = fopen("BubbleSort_Promedio.csv", "w");
    if (promfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5){
                fprintf(promfile, "%d", elemtProm[i]);
            } else {
                fprintf(promfile, "%d,", elemtProm[i]);
            }
        }
        fprintf(promfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5){
                fprintf(promfile, "%ld", segProm[j]);
            } else {
                fprintf(promfile, "%ld,", segProm[j]);
            }
        }
    }
    fclose(promfile);
    free(promCase);

    //Peor Caso
    struct Node** worstCase = (struct Node**)malloc(5*sizeof(struct Node));
    int worstIndex = 0;
    for (int l = 10; l <= 100000; l*=10) {
        *(worstCase + worstIndex) = invertList(l);
        worstIndex++;
    }
    long segWorst[5];
    int elemtWorst[5];
    for (int n = 0; n < 5; ++n) {
        start = clock();
        bubbleSort(*(worstCase+n));
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segWorst[n] = time;
        elemtWorst[n] = count;
        count*=10;
    }
    FILE* worstfile;
    worstfile = fopen("BubbleSort_Mejor.csv", "w");
    if (worstfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5) {
                fprintf(worstfile, "%d", elemtWorst[i]);
            } else {
                fprintf(worstfile, "%d,", elemtWorst[i]);
            }
        }
        fprintf(worstfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5) {
                fprintf(worstfile, "%ld", segWorst[j]);
            } else {
                fprintf(worstfile, "%ld,", segWorst[j]);
            }
        }
    }
    fclose(worstfile);
    free(worstCase);
}

void testInsertion(){
    //mejor caso
    struct Node** bestCase = (struct Node**)malloc(5*sizeof(struct Node));
    int ptrmover = 0;
    for (int i = 10; i <= 100000; i*=10) {
        *(bestCase + ptrmover) = sortList(i);
        ptrmover++;
    }
    int count = 10;
    long time;
    clock_t start, end;
    long segBest[5];
    int elemtBest[5];
    for (int j = 0; j < 5; ++j) {
        start = clock();
        insertionSort(&(bestCase[j]));
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segBest[j] = time;
        elemtBest[j] = count;
        count*=10;
    }
    count = 10;
    FILE* bestfile;
    bestfile = fopen("InsertionSort_Peor.csv", "w");
    if (bestfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if(i+1 == 5){
                fprintf(bestfile, "%d",elemtBest[i]);
            } else {
                fprintf(bestfile, "%d,",elemtBest[i]);
            }
        }
        fprintf(bestfile,"\n");
        for (int j = 0; j < 5; ++j) {
            if(j+1 == 5){
                fprintf(bestfile, "%ld",segBest[j]);
            } else {
                fprintf(bestfile, "%ld,",segBest[j]);
            }
        }
    }
    fclose(bestfile);
    free(bestCase);

    //Caso promedio
    struct Node** promCase = (struct Node**)malloc(5*sizeof(struct Node));
    int promIndex = 0;
    for (int m = 10; m <= 100000; m*=10) {
        *(promCase + promIndex) = rndList(m);
        promIndex++;
    }
    long segProm[5];
    int elemtProm[5];
    for (int k = 0; k < 5; ++k) {
        start = clock();
        insertionSort(&(promCase[k]));
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segProm[k] = time;
        elemtProm[k] = count;
        count*=10;
    }
    count = 10;
    FILE* promfile;
    promfile = fopen("InsertionSort_Promedio.csv", "w");
    if (promfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5){
                fprintf(promfile, "%d", elemtProm[i]);
            } else {
                fprintf(promfile, "%d,", elemtProm[i]);
            }
        }
        fprintf(promfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5){
                fprintf(promfile, "%ld", segProm[j]);
            } else {
                fprintf(promfile, "%ld,", segProm[j]);
            }
        }
    }
    fclose(promfile);
    free(promCase);

    //Peor Caso
    struct Node** worstCase = (struct Node**)malloc(5*sizeof(struct Node));
    int worstIndex = 0;
    for (int l = 10; l <= 100000; l*=10) {
        *(worstCase + worstIndex) = invertList(l);
        worstIndex++;
    }
    long segWorst[5];
    int elemtWorst[5];
    for (int n = 0; n < 5; ++n) {
        start = clock();
        insertionSort(&(worstCase[n]));
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segWorst[n] = time;
        elemtWorst[n] = count;
        count*=10;
    }
    FILE* worstfile;
    worstfile = fopen("InsertionSort_Mejor.csv", "w");
    if (worstfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5) {
                fprintf(worstfile, "%d", elemtWorst[i]);
            } else {
                fprintf(worstfile, "%d,", elemtWorst[i]);
            }
        }
        fprintf(worstfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5) {
                fprintf(worstfile, "%ld", segWorst[j]);
            } else {
                fprintf(worstfile, "%ld,", segWorst[j]);
            }
        }
    }
    fclose(worstfile);
    free(worstCase);
}

void testMerge(){
    //mejor caso
    struct Node** bestCase = (struct Node**)malloc(5*sizeof(struct Node));
    struct Node* listap;
    int ptrmover = 0;
    for (int i = 10; i <= 100000; i*=10) {
        *(bestCase + ptrmover) = sortList(i);
        ptrmover++;
    }
    int count = 10;
    long time;
    clock_t start, end;
    long segBest[5];
    int elemtBest[5];
    for (int j = 0; j < 5; ++j) {
        start = clock();
        listap = mergeSort(bestCase[j]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segBest[j] = time;
        elemtBest[j] = count;
        count*=10;
    }
    count = 10;
    FILE* bestfile;
    bestfile = fopen("MergeSort_Peor.csv", "w");
    if (bestfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if(i+1 == 5){
                fprintf(bestfile, "%d",elemtBest[i]);
            } else {
                fprintf(bestfile, "%d,",elemtBest[i]);
            }
        }
        fprintf(bestfile,"\n");
        for (int j = 0; j < 5; ++j) {
            if(j+1 == 5){
                fprintf(bestfile, "%ld",segBest[j]);
            } else {
                fprintf(bestfile, "%ld,",segBest[j]);
            }
        }
    }
    fclose(bestfile);
    free(bestCase);

    //Caso promedio
    struct Node** promCase = (struct Node**)malloc(5*sizeof(struct Node));
    int promIndex = 0;
    for (int m = 10; m <= 100000; m*=10) {
        *(promCase + promIndex) = rndList(m);
        promIndex++;
    }
    long segProm[5];
    int elemtProm[5];
    for (int k = 0; k < 5; ++k) {
        start = clock();
        listap = mergeSort(promCase[k]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segProm[k] = time;
        elemtProm[k] = count;
        count*=10;
    }
    count = 10;
    FILE* promfile;
    promfile = fopen("MergeSort_Promedio.csv", "w");
    if (promfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5){
                fprintf(promfile, "%d", elemtProm[i]);
            } else {
                fprintf(promfile, "%d,", elemtProm[i]);
            }
        }
        fprintf(promfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5){
                fprintf(promfile, "%ld", segProm[j]);
            } else {
                fprintf(promfile, "%ld,", segProm[j]);
            }
        }
    }
    fclose(promfile);
    free(promCase);

    //Peor Caso
    struct Node** worstCase = (struct Node**)malloc(5*sizeof(struct Node));
    int worstIndex = 0;
    for (int l = 10; l <= 100000; l*=10) {
        *(worstCase + worstIndex) = invertList(l);
        worstIndex++;
    }
    long segWorst[5];
    int elemtWorst[5];
    for (int n = 0; n < 5; ++n) {
        start = clock();
        listap = mergeSort(worstCase[n]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segWorst[n] = time;
        elemtWorst[n] = count;
        count*=10;
    }
    FILE* worstfile;
    worstfile = fopen("InsertionSort_Mejor.csv", "w");
    if (worstfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5) {
                fprintf(worstfile, "%d", elemtWorst[i]);
            } else {
                fprintf(worstfile, "%d,", elemtWorst[i]);
            }
        }
        fprintf(worstfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5) {
                fprintf(worstfile, "%ld", segWorst[j]);
            } else {
                fprintf(worstfile, "%ld,", segWorst[j]);
            }
        }
    }
    fclose(worstfile);
    free(worstCase);
}

void testQuick(){
    //mejor caso
    struct Node** bestCase = (struct Node**)malloc(5*sizeof(struct Node));
    int ptrmover = 0;
    for (int i = 10; i <= 100000; i*=10) {
        *(bestCase + ptrmover) = sortList(i);
        ptrmover++;
    }
    int count = 10;
    long time;
    clock_t start, end;
    long segBest[5];
    int elemtBest[5];
    for (int j = 0; j < 5; ++j) {
        start = clock();
        quickSort(bestCase[j]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segBest[j] = time;
        elemtBest[j] = count;
        count*=10;
    }
    count = 10;
    FILE* bestfile;
    bestfile = fopen("QuickSort_Peor.csv", "w");
    if (bestfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if(i+1 == 5){
                fprintf(bestfile, "%d",elemtBest[i]);
            } else {
                fprintf(bestfile, "%d,",elemtBest[i]);
            }
        }
        fprintf(bestfile,"\n");
        for (int j = 0; j < 5; ++j) {
            if(j+1 == 5){
                fprintf(bestfile, "%ld",segBest[j]);
            } else {
                fprintf(bestfile, "%ld,",segBest[j]);
            }
        }
    }
    fclose(bestfile);
    free(bestCase);

    //Caso promedio
    struct Node** promCase = (struct Node**)malloc(5*sizeof(struct Node));
    int promIndex = 0;
    for (int m = 10; m <= 100000; m*=10) {
        *(promCase + promIndex) = rndList(m);
        promIndex++;
    }
    long segProm[5];
    int elemtProm[5];
    for (int k = 0; k < 5; ++k) {
        start = clock();
        quickSort(promCase[k]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segProm[k] = time;
        elemtProm[k] = count;
        count*=10;
    }
    count = 10;
    FILE* promfile;
    promfile = fopen("QuickSort_Promedio.csv", "w");
    if (promfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5){
                fprintf(promfile, "%d", elemtProm[i]);
            } else {
                fprintf(promfile, "%d,", elemtProm[i]);
            }
        }
        fprintf(promfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5){
                fprintf(promfile, "%ld", segProm[j]);
            } else {
                fprintf(promfile, "%ld,", segProm[j]);
            }
        }
    }
    fclose(promfile);
    free(promCase);

    //Peor Caso
    struct Node** worstCase = (struct Node**)malloc(5*sizeof(struct Node));
    int worstIndex = 0;
    for (int l = 10; l <= 100000; l*=10) {
        *(worstCase + worstIndex) = invertList(l);
        worstIndex++;
    }
    long segWorst[5];
    int elemtWorst[5];
    for (int n = 0; n < 5; ++n) {
        start = clock();
        quickSort(worstCase[n]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segWorst[n] = time;
        elemtWorst[n] = count;
        count*=10;
    }
    FILE* worstfile;
    worstfile = fopen("QuickSort_Mejor.csv", "w");
    if (worstfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5) {
                fprintf(worstfile, "%d", elemtWorst[i]);
            } else {
                fprintf(worstfile, "%d,", elemtWorst[i]);
            }
        }
        fprintf(worstfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5) {
                fprintf(worstfile, "%ld", segWorst[j]);
            } else {
                fprintf(worstfile, "%ld,", segWorst[j]);
            }
        }
    }
    fclose(worstfile);
    free(worstCase);
}

void testSelection(){
    //mejor caso
    struct Node** bestCase = (struct Node**)malloc(5*sizeof(struct Node));
    int ptrmover = 0;
    for (int i = 10; i <= 100000; i*=10) {
        *(bestCase + ptrmover) = sortList(i);
        ptrmover++;
    }
    int count = 10;
    long time;
    clock_t start, end;
    long segBest[5];
    int elemtBest[5];
    for (int j = 0; j < 5; ++j) {
        start = clock();
        selectionSort(bestCase[j]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segBest[j] = time;
        elemtBest[j] = count;
        count*=10;
    }
    count = 10;
    FILE* bestfile;
    bestfile = fopen("Selection_Peor.csv", "w");
    if (bestfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if(i+1 == 5){
                fprintf(bestfile, "%d",elemtBest[i]);
            } else {
                fprintf(bestfile, "%d,",elemtBest[i]);
            }
        }
        fprintf(bestfile,"\n");
        for (int j = 0; j < 5; ++j) {
            if(j+1 == 5){
                fprintf(bestfile, "%ld",segBest[j]);
            } else {
                fprintf(bestfile, "%ld,",segBest[j]);
            }
        }
    }
    fclose(bestfile);
    free(bestCase);

    //Caso promedio
    struct Node** promCase = (struct Node**)malloc(5*sizeof(struct Node));
    int promIndex = 0;
    for (int m = 10; m <= 100000; m*=10) {
        *(promCase + promIndex) = rndList(m);
        promIndex++;
    }
    long segProm[5];
    int elemtProm[5];
    for (int k = 0; k < 5; ++k) {
        start = clock();
        selectionSort(promCase[k]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segProm[k] = time;
        elemtProm[k] = count;
        count*=10;
    }
    count = 10;
    FILE* promfile;
    promfile = fopen("Selection_Promedio.csv", "w");
    if (promfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5){
                fprintf(promfile, "%d", elemtProm[i]);
            } else {
                fprintf(promfile, "%d,", elemtProm[i]);
            }
        }
        fprintf(promfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5){
                fprintf(promfile, "%ld", segProm[j]);
            } else {
                fprintf(promfile, "%ld,", segProm[j]);
            }
        }
    }
    fclose(promfile);
    free(promCase);

    //Peor Caso
    struct Node** worstCase = (struct Node**)malloc(5*sizeof(struct Node));
    int worstIndex = 0;
    for (int l = 10; l <= 100000; l*=10) {
        *(worstCase + worstIndex) = invertList(l);
        worstIndex++;
    }
    long segWorst[5];
    int elemtWorst[5];
    for (int n = 0; n < 5; ++n) {
        start = clock();
        selectionSort(worstCase[n]);
        end = clock();
        time = 1000L*(end-start)/CLOCKS_PER_SEC;
        segWorst[n] = time;
        elemtWorst[n] = count;
        count*=10;
    }
    FILE* worstfile;
    worstfile = fopen("Selection_Mejor.csv", "w");
    if (worstfile != NULL){
        for (int i = 0; i < 5; ++i) {
            if (i+1 == 5) {
                fprintf(worstfile, "%d", elemtWorst[i]);
            } else {
                fprintf(worstfile, "%d,", elemtWorst[i]);
            }
        }
        fprintf(worstfile, "\n");
        for (int j = 0; j < 5; ++j) {
            if (j+1 == 5) {
                fprintf(worstfile, "%ld", segWorst[j]);
            } else {
                fprintf(worstfile, "%ld,", segWorst[j]);
            }
        }
    }
    fclose(worstfile);
    free(worstCase);
}

int main() {

    //testBubble();
    //testInsertion();
    //testMerge();
    //testQuick();
    //testSelection();
}