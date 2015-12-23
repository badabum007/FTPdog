#include "global_init.hpp"

global_init::global_init()
{
    curl_global_init(CURL_GLOBAL_NOTHING);
}

global_init::~global_init()
{
    curl_global_cleanup();
}

