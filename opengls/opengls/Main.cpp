#include "Core\Init\InitGLUT.h"
#include "Managers\SceneManager.h"
#include "Rendering/Models/Cube.h"

using namespace Core;
using namespace Init;
int main(int argc, char **argv){
	WindowInfo window(std::string("in2gpu OpenGL Beginner Tutorial"), 400, 200, 800, 600, true);
	ContextInfo context(4, 5, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	Init_GLUT::init(window, context, frameBufferInfo);

	Managers::SceneManager* scene = new Managers::SceneManager();
	Init_GLUT::setListener(scene);

	Init_GLUT::run();

	delete scene;
	return 0;
}