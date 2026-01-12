/*
ENCADEAMENTO EXTERIOR: there is no colisons handling.
outside structures as lists.
*/

#include <stdio.h>
#include <string.h>
#define MAX 5 // # country-capital combinations
#define LETTERS 26 // # letters from alphabet

//simple hash function using the first letter
int hash_index(char* temp) {
    return (temp[0] - 'a'); // 'a' = 97 in ASCII  slot 1 for brazil-capital -> 'b' - 'a' = 1
}

//hash table struct
struct table {
    char info[30];
} info_table[LETTERS];

int main(void) {
    int i, j;
    int flag;
    char aux[30];

    printf("hash table to store country and capital\n");
    printf("no collisions handling\n");

    //initialization
    for (i = 0; i < LETTERS; i++) {
        strcpy(info_table[i].info, "not filled yet");
    }

    printf("data entry...\n\n");
    printf("follow this format: country-capital (five entries)\n");

    //insert country-capital strings
    for (i = 0; i < MAX; i++) {
        printf("enter info %d: ", i+1);
        scanf(" %29s", aux); //limit input to avoid overflow
        j = hash_index(aux);
        strcpy(info_table[j].info, aux);
        printf("\n");
    }

    //search mode
    flag = 1;
    while(flag == 1) {
        printf("enter the country you want to know the capital of: ");
        scanf (" %29s", aux);
        j = hash_index(aux);
        printf("\ncountry-capital: %s\n", info_table[j].info);
        printf("hash table index: %d\n", j);

        printf("type c (new search) or any other key to exit: ");
        scanf(" %29s", aux);
        if (aux[0] == 'C' || aux[0] == 'c') {
            flag = 1;
        }
        else {
            flag = 0;
        }
        printf("\n");
    }
    return 0;
}

/*
this code is a hash table that keeps the name of country-capital
the hash table takes the country's first letter minus 97. the array has 26 slots
one for each alphabet letter
there is no collisions handling and the second country with the same first letter
overwrite the first name. the inputs are the countries. after all the user can search
by the first letter and see its capital
the data structure is a hash table
it is not a recursive program.

the time complexity is for the array index: O(1) because n is fixed
we do not have linked list or array to keep the informations. we
do not have inside or outside treatment, because we do not have collisions handling but 
overwriting. 

space complexity is O(n) where n is 26 for the countries name -> O(1)
*/