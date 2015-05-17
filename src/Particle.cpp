#include "Particle.h"

#include "Wave.h"

Particle::Particle(int & _index, float _x, float _y, double direction, float _speed)
{
    position.set(_x, _y);
    pPosition.set(_x,_y);
    speed.set(cos(direction)*_speed,sin(direction)*_speed);
    
    alive = true;
    killWave = false;
    isNextKilled = false;
}

void Particle::update(float _speed){
    pPosition = position;
    position+=speed*_speed;
    
    // bounce
    // ?

    // kill
//    if(position.x<0 || position.x>ofGetWidth() || position.y<0 || position.y>ofGetHeight()) alive = false;
    
    // killWave
    // if(position.x>ofGetWidth()/2) killWave=true;
}
void Particle::debugDraw(){
    if(killWave) ofSetColor(255,0,0);
    else ofSetColor(255);
    ofCircle(position.x, position.y+5, 2);
    ofSetColor(255);
}