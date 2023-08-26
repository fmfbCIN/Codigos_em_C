#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int vet[5] = {1,2,3,4,5}, *p, x;
    p = vet;
    //2.a
    printf("Endereco de vet: %p\n", &vet);
    printf("Endereco guardado em p: %p", p);
    printf("\nLetra B:\n");
    //2.b
    for (x = 0; x < 5; x++){
        printf("vet[%d] = %d\n", x, p[x]);
    }
    printf("\nLetra C:\n");
    //2.c
    for (x = 0; x < 5; x++){
        printf("vet[%d] = %d\n", x, *(p + x));
    }
    printf("\nLetra D (parte 1):\n");
    //2.d
    for (x = 0; x < 5; x++){
        printf("vet[%d] = %d\n", x, vet[x]);
    }
    printf("\nLetra D (parte 2):\n");
    for (x = 0; x < 5; x++){
        printf("vet[%d] = %d\n", x, *(vet + x));
    }

    return 0;
}