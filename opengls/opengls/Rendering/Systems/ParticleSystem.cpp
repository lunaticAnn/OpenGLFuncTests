#include "ParticleSystem.h"

using namespace Rendering;
using namespace Systems;

ParticleSystem::ParticleSystem(const size_t& pc){
//create models and register them on the model manager;
	models = std::vector<Models::Model*>(pc);
	particle_count = pc;
	target_pos = glm::vec3(0.0);
	for(size_t i = 0; i < pc; i++){
		//update initial positions and scale
		Models::Model* m = new Models::Cube(glm::ballRand(1.0) ,glm::vec3(glm::linearRand(0.01,0.05)));
		models[i] = m;		
	}
}

ParticleSystem::~ParticleSystem() {
//de-register on model manager
}

void ParticleSystem::Update(){
//calculate speed and update locations accordingly
	time(&timer);
	target_pos = glm::vec3(5.0 *glm::sin(timer), 5.0 * glm::cos(timer), 0.0);
	for (size_t i = 0; i < particle_count; i++) {
		//update initial positions and scale
		glm::vec3 new_pos = models[i]->translation +
							(float)glm::linearRand(0.0, 0.1) 
							* (target_pos - models[i] -> translation);
		double dis = glm::distance(new_pos, target_pos);	
		models[i] -> translation = new_pos;		
	}
	
}