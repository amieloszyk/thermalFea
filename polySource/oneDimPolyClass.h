#include <vector>

class OneDimPoly {

    private:
        std::vector<double> coeffArray;
        int polyOrder;

    public:

        OneDimPoly(std::vector<double>);

        double evalAt(double varVal);

        std::vector<double> getCoeffArray();
        int getPolyOrder();

        OneDimPoly addOneDimPoly(OneDimPoly otherOneDimPoly);
        OneDimPoly subOneDimPoly(OneDimPoly otherOneDimPoly);
        OneDimPoly multOneDimPoly(OneDimPoly otherOneDimPoly);

        OneDimPoly multScalar(double scalarMult);
        OneDimPoly divScalar(double scalarDiv);
        OneDimPoly addScalar(double scalarAdd);
        OneDimPoly subScalar(double scalarSub);

        OneDimPoly getDerivative();
        double findIntegralOverRange(double firstVal, double secondValue);
};


