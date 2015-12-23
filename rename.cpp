#include "rename.hpp"
#include <iostream>
#include <cstdio>

using namespace std;

rename::rename(string turl, string tname, string tpass, CURL* t_curl, string startdir)
{
    curl = t_curl;
    ftpurl = turl;
    login = tname;
    password = tpass;
    string name = startdir + "ftp-list";
    ftpfile = fopen(name.c_str(), "wb"); /* b is binary, needed on win32 */
}

rename::~rename()
{
    /* clean up the FTP commands list */
    curl_slist_free_all(headerlist);
    fclose(ftpfile);
}

void rename::mainfunc()
{
    if(curl) {
        headerlist = NULL;
        cout << "Enter item name to rename from:" << endl;
        cin >> rnfr;
        cout << "Enter item name to rename to:" << endl;
        cin >> rnto;
        buff1 = "RNFR " + rnfr;
        buff2 = "RNTO " + rnto;
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
