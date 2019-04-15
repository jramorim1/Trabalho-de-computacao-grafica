/**
* Teclas do jogo:
Space = movimento do player
P = pause/play
Q = Quit Game Imediate
Seta Cima = Aumenta velocidade dos obstaculos
Seta Baixo = Diminui a Velocidade dos obstaculos
Page UP = Deixa o jogo mais facil gerando mais miniblocos
Page DOWN = Deixa o jogo mais dificil gerando menos miniblocos
Mouse = Controla as opções do menu
*
*/

#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "player.h"
#include "obstacle.h"
#include "bg.h"

#include <GL/glut.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// Qtd máxima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 18

#define CUBE_TEXTURE 0
#define 	GLUT_KEY_SPACE   32
#define ALTURA 300
#define LARGURA 400

//GLuint texture_id[MAX_NO_TEXTURES];

GLuint texture[MAX_NO_TEXTURES];
SDL_Surface *TextureImage[MAX_NO_TEXTURES]; 
char bmpFiles[MAX_NO_TEXTURES][7] = {"1.png","2.png","3.png","4.png","5.png","6.png","7.png","8.png","9.png","10.png","11.png","12.png","13.png", 
									"14.png","15.png","16.png", "17.png", "18.png"};
int a=0;
float y1,x1;

static bool drawn = false, perdeu = false, flagMenu = false, instr = false;

Player *player= new Player(200.0,0.0,30.0,50.0);
vector<Obstacle*> obstacles;
vector<BG*> background;
int chance = 50;
float speedObstacles = -5.0;
int tempoPlat = 100;
int tempoBloco = 20;


unsigned long int frameCounter = 0;

void DesenhaRet(int x1, int x2, int y1, int y2){
	glBegin(GL_QUADS);
	
	glTexCoord2i(0 , 1); glVertex2d(x1,y1);
	glTexCoord2f(0 , 0); glVertex2d(x1,y2);
	glTexCoord2f(1 , 0); glVertex2d(x2,y2);
	glTexCoord2f(1, 1); glVertex2d(x2,y1);
	glEnd();
}

void DesenhaInstr(){
	glBindTexture ( GL_TEXTURE_2D, texture[16]);
	
	DesenhaRet(-400, 400, -300, 300);
	
	glBindTexture ( GL_TEXTURE_2D, texture[17]);
	
	DesenhaRet(200, 380, -250, -170);
}
void DesenhaMenu(){
	
	
	glBindTexture ( GL_TEXTURE_2D, texture[9]);
	
	DesenhaRet(-400, 400, -300, 300);
	
	glBindTexture ( GL_TEXTURE_2D, texture[10]);
	
	DesenhaRet(20, 240, 0, 80);
	
	glBindTexture ( GL_TEXTURE_2D, texture[11]);
	
	DesenhaRet(20,240,-110,-30);
	
}

void DesenhaPerdeu(){
	for(int i=0; i < background.size(); i++){
		glBindTexture ( GL_TEXTURE_2D, texture[8]);
		background[i]->draw();
		
	glBindTexture ( GL_TEXTURE_2D, texture[13]);
	
	DesenhaRet(-110,110,-20,60);
	
	glBindTexture ( GL_TEXTURE_2D, texture[14]);
	DesenhaRet(30,110,60,120);
	
	glBindTexture ( GL_TEXTURE_2D, texture[10]);
	DesenhaRet(-300,-80,-250,-170);
	
	glBindTexture ( GL_TEXTURE_2D, texture[15]);
	DesenhaRet(80,300,-250,-170);
	}
}

void Pause(){
	
	glBindTexture ( GL_TEXTURE_2D, texture[12]);
	
	glBegin(GL_QUADS);
	
    glTexCoord2i(0 , 1); glVertex2d(-110,-60);
	glTexCoord2f(0 , 0); glVertex2d(-110,20);
	glTexCoord2f(1 , 0); glVertex2d(110,20);
	glTexCoord2f(1, 1);glVertex2d(110,-60);
	
	glEnd();
	
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-400.0f, 400.0f, -300.0f, 300.0f);
}

int LoadGLTextures(int x)
{

    if (( TextureImage[x] = IMG_Load(bmpFiles[x])))
        {
       	
		glTexEnvi( GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,  GL_MODULATE);
	    glGenTextures( 1, &texture[x] );
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	    glBindTexture( GL_TEXTURE_2D, texture[x] );
 
		glTexImage2D(GL_TEXTURE_2D, 0, 4, TextureImage[x]->w, TextureImage[x]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[x]->pixels );
		glGetError();
		
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	    
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
	    
        }
   		if ( TextureImage[x] )
	    SDL_FreeSurface( TextureImage[x] ); 
	    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void resetGame(){
	player = new Player(200.0,0.0,30.0,50.0);
	obstacles.clear();
	speedObstacles = -5;
	obstacles.push_back(new Obstacle(LARGURA/2, ALTURA-50,400,25,true, speedObstacles));
	obstacles.push_back(new Obstacle(LARGURA/2, -ALTURA+50,400,25, true, speedObstacles));
	frameCounter = 0;
}

void tasten (unsigned char key, int xmouse, int ymouse)
{	
	if(flagMenu){
	switch (key){
		case 'p':
				drawn = !drawn;
			break;
		case GLUT_KEY_SPACE:		
		if(player->grounded){
			player->switchGravity();
			player->grounded = false;
		}
		break;
		case 'q':
			exit(0);
			
		default:
         break;
	}
	}
	glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y) // COLOCAR AQUI O AUMENTO E DIMINUICAO DA VELOCIDADE
{
	if(key == GLUT_KEY_UP){
		speedObstacles = speedObstacles - 0.1;
		//tempoPlat-=2;
	//	tempoBloco-=1;
		for(int i=0; i < obstacles.size(); i++){
		obstacles[i]->changeSpeed(speedObstacles);
	}
}
	if(key == GLUT_KEY_DOWN){
		speedObstacles = speedObstacles + 0.1;
	//	tempoPlat+=10;
	//	tempoBloco+=2;
		if(speedObstacles > -1.0){
			speedObstacles = -1.0;
		}
		for(int i=0; i < obstacles.size(); i++){
		obstacles[i]->changeSpeed(speedObstacles);
	}
}
	if(key == GLUT_KEY_PAGE_UP){
		chance += 10;
		if(chance >= 100)
		chance = 100;
	}
	if(key == GLUT_KEY_PAGE_DOWN){
		chance -= 10;
		if(chance <= 0)
		chance = 0;
	}
	
	glutPostRedisplay();
}

void Setup (void)
{
// Define a cor de fundo da janela de visualização como azul
glClearColor(0.0, 1.0, 1.0, 1.0f);

for(int i=0; i<MAX_NO_TEXTURES; i++)
	LoadGLTextures(i);
	 
 	glShadeModel(GL_FLAT);   
 	glEnable(GL_TEXTURE_2D);
 	
obstacles.push_back(new Obstacle(LARGURA/2, ALTURA-50,400,25,true, speedObstacles));
obstacles.push_back(new Obstacle(LARGURA/2, -ALTURA+50,400,25, true, speedObstacles));

background.push_back(new BG(0));
background.push_back(new BG(-2*LARGURA));
}

void Update(){
	
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (flagMenu){
		
	for(int i=0; i < background.size(); i++){
		glBindTexture ( GL_TEXTURE_2D, texture[8]);
		background[i]->draw();
	}

	glBindTexture ( GL_TEXTURE_2D, texture[a]);
		player->draw();		
	
	for(int i = 0; i<obstacles.size(); i++){
		if(obstacles[i]->ground == true)
		glBindTexture ( GL_TEXTURE_2D, texture[7]);
		else
		glBindTexture ( GL_TEXTURE_2D, texture[6]);
	obstacles[i]->draw();
	
	if(drawn){
		Pause();
	}
}
}
	else 
	if(perdeu){
		DesenhaPerdeu();
	}
	else if(instr){
		DesenhaInstr();
	}
	else{
		DesenhaMenu();
	}
	
	glutSwapBuffers();
}

void animation(int value){
	
	if(flagMenu){

	if(!drawn)
	{
	frameCounter++;
	for(int i=0; i < background.size(); i++){
		background[i]->update();
	}
	
	for(int i = 0; i<obstacles.size(); i++){
		obstacles[i]->update();
			
		if((obstacles[i]->position->x + obstacles[i]->width - 5) <= -LARGURA){
			obstacles.erase(obstacles.begin()+i,obstacles.begin()+i+1);
		}
	}
	
	player->update();
	perdeu = player->testCollision();
	if(perdeu)
		flagMenu = false;
	player->rotate();
	
		for(int i = 0; i<obstacles.size(); i++){
		player->hit(obstacles[i]);
	}

	if(frameCounter % tempoPlat == 0){
		float random = (float)( ALTURA - 30 - (rand() % 120));
		
		obstacles.push_back(new Obstacle(LARGURA,random,300,25, true, speedObstacles));
		obstacles.push_back(new Obstacle(LARGURA,-random,300,25, true, speedObstacles));
	}
	
	if(frameCounter % tempoBloco == 0){
		float random = (float)( -100 + (rand() % 200));
		float prob = (float)(rand()%100);
		if(prob < chance){
			obstacles.push_back(new Obstacle(LARGURA,random,40,20, false, speedObstacles));
		}
		
	if(frameCounter == tempoPlat*tempoBloco){
		frameCounter = 0;
	}
		
	}
	}
	}
		glutPostRedisplay();
		glutTimerFunc(33,animation, 1);
}

void Timer(int value)
{
	
	
	if(!drawn)
	{
	switch(a){
		case 0:
			a++;
		break;
		case 1:
			a++;
		break;
		case 2:
			a++;
		break;
		case 3:
			a++;
		break;
		case 4:
			a++;
		break;
		case 5:
			a=0;
		break;
		default:
			a=0;
	}
	}
    glutPostRedisplay();
    glutTimerFunc(200, Timer, 1);
}

void mouseControll(int bt, int state, int x, int y){
	
	float x1 = (x*800/glutGet(GLUT_WINDOW_WIDTH)) - 400; //Cálculo Da Posição Do Mouse Nas Coordenadas da Ortho;
	float y1 = -1*((y*600/glutGet(GLUT_WINDOW_HEIGHT)) - 300);
	

		 if (bt == GLUT_LEFT_BUTTON)
	        if (state == GLUT_DOWN) {
	        		if(!flagMenu && !perdeu && !instr){
	         			if((x1<=240) && (x1>=20) && (y1<=80) && (y1>=0)) 
	         				flagMenu=true;
	         			else if((x1<=240) && (x1>=20) && (y1<=-30) && (y1>=-110)){ 
	         				instr = true;
						 }
	         		}
	         		else if(perdeu){
	         		
	         			if((x1<=-80) && (x1>=-300) && (y1<=-170) && (y1>=-250)){
							perdeu = false;
							flagMenu = true;
							resetGame();
						
						}else 
						if ((x1<=300) && (x1>=80) && (y1<=-170) && (y1>=-250)){
							exit(1);
						}
					 }else if(instr){
					 	if((x1<=380) && (x1>=200) && (y1<=-170) && (y1>=-250)) 
					 		instr = false;
					 }
			}

    glutPostRedisplay();	
}

int main(int argc, char* argv[])
{
	
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 

glutInitWindowPosition(0,0); 
glutInitWindowSize(800,600);
glutCreateWindow("Gravity Switch");
Setup();
LoadGLTextures(0);
glutDisplayFunc(Update);
glutKeyboardFunc(tasten);
glutReshapeFunc(AlteraTamanhoJanela);
glutSpecialFunc(TeclasEspeciais);
glutTimerFunc(150, animation, 1);
glutKeyboardFunc(tasten);
glutMouseFunc(mouseControll);
glutTimerFunc(200, Timer, 1);
glutMainLoop();
return 0;
}
