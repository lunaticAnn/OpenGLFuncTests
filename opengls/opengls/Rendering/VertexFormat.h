#ifndef  VertexFormat_H_
#define VertexFormat_H_
#include "glm\glm.hpp"
namespace Rendering{
	struct VertexFormat{
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		
		VertexFormat(const glm::vec3 & pos,
					const glm::vec2 & uvs = glm::vec2(0.0),
					const glm::vec3 & norm = glm::vec3(1.0)){
			position = pos;
			uv = uvs;
			normal = norm;			
		}
		VertexFormat(){}
	};
}

#endif
