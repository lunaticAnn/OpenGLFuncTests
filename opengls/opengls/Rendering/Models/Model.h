#pragma once
#include <vector>
#include "../IGameObject.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"


namespace Rendering
{
	namespace Models 
	{
		class Model :public IGameObject
		{
		public:
			Model();
			virtual ~Model();
			// methods from interface
			virtual void Draw() override;
			virtual void Create() override;
			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix) override;
			void Update();
			virtual void SetProgram(GLuint shaderName) override;
			virtual void Destroy() override;

			virtual GLuint GetVao() const override;
			virtual const std::vector<GLuint>& GetVbos() const override;

			std::string model_name = "";

		protected:
			GLuint vao;
			GLuint program;			
			std::vector<GLuint> vbos;
		};
	}
}