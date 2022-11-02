/*!*************************************************************************
\file           Timestep.h
\author         Chen XinPeng
\par DP email:  c.xinpeng@digipen.edu
\par Programming CSD2400 Game project
\date           28/09/2022
\brief
This file contains the declaration for the delta time class
****************************************************************************/
#pragma once

namespace Thomas {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time) {}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}
