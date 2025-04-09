#include "quad.h"
#include "particle.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

Quadtree::Quadtree(int x, int y, int width, int height):x(x), y(y), width(width), height(height){
	this->divided = false;
}

unsigned long Quadtree::capacity = 4;

void Quadtree::subdivide(void){
	ne = new Quadtree(x+width/2,y+height/2, width/2, height/2);
	nw = new Quadtree(x,y+height/2, width/2, height/2);
	se = new Quadtree(x+width/2, y, width/2, height/2);
	sw = new Quadtree(x, y, width/2, height/2);
	this->divided = true;
}

void Quadtree::addParticle(Particle* particle){
	if(!divided){
		if(particles.size()<=Quadtree::capacity){
			particles.push_back(particle);
		}else{
			subdivide();
			for(Particle* particle: particles){
				passParticle(particle);
			}
			//Commented because in checkCapacity from parent might collapse this class
			//as the value is now small
			/*particles.clear();*/
		}
	}else{
		passParticle(particle);
	}
}
void Quadtree::passParticle(Particle* particle){
		if(particle->x>=width/2 && particle->y>=height/2){
			ne->addParticle(particle);
		}else if(particle->x<width/2 && particle->y>=height/2){
			nw->addParticle(particle);
		}else if(particle->x>=width/2 && particle->y<height/2){
			se->addParticle(particle);
		}else if(particle->x<width/2 && particle->y<height/2){
			sw->addParticle(particle);
		}
}

void Quadtree::checkCapacity(void){
	if(!divided) return;
	unsigned long currCapacity = ne->particles.size() + nw->particles.size() + se->particles.size() + sw->particles.size();

	if(currCapacity <= Quadtree::capacity){
		particles.clear();
		particles.reserve(particles.size() + ne->particles.size() + nw->particles.size() + se->particles.size() + sw->particles.size());
		particles.insert(particles.end(), ne->particles.begin(), ne->particles.end());
		particles.insert(particles.end(), nw->particles.begin(), nw->particles.end());
		particles.insert(particles.end(), se->particles.begin(), se->particles.end());
		particles.insert(particles.end(), sw->particles.begin(), sw->particles.end());
		ne = nw = se = sw = nullptr;
		this->divided = false;
	}
}

void Quadtree::drawBoundry(void){
		glColor3b(127, 0, 0);
		// Draw the boundary of this quadtree node (current rectangle)
		glBegin(GL_LINE_LOOP); // Draw a loop of lines (a rectangle)
		glVertex2f(x, y); // Bottom-left corner
		glVertex2f(x + width, y); // Bottom-right corner
		glVertex2f(x + width, y + height); // Top-right corner
		glVertex2f(x, y + height); // Top-left corner
		glEnd();
	if(divided){
		ne->drawBoundry();
		nw->drawBoundry();
		se->drawBoundry();
		sw->drawBoundry();
	}
}

Quadtree::~Quadtree(void){
	if(divided){
		delete ne;
		delete nw;
		delete se;
		delete sw;
	}
}
