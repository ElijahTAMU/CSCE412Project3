#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <vector>
#include "request.h"
using namespace std;

class webserver{
    public:
        webserver(int id)
        { 
            name = to_string(id);
            requestCap = 100;
            requests = vector<request>();
            openToRequests = true;
        }

        vector<request> requests;
        int requestCap;
        bool openToRequests;
        string name;

        void processRequests(int time);

        void askForRequests();

        void stopTakingRequests();
};

#endif