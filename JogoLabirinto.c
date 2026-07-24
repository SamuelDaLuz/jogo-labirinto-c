#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define N 10

// DEFINIÇÃO DE CORES ANSI
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

void mostrarLabirinto(int lab[N][N], int px, int py);
void tocarSom(int tipo);
int validarMovimento(int lab[N][N], int x, int y);

int main() {

    int labirinto[N][N] = {
        {0, 1, 0, 0, 0, 0, 1, 0, 0, -2},
        {0, 1, 0, 1, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, -2, 0, 0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, -2, 1, 1, 1, 1, 1, 0, 0, -1}
    };

    int x = 0, y = 0;   // POSIÇÃO INICIAL
    int passos = 0, pontos = 0;
    char comando;
    int jogando = 1;

    while (jogando) {
        system("cls"); // LIMPA A TELA DO WINDOWS

        printf("=== LABIRINTO ===\n");
        printf("@(JOGADOR) |(PAREDE) #(SAIDA) X(ARMADILHA)\n");
        printf("------------------------------------\n");
        printf("Posicao Atual: Linha [%d] Coluna [%d]\n", x, y);
        printf("Movimentos: %d | Pontuacao: %d\n", passos, pontos);
        printf("------------------------------------\n\n");

        mostrarLabirinto(labirinto, x, y);

        // VERIFICA A CONDIÇÃO DE VITÓRIA OU DERROTA
        if (labirinto[x][y] == -1) {
            tocarSom(3); // SOM QUANDO VENCER
            printf("\nVoce GANHOU e escapou com %d pontos e %d movimentos\n", pontos, passos);
            break;
        }
        if (labirinto[x][y] == -2) {
            tocarSom(2); // SOM MAIS GRAVE QUANDO PERDER
            printf("\nVoce caiu em uma armadilha e PERDEU o jogo!\n");
            break;
        }

        printf("\nBOA SORTE! -> W(cima) A(esquerda) S(baixo) D(direita): ");
        scanf(" %c", &comando);
        comando = toupper(comando);

        int nx = x, ny = y;

        if (comando == 'W') nx--;
        else if (comando == 'S') nx++;
        else if (comando == 'A') ny--;
        else if (comando == 'D') ny++;

        // VALIDAÇÃO DO MOVIMENTO
        int resultado = validarMovimento(labirinto, nx, ny);

        if (resultado == 1) { // MOVIMENTO VALIDO
            x = nx;
            y = ny;
            passos++;
            pontos += 2;
            tocarSom(1); // SOM DO MOVIMENTO
        } else { // QUANDO BATE NA PAREDE
            pontos -= 1;
            tocarSom(2); // SOM DA BATIDA
        }
    }

    system("pause");
    return 0;
}

// FUNÇÕES MODULARIZADAS

void mostrarLabirinto(int lab[N][N], int px, int py) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == px && j == py) {
                printf(GREEN "@ " RESET); // JOGADOR
            } else if (lab[i][j] == 1) {
                printf(RED "| " RESET);    // PAREDE
            } else if (lab[i][j] == -1) {
                printf(BLUE "# " RESET);    // SAÍDA
            } else if (lab[i][j] == -2) {
                printf(YELLOW "X " RESET);   // ARMADILHA
            } else {
                printf(". ");               // CAMINHO
            }
        }
        printf("\n");
    }
}

int validarMovimento(int lab[N][N], int x, int y) {
    // VERIFICA SE TÁ NOS LIMITES DA MATRIZ
    if (x >= 0 && x < N && y >= 0 && y < N) {
        // VERIFICA SE NÃO É UMA PAREDE
        if (lab[x][y] != 1) {
            return 1; // SUCESSO
        }
    }
    return 0; // INVÁLIDO
}

void tocarSom(int tipo) {
    switch (tipo) {
        case 1: // MOVIMENTO CORRETO: SOM MAIS AGUDO
            Beep(1200, 50);
            break;
        case 2: // BATIDA NA PAREDE: SOM GRAVE
            Beep(200, 150);
            break;
        case 3: // SOM DA VITÓRIA: AGUDO
            Beep(1200, 50);
            break;
    }
}

