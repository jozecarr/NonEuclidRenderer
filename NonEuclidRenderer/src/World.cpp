#include "World.h"
#include "Collision.h"

#include <iostream>
using std::cout;

World::World(vector<Object*> objectsP, float gravityStrengthP) {
	objects = objectsP;
	gravityStrength = gravityStrengthP;
}

void World::AddObject(Object* object) {
	objects.push_back(object);
	object->objID = objCount++;
}

bool WillObjsCollide(Object* obj, Object* otherObj, float deltaTime) {  //checks if two will be colliding in the next frame
	vector<vec3> transedVertices[2]; // 0 = obj, 1 = otherObj
	for (int i = 0; i < 2; i++){
		vector<vec3> verts = (i == 0 ? obj->GetVertices() : otherObj->GetVertices());
		for (const vec3 vertex : verts) {
			transedVertices[i].push_back(vertex+(i==0?obj->objVelocity:otherObj->objVelocity)*deltaTime);
		}
	} return AreObjsColliding(transedVertices[0], transedVertices[1]);
}

void World::HandleCollisions(float deltaTime) {
	for (Object *obj : objects) {
		if (obj->objVelocity != vec3(0, 0, 0) && obj->properties.collidable) {//if an object has some velocity
			for (Object *otherObj : objects) {
				if (otherObj->objID != obj->objID && otherObj->properties.collidable) { // for every other object
					if (!AreObjsColliding(obj->GetVertices(), otherObj->GetVertices())) { // if the object is not going to collide with any other object
						obj->Translate(obj->objVelocity * deltaTime); //apply the movement
						obj->isColliding = false;
					} else { obj->objVelocity = { 0,0,0 }; obj->isColliding = true; }
				}
			}
		}
	}
}

void World::ApplyGravity(float deltaTime) {
	for (Object* obj : objects) {
		if(obj->properties.hasGravity) obj->objVelocity += vec3(0, gravityStrength * deltaTime, 0);
	}
}

void World::Update(float deltaTime) {
	ApplyGravity(deltaTime);
	HandleCollisions(deltaTime);
}

void World::AddAxes() {
	Shader* axisShader = GetBasicShader({ 0,0,0 });
	Object* axisX = new Object(axisShader, { 1000, 0.01, 0.01 }, { 0,0,0 }, { 0,0,0 });
	AddObject(axisX);
	Object* axisY = new Object(axisShader, { 0.01, 1000, 0.01 }, { 0,0,0 }, { 0,0,0 });
	AddObject(axisY);
	Object* axisZ = new Object(axisShader, { 0.01, 0.01, 1000 }, { 0,0,0 }, { 0,0,0 });
	AddObject(axisZ);
}