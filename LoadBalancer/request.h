#ifndef REQUEST_H
#define REQUEST_H
#include <string>

struct IP
{
    int part1;
    int part2;
    int part3;
    int part4;
};

class request
{
    public:
        IP inIP;
        IP outIP;
        int time; 

        request(){};

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