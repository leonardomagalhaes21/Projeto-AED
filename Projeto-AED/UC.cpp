
#include "UC.h"
using namespace std;

UC::UC(){

}

UC::UC(string ucCode,string classCode){
    ucCode_ = ucCode;
    classCode_ = classCode;
}


UC::UC(std::string ucCode, std::string classCode, list<Lesson> lesson ) {
    ucCode_=ucCode;
    classCode_=classCode;
    numberStudents_=0;
    lesson_=lesson;
}

string UC::getUcCode() const {
    return ucCode_;
}
string UC::getClassCode() const {
    return classCode_;
}
int UC::getNumberStudents() const {
    return numberStudents_;
}
void UC::setNumberStudents(int newValue){
    numberStudents_=newValue;
}
void UC::addLesson(Lesson lesson) {
    lesson_.push_back(lesson);
}