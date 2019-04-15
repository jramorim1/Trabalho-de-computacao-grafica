#include "bg.h"
#include <GL/glut.h>

#define ALTURA 300
#define LARGURA 400


		BG::BG(int x){
		position = new Vetor(x, -ALTURA);
		speed = new Vetor(-2.5,0.0);
		}
		
		void BG::draw(){
			glPushMatrix();
			glTranslatef(this->position->x,0.0f, 0.0f);
			
			glBegin(GL_QUADS);
			glTexCoord2i(0,0); glVertex2d(-LARGURA,ALTURA);
			glTexCoord2i(1,0); glVertex2d(LARGURA + 5, ALTURA);
			glTexCoord2i(1,1); glVertex2d(LARGURA + 5,-ALTURA);
			glTexCoord2i(0,1); glVertex2d(-LARGURA,-ALTURA);
			
			glEnd();
			glPopMatrix();
		}
		void BG::update(){
			position->add(speed);
			if((this->position->x + LARGURA) <= -LARGURA){
				this->position->x = 2*LARGURA;
			}
		}
