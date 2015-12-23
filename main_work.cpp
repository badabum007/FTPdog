#include <stdio.h>
#include <iostream>
#include <curl/curl.h>
#include "interface.hpp"
#include "global_init.hpp"
#include "menu.hpp"
#include "client.hpp"

using namespace std;

int main()
{
    global_init gl_init;
    interface face("localhost", "magicpony", "76187618");
    //interface face;
    client user;
    menu menu1;
    menu1.show(face, user);
    return 0;
}
