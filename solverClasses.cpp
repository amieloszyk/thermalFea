#include <vector>
#include <iostream>

std::vector< double > gaussianElimSolve(std::vector< std::vector< double > > aMatrix,
                                        std::vector< double > bVector) {
    int matrixSize = bVector.size();

    for (int idx = 0; idx < matrixSize; ++idx){
        
        // TODO: jdx loops should be combined

        double divVal = aMatrix[idx][idx];
        bVector[idx] /= divVal;
        for (int jdx = idx; jdx < matrixSize; ++jdx){
            aMatrix[idx][jdx] /= divVal;
        };

        for (int jdx = idx+1; jdx < matrixSize; ++jdx){
            double multVal = aMatrix[jdx][idx];
            for (int kdx = idx; kdx < matrixSize; ++kdx){
                // std::cout << idx << "  " << jdx << "  " << kdx << "  " << aMatrix[jdx][kdx] << "  " << aMatrix[idx][kdx] << "  " << multVal << std::endl; 
                aMatrix[jdx][kdx] -= aMatrix[idx][kdx]*multVal;
            };
            bVector[jdx] -= bVector[idx]*multVal;
        };
    };

    std::vector< double > solVector = bVector;
    for (int idx = matrixSize-2; idx >= 0; --idx){
        for (int jdx = idx+1; jdx < matrixSize; ++jdx){
            solVector[idx] -= aMatrix[idx][jdx]*solVector[jdx];
        };
    };

    return solVector;

    // TODO: Finding the upper triangular matrix and the back substitution should be broken out into separate methods
}
