#ifndef PROJECT_SCHEDULE_H
#define PROJECT_SCHEDULE_H
#include <string>
#include <vector>
#include "Lesson.h"

class Schedule {
    public:
    Schedule();
    Schedule(std::vector<Lesson> Schedule);
    std::vector<Lesson> getSchedule();
    void setSchedule(std::vector<Lesson> Schedule);
    void addLesson(const Lesson& Lesson);



    private:
    std::vector<Lesson> Schedule_;



};


#endif
