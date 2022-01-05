#include <vector>
#include <iostream>
#include <algorithm>
#include <GridLocation.cpp>
#include <memory>

#pragma once

template<typename N, typename L>
class GridGraph
{
    friend class MapReader;

    public:
        // Constructors
        GridGraph() {};
        GridGraph(const int rows, const int cols, std::string fileName);

        // Copy constructor and copy assignment operator
        GridGraph(const GridGraph& other);
        GridGraph& operator=(const GridGraph& other);

        // Move constructor and move assigment operator
        GridGraph(GridGraph&& other) noexcept;
        GridGraph& operator=(GridGraph&& other) noexcept;

        // Pathfinding relevant methods
        std::vector<L> neighbors(L i) const;
        // Ensures Location i is inside map dimensions
        bool inBounds(L i) const;
        // Calculates cost of passing from a node to a node
        double cost(N from, N to) const;

        void setNode(N t);
        N getNode(const int x, const int y) const;

        L getStartLocation() const;
        L getEndLocation() const;

        void setPath(const std::vector<L> path);

        std::string getFileName() const;
        void printGrid() const;
        void clear() const;

    private:
        std::string fileName_;
        std::vector<std::vector<N>> grid_nodes; // Vector containg the acutal representation of a .map
        unsigned int rows_;                     // number of rows in map
        unsigned int cols_;                     // number of columns in map
};  

template<typename N, typename L>
GridGraph<N, L>::GridGraph(const int rows, const int cols, std::string fileName)
{    
    std::vector<std::vector<N>> nodes(rows, std::vector<N> (cols));

    this->fileName_ = fileName;
    this->grid_nodes = nodes;
    this->rows_ = rows;
    this->cols_ = cols;
}

template<typename N, typename L>
GridGraph<N, L>::GridGraph(const GridGraph& other)
{
    rows_ = other.rows_;
    cols_ = other.cols_;
    grid_nodes = other.grid_nodes;
    fileName_ = other.fileName_;
}

template<typename N, typename L>
GridGraph<N, L>& GridGraph<N, L>::operator=(const GridGraph& other)
{
    rows_ = other.rows_;
    cols_ = other.cols_;
    grid_nodes = other.grid_nodes;
    fileName_ = other.fileName_;
    return *this;
}

template<typename N, typename L>
GridGraph<N, L>::GridGraph(GridGraph&& other) noexcept
:   fileName_{std::move(other.fileName_)},
    grid_nodes{std::move(other.grid_nodes)},  
    rows_{std::move(other.rows_)}, 
    cols_{std::move(other.cols_)}
{}

template<typename N, typename L>
GridGraph<N, L>& GridGraph<N, L>::operator=(GridGraph&& other) noexcept
{    
    if(this != &other)
    {
        fileName_= std::move(other.fileName_);
        grid_nodes = std::move(other.grid_nodes);
        rows_ = std::move(other.rows_);
        cols_ = std::move(other.cols_);
    }
    return *this;
}

template<typename N, typename L>
std::vector<L> GridGraph<N, L>::neighbors(L i) const
{
    // Basic guarantee
    std::auto_ptr results(new std::vector<L>);

    std::array<L, 4> dirs = {
        /* East, West, North, South */
        GridLocation(1, 0), GridLocation(-1, 0),
        GridLocation(0, -1), GridLocation(0, 1)
    };

    for (L dir : dirs) 
    {
      L next{i.x_ + dir.x_, i.y_ + dir.y_};

      if (inBounds(next)) 
      {
          results->push_back(next);
      }
    }

    return *results;
}

template<typename N, typename L>
bool GridGraph<N, L>::inBounds(L i) const 
{
    return 0 <= i.x_ && i.x_ < rows_ 
        && 0 <= i.y_ && i.y_ < cols_;
}

template<typename N, typename L>
double GridGraph<N, L>::cost(N from, N to) const
{
    char node_type = to.getType();
    if(node_type == '.')
    {
        return 1;
    }
    else if(node_type == 'N')
    {
        return 20;
    }
    
    return 0;
}

template<typename N, typename L>
void GridGraph<N, L>::setNode(N t)
{
    L l = t.getLocation();
    grid_nodes[l.x_][l.y_] = t;
}

template<typename N, typename L>
N GridGraph<N, L>::getNode(const int x, const int y) const
{
    return grid_nodes[x][y];
}

template<typename N, typename L>
L GridGraph<N, L>::getStartLocation() const
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

    return L{0, 0};
}

template<typename N, typename L>
L GridGraph<N, L>::getEndLocation() const
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

    return L{0, 0};
}

template<typename N, typename L> 
void GridGraph<N, L>::printGrid() const
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

template<typename N, typename L>
void GridGraph<N, L>::setPath(const std::vector<L> path)
{
    for(auto& row : grid_nodes)
    {
        for(auto& col : row)
        {
            for(L l : path)
            {
                if(l == col.getLocation())
                {
                    col.setType('#');
                }
            }
        }
    }
}

template<typename N, typename L>
std::string GridGraph<N, L>::getFileName() const
{
    return fileName_;
}

template<typename N, typename L>
void GridGraph<N, L>::clear() const
{
    grid_nodes.clear();
}

template<typename G>
struct GraphTraits
{ };

template<typename N, typename L>
struct GraphTraits<GridGraph<N, L>>
{
    typedef N NodeType;
    typedef L LocationType;
};