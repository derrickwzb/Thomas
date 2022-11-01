/*!*************************************************************************
\file:								Mesh_manager.cpp
\author:						Xie Zhi Xiong
\par DP email:			xiong.x@digipen.edu
\par Course:				CSD2125
\par Programming:	CSD2400 Game project
\date:							31/10/2022
\brief:
	This file contains the definitions of the member functions for
	Mesh_manager class.
****************************************************************************/
// Includes
#include "thpch.h"
#include "Thomas/Renderer/Mesh_manager.h"
#include "GL/glew.h"
#include <math.h>
#define _USE_MATH_DEFINES

namespace Thomas {
	// setup_vao()
	// Called to setup the VAO for the Mesh object
	void Mesh::setup_vao() {
		pos_vtx.push_back(glm::vec2(-0.5f, -0.5f));
		pos_vtx.push_back(glm::vec2(0.5f, -0.5f));
		pos_vtx.push_back(glm::vec2(0.5f, 0.5f));
		pos_vtx.push_back(glm::vec2(-0.5f, 0.5f));

		txt_vtx.push_back(glm::vec2(0.f, 0.f));
		txt_vtx.push_back(glm::vec2(1.f, 0.f));
		txt_vtx.push_back(glm::vec2(1.f, 1.f));
		txt_vtx.push_back(glm::vec2(0.f, 1.f));

		idx_vtx = { 0,1,2,2,3,0 };
		primitive_type = GL_TRIANGLES;

		glCreateBuffers(1, &vbo_hdl);

		glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec2) * txt_vtx.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(vbo_hdl, 0, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
		glNamedBufferSubData(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec2) * txt_vtx.size(), txt_vtx.data());

		glCreateVertexArrays(1, &vaoid);

		glEnableVertexArrayAttrib(vaoid, 0);
		glVertexArrayVertexBuffer(vaoid, 3, vbo_hdl, 0, sizeof(glm::vec2));
		glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vaoid, 0, 3);

		glEnableVertexArrayAttrib(vaoid, 1);
		glVertexArrayVertexBuffer(vaoid, 4, vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec2));
		glVertexArrayAttribFormat(vaoid, 1, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vaoid, 1, 4);

		idx_elem_cnt = idx_vtx.size();
		GLuint ebo_hdl;
		glCreateBuffers(1, &ebo_hdl);
		glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_elem_cnt, reinterpret_cast<GLvoid*>(idx_vtx.data()), GL_DYNAMIC_STORAGE_BIT);
		glVertexArrayElementBuffer(vaoid, ebo_hdl);
		glBindVertexArray(0);
	}
}

