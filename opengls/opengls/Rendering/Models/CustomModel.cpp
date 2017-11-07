#define _CRT_SECURE_NO_WARNINGS
#include "CustomModel.h"
using namespace Rendering;
using namespace Models;

//Write vertices data directly
CustomModel::CustomModel(std::vector<VertexFormat>& v,
						const glm::vec3& t, 
						const glm::vec3& s, 
						const glm::vec3& r){
	translation = t;
	scale = s;
	rotation = r;
	vs = v;
}

//Read vertives data from file
CustomModel::CustomModel(const std::string& obj_filename, 
						const glm::vec3& t, 
						const glm::vec3& s, 
						const glm::vec3& r ){
	translation = t;
	scale = s;
	rotation = r;
	if (!LoadFromObj(obj_filename)){
		std::vector<VertexFormat> vertices;
		vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0),
			glm::vec4(1, 0, 0, 1)));
		vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
			glm::vec4(1, 0, 0, 1)));
		vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0),
			glm::vec4(1, 0, 0, 1)));
		vs = vertices;
	}	
};

CustomModel::~CustomModel(){

}


void CustomModel::Create(){
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vs.size(), &vs[0], GL_STATIC_DRAW);
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

void CustomModel::Update(){
	Model::Update();
}

void CustomModel::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix) {
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(texture, "texture1"), 0);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1,
		false, &TransformMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vs.size());
}

bool CustomModel::LoadFromObj(const std::string& obj_filename){
	//parse data and save to vs
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	//to support uv and normals in future.
	FILE* file = fopen(obj_filename.c_str(),"r");
	if (file == NULL) {
		printf("File open failed.\n");
		return false;
	}

	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			//uv.y = -uv.y;
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			//read vertex index and !TRIANGULATE
			unsigned int arr[100];
			unsigned int arr_uv[100];
			unsigned int arr_norm[100];
			char temp;
			int i = 0;
			do {
				fscanf(file, "%d%c", &arr[i], &temp);
				if(temp == '/') {
					//get v
					int res = fscanf(file, "%d%c", &arr_uv[i], &temp);
					if (res == 1) {
						arr_uv[i] = arr[i];
					}
					if (temp == '/') {
						fscanf(file, "%d%c", &arr_norm[i], &temp);
					}
				}
				else{
					arr_uv[i] = arr[i];
					arr_norm[i] = arr[i];
				}
				i++;
			} while (temp != '\n');

			//triangulate
			for (int n = 2; n < i; n++) {
				vertexIndices.push_back(arr[0]);
				vertexIndices.push_back(arr[n - 1]);
				vertexIndices.push_back(arr[n]);
				uvIndices.push_back(arr_uv[0]);
				uvIndices.push_back(arr_uv[n - 1]);
				uvIndices.push_back(arr_uv[n]);
				normIndices.push_back(arr_norm[0]);
				normIndices.push_back(arr_norm[n - 1]);
				normIndices.push_back(arr_norm[n]);
			}
		}
		else {
			char useless[1000];
			fgets(useless, 1000, file);
		}
	}

		//indexing vertices to vertices array
	std::vector<VertexFormat> vert;
	if (vertexIndices.size() % 3 != 0) {
		printf("Triangulate error.\n");
		return false;
	}

	for (unsigned int i = 0; i < vertexIndices.size()/3; i++){
		glm::vec3 v1 = temp_vertices[vertexIndices[i * 3] - 1];		
		glm::vec3 v2 = temp_vertices[vertexIndices[i * 3 + 1] - 1];		
		glm::vec3 v3 = temp_vertices[vertexIndices[i * 3 + 2] - 1];		
		glm::vec3 norm = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		
		VertexFormat vf1(v1, glm::vec2(0.0), norm);
		VertexFormat vf2(v2, glm::vec2(0.0), norm);
		VertexFormat vf3(v3, glm::vec2(0.0), norm);
		if (temp_uvs.size() > 0) {
			vf1.uv = temp_uvs[uvIndices[i * 3] - 1];
			vf2.uv = temp_uvs[uvIndices[i * 3 + 1] - 1];
			vf3.uv = temp_uvs[uvIndices[i * 3 + 2] - 1];
		}

		if (temp_normals.size() > 0) {
			vf1.normal = temp_normals[normIndices[i * 3] - 1];
			vf2.normal = temp_normals[normIndices[i * 3 + 1] - 1];
			vf3.normal = temp_normals[normIndices[i * 3 + 2] - 1];		
		}
				
		vert.push_back(vf1);
		vert.push_back(vf2);
		vert.push_back(vf3);
		
	}
	vs = vert;
	return true;
}
