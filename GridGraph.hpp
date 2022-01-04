#include <vector>
#include <iostream>
#include <algorithm>
#include <GridLocation.cpp>
#include <memory_resource>

#pragma once

template<typename T, typename L>
class GridGraph
{
    public:

        friend class MapReader;

        GridGraph(){};

        GridGraph(const unsigned int width, const unsigned int height, std::string fileName);

        // Copy constructor
        GridGraph(const GridGraph& other);

        // Copy assignment
        GridGraph& operator=(const GridGraph& other);

        // Pathfinding relevant
        std::vector<GridLocation> neighbors(GridLocation id) const;
        bool inBounds(GridLocation id) const;
        double cost(T from, T to) const;

        void setNode(T t);
        T getNode(unsigned int x, unsigned int y);

        GridLocation getStartLocation();
        GridLocation getEndLocation();

        void printGrid();
        void setPath(const std::vector<GridLocation> path);

        unsigned int getRows();
        unsigned int getCols();

        std::string getFileName();

        void clear();

    private:
        std::string fileName_;
        std::vector<std::vector<T>> grid_nodes;
        unsigned int rows_;
        unsigned int columns_;
        static std::array<GridLocation, 4> DIRS;
};

template<typename T, typename L>
GridGraph<T, L>::GridGraph(const unsigned int rows, const unsigned int columns, std::string fileName)
{
    std::cout << "Creating grid with " << rows << " rows and " << columns << " columns" << std::endl;
    
    std::vector<std::vector<T>> nodes(rows, std::vector<T> (columns));

    this->fileName_ = fileName;
    this->grid_nodes = nodes;
    this->rows_ = rows;
    this->columns_ = columns;
}

template<typename T, typename L>
GridGraph<T, L>::GridGraph(const GridGraph& other)
{
    operator=(other);
}

template<typename T, typename L>
GridGraph<T, L>& GridGraph<T, L>::operator=(const GridGraph& other)
{
    rows_ = other.rows_;
    columns_ = other.columns_;
    grid_nodes = other.grid_nodes;
    fileName_ = other.fileName_;
    return *this;
}

template<typename T, typename L>
std::vector<GridLocation> GridGraph<T, L>::neighbors(GridLocation id) const
{
    // Basic guarantee
    std::auto_ptr results(new std::vector<GridLocation>);

    for (GridLocation dir : DIRS) 
    {
      GridLocation next{id.getX() + dir.getX(), id.getY() + dir.getY()};

      if (inBounds(next)) results->push_back(next);
    }

    if ((id.getX() + id.getY()) % 2 == 0) 
    {
      std::reverse(results->begin(), results->end());
    }

    return *results;
}

template<typename T, typename L>
bool GridGraph<T, L>::inBounds(GridLocation id) const 
{
    return 0 <= id.getX() && id.getX() < rows_ 
        && 0 <= id.getY() && id.getY() < columns_;
}

template<typename T, typename L>
double GridGraph<T, L>::cost(T from, T to) const
{
    char node_type = to.getType();
    if(node_type == '.')
    {
        return 1;
    }
    else if(node_type == 'T')
    {
        return 20;
    }
    
    return 0;
}

template<typename T, typename L>
void GridGraph<T, L>::setNode(T t)
{
    L l = t.getLocation();
    grid_nodes[l.x_][l.y_] = t;
}

template<typename T, typename L>
T GridGraph<T, L>::getNode(unsigned int x, unsigned int y)
{
    return grid_nodes[x][y];
}

template<typename T, typename L>
GridLocation GridGraph<T, L>::getStartLocation()
{
    for(auto& row : grid_nodes)
    {
        for(auto& col : row)
        {
            if(col.getType() == 'X')
            {
                return col.getLocation();
            }
        }    
    }

    return GridLocation{0, 0};
}

template<typename T, typename L>
GridLocation GridGraph<T, L>::getEndLocation()
{
    for(auto& row : grid_nodes)
    {
        for(auto& col : row)
        {
            if(col.getType() == 'Y')
            {
                return col.getLocation();
            }
        }    
    }

    return GridLocation{0, 0};
}

template<typename T, typename L> 
void GridGraph<T, L>::printGrid()
{
    for(auto& row : grid_nodes)
    {
        for(auto& col : row)
        {
            col.printNode();
        }
        std::cout << std::endl;      
    }
}

template<typename T, typename L>
void GridGraph<T, L>::setPath(const std::vector<GridLocation> path)
{
    for(auto& row : grid_nodes)
    {
        for(auto& col : row)
        {
            for(GridLocation l : path)
            {
                if(l == col.getLocation())
                {
                    col.setType('#');
                }
            }
        }
    }
}

template<typename T, typename L>
unsigned int GridGraph<T, L>::getRows()
{
    return rows_;
}

template<typename T, typename L>
unsigned int GridGraph<T, L>::getCols()
{
    return columns_;
}

template<typename T, typename L>
std::string GridGraph<T, L>::getFileName()
{
    return fileName_;
}

template<typename T, typename L>
void GridGraph<T, L>::clear()
{
    grid_nodes.clear();
}

template<typename T, typename L>
std::array<GridLocation, 4> GridGraph<T, L>::DIRS = {
        /* East, West, North, South */
        GridLocation(1, 0), GridLocation(-1, 0),
        GridLocation(0, -1), GridLocation(0, 1)
};