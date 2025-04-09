#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "particle.h"
#include "quad.h"

std::vector<Particle*>particles;
void randomPopulate(void){
		for (int i = 0; i < 100; ++i) {
			particles.push_back(new Particle(rand() % 801, rand() % 601));
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
	glOrtho(0, 800, 600, 0, -1, 1);  // Set orthogonal projection, for 2D rendering
	
	Quadtree quadtree(0, 0, 800, 600);
	Particle particle(100,200);
		quadtree.addParticle(&particle);

	randomPopulate();
	for(const auto& particle : particles){
		quadtree.addParticle(particle);
	}

	while (!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			// Render the quadtree boundary
		quadtree.drawBoundry();
		particle.draw();

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
