#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "particle.h"
#include "quad.h"
#include <random>

std::vector<Particle*>particles;

// Generate a random integer in the range [min, max]
int randomi(int min, int max) {
    static std::mt19937 mt(std::random_device{}()); // Seeded once
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
void randomPopulate(void){
		for (int i = 0; i < 100; ++i) {
			particles.push_back(new Particle(randomi(0, 800), randomi(0, 600)));
	}
}
int main(void){
	// Example of OpenGL initialization in your main loop
	if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW!" << std::endl;
			return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Quadtree Visualization", nullptr, nullptr);
	if (!window) {
			glfwTerminate();
			std::cerr << "Failed to create GLFW window!" << std::endl;
			return -1;
	}

	glfwMakeContextCurrent(window);

	// Set OpenGL settings
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Clear to black
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -1, 1);  // (0,0) = bottom-left
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Quadtree quadtree(0, 0, 800, 600);
	Particle particle(100,250);
	Particle particle1(100,500);
	Particle particle2(100,190);
	Particle particle3(70,189);
	Particle particle4(120,200);
	Particle particle5(110,200);
	Particle particle6(0,0);
		quadtree.addParticle(&particle);
		quadtree.addParticle(&particle1);
		quadtree.addParticle(&particle2);
		quadtree.addParticle(&particle3);
		quadtree.addParticle(&particle4);
		quadtree.addParticle(&particle5);
		quadtree.addParticle(&particle6);

	randomPopulate();
	for(const auto& p : particles){
		quadtree.addParticle(p);
	}

	while (!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			// Render the quadtree boundary
		quadtree.drawBoundry();
		particle.draw();
		particle1.draw();
		particle2.draw();
		particle3.draw();
		particle4.draw();
		particle5.draw();
		particle6.draw();

		for(const auto& particle : particles){
			particle->draw();
		}

			glfwSwapBuffers(window);
			glfwPollEvents();
	}

	glfwTerminate();
	return 0;

	return 0;
}
