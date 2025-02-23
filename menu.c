// Arthur Marques Vida de Oliveira - 242038820

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dadosjogador {
    char nickname[20];
    int pontuacao;
};

void exibir_ranking();
void mudar_jogador();
void abrir_configuracoes(); 

int main() {
    char nickname[20];
    FILE *temp = fopen("nickname.txt", "r");
    fscanf(temp, "%19s", nickname);
    fclose(temp);

    int opcao;
    // Menu
    while (1) {
        printf("*** JOGO DROP MERGE de APC ***\n");
        printf("Jogador: %s\n", nickname);
        printf("\n");
        printf("1 - Jogar\n");
        printf("2 - Configuracoes\n");
        printf("3 - Instrucoes (nao implementado)\n");
        printf("4 - Ranking\n");
        printf("5 - Mudar Jogador\n");
        printf("6 - Sair\n");
        printf("\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (system("gcc main.c -o main.exe") != 0) {
                    printf("Erro ao compilar o arquivo main.c.\n");
                    return 1;
                }
                if (system(".\\main.exe") != 0) { 
                    printf("Erro ao executar o jogo.\n");
                    return 1;
                }
                break;

            case 2:
                abrir_configuracoes();
                break;

            case 4:
                exibir_ranking();
                break;

            case 5:
                mudar_jogador();
                return 0; 

            case 6:
                printf("Saindo do jogo. Ate a proxima!\n");
                return 0;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}

// Funcao para exibir o ranking
void exibir_ranking() {
    FILE *file = fopen("ranking.bin", "rb");
    if (!file) {
        printf("Nenhum ranking encontrado.\n");
        return;
    }

    struct dadosjogador jogadores[100];
    int count = 0;

    // Carrega ranking 
    while (fread(&jogadores[count], sizeof(struct dadosjogador), 1, file)) {
        count++;
    }
    fclose(file);

    // Ordena o ranking 
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (jogadores[j].pontuacao < jogadores[j + 1].pontuacao) {
                struct dadosjogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }

    // 10 melhores jogadores
    printf("\n*** TOP 10 RANKING ***\n");
    int max_exibir = count < 10 ? count : 10; 
    for (int i = 0; i < max_exibir; i++) {
        printf("%d. %s - %d pontos\n", i + 1, jogadores[i].nickname, jogadores[i].pontuacao);
    }
    printf("\n");
}

// Mudar o jogador
void mudar_jogador() {
    printf("Mudando jogador...\n");
    if (system(".\\inicio.exe") != 0) { 
        return;
    }
}

// Abrir o menu de configuracoes
void abrir_configuracoes() {
    printf("Abrindo menu de configuracoes...\n");
    if (system("gcc configuracoes.c -o configuracoes.exe") != 0) {
        return;
    }
    if (system(".\\configuracoes.exe") != 0) {
        return;
    }
}