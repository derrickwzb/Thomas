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
		CT_TagComponent,
		CT_Transform,
		CT_Shader_manager,
		CT_Mesh,
		CT_Texture,
		CT_Additional_parts,
		//CT_Camera,
		CT_Box_collider,
		CT_RigidBody,
		CT_BoxCollider2D,
		CT_AudioComponent,
		CT_ScriptComponent,
		CT_BulletComponent,
		CT_ParticleComponent,
		CT_Particle,
		CT_ObjectType,
		CT_CombatComponent,
		CT_DeleteComponent,
		CT_AStarPathfindingAgent,
		CT_Grid,
		CT_AStarPathfindingObstacle,
		CT_Target,
		CT_Spawner,
		CT_Additional_Parts,

		//Max component number
		CT_MaxComponents
	};

	class ScriptableEntity;

	struct NativeScriptComponent
	{
		std::string ClassName;
		bool HasClass = false;
		ScriptableEntity* Instance = nullptr;
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);
		

		template<typename T>
		void Bind()
		{

			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {TH_CORE_INFO("deleted"); delete nsc->Instance; nsc->Instance = nullptr; };
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

	struct ScriptComponent
	{
		std::string ClassName;

		ScriptComponent() = default;
		ScriptComponent(const ScriptComponent&) = default;
	};

	class ParticleComponent {
	public:
		float time{};

		ParticleComponent() = default;
		ParticleComponent(const ParticleComponent&) = default;
	};

	class Particle {
	public:
		float total_time{};
		float life_time{};
		Vec2 dir;

		Particle() = default;
		Particle(const Particle&) = default;
	};

	enum class ObjectTypeID { nil = 0, player, enemy, obstacle, bullet, pickup, goal, ui, puddle, cheat_mode, basin, boss };

	class ObjectType {
	public:

		ObjectTypeID type = ObjectTypeID::nil;
		bool basin_collide = false;
		bool pickup_collide = false;
		int win_point{};
		bool win_collide = false;
		Vec2 fix_ui_trans{};
		bool puddle_collide = false;
		bool destroy_pickup = false;
		bool cheat = false;
		

		ObjectType() = default;
		ObjectType(const ObjectType&) = default;
	};

	class CombatComponent {
	public:
		float attack{};
		float attack_interval{};
		float health{1};
		float death_timer = 1.5f;

		CombatComponent() = default;
		CombatComponent(const CombatComponent&) = default;
	};

	class DeleteComponent {
	public:
		bool isdeleted = false;


		DeleteComponent() = default;
		DeleteComponent(const DeleteComponent&) = default;
	};

}
