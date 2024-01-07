#include "GameObject.h"

Object::Object(vec3 objScaleP, vec3 objPositionP, vec3 objRotationP/*, std::string& texPathP*/) {
	objScale = objScaleP;
	objPosition = objPositionP;
	objRotation = objRotationP;
	//texPath = texPathP;

	UpdateModelMatrix();
}

// Function to update the model matrix based on the current position, scale, and rotation
void Object::UpdateModelMatrix() {
	model = glm::mat4(1.0f);
	model = translate(model, objPosition);
	model = rotate(model, radians(objRotation.x), vec3(1.0f, 0.0f, 0.0f)); // X-axis rotation
	model = rotate(model, radians(objRotation.y), vec3(0.0f, 1.0f, 0.0f)); // Y-axis rotation
	model = rotate(model, radians(objRotation.z), vec3(0.0f, 0.0f, 1.0f)); // Z-axis rotation
	model = scale(model, objScale);
}

void Object::SetPosition(vec3 newPos) {
	objPosition = newPos;
	UpdateModelMatrix();
}

void Object::SetRotation(vec3 newRot) {
	objRotation = newRot;
	UpdateModelMatrix();
}

void Object::SetScale(vec3 newScl) {
	objScale = newScl;
	UpdateModelMatrix();
}

void Object::Translate(vec3 translation){
	SetPosition(objPosition + translation);
}

void Object::Rotate(vec3 rotation){
	SetRotation(objRotation + rotation);
}

void Object::Grow(vec3 growth){
	SetScale(objScale + growth);
}