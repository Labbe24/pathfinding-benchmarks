#include <iostream>
#include <GridGraph.hpp>
#include <Node.hpp>
#include <fstream>
#include <iterator>

#pragma once

std::istream& operator>>(std::istream& i, Node& n)
{
    return i >> n._type;
}

template<typename T>
void readMap(GridGraph<T>& g, const std::string& fileName)
{
    const unsigned int rows = g.getRows();
    const unsigned int cols = g.getCols();

    //g.clear();
    //g.resize(rows, cols);

    std::vector<T> buffer;

    std::ifstream mapFile( fileName.c_str() );
    
    std::istream_iterator<char> it1( mapFile );
    std::istream_iterator<char> it2;

    copy(it1, it2, back_inserter( buffer ));

    std::cout << "Buffer size: " << buffer.size() << std::endl;

    for (int i = 0; i < buffer.size(); i++)
    {
        int row = i / rows;
        int col = i % cols;
        g.setNode(row, col, buffer[i]);
    }

    g.printSize();

    buffer.clear(); 
    mapFile.close();
}

