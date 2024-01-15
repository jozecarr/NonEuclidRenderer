#include "Raycasting.h"

Ray::Ray(vec3 pos, vec3 dir, World* world) {
    position = pos;
    direction = dir;

    // Raycast calculations
    for (Object* object : world->objects) {
        // Convert ray to object's local space
        mat4 inverseModelMatrix = glm::inverse(object->model);
        vec4 localRayOrigin = inverseModelMatrix * vec4(position, 1.0);
        vec4 localRayDirection = inverseModelMatrix * vec4(direction, 0.0);

        // Extract local space vectors
        vec3 localPosition = vec3(localRayOrigin);
        vec3 localDirection = vec3(localRayDirection);

        // Calculate bounds in local space
        vec3 localMinBounds = object->objPosition - object->objScale / 2.0f;
        vec3 localMaxBounds = object->objPosition + object->objScale / 2.0f;

        // Ray-object intersection in local space
        vec3 tMin = (localMinBounds - localPosition) / localDirection;
        vec3 tMax = (localMaxBounds - localPosition) / localDirection;

        vec3 t1 = glm::min(tMin, tMax);
        vec3 t2 = glm::max(tMin, tMax);

        float tEnter = glm::max(glm::max(t1.x, t1.y), t1.z);
        float tExit = glm::min(glm::min(t2.x, t2.y), t2.z);

        if (tExit >= 0 && tEnter <= tExit && (hitInfo.hitDistance < 0 || tEnter < hitInfo.hitDistance)) {
            // Update hit information
            hitInfo.hitDistance = tEnter;
            hitInfo.hitObj = object;

            // Transform hit position back to world space
            hitInfo.hitPosition = vec3(object->model * vec4(localPosition + localDirection * tEnter, 1.0));

            didHit = true;
        }
    }
}
