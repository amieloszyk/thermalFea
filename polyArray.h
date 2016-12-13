#include <vector>
#include "polySource/twoDimPoly.cpp"

class PolyArray {

    private:

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

    // To be implemented
    TwoDimPoly multScalar(double multVal);
    PolyArray getPolyArrayGrad();
};

class XyShapeMatrix : public PolyArray{
    // Matrix of shape functions for 2-D in x-y plane
};

