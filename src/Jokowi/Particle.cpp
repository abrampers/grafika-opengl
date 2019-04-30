#include "Particle.h"

Jokowi::Particle::Particle(glm::vec3 initial_position, glm::vec3 velocity)
    : initial_position(initial_position), velocity(velocity), position(initial_position) {

}

Jokowi::Particle::~Particle() {

}

void Jokowi::Particle::Update(float dt) {
    position += dt * velocity;
    if (position.y < 0.0f) {
        position = initial_position;
    }
}

glm::vec3 Jokowi::Particle::GetPosition() const {
    return position;
}