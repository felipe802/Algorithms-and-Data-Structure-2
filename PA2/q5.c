// OPEN ADRESSING, LINEAR PROBING
// HASH FUNCTION BY MULTIPLICATION METHOD
//h(k) = floor(m * ( (k * A) mod 1) ), where A is a constant between 0 and 1
//instead of chaining, on colision, you probe the next slot

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
#define LETTERS 26

typedef struct node {
    char info[30];
    int occupied;
} Node;

//hash function using multiplication method
int hash_index(char* temp) {
    unsigned int k = 0;
    for (int i = 0; temp[i] != '\0'; i++) 
        k = k * 31 + temp[i]; //simple string to int
    double A = 0.6180339887; // sugested constant
    double frac = (k * A) - (int)(k * A);
    return (int)(LETTERS * frac);
}

// insert using open adressing (linear probing)
void insert(Node table[], char* value) {
    // Extract country part
    char country[30];
    char* dash = strchr(value, '-');
    if (dash) {
        size_t len = dash - value;
        strncpy(country, value, len);
        country[len] = '\0';
    } else {
        strcpy(country, value);
    }

    int idx = hash_index(country);
    int start_idx = idx; // circular array
    do {
       if (table[idx].occupied == 0) {
            strcpy(table[idx].info, value);
            table[idx].occupied = 1;
            return;
       }
       idx = (idx + 1) % LETTERS;
    } while (idx != start_idx);

   printf("table full! cannot insert %s\n", value);
}

//search using open adressing (linear probing)
void search(Node table[], char* key) {
    int idx = hash_index(key);
    int start_idx = idx;
    do {
        if (table[idx].occupied) {
            char* dash = strchr(table[idx].info, '-');
            if (dash) {
                size_t len = dash - table[idx].info;
                if (strncmp(table[idx].info, key, len) == 0 && strlen(key) == len) {
                    printf("found: %s\n", table[idx].info);
                    return;
                }
            }
        } else {
            //if we hit an empty slot, key is not present
            break;
        }
        idx = (idx + 1) % LETTERS;
    } while (idx != start_idx);

    printf("not found\n");
}


int main() {
    Node info_table[LETTERS];
    char aux[30];

    //initialize table: all slots free
    for (int i = 0; i < LETTERS; i++) {
        info_table[i].occupied = 0;
    } 

    //insert entries
    printf("\nenter %d country-capital pairs (e.g., brazil-brasilia):\n", MAX);
    for (int i = 0; i < MAX; i++) {
        printf("entry %d: ", i+1);
        scanf(" %29s", aux);
        insert(info_table, aux);
    }

    //search loop
    char op = 'c';
    while(op == 'c' || op == 'C') {
        printf("\nenter the country to search: ");
        scanf(" %29s", aux);
        search(info_table, aux);
        printf("\ntype 'c' for a new search or any other key to exit: ");
        scanf(" %c", &op);
        while(getchar() != '\n'); //clear buffer
    }

    return 0;
}