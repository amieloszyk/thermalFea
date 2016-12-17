#include "polyArray.h"
#include <iostream>

PolyArray::PolyArray() {
    numbOfRows = 0;
    numbOfCols = 0;
};

void PolyArray::addRow(std::vector< TwoDimPoly > polyRow) {

    if (numbOfCols == 0) {
        numbOfCols = polyRow.size();
    } else {
        if (polyRow.size() != numbOfCols) {
            //TODO: Make this a real exception
            throw;
        };
    };

    polyArrayTwoDim.push_back(polyRow);

    numbOfRows++;
};

std::vector< std::vector< double > > PolyArray::evalAt(double xVal, double yVal) {

    std::vector< std::vector< double > > arrayVals;
    std::vector <double> rowVals;

    for (int rowIdx = 0; rowIdx < numbOfRows; ++rowIdx) {
        for (int colIdx = 0; colIdx < numbOfCols; ++colIdx) {
            rowVals.push_back(polyArrayTwoDim[rowIdx][colIdx].evalAt(xVal,yVal));
        };
        arrayVals.push_back(rowVals);
        rowVals.clear();
    };

    return arrayVals;
};

PolyArray PolyArray::transpose() {

    PolyArray transArray;
    std::vector <TwoDimPoly> transRow;

    for (int colIdx = 0; colIdx < numbOfCols; ++colIdx) {
        for (int rowIdx = 0; rowIdx < numbOfRows; ++rowIdx) {
            transRow.push_back(polyArrayTwoDim[rowIdx][colIdx]);
        };
        transArray.addRow(transRow);
        transRow.clear();
    };

    return transArray;
};

TwoDimPoly PolyArray::getPoly(int rowIdx, int colIdx) {
    return polyArrayTwoDim[rowIdx][colIdx];
};

std::vector<int> PolyArray::getArraySize() {
    std::vector<int> arraySize(2);
    arraySize[0] = numbOfRows;
    arraySize[1] = numbOfCols;
    return arraySize;
}

PolyArray PolyArray::matMultPolyArray(PolyArray otherPolyArray) {

    std::vector<int> otherArraySize = otherPolyArray.getArraySize();
    int otherNumbOfRows = otherArraySize[0];
    int otherNumbOfCols = otherArraySize[1];

    if (numbOfCols != otherNumbOfRows) {
        //TODO: Make this a real exception
        throw;
    };

    std::vector <TwoDimPoly> prodRow;
    PolyArray prodArray;

    std::vector<OneDimPoly> zeroOneDimPolyVect;
    std::vector<double> zeroOneDimCoeffVect;
    zeroOneDimCoeffVect.push_back(0.0);
    zeroOneDimPolyVect.push_back(zeroOneDimCoeffVect);
    TwoDimPoly tempPoly(zeroOneDimPolyVect);
    TwoDimPoly prodPoly(zeroOneDimPolyVect);

    for (int rowIdx = 0; rowIdx < numbOfRows; ++rowIdx) {

        for (int newColIdx = 0; newColIdx < otherNumbOfCols; ++newColIdx) {

            prodPoly = TwoDimPoly(zeroOneDimPolyVect);

            for (int colIdx = 0; colIdx < numbOfCols; ++colIdx) {

                tempPoly = polyArrayTwoDim[rowIdx][colIdx].multTwoDimPoly(otherPolyArray.getPoly(colIdx,newColIdx));
                prodPoly = prodPoly.addTwoDimPoly(tempPoly);
            };

            prodRow.push_back(prodPoly);
        };

        prodArray.addRow(prodRow);
        prodRow.clear();
    };

    return prodArray;
};

PolyArray PolyArray::matMultScalarAhead(std::vector< std::vector< double > > doubleMatrix) {
    
    int otherNumbOfRows = doubleMatrix.size();
    int otherNumbOfCols = doubleMatrix[0].size();

    if (numbOfCols != otherNumbOfRows) {
        //TODO: Make this a real exception
        throw;
    };

    std::vector <TwoDimPoly> prodRow;
    PolyArray prodArray;

    std::vector<OneDimPoly> zeroOneDimPolyVect;
    std::vector<double> zeroOneDimCoeffVect;
    zeroOneDimCoeffVect.push_back(0.0);
    zeroOneDimPolyVect.push_back(zeroOneDimCoeffVect);
    TwoDimPoly tempPoly(zeroOneDimPolyVect);
    TwoDimPoly prodPoly(zeroOneDimPolyVect);

    for (int rowIdx = 0; rowIdx < otherNumbOfRows; ++rowIdx) {
        std::cout << "row" << rowIdx << std::endl;
        for (int newColIdx = 0; newColIdx < numbOfCols; ++newColIdx) {
            std::cout << "newCol" << newColIdx << std::endl;
            prodPoly = TwoDimPoly(zeroOneDimPolyVect);

            for (int colIdx = 0; colIdx < otherNumbOfCols; ++colIdx) {
                std::cout << "col" << colIdx << std::endl;
                tempPoly = polyArrayTwoDim[colIdx][newColIdx].multScalar(doubleMatrix[rowIdx][colIdx]);
                prodPoly = prodPoly.addTwoDimPoly(tempPoly);
            };

            prodRow.push_back(prodPoly);
        };

        prodArray.addRow(prodRow);
        prodRow.clear();
    };

    return prodArray;
};

PolyArray PolyArray::matMultScalarBehind(std::vector< std::vector< double > > doubleMatrix) {
    
    int otherNumbOfRows = doubleMatrix.size();
    int otherNumbOfCols = doubleMatrix[0].size();

    if (numbOfCols != otherNumbOfRows) {
        //TODO: Make this a real exception
        throw;
    };

    std::vector <TwoDimPoly> prodRow;
    PolyArray prodArray;

    std::vector<OneDimPoly> zeroOneDimPolyVect;
    std::vector<double> zeroOneDimCoeffVect;
    zeroOneDimCoeffVect.push_back(0.0);
    zeroOneDimPolyVect.push_back(zeroOneDimCoeffVect);
    TwoDimPoly tempPoly(zeroOneDimPolyVect);
    TwoDimPoly prodPoly(zeroOneDimPolyVect);

    for (int rowIdx = 0; rowIdx < numbOfRows; ++rowIdx) {

        for (int newColIdx = 0; newColIdx < otherNumbOfCols; ++newColIdx) {

            prodPoly = TwoDimPoly(zeroOneDimPolyVect);

            for (int colIdx = 0; colIdx < numbOfCols; ++colIdx) {

                tempPoly = polyArrayTwoDim[rowIdx][colIdx].multScalar(doubleMatrix[colIdx][newColIdx]);
                prodPoly = prodPoly.addTwoDimPoly(tempPoly);
            };

            prodRow.push_back(prodPoly);
        };

        prodArray.addRow(prodRow);
        prodRow.clear();
    };

    return prodArray;
};

PolyArray PolyArray::multScalar(double multVal) {

    std::vector <TwoDimPoly> tempRow;
    PolyArray newPolyArray;
    for (int rowIdx = 0; rowIdx < numbOfRows; ++rowIdx) {
        for (int colIdx = 0; colIdx < numbOfCols; ++colIdx) {
            tempRow.push_back(polyArrayTwoDim[rowIdx][colIdx].multScalar(multVal));
        };
        newPolyArray.addRow(tempRow);
        tempRow.clear();
    };
    return newPolyArray;
};

PolyArray XyShapeFuncVector::getGrad() {
    
    // Broken?

    std::vector <TwoDimPoly> tempRow;
    PolyArray newShapeFunc;

    for (int colIdx = 0; colIdx < numbOfCols; ++colIdx) {
        tempRow.push_back(polyArrayTwoDim[0][colIdx].getDerivVarOne());
    };
    newShapeFunc.addRow(tempRow);

    for (int colIdx = 0; colIdx < numbOfCols; ++colIdx) {
        tempRow.push_back(polyArrayTwoDim[0][colIdx].getDerivVarTwo());
    };
    newShapeFunc.addRow(tempRow);

    return newShapeFunc;

};
