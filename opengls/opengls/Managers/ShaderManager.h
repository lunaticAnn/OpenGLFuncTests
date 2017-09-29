#pragma once
#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

namespace Managers
{
	class ShaderManager{
		private:
			std::string ReadShader(const std::string& file_name);
			GLuint CreateShader(GLenum shader_type,
				const std::string& source,
				const std::string& shader_name);
			static std::map<std::string, GLuint> programs;

		public:
			ShaderManager(void);
			~ShaderManager(void);
			static const GLuint GetShader(const std::string& shader_name);
			GLuint CreateProgram(const std::string& shader_name,
								const std::string& vertex_shader_file,
								const std::string& fragment_shader_file);
	};
}