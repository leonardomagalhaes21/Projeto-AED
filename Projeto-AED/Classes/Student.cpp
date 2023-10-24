#include "Student.h"
#include <string>
#include <set>

using namespace std;

Student::Student(){

}
Student::Student(int studentCode, string studentName, list<UC> ucs){
    studentCode_ = studentCode;
    studentName_ = studentName;
    ucs_ = ucs;
}

Student::Student(int studentCode, string studentName){
    studentCode_ = studentCode;
    studentName_ = studentName;
}


int Student::get_StudentCode() const {
    return studentCode_;
}

std::string Student::get_StudentName() const {
    return studentName_;
}
list<UC> Student::get_Ucs() const {
    return ucs_;
}
void Student::set_StudentCode(int StudentCode) {
    studentCode_ = StudentCode;
}

void Student::set_StudentName(string StudentName) {
    studentName_ = StudentName;
}
void Student::set_Ucs(list<UC> ucs) {
    ucs_ = ucs;
}

bool Student::operator<(const Student &Student) const {
    return studentCode_ < Student.studentCode_;
}
void Student::add_UC(UC uc) {
    ucs_.push_back(uc);
}
bool Student::has_Class(string classCode) const {
    for(UC uc: ucs_){
        if(uc.getClassCode()==classCode){
            return true;
        }
    }
    return false;
}
bool Student::has_Uc(string ucCode) const {
    for(UC uc: ucs_){
        if(uc.getUcCode()==ucCode){
            return true;
        }
    }
    return false;
}

Schedule Student::getStudentSchedule(const std::list<std::pair<Student, UC>>& l1,const std::list<std::pair<UC, Lesson>>& l2) const {
    Schedule s = Schedule();
    set<UC> ucs;

    for (const auto& c : l1){
        if (c.first.get_StudentCode() == studentCode_){
            ucs.insert(c.second);
        }
    }

    for (const auto& c : l2){
        if (ucs.find(c.first) != ucs.end()){
            s.addLesson(c.first,c.second);
        }
    }

    return s;

}

void Student::printStudentTableSchedule() const {

}




