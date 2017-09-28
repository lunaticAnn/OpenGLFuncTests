#include "ShaderManager.h" 
#include<iostream>
#include<fstream>
#include<vector>

using namespace Managers;
std::map<std::string, GLuint> ShaderManager::programs;

ShaderManager::ShaderManager(void) {}
ShaderManager::~ShaderManager(void) {
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); ++i){
		GLuint pr = i->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

std::string ShaderManager::ReadShader(const std::string& file_name){
	std::string shaderCode;
	std::ifstream file(file_name, std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << file_name.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderManager::CreateShader(GLenum shader_type,
	const std::string& source,
	const std::string& shader_name){

	int compile_result = 0;
	GLuint shader = glCreateShader(shader_type);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE){
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shader_name.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

GLuint ShaderManager::CreateProgram(const std::string& shader_name,
	const std::string& vertex_shader_filename,
	const std::string& fragment_shader_filename){

	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertex_shader_filename);
	std::string fragment_shader_code = ReadShader(fragment_shader_filename);

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Manager : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	//change this to map shader to names
	if(programs.find(shader_name)!=programs.end()){
		std::cout<<"Shader Manager: Name has been used."<<std::endl;
		return 0;
	}
	programs[shader_name] = program;
	//return program;
}

const GLuint ShaderManager::GetShader(const std::string& shader_name){
	return programs.at(shader_name);
};