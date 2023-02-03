/******************************************************************************/
/*!
\file   Node.cpp
\author Keith Lua
\par    email: weijiekeith.lua\@digipen.edu
\par    DigiPen login: weijiekeith.lua
\par    Course: CSD-2125 HLP3
\date   3/2/2023
\brief
    This file is the implementation of a Node that form the Grid which is a 
    vector of Node pointer

*/
/******************************************************************************/



#include "thpch.h"
#include "Thomas/AI/Node.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/Math/Vector2D.h"


namespace Thomas
{
    //Parametrized Constructor to initialize the Node's global position, grid index and whether its accessible
    Node::Node(bool pBlocked, Vec2 pPosition, int pGridX, int pGridY) : position{ 0,0 }, gridX{ pGridX }, gridY{ pGridY }, Gcost{ 0 }, Hcost{ 0 }, Fcost{ 0 }, blocked{ false }, parent{ nullptr }, neighbours{}
    {
        position = pPosition;

        blocked = pBlocked;

        gridX = pGridX;

        gridY = pGridY;


    }

    //Copy Constructor
    Node::Node(Node const& rhs)
    {


        position = rhs.position;

        gridX = rhs.gridX;

        gridY = rhs.gridY;

        Gcost = rhs.Gcost;

        Hcost = rhs.Hcost; 

        Fcost = rhs.Fcost; 

        parent = rhs.parent; 
        blocked = rhs.blocked;
        neighbours = rhs.neighbours;



    };

 
    //Overload to check if the nodes are the same
    bool operator == (Node const& lhs, Node const& rhs)
    {
        if (lhs.gridX == rhs.gridX && lhs.gridY == rhs.gridY)
        {
            return true;
        }
        return false;
    }

    //Overload to check if the nodes are different
    bool operator != (Node const& lhs, Node const& rhs)
    {
        if (lhs.gridX != rhs.gridX || lhs.gridY != rhs.gridY)
        {
            return true;
        }
        return false;
    }

}
