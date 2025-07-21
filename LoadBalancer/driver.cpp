#include <iostream>
#include <fstream>
#include <queue>
#include "request.h"
#include "webserver.h"
#include "loadBalancer.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Creates a new request with randomized IP addresses and time.
 * 
 * Allocates two arrays of four integers each to represent inIP and outIP parts,
 * fills them with random values between 0 and 255, and a random time.
 * Logs the generated request to "log.txt".
 * 
 * @return request Newly created request object.
 */
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
    outputFile << "New Request: In - " << to_string(inIP[0]) << "." << to_string(inIP[1]) << "." << to_string(inIP[2]) << "." << to_string(inIP[3])
               << " | Out - " << to_string(outIP[0]) << "." << to_string(outIP[1]) << "." << to_string(outIP[2]) << "." << to_string(outIP[3])
               << " | Time: " << time << "\n";

    return newRequest;
}

/**
 * @brief Main driver function to initialize load balancer, create webservers,
 *        generate requests, and run the simulation clock cycles.
 * 
 * Prompts user for number of servers, creates and distributes requests,
 * processes requests over simulated time, and logs status updates.
 * 
 * @return int Exit status code.
 */
int main()
{
    ofstream outputFile("log.txt", std::ios::out);
    int clockCycles = 10000;

    loadBalancer * LB = new loadBalancer();

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
    LB->balanceRequests();
    outputFile << "\n\n-- Start Processing Requests --\n\n";

    outputFile << "\n\nAt start of simulation: Total Requests in Queue: " << to_string(LB->requestQueue.size()) << "\n";

    {
        int totalRequests = 0;
        for(int j = 0; j < LB->thisWebservers.size(); j++){
            totalRequests += LB->thisWebservers[j].requests.size();
        }
        outputFile << "\n\nAt start of simulation: Total Requests on Servers: " << to_string(totalRequests) << "\n";
        outputFile.close();
    }

    for(int i = 0; i < clockCycles; i++)
    {
        outputFile.open("log.txt", std::ios::app);
        outputFile << "\n\n- Running Clock Cycle " << to_string(i) << " -\n\n";
        outputFile.close();

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

    int totalRequests2 = 0;
    for(int j = 0; j < LB->thisWebservers.size(); j++){
        totalRequests2 += LB->thisWebservers[j].requests.size();
    }

    outputFile.open("log.txt", std::ios::app);
    outputFile << "\n\nAt end of simulation: Total Requests in Queue: " << to_string(LB->requestQueue.size()) << "\n";
    outputFile << "\n\nAt end of simulation: Total Requests on Servers: " << to_string(totalRequests2) << "\n";
    outputFile.close();

    return 0;
}
