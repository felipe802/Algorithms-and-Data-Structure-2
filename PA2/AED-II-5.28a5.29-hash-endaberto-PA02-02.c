#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define VAZIO  "!!!!!!!!!!"
#define RETIRADO  "**********"
#define M  7
#define N  11   /* Tamanho da chave */

typedef unsigned int TipoApontador;
typedef char TipoChave[N];
typedef unsigned TipoPesos[N];
typedef struct {
  TipoChave Chave;
} TipoItem;
typedef unsigned int TipoIndice;
typedef TipoItem TipoDicionario[M];
TipoDicionario Tabela;
TipoPesos p;
TipoItem Elemento;
FILE *arq;
int j, i;

void GeraPesos(TipoPesos p) {
  int i; struct timeval semente;
  gettimeofday(&semente,NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
     p[i] = 1 + (int) (10000.0 * rand()/(RAND_MAX + 1.0));
}

TipoIndice h(TipoChave Chave, TipoPesos p) {
  int i; unsigned int Soma = 0; int comp = strlen(Chave);
  for (i = 0; i < comp; i++)
    Soma += (unsigned int)Chave[i] * p[i];
  return (Soma % M);
}

void Inicializa(TipoDicionario T) {
  int i;
  for (i = 0; i < M; i++) memcpy(T[i].Chave, VAZIO, N);
} 

TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T) {
  unsigned int  i = 0; unsigned int  Inicial;
  Inicial = h(Ch, p);
  while (strcmp(T[(Inicial + i) % M].Chave,VAZIO) != 0 &&
         strcmp (T[(Inicial + i) % M].Chave, Ch) != 0 && i < M) 
    i++;
  if (strcmp( T[(Inicial + i) % M].Chave, Ch) == 0)  
    return ((Inicial + i) % M);
  else return M;  /* Pesquisa sem sucesso */
} 

void Insere(TipoItem x, TipoPesos p, TipoDicionario T) {
  unsigned int i = 0; unsigned int Inicial;
  if (Pesquisa(x.Chave, p, T) < M) {
    printf("Elemento ja esta presente\n"); return;
  }
  Inicial = h(x.Chave, p);
  while (strcmp(T[(Inicial + i) % M].Chave,VAZIO) != 0 &&
         strcmp(T[(Inicial + i) % M].Chave, RETIRADO) != 0 && i < M) 
     i++;
  if (i < M) 
    strcpy(T[(Inicial + i) % M].Chave, x.Chave);
  else printf(" Tabela cheia\n");
} 

void Retira(TipoChave Ch, TipoPesos p, TipoDicionario T) {
  TipoIndice i;
  i = Pesquisa(Ch, p, T);
  if (i < M) 
    memcpy(T[i].Chave, RETIRADO, N);
  else printf("Registro nao esta presente\n");
} 

void Imprime(TipoDicionario tabela) {
  int  i, j, tam;
  for (i = 0; i < M; i++) {
    printf("%d  ", i);
    tam = strlen(tabela[i].Chave);
    for (j = 0; j < tam; j++)
      putchar(tabela[i].Chave[j]);
    putchar('\n');
  }
}

void LerPalavra(char *p, int Tam) {
  char c; int i, j;
  fflush(stdin); j=0;
  while (((c=getchar())!='\n') && (j < (Tam - 1))) p[j++]= c;
  p[j] = '\0';
  while(c != '\n') c = getchar();
  for(i = j - 1;(i >= 0 && p[i] == ' ');i--) p[i] = '\0';
}

int main(int argc, char *argv[]) {
  arq = NULL;
  Inicializa(Tabela);
  GeraPesos(p); LerPalavra(Elemento.Chave, N);
  while (strcmp(Elemento.Chave, "aaaaaaaaaa") != 0) {
    Insere(Elemento, p, Tabela);
    LerPalavra(Elemento.Chave, N);
  }
  printf("Tabela apos insercao:\n");
  Imprime(Tabela);
  printf("Pesquisar :  "); LerPalavra(Elemento.Chave, N);
  while (strcmp(Elemento.Chave, "aaaaaaaaaa") != 0) {
    i = Pesquisa(Elemento.Chave, p, Tabela);
    if (i < M) printf("sucesso na posicao %d \n", i);
    else printf("pesquisa sem sucesso \n");
    printf("Pesquisar :  ");
    LerPalavra(Elemento.Chave, N);
  }
  printf("Retirar seguintes chaves:\n");
  LerPalavra(Elemento.Chave, N);
  while (strcmp(Elemento.Chave, "aaaaaaaaaa") != 0) {
    Retira(Elemento.Chave, p, Tabela);
    LerPalavra(Elemento.Chave, N);
  }
  printf("Tabela apos retiradas:\n");
  Imprime(Tabela);
  printf("Inserir de novo os elementos seguintes:\n");
  LerPalavra(Elemento.Chave, N);  
  while (strcmp(Elemento.Chave, "aaaaaaaaaa") != 0) {
    Insere(Elemento, p, Tabela);
    LerPalavra(Elemento.Chave, N);
  }
  printf("Tabela apos novas insercoes:\n");
  Imprime(Tabela);
  if (arq != NULL) fclose(arq);
  return 0;
}

/*
open adressing with linear probing as collisions handling
each table position keep one key
especial flags for occupied slot
space complexity O(m), m = table size
time complexity O(m) worst case, much collisions
*/