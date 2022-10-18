#pragma once
#include "Thomas/Renderer/Graphics.h"
namespace Thomas {
	class Box_collider {
	public:
		//	Data Members
		int										collision_detected{};
		int										box_tog{};
		Mesh									box_mesh;
		Shader_manager					box_shader;
		Transform							box_trans;
		// Member Functions
	};
}