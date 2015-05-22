#include "Obstacle.h"



Obstacle::Obstacle(){}
Obstacle::Obstacle(ofVec2f position, ElementKind type){
    pos = position;
    kind = type;
    animation = -1;
    scale = 10;
}

bool Obstacle::collisionCheck(ofVec2f pt1, ofVec2f pt2, ofVec2f pt3, ofVec2f pt4){
    // bounding box collision check
    if((pos.x<pt1.x && pos.x<pt2.x && pos.x<pt3.x && pos.x<pt4.x) ||
       (pos.x>pt1.x && pos.x>pt2.x && pos.x>pt3.x && pos.x>pt4.x) ||
       (pos.y<pt1.y && pos.y<pt2.y && pos.y<pt3.y && pos.y<pt4.y) ||
       (pos.y>pt1.y && pos.y>pt2.y && pos.y>pt3.y && pos.y>pt4.y)
       ){
        return false;
    }
    return true;
}

void Obstacle::draw(){
    ofNoFill(); ofSetLineWidth(2);
    
    if(kind==DESTROYER_OBSTACLE){
        if(animation>=0){
            if(animation < 30){                                 // expand and disapear
                scale = 10+(animation*2);                       // - scale up
                ofSetColor(255, 255-(animation*8));             // - blend out
            }
            else if(animation < 50) scale = (animation-30)/2;   // loop back to original size
            
            if(animation > 50) animation = -1;                  // animation end
            else animation++;                                   // advance anim
            
            ofSetColor(255);    // reset color (/opacity)
            scale = 10;         // reset scale
        }
        ofCircle(pos.x, pos.y, scale);
    }
    else if(kind==TARGET_OBSTACLE) ofCircle(pos.x, pos.y, 10);
    glLineWidth(0);
}
void Obstacle::collided(){
    if(kind==DESTROYER_OBSTACLE) animation = 0; // start animation
    else if(kind==TARGET_OBSTACLE) animation = 0;
}
