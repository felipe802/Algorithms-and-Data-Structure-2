/*
vector: without pointers. colisions treatment inside the vector itself = encadeamento interior and enderecamento aberto
linked list: pointers. colisions treatment outside = encadeamento exterior
*/

#include <stdio.h>
#include <stdlib.h>
//15 elements, double 30, nearer prime 31
#define SIZE 31

//list structure
typedef struct node {
    int key;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    int size;
} List;

//initialize each list in the table correctly
void initializeList(List* l) {
    l->head = NULL;
    l->size = 0;
}

//initialize all the table, run all the vector
void initializeTab(List t[]) {
    for (int i = 0; i < SIZE; i++) {
        initializeList(&t[i]);
    }
}

int funcHash(int key) {
    return key % SIZE;
}

void insertList(List* l, int value) {
    Node* new = malloc(sizeof(Node));

    if(new) {
        new->key = value;
        new->next = l->head;
        l->head = new;
        l->size++;
    }
    else printf("error allocating memory!");
}

//now, we insert on Hash table
void insertTab(List t[], int value) {
    int id = funcHash(value);
    insertList(&t[id], value);
}


void displayList(List* l) {
    Node* aux = l->head;
    printf("Size = %d:  ", l->size);
    while(aux) {
        printf("%d -> ", aux->key);
        aux = aux->next;
    }
}

void displayTab(List t[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%2d: ", i);
        displayList(&t[i]);
        printf("\n");
    }
}


int searchList(List* l, int value) {
    Node* aux = l->head;
    while(aux && aux->key != value) aux = aux->next;
    if (aux) return aux->key;
    return 0;
}


int searchTab(List t[], int key) {
    int id = funcHash(key);
    return searchList(&t[id], key);
}


int main() {
    int op, value, output;
    List tab[SIZE];

    initializeTab(tab);

    do {
        printf("\n0-exit\n1-insert\n2-search\n3-display\n");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("which value to insert? ");
                scanf("%d", &value);
                insertTab(tab, value);
                break;
            case 2:
                printf("which value to search? ");
                scanf("%d", &value);
                output = searchTab(tab, value);
                if (output != 0) printf("value found!: %d\n", value);
                else printf("value did not found!\n");
                break;
            case 3:
                printf("\n");
                displayTab(tab);
                break;
            default: 
                if (op != 0) printf("invalid option\n");
        }
    } while (op != 0);

    return 0;
}