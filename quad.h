#ifndef QUAD_H
#define QUAD_H
#include "particle.h"
#include <vector>

class Quadtree{
	public:
	int x, y, width, height;
	static unsigned long capacity;
	std::vector<Particle*> particles;

	Quadtree(int x, int y, int width, int height);

	//Methods
	void subdivide(void);
	void addParticle(Particle* particle);
	void passParticle(Particle* particle);
	void checkCapacity(void);
	void drawBoundry(void);

	Quadtree* ne;
	Quadtree* nw;
	Quadtree* sw;
	Quadtree* se;

	~Quadtree();

	private:
	bool divided;

};

#endif
