using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Thomas;

namespace Scripts
{
    public class Camera : Entity
    {
        void OnUpdate(float ts)
        {
           
            float speed = 1.0f;
            Vector3 velocity = Vector3.Zero;

            if (Input.IsKeyDown(KeyCode.TH_KEY_UP))
                velocity.Y = 1.0f;

            else if (Input.IsKeyDown(KeyCode.TH_KEY_DOWN))
                velocity.Y = -1.0f;

            if (Input.IsKeyDown(KeyCode.TH_KEY_LEFT))
                velocity.X = -1.0f;

            else if (Input.IsKeyDown(KeyCode.TH_KEY_RIGHT))
                velocity.X = 1.0f;

            velocity *= speed;

            Vector3 translation = Translation;
            translation += velocity * ts;
            Translation = translation;
        }

    }

}