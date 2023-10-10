#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    string f = "schedule/classes.csv";
    ifstream file(f);
    if(!file.is_open()&&!file.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
        return 1;
    }

    string line,ClassCode,UcCode,Weekday,Type,StartHour,Duration;
    vector<vector<string>> p;
    getline(file,line);
    while(getline(file,line)){
        istringstream iss(line);
        getline(iss,ClassCode,',');
        getline(iss,UcCode,',');
        getline(iss,Weekday,',');
        getline(iss,StartHour,',');
        getline(iss,Duration,',');
        getline(iss,Type,',');
        vector<string> s = {ClassCode,UcCode,Weekday,Type,StartHour,Duration};
        p.push_back(s);
    }

    return 0;
}