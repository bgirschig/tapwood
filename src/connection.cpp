//
//  connection.cpp
//  sn_tcpClient
//
//  Created by bastien girschig on 10/05/2015.
//
//

#include "connection.h"

connection::connection(){}
void connection::setup(string ip, int port){
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
                
                vector<string> parts = ofSplitString(str, ",");
                
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
            Connected = tcpClient.setup("127.0.0.1", 11999);
            connectTime = ofGetElapsedTimeMillis();
        }
    }
}

void connection::drawInterface(){
    ofSetColor(30, 80);ofRect(0, 0, 600, 450);
    ofSetColor(255);
    if(Connected)ofDrawBitmapString("status: connected to server", 15, 20);
    else ofDrawBitmapString("status: not connected. start server and check ports", 15, 20);
    ofDrawBitmapString("raw messages:\n\n"+rawMsg, 15, 75);
    ofDrawBitmapString("satus messages:\n\n"+statusMessages, 400, 75);
}

void connection::send(string msg){
    tcpClient.send(msg);
}