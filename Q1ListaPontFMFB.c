#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char c = 'a', *pc;
    pc = &c;
    //1.A
    printf("Valor de c e endereco dele: %c %p\n", c, &c);
    //1.B
    printf("Valor de pc e endereco do valor dele: %c %p\n", *pc, pc);
    //1.C
    printf("Endereco de pc: %p\n", &pc);
    //1.D
    printf("endereço do valor guardado no endereço apontado por pc: %p\n", &*pc);
    printf("valor guardado no endereço de pc: %p", *&pc);
    /*
    Resposta:
    Porque no endereço de pc é armazenado o endereço (valor) da variável em que pc aponta.
    Ou seja, o valor guardado no endereço de pc é justamente o endereço do valor
    guardado no endereço apontado por ele mesmo.
    */
    /*
    
    */
    return 0;
}