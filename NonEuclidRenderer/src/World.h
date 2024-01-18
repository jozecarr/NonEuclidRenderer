#pragma once

#include "GameObject.h"
#include <vector>

using std::vector;

class World {
public:
	vector<Object*> objects = {};
	World(vector<Object*> objectsP = {});
	void AddObject(Object* object);
	void Update();
};
