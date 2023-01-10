
//#pragma once
#include "thpch.h"
#include "Thomas/AI/Node.h"
#include "Thomas/AI/Grid.h"
#include "Thomas/Math/Vector2D.h"


namespace Thomas
{
    //Parametrized Constructor to initialize the Node's global position, corodinates in the bottom left system and whether its accessible
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
