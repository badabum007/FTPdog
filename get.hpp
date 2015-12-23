#ifndef GET_HPP
#define GET_HPP
#include <iostream>
#include <curl/curl.h>

using namespace std;

class get
{
    string ftpurl, login, password, path, user_work_dir;
    CURL* curl;
    CURLcode res;
    struct FtpFile
    {
        const char* filename;
        FILE* stream;
    };

public:
    get(string t_url, string t_name, string t_pass, CURL* t_curl, string startdir);
    ~get();
    void mainfunc();
    void get_wd();
    static size_t my_fwrite(void* buffer, size_t size, size_t nmemb, void* stream);
    void download(string filename);
};

#endif // GET_HPP