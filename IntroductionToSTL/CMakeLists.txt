cmake_minimum_required(VERSION 3.1)
project(Algo/IntroductionToSTL)

set(CMAKE_CXX_STANDARD 14)

add_executable(set_tutorial ${HEADER_FILES} set_tutorial.cpp)
add_executable(multiset_tutorial ${HEADER_FILES} multiset_tutorial.cpp)