#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Data.h"
using namespace std;

Data::Data() {};


void Data::readClasses(){
    string f = "../schedule/classes.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
    }
    string line, ClassCode, UcCode, Weekday, Type, StartHour, Duration;
    list<pair<UC,Lesson>> aux;
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ClassCode, ',');
        getline(iss, UcCode, ',');
        getline(iss, Weekday, ',');
        getline(iss, StartHour, ',');
        getline(iss, Duration, ',');
        getline(iss, Type, ',');

        int w = stoi(Weekday);
        float sh = stof(StartHour);
        float d = stof(Duration);


        pair<UC,Lesson> p (UC(UcCode,ClassCode), Lesson(w, sh, d, Type));
        aux.push_back(p);
    }
    listClasses_ = aux;
    file.close();
}
void Data::readClasses_Per_Uc(){
    string f = "../schedule/classes_per_uc.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
    }
    string UcCode,ClassCode,line;
    list<UC> aux;
    list<Lesson> Lesson={};
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ClassCode, ',');
        getline(iss, UcCode, ',');
        aux.push_back(UC(UcCode, ClassCode, Lesson));
    }
    listClasses_Per_Uc_ = aux;
    file.close();
}

void Data::readStudents_Classes(){
    string f = "../schedule/students_classes.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
    }
    string StName,StCode, UcCode, ClassCode, line;

    list<pair<Student, UC>> aux;
    getline(file, line);
    while(getline(file, line)) {
        istringstream inn(line);
        getline(inn, StCode, ',');
        getline(inn, StName, ',');
        getline(inn, UcCode, ',');
        getline(inn, ClassCode, ',');

        int stc = stoi(StCode);

        pair<Student,UC> p (Student(stc,StName), UC(UcCode, ClassCode));
        aux.push_back(p);

    }
    listStudents_Classes_ = aux;
    file.close();
}

std::list<std::pair<UC, Lesson>> Data::getListClasses_() {
    return listClasses_;
}

std::list<UC> Data::getListClasses_Per_Uc_() {
    return listClasses_Per_Uc_;
}

std::list<std::pair<Student, UC>> Data::getListStudents_Classes_() {
    return listStudents_Classes_;
}
