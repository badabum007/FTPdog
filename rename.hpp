#ifndef RENAME_HPP
#define RENAME_HPP
#include <curl/curl.h>
#include <iostream>
#include <cstdio>

using namespace std;

class rename
{
    struct curl_slist* headerlist;
    string ftpurl, login, password, rnfr, rnto, buff1, buff2;
    CURL* curl;
    CURLcode res;
    FILE* ftpfile;

public:
    rename(string turl, string tname, string tpass, CURL* t_curl, string startdir);
    void mainfunc();
    ~rename();
};

#endif // RENAME_HPP
