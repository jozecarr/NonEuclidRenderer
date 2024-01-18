#pragma once
#include "glm.hpp"
#include "Shader.h"
#include "matrix_transform.hpp"
#include <string>
#include <vector>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::translate;
using glm::scale;
using glm::radians;
using std::string;
using std::vector;


class Object {
public:
	vec3 objScale = { 1, 1, 1 };
	vec3 objPosition = { 0, 0, 0 };
	vec3 objRotation = { 0, 0, 0 }; // Euler angles for rotation
	mat4 model = glm::mat4(1.0f);
	Shader *shader;
	string texPath;

	Object(Shader *shader, vec3 objScaleP = { 1, 1, 1 }, vec3 objPositionP = { 0, 0, 0 }, vec3 objRotationP = { 0, 0, 0 });

	//std::string& texPath;

	void UpdateModelMatrix();

	void SetPosition(vec3 newPos);
	void SetRotation(vec3 newRot);
	void SetScale(vec3 newScl);

	void Translate(vec3 translation);
	void Rotate(vec3 rotation);
	void Grow(vec3 growth);

	vector<vec3> GetVertices();
};