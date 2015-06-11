#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y){
    force = 1;
    resolution = 300;
    speed = 2;
    alive = true;
    
    screenW = ofGetScreenWidth();
    screenH = ofGetScreenHeight();
    
    mesh.setMode(OF_PRIMITIVE_POINTS);

    pitch = TWO_PI/resolution;                                                  // 'angle' between each point

    for (float i=0; i<TWO_PI; i+= pitch){
        if(rayIntersects(x, y, i)){                                             // only add particles that are aimed to the screen
            mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));   // add vertexes to mesh, and create new particles
            particles.push_back(Particle(x, y, i, 4));                          // FIXME: particles are a double of mesh verteces.
            int s = particles.size();
            if(s==100) particles[i].special = true;
        }
    }
}

// checks if a ray ( defined by an origin and an angle(/direction) ) crosses(intersects) the screen
bool Wave::rayIntersects(int x, int y, float angle){
    float a = tan(angle);
    float b = y-(a*x);
    int side = (cos(angle)>0)? 1 : -1;
    
    float px, py;
    
    // intersection with left side of screen
    px = 0; py = (a*px)+b;
    if( ( py < screenH ) && ( py > 0 ) && (x-px)*side<0) return true;

    // intersection with right side of screen
    px = screenW; py = (a*px)+b;
    if( ( py < screenH ) && ( py > 0 ) && (x-px)*side<0) return true;
    
    // intersection with bottom side of screen
    py = screenH; px = (py-b)/a;
    if( (px>0) && (px<screenW) && (y-py)*side*a<0) return true;

    // intersection with top side of screen
    py = 0; px = (py-b)/a;
    if( (px>0) && (px<screenW) && (y-py)*side*a<0) return true;

    return false;
};

void Wave::update(vector<PointElement *>& points, vector<LineElement *>& lines, float opacity){
    if(alive){
        int vc = mesh.getNumVertices();
        int pc = points.size();
        int lc = lines.size();
        
        for (int i=0; i<vc; i++) {
            // update particle position
            particles[i].update(speed);
            
            if(particles[i].blackHole==NULL){
                // is particle going away from the screen ?
                if((particles[i].speed.x>0 && particles[i].position.x > screenW)||
                   (particles[i].speed.y>0 && particles[i].position.y > screenH)||
                   (particles[i].speed.x<0 && particles[i].position.x < 0)||
                   (particles[i].speed.y<0 && particles[i].position.y < 0)){
                    particles[i].alive = false;
                    particles[(i+1)%vc].isEdge = true;          // next particle becomes an edge
                    particles[(i>0)?i-1:vc-1].isEdge = true;    // previous particle becomes an edge
                }
                else{
                    // check collisions
                    for (int j=0; j < pc; j++) {
                        // vc-1: do not check edge points to avoid 'wrap' bugs.
                        if(i<vc-1){
                    
                        // (bounding box) collision check
                            if(!particles[i].isEdge){
                                if(points[j]->collisionCheck( particles[i].position, particles[(i+1)].position, particles[(i+1)].pPosition, particles[i].pPosition )){
                                    points[j]->collided();
                                    
                                    // DESTROYER_ELEMENT -> destroy wave on collision
                                    if(points[j]->kind == DESTROYER_ELEMENT){
                                        // go trhough all particles, going forward from the collided point
                                        particles[i].alive = false;
                                        for (int k=(i+1)%vc; k!=i; k=(k+1)%vc) {
                                            if(!particles[k].isEdge) particles[k].blackHole = points[j];
                                            else break; // stop at first wave edge (do not affect parts of the wave that separated)
                                        }
                                        // go trhough all particles, going backwards from the collided point
                                        for (int k=(i-1)%vc; k!=i; k=(k>0)?k-1:vc-1) {
                                            if(!particles[k].isEdge) particles[k].blackHole = points[j];
                                            else break; // stop at first wave edge (do not affect parts of the wave that separated)
                                        }
                                    }
                                    else if(points[j]->kind == TARGET_ELEMENT && points[j]->buttonKind!=NOT_BUTTON){
                                        fadeout = true;
                                    }
                                }
                            }
                        }
                    }
                    // check line elements
                    for (int l=0; l < lc; l++) particles[i].lineBounce(lines[l]);
                    
                    // check if particle is the edge of the wave
                    if(
                       abs(particles[i].speed.angleRad( particles[(i+1)%vc].speed)) - pitch > 0.1 ||
                       abs(particles[i].speed.angleRad( particles[(i>0)?i-1:vc-1].speed)) - pitch > 0.1
                       ){
                        particles[i].isEdge = true;
                    } else particles[i].isEdge = false;
                }
            }

            // kill particle if needed (and update the vertices count (vc) to match)
            if (!particles[i].alive){ killParticle(i); vc--; i--;} // TODO: reverse main loop
            else{
                mesh.setVertex(i, particles[i].position);                                           // update 'mesh vertice' to particle position
                mesh.setColor(i, ofColor(255,opacity*force*255));                                   // set particle opacity (for fade out effects)
            }
        }
        
        if(vc==0) alive = false; // kill wave if there are no particles.
        if(fadeout){
            force -= force/10;
            speed -= speed/10;
        }
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
void Wave::kill(){
    alive = false;
    for (int i=particles.size()-1; i>=0; i--) {
        mesh.removeVertex(i);
        particles.erase(particles.begin()+i);
    }
}