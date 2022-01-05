#include <iostream>
#include <cstring>

#pragma once

class Node
{
    public:
        // Constructor with default argument
        Node(const char type = '.');

        // Copy constructor
        Node(const Node& other);

        // Assignment operator
        Node& operator=(const Node& other);

        void printNode() const;
     
        void setType(const char);
        const char getType() const;

        void setLocation(const int x, const int y);
        GridLocation getLocation() const;

        // Used for converting character in .map fil to type Node
        friend std::istream& operator>> (std::istream& i, Node& n);

    private:
        char type_;             // Helps determine cost of passing through node
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

void Node::printNode() const
{
    std::cout << type_;
}

void Node::setType(const char type)
{
    type_ = type;
}

const char Node::getType() const
{
    return type_;
}


void Node::setLocation(const int x, const int y)
{
    location_.x_ = x;
    location_.y_ = y;
}

GridLocation Node::getLocation() const
{
    return location_;
}
