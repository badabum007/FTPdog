#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <fstream>

using namespace std;

class client
{
    string command, arguments, request;
    int choize;

public:
    client();
    ~client();
    void terminal_session(string);
    void actions();
};

#endif // CLIENT_HPP
