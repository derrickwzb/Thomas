using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Thomas
{
    public class Audio
    {

        public static int PlaySound(string filepath)
        {
            return InternalCalls.Audio_PlaySound(filepath);
        }

        public static bool PauseChannel(int channel)
        {
            return InternalCalls.Audio_PauseSound(channel);
        }

        public static bool AudioIsPlaying(int channel)
        {
            return InternalCalls.Audio_IsPlaying(channel);
        }
    }
}
