cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(model_generator)

#find_package(PCL 1.7 REQUIRED)

#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

add_executable (model_generator src/generator.cpp)
add_executable (model_generator_ver2 src/generator_ver2.cpp)
#target_link_libraries (greedy_projection ${PCL_LIBRARIES})

