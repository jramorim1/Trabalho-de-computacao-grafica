#ifndef VETOR_H
#define VETOR_H

class Vetor{
	
	public:
	float x;
	float y;
	float mod;
	
	public:
	Vetor(float, float);
	Vetor();
	~Vetor();
	void modulo();
	void norma();	
	void add(Vetor*);
	void sub(Vetor*);
	void m();
	
};

#endif
