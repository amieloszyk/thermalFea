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
        std::vector< bool > nodeValSet;

        int numbOfSurfs;
        std::vector< std::vector< int > > surfElemNumbs;
        std::vector< std::vector< int > > surfLocNumbs;

    public:

        //Note that some of these should be in the parent class

        // Unimplemented and untested
        void setSurfaceFixedVals(int globSurfNumb, double nodeVal); // allow polynomials too
        std::vector< std::vector< double > > getStiffMatToSolve();
        std::vector< double > getLoadVectToSolve();
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
        std::vector< std::vector< double > > getRawGlobStiffMatrix();
        std::vector< double > getRawGlobLoadVect();
        void setFixedNodeVals(std::vector< int > nodesToSet, std::vector< double > setVals);

};
