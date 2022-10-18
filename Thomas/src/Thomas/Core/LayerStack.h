/******************************************************************************/
/*!
\file		LayerStack.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the class abstraction of the LayerStack system

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "Thomas/Core/Core.h"
#include "Layer.h"

#include <vector>

namespace Thomas 
{

	class THOMAS_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }


	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;

	};


}

