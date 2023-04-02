/******************************************************************************/
/*!
\file		Boss.h
\author 	Chen XinPeng
\email:		c.xinpeng@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of boss script.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"
#include "Player.h"

static float b_bulletLifetime;
static float boss_attackTimer = 0;
static float g_boss_health = 0;

struct Boss : Thomas::ScriptableEntity
{
	void OnCreate()
	{
		TH_CORE_INFO("Boss Script Instantiated");
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		if (!g_IsPaused)
		{
			auto& combat_data = GetComponent<Thomas::CombatComponent>();
			auto& type_data = GetComponent<Thomas::ObjectType>();

			auto& trans = GetComponent<Thomas::Transform>();
			auto& box_data = GetComponent<Thomas::Box_collider>();
			auto& text_data = GetComponent<Thomas::Texture>();

			g_boss_health = combat_data.health;

			// Boss follows player
			glm::vec2 A = glm::vec2(0.f, 1.f);
			glm::vec2 B = glm::vec2(p_Pos.x, p_Pos.y);
			B.x -= trans.translation.x;
			B.y -= trans.translation.y;
			float dot_product = glm::dot(A, B);
			float angle = -acos(dot_product / (glm::length(A) * glm::length(B)));
			if ((B.x + trans.translation.x) > trans.translation.x)
				angle *= -1;
			trans.rotation = angle + (float)(M_PI);

			if (combat_data.health > 0)
			{
				// Create a timer to shoot later 
				boss_attackTimer += ts;
				if (boss_attackTimer > 2.f)
				{
					std::cout << "BOSS SHOOT" << std::endl;
					if (b_bulletLifetime <= 0)
					{
						auto entity = GetScene()->CreateEntity("Bullet");
						bossBullet(entity, GetSelf());
					}
					boss_attackTimer = 0;
				}
			}

			if (combat_data.health <= 0)
			{
				type_data.destroy_pickup = true;
				g_gameStateNext = GameState::Win;
			}

			if (b_bulletLifetime >= 0.f) 
			{
				b_bulletLifetime -= ts;
			}
		}
	}

	void OnDestroy()
	{
	}

	void bossBullet(Thomas::Entity& entity, Thomas::Entity& player)
	{
		if (b_bulletLifetime <= 0.f) {
			//set transform data
			auto& trans = entity.GetComponent<Thomas::Transform>();
			trans.scaling.x = 1.f;
			trans.scaling.y = 1.f;
			trans.z_axis = player.GetComponent<Thomas::Transform>().z_axis;
			trans.translation.x = player.GetComponent<Thomas::Transform>().translation.x;
			trans.translation.y = player.GetComponent<Thomas::Transform>().translation.y;
			trans.rotation = player.GetComponent<Thomas::Transform>().rotation;

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
			box.box_trans.translation.x = player.GetComponent<Thomas::Transform>().translation.x;
			box.box_trans.translation.y = player.GetComponent<Thomas::Transform>().translation.y;

			//Audio for shooting bullet
			SoundSFX_CurrChannel = Thomas::CAudioEngine::PlaySFXSound(Thomas::stash.Audio_Storage["Enemy_Death.wav"], Thomas::CAudioEngine::currSFX_volume);

			auto& bullet_data = entity.AddComponent<Thomas::BulletComponent>();
			bullet_data.speed = 10.f;
			bullet_data.time = 3.f;

			auto& type = entity.AddComponent<Thomas::ObjectType>();
			type.type = Thomas::ObjectTypeID::enemyRangedBullet;

			auto& combat = entity.AddComponent<Thomas::CombatComponent>();
			combat.attack = 3.f;

			auto& box_collider2d = entity.AddComponent<Thomas::BoxCollider2D>();
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice0);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice1);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice2);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice3);

			//bullet movement direction based on the mouse position and center of the screen
			if (((p_Pos.x - 0.5f) * 4) >= 0.f)
			{
				bullet_data.dir.x = cosf(static_cast <float>(-trans.rotation - M_PI / 2.f));
				bullet_data.dir.y = sinf(static_cast <float>(-trans.rotation - M_PI / 2.f));
			}
			else if (((p_Pos.x - 0.5f) * 4) < 0.f)
			{
				bullet_data.dir.x = -cosf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
				bullet_data.dir.y = -sinf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
			}

			if (g_boss_health >= 40)
			{
				b_bulletLifetime += 0.25f;
			}
			else 
			{
				b_bulletLifetime += 0.15f;
			}
			
		}
	}
};