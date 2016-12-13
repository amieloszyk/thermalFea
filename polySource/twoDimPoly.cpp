#include "twoDimPolyClass.h"
#include <math.h>
#include <algorithm>

TwoDimPoly::TwoDimPoly(std::vector<OneDimPoly> inpPolyArray) {
    varOnePolyArray = inpPolyArray;
    varTwoPolyOrder = varOnePolyArray.size() - 1;
};

double TwoDimPoly::evalAt(double varOneVal, double varTwoVal) {
    
    double returnVal = 0.0;

    double varTwoMult;
    double varOneMult;

    for (int varTwoIdx = 0; varTwoIdx <= varTwoPolyOrder; ++varTwoIdx) {

        varTwoMult = pow(varTwoVal,varTwoIdx);
        
        varOneMult = varOnePolyArray[varTwoIdx].evalAt(varOneVal);

        returnVal += varOneMult*varTwoMult;
    };

    return returnVal;
};

TwoDimPoly TwoDimPoly::multTwoDimPoly(TwoDimPoly otherTwoDimPoly) {
    std::vector<OneDimPoly> otherVarOneArray = otherTwoDimPoly.getVarOneArray();
    int otherVarTwoOrder = otherTwoDimPoly.getVarTwoOrder();

    int newPolyOrder = otherVarTwoOrder + varTwoPolyOrder;
    std::vector<OneDimPoly> newVarTwoArray;
    std::vector<double> dummyVarOneCoeffs(1);
    dummyVarOneCoeffs[0] = 0.0;
    for (int newArrayIdx = 0; newArrayIdx <= newPolyOrder; ++newArrayIdx) {
        newVarTwoArray.push_back(dummyVarOneCoeffs);
    };

    OneDimPoly dummyOneDimPoly = OneDimPoly(dummyVarOneCoeffs);
    for (int thisCoeffIdx = 0; thisCoeffIdx <= varTwoPolyOrder; ++thisCoeffIdx) {
        for (int otherCoeffIdx = 0; otherCoeffIdx <= otherVarTwoOrder; ++otherCoeffIdx) {
            dummyOneDimPoly = varOnePolyArray[thisCoeffIdx].multOneDimPoly(otherVarOneArray[otherCoeffIdx]);
            newVarTwoArray[thisCoeffIdx + otherCoeffIdx] = newVarTwoArray[thisCoeffIdx + otherCoeffIdx].addOneDimPoly(dummyOneDimPoly);
        };
    };
    
    TwoDimPoly newTwoDimPoly(newVarTwoArray);
    
    return newTwoDimPoly;
};

TwoDimPoly TwoDimPoly::addTwoDimPoly(TwoDimPoly otherTwoDimPoly) {
    
    std::vector<OneDimPoly> otherVarOneArray = otherTwoDimPoly.getVarOneArray();
    int otherVarTwoOrder = otherTwoDimPoly.getVarTwoOrder();
    int newVarTwoPolyOrder = std::max(varTwoPolyOrder,otherVarTwoOrder);
    std::vector<OneDimPoly> newVarTwoArray;
    std::vector<double> dummyVarOneCoeff(1);
    dummyVarOneCoeff[0] = 0.0;

    for (int varTwoIdx = 0; varTwoIdx <= newVarTwoPolyOrder; ++varTwoIdx) {
        
        newVarTwoArray.push_back(OneDimPoly(dummyVarOneCoeff));

        if (varTwoIdx <= varTwoPolyOrder) {
            newVarTwoArray[varTwoIdx] = newVarTwoArray[varTwoIdx].addOneDimPoly(varOnePolyArray[varTwoIdx]);
        };
        if (varTwoIdx <= otherVarTwoOrder) {
            newVarTwoArray[varTwoIdx] = newVarTwoArray[varTwoIdx].addOneDimPoly(otherVarOneArray[varTwoIdx]);
        };
    };
    
    TwoDimPoly newTwoDimPoly(newVarTwoArray);

    return newTwoDimPoly;
};


std::vector<OneDimPoly> TwoDimPoly::getVarOneArray() {
    return varOnePolyArray;
};

int TwoDimPoly::getVarTwoOrder() {
    return varTwoPolyOrder;
};


TwoDimPoly TwoDimPoly::getDerivVarOne() {
    
    std::vector<OneDimPoly> newVarTwoArray;
    
    for (int varTwoIdx = 0; varTwoIdx <= varTwoPolyOrder; ++varTwoIdx) {
        OneDimPoly varOneDeriv = varOnePolyArray[varTwoIdx].getDerivative(); 
        newVarTwoArray.push_back(varOneDeriv);
    };

    TwoDimPoly newTwoDimPoly(newVarTwoArray);
    return newTwoDimPoly; 
};

TwoDimPoly TwoDimPoly::getDerivVarTwo() {

    int numbOfDerivTerms = varTwoPolyOrder;
    std::vector<OneDimPoly> newVarTwoArray;
    

    if (numbOfDerivTerms == 0) {
        std::vector<double> dummyVarOneArray;
        dummyVarOneArray.push_back(0.0);
        newVarTwoArray.push_back(dummyVarOneArray);
    } 
    else {
        for (int coeffIdx = 1; coeffIdx <= numbOfDerivTerms; ++coeffIdx) {
            newVarTwoArray.push_back(varOnePolyArray[coeffIdx].multScalar(double(coeffIdx)));
        };
    };

    TwoDimPoly varTwoDerivPoly(newVarTwoArray);
    return varTwoDerivPoly;

};

TwoDimPoly TwoDimPoly::multScalar(double scalarMult) {
    
    std::vector<OneDimPoly> newVarOneArray;

    for (int coeffIdx = 0; coeffIdx <= varTwoPolyOrder; ++coeffIdx) {
        newVarOneArray.push_back(varOnePolyArray[coeffIdx].multScalar(scalarMult));
    };

    TwoDimPoly newVarTwoPoly(newVarOneArray);
    return newVarTwoPoly;

};
