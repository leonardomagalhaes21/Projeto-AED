#include "Request.h"
using namespace std;


void RequestLog::requestAndLog(const std::string& action,Student student, UC newUc) {
    Operation operation;
    operation.action_ = action;
    operation.newUc_ = newUc;
    operations.push_back(operation);
}
void RequestLog::requestAndLog(const std::string& action, Student student,UC newUc,UC oldUc) {
    Operation operation;
    operation.action_ = action;
    operation.student_=student;
    operation.newUc_ = newUc;
    operation.oldUc_= oldUc;
    operations.push_back(operation);
}
void RequestLog::requestAndLog(const std::string& action,Student student, std::string class_uc_Code){
    Operation operation;
    operation.action_ = action;
    operation.student_=student;
    operation.class_Uc_Code_=class_uc_Code;
}

/*
void RequestLog::printLog() {
    std::cout << "Request Log:" << std::endl;
    for (const Operation& operation : operations) {
        std::cout << operation.action << " " << operation.value << std::endl;
    }
}
*/
Request::Request(){}

bool Request::addUC(const Student& s, const string& ucc, const string& cc, list<pair<Student, UC>>& val, const list<pair<UC, Lesson>>& val2) {
    int n = 0;
    for(const pair<Student,UC>& c: val){
        if (c.first.get_StudentCode() == s.get_StudentCode()){
            n++;
        }
    }
    bool cond1, cond2, cond3;
    cond1 = n<7;
    cond2 = true;
    cond3 = true;

    map<string, int> m;
    for(const pair<Student,UC>& c: val){
        if (c.second.getUcCode() == ucc){
            if (m.count(c.second.getClassCode()) > 0){
                m[c.second.getClassCode()]++;
            }
            else{
                m[c.second.getClassCode()]=1;
            }
        }
    }

    for(const auto& c : m){
        if (abs(m[cc]+1 - c.second) > 4){
            cond2 = false;
        }
    }

    Schedule schedule = s.getStudentSchedule(val,val2);

    UC a = UC(ucc, cc);
    for(const auto& c : val2){
        if(c.first.getClassCode() == cc && c.first.getUcCode() == ucc) {
            a.addLesson(c.second);
        }
    }
    for(const auto& c : schedule.getSchedule()){
        for (const auto& d : a.getLessons()){
            if (c.second.Coincide_T(d)){
                cond3 = false;
                break;
            }
        }
    }

    if (cond1 && cond2 && cond3){
        pair<Student, UC> p = {s,a};
        val.push_back(p);
        cout << "Operation successful!";
        return true;
    }
    else{
        cout << "Operation failed!";
        return false;
    }

}


void Request::switchUC(const Student& s, const UC& oldUC, const UC& newUC, list<pair<Student, UC>>& val,const list<pair<UC, Lesson>>& val2) {
    removeUC(s, oldUC, val);
    if(addUC(s, newUC.getUcCode(),newUC.getClassCode(), val,val2)){
        cout << "Operation successful!";
    }
    else{
        addUC(s,oldUC.getUcCode(),oldUC.getClassCode(),val,val2);
        cout << "Operation failed!";
    }
}

void Request::removeUC(const Student& s, const UC& uc, list<pair<Student, UC>>& val) {
    for (auto it = val.begin(); it != val.end(); ) {
        if (it->first.get_StudentCode()==s.get_StudentCode() and it->second.getUcCode()==uc.getUcCode()) {
            it = val.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool Request::addClass(const Student& s, const UC& uc, list<pair<Student, UC>>& val, const list<pair<UC, Lesson>>& val2){
    bool cond1, cond2, cond3;
    cond1 = true;
    cond2 = true;
    cond3 = true;

    for (const auto& pair : val) {
        if (pair.first.get_StudentCode() == s.get_StudentCode() && pair.second.getClassCode() != uc.getClassCode()) {
            cond1 = false;
        }
    }

    map<string, int> m;
    for(const pair<Student,UC>& c: val){
        if (c.second.getUcCode() == uc.getUcCode()){
            if (m.count(c.second.getClassCode()) > 0){
                m[c.second.getClassCode()]++;
            }
            else{
                m[c.second.getClassCode()]=1;
            }
        }
    }

    for(const auto& c : m){
        if (abs(m[uc.getClassCode()]+1 - c.second) > 4){
            cond2 = false;
        }
    }

    Schedule schedule = s.getStudentSchedule(val,val2);

    UC a = UC(uc.getUcCode(), uc.getClassCode());
    for(const auto& c : val2){
        if(c.first.getClassCode() == uc.getClassCode() && c.first.getUcCode() == uc.getUcCode()) {
            a.addLesson(c.second);
        }
    }
    for(const auto& c : schedule.getSchedule()){
        for (const auto& d : a.getLessons()){
            if (c.second.Coincide_T(d)){
                cond3 = false;
                break;
            }
        }
    }

    if (cond1 && cond2 && cond3){
        pair<Student, UC> p = {s,a};
        val.push_back(p);
        cout << "Operation successful!";
        return true;
    }
    else{
        cout << "Operation failed!";
        return false;
    }
}

void Request::switchClass(const Student& s, const UC& oldUC, const UC& newUC, list<pair<Student, UC>>& val,const list<pair<UC, Lesson>>& val2) {
    removeClass(s, oldUC, val);

    if(addClass(s, newUC, val,val2)){
        cout << "Operation successful!";
    }
    else{
        addClass(s,oldUC,val,val2);
        cout << "Operation failed!";
    }
}
void Request::removeClass(const Student& s, const UC& uc, list<pair<Student, UC>>& val) {
    for (auto it = val.begin(); it != val.end(); ) {
        if (it->first.get_StudentCode()==s.get_StudentCode() and it->second.getClassCode()==uc.getClassCode()) {
            it = val.erase(it);
        }
        else {
            ++it;
        }
    }
}

