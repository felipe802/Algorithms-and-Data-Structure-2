#include <stdio.h>
#define SIZE 10

int main() {
    int i;
    FILE* pa;
    float saldo[SIZE];

    // open file for writing in binary code
    if ((pa = fopen("saldo", "wb")) == NULL) {
        printf("could not open the file\n");
        return 1;
    }

    // fill the array with values
    for (i = 0; i < SIZE; i++) saldo[i] = (float)i;
    
    // save the entire array in one step
    fwrite(saldo, sizeof(saldo), 1, pa);
    fclose(pa);

    // reset the array 
    for (i = 0; i < SIZE; i++) saldo[i] = 0.0;

    // open file for reading in binary code
    if ((pa = fopen("saldo", "rb")) == NULL) {
        printf("could not open the file\n");
        return 1;
    }

    // read the entire array in one step
    fread(saldo, sizeof(saldo), 1, pa);

    // display the contents of the array
    for (i = 0; i < SIZE; i++) printf("%f\n", saldo[i]);
    printf("\n");

    fclose(pa);
    return 0;
}

/*
fills an array of SIZE floats with values from 0 to 99
writes the entire array to a binary file called saldo
resets the array to zeros
reads the array back from the file
prints the array values

no user inputs
print the numbers 0.000000 to 9.000000 separate by lines


time complexity O(n) to write each number
space complexity O(n) for the float array
*/