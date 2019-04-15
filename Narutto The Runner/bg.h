#ifndef BG_H
#define BG_H

#include "vetor.h"
#include <iostream>

class BG{
	public:
		Vetor *position;
		Vetor *speed;
		
		BG(int x);
		BG();
		~BG();
		void draw();
		void update();
};


#endif
