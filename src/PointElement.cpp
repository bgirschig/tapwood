#include "PointElement.h"


ofEvent<ButtonKind> PointElement::buttonEvent = ofEvent<ButtonKind>();

PointElement::PointElement(){}
PointElement::PointElement(ofVec2f position, ElementKind type){
    pos = position;
    kind = type;
    reset();
    buttonKind = NOT_BUTTON;
    size = 1;
    animation = ofRandom(20);
}
void PointElement::reset(){
    secondaryAnim = 0;
    hasCollided = false;
    valid = false;
    buttonClicked = false;
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
        animation = fmod(animation+1,45);
        
        ofSetLineWidth(3);
        ofSetColor(Colors[GAME_OBJ], opacity*4*animation-1);
        ofCircle(pos.x, pos.y, 23-(animation*0.5));
        
        ofSetColor(Colors[GAME_OBJ], opacity*4*((animation<23)? (animation+23): (animation-23))-1);
        ofCircle(pos.x, pos.y, (animation<23)?11.25-(animation*0.5):33.75-(animation*0.5));
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
    if(!hasCollided){
        if(buttonKind!=NOT_BUTTON) ofNotifyEvent(buttonEvent, buttonKind, this);
        else if(kind==TARGET_ELEMENT){ string val = "targetReached"; ofNotifyEvent(Utils::playSoundEventUtil, val, this);}
        hasCollided = true;
    }
}
