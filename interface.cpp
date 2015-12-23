#include "interface.hpp"
#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <cstdlib>
#include "get.hpp"
#include "upload.hpp"
#include "makedir.hpp"
#include "rename.hpp"
#include "remove.hpp"

using namespace std;

interface::interface()
{
    set_ftpurl();
    get_startdir();
    curl = curl_easy_init();
}

void interface::url_check()
{
    if(ftpurl.find("ftp://") == string::npos)
        ftpurl.insert(0, "ftp://");
    if(ftpurl[ftpurl.length() - 1] != '/')
        ftpurl += '/';
}

void interface::get_startdir()
{
    fstream user_start;
    user_start.open("start_location", ios::in | ios::out | ios::trunc);
    system("pwd > start_location");
    user_start.seekg(0);
    // reading path to string
    getline(user_start, start_dir);
    start_dir += '/';
    user_start.close();
}

// constructors for debugging
interface::interface(string url)
{
    ftpurl = url;
    url_check();
    get_startdir();
    curl = curl_easy_init();
}

interface::interface(string temp_urlname, string temp_login, string temp_password)
{
    login = temp_login;
    password = temp_password;
    ftpurl = temp_urlname;
    url_check();
    get_startdir();
    curl = curl_easy_init();
}

interface::~interface()
{
    curl_easy_cleanup(curl);
}

void interface::set_ftpurl()
{
    cout << "Enter the ftp name: " << endl;
    cin >> ftpurl;
    url_check();
    cout << "Enter the ftp login: " << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, login);
    if(login != "\0") {
        cout << "Enter a ftp password: " << endl;
        getline(cin, password);
    } else {
        password = "\0";
    }
}

void interface::pwd()
{
    cout << ftpurl << endl;
}

void interface::cd()
{
    cout << "Enter path to directory" << endl;
    string path;
    cin >> path;
    if(path.find("ftp://") != string::npos)
        ftpurl = path;
    else {
        ftpurl += path;
    }
    if(ftpurl[ftpurl.length() - 1] != '/')
        ftpurl += '/';
}

void interface::rm()
{
    class remove removeobj(ftpurl, login, password, curl, start_dir);
    removeobj.mainfunc();
}

void interface::rn()
{
    class rename renameobj(ftpurl, login, password, curl, start_dir);
    renameobj.mainfunc();
}

void interface::ls()
{

    if(curl) {
        if(login != "\0" && login != "\n") {
            curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_URL, ftpurl.c_str());
        curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 0L);
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
}

void interface::mkd()
{
    makedir mkdobj(ftpurl, login, password, curl, start_dir);
    mkdobj.mainfunc();
}

void interface::upload_func()
{
    upload upl(ftpurl, login, password, curl);
    upl.mainfunc();
}

void interface::improved_get()
{
    get getobj(ftpurl, login, password, curl, start_dir);
    getobj.mainfunc();
}