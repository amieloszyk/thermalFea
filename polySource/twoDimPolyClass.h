#include <vector>
#include "oneDimPoly.cpp"

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
        
        // Yet to be implemented
        TwoDimPoly addTwoDimPoly(TwoDimPoly otherTwoDimPoly);
        TwoDimPoly subTwoDimPoly(TwoDimPoly otherTwoDimPoly);
        TwoDimPoly multOneDimPoly(OneDimPoly otherOneDimPoly);

        
        double findIntegralOverRange(double varOneFirstVal, double varOneSecondVal, 
                                     double varTwoFirstVal, double varTwoSecondVal);

        void printCoeffs();

};
