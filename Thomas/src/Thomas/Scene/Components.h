/*!*************************************************************************
\file           Components.h
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           28/09/2022
\brief
This file contains the different component struct and class used in the game
****************************************************************************/
#pragma once
#include "Thomas/Math/Math.hpp"

namespace Thomas {

	enum ComponentTypeId
	{
		//Invalid component id
		CT_None = 0,
		CT_Point,
		CT_Colour,
		CT_Triangle,
		CT_Transform,
		CT_Shader_manager,
		CT_Mesh,
		CT_Texture,
		CT_Camera,
		CT_Box_collider,
		CT_RigidBody,
		CT_BoxCollider2D,
		CT_BulletComponent,

		//Max component number
		CT_MaxComponents
	};

	class ScriptableEntity;

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	struct TagComponent {
		std::string tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string name) : tag(name) {}
	};

	class AudioComponent {
	public:
		std::string filepath;
		bool bLooping;
		float fVolumedB;
		int nChannelId;

		AudioComponent();
		AudioComponent(std::string fpath, bool bloop, float fvol, int ncha);
	};

	class BulletComponent{
	public:
		float time{};
		float speed{};
		Vec2 dir;	

		BulletComponent() = default;
		BulletComponent(const BulletComponent&) = default;
	};

}
