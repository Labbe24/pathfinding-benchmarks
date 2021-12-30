#include <vector>
#include <iostream>

#pragma once

template<typename T>
class Grid 
{
    public:

    // Constructor
    Grid(const unsigned int width, const unsigned int height);

    // Destructor
    ~Grid();

    void printGrid();

    private:

    std::vector<std::vector<T>> grid_nodes;
    unsigned int width_;
    unsigned int height_;
};

template<typename T>
Grid<T>::Grid(const unsigned int width, const unsigned int height)
{
    std::vector<std::vector<T>> nodes(width, std::vector<T>(height));

    for(int i = 0; i < width; i++) 
    {
        for(int j = 0; j < height; j++)
        {
            nodes[i][j] = T();
        }   
    }

    this->grid_nodes = nodes;
    this->width_ = width;
    this->height_ = height;
}

template<typename T>
Grid<T>::~Grid()
{}

template<typename T> 
void Grid<T>::printGrid()
{
    for(int i = 0; i < width_; i++)
    {
        for(int j = 0; j < height_; j++)
        {
            grid_nodes[i][j].printNode();
        }
        std::cout << std::endl;
    }
}