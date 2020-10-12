# Setup Eigen with CMakeLists.txt
See https://sites.google.com/site/alexeyvakimov/mini-tutorials/programming-boost-python-c/cmake-tutorial for more details.

1. [Download](https://gitlab.com/libeigen/eigen/-/releases) and unzip Eigen to a global directory `EigenDir`, e.g. `~/dev/libs/eigen-x.x.x`.
2. Add following line right after `project(Eigen3)` in `<EigenDir>/CMakeLists.txt`: `set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/_install)`.
3. build and install the eigen library (in `<EigenDir>`):
```shell script
mkdir _build
cd _build
cmake ..
make
make install
```
4. Add following lines to your project's CMakeLists.txt file:
```cmake
cmake_minimum_required(VERSION 3.18)
project(project_name)

set(CMAKE_CXX_STANDARD 14)

include_directories(<EigenDir>/_install/share/eigen3)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(project_name main.cpp)
target_link_libraries(project_name Eigen3::Eigen)
```