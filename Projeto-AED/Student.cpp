
#include "Student.h"
#include <string>
using namespace std;

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
