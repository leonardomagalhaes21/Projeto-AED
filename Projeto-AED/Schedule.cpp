#include "Schedule.h"
using namespace std;


Schedule::Schedule(){
}

Schedule::Schedule(vector<Lesson> schedule) {
    schedule_ = schedule;
}

std::vector<Lesson> Schedule::getSchedule() {
    return schedule_;
}

void Schedule::setSchedule(vector<Lesson> schedule) {
    schedule_ = schedule;
}


void Schedule::addLesson(const Lesson& lesson) {
    schedule_.push_back(lesson);
}


