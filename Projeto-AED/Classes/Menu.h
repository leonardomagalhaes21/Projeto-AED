#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H
#include <iostream>
#include <string>
#include <iomanip>
#include "Student.h"
#include "UC.h"
#include "Schedule.h"
#include "Request.h"

class Menu {

public:
    Menu();
    void showMenu();
    static void drawTop();
    static void drawBottom();
};


#endif //PROJECT_MENU_H








