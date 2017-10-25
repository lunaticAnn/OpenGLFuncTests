#include "SceneManager.h"
using namespace Managers;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = new ShaderManager();
	shader_manager->CreateProgram("colorShader",
		"Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");

	camera = new Camera(glm::vec3(5.0,2.0,1.0), glm::vec3(0.0,0.0,0.0));
	view_matrix = camera -> ViewMatrix();
	
	model_manager = new ModelsManager();
	system_manager = new SystemManager();
	system_manager->RegisterModels(model_manager);
}

SceneManager::~SceneManager(){
	delete shader_manager;
	delete model_manager;
}

void SceneManager::notifyBeginFrame(){
	system_manager->Update();
	model_manager->Update();
}

void SceneManager::notifyDisplayFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//update camera here
	camera->Update();
	view_matrix = camera->ViewMatrix();
	model_manager->Draw();
	model_manager->Draw(projection_matrix, view_matrix);
}

void SceneManager::notifyEndFrame(){
	
}

void SceneManager::notifyReshape(int width,
	int height,
	int previous_width,
	int previous_height){
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) /
		(float)glutGet(GLUT_WINDOW_HEIGHT);
	//clipping planes
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;
	projection_matrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projection_matrix[1][1] = 1.0f / tan(angle / 2.0f);
	projection_matrix[2][2] = (-near1 - far1) / (near1 - far1);
	projection_matrix[2][3] = 1.0f;
	projection_matrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);	
}

Managers::ModelsManager* SceneManager::GetModelsManager(){
	return model_manager;
}