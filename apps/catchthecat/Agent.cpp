#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"

using namespace std;

const Point2D BORDER_SENTINAL(INT32_MAX, INT32_MAX);

int Agent::heuristic(const CatWorld* w, const Point2D& p) 
{ 
    const int sideSize = w->getWorldSideSize() / 2;
    return min(sideSize - abs(p.x), sideSize - abs(p.y));
}

std::vector<Point2D> Agent::generatePath(CatWorld* w) 
{
  unordered_map<Point2D, int> costSoFar;
  unordered_map<Point2D, bool> visited;
  unordered_map<Point2D, Point2D> cameFrom; 
  priority_queue<pair<int, Point2D>, vector<pair<int, Point2D>>, greater<pair<int, Point2D>>> frontier;

  const Point2D catPos = w->getCat();
  Point2D borderExit = BORDER_SENTINAL;  // sentinel: no border found yet
  frontier.emplace(0, catPos);
  costSoFar.emplace(catPos, 0);

  while (!frontier.empty()) 
  {
    const pair<int, Point2D> currentPair = frontier.top();
    Point2D currentPoint = currentPair.second;
    frontier.pop();

    if (visited.find(currentPoint) != visited.end()) 
        continue;
    else if (w->catWinsOnSpace(currentPoint))
    {
        borderExit = currentPoint;
        break;
    }

    visited[currentPoint] = true;

    for (Point2D neighbor : w->neighbors(currentPoint)) 
    {
      if (visited.contains(neighbor) || !w->isValidPosition(neighbor) || w->getContent(neighbor) || neighbor == catPos) 
          continue;

      const int newCost = costSoFar[currentPoint] + 1;

      if (costSoFar.find(neighbor) == costSoFar.end() || newCost < costSoFar[neighbor]) 
      {
        costSoFar[neighbor] = newCost;
        cameFrom[neighbor] = currentPoint;
        frontier.emplace(newCost + heuristic(w, neighbor), neighbor);
      } 
    }
  }

  vector<Point2D> path;

  if (borderExit != BORDER_SENTINAL) 
  {
    Point2D current = borderExit;

    while (current != catPos) 
    {
      path.push_back(current);
      current = cameFrom.at(current);
    }
  }

  return path;
}
