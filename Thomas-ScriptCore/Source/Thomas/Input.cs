using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Thomas
{
    public class Input
    {

        public static bool IsKeyDown(KeyCode keycode)
        {
            return InternalCalls.Input_IsKeyDown(keycode);
        }

        public static bool IsMouseButtonPressed(int button) 
        {
            return InternalCalls.Input_MouseButtonPressed(button); 
        }
        
        /*
        public static float GetMouseX() 
        { 
            return s_Instance->GetMouseXImpl(); 
        }
        public static float GetMouseY() 
        { 
            return s_Instance->GetMouseYImpl(); 
        }
        public static std::pair<float, float> GetMousePosition()
        { 
            return s_Instance->GetMousePositionImpl(); 
        }*/

    }
}
