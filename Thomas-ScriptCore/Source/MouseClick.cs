using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Thomas;

namespace Scripts{
    class MouseClick : Entity
    {

        void onCreate()
        {


        }

        void OnUpdate(float ts)
        {
            if (Input.IsMouseButtonPressed(0))
                Console.WriteLine("This is being clicked");

        }

    }




}
