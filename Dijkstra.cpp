#include <Node.hpp>
#include <Benchmark.hpp>
#include <PriorityQueue.cpp>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/signals2.hpp>


/* Implementation of basic dijkstra algorithm */
template<typename N, typename G>
class Dijkstra {

  public:

    template<typename T>
    Dijkstra(Benchmark<T>& b, G graph, N start, N end)
    { 

      b.attach(boost::bind(&Dijkstra::search, this));
      sig_.connect(boost::bind(&Benchmark<T>::done, b));
      graph_ = graph;
      start_ = start;
      end_ = end;
    }

    /* Applys dijkstra to provided grid with start and end markers */
    void search()
    {
      std::unordered_map<N, N> from;
      std::unordered_map<N, double> cost;
      PQ::PriorityQueue<N, double> frontier;
      frontier.put(start_, 0);

      from[start_] = start_;
      cost[start_] = 0;
      
      while (!frontier.empty()) {
        N current = frontier.get();

        if (current == end_) {
          break;
        }

        for (N next : graph_.neighbors(current)) 
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

    /* Reconstructs found path on provided grid */
    std::vector<N> reconstructPath(N start, N end, std::unordered_map<N, N> from)
    {
      std::vector<N> reconstructedPath;
      N current = end;

      while( current != start )
      {
        reconstructedPath.push_back(current);
        current = from[current];
      }

      reconstructedPath.push_back(start);
      std::reverse(reconstructedPath.begin(), reconstructedPath.end());
      return reconstructedPath;
    }

      private:
        G graph_;
        N start_;
        N end_;
        boost::signals2::signal<void()> sig_;
};