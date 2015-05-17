#include "Obstacle.h"



Obstacle::Obstacle(){}
Obstacle::Obstacle(ofVec2f position){
    pos = position;
    hasCollided = false;
}

bool Obstacle::collisionCheck(ofVec2f pt1, ofVec2f pt2, ofVec2f pt3, ofVec2f pt4){
//    int previous_side = -2;
//    cout << "//////////\n";
//    cout << pt1 << endl;
//    cout << pt2 << endl;
//    cout << pt3 << endl;
//    cout << pt4 << endl;
    
    if((pos.x<pt1.x && pos.x<pt2.x && pos.x<pt3.x && pos.x<pt4.x) ||
       (pos.x>pt1.x && pos.x>pt2.x && pos.x>pt3.x && pos.x>pt4.x) ||
       (pos.y<pt1.y && pos.y<pt2.y && pos.y<pt3.y && pos.y<pt4.y) ||
       (pos.y>pt1.y && pos.y>pt2.y && pos.y>pt3.y && pos.y>pt4.y)
       ){
        return false;
    }
    return true;
    
//    vector<ofVec2f> vertices;
//    vertices.push_back(pt1);
//    vertices.push_back(pt2);
//    vertices.push_back(pt3);
//    vertices.push_back(pt4);
//    
//    for (int i=0; i<4; i++) {
//        a = vertices[i];
//        b = vertices[(i+1)%4];
//        
//        affine_segment = b - a;
//        affine_point = pos - a;
//        
//        float currentSide = (a.x*b.y)-(a.y*b.x);
//        if(currentSide==0) return false;
//        currentSide = (currentSide<0)? -1 : 1;
//        
//        if(previous_side==-2) previous_side = currentSide;
//        else if(previous_side != current_side) return false;
//    }
//    return true;
    
////////// intersection 2 segments (pta-ptb and point-prevPoint) ////////////////////
//    ofVec2f s1 = pointB-pointA;
//    ofVec2f s2 = point-prevPoint;
//
//    float s, t;
//    s = (-s1.y * (pointA.x - prevPoint.x) + s1.x * (pointA.y - prevPoint.y)) / (-s2.x * s1.y + s1.x * s2.y);
//    t = ( s2.x * (pointA.y - prevPoint.y) - s2.y * (pointA.x - prevPoint.x)) / (-s2.x * s1.y + s1.x * s2.y);
//    
//    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) return 1;
//    return 0; // No collision
}

void Obstacle::draw(){
    if(hasCollided) ofSetColor(0,255,0);
    else(ofSetColor(255));
    ofCircle(pos.x, pos.y, 3);
}
