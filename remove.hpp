#ifndef REMOVE_HPP
#define REMOVE_HPP
#include <curl/curl.h>
#include <iostream>
#include <cstdio>

using namespace std;

class remove
{
    struct curl_slist* headerlist;
    string ftpurl, login, password, buff1, buff2;
    CURL* curl;
    CURLcode res;
    FILE* ftpfile;
public:
    remove(string turl, string tname, string tpass, CURL* t_curl, string startdir);
    ~remove();
    void mainfunc();
    void remove_func(string name);
};

#endif // REMOVE_HPP
