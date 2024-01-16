#include "Raycasting.h"

Ray::Ray(vec3 pos, vec3 dir, World* world) {
    position = pos;
    direction = glm::normalize(dir);

    // Initialize hitInfo distance to infinity
    hitInfo.hitDistance = std::numeric_limits<float>::infinity();
    didHit = false;

    // Raycast calculations
    for (Object* object : world->objects) {
        // Convert ray to object's local space
        mat4 inverseModelMatrix = glm::inverse(object->model);
        vec4 localRayOrigin = inverseModelMatrix * vec4(position, 1.0);
        vec4 localRayDirection = inverseModelMatrix * vec4(direction, 0.0);

        // Debugging output
        std::cout << "localRayOrigin: " << localRayOrigin.x << ", " << localRayOrigin.y << ", " << localRayOrigin.z << std::endl;
        std::cout << "localRayDirection: " << localRayDirection.x << ", " << localRayDirection.y << ", " << localRayDirection.z << std::endl;

        // Extract local space vectors
        vec3 localPosition = vec3(localRayOrigin) / localRayOrigin.w;
        vec3 localDirection = glm::normalize(vec3(localRayDirection));

        // Debugging output
        std::cout << "localPosition: " << localPosition.x << ", " << localPosition.y << ", " << localPosition.z << std::endl;
        std::cout << "localDirection: " << localDirection.x << ", " << localDirection.y << ", " << localDirection.z << std::endl;


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

        // Debugging output
        std::cout << "tEnter: " << tEnter << ", tExit: " << tExit << std::endl;

        if (tExit >= 0 && tEnter <= tExit && tEnter < hitInfo.hitDistance) {
            // Update hit information
            hitInfo.hitDistance = tEnter;
            hitInfo.hitObj = object;

            // Calculate hit position in local space
            vec3 localHitPosition = localPosition + tEnter * localDirection;

            // Debugging output
            std::cout << "localHitPosition: " << localHitPosition.x << ", " << localHitPosition.y << ", " << localHitPosition.z << std::endl;

            // Transform hit position back to world space
            hitInfo.hitPosition = vec3(object->model * vec4(localHitPosition, 1.0));

            // Debugging output
            std::cout << "worldHitPosition: " << hitInfo.hitPosition.x << ", " << hitInfo.hitPosition.y << ", " << hitInfo.hitPosition.z << std::endl;

            didHit = true;
        }
    }

    // Final debugging output
    std::cout << "Final didHit? " << didHit << ", Final hitDistance: " << hitInfo.hitDistance << std::endl;
}