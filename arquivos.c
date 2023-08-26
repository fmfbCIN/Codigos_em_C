#include <stdio.h>

int main(){
    FILE *meuArq;
    int num = 250;
    if((meuArq = fopen("teste.bin","w") != NULL)){
        fwrite (&num , sizeof(int), 1, meuArq);
        printf("Tudo deu certo\n");
    } else {
        printf("Arquivo não pode ser criado");
    }
}