#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct queue {
    int data[SIZE]; //elements themeslves
    int head, tail; //[0, 0, 2(head), 3, 4, 0(tail), 0]
} Queue;

//ALL CODE USE CIRCULAR VERSION, (n + 1) % SIZE
void initializeQueue(Queue* q) {
    for (int i = 0; i < SIZE; i++) q->data[i] = 0;
    q->head = 0; //as index
    q->tail = 0; //check in here
}

int isEmpty(Queue* q) {
    return q->head == q->tail; //return 1 if true
}

int isFull(Queue* q) { 
    return ((q->tail + 1) % SIZE) == q->head; //return 1 if true
}

void enqueue(Queue* q, int n) {
    if (isFull(q)) printf("overflow!\n");
    else {
        q->data[q->tail] = n;
        printf("inserted!\n");
        q->tail = (q->tail + 1) % SIZE;
    }
}

int dequeue(Queue* q) { 
    if (isEmpty(q)) {
        printf("underflow\n");
        return -1;
    }
    int val = q->data[q->head];
    q->head = (q->head + 1) % SIZE;
    return val;
}//we lost the value, but we do not delete exactly


void display(Queue* q) {
    int i = q->head;
    while (i != q->tail) {
        printf("%d ", q->data[i]);
        i = (i + 1) % SIZE;
    }
    printf("\n");
}


void separateEvenOdd(Queue* Q1, Queue* Q2) {
    Queue aux;
    initializeQueue(&aux);

    while(!isEmpty(Q1)) enqueue(&aux, dequeue(Q1));

    while(!isEmpty(&aux)) {
        int val = dequeue(&aux);
        if (val % 2 == 0) enqueue(Q2, val);
        else enqueue(Q1, val);
    }
}


int main()
{
    int op, num;
    Queue Q1, Q2;
    initializeQueue(&Q1);
    initializeQueue(&Q2);

    do {
        printf("\n1-Inserir elemento na fila\n2-Apresentar fila F1 original;\n3-Apresentar a fila F1 após a remoção dos números pares;\n4-Apresentar a fila F2 após a inserção dos elementos pares;\n5-Sair do programa\n\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("insert a number:\n");
                scanf("%d", &num);
                enqueue(&Q1, num);
                break;
            case 2:
                printf("original F1:\n");
                display(&Q1);
                break;
            case 3: 
                separateEvenOdd(&Q1, &Q2);
                printf("F1 without evens:\n");
                display(&Q1);
                break;
            case 4: 
                printf("F2 with evens:\n");
                display(&Q2);
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
time complexity: O(n) to read each and insert into aux
O(n) separate evens and odds for each pass
2n -> O(2n) = O(n) in general
(only one insertion is O(1))

space complexity: O(n) to alocate the auxiliary queue
*/