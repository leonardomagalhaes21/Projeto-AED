#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <map>
#include <iomanip>
#include "Data.h"
using namespace std;

Data::Data() {
    readClasses();
    readClasses_Per_Uc();
    readStudents_Classes();
}
UC* Data::findClass(string ucCode, string classCode) const {

    int low = 0, high = listClasses_Per_Uc_.size() - 1;
    UC* available;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        auto it=listClasses_Per_Uc_.begin();
        advance(it,middle);
        *available = *it;

        if (ucCode < available->getUcCode()) {
            high = middle - 1;
        }
        else if (ucCode == available->getUcCode()) {
            if (classCode == available->getClassCode()) {
                return available;
            }
            else if (classCode < available->getClassCode()) {
                high = middle - 1;
            }
            else {
                low = middle + 1;
            }
        } else {
            low = middle + 1;
        }
    }
    return available;

}

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
    listClasses_Per_Uc_=aux;
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

std::list<std::pair<UC, Lesson>> Data::getListClasses_() const {
    return listClasses_;
}

std::list<UC> Data::getListClasses_Per_Uc_() {
    return listClasses_Per_Uc_;
}

std::list<std::pair<Student, UC>> Data::getListStudents_Classes_() {
    return listStudents_Classes_;
}

void Data::printStudentsByYear(int x,const list<pair<Student, UC>>& val){
    set<Student> res;
    for(const pair<Student,UC>& s: val){
        if (x == (s.first.get_StudentCode()/100000)){
            res.insert(s.first);
        }
    }
    for(const auto & r : res){
        cout << r.get_StudentName() << " ("  << r.get_StudentCode() << ")" << '\n';
    }
}

int Data::numberOfStudentsByYear(int x,const list<pair<Student, UC>>& val){
    set<Student> res;
    for(const pair<Student,UC>& s: val){
        if (x == (s.first.get_StudentCode()/100000)){
            res.insert(s.first);
        }
    }
    return (int) res.size();
}

void Data::printStudentsByClass(const string& x,const list<pair<Student, UC>>& val){
    set<Student> res;
    for(const pair<Student,UC>& s: val){
        if (x == (s.second.getClassCode())){
            res.insert(s.first);
        }
    }
    for(const auto & r : res){
        cout << r.get_StudentName() << " ("  << r.get_StudentCode() << ")" << '\n';
    }
}

int Data::numberOfStudentsInClass(const string& x,const list<pair<Student, UC>>& val) {
    set<Student> res;
    for (const pair<Student, UC>& s: val) {
        if (x == (s.second.getClassCode())) {
            res.insert(s.first);
        }
    }
    return (int) res.size() ;
}


void Data::printStudentsInUC(const string& x,const list<pair<Student, UC>>& val){
    set<Student> res;
    for(const pair<Student,UC>& a: val){
        if (x == (a.second.getUcCode())){
            res.insert(a.first);
        }
    }
    for(const auto & r : res){
        cout << r.get_StudentName() << " ("  << r.get_StudentCode() << ")" << '\n';
    }
}

int Data::numberOfStudentsInUC(const string& x,const list<pair<Student, UC>>& val) {
    set<Student> res;
    for (const pair<Student, UC>& s: val) {
        if (x == (s.second.getUcCode())) {
            res.insert(s.first);
        }
    }
    return (int) res.size() ;
}


void Data::printStudentsWithNUcs(int n,const list<pair<Student, UC>>& val){
    map<Student,int> m;
    for(const pair<Student,UC>& s: val){

        if (m.count(s.first) > 0){
            m[s.first]++;
        }
        else{
            m[s.first]=1;
        }
    }
    for(const auto& par: m){
        if(par.second >=n) {
            cout << par.first.get_StudentName() << " ("  << par.first.get_StudentCode() << ")" << '\n';
        }
    }
}

int Data::numberStudentsWithNUcs(int n,const list<pair<Student, UC>>& val){
    map<Student,int> m;
    for(const pair<Student,UC>& s: val){

        if (m.count(s.first) > 0){
            m[s.first]++;
        }
        else{
            m[s.first]=1;
        }
    }
    int sum =0;
    for(const auto& par: m){
        if(par.second >=n) {
            sum++;
        }
    }
    return sum;
}

void Data::printClassByUcs(const string& UCCode,const list<UC>& val){
    set<UC> res;
    for(const UC& s: val){
        if (UCCode == s.getClassCode()){
            res.insert(s);
        }
    }
    for(const auto & r : res){
        cout << r.getUcCode() << '\n';
    }
}
void Data::printUcsByClass(const string& CCode,const list<UC>& val){
    set<UC> res;
    for(const UC& s: val){
        if (CCode == s.getUcCode()){
            res.insert(s);
        }
    }
    for(const auto & r : res){
        cout << r.getClassCode() << '\n';
    }
}
void Data::printClassTableSchedule(const string& classCode) const{

    cout << classCode + " schedule\n";
    string schedule_ = " ________________________________________________________________________________________\n"
                       "|     Hour    |    Monday    |   Tuesday    |   Wednesday  |   Thursday   |    Friday    |\n"
                       "|________________________________________________________________________________________|\n";


    vector<string> scheduleVector;
    for (int i = 0; i < 24 * 5 * 2; i += 2) {
        scheduleVector.push_back("              |");
        scheduleVector.push_back("______________|");
    }
    for (const auto& ucClass : getListClasses_() ){
        if (ucClass.first.getClassCode() == classCode) {
            //for (const Lesson& lesson : ucClass.getLessons()) {
                Lesson lesson= ucClass.second;
                int weekDayPosition=lesson.getWeekday() -1;

                float duration = lesson.getDuration();
                int lessonStartPosition = 24 * 2 * weekDayPosition + (lesson.getStartHour() - 8.00) * 4;



                if (ucClass.first.getUcCode().length() + lesson.getType().length() +2 < 14) {
                    if ("T" == ucClass.second.getType()){
                        scheduleVector[lessonStartPosition] = "  " + ucClass.first.getUcCode() + "(" + lesson.getType() + ")";
                        scheduleVector[lessonStartPosition] += string(10 - ucClass.first.getUcCode().length() - lesson.getType().length(), ' ');
                    }
                    else if((ucClass.first.getUcCode()) == "UP001"){
                        scheduleVector[lessonStartPosition] = "   " + ucClass.first.getUcCode() + "(" + lesson.getType() + ")";
                        scheduleVector[lessonStartPosition] += string(9 - ucClass.first.getUcCode().length() - lesson.getType().length(), ' ');
                    }
                    else{
                        scheduleVector[lessonStartPosition] = " " + ucClass.first.getUcCode() + "(" + lesson.getType() + ")";
                        scheduleVector[lessonStartPosition] += string(11 - ucClass.first.getUcCode().length() - lesson.getType().length(), ' ');
                    }
                }
                scheduleVector[lessonStartPosition] += "|";

                scheduleVector[++lessonStartPosition] = "   " + ucClass.first.getClassCode() + "    |";

                duration -= 0.5;
                while (duration > 0.5) {
                    duration -= 0.5;
                    scheduleVector[++lessonStartPosition] = "              |";
                    scheduleVector[++lessonStartPosition] = "              |";
                }
                scheduleVector[++lessonStartPosition] = "              |";
            //}
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



void Data::printClassSchedule(const string& classCode, const std::list<UC>& classes_per_uc, const std::list<std::pair<UC, Lesson>>& getListClasses) {
    Schedule s = Schedule();

    for (const auto& c : getListClasses){
        if (c.first.getClassCode() == classCode){
            s.addLesson(c.first,c.second);
        }
    }
    s.printSchedule();

}