
#include "UC.h"
using namespace std;

UC::UC(){

}

UC::UC(string UcCode,string ClassCode){
    UcCode_ = UcCode;
    ClassCode_ = ClassCode;
}


UC::UC(std::string UcCode, std::string ClassCode, list<Lesson> Lesson ) {
    UcCode_=UcCode;
    ClassCode_=ClassCode;
    NumberStudents_=0;
    Lesson_=Lesson;
}

string UC::getUcCode() const {
    return UcCode_;
}
string UC::getClassCode() const {
    return ClassCode_;
}
int UC::getNumberStudents() const {
    return NumberStudents_;
}
void UC::setNumberStudents(int newValue){
    NumberStudents_=newValue;
}
void UC::addLesson(Lesson Lesson) {
    Lesson_.push_back(Lesson);
}