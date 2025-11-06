#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define TAM 8

char tabuleiro[TAM][TAM];

void inicializarTabuleiro() {
    char linha1[] = {'T','C','B','D','R','B','C','T'};
    char linha2[] = {'P','P','P','P','P','P','P','P'};
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

int caminhoLivre(int x1, int y1, int x2, int y2) {
    int dx = (x2 > x1) - (x2 < x1);
    int dy = (y2 > y1) - (y2 < y1);
    int i = x1 + dx, j = y1 + dy;
    while (i != x2 || j != y2) {
        if (tabuleiro[i][j] != '.') return 0;
        i += dx;
        j += dy;
    }
    return 1;
}

int movimentoValido(int x1, int y1, int x2, int y2, int turno) {
    char peca = tabuleiro[x1][y1];
    char destino = tabuleiro[x2][y2];
    if (peca == '.') return 0;
    if ((turno == 0 && !isBranco(peca)) || (turno == 1 && !isPreto(peca))) return 0;
    if ((turno == 0 && isBranco(destino)) || (turno == 1 && isPreto(destino))) return 0;

    int dx = x2 - x1;
    int dy = y2 - y1;
    int adx = abs(dx), ady = abs(dy);

    switch (tolower(peca)) {
        case 'p': {
            int dir = (turno == 0) ? -1 : 1;
            if (dy == 0 && dx == dir && destino == '.') return 1;
            if (dy == 0 && dx == 2 * dir && ((turno == 0 && x1 == 6) || (turno == 1 && x1 == 1)) &&
                tabuleiro[x1 + dir][y1] == '.' && destino == '.') return 1;
            if (adx == 1 && ady == 1 && isAdversario(destino, turno)) return 1;
            return 0;
        }
        case 't': return (dx == 0 || dy == 0) && caminhoLivre(x1, y1, x2, y2);
        case 'b': return (adx == ady) && caminhoLivre(x1, y1, x2, y2);
        case 'd': return ((dx == 0 || dy == 0) || (adx == ady)) && caminhoLivre(x1, y1, x2, y2);
        case 'c': return (adx == 2 && ady == 1) || (adx == 1 && ady == 2);
        case 'r': return adx <= 1 && ady <= 1;
        default: return 0;
    }
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
