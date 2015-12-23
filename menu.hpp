#ifndef MENU_HPP
#define MENU_HPP
#include "interface.hpp"
#include "client.hpp"

class menu
{
    int choize;
public:
    menu();
    ~menu();
    void show(interface&, client&);
};

#endif // MENU_HPP
