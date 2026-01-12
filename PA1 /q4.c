#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

// zero will also be empty
void initializeArray(int array[])
{
    for (int i = 0; i < SIZE; i++)
        array[i] = 0;
}

void insert(int array[], int n)
{
    int i;
    int flag = 0;
    for (i = 0; i < SIZE; i++)
    {
        if (array[i] == 0)
        {
            array[i] = n;
            printf("inserted\n");
            flag = 1;
            break; // only the loop will break in here
        }
    }
    if (flag == 0)
        printf("array is full\n");
}

void display(int array[])
{
    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");
}

// subfunction to qsort. divide and conquer!
int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// a binary search works in a ordened vector
void binSearch(int array[], int start, int end, int n)
{
    // working with index
    int flag = 0;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (array[mid] == n)
        {
            printf("value found: %d\nindexed in: %d\n", n, mid);
            flag = 1;
            return;
        }
        if (n < array[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }
    if (flag == 0)
        printf("not found");
}
/*
as quicksort, time complexity is O(n log n) because there is n * O(log n) recursions. binary search is
also O(log n). as n is 10, O(1).
as recursion, extra memory is necessary, the space complexity is O(log n), the array itself if O(n).
(as n is fixed at the beginning and small the space complexiy is O(1) for this program only).
O(n log n) for sorting and O(log n) for searching
space complexity is O(n) for the array
*/

int main()
{
    int op, num;
    int array[SIZE], arr[SIZE];
    initializeArray(array);

    do
    {
        printf("\n1-inserir elemento no array\n2-apresentar array original\n3-informar elemento a ser buscado\n4-sair do programa\n\n");
        scanf("%d", &op);
        switch (op)
        { // time complexity O(1)
        case 1:
            printf("insert a number:\n");
            scanf("%d", &num);
            insert(array, num);
            break;
        case 2:
            display(array);
            break;
        case 3:
            qsort(array, SIZE, sizeof(array[0]), comp);
            printf("what number?\n");
            scanf("%d", &num);
            binSearch(array, 0, SIZE - 1, num);
            break;
        case 4:
            break;
        default:
            if (op != 4)
            {
                printf("invalid\n");
            }
            break;
        }
    } while (op != 4);
    return 0;
}
