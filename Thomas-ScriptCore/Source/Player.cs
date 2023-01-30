using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Thomas;

namespace Scripts
{
    public class Player : Entity
    {

        private Transform m_Transform;

        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {ID}");

            m_Transform = GetComponent<Transform>();

            //Scene.Load_Scene("../Assets/Scene/Mainmenu.json");
            
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

            Vector3 translation = m_Transform.Translation;
            translation += velocity * ts;
            m_Transform.Translation = translation;
        }

    }

}