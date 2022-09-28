#include "Thomas/Maths/Matrix3x3.h"
#include "Thomas/Maths/Vector2D.h"

#define UNIT_MASS 1.0f
#define GRAVITY 9.8f

namespace Thomas {

    class RigidBody {

        public:
            RigidBody() : m_Mass{ UNIT_MASS }, m_Gravity{ GRAVITY } {}

        //Setters & Getters for Mass and Gravity
        //Keyword inline is used to save memory good use for 1 line function
        inline void SetMass(float mass) {mass = m_Mass;}
        inline void SetGravity(float gravity) {gravity = m_Gravity;}

        //Force
        inline void ApplyForce(Vector2D force) {m_Force = force;}
        inline void ApplyForceX(Vector2D forceX) {m_Force.x = forceX.x;}
        inline void ApplyForceY(Vector2D forceY) {m_Force.y = forceY.y;}
        inline void ZeroForce() {m_Force = Vector2D(0,0);}

        //Friction
        inline void ApplyFriction(Vector2D friction) {m_Friction = friction;}
        inline void ZeroFriction() {m_Friction = Vector2D(0,0);}

        //Update Methods
        void Update(float dt) {

            m_Acceleration.x = (m_Force.x + m_Friction.x) / m_Mass;
            m_Acceleration.y = m_Gravity + (m_Force.y / m_Mass);
            m_Velocity = m_Acceleration * dt;
            m_Position = m_Velocity * dt;

        }   

        private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;

    }


}
