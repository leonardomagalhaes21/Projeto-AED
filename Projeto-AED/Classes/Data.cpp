#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <iomanip>
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

    map<string, int> WeekdayToNum = {
            {"Monday", 1},
            {"Tuesday", 2},
            {"Wednesday", 3},
            {"Thursday", 4},
            {"Friday", 5}
    };

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ClassCode, ',');
        getline(iss, UcCode, ',');
        getline(iss, Weekday, ',');
        getline(iss, StartHour, ',');
        getline(iss, Duration, ',');
        iss >> Type;


        int w = WeekdayToNum[Weekday];
        float sh = stof(StartHour);
        float d = stof(Duration);


        pair<UC,Lesson> p (UC(UcCode,ClassCode), Lesson(w, d, sh, Type));
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
        iss >> UcCode;
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
        inn >> ClassCode;

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
void Data::printStudentsByYear(int x,list<pair<Student, UC>> val){
    set<Student> res;
    for(pair<Student,UC> s: val){
        if (x == (s.first.get_StudentCode()/100000)){
            res.insert(s.first);
        }
    }
    for(auto i = res.begin();i!=res.end();i++){
        cout << i->get_StudentName() << '\n';
    }
}
void Data::numberOfStudentsByYear(int x,list<pair<Student, UC>> val){
    set<Student> res;
    for(pair<Student,UC> s: val){
        if (x == (s.first.get_StudentCode()/100000)){
            res.insert(s.first);
        }
    }
    cout << res.size() << '\n';
}
void Data::printStudentsByClass(string x,list<pair<Student, UC>> val){
    set<Student> res;
    for(pair<Student,UC> s: val){
        if (x == (s.second.getClassCode())){
            res.insert(s.first);
        }
    }
    for(auto i = res.begin();i!=res.end();i++){
        cout << i->get_StudentName() << '\n';
    }
}
void Data::numberOfStudentsInClass(string x,list<pair<Student, UC>> val) {
    set<Student> res;
    for (pair<Student, UC> s: val) {
        if (x == (s.second.getClassCode())) {
            res.insert(s.first);
        }
    }
    cout << res.size() << '\n';
}
void Data::studentsWithNUcs(int n,list<pair<Student, UC>> val){
    map<Student,int> m;
    for(pair<Student,UC> s: val){

        if (m.count(s.first) > 0){
            m[s.first]++;
        }
        else{
            m[s.first]=1;
        }
    }
    for(const auto par: m){
        if(par.second >=n) {
            cout << par.first.get_StudentName() << '\n';
        }
    }
}
void Data::numberStudentsWithNUcs(int n,list<pair<Student, UC>> val){
    map<Student,int> m;
    for(pair<Student,UC> s: val){

        if (m.count(s.first) > 0){
            m[s.first]++;
        }
        else{
            m[s.first]=1;
        }
    }
    int sum =0;
    for(const auto par: m){
        if(par.second >=n) {
            sum++;
        }
    }
    cout << sum;
}
void Data::printClassTableSchedule(string classCode) const{

    cout << classCode + " schedule\n";
    string schedule_ = " ________________________________________________________________________________________\n"
                       "|     Hour    |    Monday    |   Tuesday    |   Wednesday  |   Thursday   |    Friday    |\n"
                       "|________________________________________________________________________________________|\n";


    vector<string> scheduleVector;
    for (int i = 0; i < 24 * 5 * 2; i += 2) {
        scheduleVector.push_back("              |");
        scheduleVector.push_back("______________|");
    }
    Data d=Data ();
    d.readClasses_Per_Uc();
    list<Lesson> lesson= {};
    for (const UC& ucClass_ : listClasses_Per_Uc_) {
        if (ucClass_.getClassCode() == classCode) {
            UC c= UC (ucClass_.getUcCode(),classCode,lesson);
            c.addClassLessons(listClasses_);
            for (const Lesson& lesson : ucClass_.getLessons()) {
                int weekDayPosition=lesson.getWeekday() -1;

                float duration = lesson.getDuration();
                int lessonStartPosition = 24 * 2 * weekDayPosition + (lesson.getStartHour() - 8.00) * 4;

                scheduleVector[lessonStartPosition] = " " + ucClass_.getUcCode() + "(" + lesson.getType() + ")";

                if (ucClass_.getUcCode().length() + lesson.getType().length() + 2 < 15)
                    scheduleVector[lessonStartPosition] += string(15 - ucClass_.getUcCode().length() - lesson.getType().length(), ' ');

                scheduleVector[lessonStartPosition] += "|";

                scheduleVector[++lessonStartPosition] = "   " + ucClass_.getClassCode() + "    |";

                duration -= 0.5;
                while (duration > 0.5) {
                    duration -= 0.5;
                    scheduleVector[++lessonStartPosition] = "              |";
                    scheduleVector[++lessonStartPosition] = "              |";
                }
                scheduleVector[++lessonStartPosition] = "              |";
            }
        }
    }

    float time = 8.0;
    for (int i = 0; i < 24 * 2; i += 2) {
        if (time < 10 || (time + 0.5 < 10)) schedule_ += "|  ";
        else schedule_ += "| ";

        schedule_ +=to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6)) + "0-";

        time += 0.5;
        if (time-static_cast<int>(time)==0){
            schedule_ += to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6))+ "0";
        }
        else {
            schedule_ += to_string(static_cast<int>(time)) + ':' + to_string(static_cast<int>((time - static_cast<int>(time)) * 6 * 10));
        }
        if (time < 10 && (time - 0.5 < 10)) schedule_ += ' ';
        schedule_ += " |" + scheduleVector[i] + scheduleVector[48 * 1 + i] + scheduleVector[48 * 2 + i] + scheduleVector[48 * 3 + i] + scheduleVector[48 * 4 + i] + '\n';
        schedule_ += "|_____________|" + scheduleVector[i + 1] + scheduleVector[48 * 1 + i + 1] + scheduleVector[48 * 2 + i + 1] + scheduleVector[48 * 3 + i + 1] + scheduleVector[48 * 4 + i + 1] + '\n';
    }
    cout << schedule_;
}
