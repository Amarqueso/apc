// Arthur Marques Vida de Oliveira - 242038820

#include <stdio.h>
#include <stdlib.h>

int main() {
    char nickname[20];

    
    printf("\nBem vindo(a) ao jogo de DROP MERGE de APC!!!!\n");
    printf("Informe o seu nickname: ");
    scanf("%19s", nickname);


    FILE *temp = fopen("nickname.txt", "w");
    fprintf(temp, "%s", nickname);
    fclose(temp);

    
    if (system(".\\menu.exe") != 0) {
        return 1;
    }

    return 0;
}