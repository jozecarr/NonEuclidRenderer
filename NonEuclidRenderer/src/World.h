#pragma once

#include "GameObject.h"

#include <vector>

using std::vector;

class World {
public:
	vector<Object*> objects = {};	
	int objCount = 0;
	float gravityStrength = -9.81f;
	World(vector<Object*> objectsP = {}, float gravityStrengthP = -9.8f);
	void AddObject(Object* object);
	void Update(float deltaTime);
	void AddAxes();
	void HandleCollisions(float deltaTime);
	void ApplyGravity(float deltaTime);
};
