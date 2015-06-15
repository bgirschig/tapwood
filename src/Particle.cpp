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

    blackHole = NULL;
}

void Particle::update(float _speed){
    if(blackHole != NULL){
        position += (blackHole->pos - position)/ofRandom(2,15);        // ease to black hole, with some random.
        if(position.distance(blackHole->pos) < 20) alive = false;       // arrived at blackhole, delete this particle
    }
    else{
        pPosition = position;
        position+=speed*_speed;
    }
}

bool Particle::lineBounce(LineElement *l){
    slope = speed.y/speed.x;
    offset = position.y-(slope*position.x);
    
    float intersectX = (l->b - offset) / (slope - l->a);
    float intersectY = (l->a * intersectX)+l->b;
    if(
       l->local.x/(intersectX-l->pt1.x) > 1
       && l->local.y/(intersectY-l->pt1.y) > 1
       && abs(speed.x) > abs(intersectX-position.x)
       && abs(speed.y) > abs(intersectY-position.y)
       ){
        float dot = (speed.x*l->normal.x)+(speed.y*l->normal.y);
        speed.set((speed.x-(2*dot*l->normal.x))*l->dampening, (speed.y-(2*dot*l->normal.y))*l->dampening);
        return true;
    }
    return false;
}