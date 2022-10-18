/******************************************************************************/
/*!
\file		LayerStack.cpp
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of LayerStack class
			that are specified in the interface file LayerStack.h

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "thpch.h"
#include "LayerStack.h"


namespace Thomas {
	
	/**************************************************************************/
	/*!
		This is the default constructor of the LayerStack class.
	*/
	/**************************************************************************/
	LayerStack::LayerStack()
	{
		
	}
	/**************************************************************************/
	/*!
		This is the default destructor of the LayerStack class.
	*/
	/**************************************************************************/
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}	
	/**************************************************************************/
	/*!
		This is the definition of PushLayer member function.
	*/
	/**************************************************************************/
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}
	/**************************************************************************/
	/*!
		This is the definition of PushOverlay member function.
	*/
	/**************************************************************************/
	void LayerStack::PushOverlay(Layer* overlay)
	{
		 m_Layers.emplace_back(overlay);
	}
	/**************************************************************************/
	/*!
		This is the definition of PopLayer member function.
	*/
	/**************************************************************************/
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	/**************************************************************************/
	/*!
		This is the definition of PopOverlay member function.
	*/
	/**************************************************************************/
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}