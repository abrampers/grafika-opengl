#include "Particle.h"

Jokowi::Particle::Particle(glm::vec3 initial_position, glm::vec3 velocity)
    : initial_position(initial_position), velocity(velocity), position(initial_position) {

}

Jokowi::Particle::~Particle() {

}

void Jokowi::Particle::Update(float dt) {
    position += dt * velocity;
    if (velocity.x == 0.0f && velocity.y != 0.0f && velocity.z == 0.0f && position.y < 0.0f) {
        position = initial_position;
    }

    if (velocity.x == 0.0f && velocity.y == 0.0f && velocity.z != 0.0f && position.z < -3.0f) {
        position = initial_position;
    }
}

glm::vec3 Jokowi::Particle::GetPosition() const {
    return position;
}