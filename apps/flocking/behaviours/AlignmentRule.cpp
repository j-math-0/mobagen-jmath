#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 averageVelocity(0.f);
  // glm::vec2 can be divided by a float, which will divide each component of the vector by that float.

  // begin solution
  if (neighborhood.size() > 0) {
    glm::vec2 alignment(0.f);

    for (BoidView otherBoid : neighborhood) {
      alignment += otherBoid.velocity;
    }

    averageVelocity = alignment / static_cast<float>(neighborhood.size());
  }

  return averageVelocity;
  // end solution
}
