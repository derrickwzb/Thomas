///*!*************************************************************************
//\file           Logic.cpp
//\author         Chen XinPeng
//\par DP email:  c.xinpeng@digipen.edu
//\par Programming CSD2400 Game project
//\date           28/09/2022
//\brief
//This file contains the defination for logic system, it contains 2 different
//logic for the game object
//****************************************************************************/
//#pragma once
#include "thpch.h"
//#include "Logic.h"
//#include "Thomas/Scene/Entity.h"
//#include "Platform/Windows/WindowsInput.h"
//#include "Thomas/Core/KeyCodes.h"
//#include "Thomas/Physics/physicsSystem.h"
//#include "Thomas/Renderer/Graphics.h"
//
//#include "Thomas/Core/application.h"
//#include "GLFW/glfw3.h"
//
//namespace Thomas {
//
//	static float change = 1.f;
//	static int w{};
//	static int h{};
//
//	enum {
//	move_right,
//	move_down,
//	move_left,
//	move_up
//	};
//
//	static int logic01_move = move_right;
//	static bool logic01_addw = false;
//	static bool logic01_addh = false;
//
//	static bool logic02_run = false;
//	static bool logic02_addw = false;
//	static bool logic02_addh = false;
//
//	//first logic will make the object partol around the screen
//	void Logic01::update(EntityID entity, Timestep ts) {
//		auto trans_data = factory.GetComponent<Transform>(entity);
//		//auto box_data = factory.GetComponent<Box_collider>(entity);
//
//		if (trans_data.translation.x >= 2) {
//			logic01_addw = false;
//		}
//		if (trans_data.translation.x <= -2) {
//			logic01_addw = true;
//		}
//
//		if (trans_data.translation.y >= 2) {
//			logic01_addh = false;
//		}
//		if (trans_data.translation.y <= -2) {
//			logic01_addh = true;
//		}
//
//		if (trans_data.translation.x <= -2 && trans_data.translation.y <= -2) {
//			trans_data.translation.x += change * ts;
//			trans_data.translation.y += change * ts;
//		}
//		else if (trans_data.translation.x >= 2 && trans_data.translation.y >= 2) {
//			trans_data.translation.x -= change * ts;
//			trans_data.translation.y -= change * ts;
//		}
//		else {
//			switch (logic01_move)
//			{
//			case move_right:
//				trans_data.translation.x += change * ts;
//				if (trans_data.translation.x >= 2 - trans_data.scaling.x / 4) {
//					logic01_move = move_down;
//				}
//				break;
//			case move_down:
//				trans_data.translation.y += change * ts;
//				if (trans_data.translation.y >= 2 - trans_data.scaling.y / 2) {
//					logic01_move = move_left;
//				}
//				break;
//			case move_left:
//				trans_data.translation.x -= change * ts;
//				if (trans_data.translation.x <= -2 + trans_data.scaling.x / 4) {
//					logic01_move = move_up;
//				}
//				break;
//			case move_up:
//				trans_data.translation.y -= change * ts;
//				if (trans_data.translation.y <= -2 + trans_data.scaling.y / 2) {
//					logic01_move = move_right;
//				}
//				break;
//			default:
//				break;
//			}
//		}
//
//		factory.UpdateComponent<Transform>(entity, trans_data);
//		//factory.UpdateComponent<Box_collider>(entity, box_data);
//	}
//
//	//second logic will make the object follow the mouse when the user
//	//press space key, it will stop follow when user press space key again
//	void Logic02::update(EntityID entity, Timestep ts) {
//		auto trans_data = factory.GetComponent<Transform>(entity);
//		//auto box_data = factory.GetComponent<Box_collider>(entity);
//
//		if (Input::IsKeyPressed(TH_KEY_SPACE)) {
//			if (logic02_run == false) {
//				logic02_run = true;
//			}
//			else if (logic02_run == true) {
//				logic02_run = false;
//			}
//		}
//
//		if (logic02_run == true) {
//
//			if (trans_data.translation.x >= ((Input::GetMouseX() / w * 2 - 1) * 2)) {
//				logic02_addw = false;
//			}
//			if (trans_data.translation.x <= ((Input::GetMouseX() / w * 2 - 1) * 2)) {
//				logic02_addw = true;
//			}
//
//			if (logic02_addw == true) {
//				trans_data.translation.x += change * ts;
//				//box_data.box_trans.translation.x += change * ts;
//			}
//			if (logic02_addw == false) {
//				trans_data.translation.x -= change * ts;
//				//box_data.box_trans.translation.x -= change * ts;
//			}
//
//			if (trans_data.translation.y >= ((Input::GetMouseY() / h * 2 - 1) * 2)) {
//				logic02_addh = false;
//			}
//			if (trans_data.translation.y <= ((Input::GetMouseY() / h * 2 - 1) * 2)) {
//				logic02_addh = true;
//			}
//
//			if (logic02_addh == true) {
//				trans_data.translation.y += change * ts;
//				//box_data.box_trans.translation.y += change * ts;
//			}
//			if (logic02_addh == false) {
//				trans_data.translation.y -= change * ts;
//				//box_data.box_trans.translation.y -= change * ts;
//			}
//		}
//
//		factory.UpdateComponent<Transform>(entity, trans_data);
//		//factory.UpdateComponent<Box_collider>(entity, box_data);
//	}
//
//	//get the width and height of the sceen
//	void Logic::Init() {
//		Thomas::Application& app = Thomas::Application::Get();
//		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
//		glfwGetWindowSize(window, &w, &h);
//	}
//
//	//update object that have logic component
//	void Logic::Update(std::vector<EntityID> allentity, Timestep ts) {
//
//		auto start = std::chrono::steady_clock::now();
//
//		for (auto const& entity : allentity) {
//
//			if (factory.HasComponent<Logic01>(entity)) {
//				auto logic = factory.GetComponent<Logic01>(entity);
//				logic.update(entity, ts);
//				factory.UpdateComponent<Logic01>(entity, logic);
//			}
//
//			if (factory.HasComponent<Logic02>(entity)) {
//				auto logic2 = factory.GetComponent<Logic02>(entity);
//				logic2.update(entity, ts);
//				factory.UpdateComponent<Logic02>(entity, logic2);
//			}
//		}
//
//		auto stop = std::chrono::steady_clock::now();
//		std::chrono::duration<double> duration = (stop - start);
//		Logic_timetaken = duration.count();
//	}
//}
