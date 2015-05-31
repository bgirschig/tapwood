#include "LineElement.h"

LineElement::LineElement(){}
LineElement::LineElement(ofVec2f _point1, ofVec2f _point2){
    pt1 = _point1;
    pt2 = _point2;
    
    dampening = 1;
    setEquation();
}
void LineElement::draw(float opacity){
    ofNoFill();ofSetColor(255, 255*opacity);
    ofLine(pt1.x, pt1.y, pt2.x, pt2.y);
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