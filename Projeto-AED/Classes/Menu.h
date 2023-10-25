#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H
#include <iostream>
#include <string>
#include <iomanip>

class Menu {
public:
    Menu();
    void showMenu();
    void drawTop(int largura);
    void drawBottom(int largura);
    int numberOfDigits(int stc);
};


#endif //PROJECT_MENU_H
