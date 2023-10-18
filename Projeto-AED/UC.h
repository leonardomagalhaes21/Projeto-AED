#ifndef PROJECT_UC_H
#define PROJECT_UC_H
#include <string>
#include <list>
#include "Lesson.h"

class UC {
public:
    UC();
    UC(std::string UcCode, std::string ClassCode, std::list<Lesson> Lesson);
    UC(std::string UcCode, std::string ClassCode);
    std::string getUcCode() const;
    std::string getClassCode() const;
    int getNumberStudents() const;
    void setNumberStudents(int newValue);
    void addLesson(Lesson Lesson_);
private:
    std::string UcCode_;
    std::string ClassCode_;
    int NumberStudents_;
    std::list<Lesson> Lesson_;

};


#endif //PROJECT_UC_H
