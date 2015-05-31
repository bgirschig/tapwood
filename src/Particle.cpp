#include "Particle.h"

#include "Wave.h"

Particle::Particle(float _x, float _y, double direction, float _speed)
{
    position.set(_x, _y);
    pPosition.set(_x,_y);
    speed.set(cos(direction)*_speed, sin(direction)*_speed);
    
    alive = true;
    killWave = false;
    isNextKilled = false;
    isEdge = false;
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

void Particle::lineBounce(LineElement *l){
    float a = speed.y/speed.x;
    float b = position.y-(a*position.x);
    float intersectX = (l->b - b) / (a - l->a);
    float intersectY = (l->a * intersectX)+l->b;
    if(
       l->local.x/(intersectX-l->pt1.x) > 1
       && l->local.y/(intersectY-l->pt1.y) > 1
       && abs(speed.x) > abs(intersectX-position.x)
       && abs(speed.y) > abs(intersectY-position.y)
       ){
        float dot = (speed.x*l->normal.x)+(speed.y*l->normal.y);
        speed.set((speed.x-(2*dot*l->normal.x))*l->dampening, (speed.y-(2*dot*l->normal.y))*l->dampening);
    }
}