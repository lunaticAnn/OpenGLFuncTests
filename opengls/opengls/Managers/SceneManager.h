#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "SystemManager.h"
#include "../Core/Init/IListener.h"
namespace Managers
{
	class SceneManager : public Core::IListener{
		public:
			SceneManager();
			~SceneManager();

			virtual void notifyBeginFrame();
			virtual void notifyDisplayFrame();
			virtual void notifyEndFrame();
			virtual void notifyReshape(int width,
				int height,
				int previous_width,
				int previous_height);

			Managers::ModelsManager* GetModelsManager();
		private:
			Rendering::Camera* camera;
			Managers::ShaderManager* shader_manager;
			Managers::ModelsManager* model_manager;
			Managers::SystemManager* system_manager;
			glm::mat4 projection_matrix;
			glm::mat4 view_matrix;
	};
}