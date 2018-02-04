#include <vector>
#include <string>
#include "elementClasses.cpp"
//#include "polySource/oneDimPoly.cpp"


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


        // Implemented and tested
        TwoDimMeshOfElements(int nodesInMesh=0, int elementsInMesh=0);
        void addExistingElement(int elementNumb, TwoDimThermalElement* element, std::vector<int> globalNodeNumbs);
        int makeNewSurf();
        void addLocSurfToMesh(int meshSurfNumb, int meshElementNumb, int locSurfNumb);
        void setScalarSurfFlux(int globSurfNumb, double scalarFlux);
        std::vector< std::vector< double > > getRawGlobStiffMatrix();
        std::vector< double > getRawGlobLoadVect();
        void setFixedNodeVals(std::vector< int > nodesToSet, std::vector< double > setVals);
        std::vector< std::vector< double > > getStiffMatToSolve();
        std::vector< double > getLoadVectToSolve();
        void addLocCoordLoadToSurf(int globSurfNumb, OneDimPoly locCoordPoly);
        

        // Implemented, not tested
        int addNewElement(std::string elemType, std::vector< std::vector< double > > nodeCoords,
                          std::vector< int > globalNodeNumbs);
        
        
        // Unimplemented and untested
        void setElemThick(float thick, int elementNumb);
        void setElemIsoThermCond(float isoThermCond, int elementNumb);
        void setAllThick(float thick);
        void setAllIsoThermCond(float isoThermCond);

        void setSurfaceFixedVals(int globSurfNumb, double nodeVal); // allow polynomials too
        int makeNewElemSet();
        int makeNewNodeSet();
        // std::vector< double > solveNodeVals(); -> remove
        void checkNumbOfNodes();
        void checkNumbOfElements();
        void getGlobToLocMapping(); // Likely a vector of some sort, not void
        
       

};
