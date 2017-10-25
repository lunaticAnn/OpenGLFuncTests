#pragma once
#include "Model.h"
#include <cstring>
#include <string>
#include <stdio.h>

namespace Rendering {
	namespace Models {
		//a model that customizable by passing in vector<VertexFormat>
		class CustomModel : public Model {
			public:
				CustomModel(const std::string& obj_filename, 
							const glm::vec3& t = glm::vec3(0.0), 
							const glm::vec3& s = glm::vec3(1.0), 
							const glm::vec3& r = glm::vec3(0.0));
				CustomModel(std::vector<VertexFormat>& v, 
							const glm::vec3& t = glm::vec3(0.0),
							const glm::vec3& s = glm::vec3(1.0),
							const glm::vec3& r = glm::vec3(0.0));
				~CustomModel();
							
				void Create();
				virtual void Update() override final;
				virtual void Draw(const glm::mat4& projection_matrix,
					const glm::mat4& view_matrix) override final;

			private:
				std::vector<VertexFormat> vs;	
				bool LoadFromObj(const std::string& obj_filename);
		};
	}
}
