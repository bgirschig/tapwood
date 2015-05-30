#include "Wave.h"
#define WINDOW_W 1500
#define WINDOW_H 1000

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

    for (float i=0; i<TWO_PI; i+=pitch){
        if(rayIntersects(x, y, i)){                                             // only add particles that are aimed to the screen
            mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));   // add vertexes to mesh, and create new particles
            particles.push_back(Particle(x, y, i, 4));                          // FIXME: particles are a double of mesh verteces.
        }
    }
    particles[0].isEdge = true;
    particles[particles.size()-1].isEdge = true;
}

// checks if a ray ( defined by an origin and an angle(/direction) ) crosses(intersects) the screen
bool Wave::rayIntersects(int x, int y, float angle){
    float a = tan(angle);
    float b = y-(a*x);
    int side = (cos(angle)>0)? 1 : -1;
    
    float px, py;
    
    // intersection with left side of rect
    px = 0; py = (a*px)+b;
    if( ( py < WINDOW_H ) && ( py > 0 ) && (x-px)*side<0) return true;

    // intersection with right side of rect
    px = WINDOW_W; py = (a*px)+b;
    if( ( py < WINDOW_H ) && ( py > 0 ) && (x-px)*side<0) return true;
    
    // intersection with bottom side of rect
    py = WINDOW_H; px = (py-b)/a;
    if( (px>0) && (px<WINDOW_W) && (y-py)*side*a<0) return true;

    // intersection with top side of rect
    py = 0; px = (py-b)/a;
    if( (px>0) && (px<WINDOW_W) && (y-py)*side*a<0) return true;
//
    return false;
};

void Wave::update(vector<PointElement *>& elements, float opacity){
    
    int s = mesh.getNumVertices();
    int os = elements.size();
    for (int i=0; i<s; i++) {

        // black hole slurp
        if(blackHole != NULL){
            particles[i].position += (blackHole->pos - particles[i].position)/ofRandom(2,20);        // ease to black hole, with some random.
            if(particles[i].position.distance(blackHole->pos) < 1) particles[i].alive = false;       // arrived at blackhole, delete this particle
        }
        else{
            particles[i].update(speed);                                                // update particle position
            if(i<s-1){                                                                 // do not check edge points to avoid 'wrap' bugs.
                for (int j=0; j < os; j++) {
                    if(elements[j]->collisionCheck(                                    // (bounding box) collision check
                       particles[i].position,
                       particles[(i+1)].position,
                       particles[(i+1)].pPosition,
                       particles[i].pPosition
                       )){
                        elements[j]->collided();
                        if(elements[j]->kind == DESTROYER_ELEMENT) blackHole = elements[j];  // DESTROYER_ELEMENT -> destroy wave on collision
                    }
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
    ofSetColor(255);
    ofRect(0, 0, WINDOW_W, WINDOW_H);
    glPointSize(3);
    mesh.draw();
    glPointSize(1);
}

void Wave::killParticle(int index){
    mesh.removeVertex(index);
    particles.erase(particles.begin()+index);
}