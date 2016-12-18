cmake_minimum_required(VERSION 2.6)
project(SC_project_crystal_growth_KMC)

find_package(Boost)
link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS_RELEASE "-C0")
set(SOURCE_FILES main.cpp main.h problem_space/problem_space.cpp problem_space/problem_space.h problem_space/cell/cell.cpp problem_space/cell/cell.h problem_space/cell/coordinate.h problem_space/cell/neighbor.h problem_space/Surface.h KMC.cpp KMC.h global_functions.cpp memory_func.cpp)
add_executable(SC_porject_crystal_growth_KMC ${SOURCE_FILES})
add_custom_command(TARGET SC_porject_crystal_growth_KMC POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/visualization $<TARGET_FILE_DIR:SC_porject_crystal_growth_KMC>/visualization)

add_custom_command(TARGET SC_porject_crystal_growth_KMC POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/initialization_data $<TARGET_FILE_DIR:SC_porject_crystal_growth_KMC>)

add_custom_target(build-time-make-directory PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${visualization})