#ifndef PROJECT_LESSON_H
#define PROJECT_LESSON_H
#include <string>

class Lesson {

public:
    Lesson(int i, float i1, float i2, std::string string);

private:
    float start_hour_;
    float duration_;
    int weekday_;
    std::string type_;

};


#endif //PROJECT_LESSON_H
