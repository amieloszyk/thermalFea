#include <iostream>
#include <vector>
#include "elementClasses.cpp"

void testGeneralElements() {

    GeneralElement testGenElem;
    std::cout << "Test General Element Class Functionality" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    testGenElem.setElementNumber(1234);
    std::cout << "Element number -- Given: 1234; Returned: " << testGenElem.getElementNumber() << std::endl;

    testGenElem.setNumberOfNodes(3);
    std::cout << "Number of Nodes -- Given: 3; Returned: " << testGenElem.getNumberOfNodes() << std::endl;

    bool checkNumbThrow = false;
    try{testGenElem.checkNumbOfNodes(4);}
    catch (...) {checkNumbThrow = true;}
    std::cout << "Test checkNumbOfNodes(4): "; 
    if (checkNumbThrow == true) {
        std::cout << "Caught! :)" << std::endl;
    } 
    else {
        std::cout << "Missed! :(" << std::endl;
    };

    std::vector< int > dummyIntVect;
    dummyIntVect.push_back(3);
    dummyIntVect.push_back(4);
    dummyIntVect.push_back(5);
    testGenElem.setNodeGlobNumber(dummyIntVect);
    dummyIntVect.clear();
    dummyIntVect = testGenElem.getNodeGlobNumber();
    std::cout << "Node numbers -- Given: {3, 4, 5}; Returned: {";
    for (int idx = 0; idx < dummyIntVect.size(); ++idx) {
        std::cout << dummyIntVect[idx] << ", ";
    }; 
    std::cout << "}" << std::endl;
    
    std::vector< double > dummyDoubVect(3);
    std::vector< std::vector< double > > dummyDoubVectVect;
    dummyDoubVect[0] = 1.0;
    dummyDoubVect[1] = 2.0;
    dummyDoubVect[2] = 3.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 3.0;
    dummyDoubVect[1] = 1.0;
    dummyDoubVect[2] = 2.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 2.0;
    dummyDoubVect[1] = 3.0;
    dummyDoubVect[2] = 1.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    testGenElem.setNodeCoords(dummyDoubVectVect);
    dummyDoubVectVect.clear();
    dummyDoubVectVect = testGenElem.getNodeCoords();
    std::cout << "Node coords -- Given: {{1,2,3}, {3,1,2}, {2,3,1}}; Returned: {";
    for (int nodeIdx = 0; nodeIdx < 3; ++nodeIdx) {
        std::cout << "{";
        for(int coordIdx = 0; coordIdx < 3; ++coordIdx) {
            std::cout << dummyDoubVectVect[nodeIdx][coordIdx] << ",";
        }; 
        std::cout << "}, ";
    };
    std::cout << "}" << std::endl;

    std::cout << std::endl << std::endl;


};


void testXyLinearThermalMeloshElement() {
    
    XyLinearThermalMeloshElement testElem;
    std::cout << "Test X-Y Thermal Melosh Element Class Functionality:" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    std::cout << "Number of Nodes -- Known: 4; Returned: " << testElem.getNumberOfNodes() << std::endl;

    std::vector< double > dummyDoubVect(2);
    std::vector< std::vector< double > > dummyDoubVectVect;
    dummyDoubVect[0] = 1.0;
    dummyDoubVect[1] = -1.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 1.0;
    dummyDoubVect[1] = -1.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 1.0;
    dummyDoubVect[1] = 1.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = -1.0;
    dummyDoubVect[1] = 1.0;
    dummyDoubVectVect.push_back(dummyDoubVect);

    bool checkNumbThrow = false;
    try{testElem.setNodeCoords(dummyDoubVectVect);}
    catch (...) {checkNumbThrow = true;}
    std::cout << "Test checkNodeCoords: "; 
    if (checkNumbThrow == true) {
        std::cout << "Caught! :)" << std::endl;
    } 
    else {
        std::cout << "Missed! :(" << std::endl;
    };

    dummyDoubVectVect.clear();

    dummyDoubVect[0] = 0.0;
    dummyDoubVect[1] = 0.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 1.0;
    dummyDoubVect[1] = 0.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 1.0;
    dummyDoubVect[1] = 2.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 0.0;
    dummyDoubVect[1] = 2.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    testElem.setNodeCoords(dummyDoubVectVect);
    dummyDoubVectVect.clear();
    dummyDoubVectVect = testElem.getNodeCoords();
    std::cout << "Global node coords -- Given: {{0,0}, {1,0}, {1,2}, {0,2}}; Returned: {";
    for (int nodeIdx = 0; nodeIdx < 4; ++nodeIdx) {
        std::cout << "{";
        for(int coordIdx = 0; coordIdx < 2; ++coordIdx) {
            std::cout << dummyDoubVectVect[nodeIdx][coordIdx] << ",";
        }; 
        std::cout << "}, ";
    };
    std::cout << "}" << std::endl;

    dummyDoubVectVect.clear();
    dummyDoubVectVect = testElem.getLocNodeCoords();
    std::cout << "Node coords -- Given: {{-0.5,-1.0}, {0.5,-1.0}, {0.5,1.0}, {-0.5,1.0}}; Returned: {";
    for (int nodeIdx = 0; nodeIdx < 4; ++nodeIdx) {
        std::cout << "{";
        for(int coordIdx = 0; coordIdx < 2; ++coordIdx) {
            std::cout << dummyDoubVectVect[nodeIdx][coordIdx] << ",";
        }; 
        std::cout << "}, ";
    };
    std::cout << "}" << std::endl;

    std::cout << "Half width -- Known: 0.5; Returned: " << testElem.getHalfWidth() << std::endl;
    std::cout << "Half height -- Known: 1.0; Returned: " << testElem.getHalfHeight() << std::endl;

    testElem.setElemThick(0.1234);
    std::cout << "Thickness -- Known: 0.1234; Returned: " << testElem.getElemThick() << std::endl;

    dummyDoubVectVect.clear();
    dummyDoubVect[0] = 1.0;
    dummyDoubVect[1] = 2.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 3.0;
    dummyDoubVect[1] = 4.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    testElem.setMatMatrix(dummyDoubVectVect);
    dummyDoubVectVect.clear();
    dummyDoubVectVect = testElem.getMatMatrix();
    std::cout << "Material Matrix -- Known: {{1, 2},   Returned: {{" << dummyDoubVectVect[0][0] << ", " << dummyDoubVectVect[0][1] << "}," << std::endl;
    std::cout << "                           {3, 4}};  Returned:  {" << dummyDoubVectVect[1][0] << ", " << dummyDoubVectVect[1][1] << "}}" << std::endl;

    testElem.setIsoThermCond(12.345);
    dummyDoubVectVect.clear();
    dummyDoubVectVect = testElem.getMatMatrix();
    std::cout << "Isotropic Material Matrix -- Known: {{12.345, 0},   Returned: {{" << dummyDoubVectVect[0][0] << ", " << dummyDoubVectVect[0][1] << "}," << std::endl;
    std::cout << "                                     {0, 12.345}};  Returned:  {" << dummyDoubVectVect[1][0] << ", " << dummyDoubVectVect[1][1] << "}}" << std::endl;

    testElem.setShapeFuncs();
    std::cout << "Shape Function Vector -- " << std::endl;
    std::cout << "Known @ (0.25,-0.25): {0.15625, 0.46875, 0.28125, 0.09375}" << std::endl;
    std::vector< std::vector< double > > testVals = testElem.getShapeFuncs().evalAt(0.25,-0.25);
    std::cout << "Returned @ (0.25,-0.25): {" << testVals[0][0] << ", " << testVals[0][1] << ", " << testVals[0][2] << ", " << testVals[0][3] << "}" << std::endl;

    // Test element from 'Lectur_3_4.pdf' slide #21
    XyLinearThermalMeloshElement slideTestElement;

    dummyDoubVectVect.clear();
    dummyDoubVect[0] = 0.0;
    dummyDoubVect[1] = 0.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 2.0;
    dummyDoubVect[1] = 0.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 2.0;
    dummyDoubVect[1] = 1.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 0.0;
    dummyDoubVect[1] = 1.0;
    dummyDoubVectVect.push_back(dummyDoubVect);

    slideTestElement.setNodeCoords(dummyDoubVectVect);
    slideTestElement.setElemThick(1.3);

    dummyDoubVectVect.clear();
    dummyDoubVect[0] = 4.56;
    dummyDoubVect[1] = 0.0;
    dummyDoubVectVect.push_back(dummyDoubVect);
    dummyDoubVect[0] = 0.0;
    dummyDoubVect[1] = 3.8;
    dummyDoubVectVect.push_back(dummyDoubVect);
    slideTestElement.setMatMatrix(dummyDoubVectVect);

    slideTestElement.setShapeFuncs();
    std::vector< std::vector< double > > slideStiffMatrix = slideTestElement.getStiffnessMatrix();
    std::cout << slideStiffMatrix.size() << "," << slideStiffMatrix[0].size() << std::endl;
    std::cout << std::endl << "Melosh Element Test from slide #21 in Lecture_3_4.pdf" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "Width = 2, Height = 1, kxx = 4.56, kyy = 3.8, t = 1.3" << std::endl;
    std::cout << "K_known = [[4.2813, 0.6587, -2.1407, -2.7993]," << std::endl;
    std::cout << "           [0.6587, 4.2813, -2.7993, -2.1407]" << std::endl;
    std::cout << "           [-2.1407, -2.7993, 4.2813, 0.6587]" << std::endl;
    std::cout << "           [-2.7993, -2.1407, 0.6587, 4.2813]" << std::endl;
    std::cout << "K_test = [[" << slideStiffMatrix[0][0] << ", " << slideStiffMatrix[0][1] << ", " << slideStiffMatrix[0][2] << ", " << slideStiffMatrix[0][3] << "],"<< std::endl;
    std::cout << "          [" << slideStiffMatrix[1][0] << ", " << slideStiffMatrix[1][1] << ", " << slideStiffMatrix[1][2] << ", " << slideStiffMatrix[1][3] << "],"<< std::endl;
    std::cout << "          [" << slideStiffMatrix[2][0] << ", " << slideStiffMatrix[2][1] << ", " << slideStiffMatrix[2][2] << ", " << slideStiffMatrix[2][3] << "],"<< std::endl;
    std::cout << "          [" << slideStiffMatrix[3][0] << ", " << slideStiffMatrix[3][1] << ", " << slideStiffMatrix[3][2] << ", " << slideStiffMatrix[3][3] << "]]"<< std::endl;

};


int main() {
    testGeneralElements();
    testXyLinearThermalMeloshElement();
};
