#ifndef PROJECT_REQUEST_H
#define PROJECT_REQUEST_H


#include "Student.h"

class Request {
    public:
    Request();
    static void addUC(const Student& s, const std::string& ucc, std::list<std::pair<Student, UC>>& val, const std::list<std::pair<UC, Lesson>>& val2);

};


#endif //PROJECT_REQUEST_H
