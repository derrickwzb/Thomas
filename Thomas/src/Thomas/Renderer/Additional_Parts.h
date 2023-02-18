#pragma once
/*!*************************************************************************
\file:								Additional_Parts.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declaration for Additional_Parts class.
****************************************************************************/
// Includes
#include "Thomas/Renderer/Transform.h"
#include "Thomas/Renderer/Texture.h"
#include <vector>

namespace Thomas {
	class Additional_Parts {
	public:
		//	Data Members
		std::vector<Transform> parts_Transform;
		std::vector<Texture> parts_Texture;
	};
}
