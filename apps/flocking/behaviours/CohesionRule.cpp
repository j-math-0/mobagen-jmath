#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  if (!neighborhood.empty()) {
    glm::vec2 centerOfMass(0.f);

    for (BoidView otherBoid : neighborhood) centerOfMass += otherBoid.position;

    // Average the center of mass
    centerOfMass /= neighborhood.size();

    glm::vec2 difference = centerOfMass - boid.position;

    return glm::normalize(difference) * glm::length(difference);
  }

  return glm::vec2(0.0f, 0.0f);
}
