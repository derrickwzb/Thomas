using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Thomas
{
    public class Scene
    {
        public static void Load_Scene(string filepath)
        {
           InternalCalls.LoadScene(filepath);
        }

        public static void Save_Scene(string filepath)
        {
            InternalCalls.SaveScene(filepath);
        }
    }
}
