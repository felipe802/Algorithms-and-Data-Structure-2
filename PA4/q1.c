#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // para INT_MAX
#include <time.h>
// constantes e variaveis globais

#define K_PATHS 3  // numero de caminhos para a intercalacao 
#define BLOCK_SIZE 10 // tamanho do bloco para ordenacao interna(simples, ajuste conforme N e memória)
#define NUM_FILES 2 * K_PATHS // numero total de arquivos auxilares (k para leitura, k para escrita)

// nomes dos arquivos auxiliares
const char* aux_filenames[] = {
    "aux_0.txt", "aux_1.txt", "aux_2.txt",
    "aux_3.txt", "aux_4.txt", "aux_5.txt" // para k = 3, precisamos de 6 arquivos
};

// funcoes auxiliares

// funcao para gerar um arquivo de entrada com numeros aleatorios
void generate_input_file(const char* filename, int num_elements) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Erro ao criar arquivo de entrada");
        exit(EXIT_FAILURE);
    }
    printf("Gerando %d elementos aleatorios em %s...\n", num_elements, filename);
    srand(time(NULL)); // inicializa o gerador de numeros aleatorios
    for (int i = 0; i < num_elements; i++) {
        fprintf(f, "%d\n", rand() % 10000); // numeros aleatorios enntre 0 e 9999
    }
    fclose(f);
}


// funcao de comparacao para qsort
int compare_integers(const void* a, const void* b){
    return (*(int *)a - *(int *)b);
}

// fase 1: criacao de blocos (runs) iniciais
void create_initial_run(const char* input_filename) {
    FILE* input_file = fopen(input_filename, "r");
    if (!input_file) {
        perror("Erro ao abrir arquivo de entrada para runs");
        exit(EXIT_FAILURE);
    }

    // abre os primeiros K_PATHS arquivos auxiliares para escrita
    FILE* output_files[K_PATHS];
    for (int i = 0; i < K_PATHS; i++) {
        output_files[i] = fopen(aux_filenames[i], "w");
        if (!output_files[i]) {
            perror("Erro ao abrir arquivo auxiliar para escrita (runs)");
            exit(EXIT_FAILURE);
        }
    }

    int* buffer = (int *)malloc(sizeof(int) * BLOCK_SIZE);
    if (!buffer) {
        perror("Erro de alocacao de memoria para buffer");
        exit(EXIT_FAILURE);
    }

    int current_file_idx = 0;
    int elements_read;

    printf("Fase 1: criando blocos iniciais ordenados...\n");
    while (1) {
        elements_read = 0;
        // le um bloco de elementos
        for (int i = 0; i < BLOCK_SIZE; i++) {
            if (fscanf(input_file, "%d", &buffer[i]) == 1) {
                elements_read++;
            } else {
                break; // fim do arquivo ou erro de leitura
            }
        }

        if (elements_read == 0) {
            break; // todos os elementso foram lidos
        }

        //ordena o bloco na memoria
        qsort(buffer, elements_read, sizeof(int), compare_integers);

        // escreva o bloco ordenado no arquivo auxiliar correspondente
        for (int i = 0; i < elements_read; i++) {
            fprintf(output_files[current_file_idx], "%d\n", buffer[i]);
        }
        // adiciona uma linha vazia para separar os runs (para facilitar a leitura na intercalacao)
        // isso assume que nao teremos INT_MAX nos dados
        fprintf(output_files[current_file_idx], "%d\n", INT_MAX);

        // alterna para o proximo arquivo auxiliar
        current_file_idx = (current_file_idx + 1) % K_PATHS;
    }

    free(buffer);
    fclose(input_file);
    for (int i = 0; i < K_PATHS; i++) {
        fclose(output_files[i]);
    }
    printf("fase 1 concluida. \n");
}


//fase 2: intercalacao multi_caminhos
void merge_pass(FILE* input_files[], FILE* output_files[], int num_input_files) {
    // buffers para os elementos atuais de cada arquivo de entrada
    int current_elements[K_PATHS];
    // flags para indicar se o arquivo de entrada correspondente terminou um run ou o arquivo inteiro
    int end_of_run[K_PATHS];
    int end_of_file[K_PATHS];

    // inicializa todos os buffers com o primeiro elemento de cada arquivo ou INT_MAX se vazio
    for (int i = 0; i < num_input_files; i++) {
        end_of_run[i] = 0;
        end_of_file[i] = 0;
        if (fscanf(input_files[i], "%d", &current_elements[i]) != 1) {
            current_elements[i] = INT_MAX; // arquivo vazio ou erro
            end_of_file[i] = 1;
        }
    }

    int output_file_idx = 0;
    int active_input_files = num_input_files;

    while (active_input_files > 0) {
        int min_val = INT_MAX;
        int min_idx = -1;

        // encontra o menor elemento entre os ativos
        for (int i = 0; i < num_input_files; i++) {
            if (current_elements[i] < min_val) {
                min_val = current_elements[i];
                min_idx = i;
            }
        }

        // se o menor valor eh INT_MAX, significa que todos os runs atuais terminaram
        // ou que todos os arquivs de entrada terminaram
        if (min_val == INT_MAX) {
            // avanca para o proximo arquivo de saida para iniciar um novo run
            output_file_idx = (output_file_idx + 1) % K_PATHS;

            // reinicia os indicadores de fim de run para os arquivos que ainda tem dados
            for (int i = 0; i < num_input_files; i++) {
                if (current_elements[i] == INT_MAX && !end_of_file[i]) {
                    // se INT_MAX foi lido (indicando fim de run), tenta ler o proximo
                    // se o proximo tambem for INT_MAX, entao o arquivo terminou, caso contrario, eh um novo run
                    if (fscanf(input_files[i], "%d", &current_elements[i]) != 1) {
                        current_elements[i] = INT_MAX; // arquivo realmente terminou
                        end_of_file[i] = 1;
                        active_input_files--;
                    } else if (current_elements[i] == INT_MAX) { // outro INT_MAX consecutivo
                        end_of_file[i] = 1; // considera o arquivo terminado
                        active_input_files--;
                    }
                }
                end_of_run[i] = 0; // reinicia para o proximo run
            }
            continue; // tenta encontrar o menor novamente
        }

        // escreve o menor elemento no arquivo de saida atual
        fprintf(output_files[output_file_idx], "%d\n", min_val);

        // le o proximo elemento do arquivo de onde o menor veio
        if (fscanf(input_files[min_idx], "%d", &current_elements[min_idx]) != 1) {
            current_elements[min_idx] = INT_MAX; // fim do arquivo 
            end_of_file[min_idx] = 1;
            active_input_files--;
        } else if (current_elements[min_idx] == INT_MAX) {
            // se leu INT_MAX, significa fim de um run no arquivo
            end_of_run[min_idx] = 1;
            // nao decrementa active_input_files ainda, pois pode ter mais runs no mesmo arquivo
        }
    }
}


// funcao principal de ordenacao externa
void external_sort(const char* input_filename, const char* output_filename) {
    // fase 1: criacao de blocos iniciais ordenados
    create_initial_run(input_filename);

    int current_read_offset = 0; // 0 para files 0, 1, 2; K_PATHS para files 3, 4, 5
    int current_write_offset = K_PATHS;  // K_PATHS para files 3, 4, 5; 0 para files 0, 1, 2

    int total_runs = -1; // usado para determinar quando parar (1 run final)

    printf("fase 2: intercalacao de multiplos caminhos...\n");
    while(total_runs != 1) { //continua intercalando ate ter apenas 1 run
        FILE* input_files[K_PATHS];
        FILE* output_files[K_PATHS];

        // abre os arquivos de entrada e saida para esta passagem
        for (int i = 0; i < K_PATHS; i++) {
            input_files[i] = fopen(aux_filenames[current_read_offset + i], "r");
            if (!input_files[i]) {
                // se o arquivo nao existir, significa que ele nao foi usado na passagem anterior
                // ou esta vazio. trate como um arquivo "vazio" com INT_MAX para continuar
                input_files[i] = fopen (aux_filenames[current_read_offset + i], "w"); // cria se nao existe
                if (!input_files[i], "%d\n", INT_MAX); // marca como vazio
                rewind(input_files[i]);
            }

            output_files[i] = fopen(aux_filenames[current_write_offset + i], "w");
            if (!output_files[i]) {
                perror("Erro ao abrir arquivo auxiliar para escrita (passagem)");
                exit(EXIT_FAILURE);
            }
        }

        // realiza uma passagem de intercalacao 
        merge_pass(input_files, output_files, K_PATHS);

        // fecha os arquivos para esta passagem
        for (int i = 0; i < K_PATHS; i++) {
            fclose(input_files[i]);
            fclose(output_files[i]);
        }

        // calcula o numero de runs resultantes para a proxima iteracao
        // isso eh feito contando os INT_MAX nos arquivos de saida desta passagem
        total_runs = 0;
        for (int i = 0; i < K_PATHS; i++) {
            FILE* f_check = fopen(aux_filenames[current_write_offset + i], "r");
            if (!f_check) {
                perror("Erro ao abrir arquivo para contagem de runs");
                exit(EXIT_FAILURE);
            }
            int val;
            while (fscanf(f_check, "%d", &val) == 1) {
                if (val == INT_MAX) {
                    total_runs++;
                }
            }
            fclose(f_check);
        }
        // se houver apenas um run em um arquivo e os outros estiverem vazios, isso conta como 1 run
        if (total_runs == 0) total_runs = 1; // caso especial: todo o arquivo ja esta ordenado em um run final

        printf(" passagem concluida. runs restantes: %d\n", total_runs);

        //inverte os papeis de arquivos de leitura e escrita para a proxima passagem
        int temp_offset = current_read_offset;
        current_read_offset = current_write_offset;
        current_write_offset = temp_offset;
    }

    // o arquivo final ordenado esta no conjunto de arquivos "read_offset"
    // copie o conteudo do primeiro arquivo (que agora contem tudo) para o arquivo de saida final
    FILE* final_output = fopen(output_filename, "w");
    if (!final_output) {
        perror("Erro ao abrir arquivo de saida final");
        exit(EXIT_FAILURE);
    }

    FILE* final_input_file = fopen(aux_filenames[current_read_offset], "r");
    if (!final_input_file) {
        perror("Erro ao abrir arquivo final ordenado");
        exit(EXIT_FAILURE);
    }

    int val;
    printf("copiando resultado final para %s...\n", output_filename);
    while (fscanf(final_input_file, "%d", &val) == 1) {
        if (val != INT_MAX) { // nao copia os marcadores do fim de run
            fprintf(final_output, "%d\n", val);
        }
    }

    fclose(final_input_file);
    fclose(final_output);

    // limpa os arquivos auxiliares (opcional)
    printf("limpando arquivos auxiliares...\n");
    for (int i = 0; i < NUM_FILES; i++) {
        remove(aux_filenames[i]);
    }

    printf("ordenacao externa concluida. saida em %s\n", output_filename);
}


// funcao principal
int main() {
    const char* input_file = "input.txt";
    const char* output_file = "output.txt";
    int num_elements = 100; // numero de elementos a serem ordenados (ajuste para testar)

    // 1. gerar arquivo de entrada
    generate_input_file(input_file, num_elements);

    // 2. executar a ordenacao externa
    external_sort(input_file, output_file);

    return 0;
}



/* ANALISE DE COMPLEXIDADE
fase 1: criacao de runs
de tempo eh dominada pela intercalacao
leitura de N elementos
ordenacao de N/M blocos de tamanho M
total: O(N + (N/M) * M log M) = O(N + N log M) = O(N log M)

fase 2: intercalacao
O(N log N)

complexidade de espaco em memoria principal eh O(M)

se considerarmos o numero de blocos fisicos de disco (B eh o tamanho do bloco de disco)
a complexidade seria:

O( N/B log3(N/M))


*/
