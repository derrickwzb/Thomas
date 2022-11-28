#ifndef NODE_HPP
#define NODE_HPP

//#include "../Math/Vector2D.h"
//#include <vector>
#include "Thomas/Math/Vector2D.h"

namespace Thomas {

    //class Vec2;

    class Node
    {
    public:

        //Position of the Node in global space.
        Vec2 position;

        //X coordinate of the Node in the grid from the bottom left coordinate system.
        int gridX; 

        //Y coordinate of the Node in the grid from the bottom left coordinate system.
        int gridY;

        //Cost of distance of Node from starting Node
        int Gcost;

        //Cost of distance of Node from end Node. Priority of Hcost > Gcost
        int Hcost;

        //Total cost of the distance from starting the node to current node and to the end node. Gcost + Hcost = Fcost
        int Fcost; 

        //To marked that the node is inaccessible
        bool blocked;

        //The parent node keep track of where the current node came from.
        Node * parent;

        //vector to store the neighboring Node *
        std::vector<Node*> neighbours;        
        
        //Constructor to initialise the values
        Node() : position{ 0,0 }, gridX{ 0 }, gridY{ 0 }, Gcost{ 0 }, Hcost{ 0 }, Fcost{ 0 }, blocked{ false }, parent{ nullptr },neighbours{} {}

        //Copy Constructor
        Node(Node const& rhs);

        //Parametrized Constructor to initialize the Node's global position, corodinates in the bottom left system and whether its accessible
        Node(bool pBlocked , Vec2 pPosition, int pGridX, int pGridY );

    };
    
    //Overload to check if the nodes are the same
    bool operator == (Node const& lhs, Node const& rhs);

    //Overload to check if the nodes are different
    bool operator != (Node const& lhs, Node const& rhs);
    
}

#endif
