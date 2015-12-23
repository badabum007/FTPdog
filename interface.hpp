#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <string>
#include <curl/curl.h>
#include <fstream>

using namespace std;

class interface
{
    string ftpurl, login, password, start_dir;
    CURL* curl;
    CURLcode res;

public:
    interface(string);
    interface(string, string, string);
    interface();
    ~interface();
    void set_ftpurl();
    void pwd();
    void cd();
    void ls();
    void user_ls();
    void improved_get();
    void rn();
    void rm();
    void mkd();
    void url_check();
    void get_startdir();
    void upload_func();
};

#endif // INTERFACE_HPP
