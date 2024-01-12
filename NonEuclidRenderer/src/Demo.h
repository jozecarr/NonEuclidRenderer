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
        
        vector<Object> newObjs;
        vector<Shader> newShaders;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> randFloat_rot(0.015f, 0.02f);

        randvec_rot = { randFloat_rot(gen), randFloat_rot(gen), randFloat_rot(gen) };
    }

	void run() {
        if (time->EveryNSeconds(0.1) && world->objects.size() <= 100)
        {
            // Random number generators
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> randFloatS(0.4f, 2.0f);
            std::uniform_real_distribution<float> randFloatP(0.0f, 5.0f);
            std::uniform_real_distribution<float> randFloatR(0.0f, 360.0f);
            std::uniform_real_distribution<float> randFloatClr(0.0f, 1.0f);

            vec3 randvecS = { randFloatS(gen), randFloatS(gen), randFloatS(gen) };
            vec3 randvecP = { randFloatS(gen), randFloatS(gen), randFloatS(gen) };
            vec3 randvecR = { randFloatS(gen), randFloatS(gen), randFloatS(gen) };
            vec3 randvecClr = { randFloatClr(gen), randFloatClr(gen), randFloatClr(gen) };

            glm::vec3 randomScale = { randvecS.x * 2, randvecS.y * 2, randvecS.z * 2 };
            glm::vec3 randomPosition = { randvecP.x * 20, randvecP.y * 20, randvecP.z * 20 };
            glm::vec3 randomRotation = { randvecR.x * 360, randvecR.y * 360, randvecR.z * 360 };

            // Allocate memory on the heap
            Shader* newShader = new Shader("res/shaders/Basic.shader");
            newShader->Bind();
            newShader->SetUniform1i("u_Texture", 1);
            newShader->SetUniform4f("u_Color", randvecClr.x, randvecClr.y, randvecClr.z, 1.0);
            newShader->Unbind();

            // Allocate memory on the heap
            Object* newObj = new Object(newShader, randomScale, randomPosition, randomRotation);
            world->objects.push_back(newObj);
        }

        for (const auto obj : world->objects) {
            obj->Rotate({ randvec_rot.x, randvec_rot.y, randvec_rot.z });
        }
	}
};