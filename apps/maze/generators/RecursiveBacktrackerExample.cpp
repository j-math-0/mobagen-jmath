#include "../World.h"
#include "../SeededRandom.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

// Recursive backtracker, in FORMAL units: (0, 0) is the top-left cell, x grows
// right, y grows down. The caller seeds SeededRandom before the first Step;
// every decision consumes the seed in order, so the maze is deterministic.
//
// Procedure per Step, on the cell at the top of the path stack:
//   1. mark it visited;
//   2. list its visitable (unvisited) neighbors in clockwise order starting
//      from the top: UP, RIGHT, DOWN, LEFT (getVisitables does this);
//   3. none        -> dead end: pop the stack (backtrack). Empty stack = done;
//   4. exactly one -> move to it, do not consume a random number;
//   5. two or more -> consume SeededRandom::next() and pick
//      next() % visitableCount;
//   6. moving opens the wall between the two cells
//      (World::SetNorth/SetEast/SetSouth/SetWest with false).

const Color32 STEP(1.0, 0.0, 0.0), COMPLETE(0.0, 0.0, 0.0);
const Point2D UP{0, -1}, DOWN{0, 1}, LEFT{-1, 0}, RIGHT{1, 0};

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  stack.push_back({0, 0});
}

bool RecursiveBacktrackerExample::Step(World* w) {
  if (stack.empty()) 
      return false;

  Point2D current = stack.back();
  
  visited[current.x][current.y] = true;

  std::vector<Point2D> visitables = getVisitables(w, current);

  if (visitables.empty())
  {
    stack.pop_back();
    w->SetNodeColor(w->ToWorldCoords(current), COMPLETE);
    return !stack.empty();
  }

  Point2D visitable;

  if (visitables.size() == 1)
    visitable = visitables.front();
  else if (visitables.size() >= 2)
    visitable = visitables[SeededRandom::next() % visitables.size()];
  
  Point2D worldCurrent = w->ToWorldCoords(current);

  if (visitable == UP)
    w->SetNorth(worldCurrent, false);
  else if (visitable == RIGHT)
    w->SetEast(worldCurrent, false);
  else if (visitable == DOWN)
    w->SetSouth(worldCurrent, false);
  else if (visitable == LEFT)
    w->SetWest(worldCurrent, false);

  stack.push_back(current + visitable);

  w->SetNodeColor(w->ToWorldCoords(current), STEP);

  return true;
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& formalPoint) {
  std::vector<Point2D> visitables;
  std::vector<Point2D> directions{UP, RIGHT, DOWN, LEFT};
 
  for (const Point2D& direction : directions) {
    int x = formalPoint.x + direction.x, y = formalPoint.y + direction.y;
    if (0 <= x && x < w->GetWidth() && 0 <= y && y < w->GetHeight() && !visited[x][y]) {
      visitables.push_back(direction);
    }
  }

  return visitables;
}
