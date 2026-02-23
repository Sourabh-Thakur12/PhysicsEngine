#include <iostream>
#include <unistd.h>

const int NUM_RIGID_BODY = 1;
const float M_PI = 3.14f;

struct BoxShape
{
    float width;
    float height;
    float mass;
    float momentOfInertia;
};

struct vec2
{
    float x;
    float y;
};

void CalculateBoxInertia(BoxShape *boxShape)
{
    float m = boxShape->mass;
    float w = boxShape->width;
    float h = boxShape->height;
    boxShape->momentOfInertia = m * (h * h + w * w) / 12;
}

struct RigidBody
{
    vec2 position;
    vec2 linearVelocity;
    float angle;
    float angularVelocity;
    vec2 force;
    float torque;
    BoxShape shape;
};

RigidBody rigidBodies[NUM_RIGID_BODY];

void PrintRigidBodies()
{
    for (int i = 0; i < NUM_RIGID_BODY; i++)
    {
        RigidBody *rigidBody = &rigidBodies[i];
        printf("body[%i] p = (%.2f, %.2f), a = %.2f\n", i, rigidBody->position.x, rigidBody->position.y, rigidBody->angle);
    }
}

void InitializeRigidBodies()
{
    for (int i = 0; i < NUM_RIGID_BODY; i++)
    {
        RigidBody *rigidBody = &rigidBodies[i];
        rigidBody->position = (vec2){static_cast<float>(arc4random_uniform(50)), static_cast<float>(arc4random_uniform(50))};
        rigidBody->angle = static_cast<float>(arc4random_uniform(360)) / 360.f * M_PI * 2;
        rigidBody->linearVelocity = vec2{0, 0};
        rigidBody->angularVelocity = 0;

        BoxShape shape;
        shape.mass = 10;
        shape.width = 1 + arc4random_uniform(2);
        shape.height = 1 + arc4random_uniform(2);
        CalculateBoxInertia(&shape);
        rigidBody->shape = shape;
    }
}

void ComputeForceAndTorque(RigidBody *rigidBody)
{
    vec2 f = (vec2){0, 100};
    rigidBody->force = f;

    vec2 r = (vec2){rigidBody->shape.width / 2, rigidBody->shape.height / 2};
    rigidBody->torque = r.x * f.y - r.y * f.x;
}

void RunRigidBodySimulation()
{
    float totalSimulationTime = 10;
    float currentTime = 0;
    float dt = 1;

    InitializeRigidBodies();
    PrintRigidBodies();

    while (currentTime < totalSimulationTime)
    {

        for (int i = 0; i < NUM_RIGID_BODY; i++)
        {
            RigidBody *rigidBody = &rigidBodies[i];
            ComputeForceAndTorque(rigidBody);
            vec2 linearAccelearation = (vec2){rigidBody->force.x / rigidBody->shape.mass, rigidBody->force.y / rigidBody->shape.mass};
            rigidBody->linearVelocity.x += linearAccelearation.x * dt;
            rigidBody->linearVelocity.y += linearAccelearation.y * dt;

            rigidBody->position.x += rigidBody->linearVelocity.x * dt;
            rigidBody->position.y += rigidBody->linearVelocity.y * dt;

            float angularAcceleration = rigidBody->torque / rigidBody->shape.momentOfInertia;
            rigidBody->angularVelocity += angularAcceleration * dt;
            rigidBody->angle += rigidBody->angularVelocity * dt;
        }

        PrintRigidBodies();
        currentTime += dt;
    }
}

int main()
{
    RunRigidBodySimulation();
    return 0;
}
