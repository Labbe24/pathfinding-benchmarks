#include <Node.hpp>
#include <Benchmark.hpp>
#include <PriorityQueue.cpp>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/signals2.hpp>

template<typename L, typename G>
class Dijkstra {

  private:
    G graph_;
    L start_;
    L end_;
    boost::signals2::signal<void()> sig_;

  public:

    template<typename T>
    Dijkstra(Benchmark<T>& b, G graph, L start, L goal)
    { 

      b.attach(boost::bind(&Dijkstra::search, this));
      sig_.connect(boost::bind(&Benchmark<T>::done, b));
      graph_ = graph;
      start_ = start;
      end_ = goal;
    }

    void search()
    {
      std::unordered_map<L, L> from;
      std::unordered_map<L, double> cost;
      PriorityQueue<L, double> frontier;
      frontier.put(start_, 0);

      from[start_] = start_;
      cost[start_] = 0;
      
      while (!frontier.empty()) {
        L current = frontier.get();

        if (current == end_) {
          break;
        }

        for (L next : graph_.neighbors(current)) 
        {
          Node currentNode = graph_.getNode(current.getX(), current.getY());
          Node nextNode = graph_.getNode(next.getX(), next.getY());
          double new_cost = cost[current] + graph_.cost(currentNode, nextNode);

          if (cost.find(next) == cost.end()
              || new_cost < cost[next]) 
          {
            cost[next] = new_cost;
            from[next] = current;
            frontier.put(next, new_cost);
          }
        }
      }
      sig_();
    }

    std::vector<L> reconstructPath(L start, L end, std::unordered_map<L, L> from)
    {
      std::vector<L> reconstructedPath;
      L current = end;

      while( current != start )
      {
        reconstructedPath.push_back(current);
        current = from[current];
      }

      reconstructedPath.push_back(start);
      std::reverse(reconstructedPath.begin(), reconstructedPath.end());
      return reconstructedPath;
    }
};