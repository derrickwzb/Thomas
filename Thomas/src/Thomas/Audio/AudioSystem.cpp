#include "thpch.h"
//#include "AudioSystem.h"
//#include "Platform/Windows/WindowsInput.h"
//#include "Thomas/Core/KeyCodes.h"
//
//namespace Thomas {
//
//	void AudioSystem::Init() {
//		CAudioEngine AEngine;
//		AEngine.Init();
//	}
//	
//	void AudioSystem::Update(std::vector<EntityID> allentity) {
//
//		for (auto const& entity : allentity) {
//
//			if (factory.HasComponent<AudioComponent>(entity)) {
//				
//				auto getAudio = factory.GetComponent<AudioComponent>(entity);
//				CAudioEngine AEngine;
//				//playing a sound
//				getAudio.filepath = stash.Audio_Storage["boss.wav"];
//				getAudio.fVolumedB = 10.0;
//				//std::cout << getAudio.filepath << "\n" << getAudio.fVolumedB;
//				getAudio.nChannelId = AEngine.PlaySound(getAudio.filepath, getAudio.fVolumedB);
//				factory.UpdateComponent<Thomas::AudioComponent>(entity, getAudio);//Updates data for component
//
//			}
//		}
//	}
//
//	void AudioSystem::TempSfxInput(std::vector<EntityID> allentity) {
//
//		auto start = std::chrono::steady_clock::now();
//
//		for (auto const& entity : allentity) {
//
//			if (factory.HasComponent<AudioComponent>(entity)) {
//
//				if (Input::IsKeyPressed(TH_KEY_M)) {
//
//					auto getAudio = factory.GetComponent<AudioComponent>(entity);
//					CAudioEngine AEngine;
//					//playing a sound
//					getAudio.filepath = stash.Audio_Storage["death.mp3"];
//					getAudio.fVolumedB = 10.0;
//					//std::cout << getAudio.filepath << "\n" << getAudio.fVolumedB;
//					getAudio.nChannelId = AEngine.PlaySfxSound(getAudio.filepath, getAudio.fVolumedB);
//					factory.UpdateComponent<Thomas::AudioComponent>(entity, getAudio);//Updates data for component
//
//				}
//			}
//		}
//
//		auto stop = std::chrono::steady_clock::now();
//		std::chrono::duration<double> duration = (stop - start);
//		Audio_timetaken = duration.count();
//	}
//
//}