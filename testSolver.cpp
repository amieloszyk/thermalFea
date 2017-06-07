#include <iostream>
// #include <vector>
#include "solverClasses.cpp"

int main() {
    std::vector< std::vector< double > > given_aMatrix;
    std::vector< double > given_bVector;
    std::vector< double > fillerVect;

    fillerVect.push_back(2.0);
    fillerVect.push_back(14.0);
    fillerVect.push_back(8.0);
    given_aMatrix.push_back(fillerVect);

    fillerVect[0] = 2.0;
    fillerVect[1] = 6.0;
    fillerVect[2] = 3.0;
    given_aMatrix.push_back(fillerVect);

    fillerVect[0] = 3.0;
    fillerVect[1] = 5.0;
    fillerVect[2] = 3.0;
    given_aMatrix.push_back(fillerVect);

    given_bVector.push_back(54.0);
    given_bVector.push_back(23.0);
    given_bVector.push_back(22.0);

    std::vector< double > found_solVector = gaussianElimSolve(given_aMatrix,
                                                              given_bVector);
    // std::vector< std::vector< double > > upperMatrix = gaussianElimSolve(given_aMatrix,
    //                                                           given_bVector);
    
    std::cout << "| 2.0  14.0  8.0 |       | 54.0 | " << std::endl;
    std::cout << "| 2.0   6.0  3.0 | * x = | 23.0 | " << std::endl;
    std::cout << "| 3.0   5.0  3.0 |       | 22.0 | " << std::endl;

    std::cout << "    | 1.0 | " << std::endl;
    std::cout << "x = | 2.0 | " << std::endl;
    std::cout << "    | 3.0 | " << std::endl;

    std::cout << "          | " << found_solVector[0] << " |" << std::endl;
    std::cout << "x_found = | " << found_solVector[1] << " |" << std::endl;
    std::cout << "          | " << found_solVector[2] << " |" << std::endl;

    // std::cout << "| " << upperMatrix[0][0] << "," << upperMatrix[0][1] << "," <<  upperMatrix[0][2] << " |" << std::endl;
    // std::cout << "| " << upperMatrix[1][0] << "," << upperMatrix[1][1] << "," <<  upperMatrix[1][2] << " |" << std::endl;
    // std::cout << "| " << upperMatrix[2][0] << "," << upperMatrix[2][1] << "," <<  upperMatrix[2][2] << " |" << std::endl;

}
