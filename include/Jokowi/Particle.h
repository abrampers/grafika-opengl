#ifndef JOKOWI_PARTICLE_H
#define JOKOWI_PARTICLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Jokowi {
class Particle
{
private:
    /* data */
    glm::vec3 initial_position, position, velocity;
public:
    Particle(glm::vec3 initial_position, glm::vec3 velocity);
    ~Particle();
    
    void Update(float dt);

    glm::vec3 GetPosition() const;
};
}

#endif
