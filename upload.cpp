#include "upload.hpp"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <vector>

upload::upload(string turl, string tname, string tpass, CURL* t_curl)
{
    curl = t_curl;
    url = turl;
    login = tname;
    pass = tpass;
}

upload::~upload()
{
}

static size_t readcallback(void* ptr, size_t size, size_t nmemb, void* stream)
{
    size_t retcode = fread(ptr, size, nmemb, (FILE*)stream);
    return retcode;
}

void upload::upload_func(string local_file)
{
    struct stat file_info;

    /* get the file size of the local file */
    if(stat(local_file.c_str(), &file_info)) {
        printf("Couldnt open '%s': %s\n", local_file.c_str(), strerror(errno));
        return;
    }
    fsize = (curl_off_t)file_info.st_size;

    printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);

    /* get a FILE * of the same file */
    hd_src = fopen(local_file.c_str(), "rb");

    if(curl) {

        /* we want to use our own read function */
        // curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

        std::string name_save = local_file;
        url += name_save;

        /* enable uploading */
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        /* specify target */
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        if(login != "\0" && login != "\n") {
            curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, pass.c_str());
        }

        /* now specify which file to upload */
        curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readcallback);

        /* Set the size of the file to upload (optional).  If you give a *_LARGE
           option you MUST make sure that the type of the passed-in argument is a
           curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
           make sure that to pass in a type 'long' argument. */
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);

        /* Now run off and do what you've been told! */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    fclose(hd_src); /* close the local file */
}

void upload::mainfunc()
{
    std::cout << "Choose files to upload" << std::endl;
    std::vector<string> list;
    std::cin.ignore(INT_MAX, '\n');
    std::string local_file;
    while(true) {
        std::cin.clear();
        std::getline(std::cin, local_file);
        if(local_file != "")
            list.push_back(local_file);
        else
            break;
    }
    for(unsigned int i = 0; i < list.size(); i++)
        upload_func(list[i]);
}