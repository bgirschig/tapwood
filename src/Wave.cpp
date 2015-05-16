#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y, float _force, int _resolution){
    force = _force;
    resolution = _resolution;           // number of points per wave
    speed = 1;
    alive = true;
    
    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    double pitch = TWO_PI/resolution;    // 'angle' between each point
    
    // add vertexes to mesh, and create new particles
    // FIXME: particles are a double of mesh verteces.
    for (int i=0; i<resolution; i++){
        mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));
        particles.push_back(Particle(i, x, y, pitch*i, 4));
    }
}

void Wave::update(){
    force -= 0.1;
    if(stopped) speed*=0.94;
    
    int s = mesh.getNumVertices();
    
    if(s>0){
        for (int i=0; i<s; i++) {
            particles[i].update(speed);
            
            if(particles[i].killWave){
                killParticle(i);
                s--;
                stopped = true;
                particles[i%s].killWave = true;
                if(i > 1)particles[i-1].killWave = true;
                else particles[s-1].killWave = true;
            }
            else if (!particles[i].alive) {
                killParticle(i);
                s--;
            }
            else{
                mesh.setVertex(i, particles[i].position);
                mesh.setColor(i, ofColor(255,int(force)));            
            }
        }
    }
    else{
        alive = false;
    }
}

void Wave::draw(){
//    ofSetLineWidth(force);
    glPointSize(3);
    mesh.draw();
    glPointSize(1);
    
//    mesh.drawVertices();
}

void Wave::killParticle(int index){
    mesh.removeVertex(index);
    particles.erase(particles.begin()+index);
}