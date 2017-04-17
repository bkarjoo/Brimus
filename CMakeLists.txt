cmake_minimum_required(VERSION 3.6)
project(Brimus)

add_definitions(-std=gnu++14)

#set(BOOST_ROOT /Users/SuperMac/devel/cpp/boost_1_63_0/build)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} C:/Users/b.karjoo/Documents/boost_1_63_0/lib64-msvc-14.0)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /Users/SuperMac/devel/cpp/boost_1_63_0/build/lib)
set(Boost_INCLUDE_DIR C:/Users/b.karjoo/Documents/boost_1_63_0)
#set(Boost_INCLUDE_DIR /Users/SuperMac/devel/cpp/boost_1_63_0/build/include)
set(BOOST_LIBRARYDIR C:/Users/b.karjoo/Documents/boost_1_63_0/lib64-msvc-14.0)
#set(BOOST_LIBRARYDIR /Users/SuperMac/devel/cpp/boost_1_63_0/build/lib)
set (Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.63.0 COMPONENTS program_options system thread REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(Brimus_run ${SOURCE_FILES})

include_directories(${Boost_INCLUDE_DIR})
include_directories(Brimus)

#link_directories(${Boost_LIBRARYDIR})

add_subdirectory(Brimus)
add_subdirectory(Brimus-Test)

#target_link_libraries(Brimus_run Brimus)
target_link_libraries(Brimus_run Brimus  ${Boost_LIBRARIES})
