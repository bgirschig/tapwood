#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y, float _force, int _resolution){

    force = _force;                     // not used
    resolution = _resolution;           // number of points per wave
    
    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    float pitch = TWO_PI/resolution;    // 'angle' between each point
    
    // add vertexes to mesh, and create new particles
    // FIXME: particles are a double of mesh verteces.
    for (int i=0; i<resolution; i++){
        mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));
        particles.push_back( Particle(x, y, pitch*i, 3) );
    }
}

void Wave::update(){
    int s = mesh.getNumVertices();
    
    for (int i=0; i<s; i++) {
        particles[i].update();
        ofVec3f v = mesh.getVertex(i);
        v.set(particles[i].x, particles[i].y);
        mesh.setVertex(i, v);
    }
}

void Wave::draw(){
//    for(Particle &p : particles) p.draw();
    mesh.draw();
}