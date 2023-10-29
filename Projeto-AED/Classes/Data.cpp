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
    startNUcsToStudentsMap();
    startUcToClassMap();
    startClassToUcMap();
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
        students_.insert(Student(stc,StName));

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
set<Student> Data::getStudents(){
    return students_;
}
void Data::setListStudents_Classes_(std::list<std::pair<Student, UC>> l){
    listStudents_Classes_= l;
}

void Data::printStudentsAscendingCode(){
    for ( const auto& student: students_){
        cout << student.get_StudentCode() << " - " << student.get_StudentName()<< endl;
    }

}
void Data::printStudentsDescendingCode() {
    vector<Student> studentsVector(students_.begin(), students_.end());
    std::sort(studentsVector.rbegin(), studentsVector.rend());

    for (const auto& student : studentsVector) {
        cout << student.get_StudentCode() << " - " << student.get_StudentName() << endl;
    }

}
void Data::printStudentsAscendingName() {
    vector<Student> studentsVector(students_.begin(), students_.end());
    std::sort(studentsVector.begin(), studentsVector.end(), [](const Student& a, const Student& b) {
        return a.get_StudentName() < b.get_StudentName();
    });

    for (const auto& student : studentsVector) {
        cout << student.get_StudentName() << " - " << student.get_StudentCode() << endl;
    }
}
struct CompareStudentsByName {
    bool operator()(const Student& lhs, const Student& rhs) const {
        return lhs.get_StudentName() > rhs.get_StudentName();
    }
};

void Data::printStudentsDescendingName() {
    set<Student, CompareStudentsByName> students;

    for (const auto& student : students_) {
        students.insert(student);
    }

    for (const auto& student : students) {
        cout << student.get_StudentName() << " - " << student.get_StudentCode()<< endl;
    }
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

void Data::startNUcsToStudentsMap(){

    std::map<int, int> studentCodeToN;

    for (const auto& d : listStudents_Classes_) {
        studentCodeToN[d.first.get_StudentCode()]++;
    }

    for (const auto& d : listStudents_Classes_) {
        Student s = d.first;
        int c = studentCodeToN[s.get_StudentCode()];

        NUcsToStudentsMap_[c].push_back(s);
    }
}

map<int, list<Student>> Data::getNUcsToStudentsMap(){
    return NUcsToStudentsMap_;
}


void Data::printStudentsWithNUcs(int n,const map<int, list<Student>>& m){

    auto i= m.find(n);

    if (i == m.end()){
        return;
    }
    else {
        for (const Student &s: i->second) {
            cout << s.get_StudentName() << " (" << s.get_StudentCode() << ")\n";
        }
    }
}

int Data::numberStudentsWithNUcs(int n,const map<int, list<Student>>& m){

    auto i= m.find(n);

    if (i == m.end()){
        return 0;
    }
    else {
        return (int) i->second.size();
    }
}


void Data::startUcToClassMap(){
    for (const auto& d : listStudents_Classes_) {
        ucToClassMap_[d.second.getUcCode()].insert(d.second.getClassCode());
    }
}

void Data::startClassToUcMap(){
    for (const auto& d : listStudents_Classes_) {
        classToUcMap_[d.second.getClassCode()].insert(d.second.getUcCode());
    }
}

map<string, set<string>> Data::getUcToClassMap(){
    return ucToClassMap_;
}

map<string, set<string>> Data::getClassToUcMap(){
    return classToUcMap_;
}

void Data::printClassByUcs(const string& UCCode,map<string, set<string>> m){
    auto i = m.find(UCCode);
    if (i != m.end()) {
        for (const string& c : i->second) {
            cout << c << endl;
        }
    }
}
void Data::printUcsByClass(const string& CCode,map<string, set<string>> m){
    auto i = m.find(CCode);
    if (i != m.end()) {
        for (const string& u : i->second) {
            cout << u << endl;
        }
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
                Lesson lesson= ucClass.second;
                int weekDayPos=lesson.getWeekday() -1;

                float duration = lesson.getDuration();
                int lessonPosition = 24 * 2 * weekDayPos + (lesson.getStartHour() - 8.00) * 4;



                if (ucClass.first.getUcCode().length() + lesson.getType().length() +2 < 14) {
                    if ("T" == ucClass.second.getType()){
                        scheduleVector[lessonPosition] = "  " + ucClass.first.getUcCode() + "(" + lesson.getType() + ")";
                        scheduleVector[lessonPosition] += string(10 - ucClass.first.getUcCode().length() - lesson.getType().length(), ' ');
                    }
                    else if((ucClass.first.getUcCode()) == "UP001"){
                        scheduleVector[lessonPosition] = "   " + ucClass.first.getUcCode() + "(" + lesson.getType() + ")";
                        scheduleVector[lessonPosition] += string(9 - ucClass.first.getUcCode().length() - lesson.getType().length(), ' ');
                    }
                    else{
                        scheduleVector[lessonPosition] = " " + ucClass.first.getUcCode() + "(" + lesson.getType() + ")";
                        scheduleVector[lessonPosition] += string(11 - ucClass.first.getUcCode().length() - lesson.getType().length(), ' ');
                    }
                }
                scheduleVector[lessonPosition] += "|";

                scheduleVector[++lessonPosition] = "   " + ucClass.first.getClassCode() + "    |";

                duration -= 0.5;
                while (duration > 0.5) {
                    duration -= 0.5;
                    scheduleVector[++lessonPosition] = "              |";
                    scheduleVector[++lessonPosition] = "              |";
                }
                scheduleVector[++lessonPosition] = "              |";
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