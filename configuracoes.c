// Arthur Marques Vida de Oliveira - 242038820

#include <stdio.h>
#include <stdlib.h>


void zerar_ranking();
void voltar_ao_menu();

int main() {
    int opcao;

    while (1) {
        printf("\n*** MENU CONFIGURACOES ***\n");
        printf("1 - Zerar Ranking\n");
        printf("2 - Modo de Dificuldade (em desenvolvimento...)\n");
        printf("3 - Voltar ao Menu Principal\n");
        printf("\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                zerar_ranking();
                break;

            case 2:
                printf("Modo de dificuldade em desenvolvimento...\n");
                break;

            case 3:
                voltar_ao_menu();
                return 0;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}

void zerar_ranking() {
    char confirmacao;
    printf("Tem certeza de que deseja zerar o ranking? (S/N): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        FILE *file = fopen("ranking.bin", "wb");
        fclose(file);
        printf("Ranking zerado com sucesso!\n\n");
    } else {
        printf("Operacao cancelada. O ranking nao foi alterado.\n\n");
    }
}

void voltar_ao_menu() {
    printf("Voltando ao menu principal...\n");
}