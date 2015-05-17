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
    // update and check obstacles
    int s = mesh.getNumVertices();
    for (int i=0; i<s; i++) {
        if(blackHole != NULL){
            particles[i].position += (blackHole->pos - particles[i].position)/ofRandom(3,7);
//            particles[i].position.x += (blackHole->pos.x - particles[i].position.x)/ofRandom(3,7);
//            particles[i].position.y += (blackHole->pos.y - particles[i].position.y)/ofRandom(3,7);  //
            if(particles[i].position.distance(blackHole->pos) < 1)particles[i].alive = false;       // arrived at blackhole, delete this particle
        }
        else particles[i].update(speed);
        
        // 'collision detection'
        if(obst.collisionCheck(
            particles[i].position,
            particles[(i+1)%s].position,
            particles[(i+1)%s].pPosition,
            particles[i].pPosition
        )){
            if(obst.kind == DESTROYER_OBSTACLE) blackHole = &obst;
        }
        
        if (!particles[i].alive){
            killParticle(i); s--;
        }
        else{
            mesh.setVertex(i, particles[i].position);
            mesh.setColor(i, ofColor(255,speed*255));
        }
    }
    if(s==0)alive = false;
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