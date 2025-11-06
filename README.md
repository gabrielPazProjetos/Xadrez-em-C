--- Jogo de Xadrez em C
Este é um jogo de xadrez simples feito em linguagem C, jogado diretamente no terminal. Ele foi desenvolvido com fins educacionais e demonstra conceitos como matrizes, controle de fluxo, entrada do
usuário e lógica de jogo.

--- Limitações
- Não implementa roque, xeque, xeque-mate, promoção de peão ou en passant
- Não possui verificação de fim de jogo ou empate
- Interface apenas em modo texto (sem gráficos)

--- Funcionalidades
- Tabuleiro exibido em modo texto
- Sistema de turnos entre jogador branco e preto
- Validação completa de movimentos:
  - x Peão: avanço simples, duplo inicial, captura diagonal
  - x Torre: movimentos horizontais e verticais
  - x Bispo: movimentos diagonais
  - x Cavalo: movimentos em L
  - x Rainha: combinação de torre e bispo
  - x Rei: uma casa em qualquer direção
- Captura de peças adversárias
- Verificação de caminho livre para peças deslizantes (torre, bispo, rainha)

  gcc xadrez.c -o xadrez
  ./xadrez

  a b c d e f g h
8 T C B D R B C T
7 P P P P P P P P
6 . . . . . . . .
5 . . . . . . . .
4 . . . . . . . .
3 . . . . . . . .
2 p p p p p p p p
1 t c b d r b c t

Origem (ex: e2): e2
Destino (ex: e4): e4
Origem (ex: e2): e2
Destino (ex: e4): e4
