#include "Menu.h"

using namespace std;
Menu::Menu() {}


void Menu::drawTop(int largura){
    cout << "----------------------------------------" << endl;
    cout << "|" << "################ Menu ################" << "|" << endl;
    cout << "|";
    cout << "--------------------------------------";
    cout << "|" << endl;
}
void Menu::drawBottom(int largura){
    cout << "|--------------------------------------|" << endl;
    cout << "|######################################|" << endl;
    cout << "|--------------------------------------|" << endl;
}

void Menu::showMenu() {

    Data d = Data();

    short t2;
    const int largura = 40;
    int stc;
    char key;
    string newCicle;
    bool flag = true;
    string nm, ccode, ucode;
    while (flag) {
        drawTop(largura);
        cout << "| " << setw(largura - 14) << "1. View" << setw(12) << "|" << endl;
        cout << "| " << setw(largura - 14) << "2. Edit" << setw(12) << "|" << endl;
        cout << "| " << setw(largura - 14) << "3. Queue" << setw(12) << "|" << endl;
        cout << "| " << setw(largura - 19) << "Q. EXIT" << setw(17) << " |" << endl;
        drawBottom(largura);
        cout << "Choose an option: ";
        cin >> key;
        switch (key) {
            case  '1' :
                drawTop(largura);
                cout << "| " << setw(largura - 14) << "1. View Schedule" << setw(12) << "|" << endl;
                cout << "| " << setw(largura - 14) << "2. View Students" << setw(12) << "|" << endl;
                cout << "| " << setw(largura - 14) << "3. Classes <-> UC" << setw(12) << "|" << endl;
                cout << "| " << setw(largura - 15) << "4. Make Request" << setw(13) << "|" << endl;
                cout << "| " << setw(largura - 19) << "Q. EXIT" << setw(17) << " |" << endl;
                drawBottom(largura);
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        drawTop(largura);
                        cout << "| " << setw(largura - 18) << "1. Print Schedule from Student" << setw(6) << "|"
                             << endl;
                        cout << "| " << setw(largura - 14) << "2. Print Schedule from Class(Table)" << setw(12) << "|"
                             << endl;
                        cout << "| " << setw(largura - 14) << "3. Print Schedule from Class" << setw(12) << "|" << endl;
                        cout << "| " << setw(largura - 14) << "4. Print Schedule from UC" << setw(12) << "|" << endl;
                        cout << "| " << setw(largura - 14) << "5. Print Schedule from UC(with Class)" << setw(12)
                             << "|" << endl;
                        cout << "| " << setw(largura - 19) << "Q. EXIT" << setw(17) << " |" << endl;
                        drawBottom(largura);
                        cout << "Choose an option: ";
                        cin >> key;
                    }
                        switch (key) {
                            case '1': {

                                cout << "Enter Student Code: ";
                                cin >> stc;
                                string k = to_string(stc);
                                if (k.size() != 9){
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                Student s = Student(stc);
                                cout << "The student's name is : " << s.findName(d.getListStudents_Classes_(), stc) << endl;
                                s.getStudentSchedule(d.getListStudents_Classes_(), d.getListClasses_()).printSchedule();
                                break;
                            }
                            case '2': {
                                cout << "Enter Class Code: ";
                                cin >> ccode;
                                d.printClassTableSchedule(ccode);
                                break;
                            }
                            case '3': {
                                cout << "Enter Class Code: ";
                                cin >> ccode;
                                d.printClassSchedule(ccode, d.getListClasses_Per_Uc_(), d.getListClasses_());
                                break;
                            }
                            case '4': {
                                cout << "Enter UC Code: ";
                                cin >> ucode;
                                UC u = UC(ucode);
                                u.getSchedule(d.getListClasses_()).printSchedule();
                                break;
                            }
                            case '5' : {
                                cout << "Enter UC Code: ";
                                cin >> ucode;
                                cout << "Enter Class Code: ";
                                cin >> ccode;
                                UC uc = UC(ucode, ccode);
                                uc.addClassLessons(d.getListClasses_());
                                uc.printLessons();
                                break;
                            }
                            case 'Q' : {
                                break;
                            }
                            default: {
                                cout << endl << "Invalid option!" << endl;
                            }
                        };
                        break;
                    case '2' : {
                        break;
                    }

                    case 'Q': {
                        break;
                    }
                    default: {
                        cout << endl << "Invalid option!" << endl;
                    }
                };
                break;
            case '2': {
                //menu de edit
                cin >> key;
                switch (key) {
                    case '1': {
                        break;
                    }
                    case 'Q': {
                        break;
                    }
                    default: {
                        cout << endl << "Invalid option!" << endl;
                    }
                };
                break;
            }
            case '3': {
                //menu de queue
                cin >> key;
                switch (key) {
                    case '1': {
                        break;
                    }
                    case 'Q': {
                        break;
                    }
                    default: {
                        cout << endl << "Invalid option!" << endl;
                    }
                };
                case 'Q': {
                    break;
                }
                default: {
                    cout << endl << "Invalid option!" << endl;
                }
                break;
            }
        };
        cout << endl;
        cout << "Would you like to do something else? (Y/N) \n";
        cin >> newCicle;
        if (newCicle == "N") flag = false;
        while (newCicle != "Y") {
            if (newCicle == "N") {
                flag = false;
                break;
            }
            cout << "Please type \"Y\" or \"N\"." << endl;
            cin >> newCicle;
        }
    }
}
