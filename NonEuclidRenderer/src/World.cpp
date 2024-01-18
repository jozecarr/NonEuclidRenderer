#include "World.h"

World::World(vector<Object*> objectsP) {
	objects = objectsP;
}

void World::AddObject(Object* object) {
	objects.push_back(object);
}

void World::Update() {

}