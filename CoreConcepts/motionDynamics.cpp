#include <iostream>
#include <unistd.h>
using namespace std;

const int NUM_PARTICLES = 1;
struct vec2{
    float x;
    float y;
};

struct part2{
    vec2 posttion;
    vec2 velocity;
    float mass;
};

part2 particles[NUM_PARTICLES];

void PrintParticles(){
    for(int i = 0; i< NUM_PARTICLES; i++){
        part2 *particle = &particles[i];
        printf("particle[%i] (%.2f, %.2f)\n", i, particle->posttion.x, particle->posttion.y);
    }
}


void IntializePartices(){
    for(int i = 0; i< NUM_PARTICLES; i++){
        particles[i].posttion = (vec2){static_cast<float>(arc4random_uniform(50)), static_cast<float>(arc4random_uniform(50))}; //arc4random_uniform returns uniform rand values from 0 49
        particles[i].velocity = (vec2){0.0f, 0.0f};
        particles[i].mass = 1.0f;
    }
}


vec2 ComputeForce(part2 *particle){
    return (vec2){0, particles->mass * -9.81f};
}

void RunSimulation(){
    float totalSimulationTime = 10;
    float currentTime = 0;
    float dt = 1; //increment 1 sec each step


    IntializePartices();
    PrintParticles();

    while(currentTime < totalSimulationTime){
        sleep(dt); //for simplification in real apps use api to update time


        for(int i = 0; i< NUM_PARTICLES; i++){
            part2 *particle = &particles[i];
            vec2 force = ComputeForce(particle);
            vec2 acceleration = (vec2){force.x / particle->mass, force.y/ particle->mass};
            particle ->velocity.x += acceleration.x * dt;
            particle->velocity.y += acceleration.y * dt;
            particle->posttion.x += particle->velocity.x * dt;
            particle->posttion.y += particle->velocity.y * dt;

        }

        PrintParticles();
        currentTime += dt;

    }
}

int main(){
    RunSimulation();
    return 0;
}
