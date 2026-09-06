#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  if (!neighborhood.empty()) {
    glm::vec2 centerOfMass(0.f);

    for (BoidView otherBoid : neighborhood) 
        centerOfMass += otherBoid.position;

    // Average the center of mass
    centerOfMass /= neighborhood.size();

    glm::vec2 difference = centerOfMass - boid.position;
    float distance = glm::length(difference);

    // Epsilon check. Ensure the magnitude of the difference isn't a really small number
    if (distance > 0.0001f) 
        return glm::normalize(difference) * distance;
  }

  return glm::vec2(0.f);
}
