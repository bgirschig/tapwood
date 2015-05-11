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
    cout << total;
    for (int i = 0; i<total; ++i)
    {
        mesh.addVertex(ofPoint((i%colCount)*squareSize, (i/colCount)*squareSize));
    }
}
void Grid::update(){
}
void Grid::draw(){
    ofPushMatrix();
//    ofTranslate(1, 1, 0);
    mesh.draw();
    ofPopMatrix();
}