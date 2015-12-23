#include <iostream>
#include <cstdlib>
#include "menu.hpp"

using namespace std;

menu::menu()
{
}

menu::~menu()
{
}

void menu::show(interface& server, client& user)
{
    while(true) {
        cout << "Menu:" << endl;
        cout << "1.  Choose url" << endl;
        cout << "2.  Print server working directory" << endl;
        cout << "3.  Change server working directory" << endl;
        cout << "4.  List of items on server working directory" << endl;
        cout << "5.  Download file" << endl;
        cout << "6.  Client side filesystem options" << endl;
        cout << "7.  Rename items on server" << endl;
        cout << "8.  Remove items from server" << endl;
        cout << "9.  Create directory on server" << endl;
        cout << "10. Upload file" << endl;
        cout << "0.  Exit" << endl;
        cin >> choize;
        while(!cin.good()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> choize;
        }
        switch(choize) {
        case 1:
            server.set_ftpurl();
            break;
        case 2:
            server.pwd();
            break;
        case 3:
            server.cd();
            break;
        case 4:
            server.ls();
            break;
        case 5:
            server.improved_get();
            break;
        case 6:
            user.actions();
            break;
        case 7:
            server.rn();
            break;
        case 8:
            server.rm();
            break;
        case 9:
            server.mkd();
            break;
        case 10:
            server.upload_func();
            break;
        case 0:
            exit(0);
            break;
        default:
            break;
        }
    }
}