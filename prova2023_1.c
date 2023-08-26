#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//structs
typedef struct{
    int linha;
    int coluna;
    char medic[50];
} localM;

typedef struct{
    int qtdM;
    char medic[50];
} TMed;

typedef struct{
    int qtd;
    TMed* dados; //nao especifica o nome dessa variavel na prova, então coloquei dados pois são os dados de cada tipo de medicamento em um pedido
} pedido;

//declaração de funções (boa prática)
localM *carregaConfig(int *tamC);
pedido *carregaPedidos(int *tamP);
TMed **inicializa();
void processaPedido(pedido meuPedido, TMed **estoque, localM *config, int tamC);
void processaPedidos(pedido *todosPedidos, int tamP, TMed **estoque, localM *config, int tamC);

//Monitores recomendaram seguir lógica na main ao invés de fazer Menu
int main(){
    //declaracao de variaveis
    int op, tamC = 0, tamP = 0, x;
    pedido meuPedido;
    TMed **estoque;
    localM *config;
    pedido *todosPedidos;
    localM *vet;
    printf("Inicializando programa...\n");
    estoque = inicializa();
    //exit - erro de memoria
    if (estoque == NULL){
        free(estoque);
        exit(1);
    }
    printf("Adquirindo informações de medicamentos...\n");
    config = carregaConfig(&tamC);
    //exit - erro de memoria
    if (config == NULL){
        for (x = 0; x < 20; x++){
            free(estoque[x]);
        }
        free(estoque);
        free(config);
        exit(1);
    }
    printf("Adquirindo informações de pedidos...\n");
    todosPedidos = carregaPedidos(&tamP);
    //exit - erro de memoria
    if (todosPedidos == NULL){
        for (x = 0; x < 20; x++){
            free(estoque[x]);
        }
        free(estoque);
        free(config);
        free(todosPedidos);
        exit(1);
    }
    printf("Armazenando estoque e transferindo informações para arquivo txt final...\n");
    processaPedidos(todosPedidos,tamP,estoque,config,tamC);
    return 0;
}

localM *carregaConfig(int *tamC){
    //declarando variáveis
    (*tamC) = 0;
    FILE *arq;
    localM *vet = NULL;
    //abrindo arquivo de leitura
    arq = fopen("config.txt","r");
    if (arq != NULL){
        //adquirindo informações do arquivo txt
        while(!(feof(arq))){
            //realocando memória
            vet = (localM*) realloc(vet, ((*tamC) + 1) * sizeof(localM));
            //erro de alocacao - seguranca de memoria
            if (vet == NULL){
                printf("Erro de alocacao de memoria!\n");
                return NULL;
            }
            //adquirindo informações do arquivo txt
            fscanf(arq, "%d, %d, %49[^\n]\n", &vet[(*tamC)].linha, &vet[(*tamC)].coluna, vet[(*tamC)].medic);
            (*tamC)++;
        }
        fclose(arq);
    } else if (arq == NULL){
        printf("Erro em acessar arquivo!\n");
    }
    //retornando vetor
    printf("Configurações carregadas com sucesso!\n");
    return vet;
}

pedido *carregaPedidos(int *tamP){
    //inicializando variáveis
    (*tamP) = 0;
    pedido* vet = NULL;
    FILE *arq;
    arq = fopen("binario.bin","rb"); //nao tem o nome do arquivo binario na prova, entao coloquei binario para facilitar, porem ele contem os dados dos pedidos
    if (arq == NULL){
        printf("Erro em acessar arquivo!\n");
    } else if (arq != NULL){
        //adquirindo informações do arquivo binário
        while(!(feof(arq))){
            vet = (pedido*) realloc(vet, ((*tamP) + 1) * sizeof(pedido));
            //erro de alocacao - seguranca de memoria
            if (vet == NULL){
                printf("Erro de alocacao de memoria!\n");
                return NULL;
            }
            //adquirindo informacoes do arquivo binario
            fread(&vet[(*tamP)].qtd,sizeof(pedido),1,arq);
            vet[(*tamP)].dados = (TMed*) realloc(vet[(*tamP)].dados, vet[(*tamP)].qtd * sizeof (TMed));
            //erro de alocacao - seguranca de memoria
            if (vet[(*tamP)].dados == NULL){
                printf("Erro de alocacao de memoria!\n");
                return NULL;
            }
            //adquirindo informaçõpes do arquivo binário
            for (int x = 0; x < vet[(*tamP)].qtd; x++){
                fread(&vet[(*tamP)].dados[x].qtdM,sizeof(pedido),1,arq);
                fread(vet[(*tamP)].dados[x].medic,sizeof(pedido),1,arq); //vetor char = sem '&' no fread
                (*tamP)++;
            }
        }
        fclose(arq);
    }
    printf("Pedidos carregados com sucesso!\n");
    return vet;
}

TMed **inicializa(){
    //variaveis da funcao
    TMed **Coliseu = NULL;
    int x = 20;
    //realocando a matriz dinamica
    Coliseu = (TMed**) realloc(Coliseu, 20 * sizeof(TMed));
    //erro de alocacao - seguranca de memoria
    if (Coliseu == NULL){
        printf("Erro de alocação!\n");
        return NULL;
    }
    //realocando cada coluna da matriz
    for (int y = 0; y < 20; y++){
        (Coliseu)[y] = (TMed*) realloc((Coliseu)[y], x * sizeof(TMed));
        x += 2;
    }
    //retornando a matriz com sucesso
    printf("Inicialização com sucesso!\n");
    return Coliseu;
}

void processaPedido(pedido meuPedido, TMed **estoque, localM *config, int tamC){
    FILE *arq;
    arq = fopen("pedidos.txt","a");
    if (arq == NULL){
        printf("Erro em acessar arquivo!\n");
        //procurando os dados para enviar ao arquivo txt e diminuir na quantidade da matriz estoque
    } else if (arq != NULL){
        for (int y = 0; y < meuPedido.qtd; y++){
            for (int z = 0; z < tamC; z++){
                if (strcmp(meuPedido.dados[y].medic, config[z].medic) == 0){
                    (estoque[config[z].linha][config[z].coluna].qtdM)--;
                    fprintf(arq,"separei %d unidades do medicamento %s", meuPedido.dados[y].qtdM, meuPedido.dados[y].medic);
                }
            }
        }
        fclose(arq);
    }
}

void processaPedidos(pedido *todosPedidos, int tamP, TMed **estoque, localM *config, int tamC){
    //Abastecendo o estoque
    for (int x = 0; x < tamC; x++){
        estoque[config[x].linha][config[x].coluna].qtdM = 20;
        strcpy(estoque[config[x].linha][config[x].coluna].medic,config[x].medic);
    }
    printf("Estoque armazenado com sucesso!\n");
    FILE *arq;
    arq = fopen("pedidos.txt","a");
    if (arq == NULL){
        printf("Erro em acessar arquivo!\n");
    } else if (arq != NULL){
        //procurando o medicamento no estoque
        for (int x = 0; x <  tamP; x++){
            for (int y = 0; y < todosPedidos[x].qtd; y++){
                for (int z = 0; z < tamC; z++){
                    if (strcmp(todosPedidos[x].dados[y].medic, config[z].medic) == 0){
                        //chamando a função processaPedido, que irá trabalhar unicamente dentro dessa função
                        processaPedido(todosPedidos[x],estoque,config,tamC);
                        for (int b = 0; b < 70; b++){
                            fprintf(arq,"+");
                        }
                            fprintf(arq,"\n");
                    }
                }
            }
        }
        fclose(arq);
    }
    printf("Comandos realizados com sucesso!\nEncerrando operacoes...\n");
    //free nos vetores
    free(todosPedidos);
    for (int x = 0; x < 20; x++){
        free(estoque[x]);
    }
    free(estoque);
    free(config);
}