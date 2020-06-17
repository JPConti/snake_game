#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

///CONSTANTES PARA A DIREÇÃO
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

///TAMANHO MAXIMO DA COBRA
#define MAX 60


void initGrid(int x, int y);
void desenhaGrid();
void unidade(int x, int y);
void desenhaCobra();
void desenhaComida();
void random(int &x, int &y);




#endif // JOGO_H_INCLUDED
