#include <iostream>

#pragma once

class Node
{
    public:

    // Constructor
    Node(char type = 'L');

    // Destructor
    ~Node();

    // Copy constructor
    Node(const Node& other);

    // Assignment operator
    Node& operator=(const Node& other);

    // Move Constructor
    Node(Node&& other);

    // Move assignment operator
    Node& operator=(Node&& other) noexcept;

    void printNode();

    private:

    char _type;
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
    return *this;
}

Node::Node(Node&& other)
: _type('.')
{
    this->_type = other._type;

    other._type = NULL;
}

Node& Node::operator=(Node&& other) noexcept
{
    if(this != &other)
    {
        this->_type = other._type;

        other._type = NULL;
    }
}

void Node::printNode()
{
    std::cout << _type;
}