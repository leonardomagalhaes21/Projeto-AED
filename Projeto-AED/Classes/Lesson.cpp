#include "Lesson.h"


using namespace std;

Lesson::Lesson(){};

Lesson::Lesson(int weekday, float duration, float start_hour, string type)
        : weekday_(weekday), duration_(duration), start_hour_(start_hour), type_(type){
}



int Lesson::getWeekday() const{
   return weekday_;
}
float Lesson::getDuration() const{
    return duration_;
}
float Lesson::getStartHour() const{
    return start_hour_;
}
string Lesson::getType() const{
    return type_;
}
bool Lesson::Coincide_T(const Lesson& lesson) const{
    if (type_ == lesson.getType()) {
        if (weekday_ == lesson.getWeekday()) {
            if (start_hour_ + duration_ > getStartHour() && start_hour_ + duration_ <= getStartHour() + getDuration()){
                return true;
            }
            if(getStartHour() + getDuration() > start_hour_ && getStartHour() + getDuration() <= start_hour_ + duration_)
                return true;
        }
    }
    return false;
}


