#ifndef PROJECT_SCHEDULE_H
#define PROJECT_SCHEDULE_H
#include <string>

class Schedule {
    public:
    Schedule();
    void setschedule();
    void getschedule();



    private:
    int start_hour_;
    int duration_;
    int day_;
    std::string uc_;



};


#endif
