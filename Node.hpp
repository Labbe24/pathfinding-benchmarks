#include <iostream>

#pragma once

class Node
{
    public:

    // Constructors
    Node(char type = '.');

    // Destructor
    ~Node();

    // Copy constructor
    Node(const Node& other);

    // Assignment operator
    Node& operator=(const Node& other);

    // Move Constructor
    Node(Node&& other) noexcept;

    // Move assignment operator
    Node& operator=(Node&& other) noexcept;

    void printNode();
    void printCoor();

    void setType(const char);
    const char getType();

    void setLocation(const unsigned int x, const unsigned int y);
    GridLocation getLocation();

    friend std::istream& operator>> (std::istream& i, Node& n);

    private:

    char _type;
    GridLocation _location;
};

Node::~Node()
{}

Node::Node(char type)
{
    this->_type = type;
}

Node::Node(const Node& other)
{
    this->_type = other._type;
}

Node& Node::operator=(const Node& other)
{
    this->_type = other._type;
    this->_location = other._location;
    return *this;
}

Node::Node(Node&& other) noexcept
: _type{std::move(other._type)}
{
    other._type = '\0';
}

Node& Node::operator=(Node&& other) noexcept
{
    if(this != &other)
    {
        this->_type = other._type;

        other._type = '\0';
    }
    return *this;
}

void Node::printNode()
{
    std::cout << _type;
}

void Node::setType(const char type)
{
    _type = type;
}

const char Node::getType()
{
    return _type;
}


void Node::setLocation(const unsigned int x, const unsigned int y)
{
    _location.x = x;
    _location.y = y;
}

GridLocation Node::getLocation()
{
    return _location;
}
