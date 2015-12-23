#ifndef UPLOAD_HPP
#define UPLOAD_HPP
#include <curl/curl.h>
#include <iostream>

using std::string;

class upload
{
    CURL* curl;
    CURLcode res;
    FILE* hd_src;
    curl_off_t fsize;
    string upload_file_as, url, login, pass;

public:
    upload(string turl, string tname, string tpass, CURL* t_curl);
    ~upload();
    // size_t read_callback(void* ptr, size_t size, size_t nmemb, void* stream);
    void mainfunc();
    void upload_func(string local_file);
};

#endif // UPLOAD_HPP
