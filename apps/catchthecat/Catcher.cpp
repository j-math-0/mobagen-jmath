#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world) {
  const std::vector<Point2D> path = generatePath(world);

  if (!path.empty()) 
      return path.front();
  else 
  {
    // Maybe find an alternative path?
  }
}
