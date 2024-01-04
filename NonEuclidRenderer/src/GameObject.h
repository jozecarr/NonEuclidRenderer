#pragma once
#include "glm.hpp"
#include "matrix_transform.hpp"
#include <string>

using glm::vec3;
using glm::mat4;
using glm::translate;
using glm::scale;

//std::string defaultTexPath = "res/textures/smile.png";

class Object {
public:
	vec3 objScale = { 1, 1, 1 };
	vec3 objPosition = { 0, 0, 0 };
	vec3 objRotation = { 0, 0, 0 }; // Euler angles for rotation
	//std::string& texPath;

	mat4 model = glm::mat4(1.0f);
	Object(vec3 objScaleP = { 1, 1, 1 }, vec3 objPositionP = { 0, 0, 0 }, vec3 objRotationP = { 0, 0, 0 }/*, std::string& texPathP = defaultTexPath*/);
	void updateModelMatrix();
};