#ifndef PROJECT_LESSON_H
#define PROJECT_LESSON_H
#include <string>
#include "UC.h"


class Lesson {

public:
    Lesson();
    Lesson(int weekday, float duration, float start_hour, std::string type);
    Lesson(int weekday, float duration, float start_hour, std::string type, UC uc);
    UC getUc() const;
    void setUc(UC uc);

    int getWeekday() const;
    float getDuration() const;
    float getStartHour() const;
    std::string getType() const;
    bool Coincide_T(const Lesson Lesson) const;

private:
    float start_hour_;
    float duration_;
    int weekday_;
    std::string type_;
    UC uc_;
};


#endif //PROJECT_LESSON_H
