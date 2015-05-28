#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y){
    force = 1;
    resolution = 200;
    speed = 1;
    alive = true;
    blackHole = NULL;
    
//    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    double pitch = TWO_PI/resolution;                                       // 'angle' between each point
    
    
    
    for (int i=0; i<resolution; i++){
        mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));   // add vertexes to mesh, and create new particles
        particles.push_back(Particle(i, x, y, pitch*i, 4));                 // FIXME: particles are a double of mesh verteces.
    }
}

void Wave::update(vector<PointElement *>& elements, float opacity){
    
    int s = mesh.getNumVertices();
    int os = elements.size();
    for (int i=0; i<s; i++) {

        // black hole deletion
        if(blackHole != NULL){
            particles[i].position += (blackHole->pos - particles[i].position)/ofRandom(2,20);        // ease to black hole, with some random.
            if(particles[i].position.distance(blackHole->pos) < 1) particles[i].alive = false;       // arrived at blackhole, delete this particle
        }
        else{
            particles[i].update(speed);                                              // update particle position
            for (int j=0; j < os; j++) {
                if(elements[j]->collisionCheck(                                     // (bounding box) collision check
                   particles[i].position,
                   particles[(i+1)%s].position,
                   particles[(i+1)%s].pPosition,
                   particles[i].pPosition
                   )){
                    elements[j]->collided();
                    if(elements[j]->kind == DESTROYER_ELEMENT) blackHole = elements[j];  // DESTROYER_ELEMENT -> destroy wave on collision
                }
            }
        }
        if (!particles[i].alive){ killParticle(i); s--; }           // kill particle if needed (and update the loop limit consequently)
        
        else{
            mesh.setVertex(i, particles[i].position);               // update 'mesh vertice' to particle position
             mesh.setColor(i, ofColor(255,opacity*force*255));              // set particle opacity (for fade out effects)
        }

       
    }
    if(s==0) alive = false; // kill wave if there are no particles.
    if(fadeout){
        force -= force/10;
        speed -= speed/10;
    }
}

void Wave::draw(){
    glPointSize(3);
    mesh.draw();
    glPointSize(1);
}

void Wave::killParticle(int index){
    mesh.removeVertex(index);
    particles.erase(particles.begin()+index);
}