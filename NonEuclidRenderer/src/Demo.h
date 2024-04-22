#pragma once

#include <random>

#include "GameObject.h"
#include "World.h"
#include "Time.h"

class Demo {
public:
    Time *time;
    World *world;
    vec3 randvec_rot;

    Demo(Time *timeP, World *worldP) {
        time = timeP;
        world = worldP;

        while (world->objCount < 5000) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> randFloatS(0.4f, 2.0f);
            std::uniform_real_distribution<float> randFloatP(-10.0f, 10.0f);
            std::uniform_real_distribution<float> randFloatR(0.0f, 360.0f);
            std::uniform_real_distribution<float> randFloatClr(0.0f, 1.0f);

            vec3 randvecS = { randFloatS(gen), randFloatS(gen), randFloatS(gen) };
            vec3 randvecP = { randFloatS(gen), randFloatS(gen), randFloatS(gen) };
            vec3 randvecR = { randFloatS(gen), randFloatS(gen), randFloatS(gen) };
            vec3 randvecClr = { randFloatClr(gen), randFloatClr(gen), randFloatClr(gen) };

            glm::vec3 randomScale = { randvecS.x * 2, randvecS.y * 2, randvecS.z * 2 };
            glm::vec3 randomPosition = { randvecP.x * 20, randvecP.y * 20, randvecP.z * 20 };
            glm::vec3 randomRotation = { randvecR.x * 360, randvecR.y * 360, randvecR.z * 360 };

            Shader* newShader = GetBasicShader({ randvecClr.x, randvecClr.y, randvecClr.z });

            Object* newObj = new Object(newShader, randomScale, randomPosition, randomRotation);
            world->AddObject(newObj);
        }
    }
};