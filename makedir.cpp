#include "makedir.hpp"
#include <curl/curl.h>
#include <cstdio>
#include <iostream>

using namespace std;

makedir::makedir(string turl, string tname, string tpass, CURL* t_curl, string startdir)
{
    curl=t_curl;
    ftpurl = turl;
    login = tname;
    password = tpass;
    string name = startdir + "ftp-list";
    ftpfile = fopen(name.c_str(), "wb"); /* b is binary, needed on win32 */
}

makedir::~makedir()
{
    curl_slist_free_all(headerlist);
    fclose(ftpfile);
}

void makedir::mainfunc(){
    if(curl) {
        headerlist = NULL;
        cout << "Enter directory name" << endl;
        cin >> name;
        buff1 = "MKD " + name;
        curl_easy_setopt(curl, CURLOPT_URL, ftpurl.c_str());
        if(login != "\0" && login != "\n") {
            curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, ftpfile);
        headerlist = curl_slist_append(headerlist, buff1.c_str());
        curl_easy_setopt(curl, CURLOPT_QUOTE, headerlist);
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        /* clean up the FTP commands list */
    }
}
