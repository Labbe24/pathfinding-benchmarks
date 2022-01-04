#include <Node.hpp>
#include <Benchmark.hpp>
#include <PriorityQueue.cpp>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>
#include <boost/bind/bind.hpp>

template<typename L, typename G>
class Dijkstra {

  private:
    G graph_;
    L start_;
    L end_;
    std::unordered_map<L, L>& from_;
    std::unordered_map<L, double>& cost_;


  public:

    template<typename T>
    Dijkstra(Benchmark<T>& b, G graph, L start, L goal, std::unordered_map<L, L>& from, std::unordered_map<L, double>& cost)
    : from_(from), cost_(cost)
    { 

      b.attach(boost::bind(&Dijkstra::search, this));
      graph_ = graph;
      start_ = start;
      end_ = goal;
    }

    void search()
    {
      std::cout << std::endl << "Applying dijkstra" << std::endl;
      PriorityQueue<L, double> frontier;
      frontier.put(start_, 0);

      from_[start_] = start_;
      cost_[start_] = 0;
      
      while (!frontier.empty()) {
        L current = frontier.get();

        if (current == end_) {
          break;
        }

        for (L next : graph_.neighbors(current)) 
        {
          Node currentNode = graph_.getNode(current.getX(), current.getY());
          Node nextNode = graph_.getNode(next.getX(), next.getY());
          double new_cost = cost_[current] + graph_.cost(currentNode, nextNode);

          if (cost_.find(next) == cost_.end()
              || new_cost < cost_[next]) 
          {
            cost_[next] = new_cost;
            from_[next] = current;
            frontier.put(next, new_cost);
          }
        }
      }
    }

    std::vector<L> reconstruct_path(L start, L end, std::unordered_map<L, L> from)
    {
      std::vector<L> path;
      L current = end;

      while( current != start )
      {
        path.push_back(current);
        current = from[current];
      }

      path.push_back(start);
      std::reverse(path.begin(), path.end());
      return path;
    }
};