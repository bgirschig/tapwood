//
//  Particle.cpp
//  tapwood
//
//  Created by bastien girschig on 07/05/2015.
//
//

#include "Particle.h"

Particle::Particle(float x, float y, float direction, float _speed){
    position.set(x,y);
    speed.set(cos(direction)*_speed,sin(direction)*_speed);
}

void Particle::update(){
    position+=speed;
}
void Particle::draw(){
    ofCircle(position.x,position.y,2);
}