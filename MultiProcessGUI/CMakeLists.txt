cmake_minimum_required(VERSION 3.10)

find_package(Qt5 5.9 COMPONENTS REQUIRED Core Gui Widgets Network)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ChildWindow)
add_subdirectory(ParentWindow)
