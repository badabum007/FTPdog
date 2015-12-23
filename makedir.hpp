#ifndef MAKEDIR_HPP
#define MAKEDIR_HPP
#include <curl/curl.h>
#include <cstdio>
#include <iostream>

using namespace std;

class makedir
{
    struct curl_slist* headerlist;
    FILE* ftpfile;
    string name, buff1, ftpurl, login, password;
    CURL* curl;
    CURLcode res;

public:
    makedir(string turl, string tname, string tpass, CURL* t_curl, string startdir);
    ~makedir();
    void mainfunc();
};

#endif // MAKEDIR_HPP
