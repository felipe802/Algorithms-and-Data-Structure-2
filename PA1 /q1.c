#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
} //KBHIT IS NOT A STANDARD C FUNCTION

int main(void) {
    int x[10];
    int t;
    for (t = 0; t < 10; ++t) x[t] = t;
    for (t = 0; t < 10; ++t) printf("%d ", x[t]);
    printf("\nPress any key to exit...\n");
    do {} while (!kbhit());
    return 0;
}
/*
esse programa apresenta os numeros de 0 a 9 de 1 em 1
entao espera o usuario digitar qualquer tecla para encerrar

as entradas sao um vetor com 10 posicoes e um inteiro t
t assume os valores de 0 ate 9 e entao atribui esses valores 
ao vetor nas respectivas posicoes. cada posicao recebe o valor do 
seu indice.
depois de cada elemento printado eh aguardado o usuario digitar
qualquer tecla

a estrutura de dados eh um array. nao eh um programa recursivo
mas iterativo uma vez que a funcao executa passo a passo e nao 
eh chamada a si mesma.

para atribuir os valores ao array tem-se o tempo O(n) pois cada
elemento eh lido e atribuido. o tamanho é constante logo a complexidade
de tempo eh O(1)

a complexidade de espaco eh O(1) uma vez que n = 10. a entrada 
eh constante
*/
