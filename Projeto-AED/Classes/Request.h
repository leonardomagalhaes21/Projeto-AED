#ifndef PROJECT_REQUEST_H
#define PROJECT_REQUEST_H


#include "Student.h"

class Request {
    public:
    Request();
    static void addUC(const Student& s, const std::string& ucc, const std::string& cc, std::list<std::pair<Student, UC>>& val, const std::list<std::pair<UC, Lesson>>& val2);
    //void switchUC(const Student& s, const UC& oldUC, const UC& newUC, std::list<std::pair<Student, UC>>& val,const std::list<std::pair<UC, Lesson>>& val2);
    void removeUC(const Student& s, const UC& uc, std::list<std::pair<Student, UC>>& val);
    void addClass(const Student& s, const std::string& ucc, const std::string& cc, std::list<std::pair<Student, UC>>& val, const std::list<std::pair<UC, Lesson>>& val2);
    //void switchClass(const Student& s, const UC& oldUC, const UC& newUC, std::list<std::pair<Student, UC>>& val,const std::list<std::pair<UC, Lesson>>& val2);
    void removeClass(const Student& s, const UC& uc, std::list<std::pair<Student, UC>>& val);
};


#endif //PROJECT_REQUEST_H
