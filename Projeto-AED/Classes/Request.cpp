#include "Request.h"
using namespace std;

Request::Request(){}

void Request::addUC(const Student& s, const string& ucc, const string& cc, list<pair<Student, UC>>& val, const list<pair<UC, Lesson>>& val2) {
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
    }
    else{
        cout << "Operation failed!";
    }

}

/*
void Request::switchUc(const Student& s, const UC& oldUC, const UC& newUC, list<pair<Student, UC>>& val,const list<pair<UC, Lesson>>& val2) {
    removeUc(s, oldUC, val);
    addUC(s, newUC, val,val2);
}*/

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
/*
void Request::addClass(const Student& s, const UC& uc, list<pair<Student, UC>>& val, const list<pair<UC, Lesson>>& val2){
    for (const auto& pair : val) {
        if (pair.first.get_StudentCode() == s.get_StudentCode() && pair.second.getClassCode() != uc.getClassCode()) {
            cout << "O estudante já está em outra classe para a mesma UC" << endl;
            return;
        }
    }
    bool cond2, cond3;
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

    if (cond2 && cond3){
        pair<Student, UC> p = {s,a};
        val.push_back(p);
        cout << "Operation successful!";
    }
    else{
        cout << "Operation failed!";
    }
}*/
/*
void Request::switchClass(const Student& s, const UC& oldUC, const UC& newUC, list<pair<Student, UC>>& val,const list<pair<UC, Lesson>>& val2) {
    removeClass(s, oldUC, val);
    addClass(s, newUC, val,val2);
}*/
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

