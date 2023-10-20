#include "Schedule.h"
#include <algorithm>
using namespace std;


Schedule::Schedule(){
}

Schedule::Schedule(vector<Lesson> schedule) : schedule_(schedule) {
}

std::vector<Lesson> Schedule::getSchedule() {
    return schedule_;
}

void Schedule::setSchedule(vector<Lesson> schedule) {
    copy(schedule.begin(),schedule.end(),schedule_.begin());
}

void Schedule::addLesson(const Lesson& lesson) {
    schedule_.push_back(lesson);
}


