#include "Core/Init/InitGLUT.h"
#include "Managers/SceneManager.h"
#include "Managers/ShaderManager.h"
#include "Rendering/Models/CustomModel.h"
#include "Rendering/Textures/texture.hpp"

using namespace Core;
using namespace Init;
int main(int argc, char **argv){
	WindowInfo window(std::string("my window"), 400, 200, 1200, 900, true);
	ContextInfo context(4, 5, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	Init_GLUT::init(window, context, frameBufferInfo);

	Managers::SceneManager* scene = new Managers::SceneManager();
	Init_GLUT::setListener(scene);

	Models::CustomModel* lamp = new Models::CustomModel("Assets/Model/lamp.obj", 
														glm::vec3(-9.0, -0.5, 0.0), 
														glm::vec3(1.5));
	lamp->SetProgram(Managers::ShaderManager::GetShader("colorShader"));
	lamp->SetTexture(Rendering::loadBMP_custom("Assets/Texture/tiles.bmp"));
	lamp->Create();
	scene->AddModel(lamp, "lamp");
	GLuint texture2 = Rendering::loadBMP_custom("Assets/Texture/LaminatedOak.bmp");
	Models::CustomModel* teapot = new Models::CustomModel("Assets/Model/teapot.obj", 
														glm::vec3(0.0, -0.5, -0.0), 
														glm::vec3(0.05),
														glm::vec3(135.0));
	teapot->SetProgram(Managers::ShaderManager::GetShader("colorShader"));
	teapot->SetTexture(texture2);
	teapot->Create();
	scene->AddModel(teapot, "teapot");
	Models::CustomModel* tree = new Models::CustomModel("Assets/Model/DeadTree.obj", 
														glm::vec3(9.0, -4.0, 0.0), 
														glm::vec3(1.5));
	tree->SetProgram(Managers::ShaderManager::GetShader("colorShader"));
	tree->SetTexture(texture2);
	tree->Create();
	scene->AddModel(tree, "tree");


	Init_GLUT::run();

	delete scene;
	return 0;
}