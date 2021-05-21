cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)

set(source
    testMain.cpp
    )

add_executable(thermalFeaTests ${source})

enable_testing()
add_test(NAME "Polynomial array test" COMMAND thermalFeaTests testPolyArray)
add_test(NAME "Solver test" COMMAND thermalFeaTests testSolver)
add_test(NAME "General element test" COMMAND thermalFeaTests testGeneralElements)
add_test(NAME "XY Melosh element test" COMMAND thermalFeaTests testXyLinearThermalMeloshElement)
add_test(NAME "XT CST element test" COMMAND thermalFeaTests testXyCstThermalTriElement)
add_test(NAME "Slide #1 element patch test" COMMAND thermalFeaTests slideOneElementMeshTest)
add_test(NAME "Single element patch test" COMMAND thermalFeaTests oneElementMeshTest)
add_test(NAME "Three element rectangular patch test" COMMAND thermalFeaTests threeElementMeshTest)
add_test(NAME "Nine element rectangular patch test" COMMAND thermalFeaTests nineElementMeshTest)
add_test(NAME "Three element triangular patch test" COMMAND thermalFeaTests threeCstElementMeshTest)

target_link_libraries(thermalFeaTests PRIVATE thermalFea)
