using System;
using System.Text;
using System.Threading.Tasks;

namespace Thomas
{
    public abstract class Component
    {
        public Entity Entity { get; internal set; }
    }

    public class Transform : Component
    {
        public Vector3 Translation
        { 
            get
            {
                InternalCalls.Transform_GetTranslation(Entity.ID, out Vector3 translation);
                return translation;
            }

            set
            {
                InternalCalls.Transform_SetTranslation(Entity.ID, ref value);  
            }
        
        }


    }

}
