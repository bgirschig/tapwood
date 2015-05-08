#include "Particle.h"

Particle::Particle(float _x, float _y, float direction, float _speed){
    x = _x;
    y = _y;
    
    speed.set(cos(direction)*_speed,sin(direction)*_speed);
}

void Particle::update(){
    x+=speed.x;
    y+=speed.y;
}

void Particle::draw(){
    ofRect(x, y, 5, 5);

}