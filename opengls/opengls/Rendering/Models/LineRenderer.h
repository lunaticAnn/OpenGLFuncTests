#pragma once
#include "Model.h"
namespace Rendering{
	namespace Models{
		class LineRenderer : public Models::Model{
			public:
				LineRenderer(const glm::vec3& st, 
                             const glm::vec3& e,
                             const float& w,
                             const glm::vec4& s_c = glm::vec4(1.0),
                             const glm::vec4& e_c = glm::vec4(1.0),
                            //where this render face to
                             const glm::vec3& f = glm::vec3(0.0,1.0,0.0),                            
                             const glm::vec3& t = glm::vec3(0.0), 
                             const glm::vec3& sc = glm::vec3(1.0), 
                             const glm::vec3& r = glm::vec3(0.0));
				~LineRenderer();
				void Create();
				virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix);
				virtual void Update() override final;
            private:
                glm::vec3 start;
                glm::vec3 end;
                glm::vec4 start_color;
                glm::vec4 end_color;
                float width;
                glm::vec3 front;
				
		};
	}
}

