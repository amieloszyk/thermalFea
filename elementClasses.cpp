#include "elementClasses.h"

ThermalElement::ThermalElement() {
    this->numbOfNodes = 0;
};

void ThermalElement::setNumberOfNodes(int thisManyNodes) {
    this->numbOfNodes = thisManyNodes;
};

int ThermalElement::getNumberOfNodes() {
    return this->numbOfNodes;
};

void ThermalElement::setElementNumber(int giveElementNumb) {
    this->elementNumb = giveElementNumb;
};

int ThermalElement::getElementNumber() {
    return this->elementNumb;
};

void ThermalElement::checkNumbOfNodes(int givenVectSize) {
    if(givenVectSize != this->numbOfNodes) {
        //TODO: Make this a real exception
        throw "Wrong numbOfNodes";
    };
};

void ThermalElement::setNodeGlobNumber(std::vector< int > nodeGlobNumb) {
    
    if (this->numbOfNodes == 0) {
        this->numbOfNodes = nodeGlobNumb.size(); 
    }
    else {
        checkNumbOfNodes(nodeGlobNumb.size());
    };
    
    this->nodeGlobNumbVect = nodeGlobNumb;
};

std::vector< int > ThermalElement::getNodeGlobNumber() {
    return this->nodeGlobNumbVect;
};

void ThermalElement::setNodeCoordVect(std::vector< std::vector< double > > nodeGlobCoords) {

    if (numbOfNodes == 0) {
        this->numbOfNodes = nodeGlobCoords.size(); 
    }
    else {
        checkNumbOfNodes(nodeGlobCoords.size());
    };

    this->nodeGlobCoordVect = nodeGlobCoords;
};

std::vector< std::vector< double > > ThermalElement::getNodeCoords() {
    return this->nodeGlobCoordVect;
};















XyLinearThermalMeloshElement::XyLinearThermalMeloshElement() 
:condMatrix (2,std::vector< double >(2,0.0) )
{
    this->numbOfNodes = 4;
    this->numbOfSurfs = numbOfNodes;
    this->degreesOfFreedom = 1;
    this->halfHeight = 0.0;
    this->halfWidth = 0.0;
    this->loadOnSurf[0] = false;
    this->loadOnSurf[1] = false;
    this->loadOnSurf[2] = false;
    this->loadOnSurf[3] = false;
    this->loadOnBody = false;
    
    std::vector<double> zeroCoeff;
    zeroCoeff.push_back(0.0);
    for(int idx = 0; idx < numbOfSurfs; ++idx) {
        this->locSurfLoads.push_back(zeroCoeff);
    };
};

void XyLinearThermalMeloshElement::checkNodeCoords() {

    if (this->nodeGlobCoordVect[0].size() != 2) {
        //TODO: Make this a real exception
        throw "Node coordinates must be 2-D";
    }

    if (this->nodeGlobCoordVect[0][0] != nodeGlobCoordVect[3][0]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    }
    else if (this->nodeGlobCoordVect[1][0] != nodeGlobCoordVect[2][0]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    }
    else if (this->nodeGlobCoordVect[0][1] != nodeGlobCoordVect[1][1]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    }
    else if (this->nodeGlobCoordVect[2][1] != nodeGlobCoordVect[3][1]) {
        //TODO: Make this a real exception
        throw "Melosh elements must be rectangular";
    };
};

void XyLinearThermalMeloshElement::setLocNodeCoords() {
    
    this->halfWidth = (this->nodeGlobCoordVect[1][0] - this->nodeGlobCoordVect[0][0])/2.0;
    this->halfHeight = (this->nodeGlobCoordVect[3][1] - this->nodeGlobCoordVect[0][1])/2.0;

    std::vector< double > coordVect(2);
    coordVect[0] = -halfWidth;
    coordVect[1] = -halfHeight;
    this->nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = halfWidth;
    coordVect[1] = -halfHeight;
    this->nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = halfWidth;
    coordVect[1] = halfHeight;
    this->nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = -halfWidth;
    coordVect[1] = halfHeight;
    this->nodeLocCoordVect.push_back(coordVect);

};

std::vector< std::vector< double > > XyLinearThermalMeloshElement::getLocNodeCoords() {
    return this->nodeLocCoordVect;
};

double XyLinearThermalMeloshElement::getHalfWidth() {
    return this->halfWidth;
};

double XyLinearThermalMeloshElement::getHalfHeight() {
    return this->halfHeight;
};

void XyLinearThermalMeloshElement::setNodeCoords(std::vector< std::vector< double > > globalNodeCoords){
    ThermalElement::setNodeCoordVect(globalNodeCoords);
    this->checkNodeCoords();
    this->setLocNodeCoords();
    this->setShapeFuncs();
};

void XyLinearThermalMeloshElement::setElemThick(double elemThick) {
    // This should be moved to a more generic 2-D class

    this->elemThickness = elemThick;
};

double XyLinearThermalMeloshElement::getElemThick() {
    // This should be moved to a more generic 2-D class

    return this->elemThickness;
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

    this->condMatrix = thermCondMatrix;
};

std::vector< std::vector< double > > XyLinearThermalMeloshElement::getMatMatrix() {
    return this->condMatrix;
};

void XyLinearThermalMeloshElement::setIsoThermCond(double thermCond) {
    this->condMatrix[0][0] = thermCond;
    this->condMatrix[0][1] = 0.0;
    this->condMatrix[1][0] = 0.0;
    this->condMatrix[1][1] = thermCond;
};

void XyLinearThermalMeloshElement::setShapeFuncs() {
    if (this->halfWidth == 0.0) {
        //TODO: Make this a real exception
        throw "Element size not set";
    }
    else if (this->halfWidth == 0.0) {
        //TODO: Make this a real exception
        throw "Element size not set";
    };
    
    double denomMult = 1.0/(4.0*this->halfWidth*this->halfHeight);
    std::vector< double > oneDimCoeffVect(2);
    std::vector< OneDimPoly > oneDimPolyVect;
    std::vector< TwoDimPoly > polyRow;

    // Shape #1: -,-
    oneDimCoeffVect[0] = this->halfWidth;
    oneDimCoeffVect[1] = -1.0;
    OneDimPoly dummyOneDimPoly1(oneDimCoeffVect);  //TODO: This should get redefined for each shape function
    oneDimPolyVect.push_back(dummyOneDimPoly1.multScalar(this->halfHeight*denomMult));
    oneDimPolyVect.push_back(dummyOneDimPoly1.multScalar(-denomMult));
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    // Shape #2: +,-
    oneDimCoeffVect[0] = this->halfWidth;
    oneDimCoeffVect[1] = 1.0;
    OneDimPoly dummyOneDimPoly2(oneDimCoeffVect); //TODO: This should get redefined for each shape function
    oneDimPolyVect[0] = dummyOneDimPoly2.multScalar(this->halfHeight*denomMult);
    oneDimPolyVect[1] = dummyOneDimPoly2.multScalar(-denomMult);
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    // Shape #3: +,+
    oneDimCoeffVect[0] = this->halfWidth;
    oneDimCoeffVect[1] = 1.0;
    OneDimPoly dummyOneDimPoly3(oneDimCoeffVect); //TODO: This should get redefined for each shape function
    oneDimPolyVect[0] = dummyOneDimPoly3.multScalar(this->halfHeight*denomMult);
    oneDimPolyVect[1] = dummyOneDimPoly3.multScalar(denomMult);
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    // Shape #4: -,+
    oneDimCoeffVect[0] = this->halfWidth;
    oneDimCoeffVect[1] = -1.0;
    OneDimPoly dummyOneDimPoly4(oneDimCoeffVect); //TODO: This should get redefined for each shape function
    oneDimPolyVect[0] = dummyOneDimPoly4.multScalar(this->halfHeight*denomMult);
    oneDimPolyVect[1] = dummyOneDimPoly4.multScalar(denomMult);
    polyRow.push_back(TwoDimPoly(oneDimPolyVect));

    this->shapeFuncVect.addRow(polyRow);

};

XyShapeFuncVector XyLinearThermalMeloshElement::getShapeFuncs() {
    return this->shapeFuncVect;
};

PolyArray XyLinearThermalMeloshElement::getStiffIntegrand() {
    // trans( grad( shapeFunc ) ) * thick * MatMatrix * shapeFunc

    PolyArray gradShapeFuncs = shapeFuncVect.getGrad();
    
    PolyArray stiffIntegrand = gradShapeFuncs.transpose();
    stiffIntegrand = stiffIntegrand.multScalar(this->elemThickness);
    stiffIntegrand = stiffIntegrand.matMultScalarBehind(this->condMatrix);
    stiffIntegrand = stiffIntegrand.matMultPolyArray(gradShapeFuncs);

    return stiffIntegrand;

};

std::vector< std::vector< double > > XyLinearThermalMeloshElement::getStiffnessMatrix() {
    
    PolyArray stiffIntegrand = this->getStiffIntegrand();
    std::vector< std::vector< double > > stiffMatrix = stiffIntegrand.findIntegralOverRange(this->nodeLocCoordVect[0][0],this->nodeLocCoordVect[1][0],
                                                                                            this->nodeLocCoordVect[0][1],this->nodeLocCoordVect[3][1]);
    return stiffMatrix;
};

void XyLinearThermalMeloshElement::setSurfaceLoadInLocCoords(int surfNumb, OneDimPoly locLoadShape) {
    /*
    Note that the local load shape must be defined as a function of position on the applicable
    surface in local coordinates. transformations are likely necessary.
    */

    int surfIdx = surfNumb - 1;
    this->loadOnSurf[surfIdx] = true;
    this->locSurfLoads[surfIdx].multScalar(0.0);
    this->locSurfLoads[surfIdx] = this->locSurfLoads[surfIdx].addOneDimPoly(locLoadShape);
};

std::vector<double> XyLinearThermalMeloshElement::getLoadOnSurf(int surfNumb){
    
    int surfIdx = surfNumb - 1;

    std::vector<double> surfLoadVect(this->numbOfNodes,0.0);

    if (this->loadOnSurf[surfIdx]) {
        
        OneDimPoly surfFuncIntShapeFuncs(std::vector<double>(1,0.0)); // Appropriate shape functions for integrating surface loads
        OneDimPoly tempOneDimPoly(std::vector<double>(1,0.0));
        
        double fixedX;
        double fixedY;
        double lowerIntBound;
        double upperIntBound;
        PolyArray transShapeFuncs = this->shapeFuncVect.transpose();
        
        for (int shapeIdx = 0; shapeIdx < this->numbOfNodes; ++shapeIdx) {
            
            TwoDimPoly tempTwoDimPoly = transShapeFuncs.getPoly(shapeIdx, 0);
            
            if (surfNumb == 1){
                // Bottom surface
                fixedY = -this->halfHeight;
                lowerIntBound = -this->halfWidth;
                upperIntBound = this->halfWidth;
                tempOneDimPoly = tempTwoDimPoly.getFixedVarTwoPoly(fixedY);
            }
            else if (surfNumb == 2){
                // Right surface
                fixedX = this->halfWidth;
                lowerIntBound = -this->halfHeight;
                upperIntBound = this->halfHeight;
                tempOneDimPoly = tempTwoDimPoly.getFixedVarOnePoly(fixedX);
            }
            else if (surfNumb == 3){
                // Top surface
                fixedY = this->halfHeight;
                lowerIntBound = -this->halfWidth;
                upperIntBound = this->halfWidth;
                tempOneDimPoly = tempTwoDimPoly.getFixedVarTwoPoly(fixedY);
            }
            else if (surfNumb == 4){
                // Left surface
                fixedX = -this->halfWidth;
                lowerIntBound = -this->halfHeight;
                upperIntBound = this->halfHeight;
                tempOneDimPoly = tempTwoDimPoly.getFixedVarOnePoly(fixedX);
            }

            surfFuncIntShapeFuncs = tempOneDimPoly;
            surfFuncIntShapeFuncs = surfFuncIntShapeFuncs.multScalar(elemThickness);
            surfFuncIntShapeFuncs = surfFuncIntShapeFuncs.multOneDimPoly(locSurfLoads[surfIdx]);
            surfLoadVect[shapeIdx] = surfFuncIntShapeFuncs.findIntegralOverRange(lowerIntBound, upperIntBound);
        };
    }

    return surfLoadVect;
};

std::vector<double> XyLinearThermalMeloshElement::getTotalLoadVect() {

    std::vector< double > totalLoad(this->numbOfNodes, 0.0);
    std::vector< double > specSurfLoad;

    for (int surfNumb = 1; surfNumb <= this->numbOfSurfs; surfNumb++) {
        specSurfLoad = this->getLoadOnSurf(surfNumb);
        for (int nodeIdx = 0; nodeIdx < this->numbOfNodes; nodeIdx++) {
            totalLoad[nodeIdx] += specSurfLoad[nodeIdx];
        };
    };

    // TODO: need to add body loads

    return totalLoad;
};
