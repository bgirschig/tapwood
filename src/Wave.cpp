#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y, float _force, int _resolution){

    force = _force;                     // not used
    resolution = _resolution;           // number of points per wave
    
    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    double pitch = TWO_PI/resolution;    // 'angle' between each point
    
    // add vertexes to mesh, and create new particles
    // FIXME: particles are a double of mesh verteces.
    for (int i=0; i<resolution; i++){
        mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));
        particles.push_back(Particle(this, i, x, y, pitch*i, 4));
    }
}

void Wave::hello()
{
    cout << "hello" << endl;
}

void Wave::update(){
//    force *= 0.99;

    int s = mesh.getNumVertices();
    for (int i=0; i<s; i++) {
        particles[i].update();
        mesh.setVertex(i, particles[i].position);
    }
}

void Wave::draw(){
//    ofSetLineWidth(force);
    mesh.draw();
//    mesh.drawVertices();
}