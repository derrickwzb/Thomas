/******************************************************************************/
/*!
\file		Layer.cpp
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the implementation of Layer class
			that are specified in the interface file Layer.h

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "thpch.h"
#include "Thomas/Core/Layer.h"

namespace Thomas {
	/**************************************************************************/
	/*!
		This is the default constructor of the Layer class.
	*/
	/**************************************************************************/
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}


}