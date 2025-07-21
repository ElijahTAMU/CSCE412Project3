#include <queue>
#include <vector>
#include "request.h"

class request;
class webserver;

using namespace std;
class loadBalancer{
    public:

        // create requests
        std::queue<request> requestQueue;
        std::vector<webserver> thisWebservers;

        void balanceRequests();
        void removeServer(int index);

};