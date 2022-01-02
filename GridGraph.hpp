#include <vector>
#include <iostream>
#include <algorithm>
#include <GridLocation.cpp>

#pragma once

template<typename T>
class GridGraph
{
    public:
    //Default constructor
    GridGraph();

    // Constructor
    GridGraph(const unsigned int width, const unsigned int height);

    // Destructor
    ~GridGraph();

    std::vector<GridLocation> neighbors(GridLocation id) const;
    bool in_bounds(GridLocation id) const;
    double cost(GridLocation from, GridLocation to) const;
    double nodeCost(T from, T to) const;
    void setNode(const unsigned int row, const unsigned int col, T t);
    T getNode(unsigned int x, unsigned int y);
    GridLocation getStartLocation();
    GridLocation getEndLocation();

    void printGrid();
    void setPath(const std::vector<GridLocation> path);
    void printSize();

    void resize(const unsigned int n, const unsigned int m);
    unsigned int getRows();
    unsigned int getCols();

    void clear();

    private:

    std::vector<std::vector<T>> grid_nodes;
    unsigned int rows_;
    unsigned int columns_;
    static std::array<GridLocation, 4> DIRS;
};

template<typename T>
GridGraph<T>::GridGraph()
{}

template<typename T>
GridGraph<T>::GridGraph(const unsigned int rows, const unsigned int columns)
{
    std::cout << "Creating GridGraph with " << rows << " rows and " << columns << " columns" << std::endl;
    
    std::vector<std::vector<T>> nodes(rows, std::vector<T> (columns, '\0'));


    /*for(auto rowIt = nodes.begin(); rowIt != nodes.end(); ++rowIt)
    { 
        for(auto colIt = rowIt->begin(); colIt != rowIt->end(); colIt++)
        {
            *colIt = T();
        }
    }*/

    this->grid_nodes = nodes;
    this->rows_ = rows;
    this->columns_ = columns;
}

template<typename T>
GridGraph<T>::~GridGraph()
{}

template<typename T>
std::vector<GridLocation> GridGraph<T>::neighbors(GridLocation id) const
{
    std::vector<GridLocation> results;

    for (GridLocation dir : DIRS) 
    {
      GridLocation next{id.x + dir.x, id.y + dir.y};

      if (in_bounds(next)) 
      {
        results.push_back(next);
      }
    }

    if ((id.x + id.y) % 2 == 0) 
    {
      // see "Ugly paths" section for an explanation:
      std::reverse(results.begin(), results.end());
    }

    return results;
}

template<typename T>
bool GridGraph<T>::in_bounds(GridLocation id) const 
{
    return 0 <= id.x && id.x < rows_ 
        && 0 <= id.y && id.y < columns_;
}

template<typename T>
double GridGraph<T>::cost(GridLocation from, GridLocation to) const
{
    return 5.5;
}

template<typename T>
double GridGraph<T>::nodeCost(T from, T to) const
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

template<typename T>
void GridGraph<T>::setNode(const unsigned int row, const unsigned int col, T t)
{
    t.setLocation(row, col);
    grid_nodes[row][col] = t;
}

template<typename T>
T GridGraph<T>::getNode(unsigned int x, unsigned int y)
{
    return grid_nodes[x][y];
}

template<typename T>
GridLocation GridGraph<T>::getStartLocation()
{
    GridLocation start;
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

template<typename T>
GridLocation GridGraph<T>::getEndLocation()
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

template<typename T> 
void GridGraph<T>::printGrid()
{
    std::cout << "Grid size: " << grid_nodes.size() << std::endl;
    
    for(auto& row : grid_nodes)
    {
        for(auto& col : row)
        {
            col.printNode();
        }
        std::cout << std::endl;      
    }
}

template<typename T>
void GridGraph<T>::setPath(const std::vector<GridLocation> path)
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

template<typename T>
void GridGraph<T>::printSize()
{
    std::cout << "grid_nodes size: " << grid_nodes.size() << std::endl;
}

template<typename T>
void GridGraph<T>::resize(const unsigned int n, const unsigned int m)
{
    grid_nodes.resize(n);
    for(int i = 0; i < n; ++i)
    {
        grid_nodes[i].resize(m);
    }
}

template<typename T>
unsigned int GridGraph<T>::getRows()
{
    return rows_;
}

template<typename T>
unsigned int GridGraph<T>::getCols()
{
    return columns_;
}

template<typename T>
void GridGraph<T>::clear()
{
    grid_nodes.clear();
}

template<typename T>
std::array<GridLocation, 4> GridGraph<T>::DIRS = {
        /* East, West, North, South */
        GridLocation{1, 0}, GridLocation{-1, 0},
        GridLocation{0, -1}, GridLocation{0, 1}
};