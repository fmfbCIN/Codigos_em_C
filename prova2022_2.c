#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct{
    char nome[100];
    char cpf[11];
    int qtdNotas;
    float* notas;
    float media;
} Aluno;

Aluno *carregaAlunos(int *qtdAlunos);
float *leNotas(int *qtdNotas);
float media(float *notas, int qtdNotas);
void ordena(Aluno *alunos, int qtdAlunos);
void salvaAlunos(Aluno *alunos, int qtdAlunos);

int main(){
    Aluno *alunos;
    int qtdAlunos = 0, op = 0, x;
    while (op != 6){
        printf("Escolha uma opcao valida para fazer:\n1-Carregar Alunos\n2-Ler Notas\n3-Obter media de um aluno\n4-Ordenar alunos\n5-Salvar Alunos\n6-Sair\nOpcao: ");
        scanf("%d", &op);
        if (op == 1){
            alunos = carregaAlunos(&qtdAlunos);
            if (alunos == NULL){
                for (x = 0; x < qtdAlunos; x++){
                    free(alunos[x].notas);
                }
                free(alunos);
                exit(1);
            }
        } else if (op == 2){
            for (x = 0; x < qtdAlunos; x++){
                alunos[x].notas = leNotas(&alunos[x].qtdNotas);
            }
        } else if (op == 3){
            for (x = 0; x < qtdAlunos; x++){
                alunos[x].media = media(alunos[x].notas, alunos[x].qtdNotas);
            }
        } else if (op == 4){
            ordena(alunos, qtdAlunos);
        } else if (op == 5){
            salvaAlunos(alunos, qtdAlunos);
        }
    }
    printf("Fechando operacoes...");
    for (x = 0; x < qtdAlunos; x++){
        free(alunos[x].notas);
    }
    free(alunos);
    return 0;
}

Aluno *carregaAlunos(int *qtdAlunos){
    (*qtdAlunos) = 0;
    FILE *arq;
    Aluno *alunos = NULL;
    arq = fopen ("alunos.txt", "r");
    if (arq != NULL){
        while (!feof(arq)){
            alunos = (Aluno*) realloc(alunos, ((*qtdAlunos) + 1) * sizeof(Aluno));
            if (alunos == NULL){
                free(alunos);
                return NULL;
            }
            fscanf(arq, "%[^,], %[^\n]", alunos[(*qtdAlunos)].nome, alunos[(*qtdAlunos)].cpf);
            (*qtdAlunos)++;
        }
        printf("Alunos carregados com sucesso!\n");
    } else {
        printf("Erro de achar arquivo\n");
    }
    return alunos;
}
float *leNotas(int *qtdNotas){
    float *notas = NULL, nota = 0;
    while (nota >= 0){
        notas = (float *) realloc(notas, ((*qtdNotas) + 1) * sizeof(float));
        if (notas == NULL){
            printf("Erro de alocacao!\n");
            return NULL;
        }
        printf("Digite uma nota que o aluno tirou: ");
        scanf("%f", &notas[(*qtdNotas)]);
        (*qtdNotas)++;
    }
    return notas;
}
float media(float *notas, int qtdNotas){
    int x;
    float media = 0;
    for (x = 0; x < qtdNotas; x++){
        media += notas[x];
    }
    media = media / qtdNotas;
    return media;
}
void ordena(Aluno *alunos, int qtdAlunos){
    int x, y;
    Aluno cache;
    for (x = 0; x < qtdAlunos; x++){
        for(y = 0; y < qtdAlunos - 1; y++){
            if (alunos[y].media < alunos[y+1].media){
                cache = alunos[y+1];
                alunos[y+1] =  alunos[y];
                alunos[y] = cache;
            }
        }
    }
}
void salvaAlunos(Aluno *alunos, int qtdAlunos){
    int x;
    FILE *arq;
    arq = fopen ("alunos.bin", "w");
    if (arq != NULL){
        for (x = 0; x < qtdAlunos; x++){
            fwrite(&(alunos[x]), sizeof(Aluno), 1, arq);
        }
        fclose(arq);
    } else if (arq == NULL){
        printf("Erro de acesso ao arquivo!\n");
    }
}