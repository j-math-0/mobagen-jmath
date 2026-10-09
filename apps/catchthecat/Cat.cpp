#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(CatWorld* world) 
{
  const std::vector<Point2D> path = generatePath(world);

  if (!path.empty())
	  return path.back();
  else 
  {
	  // Alternative path?
  }
}
