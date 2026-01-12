#include <stdio.h>
#include <stdlib.h>
//15 elements, double is 30, nearer prime is 29 or 31, then the size can be 31
#define SIZE 31

//initialize all positions with 0s
void initializeTab(int t[]) {
    for (int i = 0; i < SIZE; i++)
        t[i] = 0;
}

//Dispersing hash function, key mod size
int funcHash(int key) {
    return key % SIZE;
}

//element insertion
void insert(int t[], int value) {
    int id = funcHash(value);
    while (t[id] != 0) {
        id = funcHash(id + 1); //linear treatment
    }
    t[id] = value;
    printf("indexed: %d\n", id);
}

//searching function 
int search(int t[], int key) {
    int id = funcHash(key);
    while (t[id] != 0) {
        if (t[id] == key) {
            printf("\nIndex: %d\n", id);
            return t[id];
        }
        else id = funcHash(id + 1);
    }
    return 0;
}

void display(int t[]) {
    int i;
    for (i = 0; i < SIZE; i++) {
        printf("%2d: %d\n", i, t[i]);
    }
}

int main() {
    int op, value, output, tab[SIZE];
    initializeTab(tab);

    do {
        printf("\n0-exit\n1-insert\n2-search\n3-display\n");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("which value to insert? ");
                scanf("%d", &value);
                insert(tab, value);
                break;
            case 2:
                printf("which value to search? ");
                scanf("%d", &value);
                output = search(tab, value);
                if (output != 0) printf("value found!: %d\n", value);
                else printf("value did not found!\n");
                break;
            case 3:
                printf("\n");
                display(tab);
                break;
            default: 
                if (op != 0) printf("invalid option\n");
        }

    } while (op != 0);

    return 0;
}