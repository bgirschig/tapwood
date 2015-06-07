#pragma once

#include <stdio.h>
#include "ofxNetwork.h"
#include "ofMain.h"

class connection{

    public:
    connection();
    void setup(string _ip, int _port);
    void update();
    void drawInterface();
    void send(string msg);
    
    ofxTCPClient tcpClient;
    string rawMsg;
    string statusMessages;
    ofEvent<string> serverEvent;
    ofEvent<string> deviceEvent;
    ofEvent<string> dataEvent;
    ofEvent<ofVec2f> tapEvent;
    bool Connected;

    private:
    int msgCount;
    int connectTime;
    string ip;
    int port;
};