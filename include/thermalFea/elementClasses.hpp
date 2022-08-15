#pragma once

#include <thermalFea/polyArray.hpp>

#include <vector>

class ThermalElement {
    /* 
    This is a generalized class for heat transfer elements
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

        ThermalElement();

        // Not implemented
        void setNodeValues(std::vector< double > nodeValueVect);
        void setFixedNodes(std::vector< bool > isNodeFixedVect);
        void setMaterialName(char* matName);
        void setNodeVals(int dofIdx, int nodeIdx);

        // Add some getters        

        // Implemented and tested
        void setElementNumber(int giveElementNumb);
        int getElementNumber();
        void setNodeGlobNumber(std::vector< int > nodeGlobNumb);
        std::vector< int > getNodeGlobNumber();
        void setNumberOfNodes(int thisManyNodes);
        int getNumberOfNodes();
        void checkNumbOfNodes(int givenVectSize);
        void setNodeCoordVect(std::vector< std::vector< double > > nodeGlobCoords);
        std::vector< std::vector< double > > getNodeCoords();

        // Generic placeholder for subclass  
        virtual void setLocNodeCoords() {};
        virtual void setShapeFuncs() {};
        virtual void setMatMatrix(std::vector< std::vector< double > > thermCondMatrix) {};
        virtual void setIsoThermCond(double thermCond) {};
        virtual std::vector< std::vector< double > > getStiffnessMatrix(){
            return std::vector< std::vector< double > >(0);
        };
        virtual std::vector< double > getTotalLoadVect(){
            return std::vector< double >(0);
        };
        virtual void setSurfaceLoadInLocCoords(int surfNumb, OneDimPoly locLoadShape) {};
        virtual void setNodeCoords(std::vector< std::vector< double > > nodeGlobCoords) {};
};

class TwoDimThermalElement : public ThermalElement {
    
    private:

    public:
        virtual void setElemThick(double elemThick) {};
        virtual double getElemThick() {return 0.0;};
};

class XyLinearThermalMeloshElement : public TwoDimThermalElement{
/*
  (x4,y4)      S3        (x3,y3)
     4----------|----------3
     |          |          |       /\ y
     |          | (0,0)    |       |
 S4 -|----------|----------|-  S2 -|--> x
     |          |          |
     |          |          |
     1----------|----------2
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
        std::vector<double> getLoadOnSurf(int surfNumb);
        std::vector<double> getTotalLoadVect();

        // Not implemented
        void setBodyLoad(TwoDimPoly loadShape);
        std::vector<double> getBodyLoadVect();
        
};


class XyCstThermalTriElement : public TwoDimThermalElement{
/*
Constant strain triangle with natural coordinates
        (x3,y3)
        (0,0,1)
          3
         / \
        /   \
    S3 /     \ S2
      /       \
     /         \
    1-----------2
(x1,y1)  S1    (x2,y2)
(1,0,0)        (0,1,0)

DOF:
    - Temperature
*/

    private:

        double elemThickness;
        std::vector< std::vector< double > > condMatrix;
        XyShapeFuncVector shapeFuncVect;
        bool loadOnSurf[3];
        std::vector<OneDimPoly> locSurfLoads;
        bool loadOnBody;
        PolyArray bodyLoad;
        std::vector< std::vector< double > > natTransMatrix;
        std::vector< std::vector< double > > invNatTransMatrix;
        double area;

    public: //TODO: Some of these ought to be private

        XyCstThermalTriElement(); 
        
        // Implemented and tested
        

        // Implemented not tested
        void checkNodeCoords();
        void setLocNodeCoords();
        std::vector< std::vector< double > > getLocNodeCoords();
        void setNodeCoords(std::vector< std::vector< double > > nodeGlobCoords);
        void setElemThick(double elemThick);
        double getElemThick();
        void setMatMatrix(std::vector< std::vector< double > > thermCondMatrix);
        std::vector< std::vector< double > > getMatMatrix();
        void setIsoThermCond(double thermCond);
        void setShapeFuncs();
        XyShapeFuncVector getShapeFuncs();
        PolyArray getStiffIntegrand();
        std::vector< std::vector< double > > getStiffnessMatrix();

        // Not implemented
        std::vector<double> getLoadOnSurf(int surfNumb);
        std::vector<double> getTotalLoadVect();

        void setSurfaceLoadInLocCoords(int surfNumb, OneDimPoly locLoadShape);
        
        
        //void setBodyLoad(TwoDimPoly loadShape);
        //std::vector<double> getBodyLoadVect();
        
};

