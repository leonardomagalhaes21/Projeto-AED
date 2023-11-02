#include "Menu.h"

using namespace std;

/**
 * @brief Default constructor for the Menu class.
 *
 * This constructor initializes an instance of the Menu class.
 *
 * Time Complexity: O(1)
 */
Menu::Menu() {}

/**
 * @brief Draws the top section of the menu interface.
 *
 * This function is responsible for rendering the top section of the menu interface.
 *
 * Time Complexity: O(1)
 */
void Menu::drawTop(){
    cout << "________________________________________" << endl;
    cout << "|" << "================ Menu ================" << "|" << endl;
    cout << "|" << "______________________________________" << "|" << endl;
}

/**
 * @brief Draws the bottom section of the menu interface.
 *
 * This function is responsible for rendering the bottom section of the menu interface.
 *
 * Time Complexity: O(1)
 */
void Menu::drawBottom(){
    cout << "|______________________________________|" << endl;
    cout << "|======================================|" << endl;
    cout << "|______________________________________|" << endl;
}

/**
 * @brief Displays the main menu and handles user interactions.
 *
 * This function presents the main menu to the user and processes user input to navigate
 * through different options.
 *
 * @b Complexity: Depends on the complexity of the code executed within the switch cases.
 */
void Menu::showMenu() {

    Data d = Data();
    Request r = Request();
    RequestLog log;
    const int largura =40;
    short t2;
    int stc;
    char key;
    string newCicle;
    bool flag = true;
    string nm, ccode, ucode;
    while (flag) {
        drawTop();
        cout << "| " << setw( largura- 19) << "1. View" << setw(17) << "|" << endl;
        cout << "| " << setw( largura- 19) << "2. Edit" << setw(17) << "|" << endl;
        cout << "| " << setw( largura- 16) << "3. Save/Undo" << setw(14) << "|" << endl;
        cout << "| " << setw( largura- 19) << "Q. EXIT" << setw(17) << " |" << endl;
        drawBottom();
        cout << "Choose an option: ";
        cin >> key;
        switch (key) {
            case  '1' :
                drawTop();
                cout << "| " << setw( largura- 14) << "1. View Schedule" << setw(12) << "|" << endl;
                cout << "| " << setw( largura- 14) << "2. View Students" << setw(12) << "|" << endl;
                cout << "| " << setw( largura- 14) << "3. Classes <-> UC" << setw(12) << "|" << endl;
                cout << "| " << setw( largura- 19) << "Q. EXIT" << setw(17) << " |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        drawTop();
                        cout << "| " << setw( largura- 18) << "1. Print Schedule from Student" << setw(8) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "2. Print Schedule from Student(Table)" << "|" << endl;
                        cout << "| " << setw( largura- 14) << "3. Print Schedule from Class(Table)" << setw(3) << "|" << endl;
                        cout << "| " << setw( largura- 12) << "4. Print Schedule from Class" << setw(10) << "|" << endl;
                        cout << "| " << setw( largura- 18) << "5. Print Schedule from UC" << setw(13) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "6. Print Schedule from UC(with Class)" << setw(1) << "|" << endl;
                        cout << "| " << setw( largura- 19) << "Q. EXIT" << setw(17) << " |" << endl;
                        drawBottom();
                        cout << "Choose an option: ";
                        cin >> key;
                    }
                        switch (key) {
                            case '1': {

                                cout << "Enter Student Code: ";
                                cin >> stc;
                                if (cin.fail()){
                                    cin.clear();
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                string k = to_string(stc);
                                if (k.size() != 9){
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                Student s = Student(stc);
                                cout << "The student's name is : " << s.findName(d.getListStudentsClasses_(), stc) << endl;
                                s.getStudentSchedule(d.getListStudentsClasses_(), d.getListClasses_()).printSchedule();
                                break;
                            }
                            case '2':{
                                cout << "Enter Student Code: ";
                                cin >> stc;
                                if (cin.fail()){
                                    cin.clear();
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                string k = to_string(stc);
                                if (k.size() != 9){
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                Student s = Student(stc);
                                cout << "The student's name is : " << s.findName(d.getListStudentsClasses_(), stc) << endl;
                                s.printStudentTableSchedule(stc,d.getListStudentsClasses_(),d.getListClasses_());
                                break;
                            }
                            case '3': {
                                cout << "Enter Class Code: ";
                                cin >> ccode;
                                d.printClassTableSchedule(ccode);
                                break;
                            }
                            case '4': {
                                cout << "Enter Class Code: ";
                                cin >> ccode;
                                d.printClassSchedule(ccode, d.getListClassesPerUC_(), d.getListClasses_());
                                break;
                            }
                            case '5': {
                                cout << "Enter UC Code: ";
                                cin >> ucode;
                                UC u = UC(ucode);
                                u.getSchedule(d.getListClasses_()).printSchedule();
                                break;
                            }
                            case '6' : {
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

                        drawTop();
                        cout << "| " << setw( largura- 18) << "1. Print Students from Year" << setw(11) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "2. Print Students in Class" << setw(12) << "|" << endl;
                        cout << "| " << setw( largura- 18) << "3. Print Students in UC" << setw(15) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "4. Print Students with N UCs" << setw(10) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "5. Number of Students from Year" << setw(7) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "6. Number of Students in Class" << setw(8) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "7. Number of Students in UC" << setw(11) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "8. Number of Students with N UCs" << setw(6) << "|" << endl;
                        cout << "| " << setw( largura- 24) << "9. Print Students" << setw(21) << "|" << endl;
                        cout << "| " << setw( largura- 24) << "0. Print Top 5 UCs by student count" << setw(3) << "|" << endl;
                        cout << "| " << setw( largura- 18) << "A. Print Students in UC and Class" << setw(5) << "|" << endl;
                        cout << "| " << setw( largura- 14) << "B. Number of Students in UC and Class" << setw(1) << "|" << endl;
                        cout << "| " << setw( largura- 19) << "Q. EXIT" << setw(17) << " |" << endl;
                        drawBottom();
                        cout << "Choose an option: ";
                        cin >> key;
                        switch(key){
                            case '1': {
                                cout << "Enter year: ";
                                int y;
                                cin >> y;
                                if (cin.fail()){
                                    cin.clear();
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                string k = to_string(y);
                                if (k.size() != 4){
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                d.printStudentsByYear(y,d.getYearToStudentsMap());
                                break;
                            }
                            case '2': {
                                cout << "Enter Class Code: ";
                                string cc;
                                cin >> cc;
                                d.printStudentsByClass(cc,d.getClassToStudentsMap());
                                break;
                            }
                            case '3': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                d.printStudentsInUC(ucc,d.getUCToStudentsMap());
                                break;
                            }
                            case '4': {
                                cout << "Enter N: ";
                                int n;
                                cin >> n;
                                d.printStudentsWithNUCs(n,d.getNUCsToStudentsMap());
                                break;
                            }
                            case '5': {
                                cout << "Enter year: ";
                                int y;
                                cin >> y;
                                if (cin.fail()){
                                    cin.clear();
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                string k = to_string(y);
                                if (k.size() != 4){
                                    cout << "Error: Invalid Input!";
                                    break;
                                }
                                cout << d.numberOfStudentsByYear(y,d.getYearToStudentsMap());
                                break;
                            }
                            case '6': {
                                cout << "Enter Class Code: ";
                                string cc;
                                cin >> cc;
                                cout << d.numberOfStudentsInClass(cc,d.getClassToStudentsMap());
                                break;
                            }
                            case '7': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                cout << d.numberOfStudentsInUC(ucc,d.getUCToStudentsMap());
                                break;
                            }
                            case '8': {
                                cout << "Enter N: ";
                                int n;
                                cin >> n;
                                cout << d.numberStudentsWithNUCs(n,d.getNUCsToStudentsMap());
                                break;
                            }
                            case '9' :{
                                drawTop();
                                cout << "| " << setw( largura- 9) << "1. Ascending Order [Up Code]" << setw(7) << "|" << endl;
                                cout << "| " << setw( largura- 8) << "2. Descending Order [Up Code]" << setw(6) << "|" << endl;
                                cout << "| " << setw( largura- 9) << "3. Alphabetic Order - [A - Z]" << setw(7) << "|" << endl;
                                cout << "| " << setw( largura- 9) << "4. Alphabetic Order - [Z - A]" << setw(7) << "|" << endl;
                                cout << "| " << setw( largura- 19) << "Q. EXIT" << setw(17) << " |" << endl;
                                drawBottom();
                                cout << "Choose an option: ";
                                cin>>key;
                                switch (key) {
                                    case '1':{
                                        d.printStudentsAscendingCode();
                                        break;
                                    }
                                    case '2':{
                                        d.printStudentsDescendingCode();
                                        break;
                                    }
                                    case '3':{
                                        d.printStudentsAscendingName();
                                        break;
                                    }
                                    case '4':{
                                        d.printStudentsDescendingName();
                                        break;
                                    }
                                    case 'Q' : {
                                        break;
                                    }
                                    default: {
                                        cout << endl << "Invalid option!" << endl;
                                    }

                                }

                            }
                            case '0': {
                                d.printTop5UCs(d.getUCToStudentsMap());
                                break;
                            }
                            case 'A': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                cout << "Enter Class Code: ";
                                string cc;
                                cin >> cc;
                                d.printStudentsInUCClass(ucc,cc,d.getUCClasstoStudentsMap());
                                break;
                            }
                            case 'B': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                cout << "Enter Class Code: ";
                                string cc;
                                cin >> cc;
                                cout << d.numberOfStudentsInUCClass(ucc,cc,d.getUCClasstoStudentsMap());
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
                    }

                    case '3': {
                        drawTop();
                        cout << "| " << setw( largura- 11) << "1. Print UCs from Class" << setw(9) << "|" << endl;
                        cout << "| " << setw( largura- 10) << "2. Print Classes from UC" << setw(8) << "|" << endl;
                        cout << "| " << setw( largura- 19) << "Q. EXIT" << setw(17) << " |" << endl;
                        drawBottom();
                        cout << "Choose an option: ";
                        cin >> key;
                        switch(key){
                            case '1': {
                                cout << "Enter Class Code: ";
                                string cc;
                                cin >> cc;
                                d.printUCsByClass(cc,d.getClassToUcMap());
                                break;
                            }
                            case '2': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                d.printClassByUCs(ucc,d.getUCToClassMap());
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
                drawTop();
                cout << "| " << setw( largura- 19) << "1. Add UC" << setw(17) << "|" << endl;
                cout << "| " << setw( largura- 16) << "2. Remove UC" << setw(14) << "|" << endl;
                cout << "| " << setw( largura- 13) << "3. Remove Class" << setw(11) << "|" << endl;
                cout << "| " << setw( largura- 16) << "4. Switch Uc" << setw(14) << "|" << endl;
                cout << "| " << setw( largura- 13) << "5. Switch Class" << setw(11) << "|" << endl;
                cout << "| " << setw( largura- 18) << "Q. EXIT" << setw(16) << " |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        cout << "Enter Student Code: ";
                        cin >> stc;
                        if (cin.fail()){
                            cin.clear();
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        string k = to_string(stc);
                        if (k.size() != 9){
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        Student s = Student(stc);
                        cout << "Enter UC Code: ";
                        string ucc;
                        cin >> ucc;
                        cout << "Enter Class Code: ";
                        string cc;
                        cin >> cc;
                        list<pair<Student, UC>> l = d.getListStudentsClasses_();
                        if(r.addUC(s,ucc, cc,l,d.getListClasses_(),d.getUCClasstoStudentsMap())) {
                            d.setListStudentsClasses_(l);
                            log.requestAndLog("AddUc", s, UC(ucc, cc));
                            cout << "Operation successful!";
                        }
                        else{
                            cout << "Operation failed!";
                        }
                        break;
                    }
                    case '2': {
                        cout << "Enter Student Code: ";
                        cin >> stc;
                        if (cin.fail()){
                            cin.clear();
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        string k = to_string(stc);
                        if (k.size() != 9){
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        Student s = Student(stc);
                        cout << "Enter UC Code: ";
                        string ucc;
                        cin >> ucc;
                        list<pair<Student, UC>> l = d.getListStudentsClasses_();
                        if(r.removeUC(s,ucc,l)) {
                            d.setListStudentsClasses_(l);
                            log.requestAndLog("RemoveUc", s, ucc);
                        }
                        else{
                            cout << "Operation failed!";
                        }
                        break;
                    }
                    case '3': {
                        cout << "Enter Student Code: ";
                        cin >> stc;
                        if (cin.fail()){
                            cin.clear();
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        string k = to_string(stc);
                        if (k.size() != 9){
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        Student s = Student(stc);
                        cout << "Enter Class Code: ";
                        string cc;
                        cin >> cc;
                        list<pair<Student, UC>> l = d.getListStudentsClasses_();
                        if(r.removeClass(s,cc,l)){
                            d.setListStudentsClasses_(l);
                            log.requestAndLog("RemoveClass", s, cc);
                            cout << "Operation successful!";
                        }
                        else{
                            cout << "Operation failed!";
                        }
                        break;

                    }
                    case '4': {

                        cout << "Enter Student Code: ";
                        cin >> stc;
                        if (cin.fail()){
                            cin.clear();
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        string k = to_string(stc);
                        if (k.size() != 9){
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        Student s = Student(stc);
                        cout << "Enter Current UC Code: ";
                        string uccc;
                        cin >> uccc;
                        cout << "Enter Current Class Code: ";
                        string ccc;
                        cin >> ccc;
                        cout << "Enter New UC Code: ";
                        string nucc;
                        cin >> nucc;
                        cout << "Enter New Class Code: ";
                        string ncc;
                        cin >> ncc;
                        UC a = UC(uccc,ccc);
                        UC b = UC(nucc,ncc);
                        list<pair<Student, UC>> l = d.getListStudentsClasses_();
                        if(r.switchUC(s,a,b,l,d.getListClasses_(),d.getUCClasstoStudentsMap())) {
                            d.setListStudentsClasses_(l);
                            log.requestAndLog("SwitchUc", s, b, a);
                            cout << "Operation successful!";
                        }
                        else{
                            cout << "Operation failed!";
                        }
                        break;

                    }
                    case '5': {
                        cout << "Enter Student Code: ";
                        cin >> stc;
                        if (cin.fail()){
                            cin.clear();
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        string k = to_string(stc);
                        if (k.size() != 9){
                            cout << "Error: Invalid Input!";
                            break;
                        }
                        Student s = Student(stc);
                        cout << "Enter UC Code: ";
                        string ucc;
                        cin >> ucc;
                        cout << "Enter Current Class Code: ";
                        string ccc;
                        cin >> ccc;
                        cout << "Enter New Class Code: ";
                        string ncc;
                        cin >> ncc;
                        UC a = UC(ucc,ccc);
                        UC b = UC(ucc,ncc);
                        list<pair<Student, UC>> l = d.getListStudentsClasses_();
                        if(r.switchClass(s,a,b,l,d.getListClasses_(),d.getUCClasstoStudentsMap())) {
                            d.setListStudentsClasses_(l);
                            log.requestAndLog("SwitchClass", s, b,a);
                            cout << "Operation successful!";
                        }
                        else{
                            cout << "Operation failed!";
                        }
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
                drawTop();
                cout << "| " << setw( largura- 18) << "1. Save" << setw(16) << "|" << endl;
                cout << "| " << setw( largura- 18) << "2. Undo" << setw(16) << "|" << endl;
                cout << "| " << setw( largura- 18) << "Q. EXIT" << setw(16) << " |" << endl;
                drawBottom();
                cout << "Choose an option: ";
                cin >> key;
                switch (key) {
                    case '1': {
                        log.save();
                        break;
                    }
                    case '2':{
                        log.undo();
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
