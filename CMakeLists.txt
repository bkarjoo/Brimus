cmake_minimum_required(VERSION 3.6)
project(Brimus)

add_definitions(-std=gnu++14)

set(Boost_INCLUDE_DIR C:/Users/b.karjoo/Documents/boost_1_63_0)
set(Boost_LIBRARY_DIR C:/Users/b.karjoo/Documents/boost_1_63_0/lib64-msvc-14.0)
set (Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.63.0 COMPONENTS date_time)

set(SOURCE_FILES main.cpp)
add_executable(Brimus_run ${SOURCE_FILES})

include_directories(${Boost_INCLUDE_DIR})
include_directories(Brimus)

link_directories(${Boost_LIBRARY_DIR})

add_subdirectory(Brimus)
add_subdirectory(Brimus-Test)

#target_link_libraries(Brimus_run Brimus)
target_link_libraries(Brimus_run Brimus  ${Boost_LIBRARIES})
