#include <iostream>
#include <GridGraph.hpp>
#include <Node.hpp>
#include <fstream>
#include <iterator>
#include <boost/bind/bind.hpp>

#pragma once


/* Overloaded >> operator for converting read characters from .map files in /map directory to Node objects */
std::istream& operator>>(std::istream& i, Node& n)
{
    return i >> n.type_;
}

/* Class responsible for reading map. files and constructing corresponding graph */
class MapReader {

    public:

        /* Reads .map file and construct graph */
        template<typename Graph>
        static void readMap(Graph &grid)
        {
            std::vector<typename GraphTraits<Graph>::NodeType> buffer;

            std::cout << std::endl << "Reading file: " << grid.getFileName() << std::endl;

            std::ifstream mapFile( grid.getFileName().c_str() );          
            std::istream_iterator<char> it1( mapFile );
            std::istream_iterator<char> it2;

            copy(it1, it2, back_inserter( buffer ));
           
            int i = 0;
            std::transform(buffer.begin(), buffer.end(), buffer.begin(), boost::bind(&setPosition, boost::placeholders::_1, std::ref(i), grid.rows_, grid.cols_));

            std::for_each(buffer.begin(), buffer.end(), [&](Node const& n)
            {
                grid.setNode(n);
            });

            if(buffer.empty()) throw "Buffer empty - failed to load map";

            buffer.clear(); 
            mapFile.close();
        }

    private:
        /* No object can be constructed */
        MapReader() {};
        
        /* Calculates index for 2d vector from 1d vector index */
        static Node setPosition(Node& n, int &i, int rows, int cols)
        {
            n.setLocation(i / rows, i % cols);
            i++;
            return n;
        }
};
