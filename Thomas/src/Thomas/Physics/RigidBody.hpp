#pragma once
#include "Thomas/Math/Matrix3x3.h"
#include "Thomas/Math/Vector2D.h"

constexpr float UNIT_MASS = 1.0f;
constexpr float GRAVITY = 9.8f;

namespace Thomas {
    
    class RigidBody {

    public:
        RigidBody() { m_Mass = UNIT_MASS, m_Gravity = GRAVITY; }
        Vector2D m_Position;
        float Velocity;

        //Setters & Getters for Mass and Gravity
        //Keyword inline is used to save memory good use for 1 line function
        inline void SetMass(float mass) { mass = m_Mass; }
        inline float GetMass() { return m_Mass; }
        inline void SetGravity(float gravity) { gravity = m_Gravity; }
        
        inline void SetPositionX(float posX) { m_Position.x = posX; }
        inline float  GetPositionX(void) { return m_Position.x; }
        inline void SetPositionY(float posY) { m_Position.y = posY; }
        inline float  GetPositionY(void) { return m_Position.y; }


    private:
        float m_Mass;
        float m_Gravity;

    };

}
