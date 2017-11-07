#pragma once
#include <vector>
#include <iostream>
#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include "VertexFormat.h"

namespace Rendering
{
	class IGameObject{
		public:
			virtual ~IGameObject() = 0;
			virtual void Draw() = 0;
			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix) = 0;
			virtual void Update() = 0;
			virtual void Create() = 0;
			virtual void SetProgram(GLuint shaderName) = 0;
			virtual void SetTexture(GLuint textureName) = 0;
			virtual void Destroy() = 0;
			
			virtual GLuint GetVao() const = 0;
			virtual const std::vector<GLuint>& GetVbos() const = 0;
			glm::vec3 translation;
			glm::vec3 scale;
			glm::vec3 rotation;
		protected:
			//when doing draw call, multiply these matrix
			//TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
			glm::mat4 TranslationMatrix;
			glm::mat4 RotationMatrix;
			glm::mat4 ScaleMatrix;
			glm::mat4 TransformMatrix;
			
	};
	inline IGameObject::~IGameObject(){}	
}