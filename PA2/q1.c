#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    int size;
} List;

void createLL(List* l) {
    l->head = NULL;
    l->size = 0;
}

void insert(List* l, int n) {
    Node* new = malloc(sizeof(Node));
    if (new) {
        new->info = n;
        new->next = l->head;
        l->head = new;
        l->size++;
    }
    else {
        printf("error");
        exit(1);
    }
}

void displayLL(List l) {
    Node* node = l.head;
    printf("list size: %d\n", l.size);
    while(node) {
        printf("%d ", node->info);
        node = node->next;
    }
    printf("\n");
}

void freeLL(List* l) {
    Node* current = l->head;
    Node* next;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    l->head = NULL;
    l->size = 0;
}


int main() {
    int op, num;
    List l;
    createLL(&l);

    do {
        printf("\n1-insert element\n");
        printf("2-display list\n");
        printf("3-free memory\n");
        printf("4-exit\n\n");
        scanf("%d", &op);

        switch(op) {
            case 1:
                scanf("%d", &num);
                insert(&l, num);
                break;
            case 2:
                displayLL(l);
                break;
            case 3:
                freeLL(&l);
                break;
            default:
                if (op != 4) printf("invalid");
                break;
        }

    } while (op != 4);

    return 0;
}

/*
time complexity: insert O(1), display O(n)

space complexity: O(n) where n is the number of elements
*/