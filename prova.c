#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    char nome[100];
    char CPF[100];
    int qtdnotas;
    float *notas;
    float media;
} Aluno;

Aluno *carregaAlunos(int *qtdAlunos);
float *leNotas(int *qtdNotas);
float media(float *notas, int qtdNotas);
void ordena(Aluno *alunos, int qtdAlunos);
void salvaAlunos(Aluno *alunos, int qtdAlunos);

int main(){
    int opcao = 0;
    int x;
    int qtdAlunos = 0;
    Aluno *alunos = NULL;
    while (opcao != 6){
        if (opcao == 1){
            alunos = carregaAlunos(&qtdAlunos);
            opcao = 0;
        } else if (opcao == 2){
            for (x = 0; x < qtdAlunos; x++){
                alunos[x].qtdnotas = 0;
                alunos[x].notas = leNotas(&alunos[x].qtdnotas);
            }
            opcao = 0;
        } else if (opcao == 3){
            for (x = 0; x < qtdAlunos; x++){
                alunos[x].media = media(alunos[x].notas, alunos[x].qtdnotas);
            }
            opcao = 0;
        } else if (opcao == 4){
            ordena(alunos, qtdAlunos);
            opcao = 0;
        } else if (opcao == 5){
            salvaAlunos(alunos, qtdAlunos);
            opcao = 0;
        } else if (opcao > 6 || opcao < 1){
            printf("Defina o que gostaria de fazer:\n");
            printf("1-Carregar informacoes\n2-Ler Notas\n3-Calcular Media\n4-Ordenar notas\n5-Salvar em arquivo binario\n6-Sair\n");
            scanf ("%d", &opcao);
        }
    }
    free (alunos);
    return 0;
}

Aluno *carregaAlunos(int *qtdAlunos){
    Aluno *alunos = NULL;
    FILE *arq;
    int cont = 0;
    arq = fopen ("alunos.txt","r");
    if (arq == NULL){
        printf("Erro ao acessar o arquivo\n");
        return NULL;
    }
    while (!feof(arq)){
        cont++;
        alunos = realloc(alunos,(cont) * sizeof(Aluno));
        fscanf(arq," %s %s", (alunos[cont - 1]).nome, (alunos[cont - 1]).CPF);
    }
    *qtdAlunos = cont;
    fclose (arq);
    printf("Sucesso de execucao!\n");
    return alunos;
}
float *leNotas(int *qtdNotas){
    int contador = 0;
    float nota;
    float *notas = NULL;
    while (nota >= 0){
        contador++;
        notas = realloc(notas,contador * (sizeof(float)));
        printf("Digite uma nota tirada pelo aluno\n");
        scanf ("%f", &notas[contador - 1]);
        nota = notas[contador - 1];
        *qtdNotas = *qtdNotas + 1;
    }
    printf("Sucesso de execucao!\n");
    return notas;
}
float media(float *notas, int qtdNotas){
    float mediafinal;
    for (int z = 0; z < qtdNotas; z++){
        mediafinal = mediafinal + notas[z];
    }
    printf("Sucesso de execucao!\n");
    return mediafinal;
}
void ordena(Aluno *alunos, int qtdAlunos){
    Aluno armazenamento;
    for (int b = 0; b < qtdAlunos; b++){
        for (int a = 1; a < qtdAlunos; b++){
            if (alunos[a].media > alunos[a-1].media){
                memcpy ( &armazenamento, &alunos[a], sizeof(Aluno));
                memcpy ( &alunos[a], &alunos[a -1], sizeof(Aluno));
                memcpy ( &alunos[a -1], &armazenamento, sizeof(Aluno));
            }
        }
    }
    printf("Sucesso de execucao!\n");
}
void salvaAlunos(Aluno *alunos, int qtdAlunos){
    FILE *arq2;
    arq2 = fopen("alunos.bin", "wb");
    for (int c = 0; c < qtdAlunos; c++){
        fwrite(&(alunos[c]), sizeof(Aluno), 1, arq2);
    }
    fclose(arq2);
    printf("Sucesso de execucao!\n");
}