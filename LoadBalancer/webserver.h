#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <vector>
#include "request.h"
using namespace std;

/**
 * @class webserver
 * @brief Represents a webserver that holds and processes network requests.
 */
class webserver {
public:
    /**
     * @brief Constructs a webserver with a unique ID.
     * 
     * @param id The identifier for this webserver, converted to string as the name.
     */
    webserver(int id)
    { 
        name = to_string(id);
        requestCap = 100;
        requests = vector<request>();
        openToRequests = true;
    }

    vector<request> requests;   ///< List of current requests being handled by the server.
    int requestCap;             ///< Maximum capacity of requests the server can handle.
    bool openToRequests;        ///< Indicates if the server is accepting new requests.
    string name;                ///< Unique name/ID of the server.

    /**
     * @brief Processes requests up to the given time, removing completed ones.
     * 
     * @param time The current time step to check requests against.
     */
    void processRequests(int time);

    /**
     * @brief Marks the server as open to accept new requests and logs this event.
     */
    void askForRequests();

    /**
     * @brief Marks the server as closed to new requests and logs this event.
     */
    void stopTakingRequests();
};

#endif
