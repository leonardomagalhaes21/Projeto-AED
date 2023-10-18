#include "Schedule.h"
using namespace std;


Schedule::Schedule(){
}

Schedule::Schedule(vector<Lesson> Schedule) {
    Schedule_ = Schedule;
}

std::vector<Lesson> Schedule::getSchedule() {
    return Schedule_;
}

void Schedule::setSchedule(vector<Lesson> Schedule) {
    Schedule_ = Schedule;
}


void Schedule::addLesson(const Lesson& Lesson) {
    Schedule_.push_back(Lesson);
}


