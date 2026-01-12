#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//26 characters from the alphabet A-Z
#define SIZE 26


//list is the array
typedef struct node {
    char name[50];
    char capital[50];
    struct node* next;
} Node;

//node is the country and its capital
typedef struct list {
    Node* head;
    int size;
} List;

//initialize each list in the table correctly
void initializeList(List* l) {
    l->head = NULL;
    l->size = 0;
}

//initialize all table, run all the vector
void initializeTab(List t[]) {
    for (int i = 0; i < SIZE; i++) {
        initializeList(&t[i]);
    }
}

//to translate the first letter
int funcHash(char name[]) {
    char c = toupper(name[0]);
    if (c >= 'A' && c <= 'Z') return c - 'A';
    else return -1;
}


Node* inputCountry() {
    Node* c = malloc(sizeof(Node));
    if(!c) exit(1);
    printf("Country's name:\n");
    fgets(c->name, 49, stdin);
    c->name[strcspn(c->name, "\n")] = 0;
    printf("Country's capital:\n");
    fgets(c->capital, 49, stdin);
    c->capital[strcspn(c->capital, "\n")] = 0;
    return c;
}

void insertList(List* l, char country[], char capital[]) {
    Node* new = malloc(sizeof(Node));

    if (new) {
        strcpy(new->name, country);
        strcpy(new->capital, capital);
        new->next = l->head;
        l->head = new;
        l->size++;
    }
    else printf("error allocating memory");
}

//now, we insert on hash vector
void insertTab(List t[], Node* node) {
    int id = funcHash(node->name);
    insertList(&t[id], node->name, node->capital);
}


void displayList(List* l) {
    Node* aux = l->head;
    printf("Size = %d: ", l->size);
    while(aux) {
        printf("%s - %s -> ", aux->name, aux->capital);
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

Node* searchList(List* l, char name[]) {
    Node* aux = l->head;
    while(aux && (strcmp(aux->name, name)) != 0) aux = aux->next;
    if (aux) return aux;
    return NULL;
}

Node* searchTab(List t[], char name[]) {
    int id = funcHash(name);
    if (id < 0) {
        printf("invalid");
        return NULL;
    }
    return searchList(&t[id], name);
}

void freeList(List* l) {
    Node* current = l->head;
    while (current) {
        Node* next = current->next; //then we do not lost the list
        free(current);
        current = next;
    }
    l->head = NULL;
    l->size = 0;
}

int main() {
    int op, value, output;
    char name[50];
    Node* node;
    List tab[SIZE];

    initializeTab(tab);

    do {
        printf("\n0-exit\n1-insert\n2-search\n3-display\n");
        scanf("%d", &op);
        getchar();

        switch(op) {
            case 1:
                node = inputCountry();
                insertTab(tab, node);
                break;
            case 2:
                printf("which name to search? ");
                fgets(name, 49, stdin);
                name[strcspn(name, "\n")] = 0;
                node = searchTab(tab, name);
                if (node) {
                    printf("%s's capital is: %s", node->name, node->capital);
                }
                else printf("\nnot found\n");
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

/* TIME COMPLEXITY (PIOR CASO)
Insertion:
Hash func: O(1)
On the list head: O(1)
Worst case: O(1)

Search:
Hash calc: O(1)
Worst case all of them are in the same list: O(n)

Display:
To show every element: O(1)

Memory free: O(n) each node

SPACE COMPLEXITY
26 buckets in here
lists vector ocupy O(M), M = size
each node O(N)
total space: O(N + M), usually O(N) whether N >> M
*/
