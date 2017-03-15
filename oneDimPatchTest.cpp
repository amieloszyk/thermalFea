/*
All of these cases are of a 1-D problem with a heat flux of -1000 on the right
side and a set temperature of 100 on the left and a conductivity of 10 and a 
width of 3
*/

#include <iostream>
#include <vector>
#include "meshClasses.cpp"

void printMatrix(std::vector< std::vector< double > > matrixToPrint) { 

    for (int rowIdx=0; rowIdx < matrixToPrint.size(); rowIdx++) {
        for (int colIdx=0; colIdx < matrixToPrint[rowIdx].size(); colIdx++) {
            std::cout << matrixToPrint[rowIdx][colIdx] << ", ";
        };
        std::cout << std::endl;
    };
    std::cout << std::endl;
};

void printMatrix(std::vector< double >  matrixToPrint) { 

    for (int rowIdx=0; rowIdx < matrixToPrint.size(); rowIdx++) {
        std::cout << matrixToPrint[rowIdx];
        std::cout << std::endl;
    };
    std::cout << std::endl;
};

void slideOneElementMeshTest() {

    std::vector< double > dummyCoord(2);
    std::vector< std::vector< double > > dummyNodeCoords;
    dummyCoord[0] = 0.0;
    dummyCoord[1] = 0.0;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = 2.0;
    dummyCoord[1] = 0.0;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = 2.0;
    dummyCoord[1] = 1.0;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = 0.0;
    dummyCoord[1] = 1.0;
    dummyNodeCoords.push_back(dummyCoord);

    std::vector< std::vector< double > > condMatrix(2, std::vector<double>(2,0.0));
    condMatrix[0][0] = 4.56;
    condMatrix[1][1] = 3.8;
    
    //XyLinearThermalMeloshElement elementOne;
    TwoDimThermalElement *elementOne = new XyLinearThermalMeloshElement();
    elementOne->setNodeCoords(dummyNodeCoords);
    elementOne->setMatMatrix(condMatrix);
    elementOne->setElemThick(1.3);

    std::vector< int > dummyGlobElementMap(4);
    dummyGlobElementMap[0] = 1;
    dummyGlobElementMap[1] = 2;
    dummyGlobElementMap[2] = 3;
    dummyGlobElementMap[3] = 4;

    TwoDimMeshOfElements patchMesh(4, 1);
    patchMesh.addExistingElement(1, elementOne, dummyGlobElementMap);

    // This is not giving the right answer because the first node location is stored incorrectly in the mesh
    std::vector< std::vector< double > > globStiffMat = patchMesh.getRawGlobStiffMatrix();
    std::cout << "Calculated (in mesh) K-matrix:" << std::endl;
    printMatrix(globStiffMat);

    // This is giving the right answer
    XyLinearThermalMeloshElement slideElement;
    slideElement.setNodeCoords(dummyNodeCoords);
    slideElement.setMatMatrix(condMatrix);
    slideElement.setElemThick(1.3);
    std::vector< std::vector< double > > singleElementStiff = slideElement.getStiffnessMatrix();
    std::cout << "Calculated (single element) K-matrix:" << std::endl;
    printMatrix(singleElementStiff);

    std::cout << "Known K-matrix:" << std::endl;
    std::cout << "4.2813, 0.6587, -2.1407, -2.7993" << std::endl;
    std::cout << "0.6587, 4.2813, -2.7993, -2.1407" << std::endl;
    std::cout << "-2.1407, -2.7993, 4.2813, 0.6587" << std::endl;
    std::cout << "-2.7993, -2.1407, 0.6587, 4.2813" << std::endl;
    std::cout << std::endl;

};

void oneElementMeshTest() {

    std::vector< double > dummyCoord(2);
    std::vector< std::vector< double > > dummyNodeCoords;
    dummyCoord[0] = 0.0;
    dummyCoord[1] = 0.0;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = 3.0;
    dummyCoord[1] = 0.0;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = 3.0;
    dummyCoord[1] = 1.0;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = 0.0;
    dummyCoord[1] = 1.0;
    dummyNodeCoords.push_back(dummyCoord);

    //XyLinearThermalMeloshElement elementOne;
    TwoDimThermalElement *elementOne = new XyLinearThermalMeloshElement();
    elementOne->setNodeCoords(dummyNodeCoords);
    elementOne->setIsoThermCond(10.0);
    elementOne->setElemThick(1.0);

    std::vector< int > dummyGlobElementMap(4);
    dummyGlobElementMap[0] = 1;
    dummyGlobElementMap[1] = 2;
    dummyGlobElementMap[2] = 3;
    dummyGlobElementMap[3] = 4;

    TwoDimMeshOfElements patchMesh(4, 1);
    patchMesh.addExistingElement(1, elementOne, dummyGlobElementMap);

    int surfOneId = patchMesh.makeNewSurf();
    patchMesh.addLocSurfToMesh(surfOneId, 1, 2);
    patchMesh.setScalarSurfFlux(surfOneId, -1000.0);

    int surfTwoId = patchMesh.makeNewSurf();
    patchMesh.addLocSurfToMesh(surfTwoId, 1, 3);
    patchMesh.setScalarSurfFlux(surfTwoId, 1000.0);
    
    std::vector< std::vector< double > > rawStiffMat = patchMesh.getRawGlobStiffMatrix();
    std::vector< double > rawLoadVect = patchMesh.getRawGlobLoadVect();

    std::cout << "Raw K-Matrix:" << std::endl;
    printMatrix(rawStiffMat);
    std::cout << "Raw Load Vector:" << std::endl;
    printMatrix(rawLoadVect);

    std::vector< int > nodeWithSetVal(1,2);
    std::vector< double > setNodeVal(1,100.0);
    patchMesh.setFixedNodeVals(nodeWithSetVal, setNodeVal);

    std::vector< std::vector< double > > solveStiffMat = patchMesh.getStiffMatToSolve();
    std::vector< double > solveLoadVect = patchMesh.getLoadVectToSolve();
    
    std::cout << "Solvable K-Matrix:" << std::endl;
    printMatrix(solveStiffMat);
    std::cout << "Solvable Load Vector:" << std::endl;
    printMatrix(solveLoadVect);

};

void threeElementMeshTest() {};

void nineElementMeshTest() {
/*
    void elementOne = XyLinearThermalMeloshElement();
    elementOne->globalCoord[0] = {0.0,0.0};
    elementOne->globalCoord[1] = {1.0,0.0};
    elementOne->globalCoord[2] = {1.0,1.0};
    elementOne->globalCoord[3] = {0.0,1.0};
    elementOne->surfFlux[0] = 0.0;
    elementOne.setLocNodeTemp(0, 100.0);
    elementOne.setLocNodeTemp(3, 100.0);
    elementOne.setIsoThemCond(10.0);
    elementOne.setGlobalNodeNumb(1,1);
    elementOne.setGlobalNodeNumb(2,2);
    elementOne.setGlobalNodeNumb(3,6);
    elementOne.setGlobalNodeNumb(4,5);

    void elementTwo = XyLinearThermalMeloshElement();
    elementTwo->globalCoord[0] = {1.0,0.0};
    elementTwo->globalCoord[1] = {2.0,0.0};
    elementTwo->globalCoord[2] = {2.0,1.0};
    elementTwo->globalCoord[3] = {1.0,1.0};
    elementTwo->surfFlux[0] = 0.0;
    elementTwo.setIsoThemCond(10.0);
    elementTwo.setGlobalNodeNumb(1,2);
    elementTwo.setGlobalNodeNumb(2,3);
    elementTwo.setGlobalNodeNumb(3,7);
    elementTwo.setGlobalNodeNumb(4,6);

    void elementThree = XyLinearThermalMeloshElement();
    elementThree->globalCoord[0] = {2.0,0.0};
    elementThree->globalCoord[1] = {3.0,0.0};
    elementThree->globalCoord[2] = {3.0,1.0};
    elementThree->globalCoord[3] = {2.0,1.0};
    elementThree->surfFlux[0] = 0.0;
    elementThree->surfFlux[1] = -1000.0;
    elementThree.setIsoThemCond(10.0);
    elementThree.setGlobalNodeNumb(1,3);
    elementThree.setGlobalNodeNumb(2,4);
    elementThree.setGlobalNodeNumb(3,8);
    elementThree.setGlobalNodeNumb(4,7);

    void elementFour = XyLinearThermalMeloshElement();
    elementFour->globalCoord[0] = {0.0,1.0};
    elementFour->globalCoord[1] = {1.0,1.0};
    elementFour->globalCoord[2] = {1.0,2.0};
    elementFour->globalCoord[3] = {0.0,2.0};
    elementFour.setLocNodeTemp(0, 100.0);
    elementFour.setLocNodeTemp(3, 100.0);
    elementFour.setIsoThemCond(10.0);
    elementFour.setGlobalNodeNumb(1,5);
    elementFour.setGlobalNodeNumb(2,6);
    elementFour.setGlobalNodeNumb(3,10);
    elementFour.setGlobalNodeNumb(4,9);

    void elementFive = XyLinearThermalMeloshElement();
    elementFive->globalCoord[0] = {1.0,1.0};
    elementFive->globalCoord[1] = {2.0,1.0};
    elementFive->globalCoord[2] = {2.0,2.0};
    elementFive->globalCoord[3] = {1.0,2.0};
    elementFive.setIsoThemCond(810.0;
    elementFive.setGlobalNodeNumb(1,6);
    elementFive.setGlobalNodeNumb(2,7);
    elementFive.setGlobalNodeNumb(3,11);
    elementFive.setGlobalNodeNumb(4,12);

    void elementSix = XyLinearThermalMeloshElement();
    elementSix->globalCoord[0] = {2.0,1.0};
    elementSix->globalCoord[1] = {3.0,1.0};
    elementSix->globalCoord[2] = {3.0,2.0};
    elementSix->globalCoord[3] = {2.0,2.0};
    elementSix->surfFlux[1] = -1000.0;
    elementSix.setIsoThemCond(10.0);
    elementSix.setGlobalNodeNumb(1,7);
    elementSix.setGlobalNodeNumb(2,8);
    elementSix.setGlobalNodeNumb(3,12);
    elementSix.setGlobalNodeNumb(4,11);

    void elementSeven = XyLinearThermalMeloshElement();
    elementSeven->globalCoord[0] = {0.0,2.0};
    elementSeven->globalCoord[1] = {1.0,2.0};
    elementSeven->globalCoord[2] = {1.0,3.0};
    elementSeven->globalCoord[3] = {0.0,3.0};
    elementSeven->surfFlux[2] = 0.0;
    elementSeven.setLocNodeTemp(0, 100.0);
    elementSeven.setLocNodeTemp(3, 100.0);
    elementSeven.setIsoThemCond(10.0);
    elementSeven.setGlobalNodeNumb(1,9);
    elementSeven.setGlobalNodeNumb(2,10);
    elementSeven.setGlobalNodeNumb(3,14);
    elementSeven.setGlobalNodeNumb(4,13);

    void elementEight = XyLinearThermalMeloshElement();
    elementEight->globalCoord[0] = {1.0,2.0};
    elementEight->globalCoord[1] = {2.0,2.0};
    elementEight->globalCoord[2] = {2.0,3.0};
    elementEight->globalCoord[3] = {1.0,3.0};
    elementEight->surfFlux[2] = 0.0;
    elementEight.setIsoThemCond(10.0);
    elementEight.setGlobalNodeNumb(1,10);
    elementEight.setGlobalNodeNumb(2,11);
    elementEight.setGlobalNodeNumb(3,15);
    elementEight.setGlobalNodeNumb(4,14);

    void elementNine = XyLinearThermalMeloshElement();
    elementNine->globalCoord[0] = {2.0,2.0};
    elementNine->globalCoord[1] = {3.0,2.0};
    elementNine->globalCoord[2] = {3.0,3.0};
    elementNine->globalCoord[3] = {2.0,3.0};
    elementNine->surfFlux[1] = -1000.0;
    elementNine->surfFlux[2] = 0.0;
    elementNine.setIsoThemCond(10.0);
    elementNine.setGlobalNodeNumb(1,11);
    elementNine.setGlobalNodeNumb(2,12);
    elementNine.setGlobalNodeNumb(3,16);
    elementNine.setGlobalNodeNumb(4,15);


    TwoDimMeshOfElements patchMesh;
    //elementId = patchMesh.addElement(elementObj,nodeOneGlobNumb,nodeTwoGlobNumb,nodeThreeGlobNumb,nodeFourGlobNumb)
    int elemOneId = patchMesh.addExistingElement(elementOne,{1,2,5,6});
    int elemTwoId = patchMesh.addExistingElement(elementTwo,{2,3,7,6});
    int elemThreeId = patchMesh.addExistingElement(elementThree,{3,4,8,7});
    int elemFourId = patchMesh.addExistingElement(elementFour,{5,6,10,9});
    int elemFiveId = patchMesh.addExistingElement(elementFive,{6,7,11,10});
    int elemSixId = patchMesh.addExistingElement(elementSix,{7,8,12,11});
    int elemSevenId = patchMesh.addExistingElement(elementSeven,{9,10,14,13});
    int elemEightId = patchMesh.addExistingElement(elementEight,{10,11,15,14});
    int elemNineId = patchMesh.addExistingElement(elementNine,{11,12,16,15});

    //patchMesh.makeSurf(surfId)
    int surfOneId = patchMesh.makeNewSurf();
    //patchMesh.addLocSurfToMesh(surfId,elemId,surfId)
    patchMesh.addLocSurfToMesh(surfOneId,elemOneId,1);
    patchMesh.addLocSurfToMesh(surfOneId,elemTwoId,1);
    patchMesh.addLocSurfToMesh(surfOneId,elemThreeId,1);

    int surfTwoId = patchMesh.makeSurf();
    patchMesh.addLocSurfToMesh(surfTwoId,elemThreeId,2);
    patchMesh.addLocSurfToMesh(surfTwoId,elemFourId,2);
    patchMesh.addLocSurfToMesh(surfTwoId,elemFiveId,2);

    int surfThreeId = patchMesh.makeSurf();
    patchMesh.addLocSurfToMesh(surfThreeId,elemSevenId,3);
    patchMesh.addLocSurfToMesh(surfThreeId,elemEightId,3);
    patchMesh.addLocSurfToMesh(surfThreeId,elemNineId,3);

    int surfFourId = patchMesh.makeSurf();
    patchMesh.addLocSurfToMesh(surfFourId,elemOneId,4);
    patchMesh.addLocSurfToMesh(surfFourId,elemFourId,4);
    patchMesh.addLocSurfToMesh(surfFourId,elemSevenId,4);

    //patchMesh.setFlux(int surfId, float fluxVal)
    patchMesh.setSurfFlux(surfOneId, 0.0);
    patchMesh.setSurfFlux(surfTwoId, -1000.0);
    patchMesh.setSurfFlux(surfThreeId, 0.0);

    //patchMesh.setSurfTemp(int surfId, float tempVal)
    patchMesh.setSurfTemp(surfFourId, 100.0);

    // have these return values, but set internal matrices
    std::vector<std::vector<double>> globStiffMatrix = patchMesh.getStiffMatrix();
    std::vector<double> globReactVect = patchMesh.getLoadVect();
    std::vector<double> globNodeVals = patchMesh.solveNodeVals();


    */
};


void patchMain() {
    slideOneElementMeshTest();
    oneElementMeshTest();
};
