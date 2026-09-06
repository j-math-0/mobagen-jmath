#include "MouseInfluenceRule.h"
#include "imgui.h"

glm::vec2 MouseInfluenceRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    ImVec2 mousePos = ImGui::GetIO().MousePos;

    glm::vec2 difference = glm::vec2(mousePos.x, mousePos.y) - boid.position;
    glm::vec2 direction = glm::normalize(difference);
    float distance = glm::length(difference);
    
    // Epsilon check. Ensure the magnitude of the difference isn't a really small number
    if (distance > 0.0001f)
    {
      // The direction is flipped if the isRepulsive setting is enabled
      return (isRepulsive ? -direction : direction) * distance;
    }
  }

  return glm::vec2(0.f);
}

bool MouseInfluenceRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;

  if (ImGui::RadioButton("Attractive", !isRepulsive)) {
    isRepulsive = false;
    valueHasChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::RadioButton("Repulsive", isRepulsive)) {
    isRepulsive = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}
