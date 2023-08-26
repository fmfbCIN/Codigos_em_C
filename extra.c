#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Structs
typedef struct{
char nome[50];
char raca[50];
int idade;
float salario;
char CPF[12];
} Pessoa;

typedef struct {
char nome[50];
int codigo; //código único que identifica cada cidade
Pessoa* cidadaos;
int capacidade;
} Cidade;

//Declarando as funcoes
Cidade* NovaCidade(Cidade* censo, int* tam);
void InserirOuAtualizar(Cidade* censo, int tam);
void Remover(Cidade* censo, int tam);
void Procura(Cidade* censo, int tam);
void ViewTable(Cidade* censo, int tam);
void Desaloca(Cidade* censo, int tam);

int main(){
    int op;
    Cidade* censo = NULL;
    int tam = 0;
    //main roda ate o usuario quiser sair
    while (op != 6){
        printf("Escolha uma opcao valida do que quer fazer:\n1-Cadastrar Cidade\n2-Procurar Informações de CPF\n3-Ver Dados Registrados\n4-Adicionar/Atualizar dados salvos\n5-Remover pessoa\n6-Sair\nOpcao: ");
        scanf("%d", &op);
        if (op == 1){
            censo = NovaCidade(censo, &tam);
        } else if (op == 2){
            Procura(censo, tam);
        } else if (op == 3){
            ViewTable(censo, tam);
        } else if (op == 4){
            InserirOuAtualizar(censo, tam);
        } else if (op == 5){
            Remover(censo, tam);
        }
    }
    printf("Ok, encerrando operacoes...");
    //liberando os vetores dinamicos
    Desaloca(censo, tam);
    return 0;
}

Cidade* NovaCidade(Cidade* censo, int* tam){
    //Criando vetor dinamico temporario como metodo de seguranca
    Cidade* temp = censo;
    int x;
    char nome[50];
    int codigo;
    censo = (Cidade*) realloc(censo, ((*tam) + 1) * sizeof(Cidade));
    //Metodo de seguranca para caso a memoria esteja cheia
    if (censo == NULL){
        printf("Erro de alocacao...\n");
        for (x = 0; x < (*tam); x++){
            free(temp[x].cidadaos);
        }
        free(temp);
        exit(1);
    }
    //Declarando valores para variaveis que nao terao informacoes declaradas pelo usuario nesse momento do codigo
    censo[(*tam)].cidadaos = NULL;
    censo[*tam].capacidade = 0;
    //Adquirindo as informacoes de nome e codigo
    printf("Digite o nome da cidade: ");
    scanf(" %49[^\n]", nome);
    strcpy(censo[*tam].nome, nome);
    printf("Digite o codigo da cidade: ");
    scanf("%d", &codigo);
    censo[*tam].codigo = codigo;
    (*tam)++;
    //retornando vetor temporario para que o vetor da main adquira suas novas informacoes
    return censo;
}

void InserirOuAtualizar(Cidade* censo, int tam){
    //Criando vetor dinamico temporario como metodo de seguranca
    Pessoa* temp;
    //codigo e cpf sao variaveis de armazenamento de entradas. op e opc sao variaveis seletoras e pos e pos2 sao variaveis de posicao
    char cpf[12], opc;
    int codigo, x, pos = tam, pos2, booleano = 0, cmp, op = 0, y, pos3, novo = 0;
    //Procura a cidade que o usuario esta procurando
    printf("Digite o codigo da cidade que voce esta procurando: ");
    scanf("%d", &codigo);
    for (x = 0; x < tam; x++){
        if (censo[x].codigo == codigo){
            pos = x;
        }
    }
    //caso a cidade exista
    if (pos < tam){
        printf("Codigo de cidade valida! Digite o CPF que tera suas informacoes alteradas/adicionadas: ");
        scanf(" %11[^\n]", cpf);
        //procura CPF ate o fim do vetor de CPFs ou ate achar um que sirva (booleano = 1)
        for (y = 0; y < tam; y++){
            for (x = 0; x < censo[y].capacidade && booleano != 1; x++){
                    cmp = strcmp(cpf, censo[y].cidadaos[x].CPF);
                    //pega a posicao do CPF inserido caso esteja no vetor de CPFs
                    if (cmp == 0){
                        booleano = 1;
                        pos2 = x;
                        pos3 = y;
                    }
            }
        }
        //Caso nao ache o CPF inserido no vetor de CPFs
        if (booleano == 0){
            novo = 1;
            pos2 = censo[pos].capacidade;
            //Verificacao de seguranca para excesso de memoria (+1 CPF no vetor de CPFs)
            temp = censo[pos].cidadaos;
            censo[pos].cidadaos = (Pessoa*) realloc(censo[pos].cidadaos, (censo[pos].capacidade + 1) * sizeof(Pessoa));
            if (censo[pos].cidadaos == NULL){
                printf("Erro de alocacao...\n");
                for (x = 0; x < censo[pos].capacidade; x++){
                    free(censo[pos].cidadaos);
                }
                exit (1);
            }
            //Adquire as informacoes da pessoa com CPF inserido pelo usuario
            strcpy(censo[pos].cidadaos[pos2].CPF, cpf);
            printf("Novo CPF adicionado ao banco de dados!\nDigite o nome da pessoa: ");
            scanf(" %49[^\n]", censo[pos].cidadaos[pos2].nome);
            printf("Digite agora a raca: ");
            scanf(" %49[^\n]", censo[pos].cidadaos[pos2].raca);
            printf("Digite a idade:");
            scanf("%d", &censo[pos].cidadaos[pos2].idade);
            printf("Agora o salario:");
            scanf("%f", &censo[pos].cidadaos[pos2].salario);
            //Caso haja algum erro nas entradas, o usuario podera ajustar a informacao errada
            printf("Tudo pronto! Se desejar alterar algum dado, digite 's': ");
            scanf(" %c", &opc);
            if (opc == 's'){
                booleano = 1;
            } else {
                printf("Dados salvos com sucesso!\n");
            }
        }
        if (booleano == 1){
            //Alteracao de valores apenas se pos e pos3 sao iguais (posicoes adquiridas anteriormente) ou se o CPF eh novo
            if (pos == pos3 || novo == 1){
                while(op != 6){
                    //Fiz na lógica de um possivel registro errado de algum dado errado no CPF inserido
                    printf("Qual dado deseja alterar do CPF %s dessa vez?\n1-Nome\n2-Raca\n3-Idade\n4-Salario\n5-CPF\n6-Nenhum\nOpcao: ", censo[pos].cidadaos[pos2].CPF);
                    scanf("%d", &op);
                    if (op == 1){
                        printf("Digite o nome atualizado: ");
                        scanf(" %49[^\n]", censo[pos].cidadaos[pos2].nome);
                    } else if (op == 2){
                        printf("Digite a raca atualizada: ");
                        scanf(" %49[^\n]", censo[pos].cidadaos[pos2].raca);
                    } else if (op == 3){
                        printf("Digite a idade atualizada: ");
                        scanf("%d", &censo[pos].cidadaos[pos2].idade);
                    } else if (op == 4){
                        printf("Digite o salario atualizado: ");
                        scanf("%f", &censo[pos].cidadaos[pos2].salario);
                    }
                    else if (op == 5){
                        printf("Digite o CPF atualizado: ");
                        scanf(" %11[^\n]", censo[pos].cidadaos[pos2].CPF);
                    }
                }
                //Quando o codigo sair do loop de escolhas
                printf("Alteracoes salvas e dados atualizados!\n");   
            }
            //aumentando a capacidade de cidade
            censo[pos].capacidade++;
        } else if (pos != pos3){
            printf("CPF existe em outra cidade...\n");
        }
    } else if (pos == tam){
        //Erro em achar codigo da cidade
        printf("Codigo nao valido...\n");
    }
    return;
}

void Remover(Cidade* censo, int tam){
    Pessoa cache;
    char CPF[12];
    int x, pos1 = tam, pos2, cmp, codigo;
    //Buscando a cidade que o usuario busca
    printf("Digite a cidade em que a pessoa possui registro: ");
    scanf("%d", &codigo);
    for (x = 0; x < tam; x++){
        if (codigo == censo[x].codigo){
            pos1 = x;
        }
    }
    if (pos1 < tam){
        //Procurando o CPF que o usuario busca
        printf("Digite o CPF da pessoa que voce esta procurando: ");
        scanf(" %11[^\n]", CPF);
        pos2 = censo[pos1].capacidade;
        for (x = 0; x < censo[pos1].capacidade; x++){
            cmp = strcmp(censo[pos1].cidadaos[x].CPF, CPF);
            if (cmp == 0){
                pos2 = x;
            }
        }
        if (pos2 < censo[pos1].capacidade){
            //ajustando o vetor de informacoes e diminuindo o tamanho dele, eliminando o conteudo descartado, que sera posicionado no final do vetor com esse proposito
            for (x = pos2; x < (censo[pos1].capacidade - 1); x++){
                cache = censo[pos1].cidadaos[x];
                censo[pos1].cidadaos[x] = censo[pos1].cidadaos[x + 1];
                censo[pos1].cidadaos[x + 1] = cache;
            }
            //realocando memoria. Como esta diminuindo vetor, nao precisa fazer um metodo de seguranca para excesso de memoria (liberando memoria nesse caso)
            censo[pos1].cidadaos = (Pessoa*) realloc(censo[pos1].cidadaos, (censo[pos1].capacidade - 1) * sizeof(Pessoa));
            censo[pos1].capacidade--;
            printf("Informacoes do CPF inserido foram eliminadas com sucesso!\n");
            //print de erros nas linhas finais do codigo
        } else{
            printf("Erro em achar CPF...\n");
        }
    } else {
        printf("Erro em achar cidade...\n");
    }
    return;
}

void Procura(Cidade* censo, int tam){
    Pessoa cache;
    char CPF[12];
    int x, pos1 = tam, pos2, cmp, codigo;
    //Buscando a cidade que o usuario busca
    printf("Digite a cidade em que a pessoa possui registro: ");
    scanf("%d", &codigo);
    for (x = 0; x < tam; x++){
        if (codigo == censo[x].codigo){
            pos1 = x;
        }
    }
    if (pos1 < tam){
        //Procurando o CPF que o usuario busca
        printf("Digite o CPF da pessoa que voce esta procurando: ");
        scanf(" %11[^\n]", CPF);
        pos2 = censo[pos1].capacidade;
        for (x = 0; x < censo[pos1].capacidade; x++){
            cmp = strcmp(censo[pos1].cidadaos[x].CPF, CPF);
            if (cmp == 0){
                pos2 = x;
            }
        }
        if (pos2 < censo[pos1].capacidade){
            //imprimindo informacoes do cpf inserido
            printf("CPF achado! Dados a seguir:\n");
            printf("Nome: %s\n", censo[pos1].cidadaos[pos2].nome);
            printf("Raca: %s\n", censo[pos1].cidadaos[pos2].raca);
            printf("Idade: %d\n", censo[pos1].cidadaos[pos2].idade);
            printf("Salario: %f\n", censo[pos1].cidadaos[pos2].salario);
            printf("CPF: %s\n", censo[pos1].cidadaos[pos2].CPF);
        } else{
            //mensagens de erro de novo para caso a informacao procurada nao esteja no local em que está sendo realizada a busca
            printf("Erro em achar CPF...\n");
        }
    } else {
        printf("Erro em achar cidade...\n");
    }
    return;
}

void ViewTable(Cidade* censo, int tam){
    int x, y, booleano = 0;
    if (censo[x].cidadaos == NULL){
        booleano = 1;
    }
    //impressao de todos os dados armazenados, caso existam
    if (booleano == 0){
        for (x = 0; x < tam; x++){
            for (y = 0; y < censo[x].capacidade; y++){
                printf("Pessoa %d da cidade %s:\n", y + 1, censo[x].nome);
                printf("Nome: %s\n", censo[x].cidadaos[y].nome);
                printf("Raca: %s\n", censo[x].cidadaos[y].raca);
                printf("Idade: %d\n", censo[x].cidadaos[y].idade);
                printf("Salario: %f\n", censo[x].cidadaos[y].salario);
                printf("CPF: %s\n", censo[x].cidadaos[y].CPF);
            }
        }
    } else if (booleano == 1){
        printf("Sem dados registrados!\n");
    }
    return;
}

void Desaloca(Cidade* censo, int tam){
    //liberando a memoria alocada na funcao
    int x;
    for (x = 0; x < tam; x++){
        free(censo[x].cidadaos);
    }
    free(censo);
}