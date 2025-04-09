#include "particle.h"
#include <GLFW/glfw3.h>
#include <cmath>

void Particle::draw() const {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color

    const int numSegments = 100;   // More segments = smoother circle
    const float radius = 5.0f;

    glBegin(GL_TRIANGLE_FAN);      // For filled circle
    glVertex2f(x, y);              // Center of the circle
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * 3.1415926f * i / numSegments;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}
