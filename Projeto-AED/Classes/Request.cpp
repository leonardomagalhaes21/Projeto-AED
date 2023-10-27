#include "Request.h"
using namespace std;

void Request::addUC(const Student& s, const UC& uc, const list<pair<Student, UC>>& val) {
    int n = 0;
    for(const pair<Student,UC>& c: val){
        if (c.first.get_StudentCode() == s.get_StudentCode()){
            n++;
        }
    }


}
