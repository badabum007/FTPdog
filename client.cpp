#include <cstdlib>
#include <climits>
#include <iostream>
#include <unistd.h>
#include "client.hpp"

using namespace std;

client::client()
{
}

client::~client()
{
}

void client::terminal_session(string command)
{
    cin.clear();
    //очистка потока ввода
    cin.ignore(INT_MAX, '\n');
    cout << "Enter command line arguments:" << endl;
    getline(cin, arguments);
    if(command == "cd")
        chdir(arguments.c_str());
    else {
        request = command + " " + arguments;
        system(request.c_str());
    }
}

void client::actions()
{
    while(true) {
        cout << "List of avaible commands:" << endl;
        cout << "1. List of files" << endl;
        cout << "2. Change directory" << endl;
        cout << "3. Print working directory" << endl;
        cout << "4. Remove item" << endl;
        cout << "5. Create directory" << endl;
        cout << "6. Copy item" << endl;
        cout << "7. Move/rename item" << endl;
        cout << "0. Exit" << endl;
        cin >> choize;
        while(!choize && cin.fail()) {
            cout << "Try again" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> choize;
        }
        switch(choize) {
        case 1:
            terminal_session("ls");
            break;
        case 2:
            terminal_session("cd");
            break;
        case 3:
            terminal_session("pwd");
            break;
        case 4:
            terminal_session("rm");
            break;
        case 5:
            terminal_session("mkdir");
            break;
        case 6:
            terminal_session("cp");
            break;
        case 7:
            terminal_session("mv");
            break;
        case 0:
            return;
        }
        cout << "Press ENTER to continue..." << endl;
        cin.clear();
        //очистка потока ввода
        cin.ignore(INT_MAX, '\n');
    }
}