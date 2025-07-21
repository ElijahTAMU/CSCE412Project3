#include "loadBalancer.h"
#include "webserver.h"
#include <iostream>
#include <fstream>

using namespace std;
    // update to distribute requests that fit the current time
    void loadBalancer::balanceRequests()
    {
        //cout << "Balancing requests." << endl;
        
        while (!requestQueue.empty())
        {
            bool didStore = false;

            for (auto& server : thisWebservers)
            {
                //cout << "on server " << server.name << endl;
                if (server.openToRequests)
                {
                    if (!requestQueue.empty()) {
                        server.requests.push_back(requestQueue.front());
                        requestQueue.pop();
                        didStore = true;
                    }
                }
            }

            if (!didStore)
            {
                ofstream outputFile("log.txt", std::ios::app);
                outputFile << "\n\n--- ALLOCATING NEW SERVER. ---";
                outputFile.close();

                //cout << "ALLOCATING NEW SERVER" << endl;
                webserver newServer = webserver(thisWebservers.size());
                cout << "new server ID: " << newServer.name << endl;
                thisWebservers.push_back(newServer);
            }
        }
    }


void loadBalancer::removeServer(int index) {
    if (index < 0 || index >= static_cast<int>(thisWebservers.size())) {
        cerr << "Error: Tried to remove invalid server index " << index << endl;
        return;
    }

    ofstream outputFile("log.txt", std::ios::app);
    outputFile << "\n--- WEBSERVER " << thisWebservers[index].name << " DEALLOCATED ---\n";
    outputFile.close();

    thisWebservers.erase(thisWebservers.begin() + index);
}
