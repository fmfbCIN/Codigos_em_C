#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct{
    float pReal;
    float pImag;
} Complexo;

void empilhe(Complexo **cPilha, Complexo umC, int *tPilha);
Complexo desempilhe(Complexo **cPilha, int *tPilha);
Complexo topo(Complexo *cPilha, int tPilha);
int pilhaVazia(Complexo *cPilha, int tPilha);
void salvePilha(Complexo *cPilha, int tPilha);
Complexo *recuperePilha(int *tPilha);

int main(){
    Complexo *cPilha = NULL, umC;
    int tPilha = 0, op, estado;
    while (op != 7){
        printf("Selecione o que deseja fazer:\n1-Empilhar número complexo\n2-Desempilhar topo\n3-Ver topo da pilha\n4-Estado da Pilha\n5-Salvar Pilha\n6-Recuperar pilha salva\n7-Sair\nOpcao:");
        scanf("%d", &op);
        if (op == 1){
            printf("Digite o pReal do número complexo: ");
            scanf("%f", &umC.pReal);
            printf("Digite o pImag do número complexo: ");
            scanf("%f", &umC.pImag);
            empilhe(&cPilha, umC, &tPilha);
        } else if (op == 2){
            umC = desempilhe(&cPilha, &tPilha);
        } else if (op == 3){
            umC = topo(cPilha, tPilha);
        } else if (op == 4){
            estado = pilhaVazia(cPilha, tPilha);
        } else if (op == 5){
            salvePilha(cPilha, tPilha);
        } else if (op == 6){
            cPilha = recuperePilha(&tPilha);
            if (cPilha == NULL){
                free(cPilha);
            }
        }
    }
    free(cPilha);
    return 0;
}

void empilhe(Complexo **cPilha, Complexo umC, int *tPilha){
    (*tPilha)++;
    (*cPilha) = (Complexo*) realloc((*cPilha), (*tPilha) * sizeof(Complexo));
    if ((*cPilha) == NULL){
        printf("Erro de alocação!");
        free(*cPilha);
        exit(1);
    }
    (*cPilha)[(*tPilha) - 1] = umC;
}
Complexo desempilhe(Complexo **cPilha, int *tPilha){
    if ((*tPilha) != 0){
        (*tPilha)--;
        (*cPilha) = (Complexo*) realloc((*cPilha), (*tPilha) * sizeof(Complexo));
        if ((*cPilha) == NULL){
            printf("Erro de alocação!");
            free(*cPilha);
            exit(1);
        }
    }
}
Complexo topo(Complexo *cPilha, int tPilha){
    printf("Numero real do topo:%f\nNumero imaginario do topo:%f\n",cPilha[tPilha - 1].pReal,cPilha[tPilha - 1].pImag);
    return cPilha[tPilha - 1];
}
int pilhaVazia(Complexo *cPilha, int tPilha){
    if (cPilha == NULL || tPilha == 0){
        printf("Estado: 1\n");
        return 1;
    } else {
        printf("Estado: 0\n");
        return 0;
    }
}
void salvePilha(Complexo *cPilha, int tPilha){
    FILE *arq;
    arq = fopen("pilha.bin","wb");
    if (arq != NULL){
        fwrite(&tPilha, sizeof(Complexo), 1, arq);
        for (int x = 0; x < tPilha; x++){
            fwrite(&(cPilha[x].pReal), sizeof(Complexo), 1, arq);
            fwrite(&(cPilha[x].pImag), sizeof(Complexo), 1, arq);
        }
        fclose(arq);
    } else if (arq == NULL){
        printf("Erro em salvar dados!\n");
    }
}
Complexo *recuperePilha(int *tPilha){
    FILE *arq;
    Complexo *cPilha = NULL;
    arq = fopen("pilha.bin","rb");
    if (arq != NULL){
        fread(&(*tPilha),sizeof(int), 1, arq);
        cPilha = (Complexo*) realloc(cPilha, (*tPilha) * sizeof(Complexo));
        if (cPilha == NULL){
            return NULL;
        }
        for (int x = 0; x < (*tPilha); x++){
            fread(&cPilha[x].pReal,sizeof(int), 1, arq);
            fread(&cPilha[x].pImag,sizeof(int), 1, arq);
        }
        fclose(arq);
        return cPilha;
    } else if (arq == NULL){
        printf("Erro em salvar dados!\n");
        return NULL;
    } 
}