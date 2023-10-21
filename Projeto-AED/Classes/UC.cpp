#include "UC.h"
using namespace std;

UC::UC(){
    numberStudents_ = 0;
}

UC::UC(string ucCode,string classCode){
    ucCode_ = ucCode;
    classCode_ = classCode;
    numberStudents_ = 0;
}

UC::UC(string ucCode, string classCode, list<Lesson> lesson) : ucCode_(ucCode), classCode_(classCode), lesson_(lesson) {
    numberStudents_ = 0;
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
bool UC::operator<(const UC UC) const{
    if(ucCode_ < UC.ucCode_){
        return true;
    }
    else if(ucCode_ == UC.ucCode_){
        if(classCode_ < UC.classCode_){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}
