#include <filesystem>
#include <string>

#include <GridGraph.hpp>
#include <Node.hpp>
#include <MapReader.hpp>
#include <Dijkstra.cpp>
#include <NodeResource.hpp>
#include <Benchmark.hpp>
#include <Timer.hpp>

#define MAP_FILES_PATH "maps"
#define ROWS 512
#define COLS 512

// Basic print method using variadics and compile-time if
template<typename T, typename... Args>
void print_info(const T& t, const Args&... args)
{
    std::cout << t;

    if constexpr(sizeof... (args) > 0)
    {
        print_info(args...);
    }
}

int main() {

    Benchmark<Timer> benchmarker;
    Benchmark<Timer> b1;
    b1 = benchmarker;
    std::vector<GridGraph<Node, GridLocation>> warcraftGrids;
    int numFiles = 0;

    // Search /maps directory for files and construct corresponding number of grids
    for(auto &entry : std::filesystem::directory_iterator(MAP_FILES_PATH))
    {   
        std::string fileName = entry.path().c_str();
        GridGraph<Node, GridLocation> g(ROWS, COLS, fileName);
        warcraftGrids.emplace_back(g);
        numFiles++;
    }
    print_info("Creating ", numFiles, " grids with ", ROWS, " rows and ", COLS, " columns");
    std::cout << std::endl;

    // Read .map files and start benchmarking dijkstra for each map
    for(GridGraph<Node, GridLocation> grid : warcraftGrids)
    {
        try
        {
            MapReader::readMap(grid);
        }
        catch(const char* msg)
        {
            std::cerr << msg << std::endl;
        }
        
        GridLocation start = grid.getStartLocation();
        GridLocation end = grid.getEndLocation();
        std::cout << "Start: " << "row " << start.getX() << ", col " << start.getY() << std::endl;
        std::cout << "End: " << "row " << end.getX() << ", col " << end.getY() << std::endl;

        Dijkstra<GridLocation, GridGraph<Node, GridLocation>> dijkstra(b1, grid, start, end);
        b1.start();
        b1.printAverageDuration();
        b1.printTotalDuration();
    }
    return 0;
}