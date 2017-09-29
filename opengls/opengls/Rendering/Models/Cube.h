#pragma once
#include "Model.h"
#include<time.h>
#include<stdarg.h>
namespace Rendering{
	namespace Models{
		class Cube : public Model{
		public:
			Cube();
			~Cube();

			void Create();
			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix)
				override final;
			virtual void Update() override final;

		private:
			time_t timer;
		};
	}
}