#include "GameObject.h"

Object::Object(vec3 objScaleP, vec3 objPositionP, vec3 objRotationP/*, std::string& texPathP*/) {
	objScale = objScaleP;
	objPosition = objPositionP;
	objRotation = objRotationP;
	//texPath = texPathP;

	updateModelMatrix();
}

// Function to update the model matrix based on the current position, scale, and rotation
void Object::updateModelMatrix() {
	model = glm::mat4(1.0f);
	model = translate(model, objPosition);
	model = rotate(model, glm::radians(objRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis rotation
	model = rotate(model, glm::radians(objRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis rotation
	model = rotate(model, glm::radians(objRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis rotation
	model = scale(model, objScale);
}