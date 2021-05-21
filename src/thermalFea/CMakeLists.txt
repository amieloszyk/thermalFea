cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)

set(thermFea_include ${CMAKE_CURRENT_SOURCE_DIR}/../../include/thermalFea)
set(include
    ${thermFea_include}/elementClasses.hpp
    ${thermFea_include}/mathUtils.hpp
    ${thermFea_include}/meshClasses.hpp
    ${thermFea_include}/polyArray.hpp
    ${thermFea_include}/solverClasses.hpp
    )

set(source
    elementClasses.cpp
    mathUtils.cpp
    meshClasses.cpp
    polyArray.cpp
    solverClasses.cpp
    )

add_library(thermalFea STATIC ${include} ${source})

target_link_libraries(thermalFea PUBLIC polySource)

target_include_directories(thermalFea PUBLIC ${CMAKE_SOURCE_DIR}/include)
