#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
    int x, y;

    // Constructor
    Particle(int x, int y) : x(x), y(y) {}

    // Method to draw the particle as a blue circle
    void draw() const;
};

#endif

