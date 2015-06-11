#include "PointElement.h"


ofEvent<ButtonKind> PointElement::buttonEvent = ofEvent<ButtonKind>();

PointElement::PointElement(){}
PointElement::PointElement(ofVec2f position, ElementKind type){
    pos = position;
    kind = type;
    reset();
    buttonKind = NOT_BUTTON;
}
void PointElement::reset(){
    animation = -1;
    secondaryAnim = 0;
    scale = 10;
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
        animation = (animation+1) % 90;
        
        ofSetLineWidth(3);
        ofSetColor(255, opacity*4*animation-1);
        ofCircle(pos.x, pos.y, 45-(animation*0.5));
        
        ofSetColor(255, opacity*4*((animation<45)? (animation+45): (animation-45))-1);
        ofCircle(pos.x, pos.y, (animation<45)?22.5-(animation*0.5):67.5-(animation*0.5));
    }
    else if(kind == TARGET_ELEMENT){
        if(animation<120){
            animation ++;
            if(animation>=120) animation = 0;
            
            ofSetColor(255, 255*opacity);
            ofCircle(pos.x, pos.y, 15+sin((animation*TWO_PI)/120)*3);
            
            if(hasCollided){
                if(secondaryAnim <= 17) secondaryAnim += (18-secondaryAnim)/(secondaryAnim+4);
                else if (buttonKind == NOT_BUTTON) valid = true;
                
                ofFill();
                ofCircle(pos.x, pos.y, secondaryAnim);
            }
            // lines
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
    }
    
    glLineWidth(0);
}

void PointElement::collided(){
    if(buttonKind!=NOT_BUTTON && !hasCollided) ofNotifyEvent(buttonEvent, buttonKind, this);
    hasCollided = true;
}
