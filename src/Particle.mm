#include "Particle.h"

Particle::Particle(float x, float y, float direction, float _speed){
    
    // set position (that one was hard to guess)
    position.set(x,y);
    
    // in 'particle', speed is a vector
    speed.set(cos(direction)*_speed,sin(direction)*_speed);
}

void Particle::update(){
    
    // openframework's instruction for adding vectors.
    position+=speed;

}

void Particle::draw(){
    
    // draw this s**t
    ofCircle(position.x,position.y,2);

}