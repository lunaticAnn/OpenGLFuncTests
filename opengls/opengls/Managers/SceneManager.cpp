#include "SceneManager.h"
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = new ShaderManager();
	shader_manager->CreateProgram("colorShader",
		"Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");
}

SceneManager::~SceneManager(){
	delete shader_manager;
}

void SceneManager::notifyBeginFrame(){
	
}

void SceneManager::notifyDisplayFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

}

void SceneManager::notifyEndFrame(){
	
}

void SceneManager::notifyReshape(int width,
	int height,
	int previous_width,
	int previous_height){
	
}