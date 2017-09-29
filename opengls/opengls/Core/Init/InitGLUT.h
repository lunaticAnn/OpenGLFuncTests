#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "InitGLEW.h"
#include "Ilistener.h"

namespace Core {
	namespace Init {//two namespaces

		class Init_GLUT {

		public:            
			static void init(const Core::WindowInfo& window,
				const Core::ContextInfo& context,
				const Core::FramebufferInfo& framebufferInfo);

		public:
			static void run();//called from outside
			static void close();

			void enterFullscreen();
			void exitFullscreen();
			static void printOpenGLInfo(const Core::WindowInfo& windowInfo,
				const Core::ContextInfo& context);
			static void setListener(Core::IListener*& iListener);
		private:
			static void idleCallback(void);
			static void displayCallback(void);
			static void reshapeCallback(int width, int height);
			static void closeCallback();
			static Core::IListener* listener;
			static Core::WindowInfo windowInformation;
		};
	}
}

