#ifndef PROJECT_SCHEDULE_H
#define PROJECT_SCHEDULE_H
#include <string>
#include <vector>
#include "Lesson.h"
#include "UC.h"

class Schedule {
    public:
    Schedule();
    Schedule(std::vector<std::pair<UC,Lesson>> schedule);
    std::vector<std::pair<UC,Lesson>> getSchedule();
    void setSchedule(std::vector<std::pair<UC,Lesson>> schedule);
    void addLesson(const UC& uc, const Lesson& lesson);
    void printSchedule();

    private:
    std::vector<std::pair<UC,Lesson>> schedule_;


};


#endif
