cmake_minimum_required(VERSION 3.1)
project(Algo/IntroductionToSTL)

set(CMAKE_CXX_STANDARD 14)

add_executable(gcd_segment_tree ${HEADER_FILES} gcd_segment_tree.cpp)
add_executable(sum_segment_tree_advanced ${HEADER_FILES} sum_segment_tree_advanced.cpp)
add_executable(xor_segment_tree ${HEADER_FILES} xor_segment_tree.cpp)