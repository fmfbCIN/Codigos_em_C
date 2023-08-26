#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    char remetente[50];
    char assunto[50];
    char mensagem[200];
}email;

typedef struct{
    char nome[50];
    char senha[50];
    int qtdRecebidos, qtdEnviados;
    email *recebidos;
    email *enviados;
}Usuario;

void cadastrarUsuario(char *nome, char *senha, Usuario **usuario, int *tam);
void login(char *nome, char *senha, Usuario **usuario, int tam);
void enviarEmail(char *nome, Usuario **usuario, int tam);
void verRecebidos(Usuario usuario);
void verEnviados(Usuario usuario);

int main(){
    int op1 = 0, op2, tam = 0;
    char nome[50], senha[50];
    Usuario *usuario = NULL;
    while (op1 != 3){
        printf("Escolha uma opcao:\n1-Cadastrar\n2-Fazer Login\n3-Sair\nOpcao: ");
        scanf("%d", &op1);
        if (op1 == 1){
            cadastrarUsuario(&nome, &senha, &usuario, &tam);
        } else if (op1 == 2){
            login(&nome, &senha, &usuario, tam);
        }
    }
    return 0;
}

void cadastrarUsuario(char *nome, char *senha, Usuario **usuario, int *tam){
    int booleano = 0, temp = 0, x, op;
    while (booleano == 0){
        temp = 0;
        printf("Cadastre login: ");
        scanf(" %49[^\n]", *nome);
        if(*tam != 0){
            for (x = 0; x < *tam; x++){
                if (strcmp(*nome, (*usuario)[x].nome) == 0){
                    temp = 1;
                }
            }
            if (temp == 0){
                booleano = 1;
                op = 0;
                while (op != 1 && op != 2){
                    printf("Usuário já existe! Deseja continuar ou retornar ao menu?\n");
                    printf("1-Continuar\n2-Retornar\n");
                    scanf("%d", &op);
                }
                if (op == 2){
                    return;
                }
            }
        }
    }
    *usuario = (Usuario *)realloc(*usuario, *tam + 1);
    strcpy((*usuario)[*tam - 1].nome, *nome);
    printf("Digite a senha ");
    scanf(" %49[^\n]", *senha);
    strcpy((*usuario)[*tam - 1].senha, *senha);
    (*usuario)[*tam - 1].recebidos = NULL;
    (*usuario)[*tam - 1].enviados = NULL;
    (*usuario)[*tam - 1].qtdRecebidos = 0;
    (*usuario)[*tam - 1].qtdEnviados = 0;
    return;
}

void login(char *nome, char *senha, Usuario **usuario, int tam){
    int x, pos = -1, op = 0, booleano = 0;
    while (booleano == 0){
        printf("Digite seu login: ");
        scanf(" %49[^\n]", *nome);
        for (x = 0; x < tam; x++){
            if (strcmp(*nome, (*usuario)[x].nome) == 0){
                pos = x;
            }
        }
        if (pos == -1){
            while (op != 1 && op != 2){
                printf("Erro ao encontrar usuario! Deseja continuar?\n");
                printf("1-Continuar\n2-Retornar\n");
                scanf("%d", &op);
            }
            if (op == 2){
                return;
            }
        }
        else {
            booleano = 1;
        }
    }
    booleano = 0;
    op = 0;
    while (booleano == 0){
        printf("Digite a senha: ");
        scanf(" %49[^\n]", *senha);
        if (strcmp (*senha, (*usuario)[pos].senha) != 0){
             while (op != 1 && op != 2){
                printf("Senha errada! Deseja continuar?\n");
                printf("1-Continuar\n2-Retornar\n");
                scanf("%d", &op);
            }
            if (op == 2){
                return;
            }
        } else {
            booleano = 1;
        }
    }
    op = 0;
    while (op != 1 && op != 2 && op != 3 && op != 4){
        printf("Login realizado com sucesso! Qual opção deseja selecionar?\n");
        printf("1-Enviar e-mail\n2-Ver e-mails recebidos\n3-Ver e-mails enviados\n4-Sair\nOpcao: ");
        scanf("%d", &op);
        char nomeRemetente[50];
        if (op == 1){
            enviarEmail((*nome), &(*usuario), tam);
        } else if (op == 2){
            verRecebidos((*usuario)[pos]);
        } else if (op == 3){
            verEnviados((*usuario)[pos]);
        } else if (op == 4){
            return;
        }
    }
}

void enviarEmail(char *nome,  Usuario **usuario, int tam){
    char destinatario[50];
    int x, env, pos = -1, booleano = 0, op = 0;
    while (booleano == 0){
        scanf (" %49[^\n]", destinatario);
        for (x = 0; x < tam; x++){
            if (strcmp((*usuario)[x].nome, destinatario) == 0){
                pos = x;
            }
            if (strcmp((*usuario)[x].nome, *nome) == 0){
                env = x;
            }
        }
        if (pos == -1){
            while (op != 1 && op != 2){
                printf("Destinatario nao existe, deseja tentar enviar novo e-mail ou retornar?");
                printf("\n1-Enviar novamente\n2-Sair\nOpcao: ");
                scanf("%d", &op);
                if (op == 2){
                    return;
                }
            }
        } else {
            (*usuario)[pos].recebidos = (email *) realloc((*usuario)[pos].recebidos, ((*usuario)[pos].qtdRecebidos + 1) * sizeof(email));
            (*usuario)[env].enviados = (email *) realloc((*usuario)[env].enviados, ((*usuario)[env].qtdEnviados + 1) * sizeof(email));
            strcpy ((*usuario)[pos].recebidos[(*usuario)[pos].qtdRecebidos].remetente, *nome);
            strcpy ((*usuario)[env].enviados[(*usuario)[env].qtdEnviados].remetente, destinatario);
            printf("Assunto da mensagem: ");
            scanf(" %49[^\n]", (*usuario)[pos].recebidos[(*usuario)[pos].qtdRecebidos].assunto);
            strcpy((*usuario)[env].enviados[(*usuario)[pos].qtdEnviados].assunto,(*usuario)[pos].recebidos[(*usuario)[pos].qtdRecebidos].assunto);
            printf("Mensagem:\n");
            scanf(" %199[^\n]", (*usuario)[pos].recebidos[(*usuario)[pos].qtdRecebidos].mensagem);
            strcpy((*usuario)[env].enviados[(*usuario)[pos].qtdEnviados].mensagem,(*usuario)[pos].recebidos[(*usuario)[pos].qtdRecebidos].mensagem);
            (*usuario)[pos].qtdRecebidos++;
            (*usuario)[env].qtdEnviados++;
            booleano = 1;
            return;
        }
    }

}

void verRecebidos(Usuario usuario){
    int x;
    if (usuario.qtdRecebidos != 0){
        for (x = 0; x < usuario.qtdRecebidos; x++){
            printf("Enviado para: %s\n",usuario.recebidos[x].remetente);
            printf("Assunto: %s\n",usuario.recebidos[x].assunto);
            printf("Mensagem: %s\n",usuario.recebidos[x].mensagem);
        }
    } else {
        printf("Sem mensagens recebidas!\n");
    }
    return;
}

void verEnviados(Usuario usuario){
    int x;
    if (usuario.qtdEnviados != 0){
        for (x = 0; x < usuario.qtdEnviados; x++){
            printf("Enviado para: %s\n",usuario.enviados[x].remetente);
            printf("Assunto: %s\n",usuario.enviados[x].assunto);
            printf("Mensagem: %s\n",usuario.enviados[x].mensagem);
        }
    } else {
        printf("Sem mensagns enviadas!\n");
    }
    return;
}