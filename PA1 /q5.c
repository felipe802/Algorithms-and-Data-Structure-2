#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

//we do not use pointers for array 
typedef struct stack {
    int top; //AN INDEX, we did a struct only for this information
    int data[SIZE]; //the array itself 
} Stack;


void initializeStack(Stack* s) {
    for (int i = 0; i < SIZE; i++) s->data[i] = 0;
    s->top = -1; //as index
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == SIZE - 1;
}

void push(Stack* s, int n) {
    if (isFull(s)) printf("overflow!\n");
    else {
        s->top = s->top + 1;
        s->data[s->top] = n;
        //s->data[++(s->top)] = n
        printf("inserted!\n");
    }
}

int pop(Stack* s) { //only pop. 
    if (isEmpty(s)) {
        printf("underflow\n");
        return -1;
    }
    /*int aux = s->data[s->top];    // 3, 2, 1
    s->data[s->top] = 0;          // 3, 2
    s->top--;
    return aux;
    */
    return s->data[(s->top)--]; 
    //return the value and decrement the top
}

void display(Stack* s) {
    printf("\n");
    for (int i = s->top; i >= 0; i--) //from top to the base 7 to 0
        printf("%d\n", s->data[i]);
    printf("\n");
}

/*
void transfer1(Stack* P1, Stack* P2, Stack* Ptemp) { //the first step
    while(P1->top != -1) {
        int x = pop(P1);
        if (x % 2 == 0) { //evens
            push(Ptemp, x);
        }
        else { //odds
            push(P2, x);
        }
    }
}
void transfer2(Stack* P1, Stack* P2, Stack* Ptemp) { //the second and last step
    int x;
    while (P2->top != -1) {
        x = pop(P2);
        push(P1, x);
    }
    while (Ptemp->top != -1) {
        x = pop(Ptemp);
        push(P2, x);
    }
}  
*/

void separateEvenOdd(Stack* P1, Stack* P2) {
    Stack aux;
    initializeStack(&aux);

    //firt invert P1 to aux and preserve the insertion order
    while(!isEmpty(P1)) push(&aux, pop(P1));

    //second: separete even and odds
    while(!isEmpty(&aux)) {
        int val = pop(&aux);
        if (val % 2 == 0) push(P2, val);
        else push(P1, val);
    }
}

int main()
{
    int op, num;
    Stack P1, P2;
    initializeStack(&P1);
    initializeStack(&P2);

    do {
        printf("\n1-inserir elemento na pilha\n2-Apresentar pilha P1 original\n3-Apresentar a pilha P1 após a remoção dos números pares\n4-Apresentar a pilha P2 após a inserção dos elementos pares\n5-Sair do programa\n\n");
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("insert a number:\n");
            scanf("%d", &num);
            push(&P1, num);
            break;
        case 2:
            printf("original P1:\n");
            display(&P1);
            break;
        case 3: 
            separateEvenOdd(&P1, &P2);
            printf("P1 without evens:\n");
            display(&P1);
            break;
        case 4: 
            printf("P2 with evens:\n");
            display(&P2);
            break;
        case 5:
            break;
        default:
            if (op != 5) printf("invalid\n");
            break;
        }
    } while (op != 5);
    return 0;
}


/*
time complexity: n calls of pop and push, after n pop and push inside the separate, O(2n) = O(n)       real life O(1) in here
space complexity: O(n) to allocate a P1 copy                                                           real life also O(1)
*/