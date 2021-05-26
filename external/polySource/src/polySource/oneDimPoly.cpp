#include <polySource/oneDimPolyClass.hpp>

#include <math.h>
#include <algorithm>
#include <iostream>

OneDimPoly::OneDimPoly(std::vector<double> inpCoeffArray){
    coeffArray = inpCoeffArray;
    polyOrder = coeffArray.size() - 1;
};

double OneDimPoly::evalAt(double varVal) {
    
    double returnVal = 0.0;

    for (int exponIdx = 0; exponIdx <= polyOrder; ++exponIdx) {
        
        returnVal += coeffArray[exponIdx]*pow(varVal,exponIdx);
    
    };

    return returnVal;

};

std::vector<double> OneDimPoly::getCoeffArray() {
    return coeffArray;
};

int OneDimPoly::getPolyOrder() { 
    return polyOrder;
};

OneDimPoly OneDimPoly::getDerivative() {

    int numbOfDerivTerms = polyOrder;
    std::vector<double> derivCoeffArray(0);

    if (numbOfDerivTerms == 0) {
        derivCoeffArray.push_back(0.0);
    }
    else {
        for (int coeffIdx = 1; coeffIdx <= numbOfDerivTerms; ++coeffIdx) {
            derivCoeffArray.push_back(coeffArray[coeffIdx]*double(coeffIdx));
        };
    }

    OneDimPoly derivPoly(derivCoeffArray);
    return derivPoly;

};


double OneDimPoly::findIntegralOverRange(double firstVal, double secondVal) {

    int numbOfIntTerms = polyOrder+1;
    std::vector<double> intCoeffArray(numbOfIntTerms + 1);
    intCoeffArray[0] = 0.0;

    for (int intCoeffIdx = 1; intCoeffIdx <= numbOfIntTerms; ++intCoeffIdx) {
        double expon = intCoeffIdx;
        intCoeffArray[intCoeffIdx] = coeffArray[intCoeffIdx - 1] / expon;
    };

    OneDimPoly intOneDimPoly = OneDimPoly(intCoeffArray);

    double intAtFirstVal = intOneDimPoly.evalAt(firstVal);
    double intAtSecondVal = intOneDimPoly.evalAt(secondVal);

    double integralOverRange = intAtSecondVal - intAtFirstVal;

    return integralOverRange;

};


OneDimPoly OneDimPoly::multOneDimPoly(OneDimPoly otherOneDimPoly){

    std::vector<double> otherCoeffArray = otherOneDimPoly.getCoeffArray();
    int otherPolyOrder = otherOneDimPoly.getPolyOrder();

    int newPolyOrder = otherPolyOrder + polyOrder;
    std::vector<double> newCoeffArray(newPolyOrder + 1);
    // There's got to be a faster way to zero the array
    for (int newCoeffIdx = 0; newCoeffIdx <= newPolyOrder; ++newCoeffIdx) {
        newCoeffArray[newCoeffIdx] = 0.0;
    };
    
    for (int thisCoeffIdx = 0; thisCoeffIdx <= polyOrder; ++thisCoeffIdx) {
        for (int otherCoeffIdx = 0; otherCoeffIdx <= otherPolyOrder; ++otherCoeffIdx) {
            newCoeffArray[thisCoeffIdx + otherCoeffIdx] += coeffArray[thisCoeffIdx]*otherCoeffArray[otherCoeffIdx];
        };
    };

    OneDimPoly newOneDimPoly(newCoeffArray);

    return newOneDimPoly;
};

OneDimPoly OneDimPoly::addOneDimPoly(OneDimPoly otherOneDimPoly) {
    
    std::vector<double> otherCoeffArray = otherOneDimPoly.getCoeffArray();
    int otherPolyOrder = otherOneDimPoly.getPolyOrder();
    int newPolyOrder = std::max(polyOrder,otherPolyOrder);
    std::vector<double> newCoeffArray(newPolyOrder + 1);

    for (int coeffIdx = 0; coeffIdx <= newPolyOrder; ++coeffIdx) {

        newCoeffArray[coeffIdx] = 0.0;

        if (coeffIdx <= polyOrder) {
            newCoeffArray[coeffIdx] += coeffArray[coeffIdx];
        };
        if (coeffIdx <= otherPolyOrder) {
            newCoeffArray[coeffIdx] += otherCoeffArray[coeffIdx];
        };
    };

    OneDimPoly newOneDimPoly(newCoeffArray);
    return newOneDimPoly;
};

OneDimPoly OneDimPoly::subOneDimPoly(OneDimPoly otherOneDimPoly) {
    
    std::vector<double> otherCoeffArray = otherOneDimPoly.getCoeffArray();
    int otherPolyOrder = otherOneDimPoly.getPolyOrder();
    int newPolyOrder = std::max(polyOrder,otherPolyOrder);
    std::vector<double> newCoeffArray(newPolyOrder + 1);

    for (int coeffIdx = 0; coeffIdx <= newPolyOrder; ++coeffIdx) {

        newCoeffArray[coeffIdx] = 0.0;

        if (coeffIdx <= polyOrder) {
            newCoeffArray[coeffIdx] += coeffArray[coeffIdx];
        };
        if (coeffIdx <= otherPolyOrder) {
            newCoeffArray[coeffIdx] -= otherCoeffArray[coeffIdx];
        };
    };
    
    OneDimPoly newOneDimPoly(newCoeffArray);
    return newCoeffArray;
};

OneDimPoly OneDimPoly::multScalar(double scalarMult) {

    std::vector<double> newCoeffArray = coeffArray;
    for (int coeffIdx = 0; coeffIdx <= polyOrder; ++coeffIdx) {
        newCoeffArray[coeffIdx] *= scalarMult;
    };
    OneDimPoly newOneDimPoly(newCoeffArray);
    return newOneDimPoly;
};

OneDimPoly OneDimPoly::divScalar(double scalarDiv) {

    std::vector<double> newCoeffArray = coeffArray;
    for (int coeffIdx = 0; coeffIdx <= polyOrder; ++coeffIdx) {
        newCoeffArray[coeffIdx] /= scalarDiv;
    };
    OneDimPoly newOneDimPoly(newCoeffArray);
    return newOneDimPoly;
};

OneDimPoly OneDimPoly::addScalar(double scalarAdd) {

    std::vector<double> newCoeffArray = coeffArray;
    newCoeffArray[0] += scalarAdd;
    OneDimPoly newOneDimPoly(newCoeffArray);
    return newOneDimPoly;
};

OneDimPoly OneDimPoly::subScalar(double scalarSub) {

    std::vector<double> newCoeffArray = coeffArray;
    newCoeffArray[0] -= scalarSub;
    OneDimPoly newOneDimPoly(newCoeffArray);
    return newOneDimPoly;
};
