cmake_minimum_required(VERSION 3.18)
project(eigen_tutorial)

set(CMAKE_CXX_STANDARD 14)

include_directories(~/dev/libs/eigen-3.3.7/_install/share/eigen3)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(eigen_tutorial main.cpp)
add_executable(review_question_1_2_1_14 review_question_1.2.1.14.cpp)

target_link_libraries(eigen_tutorial Eigen3::Eigen)
target_link_libraries(review_question_1_2_1_14 Eigen3::Eigen)
