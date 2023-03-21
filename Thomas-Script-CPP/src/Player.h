/******************************************************************************/
/*!
\file		CurSceneManager.h
\author 	Derrick Woo / Xie Zhi Xiong
\par    	email: d.woo@digipen.edu /xiong.x@digipen.edu
\date   	10/3/2023
\brief		This file contains the functions and declarations of CutSceneManager script.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "ScriptUtils.h"
#include "Managers/GameManager.h"
#include "Managers/AudioManager.h"

static float g_bulletLifetime;
static int g_points;
static int move_Direction; //  0=LEFT, 1=RIGHT
static bool CanPlaySFX;
static glm::vec2 p_Pos; // Global player position, allowing other scripts to access player's position 
static bool g_puddle_collide = false;

struct Player : Thomas::ScriptableEntity
{

	void OnCreate()
	{
		TH_CORE_INFO("Player Script Instantiated");
		g_bulletLifetime = 0.f;
		g_points = 0;
		CanPlaySFX = true;
	}

	void OnUpdate(Thomas::Timestep ts)
	{
		if(!g_IsPaused)
		{ 
			GetComponent<Thomas::ObjectType>().cheat = g_CheatMode;
			GetComponent<Thomas::ObjectType>().win_point = g_points;
			float Cursor_X = Thomas::Input::GetMouseX() - Thomas::Graphics::width / 2;
			float Cursor_Y = -(Thomas::Input::GetMouseY() - Thomas::Graphics::height / 2);

			auto& trans = GetComponent<Thomas::Transform>();
			//auto& tag_c = GetComponent<Thomas::TagComponent>();
			auto& box_data = GetComponent<Thomas::Box_collider>();
			auto& text_data = GetComponent<Thomas::Texture>();
			auto& parts_data = GetComponent<Thomas::Additional_Parts>();
			p_Pos = trans.translation;

			//sync camera with player
			Thomas::Graphics::cam_stuff.translation.x = trans.translation.x;
			Thomas::Graphics::cam_stuff.translation.y = trans.translation.y;

			// Mouse Following
			glm::vec2 A = glm::vec2(0.f, 1.f);
			glm::vec2 B = glm::vec2(Cursor_X, Cursor_Y);
			B.x -= trans.translation.x;
			B.y -= trans.translation.y;
			float dot_product = glm::dot(A, B);
			float angle = -acos(dot_product / (glm::length(A) * glm::length(B)));
			if ((B.x + trans.translation.x) < trans.translation.x)
				angle *= -1;
			// Gun need to rotate counter clockwise by a quarter
			parts_data.parts_Transform[0].rotation = angle + (float)((M_PI/2));
			Thomas::Graphics::cam_stuff.rotation = (angle * -1.f);
			glm::mat3 parts_rotation_matrix = { cos(-parts_data.parts_Transform[0].rotation), sin(-parts_data.parts_Transform[0].rotation), 0, -sin(-parts_data.parts_Transform[0].rotation), cos(-parts_data.parts_Transform[0].rotation), 0, trans.translation.x, trans.translation.y, 1 };
			parts_data.parts_Transform[0].translation = glm::vec2(parts_rotation_matrix * (glm::vec3(0.6f, 0.f, 1.f)));

			if (Thomas::Input::IsKeyPressed(TH_KEY_W)) {
				trans.translation.y -= 1.f * ts;
				box_data.box_trans.translation.y -= 1.f * ts;
				parts_data.parts_Transform[0].translation.y -= 1.f * ts;
				text_data.animation_but = 1;

				//Audio for footstep
				AudioManager::PlaySFXAudioOnce("cat footsteps-idoors-carpet_5.wav", SoundSFX_CurrChannel + 20.0f);

			}
			else if (Thomas::Input::IsKeyPressed(TH_KEY_S)) {
				trans.translation.y += 1.f * ts;
				box_data.box_trans.translation.y += 1.f * ts;
				parts_data.parts_Transform[0].translation.y += 1.f * ts;
				text_data.animation_but = 1;

				//Audio for footstep
				AudioManager::PlaySFXAudioOnce("cat footsteps-idoors-carpet_5.wav", SoundSFX_CurrChannel + 20.0f);
			}
			else if (Thomas::Input::IsKeyPressed(TH_KEY_A)) {
				move_Direction = 0;
				trans.translation.x -= 1.f * ts;
				box_data.box_trans.translation.x -= 1.f * ts;
				parts_data.parts_Transform[0].translation.x -= 1.f * ts;
				text_data.animation_but = 1;
				text_data.texid = Thomas::stash.Text_Storage["NPLAYER_LEFT.png"];
				text_data.text_file = Thomas::stash.Text_Storage["NPLAYER_LEFT.png"];

				//Audio for footstep
				AudioManager::PlaySFXAudioOnce("cat footsteps-idoors-carpet_5.wav", SoundSFX_CurrChannel + 20.0f);
			}
			else if (Thomas::Input::IsKeyPressed(TH_KEY_D)) {
				move_Direction = 1;
				trans.translation.x += 1.f * ts;
				box_data.box_trans.translation.x += 1.f * ts;
				parts_data.parts_Transform[0].translation.x += 1.f * ts;
				text_data.animation_but = 1;
				text_data.texid = Thomas::stash.Text_Storage["NPLAYER_RIGHT.png"];
				text_data.text_file = Thomas::stash.Text_Storage["NPLAYER_RIGHT.png"];

				//Audio for footstep
				AudioManager::PlaySFXAudioOnce("cat footsteps-idoors-carpet_5.wav", SoundSFX_CurrChannel + 20.0f);
			}
			else {
				text_data.animation_but = 2;
				text_data.switch_text = 0;
			}
			if (Thomas::Input::IsKeyPressed(TH_KEY_ESCAPE)) {
				Thomas::SceneSerializer serializer(GetScene());
				serializer.LoadScene(Thomas::stash.Scene_Storage["New_PauseMenu.json"]);
				g_IsPaused = true;
			}
			if (Thomas::Input::IsMouseButtonPressed(TH_MOUSE_BUTTON_LEFT))
			{
				parts_data.parts_Texture[0].texid = Thomas::stash.Text_Storage["handGun_anim.png"];
				parts_data.parts_Texture[0].text_file = Thomas::stash.Text_Storage["handGun_anim.png"];
				parts_data.parts_Texture[0].animation_but = 3;
				if (g_bulletLifetime <= 0)
				{
					auto entity = GetScene()->CreateEntity("Bullet");
					InitBullet(entity, GetSelf());
					
				}
			}

			if (GetComponent<Thomas::ObjectType>().win_point != g_points)
			{
				GetComponent<Thomas::ObjectType>().win_point = g_points;
			}

			auto& combat_data = GetComponent<Thomas::CombatComponent>();

			if (combat_data.health <= 0)
			{
				g_gameStateNext = GameState::GameOver;
			}

			if (g_bulletLifetime >= 0.f) {
				g_bulletLifetime -= ts;
			}
		}
	}


	void OnDestroy()
	{

	}

	void InitBullet(Thomas::Entity& entity, Thomas::Entity& player)
	{
		if (g_bulletLifetime <= 0.f) {
			//set transform data
			auto& trans = entity.GetComponent<Thomas::Transform>();
			trans.scaling.x = 0.6f;
			trans.scaling.y = 0.6f;
			trans.z_axis = player.GetComponent<Thomas::Transform>().z_axis;
			trans.translation.x = player.GetComponent<Thomas::Additional_Parts>().parts_Transform[0].translation.x;
			trans.translation.y = player.GetComponent<Thomas::Additional_Parts>().parts_Transform[0].translation.y;
			trans.rotation = player.GetComponent<Thomas::Additional_Parts>().parts_Transform[0].rotation - (float)((M_PI/2));

			//set texture
			auto& tex = entity.AddComponent<Thomas::Texture>();
			tex.texid = Thomas::stash.Text_Storage["rotten_core_glow_1.png"];
			tex.text_file = 132;
			tex.filename = "rotten_core_glow_1.png";

			//set bounding box data
			auto& box = entity.GetComponent<Thomas::Box_collider>();
			box.box_tog = 0;
			box.box_trans.scaling.x = 0.4f;
			box.box_trans.scaling.y = 0.4f;
			box.box_trans.translation.x = player.GetComponent<Thomas::Additional_Parts>().parts_Transform[0].translation.x;
			box.box_trans.translation.y = player.GetComponent<Thomas::Additional_Parts>().parts_Transform[0].translation.y;

			//Audio for shooting bullet
			SoundSFX_CurrChannel = Thomas::CAudioEngine::PlaySFXSound(Thomas::stash.Audio_Storage["bug-death-splatter_new.wav"], Thomas::CAudioEngine::curr_volume);

			auto& bullet_data = entity.AddComponent<Thomas::BulletComponent>();
			bullet_data.speed = 5.f;
			bullet_data.time = 3.0f;

			auto& type = entity.AddComponent<Thomas::ObjectType>();
			type.type = Thomas::ObjectTypeID::bullet;

			auto& combat = entity.AddComponent<Thomas::CombatComponent>();
			combat.attack = 3.f;

			auto& box_collider2d = entity.AddComponent<Thomas::BoxCollider2D>();
			//auto& data = entity.AddComponent<Thomas::RigidBody>();
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice0);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice1);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice2);
			box_collider2d.verticesList.push_back(box.box_trans.global_vertice3);

			//bullet movement direction based on the mouse position and center of the screen
			if (((Thomas::Input::GetMouseX() / Thomas::Application::Get().GetWindow().GetWidth() - 0.5f) * 4) >= 0.f) {
				bullet_data.dir.x = cosf(static_cast <float>(-trans.rotation - M_PI / 2.f));
				bullet_data.dir.y = sinf(static_cast <float>(-trans.rotation - M_PI / 2.f));
			}
			else if (((Thomas::Input::GetMouseX() / Thomas::Application::Get().GetWindow().GetWidth() - 0.5f) * 4) < 0.f) {
				bullet_data.dir.x = -cosf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
				bullet_data.dir.y = -sinf(static_cast <float>(-trans.rotation - (3.f * M_PI) / 2.f));
			}
			/*trans.translation.x += bullet_data.dir.x * bullet_data.speed * ts;
			trans.translation.y += bullet_data.dir.y * bullet_data.speed;
			box.box_trans.translation.x += bullet_data.dir.x * bullet_data.speed;
			box.box_trans.translation.y += bullet_data.dir.y * bullet_data.speed;*/
			g_bulletLifetime += 0.25f;
		}

	}

};