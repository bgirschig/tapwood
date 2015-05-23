#include "Obstacle.h"



Obstacle::Obstacle(){}
Obstacle::Obstacle(ofVec2f position, ElementKind type){
    pos = position;
    kind = type;
    animation = -1;
    secondaryAnim = -1;
    scale = 10;
    hasCollided = false;
    valid = false;
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
    ofNoFill(); ofSetLineWidth(3);
    
    if(kind==DESTROYER_OBSTACLE){
        animation = (animation+1) % 60;
        
        ofSetColor(255, 4*animation-1);
        ofCircle(pos.x, pos.y, 30-(animation*0.5));
        
        ofSetColor(255, 4*((animation<30)? (animation+30): (animation-30))-1);
        ofCircle(pos.x, pos.y, (animation<30)?15-(animation*0.5):45-(animation*0.5));
    }
    else if(kind==TARGET_OBSTACLE){
        if(animation<120){
            if(secondaryAnim < 17){
                animation ++;
                if(animation>=120) animation = 0;
            }
            
            ofSetColor(255);
            ofCircle(pos.x, pos.y, 15+sin((animation*TWO_PI)/120)*3);
            
            if(hasCollided){
                if(secondaryAnim <= 17) secondaryAnim += (18-secondaryAnim)/(secondaryAnim+4);
                else valid = true;
                
                ofFill();
                ofCircle(pos.x, pos.y, secondaryAnim);
            }
        }
        
    }
    glLineWidth(0);
}
void Obstacle::collided(){
    hasCollided = true;
//    if(kind==DESTROYER_OBSTACLE) cout<<"obst";
    if(kind==TARGET_OBSTACLE && !hasCollided) secondaryAnim = 0;
}
