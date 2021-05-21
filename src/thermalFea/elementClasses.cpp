#include <thermalFea/elementClasses.hpp>

#include <cmath>
#include <iostream>

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




/*
TwoDimThermalElement needs to get some stuff moved into it that is currently 
in its derived classes. These include:
    * Initialization and setting of the thermal conductivity
    * Getting the node coordinates
    * Setting the thickness
    * Getting the shape functions
    * Setting the surface and body loads
    * Finding the nodal loads and stiffness (only if the integration is 
        handled by a call to a pointer defined by the derived class)
*/














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

    if (this->nodeGlobCoordVect.size() != 4) {
        //TODO: Make this a real exception
        throw "Need to define 4 nodes";
    };

    if (this->nodeGlobCoordVect[0].size() != 2) {
        //TODO: Make this a real exception
        throw "Node coordinates must be 2-D";
    };

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
    // trans( grad( shapeFunc ) ) * thick * MatMatrix * grad( shapeFunc )

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















XyCstThermalTriElement::XyCstThermalTriElement() 
:condMatrix (2,std::vector< double >(2,0.0) )
{
    this->numbOfNodes = 3;
    this->numbOfSurfs = numbOfNodes;
    this->degreesOfFreedom = 1;
    this->loadOnSurf[0] = false;
    this->loadOnSurf[1] = false;
    this->loadOnSurf[2] = false;
    this->loadOnBody = false;
    
    std::vector<double> zeroCoeff;
    zeroCoeff.push_back(0.0);
    for(int idx = 0; idx < numbOfSurfs; ++idx) {
        this->locSurfLoads.push_back(zeroCoeff);
    };
};

void XyCstThermalTriElement::checkNodeCoords() {

    // This doesn't actually check coordinates

    if (this->nodeGlobCoordVect.size() != 3) {
        //TODO: Make this a real exception
        throw "Need to define 3 nodes";
    };

    if (this->nodeGlobCoordVect[0].size() != 2) {
        //TODO: Make this a real exception
        throw "Node coordinates must be 2-D";
    };
};

void XyCstThermalTriElement::setLocNodeCoords() {
    
    std::vector< double > coordVect(3);
    coordVect[0] = 1.0;
    coordVect[1] = 0.0;
    coordVect[2] = 0.0;
    this->nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = 0.0;
    coordVect[1] = 1.0;
    coordVect[2] = 0.0;
    this->nodeLocCoordVect.push_back(coordVect);
    coordVect[0] = 0.0;
    coordVect[1] = 0.0;
    coordVect[2] = 1.0;
    this->nodeLocCoordVect.push_back(coordVect);

    coordVect[0] = 1.0;
    coordVect[1] = 1.0;
    coordVect[2] = 1.0;
    this->natTransMatrix.push_back(coordVect);
    coordVect[0] = nodeGlobCoordVect[0][0];
    coordVect[1] = nodeGlobCoordVect[1][0];
    coordVect[2] = nodeGlobCoordVect[2][0];
    this->natTransMatrix.push_back(coordVect);
    coordVect[0] = nodeGlobCoordVect[0][1];
    coordVect[1] = nodeGlobCoordVect[1][1];
    coordVect[2] = nodeGlobCoordVect[2][1];
    this->natTransMatrix.push_back(coordVect);

    this->area = (nodeGlobCoordVect[1][0]-nodeGlobCoordVect[0][0])*(nodeGlobCoordVect[2][1]-nodeGlobCoordVect[0][1])
                 -(nodeGlobCoordVect[2][0]-nodeGlobCoordVect[0][0])*(nodeGlobCoordVect[1][1]-nodeGlobCoordVect[0][1]);
    this->area /= 2.0;

    coordVect[0] = nodeGlobCoordVect[1][0]*nodeGlobCoordVect[2][1]-nodeGlobCoordVect[2][0]*nodeGlobCoordVect[1][1];
    coordVect[1] = nodeGlobCoordVect[1][1]-nodeGlobCoordVect[2][1];
    coordVect[2] = nodeGlobCoordVect[2][0]-nodeGlobCoordVect[1][0];
    invNatTransMatrix.push_back(coordVect);
    coordVect[0] = nodeGlobCoordVect[2][0]*nodeGlobCoordVect[0][1]-nodeGlobCoordVect[0][0]*nodeGlobCoordVect[2][1];
    coordVect[1] = nodeGlobCoordVect[2][1]-nodeGlobCoordVect[0][1];
    coordVect[2] = nodeGlobCoordVect[0][0]-nodeGlobCoordVect[2][0];
    invNatTransMatrix.push_back(coordVect);
    coordVect[0] = nodeGlobCoordVect[0][0]*nodeGlobCoordVect[1][1]-nodeGlobCoordVect[1][0]*nodeGlobCoordVect[0][1];
    coordVect[1] = nodeGlobCoordVect[0][1]-nodeGlobCoordVect[1][1];
    coordVect[2] = nodeGlobCoordVect[1][0]-nodeGlobCoordVect[0][0];
    invNatTransMatrix.push_back(coordVect);
    for (int idx=0; idx < 3; idx++){
        for (int jdx=0; jdx < 3; jdx++){
            invNatTransMatrix[idx][jdx] /= 2.0*this->area;
        };
    };
    
    
};

std::vector< std::vector< double > > XyCstThermalTriElement::getLocNodeCoords() {
    return this->nodeLocCoordVect;
};

void XyCstThermalTriElement::setNodeCoords(std::vector< std::vector< double > > globalNodeCoords){
    ThermalElement::setNodeCoordVect(globalNodeCoords);
    this->checkNodeCoords();
    this->setLocNodeCoords();
    this->setShapeFuncs();
};

void XyCstThermalTriElement::setElemThick(double elemThick) {
    // This should be moved to a more generic 2-D class

    this->elemThickness = elemThick;
};

double XyCstThermalTriElement::getElemThick() {
    // This should be moved to a more generic 2-D class

    return this->elemThickness;
};

void XyCstThermalTriElement::setMatMatrix(std::vector< std::vector< double > > thermCondMatrix) {
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

std::vector< std::vector< double > > XyCstThermalTriElement::getMatMatrix() {
    return this->condMatrix;
};

void XyCstThermalTriElement::setIsoThermCond(double thermCond) {
    this->condMatrix[0][0] = thermCond;
    this->condMatrix[0][1] = 0.0;
    this->condMatrix[1][0] = 0.0;
    this->condMatrix[1][1] = thermCond;
};

void XyCstThermalTriElement::setShapeFuncs() {
    
    std::vector< TwoDimPoly > polyRow;

    for (int idx = 0; idx < 3; idx++){
        std::vector< double > oneDimCoeffVect(2);
        std::vector< OneDimPoly > oneDimPolyVect;
        
        oneDimCoeffVect[0] = this->invNatTransMatrix[idx][0];
        oneDimCoeffVect[1] = this->invNatTransMatrix[idx][1];
        OneDimPoly dummyOneDimPoly1(oneDimCoeffVect);
        oneDimPolyVect.push_back(dummyOneDimPoly1);
        
        oneDimCoeffVect[0] = this->invNatTransMatrix[idx][2];
        oneDimCoeffVect[1] = 0.0;
        OneDimPoly dummyOneDimPoly2(oneDimCoeffVect);
        oneDimPolyVect.push_back(dummyOneDimPoly2);
        
        polyRow.push_back(TwoDimPoly(oneDimPolyVect));
    };

    this->shapeFuncVect.addRow(polyRow);

};

XyShapeFuncVector XyCstThermalTriElement::getShapeFuncs() {
    return this->shapeFuncVect;
};

PolyArray XyCstThermalTriElement::getStiffIntegrand() {
    // trans( grad( shapeFunc ) ) * thick * MatMatrix * grad( shapeFunc )

    PolyArray gradShapeFuncs = shapeFuncVect.getGrad();
    
    PolyArray stiffIntegrand = gradShapeFuncs.transpose();
    stiffIntegrand = stiffIntegrand.multScalar(this->elemThickness);
    stiffIntegrand = stiffIntegrand.matMultScalarBehind(this->condMatrix);
    std::vector<std::vector<double> > checkMat = stiffIntegrand.evalAt(0.0,0.0);
    stiffIntegrand = stiffIntegrand.matMultPolyArray(gradShapeFuncs);

    return stiffIntegrand;

};

std::vector< std::vector< double > > XyCstThermalTriElement::getStiffnessMatrix() {
    
    PolyArray stiffIntegrand = this->getStiffIntegrand();
    stiffIntegrand = stiffIntegrand.multScalar(this->area); // This is the actual integration (there is no spatial dependence)
    std::vector< std::vector< double > > stiffMatrix = stiffIntegrand.evalAt(0.0, 0.0); // Just retrieves the matrix entries (constants)
    return stiffMatrix;
};

std::vector<double> XyCstThermalTriElement::getLoadOnSurf(int surfNumb){
    
    int surfIdx = surfNumb - 1;

    std::vector<double> surfLoadVect(this->numbOfNodes,0.0);

    if (this->loadOnSurf[surfIdx]) {
        
        int nextNode;
        if (surfNumb == 3) {
            nextNode = 0;
        } else {
            nextNode = surfIdx+1;
        }

        //        |\ L | A11 A12 A13 |    |        1        |
        // F_n =  |    | A21 A22 A23 | *  | l*cos(theta)+xn |*load(l)*t*dl
        //       \|  0 | A31 A32 A33 |    | l*sin(theta)+yn |
        // 
        // Still need to zero out the non-adjacent node... (this may be very wrong)

        double xn = this->nodeGlobCoordVect[surfIdx][0];
        double yn = this->nodeGlobCoordVect[surfIdx][1];
        double deltaX = this->nodeGlobCoordVect[surfIdx][0]-this->nodeGlobCoordVect[nextNode][0];
        double deltaY = this->nodeGlobCoordVect[surfIdx][1]-this->nodeGlobCoordVect[nextNode][1];
        double length = std::sqrt(std::pow(deltaX,2)+std::pow(deltaY,2));
        double theta = std::atan(deltaY/deltaX);

        for (int nodeIdx = 0; nodeIdx < this->numbOfNodes; ++nodeIdx) {
            if (nodeIdx == surfIdx || nodeIdx == nextNode) {
                std::vector< double > oneDimCoeffVect(2);
                oneDimCoeffVect[0] = this->invNatTransMatrix[nodeIdx][0] +
                                    this->invNatTransMatrix[nodeIdx][1] * xn +
                                    this->invNatTransMatrix[nodeIdx][2] * yn;
                oneDimCoeffVect[1] = this->invNatTransMatrix[nodeIdx][1] * std::cos(theta) +
                                    this->invNatTransMatrix[nodeIdx][2] * std::sin(theta);
                OneDimPoly tempOneDimPoly(oneDimCoeffVect);

                tempOneDimPoly = tempOneDimPoly.multScalar(elemThickness);
                tempOneDimPoly = tempOneDimPoly.multOneDimPoly(this->locSurfLoads[surfIdx]);
                surfLoadVect[nodeIdx] = tempOneDimPoly.findIntegralOverRange(0.0, length);
            } else {
                surfLoadVect[nodeIdx] = 0.0;
            }
        }
    }

    return surfLoadVect;
};

std::vector<double> XyCstThermalTriElement::getTotalLoadVect() {
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