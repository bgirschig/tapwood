//
//  Grid.cpp
//  tapwood
//
//  Created by bastien girschig on 11/05/2015.
//
//

#include "Grid.h"

Grid::Grid(){}
void Grid::init(int squareSize){
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    int colCount = ofGetHeight()/squareSize+1;
    int total = colCount*(ofGetWidth()/squareSize)+1;
    
    for (int i = 0; i<total; ++i)
    {
        mesh.addVertex(ofPoint((i%colCount)*squareSize, (i/colCount)*squareSize));
        particles.push_back(Particle(i, (i%colCount)*squareSize, (i/colCount)*squareSize, 0, 0));
    }
}
void Grid::update(vector<Wave> & waves){
    int wCount = waves.size();
    int gCount = particles.size();
    
    for (int g=0; g < gCount; g++){                                    // for each point in the grid ...
        particles[g].force.set(0,0);
        for (int w=0; w < wCount; w++) {                                           // for each wave ...
            int pCount = waves[w].particles.size();
            for (int p=0; p < pCount; p++){                                       // for each particle of each wave ...
                particles[g].attract(waves[w].particles[p].position);    // ... add attraction
            }
        }
//        particles[g].update(0);
        mesh.setVertex(g, particles[g].position+particles[g].force);
    }
}

void Grid::draw(){
    ofPushMatrix();
//    ofTranslate(1, 1, 0);
    mesh.draw();
    ofPopMatrix();
}