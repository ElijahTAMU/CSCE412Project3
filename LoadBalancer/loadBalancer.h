#include <queue>
#include <vector>
#include "request.h"

class request;
class webserver;

using namespace std;

/**
 * @class loadBalancer
 * @brief Manages the distribution of requests across multiple webservers.
 * 
 * Holds a queue of incoming requests and a vector of webservers to which
 * requests are assigned. Responsible for balancing load and server allocation.
 */
class loadBalancer {
public:
    /** 
     * @brief Queue holding incoming requests to be distributed.
     */
    std::queue<request> requestQueue;

    /**
     * @brief Vector of active webservers handling requests.
     */
    std::vector<webserver> thisWebservers;

    /**
     * @brief Distributes requests from the queue to available webservers,
     *        allocating new servers if necessary.
     */
    void balanceRequests();

    /**
     * @brief Removes a webserver at the specified index.
     * 
     * @param index The index of the server to remove.
     */
    void removeServer(int index);
};
