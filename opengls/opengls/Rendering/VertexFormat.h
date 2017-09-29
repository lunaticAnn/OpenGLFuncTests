#ifndef  VertexFormat_H_
#define VertexFormat_H_
#include "glm\glm.hpp"
namespace Rendering{
	struct VertexFormat{
		glm::vec3 position;
		glm::vec4 color;

		VertexFormat(const glm::vec3 &pos, const glm::vec4 & col){
			position = pos;
			color = col;
		}
		VertexFormat(){}
	};
}

#endif
