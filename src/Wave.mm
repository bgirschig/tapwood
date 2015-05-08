#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y, float _force, int _resolution){

    force = _force;                     // not used
    resolution = _resolution;           // number of points per wave
    
    float pitch = TWO_PI/resolution;    // 'angle' between each point
    
    // create all particles
    for (int i=0; i<resolution; i++) particles.push_back(Particle(x, y, pitch*i, 3));
}

// update each particle of this wave
void Wave::update(){ for(Particle &p : particles) p.update(); }

// draw each particle of this wave
void Wave::draw(){ for(Particle &p : particles) p.draw(); }