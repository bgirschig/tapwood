#include "Particle.h"

#include "Wave.h"

Particle::Particle(Wave * _w, int index, float _x, float _y, double direction, float _speed)
{
    position.x = _x;
    position.y = _y;
    
    speed.set(cos(direction)*_speed,sin(direction)*_speed);
    
    wave = _w;
    
    wave->hello();
}

void Particle::update(){
    position+=speed;
    
    // bounce
    if((position.x<0 && speed.x<0)||(position.x>ofGetWidth() && speed.x>0) ){
        speed.x = -speed.x*0.8;
        speed.y = speed.y*0.8;
    }
    if((position.y<0 && speed.y<0)||(position.y>ofGetHeight() && speed.y>0) ){
        speed.y = -speed.y*0.8;
        speed.x = speed.x*0.8;
    }

    // kill
    if(position.x<0 || position.x>ofGetWidth() || position.y<0 || position.y>ofGetHeight()){
        
    }
}