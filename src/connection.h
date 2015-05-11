#pragma once

#include <stdio.h>
#include "ofxNetwork.h"
#include "ofMain.h"

class connection{

    public:
    connection();
    void setup(string ip, int port);
    void update();
    void drawInterface();
    void send(string msg);
    
    ofxTCPClient tcpClient;
    string rawMsg;
    string statusMessages;
    ofEvent<string> serverEvent;
    ofEvent<string> deviceEvent;
    ofEvent<string> dataEvent;
    bool Connected;
    
    private:
    int msgCount;
    int connectTime;
};