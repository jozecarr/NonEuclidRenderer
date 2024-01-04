#pragma once

#include "GameObject.h"
#include <vector>
#include <memory>
#include "Camera.h"
#include "Renderer.h"

using std::vector;
using std::unique_ptr;

class World {
public:
	vector<Object*> objects = {};
	World(vector<Object*> objectsP = {});
	void AddObject(Object* object);
};
//
//void InitWorld(Shader& shader) {
//
//}

void DrawWorld(World& world, Camera& camera, float scrWidth, float scrHeight, Shader& shader);