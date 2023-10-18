cmake_minimum_required(VERSION 3.26)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp
        Schedule.cpp
        Schedule.h
        Student.cpp
        Student.h
        Lesson.cpp
        Lesson.h
        UC.cpp
        UC.h
        Data.cpp
        Data.h
)
