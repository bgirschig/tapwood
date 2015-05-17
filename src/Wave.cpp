#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y, float _force, int _resolution){
    force = _force;
    resolution = _resolution;           // number of points per wave
    speed = 1;
    alive = true;
    
//    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    double pitch = TWO_PI/resolution;    // 'angle' between each point
    
    // add vertexes to mesh, and create new particles
    // FIXME: particles are a double of mesh verteces.
    for (int i=0; i<resolution; i++){
        mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));
        particles.push_back(Particle(i, x, y, pitch*i, 4));
    }
}

void Wave::update(Obstacle & obst){
    force -= 0.1;
    if(slow){
        speed*=0.94;
        if(speed<0.1) alive = false;
    }
    
    int s = mesh.getNumVertices();
    
    // update and check obstacles
    for (int i=0; i<s; i++) {
        particles[i].update(speed);
        
        if(!slow && obst.collisionCheck(
            particles[i].position,
            particles[(i+1)%s].position,
            particles[(i+1)%s].pPosition,
            particles[i].pPosition
        )){
            if(obst.kind == DESTROYER_OBSTACLE){
                for (int j=0; j<s; j++) particles[j].speed*=ofRandom(-1.1, 1.1);
                slow = true;
            }
        }
        
        if (!particles[i].alive){
            killParticle(i); s--;
        }
        else{
            mesh.setVertex(i, particles[i].position);
            mesh.setColor(i, ofColor(255,speed*255));
        }
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