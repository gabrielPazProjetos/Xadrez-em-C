#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TAM 8

char tabuleiro[TAM][TAM];

void inicializarTabuleiro() {
    // Pretas
    char linha1[] = {'T','C','B','D','R','B','C','T'};
    char linha2[] = {'P','P','P','P','P','P','P','P'};
    // Brancas
    char linha7[] = {'p','p','p','p','p','p','p','p'};
    char linha8[] = {'t','c','b','d','r','b','c','t'};

    for (int i = 0; i < TAM; i++) {
        tabuleiro[0][i] = linha1[i];
        tabuleiro[1][i] = linha2[i];
        tabuleiro[6][i] = linha7[i];
        tabuleiro[7][i] = linha8[i];
    }

    for (int i = 2; i < 6; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '.';
}

void mostrarTabuleiro() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int isBranco(char peca) {
    return islower(peca);
}

int isPreto(char peca) {
    return isupper(peca);
}

int isAdversario(char peca, int turno) {
    return (turno == 0 && isPreto(peca)) || (turno == 1 && isBranco(peca));
}

int movimentoValidoPeao(int x1, int y1, int x2, int y2, int turno) {
    int dir = (turno == 0) ? -1 : 1;
    char destino = tabuleiro[x2][y2];

    // Movimento simples
    if (y1 == y2 && destino == '.' && x2 == x1 + dir)
        return 1;

    // Movimento duplo no primeiro turno
    if (y1 == y2 && destino == '.' && x2 == x1 + 2 * dir &&
        ((turno == 0 && x1 == 6) || (turno == 1 && x1 == 1)) &&
        tabuleiro[x1 + dir][y1] == '.')
        return 1;

    // Captura
    if (abs(y2 - y1) == 1 && x2 == x1 + dir && isAdversario(destino, turno))
        return 1;

    return 0;
}

int movimentoValido(int x1, int y1, int x2, int y2, int turno) {
    char peca = tabuleiro[x1][y1];
    if (peca == '.') return 0;
    if ((turno == 0 && !isBranco(peca)) || (turno == 1 && !isPreto(peca))) return 0;
    if ((turno == 0 && isBranco(tabuleiro[x2][y2])) || (turno == 1 && isPreto(tabuleiro[x2][y2]))) return 0;

    if (tolower(peca) == 'p')
        return movimentoValidoPeao(x1, y1, x2, y2, turno);

    // Para outras peças, permitir movimento livre (sem validação real)
    return 1;
}

int main() {
    inicializarTabuleiro();
    int turno = 0;
    char origem[3], destino[3];

    while (1) {
        mostrarTabuleiro();
        printf("Turno do %s\n", turno == 0 ? "branco" : "preto");

        printf("Origem (ex: e2): ");
        scanf("%s", origem);
        printf("Destino (ex: e4): ");
        scanf("%s", destino);

        int x1 = 8 - (origem[1] - '0');
        int y1 = origem[0] - 'a';
        int x2 = 8 - (destino[1] - '0');
        int y2 = destino[0] - 'a';

        if (x1 < 0 || x1 >= TAM || y1 < 0 || y1 >= TAM || x2 < 0 || x2 >= TAM || y2 < 0 || y2 >= TAM) {
            printf("Coordenadas inválidas!\n");
            continue;
        }

        if (movimentoValido(x1, y1, x2, y2, turno)) {
            tabuleiro[x2][y2] = tabuleiro[x1][y1];
            tabuleiro[x1][y1] = '.';
            turno = 1 - turno;
        } else {
            printf("Movimento inválido!\n");
        }
    }

    return 0;
}
