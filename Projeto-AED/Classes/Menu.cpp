#include "Menu.h"

using namespace std;
void showMenu() {

    const int largura = 40;
    const int altura = 8;


    for (int i = 0; i < largura; i++) {
        cout << "_";
    }
    cout << endl;

    // Exibe o conteúdo do menu com margens
    cout << "| " << setw(largura - 4) << "Menu de Consulta de Horário" << " |" << endl;
    cout << "| " << setw(largura - 4) << "1. Consultar Horário" << " |" << endl;
    cout << "| " << setw(largura - 4) << "2. Sair" << " |" << endl;

    // Exibe a parte inferior do quadro
    for (int i = 0; i < largura; i++) {
        std::cout << "_";
    }
    std::cout << std::endl;

    std::cout << "Escolha uma opção: ";
}