#include "Student.h"
#include <string>
#include <set>

using namespace std;

Student::Student(){

}

Student::Student(int studentCode, string studentName){
    studentCode_ = studentCode;
    studentName_ = studentName;
}

int Student::get_StudentCode() const {
    return studentCode_;
}

std::string Student::get_StudentName() {
    return studentName_;
}
void Student::set_StudentCode(int StudentCode) {
    studentCode_ = StudentCode;
}

void Student::set_StudentName(string StudentName) {
    studentName_ = StudentName;
}
/*bool Student::operator<(const Student &Student) const {
    return studentCode_ < Student.studentCode_;
}*/

Schedule Student::getStudentSchedule() {
    Schedule s = Schedule();
    Data d = Data();
    d.readStudents_Classes();
    d.readClasses();
    set<UC> ucs;

    for (const auto& c : d.getListStudents_Classes_()){
        if (c.first.get_StudentCode() == studentCode_){
            ucs.insert(c.second);
        }
    }

    for (const auto& c : d.getListClasses_()){
        if (ucs.find(c.first) != ucs.end()){
            s.addLesson(c.first,c.second);
        }
    }

    return s;

}


