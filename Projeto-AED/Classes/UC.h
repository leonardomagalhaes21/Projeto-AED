#ifndef PROJECT_UC_H
#define PROJECT_UC_H
#include <string>
#include <list>
#include "Lesson.h"

class UC {
public:
    UC();
    UC(std::string ucCode, std::string classCode, std::list<Lesson> lesson);
    UC(std::string ucCode, std::string classCode);
    std::string getUcCode() const;
    std::string getClassCode() const;
    int getNumberStudents() const;
    void setNumberStudents(int newValue);
    void addLesson(Lesson lesson);
    //bool operator<(const UC Uc) const;
private:
    std::string ucCode_;
    std::string classCode_;
    int numberStudents_;
    std::list<Lesson> lesson_;

};


#endif //PROJECT_UC_H
