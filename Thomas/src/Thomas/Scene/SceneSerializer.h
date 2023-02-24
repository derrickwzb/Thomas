/*!*************************************************************************
\file           SceneSerializer.h
\author         Derrick Woo
\par DP email:  d.woo@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains declaration for functions used in a sceneSerializer
****************************************************************************/
#pragma once

#include "Scene.h"

namespace Thomas
{

	class SceneSerializer
	{
	public:
		SceneSerializer(Scene* context);


		void Serialize(const std::string& filepath);
		//void SerializeRuntime(const std::string& filepath);

		void Deserialize(const std::string& filepath);

		void LoadScene(const std::string& filepath);

		void RemoveScene(const std::string& filepath);
		//bool DeserializeRuntime(const std::string& filepath);

	private:
		Scene* m_Scene;

	};
}

