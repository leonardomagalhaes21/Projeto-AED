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
    startUcToStudentsMap();
    startClassToStudentsMap();
    startYearToStudentsMap();
    startUcClasstoStudentsMap();
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
        cout << student.getStudentCode() << " - " << student.getStudentName()<< endl;
    }

}
void Data::printStudentsDescendingCode() {
    vector<Student> studentsVector(students_.begin(), students_.end());
    std::sort(studentsVector.rbegin(), studentsVector.rend());

    for (const auto& student : studentsVector) {
        cout << student.getStudentCode() << " - " << student.getStudentName() << endl;
    }

}
void Data::printStudentsAscendingName() {
    vector<Student> studentsVector(students_.begin(), students_.end());
    std::sort(studentsVector.begin(), studentsVector.end(), [](const Student& a, const Student& b) {
        return a.getStudentName() < b.getStudentName();
    });

    for (const auto& student : studentsVector) {
        cout << student.getStudentName() << " - " << student.getStudentCode() << endl;
    }
}
struct CompareStudentsByName {
    bool operator()(const Student& lhs, const Student& rhs) const {
        return lhs.getStudentName() > rhs.getStudentName();
    }
};

void Data::printStudentsDescendingName() {
    set<Student, CompareStudentsByName> students;

    for (const auto& student : students_) {
        students.insert(student);
    }

    for (const auto& student : students) {
        cout << student.getStudentName() << " - " << student.getStudentCode()<< endl;
    }
}

void Data::startYearToStudentsMap(){
    for (const auto& c : listStudents_Classes_){
        yearToStudentsMap_[c.first.getStudentCode()/100000].insert(c.first);
    }
}

map<int, set<Student>> Data::getYearToStudentsMap(){
    return yearToStudentsMap_;
}


void Data::printStudentsByYear(int x,const map<int, set<Student>>& m){

    auto i = m.find(x);
    if (i != m.end()) {
        for (const auto &c: i->second) {
            cout << c.getStudentName() << " (" << c.getStudentCode() << ")" << '\n';
        }
    }
}

int Data::numberOfStudentsByYear(int x,const map<int, set<Student>>& m){
    auto i = m.find(x);
    if (i != m.end()) {
        return (int) i->second.size();
    }
    else return 0;
}

void Data::startClassToStudentsMap(){
    for (const auto& c : listStudents_Classes_){
        classToStudentsMap_[c.second.getClassCode()].insert(c.first);
    }
}

map<string, set<Student>> Data::getClassToStudentsMap(){
    return classToStudentsMap_;
}

void Data::printStudentsByClass(const string& x,const map<string, set<Student>>& m){

    auto i = m.find(x);
    if (i != m.end()) {
        for (const auto &c: i->second) {
            cout << c.getStudentName() << " (" << c.getStudentCode() << ")" << '\n';
        }
    }
}

int Data::numberOfStudentsInClass(const string& x,const map<string, set<Student>>& m) {
    auto i = m.find(x);
    if (i != m.end()) {
        return (int) i->second.size();
    }
    else return 0;
}

void Data::startUcToStudentsMap(){
    for (const auto& c : listStudents_Classes_){
        ucToStudentsMap_[c.second.getUcCode()].insert(c.first);
    }
}

map<string, set<Student>> Data::getUcToStudentsMap(){
    return ucToStudentsMap_;
}

void Data::printStudentsInUC(const string& x,const map<string, set<Student>>& m){

    auto i = m.find(x);
    if (i != m.end()) {
        for (const auto &c: i->second) {
            cout << c.getStudentName() << " (" << c.getStudentCode() << ")" << '\n';
        }
    }
}

int Data::numberOfStudentsInUC(const string& x,const map<string, set<Student>>& m) {
    auto i = m.find(x);
    if (i != m.end()) {
        return (int) i->second.size();
    }
    else return 0;
}

void Data::startNUcsToStudentsMap(){

    std::map<int, int> studentCodeToN;

    for (const auto& d : listStudents_Classes_) {
        studentCodeToN[d.first.getStudentCode()]++;
    }

    for (const auto& d : listStudents_Classes_) {
        Student s = d.first;
        int c = studentCodeToN[s.getStudentCode()];

        nUcsToStudentsMap_[c].push_back(s);
    }
}

map<int, list<Student>> Data::getNUcsToStudentsMap(){
    return nUcsToStudentsMap_;
}


void Data::printStudentsWithNUcs(int n,const map<int, list<Student>>& m){

    auto i= m.find(n);

    if (i == m.end()){
        return;
    }
    else {
        for (const auto& s: i->second) {
            cout << s.getStudentName() << " (" << s.getStudentCode() << ")\n";
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
        for (const auto& c : i->second) {
            cout << c << endl;
        }
    }
}
void Data::printUcsByClass(const string& CCode,map<string, set<string>> m){
    auto i = m.find(CCode);
    if (i != m.end()) {
        for (const auto& u : i->second) {
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


void Data::printTop5UCs(const map<string, set<Student>>& m) {

    vector<pair<string, int>> vec;

    for (const auto& c : m) {
        int a = c.second.size();
        pair<string,int> p = {c.first, a};
        vec.push_back(p);
    }

    sort(vec.begin(), vec.end(),[](const pair<string, int>& a, const pair<string, int>& b){
             return a.second > b.second;
         });

    cout << "1. UC: " << vec[0].first << " -> " << vec[0].second << " students" << endl;
    cout << "2. UC: " << vec[1].first << " -> " << vec[1].second << " students" << endl;
    cout << "3. UC: " << vec[2].first << " -> " << vec[2].second << " students" << endl;
    cout << "4. UC: " << vec[3].first << " -> " << vec[3].second << " students" << endl;
    cout << "5. UC: " << vec[4].first << " -> " << vec[4].second << " students" << endl;
}

void Data::startUcClasstoStudentsMap() {
    for (const auto& c : listStudents_Classes_){
        if (ucClasstoStudentsMap_.find(c.second) != ucClasstoStudentsMap_.end()){
            ucClasstoStudentsMap_[c.second].insert(c.first);
        }
        else{
            ucClasstoStudentsMap_[c.second] = set<Student>();
        }
    }
}

std::map<UC, std::set<Student>> Data::getUcClasstoStudentsMap() {
    return ucClasstoStudentsMap_;
}

void Data::printStudentsInUcClass(const string &ucCode, const string &classCode, std::map<UC, std::set<Student>> m) {
    UC a = UC(ucCode,classCode);
    for(const auto& s : m[a]){
        cout << s.getStudentName() << " (" << s.getStudentCode() << ")\n";
    }
}

int Data::numberOfStudentsInUcClass(const string &ucCode, const string &classCode, std::map<UC, std::set<Student>> m) {
    UC a = UC(ucCode,classCode);
    return (int) m[a].size();
}




