#ifndef GRID_HPP
#define GRID_HPP

#include "Vector2D.h"
#include "Node.hpp"
namespace Thomas
{


    class Grid
    {
    public:

		std::vector<std::vector<Node*>> nodeGrids;
        Vec2 gridWorldSize;
        float nodeRadius;
        float nodeDiameter;
        int gridWidth;
        int gridHeight;
		Vec2 origin;

		Grid() : nodeGrids{}, gridWorldSize{}, nodeRadius{ 0.f }, nodeDiameter{ 1.f }, gridWidth{ 1 }, gridHeight{ 1 }{}
		Grid(Vec2 gridWorldSize, float nodeRadius);
		~Grid();

		//Get Grid after converting from bottom left coordinate system to the grid index
		Node* GetNodeFromGrid(int x, int y);

		Node* GetNodeFromGrid(int x, int y) const;

		void AddNeighbours(Node * node);

		void CreateGrid();
		
		Vec2 WorldPositionToNodeIndex(Vec2 position);

		Node* WorldPositionToNode(Vec2 position);


    };

	
	
	



}

#endif