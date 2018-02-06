#include "meshClasses.h"
#include <iostream>

TwoDimMeshOfElements::TwoDimMeshOfElements(int nodesInMesh, int elementsInMesh) {
    
    //TODO: There should be more intrinsic setting of the number of nodes

    this->numbOfSurfs = 0;

    this->numbOfNodes = nodesInMesh;
    this->numbOfElements = elementsInMesh;
    
    this->resizeNodesAndElements();
};

void TwoDimMeshOfElements::resizeNodesAndElements(){
    
    if (this->numbOfNodes == 0){
        this->nodeCoords.clear();
        this->nodeVals.clear();
        this->nodeValSet.clear();
    }
    else {
        this->nodeCoords.resize(this->numbOfNodes);
        this->nodeVals.resize(this->numbOfNodes,0.0);
        this->nodeValSet.resize(this->numbOfNodes,false);
    };

    if (this->numbOfElements == 0){
        this->elementObjList.clear();
        this->globNodeOnElementMap.clear();
    }
    else {
        this->elementObjList.resize(this->numbOfElements);
        this->globNodeOnElementMap.resize(this->numbOfElements);
    };

};

int TwoDimMeshOfElements::addNewElement(std::string elemType, std::vector< std::vector< double > > nodeCoords,
                                        std::vector< int > globalNodeNumbs){
    
    this->numbOfElements++;
    int elementNumb = this->numbOfElements;
    this->numbOfNodes += globalNodeNumbs.size();
    this->resizeNodesAndElements();

    //TODO: This is breaking here. 
    // The issue is that I am allowing the global node numbers to be larger than 
    // the number of global nodes, which creates memory access issues for 
    // unallocated space. There are two solutions: 1) Force node numbering to 
    // match pace with the element numbering (i.e. never allow node numbers 
    // > the number that exist); or 2) Trust that the 'missing' nodes will get
    // added an resize the node dependent vectors to be the size of the largest 
    // node number (that feels dangerous)
    if (nodeCoords.size() == 4) {
        if (elemType == "melosh") {
            TwoDimThermalElement *dummyElement = new XyLinearThermalMeloshElement();
            dummyElement->setNodeCoords(nodeCoords);
            this->addExistingElement(elementNumb, dummyElement, globalNodeNumbs);
        }
    }
    
    return elementNumb;
};

void TwoDimMeshOfElements::setElemThick(float thick, int elementNumb){
    this->elementObjList[elementNumb-1]->setElemThick(thick);
};

void TwoDimMeshOfElements::setAllThick(float thick){
    for(int elemNumb=1; elemNumb <= this->numbOfElements; elemNumb++){
        this->setElemThick(thick,elemNumb+1);
    };
};

void TwoDimMeshOfElements::setElemIsoThermCond(float isoThermCond, int elementNumb){
    this->elementObjList[elementNumb-1]->setIsoThermCond(isoThermCond);
};

void TwoDimMeshOfElements::setAllIsoThermCond(float isoThermCond){
    for(int elemNumb=1; elemNumb <= this->numbOfElements; elemNumb++){
        this->setElemIsoThermCond(isoThermCond,elemNumb);
    };
};

void TwoDimMeshOfElements::addExistingElement(int elementNumb, TwoDimThermalElement* element, std::vector<int> globalNodeNumbs) {

    //TODO: Add error for global node list size not matching number of nodes on element
    //TODO: There should be more intrinsic setting of the number of nodes

    //element tracking
    int elementIdx = elementNumb-1;
    element->setNodeGlobNumber(globalNodeNumbs);
    this->elementObjList[elementIdx] = element;
    this->globNodeOnElementMap[elementIdx] = globalNodeNumbs;

    //node tracking
    std::vector< std::vector< double > > newNodeCoords = element->getNodeCoords();
    for(int locNodeIdx = 0; locNodeIdx < globalNodeNumbs.size(); locNodeIdx++) {
        this->nodeCoords[globalNodeNumbs[locNodeIdx]-1] = newNodeCoords[locNodeIdx];
    };

};

int TwoDimMeshOfElements::makeNewSurf() {
    this->numbOfSurfs ++;
    this->surfElemNumbs.push_back(std::vector<int>(0));
    this->surfLocNumbs.push_back(std::vector<int>(0));

    return this->numbOfSurfs;
};

void TwoDimMeshOfElements::addLocSurfToMesh(int meshSurfNumb, int meshElementNumb, int locSurfNumb){
    
    int meshSurfIdx = meshSurfNumb-1;
    this->surfElemNumbs[meshSurfIdx].push_back(meshElementNumb);
    this->surfLocNumbs[meshSurfIdx].push_back(locSurfNumb);

};

void TwoDimMeshOfElements::addLocCoordLoadToSurf(int globSurfNumb, OneDimPoly locCoordPoly){

    int globSurfIdx = globSurfNumb-1;
    int numbLocSurfs = this->surfLocNumbs[globSurfIdx].size();
    int elemIdx = 0;
    int locSurfNumb = 0;

    for (int surfIdx = 0; surfIdx < numbLocSurfs; surfIdx++) {
        elemIdx = this->surfElemNumbs[globSurfIdx][surfIdx]-1;
        locSurfNumb = this->surfLocNumbs[globSurfIdx][surfIdx];
        this->elementObjList[elemIdx]->setSurfaceLoadInLocCoords(locSurfNumb, locCoordPoly);
    };
};

void TwoDimMeshOfElements::setScalarSurfFlux(int globSurfNumb, double scalarFlux){

    std::vector<double> locCoordPolyFlux(1, scalarFlux);
    this->addLocCoordLoadToSurf(globSurfNumb, locCoordPolyFlux);

};

std::vector< std::vector< double > > TwoDimMeshOfElements::getRawGlobStiffMatrix() {
    
    std::vector< std::vector< double > > globStiff(this->numbOfNodes, std::vector< double >(this->numbOfNodes, 0.0));
    std::vector< std::vector< double > > locStiff;
    std::vector< int > globNodeNumbs;

    for (int elemIdx=0; elemIdx < this->numbOfElements; elemIdx++) {

        locStiff = this->elementObjList[elemIdx]->getStiffnessMatrix();
        globNodeNumbs = this->elementObjList[elemIdx]->getNodeGlobNumber();
        int numbLocNodes = globNodeNumbs.size();

        for (int locRowIdx=0; locRowIdx < numbLocNodes; locRowIdx++) {
            int globRowIdx = globNodeNumbs[locRowIdx]-1;

            for (int locColIdx=0; locColIdx < numbLocNodes; locColIdx++) {
                int globColIdx = globNodeNumbs[locColIdx]-1;

                globStiff[globRowIdx][globColIdx] += locStiff[locRowIdx][locColIdx];
            };
        };
        locStiff.clear();
        globNodeNumbs.clear();
    };

    return globStiff;
};

std::vector< double > TwoDimMeshOfElements::getRawGlobLoadVect() {
    std::vector< double > globLoad(this->numbOfNodes, 0.0);
    std::vector< double > locLoads;
    std::vector< int > globNodeNumbs;

    for (int elemIdx=0; elemIdx < this->numbOfElements; elemIdx++) {

        locLoads = this->elementObjList[elemIdx]->getTotalLoadVect();
        globNodeNumbs = this->elementObjList[elemIdx]->getNodeGlobNumber();
        int numbLocNodes = globNodeNumbs.size();

        for (int locRowIdx=0; locRowIdx < numbLocNodes; locRowIdx++) {
            int globRowIdx = globNodeNumbs[locRowIdx]-1;

            globLoad[globRowIdx] += locLoads[locRowIdx];
        };
    };
    
    return globLoad;
};

void TwoDimMeshOfElements::setFixedNodeVals(std::vector< int > nodesToSet, std::vector< double > setVals) {

    int nodeIdx = 0;
    for (int setIdx = 0; setIdx < nodesToSet.size(); setIdx++) {
        std::cout << setIdx << std::endl;
        nodeIdx = nodesToSet[setIdx]-1;
        std::cout << nodeIdx << std::endl;
        this->nodeValSet[nodeIdx] = true;
        this->nodeVals[nodeIdx] = setVals[setIdx];
    };

};

std::vector< std::vector< double > > TwoDimMeshOfElements::getStiffMatToSolve() {
    
    std::vector< std::vector< double > > rawStiff = this->getRawGlobStiffMatrix();
    std::vector< std::vector< double > > solveStiff;
    std::vector< double > dummyRow(rawStiff[0].size(),0.0);

    for (int rowIdx=0; rowIdx < this->numbOfNodes; rowIdx++) {
        if (this->nodeValSet[rowIdx]) {
            std::fill(dummyRow.begin(), dummyRow.end(), 0.0);
            dummyRow[rowIdx] = 1.0;
        }
        else {
            dummyRow = rawStiff[rowIdx];
        };
        solveStiff.push_back(dummyRow);
    };
    
    return solveStiff;
};

std::vector< double > TwoDimMeshOfElements::getLoadVectToSolve() {
    std::vector< double > rawLoad = this->getRawGlobLoadVect();
    std::vector< double > solveLoad;
    double dummy;

    for (int rowIdx=0; rowIdx < this->numbOfNodes; rowIdx++) {
        if (this->nodeValSet[rowIdx]) {
            dummy = this->nodeVals[rowIdx];
        }
        else {
            dummy = rawLoad[rowIdx];
        };
        solveLoad.push_back(dummy);
    };

    return solveLoad;
};

