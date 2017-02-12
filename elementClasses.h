#include <vector>
#include "polyArray.cpp"

class GeneralElement {
    /* 
    This is a generalized class for elements. I should consider making this 
    specific to 2-D elements...
    */

    protected:
        int elementNumb;
        int numbOfNodes;
        int numbOfSurfs;
        int degreesOfFreedom;
        std::vector< int > nodeLocNumbVect;
        std::vector< int > nodeGlobNumbVect; 
        std::vector< std::vector< double > > nodeLocCoordVect;
        std::vector< std::vector< double > > nodeGlobCoordVect;
        std::vector< double > nodeValueVect;
        std::vector< bool > isNodeFixedVect;
        
        // [X] Node locations
        // [X] Node numbers
        // [X] Element number
        // [] Surface numbers
        // [] Global mapping info
        // [] Local stiffness matrix
        // [] Local load vector
        // [] Node values
        // [] Material name
        // [] Material properties functions
        // [] Shape function array
        // Mapping functions:
        //      [] [dof][nodeNumb] --> shapeFuncArray 
        //      [] dof naming
    public:

        GeneralElement();

        // Not implemented
        
        std::vector< std::vector< double > > getStiffnessMatrix();
        std::vector< double > getLoadVector();
        void setNodeValues(std::vector< double > nodeValueVect);
        void setFixedNodes(std::vector< bool > isNodeFixedVect);
        void setMaterialName(char* matName);
        void setNodeVals(int dofIdx, int nodeIdx);

        // Implemented, not tested
        

        

        // Implemented and tested
        void setElementNumber(int giveElementNumb);
        int getElementNumber();
        void setNodeGlobNumber(std::vector< int > nodeGlobNumb);
        std::vector< int > getNodeGlobNumber();
        void setNumberOfNodes(int thisManyNodes);
        int getNumberOfNodes();
        void checkNumbOfNodes(int givenVectSize);
        void setNodeCoords(std::vector< std::vector< double > > nodeGlobCoords);
        std::vector< std::vector< double > > getNodeCoords();

        // Generic placeholder for subclass  
        void setLocNodeCoords();
        void setShapeFuncs();
};

class XyLinearThermalMeloshElement : public GeneralElement{
/*
  (x4,y4)      S3        (x3,y3)
     O----------|----------O
     |          |          |       /\ y
     |          | (0,0)    |       |
 S4 -|----------|----------|-  S2 -|--> x
     |          |          |
     |          |          |
     O----------|----------O
  (x1,y1)      S1        (x2,y2)

DOF:
    - Temperature
*/

    private:

        double elemThickness;
        double halfWidth;
        double halfHeight;
        std::vector< std::vector< double > > condMatrix;
        XyShapeFuncVector shapeFuncVect;
        bool loadOnSurf[4];
        std::vector<OneDimPoly> locSurfLoads;
        bool loadOnBody;
        PolyArray bodyLoad;

    public: //TODO: Some of these ought to be private

        XyLinearThermalMeloshElement(); 
        
        // Implemented and tested
        void setNodeCoords(std::vector< std::vector< double > > nodeGlobCoords);
        void setLocNodeCoords();
        void checkNodeCoords();
        std::vector< std::vector< double > > getLocNodeCoords();
        double getHalfWidth();
        double getHalfHeight();
        void setElemThick(double elemThick);
        double getElemThick();
        void setMatMatrix(std::vector< std::vector< double > > thermCondMatrix);
        std::vector< std::vector< double > > getMatMatrix();
        void setIsoThermCond(double thermCond);
        void setShapeFuncs();
        XyShapeFuncVector getShapeFuncs();
        PolyArray getStiffIntegrand();
        std::vector< std::vector< double > > getStiffnessMatrix();

        // Implemented not tested
        void setSurfaceLoadInLocCoords(int surfNumb, OneDimPoly locLoadShape);

        // Not implemented
        
        
        
        std::vector<double> getLoadOnSurf(int surfNumb);
        
        void setBodyLoad(TwoDimPoly loadShape);
        std::vector<double> getBodyLoadVect();
        
        std::vector<double> getTotalLoadVect();
};

