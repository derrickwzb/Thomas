

#include "Node.hpp"
#include "Grid.hpp"

namespace Thomas
{
    Node::Node(bool pBlocked, Vec2 pPosition, int pGridX, int pGridY) : position{ 0,0 }, gridX{ pGridX }, gridY{ pGridY }, Gcost{ 0 }, Hcost{ 0 }, Fcost{ 0 }, blocked{ false }, parent{ nullptr }, neighbours{}
    {
        position = pPosition;

        blocked = pBlocked;

        gridX = pGridX;

        gridY = pGridY;


    }

    Node::Node(Node const& rhs)
    {


        position = rhs.position;
        gridX = rhs.gridX;
        gridY = rhs.gridY;
        Gcost = rhs.Gcost; //Distance of Node from starting Node
        Hcost = rhs.Hcost; //Distance of Node from end Node Priority of Hcost > Gcost
        Fcost = rhs.Fcost; //Gcost + Hcost = Fcost Priority of Fcost > Hcost
        parent = rhs.parent;
        blocked = rhs.blocked;
        neighbours = rhs.neighbours;



    };

 

    bool operator == (Node const& lhs, Node const& rhs)
    {
        if (lhs.gridX == rhs.gridX && lhs.gridY == rhs.gridY)
        {
            return true;
        }
        return false;
    }

    bool operator != (Node const& lhs, Node const& rhs)
    {
        if (lhs.gridX != rhs.gridX || lhs.gridY != rhs.gridY)
        {
            return true;
        }
        return false;
    }

}
