#include "meshClasses.h"

TwoDimMeshOfElements::TwoDimMeshOfElements(int nodesInMesh, int elementsInMesh) {
    
    this->numbOfSurfs = 0;

    this->numbOfNodes = nodesInMesh;
    this->nodeCoords.resize(nodesInMesh);
    this->nodeVals.resize(nodesInMesh,0);

    this->numbOfElements = elementsInMesh;
    this->elementObjList.resize(elementsInMesh);
    this->globNodeOnElementMap.resize(elementsInMesh);
    
    
};

void TwoDimMeshOfElements::addExistingElement(int elementNumb, TwoDimThermalElement* element, std::vector<int> globalNodeNumbs) {

    //TODO: Add error for global node list size not matching number of nodes on element

    //element tracking
    int elementIdx = elementNumb-1;
    element->setNodeGlobNumber(globalNodeNumbs);
    this->elementObjList[elementIdx] = element;
    this->globNodeOnElementMap[elementIdx] = globalNodeNumbs;

    //node tracking
    std::vector< std::vector< double > > newNodeCoords = element->getNodeCoords();
    for(int locNodeIdx = 0; locNodeIdx < globalNodeNumbs.size(); locNodeIdx++) {
        this->nodeCoords[globalNodeNumbs[locNodeIdx]] = newNodeCoords[locNodeIdx];
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

std::vector< std::vector< double > > TwoDimMeshOfElements::getGlobStiffMatrix() {
    
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

std::vector< double > TwoDimMeshOfElements::getGlobLoadVect() {
    std::vector< double > globLoad(this->numbOfNodes, 0.0);
    std::vector< double > locLoads;
    std::vector< int > globNodeNumbs;

    for (int elemIdx=0; elemIdx < this->numbOfElements; elemIdx++) {

        locLoads = this->elementObjList[elemIdx]->getTotalLoadVect();
        globNodeNumbs = this->elementObjList[elemIdx]->getNodeGlobNumber();
        int numbLocNodes = globNodeNumbs.size();

        for (int locRowIdx=0; locRowIdx < numbLocNodes; locRowIdx++) {
            int globRowIdx = globNodeNumbs[locRowIdx]-1;

    //         for (int locColIdx=0; locColIdx < numbLocNodes; locColIdx++) {
    //             int globColIdx = globNodeNumbs[locColIdx]-1;

            globLoad[globRowIdx] += locLoads[locRowIdx];
    //         };
        };
    //     locLoad.clear();
    //     globNodeNumbs.clear();
    };
    
    return locLoads;
};

