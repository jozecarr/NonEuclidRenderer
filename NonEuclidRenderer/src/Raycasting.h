#pragma once

#include "World.h"
#include "matrix_transform.hpp"

#include <iostream>

using glm::rotate;
using glm::conjugate;
using glm::vec4;

class HitInfo {
public:
	float hitDistance = -1;
	vec3 hitPosition = { 0, 0, 0 };
    Object* hitObj = nullptr;
};

class Ray {
public:
    vec3 position = { 0, 0, 0 };
    vec3 direction = { 0, 0, 0 };
    HitInfo hitInfo;
    bool didHit = false;

    Ray(vec3 pos, vec3 dir, World* world);
};