#pragma once
#include "../../Dependencies/glew/glew.h"
#include "../../Dependencies/freeglut/freeglut.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Rendering{
	class Camera {
		public:
			Camera (const glm::vec3& t = glm::vec3(0.0), const glm::vec3& r = glm::vec3(0.0));
			~Camera ();
			glm::mat4 ViewMatrix();
			void Update();
			glm::vec3 translation;
			glm::vec3 look_at_point;
		private:
			
		};


}