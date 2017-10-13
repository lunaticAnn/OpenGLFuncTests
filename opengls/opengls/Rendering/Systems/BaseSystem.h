#pragma once
#include "../Models/Model.h"
#include <vector>

namespace Rendering{
	namespace Systems{
		class BaseSystem {
			public:
				BaseSystem(){};
				virtual ~BaseSystem(){};
				virtual void Update() = 0;
				std::vector<Models::Model*>* GetModels(){return &models;};
			protected:
				std::vector<Models::Model*> models;
				int timer;
		};
	}
}