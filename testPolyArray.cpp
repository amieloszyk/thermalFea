#include <iostream>
#include <math.h>
#include "polyArray.cpp"

int main() {

    std::vector<OneDimPoly> oneDimPolyVect;
    std::vector<double> oneDimCoeffs;

    // f(x,y) = 1.0 + (3.0)*y + (0.5+0.3*x-7.0*x**2)*y**2
    oneDimCoeffs.push_back(1.0);
    oneDimPolyVect.push_back(OneDimPoly(oneDimCoeffs));
    oneDimCoeffs.clear();

    oneDimCoeffs.push_back(3.0);
    oneDimPolyVect.push_back(OneDimPoly(oneDimCoeffs));
    oneDimCoeffs.clear();

    oneDimCoeffs.push_back(0.5);
    oneDimCoeffs.push_back(0.3);
    oneDimCoeffs.push_back(-7.0);
    oneDimPolyVect.push_back(OneDimPoly(oneDimCoeffs));
    oneDimCoeffs.clear();

    TwoDimPoly testFuncF(oneDimPolyVect);
    oneDimPolyVect.clear();

    // g(x,y) = (2.5+8.9*x)*y + (4.2*x**3)*y**3
    oneDimCoeffs.push_back(0.0);
    oneDimPolyVect.push_back(OneDimPoly(oneDimCoeffs));
    oneDimCoeffs.clear();

    oneDimCoeffs.push_back(2.5);
    oneDimCoeffs.push_back(8.9);
    oneDimPolyVect.push_back(OneDimPoly(oneDimCoeffs));
    oneDimCoeffs.clear();

    oneDimCoeffs.push_back(0.0);
    oneDimPolyVect.push_back(OneDimPoly(oneDimCoeffs));
    oneDimCoeffs.clear();

    oneDimCoeffs.push_back(0.0);
    oneDimCoeffs.push_back(0.0);
    oneDimCoeffs.push_back(0.0);
    oneDimCoeffs.push_back(4.2);
    oneDimPolyVect.push_back(OneDimPoly(oneDimCoeffs));
    oneDimCoeffs.clear();

    TwoDimPoly testFuncG(oneDimPolyVect);
    oneDimPolyVect.clear();

    // h(x,y) = 4.0*f(x,y)
    TwoDimPoly testFuncH = testFuncF.multScalar(4.0);

    // i(x,y) = f(x,y) + g(x,y)
    TwoDimPoly testFuncI = testFuncF.addTwoDimPoly(testFuncG);

    // j(x,y) = dg(x,y)/dx
    TwoDimPoly testFuncJ = testFuncG.getDerivVarOne();

    // k(x,y) = d2f(x,y)/dxdy
    TwoDimPoly testFuncK = testFuncF.getDerivVarOne().getDerivVarTwo();

    std::cout << std::endl << "Test functions:" << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "f(x,y) = 1.0 + (3.0)*y + (0.5+0.3*x-7.0*x**2)*y**2" << std::endl;
    std::cout << "g(x,y) = (2.5+8.9*x)*y + (4.2*x**3)*y**3" << std::endl;
    std::cout << "h(x,y) = 4.0*f(x,y)" << std::endl;
    std::cout << "i(x,y) = f(x,y) + g(x,y)" << std::endl;
    std::cout << "j(x,y) = dg(x,y)/dx" << std::endl;
    std::cout << "k(x,y) = d2f(x,y)/dxdy" << std::endl;

    std::cout << std::endl << "Check Test Functions" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "f(2.4,-6.7) = -1774.299 ?= " << testFuncF.evalAt(2.4,-6.7) << std::endl;
    std::cout << "g(2.4,-6.7) = -17622.4023904 ?= " << testFuncG.evalAt(2.4,-6.7) << std::endl;
    std::cout << "h(2.4,-6.7) = -7097.196 ?= " << testFuncH.evalAt(2.4,-6.7) << std::endl;
    std::cout << "i(2.4,-6.7) = -19396.7013904 ?= " << testFuncI.evalAt(2.4,-6.7) << std::endl;
    std::cout << "j(2.4,-6.7) = -21887.805488 ?= " << testFuncJ.evalAt(2.4,-6.7) << std::endl;
    std::cout << "k(2.4,-6.7) = 446.22 ?= " << testFuncK.evalAt(2.4,-6.7) << std::endl;

    std::cout << std::endl << "Test Poly Array:" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "N(x,y) = [[ f(x,y), g(x,y), h(x,y) ]"  << std::endl;
    std::cout << "          [ i(x,y), j(x,y), k(x,y) ]]" << std::endl;

    PolyArray testPolyArray;
    std::vector< TwoDimPoly > dummyPolyRow;
    
    dummyPolyRow.push_back(testFuncF);
    dummyPolyRow.push_back(testFuncG);
    dummyPolyRow.push_back(testFuncH);

    testPolyArray.addRow(dummyPolyRow);
    dummyPolyRow.clear();

    dummyPolyRow.push_back(testFuncI);
    dummyPolyRow.push_back(testFuncJ);
    dummyPolyRow.push_back(testFuncK);

    testPolyArray.addRow(dummyPolyRow);
    dummyPolyRow.clear();

    std::cout << std::endl << "Check Test Array" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "N(17.3,9.6) = [[ -192524.0, 1.92413×10^7, -770095.0 ]"  << std::endl;
    std::cout << "               [ 1.90488×10^7, 3.33647×10^6, -4644.48 ]]" << std::endl << std::endl;

    std::vector< std::vector <double > > testValArray = testPolyArray.evalAt(17.3, 9.6);
    std::cout << "N_test(17.3,9.6) = [[ " << testValArray[0][0] << ", " << testValArray[0][1];
    std::cout << ", " << testValArray[0][2] << " ]" << std::endl;
    std::cout << "                    [ " << testValArray[1][0] << ", " << testValArray[1][1];
    std::cout << ", " << testValArray[1][2] << " ]]" << std::endl << std::endl;

    std::cout << "Check Transpose Test Array" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "trans(N)(17.3,9.6) = [[ -192524.0, 1.90488×10^7 ]"  << std::endl;
    std::cout << "                      [ 1.92413×10^7, 3.33647×10^6 ]" << std::endl; 
    std::cout << "                      [ -770095.0, -4644.48 ]]" << std::endl << std::endl;

    PolyArray transTestPolyArray = testPolyArray.transpose();
    std::vector< std::vector <double > > testTransValArray = transTestPolyArray.evalAt(17.3, 9.6);
    std::cout << "trans(N_test)(17.3,9.6) = [[ " << testTransValArray[0][0] << ", " << testTransValArray[0][1] << "]" << std::endl;
    std::cout << "                           [ " << testTransValArray[1][0] << ", " << testTransValArray[1][1] << "]" << std::endl;
    std::cout << "                           [ " << testTransValArray[2][0] << ", " << testTransValArray[2][1] << "]]" << std::endl  << std::endl;

    std::cout << std::endl <<"Test Getting an Entry" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "N(2,3)(1.0,3.0) = -82.2" << std::endl;
    std::cout << "N_test(2,3)(1.0,3.0) = " << testPolyArray.getPoly(1,2).evalAt(1.0,3.0) << std::endl;

    std::cout << std::endl << "Test Getting Array Size" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "size(N) = 2x3" <<std::endl;
    std::cout << "size(N_test) = " << testPolyArray.getArraySize()[0] << "x"  << testPolyArray.getArraySize()[1] <<std::endl;

    std::cout << std::endl << "Test Matrix Multiplication" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "N*trans(N)(17.3,9.6) = [[3.70857×10^14 , 6.05342×10^13]" << std::endl;
    std::cout << "                        [6.05342×10^13 , 3.73989×10^14]]" << std::endl;
    std::cout << "size(N*trans(N)) = 2x2" << std::endl;

    PolyArray multTestArray = testPolyArray.matMultPolyArray(transTestPolyArray);
    std::vector< std::vector <double > > testMultVal = multTestArray.evalAt(17.3, 9.6);
    std::cout << "N_test*trans(N_test)(17.3,9.6) = [[" << testMultVal[0][0] << "," << testMultVal[0][1] << "]" << std::endl;
    std::cout << "                                  [" << testMultVal[1][0] << "," << testMultVal[1][1] << "]]" << std::endl;
    std::cout << "size(N_test*trans(N_test)) = " << multTestArray.getArraySize()[0] << "x"  << multTestArray.getArraySize()[1] <<std::endl;

    // Test double matrix multiplication
    std::vector< std::vector < double > > scalarMatrix;
    std::vector < double > scalarRow;
    scalarRow.push_back(1.0);
    scalarRow.push_back(2.0);
    scalarMatrix.push_back(scalarRow);
    scalarRow.clear();
    scalarRow.push_back(3.0);
    scalarRow.push_back(4.0);
    scalarMatrix.push_back(scalarRow);
    scalarRow.clear();
    scalarRow.push_back(5.0);
    scalarRow.push_back(6.0);
    scalarMatrix.push_back(scalarRow);
    scalarRow.clear();

    std::cout << std::endl << "Test Scalar Matrix Multiplication" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "scalMat = [[ " << scalarMatrix[0][0] << ", " << scalarMatrix[0][1] << "]" << std::endl;
    std::cout << "           [ " << scalarMatrix[1][0] << ", " << scalarMatrix[1][1] << "]" << std::endl;
    std::cout << "           [ " << scalarMatrix[2][0] << ", " << scalarMatrix[2][1] << "]]" << std::endl  << std::endl;
    
    std::vector< std::vector < double > > scalarMultProd = testPolyArray.matMultScalarBehind(scalarMatrix).evalAt(17.3,9.6);
    std::cout << "known(N(17.3,9.6)*scalarMat) = [[5.3681x10^7, 7.19595x10^7]" << std::endl;
    std::cout << "                                [2.9035×10^7, 5.14156×10^7]" << std::endl << std::endl;
    std::cout << "N(17.3,9.6)*scalarMat = [[ " << scalarMultProd[0][0] << ", " << scalarMultProd[0][1] << "]" << std::endl;
    std::cout << "                         [ " << scalarMultProd[1][0] << ", " << scalarMultProd[1][1] << "]" << std::endl << std::endl;

    scalarMultProd.clear();
    scalarMultProd = testPolyArray.matMultScalarAhead(scalarMatrix).evalAt(17.3,9.6);
    std::cout << "known(scalarMat*N(17.3,9.6)) = [[3.7905076x10^7, 2.5914240x10^7, -779384      ]" << std::endl;
    std::cout << "                                [7.5617628x10^7, 7.1069780x10^7, -2.32886×10^6]" << std::endl;
    std::cout << "                                [1.1333018x10^8, 1.1622532x10^8, -3.87834×10^6]" << std::endl << std::endl;
    std::cout << "scalarMat*N(17.3,9.6) = [[ " << scalarMultProd[0][0] << ", " << scalarMultProd[0][1] << ", " << scalarMultProd[0][2] << "]" << std::endl;
    std::cout << "                         [ " << scalarMultProd[1][0] << ", " << scalarMultProd[1][1] << ", " << scalarMultProd[1][2] << "]" << std::endl;
    std::cout << "                         [ " << scalarMultProd[2][0] << ", " << scalarMultProd[2][1] << ", " << scalarMultProd[2][2] << "]" << std::endl << std::endl;

}; 