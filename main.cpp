#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include "jogo.h"

#define COLUNAS 40
#define LINHAS 40
#define FPS 10 /// Tempo de gera��o de quadros, por segundo

extern short sDirection;
bool gameOver = false;

int pontos = 0;

void display_callback();
void timer_callback(int);
void reshape_callback(int,int);
void keyboard_callback(int, int, int);

/// FUNCAO QUE INICIA VALORES ANTES DA EXECU��O DO PROGRAMA
void init()
{
    glClearColor(0.0,0.0,0.0,1.0); /// Cor da tela de fundo (varia de 0 a 1) (r, g, b, a)
    initGrid(COLUNAS, LINHAS); ///Inicia a grade
}

int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); ///Modo de exibi��o RGB com Dupla janela (dois buffers em exibi��o)
    glutInitWindowSize(500, 500); ///Tamanho da tela inicial
    glutCreateWindow("JOGO SNAKE"); ///T�tulo da tela
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback); ///Para quando a janela for redimensionada, envia dois valores int do novo tamanho
    glutTimerFunc(0,timer_callback, 0); ///tempo para chamar uma funcao em um numero de milissegundos
    glutSpecialFunc(keyboard_callback); ///Rechebe chamadas do teclado (apenas setas)
    init();
    glutMainLoop();

    return 0;
}


void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT); ///Limpa o buffer de cores para que fique com a cor expecificada no init
    desenhaGrid(); ///Cria o Grid toda vez que a nova janela for criada
    desenhaCobra();
    desenhaComida(); ///chama depois de desenhar a cobra pois � feita a verificacao se estao na mesma posicao primeiro
    glutSwapBuffers(); ///Faz uma varredura no buffer e exibe o novo quadro

    ///se o jogo acabar
    if(gameOver){
        char _pontos[10];
        itoa(pontos, _pontos, 10); ///converte do primeiro para segundo, o 10 significa que o primeiro valor � decimal
        char text[50] = "Sua pontua��o foi de: ";
        strcat(text, _pontos); ///funcao de concatenacao, concatena _pontos em text
        MessageBox(NULL,text,"FIM DE JOGO",0); ///(ID da janela, texto, legenda, 0)
        exit(0); ///sai do jogo
    }
}

void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h); ///Cobrir a janela inteira
    glMatrixMode(GL_PROJECTION); ///Matriz de proge��o
    glLoadIdentity(); ///Garante que nao havera alteracoes na matriz, ser� padr�o inicial

    ///Proje��o Ortogr�fica -> em rela��o a janela (esq, dir, bai, cima, perto, longe (dos objetos mostrados, como eixo z))
    glOrtho(0.0, COLUNAS, 0.0, LINHAS, -1.0, 1.0); /// 0.0 para 40.0 (distancia entre esq -> dir e baixo -> cima)

    glMatrixMode(GL_MODELVIEW);


}

void timer_callback(int)
{
    glutPostRedisplay(); ///fun��o de exibi��o ser� chamada (display_callback) para a cria��o de um novo quadro
    glutTimerFunc(800/FPS, timer_callback, 0);
}

/// Fun��o que le o comando  digitado no teclado
void keyboard_callback(int key, int,int) ///le apenas o comando, nao precisa das posi��es
{

    switch(key)
    {
    case GLUT_KEY_UP:
        ///Primeiro verifica se nao esta indo na dire��o oposta
        ///pq a cobra nao vira 180�
        if(sDirection!=DOWN){
            sDirection=UP;
        }
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP){
            sDirection=DOWN;
        }
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT){
            sDirection=LEFT;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT){
            sDirection=RIGHT;
        }
        break;
    }
}
