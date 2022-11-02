#pragma once

/*!*************************************************************************
\file:								Mesh_manager.h
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the declaration for Mesh class.
****************************************************************************/
#include "glm/glm.hpp"
#include <vector>

namespace Thomas {
	class Mesh {
	public:
		// Data Members
		std::vector<glm::vec2> pos_vtx;
		std::vector<glm::vec2> txt_vtx;
		std::vector<unsigned short> idx_vtx;
		uint32_t			primitive_type;
		uint32_t			vbo_hdl{};
		uint32_t			vaoid{};
		uint32_t			idx_elem_cnt{};

		// Member Functions
		void setup_vao();
	};
}