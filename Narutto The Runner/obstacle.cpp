#include "obstacle.h"
#include <GL/glut.h>

#define ALTURA 300
#define LARGURA 400


Obstacle::Obstacle(float x, float y, float w, float h, bool g, float s){
	this->width = w;
	this->height = h;
	this->position = new Vetor(x,y);
	this->speed = new Vetor(s,0.0);
	this->ground = g;
}

void Obstacle::draw(){
	glPushMatrix();
	glTranslatef(this->position->x, this->position->y, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2i(0 , 0); glVertex2d(0.0,0.0);
	glTexCoord2f(0 , 1); glVertex2d(0.0,height);
	glTexCoord2f(1 , 1); glVertex2d(width,height);
	glTexCoord2f(1, 0); glVertex2d(width,0.0);
	glEnd();
	glPopMatrix();
}

void Obstacle::changeSpeed(float s){
	this->speed->x = s;
}

void Obstacle::update(){
	this->position->add(this->speed);
	if(isOut())
		Obstacle::spawnPoint(LARGURA, this->position->y);
}
void Obstacle::spawnPoint(float x, float y){
	this->position->x = x;
	this->position->y = y;
}

bool Obstacle::isOut(){
	if((this->position->x + this->width) <= -LARGURA || (this->position->y + this->height) > ALTURA || (this->position->y + this->height) < -ALTURA)
		return true;
	return false;
}

