#include "Camera.h"

using namespace Rendering;
Camera::Camera(const glm::vec3& t, const glm::vec3& r){
	translation = t;
	look_at_point = r;
}

Camera::~Camera(){

}

void Camera::Update() {

}

glm::mat4 Camera::ViewMatrix(){
//===================to_do: make up vector customizable=============
	glm::vec3 camera_front =  translation - look_at_point;
	camera_front = glm::normalize(camera_front);
	return glm::lookAt(
		translation,
		translation + camera_front,
		glm::vec3(0.0, 1.0, 0.0)
	);
}