#include <Node.hpp>
#include <PriorityQueue.cpp>
#include <unordered_map>
#include <stdlib.h>

template<typename Location, typename Graph>
void dijkstra_search
  (Graph graph,
   Location start,
   Location goal,
   std::unordered_map<Location, Location>& came_from,
   std::unordered_map<Location, double>& cost_so_far)
{
  PriorityQueue<Location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;
  
  while (!frontier.empty()) {
    Location current = frontier.get();

    if (current == goal) {
      break;
    }

    for (Location next : graph.neighbors(current)) 
    {
      Node currentNode = graph.getNode(current.x, current.y);
      Node nextNode = graph.getNode(next.x, next.y);
      double new_cost = cost_so_far[current] + graph.nodeCost(currentNode, nextNode);

      if (cost_so_far.find(next) == cost_so_far.end()
          || new_cost < cost_so_far[next]) 
      {
        cost_so_far[next] = new_cost;
        came_from[next] = current;
        frontier.put(next, new_cost);
      }
    }
  }
}

template<typename Location>
std::vector<Location> reconstruct_path(
  Location start,
  Location end,
  std::unordered_map<Location, Location> from)
{
  std::vector<Location> path;
  Location current = end;

  while( current != start )
  {
    path.push_back(current);
    current = from[current];
  }

  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}