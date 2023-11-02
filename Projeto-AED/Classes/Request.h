#ifndef PROJECT_REQUEST_H
#define PROJECT_REQUEST_H

#include "Student.h"
#include <fstream>
#include <queue>
struct RequestLog {
    struct Operation {
        std::string action_; // "add" ou "remove"
        UC newUc_;
        UC oldUc_;
        std::string class_Uc_Code_;
        Student student_;
    };
    RequestLog();
    std::queue<Operation> operations_;
    void requestAndLog(const std::string& action,const Student& student, UC newUc);
    void requestAndLog(const std::string& action,const Student& student,UC newUc, UC oldUc);
    void requestAndLog(const std::string& action,const Student& student, std::string class_uc_Code);
    void save();
    void undo();
};

class Request {
    public:
    Request();
    static bool addUC(const Student& s, const std::string& ucc, const std::string& cc, std::list<std::pair<Student, UC>>& val, const std::list<std::pair<UC, Lesson>>& val2, const std::map<UC, std::set<Student>>& m);
    static bool switchUC(const Student& s, const UC& oldUC, const UC& newUC, std::list<std::pair<Student, UC>>& val,const std::list<std::pair<UC, Lesson>>& val2, const std::map<UC, std::set<Student>>& m);
    static bool removeUC(const Student& s, const UC& uc, std::list<std::pair<Student, UC>>& val);
    static bool switchClass(const Student& s, const UC& oldUC, const UC& newUC, std::list<std::pair<Student, UC>>& val,const std::list<std::pair<UC, Lesson>>& val2, const std::map<UC, std::set<Student>>& m);
    static bool removeClass(const Student& s, const std::string& uc, std::list<std::pair<Student, UC>>& val);
private:
    RequestLog log;
};


#endif //PROJECT_REQUEST_H
