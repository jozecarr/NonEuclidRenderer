#include "World.h"
#include "Collision.h"

#include <iostream>

World::World(vector<Object*> objectsP) {
	objects = objectsP;
}

void World::AddObject(Object* object) {
	objects.push_back(object);
	object->objID = objCount++;
}

void World::Update(float deltaTime) {
	for (auto obj : objects) {
		if (obj->objVelocity != vec3(0,0,0)) //if an object has some velocity
		{
			obj->Translate(obj->objVelocity * deltaTime); //apply the velocity
			for (auto otherObj : objects)
			{
				if (otherObj->objID != obj->objID) // for every other object
				{
					if (AreObjsColliding(*obj, *otherObj) && obj->collidable && otherObj->collidable) // if the object is colliding with any other object
					{
						obj->Translate(-obj->objVelocity * deltaTime); //undo the movement
						obj->objVelocity = { 0,0,0 }; //reset the objs velocity
					}
				}
			}
		}
	}
}