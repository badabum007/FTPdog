#ifndef GLOBAL_INIT_HPP
#define GLOBAL_INIT_HPP

#include <curl/curl.h>

//инициализация и очистка глобального окружения libcurl
class global_init
{
public:
    global_init();
    ~global_init();
    
};

#endif // GLOBAL_INIT_HPP
