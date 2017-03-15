#include <vector>
#include "elementClasses.cpp"
//#include "polySource/oneDimPoly.cpp"

class GeneralMesh {
    //Need to make an abstract mesh class that is not dependent on dimensionality or element type
};

class TwoDimMeshOfElements {

    protected:

        // lists of elements and nodes
        int numbOfElements;
        std::vector<TwoDimThermalElement*> elementObjList;
        std::vector< std::vector < int > > globNodeOnElementMap;
        
        int numbOfNodes;
        std::vector< std::vector< double > > nodeCoords;
        std::vector< double > nodeVals;
        std::vector< bool > nodeVal;

        int numbOfSurfs;
        std::vector< std::vector< int > > surfElemNumbs;
        std::vector< std::vector< int > > surfLocNumbs;

        // These need to be sized in constructor 
        std::vector< bool > nodesWithSetVals;
        std::vector< double > fixedNodeVals;

    public:

        //Note that some of these should be in the parent class

        // Unimplemented and untested
        void setFixedNodeVals(std::vector< int > nodesToSet, std::vector< double > setVals);
        void setSurfaceFixedVals(int globSurfNumb, double nodeVal); // allow polynomials too
        void getMatsToSolve();  // augmented stiffness matrix and load vector
        // std::vector< double > solveNodeVals(); -> remove
        void checkNumbOfNodes();
        void checkNumbOfElements();
        void getGlobToLocMapping(); // Likely a vector of some sort, not void

        // Implemented, not tested
        TwoDimMeshOfElements(int nodesInMesh, int elementsInMesh);
        void addExistingElement(int elementNumb, TwoDimThermalElement* element, std::vector<int> globalNodeNumbs);
        int makeNewSurf();
        void addLocSurfToMesh(int meshSurfNumb, int meshElementNumb, int locSurfNumb);
        void addLocCoordLoadToSurf(int globSurfNumb, OneDimPoly locCoordPoly);
        void setScalarSurfFlux(int globSurfNumb, double scalarFlux);
        std::vector< std::vector< double > > getGlobStiffMatrix();
        std::vector< double > getGlobLoadVect();

};
