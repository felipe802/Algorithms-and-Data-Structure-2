#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 8

//zero will also be empty
void initializeArray(int array[]) {
    for (int i = 0; i < SIZE; i++) array[i] = 0;
}


void insert(int array[], int n) {
    int i;
    int flag = 0;
    for (i = 0; i < SIZE; i++) {
        if (array[i] == 0) {
            array[i] = n;
            printf("inserted\n");
            flag = 1;
            break; //only the loop will break in here
        }
    }
    if (flag == 0) printf("array is full\n");
}


// 2 3 4 5
// 5 3 4 2
// 5 4 3 2
void invert(int array[], int start, int end) {
    //working with the index
    if (start >= end) return;
    int aux;
    if (start < end) {
        aux = array[end];
        array[end] = array[start];
        array[start] = aux;
    }
    /*
    invert(array, start++, end++);
    it means, pass the current value of start, THEN increment start
    after the value is used.
    the increment has no effect on the next call
    it keeps passing the same values again and again, leading
    to infinite recursion->stack overflow->core dumped
    */
   invert(array, start + 1, end - 1);

}


void display(int array[]) {
    for (int i = 0; i < SIZE; i++) 
        printf("%d ", array[i]);
    printf("\n");
}


int main() {
    int op, num;
    int array[SIZE], arr[SIZE];
    initializeArray(array);

    do {
        printf("\n1-inserir elemento no array\n2-apresentar array original\n3-apresentar array invertido\n4-sair do programa\n\n");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("insert a number:\n");
                scanf("%d", &num);
                insert(array, num);
                break;
            case 2:
                display(array);
                break;
            case 3:
                memcpy(arr, array, SIZE * sizeof(int));
                invert(arr, 0, SIZE-1);
                display(arr);
                break;
            case 4:
                break;
            default:
            if (op != 4) {
                printf("invalid\n");
            }
                break;
        }
    } while (op != 4);
    return 0;
}

/*
TIME COMPLEXITY is O(1) constant because the input is defined
at first. but loop to invert is considered because it is recursion O(n)
there are n/2 swaps, so the time compexity will be O(n).
the same for space complexity, each call is O(1) but all happens
at the same time, we have n/2 calls and O(n)

if this code would be iterative, at any given time:
i: loop index
aux: for swapping
for any n elements the 2 integers variables are always the same
SPACE COMPLEXITY measures how much extra memory your algorithm 
uses as the input grows. in this case the memory usage doesn't grow 
with input size

the inputs are only the values and are also the output, the n is
provided at the beginning
*/