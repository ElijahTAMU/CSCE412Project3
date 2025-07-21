#include <iostream>
#include <fstream>
#include <queue>
#include "request.h"
#include "webserver.h"
#include "loadBalancer.h"
#include <string>
#include <vector>

using namespace std;

request createRequest()
{

    int* inIP = new int[4];
    inIP[0] = rand() % 256;
    inIP[1] = rand() % 256;
    inIP[2] = rand() % 256;
    inIP[3] = rand() % 256;

    int* outIP = new int[4];
    outIP[0] = rand() % 256;
    outIP[1] = rand() % 256;
    outIP[2] = rand() % 256;
    outIP[3] = rand() % 256;

    int time = rand() % 10000;

    request newRequest = request(inIP, outIP, time);

    ofstream outputFile("log.txt", std::ios::app);

    outputFile << "New Request: In - " << to_string(inIP[0]) << "." << to_string(inIP[1]) << "." << to_string(inIP[2]) << "." << to_string(inIP[3]) <<
    " | Out - "<< to_string(outIP[0]) << "." << to_string(outIP[1]) << "." << to_string(outIP[2]) << "." << to_string(outIP[3]) << " | Time: " << time << "\n";

    return newRequest;
}

int main()
{
    ofstream outputFile("log.txt", std::ios::out);
    // track runtime
    int clockCycles = 10000;

    // create requests + loadBalancer and run LB to balance requests across servers
    loadBalancer * LB = new loadBalancer();


    // create webservers
    vector<webserver> webservers = vector<webserver>();

    int serverCount = 0;

    bool valid = false;
    while(!valid){
        cout << "How many servers will we be running today? (Enter a numeric value between 1 and 100)" << endl;
        string input;
        cin >> input;

        try{
            serverCount = stoi(input);

            if(serverCount >= 1 && serverCount <= 100){
                valid = true;
                for(int i = 0; i < serverCount; i++){
                    LB->thisWebservers.push_back(webserver(i));
                }
            }
        }
        catch(...){
            cout << "Invalid input. Try again.";
        }
    }

    outputFile << "-- Initial Request Creation--\n\n"; 
    
    outputFile.close();

    for(int i = 0; i < serverCount * 100; i++){
        LB->requestQueue.push(createRequest());
    }

    outputFile.open("log.txt", std::ios::app);

    //balance load at beginning
    LB->balanceRequests();

    outputFile << "\n\n-- Start Processing Requests --\n\n";

    outputFile << "\n\nAt start of simulation: Total Requests in Queue: " << to_string(LB->requestQueue.size()) << "\n";

    // status report for content of servers
    {
        int totalRequests;
        for(int j = 0; j < LB->thisWebservers.size(); j++){
            totalRequests += LB->thisWebservers[j].requests.size();
        }
        outputFile << "\n\nAt start of simulation: Total Requests on Servers: " << to_string(totalRequests) << "\n";

        outputFile.close();
    }

    // main driver logic
    for(int i = 0; i < clockCycles; i++)
    {
        outputFile.open("log.txt", std::ios::app);
        outputFile << "\n\n- Running Clock Cycle " << to_string(i) << " -\n\n";
        outputFile.close();

        //cout << "Status report: Total web servers: " << to_string(LB->thisWebservers.size()) << "; requests in Queue (should be 0): " << to_string(LB->requestQueue.size()) <<endl;

        for(int j = 0; j < rand() % 200; j++){
            LB->requestQueue.push(createRequest());
        }

        LB->balanceRequests();

        for (auto it = LB->thisWebservers.begin(); it != LB->thisWebservers.end(); )
        {
            it->processRequests(i);
            if (it->requests.empty()) {
                it = LB->thisWebservers.erase(it);
            } else {
                ++it;
            }
        }
    }

    int totalRequests2;
    for(int j = 0; j < LB->thisWebservers.size(); j++){
        totalRequests2 += LB->thisWebservers[j].requests.size();
    }

    outputFile.open("log.txt", std::ios::app);
    outputFile << "\n\nAt end of simulation: Total Requests in Queue: " << to_string(LB->requestQueue.size()) << "\n";
    outputFile << "\n\nAt end of simulation: Total Requests on Servers: " << to_string(totalRequests2) << "\n";
    outputFile.close();

}

