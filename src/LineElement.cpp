#include "LineElement.h"

LineElement::LineElement(){}
LineElement::LineElement(ofVec2f _point1, ofVec2f _point2){ init(_point1, _point2, false); }
LineElement::LineElement(ofVec2f _point1, ofVec2f _point2, bool _rotate){ init(_point1, _point2, _rotate); }

void LineElement::init(ofVec2f _point1, ofVec2f _point2, bool _rotate){
    pt1 = _point1;
    pt2 = _point2;
    rotate = _rotate;
    rotationPos = 0;
    
    animFrame = ofRandom(3);
    dampening = 1;

    length = pt2.distance(pt1)/2;
    center.set((pt1.x+pt2.x)/2, (pt1.y+pt2.y)/2);
    
    setEquation();
}

void LineElement::draw(float opacity){
    ofSetLineWidth(3);
    
    if(rotate){
        rotationPos+=0.009;
        pt1.set(center.x+sin(rotationPos)*length, center.y+cos(rotationPos)*length);
        pt2.set(center.x-sin(rotationPos)*length, center.y-cos(rotationPos)*length);
        setEquation();
    }
    
    animFrame+=0.1;
    ofNoFill(); ofSetColor(Colors[GAME_OBJ]);
    ofVec2f animVector = normal/(sin(animFrame)+1.18);
    
    ofLine(pt1.x+animVector.x, pt1.y+animVector.y, pt2.x+animVector.x, pt2.y+animVector.y);
    ofLine(pt1.x-animVector.x, pt1.y-animVector.y, pt2.x-animVector.x, pt2.y-animVector.y);
}

void LineElement::setEquation(){
    // equation of type 'y=ax+b'
    a = (pt2.y-pt1.y)/(pt2.x-pt1.x);
    b = pt1.y-(a*pt1.x);
    
    // pt1->pt2 vector
    local.set(pt2.x-pt1.x, pt2.y-pt1.y);
    
    // edge's normal (unit vector)
    normal.set(pt2.y-pt1.y,pt1.x-pt2.x); // right angle to vertor(x,y): (y,-x);
    normal.normalize();
}