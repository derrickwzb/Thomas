using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace Thomas
{
    public static class InternalCalls
    {
        // ENTITITYTY
        //Internal calls inside the c# script must match with the internal call inside the C++ file
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Entity_HasComponent(ulong entityid, Type componentType);

        
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void Transform_GetTranslation(ulong entityid, out Vector3 translation);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static float Transform_SetTranslation(ulong entityid, ref Vector3 translation);
        
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool RigidBody_ChangePosition(ulong entityid, float posX, float posY);



        // INPUT

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Input_IsKeyDown(KeyCode keycode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Input_MouseButtonPressed(int button);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static float Input_GetMouseX();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static float Input_GetMouseY();




        //SCENE MANAGER
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void LoadScene(string filepath);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void SaveScene(string filepath);


        //Creating Entity
        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //internal extern static void CreateEntityCSharp(string name);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static int Audio_PlaySound(string filepath);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Audio_PauseSound(int channel);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static bool Audio_IsPlaying(int channel);
    }

}
