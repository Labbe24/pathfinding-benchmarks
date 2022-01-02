#include <GridGraph.hpp>
#include <Node.hpp>
#include <MapReader.hpp>
#include <unordered_map>
#include <Dijkstra.cpp>

#define MAP_FILE "map.txt"

int main() {
    GridGraph<Node> grid(512, 512);
    readMap<Node>(grid, MAP_FILE);

    //grid.printGrid();
    //GridLocation start{50, 450}, goal{80, 333};

    GridLocation start = grid.getStartLocation();
    GridLocation end = grid.getEndLocation();

    std::cout << "Start: " << start.x << ", " << start.y << std::endl;
    std::cout << "End: " << end.x << ", " << end.y << std::endl;

    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;
    dijkstra_search<GridLocation, GridGraph<Node>>(grid, start, end, came_from, cost_so_far);
    std::vector<GridLocation> path = reconstruct_path(start, end, came_from);

    /*for(GridLocation l : path)
    {
        std::cout << "x: " << l.x << ", y: " << l.y << std::endl;
    }*/
    grid.setPath(path);
    grid.printGrid();

    return 0;
}