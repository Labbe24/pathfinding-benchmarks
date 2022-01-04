#include <GridGraph.hpp>
#include <Node.hpp>
#include <MapReader.hpp>
#include <unordered_map>
#include <Dijkstra.cpp>
#include <NodeResource.hpp>
#include <chrono>
#include <memory_resource>
#include <NodeResource.hpp>
#include <filesystem>
#include <set>
#include <string>
#include <Benchmark.hpp>
#include <Timer.hpp>

#define MAP_FILE "map.txt"
#define MAP_FILES_PATH "maps"

int main() { 

    NodeResource nr; 
    std::pmr::vector<std::pmr::string> vi (&nr);
    Benchmark<Timer> benchmarker;

    std::string path_name = MAP_FILES_PATH;
    std::vector<GridGraph<Node, GridLocation>> warcraftGrids;

    for(auto &entry : std::filesystem::directory_iterator(MAP_FILES_PATH))
    {   
        GridGraph<Node, GridLocation> g(512, 512, entry.path().c_str());
        warcraftGrids.emplace_back(g);
    }

    for(GridGraph<Node, GridLocation> grid : warcraftGrids)
    {
        try
        {
            MapReader::readMap<Node, GridLocation>(grid);
        }
        catch(const char* msg)
        {
            std::cerr << msg << std::endl;
        }
        
        GridLocation start = grid.getStartLocation();
        GridLocation end = grid.getEndLocation();

        std::cout << "Start: " << "row " << start.getX() << ", col " << start.getY() << std::endl;
        std::cout << "End: " << "row " << end.getX() << ", col " << end.getY() << std::endl;

        Dijkstra<GridLocation, GridGraph<Node, GridLocation>> dijkstra(benchmarker, grid, start, end);
        benchmarker.start();
        benchmarker.printAverageDuration();
        benchmarker.printTotalDuration();
    }
    return 0;
}