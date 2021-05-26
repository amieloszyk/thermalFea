cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)

set(polyFea_include ${CMAKE_CURRENT_SOURCE_DIR}/../../include/polySource)
set(include
    ${polyFea_include}/oneDimPolyClass.hpp
    ${polyFea_include}/twoDimPolyClass.hpp
    )

set(source
    oneDimPoly.cpp
    twoDimPoly.cpp
    )

add_library(polySource STATIC ${include} ${source})

target_include_directories(polySource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
