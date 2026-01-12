/*
eu escolho o sequencial indexado, pois:
1. nao existem tantos dados para que sejam implementados arquivos indexados ou
de acesso direto
2. Nao eh bom implementar um do tipo sequencial pois podem haver muitas alteracoes
(como aumento de salario), e esse tipo de arquivo se torna ineficiente
3. dado que as chaves primarias se tornam as faixas de valores dos grupos correspontes,
o tipo sequencial indexado se torna bem vindo
*/

#include <stdio.h>
#include <string.h>
#define TOTAL_FUNC 1500
#define CATEGORIAS 4
#define NIVEIS 6

typedef struct {
    char nome[3];
    int quantidade;
    double salario_base;
    double salarios[NIVEIS];
} Categoria;

int main() {
    Categoria categorias[CATEGORIAS] = {
        {"C1", 0, 0, {0}},
        {"C2", 0, 0, {0}},
        {"C3", 0, 0, {0}},
        {"C4", 0, 39500.00, {0}} // Only C4 has known base salary
    };

    // Distribuição dos funcionários entre as categorias
    categorias[0].quantidade = TOTAL_FUNC * 0.4;  // C1: 40%
    categorias[1].quantidade = TOTAL_FUNC * 0.3;  // C2: 30%
    categorias[2].quantidade = TOTAL_FUNC * 0.2;  // C3: 20%
    categorias[3].quantidade = TOTAL_FUNC * 0.1;  // C4: 10%

    // Cálculo dos salários de cada nível e base das categorias
    for (int i = CATEGORIAS - 1; i >= 0; i--) {
        categorias[i].salarios[0] = categorias[i].salario_base;
        for (int n = 1; n < NIVEIS; n++) {
            categorias[i].salarios[n] = categorias[i].salarios[n - 1] * 1.10; // aumento de 10% por nível
        }
        // Atualiza o salário base da categoria anterior
        if (i > 0) {
            categorias[i - 1].salario_base = categorias[i].salarios[NIVEIS - 1] * 1.10;
        }
    }

    // Exibe a tabela de salários
    printf("Tabela de salários por categoria e nível:\n");
    for (int i = 0; i < CATEGORIAS; i++) {
        printf("\nCategoria %s (Funcionários: %d):\n", categorias[i].nome, categorias[i].quantidade);
        for (int n = 0; n < NIVEIS; n++) {
            printf("  Nível %d: R$ %.2f\n", n + 1, categorias[i].salarios[n]);
        }
    }

    return 0;
}



/*
time complexity:
o algoritmo principal é dominado pelos loops para calcular salarios, ambos
de tamaho fixo (4 categ * 6 niveis) = O(1)

space complexity:
como o numero de categorias é fixo, O(1)
*/


