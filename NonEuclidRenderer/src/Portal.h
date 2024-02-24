#pragma once
#include "Camera.h"
#include "GameObject.h"

using glm::vec2;
using glm::vec3;
using glm::mat4;
using glm::translate;
using glm::inverse;
using glm::rotate;
using glm::radians;

class Portal {
public:
	vec3 position = { 0, 0, 0 };
	vec2 scale = { 1, 1 };
	vec3 rotation = { 0, 0, 0 };
	Portal (vec3 posP, vec2 scaleP, vec3 rotP);
	mat4 GetOtherCameraView(Camera camera, Portal portal_to);
	vec3 GetOtherCameraPos(Camera camera, Portal portal_to);
private:
	mat4 model = glm::mat4(1.0f);
	void UpdateModelMatrix();
};

Portal::Portal(vec3 posP = {0,0,0}, vec2 scaleP = {1,1}, vec3 rotP = {0,0,0}) {
	position = posP;
	scale = scaleP;
	rotation = rotP;
	UpdateModelMatrix();
}

void Portal::UpdateModelMatrix() {
	model = glm::mat4(1.0f);
	model = translate(model, position);
	model = rotate(model, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f)); // X-axis rotation
	model = rotate(model, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f)); // Y-axis rotation
	model = rotate(model, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f)); // Z-axis rotation
	model = glm::scale(model, vec3(scale.x, scale.y, 0.0f));
}

mat4 Portal::GetOtherCameraView(Camera camera, Portal portal_to) {
	// 1. Calculate the transformation from the camera's view to the first portal
	mat4 camera_to_portal_from = inverse(model) * camera.GetViewMatrix();

	// 2. Apply the transformation from the first portal to the second portal
	mat4 portal_from_to_portal_to = portal_to.model * inverse(model);

	// 3. Transform from the second portal to the "fake" camera
	mat4 camera_to_portal_to = portal_to.model * camera_to_portal_from;

	return camera_to_portal_to;
}

vec3 Portal::GetOtherCameraPos(Camera camera, Portal portal_to) {
	return {0,0,0};
}