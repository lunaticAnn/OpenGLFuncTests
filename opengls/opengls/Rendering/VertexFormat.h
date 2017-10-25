#ifndef  VertexFormat_H_
#define VertexFormat_H_
#include "glm\glm.hpp"
namespace Rendering{
	struct VertexFormat{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;

		VertexFormat(const glm::vec3 & pos, 
					const glm::vec4 & col = glm::vec4(1.0)){
			position = pos;
			color = col;			
		}
		VertexFormat(){}
	};
}

#endif
