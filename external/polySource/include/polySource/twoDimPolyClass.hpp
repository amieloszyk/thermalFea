#pragma once

#include "oneDimPolyClass.hpp"

#include <vector>

class TwoDimPoly {

    private:

        std::vector<OneDimPoly> varOnePolyArray;
        int varTwoPolyOrder;

    public:

        TwoDimPoly(std::vector<OneDimPoly>);
        
        double evalAt(double varOneVal, double varTwoVal);
        
        std::vector<OneDimPoly> getVarOneArray();
        int getVarTwoOrder();

        TwoDimPoly multTwoDimPoly(TwoDimPoly otherTwoDimPoly);
        TwoDimPoly getDerivVarOne();
        TwoDimPoly getDerivVarTwo();
        TwoDimPoly multScalar(double scalarMult);
        TwoDimPoly addTwoDimPoly(TwoDimPoly otherTwoDimPoly);
        double findIntegralOverRange(double varOneFirstVal, double varOneSecondVal, 
                                     double varTwoFirstVal, double varTwoSecondVal);
        OneDimPoly getFixedVarOnePoly(double fixedVarOne);

        // Yet to be implemented
        OneDimPoly getFixedVarTwoPoly(double fixedVarTwo);
        
        TwoDimPoly subTwoDimPoly(TwoDimPoly otherTwoDimPoly);
        TwoDimPoly multOneDimPoly(OneDimPoly otherOneDimPoly);

        void printCoeffs();

};
