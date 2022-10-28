#include "thpch.h"//This must be the first header
#include "AudioEngine.h"

namespace Thomas {

    FMOD::System* CAudioEngine::mpSystem;
    std::map<std::string, FMOD::Sound*> CAudioEngine::SoundMap;
    std::map<int, FMOD::Channel*> CAudioEngine::ChannelMap;
    int CAudioEngine::mnNextChannelId;

    FMOD::ChannelGroup* CAudioEngine::BGM;
    FMOD::ChannelGroup* CAudioEngine::SFX;
    FMOD::ChannelGroup* CAudioEngine::Master;

    int CAudioEngine::ErrorCheck(FMOD_RESULT result) {
        if (result != FMOD_OK) {
            std::cout << "FMOD ERROR " << result << "\n";
            return 1;
        }
        return 0;
    }

    void CAudioEngine::Init() {
        FMOD::System_Create(&mpSystem);
        mpSystem->init(1024, FMOD_INIT_NORMAL, nullptr);
        mpSystem->getMasterChannelGroup(&Master);
        mpSystem->createChannelGroup("background", &BGM);
        mpSystem->createChannelGroup("special_fx", &SFX);
        Master->addGroup(BGM);
        Master->addGroup(SFX);
    }

    void CAudioEngine::Shutdown() {
        CAudioEngine::ErrorCheck(BGM->release());
        CAudioEngine::ErrorCheck(SFX->release());
        CAudioEngine::ErrorCheck(Master->release());
        CAudioEngine::ErrorCheck(mpSystem->release());
    }

    void CAudioEngine::Update() {
    
        std::vector<std::map<int, FMOD::Channel*>::iterator> pStoppedChannels;

        for (auto it = ChannelMap.begin(), itEnd = ChannelMap.end(); it != itEnd; ++it)
        {
            bool bIsPlaying = false;
            it->second->isPlaying(&bIsPlaying);
            if (!bIsPlaying)
            {
                pStoppedChannels.push_back(it);
            }
        }
        for (auto& it : pStoppedChannels)
        {
            ChannelMap.erase(it);
        }
        CAudioEngine::ErrorCheck(mpSystem->update());
    }

    void CAudioEngine::LoadSound(const std::string& strSoundName, bool bLooping)
    {
        auto tFoundIt = SoundMap.find(strSoundName);
        if (tFoundIt !=  SoundMap.end())
            return;

        FMOD_MODE eMode = FMOD_DEFAULT;
        eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

        FMOD::Sound* pSound = nullptr;
        CAudioEngine::ErrorCheck(mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
        if (pSound) {
            SoundMap[strSoundName] = pSound;
        }

    }

    //Unloading of sounds. Take in the file name, look it up in the sound map and release the sound.
    void CAudioEngine::UnLoadSound(const std::string& strSoundName)
    {
        auto tFoundIt = SoundMap.find(strSoundName);
        if (tFoundIt == SoundMap.end())
            return;

        CAudioEngine::ErrorCheck(tFoundIt->second->release());
        SoundMap.erase(tFoundIt);
    }

    //Every sound must have a channel,returns an int which is the sound channel
    int CAudioEngine::PlaySound(const std::string& strSoundName, float fVolumedB)
    {
        std::cout << "is playing" << std::endl;
        int nChannelId = mnNextChannelId++;
        auto tFoundIt = SoundMap.find(strSoundName);
        if (tFoundIt == SoundMap.end())
        {
            LoadSound(strSoundName);
            tFoundIt = SoundMap.find(strSoundName);
            if (tFoundIt == SoundMap.end())
            {
                return nChannelId;
            }
        }
        FMOD::Channel* pChannel = nullptr;
        CAudioEngine::ErrorCheck(mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
        if (pChannel)
        {
            FMOD_MODE currMode;
            tFoundIt->second->getMode(&currMode);
            CAudioEngine::ErrorCheck(pChannel->setVolume(VolumeTodb(fVolumedB)));
            CAudioEngine::ErrorCheck(pChannel->setPaused(false));
            ChannelMap[nChannelId] = pChannel;
        }
        return nChannelId;
    }

    void CAudioEngine::StopChannel(int nChannelId) {
       
        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;
       
        tFoundIt->second->stop();

    }

    void CAudioEngine::PauseChannel(int nChannelId) {
        
        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;

        tFoundIt->second->setPaused(true);
    }
    
    void CAudioEngine::UnpauseChannel(int nChannelId) {

        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;

        tFoundIt->second->setPaused(false);

    }

    void CAudioEngine::SetChannelvolume(int nChannelId, float fVolumedB)
    {
        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;

        CAudioEngine::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
    }

    bool CAudioEngine::IsPlaying(int nChannelId) const {

        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return true;
        
        bool isplaying;
        if (tFoundIt->second->isPlaying(&isplaying)) {
            return true;
        }
        return false;

    }

    float CAudioEngine::dbToVolume(float dB) {

        return powf(10.0f, 0.05f * dB);

    }
    float  CAudioEngine::VolumeTodb(float volume) {
        return 20.0f * log10f(volume);
    }



}