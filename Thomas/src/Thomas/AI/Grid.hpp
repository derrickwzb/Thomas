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
		
		/*Node* operator()(int x, int y);
		
		Node* operator()(int x, int y) const;	*/



		Grid() : nodeGrids{}, gridWorldSize{}, nodeRadius{ 0.f }, nodeDiameter{ 1.f }, gridWidth{ 1 }, gridHeight{ 1 }{}
		Grid(Vec2 gridWorldSize, float nodeRadius);

		Node* GetNodeFromGrid(int x, int y);

		Node* Grid::GetNodeFromGrid(int x, int y) const;

		void AddNeighbours(Node * node);
		void Init();


		void CreateGrid();
		
		
		Node* WorldPostionToNode(Vec2 position);

	


    };

	
	
	



}

#endif