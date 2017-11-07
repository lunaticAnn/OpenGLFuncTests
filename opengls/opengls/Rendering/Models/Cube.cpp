#include "Cube.h"
using namespace Rendering;
using namespace Models;

#define PI 3.14159265

Cube::Cube(const glm::vec3& t, const glm::vec3& s, const glm::vec3& r){
	translation = t;
	scale = s;
	rotation = r;
}

Cube::~Cube(){
}

void Cube::Create(){
	GLuint vao;
	GLuint vbo;

	time(&timer);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	//vertices for the front face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0)));

	//vertices for the right face of the cube
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0)));

	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0)));

	//vertices for the back face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0)));

	//vertices for the left face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0)));

	//vertices for the upper face of the cube
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0)));

	//vertices for the bottom face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::uv)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));
	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Cube::Update(){
	Model::Update();
}

void Cube::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix){
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"),1,
		false, &TransformMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}