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

    // Way to check that all FMOD calls are successful 
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
        //std::cout << "init engine";
    }

    void CAudioEngine::Shutdown() {
        CAudioEngine::ErrorCheck(BGM->release());
        CAudioEngine::ErrorCheck(SFX->release());
        CAudioEngine::ErrorCheck(Master->release());
        CAudioEngine::ErrorCheck(mpSystem->release());
    }

    //In this function, check if a channel has stopped playing,
    //if it has, we destroy it so we can clear up a channel to use. 
    void CAudioEngine::Update() {
        //Vector to store the channels that was stopped
        std::vector<std::map<int, FMOD::Channel*>::iterator> pStoppedChannels;

        //iterate through the whole channel map to find if a sound is playing
        for (auto it = ChannelMap.begin(), itEnd = ChannelMap.end(); it != itEnd; ++it) {
            bool bIsPlaying = false;
            it->second->isPlaying(&bIsPlaying);
            if (!bIsPlaying) {
                pStoppedChannels.push_back(it);
            }
        }
        //delete all the stopped channels
        for (auto& it : pStoppedChannels) {
            ChannelMap.erase(it);
        }
        CAudioEngine::ErrorCheck(mpSystem->update());
    }

    void CAudioEngine::LoadSound(const std::string& strSoundName, bool bLooping) {
       //Find the sound name in the sound map
        auto tFoundIt = SoundMap.find(strSoundName);
        if (tFoundIt != SoundMap.end())
            return;
        //setting the mode to default, if there is looping, set the sound to loop
        FMOD_MODE eMode = FMOD_DEFAULT;
        eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

        FMOD::Sound* pSound = nullptr;
        CAudioEngine::ErrorCheck(mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
        if (pSound) {
            SoundMap[strSoundName] = pSound;
        }

    }

    //Unloading of sounds. Take in the file name, look it up in the sound map and release the sound.
    void CAudioEngine::UnLoadSound(const std::string& strSoundName) {
        //Find the sound name in the sound map
        auto tFoundIt = SoundMap.find(strSoundName);
        if (tFoundIt == SoundMap.end())
            return;

        CAudioEngine::ErrorCheck(tFoundIt->second->release());
        SoundMap.erase(tFoundIt);
    }

    //Every sound must have a channel,returns an int which is the sound channel
    int CAudioEngine::PlaySound(const std::string& strSoundName, float fVolumedB)
    {
        //std::cout << "is playing" << std::endl;
        int nChannelId = mnNextChannelId++;
        auto tFoundIt = SoundMap.find(strSoundName);
        if (tFoundIt == SoundMap.end()) {
            LoadSound(strSoundName);
            tFoundIt = SoundMap.find(strSoundName);
            if (tFoundIt == SoundMap.end()) {
                return nChannelId;
            }
        }

        FMOD::Channel* pChannel = nullptr;
        CAudioEngine::ErrorCheck(mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
        if (pChannel) {
            FMOD_MODE currMode;
            tFoundIt->second->getMode(&currMode);
            CAudioEngine::ErrorCheck(pChannel->setVolume(VolumeTodb(fVolumedB)));
            CAudioEngine::ErrorCheck(pChannel->setPaused(false));
            ChannelMap[nChannelId] = pChannel;
        }
        return nChannelId;
    }

    //Playing a SFX sound
    int CAudioEngine::PlaySfxSound(const std::string& strSoundName, float fVolumedB)
    {
        //std::cout << "is playing" << std::endl;
        int nChannelId = mnNextChannelId++;
        auto tFoundIt = SoundMap.find(strSoundName); //finding the sound in the soundmap according to the soundname
        if (tFoundIt == SoundMap.end()) {
            LoadSound(strSoundName);
            tFoundIt = SoundMap.find(strSoundName);
            if (tFoundIt == SoundMap.end()) {
                return nChannelId;
            }
        }

        FMOD::Channel* pChannel = nullptr;
        CAudioEngine::ErrorCheck(mpSystem->playSound(tFoundIt->second, SFX, true, &pChannel));
        if (pChannel) {
            FMOD_MODE currMode;
            tFoundIt->second->getMode(&currMode);
            CAudioEngine::ErrorCheck(pChannel->setVolume(VolumeTodb(fVolumedB)));
            CAudioEngine::ErrorCheck(pChannel->setPaused(false));
            ChannelMap[nChannelId] = pChannel;
        }
        return nChannelId;
    }

    //Stopping a channel
    void CAudioEngine::StopChannel(int nChannelId) {

        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;

        tFoundIt->second->stop();

    }

    //Pausing a channel
    void CAudioEngine::PauseChannel(int nChannelId) {

        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;

        tFoundIt->second->setPaused(true);
    }
    //Unpausing a channel
    void CAudioEngine::UnpauseChannel(int nChannelId) {

        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;

        tFoundIt->second->setPaused(false);

    }

    //Setting the channel volume 
    void CAudioEngine::SetChannelvolume(int nChannelId, float fVolumedB) {
        auto tFoundIt = ChannelMap.find(nChannelId);
        if (tFoundIt == ChannelMap.end())
            return;

        CAudioEngine::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
    }
    //Checking if a sound is playing or not
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

    //Math forumla to calculate from db to volume
    float CAudioEngine::dbToVolume(float dB) {

        return powf(10.0f, 0.05f * dB);

    }

    //Math forumla to calculate from db to volume
    float  CAudioEngine::VolumeTodb(float volume) {
        return 20.0f * log10f(volume);
    }

}