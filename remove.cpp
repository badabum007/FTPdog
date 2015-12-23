#include "remove.hpp"
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

remove::remove(string turl, string tname, string tpass, CURL* t_curl, string startdir)
{
    curl = t_curl;
    ftpurl = turl;
    login = tname;
    password = tpass;
    string name = startdir + "ftp-list";
    ftpfile = fopen(name.c_str(), "wb"); /* b is binary, needed on win32 */
}

remove::~remove()
{
    /* clean up the FTP commands list */
    curl_slist_free_all(headerlist);
    fclose(ftpfile);
}

void remove::mainfunc()
{
    string name;
    cout << "Enter items to delete:" << endl;
    vector<string> list;
    cin.ignore(INT_MAX, '\n');
    while(true) {
        cin.clear();
        getline(cin, name);
        if(name != "")
            list.push_back(name);
        else
            break;
    }
    for(unsigned int i = 0; i < list.size(); i++)
        remove_func(list[i]);
}

void remove::remove_func(string name)
{
    if(curl) {
        headerlist = NULL;
        buff1 = "*DELE " + name;
        buff2 = "*RMD " + name;
        curl_easy_setopt(curl, CURLOPT_URL, ftpurl.c_str());
        if(login != "\0" && login != "\n") {
            curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, ftpfile);
        headerlist = curl_slist_append(headerlist, buff1.c_str());
        headerlist = curl_slist_append(headerlist, buff2.c_str());
        curl_easy_setopt(curl, CURLOPT_QUOTE, headerlist);
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
}
