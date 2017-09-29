#include "Core\Init\InitGLUT.h"
using namespace Core;
#include "Managers\SceneManager.h"
int main(int argc, char **argv){
	WindowInfo window(std::string("window1"),
		400, 200,
		800, 600, 
		true);

	ContextInfo context(4, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init::Init_GLUT::init(window, context, frameBufferInfo);
	IListener* scene = new Managers::SceneManager();
	Init::Init_GLUT::setListener(scene);
	Init::Init_GLUT::run();
	
	return 0;
}