
#include "Student.h"
#include <string>
using namespace std;

Student::Student(int StudentCode, string StudentName){
    StudentCode_ = StudentCode;
    StudentName_ = StudentName;
}

int Student::get_StudentCode() const {
    return StudentCode_;
}

std::string Student::get_StudentName() {
    return StudentName_;
}
