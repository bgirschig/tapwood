#include "Wave.h"

//default constructor
Wave::Wave(){ }

Wave::Wave(float x, float y){
    force = 1;
    resolution = 600;
    speed = 1;
    alive = true;
    blackHole = NULL;
    screenW = ofGetScreenWidth();
    screenH = ofGetScreenHeight();
    
//    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.setMode(OF_PRIMITIVE_POINTS);

    pitch = TWO_PI/resolution;                                                  // 'angle' between each point

    for (float i=0; i<TWO_PI; i+= pitch){
        if(rayIntersects(x, y, i)){                                             // only add particles that are aimed to the screen
            mesh.addVertex(ofPoint(x,y)); mesh.addColor(ofFloatColor(1,1,1));   // add vertexes to mesh, and create new particles
            particles.push_back(Particle(x, y, i, 4));                          // FIXME: particles are a double of mesh verteces.
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
    
    int vc = mesh.getNumVertices();
    int pc = points.size();
    int lc = lines.size();
    
    for (int i=0; i<vc; i++) {

        // black hole slurp
        if(blackHole != NULL){
            particles[i].position += (blackHole->pos - particles[i].position)/ofRandom(2,20);        // ease to black hole, with some random.
            if(particles[i].position.distance(blackHole->pos) < 1) particles[i].alive = false;       // arrived at blackhole, delete this particle
        }
        else{
            // update particle position
            particles[i].update(speed);
            
            // is particle going away from the screen ?
            // FIXME: the '+20' / '-20' thing is a quick fix for a bug (animation problem on edge). Fix the bug instead.
            if((particles[i].speed.x>0 && particles[i].position.x > screenW+20)||
               (particles[i].speed.y>0 && particles[i].position.y > screenH+20)||
               (particles[i].speed.x<0 && particles[i].position.x < -20)||
               (particles[i].speed.y<0 && particles[i].position.y < -20)){
                    particles[i].alive = false;
                }

            // alive and well particles...
            else{
                // check collisions with point elements
                for (int j=0; j < pc; j++) {
                    // vc-1: do not check edge points to avoid 'wrap' bugs.
                    if(i<vc-1){
                        
                        // (bounding box) collision check
                        if(points[j]->collisionCheck( particles[i].position, particles[(i+1)].position, particles[(i+1)].pPosition, particles[i].pPosition )){
                            points[j]->collided();
                            
                            // DESTROYER_ELEMENT -> destroy wave on collision
                            if(points[j]->kind == DESTROYER_ELEMENT){
                                blackHole = points[j];
                            }
                        }
                    }
                }
                // check line elements
                for (int l=0; l < lc; l++) particles[i].lineBounce(lines[l]);
                
                if(abs(particles[i].speed.angle( particles[(i+1)%vc].speed) - pitch)>1 ||
                   abs(particles[i].speed.angle( particles[(i>0)?i-1:vc].speed) - pitch)>1){
                    particles[i].isEdge = true;
                }
                else{
                    particles[i].isEdge = false;
                    particles[(i+1)%vc].isEdge = false;
                }
            }
        }
        if (!particles[i].alive){ killParticle(i); vc--; }           // kill particle if needed (and update the loop limit to match)
        else{
            mesh.setVertex(i, particles[i].position);               // update 'mesh vertice' to particle position
            if(particles[i].isEdge) mesh.setColor(i, ofColor(255,0,0,opacity*force*255));
            else mesh.setColor(i, ofColor(255,opacity*force*255));       // set particle opacity (for fade out effects)
        }
    }
    
    if(vc==0) alive = false; // kill wave if there are no particles.
    if(fadeout){
        force -= force/10;
        speed -= speed/10;
    }
}

void Wave::draw(){
    ofSetColor(255);
    ofRect(0, 0, screenW, screenH);
    glPointSize(3);
    mesh.draw();
    glPointSize(1);
}

void Wave::killParticle(int index){
    mesh.removeVertex(index);
    particles.erase(particles.begin()+index);
}