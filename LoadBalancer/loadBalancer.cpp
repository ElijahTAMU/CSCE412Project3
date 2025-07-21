#include "loadBalancer.h"
#include "webserver.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @brief Distributes requests from the queue to available webservers in a round-robin style.
 * 
 * Iterates through the list of servers and assigns requests to servers open to receiving them.
 * If no server can take more requests, allocates a new webserver and continues distributing.
 */
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

/**
 * @brief Removes a webserver at the specified index from the list.
 * 
 * Checks if the index is valid, logs the deallocation, and erases the server from the vector.
 * 
 * @param index The index of the webserver to remove.
 */
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
