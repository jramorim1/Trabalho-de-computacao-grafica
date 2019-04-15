#include "vetor.h"
#include <math.h>
#include<iostream>
using namespace std;

Vetor::Vetor(float k, float z){
	this->x=k;
	this->y=z;
}

void Vetor::modulo(){
	mod = sqrt(x*x + y*y);
}

void Vetor::norma(){
	this->modulo();
	this->x=this->x/mod;
	this->y=this->y/mod;
}

void Vetor::add(Vetor *v1){
	this->x = this->x + v1->x;
	this->y = this->y + v1->y;
}

void Vetor::sub(Vetor *v1){
	this->x = this->x - v1->x;
	this->y = this->y - v1->y;
}

void Vetor::m(){
	cout << "X: = "<<this->x<<endl;
	cout << "Y: = "<<this->y<<endl;
	cout << "MOD: = "<<this->mod<<endl;
}



