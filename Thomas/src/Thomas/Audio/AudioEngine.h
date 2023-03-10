#pragma once

#include "../vendor/fmod/inc/fmod.hpp"
#include "../vendor/fmod/inc/fmod_errors.h"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include "AudioComponent.h"

namespace Thomas {

    class CAudioEngine {
    public:
        static FMOD::System* mpSystem; //Pointer to system
        static int mnNextChannelId; //Channel Id 1 sound to 1 channel
        static std::map<std::string, FMOD::Sound*> SoundMap; //Pointer to the fmod sound api
        static std::map<int, FMOD::Channel*> ChannelMap; //Pointer to an fmod channel
        static FMOD::ChannelGroup *BGM, *SFX ,*Master; //Creating 3 diff channel groups 

        static void Init();
        static void Update();
        static void Shutdown();
        static int  ErrorCheck(FMOD_RESULT result);

        static void LoadSound(const std::string& strSoundName, bool bLooping = false);
        static void UnLoadSound(const std::string& strSoundName);
        static void PlaySFX(bool& canplay, const std::string& filepath, float vol);
        static int  PlaySound(const std::string& strSoundName, float fVolumedB = 0.0f);
        static int  PlaySFXSound(const std::string& strSoundName, float fVolumedB = 0.0f);
        static int  PlayBGMSound(const std::string& strSoundName, float fVolumedB = 0.0f);
        static void StopChannel(int channelid);
        static void PauseChannel(int channelid);
        static void UnpauseChannel(int channelid);
        //void StopAllChannels();
        static void SetChannelvolume(int channelid, float fVolumedB);
        static bool IsPlaying(int channelid);
    
        static float dbToVolume(float db); //make sure to measure the sound
        static float VolumeTodb(float volume); //make sure to measure the sound

        inline static float curr_volume{};
        inline static int SFXCurrChID{};
 
    };

    static CAudioEngine AEngine;

}
