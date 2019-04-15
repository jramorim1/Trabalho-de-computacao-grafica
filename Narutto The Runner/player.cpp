#include <iostream>
#include <GL/glut.h>
#include "player.h"
#include "vetor.h"
#include <math.h>
#define ALTURA 300
#define LARGURA 400


Player::Player(float x, float y, float w, float h){
	
	this->width = w;
	this->height = h;
	this->position = new Vetor(x,y);
	this->speed = new Vetor(0.0,0.0);
	this->aceleracao = new Vetor(0.0,0.0);
	this->gravidade = new Vetor(0.0,-0.5);
	this->angle = 0.0;
	this->isAlive = true;
	this->grounded = false;
}

void Player::draw(){
	glPushMatrix();
	glTranslatef(this->position->x, this->position->y, 0.0f);
	glRotatef(angle,0.0,0.0,1.0);
	gravChange();
	glBegin(GL_QUADS);
	
	glTexCoord2i(1,1); glVertex2d(0.0,0.0);
	glTexCoord2i(1,0); glVertex2d(0.0,this->height);
	glTexCoord2i(0,0); glVertex2d(this->width,this->height);
	glTexCoord2i(0,1); glVertex2d(this->width,0.0);
	
	glEnd();
	glPopMatrix();
}

void Player::applyForce(Vetor *force){
	this->aceleracao->add(force);
}

void Player::update(){
	this->applyForce(this->gravidade);
	this->speed->add(this->aceleracao);
	this->position->add(this->speed);
	this->aceleracao = new Vetor(0,0);
}

void Player::switchGravity(){
	this->speed->y = 0.0;
	this->gravidade->y *= -1;
}

void Player::setY(float y){
	this->position->y = y;
}

void Player::rotate(){
	if(this->gravidade->y < 0 && this->angle != 0){
			this->angle+=60;
			if(this->angle >= 360)
				this->angle = 0;
		}else if(this->gravidade->y > 0 && this->angle != 180){
			this->angle-=60;
			if(this->angle <= -360)
				this->angle = 180;
		}
}

void Player::hit(Obstacle *o){
		if ((this->position->y >= o->position->y) && (this->position->y <= (o->position->y + o->height))) {
			if (((this->position->x + this->width) >= o->position->x) && (this->position->x <= (o->position->x + o->width))){
			
			if(this->position->x + this->width >= o->position->x && (this->position->x + this->width) <= (o->position->x + this->width) && !grounded){
				this->position->add(o->speed);
			}
			
			if(this->gravidade->y < 0){
				this->grounded=true;
				this->speed->y = 0.0;
				this->position->y = o->position->y + o->height;
			}
			else {
				this->grounded=true;
				this->speed->y = 0.0;
				this->position->y = o->position->y;
			}
		}
	}
}

void Player::spawnPoint(float x, float y){
	this->position->x = x;
	this->position->y = y;
}

bool Player::testCollision(){
	if((this->position->x + this->width) <= -LARGURA || (this->position->y) > ALTURA || (this->position->y) < -ALTURA){
		return 1;
	}
		return 0;
}//

void Player::gravChange(){
	if(this->gravidade->y < 0)
	glRotatef(180,0,1,0); 
}
	
	



