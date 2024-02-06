#pragma once

#include <glm.hpp>
#include <gtx/norm.hpp>
#include <vector>

#include "GameObject.h"

using std::vector;
using glm::vec3;
using std::numeric_limits;
using glm::min;
using glm::max;

bool AreObjsColliding(const vector<vec3> cuboid1, const vector<vec3> cuboid2) {

    // Function to calculate the separating axis
    auto getSepAxis = [](const vec3& axis, const vector<vec3>& cuboid1, const vector<vec3>& cuboid2) {
        float min1 = numeric_limits<float>::max();
        float max1 = numeric_limits<float>::lowest();
        float min2 = numeric_limits<float>::max();
        float max2 = numeric_limits<float>::lowest();

        for (size_t i = 0; i < cuboid1.size(); ++i) {
            float projection1 = dot(cuboid1[i], axis);
            min1 = min(min1, projection1);
            max1 = max(max1, projection1);

            float projection2 = dot(cuboid2[i], axis);
            min2 = min(min2, projection2);
            max2 = max(max2, projection2);
        }

        return !(max1 >= min2 && max2 >= min1);
    };

    // Separating axes
    vec3 axes[] = {
        normalize(cuboid1[1] - cuboid1[0]),
        normalize(cuboid1[3] - cuboid1[0]),
        normalize(cuboid1[4] - cuboid1[0]),
        normalize(cuboid2[1] - cuboid2[0]),
        normalize(cuboid2[3] - cuboid2[0]),
        normalize(cuboid2[4] - cuboid2[0]),
        cross(normalize(cuboid1[1] - cuboid1[0]), normalize(cuboid2[1] - cuboid2[0])),
        cross(normalize(cuboid1[1] - cuboid1[0]), normalize(cuboid2[3] - cuboid2[0])),
        cross(normalize(cuboid1[1] - cuboid1[0]), normalize(cuboid2[4] - cuboid2[0])),
    };

    // Check for overlap along each separating axis
    for (const auto& axis : axes) {
        if (getSepAxis(axis, cuboid1, cuboid2)) {
            return false;  // Cuboids are not intersecting along this axis
        }
    }

    return true;  // No separating axis found, cuboids are intersecting
}