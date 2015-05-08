#include "Particle.h"

Particle::Particle(float _x, float _y, float direction, float _speed){
    x = _x;
    y = _y;
    
    speed.set(cos(direction)*_speed,sin(direction)*_speed);
}

void Particle::update(){
    x+=speed.x;
    y+=speed.y;
    if((x<0 && speed.x<0)||(x>ofGetWidth() && speed.x>0) )speed.x = -speed.x;
    if((y<0 && speed.y<0)||(y>ofGetHeight() && speed.y>0) )speed.y = -speed.y;
}

void Particle::draw(){
    ofRect(x, y, 5, 5);

}