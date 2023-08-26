#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct{
    char Placa[6];
} Caminhao;


typedef struct{
    int codigo;
    float loc_x, loc_y;
    Caminhao *caminhao;
    int n_caminhao;
} Filial;


typedef struct{
    float origem_x, origem_y;
    float destino_x, destino_y;
} Produto;


Caminhao remover_caminhao(Filial *filiais, int codigo_filial);
Filial *cadastrar_filial(Filial *filiais, int *n_filiais);
void cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial);
void realizar_entrega(Filial *filiais, Produto produto, int n_filiais);
void imprimir_filiais(Filial *filiais, int n_filiais);


int main(){
    int op, codigo_filial = 0, n_filiais, x;
    Caminhao caminhao;
    Filial *filiais = NULL;
    Produto produto;
    while (op != 5){
        printf("Escolha uma opcao:\n1-Cadastrar filial\n2-Cadastrar caminhao\n3-Realizar entrega\n4-Imprimir filiais\n5-Sair\nOpcao: ");
        scanf("%d",&op);
        if (op == 1){
            filiais = cadastrar_filial(filiais, &n_filiais);
        } else if (op == 2){
            printf("Digite uma filial valida para cadastrar caminhao:");
            scanf("%d", &codigo_filial);
            printf("Digite a placa do caminhao: ");
            scanf(" %5[^\n]", caminhao.Placa);
            cadastrar_caminhao(filiais, caminhao, codigo_filial);
        } else if (op == 3){
            printf("Digite a origem (x,y): ");
            scanf("%f %f", &produto.origem_x, &produto.origem_y);
            printf("Digite o destino (x,y): ");
            scanf("%f %f", &produto.destino_x, &produto.destino_y);
            realizar_entrega(filiais, produto, n_filiais);
        } else if (op == 4){
            imprimir_filiais(filiais, n_filiais);
        }
    }
    for (x = 0; x < n_filiais; x++){
        free(filiais[x].caminhao);
    }
    free(filiais);
    return 0;
}


Caminhao remover_caminhao(Filial *filiais, int codigo_filial){
    Caminhao removido;
    if (filiais[codigo_filial].n_caminhao == 0)
    {
        printf("Nao ha caminhoes nessa filial!\n");
        return removido;
    }
    removido = filiais[codigo_filial].caminhao[filiais[codigo_filial].n_caminhao - 1];
    filiais[codigo_filial].n_caminhao--;
    filiais[codigo_filial].caminhao = (Caminhao *)realloc(filiais[codigo_filial].caminhao, filiais[codigo_filial].n_caminhao * sizeof(Caminhao));
    return removido;
}


Filial *cadastrar_filial(Filial *filiais, int *n_filiais){
    Filial *temp = filiais;
    filiais = (Filial*) realloc(filiais, (*n_filiais + 1) * sizeof(Filial));
    if (filiais == NULL){
        printf("Erro de alocacao\n");
        for (int x = 0; x < (*n_filiais); x++){
            free(temp[x].caminhao);
        }
        free(temp);
        exit (1);
    }
    filiais[*n_filiais].codigo = *n_filiais;
    filiais[*n_filiais].caminhao = NULL;
    filiais[*n_filiais].n_caminhao = 0;
    printf("Digite as coordenadas (x,y) da filial: ");
    scanf("%d %d", &filiais[*n_filiais].loc_x, &filiais[*n_filiais].loc_y);
    (*n_filiais)++;
    printf("Filial cadastrada com sucesso!\n");
    return filiais;
}


void cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial){
    Caminhao *temp = filiais[codigo_filial - 1].caminhao;
    filiais[codigo_filial - 1].caminhao = (Caminhao*) realloc(filiais[codigo_filial - 1].caminhao, filiais[codigo_filial - 1].n_caminhao * sizeof(Caminhao));
    if (filiais[codigo_filial - 1].caminhao == NULL){
        printf("Erro de alocacao\n");
        free(temp);
        exit (1);
    }
    filiais[codigo_filial - 1].caminhao[filiais[codigo_filial].n_caminhao] = caminhao;
    (filiais[codigo_filial].n_caminhao)++;
    printf("Caminhao cadastrado com sucesso!\n");
    return;
}


void realizar_entrega(Filial *filiais, Produto produto, int n_filiais){
    int dist, x, respvalor = 0, respind;
    for (x = 0; x < n_filiais; x++){
        dist = pow((filiais[x].loc_x + produto.origem_x), 2);
        dist += pow((filiais[x].loc_y + produto.origem_y), 2);
        dist = sqrt(dist);
        if (dist > respvalor){
            respvalor = dist;
            respind = x;
        }
        Caminhao novo = remover_caminhao(filiais, respind);
        cadastrar_caminhao(filiais, novo, respind);
    }
}


void imprimir_filiais(Filial *filiais, int n_filiais){
    int x, y;
    for (x = 0; x < n_filiais; x++){
        printf("Filial: %d", filiais[x].codigo);
        for (y = 0; y < filiais[x].n_caminhao; y++){
            printf("Placa do %do caminhao: %s", y + 1, filiais[x].caminhao[y].Placa);
        }
    }
}