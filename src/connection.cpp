//
//  connection.cpp
//  sn_tcpClient
//
//  Created by bastien girschig on 10/05/2015.
//
//

#include "connection.h"

connection::connection(){}
void connection::setup(string _ip, int _port){
    ip = _ip;
    port = _port;
    
    Connected = tcpClient.setup(ip, port);
    tcpClient.setMessageDelimiter("\n");
    
    connectTime = 0;
    msgCount = 0;
    statusMessages = "";
    rawMsg = "";
}

void connection::update(){
    if(Connected){
        if(tcpClient.isConnected()){
            string str = tcpClient.receive();
            if( str.length() > 0 ){
                
                msgCount++;
                
                vector<string> parts = ofSplitString(str, ":");
                
                if(parts[0]=="serverStatus"){
                    if(parts[1]=="connect"){
                        string s = "connect";
                        ofNotifyEvent(serverEvent, s, this);
                        statusMessages =  "connection to server\n"+statusMessages;
                    }
                    else if(parts[1]=="shutdown"){
                        string s = "shutdown";
                        ofNotifyEvent(serverEvent, s, this);
                        statusMessages = "server shut down\n"+statusMessages;
                    }
                    else if(parts[1]=="crash"){
                        string s = "crash";
                        ofNotifyEvent(serverEvent, s, this);
                        statusMessages = "server crash\n"+statusMessages;
                    }
                }
                
                else if(parts[0]=="deviceStatus"){
                    if(parts[1]=="disconnected"){
                        string s = "disconnected";
                        ofNotifyEvent(deviceEvent, s, this);
                        statusMessages = "the device is disconnected\n"+statusMessages;
                    }
                    else if(parts[1]=="connected"){
                        string s = "connected";
                        ofNotifyEvent(deviceEvent, s, this);
                        statusMessages = "the device is connected\n"+statusMessages;
                    }
                    else{
                        string s = "unknown";
                        ofNotifyEvent(deviceEvent, s, this);
                        statusMessages = "unknown device message:\n   "+ofToString(parts[1])+"\n"+statusMessages;
                    }
                }
                else if(parts[0]=="calibration"){
                    if(parts[1]=="start"){
                        string s = "recalibrate";
                        ofNotifyEvent(serverEvent, s, this);
                    }
                    ofVec2f v;
                    if(parts[1]=="step") ofNotifyEvent(tapEvent, v, this);
                }
                else if(parts[0]=="tap"){
                    vector<string> pt = ofSplitString(parts[1], ",");
                    ofVec2f vect = ofVec2f(ofToFloat(pt[0]), ofToFloat(pt[1]));
                    ofNotifyEvent(tapEvent, vect, this);
                }
                else ofNotifyEvent(dataEvent, str, this);
                
                // for interface only
                rawMsg = ofToString(msgCount)+"\t"+str+"\n"+rawMsg;
            }
        }
        else Connected = false;
    }
    
    // retry connection
    else{
        if( ofGetElapsedTimeMillis() - connectTime > 5000 ){
            cout << "trying connection to server..." << endl;
            Connected = tcpClient.setup(ip, port);
            connectTime = ofGetElapsedTimeMillis();
        }
    }
}

void connection::drawInterface(){
    ofSetColor(30, 80);ofRect(0, 0, 600, 450);
    ofSetColor(255);
    if(Connected)ofDrawBitmapString("status: connected to server", 15, 20);
    else{
        ofSetColor(ofColor(0,100)); ofFill();
        ofDrawBitmapString("status: not connected. start server and check ports", 15, 20);
    }
    ofDrawBitmapString("raw messages:\n\n"+rawMsg, 15, 75);
    ofDrawBitmapString("satus messages:\n\n"+statusMessages, 400, 75);
}

void connection::send(string msg){
    if(tcpClient.isConnected()) tcpClient.send(msg);
}