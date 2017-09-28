#define _CRT_SECURE_NO_WARNINGS
#include "Core\Init\InitGLUT.h"
using namespace Core;
using namespace Init;
int main(int argc, char **argv){
	WindowInfo window(std::string("window1"),
		400, 200,//position
		800, 600, //size
		true);//reshape

	ContextInfo context(4, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init_GLUT::init(window, context, frameBufferInfo);
	
	Init_GLUT::run();
	
	return 0;
}