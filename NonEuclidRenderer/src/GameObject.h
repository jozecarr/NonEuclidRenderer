#pragma once
#include "glm.hpp"
#include "matrix_transform.hpp"
#include <string>
#include <vector>
#include "Shader.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::translate;
using glm::scale;
using glm::radians;
using std::string;
using std::vector;

class ObjectProperties {
public:
	bool collidable = false;
	bool hasGravity = false;
	ObjectProperties(bool collidableP = false, bool hasGravityP = false) {
		collidable = collidableP;
		hasGravity = hasGravityP;
	};
};

class Object {
public:
	int objID = 0;
	vec3 objScale = { 1, 1, 1 };
	vec3 objPosition = { 0, 0, 0 };
	vec3 objRotation = { 0, 0, 0 }; // Euler angles for rotation

	vec3 objVelocity = { 0, 0, 0 };
	vec3 objAngVelocity = { 0, 0, 0 };

	mat4 model = glm::mat4(1.0f);
	Shader *shader;
	string texPath;

	ObjectProperties properties = {0,0};

	Object(Shader* shader, vec3 objScaleP = { 1, 1, 1 }, vec3 objPositionP = { 0, 0, 0 }, vec3 objRotationP = { 0, 0, 0 }, ObjectProperties propertiesP = {0,0});

	//std::string& texPath;

	void UpdateModelMatrix();

	void SetPosition(vec3 newPos);
	void SetRotation(vec3 newRot);
	void SetScale(vec3 newScl);

	void Translate(vec3 translation);
	void Rotate(vec3 rotation);
	void Grow(vec3 growth);

	vector<vec3> GetVertices() ;
};