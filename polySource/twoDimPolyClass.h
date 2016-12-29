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
        TwoDimPoly addTwoDimPoly(TwoDimPoly otherTwoDimPoly);
        double findIntegralOverRange(double varOneFirstVal, double varOneSecondVal, 
                                     double varTwoFirstVal, double varTwoSecondVal);

        // Yet to be implemented
        
        TwoDimPoly subTwoDimPoly(TwoDimPoly otherTwoDimPoly);
        TwoDimPoly multOneDimPoly(OneDimPoly otherOneDimPoly);

        void printCoeffs();

};
