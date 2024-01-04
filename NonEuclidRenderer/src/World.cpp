#include "World.h"

World::World(vector<Object*> objectsP) {
	objects = objectsP;
}

void World::AddObject(Object* object) {
	objects.push_back(object);
}

void DrawWorld(World& world, Camera& camera, float scrWidth, float scrHeight, Shader& shader) {
	shader.Bind();

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
		(float)scrWidth / (float)scrHeight, 0.1f, 100.0f);

	shader.SetUniformMat4("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	shader.SetUniformMat4("view", view);

	for (const auto& obj : world.objects)
	{
		shader.SetUniformMat4("model", obj->model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}