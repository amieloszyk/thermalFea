/*
All of these cases are of a 1-D problem with a heat flux of -1000 on the right
side and a set temperature of 100 on the left and a conductivity of 10 and a 
width of 3
*/
#include <thermalFea/meshClasses.hpp>
#include <thermalFea/solverClasses.hpp>

#include <iostream>
#include <vector>

void printMatrix(std::vector< std::vector< double > > matrixToPrint) { 
    // TODO: Move this to a more generally accesssible location

    std::cout << "["  << std::endl;
    for (int rowIdx=0; rowIdx < matrixToPrint.size(); rowIdx++) {
        std::cout << "[";
        for (int colIdx=0; colIdx < matrixToPrint[rowIdx].size(); colIdx++) {
            std::cout << matrixToPrint[rowIdx][colIdx] << ", ";
        };
        std::cout << "],";
        std::cout << std::endl;
    };
    std::cout << "]";
    std::cout << std::endl;
};

void printMatrix(std::vector< std::vector< int > > matrixToPrint) { 
    // TODO: Move this to a more generally accesssible location

    std::cout << "["  << std::endl;
    for (int rowIdx=0; rowIdx < matrixToPrint.size(); rowIdx++) {
        std::cout << "[";
        for (int colIdx=0; colIdx < matrixToPrint[rowIdx].size(); colIdx++) {
            std::cout << matrixToPrint[rowIdx][colIdx] << ", ";
        };
        std::cout << "],";
        std::cout << std::endl;
    };
    std::cout << "]";
    std::cout << std::endl;
};

void printMatrix(std::vector< double >  matrixToPrint) { 
    // TODO: Move this to a more generally accesssible location

    std::cout << "[";
    for (int rowIdx=0; rowIdx < matrixToPrint.size(); rowIdx++) {
        std::cout << matrixToPrint[rowIdx] << ", ";
        std::cout << std::endl;
    };
    std::cout << "]";
    std::cout << std::endl;
};

void printMatrix(std::vector< int >  matrixToPrint) { 
    // TODO: Move this to a more generally accesssible location

    std::cout << "[";
    for (int rowIdx=0; rowIdx < matrixToPrint.size(); rowIdx++) {
        std::cout << matrixToPrint[rowIdx] << ", ";
        std::cout << std::endl;
    };
    std::cout << "]";
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
    // TODO: There should also be a method to add a new element

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

}

void oneElementMeshTest() {

    double xStart = 0.0;
    double xEnd = 1.0;
    double yStart = 0.0;
    double yEnd = 1.0;
    double thick = 1.0;
    double isoThermCond = 10.0;

    std::vector< double > dummyCoord(2);
    std::vector< std::vector< double > > dummyNodeCoords;
    dummyCoord[0] = xStart;
    dummyCoord[1] = yStart;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = xEnd;
    dummyCoord[1] = yStart;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = xEnd;
    dummyCoord[1] = yEnd;
    dummyNodeCoords.push_back(dummyCoord);
    dummyCoord[0] = xStart;
    dummyCoord[1] = yEnd;
    dummyNodeCoords.push_back(dummyCoord);

    //XyLinearThermalMeloshElement elementOne;
    TwoDimThermalElement *elementOne = new XyLinearThermalMeloshElement();
    elementOne->setNodeCoords(dummyNodeCoords);
    elementOne->setIsoThermCond(isoThermCond);
    elementOne->setElemThick(thick);

    std::vector< int > dummyGlobElementMap(4);
    dummyGlobElementMap[0] = 1;
    dummyGlobElementMap[1] = 2;
    dummyGlobElementMap[2] = 3;
    dummyGlobElementMap[3] = 4;

    TwoDimMeshOfElements patchMesh(4, 1);
    patchMesh.addExistingElement(1, elementOne, dummyGlobElementMap);

    // TODO: There should also be an internal method to add a new surface
    int surfOneId = patchMesh.makeNewSurf();
    patchMesh.addLocSurfToMesh(surfOneId, 1, 2);
    patchMesh.setScalarSurfFlux(surfOneId, -1000.0);

    int surfTwoId = patchMesh.makeNewSurf();
    patchMesh.addLocSurfToMesh(surfTwoId, 1, 4);
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

    // TODO: These steps should be integrated into an internal method
    std::vector< std::vector< double > > solveStiffMat = patchMesh.getStiffMatToSolve();
    std::vector< double > solveLoadVect = patchMesh.getLoadVectToSolve();
    std::vector< double > calcNodeTemps = gaussianElimSolve(solveStiffMat,solveLoadVect);
    
    std::cout << "Solvable K-Matrix:" << std::endl;
    printMatrix(solveStiffMat);
    std::cout << "Solvable Load Vector:" << std::endl;
    printMatrix(solveLoadVect);
    std::cout << "Calculated Node Values:" << std::endl;
    printMatrix(calcNodeTemps);

}

void threeElementMeshTest() {
    
/*
             5           6           7           8
       100K  +-----------+-----------+-----------+
            <-|           |           |           |<-
            <-|           |           |           |<-
 1000 W/m2  <-|     1     |     2     |     3     |<- 1000 W/m2
            <-| k=10W/m-K | k=10W/m-K | k=10W/m-K |<-
            <-|           |           |           |<-
             +-----------+-----------+-----------+
             1           2           3           4

*/

    double xStart = 0.0;
    double xEnd = 3.0;
    double yStart = 0.0;
    double yEnd = 1.0;
    int numbElemX = 3;
    int numbElemY = 1;
    double xStep = (xEnd-xStart)/double(numbElemX);
    double yStep = (yEnd-yStart)/double(numbElemY);
    double thick = 1.0;
    double isoThermCond = 10.0;

    // The code immediately below can likely be generalized into a function that returns a mesh
    int elemCounter = 0;
    int nodeCounter = 0;
    double xLeft = 0.0;
    double xRight = 0.0;
    double yBot = 0.0;
    double yTop = 0.0;
    std::vector< std::vector< double > > dummyNodeCoords(4,std::vector< double >(2,0.0));
    std::vector< int > dummyGlobNodeMap(4);
    
    // TwoDimMeshOfElements rectMesh((numbElemX+1)*2, numbElemX);
    TwoDimMeshOfElements rectMesh;
    for (int yIdx = 1; yIdx <= numbElemY; yIdx++) {
        
        yTop += yStep;

        for (int xIdx = 1; xIdx <= numbElemX; xIdx++) {

            xRight += xStep;
            

            elemCounter++;

            dummyNodeCoords[0][0] = xLeft;
            dummyNodeCoords[0][1] = yBot;
            dummyNodeCoords[1][0] = xRight;
            dummyNodeCoords[1][1] = yBot;
            dummyNodeCoords[2][0] = xRight;
            dummyNodeCoords[2][1] = yTop;
            dummyNodeCoords[3][0] = xLeft;
            dummyNodeCoords[3][1] = yTop;

            // TwoDimThermalElement *dummyElement = new XyLinearThermalMeloshElement();
            // dummyElement->setNodeCoords(dummyNodeCoords);
            // dummyElement->setIsoThermCond(isoThermCond);
            // dummyElement->setElemThick(thick);
            // rectMesh.addExistingElement(elemCounter, dummyElement, dummyGlobNodeMap);

            // std::vector< int > dummyGlobElementMap(4);
            // Not fully generalized past one row
            dummyGlobNodeMap[0] = xIdx;
            dummyGlobNodeMap[1] = xIdx+1;
            dummyGlobNodeMap[2] = numbElemX*yIdx+2+xIdx;
            dummyGlobNodeMap[3] = numbElemX*yIdx+1+xIdx;

            rectMesh.addNewElement("melosh",dummyNodeCoords,dummyGlobNodeMap);
            rectMesh.setElemThick(thick,elemCounter);
            rectMesh.setElemIsoThermCond(isoThermCond,elemCounter);

            xLeft += xStep;
        };
        yBot += yStep;
    };
    int surfOneId = rectMesh.makeNewSurf();
    rectMesh.addLocSurfToMesh(surfOneId, numbElemX, 2);
    rectMesh.setScalarSurfFlux(surfOneId, 1000.0);

    int surfTwoId = rectMesh.makeNewSurf();
    rectMesh.addLocSurfToMesh(surfTwoId, 1, 4);
    rectMesh.setScalarSurfFlux(surfTwoId, -1000.0);
    
    std::vector< int > nodeWithSetVal(2);
    nodeWithSetVal[0] = 1;
    nodeWithSetVal[1] = numbElemX+2;
    std::vector< double > setNodeVal(2,100.0);
    rectMesh.setFixedNodeVals(nodeWithSetVal, setNodeVal);

    std::vector< std::vector< double > > solveStiffMat = rectMesh.getStiffMatToSolve();
    std::vector< double > solveLoadVect = rectMesh.getLoadVectToSolve();
    std::vector< double > calcNodeTemps = gaussianElimSolve(solveStiffMat,solveLoadVect);
    
    std::vector< std::vector< double > > rawStiffMat = rectMesh.getRawGlobStiffMatrix();
    std::vector< double > rawLoadVect = rectMesh.getRawGlobLoadVect();

    std::cout << "Raw K-Matrix:" << std::endl;
    printMatrix(rawStiffMat);
    std::cout << "Raw Load Vector:" << std::endl;
    printMatrix(rawLoadVect);

    std::cout << "Solvable K-Matrix:" << std::endl;
    printMatrix(solveStiffMat);
    std::cout << "Solvable Load Vector:" << std::endl;
    printMatrix(solveLoadVect);
    std::cout << "Calculated Node Values:" << std::endl;
    printMatrix(calcNodeTemps);

}

void nineElementMeshTest() {
/*
1- D patch test with a pretty unstructured mesh
             4            7           11          13
              +-----------+-----------+-----------+
            <-|           |           |           |<-
            <-|           |           |           |<-
 1000 W/m2  <-|     1     |     2     |     6     |<- 1000 W/m2
            <-| k=10W/m-K | k=10W/m-K | k=10W/m-K |<-
            <-|           |           |           |<-
              +-----------+-----------+-----------+
            <-| 3         |  8        | 5      14 |<-
            <-|           |           |           |<-
 1000 W/m2  <-|     4     |     5     |     7     |<- 1000 W/m2
            <-| k=10W/m-K | k=10W/m-K | k=10W/m-K |<-
            <-|           |           |           |<-
              +-----------+-----------+-----------+
            <-| 2         |   9       | 12     15 |<-
            <-|           |           |           |<-
 1000 W/m2  <-|     3     |     9     |     8     |<- 1000 W/m2
            <-| k=10W/m-K | k=10W/m-K | k=10W/m-K |<-
            <-|           |           |           |<-
              +-----------+-----------+-----------+ 200K
              1           10          6           16
*/

    int numbElement = 9;
    int numbNode = 16;

    std::vector< std::vector< int >  > nodeToElemMap(9,std::vector< int >(4,0));
    nodeToElemMap[0][0] = 3;
    nodeToElemMap[0][1] = 8;
    nodeToElemMap[0][2] = 7;
    nodeToElemMap[0][3] = 4;
    nodeToElemMap[1][0] = 8;
    nodeToElemMap[1][1] = 5;
    nodeToElemMap[1][2] = 11;
    nodeToElemMap[1][3] = 7;
    nodeToElemMap[2][0] = 1;
    nodeToElemMap[2][1] = 10;
    nodeToElemMap[2][2] = 9;
    nodeToElemMap[2][3] = 2;
    nodeToElemMap[3][0] = 2;
    nodeToElemMap[3][1] = 9;
    nodeToElemMap[3][2] = 8;
    nodeToElemMap[3][3] = 3;
    nodeToElemMap[4][0] = 9;
    nodeToElemMap[4][1] = 12;
    nodeToElemMap[4][2] = 5;
    nodeToElemMap[4][3] = 8;
    nodeToElemMap[5][0] = 5;
    nodeToElemMap[5][1] = 14;
    nodeToElemMap[5][2] = 13;
    nodeToElemMap[5][3] = 11;
    nodeToElemMap[6][0] = 12;
    nodeToElemMap[6][1] = 15;
    nodeToElemMap[6][2] = 14;
    nodeToElemMap[6][3] = 5;
    nodeToElemMap[7][0] = 6;
    nodeToElemMap[7][1] = 16;
    nodeToElemMap[7][2] = 15;
    nodeToElemMap[7][3] = 12;
    nodeToElemMap[8][0] = 10;
    nodeToElemMap[8][1] = 6;
    nodeToElemMap[8][2] = 12;
    nodeToElemMap[8][3] = 9;

    double xStart = 0.0;
    double xEnd = 3.0;
    double xStep = 1.0;
    double yStart = 0.0;
    double yEnd = 3.0;
    double yStep = 1.0;

    std::vector< std::vector< double > > nodeCoords(16,std::vector< double >(2, 0.0));
    nodeCoords[0][0] = xStart;
    nodeCoords[0][1] = yStart;
    nodeCoords[1][0] = xStart;
    nodeCoords[1][1] = yStart+yStep;
    nodeCoords[2][0] = xStart;
    nodeCoords[2][1] = yStart+2.0*yStep;
    nodeCoords[3][0] = xStart;
    nodeCoords[3][1] = yEnd;
    nodeCoords[4][0] = xStart+2.0*xStep;
    nodeCoords[4][1] = yStart+2.0*yStep;
    nodeCoords[5][0] = xStart+2.0*xStep;
    nodeCoords[5][1] = yStart;
    nodeCoords[6][0] = xStart+xStep;
    nodeCoords[6][1] = yEnd;
    nodeCoords[7][0] = xStart+xStep;
    nodeCoords[7][1] = yStart+2.0*yStep;
    nodeCoords[8][0] = xStart+xStep;
    nodeCoords[8][1] = yStart+yStep;
    nodeCoords[9][0] = xStart+xStep;
    nodeCoords[9][1] = yStart;
    nodeCoords[10][0] = xStart+2.0*xStep;
    nodeCoords[10][1] = yEnd;
    nodeCoords[11][0] = xStart+2.0*xStep;
    nodeCoords[11][1] = yStart+yStep;
    nodeCoords[12][0] = xEnd;
    nodeCoords[12][1] = yEnd;
    nodeCoords[13][0] = xEnd;
    nodeCoords[13][1] = yStart+2.0*yStep;
    nodeCoords[14][0] = xEnd;
    nodeCoords[14][1] = yStart+yStep;
    nodeCoords[15][0] = xEnd;
    nodeCoords[15][1] = yStart;

    TwoDimMeshOfElements patchMesh;

    std::vector< std::vector< double > > dummyNodeCoords(4,std::vector< double >(2,0.0));
    std::vector< int > dummyNodeNumb(4);
    int dummyNodeIdx;
    double thick = 1.0;
    double isoThermCond = 10.0;
    for (int elemIdx = 0; elemIdx < numbElement; elemIdx++) {
        for (int locNode = 0; locNode < 4; locNode++){
            dummyNodeIdx = nodeToElemMap[elemIdx][locNode]-1;
            dummyNodeNumb[locNode] = nodeToElemMap[elemIdx][locNode];
            dummyNodeCoords[locNode][0] = nodeCoords[dummyNodeIdx][0];
            dummyNodeCoords[locNode][1] = nodeCoords[dummyNodeIdx][1];
        };
        
        patchMesh.addNewElement("melosh",dummyNodeCoords,dummyNodeNumb);
        patchMesh.setElemThick(thick,elemIdx+1);
        patchMesh.setElemIsoThermCond(isoThermCond,elemIdx+1);
    };

    int rightSurfIdx = patchMesh.makeNewSurf();
    patchMesh.addLocSurfToMesh(rightSurfIdx,6,2);
    patchMesh.addLocSurfToMesh(rightSurfIdx,7,2);
    patchMesh.addLocSurfToMesh(rightSurfIdx,8,2);
    patchMesh.setScalarSurfFlux(rightSurfIdx,1000.0);

    int leftSurfIdx = patchMesh.makeNewSurf();
    std::cout << "here 1" << std::endl;
    patchMesh.addLocSurfToMesh(leftSurfIdx,1,4);
    patchMesh.addLocSurfToMesh(leftSurfIdx,4,4);
    patchMesh.addLocSurfToMesh(leftSurfIdx,3,4);
    std::cout << "here 2" << std::endl;
    patchMesh.setScalarSurfFlux(leftSurfIdx,-1000.0);
    std::cout << "here 3" << std::endl;

    std::vector< int > boundaryNodes(1);
    boundaryNodes[0] = 1;
    std::vector< double > fixedNodeVal(1,100.0);
    patchMesh.setFixedNodeVals(boundaryNodes, fixedNodeVal);

    std::vector< std::vector< double > > solveStiffMat;
    std::vector< double > solveLoadVect;
    solveStiffMat = patchMesh.getStiffMatToSolve();
    solveLoadVect = patchMesh.getLoadVectToSolve();

    std::vector< double > calcNodeTemps;
    calcNodeTemps = gaussianElimSolve(solveStiffMat,solveLoadVect);
    patchMesh.setFoundNodeVals(calcNodeTemps);
    std::vector< double > nodeTemps;
    nodeTemps = patchMesh.getFoundNodeVals();

    std::cout << "Solvable K-Matrix:" << std::endl;
    printMatrix(solveStiffMat);
    std::cout << "Solvable Load Vector:" << std::endl;
    printMatrix(solveLoadVect);
    std::cout << "Calculated, Set, and Returned Node Values:" << std::endl;
    printMatrix(nodeTemps);
};

void threeCstElementMeshTest() {
    
/*
             5              4
       100K  +--------------+
           <-| \          / |<-
           <-|  -    2   -  |<-
 1000 W/m2 <-|    \     /   |<- 1000 W/m2
           <-|  1  -   -  3 |<-
           <-|      \ /     |<-
             +-------+------+
             1       2      3
k = 10 W/m-K for all
*/

    double thick = 1.0;
    double isoThermCond = 10.0;
    
    TwoDimMeshOfElements cstMesh;
    std::vector< std::vector< double > > dummyNodeCoords(3,std::vector< double >(2,0.0));
    std::vector< int > dummyGlobNodeMap(3);
    
    dummyNodeCoords[0][0] = 0.0;
    dummyNodeCoords[0][1] = 0.0;
    dummyNodeCoords[1][0] = 1.5;
    dummyNodeCoords[1][1] = 0.0;
    dummyNodeCoords[2][0] = 0.0;
    dummyNodeCoords[2][1] = 1.0;
    dummyGlobNodeMap[0] = 1;
    dummyGlobNodeMap[1] = 2;
    dummyGlobNodeMap[2] = 5;
    std::cout << "Here0\n";
    cstMesh.addNewElement("cst",dummyNodeCoords,dummyGlobNodeMap); // Error here
    std::cout << "Here1\n";
    cstMesh.setElemThick(thick,1);
    cstMesh.setElemIsoThermCond(isoThermCond,1);

    dummyNodeCoords[0][0] = 0.0;
    dummyNodeCoords[0][1] = 1.0;
    dummyNodeCoords[1][0] = 1.5;
    dummyNodeCoords[1][1] = 0.0;
    dummyNodeCoords[2][0] = 3.0;
    dummyNodeCoords[2][1] = 1.0;
    dummyGlobNodeMap[0] = 5;
    dummyGlobNodeMap[1] = 2;
    dummyGlobNodeMap[2] = 4;
    cstMesh.addNewElement("cst",dummyNodeCoords,dummyGlobNodeMap);
    cstMesh.setElemThick(thick,2);
    cstMesh.setElemIsoThermCond(isoThermCond,2);

    dummyNodeCoords[0][0] = 3.0;
    dummyNodeCoords[0][1] = 0.0;
    dummyNodeCoords[1][0] = 1.5;
    dummyNodeCoords[1][1] = 0.0;
    dummyNodeCoords[2][0] = 3.0;
    dummyNodeCoords[2][1] = 1.0;
    dummyGlobNodeMap[0] = 3;
    dummyGlobNodeMap[1] = 2;
    dummyGlobNodeMap[2] = 4;
    cstMesh.addNewElement("cst",dummyNodeCoords,dummyGlobNodeMap);
    cstMesh.setElemThick(thick,3);
    cstMesh.setElemIsoThermCond(isoThermCond,3);

    int surfOneId = cstMesh.makeNewSurf();
    cstMesh.addLocSurfToMesh(surfOneId, 3, 3);
    cstMesh.setScalarSurfFlux(surfOneId, 1000.0);

    int surfTwoId = cstMesh.makeNewSurf();
    cstMesh.addLocSurfToMesh(surfTwoId, 1, 3);
    cstMesh.setScalarSurfFlux(surfTwoId, -1000.0);

    std::cout << "Here2\n";
    
    std::vector< int > nodeWithSetVal(2);
    nodeWithSetVal[0] = 1;
    nodeWithSetVal[1] = 5;
    std::vector< double > setNodeVal(2,100.0);
    cstMesh.setFixedNodeVals(nodeWithSetVal, setNodeVal);

    std::cout << "Here3\n";

    std::vector< std::vector< double > > solveStiffMat = cstMesh.getStiffMatToSolve();
    std::cout << "Here4\n";
    std::vector< double > solveLoadVect = cstMesh.getLoadVectToSolve();
    std::cout << "Here5\n";
    std::vector< double > calcNodeTemps = gaussianElimSolve(solveStiffMat,solveLoadVect);
    
    std::cout << "Here6\n";

    std::vector< std::vector< double > > rawStiffMat = cstMesh.getRawGlobStiffMatrix();
    std::vector< double > rawLoadVect = cstMesh.getRawGlobLoadVect();

    std::cout << "Here5\n";

    std::cout << "Raw K-Matrix:" << std::endl;
    printMatrix(rawStiffMat);
    std::cout << "Raw Load Vector:" << std::endl;
    printMatrix(rawLoadVect);

    std::cout << "Solvable K-Matrix:" << std::endl;
    printMatrix(solveStiffMat);
    std::cout << "Solvable Load Vector:" << std::endl;
    printMatrix(solveLoadVect);
    std::cout << "Calculated Node Values:" << std::endl;
    printMatrix(calcNodeTemps);

}
