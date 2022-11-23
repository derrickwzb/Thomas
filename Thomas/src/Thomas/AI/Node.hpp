#ifndef NODE_HPP
#define NODE_HPP

#include "Vector2D.h"
#include <list>
#include <vector>

class Grid;

namespace Thomas {
    class Node
    {
    public:
        Vec2 position;
        int gridX;
        int gridY;
        int Gcost; //Distance of Node from starting Node
        int Hcost; //Distance of Node from end Node Priority of Hcost > Gcost
        int Fcost; //Gcost + Hcost = Fcost Priority of Fcost > Hcost 
        bool blocked;
        Node * parent;
        std::vector<Node*> neighbours;        
        
        Node() : position{ 0,0 }, gridX{ 0 }, gridY{ 0 }, Gcost{ 0 }, Hcost{ 0 }, Fcost{ 0 }, blocked{ false }, parent{ nullptr },neighbours{} {}
        Node(Node const& rhs);
        Node(bool pBlocked , Vec2 pPosition, int pGridX, int pGridY );
        //void AddNeighbours(std::vector<std::vector<Node*>>const & nodes );
        //void AddNeighbours(std::vector<std::vector<Node*>> grids);

        

    };
    
    bool operator == (Node const& lhs, Node const& rhs);

    bool operator != (Node const& lhs, Node const& rhs);
    
    //template <typename T>
    //bool contains(std::list<T>& listOfElements, const T& element)
    //{
    //    // Find the iterator if element in list
    //    auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
    //    //return if iterator points to end or not. It points to end then it means element
    //    // does not exists in list
    //    return *it != listOfElements.end();
    //}

    /*bool operator == (const Node& lhs, const Node& rhs)
    {
        lhs.
    }*/
    
}

#endif
