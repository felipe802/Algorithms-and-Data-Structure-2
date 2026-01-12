#include <stdio.h>
#include <stdlib.h>
#define SIZE 9
//i can write a hash table(much faster) or a iterative version (O(n²))
//the hash func could start by mod SIZE
//first version will be iterative

void initializeArr(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = 0;
    }
}

int find_mode(int array[], int* count) {
    int max_count = 0, mode = 0;
    for (int i = 0; i < SIZE; i++) {
        int curr_count = 0;
        for (int j = 0; j < SIZE; j++) {
            if (array[j] == array[i]) curr_count++;
        }
        if (curr_count > max_count) {
            max_count = curr_count;
            mode = array[i];
        }
    }
    *count = max_count;
    return mode;
}


void insert(int array[], int n) {
    for (int i = 0; i < SIZE; i++) {
        if (array[i] == 0) {
            array[i] = n;
            break;
        }
    }
}

void display(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int op, num;
    int array[SIZE];
    initializeArr(array);


    do {
        printf("\n1-Inserir elemento no array\n2-Apresentar array\n3-Apresentar a moda e quantas vezes aparece\n4-Sair do programa\n\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("insert a number:\n");
                scanf("%d", &num);
                insert(array, num);
                break;
            case 2:
                display(array);
                break;
            case 3: 
                int count;
                int mode = find_mode(array, &count);
                printf("the mode is %d and appears %d times\n", mode, count);
                break;
            case 4:
                break;
            default:
                if (op != 4) printf("invalid\n");
                break;
        }
    } while (op != 4);
    return 0;
}


/*
time complexity: read each value and compare, two loops: O(n²)
this function domains the program
display O(n)
insert O(1)

space complexity: no extra memory necessary: O(1);
everything is already fixed
*/