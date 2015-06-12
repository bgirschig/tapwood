#include "Link.h"

Link::Link(){
    animation = 0;
    valid = false;
}

void Link::update(){
    animation+=0.1;
    
    valid = true;
    // check if all elements are valid
    for (int i=0; i<elements.size(); i++) if(!elements[i]->hasCollided) valid = false;
    
    // if not, 'de-animate' linked points
    if(!valid){
        for(int i=0;i<elements.size();i++){
            if(elements[i]->valid){
                if(elements[i]->secondaryAnim>0) elements[i]->secondaryAnim-=1.8;
                else{
                    elements[i]->hasCollided = false;
                    elements[i]->valid = false;
                    valid = false;
                }
            }
        }
    }
}
void Link::draw(float opacity){
    ofSetColor(Colors[GAME_OBJ], 255*opacity*0.2);
    for(int i=0;i<elements.size();i++){
        if(i>0)ofLine(elements[i-1]->pos.x, elements[i-1]->pos.y, elements[i]->pos.x, elements[i]->pos.y);
    }
}
void Link::add(PointElement* el){
    elements.push_back(el);
}