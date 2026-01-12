// ENCADEAMENTO INTERIOR
// HASH FUNCTION BY DIVISION METHOD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
#define LETTERS 26

typedef struct node {
    char info[30];
    int occupied, next;
} Node;

//hash table: array of nodes (no pointers)
Node info_table[LETTERS];

//simple hash function using the first letter (lowercase)
int hash_index(char* temp) {
    int sum = 0;
    for (int i = 0; i < strlen(temp); i++) {
        sum += temp[i];
    }
    return sum % LETTERS;
}

// insert using interior chaining
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

    //if slot is free, insert here
    if (table[idx].occupied == 0) {
        strcpy(table[idx].info, value);
        table[idx].next = -1;
        table[idx].occupied = 1;
        return;
    }

    //collision: find next free slot
    int prev = idx;
    while (table[prev].next != -1) {
        prev = table[prev].next;
    }

    //find a free slot in the table
    int free_idx = -1;
    for (int i = 0; i < LETTERS; i++) {
        if (table[i].occupied == 0) {
            free_idx = i;
            break;
        }
    }
    if (free_idx == -1) {
        printf("table full! cannot insert %s\n", value);
        return;
    }

    //insert at free slot and update chain
    strcpy(table[free_idx].info, value);
    table[free_idx].next = -1;
    table[free_idx].occupied = 1;
    table[prev].next = free_idx;
}


void search(Node table[], char* key) {
    int idx = hash_index(key);
    while (idx != -1) {
        char* dash = strchr(table[idx].info, '-');
        if (dash) {
            size_t len = dash - table[idx].info;
            //compare only the country part
            if (table[idx].occupied && strncmp(table[idx].info, key, len) == 0 && strlen(key) == len) {
                printf("Found: %s\n", table[idx].info);
                return;
            }
        }
        idx = table[idx].next;
    }
    printf("not found\n");
}


int main() {
    char aux[30];

    //initialize table: all slots free, next = -1
    for (int i = 0; i < LETTERS; i++) {
        info_table[i].occupied = 0;
        info_table[i].next = -1;
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