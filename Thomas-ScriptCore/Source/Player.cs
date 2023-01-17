using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Thomas;

namespace Sandbox
{
    public class Player : Entity
    {

        private Transform m_Transform;
        private RigidBody m_RigidBody;

        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {ID}");

            m_Transform = GetComponent<Transform>();
            m_RigidBody = GetComponent<RigidBody>();
        }

        void OnUpdate(float ts)
        {
            Console.WriteLine($"Player.OnUpdate: {ts}");

            float speed = 1.0f;
            Vector3 velocity = Vector3.Zero;

            if (Input.IsKeyDown(KeyCode.TH_KEY_W))
                velocity.Y = 1.0f;

            else if (Input.IsKeyDown(KeyCode.TH_KEY_S))
                velocity.Y = -1.0f;

            if (Input.IsKeyDown(KeyCode.TH_KEY_A))
                velocity.X = -1.0f;

            else if (Input.IsKeyDown(KeyCode.TH_KEY_D))
                velocity.X = 1.0f;

            velocity *= speed;

            int x = 1;
            int y = 1;
            ++x; ++y;

            if (Input.IsKeyDown(KeyCode.TH_KEY_SPACE))
                m_RigidBody.RigidBody_ChangePosition(x, y);

            Vector3 translation = m_Transform.Translation;
            translation += velocity * ts;
            m_Transform.Translation = translation;
        }

    }

}