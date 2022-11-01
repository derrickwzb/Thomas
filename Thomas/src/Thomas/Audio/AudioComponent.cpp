#include "thpch.h"
#include "AudioComponent.h"

namespace Thomas {

	AudioComponent::AudioComponent() : filepath{}, bLooping{false}, fVolumedB{0.f}, nChannelId{1}{};

	AudioComponent::AudioComponent(std::string fpath, bool bloop, float fvol, int ncha) : 
	filepath{ fpath }, bLooping{ bloop }, fVolumedB{ fvol }, nChannelId{ ncha } {}

}