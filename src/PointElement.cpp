#include "PointElement.h"


ofEvent<ButtonKind> PointElement::buttonEvent = ofEvent<ButtonKind>();

PointElement::PointElement(){}
PointElement::PointElement(ofVec2f position, ElementKind type){
    pos = position;
    kind = type;
    reset();
    buttonKind = NOT_BUTTON;
    size = 1;
}
void PointElement::reset(){
    animation = 0;
    secondaryAnim = 0;
    hasCollided = false;
    valid = false;
    buttonClicked = false;
    tolerance = 0;
}

bool PointElement::collisionCheck(ofVec2f pt1, ofVec2f pt2, ofVec2f pt3, ofVec2f pt4){
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

void PointElement::draw(float opacity){
    ofNoFill(); ofSetLineWidth(3);
    
    if(kind==DESTROYER_ELEMENT){
        animation = fmod(animation+1,90);
        
        ofSetLineWidth(3);
        ofSetColor(Colors[GAME_OBJ], opacity*4*animation-1);
        ofCircle(pos.x, pos.y, 45-(animation*0.5));
        
        ofSetColor(Colors[GAME_OBJ], opacity*4*((animation<45)? (animation+45): (animation-45))-1);
        ofCircle(pos.x, pos.y, (animation<45)?22.5-(animation*0.5):67.5-(animation*0.5));
    }
    else if(kind == TARGET_ELEMENT || kind == LINKED_TARGET_ELEMENT){
        animation += 1;
        if(animation>=120) animation = 0;
        size = 15+sin((animation*TWO_PI)/120)*3;
        
        ofSetColor(Colors[GAME_OBJ], 255*opacity);
        ofCircle(pos.x, pos.y, size);
        
        if(hasCollided){
            if(!valid){
                if(secondaryAnim <= 13) secondaryAnim += (14-secondaryAnim)/(secondaryAnim+4);
                else if (buttonKind == NOT_BUTTON) valid = true;
            }
            
            ofSetColor(Colors[GAME_OBJ]);ofFill();
            ofCircle(pos.x, pos.y, secondaryAnim);
        }

        // rays
        if(buttonKind == NOT_BUTTON){
            ofPushMatrix();
            ofTranslate(pos.x, pos.y);
            ofRotate(animation*0.2);
            for(int i=0;i<15;i++){
                ofRotate(24);
                ofLine(30, 0, 35, 0);
            }
            ofPopMatrix();
        }
    }
    
    glLineWidth(0);
}

void PointElement::collided(){
    if(buttonKind!=NOT_BUTTON && !hasCollided) ofNotifyEvent(buttonEvent, buttonKind, this);
    hasCollided = true;
    tolerance = 20;
}
