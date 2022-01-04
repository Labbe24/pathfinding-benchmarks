#include <iostream>
#include <cstring>

#pragma once

class Node
{
    public:
        // Constructor
        Node(const char type = '.');

        // Copy constructor
        Node(const Node& other);

        // Assignment operator
        Node& operator=(const Node& other);

        void printNode();
        void printCoor();

        void setType(const char);
        const char& getType();


        void setLocation(const unsigned int x, const unsigned int y);
        GridLocation getLocation();

        friend std::istream& operator>> (std::istream& i, Node& n);

    private:
        char type_;
        GridLocation location_; 
};

Node::Node(const char type)
{
    type_ = type;
}

Node::Node(const Node& other)
{
    this->type_ = other.type_;
    this->location_ = other.location_;
}

Node& Node::operator=(const Node& other)
{
    type_ = other.type_;
    location_ = other.location_;
    return *this;
}

void Node::printNode()
{
    std::cout << type_;
}

void Node::setType(const char type)
{
    type_ = type;
}

const char& Node::getType()
{
    return type_;
}


void Node::setLocation(const unsigned int x, const unsigned int y)
{
    location_.x_ = x;
    location_.y_ = y;
}

GridLocation Node::getLocation()
{
    return location_;
}
