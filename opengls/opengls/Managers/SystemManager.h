#pragma once
#include "ModelsManager.h"
#include "../Rendering/Systems/BaseSystem.h"
#include "ModelsManager.h"
#include "../Rendering/Systems/ParticleSystem.h"
#include <map>

namespace Managers
{
	class SystemManager{
		public:
			SystemManager();
			~SystemManager();		
			void Update();
			void RegisterModels(ModelsManager* model_manager);
		protected:
			std::map<std::string, Systems::BaseSystem*> systemNameList;
	};
}