#include "Menu.h"

using namespace std;
Menu::Menu() {}
void Menu::showMenu() {

    const int largura = 40;
    const int altura = 8;


    for (int i = 0; i < largura; i++) {
        cout << "_";
    }
    cout << endl;


    cout << "| " << setw(largura -8) << "Menu de Consulta de Horário" <<setw(7)<< "|" << endl;
    cout << "| " << setw(largura - 12) << "1. Consultar Horário" << setw(11)<< "|" << endl;
    cout << "| " << setw(largura - 19) << "2. Sair" << setw(17) << " |" << endl;
    //if (ucClass_.getUcCode().length() + lesson.getType().length() + 2 < 15)
    //    scheduleVector[lessonStartPosition] += string(15 - ucClass_.getUcCode().length() - lesson.getType().length(), ' ');

    for (int i = 0; i < largura; i++) {
        std::cout << "_";
    }
    cout << endl;

    cout << "Escolha uma opção: ";
}