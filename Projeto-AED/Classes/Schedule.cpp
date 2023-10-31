#include "Schedule.h"
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


Schedule::Schedule(){
}

Schedule::Schedule(vector<pair<UC,Lesson>> schedule) : schedule_(schedule) {
}

vector<pair<UC,Lesson>> Schedule::getSchedule() {
    return schedule_;
}

void Schedule::setSchedule(vector<pair<UC,Lesson>> schedule) {
    schedule_=schedule;
}

void Schedule::addLesson(const UC& uc,const Lesson& lesson) {
    pair<UC,Lesson> p = {uc, lesson};
    schedule_.push_back(p);
}

struct compareLessons {
    bool operator()(const pair<UC, Lesson> &a, const pair<UC, Lesson> &b) {
        if (a.second.getWeekday() < b.second.getWeekday()) {
            return true;
        }
        else if (a.second.getWeekday() > b.second.getWeekday()) {
            return false;
        }
        else return (a.second.getStartHour() < b.second.getStartHour());
    }
};

void Schedule::printSchedule() {

    map<string, string> UcCodeToName = {
            {"L.EIC001", "ALGA"},
            {"L.EIC002", "AMI"},
            {"L.EIC003", "FP"},
            {"L.EIC004", "FSC"},
            {"L.EIC005", "MD"},
            {"L.EIC006", "AC"},
            {"L.EIC007", "AMII"},
            {"L.EIC008", "FI"},
            {"L.EIC009", "P"},
            {"L.EIC010", "TC"},
            {"L.EIC011", "AED"},
            {"L.EIC012", "BD"},
            {"L.EIC013", "FII"},
            {"L.EIC014", "LDTS"},
            {"L.EIC015", "SO"},
            {"L.EIC016", "DA"},
            {"L.EIC017", "ES"},
            {"L.EIC018", "LC"},
            {"L.EIC019", "LTW"},
            {"L.EIC020", "ME"},
            {"L.EIC021", "FSI"},
            {"L.EIC022", "IPC"},
            {"L.EIC023", "LBAW"},
            {"L.EIC024", "PFL"},
            {"L.EIC025", "RC"},
            {"UP001", "PUP"}
    };

    map<int, string> NumToWeekday = {
            {1, "Monday"},
            {2, "Tuesday"},
            {3, "Wednesday"},
            {4, "Thursday"},
            {5, "Friday"}
    };

    sort(schedule_.begin(), schedule_.end(), compareLessons());

    cout << "--------------------------------------------------------------------" << endl;
    cout << "Weekday | UC Code (Name) (Class Code) | Class Time (Duration) | Type" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (const auto &p : schedule_) {
        UC uc = p.first;
        Lesson l = p.second;
        cout << NumToWeekday[l.getWeekday()] << " | ";
        cout << uc.getUCCode() <<" (" << UcCodeToName[uc.getUCCode()] << ")" << " (" << uc.getClassCode() << ") | ";
        cout << toTime(l.getStartHour()) << " hours";
        if (l.getDuration() == 1.0){
            cout << " -> " << toTime(l.getStartHour() + l.getDuration()) << " hours " << "(" << toTime(l.getDuration()) << " hour" << ")"  "| " << l.getType() << endl;
        }
        else{
            cout << " -> " << toTime(l.getStartHour() + l.getDuration()) << " hours " << "(" << toTime(l.getDuration()) << " hours" << ")"  "| " << l.getType() << endl;
        }
    }

    cout << "--------------------------------------------------------------------" << endl;
}

std::string Schedule::toTime(float hour) {
    int hrs = (int) hour;
    int mins = (int) ((hour-hrs)*60);
    if (mins > 10){
        return to_string(hrs) + ":" + to_string(mins);
    }
    else{
        return to_string(hrs) + ":" + "0" + to_string(mins);
    }
}





