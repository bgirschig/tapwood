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
    ofVec2f vect;
    
    for(int i=1;i<elements.size();i++){
        vect = elements[i-1]->pos - elements[i]->pos;
        vect.normalize();
        ofLine((elements[i-1]->pos - vect*elements[i-1]->size).x,
               (elements[i-1]->pos - vect*elements[i-1]->size).y,
               (elements[i]->pos + vect*elements[i-1]->size).x,
               (elements[i]->pos + vect*elements[i-1]->size).y
               );
    }
}
void Link::add(PointElement* el){
    elements.push_back(el);
}