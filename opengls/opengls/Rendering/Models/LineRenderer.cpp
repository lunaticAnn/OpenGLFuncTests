#include "LineRenderer.h"
using namespace Rendering;
using namespace Models;

LineRenderer::LineRenderer(const glm::vec3& st, 
                             const glm::vec3& e,
                             const float& w,
                             const glm::vec4& s_c,
                             const glm::vec4& e_c, 
                            //where this render face to
                             const glm::vec3& f,                            
                             const glm::vec3& t, 
                             const glm::vec3& sc, 
                             const glm::vec3& r){
    start = st;
    end = e;
    width = w;
    start_color = s_c;
    end_color = e_c;
    front = f;
    translation = t;
    scale = sc;
    rotation = r;

}

LineRenderer::~LineRenderer(){

}

void LineRenderer::Create(){
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	//vertices for the front face of the LineRenderer
    
    glm::vec3 line_dir = glm::normalize(end - start);
    line_dir = glm::vec3(line_dir.x, 0, line_dir.z);
    glm::vec3 w_dir = 0.5f * width * glm::cross(line_dir, front);
    glm::vec3 p1 = start + w_dir;
    glm::vec3 p2 = start - w_dir;
    glm::vec3 p3 = end - w_dir;
    glm::vec3 p4 = end + w_dir; 
    
    
    vertices.push_back(VertexFormat(p1,start_color));
    vertices.push_back(VertexFormat(p2,start_color));
    vertices.push_back(VertexFormat(p3,end_color));

    vertices.push_back(VertexFormat(p1,start_color));
    vertices.push_back(VertexFormat(p3,end_color));
    vertices.push_back(VertexFormat(p4,end_color));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

}

void LineRenderer::Update(){
	Model::Update();
}

void LineRenderer::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix){

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"),1,
		false, &TransformMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
