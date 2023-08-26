#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int tamentrada, tamfinal;
    char *vetfinal = NULL;
    char *aux;
    aux = vetfinal;
    char entrada[100];
    while (scanf(" %99[^\n]", entrada) != EOF){
        tamentrada = strlen(entrada);
        tamfinal = tamfinal + tamentrada;
        vetfinal = realloc(vetfinal, tamfinal * sizeof(char));
        if (vetfinal == NULL){
            printf("Erro de alocacao!\n");
            free(aux);
            exit(1);
        }
        strcat (vetfinal, entrada);
    }
    printf("%s", vetfinal);
    free(vetfinal);
    return 0;
}