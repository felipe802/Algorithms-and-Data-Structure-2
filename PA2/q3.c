//a real ENCADEAMENTO EXTERIOR
//SEPARATE CHINING(EXTERNAL CHINING)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
#define LETTERS 26

typedef struct node {
    char info[30];
    struct node* next;
} Node;

//hash table: array of pointers to node
Node* info_table[LETTERS];

//simple hash function using the first letter (lowercase)
int hash_index(char* temp) {
    return temp[0] - 'a';
}

void insert(Node* table[], char* value) {
    int idx = hash_index(value);
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory error\n");
        exit(1);
    }
    strcpy(new_node->info, value);
    new_node->next = table[idx]; //inserting at the beginnig of the list
    table[idx] = new_node;
}

void search(Node* table[], char* key) {
    int idx = hash_index(key);
    Node* curr = table[idx];
    int found = 0;
    while(curr) {
        char* dash = strchr(curr->info, '-');
        if (dash) {
            size_t len = dash - curr->info;
            if (strncmp(curr->info, key, len) == 0 && strlen(key) == len) {
                printf("Found: %s\n", curr->info);
                found = 1;
            }
        }
        curr = curr->next;
    }
    if (!found) printf("not found\n");
}

//free all allocated memory
void free_table(Node* table[]) {
    for (int i = 0; i < LETTERS; i++) {
        Node* curr = table[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        table[i] = NULL;
    }
}

int main() {
    char aux[30];

    //initialize table
    for (int i = 0; i < LETTERS; i++) info_table[i] = NULL;

    //insert entries
    printf("\nenter %d country-capital pairs (e.g., brazil-brasilia):\n", MAX);
    for (int i = 0; i < MAX; i++) {
        printf("entry %d: ", i+1);
        scanf(" %29s", aux);
        insert(info_table, aux);
    }

    //search
    char op = 'c';
    while(op == 'c' || op == 'C') {
        printf("\nenter the country to search: ");
        scanf(" %29s", aux);
        search(info_table, aux);
        printf("\ntype 'c' for a new search or any other key to exit: ");
        scanf(" %c", &op);
        while(getchar() != '\n'); //clear buffer
    }

    //free memory
    free_table(info_table);
    return 0;
}