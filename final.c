#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//criando a struct
typedef struct{
    unsigned parte1;
    unsigned parte2;
    unsigned emJogo;
} Peca;

//criando as funcoes
Peca *inicializaPecasDomino();
char *pecasIndividuo(Peca *todasPecas);
char *jogada(char pecaEscolhida, char extremidade, char *pecasJogador, char *tamPecasJog, Peca *todasPecas, char *Mesa, char *tamMesa);
void mostraPecas(char *pecasJogador,Peca *todasPecas);
unsigned char pontuacao(char *pecasJogador, char *tamPecasJog,Peca *todasPecas);
void mostraMesa(char *mesa,Peca *todasPecas);


int main(){
    srand(time(NULL));
    int opcao = 0;
    //criando o vetor dinamico de estruturas para poder armazenar as informacoes de cada peça de dominó
    Peca *todasPecas = NULL;
    //igualando o vetor dinamico com a funcao para adquirir as informações contidas nela e organizar esse vetor
    *todasPecas = *inicializaPecasDomino();
    while (opcao != 1){
        printf("Pressione 1 para distribuir as peças!\n");
    }
    opcao = 3;
    //criando os vetor com as informações de cada jogador
    char *pecasp1 = malloc(7 * sizeof(char));
    for (int x = 0; x < 7; x++){
        pecasp1[x] = realloc(pecasp1[x], 3 * sizeof(char));
    }
    *pecasp1 = *pecasIndividuo(todasPecas);

    char *pecasp2 = malloc(7 * sizeof(char));
    for (int x = 0; x < 7; x++){
        pecasp2[x] = realloc(pecasp2[x], 3 * sizeof(char));
    }
    *pecasp2 = *pecasIndividuo(todasPecas);
    opcao = 1;
    int escolha;
    char escolhido[3];
    char *Mesa = malloc (14 * sizeof (char));
    char extremo1[3];
    int y;
    char extremo2[3];
    char tampecasp1[3] = "07";
    char tampecasp2[3] = "07";
    char tamMesa[3] = "07";
    for(int x = 0; x < 14; x++){
        Mesa[x] = realloc(Mesa[x], 3 * sizeof(char));
    }
    int varnome;
    //loop do jogo;
    while (opcao != 3){
        if (opcao = 1){
            printf("P1 quer:\n1-Ver cartas\n2-Jogar\n");
            printf("Suas peças são:\n");
            if (varnome == 1){
                mostraPecas(pecasp1, todasPecas);
            }
            printf("Qual peça voce gostaria de colocar na mesa?\n");
            scanf("%d", &escolha);
            strcpy(escolhido,pecasp1[escolha - 1]);
            //ERRO
            pecasp1 = *jogada(escolhido, extremo1, pecasp1, &tampecasp1, todasPecas, Mesa, &tamMesa);
            pecasp1 = *jogada(escolhido, extremo2, pecasp1, &tampecasp1, todasPecas, Mesa, &tamMesa);
            opcao++;
        }
        else if (opcao = 2){
            printf("P1 quer:\n1-Ver cartas\n2-Jogar\n");
            printf("Suas peças são:\n");
            if (varnome == 1){
                mostraPecas(pecasp1, todasPecas);
            }
            printf("Qual peça voce gostaria de colocar na mesa?\n");
            scanf("%d", &escolha);
            strcpy(escolhido,pecasp2[escolha - 1]);
            //ERRO
            pecasp1 = *jogada(escolhido, extremo1, pecasp2, &tampecasp2, todasPecas, Mesa, &tamMesa);
            pecasp1 = *jogada(escolhido, extremo2, pecasp2, &tampecasp2, todasPecas, Mesa, &tamMesa);
            opcao++;
        }
    }
    printf("Quer jogar outra?\n1-Sim\n2-Nao\n");
    int ysorno;
    scanf("%d", &ysorno);
    free (pecasp1);
    free (pecasp2);
    free (Mesa);
    free (todasPecas);
    return 0;
}

Peca *inicializaPecasDomino(){
    unsigned x;
    unsigned y;
    int cont = 0;
    Peca *pecas = malloc (28 * sizeof(unsigned));
    for (x = 0; x < 6; x++){
        for (y = 0; y < 6; y++){
            pecas[cont].parte1 = x;
            pecas[cont].parte2 = y;
            pecas[cont].emJogo = 0;
            cont++;
        }
    }
    return pecas;
}
char *pecasIndividuo(Peca *todasPecas){
    int aleatorio;
    int escolhidos[7];
    int cont = 0;
    char *pecasIndividuo = malloc(7 * sizeof(char));
    for (int x = 0; x < 7; x++){
        pecasIndividuo[x] = realloc(pecasIndividuo[x], 3 * sizeof(char)); //checar se é malloc ou realloc aqui
    }
    while (cont < 7){
        aleatorio = rand() % 28;
        if (todasPecas[aleatorio - 1].emJogo == 0){
            todasPecas[aleatorio - 1].emJogo = 1;
            escolhidos[cont] = aleatorio;
            if (aleatorio == 1) pecasIndividuo[cont] = "01";
            if (aleatorio == 2) pecasIndividuo[cont] = "02";
            if (aleatorio == 3) pecasIndividuo[cont] = "03";
            if (aleatorio == 4) pecasIndividuo[cont] = "04";
            if (aleatorio == 5) pecasIndividuo[cont] = "05";
            if (aleatorio == 6) pecasIndividuo[cont] = "06";
            if (aleatorio == 7) pecasIndividuo[cont] = "07";
            if (aleatorio == 8) pecasIndividuo[cont] = "08";
            if (aleatorio == 9) pecasIndividuo[cont] = "09";
            if (aleatorio == 10) pecasIndividuo[cont] = "10";
            if (aleatorio == 11) pecasIndividuo[cont] = "11";
            if (aleatorio == 12) pecasIndividuo[cont] = "12";
            if (aleatorio == 13) pecasIndividuo[cont] = "13";
            if (aleatorio == 14) pecasIndividuo[cont] = "14";
            if (aleatorio == 15) pecasIndividuo[cont] = "15";
            if (aleatorio == 16) pecasIndividuo[cont] = "16";
            if (aleatorio == 17) pecasIndividuo[cont] = "17";
            if (aleatorio == 18) pecasIndividuo[cont] = "18";
            if (aleatorio == 19) pecasIndividuo[cont] = "19";
            if (aleatorio == 20) pecasIndividuo[cont] = "20";
            if (aleatorio == 21) pecasIndividuo[cont] = "21";
            if (aleatorio == 22) pecasIndividuo[cont] = "22";
            if (aleatorio == 23) pecasIndividuo[cont] = "23";
            if (aleatorio == 24) pecasIndividuo[cont] = "24";
            if (aleatorio == 25) pecasIndividuo[cont] = "25";
            if (aleatorio == 26) pecasIndividuo[cont] = "26";
            if (aleatorio == 27) pecasIndividuo[cont] = "27";
            if (aleatorio == 28) pecasIndividuo[cont] = "28";
            cont++;
        }
    }
    return pecasIndividuo;
}
char *jogada(char pecaEscolhida, char extremidade, char *pecasJogador, char *tamPecasJog, Peca *todasPecas, char *Mesa, char *tamMesa){
    if (pecaEscolhida == extremidade){
        //atualizando tamanhos de cada jogador
        if (tamPecasJog == "07") tamPecasJog == "06";
        else if (tamPecasJog == "06") tamPecasJog == "05";
        else if (tamPecasJog == "05") tamPecasJog == "04";
        else if (tamPecasJog == "04") tamPecasJog == "03";
        else if (tamPecasJog == "03") tamPecasJog == "02";
        else if (tamPecasJog == "02") tamPecasJog == "01";
        else if (tamPecasJog == "01"){
            tamPecasJog == "00";
            printf("Você venceu!");
            exit (1);
        }
        if (tamMesa == "00") tamMesa = "01";
        else if (tamMesa == "01") tamMesa = "02";
        else if (tamMesa == "02") tamMesa = "03";
        else if (tamMesa == "03") tamMesa = "04";
        else if (tamMesa == "04") tamMesa = "05";
        else if (tamMesa == "05") tamMesa = "06";
        else if (tamMesa == "06") tamMesa = "07";
        else if (tamMesa == "07") tamMesa = "08";
        else if (tamMesa == "08") tamMesa = "09";
        else if (tamMesa == "09") tamMesa = "10";
        else if (tamMesa == "10") tamMesa = "11";
        else if (tamMesa == "11") tamMesa = "12";
        else if (tamMesa == "12") tamMesa = "13";
        else if (tamMesa == "13") tamMesa = "14";
        for (int x = 0; x < 7; x++){
            if (pecaEscolhida == pecasJogador[x]){
                pecasJogador = "00"; //como não possui peça "nomeada" de 00, não irá interferir no continuar do código
            }
        }
    } else if (pecaEscolhida != extremidade){
        printf("Erro em posicionar peca!");
    }
    return pecasJogador;
}
void mostraPecas(char *pecasJogador,Peca *todasPecas){
        char numeros[28] = {"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28"};
            for (int x = 0; x < 7; x++){
                for (y = 0; y < 28; y++){
                    if (pecasJogador[x] == numeros[y])
                        printf("%u:%u\n",todasPecas[y].parte1,todasPecas[y].parte2);
                }
            }
}
unsigned char pontuacao(char *pecasJogador, char *tamPecasJog,Peca *todasPecas){

}
void mostraMesa(char *mesa,Peca *todasPecas){

}