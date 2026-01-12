#include <stdio.h>

long fatorial(long n);

int main() {
    long num, total;
    printf("informe o numero a ser calculado o N!:\n");
    scanf("%ld", &num);
    total = fatorial(num);
    printf("N! de %ld = %ld\n", num, total);
    printf("press enter to exit...");
    getchar(); //consume leftover newline
    getchar(); //wait for enter
    return 0;
}

long fatorial(long n) {
    if (n <= 1) return 1;
    return n * fatorial(n - 1);
}

/*
the inputs are only the number provide by the user
this program calculates the fatorial of any number
this is a recursive program because the function call itself 
to calculate 

time complexity depends of the provide number because the stack
wait the next number, increase with n. O(n)

space complexity is the size of input, O(n) because each new number
is stored. O(n)
*/