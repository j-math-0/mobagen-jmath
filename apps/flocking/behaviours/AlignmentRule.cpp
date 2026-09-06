#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) { 
  if (!neighborhood.empty()) {
    glm::vec2 alignment(0.f);

    for (BoidView otherBoid : neighborhood)
      alignment += otherBoid.velocity;

    // Average the alignment
    return alignment /= neighborhood.size();
  }

  return glm::vec2(0.f);
}
