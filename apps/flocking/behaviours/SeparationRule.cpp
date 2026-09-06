#include "SeparationRule.h"
#include "imgui.h"
#include <glm/glm.hpp>

glm::vec2 SeparationRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 separatingForce(0.f);

  for (BoidView otherBoid : neighborhood) {
    glm::vec2 difference = boid.position - otherBoid.position;
    glm::vec2 direction = glm::normalize(difference);
    float distance = glm::length(difference);
    
    if (distance > 0.0001f) 
        separatingForce += direction * (desiredMinimalDistance / distance);
  }

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;
  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valueHasChanged = true;
  }
  return valueHasChanged;
}
