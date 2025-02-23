#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h> // Para Sleep() no Windows
#else
    #include <unistd.h>  // Para usleep() no Linux/MacOS
#endif

void limpa_tela();
void cair_numeros();
void Mostra(int nro, int nro_seguinte);
void empilhar(int coluna, int numero);
int verificar_e_realizar_operacoes(int coluna);
int realizar_operacoes_proximas(int coluna);
void salvar_pontuacao(const char *nickname, int pontuacao);
void usar_martelo(); 

// Matriz do jogo
int matriz_jogo[10][5] = {0};

// Pontuacao do jogador
int pontuacao = 0;

// Pontuacao minima para usar o martelo
const int pontuacao_para_martelo = 5000;

int martelo_disponivel = 1;

void limpa_tela() {
    // Limpar a tela dependendo do sistema operacional
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
}

// Estado atual do jogo
void Mostra(int nro, int nro_seguinte) {
    limpa_tela();
    printf("           +----+  +----+\n");
    printf("           |%4d|  |%4d|\n", nro, nro_seguinte);
    printf("           +----+  +----+\n");
    for (int i = 9; i >= 0; i--) {
        printf("  +----+----+----+----+----+\n");
        printf("  |");
        for (int j = 0; j < 5; j++) {
            if (matriz_jogo[i][j] != 0)
                printf("%4d|", matriz_jogo[i][j]);
            else
                printf("    |");
        }
        printf("\n");
    }
    printf("  +----+----+----+----+----+\n");
    printf("  +----+----+----+----+----+\n");
    printf("  |  1 |  2 |  3 |  4 |  5 |\n");
    printf("  +----+----+----+----+----+\n\n");

    // Exibir a pontuacao atual
    printf("Pontuacao: %d\n\n", pontuacao);

    // Informar que o martelo esta disponivel
if (martelo_disponivel) {
        printf("Martelo disponivel! Use a tecla '6' para ativar (necessario ao menos %d pontos).\n\n", pontuacao_para_martelo);
    }
}

// Empilhar um numero em uma coluna
void empilhar(int coluna, int numero) {
    for (int i = 0; i < 10; i++) {
        if (matriz_jogo[i][coluna] == 0) {
            matriz_jogo[i][coluna] = numero;
            return;
        }
    }
    printf("Coluna cheia! Tente outra coluna.\n");
}

// Função para realizar operações e aplicar as regras
int verificar_e_realizar_operacoes(int coluna_escolhida) {
    int operacoes_realizadas = 0;

    // Percorre a matriz linha por linha, começando pela coluna escolhida
    for (int i = 0; i < 10; i++) {
        // Se a célula está vazia, ignora
        if (matriz_jogo[i][coluna_escolhida] == 0) {
            continue;
        }

        int numero = matriz_jogo[i][coluna_escolhida];
        int multiplicador = 1;

        // Verifica os vizinhos: abaixo, à direita e à esquerda
        if (i < 9 && matriz_jogo[i + 1][coluna_escolhida] == numero) {  // Abaixo
            multiplicador *= 2;
        }
        if (coluna_escolhida < 4 && matriz_jogo[i][coluna_escolhida + 1] == numero) {  // Direita
            multiplicador *= 2;
        }
        if (coluna_escolhida > 0 && matriz_jogo[i][coluna_escolhida - 1] == numero) {  // Esquerda
            multiplicador *= 2;
        }

        // Se houve algum vizinho igual, realiza a operação
        if (multiplicador > 1) {
            matriz_jogo[i][coluna_escolhida] = numero * multiplicador;
            pontuacao += matriz_jogo[i][coluna_escolhida];

            // Limpa os vizinhos que participaram da operação
            if (i < 9 && matriz_jogo[i + 1][coluna_escolhida] == numero) {
                matriz_jogo[i + 1][coluna_escolhida] = 0;
            }
            if (coluna_escolhida < 4 && matriz_jogo[i][coluna_escolhida + 1] == numero) {
                matriz_jogo[i][coluna_escolhida + 1] = 0;
            }
            if (coluna_escolhida > 0 && matriz_jogo[i][coluna_escolhida - 1] == numero) {
                matriz_jogo[i][coluna_escolhida - 1] = 0;
            }

            operacoes_realizadas = 1;  // Marca que houve operações
        }
    }

    // Após realizar as operações, faz os números caírem para preencher os espaços
    cair_numeros();

    return operacoes_realizadas;
}

// Realizar operacoes com numeros proximos
int realizar_operacoes_proximas(int coluna) {

    int operacoes_realizadas = 0;

    while (verificar_e_realizar_operacoes(coluna)) {
        operacoes_realizadas = 1;

        Mostra(0, 0);
    }

    return operacoes_realizadas;
}

// Fazer os numeros cairem para preencher espacos vazios
void cair_numeros() {
    for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 9; i++) {
        if (matriz_jogo[i][j] == 0) {
            for (int k = i + 1; k < 10; k++) {
                    if (matriz_jogo[k][j] != 0) {

                        matriz_jogo[i][j] = matriz_jogo[k][j];
                        matriz_jogo[k][j] = 0;

                        Mostra(0, 0);
                        break;
                }
            }
        }
    }
    }
}

// Usar o martelo para remover um numero da matriz
void usar_martelo() {
    if (pontuacao < pontuacao_para_martelo) {
    printf("Voce precisa de pelo menos %d pontos para usar o martelo.\n", pontuacao_para_martelo);
    return;
    }

    int linha, coluna;

    printf("Digite a linha (1-10) e a coluna (1-5) onde deseja usar o martelo: ");
    if (scanf("%d %d", &linha, &coluna) != 2 || linha < 1 || linha > 10 || coluna < 1 || coluna > 5) {
    printf("Posicao invalida! Tente novamente.\n");
    return;
    }

    linha--;  
    coluna--;
    matriz_jogo[linha][coluna] = 0;
    cair_numeros();
    realizar_operacoes_proximas(coluna);
    martelo_disponivel = 1; 
    Mostra(0, 0);
}

// Salvar a pontuacao e o nome do jogador no ranking
void salvar_pontuacao(const char *nickname, int pontuacao) {

    FILE *file = fopen("ranking.bin", "ab");

    struct {
        char nickname[20];
        int pontuacao;
    } jogador;

    strncpy(jogador.nickname, nickname, 19);

    jogador.nickname[19] = '\0';
    jogador.pontuacao = pontuacao;

    fwrite(&jogador, sizeof(jogador), 1, file);
    fclose(file);
}

// Funcao principal
int main() {
    FILE *file;
    int numeros[100], i = 0;

    file = fopen("numeros.txt", "r");
    while (i < 100 && fscanf(file, "%d", &numeros[i]) != EOF) i++;
    fclose(file);

    if (i == 0) {
        printf("O arquivo esta vazio!\n");
        return 1;
    }

    int posicao;
    char nickname[20];
    FILE *temp = fopen("nickname.txt", "r");
    fscanf(temp, "%19s", nickname);
    fclose(temp);

    for (i = 0; i < 99; i++) {
        Mostra(numeros[i], numeros[i + 1]);
        
        printf("Escolha uma coluna (1-5), digite 6 para usar o martelo ou 0 para sair: ");
        if (scanf("%d", &posicao) != 1 || posicao < 0 || posicao > 6) {
            printf("Opcao invalida. Encerrando o jogo.\n");
            break;
        }

        if (posicao == 0) {
            printf("Saindo do jogo...\n");
            salvar_pontuacao(nickname, pontuacao);
            break;
        }

        if (posicao == 6 && martelo_disponivel) {
            usar_martelo();
            continue;
        } else if (posicao == 6) {
            printf("Voce nao possui um martelo disponivel.\n");
            continue;
        }

        empilhar(posicao - 1, numeros[i]);
        realizar_operacoes_proximas(posicao - 1);
    }

    printf("Fim do jogo! Sua pontuacao final: %d\n", pontuacao);
    return 0;
}