cmake_minimum_required(VERSION 3.18)
project(1_2_3_9_col_row_matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(~/dev/libs/eigen-3.3.7/_install/share/eigen3)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(1_2_3_9_col_row_matrix main.cpp)
target_link_libraries(1_2_3_9_col_row_matrix Eigen3::Eigen)