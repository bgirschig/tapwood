#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y, float _force, int _resolution){
    force = _force;
    resolution = _resolution;
    speed = 1;
    alive = true;
    
//    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    double pitch = TWO_PI/resolution;                                       // 'angle' between each point
    
    
    
    for (int i=0; i<resolution; i++){
        mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));   // add vertexes to mesh, and create new particles
        particles.push_back(Particle(i, x, y, pitch*i, 4));                 // FIXME: particles are a double of mesh verteces.
    }
}

void Wave::update(vector<Obstacle *> obstacles){
    
    int s = mesh.getNumVertices();
    int os = obstacles.size();
    for (int i=0; i<s; i++) {

        // black hole deletion
        if(blackHole != NULL){
            particles[i].position += (blackHole->pos - particles[i].position)/ofRandom(2,20);        // ease to black hole, with some random.
            if(particles[i].position.distance(blackHole->pos) < 1) particles[i].alive = false;       // arrived at blackhole, delete this particle
        }
        else{
            particles[i].update(speed);                                              // update particle position
            for (int j=0; j < os; j++) {
                if(obstacles[j]->collisionCheck(                                     // (bounding box) collision check
                   particles[i].position,
                   particles[(i+1)%s].position,
                   particles[(i+1)%s].pPosition,
                   particles[i].pPosition
                   )){
                    if(obstacles[j]->kind == DESTROYER_OBSTACLE) blackHole = obstacles[j];  // DESTROYER_OBSTACLE -> destroy wave on collision
                    cout << obstacles[j]->kind << endl;
                }
            }
        }
        if (!particles[i].alive){ killParticle(i); s--; }           // kill particle if needed (and update the loop limit consequently)
        
        else{
            mesh.setVertex(i, particles[i].position);               // update 'mesh vertice' to particle position
            // mesh.setColor(i, ofColor(255,speed*255));            // set particle opacity (for fade out effects)
        }

       
    }
    if(s==0) alive = false; // kill wave if there are no particles.
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