#include <Grid.hpp>
#include <Node.hpp>

int main() {
    Grid<Node> grid(3, 3);

    grid.printGrid();

    return 0;
}