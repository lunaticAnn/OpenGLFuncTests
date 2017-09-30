#pragma once
#include "BaseSystem.h"
#include "../Models/Cube.h"
#include "glm\gtc\random.hpp"
#include<vector>

#define learn_factor 1.4961f
namespace Rendering{
	namespace Systems{
		class ParticleSystem: public BaseSystem{
			public:
				ParticleSystem(const size_t& pc);
				~ParticleSystem();
				void Update() override;
				
			private:
				size_t particle_count;
				glm::vec3 target_pos;
				
		};
	}
}
