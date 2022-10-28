#include "thpch.h"
#include "AudioSystem.h"


namespace Thomas {

	void AudioSystem::Init() {
		CAudioEngine AEngine;
		AEngine.Init();
	}
	
	void AudioSystem::Update(std::vector<Entity> allentity) {

		for (auto const& entity : allentity) {

			if (factory.HasComponent<AudioComponent>(entity)) {

				auto getAudio = factory.GetComponent<AudioComponent>(entity);
				CAudioEngine AEngine;
				//playing a sound
				getAudio.filepath = "C:\\Users\\Brandon\\Documents\\GitHub\\Thomas\\Assets\\boss.wav";
				getAudio.fVolumedB = 10.0;
				//std::cout << getAudio.filepath << "\n" << getAudio.fVolumedB;
				getAudio.nChannelId = AEngine.PlaySound(getAudio.filepath, getAudio.fVolumedB);
				factory.ChangeComponent<Thomas::AudioComponent>(entity, getAudio);//Updates data for component

			}
		}
	}




}