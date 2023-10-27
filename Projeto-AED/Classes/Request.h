#ifndef PROJECT_REQUEST_H
#define PROJECT_REQUEST_H


#include "Student.h"

class Request {
    void addUC(const Student& s, const UC& uc, const std::list<std::pair<Student, UC>>& val);

};


#endif //PROJECT_REQUEST_H
