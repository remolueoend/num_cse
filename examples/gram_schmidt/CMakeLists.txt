cmake_minimum_required(VERSION 3.18)
project(gram_schmidt)

set(CMAKE_CXX_STANDARD 14)

include_directories(~/dev/libs/eigen-3.3.7/_install/share/eigen3)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(gram_schmidt main.cpp)
target_link_libraries(gram_schmidt Eigen3::Eigen)