#include <vector>
#include "polySource/twoDimPoly.cpp"

class PolyArray {

    protected:

    std::vector< std::vector< TwoDimPoly > > polyArrayTwoDim;
    int numbOfRows;
    int numbOfCols;

    public:

    PolyArray();

    void addRow(std::vector< TwoDimPoly > polyRow);
    std::vector< std::vector< double > > evalAt(double xVal, double yVal);
    PolyArray transpose();
    TwoDimPoly getPoly(int rowIdx, int colIdx);
    std::vector<int> getArraySize();
    PolyArray matMultPolyArray(PolyArray otherPolyArray);
    PolyArray matMultScalarAhead(std::vector< std::vector< double > > doubleMatrix);
    PolyArray matMultScalarBehind(std::vector< std::vector< double > > doubleMatrix);
    PolyArray multScalar(double multVal);
    std::vector< std::vector< double > > findIntegralOverRange(double varOneFirstVal, double varOneSecondVal, 
                                                               double varTwoFirstVal, double varTwoSecondVal);

    
};

class XyShapeFuncVector : public PolyArray{
    // Matrix of shape functions for 2-D in x-y plane
    // varOne is X, varTwo is Y
    
    public:

    XyShapeFuncVector() : PolyArray() {};

    PolyArray getGrad();
};

