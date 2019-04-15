#ifndef PLAYER_H
#define PLAYER_H
#include "vetor.h"
#include "obstacle.h"
#include <vector>


using namespace std;

class Player{
	public:
		float width;
		float height;
		Vetor *position;
		Vetor *speed;
		Vetor *aceleracao;
		Vetor *gravidade;
		float angle;
		bool isAlive;
		bool grounded;
		
		Player(float,float,float, float);
		void draw();
		void hit(Obstacle*);
		void update();
		bool testCollision();
		void spawnPoint(float , float);
		void applyForce(Vetor*);
		void switchGravity();
		void rotate();
		void setY(float);
		void gravChange();
	
		
};

#endif
