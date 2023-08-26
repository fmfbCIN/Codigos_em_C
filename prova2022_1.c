#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
typedef struct{
    Candidato* DF;
    Candidato* DE;
    Candidato* SEN;
    Candidato* GOV;
    Candidato* PR;
    int qtdCandidatos[5];
} listaCandidatos;

typedef struct{

} Eleitor;

typedef struct{
    char nome[100];
    int numero;
} Candidato;

typedef struct{
    Candidato *end;
    int votos;
} TotalVoto;

listaCandidatos carregarCandidatos(char *nomeArq);
Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores);
int verificaCandidato(listaCandidatos listaC, Candidato candidatoAt);
int verificaEleitor(Eleitor *listaE, Eleitor eleitorAt);
void apresentaResultado(TotalVoto *votos, int qtdCandidatos);
Candidato *localizaCandidato(listaCandidatos listaC, Candidato candidatoAt, char *cargo);

int main(){
    
    return 0;
}

listaCandidatos carregarCandidatos(char *nomeArq){
    FILE *arq;
    char arqfinal[100], nome;
    int numero;
    listaCandidatos candidatos;
    candidatos.DF = NULL;
    candidatos.DE = NULL;
    candidatos.GOV = NULL;
    candidatos.PR = NULL;
    candidatos.SEN = NULL;
    strcpy(arqfinal, (*nomeArq));
    strcat(arqfinal, ".txt");
    arq = fopen(arqfinal,"r");
    if(arq != NULL){
        while(!(feof(arq))){
            fscanf(" %[^,], %d", nome, &numero);
        }
    } else if (arq == NULL){
        printf("Erro em acessa arquivo!\n");
    }
}
Eleitor *carregarEleitores(char *nomeArq, int *qtdEleitores);
int verificaCandidato(listaCandidatos listaC, Candidato candidatoAt);
int verificaEleitor(Eleitor *listaE, Eleitor eleitorAt);
void apresentaResultado(TotalVoto *votos, int qtdCandidatos);
Candidato *localizaCandidato(listaCandidatos listaC, Candidato candidatoAt, char *cargo);