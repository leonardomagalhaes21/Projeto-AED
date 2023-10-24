#ifndef PROJECT_UC_H
#define PROJECT_UC_H
#include <string>
#include <list>
#include "Lesson.h"
#include <iostream>
#include <map>
#include <set>
#include "Data.h"
#include "Schedule.h"

class Schedule;

class UC {
public:
    UC();
    UC(std::string ucCode, std::string classCode, std::list<Lesson> lesson);
    UC(std::string ucCode, std::string classCode);
    UC(std::string ucCode);

    std::string getUcCode() const;
    std::string getClassCode() const;
    int getNumberStudents() const;
    void setNumberStudents(int newValue);
    void addLesson(const Lesson& lesson);
    bool operator<(const UC& Uc) const;
    void printLessons() const;
    std::list<Lesson> getLessons() const;
    void addClassLessons(const std::list<std::pair<UC, Lesson>>& l1);
    Schedule getSchedule(const std::list<std::pair<UC, Lesson>>& l1);
private:
    std::string ucCode_;
    std::string classCode_;
    int numberStudents_;
    std::list<Lesson> lesson_;


};


#endif //PROJECT_UC_H
