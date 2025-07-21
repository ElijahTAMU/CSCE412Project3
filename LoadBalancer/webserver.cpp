#include "webserver.h"
#include <iostream>
#include <fstream>

using namespace std;

void webserver::processRequests(int time)
{
    int before = static_cast<int>(requests.size());
    //cout << "Current requests in 'requests': " << requests.size() << endl;

    for (auto it = requests.begin(); it != requests.end(); ) {
        if (it->time <= time) {
            it = requests.erase(it);
        } else {
            ++it;
        }
    }

    //cout << "Requests resolved: " << (before - static_cast<int>(requests.size())) << endl;

    if (requests.size() < 100) {
        askForRequests();
    } else if (openToRequests) {
        stopTakingRequests();
    }
}


void webserver::askForRequests()
{
    openToRequests = true;
    ofstream outputFile("log.txt", std::ios::app);
    outputFile << "\nA server has resolved some requests and is now open.\n";
    outputFile.close();
}

void webserver::stopTakingRequests()
{
    openToRequests = false;
    ofstream outputFile("log.txt", std::ios::app);
    outputFile << "\nA server has stopped taking requests. It is currently full and will open after resolving some requests.\n";
    outputFile.close();
}