#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "vetor.h"
#include <iostream>

class Obstacle{
	public:
		float width;
		float height;
		Vetor *position;
		Vetor *speed;
		bool ground;
		
		Obstacle(float,float,float,float, bool, float);
		Obstacle();
		~Obstacle();
		void draw();
		void update();
		void spawnPoint(float , float);
		bool isOut();
		void changeSpeed(float);
};


#endif
