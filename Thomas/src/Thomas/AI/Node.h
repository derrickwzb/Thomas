/******************************************************************************/
/*!
\file   Node.h
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
    This file is the contains the Node Class which makes up the Grid

*/
/******************************************************************************/


#pragma once


#include "Thomas/Math/Vector2D.h"

namespace Thomas {


    class Node
    {
    public:

        //Position of the Node in global space.
        Vec2 position;

        //X coordinate of the Node in the grid 
        int gridX; 

        //Y coordinate of the Node in the grid
        int gridY;

        //Cost of distance of Node from starting Node
        int Gcost;

        //Cost of distance of Node from end Node. Priority of Hcost > Gcost
        int Hcost;

        //Total cost of the distance from starting the node to current node and to the end node. Gcost + Hcost = Fcost
        int Fcost; 

        //To marked that the node is inaccessible
        bool blocked;

        std::vector<int> obstacleIDs;

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

//#endif
