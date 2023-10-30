#include "Menu.h"

using namespace std;
Menu::Menu() {}

void Menu::drawTop(){
    cout << "________________________________________" << endl;
    cout << "|" << "================ Menu ================" << "|" << endl;
    cout << "|" << "______________________________________" << "|" << endl;
}
void Menu::drawBottom(){
    cout << "|______________________________________|" << endl;
    cout << "|======================================|" << endl;
    cout << "|______________________________________|" << endl;
}

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
        cout << "| " << setw( largura- 18) << "3. Queue" << setw(16) << "|" << endl;
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
                                cout << "The student's name is : " << s.findName(d.getListStudents_Classes_(), stc) << endl;
                                s.getStudentSchedule(d.getListStudents_Classes_(), d.getListClasses_()).printSchedule();
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
                                cout << "The student's name is : " << s.findName(d.getListStudents_Classes_(), stc) << endl;
                                s.printStudentTableSchedule(stc,d.getListStudents_Classes_(),d.getListClasses_());
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
                                d.printClassSchedule(ccode, d.getListClasses_Per_Uc_(), d.getListClasses_());
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
                                d.printStudentsInUC(ucc,d.getUcToStudentsMap());
                                break;
                            }
                            case '4': {
                                cout << "Enter N: ";
                                int n;
                                cin >> n;
                                d.printStudentsWithNUcs(n,d.getNUcsToStudentsMap());
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
                                cout << d.numberOfStudentsInUC(ucc,d.getUcToStudentsMap());
                                break;
                            }
                            case '8': {
                                cout << "Enter N: ";
                                int n;
                                cin >> n;
                                cout << d.numberStudentsWithNUcs(n,d.getNUcsToStudentsMap());
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
                                d.printTop5UCs(d.getUcToStudentsMap());
                                break;
                            }
                            case 'A': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                cout << "Enter Class Code: ";
                                string cc;
                                cin >> cc;
                                d.printStudentsInUcClass(ucc,cc,d.getUcClasstoStudentsMap());
                                break;
                            }
                            case 'B': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                cout << "Enter Class Code: ";
                                string cc;
                                cin >> cc;
                                cout << d.numberOfStudentsInUcClass(ucc,cc,d.getUcClasstoStudentsMap());
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
                                d.printUcsByClass(cc,d.getClassToUcMap());
                                break;
                            }
                            case '2': {
                                cout << "Enter UC Code: ";
                                string ucc;
                                cin >> ucc;
                                d.printClassByUcs(ucc,d.getUcToClassMap());
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
                cout << "| " << setw( largura- 16) << "2. Add Class" << setw(14) << "|" << endl;
                cout << "| " << setw( largura- 16) << "3. Remove UC" << setw(14) << "|" << endl;
                cout << "| " << setw( largura- 13) << "4. Remove Class" << setw(11) << "|" << endl;
                cout << "| " << setw( largura- 16) << "5. Switch Uc" << setw(14) << "|" << endl;
                cout << "| " << setw( largura- 13) << "6. Switch Class" << setw(11) << "|" << endl;
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
                        list<pair<Student, UC>> l = d.getListStudents_Classes_();
                        r.addUC(s,ucc, cc,l,d.getListClasses_());
                        d.setListStudents_Classes_(l);
                        log.requestAndLog("AddUc", s,UC(ucc,cc));
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
                        cout << "Enter Class Code: ";
                        string cc;
                        cin >> cc;
                        list<pair<Student, UC>> l = d.getListStudents_Classes_();
                        r.addClass(s,cc,l,d.getListClasses_());
                        d.setListStudents_Classes_(l);
                        log.requestAndLog("AddClass", s,cc);
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
                        cout << "Enter UC Code: ";
                        string ucc;
                        cin >> ucc;
                        list<pair<Student, UC>> l = d.getListStudents_Classes_();
                        r.removeUC(s,ucc,l);
                        d.setListStudents_Classes_(l);
                        log.requestAndLog("RemoveUc", s,ucc);
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
                        cout << "Enter Class Code: ";
                        string cc;
                        cin >> cc;
                        list<pair<Student, UC>> l = d.getListStudents_Classes_();
                        r.removeClass(s,cc,l);
                        d.setListStudents_Classes_(l);
                        log.requestAndLog("RemoveClass", s,cc);
                        break;

                    }
                    case '5': {
                        /*
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
                        list<pair<Student, UC>> l = d.getListStudents_Classes_();
                        r.addUC(s,ucc, cc,l,d.getListClasses_());
                        d.setListStudents_Classes_(l);
                        log.requestAndLog("AddUc", s,UC(ucc,cc));
                        break;
                         */
                    }
                    case '6': {
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
