/******************************************************************************/
/*!
\file		Enemy.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of enemy script.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"
static float g_enemy_bulletLifetime;
static float timeOfShot;
static int att_timer = 0;
//std::string enemyType{};

struct Enemy : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		g_enemy_bulletLifetime = 0.f;
		//g_bulletLifetime = 0.f;
		timeOfShot = 0;
		if (GetComponent<Thomas::ObjectType>().type == Thomas::ObjectTypeID::enemyRanged)
		{

		}
		//enemyType = GetComponent<Thomas::Texture>().filename;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		auto& combat_data = GetComponent<Thomas::CombatComponent>();
		auto& trans = GetComponent<Thomas::Transform>();
		auto& text_data = GetComponent<Thomas::Texture>();
		auto& box_data = GetComponent<Thomas::Box_collider>();
		auto& path_data = GetComponent<Thomas::AStarPathfindingAgent>();

		if (g_IsPaused == false)
		{

			Thomas::Vec2 direction = GetComponent<Thomas::AStarPathfindingAgent>().target->translation - GetComponent<Thomas::Transform>().translation;
			Vector2DNormalize(direction, direction);
			int distanceToWaypoint = (int)Thomas::Vector2DDistance(GetComponent<Thomas::AStarPathfindingAgent>().target->translation, GetComponent<Thomas::Transform>().translation);

			// RANGE ENEMY ============================================================================================================
			if (GetComponent<Thomas::ObjectType>().type == Thomas::ObjectTypeID::enemyRanged)
			{
				text_data.animation_but = 1;
				trans.rotation = 0;
				box_data.box_trans.rotation = 0;
				if (path_data.movingDirection.x >= 0.f)
				{
					text_data.slices = 7.f;
					text_data.speed = 13.f;
					text_data.texid = Thomas::stash.Text_Storage["Bear_Walk_Right.png"];
					text_data.text_file = Thomas::stash.Text_Storage["Bear_Walk_Right.png"];
				}
				else {
					text_data.slices = 7.f;
					text_data.speed = 13.f;
					text_data.texid = Thomas::stash.Text_Storage["Bear_Walk_Left.png"];
					text_data.text_file = Thomas::stash.Text_Storage["Bear_Walk_Left.png"];
				}
				// ATTACKING ====================================================================================
				if (distanceToWaypoint <= 5)
				{
					float angleOfRotation = acosf(Vector2DDotProduct(direction, GetComponent<Thomas::AStarPathfindingAgent>().currentDirection));
					if (direction.x < 0)
					{
						angleOfRotation *= -1;
					}
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;
					timeOfShot -= ts;
					if (path_data.movingDirection.x >= 0.f)
					{
						text_data.slices = 5.f;
						text_data.speed = 13.f;
						text_data.texid = Thomas::stash.Text_Storage["Bear_ATK_Right.png"];
						text_data.text_file = Thomas::stash.Text_Storage["Bear_ATK_Right.png"];
					}
					else 
					{
						text_data.slices = 5.f;
						text_data.speed = 13.f;
						text_data.texid = Thomas::stash.Text_Storage["Bear_ATK_Left.png"];
						text_data.text_file = Thomas::stash.Text_Storage["Bear_ATK_Left.png"];
					}
					if (timeOfShot <= 0)
					{
						auto entity = GetScene()->CreateEntity("Bullet");
						InitBullet(entity, GetSelf(), angleOfRotation);
						timeOfShot = 3;
					}
				}
				// ===========================================================================================
				else
				{
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = true;
				}
			}
			// MEELEE ENEMY ============================================================================================================
			else if (GetComponent<Thomas::ObjectType>().type == Thomas::ObjectTypeID::enemy)
			{
				if (combat_data.health > 0 && distanceToWaypoint > 0)
				{
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = true;
					text_data.animation_but = 1;
					if (path_data.movingDirection.x >= 0.f) 
					{
						trans.rotation = 0.f;
						box_data.box_trans.rotation = 0.f;
						if (box_data.collision_detected == 1) 
						{
							text_data.slices = 3.f;
							text_data.texid = Thomas::stash.Text_Storage["RACC_Attack.png"];
							text_data.text_file = Thomas::stash.Text_Storage["RACC_Attack.png"];
							att_timer++;
							if (att_timer > 20) 
							{
								att_timer = 0;
								box_data.collision_detected = 0;
							}
						}
						else 
						{
							text_data.slices = 10.f;
							text_data.speed = 30.f;
							text_data.texid = Thomas::stash.Text_Storage["RACC_Walk_Right.png"];
							text_data.text_file = Thomas::stash.Text_Storage["RACC_Walk_Right.png"];
						}
					}
					else {
						trans.rotation = 0.f;
						box_data.box_trans.rotation = 0.f;
						if (box_data.collision_detected == 1)
						{
							text_data.slices = 3.f;
							text_data.texid = Thomas::stash.Text_Storage["RACC_Attack_Left.png"];
							text_data.text_file = Thomas::stash.Text_Storage["RACC_Attack_Left.png"];
							att_timer++;
							if (att_timer > 20) 
							{
								att_timer = 0;
								box_data.collision_detected = 0;
							}
						}
						else 
						{
							text_data.slices = 10.f;
							text_data.speed = 30.f;
							text_data.texid = Thomas::stash.Text_Storage["RACC_Walk_Left.png"];
							text_data.text_file = Thomas::stash.Text_Storage["RACC_Walk_Left.png"];
						}
					}
				}
				else
				{
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;
				}
			}
			// =====================================================================================================================
			else
			{
				if (combat_data.health <= 0)
				{
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;
				}
			}
			
		}
		
		else {

			GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;

		}

		if (g_gameStateCurr == GameState::Level3) {
			if (combat_data.health <= 0) {
				g_gameStateNext = GameState::Win;
			}
		}
		if (g_enemy_bulletLifetime >= 0.f) {
			g_enemy_bulletLifetime -= ts;
		}
	}

	void InitBullet(Thomas::Entity& entity, Thomas::Entity& enemy, float angleOfRotation)
	{
		if (g_enemy_bulletLifetime <= 0.f) {
			//set transform data
			auto& trans = entity.GetComponent<Thomas::Transform>();
			trans.scaling.x = 0.6f;
			trans.scaling.y = 0.6f;
			trans.z_axis = enemy.GetComponent<Thomas::Transform>().z_axis;
			trans.translation.x = enemy.GetComponent<Thomas::Transform>().translation.x;
			trans.translation.y = enemy.GetComponent<Thomas::Transform>().translation.y;
			trans.rotation = angleOfRotation;
			
			//trans.rotation = player.GetComponent<Thomas::Additional_Parts>().parts_Transform[0].rotation - (float)((M_PI / 2));

			//set texture

			auto& tex = entity.AddComponent<Thomas::Texture>();
			tex.texid = Thomas::stash.Text_Storage["bullet_2.png"];
			tex.text_file = Thomas::stash.Text_Storage["bullet_2.png"];
			tex.filename = "bullet_2.png";
			
			//set bounding box data
			auto& box = entity.GetComponent<Thomas::Box_collider>();
			box.box_tog = 0;
			box.box_trans.scaling.x = 0.4f;
			box.box_trans.scaling.y = 0.4f;
			box.box_trans.translation.x = enemy.GetComponent<Thomas::Transform>().translation.x;
			box.box_trans.translation.y = enemy.GetComponent<Thomas::Transform>().translation.y;
		
			//Audio for shooting bullet
			SoundSFX_CurrChannel = Thomas::CAudioEngine::PlaySFXSound(Thomas::stash.Audio_Storage["Enemy_Death.wav"], Thomas::CAudioEngine::currSFX_volume);

			auto& bullet_data = entity.AddComponent<Thomas::BulletComponent>();
			bullet_data.speed = 3.f;
			bullet_data.time = 3.0f;
			
			auto& type = entity.AddComponent<Thomas::ObjectType>();
			type.type = Thomas::ObjectTypeID::enemyRangedBullet;

			auto& combat = entity.AddComponent<Thomas::CombatComponent>();
			combat.attack = 1.f;

			auto& box_collider2d = entity.AddComponent<Thomas::BoxCollider2D>();
			//auto& data = entity.AddComponent<Thomas::RigidBody>();
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice0);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice1);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice2);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice3);
			
			//bullet movement direction based on the mouse position and center of the screen
			//bullet_data.dir.x = enemy.GetComponent<Thomas::AStarPathfindingAgent>().actualDirection.x;
			//bullet_data.dir.y = enemy.GetComponent<Thomas::AStarPathfindingAgent>().actualDirection.y;
			if (((GetComponent<Thomas::AStarPathfindingAgent>().target->translation.x - 0.5f) * 4) >= 0.f) {
				bullet_data.dir.x = -cosf(static_cast <float>(-trans.rotation - M_PI / 2.f));
				bullet_data.dir.y = -sinf(static_cast <float>(-trans.rotation - M_PI / 2.f));
			}
			else if (((GetComponent<Thomas::AStarPathfindingAgent>().target->translation.x - 0.5f) * 4) < 0.f) {
				bullet_data.dir.x = cosf(static_cast <float>(-trans.rotation - (2.f * M_PI)));
				bullet_data.dir.y = sinf(static_cast <float>(-trans.rotation - (2.f * M_PI)));
			}
			/*trans.translation.x += bullet_data.dir.x * bullet_data.speed * ts;
			trans.translation.y += bullet_data.dir.y * bullet_data.speed;
			box.box_trans.translation.x += bullet_data.dir.x * bullet_data.speed;
			box.box_trans.translation.y += bullet_data.dir.y * bullet_data.speed;*/
			g_enemy_bulletLifetime += 0.25f;
		}

	}
	void OnDestroy()
	{

	}
};