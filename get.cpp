#include "get.hpp"
#include <curl/curl.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <vector>

using namespace std;

get::get(string t_url, string t_name, string t_pass, CURL* t_curl, string startdir)
{
    curl = t_curl;
    ftpurl = t_url;
    login = t_name;
    password = t_pass;
    path = startdir;
}

get::~get()
{
}

size_t get::my_fwrite(void* buffer, size_t size, size_t nmemb, void* stream)
{
    struct FtpFile* out = (struct FtpFile*)stream;
    if(out && !out->stream) {
        // open file for writing
        out->stream = fopen(out->filename, "wb");
        if(!out->stream)
            return -1; // failure, can't open file to write
    }
    return fwrite(buffer, size, nmemb, out->stream);
}

void get::get_wd()
{
    fstream user_wd;
    string temp = path + "user_working_directory", command = "pwd > " + temp;
    user_wd.open(temp.c_str(), ios::trunc | ios::out | ios::in);
    system(command.c_str());
    user_wd.seekg(0);
    // reading path to string
    getline(user_wd, user_work_dir);
    user_wd.close();
}

void get::download(string filename)
{
    string absolute_filename = user_work_dir + "/" + filename;
    string fileurl = ftpurl + filename;
    // name to store the file as if successful
    struct FtpFile ftpfile = { absolute_filename.c_str(), NULL };
    if(curl) {
        if(login != "\0" && login != "\n") {
            curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_URL, fileurl.c_str());
        // Define our callback to get called when there's data to be written
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
        // Set a pointer to our struct to pass to the callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
        curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 0L);
        res = curl_easy_perform(curl);
        if(CURLE_OK != res) {
            // we failed
            fprintf(stderr, "curl told us %d\n", res);
        } else {
            ofstream test;
            test.open(filename.c_str());
            if(!test.is_open()) {
                test.close();
                string temp = "touch " + filename;
                system(temp.c_str());
            } else
                test.close();
        }
    }
    if(ftpfile.stream)
        fclose(ftpfile.stream); // close the local file
}

void get::mainfunc()
{
    get_wd();
    // saving path to current user local directory to file
    cout << "Enter filenames:" << endl;
    vector<string> list;
    string filename;
    cin.ignore(INT_MAX,'\n');
    while(true) {
        cin.clear();
        getline(cin, filename);
        if(filename!="")
            list.push_back(filename);
        else
            break;
    }
    for(unsigned int i = 0; i < list.size(); i++)
        download(list[i]);
}
