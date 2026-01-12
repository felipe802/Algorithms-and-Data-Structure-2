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
    unsigned int sum = 0;
    int group = 0;
    int count = 0;
    for (int i = 0; temp[i] != '\0'; i++) {
        group = group * 256 + (unsigned char)temp[i];
        count++;
        if (count == 4) {
            sum += group;
            group = 0;
            count = 0;
        }
    }
    if (count > 0) {
        sum += group;
    }
    return sum % LETTERS;
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

/*
for open adressing (linear, quadratic, folding, multiplication), space complexity
is O(m) where m is the table size
no extra space is used for pointers or linked lists (unlike chaining)

average-case search/insert/delete: O(1) if the load factor is low and the hash 
function distributes keys well
worst-case: O(m) if there are many collisions (e.g., poor hash function, high load
factor)

multiplication and folding methods both compute a hash in O(L) time, where L is 
the lenght of the string key
the quality of the hash function affects the number of collisions, which impacts
the average-case time

summary:
open adressing (any):
space complexity o(m), average time O(1), worst time O(m)

chaining:
space complexity O(m + n), average time O(1), worst time O(n)
*/