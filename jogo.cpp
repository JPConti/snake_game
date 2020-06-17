#include <GL/glut.h>
#include <GL/gl.h>
#include <ctime>
#include "jogo.h"

int gridX, gridY;
bool comida = true; ///variavel para saber se precisa de uma nova comida ou nao
int comidaX, comidaY;
short sDirection = RIGHT; ///Direção atual da cobra
extern bool gameOver;
extern int pontos;

int cobraTam = 5;
int posX[60]={20,20,20,20,20}, posY[60]={20,19,18,17,16}; ///Posição da Cobra inicia no meio, inicia as primeiras 5 posições que é o tamanho inicial da cobra

/// Recebe as cordenadas e armazena nas variaveis
void initGrid(int x, int y)
{
    gridX = x;
    gridY = y;
}

/// Função para desenhar a Grade
void desenhaGrid()
{
    for(int x=0; x<gridX; x++){
        for(int y=0; y<gridY; y++){
            unidade(x,y); ///desenha um quadrado no ponto (x, y)
        }
    }
}

/// Cria um quadrado unitário
void unidade(int x, int y)
{
    /*glLineWidth(1.0); ///Expessura da linha
    glColor3f(1.0,1.0,1.0); ///Cor da linha*/
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1){ /// Se estiver na borda
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    } else { ///se nao for borda
        glLineWidth(1.0); ///Expessura da linha
        glColor3f(1.0,1.0,1.0); ///Cor da linha
    }
    ///Pode desenhar varias progressoes geometricas, (triangulo, quadrado, etc)
    glBegin(GL_LINE_LOOP); ///No caso é o loop de linhas

        /// Vertice 2D (x,y)
        /// Posições vao mudando até que se forme o quadrado
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);


    glEnd(); /// Para quando finalizar o desenho
}

/// Desenha as comidas aleatoriamente
void desenhaComida(){
    if(comida){ ///se precisa criar nova comida
        random(comidaX, comidaY);
    }
    //mesmo se a comida nao precisar ser criada num novo local,  ele mantem falso e recria no mesmo lugar que ja estava
    comida=false;
    glColor3f(0.0,1.0,0.0); ///cor da comida
    glRectf(comidaX, comidaY, comidaX+1, comidaY+1); ///Desenha a comida
}

void desenhaCobra()
{
    ///atualiza a cobra para que um quadrado seja igual ao qquadrado que estava na frente
    for(int i=cobraTam-1; i>0; i--){
        posX[i] = posX[i-1];
        posY[i] = posY[i-1];
    }

    ///verifica a direção que esta indo e adiciona (remove) posições
    if(sDirection==UP){
        posY[0]++;
    } else if(sDirection==DOWN){
        posY[0]--;
    } else if(sDirection==LEFT){
        posX[0]--;
    } else if(sDirection==RIGHT){
        posX[0]++;
    }

    ///desenha a cobra
    for(int i=0; i<cobraTam; i++){
        if(i==0){ ///cabeca da cobra
            glColor3f(0.2,0.2,1.0);
        } else {
            glColor3f(1.0,1.0,1.0);
        }
        glRectd(posX[i], posY[i], posX[i]+1, posY[i]+1); ///gera um quadrado das posições
    }



    ///Se a cobra chegar na beirada
    if(posX[0]==0 || posX[0]==gridX-1 || posY[0]==0 || posY[0]==gridY-1){
            gameOver = true;
    }
    if(posX[0]==comidaX && posY[0]==comidaY){ ///se a cabeca da cobra e a comida estiverem na mesma posição
        pontos++;
        cobraTam++;
        if(cobraTam>MAX){
            cobraTam=MAX; ///SE chegar no tamanho maximo ela para de crescer
        }
        comida = true;
    }
}

/// funcao para gerar a posição da comida
void random(int &x, int &y) ///recebe referencia de x e y
{
    ///valores nesse intervalo pq a comida nao deve aparecer nas bordas vermelhas
    int _maxX = gridX-2;
    int _maxY = gridY-2;
    int _min = 1;

    srand(time(NULL)); ///gera um valor aleatorio de acordo com o tempo (retorna um valor inteiro)

    x = _min + rand() % (_maxX - _min);
    y = _min + rand() % (_maxY - _min);
}
