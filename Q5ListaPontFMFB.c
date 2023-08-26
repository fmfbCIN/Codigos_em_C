#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int ID_produto;
    int qtd;
    int preco;
} Dados;
int main(){
    Dados *compras = NULL;
    Dados *aux;
    aux = compras;
    char tipo[4];
    int cmp1 = 1, cmp2, tam = 0, x, y, cache, ID_produto;
    while(cmp1 != 0){
        scanf(" %s", tipo);
        cmp1 = strcmp(tipo, "END");
        if (cmp1 != 0){
            cmp2 = strcmp(tipo, "NEW");
            if (cmp2 == 0){
                tam++;
                compras = realloc(compras, tam * sizeof(Dados));
                if (compras == NULL){
                    printf("Erro de Alocacao!\n");
                    free(aux);
                    exit(1);
                }
                scanf("%d %d %d", &compras[tam - 1].ID_produto, &compras[tam - 1].qtd, &compras[tam - 1].preco);
            }
            cmp2 = strcmp(tipo, "RM");
            if(cmp2 == 0){
                scanf("%d", &ID_produto);
                for (x = 0; x < tam; x++){
                    if (compras[x].ID_produto == ID_produto){
                        for (y = x; y < (tam - 1); y++){
                            compras[y] = compras[y + 1];
                        }
                        tam--;
                        compras = realloc(compras, tam * sizeof(Dados));
                    }
                }
            }
        }
    }
    for (x = 0; x < tam; x++){
        printf("%d %d %d\n", compras[x].ID_produto, compras[x].qtd, compras[x].preco);
    }
    free(compras);
    return 0;
}