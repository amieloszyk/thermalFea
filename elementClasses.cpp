#include "elementClasses.h"

GeneralElement::GeneralElement() {
    numbOfNodes = 0;
};

void GeneralElement::setNumberOfNodes(int thisManyNodes) {
    numbOfNodes = thisManyNodes;
};

int GeneralElement::getNumberOfNodes() {
    return numbOfNodes;
};

void GeneralElement::setElementNumber(int giveElementNumb) {
    elementNumb = giveElementNumb;
};

int GeneralElement::getElementNumber() {
    return elementNumb;
};

void GeneralElement::checkNumbOfNodes(int givenVectSize) {
    if(givenVectSize != numbOfNodes) {
        //TODO: Make this a real exception
        throw "Wrong numbOfNodes";
    };
};

void GeneralElement::setNodeGlobNumber(std::vector< int > nodeGlobNumb) {
    
    if (numbOfNodes == 0) {
        numbOfNodes = nodeGlobNumb.size(); 
    }
    else {
        checkNumbOfNodes(nodeGlobNumb.size());
    };
    
    nodeGlobNumbVect = nodeGlobNumb;
};

std::vector< int > GeneralElement::getNodeGlobNumber() {
    return nodeGlobNumbVect;
};

void GeneralElement::setNodeCoords(std::vector< std::vector< double > > nodeGlobCoords) {

    if (numbOfNodes == 0) {
        numbOfNodes = nodeGlobCoords.size(); 
    }
    else {
        checkNumbOfNodes(nodeGlobCoords.size());
    };

    nodeGlobCoordVect = nodeGlobCoords;
};

std::vector< std::vector< double > > GeneralElement::getNodeCoords() {
    return nodeGlobCoordVect;
};















XyLinearThermalMeloshElement::XyLinearThermalMeloshElement() 
:condMatrix (2,std::vector< double >(2,0.0) )
{
    numbOfNodes = 4;
    degreesOfFreedom = 1;
    halfHeight = 0.0;
    halfWidth = 0.0;
    loadOnSurf[0] = false;
    loadOnSurf[1] = false;
    loadOnSurf[2] = false;
    loadOnSurf[3] = false;
    loadOnBody = false;
};

void XyLinearThermalMeloshElement::checkNodeCoords() {

    if (nodeGlobCoordVect[0].size() != 2) {
        //TODO: Make this a real exception
        throw "Node coordinates must be 2-D";
    }

    if (nodeGlobCoordVect[0][0] != nodeGlobCoordVect[3][0]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    }
    else if (nodeGlobCoordVect[1][0] != nodeGlobCoordVect[2][0]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    }
    else if (nodeGlobCoordVect[0][1] != nodeGlobCoordVect[1][1]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    }
    else if (nodeGlobCoordVect[2][1] != nodeGlobCoordVect[3][1]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    };
};

void XyLinearThermalMeloshElement::setLocNodeCoords() {
    
    halfWidth = (nodeGlobCoordVect[1][0] - nodeGlobCoordVect[0][0])/2.0;
    halfHeight = (nodeGlobCoordVect[3][1] - nodeGlobCoordVect[0][1])/2.0;

    std::vector< double > coordVect(2);
    coordVect[0] = -halfWidth;
    coordVect[1] = -halfHeight;
    nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = halfWidth;
    coordVect[1] = -halfHeight;
    nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = halfWidth;
    coordVect[1] = halfHeight;
    nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = -halfWidth;
    coordVect[1] = halfHeight;
    nodeLocCoordVect.push_back(coordVect);

};

std::vector< std::vector< double > > XyLinearThermalMeloshElement::getLocNodeCoords() {
    return nodeLocCoordVect;
};

double XyLinearThermalMeloshElement::getHalfWidth() {
    return halfWidth;
};

double XyLinearThermalMeloshElement::getHalfHeight() {
    return halfHeight;
};

void XyLinearThermalMeloshElement::setNodeCoords(std::vector< std::vector< double > > globalNodeCoords){
    GeneralElement::setNodeCoords(globalNodeCoords);
    checkNodeCoords();
    setLocNodeCoords();
    //TODO: Maybe move call to setShapeFuncs here?
};

void XyLinearThermalMeloshElement::setElemThick(double elemThick) {
    // This should be moved to a more generic 2-D class

    elemThickness = elemThick;
};

double XyLinearThermalMeloshElement::getElemThick() {
    // This should be moved to a more generic 2-D class

    return elemThickness;
};


void XyLinearThermalMeloshElement::setMatMatrix(std::vector< std::vector< double > > thermCondMatrix) {
    if (thermCondMatrix.size() != 2) {
        //TODO: Make this a real exception
        throw "Thermal conductivity matrix must be 2x2";
    }
    else if (thermCondMatrix[0].size() != 2) {
        //TODO: Make this a real exception
        throw "Thermal conductivity matrix must be 2x2";
    };

    condMatrix = thermCondMatrix;
};

std::vector< std::vector< double > > XyLinearThermalMeloshElement::getMatMatrix() {
    return condMatrix;
};

void XyLinearThermalMeloshElement::setIsoThermCond(double thermCond) {
    condMatrix[0][0] = thermCond;
    condMatrix[0][1] = 0.0;
    condMatrix[1][0] = 0.0;
    condMatrix[1][1] = thermCond;
};

void XyLinearThermalMeloshElement::setShapeFuncs() {
    if (halfWidth == 0.0) {
        //TODO: Make this a real exception
        throw "Element size not set";
    }
    else if (halfWidth == 0.0) {
        //TODO: Make this a real exception
        throw "Element size not set";
    };
    
    double denomMult = 1.0/(4.0*halfWidth*halfHeight);
    std::vector< double > oneDimCoeffVect(2);
    std::vector< OneDimPoly > oneDimPolyVect;
    std::vector< TwoDimPoly > polyRow;

    // Shape #1: -,-
    oneDimCoeffVect[0] = halfWidth;
    oneDimCoeffVect[1] = -1.0;
    OneDimPoly dummyOneDimPoly1(oneDimCoeffVect);  //TODO: This should get redefined for each shape function
    oneDimPolyVect.push_back(dummyOneDimPoly1.multScalar(halfHeight*denomMult));
    oneDimPolyVect.push_back(dummyOneDimPoly1.multScalar(-denomMult));
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    // Shape #2: +,-
    oneDimCoeffVect[0] = halfWidth;
    oneDimCoeffVect[1] = 1.0;
    OneDimPoly dummyOneDimPoly2(oneDimCoeffVect); //TODO: This should get redefined for each shape function
    oneDimPolyVect[0] = dummyOneDimPoly2.multScalar(halfHeight*denomMult);
    oneDimPolyVect[1] = dummyOneDimPoly2.multScalar(-denomMult);
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    // Shape #3: +,+
    oneDimCoeffVect[0] = halfWidth;
    oneDimCoeffVect[1] = 1.0;
    OneDimPoly dummyOneDimPoly3(oneDimCoeffVect); //TODO: This should get redefined for each shape function
    oneDimPolyVect[0] = dummyOneDimPoly3.multScalar(halfHeight*denomMult);
    oneDimPolyVect[1] = dummyOneDimPoly3.multScalar(denomMult);
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    // Shape #4: -,+
    oneDimCoeffVect[0] = halfWidth;
    oneDimCoeffVect[1] = -1.0;
    OneDimPoly dummyOneDimPoly4(oneDimCoeffVect); //TODO: This should get redefined for each shape function
    oneDimPolyVect[0] = dummyOneDimPoly4.multScalar(halfHeight*denomMult);
    oneDimPolyVect[1] = dummyOneDimPoly4.multScalar(denomMult);
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    shapeFuncVect.addRow(polyRow);

};

XyShapeFuncVector XyLinearThermalMeloshElement::getShapeFuncs() {
    return shapeFuncVect;
};

PolyArray XyLinearThermalMeloshElement::getStiffIntegrand() {
    // trans( grad( shapeFunc ) ) * thick * MatMatrix * shapeFunc

    PolyArray gradShapeFuncs = shapeFuncVect.getGrad();
    
    PolyArray stiffIntegrand = gradShapeFuncs.transpose();
    stiffIntegrand = stiffIntegrand.multScalar(elemThickness);
    stiffIntegrand = stiffIntegrand.matMultScalarBehind(condMatrix);
    stiffIntegrand = stiffIntegrand.matMultPolyArray(gradShapeFuncs);

    return stiffIntegrand;

};

std::vector< std::vector< double > > XyLinearThermalMeloshElement::getStiffnessMatrix() {
    
    PolyArray stiffIntegrand = getStiffIntegrand();
    std::vector< std::vector< double > > stiffMatrix = stiffIntegrand.findIntegralOverRange(nodeLocCoordVect[0][0],nodeLocCoordVect[1][0],
                                                                                            nodeLocCoordVect[0][1],nodeLocCoordVect[3][1]);
    return stiffMatrix;
};
