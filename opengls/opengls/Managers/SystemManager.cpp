#include "SystemManager.h"

using namespace Managers;
SystemManager::SystemManager(){
	Systems::ParticleSystem* particle_system = new Systems::ParticleSystem(1000);
	systemNameList["marching_cube"] = particle_system;
}

SystemManager::~SystemManager(){

}

void SystemManager::RegisterModels(ModelsManager* model_manager){
	for(auto it : systemNameList){
		model_manager->SetModels(it.first, it.second ->GetModels());
	}
}
void SystemManager::Update(){
	for (auto it : systemNameList) {
		 it.second->Update();
	}
};