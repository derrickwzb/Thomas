#include "thpch.h"
#include "AudioSystem.h"
#include "Platform/Windows/WindowsInput.h"
#include "Thomas/Core/KeyCodes.h"

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
				getAudio.filepath = "../Assets/boss.wav";
				getAudio.fVolumedB = 10.0;
				//std::cout << getAudio.filepath << "\n" << getAudio.fVolumedB;
				getAudio.nChannelId = AEngine.PlaySound(getAudio.filepath, getAudio.fVolumedB);
				factory.UpdateComponent<Thomas::AudioComponent>(entity, getAudio);//Updates data for component

			}
		}
	}

	void AudioSystem::TempSfxInput(std::vector<Entity> allentity) {

		for (auto const& entity : allentity) {

			if (factory.HasComponent<AudioComponent>(entity)) {

				if (Input::IsKeyPressed(TH_KEY_L)) {

					auto getAudio = factory.GetComponent<AudioComponent>(entity);
					CAudioEngine AEngine;
					//playing a sound
					getAudio.filepath = "../Assets/death.mp3";
					getAudio.fVolumedB = 10.0;
					//std::cout << getAudio.filepath << "\n" << getAudio.fVolumedB;
					getAudio.nChannelId = AEngine.PlaySfxSound(getAudio.filepath, getAudio.fVolumedB);
					factory.UpdateComponent<Thomas::AudioComponent>(entity, getAudio);//Updates data for component

				}
			}
		}
	}

}