#ifndef PROJECT_LESSON_H
#define PROJECT_LESSON_H
#include <string>


class Lesson {

public:
    Lesson();
    Lesson(int weekday, float duration, float start_hour, std::string type);

    int getWeekday() const;
    float getDuration() const;
    float getStartHour() const;
    std::string getType() const;
    bool Coincide_T(const Lesson& Lesson) const;
    bool operator<(Lesson a) const;
private:
    float start_hour_;
    float duration_;
    int weekday_;
    std::string type_;
};


#endif //PROJECT_LESSON_H
