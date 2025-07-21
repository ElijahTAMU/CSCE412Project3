#ifndef REQUEST_H
#define REQUEST_H
#include <string>

/**
 * @struct IP
 * @brief Represents an IPv4 address as four integer parts.
 */
struct IP
{
    int part1; ///< First octet of the IP address.
    int part2; ///< Second octet of the IP address.
    int part3; ///< Third octet of the IP address.
    int part4; ///< Fourth octet of the IP address.
};

/**
 * @class request
 * @brief Represents a network request with source and destination IPs and a timestamp.
 */
class request
{
public:
    IP inIP;   ///< Incoming/source IP address.
    IP outIP;  ///< Outgoing/destination IP address.
    int time;  ///< Timestamp or time associated with the request.

    /**
     * @brief Default constructor.
     */
    request(){};

    /**
     * @brief Constructs a request with given source/destination IP arrays and time.
     * 
     * @param in Pointer to an array of 4 ints representing the source IP.
     * @param out Pointer to an array of 4 ints representing the destination IP.
     * @param t Timestamp for the request.
     */
    request(int* in, int* out, int t)
    {
        inIP.part1 = in[0];
        inIP.part2 = in[1];
        inIP.part3 = in[2];
        inIP.part4 = in[3];

        outIP.part1 = out[0];
        outIP.part2 = out[1];
        outIP.part3 = out[2];
        outIP.part4 = out[3];

        time = t;
    }
};

#endif
