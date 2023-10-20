#ifndef PROJECT_SCHEDULE_H
#define PROJECT_SCHEDULE_H
#include <string>
#include <vector>
#include "Lesson.h"

class Schedule {
    public:
    Schedule();
    Schedule(std::vector<Lesson> schedule);
    std::vector<Lesson> getSchedule();
    void setSchedule(std::vector<Lesson> schedule);
    void addLesson(const Lesson& lesson);


    private:
    std::vector<Lesson> schedule_;



};


#endif
