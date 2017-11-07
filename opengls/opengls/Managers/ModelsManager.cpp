#include "ModelsManager.h"

using namespace Managers;
using namespace Rendering;

ModelsManager::ModelsManager(){	
	
}

ModelsManager::~ModelsManager(){
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

void ModelsManager::DeleteModel(const std::string& gameModelName){
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const{
	return (*gameModelList.at(gameModelName));
}

void ModelsManager::Update(){	
	for (auto model : gameModelList){
		model.second->Update();
	}
}

void ModelsManager::Draw(){
	for (auto model : gameModelList){
		model.second->Draw();
	}
}

//add defered rendering support
void ModelsManager::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix) {
	for (auto model : gameModelList) {
		model.second->Draw(projection_matrix, view_matrix);
	}
}

void ModelsManager::SetModel(const std::string& gameObjectName, IGameObject* gameObject){
	gameModelList[gameObjectName.c_str()] = gameObject;
}

void ModelsManager::SetModels(const std::string& gameObjectGroupName, std::vector<Models::Model*>* gameObjects){
	for(size_t i = 0; i < gameObjects->size(); i++){
		gameModelList[(gameObjectGroupName + std::to_string(i)).c_str()] = (*gameObjects)[i];
		(*gameObjects)[i]->SetProgram(ShaderManager::GetShader("colorShader"));
		(*gameObjects)[i]->Create();
	}
}