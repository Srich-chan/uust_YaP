cmake_minimum_required(VERSION 3.31)
project(main_cmake)

set(CMAKE_CXX_STANDARD 20)


############ 2nd_course

#add_executable(lab0 "YaP/2nd_course/Complex.cpp")
add_executable(lab1
        YaP/2nd_course/lab1/Classes.h
        YaP/2nd_course/lab1/Classes.cpp
        YaP/2nd_course/lab1/main.cpp
)
