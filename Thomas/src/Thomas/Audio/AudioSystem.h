#pragma once
#include "Thomas/Audio/AudioEngine.h"
#include "Thomas/Audio/AudioComponent.h"
#include "Thomas/Scene/Entity.h"

namespace Thomas {

	class AudioSystem {

	public:
		void Init();
		void Update(std::vector<EntityID> allentity);
		void TempSfxInput(std::vector<EntityID> allentity);

		inline static double Audio_timetaken = 0;

	};

	static AudioSystem aSystem;

}