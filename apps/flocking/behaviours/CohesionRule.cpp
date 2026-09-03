#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 cohesionForce(0.f);

  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.

  // begin solution

  for (BoidView otherBoid : neighborhood) {
    glm::vec2 difference = otherBoid.position - boid.position;
    glm::vec2 direction = glm::normalize(difference);
    float distance = glm::length(difference);

    cohesionForce += direction * distance;
  }

  // end solution

  return cohesionForce;
}
