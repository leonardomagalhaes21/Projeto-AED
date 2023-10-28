#include "Request.h"
using namespace std;

Request::Request(){}

void Request::addUC(const Student& s, const string& ucc, list<pair<Student, UC>>& val, const list<pair<UC, Lesson>>& val2) {
    int n = 0;
    for(const pair<Student,UC>& c: val){
        if (c.first.get_StudentCode() == s.get_StudentCode()){
            n++;
        }
    }
    bool t, y;
    t = n<7;
    y = true;

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

    Schedule schedule = s.getStudentSchedule(val,val2);
    string cl;
    while (true){
        int min = INT_MAX;
        for(const auto& c : m){
            if (c.second < min){
                cl = c.first;
                min = c.second;
            }
        }
        UC a = UC(ucc, cl);
        for(const auto& c : val2){
            a.addLesson(c.second);
        }
        for(const auto& c : schedule.getSchedule()){
            for (const auto& d : a.getLessons()){
                if (c.second.Coincide_T(d)){
                    y = false;
                    break;
                }
            }
        }

        if (m.empty()) break;
        if (!y){
            m.erase(cl);
        }
        else break;
    }

    if (t && y){
        UC a = UC(ucc, cl);
        pair<Student, UC> p = {s,a};
        val.push_back(p);
    }



}
