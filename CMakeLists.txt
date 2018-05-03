cmake_minimum_required(VERSION 3.10)
project(final_project_abhitekula)

set(CMAKE_CXX_STANDARD 11)

include_directories(Test/)

add_executable(final_project_abhitekula_tests
        Test/tank_trouble_tests.cpp)
