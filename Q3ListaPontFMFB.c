#include <stdio.h>
#include <string.h>
int main(){
    char str[50]; // String
    char str_inv[50]; // String invertida
    char *ptr_str = str;
    char *ptr_inv = str_inv;
    int i=-1;
    scanf(" %s", str);
    //continue o código a partir daqui

    for (i = 0; i < strlen(ptr_str); i++){
        ptr_inv[i] = ptr_str[(strlen(ptr_str)) - i - 1];
    }
    printf(" O inverso da string : %s\n\n",str_inv);
    return 0;
}