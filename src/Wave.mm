//
//  Wave.cpp
//  tapwood
//
//  Created by bastien girschig on 07/05/2015.
//
//

#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(ofVec2f _position, float _force, int _resolution){
    force = _force;
    resolution = _resolution;
    
    float pitch = TWO_PI/resolution;
    for (int i=0; i<resolution; i++) {
        particles.push_back(Particle(_position.x, _position.y, pitch*i, 3));
    }
}
void Wave::update(){
    for (int i=0; i<resolution; i++) particles[i].update();
}
void Wave::draw(){
    for (int i=0; i<resolution; i++) particles[i].draw();
}