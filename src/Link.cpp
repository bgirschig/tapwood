#include "Link.h"

Link::Link(){
    animation = 0;
}
void Link::update(){
    animation+=0.1;
}
void Link::draw(float opacity){
    for(int i=0;i<elements.size();i++) elements[i].draw(255*opacity);
}