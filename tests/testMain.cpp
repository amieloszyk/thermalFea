#include "testPolyArray.cpp"
#include "testSolver.cpp"
#include "testElementClasses.cpp"
#include "oneDimPatchTest.cpp"

#include <thermalFea/mathUtils.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
    //testElementMain(); // testElementClasses.cpp
    //patchMain(); //oneDimPatchTest.cpp
    // utilities::placeHolder();

    for (int idx = 1; idx < argc; ++idx) {
        if (strcmp(argv[idx], "testPolyArray") == 0){
            testPolyArray();
        }
        if (strcmp(argv[idx], "testSolver") == 0){
            testSolver();
        }
        if (strcmp(argv[idx], "testGeneralElements") == 0){
            testGeneralElements();
        }
        if (strcmp(argv[idx], "testXyLinearThermalMeloshElement") == 0){
            testXyLinearThermalMeloshElement();
        }
        if (strcmp(argv[idx], "testXyCstThermalTriElement") == 0){
            testXyCstThermalTriElement();
        }
        if (strcmp(argv[idx], "slideOneElementMeshTest") == 0){
            slideOneElementMeshTest();
        }
        if (strcmp(argv[idx], "oneElementMeshTest") == 0){
            oneElementMeshTest();
        }
        if (strcmp(argv[idx], "threeElementMeshTest") == 0){
            threeElementMeshTest();
        }
        if (strcmp(argv[idx], "nineElementMeshTest") == 0){
            nineElementMeshTest();
        }
        if (strcmp(argv[idx], "threeCstElementMeshTest") == 0){
            threeCstElementMeshTest();
        }
    }
}