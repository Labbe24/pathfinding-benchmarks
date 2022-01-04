#include <iostream>
#include <GridGraph.hpp>
#include <Node.hpp>
#include <fstream>
#include <iterator>
#include <chrono>
#include <boost/bind/bind.hpp>

#pragma once

 std::istream& operator>>(std::istream& i, Node& n)
{
    return i >> n.type_;
}

class MapReader {

    public:

        template<typename T, typename L>
        static void readMap(GridGraph<T, L>& g)
        {
            unsigned int i = 0;
            std::vector<T> buffer;

            std::cout << std::endl << "Reading file: " << g.getFileName() << std::endl;

            std::ifstream mapFile( g.getFileName().c_str() );          
            std::istream_iterator<char> it1( mapFile );
            std::istream_iterator<char> it2;

            copy(it1, it2, back_inserter( buffer ));
           
            std::transform(buffer.begin(), buffer.end(), buffer.begin(), boost::bind(&setPos<Node, GridLocation>, boost::placeholders::_1, std::ref(g), std::ref(i), g.rows_, g.columns_));

            if(buffer.empty()) throw "Buffer empty - failed to load map";

            buffer.clear(); 
            mapFile.close();
        }

        template<typename T, typename L>
        static Node setPos(Node n, GridGraph<T, L> &g, unsigned int& i, int rows, int cols)
        {
            n.setLocation(i / rows, i % cols);
            g.setNode(n);
            i++;
            return n;
        }

    private:
        MapReader() {};
};
