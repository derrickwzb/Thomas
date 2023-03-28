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

		if (g_IsPaused == false)
		{

			Thomas::Vec2 direction = GetComponent<Thomas::AStarPathfindingAgent>().target->translation - GetComponent<Thomas::Transform>().translation;
			Vector2DNormalize(direction, direction);
			//std::cout << "Angle Of Rotation" << GetComponent<Thomas::AStarPathfindingAgent>().angleOfRotation << "\n";
			int distanceToWaypoint = (int)Thomas::Vector2DDistance(GetComponent<Thomas::AStarPathfindingAgent>().target->translation, GetComponent<Thomas::Transform>().translation);
			if (GetComponent<Thomas::ObjectType>().type == Thomas::ObjectTypeID::enemyRanged)
			{
				//Thomas::Vec2 directionOfPlayer = GetComponent<Thomas::AStarPathfindingAgent>().angleOfRotation * GetComponent<Thomas::AStarPathfindingAgent>().currentDirection;
				//GetComponent<Thomas::AStarPathfindingAgent>().actualDirection = directionOfPlayer;
				//std::cout << "("  << direction.x << "," << direction.y << ")" << "--------------PlayerDirection--------------------------------" << "\n";
				//std::cout << "(" <<  GetComponent<Thomas::AStarPathfindingAgent>().currentDirection.x << "," << GetComponent<Thomas::AStarPathfindingAgent>().currentDirection.y << ")" << "--------------CurrentDirection--------------------------------" << "\n";
				if (distanceToWaypoint <= 5)
				{
					

					//float dot_product = Thomas::Vector2DDotProduct()
					float angleOfRotation = acosf(Vector2DDotProduct(direction, GetComponent<Thomas::AStarPathfindingAgent>().currentDirection));
					if (direction.x < 0)
					{
						angleOfRotation *= -1;
					}
					GetComponent<Thomas::Transform>().rotation = angleOfRotation;
					//GetComponent<Thomas::Transform>().rotation = -(GetComponent<Thomas::AStarPathfindingAgent>().target->rotation);
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = false;
					//if (g_enemy_bulletLifetime <= 0)
					//{
						timeOfShot -= ts;
						if (timeOfShot <= 0)
						{
							auto entity = GetScene()->CreateEntity("Bullet");
							InitBullet(entity, GetSelf());
							timeOfShot = 3;
							//std::cout << timeOfShot << "----------------------Shoot------------------------" << "\n";
						}

					//}
				}
				else
				{
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = true;
				}
			}
			else if (GetComponent<Thomas::ObjectType>().type == Thomas::ObjectTypeID::enemy)
			{
				if (combat_data.health > 0 && distanceToWaypoint > 0)
				{
					GetComponent<Thomas::AStarPathfindingAgent>().pathfindingEnabled = true;
					text_data.animation_but = 1;
					if (trans.rotation > 0.f && trans.rotation < 180.f) 
					{
						trans.rotation = 0;
						box_data.box_trans.rotation = 0;
						if (box_data.collision_detected == 1) 
						{
							text_data.slices = 3.f;
							text_data.speed = 10.f;
							text_data.texid = Thomas::stash.Text_Storage["RACC_Attack.png"];
							text_data.text_file = Thomas::stash.Text_Storage["RACC_Attack.png"];
							att_timer++;
							if (att_timer > 20) {
								att_timer = 0;
								box_data.collision_detected = 0;
							}
						}
						else {
							text_data.slices = 10.f;
							text_data.speed = 20.f;
							text_data.texid = Thomas::stash.Text_Storage["RACC_Walk_Right.png"];
							text_data.text_file = Thomas::stash.Text_Storage["RACC_Walk_Right.png"];
						}
					}
					else {
						if (box_data.collision_detected == 1)
						{
							text_data.slices = 3.f;
							text_data.speed = 10.f;
							text_data.texid = Thomas::stash.Text_Storage["RACC_Attack_Left.png"];
							text_data.text_file = Thomas::stash.Text_Storage["RACC_Attack_Left.png"];
							att_timer++;
							if (att_timer > 20) {
								att_timer = 0;
								box_data.collision_detected = 0;
							}
						}
						else {
							trans.rotation = 0;
							text_data.slices = 10.f;
							text_data.speed = 20.f;
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

	void InitBullet(Thomas::Entity& entity, Thomas::Entity& enemy)
	{
		if (g_enemy_bulletLifetime <= 0.f) {
			//set transform data
			auto& trans = entity.GetComponent<Thomas::Transform>();
			trans.scaling.x = 0.6f;
			trans.scaling.y = 0.6f;
			trans.z_axis = enemy.GetComponent<Thomas::Transform>().z_axis;
			trans.translation.x = enemy.GetComponent<Thomas::Transform>().translation.x;
			trans.translation.y = enemy.GetComponent<Thomas::Transform>().translation.y;
			trans.rotation = enemy.GetComponent<Thomas::Transform>().rotation;
			
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
			//SoundSFX_CurrChannel = Thomas::CAudioEngine::PlaySFXSound(Thomas::stash.Audio_Storage["bug-death-splatter_new.wav"], (float)Sound_CurrChannel);

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
				bullet_data.dir.x = cosf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
				bullet_data.dir.y = sinf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
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