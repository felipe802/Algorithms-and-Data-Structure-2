/*
A PHONE LIST. as hash table, I chose separate chaining
the key will be the name. the hash function is the first two letters
table size SIZE = 26 * 26 = 676, 676 * 2 = 1352, nearest prime is 1361
firstly it will insert on hash table. secondly it will pass all data to 
the FILE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1361
#define NAME_SIZE 50
#define PHONE_SIZE 20


// define a node for separate chaining
typedef struct node {
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    struct node* next;
} Node;

//hash table: array of pointers to linked lists
Node* hashTable[TABLE_SIZE];

// hash function based on the first two letters of the name
int hashFunction(char* name) {
    int first = toupper(name[0]) - 'A';
    int second = toupper(name[1]) - 'A';
    return (first * 26 + second) % TABLE_SIZE;
}

// initialize hash table
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// insert a record into the hash table
void insert(char* name, char* phone) {
    int index = hashFunction(name);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}


// search for a name or phone number
Node* search(char* key) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            if (strcmp(current->name, key) == 0 || strcmp(current->phone, key) == 0) 
                return current;
            current = current->next;
        }
    }
    return NULL;
}


// remove a record
int removeEntry(char* key) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        Node* prev = NULL;
        while (current != NULL) {
            if (strcmp(current->name, key) == 0 || strcmp(current->phone, key) == 0) {
                if (prev == NULL) 
                    hashTable[i] = current->next;
                else    
                    prev->next = current->next;
                free(current);
                return 1; //success
            }
            prev = current;
            current = current->next;
        }
    }
    return 0; //not found
}


// save hash table to file
void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("file open failed");
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            fwrite(current, sizeof(Node), 1, file);
            current = current->next;
        }
    }
    fclose(file);
}


// load data from file
void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return;

    Node temp;
    while(fread(&temp, sizeof(Node), 1, file)) {
        insert(temp.name, temp.phone);
    }
    fclose(file);
}

// print hash table (for debugging)
void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        if (current) {
            printf("Index %d:\n", i);
            while(current != NULL) {
                printf(" Name: %s, Phone: %s\n", current->name, current->phone);
                current = current->next;
            }
        }
    }
}


// example usage
int main() {
    initializeTable();
    loadFromFile("phonebook.dat");

    insert("alice", "1234");
    insert("bob", "5678");
    insert("carol", "91011");

    Node* found = search("bob");
    if (found) printf("found: %s - %s\n", found->name, found->phone);
    else printf("not found\n");
    
    removeEntry("alice");

    saveToFile("\nphonebook.dat");
    printTable();

    return 0;
}

/*
for big data, indexed files or direct access(hash table) are better than
sequential or indexed sequential

TIME COMPLEXITY: O(1) for insert/remove/search
worst case O(n)

SPACE COMPLECITY: O(n), where n is the number of entries(here, each node)

for the file direclty on DISK, usually 1 access, 1 reading, 1 writing per operation
only in-memory hash table there is no file access 

for more than 10 million entries, consider disk-based indexing or splitting the data
*/